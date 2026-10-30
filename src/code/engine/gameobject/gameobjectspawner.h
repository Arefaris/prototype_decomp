// engine::GameObjectSpawner (RTTI name; 10 vftable slots, base content::MetaLoadObject): builds game objects from a
// content::MetaObjectTemplate and places them at its transform. The engine's and the game's spawners (PropSpawner,
// ActorSpawner, proto::CloudSpawner, ...) derive from it. Unit 0x107F22C0 - 0x107F27D0 (no assert path; the file name
// is a guess). The reflected members are "transform" and "template"; the other names are guesses.
#ifndef ENGINE_GAMEOBJECT_GAMEOBJECTSPAWNER_H
#define ENGINE_GAMEOBJECT_GAMEOBJECTSPAWNER_H

#include "code/content/loadinventory.h"
#include "code/core/refptr.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/matrix.h"

namespace engine
{
	class GameObject;
}

namespace content
{
	struct ClassInfo;
	struct MemberList;
	class MetaObjectFactoryBase;

	// content::MetaObjectTemplate (RTTI: 11 vftable slots; unit 0x10606A10 - 0x10606BB0, content/metaobjecttemplate.cpp):
	// what game objects are built from. It holds an object of the class its factory makes; slot 9 builds a copy.
	class MetaObjectTemplate : public MetaLoadObject
	{
	public:
		// 0x10606B60
		MetaObjectTemplate();
		// 0x10606B30 (the scalar deleting destructor is 0x10606B90): destroys the object it holds
		virtual ~MetaObjectTemplate();

		// Slot 6 (0x10445BE0 in the engine's copy): takes the name
		virtual void SetName(const ObjectName& newName);
		// The object the template is made of (slot 7: answers it; slot 8: takes it, a new value of the class)
		virtual void* Slot7();
		virtual void Slot8(void* object);
		// The new object of name in heap, kept in inventory (flag: passed on from the spawner, meaning unknown)
		virtual engine::GameObject* Create(int heap, LoadInventory* inventory, const ObjectName& name, bool flag);
		// Slot 10 (0x10606A40): takes the factory that makes the objects the template stands for
		virtual void Slot10(MetaObjectFactoryBase* newFactory);
		// 0x10606A50
		MetaObjectFactoryBase* GetFactory();

		MetaObjectFactoryBase* factory;
		void* object;
		ObjectName name;
	};
}

namespace engine
{
	class GameObjectSpawner : public content::MetaLoadObject
	{
	public:
		GameObjectSpawner();
		virtual ~GameObjectSpawner();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
		// The number of objects named "gameobject<n>" so far
		static int GetNameCount();

		// Builds an object of tmpl in heap and keeps it in inventory (null: the root inventory), adds it to target
		// (null: the game object inventory) and records the template's name in its "meta object template" attribute;
		// with flag the object leaves the message channel of its "packageName" attribute
		static GameObject* Create(content::MetaObjectTemplate* tmpl, const content::ObjectName& name, int heap,
			content::LoadInventory* inventory, content::LoadInventory* target, bool flag);
		// Create in the current heap
		static GameObject* Create(content::MetaObjectTemplate* tmpl, const content::ObjectName& name,
			content::LoadInventory* inventory, content::LoadInventory* target, bool flag);
		// Create under the next "gameobject<n>" name
		static GameObject* Create(content::MetaObjectTemplate* tmpl, content::LoadInventory* inventory);

		virtual bool IsReady();
		void SetTemplate(content::MetaObjectTemplate* newTemplate);

		// Slot 7: an object of the spawner's template
		virtual GameObject* CreateObject(const content::ObjectName& name, content::LoadInventory* inventory);
		// Slot 8: CreateObject (an empty name takes the next "gameobject<n>") placed at the spawner's transform
		virtual GameObjectHandle Spawn(content::LoadInventory* inventory, content::ObjectName name);
		// Slot 9 (its copy is in another unit, 0x102994B0)
		virtual void SetTransform(const math::Matrix& matrix)
		{
			transform = matrix;
		}

		static int sNameCount;

		content::MetaObjectTemplate* objectTemplate;
		math::Matrix transform;
	};
}

#endif
