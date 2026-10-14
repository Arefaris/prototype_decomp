// engine::render::DeferredDeletionManager (assert path ..\..\..\code\engine\render\async\private\
// deferreddeletion.cpp): the ring of objects whose release waits for the render thread.
#include "code/core/debug.h"
#include "code/pure3d/pddi.h"
#include "code/engine/render/async/private/deferreddeletion.h"

extern "C"
{
	long _InterlockedAnd(long volatile*, long);
	long _InterlockedExchange(long volatile*, long);
	long _InterlockedExchangeAdd(long volatile*, long);
	long _InterlockedIncrement(long volatile*);
	long _InterlockedDecrement(long volatile*);
}
#pragma intrinsic(_InterlockedAnd, _InterlockedExchange, _InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)

#define DEFERREDDELETION_FILE "..\\..\\..\\code\\engine\\render\\async\\private\\deferreddeletion.cpp"

namespace engine
{
	namespace render
	{
		inline long AtomicInt::Load()
		{
			return _InterlockedAnd(&mValue, -1);
		}

		inline long AtomicInt::Increment()
		{
			return _InterlockedIncrement(&mValue);
		}

		inline long AtomicInt::Decrement()
		{
			return _InterlockedDecrement(&mValue);
		}

		inline long AtomicInt::Exchange(long value)
		{
			return _InterlockedExchange(&mValue, value);
		}

		inline long AtomicInt::ExchangeAdd(long value)
		{
			return _InterlockedExchangeAdd(&mValue, value);
		}

		template<int Count> inline void RingIndex<Count>::Advance()
		{
			Exchange((Load() + 1) % Count);
		}

		// FUNCTION: ENGINE 0x108BC7B0
		DeferredDeletionManager::DeferredDeletionManager()
		{
			mFrame.Exchange(0);
			mCount.Exchange(0);
			mHead.Exchange(0);
			mTail.Exchange(0);
		}

		// FUNCTION: ENGINE 0x108BC620
		DeferredDeletionManager::~DeferredDeletionManager()
		{
			Clear();
		}

		// FUNCTION: ENGINE 0x108BC550
		void DeferredDeletionManager::Clear()
		{
			for (int i = 0; i < mRefCountedItems.Capacity(); i++)
			{
				mRefCountedItems[i].Release();
			}
			mCount.Exchange(0);
			mHead.Exchange(0);
			mTail.Exchange(0);
		}

		// FUNCTION: ENGINE 0x108BC640
		void DeferredDeletionManager::Add(pure3d::Entity* entity)
		{
			if (entity == 0)
			{
				return;
			}
			if (mCount.Load() == mRefCountedItems.Capacity())
			{
				OLD_ASSERT_AT(DEFERREDDELETION_FILE, 0x69, false, "false",
					"DeferredDeletionManager overflowed, objects will be immediatly deleted. This may cause a long pause or "
					"graphical corruption, so it should be fixed, but you should be able to safely continue.");
				pure3d::pddi->Unknown9();
				Clear();
			}
			OLD_ASSERT_TEXT_AT(DEFERREDDELETION_FILE, 0x6e, mRefCountedItems[mHead.Load()].Empty(),
				"mRefCountedItems[mHead].Empty()");
			mRefCountedItems[mHead.Load()].Set(entity, mFrame.Load() + 1);
			mCount.Increment();
			mHead.Advance();
		}

		// FUNCTION: ENGINE 0x108BC400
		int DeferredDeletionManager::Process()
		{
			while (mTail.Load() != mHead.Load())
			{
				OLD_ASSERT_TEXT_AT(DEFERREDDELETION_FILE, 0x96, !mRefCountedItems[mTail.Load()].Empty(),
					"!mRefCountedItems[mTail].Empty()");
				if (mRefCountedItems[mTail.Load()].mFrame > (unsigned int)mFrame.Load())
				{
					break;
				}
				mRefCountedItems[mTail.Load()].Release();
				mCount.Decrement();
				mTail.Advance();
			}
			AtomicInt* frame = &mFrame;
			return frame->ExchangeAdd(1);
		}
	}
}

// Kept copies: the member functions of the helper classes in deferreddeletion.h that the original left as separate code
// FUNCTION: ENGINE 0x108BC270
// FUNCTION: ENGINE 0x108BC280
// FUNCTION: ENGINE 0x108BC2A0
// FUNCTION: ENGINE 0x108BC2C0
// FUNCTION: ENGINE 0x108BC2E0
// FUNCTION: ENGINE 0x108BC320
// FUNCTION: ENGINE 0x108BC330
// FUNCTION: ENGINE 0x108BC340
// FUNCTION: ENGINE 0x108BC350
// FUNCTION: ENGINE 0x108BC370
// FUNCTION: ENGINE 0x108BC3B0
// FUNCTION: ENGINE 0x108BC3D0
// FUNCTION: ENGINE 0x108BC5A0
// FUNCTION: ENGINE 0x108BC5D0
// FUNCTION: ENGINE 0x108BC780
