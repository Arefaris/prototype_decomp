#define _CRT_SECURE_NO_DEPRECATE

#include <string.h>

#include "code/core/criticalsection.h"
#include "code/core/file/request.h"
#include "code/core/heap.h"
#include "code/core/memory/memorypool.h"
#include "code/core/report.h"
#include "code/core/strings.h"

// __FILE__ as the original build spelled it
#define FILE_FILE "..\\..\\..\\code\\core\\src\\file\\common\\file.cpp"

namespace core
{
	// The file lock (also every file's IMutable lock), the file pool and the table of open files
	// GLOBAL: ENGINE 0x1127CA60
	static int sFileLock[6];
	// GLOBAL: ENGINE 0x1127CA78
	static MemoryPool* sFilePool;
	// GLOBAL: ENGINE 0x1127CA7C
	static File** sFiles;
	// GLOBAL: ENGINE 0x1127CA80
	static unsigned int sFileCount;

	// FUNCTION: ENGINE 0x1064DF50
	void ReportOpenFiles()
	{
		CriticalSectionEnter(sFileLock);
		for (unsigned int i = 0; i < sFileCount; i++)
		{
			if (sFiles[i] != 0)
			{
				static bool sReportOpen = true;
				if (sReportOpen && Report(0, 0, FILE_FILE, 0x33, 0, "Open file: %s\n", sFiles[i]->GetName(), 0) == 3)
				{
					sReportOpen = false;
				}
			}
		}
		CriticalSectionLeave(sFileLock);
	}

	// FUNCTION: ENGINE 0x1064DFE0
	void InitFiles(unsigned int count, int heap)
	{
		CriticalSectionInit(sFileLock);
		CreateMemoryPool(&sFilePool, 0x174, count, heap, "File", 16);
		sFilePool->SetSafetyMode(0);
		File** files = (File**)HeapAlloc(heap, count * sizeof(File*));
		sFiles = files;
		sFileCount = count;
		for (unsigned int i = 0; i < count; i++)
		{
			files[i] = 0;
		}
	}

	// FUNCTION: ENGINE 0x1064E050
	void* File::operator new(unsigned int size)
	{
		CriticalSectionEnter(sFileLock);
		void* block = sFilePool->AllocBlock();
		if (block == 0)
		{
			ReportOpenFiles();
		}
		else
		{
			sFiles[sFilePool->GetIndex(block)] = (File*)block;
		}
		CriticalSectionLeave(sFileLock);
		return block;
	}

	// FUNCTION: ENGINE 0x1064E0B0
	void File::operator delete(void* block)
	{
		CriticalSectionEnter(sFileLock);
		sFiles[sFilePool->GetIndex(block)] = 0;
		sFilePool->Free(block);
		CriticalSectionLeave(sFileLock);
	}

	// FUNCTION: ENGINE 0x1064E100
	File::~File()
	{
		if (hasEvent)
		{
			EventDestroy(event);
			hasEvent = false;
		}
		drive->Release();
	}

	// FUNCTION: ENGINE 0x1064E150
	void File::AddRef()
	{
		Lock();
		refCount++;
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064E170
	// The last reference closes an open file through a request (which holds a reference until it is done);
	// a closed file is deleted, its count parked at 500000 meanwhile
	void File::Release()
	{
		Lock();
		if (--refCount == 0)
		{
			if (open)
			{
				Unlock();
				drive->Submit(new FileCloseRequest(this), key, 0);
				return;
			}
			refCount = 500000;
			Unlock();
			delete this;
			return;
		}
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064E200
	void File::Lock()
	{
		CriticalSectionEnter(sFileLock);
	}

	// FUNCTION: ENGINE 0x1064E210
	void File::Unlock()
	{
		CriticalSectionLeave(sFileLock);
	}

	// FUNCTION: ENGINE 0x1064E220
	int File::Commit()
	{
		return drive->Submit(new FileCommitRequest(this), key, 0);
	}

	// FUNCTION: ENGINE 0x1064E260
	int File::Read(void* buffer, unsigned int count, int option)
	{
		return drive->Submit(new FileReadRequest(this, buffer, count, option), key, 0);
	}

	// FUNCTION: ENGINE 0x1064E2B0
	int File::Write(const void* buffer, unsigned int count, int option)
	{
		return drive->Submit(new FileWriteRequest(this, buffer, count, option), key, 0);
	}

	// FUNCTION: ENGINE 0x1064E300
	int File::SetPosition(unsigned int value)
	{
		return drive->Submit(new FileSetPositionRequest(this, value), key, 0);
	}

	// FUNCTION: ENGINE 0x1064E350
	int File::GetPosition(unsigned int* value)
	{
		return drive->Submit(new FileGetPositionRequest(this, value), key, 0);
	}

	// FUNCTION: ENGINE 0x1064E3A0
	int File::GetSize(unsigned int* value)
	{
		return drive->Submit(new FileGetSizeRequest(this, value), key, 0);
	}

	// FUNCTION: ENGINE 0x1064E3F0
	void File::ReadWait(void* buffer, unsigned int count, int option)
	{
		Read(buffer, count, option);
		Wait();
	}

	// FUNCTION: ENGINE 0x1064E420
	void File::WriteWait(const void* buffer, unsigned int count, int option)
	{
		Write(buffer, count, option);
		Wait();
	}

	// FUNCTION: ENGINE 0x1064E450
	void File::SetPositionWait(unsigned int value)
	{
		SetPosition(value);
		Wait();
	}

	// FUNCTION: ENGINE 0x1064E470
	void File::GetPositionWait(unsigned int* value)
	{
		GetPosition(value);
		Wait();
	}

	// FUNCTION: ENGINE 0x1064E490
	void File::GetSizeWait(unsigned int* value)
	{
		GetSize(value);
		Wait();
	}

	// FUNCTION: ENGINE 0x1064E4B0
	void File::CommitWait()
	{
		Commit();
		Wait();
	}

	// FUNCTION: ENGINE 0x1064E4D0
	unsigned int File::GetCurrentSize()
	{
		return size;
	}

	// FUNCTION: ENGINE 0x1064E4E0
	int File::Cancel()
	{
		return drive->Submit(new FileCancelRequest(this), key, 1);
	}

	// FUNCTION: ENGINE 0x1064E520
	int File::Notify(ICompletionCallback* callback, void* userData)
	{
		return drive->Submit(new FileCompletionRequest(GetThreadData(), this, callback, userData), key, 0);
	}

	// FUNCTION: ENGINE 0x1064E580
	int File::Signal(void* semaphore)
	{
		return drive->Submit(new CompletionEventRequest(semaphore, drive), key, 0);
	}

	// FUNCTION: ENGINE 0x1064E5D0
	bool File::IsIdle()
	{
		Lock();
		bool idle = pending == 0;
		Unlock();
		return idle;
	}

	// FUNCTION: ENGINE 0x1064E600
	void File::Wait()
	{
		while (!IsIdle())
		{
			drive->Update();
			ThreadSleep(0);
		}
	}

	// FUNCTION: ENGINE 0x1064E640
	// Blocks on the file's event until the last pending request ends (EndRequest signals it)
	void File::WaitSignal()
	{
		Lock();
		if (pending > 0)
		{
			if (!waiting)
			{
				if (!hasEvent)
				{
					EventInit(event, 1);
					hasEvent = true;
				}
				else
				{
					EventReset(event, 1);
				}
				waiting = true;
			}
			Unlock();
			EventWait(event);
			return;
		}
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064E6B0
	int File::GetError()
	{
		Lock();
		int value = error;
		Unlock();
		return value;
	}

	// FUNCTION: ENGINE 0x1064E6E0
	bool File::IsOpen()
	{
		return open;
	}

	// FUNCTION: ENGINE 0x1064E6F0
	const char* File::GetName()
	{
		if (drive->GetFlags() & 0x80)
		{
			return 0;
		}
		return path;
	}

	// FUNCTION: ENGINE 0x1064E710
	const char* File::GetPath()
	{
		return path;
	}

	// FUNCTION: ENGINE 0x1064E720
	int File::GetDriveId()
	{
		return drive->GetId();
	}

	// FUNCTION: ENGINE 0x1064E730
	void File::SetUnused(int value)
	{
	}

	// FUNCTION: ENGINE 0x1064E740
	int File::GetKey()
	{
		return key;
	}

	// FUNCTION: ENGINE 0x1064E750
	bool File::GetFlag()
	{
		return flag;
	}

	// FUNCTION: ENGINE 0x1064E760
	int File::GetGranularity()
	{
		return granularity;
	}

	// FUNCTION: ENGINE 0x1064E770
	void File::SetField12C(unsigned int value)
	{
		field12C = value;
	}

	// FUNCTION: ENGINE 0x1064E780
	FileCache* File::GetCache()
	{
		return &cache;
	}

	// FUNCTION: ENGINE 0x1064E790
	bool File::CanShare(Drive* other)
	{
		Lock();
		if (drive == other)
		{
			Unlock();
			return true;
		}
		if (pending == 1 && !open)
		{
			drive->Release();
			drive = other;
			other->AddRef();
			Unlock();
			return true;
		}
		Unlock();
		return false;
	}

	// FUNCTION: ENGINE 0x1064E7F0
	void File::BeginRequest()
	{
		Lock();
		pending++;
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064E810
	void File::EndRequest()
	{
		Lock();
		if (--pending == 0 && waiting)
		{
			EventSignal(event, 0xFFFF);
			waiting = false;
		}
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064E850
	// The statistic read before the pool goes is not used (a check compiled out)
	void ShutdownFiles()
	{
		CriticalSectionDelete(sFileLock);
		int used = 0;
		sFilePool->GetStat(0, &used);
		sFilePool->Release();
		sFilePool = 0;
		core::Free(sFiles);
		sFiles = 0;
		sFileCount = 0;
	}

	// FUNCTION: ENGINE 0x1064E8D0
	File::File(Drive* owner, const char* name, bool canWrite, int mode, int a, int b, int value)
		: refCount(1), drive(owner), key(value), error(0), pending(0), hasEvent(false), waiting(false), open(false),
		writable(canWrite), field12C(0), position(0), size(0), flag(true), granularity(0x800)
	{
		CoreName();
		drive->AddRef();
		if (Utf8Copy(path, name, 0x100) < 0)
		{
			strncpy(path, name, 0x100);
			path[0x100] = 0;
		}
		drive->GetFlags();
		drive->Submit(new SaveGameOpenRequest(this, mode, canWrite, a, b), key, 0);
	}

	// FUNCTION: ENGINE 0x1064E9E0
	File::File(Drive* owner, const char* name, bool canWrite, int mode, int value, int unused1, int unused2, int unused3, bool openNow, int option)
		: refCount(1), drive(owner), key(value), error(0), pending(0), hasEvent(false), waiting(false), open(false),
		writable(canWrite), field12C(0), position(0), size(0), flag(false), granularity(0x800)
	{
		CoreName();
		drive->AddRef();
		if (Utf8Copy(path, name, 0x100) < 0)
		{
			strncpy(path, name, 0x100);
			path[0x100] = 0;
		}
		drive->GetFlags();
		if (openNow)
		{
			drive->Submit(new FileOpenRequest(this, mode, canWrite, option), key, 0);
		}
	}
}
