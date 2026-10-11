#include "code/core/criticalsection.h"
#include "code/core/file/request.h"
#include "code/core/memory/memorypool.h"

namespace core
{
	// The instance lock (also every instance's IMutable lock) and the instance pool
	// GLOBAL: ENGINE 0x1127CA84
	static int sInstanceLock[6];
	// GLOBAL: ENGINE 0x1127CA9C
	static MemoryPool* sInstancePool;

	// FUNCTION: ENGINE 0x1064EB10
	void InitInstanceDrives(unsigned int count, int heap)
	{
		CriticalSectionInit(sInstanceLock);
		CreateMemoryPool(&sInstancePool, 0x30, count, heap, "InstanceDrive", 16);
		sInstancePool->SetSafetyMode(0);
	}

	// FUNCTION: ENGINE 0x1064EB50
	void* InstanceDrive::operator new(unsigned int size)
	{
		CriticalSectionEnter(sInstanceLock);
		void* block = sInstancePool->AllocBlock();
		CriticalSectionLeave(sInstanceLock);
		return block;
	}

	// FUNCTION: ENGINE 0x1064EB80
	void InstanceDrive::operator delete(void* block)
	{
		CriticalSectionEnter(sInstanceLock);
		sInstancePool->Free(block);
		CriticalSectionLeave(sInstanceLock);
	}

	// FUNCTION: ENGINE 0x1064EBB0
	InstanceDrive::~InstanceDrive()
	{
		if (hasEvent)
		{
			EventDestroy(event);
			hasEvent = false;
		}
		drive->Release();
	}

	// FUNCTION: ENGINE 0x1064EBF0
	void InstanceDrive::AddRef()
	{
		Lock();
		refCount++;
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064EC10
	// The last reference closes an open search through a request; otherwise the instance is deleted, its count
	// parked at 500000 meanwhile
	void InstanceDrive::Release()
	{
		Lock();
		if (--refCount == 0)
		{
			if (searching)
			{
				searching = false;
				Unlock();
				drive->Submit(new DriveFindCloseRequest(this), key, 0);
				return;
			}
			refCount = 500000;
			Unlock();
			delete this;
			return;
		}
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064ECA0
	void InstanceDrive::Lock()
	{
		CriticalSectionEnter(sInstanceLock);
	}

	// FUNCTION: ENGINE 0x1064ECB0
	void InstanceDrive::Unlock()
	{
		CriticalSectionLeave(sInstanceLock);
	}

	// FUNCTION: ENGINE 0x1064ECC0
	unsigned char InstanceDrive::GetFlags()
	{
		return drive->GetFlags();
	}

	// FUNCTION: ENGINE 0x1064ECD0
	int InstanceDrive::GetMedia(DriveInfo* info)
	{
		return drive->Submit(new DriveMediaRequest(this, info), key, 0);
	}

	// FUNCTION: ENGINE 0x1064ED20
	int InstanceDrive::CanCreateFile(int a, int b, int* result)
	{
		return drive->Submit(new DriveCanCreateFileRequest(this, a, b, result), key, 0);
	}

	// FUNCTION: ENGINE 0x1064ED70
	int InstanceDrive::Format()
	{
		return drive->Submit(new DriveFormatRequest(this), key, 0);
	}

	// FUNCTION: ENGINE 0x1064EDB0
	// The drives that hide their names take the native form of the path
	int InstanceDrive::CreateDirectory(const char* path)
	{
		const char* native = 0;
		const char* relative = 0;
		char device[0x14];
		char full[0x104];
		SplitPath(path, full, device, &relative, &native);
		const char* name = relative;
		if (drive->GetFlags() & 0x80)
		{
			name = native;
		}
		return drive->Submit(new DriveCreateDirectoryRequest(this, name), key, 0);
	}

	// FUNCTION: ENGINE 0x1064EE40
	int InstanceDrive::DestroyDirectory(const char* path)
	{
		const char* native = 0;
		const char* relative = 0;
		char device[0x14];
		char full[0x104];
		SplitPath(path, full, device, &relative, &native);
		const char* name = relative;
		if (drive->GetFlags() & 0x80)
		{
			name = native;
		}
		return drive->Submit(new DriveDestroyDirectoryRequest(this, name), key, 0);
	}

	// FUNCTION: ENGINE 0x1064EED0
	int InstanceDrive::FindFirst(const char* path, int flags)
	{
		const char* native = 0;
		const char* relative = 0;
		char device[0x14];
		char full[0x104];
		SplitPath(path, full, device, &relative, &native);
		const char* name = relative;
		if (drive->GetFlags() & 0x80)
		{
			name = native;
		}
		return drive->Submit(new DriveFindFirstRequest(this, name, flags), key, 0);
	}

	// FUNCTION: ENGINE 0x1064EF70
	int InstanceDrive::FindNext(void* data)
	{
		return drive->Submit(new DriveFindNextRequest(this, data), key, 0);
	}

	// FUNCTION: ENGINE 0x1064EFC0
	int InstanceDrive::DestroyFile(const char* path)
	{
		const char* native = 0;
		const char* relative = 0;
		char device[0x14];
		char full[0x104];
		SplitPath(path, full, device, &relative, &native);
		const char* name = relative;
		if (drive->GetFlags() & 0x80)
		{
			name = native;
		}
		return drive->Submit(new DriveFileDestroyRequest(this, name), key, 0);
	}

	// FUNCTION: ENGINE 0x1064F050
	void InstanceDrive::GetMediaWait(DriveInfo* info)
	{
		GetMedia(info);
		Wait();
	}

	// FUNCTION: ENGINE 0x1064F070
	void InstanceDrive::CanCreateFileWait(int a, int b, int* result)
	{
		CanCreateFile(a, b, result);
		Wait();
	}

	// FUNCTION: ENGINE 0x1064F0A0
	void InstanceDrive::FormatWait()
	{
		Format();
		Wait();
	}

	// FUNCTION: ENGINE 0x1064F0C0
	void InstanceDrive::CreateDirectoryWait(const char* path)
	{
		CreateDirectory(path);
		Wait();
	}

	// FUNCTION: ENGINE 0x1064F0E0
	void InstanceDrive::DestroyDirectoryWait(const char* path)
	{
		DestroyDirectory(path);
		Wait();
	}

	// FUNCTION: ENGINE 0x1064F100
	void InstanceDrive::FindFirstWait(const char* path, int flags)
	{
		FindFirst(path, flags);
		Wait();
	}

	// FUNCTION: ENGINE 0x1064F130
	void InstanceDrive::FindNextWait(void* data)
	{
		FindNext(data);
		Wait();
	}

	// FUNCTION: ENGINE 0x1064F150
	void InstanceDrive::DestroyFileWait(const char* path)
	{
		DestroyFile(path);
		Wait();
	}

	// FUNCTION: ENGINE 0x1064F170
	int InstanceDrive::Cancel()
	{
		return drive->Submit(new DriveCancelRequest(this), key, 1);
	}

	// FUNCTION: ENGINE 0x1064F1B0
	int InstanceDrive::Notify(ICompletionCallback* callback, void* userData)
	{
		return drive->Submit(new DriveCompletionRequest(GetThreadData(), this, callback, userData), key, 0);
	}

	// FUNCTION: ENGINE 0x1064F210
	int InstanceDrive::Signal(void* semaphore)
	{
		return drive->Submit(new CompletionEventRequest(semaphore, drive), key, 0);
	}

	// FUNCTION: ENGINE 0x1064F260
	bool InstanceDrive::IsIdle()
	{
		Lock();
		bool idle = pending == 0;
		Unlock();
		return idle;
	}

	// FUNCTION: ENGINE 0x1064F290
	void InstanceDrive::Wait()
	{
		while (!IsIdle())
		{
			drive->Update();
			ThreadSleep(0);
		}
	}

	// FUNCTION: ENGINE 0x1064F2D0
	void InstanceDrive::WaitSignal()
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

	// FUNCTION: ENGINE 0x1064F340
	// A faulted drive reports its own error
	int InstanceDrive::GetError()
	{
		Lock();
		int value;
		if (drive->IsFaulted())
		{
			value = drive->GetError();
		}
		else
		{
			value = error;
		}
		Unlock();
		return value;
	}

	// FUNCTION: ENGINE 0x1064F390
	void InstanceDrive::BeginExclusive(IDriveFaultHandler* handler, int value)
	{
		drive->BeginExclusive(handler, value);
	}

	// FUNCTION: ENGINE 0x1064F3A0
	void InstanceDrive::EndExclusive(int a)
	{
		drive->EndExclusive(a);
	}

	// FUNCTION: ENGINE 0x1064F3B0
	void InstanceDrive::Suspend(void* semaphore)
	{
		drive->Suspend(semaphore);
	}

	// FUNCTION: ENGINE 0x1064F3C0
	void InstanceDrive::Resume(void* semaphore)
	{
		drive->Resume(semaphore);
	}

	// FUNCTION: ENGINE 0x1064F3D0
	bool InstanceDrive::IsFaulted()
	{
		return drive->IsFaulted();
	}

	// FUNCTION: ENGINE 0x1064F3E0
	void InstanceDrive::ClearFault(int value)
	{
		drive->ClearFault(value);
	}

	// FUNCTION: ENGINE 0x1064F3F0
	void InstanceDrive::SetMode(int mode)
	{
		drive->SetMode(mode);
	}

	// FUNCTION: ENGINE 0x1064F400
	void InstanceDrive::SetFlag(bool flag)
	{
		drive->SetFlag(flag);
	}

	// FUNCTION: ENGINE 0x1064F410
	bool InstanceDrive::Configure(int* a, int* b)
	{
		return drive->Configure(a, b);
	}

	// FUNCTION: ENGINE 0x1064F420
	void InstanceDrive::OpenFile(IFile** file, const char* path, bool writable, int mode, int value, int unused1, int unused2, int unused3, int option)
	{
		const char* native = 0;
		const char* relative = 0;
		char device[0x14];
		char full[0x104];
		SplitPath(path, full, device, &relative, &native);
		const char* name = relative;
		if (drive->GetFlags() & 0x80)
		{
			name = native;
		}
		*file = new File(drive, name, writable, mode, value, unused1, unused2, unused3, true, option);
	}

	// FUNCTION: ENGINE 0x1064F500
	void InstanceDrive::OpenFileWait(IFile** file, const char* path, bool writable, int mode, int value, int unused1, int unused2, int unused3, int option)
	{
		OpenFile(file, path, writable, mode, value, unused1, unused2, unused3, option);
		if (*file != 0)
		{
			(*file)->Wait();
		}
	}

	// FUNCTION: ENGINE 0x1064F550
	void InstanceDrive::OpenSaveGame(IFile** file, const char* path, bool writable, int mode, int a, int b, int value)
	{
		const char* native = 0;
		const char* relative = 0;
		char device[0x14];
		char full[0x104];
		SplitPath(path, full, device, &relative, &native);
		const char* name = relative;
		if (drive->GetFlags() & 0x80)
		{
			name = native;
		}
		*file = new File(drive, name, writable, mode, a, b, value);
	}

	// FUNCTION: ENGINE 0x1064F620
	void InstanceDrive::OpenSaveGameWait(IFile** file, const char* path, bool writable, int mode, int a, int b, int value)
	{
		OpenSaveGame(file, path, writable, mode, a, b, value);
		if (*file != 0)
		{
			(*file)->Wait();
		}
	}

	// FUNCTION: ENGINE 0x1064F660
	void InstanceDrive::SetUnused(int value)
	{
	}

	// FUNCTION: ENGINE 0x1064F670
	int InstanceDrive::GetKey()
	{
		return key;
	}

	// FUNCTION: ENGINE 0x1064F680
	int InstanceDrive::GetDriveId()
	{
		return drive->GetId();
	}

	// FUNCTION: ENGINE 0x1064F690
	int InstanceDrive::GetDriveSlot5(int a, int b)
	{
		return drive->Slot5(a, b);
	}

	// FUNCTION: ENGINE 0x1064F6A0
	bool InstanceDrive::GetDriveSlot7(int a, int b)
	{
		return drive->Slot7(a, b);
	}

	// FUNCTION: ENGINE 0x1064F6B0
	void InstanceDrive::BeginRequest()
	{
		Lock();
		pending++;
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064F6D0
	void InstanceDrive::EndRequest()
	{
		Lock();
		if (--pending == 0 && waiting)
		{
			EventSignal(event, 0xFFFF);
			waiting = false;
		}
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064F710
	// The statistic read before the pool goes is not used (a check compiled out)
	void ShutdownInstanceDrives()
	{
		CriticalSectionDelete(sInstanceLock);
		int used = 0;
		sInstancePool->GetStat(0, &used);
		sInstancePool->Release();
		sInstancePool = 0;
	}

	// FUNCTION: ENGINE 0x1064F790
	InstanceDrive::InstanceDrive(Drive* owner, int value)
		: refCount(1), drive(owner), key(value), pending(0), hasEvent(false), waiting(false), searching(false)
	{
		CoreName();
		drive->AddRef();
		drive->Submit(new DriveOpenRequest(this), key, 0);
	}
}
