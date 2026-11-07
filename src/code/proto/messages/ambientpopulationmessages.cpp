#include "code/proto/messages/ambientpopulationmessages.h"

// A function that constructs each message with the expansion of inline functions off: the compiler keeps the out-of-line
// copy of the constructor and of the destructor the engine has too
#pragma inline_depth(0)
namespace
{
	void EmitSpawnVehicleMessage(const math::Vector& vector)
	{
		proto::SpawnVehicleMessage message(vector, vector, vector, 0, 0, false);
	}

	void EmitGetVehiclePhysicsLODMessage(engine::GameObjectHandle handle)
	{
		proto::GetVehiclePhysicsLODMessage message;
	}

	void EmitSetPhysicsLODHighMessage(engine::GameObjectHandle handle)
	{
		proto::SetPhysicsLODHighMessage message(false);
	}

	void EmitIsPhysicsDownGradeAbleMessage(engine::GameObjectHandle handle)
	{
		proto::IsPhysicsDownGradeAbleMessage message;
	}

	void EmitSetAsParkedCarMessage(engine::GameObjectHandle handle)
	{
		proto::SetAsParkedCarMessage message;
	}

	void EmitResetSensesInfoMessage(engine::GameObjectHandle handle)
	{
		proto::ResetSensesInfoMessage message;
	}

	void EmitWorldGetAmbientPackagesMessage(engine::GameObjectHandle handle)
	{
		proto::WorldGetAmbientPackagesMessage message;
	}

	void EmitThreatBallInitializeMessage(const math::Sphere& sphere, const math::Vector& vector,
		core::Name<core::CaseSensitiveKey> name, engine::GameObjectHandle handle)
	{
		proto::ThreatBallInitializeMessage message(sphere, vector, 0.0f, name, handle, 0, 0);
	}

	void EmitThreatInitializeMessage(core::Name<core::CaseSensitiveKey> name)
	{
		proto::ThreatInitializeMessage message(0.0f, name, engine::HandleBase(), engine::HandleBase(), 0, 0);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10407F80
// FUNCTION: ENGINE 0x10407F90
// FUNCTION: ENGINE 0x10407EE0
// FUNCTION: ENGINE 0x10408000
// FUNCTION: ENGINE 0x10408010
// FUNCTION: ENGINE 0x10408040
// FUNCTION: ENGINE 0x104095C0
// FUNCTION: ENGINE 0x10409650
// FUNCTION: ENGINE 0x10409660
// FUNCTION: ENGINE 0x10409690
// FUNCTION: ENGINE 0x104096A0
// FUNCTION: ENGINE 0x104096D0
// FUNCTION: ENGINE 0x104096E0
// FUNCTION: ENGINE 0x10409710
// FUNCTION: ENGINE 0x10409840
// FUNCTION: ENGINE 0x10409870
// FUNCTION: ENGINE 0x1040C670
// FUNCTION: ENGINE 0x1040C6A0
// FUNCTION: ENGINE 0x1040C6E0
// FUNCTION: ENGINE 0x1040C6F0
// FUNCTION: ENGINE 0x1040C720
// FUNCTION: ENGINE 0x1040C750
// FUNCTION: ENGINE 0x1040C7B0
// FUNCTION: ENGINE 0x1040C7E0
// FUNCTION: ENGINE 0x1040C820
// FUNCTION: ENGINE 0x10411A10
// FUNCTION: ENGINE 0x10411A40
