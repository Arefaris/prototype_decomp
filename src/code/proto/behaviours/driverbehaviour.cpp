#include "code/proto/behaviours/driverbehaviour.h"
#include "code/proto/autotargetprioritylist.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/motion/motionmessages.h"
#include "code/proto/fightitems/ai/aiactionmessages.h"

namespace engine
{
	// 0x11265838, 0x11265848, 0x11265850, 0x11265868, 0x11265870: the names of the driver states (charactertypenames.cpp)
	extern core::Name<core::CaseSensitiveKey> gDriverPlayer;
	extern core::Name<core::CaseSensitiveKey> gDriverAIPlayerGunner;
	extern core::Name<core::CaseSensitiveKey> gDriverAILanded;
	extern core::Name<core::CaseSensitiveKey> gDriverAILandedEngineOn;
	extern core::Name<core::CaseSensitiveKey> gNoDriver;
}

namespace content
{
	static const EnumValue sDriverStateValues[] =
	{
		{ "NoDriver", 0 },
		{ "DriverAI", 1 },
		{ "DriverPlayer", 2 },
		{ "DriverLanded", 3 }
	};

	// FUNCTION: ENGINE 0x103D62E0
	template<> void EnumInfo<proto::DriverBehaviour::DriverState>::Get(const char** name, const EnumValue** values,
		int* count, const char** code)
	{
		*name = "proto::DriverBehaviour::DriverState";
		*code = "pn";
		*values = sDriverStateValues;
		*count = 4;
	}
}

namespace proto
{
	// RTTI proto::ResetTargetClassMessage: the object is targeted as what it is again (message type 0x3B id 4)
	struct ResetTargetClassMessage : public TargetableMessage
	{
		ResetTargetClassMessage() : TargetableMessage(4)
		{
		}
		virtual ~ResetTargetClassMessage()
		{
		}
	};

	// FUNCTION: ENGINE 0x103D6320
	content::ClassInfo* DriverBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DriverBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103D6370
	bool DriverBehaviour::IsAiState(int state)
	{
		switch (state)
		{
		case STATE_NO_DRIVER:
		case STATE_DRIVER_PLAYER:
			return false;
		case STATE_DRIVER_AI:
		case STATE_DRIVER_AI_LANDED:
		case STATE_DRIVER_AI_LANDED_ENGINE_ON:
		case STATE_DRIVER_AI_TAKING_OFF:
		case STATE_DRIVER_AI_PLAYER_GUNNER:
			return true;
		default:
			return false;
		}
	}

	// FUNCTION: ENGINE 0x103D63F0
	bool DriverBehaviour::IsNotPiloting(int state)
	{
		switch (state)
		{
		case STATE_DRIVER_AI:
		case STATE_DRIVER_PLAYER:
		case STATE_DRIVER_AI_LANDED_ENGINE_ON:
		case STATE_DRIVER_AI_TAKING_OFF:
			return false;
		case STATE_DRIVER_AI_LANDED:
			return true;
		default:
			return true;
		}
	}

	// FUNCTION: ENGINE 0x103D6590
	DriverBehaviour::DriverBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), state(1),
		stateName("None", 1), notDrivenByAITargetClass(0), unknown1C(false)
	{
		Listen(0x39, true);
		Listen(0x2f, true);
		Listen(0x31, true);
	}

	// FUNCTION: ENGINE 0x103D6600
	void DriverBehaviour::UpdateTargetClass()
	{
		if (notDrivenByAITargetClass != 0)
		{
			if (IsAiState(state))
			{
				ResetTargetClassMessage message;
				owner->SendMessage(&message);
			}
			else
			{
				SetTargetClassMessage message(notDrivenByAITargetClass);
				owner->SendMessage(&message);
			}
		}
	}

	// FUNCTION: ENGINE 0x103D68D0
	core::Name<core::CaseSensitiveKey> DriverBehaviour::GetStateName(int state)
	{
		switch (state)
		{
		case STATE_NO_DRIVER:
			return engine::gNoDriver;
		case STATE_DRIVER_AI:
			return engine::gDriverAI3;
		case STATE_DRIVER_PLAYER:
			return engine::gDriverPlayer;
		case STATE_DRIVER_AI_LANDED:
			return engine::gDriverAILanded;
		case STATE_DRIVER_AI_LANDED_ENGINE_ON:
			return engine::gDriverAILandedEngineOn;
		case STATE_DRIVER_AI_TAKING_OFF:
			return engine::gDriverAITakingOff;
		case STATE_DRIVER_AI_PLAYER_GUNNER:
			return engine::gDriverAIPlayerGunner;
		default:
			return core::Name<core::CaseSensitiveKey>("UnknownDriver", 1);
		}
	}

	// FUNCTION: ENGINE 0x103D69F0
	int DriverBehaviour::GetStateFromName(core::Name<core::CaseSensitiveKey> name)
	{
		if (name == engine::gNoDriver)
		{
			return STATE_NO_DRIVER;
		}
		if (name == engine::gDriverAI3)
		{
			return STATE_DRIVER_AI;
		}
		if (name == engine::gDriverPlayer)
		{
			return STATE_DRIVER_PLAYER;
		}
		if (name == engine::gDriverAILanded)
		{
			return STATE_DRIVER_AI_LANDED;
		}
		if (name == engine::gDriverAILandedEngineOn)
		{
			return STATE_DRIVER_AI_LANDED_ENGINE_ON;
		}
		if (name == engine::gDriverAITakingOff)
		{
			return STATE_DRIVER_AI_TAKING_OFF;
		}
		if (name == engine::gDriverAIPlayerGunner)
		{
			return STATE_DRIVER_AI_PLAYER_GUNNER;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x103D6B70
	content::MemberList* DriverBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, DriverBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<DriverState>(), 0xC, "driverState" },
			{ content::GetEnumMetaType<TargetClass>(), 0x18, "notDrivenByAITargetClass" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103D6C60
	void DriverBehaviour::Slot1()
	{
		Listen2(4, true);
		SetStateStateChangeMessage message(GetStateName(state));
		owner->SendMessage(&message);
		UpdateTargetClass();
	}

	// FUNCTION: ENGINE 0x103D6CE0
	void DriverBehaviour::OnActiveChanged(bool active)
	{
		engine::Behaviour::OnActiveChanged(active);
		if (active)
		{
			SetStateStateChangeMessage message(GetStateName(state));
			owner->SendMessage(&message);
			UpdateTargetClass();
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103D6430
// FUNCTION: ENGINE 0x103D6550
