// content::CompressedFile (unit 0x1060DDC0 - 0x1060E4D0; see compressedfile.h).
#include "code/content/compressedfile.h"
#include "code/core/criticalsection.h"
#include "code/core/heap.h"
#include "code/core/memory/align.h"
#include <intrin.h>

// The engine's slots that do nothing return no value (whatever eax holds)
#pragma warning(disable : 4716)

namespace content
{
	// The thread that unpacks compressed files (0x11276A98, see loadstream.cpp)
	class CompressedFileFactory
	{
	public:
		// 0x1060BCE0: queues a request
		void Queue(DecompressRequest* request);
	};

	// The decompressor (0x106DC260 / 0x106DC2B0: makes one for a level / destroys it; names guessed)
	void* CreateDecompressor(int level, int unused, int heap);
	void DestroyDecompressor(void* decompressor);

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
		start = aligned;
		secondStart = halfSize + aligned;
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
