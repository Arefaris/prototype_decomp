// The render-thread globals of the asynchronous renderer (unit around 0x10817A10 - 0x10818F00, assert path
// ..\..\..\code\engine\render\async\private\renderglobals.cpp): the drawable table, the render event queues the game
// thread fills and the render thread drains, the event allocator and the deferred deletion list. Names are guesses.
#include <new>
#include "code/core/criticalsection.h"
#include "code/core/debug.h"
#include "code/core/heap.h"
#include "code/core/refptr.h"
#include "code/pure3d/scene.h"
#include "code/engine/render/async/drawable.h"
#include "code/engine/render/async/renderevent.h"
#include "code/engine/render/async/private/deferreddeletion.h"
#include "code/engine/render/async/private/drawableimpl.h"

extern "C"
{
	long _InterlockedAnd(long volatile*, long);
	long _InterlockedCompareExchange(long volatile*, long, long);
	long _InterlockedExchange(long volatile*, long);
	__int64 _InterlockedCompareExchange64(__int64 volatile*, __int64, __int64);
}
#pragma intrinsic(_InterlockedAnd, _InterlockedCompareExchange, _InterlockedExchange, _InterlockedCompareExchange64)

#define RENDERGLOBALS_FILE "..\\..\\..\\code\\engine\\render\\async\\private\\renderglobals.cpp"

namespace engine
{
	namespace render
	{
		// A drawable or controller handle: the slot's index and the slot's serial (the table compares both)
		union HandleParts
		{
			int value;
			struct
			{
				unsigned short index;
				unsigned short serial;
			};
		};

		// An empty allocator (the arrays keep one)
		struct NewAllocator
		{
		};

		// A slot of the controller table: the object a controller handle stands for, its controller and whether the
		// controller runs
		struct ControllerSlot
		{
			ControllerSlot();
			ControllerSlot(const ControllerSlot& other);

			void* unknown0;
			pure3d::FrameController* controller;
			bool active;
		};

		template<class T> struct HandleNode;

		// Constructs the slots in [first, last) (nothing for the plain types)
		template<class T> __forceinline void ConstructRange(T* first, T* last)
		{
			for (; first != last; ++first)
			{
				if (first != 0)
				{
					new (first) T;
				}
			}
		}
		template<> void ConstructRange<DrawableData>(DrawableData* first, DrawableData* last)
		{
			for (; first != last; ++first)
			{
				if (first != 0)
				{
					new (first) DrawableData;
				}
			}
		}

		// One slot made or unmade in place
		template<class T> void ConstructAt(T* slot)
		{
			if (slot != 0)
			{
				new (slot) T;
			}
		}
		template<class T> void DestroyAt(T* slot)
		{
			slot->~T();
		}
		template<class T> void DestroyRange(T* first, T* last)
		{
			for (; first != last; ++first)
			{
				DestroyAt(first);
			}
		}
		// The serial array's elements read and written by index
		template<class T> void SetElement(T* array, int index, const T* value)
		{
			array[index] = *value;
		}
		template<class T> void GetElement(T* array, int index, T* value)
		{
			*value = array[index];
		}

		// An array of begin / end pointers over operator new[] (names guessed)
		template<class T> struct SlotArray
		{
			// A new array of count elements; false (and an empty array) when count is 0 or the allocation fails
			bool Allocate(unsigned int count)
			{
				if (count > 0)
				{
					begin = (T*)operator new[](count * sizeof(T));
					if (begin != 0)
					{
						end = begin + count;
						return true;
					}
				}
				begin = 0;
				end = 0;
				return false;
			}
			// An array of count constructed elements (empty when count is 0 or the allocation fails)
			__forceinline SlotArray(unsigned int count, const NewAllocator& allocator)
			{
				if (count > 0)
				{
					begin = (T*)operator new[](count * sizeof(T));
					if (begin != 0)
					{
						end = begin + count;
						ConstructRange(begin, end);
						return;
					}
				}
				begin = 0;
				end = 0;
			}
			T& operator[](unsigned int index)
			{
				return begin[index];
			}
			~SlotArray()
			{
				DestroyRange(begin, end);
				if (begin != 0)
				{
					delete[] begin;
				}
			}

			T* begin;
			T* end;
			NewAllocator allocator;
		};

		// A free slot index: the nodes form a lock-free stack through next
		template<class T> struct HandleNode
		{
			HandleNode* next;
			unsigned int index;
		};

		// The slots behind the handles: a handle is valid while its serial is the slot's (names guessed)
		template<class T> class HandleTable
		{
		public:
			explicit HandleTable(unsigned int count) : mSlots(count, NewAllocator()), mNodes(count, NewAllocator()), mSerials(count, NewAllocator())
			{
				mCount = count;
				_InterlockedExchange((long volatile*)&mFreeList, 0);
				for (unsigned int i = 0; i < count; i++)
				{
					mSerials[i] = 0;
					mNodes[i].index = i;
					HandleNode<T>* node = &mNodes[i];
					node->next = mFreeList;
					mFreeList = node;
				}
			}
			~HandleTable()
			{
			}
			bool IsValid(const HandleParts& handle) const
			{
				int index = handle.value & 0xFFFF;
				return (unsigned int)index < mCount && handle.serial == mSerials.begin[index];
			}
			unsigned int GetCount() const
			{
				return mCount;
			}
			// A free slot for the handle (null when there is none)
			T* Alloc(HandleParts* handle)
			{
				HandleNode<T>* node = mFreeList;
				HandleNode<T>* expected;
				do
				{
					if (node == 0)
					{
						return 0;
					}
					HandleNode<T>* next = node->next;
					expected = node;
					node = (HandleNode<T>*)_InterlockedCompareExchange((long volatile*)&mFreeList, (long)next, (long)expected);
				} while (node != expected);
				if (node == 0)
				{
					return 0;
				}
				handle->index = (unsigned short)node->index;
				mSerials.begin[handle->value & 0xFFFF] = sSerial;
				handle->serial = (unsigned short)sSerial;
				sSerial = sSerial + 1;
				if (sSerial > 0xFFFE)
				{
					sSerial = 1;
				}
				return &mSlots.begin[handle->value & 0xFFFF];
			}
			void Free(const HandleParts& handle)
			{
				int index = handle.value & 0xFFFF;
				if ((unsigned int)index >= mCount)
				{
					return;
				}
				unsigned int* serial = &mSerials.begin[index];
				if (handle.serial != *serial)
				{
					return;
				}
				*serial = 0;
				HandleNode<T>* node = &mNodes.begin[handle.value & 0xFFFF];
				HandleNode<T>* head = mFreeList;
				HandleNode<T>* expected;
				do
				{
					node->next = head;
					expected = head;
					head = (HandleNode<T>*)_InterlockedCompareExchange((long volatile*)&mFreeList, (long)node, (long)expected);
				} while (head != expected);
			}
			T* Get(const HandleParts& handle) const
			{
				int index = handle.value & 0xFFFF;
				if ((unsigned int)index < mCount && handle.serial == mSerials.begin[index])
				{
					return &mSlots.begin[index];
				}
				return 0;
			}
			T* GetByIndex(unsigned int index) const
			{
				if (index < mCount && mSerials.begin[index] != 0)
				{
					return &mSlots.begin[index];
				}
				return 0;
			}

			SlotArray<T> mSlots;
			HandleNode<T>* volatile mFreeList;
			SlotArray<HandleNode<T> > mNodes;
			SlotArray<unsigned int> mSerials;
			unsigned int mCount;
			static unsigned int sSerial;
		};

		// The controller slots' array is built out of line
		// FUNCTION: ENGINE 0x10818B30
		// EQUIVALENT: the branch for an empty range goes to the second of the two identical epilogue copies, the original's to the first (98.9%)
		template<> __declspec(noinline) SlotArray<ControllerSlot>::SlotArray(unsigned int count, const NewAllocator& allocator)
		{
			if (count > 0)
			{
				begin = (ControllerSlot*)operator new[](count * sizeof(ControllerSlot));
				if (begin != 0)
				{
					end = begin + count;
					ConstructRange(begin, end);
					return;
				}
			}
			begin = 0;
			end = 0;
		}

		typedef HandleTable<DrawableData> DrawableTable;
		typedef HandleTable<ControllerSlot> ControllerTable;

		// The memory the render events are made in (a heap allocator)
		class RenderEventAllocator : public core::IMemoryAllocator
		{
		};

		// A queue the game thread pushes into and the render thread pops from: a ring of 1 << Bits values behind two
		// semaphores (free slots, ready values); a pushed slot becomes readable once every slot before it has been
		// committed (the commit state at +0x10 holds the oldest uncommitted slot in its low Bits and a bitmap of the
		// slots committed after it above)
		template<class T, int Bits> struct AsyncQueue
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
			T values[1 << Bits];
		};

		// The unit's globals stay the image's
		extern RenderList* gRenderList;
		extern DrawableTable* gDrawableTable;
		extern ControllerTable* gControllerTable;
		extern DeferredDeletionManager* gDeferredDeletionManager;
		extern RenderEventAllocator* gRenderEventAllocator;
		extern AsyncQueue<RenderEvent*, 17> gRenderEventQueue;
		extern AsyncQueue<RenderEvent*, 13> gRenderEventQueueSecondary;

		// Runs the queued render events now (another unit, 0x10861550)
		void FlushRenderEvents();

		// Element constructors
		ControllerSlot::ControllerSlot()
		{
			unknown0 = 0;
			controller = 0;
			active = true;
		}

		ControllerSlot::ControllerSlot(const ControllerSlot& other)
		{
			unknown0 = other.unknown0;
			controller = other.controller;
			active = other.active;
		}

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
		// The next write slot (the ring index wraps at the ring size)
		template<class T, int Bits> long AllocAsyncQueueSlot(AsyncQueue<T, Bits>* queue)
		{
			long slot = 0;
			long index = _InterlockedAnd(&queue->writeIndex, -1);
			long expected = ~index;
			while (expected != index)
			{
				slot = index;
				long next = (index + 1) & ((1 << Bits) - 1);
				expected = index;
				index = _InterlockedCompareExchange(&queue->writeIndex, next, expected);
			}
			return slot;
		}

		// FUNCTION: ENGINE 0x10817F90
		// EQUIVALENT: same operations in the same order; the head, the bitmap and the counters sit in other registers, the comparand of the compare exchange in other stack slots (31.0%)
		// Marks the slot as written; the number of slots that became readable. The state holds the oldest uncommitted
		// slot in its low Bits and one bit per later slot (set once committed) above
		template<class T, int Bits> unsigned int CommitAsyncQueueSlots(int* commits, long slot)
		{
			const unsigned int headMask = (1 << Bits) - 1;
			const unsigned int bitCount = 64 - Bits;
			unsigned int count = 0;
			unsigned int offset = 0;
			do
			{
				unsigned __int64 seen = _InterlockedCompareExchange64((__int64 volatile*)commits, 0, 0);
				unsigned __int64 expected = ~seen;
				while (expected != seen)
				{
					unsigned int head = (unsigned int)seen & headMask;
					unsigned __int64 later = seen >> Bits;
					if (head == (unsigned int)slot)
					{
						count = 1;
						unsigned __int64 rest = later;
						unsigned int bit = (unsigned int)rest & 1;
						rest >>= 1;
						for (unsigned int shifted = 0; shifted < bitCount; shifted++)
						{
							if (bit == 0)
							{
								break;
							}
							bit = (unsigned int)rest & 1;
							rest >>= 1;
							count++;
						}
						later = rest;
						head = (head + count) & headMask;
						offset = 0;
					}
					else
					{
						count = 0;
						offset = (((unsigned int)slot - head) & headMask) - 1;
						if (offset < bitCount)
						{
							later |= (unsigned __int64)1 << offset;
						}
					}
					unsigned __int64 updated = (later << Bits) | head;
					expected = seen;
					seen = _InterlockedCompareExchange64((__int64 volatile*)commits, updated, expected);
				}
			} while (offset >= bitCount);
			return count;
		}

		// 0x108186B0: takes the value at the read index and gives its slot back
		template<class T, int Bits> void TakeAsyncQueueValue(AsyncQueue<T, Bits>* queue, T* value);

		// FUNCTION: ENGINE 0x10818260
		bool IsValidDrawable(const Drawable& drawable)
		{
			return gDrawableTable->IsValid((const HandleParts&)drawable.mHandle);
		}

		// FUNCTION: ENGINE 0x108185F0
		// A free slot, or -1 when the queue is full
		template<class T, int Bits> long ReserveAsyncQueueSlot(AsyncQueue<T, Bits>* queue)
		{
			if (core::SemaphoreWaitTimeout(&queue->freeSemaphore, 0))
			{
				return -1;
			}
			return AllocAsyncQueueSlot(queue);
		}

		// FUNCTION: ENGINE 0x10818620
		template<class T, int Bits> void CommitAsyncQueueSlot(AsyncQueue<T, Bits>* queue, long slot)
		{
			unsigned int ready = CommitAsyncQueueSlots<T, Bits>(queue->commits, slot);
			if (ready > 0)
			{
				core::SemaphoreRelease(&queue->readySemaphore, ready);
			}
		}

		// FUNCTION: ENGINE 0x108186B0
		// Takes the value at the read index and gives its slot back
		template<class T, int Bits> void TakeAsyncQueueValue(AsyncQueue<T, Bits>* queue, T* value)
		{
			long slot = 0;
			long index = _InterlockedAnd(&queue->readIndex, -1);
			long expected = ~index;
			while (expected != index)
			{
				slot = index;
				long next = (index + 1) & ((1 << Bits) - 1);
				expected = index;
				index = _InterlockedCompareExchange(&queue->readIndex, next, expected);
			}
			*value = queue->values[slot];
			core::SemaphoreRelease(&queue->freeSemaphore, 1);
		}

		// FUNCTION: ENGINE 0x10817D90
		// An empty queue (initial slots already written) with its two semaphores
		template<class T, int Bits> void InitAsyncQueue(AsyncQueue<T, Bits>* queue, int initial)
		{
			queue->unknown0[0] = 0;
			queue->unknown0[1] = 0;
			queue->readIndex = 0;
			queue->unknownC = 0;
			queue->commits[1] = 0;
			queue->unknown1C = 0;
			queue->commits[0] = initial;
			queue->writeIndex = initial;
			core::SemaphoreCreate(&queue->freeSemaphore, (1 << Bits) - initial);
			core::SemaphoreCreate(&queue->readySemaphore, initial);
		}

		// FUNCTION: ENGINE 0x10817E30
		template<class T, int Bits> void ShutdownAsyncQueue(AsyncQueue<T, Bits>* queue)
		{
			core::SemaphoreDestroy(&queue->freeSemaphore);
			core::SemaphoreDestroy(&queue->readySemaphore);
		}

		// FUNCTION: ENGINE 0x10818920
		DrawableData* GetDrawableData(const Drawable& drawable)
		{
			return gDrawableTable->Get((const HandleParts&)drawable.mHandle);
		}

		// FUNCTION: ENGINE 0x10818C00
		template<class T, int Bits> bool TryPushAsyncQueue(AsyncQueue<T, Bits>* queue, const T& value)
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
		template<class T, int Bits> bool TryPopAsyncQueue(AsyncQueue<T, Bits>* queue, T* value)
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

		// FUNCTION: ENGINE 0x10818D30
		void PushRenderEventSecondary(RenderEvent* event)
		{
			if (TryPushAsyncQueue(&gRenderEventQueueSecondary, event))
			{
				return;
			}
			FlushRenderEvents();
			if (TryPushAsyncQueue(&gRenderEventQueueSecondary, event))
			{
				return;
			}
			OLD_ASSERT_AT(RENDERGLOBALS_FILE, 0xCC, false, "false", "");
			FreeRenderEvent(event);
		}

		// FUNCTION: ENGINE 0x10818DE0
		// The render thread: runs the events of the second queue
		void ExecuteSecondaryRenderEvents()
		{
			RenderEvent* event;
			while (TryPopAsyncQueue(&gRenderEventQueueSecondary, &event) && event != 0)
			{
				event->Execute();
			}
		}

		// The render thread: whether it runs, and the way the frame is run (2: the game thread waits for the render thread)
		extern bool gRenderThreadRunning;
		extern int gRenderMode;
		// The object the render thread draws the list with (0x40 bytes; another unit)
		class RenderObject
		{
		public:
			// 0x108BD150 / 0x108BCBE0
			explicit RenderObject(RenderList* list);
			~RenderObject();

			unsigned char unknown0[0x40];
		};
		extern RenderObject* gRenderObject;

		// FUNCTION: ENGINE 0x10817A10
		void SetRenderThreadRunning(bool running)
		{
			gRenderThreadRunning = running;
		}

		// FUNCTION: ENGINE 0x10817A20
		bool IsRenderThreadRunning()
		{
			return gRenderThreadRunning;
		}

		// FUNCTION: ENGINE 0x10817A30
		void SetRenderMode(int mode)
		{
			gRenderMode = mode;
		}

		// FUNCTION: ENGINE 0x10817A40
		int GetRenderMode()
		{
			return gRenderMode;
		}

		// FUNCTION: ENGINE 0x10817AF0
		int ProcessDeferredDeletion()
		{
			return gDeferredDeletionManager->Process();
		}

		// FUNCTION: ENGINE 0x10817B00
		RenderObject* GetRenderObject()
		{
			return gRenderObject;
		}

		// FUNCTION: ENGINE 0x10817B20
		void InvalidateHandle(int* handle)
		{
			*handle = -1;
		}

		// FUNCTION: ENGINE 0x10817B60
		bool RenderTrue()
		{
			return true;
		}

		// A handle the controller table gave out
		class ControllerHandle
		{
		public:
			ControllerHandle() : mHandle(-1)
			{
			}

			int mHandle;
		};

		// FUNCTION: ENGINE 0x10818290
		bool IsValidController(const ControllerHandle& handle)
		{
			return gControllerTable->IsValid((const HandleParts&)handle.mHandle);
		}

		// FUNCTION: ENGINE 0x10818790
		Drawable AllocateDrawable(SourceDrawable* source, bool registerOnCreate)
		{
			Drawable drawable;
			DrawableData* data = gDrawableTable->Alloc((HandleParts*)&drawable.mHandle);
			if (data != 0)
			{
				OLD_ASSERT_TEXT_AT(RENDERGLOBALS_FILE, 0x133, 0 == data->sourceDrawable, "0 == drawableData->sourceDrawable");
				core::RefAssign((core::IRefCount*&)data->sourceDrawable, (core::IRefCount*)source);
				data->drawable = 0;
				data->created = false;
				data->registered = false;
				data->registerOnCreate = registerOnCreate;
			}
			return drawable;
		}

		// FUNCTION: ENGINE 0x10818820
		ControllerHandle AllocateController()
		{
			ControllerHandle handle;
			ControllerSlot* slot = gControllerTable->Alloc((HandleParts*)&handle.mHandle);
			slot->unknown0 = 0;
			slot->controller = 0;
			return handle;
		}

		// FUNCTION: ENGINE 0x10818850
		void FreeDrawable(Drawable drawable, DestroyMode mode)
		{
			DrawableData* data = gDrawableTable->Get((const HandleParts&)drawable.mHandle);
			if (data != 0)
			{
				SourceDrawable* source = data->sourceDrawable;
				if (source != 0 && data->drawable == source->drawable)
				{
					source->flags24 &= 0xFB;
				}
				if (data->drawable != 0 && data->drawable->registered)
				{
					GetRenderList()->Remove(data->drawable);
					data->registered = false;
				}
				if (mode == DESTROY_MODE_DEFERRED)
				{
					gDeferredDeletionManager->Add(data->drawable);
				}
				pure3d::RefCounted::Release(data->unknown4);
				core::SafeRelease(data->drawable);
				core::SafeRelease((core::IRefCount*&)data->sourceDrawable);
				gDrawableTable->Free((const HandleParts&)drawable.mHandle);
			}
		}

		// FUNCTION: ENGINE 0x10818900
		void FreeController(const ControllerHandle& handle)
		{
			gControllerTable->Free((const HandleParts&)handle.mHandle);
		}

		// FUNCTION: ENGINE 0x10818950
		void* GetControllerObject(const ControllerHandle& handle)
		{
			ControllerSlot* slot = gControllerTable->Get((const HandleParts&)handle.mHandle);
			if (slot != 0)
			{
				return slot->unknown0;
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x10818990
		ControllerSlot* GetControllerSlot(const ControllerHandle& handle)
		{
			return gControllerTable->Get((const HandleParts&)handle.mHandle);
		}

		// FUNCTION: ENGINE 0x108189C0
		void UpdateControllers(float dt)
		{
			unsigned int count = gControllerTable->GetCount();
			for (unsigned int i = 0; i < count; i++)
			{
				ControllerSlot* slot = gControllerTable->GetByIndex(i);
				if (slot != 0 && slot->active)
				{
					pure3d::FrameController* controller = slot->controller;
					if (controller != 0)
					{
						controller->Advance(dt, true);
					}
				}
			}
		}

		// The queues' instances of the queue functions
		template void InitAsyncQueue<RenderEvent*, 17>(AsyncQueue<RenderEvent*, 17>* queue, int initial);
		template void ShutdownAsyncQueue<RenderEvent*, 17>(AsyncQueue<RenderEvent*, 17>* queue);
		// FUNCTION: ENGINE 0x10817DE0
		template void InitAsyncQueue<RenderEvent*, 13>(AsyncQueue<RenderEvent*, 13>* queue, int initial);
		// FUNCTION: ENGINE 0x10817E50
		template void ShutdownAsyncQueue<RenderEvent*, 13>(AsyncQueue<RenderEvent*, 13>* queue);
		// FUNCTION: ENGINE 0x108180C0
		template long AllocAsyncQueueSlot<RenderEvent*, 13>(AsyncQueue<RenderEvent*, 13>* queue);
		// FUNCTION: ENGINE 0x10818110
		// EQUIVALENT: same operations in the same order; the head, the bitmap and the counters sit in other registers, the comparand of the compare exchange in other stack slots
		template unsigned int CommitAsyncQueueSlots<RenderEvent*, 13>(int* commits, long slot);
		// FUNCTION: ENGINE 0x10818650
		template long ReserveAsyncQueueSlot<RenderEvent*, 13>(AsyncQueue<RenderEvent*, 13>* queue);
		// FUNCTION: ENGINE 0x10818680
		template void CommitAsyncQueueSlot<RenderEvent*, 13>(AsyncQueue<RenderEvent*, 13>* queue, long slot);
		// FUNCTION: ENGINE 0x10818720
		template void TakeAsyncQueueValue<RenderEvent*, 13>(AsyncQueue<RenderEvent*, 13>* queue, RenderEvent** value);
		// FUNCTION: ENGINE 0x10818C30
		template bool TryPushAsyncQueue<RenderEvent*, 13>(AsyncQueue<RenderEvent*, 13>* queue, RenderEvent* const& value);
		// FUNCTION: ENGINE 0x10818C90
		template bool TryPopAsyncQueue<RenderEvent*, 13>(AsyncQueue<RenderEvent*, 13>* queue, RenderEvent** value);

		// What the render globals are made from (the settings of the renderer, at 0x113159B8; only what this unit reads)
		struct RenderConfig
		{
			unsigned char unknown0[0x64];
			unsigned int drawableCount;
			int unknown68;
			unsigned char unknown6C[4];
			unsigned int controllerCount;
			unsigned char unknown74[0xC];
			// The bytes of the heap the render events are made in
			unsigned int eventHeapSize;
			unsigned char unknown84[0x20];
			float unknownA4;
		};

		// FUNCTION: ENGINE 0x10819040
		// EQUIVALENT: same operations in the same order; the store of the new allocator and the load of its function table are swapped (99.1%)
		void InitRenderGlobals(const RenderConfig* config)
		{
			int heap = core::SetCurrentHeap(0x76);
			gDrawableTable = new DrawableTable(config->drawableCount);
			gControllerTable = new ControllerTable(config->controllerCount);
			gDeferredDeletionManager = new DeferredDeletionManager;
			pure3d::SceneSettings settings;
			settings.drawableCount = config->drawableCount;
			settings.unknownC = config->unknown68;
			settings.unknown10 = config->unknownA4;
			settings.unknown44 = config->unknown68;
			gRenderList = new RenderList(settings);
			gRenderObject = new RenderObject(gRenderList);
			InitAsyncQueue(&gRenderEventQueue, 0);
			InitAsyncQueue(&gRenderEventQueueSecondary, 0);
			core::IMemoryAllocator* allocator = core::NewHeapAllocator(config->eventHeapSize, 0x76, "Render Event Queue", 0x10, false, true);
			gRenderEventAllocator = (RenderEventAllocator*)allocator;
			allocator->AddRef();
			gRenderEventAllocator->SetSafetyMode(2);
			core::SetCurrentHeap(heap);
		}

		// FUNCTION: ENGINE 0x10819240
		void ShutdownRenderGlobals()
		{
			delete gDeferredDeletionManager;
			delete gControllerTable;
			delete gDrawableTable;
			delete gRenderObject;
			delete gRenderList;
			gRenderEventAllocator->Release();
			ShutdownAsyncQueue(&gRenderEventQueue);
			ShutdownAsyncQueue(&gRenderEventQueueSecondary);
		}

		// The members of the arrays and tables the original keeps out of line
		// FUNCTION: ENGINE 0x10817EB0
		template void ConstructAt<DrawableData>(DrawableData* slot);
		// FUNCTION: ENGINE 0x10817F00
		template void ConstructAt<ControllerSlot>(ControllerSlot* slot);
		// FUNCTION: ENGINE 0x10817B30
		template void ConstructRange<unsigned int>(unsigned int* first, unsigned int* last);
		// FUNCTION: ENGINE 0x10817E90
		template void SetElement<unsigned int>(unsigned int* array, int index, const unsigned int* value);
		// FUNCTION: ENGINE 0x10818240
		template void GetElement<unsigned int>(unsigned int* array, int index, unsigned int* value);
		// FUNCTION: ENGINE 0x10817ED0
		template void ConstructRange<HandleNode<DrawableData> >(HandleNode<DrawableData>* first, HandleNode<DrawableData>* last);
		// FUNCTION: ENGINE 0x10817EE0
		template void ConstructRange<HandleNode<ControllerSlot> >(HandleNode<ControllerSlot>* first, HandleNode<ControllerSlot>* last);
		// FUNCTION: ENGINE 0x10817EF0
		template void DestroyAt<DrawableData>(DrawableData* slot);
		// FUNCTION: ENGINE 0x10817F10
		template void DestroyAt<HandleNode<DrawableData> >(HandleNode<DrawableData>* slot);
		// FUNCTION: ENGINE 0x10817F20
		template void DestroyAt<ControllerSlot>(ControllerSlot* slot);
		// FUNCTION: ENGINE 0x10817F30
		template void DestroyAt<HandleNode<ControllerSlot> >(HandleNode<ControllerSlot>* slot);
		// FUNCTION: ENGINE 0x10818560
		template void DestroyAt<unsigned int>(unsigned int* slot);
		// FUNCTION: ENGINE 0x10818570
		template void DestroyRange<DrawableData>(DrawableData* first, DrawableData* last);
		// FUNCTION: ENGINE 0x10818580
		template void DestroyRange<HandleNode<DrawableData> >(HandleNode<DrawableData>* first, HandleNode<DrawableData>* last);
		// FUNCTION: ENGINE 0x108185C0
		template void DestroyRange<ControllerSlot>(ControllerSlot* first, ControllerSlot* last);
		// FUNCTION: ENGINE 0x108185D0
		template void DestroyRange<HandleNode<ControllerSlot> >(HandleNode<ControllerSlot>* first, HandleNode<ControllerSlot>* last);
		// FUNCTION: ENGINE 0x108185E0
		template void DestroyRange<unsigned int>(unsigned int* first, unsigned int* last);
		// FUNCTION: ENGINE 0x10818590
		template void ConstructRange<ControllerSlot>(ControllerSlot* first, ControllerSlot* last);
		// FUNCTION: ENGINE 0x10817C60
		template bool SlotArray<DrawableData>::Allocate(unsigned int count);
		// FUNCTION: ENGINE 0x10817CF0
		template bool SlotArray<ControllerSlot>::Allocate(unsigned int count);
		// FUNCTION: ENGINE 0x10817D40
		template bool SlotArray<HandleNode<DrawableData> >::Allocate(unsigned int count);
		// FUNCTION: ENGINE 0x10818A20
		template SlotArray<unsigned int>::SlotArray(unsigned int count, const NewAllocator& allocator);
		// FUNCTION: ENGINE 0x10818A70
		template SlotArray<DrawableData>::SlotArray(unsigned int count, const NewAllocator& allocator);
		// FUNCTION: ENGINE 0x10818AD0
		template SlotArray<HandleNode<DrawableData> >::SlotArray(unsigned int count, const NewAllocator& allocator);
		// FUNCTION: ENGINE 0x10818BA0
		template SlotArray<HandleNode<ControllerSlot> >::SlotArray(unsigned int count, const NewAllocator& allocator);
		// FUNCTION: ENGINE 0x10817C20
		template DrawableData& SlotArray<DrawableData>::operator[](unsigned int index);
		// FUNCTION: ENGINE 0x10817C30
		template HandleNode<DrawableData>& SlotArray<HandleNode<DrawableData> >::operator[](unsigned int index);
		// FUNCTION: ENGINE 0x10817C40
		template ControllerSlot& SlotArray<ControllerSlot>::operator[](unsigned int index);
		// FUNCTION: ENGINE 0x10817C50
		template HandleNode<ControllerSlot>& SlotArray<HandleNode<ControllerSlot> >::operator[](unsigned int index);
		// FUNCTION: ENGINE 0x10818AC0
		template SlotArray<DrawableData>::~SlotArray();
		// FUNCTION: ENGINE 0x10818B20
		template SlotArray<HandleNode<DrawableData> >::~SlotArray();
		// FUNCTION: ENGINE 0x10818B90
		template SlotArray<ControllerSlot>::~SlotArray();
		// FUNCTION: ENGINE 0x10818BF0
		template SlotArray<HandleNode<ControllerSlot> >::~SlotArray();

		// FUNCTION: ENGINE 0x10818E20
		// EQUIVALENT: the block that clears the first array when its allocation fails sits behind a jump after the construct call, the original's after the second array's success branch; one slot address is formed as (edx + ecx + 4), the original's (ecx + edx + 4) (81.7%)
		template HandleTable<DrawableData>::HandleTable(unsigned int count);
		// FUNCTION: ENGINE 0x10818F40
		template HandleTable<ControllerSlot>::HandleTable(unsigned int count);
		// FUNCTION: ENGINE 0x10818F00
		template HandleTable<DrawableData>::~HandleTable();
		// FUNCTION: ENGINE 0x10819000
		template HandleTable<ControllerSlot>::~HandleTable();
		// FUNCTION: ENGINE 0x10817BB0
		template bool HandleTable<DrawableData>::IsValid(const HandleParts& handle) const;
		// FUNCTION: ENGINE 0x10817BE0
		template bool HandleTable<ControllerSlot>::IsValid(const HandleParts& handle) const;
		// FUNCTION: ENGINE 0x10817C10
		template unsigned int HandleTable<ControllerSlot>::GetCount() const;
		// FUNCTION: ENGINE 0x108182C0
		template DrawableData* HandleTable<DrawableData>::Alloc(HandleParts* handle);
		// FUNCTION: ENGINE 0x108183E0
		template ControllerSlot* HandleTable<ControllerSlot>::Alloc(HandleParts* handle);
		// FUNCTION: ENGINE 0x10818350
		template void HandleTable<DrawableData>::Free(const HandleParts& handle);
		// FUNCTION: ENGINE 0x10818470
		template void HandleTable<ControllerSlot>::Free(const HandleParts& handle);
		// FUNCTION: ENGINE 0x108183B0
		template DrawableData* HandleTable<DrawableData>::Get(const HandleParts& handle) const;
		// FUNCTION: ENGINE 0x108184D0
		template ControllerSlot* HandleTable<ControllerSlot>::Get(const HandleParts& handle) const;
		// FUNCTION: ENGINE 0x10818500
		template ControllerSlot* HandleTable<ControllerSlot>::GetByIndex(unsigned int index) const;
	}
}
