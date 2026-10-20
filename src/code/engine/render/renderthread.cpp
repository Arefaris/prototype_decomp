// The engine's render thread (unit around 0x10860890 - 0x10861100; file name guessed). Names are guesses.
#include "code/core/criticalsection.h"
#include "code/engine/render/async/renderevent.h"
#include "code/engine/render/renderthread.h"

namespace engine
{
	namespace render
	{
		// FUNCTION: ENGINE 0x10860100
		// FUNCTION: ENGINE 0x10860120
		template class RenderEvent1<void*>;
		// FUNCTION: ENGINE 0x10860140
		// FUNCTION: ENGINE 0x10860160
		template class RenderEvent1<int>;
		// FUNCTION: ENGINE 0x10860180
		// FUNCTION: ENGINE 0x108601A0
		template class RenderEvent1<bool>;

		// FUNCTION: ENGINE 0x10860EF0
		template void QueueRenderEvent<void*>(void (*)(void*), void*);
		// FUNCTION: ENGINE 0x10860F30
		template void QueueRenderEvent<int>(void (*)(int), int);
		// FUNCTION: ENGINE 0x10860F70
		template void QueueRenderEvent<bool>(void (*)(bool), bool);

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
