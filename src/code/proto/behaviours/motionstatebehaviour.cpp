#include "code/proto/behaviours/motionstatebehaviour.h"
#include "code/engine/fight/fighteventmessage.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/scenariomessage.h"
#include "code/proto/scenariomessages.h"

namespace engine
{
	// 0x11252058: the listeners of the name "scenario" of this unit (name guess)
	extern MessageListeners gScenario28;

	// FUNCTION: ENGINE 0x10075450
	ScenarioMessage::ScenarioMessage(int event) : IntrusiveMessage(0xd, (short)event)
	{
	}
}

namespace content
{
	static const EnumValue sMotionStateValues[] =
	{
		{ "NotSet", -1 },
		{ "Idling", 0 },
		{ "Walking", 1 },
		{ "Running", 2 },
		{ "Falling", 3 },
		{ "Jumping", 4 },
		{ "Wallrunning", 5 },
		{ "GettingHit", 6 },
		{ "AttackWindup", 7 },
		{ "AttackRelease", 8 },
		{ "Flying", 9 },
		{ "Climbing", 10 },
		{ "BeingGrabbed", 11 },
		{ "Driving", 12 },
		{ "Blocking", 13 },
		{ "Stunned", 14 },
		{ "Gliding", 15 },
		{ "JumpingOutOfWater", 16 },
		{ "Consuming", 17 },
		{ "Devastator", 18 },
		{ "Sliding", 19 },
		{ "Other", 20 }
	};

	// FUNCTION: ENGINE 0x10075510
	template<> void EnumInfo<proto::MotionState::State>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::MotionState::State";
		*code = "";
		*values = sMotionStateValues;
		*count = 0x16;
	}
}

namespace proto
{
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10075710
	MotionStateBehaviour::MotionStateBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		motionState(MotionState::STATE_NOT_SET), unknown1C(false)
	{
		Listen(2, true);
		Listen(0x21, true);
	}

	MotionStateBehaviour::~MotionStateBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10075780
	// NONMATCHING: the engine shares the stack slot of the old name with the fight event message (85.3 %)
#ifdef NONMATCHING
	void MotionStateBehaviour::SetState(int newState, const core::Name<core::CaseSensitiveKey>& newName)
	{
		int oldState = motionState;
		core::Name<core::CaseSensitiveKey> oldName(name);
		motionState = (MotionState::State)newState;
		name = newName;
		if (oldState == newState && !(oldName != name))
		{
			return;
		}
		if (unknown1C)
		{
			int state = motionState;
			MotionStateScenarioMessage message(engine::GetHandle(owner), state, oldState);
			engine::SendMessage(&message, &engine::gScenario28);
		}
		engine::FightEventMessage fightEvent(0x40000);
		owner->SendMessage(&fightEvent);
	}
#endif

	// FUNCTION: ENGINE 0x10075880
	void MotionStateBehaviour::Reset()
	{
		motionState = MotionState::STATE_NOT_SET;
		name = core::Name<core::CaseSensitiveKey>();
		unknown1C = false;
	}

	// FUNCTION: ENGINE 0x10075590
	void MotionStateBehaviour::SetBroadcast(bool broadcast)
	{
		unknown1C = broadcast;
	}

	// FUNCTION: ENGINE 0x100759F0
	void MotionStateBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 2:
			Reset();
			break;
		case 0x21:
			switch ((unsigned short)message->id)
			{
			case 0xc:
				SetBroadcast(static_cast<SetBroadcastMotionStateMsg*>(message)->broadcast);
				break;
			case 0xb:
				static_cast<GetMotionStateMsg*>(message)->state = motionState;
				static_cast<GetMotionStateMsg*>(message)->name = name;
				break;
			case 0xa:
				SetState(static_cast<SetMotionStateMsg*>(message)->kind, static_cast<SetMotionStateMsg*>(message)->name);
				break;
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x10075550
	content::ClassInfo* MotionStateBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::MotionStateBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x100758C0
	content::MemberList* MotionStateBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, MotionStateBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<MotionState::State>(), 0x18, "motionState" },
			{ content::GetNameMetaType<MotionStateBehaviour>(true, true, ""),
				PROTO_NAME_OFFSET(MotionStateBehaviour, name), "name" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100755A0
// FUNCTION: ENGINE 0x10075630
// FUNCTION: ENGINE 0x100756D0
// FUNCTION: ENGINE 0x100756E0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10075770
// FUNCTION: ENGINE 0x100759C0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10075670
