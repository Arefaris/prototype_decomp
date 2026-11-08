// engine::GameObjectTemplateBuilder (RTTI and reflection names; a content::MetaObjectTemplate): unit 0x1090C110 -
// 0x1090D700 (no assert path; the file name is a guess). The class information, the reflection, the constructor, the
// destructor and the trivial slots are reconstructed so far; loading it (slot 5) and creating the object (slot 9) are
// left to the engine.
#include "code/engine/gameobjecttemplatebuilder.h"
#include "code/engine/reflectedclasses.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1090C110
	content::ClassInfo* GameObjectTemplateBuilder::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "GameObjectTemplateBuilder";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1090CE10
	GameObjectTemplateBuilder::GameObjectTemplateBuilder() : unknown2C(0), unknown30(0)
	{
	}

	// FUNCTION: ENGINE 0x1090D660
	GameObjectTemplateBuilder::~GameObjectTemplateBuilder()
	{
		for (unsigned int i = 0; i < (unsigned int)templates.Size(); i++)
		{
			templates[i]->Release();
		}
		delete unknown2C;
		delete unknown30;
	}

	// FUNCTION: ENGINE 0x1090CE60
	void* GameObjectTemplateBuilder::Slot7()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1090CE40
	void GameObjectTemplateBuilder::Slot8(void* object)
	{
	}

	// FUNCTION: ENGINE 0x1090CE50
	void GameObjectTemplateBuilder::Slot10(content::MetaObjectFactoryBase* newFactory)
	{
	}

	// FUNCTION: ENGINE 0x1090CC30
	content::MemberList* GameObjectTemplateBuilder::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<content::MetaObjectTemplate>();
		static content::BaseClassCasterImpl<content::MetaObjectTemplate, GameObjectTemplateBuilder> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<GameObjectTemplateBuilder, TemplateArray>(
				content::GetReferenceMetaType<GameObjectTemplateBuilder, content::MetaObjectTemplate>("p"), "p"),
				ENGINE_OFFSET(GameObjectTemplateBuilder, templates), "templates" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

namespace container
{
	template class ArrayDynamic<content::MetaObjectTemplate*, AllocatorNew>;
	template class ArrayDynamicNew<unsigned __int64>;
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1090C150
// FUNCTION: ENGINE 0x1090C160
// FUNCTION: ENGINE 0x1090C1B0
// FUNCTION: ENGINE 0x1090C1C0
// FUNCTION: ENGINE 0x1090C1E0
// FUNCTION: ENGINE 0x1090C220
// FUNCTION: ENGINE 0x1090C230
// FUNCTION: ENGINE 0x1090C290
// FUNCTION: ENGINE 0x1090C2A0
// FUNCTION: ENGINE 0x1090C300
// FUNCTION: ENGINE 0x1090C380
// FUNCTION: ENGINE 0x1090C390
// FUNCTION: ENGINE 0x1090C420
// FUNCTION: ENGINE 0x1090C430
// FUNCTION: ENGINE 0x1090C710
// FUNCTION: ENGINE 0x1090C770
// FUNCTION: ENGINE 0x1090C830
// FUNCTION: ENGINE 0x1090C840
// FUNCTION: ENGINE 0x1090C850
// FUNCTION: ENGINE 0x1090C860
// FUNCTION: ENGINE 0x1090C870
// FUNCTION: ENGINE 0x1090C8C0
// FUNCTION: ENGINE 0x1090C8D0
// FUNCTION: ENGINE 0x1090C8E0
// FUNCTION: ENGINE 0x1090C8F0
// FUNCTION: ENGINE 0x1090C910
// FUNCTION: ENGINE 0x1090C940
// FUNCTION: ENGINE 0x1090C970
// FUNCTION: ENGINE 0x1090C9B0
// FUNCTION: ENGINE 0x1090C9E0
// FUNCTION: ENGINE 0x1090CA30
// FUNCTION: ENGINE 0x1090CA40
// FUNCTION: ENGINE 0x1090CA90
// FUNCTION: ENGINE 0x1090CB40
// FUNCTION: ENGINE 0x1090CCF0
// FUNCTION: ENGINE 0x1090CD10
// FUNCTION: ENGINE 0x1090CD40
// FUNCTION: ENGINE 0x1090CD90
// FUNCTION: ENGINE 0x1090CE70
// FUNCTION: ENGINE 0x1090CFF0
// FUNCTION: ENGINE 0x1090D050
// FUNCTION: ENGINE 0x1090CB00
