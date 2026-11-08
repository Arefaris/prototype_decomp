// The entities of the om library and their registry (0x105B49E0 - 0x105B5D6E; names guessed).
#include "code/om/entity.h"

#include "code/core/criticalsection.h"
#include "code/om/atgcontent.h"
#include <string.h>

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

	// FUNCTION: ENGINE 0x105B5880
	// NONMATCHING: the engine keeps the tree in memory and the high half of the name in edi (register assignment, 47.7 %)
#ifdef NONMATCHING
	bool TreeHead::InsertEntity(Entity* entity)
	{
		TreeNode* inserted = entity != 0 ? &entity->nodeByName : 0;
		TreeNode* parent = &nil;
		TreeNode* current = root;
		if (current != &nil)
		{
			do
			{
				parent = current;
				Entity* other = current != 0 ? (Entity*)((char*)current - 0x10) : 0;
				if (entity->name.key < other->name.key)
				{
					current = current->left;
				}
				else
				{
					current = current->right;
				}
			}
			while (current != &nil);
		}
		inserted->parent = parent;
		if (parent == &nil)
		{
			root = inserted;
		}
		else
		{
			Entity* other = parent != 0 ? (Entity*)((char*)parent - 0x10) : 0;
			if (entity->name.key < other->name.key)
			{
				parent->left = inserted;
			}
			else
			{
				parent->right = inserted;
			}
		}
		inserted->left = &nil;
		inserted->right = &nil;
		inserted->color = 1;
		TreeNode* fixed = inserted;
		while (fixed != root && fixed->parent->color == 1)
		{
			if (fixed->parent == fixed->parent->parent->left)
			{
				TreeNode* uncle = fixed->parent->parent->right;
				if (uncle->color == 1)
				{
					fixed->parent->color = 0;
					uncle->color = 0;
					fixed->parent->parent->color = 1;
					fixed = fixed->parent->parent;
				}
				else
				{
					if (fixed == fixed->parent->right)
					{
						fixed = fixed->parent;
						RotateLeft(fixed);
					}
					fixed->parent->color = 0;
					fixed->parent->parent->color = 1;
					RotateRight(fixed->parent->parent);
				}
			}
			else
			{
				TreeNode* uncle = fixed->parent->parent->left;
				if (uncle->color == 1)
				{
					fixed->parent->color = 0;
					uncle->color = 0;
					fixed->parent->parent->color = 1;
					fixed = fixed->parent->parent;
				}
				else
				{
					if (fixed == fixed->parent->left)
					{
						fixed = fixed->parent;
						RotateRight(fixed);
					}
					fixed->parent->color = 0;
					fixed->parent->parent->color = 1;
					RotateLeft(fixed->parent->parent);
				}
			}
		}
		root->color = 0;
		return true;
	}

#endif

	// FUNCTION: ENGINE 0x105B4D40
	bool TreeHead::InsertEntityTypeByName(EntityTypeBase* type)
	{
		TreeNode* inserted = type != 0 ? &type->nodeByName : 0;
		TreeNode* parent = &nil;
		TreeNode* current = root;
		if (current != &nil)
		{
			const char* name = type->name;
			do
			{
				parent = current;
				EntityTypeBase* other = current != 0 ? (EntityTypeBase*)((char*)current - 0x1C) : 0;
				int result = strcmp(name, other->name);
				if (result < 0)
				{
					current = current->left;
				}
				else if (result > 0)
				{
					current = current->right;
				}
				else
				{
					return false;
				}
			}
			while (current != &nil);
		}
		inserted->parent = parent;
		if (parent == &nil)
		{
			root = inserted;
		}
		else
		{
			EntityTypeBase* other = parent != 0 ? (EntityTypeBase*)((char*)parent - 0x1C) : 0;
			int result = strcmp(type->name, other->name);
			if (result < 0)
			{
				parent->left = inserted;
			}
			else if (result > 0)
			{
				parent->right = inserted;
			}
			else
			{
				return false;
			}
		}
		inserted->left = &nil;
		inserted->right = &nil;
		inserted->color = 1;
		TreeNode* fixed = inserted;
		while (fixed != root && fixed->parent->color == 1)
		{
			if (fixed->parent == fixed->parent->parent->left)
			{
				TreeNode* uncle = fixed->parent->parent->right;
				if (uncle->color == 1)
				{
					fixed->parent->color = 0;
					uncle->color = 0;
					fixed->parent->parent->color = 1;
					fixed = fixed->parent->parent;
				}
				else
				{
					if (fixed == fixed->parent->right)
					{
						fixed = fixed->parent;
						RotateLeft(fixed);
					}
					fixed->parent->color = 0;
					fixed->parent->parent->color = 1;
					RotateRight(fixed->parent->parent);
				}
			}
			else
			{
				TreeNode* uncle = fixed->parent->parent->left;
				if (uncle->color == 1)
				{
					fixed->parent->color = 0;
					uncle->color = 0;
					fixed->parent->parent->color = 1;
					fixed = fixed->parent->parent;
				}
				else
				{
					if (fixed == fixed->parent->left)
					{
						fixed = fixed->parent;
						RotateRight(fixed);
					}
					fixed->parent->color = 0;
					fixed->parent->parent->color = 1;
					RotateLeft(fixed->parent->parent);
				}
			}
		}
		root->color = 0;
		return true;
	}

	// FUNCTION: ENGINE 0x105B4F60
	// NONMATCHING: the engine lays the branch of the greater key out behind the one of the smaller (89.9 %)
#ifdef NONMATCHING
	bool TreeHead::InsertEntityTypeByType(EntityTypeBase* type)
	{
		TreeNode* inserted = type != 0 ? &type->nodeByType : 0;
		TreeNode* parent = &nil;
		TreeNode* current = root;
		if (current != &nil)
		{
			do
			{
				parent = current;
				EntityTypeBase* other = current != 0 ? (EntityTypeBase*)((char*)current - 0x3C) : 0;
				const type_info* key = type->type;
				const type_info* otherKey = other->type;
				if (key->before(*otherKey))
				{
					current = current->right;
				}
				else if (otherKey->before(*key))
				{
					current = current->left;
				}
				else
				{
					return false;
				}
			}
			while (current != &nil);
		}
		inserted->parent = parent;
		if (parent == &nil)
		{
			root = inserted;
		}
		else
		{
			EntityTypeBase* other = parent != 0 ? (EntityTypeBase*)((char*)parent - 0x3C) : 0;
			const type_info* key = type->type;
			const type_info* otherKey = other->type;
			if (key->before(*otherKey))
			{
				parent->right = inserted;
			}
			else if (otherKey->before(*key))
			{
				parent->left = inserted;
			}
			else
			{
				return false;
			}
		}
		inserted->left = &nil;
		inserted->right = &nil;
		inserted->color = 1;
		TreeNode* fixed = inserted;
		while (fixed != root && fixed->parent->color == 1)
		{
			if (fixed->parent == fixed->parent->parent->left)
			{
				TreeNode* uncle = fixed->parent->parent->right;
				if (uncle->color == 1)
				{
					fixed->parent->color = 0;
					uncle->color = 0;
					fixed->parent->parent->color = 1;
					fixed = fixed->parent->parent;
				}
				else
				{
					if (fixed == fixed->parent->right)
					{
						fixed = fixed->parent;
						RotateLeft(fixed);
					}
					fixed->parent->color = 0;
					fixed->parent->parent->color = 1;
					RotateRight(fixed->parent->parent);
				}
			}
			else
			{
				TreeNode* uncle = fixed->parent->parent->left;
				if (uncle->color == 1)
				{
					fixed->parent->color = 0;
					uncle->color = 0;
					fixed->parent->parent->color = 1;
					fixed = fixed->parent->parent;
				}
				else
				{
					if (fixed == fixed->parent->left)
					{
						fixed = fixed->parent;
						RotateRight(fixed);
					}
					fixed->parent->color = 0;
					fixed->parent->parent->color = 1;
					RotateLeft(fixed->parent->parent);
				}
			}
		}
		root->color = 0;
		return true;
	}

#endif

	// FUNCTION: ENGINE 0x105B54A0
	// NONMATCHING: the engine's search is one template body whose registers and branch layout differ (14.8 %)
#ifdef NONMATCHING
	EntityTypeBase* TreeHead::FindEntityType(const type_info& type)
	{
		TreeNode* current = root;
		if (current == &nil)
		{
			return 0;
		}
		TreeNode* previous;
		while (true)
		{
			EntityTypeBase* other = current != 0 ? (EntityTypeBase*)((char*)current - 0x3C) : 0;
			const type_info* otherType = other->type;
			if (!type.before(*otherType))
			{
				if (!otherType->before(type))
				{
					previous = Previous(current);
					break;
				}
				current = current->left;
			}
			else
			{
				current = current->right;
			}
			if (current == &nil)
			{
				return 0;
			}
		}
		while (previous != 0)
		{
			const type_info* otherType = ((EntityTypeBase*)((char*)previous - 0x3C))->type;
			if (type.before(*otherType) || otherType->before(type))
			{
				break;
			}
			current = previous;
			previous = Previous(previous);
		}
		return current != 0 ? (EntityTypeBase*)((char*)current - 0x3C) : 0;
	}

#endif

	// FUNCTION: ENGINE 0x105B53C0
	// NONMATCHING: as the search by type (53.5 %)
#ifdef NONMATCHING
	EntityTypeBase* TreeHead::FindEntityTypeByName(const char** name)
	{
		TreeNode* current = root;
		if (current == &nil)
		{
			return 0;
		}
		TreeNode* previous;
		while (true)
		{
			EntityTypeBase* other = current != 0 ? (EntityTypeBase*)((char*)current - 0x1C) : 0;
			int result = strcmp(*name, other->name);
			if (result < 0)
			{
				current = current->left;
			}
			else
			{
				if (result <= 0)
				{
					previous = Previous(current);
					break;
				}
				current = current->right;
			}
			if (current == &nil)
			{
				return 0;
			}
		}
		while (previous != 0)
		{
			EntityTypeBase* other = (EntityTypeBase*)((char*)previous - 0x1C);
			if (strcmp(*name, other->name) != 0)
			{
				break;
			}
			current = previous;
			previous = Previous(previous);
		}
		return current != 0 ? (EntityTypeBase*)((char*)current - 0x1C) : 0;
	}

#endif

	// FUNCTION: ENGINE 0x105B57D0
	// NONMATCHING: as the search by type (24.3 %)
#ifdef NONMATCHING
	Entity* TreeHead::FindEntity(const ClassName& name)
	{
		TreeNode* current = root;
		if (current == &nil)
		{
			return 0;
		}
		TreeNode* previous;
		while (true)
		{
			Entity* other = current != 0 ? (Entity*)((char*)current - 0x10) : 0;
			if (name.key < other->name.key)
			{
				current = current->left;
			}
			else
			{
				if (name.key <= other->name.key)
				{
					previous = Previous(current);
					break;
				}
				current = current->right;
			}
			if (current == &nil)
			{
				return 0;
			}
		}
		while (previous != 0)
		{
			Entity* other = (Entity*)((char*)previous - 0x10);
			if (name.key != other->name.key)
			{
				break;
			}
			current = previous;
			previous = Previous(previous);
		}
		return current != 0 ? (Entity*)((char*)current - 0x10) : 0;
	}

#endif

	// FUNCTION: ENGINE 0x105B5610
	EntityTypeBase* GetFirstEntityType()
	{
		TreeNode* node = gEntityTypesByType.First();
		if (node != 0)
		{
			return (EntityTypeBase*)((char*)node - 0x3C);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105B5630
	EntityTypeBase* GetNextEntityType(EntityTypeBase* type)
	{
		TreeNode* node = type != 0 ? &type->nodeByType : 0;
		node = gEntityTypesByType.Next(node);
		if (node != 0)
		{
			return (EntityTypeBase*)((char*)node - 0x3C);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105B5660
	// NONMATCHING: the engine loads the string data pointer before the test of the empty string (57.1 %)
#ifdef NONMATCHING
	EntityTypeBase* FindEntityTypeByName(String* name)
	{
		const char* text = name->data;
		if (text == gEmptyStringData)
		{
			text = "";
		}
		return gEntityTypesByName.FindEntityTypeByName(&text);
	}

#endif

	// FUNCTION: ENGINE 0x105B56E0
	// NONMATCHING: the engine reads the lock before it saves esi and edi (37.7 %)
#ifdef NONMATCHING
	Entity* GetFirstEntity()
	{
		void* lock = gEntityLock;
		core::CriticalSectionEnter(lock);
		TreeNode* node = gEntitiesByName.First();
		if (node != 0)
		{
			core::CriticalSectionLeave(lock);
			return (Entity*)((char*)node - 0x10);
		}
		core::CriticalSectionLeave(lock);
		return 0;
	}

#endif

	// FUNCTION: ENGINE 0x105B5730
	// NONMATCHING: as GetFirstEntity (29 %)
#ifdef NONMATCHING
	Entity* GetNextEntity(Entity* entity)
	{
		void* lock = gEntityLock;
		core::CriticalSectionEnter(lock);
		TreeNode* node = entity != 0 ? &entity->nodeByName : 0;
		node = gEntitiesByName.Next(node);
		if (node != 0)
		{
			core::CriticalSectionLeave(lock);
			return (Entity*)((char*)node - 0x10);
		}
		core::CriticalSectionLeave(lock);
		return 0;
	}

#endif

	// FUNCTION: ENGINE 0x105B5790
	int AddRefEntity(Entity* entity)
	{
		return ThreadSafeRefCount::AddRef(&entity->count);
	}

	// FUNCTION: ENGINE 0x105B5A30
	// NONMATCHING: as GetFirstEntity (41.7 %)
#ifdef NONMATCHING
	Entity* FindEntityByName(const ClassName& name)
	{
		void* lock = gEntityLock;
		core::CriticalSectionEnter(lock);
		Entity* found = gEntitiesByName.FindEntity(name);
		core::CriticalSectionLeave(lock);
		return found;
	}

#endif

	// FUNCTION: ENGINE 0x105B5A70
	// NONMATCHING: the engine tests the pointer again before the delete (68.3 %)
#ifdef NONMATCHING
	void EntityReference::Reset()
	{
		Entity* held = entity;
		if (held != 0)
		{
			entity = 0;
			if (ThreadSafeRefCount::Release(&held->count) == 0)
			{
				delete held;
			}
		}
	}

#endif

	// FUNCTION: ENGINE 0x105B5AA0
	// NONMATCHING: register assignment of the two pointers (42.5 %)
#ifdef NONMATCHING
	EntityReference& EntityReference::operator=(const EntityReference& other)
	{
		Entity* held = entity;
		if (other.entity != held)
		{
			if (held != 0)
			{
				if (ThreadSafeRefCount::Release(&held->count) == 0)
				{
					delete held;
				}
			}
			entity = other.entity;
			if (entity != 0)
			{
				ThreadSafeRefCount::AddRef(&entity->count);
			}
		}
		return *this;
	}

#endif

	// FUNCTION: ENGINE 0x105B5AF0
	// NONMATCHING: register assignment of the two pointers (81.6 %)
#ifdef NONMATCHING
	Entity* EntityReference::operator=(Entity* newEntity)
	{
		Entity* held = entity;
		if (held != newEntity)
		{
			entity = newEntity;
			if (newEntity != 0)
			{
				ThreadSafeRefCount::AddRef(&newEntity->count);
			}
			if (held != 0)
			{
				if (ThreadSafeRefCount::Release(&held->count) == 0)
				{
					delete held;
				}
			}
			return entity;
		}
		return held;
	}

#endif

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

namespace om
{
	om::TreeHead gEntityTypesByName;
	om::TreeHead gEntityTypesByType;
	om::TreeHead gEntitiesByName;
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D66480
// FUNCTION: ENGINE 0x10D664A0
// FUNCTION: ENGINE 0x10D664C0
// FUNCTION: ENGINE 0x10D866D0
// FUNCTION: ENGINE 0x10D866E0
// FUNCTION: ENGINE 0x10D866F0
