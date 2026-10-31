// The members of engine::render::RenderQueue that the engine keeps next to the render thread's start-up (unit
// 0x1085FDB0 - 0x10860000; file name guessed, names are guesses).
#include <new>
#include "code/core/criticalsection.h"
#include "code/core/heap.h"
#include "code/engine/render/renderthread.h"

namespace engine
{
	namespace render
	{
		// FUNCTION: ENGINE 0x1085FDB0
		RenderQueue::RenderQueue(int heap, unsigned int newCapacity, int newUnknown0, unsigned int newWaiterCount)
		{
			sleeping = false;
			unknown0 = newUnknown0;
			waiterCount = newWaiterCount;
			readIndex = 0;
			capacity = newCapacity;
			writeIndex = 0;
			unknown3C = false;
			items = (void**)core::HeapAlloc(heap, newCapacity * 4);
			core::SemaphoreCreate(&semaphore, 0);
			waiters = new RenderQueueWaiter[waiterCount];
			for (unsigned int i = 0; i < waiterCount; i++)
			{
				waiters[i].thread = 0;
				core::SemaphoreCreate(&waiters[i].semaphore, 0);
				waiters[i].waiting = false;
			}
			core::CriticalSectionInit(lock);
		}

		// FUNCTION: ENGINE 0x1085FE60
		RenderQueue::~RenderQueue()
		{
			core::Free(items);
			core::SemaphoreDestroy(&semaphore);
			for (unsigned int i = 0; i < waiterCount; i++)
			{
				core::SemaphoreDestroy(&waiters[i].semaphore);
			}
			delete[] waiters;
			core::CriticalSectionDelete(lock);
		}

		// FUNCTION: ENGINE 0x1085FEC0
		void RenderQueue::Send(void* item)
		{
			core::CriticalSectionEnter(lock);
			items[writeIndex] = item;
			writeIndex = (writeIndex + 1) % capacity;
			if (sleeping)
			{
				sleeping = false;
				core::SemaphoreRelease(&semaphore, 1);
			}
			core::CriticalSectionLeave(lock);
		}

		// FUNCTION: ENGINE 0x1085FF20
		bool RenderQueue::Peek(void** item)
		{
			core::CriticalSectionEnter(lock);
			if (readIndex == writeIndex)
			{
				core::CriticalSectionLeave(lock);
				return false;
			}
			*item = items[readIndex];
			core::CriticalSectionLeave(lock);
			return true;
		}

		// FUNCTION: ENGINE 0x1085FF70
		void RenderQueue::WaitPeek(void** item)
		{
			core::CriticalSectionEnter(lock);
			bool empty = readIndex == writeIndex;
			sleeping = empty;
			core::CriticalSectionLeave(lock);
			if (empty)
			{
				core::SemaphoreWait(&semaphore);
			}
			core::CriticalSectionEnter(lock);
			*item = items[readIndex];
			core::CriticalSectionLeave(lock);
		}

		// FUNCTION: ENGINE 0x1085FFD0
		bool RenderQueue::Pop(void** item)
		{
			unknown3C = true;
			core::CriticalSectionEnter(lock);
			if (readIndex == writeIndex)
			{
				core::CriticalSectionLeave(lock);
				return false;
			}
			*item = items[readIndex];
			readIndex = (readIndex + 1) % capacity;
			return true;
		}
	}
}
