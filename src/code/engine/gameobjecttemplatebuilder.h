// engine::GameObjectTemplateBuilder (RTTI and reflection names; a content::MetaObjectTemplate): a template that is made
// of other templates, listed in its reflected "templates" array; loading it builds the objects they stand for. Unit
// 0x1090C110 - 0x1090D700 (no assert path; the file name is a guess). The two name lists behind it are made when it is
// loaded.
#ifndef ENGINE_GAMEOBJECTTEMPLATEBUILDER_H
#define ENGINE_GAMEOBJECTTEMPLATEBUILDER_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/container/arraydynamicnew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/gameobjectspawner.h"

namespace engine
{
	class GameObjectTemplateBuilder : public content::MetaObjectTemplate
	{
	public:
		typedef container::ArrayDynamic<content::MetaObjectTemplate*, container::AllocatorNew> TemplateArray;
		// The lists hold 64-bit names (hashes)
		typedef container::ArrayDynamicNew<unsigned __int64> NameArray;

		// 0x1090CE10
		GameObjectTemplateBuilder();
		// 0x1090D660 (deleting destructor 0x1090D700): lets go of the templates and the lists
		virtual ~GameObjectTemplateBuilder();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 5 (0x1090D0B0, left to the engine)
		virtual bool Slot5();
		// Slots 7, 8 and 10 (0x1090CE60, 0x1090CE40, 0x1090CE50): the template holds no object of its own
		virtual void* Slot7();
		virtual void Slot8(void* object);
		// Slot 9 (0x1090C460, left to the engine)
		virtual engine::GameObject* Create(int heap, content::LoadInventory* inventory,
			const content::ObjectName& name, bool flag);
		virtual void Slot10(content::MetaObjectFactoryBase* newFactory);

		TemplateArray templates;  // +0x18
		// The word behind the array (the arrays of this kind are followed by one; never touched here)
		int unknown24;
		bool unknown28;  // +0x28
		bool unknown29;
		bool unknown2A;
		NameArray* unknown2C;  // +0x2C
		NameArray* unknown30;  // +0x30
		int unknown34;
	};
}

#endif
