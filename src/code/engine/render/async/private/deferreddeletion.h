// engine::render::DeferredDeletionManager (the name is in the overflow assert; deferreddeletion.cpp): a ring of 3200
// reference-counted objects the game thread has finished with. The render thread may still be using them, so they are
// only released a frame later (Process runs once per frame). The members are named after the assert texts
// (mRefCountedItems, mHead, mTail); the two counters are guesses.
#ifndef ENGINE_RENDER_ASYNC_PRIVATE_DEFERREDDELETION_H
#define ENGINE_RENDER_ASYNC_PRIVATE_DEFERREDDELETION_H

#include "code/pure3d/entity.h"

namespace engine
{
	namespace render
	{
		// An integer the render and game threads share; every access is interlocked (names are guesses)
		class AtomicInt
		{
		public:
			AtomicInt() : mValue(0)
			{
			}
			// 0x108BC250
			long Load();
			// 0x108BC270 / 0x108BC280: the new value
			long Increment();
			long Decrement();
			// 0x108BC290: the previous value
			long Exchange(long value);
			long ExchangeAdd(long value);

			volatile long mValue;
		};

		// An index into a ring of Count slots
		template<int Count> class RingIndex : public AtomicInt
		{
		public:
			// 0x108BC3D0: moves to the next slot
			void Advance();
		};

		// A reference-counted pointer: it holds a reference to the object (names are guesses)
		template<class T> class RefPtr
		{
		public:
			// 0x108BC2A0
			explicit RefPtr(T* object) : mPointer(object)
			{
				if (object != 0)
				{
					object->AddRef();
				}
			}
			~RefPtr()
			{
				Release();
			}
			// 0x108BC2C0
			void Release()
			{
				T* object = mPointer;
				if (object != 0)
				{
					mPointer = 0;
					object->Release();
				}
			}
			// 0x108BC2E0
			T* operator=(T* object)
			{
				if (mPointer != object)
				{
					T* old = mPointer;
					mPointer = object;
					if (object != 0)
					{
						object->AddRef();
					}
					if (old != 0)
					{
						old->Release();
					}
				}
				return mPointer;
			}
			// 0x108BC320
			bool operator==(T* object) const
			{
				return mPointer == object;
			}

			T* mPointer;
		};

		// A deferred object and the frame from which it may be released
		struct RefCountedItem
		{
			// 0x108BC350
			RefCountedItem() : mFrame(0), mRef(0)
			{
			}
			~RefCountedItem()
			{
				Release();
			}
			// 0x108BC370
			void Set(pure3d::RefCounted* object, unsigned int frame)
			{
				mFrame = frame;
				mRef = object;
			}
			// 0x108BC3B0
			void Release()
			{
				mRef.Release();
			}
			bool Empty() const
			{
				return mRef == 0;
			}

			unsigned int mFrame;
			RefPtr<pure3d::RefCounted> mRef;
		};

		// An array of a fixed number of elements (0x108BC780 constructs the items, 0x108BC5D0 destroys them)
		template<class T, int Count> class FixedArray
		{
		public:
			static int Capacity()
			{
				return Count;
			}
			T& operator[](int index)
			{
				return mItems[index];
			}

			T mItems[Count];
		};

		class DeferredDeletionManager
		{
		public:
			// 0x108BC7B0
			DeferredDeletionManager();
			// 0x108BC620
			~DeferredDeletionManager();

			// 0x108BC640: keeps a reference to the entity until the render thread is done with it; releases
			// everything at once when the ring is full
			void Add(pure3d::Entity* entity);
			// 0x108BC400: releases the items added before the current frame, then starts the next frame; the frame
			// that ended
			int Process();
			// 0x108BC550: releases every item
			void Clear();

			AtomicInt mCount;
			AtomicInt mFrame;
			RingIndex<3200> mHead;
			RingIndex<3200> mTail;
			FixedArray<RefCountedItem, 3200> mRefCountedItems;
		};
	}
}

#endif
