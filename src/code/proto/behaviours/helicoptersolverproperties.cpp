#include "code/proto/behaviours/helicoptersolverproperties.h"
#include "code/core/refptr.h"
#include "code/engine/driving/carattributes.h"
#include "code/ravenphysics/massproperties.h"

namespace engine
{
	namespace driving
	{
		// 0x10D94F78 (symbols.txt): 0.0f in the pooled constants
		extern const float gZero;
	}
}

namespace ravenphysics
{
	// 0x10D977E4 (symbols.txt): 1000.0f in the pooled constants (name guess)
	extern const float gDefaultMaxForce;
}

namespace proto
{
#define PROTO_NAME_OFFSET(type, member) 	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	typedef HelicopterSolverGenericProperties Generic;
	typedef HelicopterSolverProperties Solver;

	// FUNCTION: ENGINE 0x1031E3E0
	Generic::CameraParams::CameraParams()
	{
		maxElevationAngle = 0.0f;
		minElevationAngle = 0.0f;
		elevationVelocity = 0.0f;
		rollPercentage = 0.0f;
		rollTime = 0.0f;
		heightOffset = 0.0f;
	}

	// FUNCTION: ENGINE 0x1031E410
	void Generic::CameraParams::SetMaxElevationAngleDegrees(float degrees)
	{
		maxElevationAngle = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x1031E430
	float Generic::CameraParams::GetMaxElevationAngleDegrees() const
	{
		return maxElevationAngle * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031E440
	float Generic::CameraParams::GetMaxElevationAngle() const
	{
		return maxElevationAngle;
	}

	// FUNCTION: ENGINE 0x1031E450
	void Generic::CameraParams::SetMinElevationAngleDegrees(float degrees)
	{
		minElevationAngle = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x1031E470
	float Generic::CameraParams::GetMinElevationAngleDegrees() const
	{
		return minElevationAngle * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031E480
	float Generic::CameraParams::GetMinElevationAngle() const
	{
		return minElevationAngle;
	}

	// FUNCTION: ENGINE 0x1031E490
	void Generic::CameraParams::SetElevationVelocityDegrees(float degrees)
	{
		elevationVelocity = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x1031E4B0
	float Generic::CameraParams::GetElevationVelocityDegrees() const
	{
		return elevationVelocity * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031E4C0
	float Generic::CameraParams::GetElevationVelocity() const
	{
		return elevationVelocity;
	}

	// FUNCTION: ENGINE 0x1031E4D0
	float Generic::CameraParams::GetRollPercentage() const
	{
		return rollPercentage;
	}

	// FUNCTION: ENGINE 0x1031E4E0
	float Generic::CameraParams::GetRollTime() const
	{
		return rollTime;
	}

	// FUNCTION: ENGINE 0x1031E4F0
	float Generic::CameraParams::GetHeightOffset() const
	{
		return heightOffset;
	}

	// FUNCTION: ENGINE 0x1031E500
	Generic::EffectsParams::EffectsParams()
	{
		float one = engine::driving::gOne;
		float fifty = gFifty;
		washEffectFrequency = one;
		bloodtoxSpawnFrequency = one;
		maxWashEffectHeight = fifty;
		rotorCollisionEffectFrequency = 0.0f;
		offsetForRaycast = 0.0f;
	}

	// FUNCTION: ENGINE 0x1031E550
	float Generic::EffectsParams::GetWashEffectFrequency() const
	{
		return washEffectFrequency;
	}

	// FUNCTION: ENGINE 0x1031E560
	float Generic::EffectsParams::GetMaxWashEffectHeight() const
	{
		return maxWashEffectHeight;
	}

	// FUNCTION: ENGINE 0x1031E570
	float Generic::EffectsParams::GetBloodtoxSpawnFrequency() const
	{
		return bloodtoxSpawnFrequency;
	}

	// FUNCTION: ENGINE 0x1031E580
	float Generic::EffectsParams::GetRotorCollisionEffectFrequency() const
	{
		return rotorCollisionEffectFrequency;
	}

	// FUNCTION: ENGINE 0x1031E590
	float Generic::EffectsParams::GetOffsetForRaycast() const
	{
		return offsetForRaycast;
	}

	// FUNCTION: ENGINE 0x1031E5A0
	bool Generic::GetIsJet() const
	{
		return isJet;
	}

	// FUNCTION: ENGINE 0x1031E5B0
	// NONMATCHING: the compiler puts the counter's increment before the last store of the vector, 80 %
#ifdef NONMATCHING
	void Generic::SetCenterOfMass(const math::Vector* position)
	{
		centerOfMass.x = position->x;
		centerOfMass.y = position->y;
		centerOfMass.z = position->z;
		centerOfMassVersion++;
	}
#endif

	// FUNCTION: ENGINE 0x1031E5F0
	const math::Vector* Generic::GetCenterOfMass() const
	{
		return &centerOfMass;
	}

	// FUNCTION: ENGINE 0x1031E600
	int Generic::GetCenterOfMassVersion() const
	{
		return centerOfMassVersion;
	}

	// FUNCTION: ENGINE 0x1031E610
	bool Generic::GetCenterOfMassDraw() const
	{
		return centerOfMassDraw;
	}

	// FUNCTION: ENGINE 0x1031E620
	float Generic::GetForwardDeadzoneSizeAtMaxStrafe() const
	{
		return forwardDeadzoneSizeAtMaxStrafe;
	}

	// FUNCTION: ENGINE 0x1031E630
	float Generic::GetStrafeDeadzoneSizeAtMaxForward() const
	{
		return strafeDeadzoneSizeAtMaxForward;
	}

	// FUNCTION: ENGINE 0x1031E640
	void Generic::SetInertiaScaleXX(float scale)
	{
		inertiaScaleVersion++;
		inertiaScale.xx = scale;
	}

	// FUNCTION: ENGINE 0x1031E660
	void Generic::SetInertiaScaleYY(float scale)
	{
		inertiaScaleVersion++;
		inertiaScale.yy = scale;
	}

	// FUNCTION: ENGINE 0x1031E680
	void Generic::SetInertiaScaleZZ(float scale)
	{
		inertiaScaleVersion++;
		inertiaScale.zz = scale;
	}

	// FUNCTION: ENGINE 0x1031E6A0
	void Generic::SetInertiaScaleXY(float scale)
	{
		inertiaScaleVersion++;
		inertiaScale.xy = scale;
	}

	// FUNCTION: ENGINE 0x1031E6C0
	void Generic::SetInertiaScaleXZ(float scale)
	{
		inertiaScaleVersion++;
		inertiaScale.xz = scale;
	}

	// FUNCTION: ENGINE 0x1031E6E0
	void Generic::SetInertiaScaleYZ(float scale)
	{
		inertiaScaleVersion++;
		inertiaScale.yz = scale;
	}

	// FUNCTION: ENGINE 0x1031E700
	float Generic::GetInertiaScaleXX() const
	{
		return inertiaScale.xx;
	}

	// FUNCTION: ENGINE 0x1031E710
	float Generic::GetInertiaScaleYY() const
	{
		return inertiaScale.yy;
	}

	// FUNCTION: ENGINE 0x1031E720
	float Generic::GetInertiaScaleZZ() const
	{
		return inertiaScale.zz;
	}

	// FUNCTION: ENGINE 0x1031E730
	float Generic::GetInertiaScaleXY() const
	{
		return inertiaScale.xy;
	}

	// FUNCTION: ENGINE 0x1031E740
	float Generic::GetInertiaScaleXZ() const
	{
		return inertiaScale.xz;
	}

	// FUNCTION: ENGINE 0x1031E750
	float Generic::GetInertiaScaleYZ() const
	{
		return inertiaScale.yz;
	}

	// FUNCTION: ENGINE 0x1031E760
	const math::SymmetricMatrix* Generic::GetInertiaScales() const
	{
		return &inertiaScale;
	}

	// FUNCTION: ENGINE 0x1031E770
	int Generic::GetInertiaScaleVersion() const
	{
		return inertiaScaleVersion;
	}

	// FUNCTION: ENGINE 0x1031E780
	ravenphysics::MassProperties* Generic::GetRestingMassProperties() const
	{
		return restingMassProperties;
	}

	// FUNCTION: ENGINE 0x1031E790
	Generic::HealthParams::HealthParams()
	{
		damagePerSpeed = 0.0f;
		rotorDamageTimeTillZeroHealth = 4.0f;
	}

	// FUNCTION: ENGINE 0x1031E7B0
	void Generic::HealthParams::SetDamagePerKph(float damagePerKph)
	{
		damagePerSpeed = damagePerKph * 0.27777779f;
	}

	// FUNCTION: ENGINE 0x1031E7D0
	float Generic::HealthParams::GetDamagePerKph() const
	{
		return damagePerSpeed * 3.6f;
	}

	// FUNCTION: ENGINE 0x1031E7E0
	float Generic::HealthParams::GetDamagePerSpeed() const
	{
		return damagePerSpeed;
	}

	// FUNCTION: ENGINE 0x1031E7F0
	float Generic::HealthParams::GetRotorDamageTimeTillZeroHealth() const
	{
		return rotorDamageTimeTillZeroHealth;
	}

	// FUNCTION: ENGINE 0x1031E800
	Generic::PowerParams::PowerParams()
	{
		powerUpTime = 0.0f;
		powerDownTime = 0.0f;
		holdLastIntentionTime = 0.0f;
		timeOnGroundForPhysicsOff = engine::driving::gHalf;
		timeInAirToClearTimeOnGround = 0.1f;
		timeOnGroundForPowerDown = gTen;
	}

	// FUNCTION: ENGINE 0x1031E850
	float Generic::PowerParams::GetPowerUpTime() const
	{
		return powerUpTime;
	}

	// FUNCTION: ENGINE 0x1031E860
	float Generic::PowerParams::GetPowerDownTime() const
	{
		return powerDownTime;
	}

	// FUNCTION: ENGINE 0x1031E870
	float Generic::PowerParams::GetHoldLastIntentionTime() const
	{
		return holdLastIntentionTime;
	}

	// FUNCTION: ENGINE 0x1031E880
	float Generic::PowerParams::GetTimeOnGroundForPhysicsOff() const
	{
		return timeOnGroundForPhysicsOff;
	}

	// FUNCTION: ENGINE 0x1031E890
	float Generic::PowerParams::GetTimeInAirToClearTimeOnGround() const
	{
		return timeInAirToClearTimeOnGround;
	}

	// FUNCTION: ENGINE 0x1031E8A0
	float Generic::PowerParams::GetTimeOnGroundForPowerDown() const
	{
		return timeOnGroundForPowerDown;
	}

	// FUNCTION: ENGINE 0x1031E8B0
	Generic::RotorParams::RotorParams()
	{
		maxPitchAngle = 0.0f;
		timeToMaxPitch = 0.0f;
		maxRollAngle = 0.0f;
		timeToMaxRoll = 0.0f;
		invertPitch = false;
		invertRoll = false;
	}

	// FUNCTION: ENGINE 0x1031E8E0
	void Generic::RotorParams::SetMaxPitchAngleDegrees(float degrees)
	{
		maxPitchAngle = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x1031E900
	float Generic::RotorParams::GetMaxPitchAngleDegrees() const
	{
		return maxPitchAngle * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031E910
	float Generic::RotorParams::GetMaxPitchAngle() const
	{
		return maxPitchAngle;
	}

	// FUNCTION: ENGINE 0x1031E920
	float Generic::RotorParams::GetTimeToMaxPitch() const
	{
		return timeToMaxPitch;
	}

	// FUNCTION: ENGINE 0x1031E930
	void Generic::RotorParams::SetMaxRollAngleDegrees(float degrees)
	{
		maxRollAngle = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x1031E950
	float Generic::RotorParams::GetMaxRollAngleDegrees() const
	{
		return maxRollAngle * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031E960
	float Generic::RotorParams::GetMaxRollAngle() const
	{
		return maxRollAngle;
	}

	// FUNCTION: ENGINE 0x1031E970
	float Generic::RotorParams::GetTimeToMaxRoll() const
	{
		return timeToMaxRoll;
	}

	// FUNCTION: ENGINE 0x1031E980
	bool Generic::RotorParams::GetInvertPitch() const
	{
		return invertPitch;
	}

	// FUNCTION: ENGINE 0x1031E990
	bool Generic::RotorParams::GetInvertRoll() const
	{
		return invertRoll;
	}

	// FUNCTION: ENGINE 0x1031E9A0
	const core::Name<core::CaseSensitiveKey>* Generic::SoundParams::GetPatchName() const
	{
		return &patchName;
	}

	// FUNCTION: ENGINE 0x1031E9B0
	const core::Name<core::CaseSensitiveKey>* Generic::SoundParams::GetStartupTriggerName() const
	{
		return &startupTriggerName;
	}

	// FUNCTION: ENGINE 0x1031E9C0
	const core::Name<core::CaseSensitiveKey>* Generic::SoundParams::GetThrottleControlName() const
	{
		return &throttleControlName;
	}

	// FUNCTION: ENGINE 0x1031E9D0
	const core::Name<core::CaseSensitiveKey>* Generic::SoundParams::GetVelocityControlName() const
	{
		return &velocityControlName;
	}

	// FUNCTION: ENGINE 0x1031E9E0
	const core::Name<core::CaseSensitiveKey>* Generic::SoundParams::GetWindDownTriggerName() const
	{
		return &windDownTriggerName;
	}

	// FUNCTION: ENGINE 0x1031E9F0
	Solver::AIParams::AIParams()
	{
		useDrag = true;
		intentionSpeed = false;
	}

	// FUNCTION: ENGINE 0x1031EA00
	bool Solver::AIParams::GetUseDrag() const
	{
		return useDrag;
	}

	// FUNCTION: ENGINE 0x1031EA10
	bool Solver::AIParams::GetIntentionSpeed() const
	{
		return intentionSpeed;
	}

	// FUNCTION: ENGINE 0x1031EA20
	Solver::HoverParams::HoverParams()
	{
		float half = engine::driving::gHalf;
		float one = engine::driving::gOne;
		throttleForHover = half;
		throttleHoverDeadzoneNoTarget = half;
		throttleHoverDeadzoneTarget = half;
		throttleForHoverPS3 = half;
		throttleHoverDeadzoneNoTargetPS3 = half;
		throttleHoverDeadzoneTargetPS3 = half;
		hoverOffsetAtMaxForwardSpeed = 0.0f;
		hoverOffsetAtMaxForwardAcceleration = 0.0f;
		hoverHeight = 0.0f;
		hoverForce = 0.0f;
		heightForHorizontalControl = one;
		driftAmount.x = 0.0f;
		driftAmount.y = 0.0f;
		driftAmount.z = 0.0f;
		timeToDriftMax = 0.0f;
		timeToDriftMin = 0.0f;
		timeToStartDrift = choreo::gMinusOne;
	}

	// FUNCTION: ENGINE 0x1031EAB0
	float Solver::HoverParams::GetThrottleForHover() const
	{
		return throttleForHover;
	}

	// FUNCTION: ENGINE 0x1031EAC0
	float Solver::HoverParams::GetHoverOffsetAtMaxForwardSpeed() const
	{
		return hoverOffsetAtMaxForwardSpeed;
	}

	// FUNCTION: ENGINE 0x1031EAD0
	float Solver::HoverParams::GetHoverOffsetAtMaxForwardAcceleration() const
	{
		return hoverOffsetAtMaxForwardAcceleration;
	}

	// FUNCTION: ENGINE 0x1031EAE0
	float Solver::HoverParams::GetHoverHeight() const
	{
		return hoverHeight;
	}

	// FUNCTION: ENGINE 0x1031EAF0
	float Solver::HoverParams::GetHoverForce() const
	{
		return hoverForce;
	}

	// FUNCTION: ENGINE 0x1031EB00
	float Solver::HoverParams::GetHeightForHorizontalControl() const
	{
		return heightForHorizontalControl;
	}

	// FUNCTION: ENGINE 0x1031EB10
	const math::Vector* Solver::HoverParams::GetDriftAmount() const
	{
		return &driftAmount;
	}

	// FUNCTION: ENGINE 0x1031EB20
	float Solver::HoverParams::GetTimeToDriftMax() const
	{
		return timeToDriftMax;
	}

	// FUNCTION: ENGINE 0x1031EB30
	float Solver::HoverParams::GetTimeToDriftMin() const
	{
		return timeToDriftMin;
	}

	// FUNCTION: ENGINE 0x1031EB40
	float Solver::HoverParams::GetTimeToStartDrift() const
	{
		return timeToStartDrift;
	}

	// FUNCTION: ENGINE 0x1031EB50
	Solver::LateralAxisLinearParams::LateralAxisLinearParams()
	{
		maxLateralAcceleration = engine::driving::gThirty;
		maxLateralSpeed = 13.888889f;
		dragCoefficient = choreo::gMinusOne;
		lowspeedDragMaxVelocity = 0.0f;
		lowSpeedDragTimeToStopFromMaxVelocity = 0.0f;
		maxInputForLowspeedDrag = 0.0f;
		lowspeedDrag = 0.0f;
	}

	// FUNCTION: ENGINE 0x1031EBA0
	float Solver::LateralAxisLinearParams::GetMaxLateralAcceleration() const
	{
		return maxLateralAcceleration;
	}

	// FUNCTION: ENGINE 0x1031EBB0
	float Solver::LateralAxisLinearParams::GetMaxLateralSpeedKph() const
	{
		return maxLateralSpeed * 3.6f;
	}

	// FUNCTION: ENGINE 0x1031EBC0
	float Solver::LateralAxisLinearParams::ScaleMaxLateralSpeed(float scale) const
	{
		return maxLateralSpeed * scale;
	}

	// FUNCTION: ENGINE 0x1031EBD0
	float Solver::LateralAxisLinearParams::GetLowspeedDragMaxVelocityKph() const
	{
		return lowspeedDragMaxVelocity * 3.6f;
	}

	// FUNCTION: ENGINE 0x1031EBE0
	float Solver::LateralAxisLinearParams::GetLowspeedDragMaxVelocity() const
	{
		return lowspeedDragMaxVelocity;
	}

	// FUNCTION: ENGINE 0x1031EBF0
	float Solver::LateralAxisLinearParams::GetLowSpeedDragTimeToStopFromMaxVelocity() const
	{
		return lowSpeedDragTimeToStopFromMaxVelocity;
	}

	// FUNCTION: ENGINE 0x1031EC00
	float Solver::LateralAxisLinearParams::GetMaxInputForLowspeedDrag() const
	{
		return maxInputForLowspeedDrag;
	}

	// FUNCTION: ENGINE 0x1031EC10
	float Solver::LateralAxisLinearParams::GetDragCoefficient() const
	{
		return dragCoefficient;
	}

	// FUNCTION: ENGINE 0x1031EC20
	float Solver::LateralAxisLinearParams::GetLowspeedDrag() const
	{
		return lowspeedDrag;
	}

	// FUNCTION: ENGINE 0x1031EC30
	float Solver::LateralAxisLinearParams::ScaleMaxLateralSpeedAgain(float scale) const
	{
		return maxLateralSpeed * scale;
	}

	// FUNCTION: ENGINE 0x1031EC40
	Solver::LateralAxisAngularParams::LateralAxisAngularParams()
	{
		maxRollAcceleration = 1.0471976f;
		maxRollAngle = 0.5235988f;
	}

	// FUNCTION: ENGINE 0x1031EC70
	void Solver::LateralAxisAngularParams::SetMaxRollAccelerationDegrees(float degrees)
	{
		maxRollAcceleration = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x1031EC90
	float Solver::LateralAxisAngularParams::GetMaxRollAccelerationDegrees() const
	{
		return maxRollAcceleration * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031ECA0
	float Solver::LateralAxisAngularParams::GetMaxRollAcceleration() const
	{
		return maxRollAcceleration;
	}

	// FUNCTION: ENGINE 0x1031ECB0
	void Solver::LateralAxisAngularParams::SetMaxRollAngleDegrees(float degrees)
	{
		maxRollAngle = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x1031ECD0
	float Solver::LateralAxisAngularParams::GetMaxRollAngleDegrees() const
	{
		return maxRollAngle * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031ECE0
	float Solver::LateralAxisAngularParams::GetMaxRollAngle() const
	{
		return maxRollAngle;
	}

	// FUNCTION: ENGINE 0x1031ECF0
	Solver::LongitudinalAxisLinearParams::LongitudinalAxisLinearParams()
	{
		maxForwardAcceleration = 60.0f;
		maxBackwardAcceleration = engine::driving::gThirty;
		maxForwardSpeed = 55.555557f;
		maxBackwardSpeed = 13.888889f;
		float minusOne = choreo::gMinusOne;
		forwardDragCoefficient = minusOne;
		backwardDragCoefficient = minusOne;
		lowspeedDragMaxVelocity = 0.0f;
		lowSpeedDragTimeToStopFromMaxVelocity = 0.0f;
		maxInputForLowspeedDrag = 0.0f;
	}

	// FUNCTION: ENGINE 0x1031ED60
	float Solver::LongitudinalAxisLinearParams::GetMaxSpeedForDirection(float direction) const
	{
		if (engine::driving::gZero < direction)
		{
			return maxForwardSpeed * direction;
		}
		return maxBackwardSpeed * direction;
	}

	// FUNCTION: ENGINE 0x1031ED90
	float Solver::LongitudinalAxisLinearParams::GetMaxForwardSpeedKph() const
	{
		return maxForwardSpeed * 3.6f;
	}

	// FUNCTION: ENGINE 0x1031EDA0
	float Solver::LongitudinalAxisLinearParams::ScaleMaxForwardSpeed(float scale) const
	{
		return maxForwardSpeed * scale;
	}

	// FUNCTION: ENGINE 0x1031EDB0
	float Solver::LongitudinalAxisLinearParams::GetMaxBackwardSpeedKph() const
	{
		return maxBackwardSpeed * 3.6f;
	}

	// FUNCTION: ENGINE 0x1031EDC0
	float Solver::LongitudinalAxisLinearParams::ScaleMaxBackwardSpeed(float scale) const
	{
		return maxBackwardSpeed * scale;
	}

	// FUNCTION: ENGINE 0x1031EDD0
	float Solver::LongitudinalAxisLinearParams::GetMaxForwardAcceleration() const
	{
		return maxForwardAcceleration;
	}

	// FUNCTION: ENGINE 0x1031EDE0
	float Solver::LongitudinalAxisLinearParams::GetMaxBackwardAcceleration() const
	{
		return maxBackwardAcceleration;
	}

	// FUNCTION: ENGINE 0x1031EDF0
	float Solver::LongitudinalAxisLinearParams::GetLowspeedDragMaxVelocityKph() const
	{
		return lowspeedDragMaxVelocity * 3.6f;
	}

	// FUNCTION: ENGINE 0x1031EE00
	float Solver::LongitudinalAxisLinearParams::GetLowspeedDragMaxVelocity() const
	{
		return lowspeedDragMaxVelocity;
	}

	// FUNCTION: ENGINE 0x1031EE10
	float Solver::LongitudinalAxisLinearParams::GetLowSpeedDragTimeToStopFromMaxVelocity() const
	{
		return lowSpeedDragTimeToStopFromMaxVelocity;
	}

	// FUNCTION: ENGINE 0x1031EE20
	float Solver::LongitudinalAxisLinearParams::GetMaxInputForLowspeedDrag() const
	{
		return maxInputForLowspeedDrag;
	}

	// FUNCTION: ENGINE 0x1031EE30
	float Solver::LongitudinalAxisLinearParams::GetForwardDragCoefficient() const
	{
		return forwardDragCoefficient;
	}

	// FUNCTION: ENGINE 0x1031EE40
	float Solver::LongitudinalAxisLinearParams::GetBackwardDragCoefficient() const
	{
		return backwardDragCoefficient;
	}

	// FUNCTION: ENGINE 0x1031EE50
	float Solver::LongitudinalAxisLinearParams::GetLowspeedDrag() const
	{
		return lowspeedDrag;
	}

	// FUNCTION: ENGINE 0x1031EE60
	Solver::LongitudinalAxisAngularParams::LongitudinalAxisAngularParams()
	{
		maxPitchAcceleration = 1.0471976f;
		maxPitchSpeed = 1.5707964f;
		maxAccelerationForwardPitch = 0.7853982f;
		maxVelocityForwardPitch = 0.7853982f;
		maxAccelerationBackwardPitch = 0.5235988f;
		maxVelocityBackwardPitch = 0.5235988f;
		float one = engine::driving::gOne;
		forwardPitchVelocityFactor = one;
		forwardPitchAccelerationFactor = one;
	}

	// FUNCTION: ENGINE 0x1031EED0
	float Solver::LongitudinalAxisAngularParams::ScaleMaxPitchSpeed(float scale) const
	{
		return maxPitchSpeed * scale;
	}

	// FUNCTION: ENGINE 0x1031EEE0
	void Solver::LongitudinalAxisAngularParams::SetMaxPitchAccelerationDegrees(float degrees)
	{
		maxPitchAcceleration = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x1031EF00
	float Solver::LongitudinalAxisAngularParams::GetMaxPitchAccelerationDegrees() const
	{
		return maxPitchAcceleration * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031EF10
	float Solver::LongitudinalAxisAngularParams::GetMaxPitchAcceleration() const
	{
		return maxPitchAcceleration;
	}

	// FUNCTION: ENGINE 0x1031EF20
	void Solver::LongitudinalAxisAngularParams::SetMaxPitchSpeedDegrees(float degrees)
	{
		maxPitchSpeed = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x1031EF40
	float Solver::LongitudinalAxisAngularParams::GetMaxPitchSpeedDegrees() const
	{
		return maxPitchSpeed * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031EF50
	float Solver::LongitudinalAxisAngularParams::GetMaxPitchSpeed() const
	{
		return maxPitchSpeed;
	}

	// FUNCTION: ENGINE 0x1031EF60
	void Solver::LongitudinalAxisAngularParams::SetMaxAccelerationForwardPitchDegrees(float degrees)
	{
		maxAccelerationForwardPitch = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x1031EF80
	float Solver::LongitudinalAxisAngularParams::GetMaxAccelerationForwardPitchDegrees() const
	{
		return maxAccelerationForwardPitch * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031EF90
	float Solver::LongitudinalAxisAngularParams::GetMaxAccelerationForwardPitch() const
	{
		return maxAccelerationForwardPitch;
	}

	// FUNCTION: ENGINE 0x1031EFA0
	void Solver::LongitudinalAxisAngularParams::SetMaxVelocityForwardPitchDegrees(float degrees)
	{
		maxVelocityForwardPitch = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x1031EFC0
	float Solver::LongitudinalAxisAngularParams::GetMaxVelocityForwardPitchDegrees() const
	{
		return maxVelocityForwardPitch * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031EFD0
	float Solver::LongitudinalAxisAngularParams::GetMaxVelocityForwardPitch() const
	{
		return maxVelocityForwardPitch;
	}

	// FUNCTION: ENGINE 0x1031EFE0
	void Solver::LongitudinalAxisAngularParams::SetMaxAccelerationBackwardPitchDegrees(float degrees)
	{
		maxAccelerationBackwardPitch = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x1031F000
	float Solver::LongitudinalAxisAngularParams::GetMaxAccelerationBackwardPitchDegrees() const
	{
		return maxAccelerationBackwardPitch * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031F010
	float Solver::LongitudinalAxisAngularParams::GetMaxAccelerationBackwardPitch() const
	{
		return maxAccelerationBackwardPitch;
	}

	// FUNCTION: ENGINE 0x1031F020
	void Solver::LongitudinalAxisAngularParams::SetMaxVelocityBackwardPitchDegrees(float degrees)
	{
		maxVelocityBackwardPitch = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x1031F040
	float Solver::LongitudinalAxisAngularParams::GetMaxVelocityBackwardPitchDegrees() const
	{
		return maxVelocityBackwardPitch * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031F050
	float Solver::LongitudinalAxisAngularParams::GetMaxVelocityBackwardPitch() const
	{
		return maxVelocityBackwardPitch;
	}

	// FUNCTION: ENGINE 0x1031F060
	float Solver::LongitudinalAxisAngularParams::GetForwardPitchAccelerationFactor() const
	{
		return forwardPitchAccelerationFactor;
	}

	// FUNCTION: ENGINE 0x1031F070
	float Solver::LongitudinalAxisAngularParams::GetForwardPitchVelocityFactor() const
	{
		return forwardPitchVelocityFactor;
	}

	// FUNCTION: ENGINE 0x1031F080
	Solver::VerticalAxisParams::VerticalAxisParams()
	{
		float thirty = engine::driving::gThirty;
		float maxTilt = 1.39626348f;
		maxUpAcceleration = thirty;
		maxUpAccelerationWithPitch = thirty;
		maxDownAcceleration = thirty;
		maxDownAccelerationWithPitch = thirty;
		maxUpVelocity = 8.333334f;
		maxDownVelocity = 8.333334f;
		maxDownVelocityWithPitch = 8.333334f;
		float minusOne = choreo::gMinusOne;
		upDragCoefficient = minusOne;
		downDragCoefficient = minusOne;
		downWithPitchDragCoefficient = minusOne;
		maxHeight = ravenphysics::gDefaultMaxForce;
		dragCoefficientMaxHeight = 0.0f;
		lowspeedDragMaxVelocity = 0.0f;
		lowSpeedDragTimeToStopFromMaxVelocity = 0.0f;
		maxInputForLowspeedDrag = 0.0f;
		lowspeedDrag = 0.0f;
		maxTiltFromVertical = maxTilt;
		maxAutomaticDownwardAcceleration = 0.0f;
	}

	// FUNCTION: ENGINE 0x1031F130
	float Solver::VerticalAxisParams::GetMaxUpSpeedForDirection(float direction) const
	{
		if (engine::driving::gZero < direction)
		{
			return maxUpVelocity * direction;
		}
		return maxDownVelocity * direction;
	}

	// FUNCTION: ENGINE 0x1031F160
	float Solver::VerticalAxisParams::GetMaxUpAcceleration() const
	{
		return maxUpAcceleration;
	}

	// FUNCTION: ENGINE 0x1031F170
	void Solver::VerticalAxisParams::SetMaxUpAccelerationWithPitch(float acceleration)
	{
		maxUpAccelerationWithPitch = acceleration;
	}

	// FUNCTION: ENGINE 0x1031F190
	float Solver::VerticalAxisParams::GetMaxUpAccelerationWithPitch() const
	{
		return maxUpAccelerationWithPitch;
	}

	// FUNCTION: ENGINE 0x1031F1A0
	float Solver::VerticalAxisParams::GetMaxDownAcceleration() const
	{
		return maxDownAcceleration;
	}

	// FUNCTION: ENGINE 0x1031F1B0
	void Solver::VerticalAxisParams::SetMaxDownAccelerationWithPitch(float acceleration)
	{
		maxDownAccelerationWithPitch = acceleration;
	}

	// FUNCTION: ENGINE 0x1031F1D0
	float Solver::VerticalAxisParams::GetMaxDownAccelerationWithPitch() const
	{
		return maxDownAccelerationWithPitch;
	}

	// FUNCTION: ENGINE 0x1031F1E0
	float Solver::VerticalAxisParams::GetMaxUpVelocityKph() const
	{
		return maxUpVelocity * 3.6f;
	}

	// FUNCTION: ENGINE 0x1031F1F0
	float Solver::VerticalAxisParams::ScaleMaxUpVelocity(float scale) const
	{
		return maxUpVelocity * scale;
	}

	// FUNCTION: ENGINE 0x1031F200
	float Solver::VerticalAxisParams::GetMaxDownVelocityKph() const
	{
		return maxDownVelocity * 3.6f;
	}

	// FUNCTION: ENGINE 0x1031F210
	float Solver::VerticalAxisParams::ScaleMaxDownVelocity(float scale) const
	{
		return maxDownVelocity * scale;
	}

	// FUNCTION: ENGINE 0x1031F220
	float Solver::VerticalAxisParams::GetMaxDownVelocityWithPitchKph() const
	{
		return maxDownVelocityWithPitch * 3.6f;
	}

	// FUNCTION: ENGINE 0x1031F230
	float Solver::VerticalAxisParams::GetMaxDownVelocityWithPitch() const
	{
		return maxDownVelocityWithPitch;
	}

	// FUNCTION: ENGINE 0x1031F240
	float Solver::VerticalAxisParams::GetLowspeedDragMaxVelocityKph() const
	{
		return lowspeedDragMaxVelocity * 3.6f;
	}

	// FUNCTION: ENGINE 0x1031F250
	float Solver::VerticalAxisParams::GetLowspeedDragMaxVelocity() const
	{
		return lowspeedDragMaxVelocity;
	}

	// FUNCTION: ENGINE 0x1031F260
	float Solver::VerticalAxisParams::GetLowSpeedDragTimeToStopFromMaxVelocity() const
	{
		return lowSpeedDragTimeToStopFromMaxVelocity;
	}

	// FUNCTION: ENGINE 0x1031F270
	float Solver::VerticalAxisParams::GetMaxInputForLowspeedDrag() const
	{
		return maxInputForLowspeedDrag;
	}

	// FUNCTION: ENGINE 0x1031F280
	void Solver::VerticalAxisParams::UpdateLowspeedDrag()
	{
		lowspeedDrag = lowspeedDragMaxVelocity / lowSpeedDragTimeToStopFromMaxVelocity;
	}

	// FUNCTION: ENGINE 0x1031F2A0
	float Solver::VerticalAxisParams::GetUpDragCoefficient() const
	{
		return upDragCoefficient;
	}

	// FUNCTION: ENGINE 0x1031F2B0
	float Solver::VerticalAxisParams::GetDownDragCoefficient() const
	{
		return downDragCoefficient;
	}

	// FUNCTION: ENGINE 0x1031F2C0
	float Solver::VerticalAxisParams::GetDownWithPitchDragCoefficient() const
	{
		return downWithPitchDragCoefficient;
	}

	// FUNCTION: ENGINE 0x1031F2D0
	float Solver::VerticalAxisParams::GetLowspeedDrag() const
	{
		return lowspeedDrag;
	}

	// FUNCTION: ENGINE 0x1031F2E0
	float Solver::VerticalAxisParams::GetMaxHeight() const
	{
		return maxHeight;
	}

	// FUNCTION: ENGINE 0x1031F2F0
	float Solver::VerticalAxisParams::GetDragCoefficientMaxHeight() const
	{
		return dragCoefficientMaxHeight;
	}

	// FUNCTION: ENGINE 0x1031F300
	float Solver::VerticalAxisParams::GetMaxTiltFromVertical() const
	{
		return maxTiltFromVertical;
	}

	// FUNCTION: ENGINE 0x1031F310
	float Solver::VerticalAxisParams::GetMaxTiltFromVerticalDegrees() const
	{
		return maxTiltFromVertical * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031F320
	void Solver::VerticalAxisParams::SetMaxTiltFromVerticalDegrees(float degrees)
	{
		maxTiltFromVertical = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x1031F340
	float Solver::VerticalAxisParams::GetMaxAutomaticDownwardAcceleration() const
	{
		return maxAutomaticDownwardAcceleration;
	}

	// FUNCTION: ENGINE 0x1031F350
	// NONMATCHING: the engine loads the first constant before the shared one of the last member, 85 %
#ifdef NONMATCHING
	Solver::YawAxisParams::YawAxisParams()
	{
		maxYawAcceleration = 1.0471976f;
		float one = engine::driving::gOne;
		maxVelocity = 1.5707964f;
		yawAmountAtMaxForwardAndSidewayVelocity = 0.0f;
		lowspeedDragMaxVelocity = 0.0f;
		lowSpeedDragTimeToStopFromMaxVelocity = one;
		maxInputForLowspeedDrag = 0.0f;
		lowspeedDrag = 0.0f;
		dragCoefficient = 0.0f;
	}
#endif

	// FUNCTION: ENGINE 0x1031F3B0
	float Solver::YawAxisParams::GetMaxYawAccelerationDegrees() const
	{
		return maxYawAcceleration * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031F3C0
	float Solver::YawAxisParams::GetMaxYawAcceleration() const
	{
		return maxYawAcceleration;
	}

	// FUNCTION: ENGINE 0x1031F3D0
	float Solver::YawAxisParams::GetMaxVelocityDegrees() const
	{
		return maxVelocity * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031F3E0
	float Solver::YawAxisParams::GetMaxVelocity() const
	{
		return maxVelocity;
	}

	// FUNCTION: ENGINE 0x1031F3F0
	void Solver::YawAxisParams::SetYawAmountAtMaxForwardAndSidewayVelocity(float amount)
	{
		if (!(amount >= 0.0f))
		{
			amount = 0.0f;
		}
		if (0.0f <= amount - engine::driving::gOne)
		{
			yawAmountAtMaxForwardAndSidewayVelocity = engine::driving::gOne;
			return;
		}
		yawAmountAtMaxForwardAndSidewayVelocity = amount;
	}

	// FUNCTION: ENGINE 0x1031F440
	float Solver::YawAxisParams::GetYawAmountAtMaxForwardAndSidewayVelocity() const
	{
		return yawAmountAtMaxForwardAndSidewayVelocity;
	}

	// FUNCTION: ENGINE 0x1031F450
	float Solver::YawAxisParams::GetLowspeedDragMaxVelocityDegrees() const
	{
		return lowspeedDragMaxVelocity * 57.295776f;
	}

	// FUNCTION: ENGINE 0x1031F460
	float Solver::YawAxisParams::GetLowspeedDragMaxVelocity() const
	{
		return lowspeedDragMaxVelocity;
	}

	// FUNCTION: ENGINE 0x1031F470
	float Solver::YawAxisParams::GetLowSpeedDragTimeToStopFromMaxVelocity() const
	{
		return lowSpeedDragTimeToStopFromMaxVelocity;
	}

	// FUNCTION: ENGINE 0x1031F480
	float Solver::YawAxisParams::GetMaxInputForLowspeedDrag() const
	{
		return maxInputForLowspeedDrag;
	}

	// FUNCTION: ENGINE 0x1031F490
	float Solver::YawAxisParams::GetLowspeedDrag() const
	{
		return lowspeedDrag;
	}

	// FUNCTION: ENGINE 0x1031F4A0
	float Solver::YawAxisParams::GetDragCoefficient() const
	{
		return dragCoefficient;
	}

	// FUNCTION: ENGINE 0x1031F740
	content::MemberList* Generic::SoundParams::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<SoundParams, 0>(true, true, "p"),
				PROTO_NAME_OFFSET(SoundParams, patchName), "patchName" },
			{ content::GetMemberNameMetaType<SoundParams, 1>(true, true, "p"),
				PROTO_NAME_OFFSET(SoundParams, startupTriggerName), "startupTriggerName" },
			{ content::GetMemberNameMetaType<SoundParams, 2>(true, true, "p"),
				PROTO_NAME_OFFSET(SoundParams, throttleControlName), "throttleControlName" },
			{ content::GetMemberNameMetaType<SoundParams, 3>(true, true, "p"),
				PROTO_NAME_OFFSET(SoundParams, velocityControlName), "velocityControlName" },
			{ content::GetMemberNameMetaType<SoundParams, 4>(true, true, "p"),
				PROTO_NAME_OFFSET(SoundParams, windDownTriggerName), "windDownTriggerName" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1031F8C0
	Generic::SoundParams::SoundParams()
	{
	}

	// FUNCTION: ENGINE 0x1031F910
	void Generic::SoundParams::SetStartupTriggerName(const core::Name<core::CaseSensitiveKey>* name)
	{
		startupTriggerName = *name;
	}

	// FUNCTION: ENGINE 0x1031F920
	void Generic::SoundParams::SetThrottleControlName(const core::Name<core::CaseSensitiveKey>* name)
	{
		throttleControlName = *name;
	}

	// FUNCTION: ENGINE 0x1031F930
	void Generic::SoundParams::SetVelocityControlName(const core::Name<core::CaseSensitiveKey>* name)
	{
		velocityControlName = *name;
	}

	// FUNCTION: ENGINE 0x1031F940
	void Generic::SoundParams::SetWindDownTriggerName(const core::Name<core::CaseSensitiveKey>* name)
	{
		windDownTriggerName = *name;
	}

	// FUNCTION: ENGINE 0x1031F720
	void ReleaseMassProperties(ravenphysics::MassProperties*& object)
	{
		if (object != 0)
		{
			object->Release();
			object = 0;
		}
	}

	// FUNCTION: ENGINE 0x1031F960
	Generic::~HelicopterSolverGenericProperties()
	{
		ReleaseMassProperties(restingMassProperties);
	}

	// FUNCTION: ENGINE 0x1031FAE0
	void Solver::LateralAxisLinearParams::UpdateDerivedValues()
	{
		dragCoefficient = maxLateralAcceleration / (maxLateralSpeed * maxLateralSpeed);
		lowspeedDrag = lowspeedDragMaxVelocity / lowSpeedDragTimeToStopFromMaxVelocity;
	}

	// FUNCTION: ENGINE 0x1031FB20
	void Solver::LongitudinalAxisLinearParams::UpdateDerivedValues()
	{
		forwardDragCoefficient = maxForwardAcceleration / (maxForwardSpeed * maxForwardSpeed);
		backwardDragCoefficient = maxBackwardAcceleration / (maxBackwardSpeed * maxBackwardSpeed);
		lowspeedDrag = lowspeedDragMaxVelocity / lowSpeedDragTimeToStopFromMaxVelocity;
	}

	// FUNCTION: ENGINE 0x1031FB80
	void Solver::VerticalAxisParams::SetLowspeedDragMaxVelocityKph(float kph)
	{
		lowspeedDragMaxVelocity = kph * 0.27777779f;
		UpdateLowspeedDrag();
	}

	// FUNCTION: ENGINE 0x1031FBB0
	void Solver::VerticalAxisParams::SetLowSpeedDragTimeToStopFromMaxVelocity(float time)
	{
		lowSpeedDragTimeToStopFromMaxVelocity = time;
		UpdateLowspeedDrag();
	}

	// FUNCTION: ENGINE 0x1031FBD0
	void Solver::VerticalAxisParams::UpdateUpDragCoefficient()
	{
		upDragCoefficient = maxUpAcceleration / (maxUpVelocity * maxUpVelocity);
	}

	// FUNCTION: ENGINE 0x1031FBF0
	void Solver::VerticalAxisParams::UpdateDownDragCoefficients()
	{
		downDragCoefficient = maxDownAcceleration / (maxDownVelocity * maxDownVelocity);
		downWithPitchDragCoefficient = maxDownAccelerationWithPitch / (maxDownVelocityWithPitch * maxDownVelocityWithPitch);
	}

	// FUNCTION: ENGINE 0x1031FC40
	void Solver::YawAxisParams::UpdateDerivedValues()
	{
		lowspeedDrag = lowspeedDragMaxVelocity / lowSpeedDragTimeToStopFromMaxVelocity;
		dragCoefficient = maxYawAcceleration / (maxVelocity * maxVelocity);
	}
}

// The engine's copies of the offset and class meta type helpers of the groups, and of the meta types of the members
// the groups' reflection reads directly (the reflection of the groups is in the following unit)
namespace content
{
	typedef proto::HelicopterSolverGenericProperties Generic;
	typedef proto::HelicopterSolverProperties Solver;

	template int MemberOffset<Generic::CameraParams>(Generic::CameraParams* member, int offset);
	template int MemberOffset<Generic::EffectsParams>(Generic::EffectsParams* member, int offset);
	template int MemberOffset<Generic::HealthParams>(Generic::HealthParams* member, int offset);
	template int MemberOffset<Generic::PowerParams>(Generic::PowerParams* member, int offset);
	template int MemberOffset<Generic::RotorParams>(Generic::RotorParams* member, int offset);
	template int MemberOffset<Generic::SoundParams>(Generic::SoundParams* member, int offset);
	template int MemberOffset<Solver::AIParams>(Solver::AIParams* member, int offset);
	template int MemberOffset<Solver::HoverParams>(Solver::HoverParams* member, int offset);
	template int MemberOffset<Solver::LateralAxisLinearParams>(Solver::LateralAxisLinearParams* member, int offset);
	template int MemberOffset<Solver::LateralAxisAngularParams>(Solver::LateralAxisAngularParams* member, int offset);
	template int MemberOffset<Solver::LongitudinalAxisLinearParams>(Solver::LongitudinalAxisLinearParams* member, int offset);
	template int MemberOffset<Solver::LongitudinalAxisAngularParams>(Solver::LongitudinalAxisAngularParams* member, int offset);
	template int MemberOffset<Solver::VerticalAxisParams>(Solver::VerticalAxisParams* member, int offset);
	template int MemberOffset<Solver::YawAxisParams>(Solver::YawAxisParams* member, int offset);
	template ClassMetaType* GetClassMetaType<Generic::SoundParams>();
	template PrimitiveMetaType<float>* GetMemberPrimitiveMetaType<Generic::CameraParams, float, 2>(const char* code);
	template PrimitiveMetaType<float>* GetMemberPrimitiveMetaType<Generic::CameraParams, float, 3>(const char* code);
	template PrimitiveMetaType<float>* GetMemberPrimitiveMetaType<Generic::CameraParams, float, 4>(const char* code);
	template PrimitiveMetaType<float>* GetMemberPrimitiveMetaType<Generic::CameraParams, float, 5>(const char* code);
	template PrimitiveMetaType<float>* GetMemberPrimitiveMetaType<Generic::EffectsParams, float, 0>(const char* code);
	template PrimitiveMetaType<float>* GetMemberPrimitiveMetaType<Generic::EffectsParams, float, 1>(const char* code);
	template PrimitiveMetaType<float>* GetMemberPrimitiveMetaType<Generic::EffectsParams, float, 2>(const char* code);
	template PrimitiveMetaType<float>* GetMemberPrimitiveMetaType<Generic::EffectsParams, float, 3>(const char* code);
	template PrimitiveMetaType<float>* GetMemberPrimitiveMetaType<Generic::EffectsParams, float, 4>(const char* code);
	template PrimitiveMetaType<float>* GetMemberPrimitiveMetaType<Generic::HealthParams, float, 1>(const char* code);
}

// Kept copies (compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103215F0
// FUNCTION: ENGINE 0x1031F640
// FUNCTION: ENGINE 0x1031F650
// FUNCTION: ENGINE 0x1031F660
// FUNCTION: ENGINE 0x1031F670
// FUNCTION: ENGINE 0x1031F680
// FUNCTION: ENGINE 0x1031F690
// FUNCTION: ENGINE 0x1031F6A0
// FUNCTION: ENGINE 0x1031F6B0
// FUNCTION: ENGINE 0x1031F6C0
// FUNCTION: ENGINE 0x1031F6D0
// FUNCTION: ENGINE 0x1031F6E0
// FUNCTION: ENGINE 0x1031F6F0
// FUNCTION: ENGINE 0x1031F700
// FUNCTION: ENGINE 0x1031F710
// FUNCTION: ENGINE 0x1031FD30
// FUNCTION: ENGINE 0x1031F4C0
// FUNCTION: ENGINE 0x1031F500
// FUNCTION: ENGINE 0x1031F540
// FUNCTION: ENGINE 0x1031F580
// FUNCTION: ENGINE 0x1031F5C0
// FUNCTION: ENGINE 0x1031FD90
// FUNCTION: ENGINE 0x1031FDD0
// FUNCTION: ENGINE 0x1031FE10
// FUNCTION: ENGINE 0x1031FE50
// FUNCTION: ENGINE 0x1031FE90
// FUNCTION: ENGINE 0x1031FED0
// FUNCTION: ENGINE 0x1031FF10
// FUNCTION: ENGINE 0x1031FF50
// FUNCTION: ENGINE 0x1031FF90
// FUNCTION: ENGINE 0x1031FFD0
