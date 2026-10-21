#include "code/engine/surfacedefinition.h"

#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

// FUNCTION: ENGINE 0x10911500
content::ClassInfo* SurfaceDefinition::GetClassInfo()
{
	static content::ClassInfo sInfo;
	sInfo.version = 1;
	sInfo.name = "SurfaceDefinition";
	sInfo.code = "p";
	return &sInfo;
}

// FUNCTION: ENGINE 0x10911670
content::MemberList* SurfaceDefinition::GetMembers()
{
	static content::MemberList sList;
	static content::MemberInfo sMembers[] =
	{
		{ content::GetMemberStringMetaType<0>(&((SurfaceDefinition*)content::gStringMemberBase)->physicsObjectReference,
			"p"), content::StringBufferOffset(&((SurfaceDefinition*)content::gStringMemberBase)->physicsObjectReference)
			+ (int)&((SurfaceDefinition*)0)->physicsObjectReference, "physicsObjectReference" },
		{ content::GetMemberStringMetaType<1>(&((SurfaceDefinition*)content::gStringMemberBase)->decalName, "p"),
			content::StringBufferOffset(&((SurfaceDefinition*)content::gStringMemberBase)->decalName)
			+ (int)&((SurfaceDefinition*)0)->decalName, "decalName" },
		{ content::GetMemberStringMetaType<2>(&((SurfaceDefinition*)content::gStringMemberBase)->soundEffectName,
			"p"), content::StringBufferOffset(&((SurfaceDefinition*)content::gStringMemberBase)->soundEffectName)
			+ (int)&((SurfaceDefinition*)0)->soundEffectName, "soundEffectName" }
	};
	sList.members = sMembers;
	sList.count = 3;
	return &sList;
}

// FUNCTION: ENGINE 0x109117B0
// EQUIVALENT: the engine's lea of the handle member sits behind the reference count store, ours before it, 92.2 %
SurfaceDefinition::SurfaceDefinition()
{
}

// FUNCTION: ENGINE 0x10911800
SurfaceDefinition::~SurfaceDefinition()
{
	if (handle.Get() != 0)
	{
		handle.DeferUpdate(false);
	}
}



// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10911540
// FUNCTION: ENGINE 0x10911560
// FUNCTION: ENGINE 0x10911570
// FUNCTION: ENGINE 0x10911580
// FUNCTION: ENGINE 0x10911590
// FUNCTION: ENGINE 0x109115A0
// FUNCTION: ENGINE 0x109115C0
// FUNCTION: ENGINE 0x109115F0
// FUNCTION: ENGINE 0x10911620
// FUNCTION: ENGINE 0x10911660
// FUNCTION: ENGINE 0x10911860

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10911550
