#include "code/proto/npcrenderbehaviour.h"
#include "code/core/refptr.h"
#include "code/engine/gameobject/gameobject.h"

namespace proto
{
#define PROTO_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1047A8D0
	content::ClassInfo* NPCRenderBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::NPCRenderBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1047A910
	NPCRenderBehaviour::NPCRenderBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), npcRender(0),
		startVisible(false)
	{
		Listen(7, true);
		Listen(0x3d, true);
		Listen(0x3a, true);
	}

	// FUNCTION: ENGINE 0x1047AA60
	NPCRenderBehaviour::~NPCRenderBehaviour()
	{
		core::SafeRelease(npcRender);
	}

	// FUNCTION: ENGINE 0x1047A970
	void NPCRenderBehaviour::Slot1()
	{
		instance.SetObject(owner);
		instance.SetRender(npcRender);
		instance.SetUnknown10(1);
		instance.SetLod(0);
		instance.SetRegistered(startVisible);
		Listen2(0x100, true);
	}

	// FUNCTION: ENGINE 0x1047A9D0
	void NPCRenderBehaviour::SetRegistered(bool registered)
	{
		instance.SetRegistered(registered);
	}

	// FUNCTION: ENGINE 0x1047A9E0
	void NPCRenderBehaviour::DestroyDrawable()
	{
		instance.DestroyDrawable();
	}

	// FUNCTION: ENGINE 0x1047A9F0
	void NPCRenderBehaviour::SetDrawableValue(float value)
	{
		instance.drawable.SetUnknownBC(value);
	}

	// FUNCTION: ENGINE 0x1047AAD0
	void NPCRenderBehaviour::OnActiveChanged(bool active)
	{
		if (active != requested.Test(7))
		{
			engine::Behaviour::OnActiveChanged(active);
			SetRegistered(active);
		}
	}

	// FUNCTION: ENGINE 0x1047AA90
	void NPCRenderBehaviour::Update(float dt, unsigned short mask)
	{
		if (mask == 0x100)
		{
			instance.Create(true);
			instance.SetTransform(owner->transform->value);
		}
	}

	// FUNCTION: ENGINE 0x1047ACF0
	content::MemberList* NPCRenderBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, NPCRenderBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<NPCRenderBehaviour, NPCRender>("p"),
				PROTO_OFFSET(NPCRenderBehaviour, npcRender), "npcRender" },
			{ content::GetMemberPrimitiveMetaType<NPCRenderBehaviour, bool, 0>("p"),
				PROTO_OFFSET(NPCRenderBehaviour, startVisible), "startVisible" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1047AA10
// FUNCTION: ENGINE 0x1047AA20
// FUNCTION: ENGINE 0x1047AA30
// FUNCTION: ENGINE 0x1047AB10
// FUNCTION: ENGINE 0x1047AB50
// FUNCTION: ENGINE 0x1047AB60
// FUNCTION: ENGINE 0x1047AB90
// FUNCTION: ENGINE 0x1047AC90
