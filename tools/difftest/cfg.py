"""Static facts about a function's code: basic blocks, `ret N`, registers read before they are written, and the
engine's call sites of it. Capstone over bytes the caller supplies (the original image is read from orig/, our
function from the build's object; nothing is written anywhere)."""

import struct

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_OP_REG, X86_REG_EAX, X86_REG_ECX, X86_REG_EDX, X86_REG_EBX, \
	X86_REG_ESI, X86_REG_EDI, X86_REG_EBP, X86_REG_ESP, X86_REG_AL, X86_REG_AX, X86_REG_CL, X86_REG_CX, X86_REG_DL, \
	X86_REG_DX, X86_REG_BL, X86_REG_BX, X86_REG_AH, X86_REG_CH, X86_REG_DH, X86_REG_BH, X86_REG_SI, X86_REG_DI, X86_REG_BP

md = Cs(CS_ARCH_X86, CS_MODE_32)
md.detail = True

JUMPS = {"jmp", "ja", "jae", "jb", "jbe", "jc", "je", "jg", "jge", "jl", "jle", "jna", "jnae", "jnb", "jnbe", "jnc", "jne",
	"jng", "jnge", "jnl", "jnle", "jno", "jnp", "jns", "jnz", "jo", "jp", "jpe", "jpo", "js", "jz", "jcxz", "jecxz", "loop",
	"loope", "loopne"}
ENDS = {"ret", "retn", "retf", "int3", "hlt", "ud2"}

# sub-registers folded into their 32-bit register for the input analysis
FULL = {X86_REG_AL: X86_REG_EAX, X86_REG_AH: X86_REG_EAX, X86_REG_AX: X86_REG_EAX, X86_REG_EAX: X86_REG_EAX,
	X86_REG_CL: X86_REG_ECX, X86_REG_CH: X86_REG_ECX, X86_REG_CX: X86_REG_ECX, X86_REG_ECX: X86_REG_ECX,
	X86_REG_DL: X86_REG_EDX, X86_REG_DH: X86_REG_EDX, X86_REG_DX: X86_REG_EDX, X86_REG_EDX: X86_REG_EDX,
	X86_REG_BL: X86_REG_EBX, X86_REG_BH: X86_REG_EBX, X86_REG_BX: X86_REG_EBX, X86_REG_EBX: X86_REG_EBX,
	X86_REG_SI: X86_REG_ESI, X86_REG_ESI: X86_REG_ESI, X86_REG_DI: X86_REG_EDI, X86_REG_EDI: X86_REG_EDI,
	X86_REG_BP: X86_REG_EBP, X86_REG_EBP: X86_REG_EBP}
NAMES = {X86_REG_EAX: "eax", X86_REG_ECX: "ecx", X86_REG_EDX: "edx", X86_REG_EBX: "ebx", X86_REG_ESI: "esi",
	X86_REG_EDI: "edi", X86_REG_EBP: "ebp"}


def disassemble(code, address):
	return list(md.disasm(code, address))


def jumpTarget(insn):
	if insn.mnemonic in JUMPS and insn.operands and insn.operands[0].type == X86_OP_IMM:
		return insn.operands[0].imm
	return None


def basicBlocks(code, address):
	"""[(start, end)] of the function's blocks: leaders are the entry, every jump target inside the function and
	the instruction after a jump or return. Instructions not reachable linearly (jump tables' data) are left out."""
	insns = disassemble(code, address)
	if not insns:
		return [], []
	end = address + len(code)
	starts = {address}
	for i, insn in enumerate(insns):
		target = jumpTarget(insn)
		if target is not None and address <= target < end:
			starts.add(target)
		if (target is not None or insn.mnemonic in ENDS) and i + 1 < len(insns):
			starts.add(insns[i + 1].address)
	leaders = sorted(starts)
	blocks = []
	for i, start in enumerate(leaders):
		stop = leaders[i + 1] if i + 1 < len(leaders) else insns[-1].address + insns[-1].size
		blocks.append((start, stop))
	return blocks, insns


def retImmediates(code, address):
	"""The set of byte counts the function's `ret` instructions pop (0 for a plain ret)."""
	result = set()
	for insn in disassemble(code, address):
		if insn.mnemonic in ("ret", "retn"):
			result.add(int(insn.op_str, 16) if insn.op_str else 0)
	return result


def hasInstruction(code, address, mnemonics):
	return [insn.address for insn in disassemble(code, address) if insn.mnemonic in mnemonics]


def registerInputs(code, address, limit=400):
	"""Registers a function reads before it writes them, along a linear sweep of its first instructions
	(stopped at the first return): its register arguments, approximately. Returns a set of names."""
	written = set()
	inputs = set()
	for insn in disassemble(code, address)[:limit]:
		if insn.mnemonic in ("ret", "retn"):
			break
		read, write = insn.regs_access()
		# an operand's memory base / index registers count as reads too (capstone lists them in regs_access)
		for reg in read:
			full = FULL.get(reg)
			if full is not None and full not in written:
				inputs.add(NAMES[full])
		# xor reg, reg and sub reg, reg define the register without reading it
		if insn.mnemonic in ("xor", "sub", "pxor") and len(insn.operands) == 2 and insn.operands[0].type == X86_OP_REG \
				and insn.operands[1].type == X86_OP_REG and insn.operands[0].reg == insn.operands[1].reg:
			full = FULL.get(insn.operands[0].reg)
			if full is not None:
				inputs.discard(NAMES[full])
		for reg in write:
			full = FULL.get(reg)
			if full is not None:
				written.add(full)
	return inputs


def stackCleanup(readCode, address, limit=0x2000):
	"""How many bytes the function at `address` pops on return, found from its first `ret` along a linear sweep
	(following jmp thunks); None when no ret is found. `readCode(address, size)` supplies bytes."""
	for _ in range(4):
		head = readCode(address, 6)
		if head is None:
			return None
		if head[0] == 0xE9:
			address = (address + 5 + struct.unpack_from("<i", head, 1)[0]) & 0xFFFFFFFF
			continue
		if head[0] == 0xFF and head[1] == 0x25:
			return None  # import thunk: the real target is in another module
		break
	code = readCode(address, limit)
	if code is None:
		return None
	for insn in md.disasm(code, address):
		if insn.mnemonic in ("ret", "retn"):
			return int(insn.op_str, 16) if insn.op_str else 0
		if insn.mnemonic == "jmp" and insn.operands and insn.operands[0].type == X86_OP_IMM:
			target = insn.operands[0].imm
			if not (address <= target < address + limit):
				return stackCleanup(readCode, target, limit) if target != address else None
	return None


def callerCleanup(readCode, returnAddress):
	"""Bytes a caller removes right after a call: `add esp, N`, or pops into scratch registers (pop ecx)."""
	code = readCode(returnAddress, 16)
	if code is None:
		return 0
	total = 0
	for insn in md.disasm(code, returnAddress):
		if insn.mnemonic == "add" and insn.operands[0].type == X86_OP_REG and insn.operands[0].reg == X86_REG_ESP \
				and insn.operands[1].type == X86_OP_IMM:
			return total + insn.operands[1].imm
		if insn.mnemonic == "pop" and insn.operands[0].type == X86_OP_REG and insn.operands[0].reg in (X86_REG_ECX, X86_REG_EDX):
			total += 4
			continue
		break
	return total


def callerPushes(readCode, returnAddress, functionStart, limit=0x1000):
	"""Dwords pushed by the caller between its previous call (or its start) and the call that returns to
	`returnAddress`: the arguments of a stdcall / COM callee (`this` included), 4 bytes each. None when the
	instruction before the return address is not a call."""
	if functionStart is None or not (0 < returnAddress - functionStart <= limit):
		return None
	code = readCode(functionStart, returnAddress - functionStart)
	if code is None:
		return None
	pushes = 0
	prologue = True  # the saves of ebx, esi, edi, ebp at the start are not arguments
	saved = {X86_REG_EBX, X86_REG_ESI, X86_REG_EDI, X86_REG_EBP}
	for insn in md.disasm(code, functionStart):
		if prologue:
			if insn.mnemonic == "push" and insn.operands[0].type == X86_OP_REG and insn.operands[0].reg in saved:
				continue
			if insn.mnemonic in ("mov", "sub", "and", "lea") and insn.operands and insn.operands[0].type == X86_OP_REG \
					and insn.operands[0].reg in (X86_REG_EBP, X86_REG_ESP, X86_REG_EDI):
				continue
			prologue = False
		if insn.mnemonic == "call":
			if insn.address + insn.size == returnAddress:
				return pushes
			pushes = 0
		elif insn.mnemonic == "push":
			pushes += 1
		elif insn.mnemonic == "sub" and insn.operands and insn.operands[0].type == X86_OP_REG and insn.operands[0].reg == X86_REG_ESP \
				and insn.operands[1].type == X86_OP_IMM:
			pushes += insn.operands[1].imm // 4
		elif insn.mnemonic in ("add", "pop") and insn.operands and insn.operands[0].type == X86_OP_REG and insn.operands[0].reg == X86_REG_ESP:
			pushes = 0
	return None


def directCallSites(image, address):
	"""[(site, viaThunk)] of every `call rel32` in the image's .text that reaches `address` directly or through
	an incremental-link jmp thunk; also the number of data words holding the address (vtables, tables)."""
	text, textEnd = image.textRange()
	data = image.data
	thunks = set()
	offset = text - image.base
	end = textEnd - image.base
	i = data.find(b"\xE9", offset, end)
	while i != -1:
		target = (image.base + i + 5 + struct.unpack_from("<i", data, i + 1)[0]) & 0xFFFFFFFF
		if target == address:
			thunks.add(image.base + i)
		i = data.find(b"\xE9", i + 1, end)
	targets = thunks | {address}
	sites = []
	i = data.find(b"\xE8", offset, end)
	while i != -1:
		target = (image.base + i + 5 + struct.unpack_from("<i", data, i + 1)[0]) & 0xFFFFFFFF
		if target in targets:
			sites.append((image.base + i, target != address))
		i = data.find(b"\xE8", i + 1, end)
	needle = struct.pack("<I", address)
	words = 0
	for name, start, stop, writable, executable in image.sections:
		if executable:
			continue
		j = data.find(needle, start - image.base, stop - image.base)
		while j != -1:
			words += 1
			j = data.find(needle, j + 1, stop - image.base)
	return sites, words


def callSiteArguments(image, site, functionStart):
	"""What a call site passes, from the instructions between the previous call (or the function start) and the
	call: pushes counted, registers set (ecx, edx, eax) and the caller's cleanup after the call."""
	start = max(functionStart, site - 200) if functionStart else site - 200
	insns = disassemble(image.read(start, site - start), start)
	pushes = 0
	regs = {}
	for insn in insns:
		if insn.mnemonic == "call":
			pushes = 0
			regs = {}
			continue
		if insn.mnemonic == "push":
			pushes += 1
		elif insn.mnemonic in ("sub",) and insn.operands and insn.operands[0].type == X86_OP_REG and insn.operands[0].reg == X86_REG_ESP \
				and insn.operands[1].type == X86_OP_IMM:
			pushes += insn.operands[1].imm // 4
		elif insn.mnemonic in ("add",) and insn.operands and insn.operands[0].type == X86_OP_REG and insn.operands[0].reg == X86_REG_ESP:
			pushes = 0
		read, write = insn.regs_access()
		for reg in write:
			full = FULL.get(reg)
			if full in (X86_REG_ECX, X86_REG_EDX, X86_REG_EAX):
				regs[NAMES[full]] = insn.mnemonic + " " + insn.op_str
	cleanup = callerCleanup(lambda a, n: image.read(a, n) if image.contains(a) else None, site + 5)
	return {"site": site, "pushes": pushes, "regs": regs, "callerCleanup": cleanup}
