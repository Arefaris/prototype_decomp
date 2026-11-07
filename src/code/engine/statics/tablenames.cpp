// Name tables that the engine's static initialisers construct in translation units whose code is not reconstructed (unit name guess).
#include "code/core/name.h"

namespace engine
{
	namespace camera
	{
		extern const float gThree;
	}

	core::Name<core::CaseSensitiveKey> gInputNames[32] =
	{
		core::Name<core::CaseSensitiveKey>("Attack", 0),
		core::Name<core::CaseSensitiveKey>("Special", 0),
		core::Name<core::CaseSensitiveKey>("Action", 0),
		core::Name<core::CaseSensitiveKey>("Jump", 0),
		core::Name<core::CaseSensitiveKey>("Run", 0),
		core::Name<core::CaseSensitiveKey>("Target", 0),
		core::Name<core::CaseSensitiveKey>("Taunt", 0),
		core::Name<core::CaseSensitiveKey>("MovementAxis", 0),
		core::Name<core::CaseSensitiveKey>("TargetAxis", 0),
		core::Name<core::CaseSensitiveKey>("LockOnTargetAxis", 0),
		core::Name<core::CaseSensitiveKey>("DpadUp", 0),
		core::Name<core::CaseSensitiveKey>("DpadDown", 0),
		core::Name<core::CaseSensitiveKey>("DpadLeft", 0),
		core::Name<core::CaseSensitiveKey>("DpadRight", 0),
		core::Name<core::CaseSensitiveKey>("LeftStickTrigger", 0),
		core::Name<core::CaseSensitiveKey>("RightStickTrigger", 0),
		core::Name<core::CaseSensitiveKey>("LeftBumper", 0),
		core::Name<core::CaseSensitiveKey>("RightBumper", 0),
		core::Name<core::CaseSensitiveKey>("Walk", 0),
		core::Name<core::CaseSensitiveKey>("LockOnTarget", 0),
		core::Name<core::CaseSensitiveKey>("ClawsHotKey", 0),
		core::Name<core::CaseSensitiveKey>("HammerFistHotKey", 0),
		core::Name<core::CaseSensitiveKey>("MuscleMassHotKey", 0),
		core::Name<core::CaseSensitiveKey>("WhipfistHotKey", 0),
		core::Name<core::CaseSensitiveKey>("BladeHotKey", 0),
		core::Name<core::CaseSensitiveKey>("ThermalVisionHotKey", 0),
		core::Name<core::CaseSensitiveKey>("InfectedVisionHotKey", 0),
		core::Name<core::CaseSensitiveKey>("ArmourHotKey", 0),
		core::Name<core::CaseSensitiveKey>("SheildHotKey", 0),
		core::Name<core::CaseSensitiveKey>("DisguiseHotKey", 0),
		core::Name<core::CaseSensitiveKey>("AlexHotKey", 0)
	};

	core::Name<core::CaseSensitiveKey> gAxisNames[20] =
	{
		core::Name<core::CaseSensitiveKey>("ForwardMovement", 0),
		core::Name<core::CaseSensitiveKey>("Steering", 0),
		core::Name<core::CaseSensitiveKey>("Rising", 0),
		core::Name<core::CaseSensitiveKey>("MotionX", 0),
		core::Name<core::CaseSensitiveKey>("MotionY", 0),
		core::Name<core::CaseSensitiveKey>("TargetX", 0),
		core::Name<core::CaseSensitiveKey>("TargetY", 0),
		core::Name<core::CaseSensitiveKey>("LockOnTargetX", 0),
		core::Name<core::CaseSensitiveKey>("LockOnTargetY", 0),
		core::Name<core::CaseSensitiveKey>("FacingPitch", 0),
		core::Name<core::CaseSensitiveKey>("FacingYaw", 0),
		core::Name<core::CaseSensitiveKey>("TankSteering", 0),
		core::Name<core::CaseSensitiveKey>("TankAcceleration", 0),
		core::Name<core::CaseSensitiveKey>("TankAccelerationSecondary", 0),
		core::Name<core::CaseSensitiveKey>("HelicopterForwardMovement", 0),
		core::Name<core::CaseSensitiveKey>("HelicopterAISteering", 0),
		core::Name<core::CaseSensitiveKey>("HelicopterSteering", 0),
		core::Name<core::CaseSensitiveKey>("HelicopterStrafe", 0),
		core::Name<core::CaseSensitiveKey>("HelicopterThrottle", 0)
	};

	core::Name<core::CaseSensitiveKey> gLegNames[3] =
	{
		core::Name<core::CaseSensitiveKey>("leg_right", 0),
		core::Name<core::CaseSensitiveKey>("leg_left", 0),
		core::Name<core::CaseSensitiveKey>(0, 1)
	};

	struct GroundSpikeNames
	{
		core::Name<core::CaseSensitiveKey> spike;
		core::Name<core::CaseSensitiveKey> superSpike;
		core::Name<core::CaseSensitiveKey> shard;
		float radius;
		float height;
	};

	GroundSpikeNames gGroundSpikeNames[3] =
	{
		{ core::Name<core::CaseSensitiveKey>("groundSpikeSmall", 0), core::Name<core::CaseSensitiveKey>("GroundSpikeShardLarge", 0), core::Name<core::CaseSensitiveKey>("GroundSpikeShardSmall", 0), 5.0f, camera::gThree },
		{ core::Name<core::CaseSensitiveKey>("groundSpikeMedium", 0), core::Name<core::CaseSensitiveKey>("GroundSpikeMediumForSuper", 0), core::Name<core::CaseSensitiveKey>("GroundSpikeShardMedium", 0), 5.5f, 4.5f },
		{ core::Name<core::CaseSensitiveKey>("groundSpikeLarge", 0), core::Name<core::CaseSensitiveKey>("GroundSpikeLargeForSuper", 0), core::Name<core::CaseSensitiveKey>("GroundSpikeShardLarge", 0), 4.5f, 5.0f }
	};
}

// The dynamic initialisers and atexit stubs of the unit's globals:
// FUNCTION: ENGINE 0x10D4C7E0
// FUNCTION: ENGINE 0x10D4CA90
// FUNCTION: ENGINE 0x10D4CD60
// FUNCTION: ENGINE 0x10D4F740
// FUNCTION: ENGINE 0x10D80FF0
// FUNCTION: ENGINE 0x10D81000
// FUNCTION: ENGINE 0x10D810A0
// FUNCTION: ENGINE 0x10D81960
