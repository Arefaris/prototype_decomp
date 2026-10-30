// content::LoadStream (RTTI name; 0x4C bytes, member names guessed): a stream over a file read through two buffers of
// the stream buffer pool, a block of memory or a compressed file (unit 0x1060A410 - 0x1060B890, the pool and the
// thread that unpacks compressed files are in front of and behind it).
#include "code/content/chunkhandler.h"
#include "code/content/loadmanager.h"
#include "code/core/file/filepath.h"
#include "code/core/heap.h"
#include "code/core/file/filesystem.h"
#include "code/core/memory/align.h"
#include "code/core/memory/memoryspace.h"
#include "code/core/memutils.h"
#include "code/core/strings.h"
#include <string.h>

namespace content
{
	// 0x10645E80 with the argument the engine passes (the function ignores it; core::MemorySpaceIsAccessible)
}
namespace core
{
	bool MemorySpaceIsAccessible(void* block);
}
namespace content
{
	// The stream buffer pool (0x11276A88 / 0x11276A8C / 0x11276A90: its aligned start, the size of one of its blocks
	// and whether the pool is memory somebody else gave; names guessed)
	extern unsigned int gStreamPool;
	extern unsigned int gStreamBlockSize;
	extern bool gStreamPoolBorrowed;
	// 0x11276B7C: set while a stream waits for its file's signal
	extern bool gStreamWaiting;

	// The thread that unpacks compressed files (0x11276A98, name guessed)
	class CompressedFileFactory
	{
	public:
		// 0x1060BE40: starts the thread (from the heap)
		void Start(int heap);
		// 0x1060BC20: stops it
		void Stop();
		// 0x1060BEA0
		void Create(core::IFile** result, core::IFile* file, unsigned int start, unsigned int size, int unused);
	};
	extern CompressedFileFactory gCompressedFileFactory;

	// 0x1060A470 / 0x1060A4E0: gives the streams their buffer pool and starts the thread that unpacks compressed
	// files / stops them
	void InitStreamPool(int heap, void* memory, unsigned int size);
	void ShutdownStreamPool();

	// 0x1060BE20: whether the name ends in the extension of compressed files
	bool IsCompressedName(const char* path);

	// FUNCTION: ENGINE 0x1060A420
	// EQUIVALENT: the engine's convention passes only the flag in a register (al), ours also the start and takes the
	// flag in cl; every caller is in this unit
	// The start and the size of the blocks that the region from start to end gives when it is cut into parts
	// (coarse: blocks of a multiple of 2 KB instead of 128 bytes)
	__declspec(noinline) static void SplitRegion(unsigned int parts, unsigned int start, unsigned int end,
		unsigned int* alignedStart, unsigned int* blockSize, bool coarse)
	{
		unsigned int granularity = coarse ? 0x800 : 0x80;
		unsigned int first = core::RoundUp(start, 0x80);
		unsigned int block = core::RoundDown((end - first) / parts, granularity);
		*alignedStart = first;
		*blockSize = block;
	}

	// FUNCTION: ENGINE 0x1060A470
	// EQUIVALENT: the call of SplitRegion, which takes the engine's start in a register in ours (see SplitRegion)
	// Gives the streams their buffer pool (2 MB from the heap when memory is null) and starts the thread that unpacks
	// compressed files
	void InitStreamPool(int heap, void* memory, unsigned int size)
	{
		if (gStreamPool == 0)
		{
			unsigned int start = (unsigned int)memory;
			unsigned int end;
			if (memory != 0)
			{
				end = size + start;
				gStreamPoolBorrowed = true;
			}
			else
			{
				start = (unsigned int)core::HeapAllocAligned(heap, 0x200000, 0x80);
				end = start + 0x200000;
				gStreamPoolBorrowed = false;
			}
			SplitRegion(1, start, end, &gStreamPool, &gStreamBlockSize, true);
		}
		gCompressedFileFactory.Start(heap);
	}

	// FUNCTION: ENGINE 0x1060A4E0
	void ShutdownStreamPool()
	{
		gCompressedFileFactory.Stop();
		if (gStreamPool != 0 && !gStreamPoolBorrowed)
		{
			core::FreeAligned((void*)gStreamPool);
		}
		gStreamPool = 0;
		gStreamBlockSize = 0;
	}

	// FUNCTION: ENGINE 0x1060A520
	unsigned int LoadStream::GetSize()
	{
		return size;
	}

	// FUNCTION: ENGINE 0x1060A530
	unsigned int LoadStream::GetPosition()
	{
		return position;
	}

	// FUNCTION: ENGINE 0x1060A540
	int LoadStream::GetSource()
	{
		int source = 0;
		if (file == 0)
		{
			source = (compressed != 0) + 1;
		}
		return source;
	}

	// FUNCTION: ENGINE 0x1060A560
	const char* LoadStream::GetName()
	{
		return file->GetName();
	}

	// FUNCTION: ENGINE 0x1060A570
	void LoadStream::Reset()
	{
		file = 0;
		compressed = 0;
		opened = false;
		blocking = false;
		buffered = false;
		swapped = false;
		unknown14 = false;
		size = 0;
		position = 0;
		filePosition = 0;
		currentBuffer = 0;
		buffers[0] = 0;
		buffers[1] = 0;
		current = 0;
		offset = 0;
		fill = 0;
		lastRead = 0;
		bufferSize = 0;
		unknown44 = 0;
		sinceYield = 0;
	}

	// FUNCTION: ENGINE 0x1060A5B0
	// EQUIVALENT: the engine keeps the path in ebp from the start, ours in esi and copies it to ebp, best 58.1%
	void LoadStream::Open(const char* path, bool compressedName)
	{
		const char* original = 0;
		char name[0x104];
		if (compressedName)
		{
			unsigned int length = 0;
			core::StrNCpy(name, path, 0x101, &length);
			name[length] = '.';
			name[length + 1] = 'r';
			name[length + 2] = 'z';
			name[length + 3] = 0;
			original = path;
			core::FileSystemOpenFileAsync(&file, core::FilePath(name), false, 0, 1, 0, 1, 1, 0);
		}
		else
		{
			core::FileSystemOpenFileAsync(&file, core::FilePath(path), false, 0, 1, 0, 1, 1, 0);
		}
		if (file == 0)
		{
			opened = false;
			return;
		}
		unknown44 = 0;
		Prepare(true, original);
	}

	// FUNCTION: ENGINE 0x1060A670
	void LoadStream::Attach(const void* data, unsigned int newSize)
	{
		opened = true;
		current = (unsigned int)data;
		size = newSize;
		fill = newSize;
		bufferSize = newSize;
		currentBuffer = 0;
		offset = 0;
		filePosition = 0;
		position = 0;
		lastRead = 0;
		buffered = true;
	}

	// FUNCTION: ENGINE 0x1060A6A0
	// Copies size bytes from source to destination (mode 1: with the processor; otherwise by the memory space
	// copy request, which is waited for)
	void LoadStream::Copy(void* destination, const void* source, unsigned int length, int mode)
	{
		if (mode == 1)
		{
			if (length >= 0x400)
			{
				if (core::MemorySpaceIsAccessible(destination))
				{
					core::MemCopyUnchecked(destination, source, length);
					return;
				}
				core::MemCopy(destination, source, length);
				return;
			}
			memcpy(destination, source, length);
			return;
		}
		core::IMemorySpaceCopyRequest* request = core::MemorySpaceCopyAsync(destination, mode, source, 1, length);
		request->AddRef();
		while (!request->IsComplete())
		{
			gLoadManager->Yield();
		}
		request->Release();
	}

	// FUNCTION: ENGINE 0x1060A770
	// EQUIVALENT: the engine keeps the object in edi and the length in esi, ours the other way round
	void LoadStream::ReadBlock(void* buffer)
	{
		unsigned int total = size;
		unsigned int done = filePosition;
		unsigned int length = bufferSize;
		if (done < total)
		{
			if (file != 0)
			{
				if (done + length >= total)
				{
					length = total - done;
					unsigned int granularity = file->GetGranularity();
					file->Read(buffer, core::RoundUp(length, granularity), 1);
					filePosition += length;
					lastRead = length;
					return;
				}
				file->Read(buffer, length, 1);
				filePosition += length;
				lastRead = length;
				return;
			}
			if (done + length >= total)
			{
				length = total - done;
				compressed->Read(buffer, core::RoundUp(length, 0x80));
				filePosition += length;
				lastRead = length;
				return;
			}
			compressed->Read(buffer, length);
			filePosition += length;
			lastRead = length;
		}
	}

	// FUNCTION: ENGINE 0x1060A830
	// EQUIVALENT: block layout: the engine loads the file before it tests the blocking flag
	void LoadStream::Wait()
	{
		if (file != 0)
		{
			if (blocking)
			{
				gStreamWaiting = true;
				file->WaitSignal();
				gStreamWaiting = false;
				return;
			}
			while (!file->IsIdle())
			{
				gLoadManager->Yield();
			}
			return;
		}
		if (compressed != 0)
		{
			if (blocking)
			{
				compressed->Wait();
				return;
			}
			while (!compressed->IsDone())
			{
				gLoadManager->Yield();
			}
		}
	}

	// FUNCTION: ENGINE 0x1060A8C0
	// EQUIVALENT: register allocation of the swap loop
	void LoadStream::SwapBytes(void* data, int count, int itemSize)
	{
		if (swapped && itemSize != 1)
		{
			unsigned char* bytes = (unsigned char*)data;
			for (; count != 0; count--)
			{
				unsigned char* last = bytes + itemSize - 1;
				unsigned char* first = bytes;
				if (bytes < last)
				{
					do
					{
						unsigned char saved = *first;
						*first = *last;
						*last = saved;
						first++;
						last--;
					}
					while (first < last);
				}
				bytes += itemSize;
			}
		}
	}

	// FUNCTION: ENGINE 0x1060AB50
	// EQUIVALENT: scheduling and registers
	void LoadStream::SetBuffers(unsigned int region, unsigned int regionSize)
	{
		if (!buffered)
		{
			currentBuffer = 0;
			buffers[0] = region;
			bufferSize = regionSize;
			fill = size;
			return;
		}
		if (regionSize < size)
		{
			unsigned int start = 0;
			unsigned int block = 0;
			SplitRegion(2, region, regionSize + region, &start, &block, file != 0);
			buffers[1] = block + start;
			region = start;
			regionSize = block;
		}
		else
		{
			buffers[1] = 0;
			currentBuffer = 1;
		}
		buffers[0] = region;
		bufferSize = regionSize;
		ReadBlock((void*)buffers[currentBuffer == 0]);
		Wait();
	}

	// FUNCTION: ENGINE 0x1060ABF0
	void LoadStream::SkipDirect(int bytes)
	{
		file->SetPosition(position + bytes);
		position += bytes;
		if (blocking)
		{
			Wait();
		}
	}

	// FUNCTION: ENGINE 0x1060AC20
	bool LoadStream::ReadDirect(void* destination, int count, int itemSize, int option)
	{
		int length = count * itemSize;
		if (file != 0)
		{
			file->Read(destination, length, option);
		}
		else
		{
			compressed->Read(destination, length);
		}
		position += length;
		Wait();
		SwapBytes(destination, count, itemSize);
		return true;
	}

	// FUNCTION: ENGINE 0x1060AC80
	void LoadStream::NextBuffer()
	{
		Wait();
		currentBuffer = currentBuffer == 0;
		current = buffers[currentBuffer];
		offset = 0;
		fill = lastRead;
		ReadBlock((void*)buffers[currentBuffer == 0]);
	}

	// FUNCTION: ENGINE 0x1060B130
	// EQUIVALENT: scheduling and registers
	bool LoadStream::ReadBuffered(void* destination, int count, int itemSize, int option)
	{
		int length = count * itemSize;
		sinceYield += length;
		if (offset + length > fill)
		{
			unsigned char* target = (unsigned char*)destination;
			while (length > 0)
			{
				int part = length;
				if (offset + length > fill)
				{
					part = fill - offset;
				}
				Copy(target, (unsigned char*)current + offset, part, option);
				offset += part;
				position += part;
				length -= part;
				if (length <= 0)
				{
					break;
				}
				NextBuffer();
				target += part;
			}
		}
		else
		{
			Copy(destination, (unsigned char*)current + offset, length, option);
			offset += length;
			position += length;
		}
		if (swapped)
		{
			SwapBytes(destination, count, itemSize);
		}
		if (!blocking && sinceYield >= 0x8000)
		{
			gLoadManager->Idle();
			sinceYield = 0;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x1060B010
	// EQUIVALENT: scheduling and registers
	void LoadStream::Prepare(bool force, const char* path)
	{
		if (unknown14 || force)
		{
			unknown14 = false;
			if (!file->IsOpen())
			{
				Wait();
			}
			if (file->IsOpen())
			{
				opened = true;
				unsigned int region = gStreamPool;
				unsigned int regionSize = gStreamBlockSize;
				if (IsCompressedName(file->GetName()))
				{
					unsigned int start = 0;
					unsigned int block = 0;
					SplitRegion(2, region, region + regionSize, &start, &block, true);
					region = start + block;
					regionSize = block;
					core::IFile* result = 0;
					gCompressedFileFactory.Create(&result, file, start, block, 1);
					file->Release();
					file = result;
					Wait();
				}
				size = file->GetCurrentSize();
				SetBuffers(region, regionSize);
				return;
			}
			if (path != 0)
			{
				file->Release();
				file = 0;
				Open(path, false);
				return;
			}
			opened = false;
		}
	}

	// FUNCTION: ENGINE 0x1060AA00
	LoadStream::LoadStream(const char* path, int unused, int mode)
	{
		Reset();
		buffered = mode == 1;
		blocking = true;
		Open(path, true);
	}

	// FUNCTION: ENGINE 0x1060AA40
	LoadStream::LoadStream(LoadRequest* request, int unused, int mode)
	{
		Reset();
		buffered = mode == 1;
		blocking = request->blocking;
		Open(request->Data(), true);
	}

	// FUNCTION: ENGINE 0x1060AA90
	// EQUIVALENT: the base class stores are ordered differently
	LoadStream::LoadStream(core::IFile* newFile, int unused, int mode, int block)
	{
		Reset();
		buffered = mode == 1;
		blocking = block == 0;
		newFile->AddRef();
		file = newFile;
		unknown14 = true;
	}

	// FUNCTION: ENGINE 0x1060AAE0
	LoadStream::LoadStream(const void* data, unsigned int newSize)
	{
		Reset();
		Attach(data, newSize);
	}

	// FUNCTION: ENGINE 0x1060AB10
	LoadStream::~LoadStream()
	{
		Wait();
		if (file != 0)
		{
			file->Release();
		}
		buffers[0] = 0;
		buffers[1] = 0;
	}

	// FUNCTION: ENGINE 0x1060AF70
	// EQUIVALENT: the flag of SplitRegion arrives in cl, the base class stores are ordered differently
	LoadStream::LoadStream(CompressedReader* newCompressed, int newOffset, int newSize, int block)
	{
		Reset();
		compressed = newCompressed;
		opened = true;
		buffered = newOffset != 0 && newSize != 0;
		blocking = block == 0;
		size = newCompressed->size;
		unsigned int start = 0;
		unsigned int length = 0;
		SplitRegion(1, newOffset, newOffset + newSize, &start, &length, false);
		SetBuffers(start, length);
	}

	// FUNCTION: ENGINE 0x1060B240
	bool LoadStream::IsOpen()
	{
		Prepare(false, 0);
		return opened;
	}

	// FUNCTION: ENGINE 0x1060B260
	// EQUIVALENT: block layout of the early return
	void LoadStream::Read(void* destination, unsigned int count, unsigned int itemSize, unsigned int option)
	{
		if (!IsOpen())
		{
			return;
		}
		if (!buffered)
		{
			ReadDirect(destination, count, itemSize, option);
			return;
		}
		ReadBuffered(destination, count, itemSize, option);
	}

	// FUNCTION: ENGINE 0x1060B2C0
	// EQUIVALENT: scheduling and registers
	void LoadStream::Skip(unsigned int bytes)
	{
		if (IsOpen() && bytes != 0)
		{
			if (!buffered)
			{
				SkipDirect(bytes);
				return;
			}
			if (offset + bytes <= fill)
			{
				position += bytes;
				offset += bytes;
				return;
			}
			if (bytes != 0)
			{
				while (true)
				{
					unsigned int part = bytes;
					unsigned int start = offset;
					if (fill < start + bytes)
					{
						part = fill - start;
					}
					position += part;
					bytes -= part;
					offset = start + part;
					if (bytes == 0)
					{
						break;
					}
					NextBuffer();
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1060B330
	// EQUIVALENT: scheduling and registers
	bool LoadStream::GetBuffer(void** buffer, unsigned int* length)
	{
		if (!buffered)
		{
			if (file != 0)
			{
				Prepare(true, 0);
			}
			unsigned int* current = &buffers[currentBuffer];
			if (*current != 0)
			{
				*buffer = (void*)*current;
				*length = bufferSize;
				return true;
			}
		}
		return false;
	}
}
