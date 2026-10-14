// The render-thread globals of the asynchronous renderer (unit around 0x10817A10 - 0x10818F00, assert path
// ..\..\..\code\engine\render\async\private\renderglobals.cpp): the drawable table, the render event queues the game
// thread fills and the render thread drains, the event allocator and the deferred deletion list. Names are guesses.
#include "code/core/criticalsection.h"
#include "code/core/debug.h"
#include "code/engine/render/async/drawable.h"
#include "code/engine/render/async/renderevent.h"
#include "code/engine/render/async/private/deferreddeletion.h"
#include "code/engine/render/async/private/drawableimpl.h"

extern "C"
{
	long _InterlockedAnd(long volatile*, long);
	long _InterlockedCompareExchange(long volatile*, long, long);
}
#pragma intrinsic(_InterlockedAnd, _InterlockedCompareExchange)

#define RENDERGLOBALS_FILE "..\\..\\..\\code\\engine\\render\\async\\private\\renderglobals.cpp"

namespace engine
{
	namespace render
	{
		// A drawable handle's halves
		struct DrawableHandle
		{
			unsigned int index : 16;
			unsigned int serial : 16;
		};

		// The drawable table: a slot (16 bytes) and a serial per drawable handle index
		struct DrawableTable
		{
			DrawableData* slots;
			int unknown4[6];
			unsigned int* serials;
			int unknown20[2];
			unsigned int count;
		};

		// The memory the render events are made in (two virtuals used: slot 3 allocates, slot 4 frees)
		class RenderEventAllocator
		{
		public:
			virtual void Slot0();
			virtual void Slot1();
			virtual void Slot2();
			virtual void* Alloc(unsigned int size);
			virtual void Free(void* block);
		};

		// A queue the game thread pushes into and the render thread pops from: a ring of 0x20000 values behind two
		// semaphores (free slots, ready values); a pushed slot becomes readable once every slot before it has been
		// committed (the commit bookkeeping at +0x10 is not reconstructed)
		template<class T> struct AsyncQueue
		{
			int unknown0[2];
			long readIndex;
			int unknownC;
			int commits[2];
			long writeIndex;
			int unknown1C;
			void* freeSemaphore;
			void* readySemaphore;
			int unknown28[2];
			T values[0x20000];
		};

		// The unit's globals stay the image's (0x1130CCC0, 0x1130CCC4, 0x1130CCCC, 0x1130CCDC, 0x11284C60)
		extern RenderList* gRenderList;
		extern DrawableTable* gDrawableTable;
		extern DeferredDeletionManager* gDeferredDeletionManager;
		extern RenderEventAllocator* gRenderEventAllocator;
		extern AsyncQueue<RenderEvent*> gRenderEventQueue;

		// Runs the queued render events now (another unit, 0x10861550)
		void FlushRenderEvents();

		// FUNCTION: ENGINE 0x10817A50
		void* AllocRenderEvent(unsigned int size)
		{
			void* mem = gRenderEventAllocator->Alloc(size);
			if (mem == 0)
			{
				FlushRenderEvents();
				mem = gRenderEventAllocator->Alloc(size);
			}
			OLD_ASSERT_AT(RENDERGLOBALS_FILE, 0xA9, mem, "mem", "");
			return mem;
		}

		// FUNCTION: ENGINE 0x10817AD0
		void FreeRenderEvent(void* event)
		{
			gRenderEventAllocator->Free(event);
		}

		// FUNCTION: ENGINE 0x10817B10
		RenderList* GetRenderList()
		{
			return gRenderList;
		}

		// FUNCTION: ENGINE 0x10817B40
		void DeferDelete(pure3d::Entity* entity)
		{
			gDeferredDeletionManager->Add(entity);
		}

		// FUNCTION: ENGINE 0x10817F40
		// EQUIVALENT: same loop; the original keeps the index pointer in esi and the slot in edi (ours edx / esi)
		// The next write slot (the ring index wraps at 0x20000)
		template<class T> long AllocAsyncQueueSlot(AsyncQueue<T>* queue)
		{
			long slot = 0;
			long index = _InterlockedAnd(&queue->writeIndex, -1);
			long expected = ~index;
			while (expected != index)
			{
				slot = index;
				expected = index;
				index = _InterlockedCompareExchange(&queue->writeIndex, (index + 1) & 0x1FFFF, expected);
			}
			return slot;
		}

		// 0x10817F90: marks the slot as written; the number of slots that became readable
		template<class T> unsigned int CommitAsyncQueueSlots(int* commits, long slot);

		// 0x108186B0: takes the value at the read index and gives its slot back
		template<class T> void TakeAsyncQueueValue(AsyncQueue<T>* queue, T* value);

		// FUNCTION: ENGINE 0x10818260
		// EQUIVALENT: the original loads the whole handle and masks the index (`and eax, 0xFFFF`) and returns 1 / 0
		// in eax; every handle form tried loads the index as a word
		bool IsValidDrawable(const Drawable& drawable)
		{
			const DrawableHandle& handle = (const DrawableHandle&)drawable.mHandle;
			unsigned int index = handle.index;
			if (index < gDrawableTable->count && handle.serial == gDrawableTable->serials[index])
			{
				return true;
			}
			return false;
		}

		// FUNCTION: ENGINE 0x108185F0
		// A free slot, or -1 when the queue is full
		template<class T> long ReserveAsyncQueueSlot(AsyncQueue<T>* queue)
		{
			if (core::SemaphoreWaitTimeout(&queue->freeSemaphore, 0))
			{
				return -1;
			}
			return AllocAsyncQueueSlot(queue);
		}

		// FUNCTION: ENGINE 0x10818620
		template<class T> void CommitAsyncQueueSlot(AsyncQueue<T>* queue, long slot)
		{
			unsigned int ready = CommitAsyncQueueSlots<T>(queue->commits, slot);
			if (ready > 0)
			{
				core::SemaphoreRelease(&queue->readySemaphore, ready);
			}
		}

		// FUNCTION: ENGINE 0x10818920
		// EQUIVALENT: as IsValidDrawable: the index is a masked dword load in the original, a word load here
		DrawableData* GetDrawableData(const Drawable& drawable)
		{
			const DrawableHandle& handle = (const DrawableHandle&)drawable.mHandle;
			unsigned int index = handle.index;
			if (index < gDrawableTable->count && handle.serial == gDrawableTable->serials[index])
			{
				return &gDrawableTable->slots[index];
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x10818C00
		template<class T> bool TryPushAsyncQueue(AsyncQueue<T>* queue, const T& value)
		{
			long slot = ReserveAsyncQueueSlot(queue);
			if (slot == -1)
			{
				return false;
			}
			queue->values[slot] = value;
			CommitAsyncQueueSlot(queue, slot);
			return true;
		}

		// FUNCTION: ENGINE 0x10818C60
		template<class T> bool TryPopAsyncQueue(AsyncQueue<T>* queue, T* value)
		{
			if (core::SemaphoreWaitTimeout(&queue->readySemaphore, 0))
			{
				return false;
			}
			TakeAsyncQueueValue(queue, value);
			return true;
		}

		// FUNCTION: ENGINE 0x10818CC0
		void PushRenderEvent(RenderEvent* event)
		{
			if (TryPushAsyncQueue(&gRenderEventQueue, event))
			{
				return;
			}
			FlushRenderEvents();
			if (TryPushAsyncQueue(&gRenderEventQueue, event))
			{
				return;
			}
			OLD_ASSERT_AT(RENDERGLOBALS_FILE, 0xBE, false, "false", "");
			FreeRenderEvent(event);
		}

		// FUNCTION: ENGINE 0x10818DA0
		// The render thread: runs the queued events
		void ExecuteRenderEvents()
		{
			RenderEvent* event;
			while (TryPopAsyncQueue(&gRenderEventQueue, &event) && event != 0)
			{
				event->Execute();
			}
		}
	}
}
