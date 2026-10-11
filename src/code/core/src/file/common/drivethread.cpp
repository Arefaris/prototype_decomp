#include "code/core/criticalsection.h"
#include "code/core/file/request.h"

namespace core
{
	// FUNCTION: ENGINE 0x106523B0
	// Whether a drive in this state has to be prepared before a request runs (not idle, not ready)
	static bool NeedsPrepare(int state)
	{
		return state != 0 && state != 1 ? true : false;
	}

	// FUNCTION: ENGINE 0x106523C0
	DriveThread::~DriveThread()
	{
		quit = true;
		SemaphoreRelease(&semaphore, 1);
		WaitThread(&thread);
		DestroyThread(&thread);
		SemaphoreDestroy(&semaphore);
		SemaphoreDestroy(&faultSemaphore);
	}

	// FUNCTION: ENGINE 0x10652440
	void DriveThread::AddRef()
	{
		SafeRefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x10652460
	void DriveThread::Release()
	{
		SafeRefCount::Release();
	}

	// FUNCTION: ENGINE 0x106524A0
	void DriveThread::Lock()
	{
		CriticalSectionEnter(lock);
	}

	// FUNCTION: ENGINE 0x106524B0
	void DriveThread::Unlock()
	{
		CriticalSectionLeave(lock);
	}

	// The original falls off the end of Submit (its callers pass on whatever is left in eax)
#pragma warning(push)
#pragma warning(disable: 4716)
	// FUNCTION: ENGINE 0x106524C0
	int DriveThread::Submit(Request* request, int key, bool front)
	{
		Lock();
		if (front)
		{
			if (tails[key] == 0)
			{
				tails[key] = request;
			}
			request->next = heads[key];
			heads[key] = request;
		}
		else
		{
			if (heads[key] == 0)
			{
				heads[key] = request;
			}
			else
			{
				tails[key]->next = request;
			}
			request->next = 0;
			tails[key] = request;
		}
		pending++;
		Unlock();
		SemaphoreRelease(&semaphore, 1);
	}
#pragma warning(pop)

	// FUNCTION: ENGINE 0x10652560
	void DriveThread::Cancel(void* owner, int key)
	{
		Lock();
		Request** link = &heads[key];
		Request* last = 0;
		while (*link != 0)
		{
			if ((*link)->IsFor(owner))
			{
				Request* request = *link;
				*link = request->next;
				delete request;
				pending--;
				SemaphoreWait(&semaphore);
			}
			else
			{
				last = *link;
				link = &last->next;
			}
		}
		tails[key] = last;
		if (current != 0 && current->IsFor(owner))
		{
			cancelled = true;
		}
		Unlock();
	}

	// FUNCTION: ENGINE 0x10652610
	bool DriveThread::Flush()
	{
		Lock();
		bool queued = pending != 0;
		Unlock();
		return queued;
	}

	// FUNCTION: ENGINE 0x10652640
	void DriveThread::WaitFault(Drive* drive, Request* request)
	{
		drive->SetFault((IDriveFault*)request);
		SemaphoreWait(&faultSemaphore);
	}

	// FUNCTION: ENGINE 0x10652670
	void DriveThread::Restart(int retry)
	{
		this->retry = retry;
		SemaphoreRelease(&faultSemaphore, 1);
	}

	// FUNCTION: ENGINE 0x10652690
	Request* DriveThread::Next(int* key)
	{
		Request* request = 0;
		Lock();
		for (unsigned int i = 0; i < 3; i++)
		{
			if (heads[i] != 0)
			{
				request = heads[i];
				if (request == tails[i])
				{
					tails[i] = 0;
				}
				heads[i] = request->next;
				request->next = 0;
				if (key != 0)
				{
					*key = i;
				}
				break;
			}
		}
		current = request;
		Unlock();
		return request;
	}

	// FUNCTION: ENGINE 0x10652710
	bool DriveThread::IsCancelled()
	{
		return cancelled;
	}

	// FUNCTION: ENGINE 0x10652720
	void DriveThread::FinishCurrent()
	{
		Lock();
		Request* request = current;
		cancelled = false;
		current = 0;
		Unlock();
		if (request != 0)
		{
			delete request;
		}
	}

	// FUNCTION: ENGINE 0x10652790
	int DriveThread::Run(void* argument)
	{
		DriveThread* self = (DriveThread*)argument;
		bool retried = false;
		SemaphoreWait(&self->semaphore);
		while (!self->quit)
		{
			int key = 1;
			Request* request = self->Next(&key);
			Drive* drive = request->GetDrive();
			int result;
			if (NeedsPrepare(drive->GetError()))
			{
				result = request->Prepare();
				if (result == 1)
				{
					result = request->Execute();
				}
			}
			else
			{
				result = request->Execute();
			}
			if (retried == true && drive->GetError() == 0 && drive->GetMode() == 2 && drive->GetFlag() == true)
			{
				self->WaitFault(drive, request);
				retried = false;
			}
			switch (result)
			{
			case 0:
				switch (drive->GetMode())
				{
				case 0:
					self->FinishCurrent();
					break;
				case 1:
					if (self->IsCancelled())
					{
						self->FinishCurrent();
					}
					else
					{
						self->Submit(request, key, true);
					}
					break;
				case 2:
					if (self->IsCancelled())
					{
						self->FinishCurrent();
						break;
					}
					self->WaitFault(drive, request);
					if (self->retry == 0)
					{
						self->FinishCurrent();
						break;
					}
					if (self->IsCancelled())
					{
						if (drive->GetFlag() == true)
						{
							int state = drive->GetError();
							drive->SetState(0);
							self->WaitFault(drive, request);
							drive->SetState(state);
						}
					}
					else
					{
						self->Submit(request, key, true);
						self->retry = 0;
						retried = true;
						break;
					}
					self->FinishCurrent();
					break;
				}
				break;
			case 1:
				self->FinishCurrent();
				break;
			case 2:
				if (self->IsCancelled())
				{
					self->FinishCurrent();
				}
				else
				{
					self->Submit(request, key, true);
				}
				break;
			}
			self->Lock();
			self->pending--;
			self->Unlock();
			SemaphoreWait(&self->semaphore);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10652970
	DriveThread::DriveThread(void* lock, int heap)
		: SafeRefCount(1), lock(lock), quit(false), retry(0), pending(0), current(0), cancelled(false)
	{
		CoreName();
		for (int i = 0; i < 3; i++)
		{
			heads[i] = 0;
			tails[i] = 0;
		}
		SemaphoreCreate(&semaphore, 0);
		SemaphoreCreate(&faultSemaphore, 0);
		StartThread(&thread, Run, this, 4, 0x8000, heap, 0, "core::DriveThread");
	}
}
