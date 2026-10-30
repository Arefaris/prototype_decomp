// The entities of the om library and their registry (0x105B49E0 - 0x105B5D6E; names guessed).
#include "code/om/entity.h"

#include "code/core/criticalsection.h"

namespace om
{
	// Holds a critical section for as long as it lives (the engine's constructor and destructor are 0x105B4CC0 and
	// 0x105B4CE0, expanded here)
	class CriticalSectionLock
	{
	public:
		explicit CriticalSectionLock(void* newSection) :
			section(newSection)
		{
			core::CriticalSectionEnter(section);
		}
		~CriticalSectionLock()
		{
			core::CriticalSectionLeave(section);
		}

		void* section;
	};

	// FUNCTION: ENGINE 0x105B49E0
	bool Entity::Slot3(void* argument)
	{
		return GetEntityType()->GetMetaType()->ReadText((const TextValue*)argument, this);
	}

	// FUNCTION: ENGINE 0x105B4A10
	void Entity::Slot4(void* argument)
	{
		GetEntityType()->GetMetaType()->WriteText((TextValue*)argument, this);
	}

	// FUNCTION: ENGINE 0x105B4A40
	bool Entity::Slot5(void* argument)
	{
		return GetEntityType()->GetMetaType()->ReadBinary((BinaryStream*)argument, this);
	}

	// FUNCTION: ENGINE 0x105B4A70
	bool Entity::Slot6(void* argument)
	{
		return GetEntityType()->GetMetaType()->ReadBinary((BinaryStream*)argument, this);
	}

	// FUNCTION: ENGINE 0x105B4AA0
	bool Entity::Slot7(void* argument)
	{
		return GetEntityType()->GetMetaType()->WriteBinary((BinaryStream*)argument, this);
	}

	// FUNCTION: ENGINE 0x105B5210
	Entity::Entity(const ClassName& newName) :
		name(newName)
	{
	}

	// FUNCTION: ENGINE 0x105B5240
	bool Entity::Slot1()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x105B5250
	bool Entity::Slot8(void* argument)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x105B56A0
	// EQUIVALENT: scheduling (49.1 %): the engine reads the lock pointer before it saves esi and edi and before it stores
	// the vftable; the same calls, reads and writes
	Entity::~Entity()
	{
		CriticalSectionLock lock(gEntityLock);
		gEntitiesByName.Erase(&nodeByName);
	}

	// FUNCTION: ENGINE 0x105B5B60
	// EQUIVALENT: scheduling (47.6 %): the engine reads the lock pointer before it saves esi
	void RegisterEntity(Entity* entity)
	{
		CriticalSectionLock lock(gEntityLock);
		gEntitiesByName.InsertEntity(entity);
	}

	// FUNCTION: ENGINE 0x105B5D00
	// EQUIVALENT: scheduling (91.2 %): the two halves of the name are copied through other registers, with the load of the
	// tree's address between the stores
	bool Entity::Rename(const ClassName& newName)
	{
		CriticalSectionLock lock(gEntityLock);
		if (newName.key == name.key)
		{
			return true;
		}
		gEntitiesByName.Erase(&nodeByName);
		name = newName;
		return gEntitiesByName.InsertEntity(this);
	}

	// FUNCTION: ENGINE 0x105B5590
	EntityTypeBase::EntityTypeBase(const char* newName, unsigned int newSize, unsigned int newAlignment,
		const type_info* newType, int newFlag) :
		name(newName),
		size(newSize),
		alignment(newAlignment),
		flag(newFlag),
		type(newType),
		registered(true)
	{
		gEntityTypesByName.InsertEntityTypeByName(this);
		gEntityTypesByType.InsertEntityTypeByType(this);
	}

	// FUNCTION: ENGINE 0x105B55E0
	// EQUIVALENT: instruction selection (92.3 %): the second node's address is computed with add on esi where the engine
	// uses lea into eax; the same calls
	EntityTypeBase::~EntityTypeBase()
	{
		gEntityTypesByName.Erase(&nodeByName);
		gEntityTypesByType.Erase(&nodeByType);
	}

	// FUNCTION: ENGINE 0x105B5690
	EntityTypeBase* FindEntityType(const type_info& type)
	{
		return gEntityTypesByType.FindEntityType(type);
	}
}
