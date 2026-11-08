// content::CompressedFile (unit 0x1060DDC0 - 0x1060E4D0; see compressedfile.h).
#include "code/content/chunkhandler.h"
#include "code/content/compressedfile.h"
#include "code/core/criticalsection.h"
#include "code/core/heap.h"
#include "code/core/memory/align.h"
#include <intrin.h>

// The engine's slots that do nothing return no value (whatever eax holds)
#pragma warning(disable : 4716)

namespace content
{
	// FUNCTION: ENGINE 0x1060DBE0
	CompressedReader::CompressedReader(int level, void* newBuffer, unsigned int newBufferSize, unsigned int newSize,
		int heap)
	{
		decompressor = 0;
		consumed = 0;
		buffer = newBuffer;
		bufferSize = newBufferSize;
		size = newSize;
		produced = 0;
		decompressor = CreateDecompressor(level, 1, heap);
	}

	// FUNCTION: ENGINE 0x1060DC20
	CompressedReader::~CompressedReader()
	{
		decompressor->Wait();
		DestroyDecompressor(decompressor);
	}

	// FUNCTION: ENGINE 0x1060DC40
	void CompressedReader::Read(void* destination, unsigned int count)
	{
		int usedOutput = decompressor->GetUsedOutput();
		int usedInput = decompressor->GetUsedInput();
		consumed += usedInput;
		produced += usedOutput;
		decompressor->Submit((char*)buffer + consumed, bufferSize - consumed, destination, count, true);
	}

	// FUNCTION: ENGINE 0x1060DC90
	int CompressedReader::IsDone()
	{
		return decompressor->IsDone();
	}

	// FUNCTION: ENGINE 0x1060DCC0
	void CompressedReader::Wait()
	{
		decompressor->Wait();
	}

	// FUNCTION: ENGINE 0x1060DCD0
	void CompressedReader::ReadWait(void* destination, unsigned int count)
	{
		Read(destination, count);
		Wait();
	}

	// The header the packed data of a file starts with (16 bytes)
	struct PackedHeader
	{
		unsigned int unknown0;
		int level;
		unsigned int unpacked;
		unsigned int unknownC;
	};

	// FUNCTION: ENGINE 0x1060DE30
	// NONMATCHING: the loads of the header and the order of the stores, 91.4 %
#ifdef NONMATCHING
	void CompressedFile::StartBlock()
	{
		switch (passthrough)
		{
		case 0:
			return;
		case 1:
			{
				unsigned int position = unknown38;
				const PackedHeader* header = (const PackedHeader*)buffers[unknown3C] + position;
				int level = header->level;
				unsigned int unpacked = header->unpacked;
				unknown1C += 0x10;
				unknown38 = position + 0x10;
				unpackedSize = unpacked;
				decompressor = CreateDecompressor(level, 1, heap);
			}
		}
	}
#endif


	// FUNCTION: ENGINE 0x1060DE80
	void CompressedFile::Unpack(void* buffer, unsigned int size)
	{
		unsigned char* output = (unsigned char*)buffer;
		unsigned int remaining = size;
		unsigned char* outputEnd = output + size;
		if (remaining + unknown20 > unpackedSize)
		{
			remaining = unpackedSize - unknown20;
		}
		if (unknown18 == 0)
		{
			unsigned int blockSize = half * 2;
			unsigned int rest;
			if (blockSize > innerSize)
			{
				blockSize = core::RoundUp(innerSize, inner->GetGranularity());
				unsigned int first;
				if (innerSize > half)
				{
					first = half;
				}
				else
				{
					first = innerSize;
				}
				unknown30 = first;
				rest = innerSize - first;
			}
			else
			{
				unknown30 = half;
				rest = half;
			}
			unknown34 = rest;
			inner->Read((void*)buffers[0], blockSize, 1);
			inner->WaitSignal();
			unknown18 = blockSize;
			unknown38 = 0;
			unknown3C = 0;
			unknown1C = 0;
			unknown20 = 0;
			StartBlock();
		}
		while (remaining > 0)
		{
			unsigned int available = unknown30 - unknown38;
			bool last = unknown1C + available >= innerSize;
			decompressor->Submit((const void*)(buffers[unknown3C] + unknown38), available, output, outputEnd - output, last);
			decompressor->Wait();
			int produced = decompressor->GetUsedOutput();
			int consumed = decompressor->GetUsedInput();
			remaining -= produced;
			unknown20 += produced;
			unknown38 += consumed;
			unknown1C += consumed;
			output += produced;
			decompressor->GetStatus();
			if (!last && unknown30 == unknown38)
			{
				inner->WaitSignal();
				unsigned int emptied = buffers[unknown3C];
				unknown3C = (unknown3C - 1) & 1;
				unknown30 = unknown34;
				unknown38 = 0;
				unknown34 = 0;
				if (unknown18 < innerSize)
				{
					unsigned int chunk = half;
					unknown34 = chunk;
					if (unknown18 + chunk >= innerSize)
					{
						unknown34 = innerSize - unknown18;
						chunk = core::RoundUp(unknown34, inner->GetGranularity());
					}
					inner->Read((void*)emptied, chunk, 1);
					unknown18 += chunk;
				}
			}
		}
		core::EventSignal(&event, 0xFFFF);
	}

	// FUNCTION: ENGINE 0x1060DDC0
	void* CompressedFile::operator new(unsigned int size, int heap)
	{
		return core::HeapAlloc(heap, size);
	}

	// FUNCTION: ENGINE 0x1060DDE0
	void CompressedFile::operator delete(void* block)
	{
		core::Free(block);
	}

	// FUNCTION: ENGINE 0x1060DDF0
	CompressedFile::~CompressedFile()
	{
		if (decompressor != 0)
		{
			DestroyDecompressor(decompressor);
		}
		inner->Release();
		core::EventDestroy(&event);
	}

	// FUNCTION: ENGINE 0x1060E040
	int CompressedFile::Read(void* buffer, unsigned int size, int option)
	{
		DecompressRequest request;
		request.file = this;
		request.buffer = buffer;
		request.size = size;
		core::EventReset(&event, 0xFFFF);
		factory->Queue(&request);
	}

	// FUNCTION: ENGINE 0x1060E0F0
	int CompressedFile::Write(const void* buffer, unsigned int size, int option)
	{
	}

	// FUNCTION: ENGINE 0x1060E100
	int CompressedFile::SetPosition(unsigned int position)
	{
	}

	// FUNCTION: ENGINE 0x1060E110
	int CompressedFile::GetPosition(unsigned int* position)
	{
	}

	// FUNCTION: ENGINE 0x1060E120
	int CompressedFile::GetSize(unsigned int* size)
	{
	}

	// FUNCTION: ENGINE 0x1060E130
	int CompressedFile::Commit()
	{
	}

	// FUNCTION: ENGINE 0x1060E150
	void CompressedFile::ReadWait(void* buffer, unsigned int size, int option)
	{
		Read(buffer, size, option);
		Wait();
	}

	// FUNCTION: ENGINE 0x1060E180
	void CompressedFile::WriteWait(const void* buffer, unsigned int size, int option)
	{
		Write(buffer, size, option);
		Wait();
	}

	// FUNCTION: ENGINE 0x1060E1B0
	void CompressedFile::SetPositionWait(unsigned int position)
	{
		SetPosition(position);
		Wait();
	}

	// FUNCTION: ENGINE 0x1060E1D0
	void CompressedFile::GetPositionWait(unsigned int* position)
	{
		GetPosition(position);
		Wait();
	}

	// FUNCTION: ENGINE 0x1060E1F0
	void CompressedFile::GetSizeWait(unsigned int* size)
	{
		GetSize(size);
		Wait();
	}

	// FUNCTION: ENGINE 0x1060E210
	void CompressedFile::CommitWait()
	{
		Commit();
		Wait();
	}

	// FUNCTION: ENGINE 0x1060E080
	unsigned int CompressedFile::GetCurrentSize()
	{
		return unpackedSize;
	}

	// FUNCTION: ENGINE 0x1060E250
	int CompressedFile::GetGranularity()
	{
		return inner->GetGranularity();
	}

	// FUNCTION: ENGINE 0x1060E140
	int CompressedFile::Cancel()
	{
	}

	// FUNCTION: ENGINE 0x1060E230
	int CompressedFile::Notify(core::IFileCompletionCallback* callback, void* userData)
	{
		return inner->Notify(callback, userData);
	}

	// FUNCTION: ENGINE 0x1060E240
	int CompressedFile::Signal(void* signalEvent)
	{
		return inner->Signal(signalEvent);
	}

	// FUNCTION: ENGINE 0x1060E090
	bool CompressedFile::IsIdle()
	{
		return core::AtomicRead(&event[0]) == 0;
	}

	// FUNCTION: ENGINE 0x1060E0B0
	void CompressedFile::Wait()
	{
		while (!IsIdle())
		{
			inner->IsIdle();
		}
	}

	// FUNCTION: ENGINE 0x1060E0E0
	void CompressedFile::WaitSignal()
	{
		core::EventWait(&event);
	}

	// FUNCTION: ENGINE 0x1060E260
	int CompressedFile::GetError()
	{
		return inner->GetError();
	}

	// FUNCTION: ENGINE 0x1060E270
	bool CompressedFile::IsOpen()
	{
		return inner->IsOpen();
	}

	// FUNCTION: ENGINE 0x1060E280
	const char* CompressedFile::GetName()
	{
		return inner->GetName();
	}

	// FUNCTION: ENGINE 0x1060E290
	const char* CompressedFile::GetPath()
	{
		return inner->GetPath();
	}

	// FUNCTION: ENGINE 0x1060E2A0
	int CompressedFile::GetDriveId()
	{
		return inner->GetDriveId();
	}

	// FUNCTION: ENGINE 0x1060E2B0
	void CompressedFile::SetUnused(int value)
	{
		inner->SetUnused(value);
	}

	// FUNCTION: ENGINE 0x1060E2C0
	int CompressedFile::GetKey()
	{
		return inner->GetKey();
	}

	// FUNCTION: ENGINE 0x1060E2D0
	bool CompressedFile::GetFlag()
	{
		return inner->GetFlag();
	}

	// FUNCTION: ENGINE 0x1060E2E0
	void CompressedFile::SetField12C(unsigned int value)
	{
		inner->SetField12C(value);
	}

	// FUNCTION: ENGINE 0x1060E2F0
	void CompressedFile::Init(core::IFile* newInner, int newPassthrough, int level, unsigned int newUnpacked,
		unsigned int newStart, unsigned int newSize, int newHeap, CompressedFileFactory* newFactory)
	{
		factory = newFactory;
		passthrough = newPassthrough;
		inner = newInner;
		unpackedSize = newUnpacked;
		unknown18 = 0;
		unknown1C = 0;
		unknown20 = 0;
		unknown30 = 0;
		unknown34 = 0;
		unknown38 = 0;
		unknown3C = 0;
		heap = newHeap;
		decompressor = 0;
		_InterlockedExchange(&refCount, 0);
		inner->AddRef();
		innerSize = inner->GetCurrentSize();
		unsigned int aligned = core::RoundUp(newStart, 0x80);
		unsigned int halfSize = core::RoundDown((newStart - aligned + newSize) >> 1, 0x800);
		half = halfSize;
		buffers[0] = aligned;
		buffers[1] = halfSize + aligned;
		if (newPassthrough == 0)
		{
			decompressor = CreateDecompressor(level, 1, newHeap);
		}
		core::EventInit(&event, 0);
	}

	// FUNCTION: ENGINE 0x1060E3F0
	CompressedFile::CompressedFile(core::IFile* newInner, int newPassthrough, unsigned int newStart,
		unsigned int newSize, int newHeap, CompressedFileFactory* newFactory)
	{
		refCount = 0;
		Init(newInner, newPassthrough, 1, 0, newStart, newSize, newHeap, newFactory);
		Read(0, 0, 1);
	}

	// FUNCTION: ENGINE 0x1060E440
	void CompressedFile::AddRef()
	{
		_InterlockedIncrement(&refCount);
	}

	// FUNCTION: ENGINE 0x1060E450
	void CompressedFile::Release()
	{
		long remaining = _InterlockedDecrement(&refCount);
		if (remaining == 0)
		{
			_InterlockedExchange(&refCount, 0x80000000);
			delete this;
		}
	}

	// FUNCTION: ENGINE 0x1060E480
	CompressedFile::CompressedFile(core::IFile* newInner, int level, unsigned int newUnpacked,
		unsigned int newStart, unsigned int newSize, int newHeap, CompressedFileFactory* newFactory)
	{
		refCount = 0;
		Init(newInner, 0, level, newUnpacked, newStart, newSize, newHeap, newFactory);
	}
}

// Kept copies (compiler-generated and inline functions of this unit):
// FUNCTION: ENGINE 0x1060E3C0
