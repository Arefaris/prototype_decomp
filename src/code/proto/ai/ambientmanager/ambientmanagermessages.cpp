#include "code/proto/ai/ambientmanager/ambientmanagermessages.h"

namespace proto
{
	// FUNCTION: ENGINE 0x10420680
	CreateVehicleMessage::CreateVehicleMessage(void* newArgument) : AmbientMessage(5), argument(newArgument)
	{
	}

	// FUNCTION: ENGINE 0x104206C0
	CreatePedMessage::CreatePedMessage(void* newArgument, NPCType* newType) :
		AmbientMessage(6), argument(newArgument), type(newType)
	{
	}

	// FUNCTION: ENGINE 0x104289C0
	VehicleMovementBehaviourActiveMessage::VehicleMovementBehaviourActiveMessage() :
		MovementMessage(0x3b), active(false)
	{
	}

	// FUNCTION: ENGINE 0x10428A00
	SetVehiclePatrolHeightOffsetMessage::SetVehiclePatrolHeightOffsetMessage(float newOffset, bool newFlag) :
		MovementMessage(0x3c), offset(newOffset), flag(newFlag)
	{
	}

	// FUNCTION: ENGINE 0x1042D320
	SetLODDestinationAIMsg::SetLODDestinationAIMsg(const math::Vector& newDestination) : LODAIMessage(0x15)
	{
		destination.x = newDestination.x;
		destination.y = newDestination.y;
		destination.z = newDestination.z;
	}

	// FUNCTION: ENGINE 0x1042D370
	HasLODArrivedAIMsg::HasLODArrivedAIMsg() : LODAIMessage(0x16), arrived(true)
	{
	}

	// FUNCTION: ENGINE 0x1042EE20
	ForceUpDatePerceptionMessage::ForceUpDatePerceptionMessage() : PerceptionMessage(0x11)
	{
	}

	// FUNCTION: ENGINE 0x1042EE60
	SetAmbientControlledAIMsg::SetAmbientControlledAIMsg(bool newControlled) : AIMessage(0x11), controlled(newControlled)
	{
	}

	// FUNCTION: ENGINE 0x1042EEA0
	SetTurnedOffMovementMessage::SetTurnedOffMovementMessage(bool newTurnedOff) :
		MovementMessage(0x46), turnedOff(newTurnedOff)
	{
	}

	// FUNCTION: ENGINE 0x104305D0
	GetIntersectionStateMessage::GetIntersectionStateMessage(int newDirection) :
		AmbientMessage(0), state(-1), direction(newDirection), unknown14(0), unknown18(0.0f), unknown1C(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x10432D40
	GetIntersectionBehaviourMessage::GetIntersectionBehaviourMessage() : AmbientMessage(1), behaviour(0)
	{
	}

	// FUNCTION: ENGINE 0x10432D80
	GetAlertInfoMessage::GetAlertInfoMessage() : AmbientMessage(0x14)
	{
	}

}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104206B0
// FUNCTION: ENGINE 0x10420700
// FUNCTION: ENGINE 0x104208E0
// FUNCTION: ENGINE 0x10420910
// FUNCTION: ENGINE 0x104289F0
// FUNCTION: ENGINE 0x10428A40
// FUNCTION: ENGINE 0x104290A0
// FUNCTION: ENGINE 0x104290D0
// FUNCTION: ENGINE 0x1042D360
// FUNCTION: ENGINE 0x1042D3A0
// FUNCTION: ENGINE 0x1042D5A0
// FUNCTION: ENGINE 0x1042D5D0
// FUNCTION: ENGINE 0x1042EE50
// FUNCTION: ENGINE 0x1042EE90
// FUNCTION: ENGINE 0x1042EED0
// FUNCTION: ENGINE 0x1042F100
// FUNCTION: ENGINE 0x1042F130
// FUNCTION: ENGINE 0x1042F160
// FUNCTION: ENGINE 0x10430620
// FUNCTION: ENGINE 0x104309D0
// FUNCTION: ENGINE 0x10432D70
// FUNCTION: ENGINE 0x10432DC0
// FUNCTION: ENGINE 0x10434100
// FUNCTION: ENGINE 0x10434130
