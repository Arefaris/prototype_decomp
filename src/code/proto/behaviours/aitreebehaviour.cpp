#include "code/proto/behaviours/aitreebehaviour.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/proto/fightitems/ai/aihelpers.h"

namespace engine
{
	// 0x11263BA0: the name "agent__" (charactertypenames.cpp)
	extern core::Name<core::CaseSensitiveKey> gAgent;
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x103C78E0
	content::ClassInfo* AiTreeBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "AiTreeBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103C7920
	void AiTreeBehaviour::Slot1()
	{
		FightTreeBehaviour::Slot1();
		Listen2(4, true);
		engine::GetHandle(owner).RouterRemove(*(const engine::MessageListeners*)&engine::gAgent);
		gAISystem->Unknown10364760(owner);
		registered = true;
	}

	// FUNCTION: ENGINE 0x103C7980
	void AiTreeBehaviour::OnActiveChanged(bool active)
	{
		FightTreeBehaviour::OnActiveChanged(active);
		if (active)
		{
			if (!registered)
			{
				gAISystem->Unknown10364760(owner);
				registered = true;
			}
		}
		else
		{
			sequencer.Reset();
			if (registered)
			{
				gAISystem->Unknown10362E30(owner);
				registered = false;
			}
		}
	}

	// FUNCTION: ENGINE 0x103C79F0
	void AiTreeBehaviour::OnPostedMessage(engine::Message* message)
	{
		FightTreeBehaviour::OnPostedMessage(message);
	}

	// FUNCTION: ENGINE 0x103C8750
	void AiTreeBehaviour::Reset()
	{
		sequencer.Reset();
		entries.Clear();
		pendingEntries.Clear();
		Unknown103B81A0(owner);
		flags = 0;
		unknown6C = false;
	}

	// FUNCTION: ENGINE 0x103C8820
	AiTreeBehaviour::~AiTreeBehaviour()
	{
		if (registered)
		{
			gAISystem->Unknown10362E30(owner);
			registered = false;
		}
	}

	// FUNCTION: ENGINE 0x103C8870
	void AiTreeBehaviour::ResetAndStop()
	{
		unknown6A = false;
		Reset();
	}

	// FUNCTION: ENGINE 0x103C8CA0
	AiTreeBehaviour::AiTreeBehaviour(engine::GameObject* newOwner) : engine::FightTreeBehaviour(newOwner, 0),
		autonomous(true), unknown69(false), unknown6A(false), registered(false), unknown6C(false), unknown6D(false),
		timeslicePeriod(0), unknown148(0.0f), tooltipOffset(0.0f), flags(0)
	{
		core::Name<core::CaseSensitiveKey>* contextNameMember = (core::Name<core::CaseSensitiveKey>*)GetSequencer();
		contextNameMember->SetText("AiTree");
		Listen(0x2b, true);
		Listen(0xd, true);
		Listen(2, true);
		Listen(0x2f, true);
		Listen(0x39, true);
		Listen(0xf, true);
		ResetAndStop();
	}

	// FUNCTION: ENGINE 0x103C82C0
	content::MemberList* AiTreeBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::FightTreeBehaviour>();
		static content::BaseClassCasterImpl<engine::FightTreeBehaviour, AiTreeBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<AiTreeBehaviour, bool, 0>("pn"),
				PROTO_OFFSET(AiTreeBehaviour, autonomous), "autonomous" },
			{ content::GetNameMetaType<AiTreeBehaviour>(true, true, "pn"),
				PROTO_NAME_OFFSET(AiTreeBehaviour, task), "task" },
			{ content::GetNameMetaTypeCopy<AiTreeBehaviour>(true, true, "pn"),
				PROTO_NAME_OFFSET(AiTreeBehaviour, goal), "goal" },
			{ content::GetMemberPrimitiveMetaType<AiTreeBehaviour, float, 1>("p"),
				PROTO_OFFSET(AiTreeBehaviour, tooltipOffset), "tooltipOffset" },
			{ content::GetMemberPrimitiveMetaType<AiTreeBehaviour, char, 2>("p"),
				PROTO_OFFSET(AiTreeBehaviour, timeslicePeriod), "timeslicePeriod" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103C7AC0
// FUNCTION: ENGINE 0x103C7AD0
// FUNCTION: ENGINE 0x103C7BA0
// FUNCTION: ENGINE 0x103C7BE0
// FUNCTION: ENGINE 0x103C7C20
// FUNCTION: ENGINE 0x103C8050
// FUNCTION: ENGINE 0x103C80D0
// FUNCTION: ENGINE 0x103C8110
// FUNCTION: ENGINE 0x103C8150
// FUNCTION: ENGINE 0x103C86C0
// FUNCTION: ENGINE 0x103C87A0
