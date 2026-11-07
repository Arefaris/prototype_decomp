#include "code/proto/ai/ambientmanager/ambientmanagermessages.h"

// A function that constructs each message with the expansion of inline functions off: the compiler keeps the out-of-line
// copy of the constructor and of the destructor the engine has too (the spawners and behaviours that send the messages
// inline them)
#pragma inline_depth(0)
namespace
{
	void EmitCreateVehicleMessage()
	{
		proto::CreateVehicleMessage message(0);
	}

	void EmitCreatePedMessage()
	{
		proto::CreatePedMessage message(0, 0);
	}

	void EmitVehicleMovementBehaviourActiveMessage()
	{
		proto::VehicleMovementBehaviourActiveMessage message;
	}

	void EmitSetVehiclePatrolHeightOffsetMessage()
	{
		proto::SetVehiclePatrolHeightOffsetMessage message(0.0f, false);
	}

	void EmitSetLODDestinationAIMsg(const math::Vector& destination)
	{
		proto::SetLODDestinationAIMsg message(destination);
	}

	void EmitHasLODArrivedAIMsg()
	{
		proto::HasLODArrivedAIMsg message;
	}

	void EmitForceUpDatePerceptionMessage()
	{
		proto::ForceUpDatePerceptionMessage message;
	}

	void EmitSetAmbientControlledAIMsg()
	{
		proto::SetAmbientControlledAIMsg message(false);
	}

	void EmitSetTurnedOffMovementMessage()
	{
		proto::SetTurnedOffMovementMessage message(false);
	}

	void EmitGetIntersectionStateMessage()
	{
		proto::GetIntersectionStateMessage message(0);
	}

	void EmitGetIntersectionBehaviourMessage()
	{
		proto::GetIntersectionBehaviourMessage message;
	}

	void EmitGetAlertInfoMessage()
	{
		proto::GetAlertInfoMessage message;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10420680
// FUNCTION: ENGINE 0x104206B0
// FUNCTION: ENGINE 0x104206C0
// FUNCTION: ENGINE 0x10420700
// FUNCTION: ENGINE 0x104208E0
// FUNCTION: ENGINE 0x10420910
// FUNCTION: ENGINE 0x104289C0
// FUNCTION: ENGINE 0x104289F0
// FUNCTION: ENGINE 0x10428A00
// FUNCTION: ENGINE 0x10428A40
// FUNCTION: ENGINE 0x104290A0
// FUNCTION: ENGINE 0x104290D0
// FUNCTION: ENGINE 0x1042D320
// FUNCTION: ENGINE 0x1042D360
// FUNCTION: ENGINE 0x1042D370
// FUNCTION: ENGINE 0x1042D3A0
// FUNCTION: ENGINE 0x1042D5A0
// FUNCTION: ENGINE 0x1042D5D0
// FUNCTION: ENGINE 0x1042EE20
// FUNCTION: ENGINE 0x1042EE50
// FUNCTION: ENGINE 0x1042EE60
// FUNCTION: ENGINE 0x1042EE90
// FUNCTION: ENGINE 0x1042EEA0
// FUNCTION: ENGINE 0x1042EED0
// FUNCTION: ENGINE 0x1042F100
// FUNCTION: ENGINE 0x1042F130
// FUNCTION: ENGINE 0x1042F160
// FUNCTION: ENGINE 0x104305D0
// FUNCTION: ENGINE 0x10430620
// FUNCTION: ENGINE 0x104309D0
// FUNCTION: ENGINE 0x10432D40
// FUNCTION: ENGINE 0x10432D70
// FUNCTION: ENGINE 0x10432D80
// FUNCTION: ENGINE 0x10432DC0
// FUNCTION: ENGINE 0x10434100
// FUNCTION: ENGINE 0x10434130
