// The unit linked just before context.cpp (0x10656020 - 0x106564C0); see smallobjects.h.
#include "code/ravenphysics/smallobjects.h"
#include "code/core/heap.h"
#include "code/core/interlocked.h"
#include "code/core/time.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/common/stackallocator.h"
#include "code/ravenphysics/context.h"
#include "code/ravenphysics/physicsobject.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x10656020
	unsigned char* Layout20::GetTail()
	{
		return tail;
	}

	// FUNCTION: ENGINE 0x10656030
	// EQUIVALENT: the engine loads the output pointer into eax after the call, ours into edx (everything else is
	// the same), 95.8 %
	void CreateObjectHandle(unsigned int* id, CollisionVolume* volume, int flag, float size)
	{
		PhysicsObject* object = CreatePhysicsObject(volume, flag, size);
		object->AddRef();
		*id = object->id;
	}

	// FUNCTION: ENGINE 0x10656090
	void* CollisionObjectTable::GetObject(const CollisionHandle* handle) const
	{
		return entries.begin[handle->index].object;
	}

	// FUNCTION: ENGINE 0x106560A0
	PhysicsObject* ObjectHandle::GetObject() const
	{
		return gObjectTable->entries[index].object;
	}

	// FUNCTION: ENGINE 0x106560D0
	long AtomicCounter::Increment()
	{
		return _InterlockedIncrement(&value);
	}

	// FUNCTION: ENGINE 0x106560E0
	long AtomicCounter::Decrement()
	{
		return _InterlockedDecrement(&value);
	}

	// FUNCTION: ENGINE 0x10656100
	void IgnoringHandler::Handle(int unused)
	{
	}

	// FUNCTION: ENGINE 0x10656110
	Flag18Holder::Flag18Holder()
	{
		flag = false;
	}

	// FUNCTION: ENGINE 0x10656120
	void BlockReleaser::FreeBlock(void* block)
	{
		core::FreeAligned(block);
	}

	// FUNCTION: ENGINE 0x10656130
	unsigned char* BroadPhaseDetector::GetUnknown10C()
	{
		return unknown10C;
	}

	// FUNCTION: ENGINE 0x10656140
	DetectorHead* BroadPhaseDetector::GetUnknown150()
	{
		return &unknown150;
	}

	// FUNCTION: ENGINE 0x10656150
	DetectorHead* BroadPhaseDetector::GetUnknown34()
	{
		return &unknown34;
	}

	// FUNCTION: ENGINE 0x10656160
	unsigned char* BroadPhaseDetector::GetUnknown54()
	{
		return unknown54;
	}

	// FUNCTION: ENGINE 0x10656170
	unsigned short BroadPhaseDetector::ObjectTable::GetMovableCount() const
	{
		return movableCount;
	}

	// FUNCTION: ENGINE 0x10656180
	unsigned short BroadPhaseDetector::ObjectTable::GetStaticCount() const
	{
		return staticCount;
	}

	// FUNCTION: ENGINE 0x10656190
	void*** BroadPhaseDetector::ObjectTable::GetObjects()
	{
		return &objects;
	}

	// FUNCTION: ENGINE 0x106561A0
	unsigned short BroadPhaseDetector::ObjectTable::GetUnknown8() const
	{
		return unknown8;
	}

	// FUNCTION: ENGINE 0x106561B0
	unsigned int BroadPhaseDetector::ObjectTable::GetUnknown6() const
	{
		return unknown6;
	}

	// FUNCTION: ENGINE 0x106561C0
	unsigned int BroadPhaseDetector::ObjectTable::GetUnknown4() const
	{
		return unknown4;
	}

	// FUNCTION: ENGINE 0x106561D0
	unsigned int BroadPhaseDetector::ObjectTable::GetUnknownA() const
	{
		return unknownA;
	}

	// FUNCTION: ENGINE 0x106561E0
	unsigned short BroadPhaseObject::GetDetectorIndex() const
	{
		return detectorIndex;
	}

	// FUNCTION: ENGINE 0x106561F0
	ProfileTimer::ProfileTimer()
	{
		start = 0;
		stop = 0;
		count = 0;
		kind = 0;
		slot = 0;
		tag = 0;
		ticks = false;
	}

	// FUNCTION: ENGINE 0x10656210
	void ProfileTimer::Start(int newTag, int newCount, unsigned short newSlot, char newKind, bool newTicks)
	{
		tag = newTag;
		count = newCount;
		slot = newSlot;
		kind = newKind;
		ticks = newTicks;
		if (newTicks)
		{
			start = (unsigned int)core::GetTicks();
		}
		else
		{
			start = (unsigned int)core::GetElapsedMicroseconds();
		}
	}

	// FUNCTION: ENGINE 0x10656260
	void ProfileTimer::Stop()
	{
		if (ticks)
		{
			stop = (unsigned int)core::GetTicks();
		}
		else
		{
			stop = (unsigned int)core::GetElapsedMicroseconds();
		}
	}

	// FUNCTION: ENGINE 0x10656280
	void FourWords::Set(unsigned int newFirst, unsigned int newSecond, unsigned int newThird)
	{
		first = newFirst;
		second = newSecond;
		third = newThird;
		unknown8 = 0;
	}

	// FUNCTION: ENGINE 0x106562A0
	void* AllocateAligned128(unsigned int size)
	{
		return core::HeapAllocAligned(core::GetCurrentHeap(), size, 0x80);
	}

	// FUNCTION: ENGINE 0x106562C0
	void FreeAlignedBlock(void* block)
	{
		core::FreeAligned(block);
	}

	// FUNCTION: ENGINE 0x106562D0
	int IntTable::Get(int index) const
	{
		return items[index];
	}

	// FUNCTION: ENGINE 0x106562E0
	SlotPool* Context::GetRecordPool()
	{
		return &recordPool;
	}

	// FUNCTION: ENGINE 0x106562F0
	int StateHolder::GetMember() const
	{
		return member0C;
	}

	// FUNCTION: ENGINE 0x10656300
	void StateHolder::SetUnknown4C(int value)
	{
		unknown4C = value;
	}

	// FUNCTION: ENGINE 0x10656310
	int StateHolder::GetFlag0() const
	{
		return flags & 1;
	}

	// FUNCTION: ENGINE 0x10656320
	bool StateHolder::IsReady() const
	{
		return link != 0 && link->member != 0 && !(flags & 1);
	}

	// FUNCTION: ENGINE 0x10656340
	ScratchAllocator::ScratchAllocator(int newOwner, void* buffer, unsigned int size)
	{
		unknown18 = false;
		owner = newOwner;
		Init(buffer, size, false);
	}

	// FUNCTION: ENGINE 0x10656370
	void RegistryRef::Add(unsigned int key)
	{
		registry->Unknown10686790(key, slot);
	}

	// FUNCTION: ENGINE 0x10656390
	bool RegistryRef::operator==(const RegistryRef& other) const
	{
		return slot == other.slot;
	}

	// FUNCTION: ENGINE 0x106563B0
	void ObjectRegistry::RemoveRef(const RegistryRef* reference)
	{
		Unknown106867F0(reference->slot);
	}

	// FUNCTION: ENGINE 0x106563D0
	// NONMATCHING: the engine keeps the store of the third 0x800 behind the float stores where ours hoists it up
	// to the other two, 66.3 %; no order of the assignments moves it
#ifdef NONMATCHING
	ContextLimits::ContextLimits()
	{
		unknown0 = 0x800;
		unknown8 = 0x800;
		unknown4 = 0x200;
		unknown14 = 0x400;
		unknown18 = 0.0f;
		gravity = -9.81f;
		unknown20 = 0.0f;
		unknownC = 0x800;
		unknown10 = false;
		unknown24 = 0x20;
		unknown28 = 0x400;
		unknown2C = 0x20;
		unknown30 = 0x400;
		unknown34 = 0x1F4;
		unknown38 = 0x7D0;
	}
#endif

	// FUNCTION: ENGINE 0x10656430
	ContextLimits::ContextLimits(const ContextLimits& other)
		: unknown0(other.unknown0), unknown4(other.unknown4), unknown8(other.unknown8), unknownC(other.unknownC),
		  unknown10(other.unknown10), unknown14(other.unknown14), unknown18(other.unknown18),
		  gravity(other.gravity), unknown20(other.unknown20), unknown24(other.unknown24),
		  unknown28(other.unknown28), unknown2C(other.unknown2C), unknown30(other.unknown30),
		  unknown34(other.unknown34), unknown38(other.unknown38), unknown3C(other.unknown3C)
	{
	}

	// FUNCTION: ENGINE 0x106564A0
	void* PlacementTracker::DestroyAndFree(unsigned int flags)
	{
		PlacementTracker::~PlacementTracker();
		if (flags & 1)
		{
			operator delete(this);
		}
		return this;
	}

	// FUNCTION: ENGINE 0x106564C0
	void Context::Unknown106564C0(PhysicsObject* object)
	{
		if (object->IsAsleep())
		{
			mWorld->Unknown18(object);
		}
	}

	// FUNCTION: ENGINE 0x10656570
	ScratchAllocator::~ScratchAllocator()
	{
	}
}
