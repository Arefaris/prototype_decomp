// The unit between the file/container code of the engine core and ravenphysics/collision/src/collisionobject.cpp
// (0x10653150 - 0x10654490). It carries no assert of its own, so nothing in the image names its source file: it is
// reconstructed here as the collision/src unit the collision object code is linked next to, and the file name is a
// guess. What it holds is the table of collision object handles, the registry of known intersection properties and
// the copies of CollisionShape's flag accessors and of the volume destructors that its own code needs.
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/core/refptr.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x10653610
	bool IntersectionProperties::operator==(const IntersectionProperties& other) const
	{
		return unknown0 == other.unknown0 && unknown4 == other.unknown4;
	}

	// FUNCTION: ENGINE 0x10653630
	IntersectionProperties* IntersectionPropertiesEntry::GetProperties()
	{
		return &properties;
	}

	// FUNCTION: ENGINE 0x106536D0
	IntersectionPropertiesEntry* FindIntersectionProperty(const IntersectionProperties& properties)
	{
		for (unsigned int i = 0; i < gIntersectionPropertyCount; i++)
		{
			const IntersectionProperties& current = gIntersectionProperties[i].properties;
			if (current.unknown0 == properties.unknown0 && current.unknown4 == properties.unknown4)
			{
				return &gIntersectionProperties[i];
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10653720
	unsigned int GetIntersectionPropertyCount()
	{
		return gIntersectionPropertyCount;
	}

	// FUNCTION: ENGINE 0x10653730
	IntersectionPropertiesEntry* GetIntersectionProperty(unsigned short index)
	{
		return &gIntersectionProperties[index];
	}

	// FUNCTION: ENGINE 0x10653860
	IntersectionProperties::IntersectionProperties()
	{
		if (GetIntersectionPropertyCount() > 0)
		{
			*this = GetIntersectionProperty(0)->properties;
		}
		else
		{
			unknown0 = -1;
			unknown4 = -1;
		}
	}

	// FUNCTION: ENGINE 0x106538D0
	bool ClearIntersectionPropertiesLoader()
	{
		core::RefAssign(gIntersectionPropertiesLoader, (IntersectionPropertiesLoader*)0);
		return true;
	}

	// FUNCTION: ENGINE 0x10654380
	void CollisionShape::SetFlag3(bool value)
	{
		flag3 = value;
	}

	// FUNCTION: ENGINE 0x106543A0
	bool CollisionShape::IsFlag3()
	{
		return flag3;
	}

	// FUNCTION: ENGINE 0x10654410
	void CollisionShape::SetFlag4(bool value)
	{
		flag4 = value;
	}

	// FUNCTION: ENGINE 0x10653250
	// NONMATCHING: the bumped serial, 70.2 %: the engine reads it out of the slot once and reuses the register
	// for both stores, ours loads it a second time for the handle (`movzx esi, word ptr [eax]` then
	// `mov dx, word ptr [eax]`); naming the value only moves the extra load
#ifdef NONMATCHING
	void CollisionObjectTable::Add(void* object, CollisionHandle* handle)
	{
		if (free.IsEmpty())
		{
			handle->value = 0xffffffff;
			return;
		}
		unsigned short index = free.Pop();
		unsigned short& serial = serials[index];
		serial++;
		CollisionHandleEntry* entry = &entries[index];
		entry->object = object;
		entry->serial = serial;
		handle->index = index;
		handle->serial = serial;
	}
#endif

	// FUNCTION: ENGINE 0x106532B0
	// NONMATCHING: the serial test, 35.6 %: the engine materialises the second half of the `&&` as a bool
	// (`sete dl` / `test dl, dl`), ours branches on the comparison directly; every other instruction, and the
	// `&&`'s short-circuit, is the same
#ifdef NONMATCHING
	void CollisionObjectTable::Remove(CollisionHandle* handle)
	{
		if (handle->index < slotCount && entries[handle->index].serial == handle->serial)
		{
			free.Push(handle->index);
			CollisionHandleEntry* entry = &entries[handle->index];
			entry->object = 0;
			entry->serial = 0xffffffff;
			handle->value = 0xffffffff;
		}
	}
#endif
}
