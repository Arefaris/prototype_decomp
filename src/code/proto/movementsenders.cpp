#include "code/proto/messages/movementmessages.h"
#include "code/proto/messages/statemessages.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/proto/fightitems/ai/aiactionhelpers.h"
#include "code/proto/fightitems/ai/aihelpers.h"
#include "code/proto/fightitems/ai/aimessages.h"
#include "code/proto/fightitems/motion/motion_patsy.h"
#include "code/engine/gameobject/gameobjectmessages.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/fightitems/motion/motionmessages.h"
#include "code/core/strings.h"
#include <math.h>

namespace engine
{
	namespace driving
	{
		extern const float gZero;
	}
}

namespace engine
{
	extern core::Name<core::CaseSensitiveKey> gDriverPlayer;
	extern core::Name<core::CaseSensitiveKey> gNoDriver;
}

namespace choreo
{
	// 0x10D94FF8: -1.0f in the pooled constants
	extern const float gMinusOne;
}

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace proto
{
	// The helpers that send movement messages to an object (unit 0x103B82F0 - 0x103B8690, no assert path; the file name is
	// a guess)

	// FUNCTION: ENGINE 0x103B82F0
	void Unknown103B82F0(engine::GameObject* object)
	{
		StopMovementMessage message;
		object->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x103B8330
	void Unknown103B8330(engine::GameObject* object, const math::Vector* position, const MoveParams* params)
	{
		SetDestinationMovementMessage message(*position, params->tolerance, params->braking, params->ignoreRestrictions,
			params->unknown6);
		object->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x103B8440
	bool Unknown103B8440(engine::GameObject* object)
	{
		GetStateMovementMessage message;
		object->SendMessage(&message);
		return message.state != 2 && message.state != 3;
	}

	// FUNCTION: ENGINE 0x103B84B0
	bool Unknown103B84B0(engine::GameObject* object)
	{
		GetStateMovementMessage message;
		object->SendMessage(&message);
		if (message.state == 5 || message.state == 6)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x103B8630
	void Unknown103B8630(engine::GameObject* object, bool run, bool unknownD)
	{
		RunMovementMessage message(run, unknownD);
		object->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x103B8DC0
	int Unknown103B8DC0(engine::GameObject* object)
	{
		GetGameObjectLODAIMsg message;
		object->SendMessage(&message);
		return message.level;
	}

	// FUNCTION: ENGINE 0x103B8E10
	int Unknown103B8E10(engine::GameObject* object)
	{
		GetSustainedGameObjectLODAIMsg message;
		object->SendMessage(&message);
		return message.level;
	}

	// FUNCTION: ENGINE 0x103B8B80
	engine::GameObjectHandle Unknown103B8B80(engine::GameObject* object)
	{
		GetTargetMessage message;
		object->SendMessage(&message);
		return message.target;
	}

	// FUNCTION: ENGINE 0x103B92B0
	const fight::Name* Unknown103B92B0(engine::GameObject* object)
	{
		engine::CharacterQueryIntentionMessage message;
		object->SendMessage(&message);
		return message.intention->GetStateName();
	}

	// FUNCTION: ENGINE 0x103BB590
	void Unknown103BB590(engine::GameObject* object, core::Name<core::CaseSensitiveKey> state)
	{
		engine::CharacterQueryIntentionMessage message;
		object->SendMessage(&message);
		message.intention->SetStateName(state);
	}

	namespace fightitems
	{
		namespace motion
		{
			// FUNCTION: ENGINE 0x103B8B20
			float GetObjectHealth(engine::GameObject* object)
			{
				engine::GetHealthMessage message;
				object->PostMessage(&message);
				return message.health;
			}
		}
	}

	// FUNCTION: ENGINE 0x103B8E60
	bool Unknown103B8E60(engine::GameObject* object)
	{
		GetLODStateAIMsg message;
		object->SendMessage(&message);
		if (message.state == 0)
		{
			return false;
		}
		if (message.state != 3)
		{
			return false;
		}
		ThawAIMsg thaw;
		object->SendMessage(&thaw);
		return true;
	}

	// FUNCTION: ENGINE 0x103B8F00
	bool Unknown103B8F00(engine::GameObject* object)
	{
		GetLODStateAIMsg message;
		object->SendMessage(&message);
		if (message.state == 0)
		{
			return false;
		}
		if (message.state != 1)
		{
			return false;
		}
		FreezeAIMsg freeze;
		object->SendMessage(&freeze);
		return true;
	}

	// FUNCTION: ENGINE 0x103B8FA0
	bool Unknown103B8FA0(engine::GameObject* object)
	{
		GetLODStateAIMsg message;
		object->SendMessage(&message);
		return message.state == 3;
	}

	// FUNCTION: ENGINE 0x103B8FF0
	bool Unknown103B8FF0(engine::GameObject* object)
	{
		GetLODStateAIMsg message;
		object->SendMessage(&message);
		return message.state != 0;
	}

	// FUNCTION: ENGINE 0x103B91C0
	bool Unknown103B91C0(engine::GameObject* object)
	{
		IsSquadSquadMessage message;
		object->SendMessage(&message);
		return message.isSquad;
	}

	// FUNCTION: ENGINE 0x103B9210
	bool Unknown103B9210(engine::GameObject* object)
	{
		CanBeInSquadSquadMessage message;
		object->SendMessage(&message);
		return message.canBe;
	}

	// FUNCTION: ENGINE 0x103B9C80
	bool Unknown103B9C80(engine::GameObject* object)
	{
		GetTunnelingStateStateChangeMessage message;
		object->SendMessage(&message);
		return message.state != 0;
	}

	// FUNCTION: ENGINE 0x103B98B0
	int Unknown103B98B0(int value)
	{
		if (value != 0 && value != 1 && value != 2)
		{
			return 0;
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x103B98E0
	int Unknown103B98E0(const char* text)
	{
		if (text != 0 && *text != 0)
		{
			int lines = 1;
			unsigned int length = core::StrLen(text);
			for (unsigned int i = 0; i < length; i++)
			{
				if (text[i] == '\n')
				{
					lines++;
				}
			}
			if (text[length - 1] == '\n')
			{
				lines--;
			}
			return lines;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x103B9A10
	// NONMATCHING: the engine loads the four floats into registers before the products (40.8 %)
#ifdef NONMATCHING
	float Unknown103B9A10(const float* first, const float* second)
	{
		if (first[1] * second[0] - second[1] * first[0] > engine::driving::gZero)
		{
			return -1.0f;
		}
		return 1.0f;
	}
#endif

	// FUNCTION: ENGINE 0x103BB2F0
	bool Unknown103BB2F0(engine::GameObject* object)
	{
		GetStateStateChangeMessage message;
		object->SendMessage(&message);
		return message.state == engine::gDriverPlayer;
	}

	// FUNCTION: ENGINE 0x103BB350
	bool Unknown103BB350(engine::GameObject* object)
	{
		GetStateStateChangeMessage message;
		object->SendMessage(&message);
		return message.state == engine::gDriverPlayer;
	}

	// FUNCTION: ENGINE 0x103BB3B0
	bool Unknown103BB3B0(engine::GameObject* object)
	{
		GetStateStateChangeMessage message;
		object->SendMessage(&message);
		return message.state == engine::gNoDriver;
	}

	// FUNCTION: ENGINE 0x103BBC10
	float Unknown103BBC10(const float* first, const float* second)
	{
		float deltaX = second[0] - first[0];
		float deltaZ = second[2] - first[2];
		return sqrtf(deltaZ * deltaZ + deltaX * deltaX);
	}

	// FUNCTION: ENGINE 0x103BBC40
	float Unknown103BBC40(const float* first, const float* second)
	{
		float deltaX = second[0] - first[0];
		float deltaZ = second[2] - first[2];
		return deltaZ * deltaZ + deltaX * deltaX;
	}

	// FUNCTION: ENGINE 0x103BAFC0
	// NONMATCHING: the engine returns the negated clamp from two copies of the tail (68.4 %)
#ifdef NONMATCHING
	float Unknown103BAFC0(float value, float limit)
	{
		if (fabsf(value) > limit)
		{
			float result;
			if (value < 0.0f)
			{
				result = choreo::gMinusOne;
			}
			else
			{
				result = 0.0f;
				if (0.0f < value)
				{
					result = engine::driving::gOne;
				}
			}
			return -result;
		}
		return choreo::gMinusOne / limit * value;
	}
#else
	float Unknown103BAFC0(float value, float limit);
#endif

	// FUNCTION: ENGINE 0x103BB040
	float Unknown103BB040(float value, float limit)
	{
		return Unknown103BAFC0(value, limit);
	}

	// FUNCTION: ENGINE 0x103BA7F0
	bool Unknown103BA7F0(engine::GameObject* object, engine::GameObjectHandle target)
	{
		GetStatusPerceptionMsg message;
		object->SendMessage(&message);
		bool result = false;
		if (message.list != 0)
		{
			for (PerceptionStatusEntry* entry = message.list->begin; entry != message.list->end; entry++)
			{
				if (entry->target == target)
				{
					result = entry->status == 'n';
					break;
				}
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x103BA880
	// NONMATCHING: the engine keeps the status in the return register and starts from the cleared result (71.4 %)
#ifdef NONMATCHING
	bool Unknown103BA880(engine::GameObject* object, engine::GameObjectHandle target)
	{
		GetStatusPerceptionMsg message;
		object->SendMessage(&message);
		if (message.list == 0)
		{
			return false;
		}
		for (PerceptionStatusEntry* entry = message.list->begin; entry != message.list->end; entry++)
		{
			if (entry->target == target)
			{
				unsigned char status = entry->status;
				if (status == 'n' || status == 'l' || ((status == 'e' || status == 'f') && entry->unknown14 <= engine::driving::gOne))
				{
					return true;
				}
				return false;
			}
		}
		return false;
	}
#else
	bool Unknown103BA880(engine::GameObject* object, engine::GameObjectHandle target);
#endif

	// FUNCTION: ENGINE 0x103BA940
	void Unknown103BA940(engine::GameObject* object, engine::GameObjectHandle target, int* status, int* unknown5)
	{
		GetStatusPerceptionMsg message;
		object->SendMessage(&message);
		*status = 0;
		*unknown5 = 0;
		if (message.list == 0)
		{
			return;
		}
		for (PerceptionStatusEntry* entry = message.list->begin; entry != message.list->end; entry++)
		{
			if (entry->target == target || entry->secondTarget == target)
			{
				*status = entry->status;
				*unknown5 = entry->unknown5;
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x103B87F0
	void Unknown103B87F0(engine::GameObject* object, const math::Vector* direction)
	{
		SetTankBaseFacingDirectionMessage message(*direction);
		object->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x103B8510
	void Unknown103B8510(engine::GameObject* object, float speed, const math::Vector* motion, bool flag)
	{
		SetMotionMovementMessage message(speed, *motion, flag);
		object->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x103B85A0
	void Unknown103B85A0(engine::GameObject* object, float speed, const math::Vector* motion, bool flag)
	{
		SetMotionRelativeMovementMessage message(speed, *motion, flag);
		object->SendMessage(&message);
	}
}

// A function that constructs each message with the expansion of inline functions off: the compiler keeps the out-of-line
// copy of the constructor and of the destructor the engine has too (the users inline them)
#pragma inline_depth(0)
namespace
{
	void EmitSetDestinationMovementMessage()
	{
		proto::SetDestinationMovementMessage message(math::kZeroVector, 0.0f, false, false, false);
	}

	void EmitStopMovementMessage()
	{
		proto::StopMovementMessage message;
	}

	void EmitSetMotionMovementMessage()
	{
		proto::SetMotionMovementMessage message(0.0f, math::kZeroVector, false);
	}

	void EmitSetMotionRelativeMovementMessage()
	{
		proto::SetMotionRelativeMovementMessage message(0.0f, math::kZeroVector, false);
	}

	void EmitRunMovementMessage()
	{
		proto::RunMovementMessage message(false, false);
	}

	void EmitSetTankBaseFacingDirectionMessage()
	{
		proto::SetTankBaseFacingDirectionMessage message(math::kZeroVector);
	}

	void EmitHydraEvaluateDestinationMovementMessage()
	{
		proto::HydraEvaluateDestinationMovementMessage message(math::kZeroVector, false);
	}

	void EmitGotoFlyPathMovementMessage()
	{
		proto::GotoFlyPathMovementMessage message(0.0f, false, false, 0);
	}

	void EmitResetAIFrameInfoMovementMessage()
	{
		proto::ResetAIFrameInfoMovementMessage message;
	}

	void EmitGetPatrolPointMovementMessage()
	{
		proto::GetPatrolPointMovementMessage message(0);
	}

	void EmitGetLastPatrolPointMovementMessage()
	{
		proto::GetLastPatrolPointMovementMessage message;
	}

	void EmitGetNumberPatrolPointsMovementMessage()
	{
		proto::GetNumberPatrolPointsMovementMessage message;
	}

	void EmitGetPatrolPathMovementMessage()
	{
		proto::GetPatrolPathMovementMessage message;
	}

	void EmitGetPatrolPathInfoMovementMessage()
	{
		proto::GetPatrolPathInfoMovementMessage message;
	}

	void EmitGetGameObjectSuspicionPerceptionMessage()
	{
		proto::GetGameObjectSuspicionPerceptionMessage message(0);
	}

	void EmitCharacterQueryPlayerControlStateMessage()
	{
		engine::CharacterQueryPlayerControlStateMessage message;
	}

	void EmitActivateRenderingMessage()
	{
		engine::ActivateRenderingMessage message(false);
	}

	void EmitGetLODStateAIMsg()
	{
		proto::GetLODStateAIMsg message;
	}

	void EmitFreezeAIMsg()
	{
		proto::FreezeAIMsg message;
	}

	void EmitInstantFreezeAIMsg()
	{
		proto::InstantFreezeAIMsg message;
	}

	void EmitThawAIMsg()
	{
		proto::ThawAIMsg message;
	}

	void EmitGetGameObjectLODAIMsg()
	{
		proto::GetGameObjectLODAIMsg message;
	}

	void EmitGetSustainedGameObjectLODAIMsg()
	{
		proto::GetSustainedGameObjectLODAIMsg message;
	}

	void EmitCanBeInSquadSquadMessage()
	{
		proto::CanBeInSquadSquadMessage message;
	}

	void EmitIsSquadSquadMessage()
	{
		proto::IsSquadSquadMessage message;
	}

	void EmitGoUnderGroundStatChangeMessage()
	{
		proto::GoUnderGroundStatChangeMessage message;
	}

	void EmitComeOutsideStateChangeMessage()
	{
		proto::ComeOutsideStateChangeMessage message;
	}

	void EmitInstantGoUndergroundStateChangeMessage()
	{
		proto::InstantGoUndergroundStateChangeMessage message;
	}

	void EmitInstantComeOutsideStateChangeMessage()
	{
		proto::InstantComeOutsideStateChangeMessage message;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1005D690
// FUNCTION: ENGINE 0x1005DBF0
// FUNCTION: ENGINE 0x1005E850
// FUNCTION: ENGINE 0x1005E8E0
// FUNCTION: ENGINE 0x1009E2A0
// FUNCTION: ENGINE 0x10102480
// FUNCTION: ENGINE 0x101ED840
// FUNCTION: ENGINE 0x101FA3B0
// FUNCTION: ENGINE 0x1020C210
// FUNCTION: ENGINE 0x103A5600
// FUNCTION: ENGINE 0x103A5640
// FUNCTION: ENGINE 0x103A5650
// FUNCTION: ENGINE 0x103A5680
// FUNCTION: ENGINE 0x103A5690
// FUNCTION: ENGINE 0x103A56C0
// FUNCTION: ENGINE 0x103A56D0
// FUNCTION: ENGINE 0x103A5700
// FUNCTION: ENGINE 0x103A5710
// FUNCTION: ENGINE 0x103A5740
// FUNCTION: ENGINE 0x103A57F0
// FUNCTION: ENGINE 0x103A5820
// FUNCTION: ENGINE 0x103A5850
// FUNCTION: ENGINE 0x103A5880
// FUNCTION: ENGINE 0x103A58B0
// FUNCTION: ENGINE 0x103B7950
// FUNCTION: ENGINE 0x103B7990
// FUNCTION: ENGINE 0x103B7A80
// FUNCTION: ENGINE 0x103B7AB0
// FUNCTION: ENGINE 0x103B7AC0
// FUNCTION: ENGINE 0x103B7B30
// FUNCTION: ENGINE 0x103B7B40
// FUNCTION: ENGINE 0x103B7B70
// FUNCTION: ENGINE 0x103B7B80
// FUNCTION: ENGINE 0x103B7BE0
// FUNCTION: ENGINE 0x103B7BF0
// FUNCTION: ENGINE 0x103B7C50
// FUNCTION: ENGINE 0x103B7C60
// FUNCTION: ENGINE 0x103B7CA0
// FUNCTION: ENGINE 0x103B7CB0
// FUNCTION: ENGINE 0x103B7CF0
// FUNCTION: ENGINE 0x103B7D00
// FUNCTION: ENGINE 0x103B7D60
// FUNCTION: ENGINE 0x103B7D70
// FUNCTION: ENGINE 0x103B7DC0
// FUNCTION: ENGINE 0x103B7DD0
// FUNCTION: ENGINE 0x103B7E00
// FUNCTION: ENGINE 0x103B7E20
// FUNCTION: ENGINE 0x103B7E50
// FUNCTION: ENGINE 0x103B7E60
// FUNCTION: ENGINE 0x103B7E90
// FUNCTION: ENGINE 0x103B7EA0
// FUNCTION: ENGINE 0x103B7ED0
// FUNCTION: ENGINE 0x103B7EE0
// FUNCTION: ENGINE 0x103B7F10
// FUNCTION: ENGINE 0x103B7F20
// FUNCTION: ENGINE 0x103B7F50
// FUNCTION: ENGINE 0x103B7F60
// FUNCTION: ENGINE 0x103B7F90
// FUNCTION: ENGINE 0x103B7FA0
// FUNCTION: ENGINE 0x103B7FD0
// FUNCTION: ENGINE 0x103B7FE0
// FUNCTION: ENGINE 0x103B8010
// FUNCTION: ENGINE 0x103B8020
// FUNCTION: ENGINE 0x103B8050
// FUNCTION: ENGINE 0x103B8070
// FUNCTION: ENGINE 0x103B80A0
// FUNCTION: ENGINE 0x103B80B0
// FUNCTION: ENGINE 0x103B80E0
// FUNCTION: ENGINE 0x103B80F0
// FUNCTION: ENGINE 0x103B8120
// FUNCTION: ENGINE 0x103B8130
// FUNCTION: ENGINE 0x103B8160
// FUNCTION: ENGINE 0x103BA190
// FUNCTION: ENGINE 0x103BA1C0
// FUNCTION: ENGINE 0x103BA1F0
// FUNCTION: ENGINE 0x103BA220
// FUNCTION: ENGINE 0x103BA250
// FUNCTION: ENGINE 0x103BA280
// FUNCTION: ENGINE 0x103BA2B0
// FUNCTION: ENGINE 0x103BA2E0
// FUNCTION: ENGINE 0x103BA310
// FUNCTION: ENGINE 0x103BA340
// FUNCTION: ENGINE 0x103BA370
// FUNCTION: ENGINE 0x103BA3A0
// FUNCTION: ENGINE 0x103BA3D0
// FUNCTION: ENGINE 0x103BA400
// FUNCTION: ENGINE 0x103BA430
// FUNCTION: ENGINE 0x103BA460
// FUNCTION: ENGINE 0x103BA490
// FUNCTION: ENGINE 0x103BA4C0
// FUNCTION: ENGINE 0x103BA4F0
// FUNCTION: ENGINE 0x103BA520
// FUNCTION: ENGINE 0x103BA550
// FUNCTION: ENGINE 0x103BA580
// FUNCTION: ENGINE 0x103BA5B0
// FUNCTION: ENGINE 0x103BA5E0
