// The engine's render thread (unit around 0x10860890 - 0x10861100; file name guessed). Names are guesses.
#include "code/core/criticalsection.h"
#include "code/engine/render/renderthread.h"

namespace engine
{
	namespace render
	{
		// FUNCTION: ENGINE 0x10860E80
		void RenderQueue::SendAndWait(void* item)
		{
			core::CriticalSectionEnter(lock);
			items[writeIndex] = item;
			writeIndex = (writeIndex + 1) % capacity;
			if (sleeping)
			{
				sleeping = false;
				core::SemaphoreRelease(&semaphore, 1);
			}
			RenderQueueWaiter* waiter = GetWaiter();
			waiter->waiting = true;
			core::CriticalSectionLeave(lock);
			core::SemaphoreWait(&waiter->semaphore);
		}
	}
}
