"""Captured states: the registers of one thread at a function's entry plus every committed page of the process.

Pages are content-addressed (blake2b-128) in one append-only store shared by all states, so the dozens of
snapshots of a session cost only the pages that changed between them. A .state file is a JSON header line
(registers, thread, modules, time) followed by its page table: sorted (page address u32, store offset u64) pairs.
Everything lives in local/difftest/ (ignored): the pages are the game's memory, never committed.
"""

import hashlib
import json
import mmap
import pathlib
import struct
import time

from . import project

PAGE = project.PAGE
ZERO = bytes(PAGE)
ENTRY = struct.Struct("<IQ")


class PageStore:
	def __init__(self, directory=project.STORE):
		directory = pathlib.Path(directory)
		directory.mkdir(parents=True, exist_ok=True)
		self.binPath = directory / "pages.bin"
		self.idxPath = directory / "pages.idx"
		self.binPath.touch()
		self.idxPath.touch()
		self.index = {}
		raw = self.idxPath.read_bytes()
		for i in range(0, len(raw) - len(raw) % 24, 24):
			self.index[raw[i:i + 16]] = struct.unpack_from("<Q", raw, i + 16)[0]
		self.bin = open(self.binPath, "r+b")
		self.bin.seek(0, 2)
		self.size = self.bin.tell()
		self.idx = open(self.idxPath, "ab")
		self.map = None
		self.pending = []
		self.zeroOffset = None

	def put(self, page):
		"""Stores one page (bytes of PAGE length) unless known; returns its offset."""
		digest = hashlib.blake2b(page, digest_size=16).digest()
		offset = self.index.get(digest)
		if offset is None:
			offset = self.size
			self.pending.append(page)
			self.size += PAGE
			self.index[digest] = offset
			self.idx.write(digest + struct.pack("<Q", offset))
			if len(self.pending) >= 4096:
				self.flush()
		return offset

	def flush(self):
		if self.pending:
			self.bin.seek(0, 2)
			self.bin.write(b"".join(self.pending))
			self.pending = []
		self.bin.flush()
		self.idx.flush()
		self.map = None

	def get(self, offset):
		if self.pending:
			self.flush()
		if self.map is None or len(self.map) < self.size:
			if self.map is not None:
				self.map.close()
			if self.size == 0:
				return None
			self.map = mmap.mmap(self.bin.fileno(), 0, access=mmap.ACCESS_READ)
		return self.map[offset:offset + PAGE]

	def close(self):
		self.flush()
		if self.map is not None:
			self.map.close()
		self.bin.close()
		self.idx.close()


class State:
	"""One captured entry state. `pages` maps page address -> offset in the store."""

	def __init__(self, header, pages, path=None):
		self.header = header
		self.pages = pages
		self.path = path

	@property
	def regs(self):
		return self.header["regs"]

	@property
	def address(self):
		return self.header["address"]

	@property
	def modules(self):
		return self.header.get("modules", [])

	def module(self, address):
		for module in self.modules:
			if module["base"] <= address < module["base"] + module["size"]:
				return module
		return None

	def save(self, path):
		path = pathlib.Path(path)
		path.parent.mkdir(parents=True, exist_ok=True)
		table = b"".join(ENTRY.pack(address, offset) for address, offset in sorted(self.pages.items()))
		with open(path, "wb") as f:
			f.write(json.dumps(self.header).encode("utf-8") + b"\n")
			f.write(table)
		self.path = path

	@classmethod
	def load(cls, path):
		path = pathlib.Path(path)
		raw = path.read_bytes()
		newline = raw.index(b"\n")
		header = json.loads(raw[:newline].decode("utf-8"))
		pages = {}
		table = raw[newline + 1:]
		for i in range(0, len(table) - len(table) % ENTRY.size, ENTRY.size):
			address, offset = ENTRY.unpack_from(table, i)
			pages[address] = offset
		return cls(header, pages, path)

	def describe(self):
		regs = self.regs
		return "%s tid %d eip 0x%08X esp 0x%08X ecx 0x%08X %s" % (self.path.name if self.path else "state",
			self.header.get("tid", 0), regs["eip"], regs["esp"], regs["ecx"], self.header.get("when", ""))


def newHeader(address, regs, tid, fsBase, modules, context=b""):
	return {"address": address, "regs": regs, "tid": tid, "fsBase": fsBase, "modules": modules,
		"context": context.hex(), "when": time.strftime("%Y-%m-%d %H:%M:%S"), "version": project.VERSION}


def snapshotRegions(store, regions, reader):
	"""Captures the given [(address, size)] regions through reader(address, size) -> bytes (or None when a
	region cannot be read, in which case it is retried page by page). Returns the page table."""
	pages = {}
	for address, size in regions:
		data = reader(address, size)
		if data is None:
			for page in range(address, address + size, PAGE):
				chunk = reader(page, PAGE)
				if chunk is not None and len(chunk) == PAGE:
					pages[page] = store.put(bytes(chunk))
			continue
		view = memoryview(data)
		for i in range(0, len(view) - len(view) % PAGE, PAGE):
			pages[address + i] = store.put(bytes(view[i:i + PAGE]))
	return pages
