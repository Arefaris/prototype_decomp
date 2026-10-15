#include <new>
#include <string.h>

#include "code/core/criticalsection.h"
#include "code/core/debug.h"
#include "code/core/heap.h"
#include "code/core/interlocked.h"
#include "code/core/time.h"
#include "code/ravenphysics/batch/midphasebatcher.h"
#include "code/ravenphysics/batch/narrowphasebatcher.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/physicsobject.h"
#include "code/ravenphysics/context.h"

#define CONTEXT_FILE "..\\..\\..\\code\\ravenphysics\\src\\context.cpp"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x106564E0
	void Context::ResetObjectWorld(ObjectHandle handle, void* world)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x215, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		PhysicsObject* object = handle.GetObject();
		unsigned int count = object->objectCount;
		object->objects[0]->IsFlag2();
		for (unsigned int i = 0; i < count; i++)
		{
			object->objects[i]->SetWorld(world);
		}
	}

	// The engine keeps two identical out-of-line copies of the object lookup; this unit's own code calls the one
	// inside its own object, so it is reconstructed here as well.
	// FUNCTION: ENGINE 0x1065F500
	PhysicsObject* ObjectHandle::GetObjectSecond() const
	{
		return gObjectTable->entries[index].object;
	}

	// FUNCTION: ENGINE 0x10657A50
	void Context::WakeObject(ObjectHandle handle)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x15c, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		PhysicsObject* object = handle.GetObjectSecond();
		if (object->IsAsleep())
		{
			return;
		}
		if (!object->IsSkipped())
		{
			object->RefreshBounds(object->IsUnflagged());
		}
		unknownC4->Add(object);
		if (!mWorld->Overlaps(object, unknownC4))
		{
			return;
		}
		if (!object->IsSkipped())
		{
			unsigned int count = object->objectCount;
			for (unsigned int i = 0; i < count; i++)
			{
				CollisionObject* collision = object->objects[i];
				if (++unknown4 == 0)
				{
					unknown4 = 1;
				}
				collision->unknown4C = unknown4;
			}
		}
		object->SetState(1, true);
		BroadPhaseDetector::ObjectTable* table = &unknownC4->Table();
		staticObjects.begin = table->objects;
		staticObjects.end = table->objects + table->staticCount;
		movableObjects.begin = table->objects + table->staticCount;
		movableObjects.end = table->objects + (table->movableCount + table->staticCount);
	}

	// FUNCTION: ENGINE 0x10657B60
	// NONMATCHING: register allocation, 97.6 %: the last list end loads the detector's movable count into ecx
	// where the engine loads the static count (both are then added the other way round, so only the two `movzx`
	// differ). The engine's WakeObject, whose tail is the same code, does load the movable count first, so the
	// order is not a property of the expression: both orders of the sum, the unparenthesised chain and a local
	// holding it all compile to the movable-first pair here.
#ifdef NONMATCHING
	void Context::SleepObject(PhysicsObject* object)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x1d8, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		if (!object->IsAsleep())
		{
			return;
		}
		if (!mWorld->Contains(object, unknownC4))
		{
			return;
		}
		if (!object->IsSkipped() && !unknownD8)
		{
			registry->Remove(object);
		}
		unknownC4->Remove(object);
		object->SetState(1, false);
		BroadPhaseDetector::ObjectTable* table = &unknownC4->Table();
		staticObjects.begin = table->objects;
		staticObjects.end = table->objects + table->staticCount;
		movableObjects.begin = table->objects + table->staticCount;
		movableObjects.end = table->objects + table->staticCount + table->movableCount;
	}
#endif

	// FUNCTION: ENGINE 0x10656580
	CollisionDetector* CollisionDetector::Clear()
	{
		mCollisionDetectorInternal = 0;
		unknown28 = 0;
		return this;
	}

	// FUNCTION: ENGINE 0x10656590
	void* CollisionDetector::GetObject()
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x270, mCollisionDetectorInternal, "mCollisionDetectorInternal",
			"Collision detection not running");
		return unknown28;
	}

	// FUNCTION: ENGINE 0x106565E0
	void* CollisionDetector::GetEvent()
	{
		return event;
	}

	// FUNCTION: ENGINE 0x10657C40
	void* CollisionDetector::GetEventChecked()
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x26a, mCollisionDetectorInternal, "mCollisionDetectorInternal",
			"Collision detection not running");
		return mCollisionDetectorInternal->GetEvent();
	}

	// FUNCTION: ENGINE 0x106566C0
	void Context::QueryObject(PhysicsBody* object)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x5e7, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryBody(object, unknownC4, object->filter & 3);
	}

	// FUNCTION: ENGINE 0x10656730
	void Context::QuerySweepObject(PhysicsBody* object, void* ray)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x604, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryPair(object, ray, unknownC4, object->filter & 3);
	}

	// FUNCTION: ENGINE 0x106567A0
	void Context::QueryObjectRay(PhysicsBody* object, void* ray)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x644, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryBodyRay(object, unknownC4, ray);
	}

	// FUNCTION: ENGINE 0x10656810
	void Context::QueryObjectShape(PhysicsBody* object, void* a, void* b)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x662, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryBodyShape(object, a, unknownC4, b);
	}

	// FUNCTION: ENGINE 0x10656880
	void Context::UpdateCollisionPairs()
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x69a, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		collisionBatch.Update(mWorld, unknownC4);
	}

	// FUNCTION: ENGINE 0x106568E0
	void* Context::AddCollisionPair(void* first, void* second)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6aa, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		collisionBatch.Add(first, second, 4);
		return first;
	}

	// FUNCTION: ENGINE 0x10656950
	void* Context::AddCollisionPairSlow(void* first, void* second)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6af, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		collisionBatch.Add(first, second, 8);
		return first;
	}

	// FUNCTION: ENGINE 0x106569C0
	void* Context::AddCollisionPairStatic(void* first, void* second)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6b4, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		collisionBatch.Add(first, second, 0x10);
		return first;
	}

	// FUNCTION: ENGINE 0x10656A30
	void Context::UpdateConstraints()
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6c1, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		constraintBatch.Update(mWorld, unknownC4);
	}

	// FUNCTION: ENGINE 0x10656A90
	void* Context::AddConstraint(void* first, void* second)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6d1, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		constraintBatch.Add(first, second, 0);
		return first;
	}

	// FUNCTION: ENGINE 0x10656B00
	void* Context::AddConstraintAwake(void* first, void* second)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6d6, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		constraintBatch.Add(first, second, 1);
		return first;
	}

	// FUNCTION: ENGINE 0x10656B70
	void* Context::AddConstraintAsleep(void* first, void* second)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6db, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		constraintBatch.Add(first, second, 2);
		return first;
	}

	// FUNCTION: ENGINE 0x10656BE0
	void Context::UpdateQueries()
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6e8, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		queryBatch.Update(mWorld, unknownC4);
	}

	// FUNCTION: ENGINE 0x10656C40
	void* Context::AddQuery(void* a, void* b, void* c, void* d)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6f9, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		queryBatch.Add(a, b, c, d);
		return a;
	}

	// FUNCTION: ENGINE 0x10656CB0
	void Context::QueryShape(void* a, void* b, void* c, void* d)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x715, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryShape(a, b, c, unknownC4, d);
	}

	// FUNCTION: ENGINE 0x10656D20
	void Context::QueryShapeSwept(void* a, void* b, void* c, void* d)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x73d, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryShapeOther(a, b, c, unknownC4, d);
	}

	// FUNCTION: ENGINE 0x10656D90
	void Context::QuerySphere(void* a, void* b, void* c, void* d)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x768, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryShape3(a, b, c, unknownC4, d);
	}

	// FUNCTION: ENGINE 0x10656E00
	void Context::QuerySphereSwept(void* a, void* b, void* c, void* d)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x790, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryShape2(a, b, c, unknownC4, d);
	}

	// FUNCTION: ENGINE 0x10656E70
	void Context::SetSolverIterations(int a, int b)
	{
		unknown10->solverIterations = a;
		unknown10->solverIterations2 = b;
	}

	// FUNCTION: ENGINE 0x106565F0
	void Context::Advance(void* a, float dt, void* b)
	{
		if (unknownD8)
		{
			return;
		}
		gLock.locked = true;
		placement->Advance(unknown10, &recordPool, a, dt, unknownC4, registry, b);
		gLock.locked = false;
	}

	// FUNCTION: ENGINE 0x10656640
	void Context::SetWorldFlag(unsigned char value)
	{
		if (placement != 0)
		{
			unknown10->unknownE = value;
		}
	}

	// FUNCTION: ENGINE 0x10656660
	void Context::ResetPlacement()
	{
		placement->Reset();
	}

	// FUNCTION: ENGINE 0x10656670
	void Context::SetPlacementPosition(math::Vector position)
	{
		placement->SetPosition(position);
	}

	// FUNCTION: ENGINE 0x10656680
	void Context::TrackMovableObjects()
	{
		placement->Track(&movableObjects);
	}

	// FUNCTION: ENGINE 0x10656690
	void Context::TrackObjects(ObjectList* objects)
	{
		placement->Track(objects);
	}

	// FUNCTION: ENGINE 0x106566A0
	void Context::UntrackMovableObjects()
	{
		placement->Untrack(&movableObjects);
	}

	// FUNCTION: ENGINE 0x106566B0
	void Context::UntrackObjects(ObjectList* objects)
	{
		placement->Untrack(objects);
	}

	// ---- the collision library's container accessors this unit emits --------------------------------------------

	// FUNCTION: ENGINE 0x10656EB0
	int RecordList52::Count() const
	{
		return (int)((mEnd - mBegin) / 52);
	}

	// FUNCTION: ENGINE 0x10656ED0
	int RecordList168::Count() const
	{
		return (int)((mEnd - mBegin) / 168);
	}

	// FUNCTION: ENGINE 0x10656EF0
	int RecordList12::Count() const
	{
		return (int)((mEnd - mBegin) / 12);
	}

	// FUNCTION: ENGINE 0x10656F10
	int PointerList::Count() const
	{
		return (int)(mEnd - mBegin);
	}

	// FUNCTION: ENGINE 0x10656F20
	int RecordList44::Count() const
	{
		return (int)((mEnd - mBegin) / 44);
	}

	// FUNCTION: ENGINE 0x10656F40
	int RecordList12Second::Count() const
	{
		return (int)((mEnd - mBegin) / 12);
	}

	// FUNCTION: ENGINE 0x106570B0
	int RecordList12Third::Count() const
	{
		return (int)((mEnd - mBegin) / 12);
	}

	// FUNCTION: ENGINE 0x106571A0
	int PointerListSecond::Count() const
	{
		return (int)(mEnd - mBegin);
	}

	// FUNCTION: ENGINE 0x10657240
	int PointerListThird::Count() const
	{
		return (int)(mEnd - mBegin);
	}

	// FUNCTION: ENGINE 0x10656EA0
	void** PointerList::End() const
	{
		return mEnd;
	}

	// FUNCTION: ENGINE 0x10656F60
	PointerList* PointerList::Clear()
	{
		mBegin = 0;
		mEnd = 0;
		return this;
	}

	// FUNCTION: ENGINE 0x10656FB0
	void** PointerList::Begin() const
	{
		return mBegin;
	}

	// FUNCTION: ENGINE 0x10656FC0
	void*& PointerList::operator[](int index)
	{
		return mBegin[index];
	}

	// FUNCTION: ENGINE 0x10656FD0
	PointerListSecond::PointerListSecond(unsigned int)
	{
		mBegin = 0;
		mEnd = 0;
	}

	// FUNCTION: ENGINE 0x10656FF0
	PointerListThird::PointerListThird(unsigned int)
	{
		mBegin = 0;
		mEnd = 0;
	}

	// FUNCTION: ENGINE 0x10657010
	unsigned char* Head18::GetHead()
	{
		return &head;
	}

	// FUNCTION: ENGINE 0x10657020
	PointerListFourth::PointerListFourth()
	{
		mBegin = 0;
		mEnd = 0;
	}

	// FUNCTION: ENGINE 0x10657060
	PointerListFifth::PointerListFifth()
	{
		mBegin = 0;
		mEnd = 0;
	}

	// FUNCTION: ENGINE 0x106570D0
	SlotPool::SlotPool()
	{
		mSlots = 0;
		mCapacity = 0;
		mCounter = 0;
	}

	// FUNCTION: ENGINE 0x106570E0
	void SlotPool::Reset()
	{
		if (mCounter != 0)
		{
			_InterlockedExchange(mCounter, 0);
		}
	}

	// FUNCTION: ENGINE 0x106570F0
	SlotPoolSecond::SlotPoolSecond()
	{
		mSlots = 0;
		mCapacity = 0;
		mCounter = 0;
	}

	// FUNCTION: ENGINE 0x10657100
	void SlotPoolSecond::Reset()
	{
		if (mCounter != 0)
		{
			_InterlockedExchange(mCounter, 0);
		}
	}

	// FUNCTION: ENGINE 0x10657110
	int SlotPool::ReadCounter()
	{
		if (mCounter != 0)
		{
			return _InterlockedAnd(mCounter, -1);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10657130
	long* SlotPool::GetCounter()
	{
		return mCounter;
	}

	// FUNCTION: ENGINE 0x10657140
	PointerListSecond::PointerListSecond(void** newBegin, void** newEnd)
	{
		mBegin = newBegin;
		mEnd = newEnd;
	}

	// FUNCTION: ENGINE 0x10657160
	void** PointerListSecond::Begin() const
	{
		return mBegin;
	}

	// FUNCTION: ENGINE 0x10657170
	void** PointerListSecond::End() const
	{
		return mEnd;
	}

	// FUNCTION: ENGINE 0x10657180
	void PointerListSecond::SetBegin(void** value)
	{
		mBegin = value;
	}

	// FUNCTION: ENGINE 0x10657190
	void PointerListSecond::SetEnd(void** value)
	{
		mEnd = value;
	}

	// FUNCTION: ENGINE 0x106571B0
	void*& PointerListSecond::operator[](int index)
	{
		return mBegin[index];
	}

	// FUNCTION: ENGINE 0x106571C0
	PointerListSecond::PointerListSecond()
	{
		mBegin = 0;
		mEnd = 0;
	}

	// FUNCTION: ENGINE 0x10657200
	void*& PointerListFifth::operator[](int index)
	{
		return mBegin[index];
	}

	// FUNCTION: ENGINE 0x10657210
	PointerListFifth::PointerListFifth(unsigned int)
	{
		mBegin = 0;
		mEnd = 0;
	}

	// FUNCTION: ENGINE 0x10657230
	unsigned char* PointerListFifth::ByteAt(int offset)
	{
		return (unsigned char*)mBegin + offset;
	}

	// FUNCTION: ENGINE 0x10657250
	void*& PointerListThird::operator[](int index)
	{
		return mBegin[index];
	}

	// FUNCTION: ENGINE 0x10657260
	void PointerListThird::SetEnd(void** value)
	{
		mEnd = value;
	}

	// FUNCTION: ENGINE 0x10657270
	void EmptyMembers::First()
	{
	}

	// FUNCTION: ENGINE 0x10657280
	void EmptyMembers::Second()
	{
	}

	// FUNCTION: ENGINE 0x10657290
	void EmptyMembers::Third()
	{
	}

	// FUNCTION: ENGINE 0x106572A0
	void EmptyMembers::Fourth()
	{
	}

	// FUNCTION: ENGINE 0x106572B0
	void EmptyMembers::Fifth()
	{
	}

	// FUNCTION: ENGINE 0x106572C0
	void EmptyMembers::Sixth()
	{
	}

	// FUNCTION: ENGINE 0x106572D0
	void EmptyMembers::Seventh()
	{
	}

	// FUNCTION: ENGINE 0x106572E0
	void EmptyMembers::Eighth()
	{
	}

	// FUNCTION: ENGINE 0x106572F0
	void* SlotPool::Acquire()
	{
		if (mCounter != 0)
		{
			int slot = _InterlockedIncrement(mCounter) - 1;
			if (slot < mCapacity)
			{
				return (char*)mSlots + (slot << 5);
			}
			_InterlockedDecrement(mCounter);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10657320
	PointerListSixth::PointerListSixth(void** newBegin, void** newEnd)
	{
		mBegin = newBegin;
		mEnd = newEnd;
	}

	// FUNCTION: ENGINE 0x10657340
	PointerListSeventh::PointerListSeventh(void** newBegin, void** newEnd)
	{
		mBegin = newBegin;
		mEnd = newEnd;
	}

	// FUNCTION: ENGINE 0x10657360
	void*& PointerListSixth::operator[](int index)
	{
		return mBegin[index];
	}

	// FUNCTION: ENGINE 0x10657370
	void*& PointerListSeventh::operator[](int index)
	{
		return mBegin[index];
	}

	// FUNCTION: ENGINE 0x10657380
	PointerListEighth::PointerListEighth(void** newBegin, void** newEnd)
	{
		mBegin = newBegin;
		mEnd = newEnd;
	}

	// FUNCTION: ENGINE 0x106573A0
	PointerListNinth::PointerListNinth(void** newBegin, void** newEnd)
	{
		mBegin = newBegin;
		mEnd = newEnd;
	}

	// FUNCTION: ENGINE 0x106573C0
	bool ScratchArray::Allocate(unsigned int count)
	{
		if (count != 0)
		{
			mBegin = (void**)allocator.Alloc(count * 4, 16);
			if (mBegin != 0)
			{
				mCapacity = mBegin + count;
				mEnd = mBegin;
				return true;
			}
		}
		else
		{
			mBegin = 0;
		}
		mEnd = 0;
		mCapacity = 0;
		return false;
	}

	// FUNCTION: ENGINE 0x10657410
	ScratchArray* ScratchArray::Self()
	{
		return this;
	}

	// FUNCTION: ENGINE 0x10657420
	void EmptyTail::Empty()
	{
	}

	// FUNCTION: ENGINE 0x10657430
	void* SlotPoolThird::Acquire()
	{
		if (mCounter != 0)
		{
			int slot = _InterlockedIncrement(mCounter) - 1;
			if (slot < mCapacity)
			{
				return mSlots + (slot << 4);
			}
			_InterlockedDecrement(mCounter);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10657460
	bool ScratchBytes::Reserve(unsigned int size)
	{
		if (size > 0)
		{
			mBegin = (unsigned char*)allocator.Alloc(size, 16);
			if (mBegin != 0)
			{
				mEnd = mBegin + size;
				return true;
			}
		}
		mBegin = 0;
		mEnd = 0;
		return false;
	}

	// FUNCTION: ENGINE 0x106574A0
	Record40::Record40(const Record32& record, const Pair8& id)
	{
		mRecord = record;
		mId = id;
	}

	// FUNCTION: ENGINE 0x106574D0
	Record40Second::Record40Second(const Record32& record, const Pair8& id)
	{
		mRecord = record;
		mId = id;
	}

	// FUNCTION: ENGINE 0x10657500
	void SlotPool::Init(unsigned int count, const ScratchStack&)
	{
		mSlots = core::HeapAllocAligned(core::GetCurrentHeap(), count << 5, 16);
		mCounter = (long*)core::HeapAllocAligned(core::GetCurrentHeap(), 4, 16);
		mCapacity = count;
		if (mCounter != 0)
		{
			_InterlockedExchange(mCounter, 0);
		}
	}

	// FUNCTION: ENGINE 0x10657550
	void SlotPoolThird::Init(unsigned int count, const ScratchStack&)
	{
		mSlots = (unsigned char*)core::HeapAllocAligned(core::GetCurrentHeap(), count << 4, 16);
		mCounter = (long*)core::HeapAllocAligned(core::GetCurrentHeap(), 4, 16);
		mCapacity = count;
		if (mCounter != 0)
		{
			_InterlockedExchange(mCounter, 0);
		}
	}

	// FUNCTION: ENGINE 0x106575A0
	void SlotPool::Release(int)
	{
		if (mSlots != 0)
		{
			core::FreeAligned(mSlots);
			core::FreeAligned(mCounter);
			mCounter = 0;
			mSlots = 0;
			mCapacity = 0;
		}
	}

	// FUNCTION: ENGINE 0x106575E0
	void SlotPoolThird::Release(int)
	{
		if (mSlots != 0)
		{
			core::FreeAligned(mSlots);
			core::FreeAligned(mCounter);
			mCounter = 0;
			mSlots = 0;
			mCapacity = 0;
		}
	}

	// FUNCTION: ENGINE 0x10657620
	void StoreId(int* target, const int* value)
	{
		if (target != 0)
		{
			*target = *value;
		}
	}

	// FUNCTION: ENGINE 0x10657640
	void StoreIdSecond(int* target, const int* value)
	{
		if (target != 0)
		{
			*target = *value;
		}
	}

	// FUNCTION: ENGINE 0x10657660
	short* ShortPair::At(int index)
	{
		return mFirst + index;
	}

	// FUNCTION: ENGINE 0x10657670
	short* ShortPair::Begin() const
	{
		return mFirst;
	}

	// FUNCTION: ENGINE 0x10657680
	int ShortPair::ByteSize() const
	{
		return mFirstCount * 2;
	}

	// FUNCTION: ENGINE 0x10657690
	int* IntArray::At(int index)
	{
		return mBegin + index;
	}

	// FUNCTION: ENGINE 0x106576A0
	void ShortPair::Fill()
	{
		memset(mSecond, 0xff, mSecondCount * 2);
		memset(mFirst, 0xff, mFirstCount * 2);
	}

	// FUNCTION: ENGINE 0x106576D0
	template Record40* ScratchStack::AllocArray<Record40>(int count, int align);

	// FUNCTION: ENGINE 0x10657700
	template Pair8* ScratchStack::AllocArray<Pair8>(int count, int align);

	// FUNCTION: ENGINE 0x10657750
	template Box124* ScratchStack::AllocArray<Box124>(int count, int align);

	// FUNCTION: ENGINE 0x10657780
	void EmptyMembers::Ninth()
	{
	}

	// FUNCTION: ENGINE 0x10657790
	void EmptyMembers::Tenth()
	{
	}

	// FUNCTION: ENGINE 0x106577A0
	void EmptyMembers::Eleventh()
	{
	}

	// FUNCTION: ENGINE 0x106577B0
	void EmptyMembers::Twelfth()
	{
	}

	// FUNCTION: ENGINE 0x106577C0
	void EmptyMembers::Thirteenth()
	{
	}

	// FUNCTION: ENGINE 0x106577D0
	void EmptyMembers::Fourteenth()
	{
	}

	// FUNCTION: ENGINE 0x106577E0
	void EmptyMembers::Fifteenth()
	{
	}

	// FUNCTION: ENGINE 0x106577F0
	void EmptyMembers::Sixteenth()
	{
	}

	// FUNCTION: ENGINE 0x10657800
	void EmptyMembers::Seventeenth()
	{
	}

	// FUNCTION: ENGINE 0x10657810
	void EmptyMembers::Eighteenth()
	{
	}

	// FUNCTION: ENGINE 0x10657820
	void EmptyMembers::Nineteenth()
	{
	}

	// FUNCTION: ENGINE 0x10657830
	void StoreByte(char* target, const char* value)
	{
		if (target != 0)
		{
			*target = *value;
		}
	}

	// FUNCTION: ENGINE 0x10657850
	ShortTriple::ShortTriple(unsigned short first, int second, int third)
	{
		mFirst = first;
		mSecond = second;
		mThird = third;
	}

	// FUNCTION: ENGINE 0x10657870
	Record40Third::Record40Third(const Record32& record, const Pair8& id)
	{
		mRecord = record;
		mId = id;
	}

	// FUNCTION: ENGINE 0x106578A0
	Record40Fourth::Record40Fourth(const Record32& record, const Pair8& id)
	{
		mRecord = record;
		mId = id;
	}

	// FUNCTION: ENGINE 0x106578D0
	void* WorkPools::Slot(unsigned short index) const
	{
		return mSecondSlots[index];
	}

	// FUNCTION: ENGINE 0x106578E0
	void WorkPools::ResetCounters()
	{
		if (mFirstCounter != 0)
		{
			_InterlockedExchange(mFirstCounter, 0);
		}
		if (mSecondCounter != 0)
		{
			_InterlockedExchange(mSecondCounter, 0);
		}
	}

	// FUNCTION: ENGINE 0x10657900
	void WorkPools::Init(unsigned int firstCount, unsigned int secondCount)
	{
		mFirstSlots = (void**)core::HeapAllocAligned(core::GetCurrentHeap(), firstCount << 5, 16);
		mFirstCounter = (long*)core::HeapAllocAligned(core::GetCurrentHeap(), 4, 16);
		mFirstCount = firstCount;
		if (mFirstCounter != 0)
		{
			_InterlockedExchange(mFirstCounter, 0);
		}
		mSecondSlots = (void**)core::HeapAllocAligned(core::GetCurrentHeap(), secondCount << 4, 16);
		mSecondCounter = (long*)core::HeapAllocAligned(core::GetCurrentHeap(), 4, 16);
		mSecondCount = secondCount;
		if (mSecondCounter != 0)
		{
			_InterlockedExchange(mSecondCounter, 0);
		}
	}

	// FUNCTION: ENGINE 0x10657990
	void WorkPools::ReleaseAll()
	{
		if (mFirstSlots != 0)
		{
			core::FreeAligned(mFirstSlots);
			core::FreeAligned(mFirstCounter);
			mFirstCounter = 0;
			mFirstSlots = 0;
			mFirstCount = 0;
		}
		if (mSecondCounter != 0)
		{
			long free = _InterlockedAnd(mSecondCounter, -1);
			if (free > 0 && mSecondSlots != 0)
			{
				core::FreeAligned(mSecondSlots);
				core::FreeAligned(mSecondCounter);
				mSecondCounter = 0;
				mSecondSlots = 0;
				mSecondCount = 0;
			}
		}
	}

	// FUNCTION: ENGINE 0x10657A00
	WorkPools::WorkPools()
	{
		mFirstSlots = 0;
		mFirstCount = 0;
		mFirstCounter = 0;
		mSecondSlots = 0;
		mSecondCount = 0;
		mSecondCounter = 0;
	}

	// FUNCTION: ENGINE 0x10657A20
	WordBlock4::WordBlock4()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
		unknownC = 0;
	}

	// FUNCTION: ENGINE 0x10658010
	void CounterPair::ResetCounters(int, int)
	{
		if (mFirstCounter != 0)
		{
			_InterlockedExchange(mFirstCounter, 0);
		}
		if (mSecondCounter != 0)
		{
			_InterlockedExchange(mSecondCounter, 0);
		}
	}

	// FUNCTION: ENGINE 0x10658030
	bool PointerRun::PushBack(void* const& value)
	{
		if (mEnd < mCapacity)
		{
			void** item = mEnd++;
			if (item != 0)
			{
				*item = value;
			}
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10658060
	void** PointerRun::Find(void* const& value)
	{
		void** item = mBegin;
		while (item != mEnd && *item != value)
		{
			item++;
		}
		return item;
	}

	// The slot the log hands out, or null when it is full; the engine's Add has this inlined, and the inliner's
	// copy of the returned pointer is what carries the explicit null test.
	inline void* AcquireStatSlot(StatLog* log)
	{
		if (log->count != 0)
		{
			int slot = _InterlockedIncrement(log->count) - 1;
			if (slot < log->capacity)
			{
				return (char*)log->entries + (slot << 4);
			}
			_InterlockedDecrement(log->count);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10658200
	bool StatLog::Add(const StatEntry& entry)
	{
		StatEntry* item = (StatEntry*)AcquireStatSlot(this);
		if (item != 0)
		{
			*item = entry;
			return true;
		}
		return false;
	}

	// The slot a 32-byte pool hands out, or null when it is full; the engine's Add has its own copy of this
	// inlined, and the inliner's copy of the returned pointer is what carries the explicit null test
	template<class Pool>
	inline void* AcquireSlot32(Pool* pool)
	{
		if (pool->mCounter != 0)
		{
			int slot = _InterlockedIncrement(pool->mCounter) - 1;
			if (slot < pool->mCapacity)
			{
				return (char*)pool->mSlots + (slot << 5);
			}
			_InterlockedDecrement(pool->mCounter);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10658080
	bool SlotPool::Add(const Record32& value)
	{
		Record32* item = (Record32*)AcquireSlot32(this);
		if (item != 0)
		{
			*item = value;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106580D0
	bool SlotPoolSecond::Add(const Record32& value)
	{
		Record32* item = (Record32*)AcquireSlot32(this);
		if (item != 0)
		{
			*item = value;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10658180
	void ScratchArray::Init(unsigned int count)
	{
		if (count != 0)
		{
			mBegin = (void**)allocator.Alloc(count * 4, 16);
			if (mBegin != 0)
			{
				mCapacity = mBegin + count;
				mEnd = mBegin;
				return;
			}
		}
		else
		{
			mBegin = 0;
		}
		mEnd = 0;
		mCapacity = 0;
	}

	// FUNCTION: ENGINE 0x106581D0
	bool PointerRunSecond::PushBack(void* const& value)
	{
		if (mEnd < mCapacity)
		{
			void** item = mEnd++;
			if (item != 0)
			{
				*item = value;
			}
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10658260
	unsigned short ShortValues::Get(int index) const
	{
		return mValues[index];
	}

	// FUNCTION: ENGINE 0x10658270
	unsigned short ShortValuesSecond::Get(unsigned short index) const
	{
		return mValues[index];
	}

	// FUNCTION: ENGINE 0x10658280
	void WalkableBatch::BeginWalk(RecordWalk* walk) const
	{
		walk->value = *mRecords;
		walk->owner = (void*)this;
		walk->limit = (char*)this + 0x20;
	}

	// FUNCTION: ENGINE 0x106582A0
	void ShortRun::Fill()
	{
		memset(mSecond, 0xff, mSecondCount * 2);
		memset(mFirst, 0xff, mFirstCount * 2);
		memset(mThird, -1, mThirdCount * 2);
	}

	// FUNCTION: ENGINE 0x106582F0
	template StatEntry* ScratchStack::AllocOne<StatEntry>(int unused);

	// FUNCTION: ENGINE 0x10658300
	template Box400* ScratchStack::AllocOne<Box400>(int unused);

	// FUNCTION: ENGINE 0x10658310
	template Box128* ScratchStack::AllocOne<Box128>(int unused);

	// FUNCTION: ENGINE 0x10658320
	void* IndexedHandle::Get() const
	{
		if (index != 0xffff)
		{
			return table->items[index];
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10658340
	void ChainedIndex::Next()
	{
		index = (*items)[index];
	}

	// FUNCTION: ENGINE 0x10658400
	void FillByteRun(char* target, unsigned int count, const char* value)
	{
		char* current = target;
		while (count != 0)
		{
			count--;
			if (current != 0)
			{
				*current = *value;
			}
			current++;
		}
	}

	// FUNCTION: ENGINE 0x10658430
	void Context::RefreshMovableObjects()
	{
		RefreshObjectList(&movableObjects);
	}

	// FUNCTION: ENGINE 0x10658440
	void* IndexedHandleSecond::Get() const
	{
		if (index != 0xffff)
		{
			return table->items[index];
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10658460
	void IndexedSlot::Set(ShortHead* newOwner, unsigned short newIndex)
	{
		owner = newOwner;
		index = newOwner->values[newIndex];
	}

	// FUNCTION: ENGINE 0x10658480
	// NONMATCHING: register allocation, 32 %: the engine reads the slot index before it stores the owner and then
	// loads the owner's run through the same register it stored, ours keeps the owner in a second register and
	// reloads through it (25 bytes against 28 with a `value` local, 28 against 28 without)
#ifdef NONMATCHING
	void IndexedSlotSecond::Get(RecordWalk* walk) const
	{
		unsigned short value = owner->values[index];
		walk->owner = owner;
		walk->value = value;
	}
#endif

	// FUNCTION: ENGINE 0x106584A0
	Block6::Block6()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
		unknownC = 0;
		unknown10 = 0;
		unknown14 = 0;
	}

	// FUNCTION: ENGINE 0x106584C0
	Block11::Block11()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
		unknownC = 0;
		unknown10 = 0;
		unknown14 = 0;
		unknown18 = 0;
		unknown1C = 0;
		unknown20 = 0;
		unknown24 = 0;
		unknown28 = 0;
	}

	// FUNCTION: ENGINE 0x106584F0
	Block8::Block8()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
		unknownC = 0;
		unknown10 = 0;
		unknown14 = 0;
		unknown18 = 0;
		unknown1C = 0;
	}

	// FUNCTION: ENGINE 0x10658510
	Block11Second::Block11Second()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
		unknownC = 0;
		unknown10 = 0;
		unknown14 = 0;
		unknown18 = 0;
		unknown1C = 0;
		unknown20 = 0;
		unknown24 = 0;
		unknown28 = 0;
	}

	// FUNCTION: ENGINE 0x10658540
	Block8Second::Block8Second()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
		unknownC = 0;
		unknown10 = 0;
		unknown14 = 0;
		unknown18 = 0;
		unknown1C = 0;
	}

	// FUNCTION: ENGINE 0x10658560
	Block11Third::Block11Third()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
		unknownC = 0;
		unknown10 = 0;
		unknown14 = 0;
		unknown18 = 0;
		unknown1C = 0;
		unknown20 = 0;
		unknown24 = 0;
		unknown28 = 0;
	}

	// FUNCTION: ENGINE 0x10658590
	Block11Fourth::Block11Fourth()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
		unknownC = 0;
		unknown10 = 0;
		unknown14 = 0;
		unknown18 = 0;
		unknown1C = 0;
		unknown20 = 0;
		unknown24 = 0;
		unknown28 = 0;
	}

	// FUNCTION: ENGINE 0x106585C0
	Block3::Block3()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
	}

	// FUNCTION: ENGINE 0x106585D0
	Block3Second::Block3Second()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
	}

	// FUNCTION: ENGINE 0x106585E0
	Block7::Block7()
	{
		unknown4 = 0;
		unknown8 = 0;
		unknownC = 0;
		unknown10 = 0;
		unknown14 = 0;
		unknown18 = 0;
	}

	// FUNCTION: ENGINE 0x10658600
	Block3Third::Block3Third()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
	}

	// FUNCTION: ENGINE 0x10658120
	TripleBlock::TripleBlock()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
	}

	// FUNCTION: ENGINE 0x10658130
	TripleBlockSecond::TripleBlockSecond()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
	}

	// FUNCTION: ENGINE 0x10658140
	void* IndexedBlock::Get(unsigned short index) const
	{
		return mItems[index];
	}

	// FUNCTION: ENGINE 0x10658150
	TripleBlockThird::TripleBlockThird()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
	}

	// FUNCTION: ENGINE 0x10658160
	TripleBlockFourth::TripleBlockFourth()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
	}

	// FUNCTION: ENGINE 0x10658170
	TripleBlockFifth::TripleBlockFifth()
	{
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
	}

	// FUNCTION: ENGINE 0x10656E90
	PlacementTracker* Context::GetPlacement()
	{
		return placement;
	}

	// FUNCTION: ENGINE 0x10657C90
	void Context::RefreshObjectList(ObjectList* objects)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x42f, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		void** it = objects->begin;
		for (; it != objects->end; it++)
		{
			PhysicsObject* object = static_cast<PhysicsObject*>(*it);
			if (!object->IsSkipped())
			{
				object->RefreshBounds(0);
			}
		}
	}

	// FUNCTION: ENGINE 0x10658A90
	void HeapRunFirst::Clear()
	{
		mEnd = mBegin;
	}

	// FUNCTION: ENGINE 0x10658AA0
	void AlignedRunFirst::Release()
	{
		if (mBegin != 0)
		{
			core::FreeAligned(mBegin);
		}
	}

	// FUNCTION: ENGINE 0x10658AB0
	void AlignedRunSecond::Release()
	{
		if (mBegin != 0)
		{
			core::FreeAligned(mBegin);
		}
	}

	// FUNCTION: ENGINE 0x10658AC0
	void AlignedRunThird::Release()
	{
		if (mBegin != 0)
		{
			core::FreeAligned(mBegin);
		}
	}

	// FUNCTION: ENGINE 0x10658AD0
	bool StatLogSecond::Add(const StatEntry& entry)
	{
		return StatLog::Add(entry);
	}

	// FUNCTION: ENGINE 0x10658B60
	void EmptyMembers::Twentieth()
	{
	}

	// FUNCTION: ENGINE 0x10658B70
	void HeapRunSecond::Clear()
	{
		mEnd = mBegin;
	}

	// FUNCTION: ENGINE 0x10658B80
	void HeapRunThird::Clear()
	{
		mEnd = mBegin;
	}

	// FUNCTION: ENGINE 0x10658B90
	void HeapRunFourth::Clear()
	{
		mEnd = mBegin;
	}

	// FUNCTION: ENGINE 0x10658BA0
	void HeapRunFifth::Clear()
	{
		mEnd = mBegin;
	}

	// FUNCTION: ENGINE 0x10658BB0
	void HeapRunSixth::Clear()
	{
		mEnd = mBegin;
	}

	// FUNCTION: ENGINE 0x10658BC0
	void HeapRunSeventh::Clear()
	{
		mEnd = mBegin;
	}

	// FUNCTION: ENGINE 0x10658BD0
	void HeapRunEighth::Clear()
	{
		mEnd = mBegin;
	}

	// FUNCTION: ENGINE 0x10658BE0
	bool ScratchBytesSecond::Reserve(unsigned int size, const char* value)
	{
		if (mBegin != 0)
		{
			return false;
		}
		if (size > 0)
		{
			unsigned char* begin = (unsigned char*)allocator.Alloc(size, 16);
			mBegin = begin;
			if (begin != 0)
			{
				mEnd = begin + size;
				FillByteRun((char*)begin, size, value);
				return true;
			}
		}
		mBegin = 0;
		mEnd = 0;
		return false;
	}

	// FUNCTION: ENGINE 0x10658C40
	void StatLogThird::Add(const StatEntry& entry)
	{
		mLog.Add(entry);
	}

	// FUNCTION: ENGINE 0x10658C50
	// NONMATCHING: register allocation, 57.7 %: the engine keeps the owner in edx and the walk in eax where ours picks
	// the other way round, every instruction otherwise identical (the same source on the twin slot at 0x10658480 has
	// the same problem)
#ifdef NONMATCHING
	void IndexedSlotThird::Get(RecordWalk* walk) const
	{
		ShortHead* owner = mOwner;
		walk->owner = owner;
		walk->value = owner->values[mIndex];
	}
#endif

	// FUNCTION: ENGINE 0x106594B0
	void HeapRunFirst::Release()
	{
		mEnd = mBegin;
		if (mBegin != 0)
		{
			delete[] mBegin;
		}
	}

	// FUNCTION: ENGINE 0x106594D0
	void HeapRunSecond::Release()
	{
		mEnd = mBegin;
		if (mBegin != 0)
		{
			delete[] mBegin;
		}
	}

	// FUNCTION: ENGINE 0x106594F0
	void HeapRunThird::Release()
	{
		mEnd = mBegin;
		if (mBegin != 0)
		{
			delete[] mBegin;
		}
	}

	// FUNCTION: ENGINE 0x10659510
	void HeapRunFourth::Release()
	{
		mEnd = mBegin;
		if (mBegin != 0)
		{
			delete[] mBegin;
		}
	}

	// FUNCTION: ENGINE 0x10659530
	void HeapRunFifth::Release()
	{
		mEnd = mBegin;
		if (mBegin != 0)
		{
			delete[] mBegin;
		}
	}

	// FUNCTION: ENGINE 0x10659550
	void HeapRunSixth::Release()
	{
		mEnd = mBegin;
		if (mBegin != 0)
		{
			delete[] mBegin;
		}
	}

	// FUNCTION: ENGINE 0x10659570
	void HeapRunSeventh::Release()
	{
		mEnd = mBegin;
		if (mBegin != 0)
		{
			delete[] mBegin;
		}
	}

	// FUNCTION: ENGINE 0x10659590
	void HeapRunNinth::Clear()
	{
		mEnd = mBegin;
	}

	// FUNCTION: ENGINE 0x106595A0
	bool ScratchBytesSecond::Reserve(unsigned int size)
	{
		char value = 0;
		return Reserve(size, &value);
	}

	// FUNCTION: ENGINE 0x106595C0
	void RunsFirst::Finalize()
	{
		unknown24 = unknown20;
		if (unknown20 != 0)
		{
			delete[] unknown20;
		}
		unknown14 = unknown10;
		if (unknown10 != 0)
		{
			delete[] unknown10;
		}
		unknown4 = unknown0;
		if (unknown0 != 0)
		{
			delete[] unknown0;
		}
	}

	// FUNCTION: ENGINE 0x10659600
	void HeapRunEighth::Release()
	{
		mEnd = mBegin;
		if (mBegin != 0)
		{
			delete[] mBegin;
		}
	}

	// FUNCTION: ENGINE 0x10659620
	void HeapRunNinth::Release()
	{
		mEnd = mBegin;
		if (mBegin != 0)
		{
			delete[] mBegin;
		}
	}

	// FUNCTION: ENGINE 0x10659640
	AlignedRuns* AlignedRuns::FinalizeDeleting(unsigned int flag)
	{
		if (unknown24 != 0)
		{
			core::FreeAligned(unknown24);
		}
		if (unknown18 != 0)
		{
			core::FreeAligned(unknown18);
		}
		if (unknownC != 0)
		{
			core::FreeAligned(unknownC);
		}
		if ((flag & 1) != 0)
		{
			operator delete(this);
		}
		return this;
	}

	// FUNCTION: ENGINE 0x10658EC0
	void AlignedRuns::Finalize()
	{
		if (unknown24 != 0)
		{
			core::FreeAligned(unknown24);
		}
		if (unknown18 != 0)
		{
			core::FreeAligned(unknown18);
		}
		unsigned char* third = (unsigned char*)unknownC;
		if (third != 0)
		{
			core::FreeAligned(third);
		}
	}

	// FUNCTION: ENGINE 0x10659CD0
	void RunsSecond::Finalize()
	{
		unknown28 = unknown24;
		if (unknown24 != 0)
		{
			delete[] unknown24;
		}
		unknown14 = unknown10;
		if (unknown10 != 0)
		{
			delete[] unknown10;
		}
		unknown4 = unknown0;
		if (unknown0 != 0)
		{
			delete[] unknown0;
		}
	}

	// FUNCTION: ENGINE 0x10659D10
	void RunsThird::Finalize()
	{
		unknown28 = unknown24;
		if (unknown24 != 0)
		{
			delete[] unknown24;
		}
		unknown14 = unknown10;
		if (unknown10 != 0)
		{
			delete[] unknown10;
		}
		unknown4 = unknown0;
		if (unknown0 != 0)
		{
			delete[] unknown0;
		}
	}

	// 0x10658AE0: the library's own copy of this walks in the hashtable unit, but the code the context calls sits
	// in this unit's range, so it is written here (the address has no functions.tsv entry of its own).
	void PointerHashTable::Reset()
	{
		memset(buckets, 0xff, bucketCount * 2);
		memset(next, 0xff, unknown4 * 2);
		memset(slotBuckets, -1, unknown14 * 2);
		freeCount = capacity;
		for (unsigned short i = 0; i < freeCount; i++)
		{
			freeSlots[i] = freeCount - i - 1;
			keys[i] = 0;
		}
	}

	// FUNCTION: ENGINE 0x10658F00
	void Context::ClearObjects()
	{
		while (unknownC4->Table().staticCount + unknownC4->Table().movableCount != 0)
		{
			SleepObject((PhysicsObject*)unknownC4->Table().objects[0]);
		}
		mWorld->Unknown0C();
		unknownC4->RemoveAll();
		if (!unknownD8)
		{
			placement->ResetTables();
			registry->Reset();
		}
	}

	// FUNCTION: ENGINE 0x10658CC0
	ObjectRegistry::ObjectRegistry()
	{
		next = 0;
		nextCount = 0;
		buckets = 0;
		bucketCount = 0;
		slotBuckets = 0;
		slotBucketCount = 0;
		table.next = 0;
		table.unknown4 = 0;
		table.buckets = 0;
		table.bucketCount = 0;
		table.slotBuckets = 0;
		table.unknown14 = 0;
		table.keys = 0;
		table.unknown1C = 0;
		table.freeSlots = 0;
		table.freeCount = 0;
		table.capacity = 0;
	}

	// FUNCTION: ENGINE 0x10658C70
	void ObjectRegistry::Reset()
	{
		memset(buckets, 0xff, bucketCount * 2);
		memset(next, 0xff, nextCount * 2);
		memset(slotBuckets, -1, slotBucketCount * 2);
		table.Reset();
	}

	// FUNCTION: ENGINE 0x10658610
	CollisionDetector::~CollisionDetector()
	{
		ScratchStack stack;
		Record32 record;
		record.name = "Waiting on gate";
		record.unknown8 = -1;
		record.kind = 7;
		record.unknown10 = true;
		record.unknown11 = true;
		record.start = (unsigned int)core::GetTicks();
		core::EventWait(event);
		record.end = (unsigned int)core::GetTicks();
		Record32* item = (Record32*)AcquireSlot32(recordPool);
		if (item != 0)
		{
			*item = record;
		}
		gLock.locked = false;
		stack.Unlock();
		midPhase->Complete();
		narrowPhase->Complete();
		core::EventDestroy(event);
	}

	// FUNCTION: ENGINE 0x10658F70
	CollisionDetector* CollisionDetector::Destroy(unsigned int flag)
	{
		this->~CollisionDetector();
		if ((flag & 1) != 0)
		{
			operator delete(this);
		}
		return this;
	}

	// FUNCTION: ENGINE 0x106593A0
	bool Context::CastRay(const RayQuery& query, RayHitArray* hits)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x622, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		hits->end = hits->begin;
		return mWorld->QueryRay(&query, hits, unknownC4, query.unknown24 & 3);
	}

	// FUNCTION: ENGINE 0x10659420
	void Context::QueryObjectShapeHits(void* object, RayHitArray* hits, void* a)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x681, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		hits->end = hits->begin;
		mWorld->QueryBodyShapeHits(object, hits, unknownC4, a);
	}

	// FUNCTION: ENGINE 0x10659690
	void CollisionDetector::End()
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x262, mCollisionDetectorInternal, "mCollisionDetectorInternal",
			"Collision detection not running");
		mCollisionDetectorInternal->~CollisionDetector();
		mCollisionDetectorInternal = 0;
		unknown28 = 0;
	}

	// FUNCTION: ENGINE 0x10659EE0
	void CollisionDetector::Begin(Context* context, void* data)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x25a, !mCollisionDetectorInternal, "!mCollisionDetectorInternal",
			"Collision detection already running");
		unknown28 = data;
		mCollisionDetectorInternal = this;
		Run(context, data);
	}

	// FUNCTION: ENGINE 0x10659F40
	void Context::BeginCollision(void* data)
	{
		detector->Begin(this, data);
		detector->GetEventChecked();
	}

	// FUNCTION: ENGINE 0x10657F20
	// NONMATCHING: register allocation, 86.6 %: the engine keeps the detector in edx and the output pointer in eax,
	// ours picks the other way round (and stores the lower half of the copy's two words one instruction later); the
	// instructions and their order are otherwise identical. A named local for either, a named local for the output,
	// a struct assignment instead of the memcpy and taking the output by pointer instead of by address all compile
	// to the same pair.
#ifdef NONMATCHING
	void Context::GetIslandTable(DetectorTable* out)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x86b, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		BroadPhaseDetector* detector = unknownC4;
		out->head = detector->unknown150;
		out->records = detector->unknown124;
		out->count = detector->unknown128;
	}
#endif

	// FUNCTION: ENGINE 0x10657FA0
	// NONMATCHING: register allocation, 88.2 %: the same swap of the detector and the output pointer as 0x10657F20,
	// the code being the same shape with the other table's offsets
#ifdef NONMATCHING
	void Context::GetAwakeTable(DetectorTable* out)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x871, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		BroadPhaseDetector* detector = unknownC4;
		out->head = detector->unknown34;
		out->records = detector->unknown6C;
		out->count = detector->unknown70;
	}
#endif

	// FUNCTION: ENGINE 0x10657D70
	// NONMATCHING: register allocation and scheduling, 42.4 %: the offsets and the arithmetic are the engine's, but
	// it interleaves the four detector loads with the words that follow them and takes the maximum of each pair of
	// counts with a branch (`cmp; jae; mov`) where ours compiles it to `cmp; cmovb` (and the division's magic lets
	// the values sit in different registers). Reordering the statements to the engine's instruction order moves the
	// ratio to 42.4 % from 38.8 % without closing it.
#ifdef NONMATCHING
	void Context::GetStatistics(int* out)
	{
		out[0] = (int)(staticObjects.end - staticObjects.begin);
		out[1] = (int)(movableObjects.end - movableObjects.begin);
		out[2] = unknownC4->Table().unknown4;
		out[3] = unknownC8;
		out[4] = unknownC4->Table().unknown6;
		out[5] = unknownCC;
		out[6] = unknownC4->Table().unknown8;
		out[7] = unknownD0;
		out[8] = unknownC4->Table().unknownA;
		out[9] = unknownDC;
		unsigned int slots = (unsigned int)((collisionBatch.slotsEnd - collisionBatch.slots) / 0xc);
		unsigned int records = (unsigned int)((collisionBatch.recordsEnd - collisionBatch.records) / 0x30);
		if (slots < records)
		{
			slots = records;
		}
		out[10] = slots;
		out[0xb] = unknownEC;
		out[0xc] = (int)((collisionBatch.recordsSecondEnd - collisionBatch.recordsSecond) / 0x30);
		out[0xd] = unknownF0;
		slots = (unsigned int)((constraintBatch.slotsEnd - constraintBatch.slots) / 0xc);
		records = (unsigned int)((constraintBatch.recordsEnd - constraintBatch.records) / 0xa8);
		if (slots < records)
		{
			slots = records;
		}
		out[0xe] = slots;
		out[0xf] = unknownF4;
		out[0x10] = (int)((constraintBatch.recordsSecondEnd - constraintBatch.recordsSecond) / 0x34);
		out[0x11] = unknownF8;
		slots = (unsigned int)((queryBatch.slotsEnd - queryBatch.slots) / 0xc);
		records = (unsigned int)((queryBatch.recordsEnd - queryBatch.records) / 0x2c);
		if (slots < records)
		{
			slots = records;
		}
		out[0x12] = slots;
		out[0x13] = unknownFC;
		out[0x14] = (int)(queryBatch.unknown24 - queryBatch.unknown20);
		out[0x15] = unknown100;
	}
#endif
}
