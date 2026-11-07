#include "code/engine/tagbehaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/messagerouter.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10929690
	content::ClassInfo* TagBehaviour::TagWrapper::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "TagBehaviour::TagWrapper";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x109296D0
	content::ClassInfo* TagBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "TagBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x109297D0
	content::MemberList* TagBehaviour::TagWrapper::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<TagWrapper>(true, true, "pn"), ENGINE_NAME_OFFSET(TagWrapper, name), "tag" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10929BB0
	content::MemberList* TagBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, TagBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<TagBehaviour, TagArray>(content::GetClassMetaType<TagWrapper>(), "pn"),
				ENGINE_OFFSET(TagBehaviour, tags), "tags" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10929DC0
	void TagBehaviour::Slot1()
	{
		GameObjectHandle handle = GetHandle(owner);
		TagWrapper* tag = tags.begin;
		TagWrapper* last = tags.end;
		for (; tag != last; tag++)
		{
			handle.RouterRemove(*static_cast<const MessageListeners*>(&tag->name));
		}
		tags.Free();
	}

	// FUNCTION: ENGINE 0x10929EE0
	TagBehaviour::TagBehaviour(GameObject* newOwner) : Behaviour(newOwner)
	{
	}

	// FUNCTION: ENGINE 0x10929F10
	TagBehaviour::~TagBehaviour()
	{
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10929710
// FUNCTION: ENGINE 0x10929740
// FUNCTION: ENGINE 0x10929750
// FUNCTION: ENGINE 0x10929790
// FUNCTION: ENGINE 0x109297A0
// FUNCTION: ENGINE 0x109297B0
// FUNCTION: ENGINE 0x10929850
// FUNCTION: ENGINE 0x10929860
// FUNCTION: ENGINE 0x10929890
// FUNCTION: ENGINE 0x10929940
// FUNCTION: ENGINE 0x10929950
// FUNCTION: ENGINE 0x10929960
// FUNCTION: ENGINE 0x10929980
// FUNCTION: ENGINE 0x109299B0
// FUNCTION: ENGINE 0x109299C0
// FUNCTION: ENGINE 0x109299D0
// FUNCTION: ENGINE 0x109299E0
// FUNCTION: ENGINE 0x10929A00
// FUNCTION: ENGINE 0x10929A10
// FUNCTION: ENGINE 0x10929A70
// FUNCTION: ENGINE 0x10929A90
// FUNCTION: ENGINE 0x10929AA0
// FUNCTION: ENGINE 0x10929B70
// FUNCTION: ENGINE 0x10929C60
// FUNCTION: ENGINE 0x10929CA0
// FUNCTION: ENGINE 0x10929D50
// FUNCTION: ENGINE 0x10929E20
// FUNCTION: ENGINE 0x10929E40
// FUNCTION: ENGINE 0x10929E70
// FUNCTION: ENGINE 0x10929FD0
