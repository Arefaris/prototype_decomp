#include "code/core/criticalsection.h"
#include "code/core/file/request.h"

namespace core
{
	// FUNCTION: ENGINE 0x1064FAA0
	Drive::~Drive()
	{
	}

	// FUNCTION: ENGINE 0x1064FB30
	void Drive::AddRef()
	{
		SafeRefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x1064FB50
	void Drive::Release()
	{
		SafeRefCount::Release();
	}

	// FUNCTION: ENGINE 0x1064FB90
	int Drive::GetError()
	{
		Lock();
		int value = error;
		Unlock();
		return value;
	}

	// FUNCTION: ENGINE 0x1064FBC0
	void Drive::SetState(int state)
	{
		Lock();
		error = state;
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064FBF0
	DriveInfo* Drive::GetInfo()
	{
		return &info;
	}

	// FUNCTION: ENGINE 0x1064FC00
	void Drive::Queue(Request* request)
	{
		Lock();
		if (first == 0)
		{
			first = request;
		}
		else
		{
			last->next = request;
		}
		request->next = 0;
		last = request;
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064FC40
	void Drive::BeginExclusive(IDriveFaultHandler* holder, int data)
	{
		Lock();
		thread = GetThreadData();
		handler = holder;
		value = data;
		mode = 2;
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064FC80
	void Drive::EndExclusive(int a)
	{
		Lock();
		handler = 0;
		thread = 0;
		mode = 0;
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064FCB0
	void Drive::Suspend(void* event)
	{
		Lock();
		semaphore = event;
		mode = 2;
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064FCE0
	void Drive::Resume(void* event)
	{
		Lock();
		semaphore = event;
		mode = 0;
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064FD10
	void Drive::SetMode(int value)
	{
		Lock();
		mode = value;
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064FD40
	int Drive::GetMode()
	{
		Lock();
		int value = mode;
		Unlock();
		return value;
	}

	// FUNCTION: ENGINE 0x1064FD70
	void Drive::ClearFault(int data)
	{
		Lock();
		faulted = false;
		fault = 0;
		Unlock();
		queue->Restart(data);
	}

	// FUNCTION: ENGINE 0x1064FDB0
	bool Drive::IsFaulted()
	{
		Lock();
		bool value = faulted;
		Unlock();
		return value;
	}

	// FUNCTION: ENGINE 0x1064FDE0
	// Wakes a suspended drive
	void Drive::SetFault(IDriveFault* value)
	{
		Lock();
		fault = value;
		faulted = true;
		if (semaphore != 0)
		{
			Unlock();
			SemaphoreRelease(semaphore, 1);
			return;
		}
		Unlock();
	}

	// FUNCTION: ENGINE 0x1064FE30
	bool Drive::Configure(int* a, int* b)
	{
		Lock();
		bool result;
		if (faulted)
		{
			*a = fault->GetA();
			*b = fault->GetB();
			result = true;
		}
		else
		{
			result = false;
		}
		Unlock();
		return result;
	}

	// FUNCTION: ENGINE 0x1064FE90
	void Drive::SetFlag(bool value)
	{
		flag = value;
	}

	// FUNCTION: ENGINE 0x1064FEA0
	bool Drive::GetFlag()
	{
		return flag;
	}

	// FUNCTION: ENGINE 0x1064FEB0
	int Drive::Submit(Request* request, int key, bool front)
	{
		return queue->Submit(request, key, front);
	}

	// FUNCTION: ENGINE 0x1064FEC0
	void Drive::CancelRequests(void* owner, int key)
	{
		queue->Cancel(owner, key);
	}

	// FUNCTION: ENGINE 0x1064FED0
	bool Drive::FlushRequests()
	{
		return queue->Flush();
	}

	// FUNCTION: ENGINE 0x1064FEE0
	bool Drive::HasCompletions()
	{
		return first != 0;
	}

	// FUNCTION: ENGINE 0x1064FEF0
	void Drive::AddCache(FileCache* cache)
	{
		caches.Add(cache);
	}

	// FUNCTION: ENGINE 0x1064FF00
	void Drive::RemoveCache(FileCache* cache)
	{
		caches.Remove(cache);
	}

	// FUNCTION: ENGINE 0x1064FF10
	FileCacheList* Drive::GetCacheList()
	{
		return &caches;
	}

	// FUNCTION: ENGINE 0x1064FF20
	int Drive::Slot5(int a, int b)
	{
		return b;
	}

	// FUNCTION: ENGINE 0x1064FF30
	// 0 when the media has room (or reports its own answer), 7 otherwise
	int Drive::CanCreateFile(int a, int b)
	{
		if (GetFlags() & 1)
		{
			unsigned int needed = Slot5(a, b);
			DriveInfo* media = GetInfo();
			if (media->data[0] != 0)
			{
				return media->data[0];
			}
			if (needed <= (unsigned int)media->data[1] && (unsigned int)media->data[2] >= 1)
			{
				return 0;
			}
		}
		return 7;
	}

	// FUNCTION: ENGINE 0x1064FF80
	bool Drive::Slot7(int a, int b)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x1064FF90
	int Drive::Commit(int handle, const char* path)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1064FFA0
	int Drive::Open(const char* path, int mode, bool flag, int* handle, unsigned int* size)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1064FFB0
	int Drive::OpenSaveGame(const char* path, int mode, bool flag, int a, int b, int* handle, unsigned int* size)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1064FFC0
	int Drive::Write(int handle, const char* path, unsigned int a, unsigned int position, const void* buffer, unsigned int size, unsigned int* done, unsigned int* fileSize, int b)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1064FFD0
	int Drive::Format()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1064FFE0
	int Drive::CreateDirectory(const char* path)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1064FFF0
	int Drive::DestroyDirectory(const char* path)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10650000
	int Drive::DestroyFile(const char* path)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10650010
	int Drive::FindFirst(void* data, int a, int* handle, bool restart)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10650020
	int Drive::FindNext(int* handle, void* data)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10650030
	int Drive::FindClose(int* handle)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x10650040
	void Drive::Slot23(int value)
	{
	}

	// FUNCTION: ENGINE 0x106500B0
	Drive::Drive()
		: SafeRefCount(1), first(0), last(0), mode(0), semaphore(0), thread(0), handler(0), value(0), faulted(false),
		fault(0), flag(true), busy(false), error(3), queue(0)
	{
		CoreName();
	}

	// FUNCTION: ENGINE 0x10650180
	// EQUIVALENT: identical except that the original loads `this` into ecx before pushing the handler's result
	// for ClearFault (98.9 %); a result temporary, this-> and Drive:: give the same order as here
	// Runs the completions of the calling thread (the link walks a copy of the next pointer after a request it
	// keeps, so only a run at the head is unlinked) and lets the exclusive holder handle a fault
	void Drive::Update()
	{
		int current = GetThreadData();
		Lock();
		Request** link = &first;
		Request* previous = 0;
		Request* following;
		while (*link != 0)
		{
			if (((CompletionCallbackRequest*)*link)->IsFromThread(current))
			{
				CompletionCallbackRequest* request = (CompletionCallbackRequest*)*link;
				*link = request->next;
				Unlock();
				request->Complete();
				Lock();
				delete request;
			}
			else
			{
				previous = *link;
				following = previous->next;
				link = &following;
			}
		}
		last = previous;
		if (faulted == 1 && handler != 0)
		{
			if (!busy)
			{
				busy = true;
				Unlock();
				ClearFault(handler->OnFault(error, GetId(), fault->GetA(), fault->GetB(), value));
				busy = false;
				return;
			}
			Unlock();
			return;
		}
		Unlock();
	}
}
