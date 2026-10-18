// The unit between the file/container code of the engine core and ravenphysics/collision/src/collisionobject.cpp
// (0x10653150 - 0x10654490). It carries no assert of its own, so nothing in the image names its source file: it is
// reconstructed here as the collision/src unit the collision object code is linked next to, and the file name is a
// guess. What it holds is the table of collision object handles, the registry of known intersection properties and
// the copies of CollisionShape's flag accessors and of the volume destructors that its own code needs.
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/core/heap.h"
#include <new>
#include "code/core/refptr.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x10653150
	bool CollisionSlotStack::IsEmpty() const
	{
		return size == 0;
	}

	// FUNCTION: ENGINE 0x10653160
	void CollisionSlotStack::Clear()
	{
		size = 0;
	}

	// FUNCTION: ENGINE 0x10653170
	inline void CollisionSlotStack::Push(const unsigned short& index)
	{
		size++;
		unsigned short* slot = begin + size - 1;
		if (slot != 0)
		{
			*slot = index;
		}
	}

	// FUNCTION: ENGINE 0x10653190
	unsigned short CollisionSlotStack::Pop()
	{
		size--;
		return begin[size];
	}

	// FUNCTION: ENGINE 0x106531A0
	inline CollisionHandleEntries::CollisionHandleEntries()
	{
		begin = 0;
		count = 0;
	}

	// FUNCTION: ENGINE 0x106531C0
	unsigned short* CollisionSlotStack::Top()
	{
		return begin + size - 1;
	}

	// FUNCTION: ENGINE 0x106531D0
	inline CollisionHandleSerials::CollisionHandleSerials()
	{
		begin = 0;
		count = 0;
	}

	// FUNCTION: ENGINE 0x106531F0
	CollisionHandleEntries::CollisionHandleEntries(CollisionHandleEntry* newBegin, unsigned int newCount)
	{
		begin = newBegin;
		count = newCount;
	}

	// FUNCTION: ENGINE 0x10653210
	void CollisionHandleSerials::Set(unsigned short* newBegin, unsigned int newCount)
	{
		begin = newBegin;
		count = newCount;
	}

	// FUNCTION: ENGINE 0x10653240
	void CollisionHandleSerials::FreeBlock(void* block)
	{
		core::FreeAligned(block);
	}

	// FUNCTION: ENGINE 0x10653360
	inline CollisionSlotStack::CollisionSlotStack()
	{
		begin = 0;
		size = 0;
		capacity = 0;
	}

	// FUNCTION: ENGINE 0x10653370
	inline void CollisionSlotStack::Create(unsigned int count, int unused)
	{
		begin = (unsigned short*)core::HeapAllocAligned(core::GetCurrentHeap(), count * 2, 16);
		size = 0;
		capacity = count;
	}

	// FUNCTION: ENGINE 0x106533A0
	inline void CollisionHandleEntries::Create(unsigned int newCount, int unused)
	{
		begin = (CollisionHandleEntry*)core::HeapAllocAligned(core::GetCurrentHeap(), newCount * 8, 16);
		count = newCount;
	}

	// FUNCTION: ENGINE 0x106533D0
	inline void CollisionHandleSerials::Create(unsigned int newCount, int unused)
	{
		begin = (unsigned short*)core::HeapAllocAligned(core::GetCurrentHeap(), newCount * 2, 16);
		count = newCount;
	}

	// FUNCTION: ENGINE 0x10653400
	inline void CollisionSlotStack::Free(int unused)
	{
		if (begin != 0)
		{
			core::FreeAligned(begin);
			begin = 0;
			size = 0;
			capacity = 0;
		}
	}

	// FUNCTION: ENGINE 0x10653430
	inline void CollisionHandleEntries::Free(int unused)
	{
		if (begin != 0)
		{
			core::FreeAligned(begin);
			begin = 0;
			count = 0;
		}
	}

	// FUNCTION: ENGINE 0x10653460
	inline void CollisionHandleSerials::Free(int unused)
	{
		if (begin != 0)
		{
			core::FreeAligned(begin);
			begin = 0;
			count = 0;
		}
	}

	// FUNCTION: ENGINE 0x10653490
	inline CollisionObjectTable::CollisionObjectTable()
	{
	}

	// FUNCTION: ENGINE 0x106534B0
	void DestroyCollisionObjectTable()
	{
		gCollisionObjectTable->free.Free(0);
		gCollisionObjectTable->entries.Free(0);
		gCollisionObjectTable->serials.Free(0);
		delete gCollisionObjectTable;
		gCollisionObjectTable = 0;
	}

	// FUNCTION: ENGINE 0x10653530
	void CreateCollisionObjectTable(unsigned int count)
	{
		gCollisionObjectTable = new CollisionObjectTable();
		if (count > 0)
		{
			gCollisionObjectTable->free.Create(count, 0);
			gCollisionObjectTable->entries.Create(count, 0);
			gCollisionObjectTable->serials.Create(count, 0);
		}
		gCollisionObjectTable->slotCount = count;
		for (unsigned int i = 0; i < count; i++)
		{
			gCollisionObjectTable->serials.begin[i] = 0;
		}
		gCollisionObjectTable->FillFreeList();
	}

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

	// FUNCTION: ENGINE 0x10653830
	inline IntersectionPropertiesEntry::IntersectionPropertiesEntry(const core::Name<core::CaseSensitiveKey>& entryName,
		const IntersectionProperties& entryProperties) : name(entryName), properties(entryProperties)
	{
	}

	// FUNCTION: ENGINE 0x106538F0
	IntersectionPropertiesEntry::~IntersectionPropertiesEntry()
	{
	}

	// FUNCTION: ENGINE 0x10653900
	// EQUIVALENT: the engine loads the registry's address behind the test of the count (nothing is loaded for an
	// empty registry), ours before it, 94.8 %
	IntersectionPropertiesEntry* FindIntersectionPropertyByName(const core::Name<core::CaseSensitiveKey>& name)
	{
		unsigned int count = gIntersectionPropertyCount;
		IntersectionPropertiesEntry* entries = gIntersectionProperties;
		for (unsigned int i = 0; i < count; i++)
		{
			if (entries[i].name == name)
			{
				return &gIntersectionProperties[i];
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10653950
	// EQUIVALENT: as FindIntersectionPropertyByName, 94.4 %
	unsigned short FindIntersectionPropertyIndex(const core::Name<core::CaseSensitiveKey>& name)
	{
		unsigned int count = gIntersectionPropertyCount;
		IntersectionPropertiesEntry* entries = gIntersectionProperties;
		for (unsigned int i = 0; i < count; i++)
		{
			if (entries[i].name == name)
			{
				return (unsigned short)i;
			}
		}
		return 0xFFFF;
	}

	// FUNCTION: ENGINE 0x106539A0
	bool FindColliderTypeIndex(const core::Name<core::CaseSensitiveKey>& name, unsigned int* index)
	{
		if (gColliderTypeNames != 0)
		{
			core::Name<core::CaseSensitiveKey>* names = gColliderTypeNames->names;
			unsigned int i = 0;
			unsigned int count = gColliderTypeNames->namesEnd - names;
			for (; i < count; i++)
			{
				if (names[i] == name)
				{
					*index = i;
					return true;
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106539F0
	bool GetColliderTypeName(unsigned int index, core::Name<core::CaseSensitiveKey>* name)
	{
		if (gColliderTypeNames != 0)
		{
			core::Name<core::CaseSensitiveKey>* names = gColliderTypeNames->names;
			core::Name<core::CaseSensitiveKey>* end = gColliderTypeNames->namesEnd;
			if (index < (unsigned int)(end - names))
			{
				*name = names[index];
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10653AA0
	IntersectionPropertiesEntry::IntersectionPropertiesEntry()
	{
	}

	// FUNCTION: ENGINE 0x10653B00
	void ClearIntersectionPropertyRegistry()
	{
		delete[] gIntersectionProperties;
		gIntersectionProperties = 0;
		gIntersectionPropertyCount = 0;
		gIntersectionPropertyCapacity = 0;
		core::RefAssign(gColliderTypeNames, (ColliderTypeNames*)0);
	}

	// FUNCTION: ENGINE 0x10653B50
	// EQUIVALENT: the same reads, writes and calls in the same order; the engine keeps the name in edi and saves ebx
	// only in the appending branch where ours keeps it in ebx for the whole function and reloads the registry
	// pointer for the second half of the copy, 26.2 %
	unsigned int RegisterIntersectionProperties(const core::Name<core::CaseSensitiveKey>& name,
		const IntersectionProperties& properties)
	{
		unsigned int index = FindIntersectionPropertyIndex(name);
		if (index != 0xFFFF)
		{
			IntersectionPropertiesEntry* entry = &gIntersectionProperties[index];
			entry->properties = properties;
			return index;
		}
		unsigned int count = gIntersectionPropertyCount;
		new (&gIntersectionProperties[count]) IntersectionPropertiesEntry(name, properties);
		count++;
		gIntersectionPropertyCount = count;
		return count - 1;
	}

	// FUNCTION: ENGINE 0x10653F50
	void RegisterDefaultIntersectionProperties()
	{
		gIntersectionPropertyCount = 0;
		IntersectionProperties properties(-1, -1);
		RegisterIntersectionProperties(core::Name<core::CaseSensitiveKey>("Default", 1), properties);
		core::RefAssign(gColliderTypeNames, (ColliderTypeNames*)0);
	}

	// FUNCTION: ENGINE 0x10653FA0
	void CreateIntersectionPropertyRegistry(unsigned int count)
	{
		gIntersectionPropertyCapacity = count;
		gIntersectionProperties = new IntersectionPropertiesEntry[count];
		core::RefAssign(gColliderTypeNames, (ColliderTypeNames*)0);
		RegisterDefaultIntersectionProperties();
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
		core::RefAssign(gColliderTypeNames, (ColliderTypeNames*)0);
		return true;
	}

	// FUNCTION: ENGINE 0x10654150
	void CollisionVolume3::SetMaterial(unsigned char newMaterial)
	{
		if (type == 4)
		{
			((CollisionVolume4*)this)->materials.SetMaterial(newMaterial);
		}
		material = newMaterial;
	}

	// FUNCTION: ENGINE 0x10654180
	bool CollisionVolume6::HasSlotGeometry() const
	{
		return unknown110->unknown4 != 0;
	}

	// FUNCTION: ENGINE 0x106541A0
	math::Vector* CollisionShape::GetUnknown34()
	{
		return &unknown34;
	}

	// FUNCTION: ENGINE 0x106541B0
	float CollisionShape::GetInverseScale()
	{
		return unknown8C;
	}

	// FUNCTION: ENGINE 0x106541C0
	void CollisionShape::SetVectors(const void* values)
	{
		unknown58 = *(const math::SymmetricMatrix*)values;
		math::SymmetricMatrix inverse;
		inverse.Invert(unknown58);
		unknown58 = inverse;
		Unknown10669160();
	}

	// FUNCTION: ENGINE 0x10654240
	math::SymmetricMatrix* CollisionShape::GetUnknown58()
	{
		return &unknown58;
	}

	// FUNCTION: ENGINE 0x10654250
	math::Vector* CollisionShape::GetUnknown90()
	{
		return &unknown90;
	}

	// FUNCTION: ENGINE 0x10654260
	// NONMATCHING: the engine stores the cross product (y, z, x) straight into the result and adds the linear velocity
	// reading only x back from memory, with the angular velocity and the point loaded first; ours keeps the cross
	// product in a local and orders the loads differently, 39.7 %
#ifdef NONMATCHING
	void CollisionShape::GetRelativeVelocity(math::Vector point, math::Vector* velocity)
	{
		math::Vector turn;
		turn.Cross(unknown1C, point);
		velocity->Add(unknown10, turn);
	}
#endif

	// FUNCTION: ENGINE 0x106542F0
	// NONMATCHING: as GetRelativeVelocity, with the previous vectors
#ifdef NONMATCHING
	void CollisionShape::GetPreviousRelativeVelocity(math::Vector point, math::Vector* velocity)
	{
		math::Vector turn;
		turn.Cross(unknown34, point);
		velocity->Add(unknown28, turn);
	}
#endif

	// FUNCTION: ENGINE 0x106543B0
	void CollisionShape::MoveToCenter(math::Vector from, int flag)
	{
		MoveTo(from, center, flag);
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

	// FUNCTION: ENGINE 0x10654430
	void* CollisionVolume6::DestroyAndFree(unsigned int flags)
	{
		CollisionVolume6::~CollisionVolume6();
		if (flags & 1)
		{
			operator delete(this);
		}
		return this;
	}

	// FUNCTION: ENGINE 0x10654450
	void* CollisionVolume3::DestroyAndFree(unsigned int flags)
	{
		CollisionVolume3::~CollisionVolume3();
		if (flags & 1)
		{
			operator delete(this);
		}
		return this;
	}

	// FUNCTION: ENGINE 0x10654470
	void* CollisionShape::DestroyAndFree(unsigned int flags)
	{
		CollisionShape::~CollisionShape();
		if (flags & 1)
		{
			operator delete(this);
		}
		return this;
	}

	// FUNCTION: ENGINE 0x10654490
	CollisionVolume4::~CollisionVolume4()
	{
	}

	// FUNCTION: ENGINE 0x10653250
	// NONMATCHING: the engine keeps the stack frame register behind the free-list update and widens the bumped
	// serial only for the slot's word (`movzx esi, ax`), ours pushes esi earlier and widens it in eax first, 81 %
#ifdef NONMATCHING
	void CollisionObjectTable::Add(void* object, CollisionHandle* handle)
	{
		if (free.IsEmpty())
		{
			handle->value = 0xffffffff;
			return;
		}
		unsigned short index = free.begin[free.size - 1];
		free.size--;
		unsigned short* serialSlot = &serials.begin[index];
		(*serialSlot)++;
		unsigned int serial = *serialSlot;
		CollisionHandleEntry* entry = &entries.begin[index];
		entry->object = object;
		entry->serial = serial;
		handle->index = index;
		handle->serial = serial;
	}
#endif

	// FUNCTION: ENGINE 0x106532B0
	void CollisionObjectTable::Remove(CollisionHandle* handle)
	{
		if (IsLive(handle))
		{
			free.Push(handle->index);
			CollisionHandleEntry* entry = &entries.begin[handle->index];
			entry->object = 0;
			entry->serial = 0xffffffff;
			handle->value = 0xffffffff;
		}
	}
}
