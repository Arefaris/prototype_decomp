#include "code/proto/behaviours/tanksolver.h"
#include "code/core/refptr.h"
#include "code/om/dynamicproperty.h"
#include <math.h>
#include "code/engine/driving/carattributes.h"
#include "code/math/sincos.h"
#include "code/math/worldbounds.h"

namespace content
{
	static const EnumValue sForceDistributionTypeValues[] =
	{
		{ "Constant", 0 },
		{ "ApplyIfAnyJointInContact", 1 },
		{ "DistributeAmongContacts", 2 }
	};

	// FUNCTION: ENGINE 0x102F3EC0
	template<> void EnumInfo<proto::TankSolverProperties::ForceDistributionType>::Get(const char** name,
		const EnumValue** values, int* count, const char** code)
	{
		*name = "proto::TankSolverProperties::ForceDistributionType";
		*code = "p";
		*values = sForceDistributionTypeValues;
		*count = 3;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_RAW_OFFSET(type, member) \
	((int)&((type*)0)->member)

	// The factor of the speeds the properties reflect in kilometres per hour (0x110781F4; name guessed)
	extern const float gKilometresPerHourToMetresPerSecond;

	// FUNCTION: ENGINE 0x102F3D40
	content::ClassInfo* AlignedAxleConstraintProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AlignedAxleConstraintProperties";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F3D80
	content::ClassInfo* AlignedAxleConstraint::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AlignedAxleConstraint";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F3DC0
	content::ClassInfo* TankSolverProperties::CameraParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankSolverProperties::CameraParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F3E00
	content::ClassInfo* TankSolverProperties::SoundParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankSolverProperties::SoundParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F3E40
	content::ClassInfo* TankSolverProperties::SuspensionSpring::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankSolverProperties::SuspensionSpring";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F3E80
	content::ClassInfo* TankSolverProperties::SensorSpring::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankSolverProperties::SensorSpring";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F3F00
	content::ClassInfo* TankSolverProperties::Friction::Scales::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankSolverProperties::Friction::Scales";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F3F40
	content::ClassInfo* TankSolverProperties::Friction::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankSolverProperties::Friction";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F3F80
	content::ClassInfo* TankSolverProperties::Thrust::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankSolverProperties::Thrust";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F3FC0
	content::ClassInfo* TankSolverProperties::Steering::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankSolverProperties::Steering";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F4000
	content::ClassInfo* TankSolverProperties::InAir::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankSolverProperties::InAir";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F4040
	content::ClassInfo* TankSolverProperties::Reaction::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankSolverProperties::Reaction";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F4080
	content::ClassInfo* TankSolverProperties::Animation::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankSolverProperties::Animation";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F40C0
	content::ClassInfo* TankSolverProperties::DebugDraw::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankSolverProperties::DebugDraw";
		sInfo.code = "";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F4100
	content::ClassInfo* TankSolverProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankSolverProperties";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F4140
	content::ClassInfo* TankSolverBehaviour::JointData::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankSolverBehaviour::JointData";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F4200
	content::ClassInfo* TreadEffects::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TreadEffectsPlugin";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F4240
	content::ClassInfo* TankSolverBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TankSolverBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F4280
	const math::Vector* AlignedAxleConstraintProperties::GetRotationAxis() const
	{
		return &rotationAxis;
	}

	// FUNCTION: ENGINE 0x102F4290
	const math::Vector* AlignedAxleConstraintProperties::GetFacingAxis() const
	{
		return &facingAxis;
	}

	// FUNCTION: ENGINE 0x102F42A0
	const math::Vector* AlignedAxleConstraintProperties::GetPerpendicularAxis() const
	{
		return &perpendicularAxis;
	}

	// FUNCTION: ENGINE 0x102F42B0
	void AlignedAxleConstraintProperties::SetMaxForce(float value)
	{
		maxForce = value;
	}

	// FUNCTION: ENGINE 0x102F42D0
	float AlignedAxleConstraintProperties::GetMaxForce() const
	{
		return maxForce;
	}

	// FUNCTION: ENGINE 0x102F42E0
	void AlignedAxleConstraintProperties::SetMaxVelocity(float degrees)
	{
		maxVelocity = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x102F4300
	float AlignedAxleConstraintProperties::GetMaxVelocity() const
	{
		return maxVelocity * 57.295776f;
	}

	// FUNCTION: ENGINE 0x102F4310
	float AlignedAxleConstraintProperties::GetMaxVelocityRadians() const
	{
		return maxVelocity;
	}

	// FUNCTION: ENGINE 0x102F4320
	void AlignedAxleConstraintProperties::SetDampingConstant(float value)
	{
		dampingConstant = value;
	}

	// FUNCTION: ENGINE 0x102F4340
	float AlignedAxleConstraintProperties::GetDampingConstant() const
	{
		return dampingConstant;
	}

	// FUNCTION: ENGINE 0x102F4350
	void AlignedAxleConstraintProperties::SetSpringConstant(float value)
	{
		springConstant = value;
	}

	// FUNCTION: ENGINE 0x102F4370
	float AlignedAxleConstraintProperties::GetSpringConstant() const
	{
		return springConstant;
	}

	// FUNCTION: ENGINE 0x102F4380
	void AlignedAxleConstraintProperties::SetMaxAngle(float degrees)
	{
		maxAngle = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x102F43A0
	float AlignedAxleConstraintProperties::GetMaxAngle() const
	{
		return maxAngle * 57.295776f;
	}

	// FUNCTION: ENGINE 0x102F43B0
	float AlignedAxleConstraintProperties::GetMaxAngleRadians() const
	{
		return maxAngle;
	}

	// FUNCTION: ENGINE 0x102F43C0
	void AlignedAxleConstraintProperties::SetMinAngle(float degrees)
	{
		minAngle = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x102F43E0
	float AlignedAxleConstraintProperties::GetMinAngle() const
	{
		return minAngle * 57.295776f;
	}

	// FUNCTION: ENGINE 0x102F43F0
	float AlignedAxleConstraintProperties::GetMinAngleRadians() const
	{
		return minAngle;
	}

	// FUNCTION: ENGINE 0x102F4400
	void AlignedAxleConstraintProperties::SetDistanceForDamper(float degrees)
	{
		distanceForDamper = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x102F4420
	float AlignedAxleConstraintProperties::GetDistanceForDamper() const
	{
		return distanceForDamper * 57.295776f;
	}

	// FUNCTION: ENGINE 0x102F4430
	float AlignedAxleConstraintProperties::GetDistanceForDamperRadians() const
	{
		return distanceForDamper;
	}

	// FUNCTION: ENGINE 0x102F4440
	void AlignedAxleConstraintProperties::SetDamperFactor(float value)
	{
		damperFactor = value;
	}

	// FUNCTION: ENGINE 0x102F4460
	float AlignedAxleConstraintProperties::GetDamperFactor() const
	{
		return damperFactor;
	}

	// FUNCTION: ENGINE 0x102F4A20
	void TankSolverProperties::SoundParams::SetAngleThresholdForMovingTurret(float degrees)
	{
		angleThresholdForMovingTurret = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x102F4A40
	float TankSolverProperties::SoundParams::GetAngleThresholdForMovingTurret() const
	{
		return angleThresholdForMovingTurret * 57.295776f;
	}

	// FUNCTION: ENGINE 0x102F4A50
	float TankSolverProperties::SoundParams::GetAngleThresholdForMovingTurretRadians() const
	{
		return angleThresholdForMovingTurret;
	}

	// FUNCTION: ENGINE 0x102F4C30
	float TankSolverProperties::SensorSpring::GetForwardSensorAngleDegrees() const
	{
		return forwardSensorAngle * 57.295776f;
	}

	// FUNCTION: ENGINE 0x102F4CE0
	float TankSolverProperties::SensorSpring::GetReverseSensorAngleDegrees() const
	{
		return reverseSensorAngle * 57.295776f;
	}

	// FUNCTION: ENGINE 0x102F4E50
	float TankSolverProperties::Thrust::GetMaxForwardSpeedKmh() const
	{
		return maxForwardSpeed * 3.6f;
	}

	// FUNCTION: ENGINE 0x102F4E60
	void TankSolverProperties::Thrust::SetMaxForwardSpeedKmh(float kmh)
	{
		maxForwardSpeed = gKilometresPerHourToMetresPerSecond * kmh;
	}

	// FUNCTION: ENGINE 0x102F4E80
	float TankSolverProperties::Thrust::GetMaxReverseSpeedKmh() const
	{
		return maxReverseSpeed * 3.6f;
	}

	// FUNCTION: ENGINE 0x102F4E90
	void TankSolverProperties::Thrust::SetMaxReverseSpeedKmh(float kmh)
	{
		maxReverseSpeed = gKilometresPerHourToMetresPerSecond * kmh;
	}

	// FUNCTION: ENGINE 0x102F4EB0
	float TankSolverProperties::Thrust::GetSensorMaxClimbUpSpeedKmh() const
	{
		return sensorMaxClimbUpSpeed * 3.6f;
	}

	// FUNCTION: ENGINE 0x102F4EC0
	void TankSolverProperties::Thrust::SetSensorMaxClimbUpSpeedKmh(float kmh)
	{
		sensorMaxClimbUpSpeed = gKilometresPerHourToMetresPerSecond * kmh;
	}

	// FUNCTION: ENGINE 0x102F4EE0
	float TankSolverProperties::Thrust::GetSensorMaxClimbDownSpeedKmh() const
	{
		return sensorMaxClimbDownSpeed * 3.6f;
	}

	// FUNCTION: ENGINE 0x102F4EF0
	void TankSolverProperties::Thrust::SetSensorMaxClimbDownSpeedKmh(float kmh)
	{
		sensorMaxClimbDownSpeed = gKilometresPerHourToMetresPerSecond * kmh;
	}

	// FUNCTION: ENGINE 0x102F4F10
	float TankSolverProperties::Thrust::GetUpwardThrustStartCutoffTiltDegrees() const
	{
		return upwardThrustStartCutoffTilt * 57.295776f;
	}

	// FUNCTION: ENGINE 0x102F4F20
	void TankSolverProperties::Thrust::SetUpwardThrustStartCutoffTiltDegrees(float degrees)
	{
		upwardThrustStartCutoffTilt = degrees * 0.017453292f;
		upwardThrustStartCutoffCosine = cosf(upwardThrustStartCutoffTilt);
	}

	// FUNCTION: ENGINE 0x102F4F50
	float TankSolverProperties::Thrust::GetUpwardThrustFullCutoffTiltDegrees() const
	{
		return upwardThrustFullCutoffTilt * 57.295776f;
	}

	// FUNCTION: ENGINE 0x102F4F60
	void TankSolverProperties::Thrust::SetUpwardThrustFullCutoffTiltDegrees(float degrees)
	{
		upwardThrustFullCutoffTilt = degrees * 0.017453292f;
		upwardThrustFullCutoffCosine = cosf(upwardThrustFullCutoffTilt);
	}

	// FUNCTION: ENGINE 0x102F5010
	float TankSolverProperties::Steering::GetMaxTurnSpeedDegrees() const
	{
		return maxTurnSpeed * 57.295776f;
	}

	// FUNCTION: ENGINE 0x102F5020
	void TankSolverProperties::Steering::SetMaxTurnSpeedDegrees(float degrees)
	{
		maxTurnSpeed = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x102F5040
	float TankSolverProperties::Steering::GetSensorMaxTurnSpeedDegrees() const
	{
		return sensorMaxTurnSpeed * 57.295776f;
	}

	// FUNCTION: ENGINE 0x102F5050
	void TankSolverProperties::Steering::SetSensorMaxTurnSpeedDegrees(float degrees)
	{
		sensorMaxTurnSpeed = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x102F50B0
	float TankSolverProperties::InAir::GetMaxDownwardSpeedKmh() const
	{
		return maxDownwardSpeed * 3.6f;
	}

	// FUNCTION: ENGINE 0x102F50C0
	void TankSolverProperties::InAir::SetMaxDownwardSpeedKmh(float kmh)
	{
		maxDownwardSpeed = gKilometresPerHourToMetresPerSecond * kmh;
	}

	// FUNCTION: ENGINE 0x102F5320
	float TankSolverProperties::GetMinSpeedToDamageCollidersKph() const
	{
		return minSpeedToDamageColliders * 3.6f;
	}

	// FUNCTION: ENGINE 0x102F5330
	void TankSolverProperties::SetMinSpeedToDamageCollidersKph(float kph)
	{
		minSpeedToDamageColliders = kph * 0.2777778f;
	}

	// FUNCTION: ENGINE 0x102F5350
	void TankSolverProperties::SetMaxTiltAngleDegrees(float degrees)
	{
		maxTiltAngle = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x102F5370
	float TankSolverProperties::GetMaxTiltAngleDegrees() const
	{
		return maxTiltAngle * 57.295776f;
	}

	// FUNCTION: ENGINE 0x102F4990
	TankSolverProperties::CameraParams::CameraParams()
	{
		baseDistance = 10.0f;
		targetOffset.x = 0.0f;
		targetOffset.y = 3.0f;
		targetOffset.z = 0.0f;
	}

	// FUNCTION: ENGINE 0x102F49F0
	// NONMATCHING: scheduling of the constant loads (77.8 %)
#ifdef NONMATCHING
	TankSolverProperties::SoundParams::SoundParams()
	{
		angleThresholdForMovingTurret = 0.0f;
		timeThresholdForTurretMoving = engine::driving::gOne;
		timeThresholdForTurretStopped = engine::driving::gOne;
	}
#endif

	// FUNCTION: ENGINE 0x102F4A60
	// NONMATCHING: scheduling of the constant loads and stores (best 89 %)
#ifdef NONMATCHING
	TankSolverProperties::SuspensionSpring::SuspensionSpring()
	{
		rayBufferHeight = 0.25f;
		restHeightOffset = 0.0f;
		rayCenterOffset = 0.0f;
		stretchDistance = 0.25f;
		compressDistance = 0.25f;
		maxSpeedForDamping = 10.0f;
		float one = engine::driving::gOne;
		dampingScale = one;
		torqueScale.x = one;
		torqueScale.y = one;
		torqueScale.z = one;
		maxSpeedForLength = 10.0f;
	}
#endif

	// FUNCTION: ENGINE 0x102F4AE0
	// NONMATCHING: scheduling of the constant loads and stores (32.0 %)
#ifdef NONMATCHING
	TankSolverProperties::SensorSpring::SensorSpring()
	{
		forwardSensorAngle = 0.0f;
		reverseSensorAngle = 0.0f;
		unknown8[0] = 0.0f;
		unknown8[1] = 0.0f;
		unknown8[2] = -1.0f;
		unknown14[0] = 0.0f;
		unknown14[1] = 0.0f;
		unknown14[2] = engine::driving::gOne;
		unknown20[0] = 0.0f;
		unknown20[1] = engine::driving::gOne;
		unknown20[2] = 0.0f;
		unknown2C[0] = 0.0f;
		unknown2C[1] = -1.0f;
		unknown2C[2] = 0.0f;
		forwardSensorOffset = math::kZeroVector;
		reverseSensorOffset = math::kZeroVector;
		rayBufferDistance = 0.25f;
		forwardSensorContactOffset = 0.2f;
		reverseSensorContactOffset = 0.2f;
		compressDistance = 0.25f;
		moveJoint = false;
		forwardSensorSpringScale = engine::driving::gOne;
		reverseSensorSpringScale = engine::driving::gOne;
		maxSpeedForDamping = 10.0f;
		dampingScale = engine::driving::gOne;
		torqueScale.x = engine::driving::gOne;
		torqueScale.y = engine::driving::gOne;
		torqueScale.z = engine::driving::gOne;
	}
#endif

	// FUNCTION: ENGINE 0x102F4DA0
	// NONMATCHING: scheduling of the constant loads and stores (39.5 %)
#ifdef NONMATCHING
	TankSolverProperties::Friction::Scales::Scales()
	{
		headingScale = engine::driving::gTwo;
		headingTorqueScale.x = engine::driving::gOne;
		headingTorqueScale.y = engine::driving::gOne;
		headingTorqueScale.z = engine::driving::gOne;
		lateralScale = engine::driving::gTwo;
		lateralTorqueScale.x = engine::driving::gOne;
		lateralTorqueScale.y = engine::driving::gOne;
		lateralTorqueScale.z = engine::driving::gOne;
		rollingScale = engine::driving::gOne;
	}
#endif

	// FUNCTION: ENGINE 0x102F4E00
	// NONMATCHING: scheduling of the constant loads and stores (77.3 %)
#ifdef NONMATCHING
	TankSolverProperties::Friction::Friction()
	{
		maxSlippingSpeed = engine::driving::gOne;
		maxSlidingSpeed = engine::driving::gOne;
	}
#endif

	// FUNCTION: ENGINE 0x102F7E70
	// NONMATCHING: scheduling of the constant loads and stores (34.0 %)
#ifdef NONMATCHING
	TankSolverProperties::Thrust::Thrust()
	{
		maxForwardSpeed = 10.0f;
		maxReverseSpeed = 10.0f;
		counterGravityScale = 0.0f;
		torqueScale.x = engine::driving::gOne;
		torqueScale.y = engine::driving::gOne;
		torqueScale.z = engine::driving::gOne;
		sensorMaxClimbUpSpeed = 5.0f;
		sensorMaxClimbDownSpeed = 5.0f;
		sensorTorqueScale.x = engine::driving::gOne;
		sensorTorqueScale.y = engine::driving::gOne;
		sensorTorqueScale.z = engine::driving::gOne;
		counterGravitySensorScale = 0.0f;
		maxSpeedForEBrake = 0.0f;
		eBrakeScale = 0.0f;
		thrustMultiplierAtZeroSpeed = engine::driving::gOne;
		maxSpeedForThrustMultiplier = 10.0f;
		disableThrustMultiplierAtFullGrip = true;
		SetUpwardThrustStartCutoffTiltDegrees(55.0f);
		SetUpwardThrustFullCutoffTiltDegrees(70.0f);
	}
#endif

	// FUNCTION: ENGINE 0x102F4F90
	// NONMATCHING: scheduling of the constant loads and stores (43.8 %)
#ifdef NONMATCHING
	TankSolverProperties::Steering::Steering()
	{
		maxTurnSpeed = 0.7853982f;
		speedFractionAtMaxTurnSpeed = 0.7f;
		steeringForceScale = engine::driving::gOne;
		steeringTorqueScale.x = engine::driving::gOne;
		steeringTorqueScale.y = engine::driving::gOne;
		steeringTorqueScale.z = engine::driving::gOne;
		sensorMaxTurnSpeed = 0.7853982f;
		sensorSteeringForceScale = engine::driving::gOne;
		sensorSteeringTorqueScale.x = engine::driving::gOne;
		sensorSteeringTorqueScale.y = engine::driving::gOne;
		sensorSteeringTorqueScale.z = engine::driving::gOne;
	}
#endif

	// FUNCTION: ENGINE 0x102F5070
	TankSolverProperties::InAir::InAir()
	{
		maxDownwardSpeed = 10.0f;
		headingDragScale = 0.0f;
		lateralDragScale = 0.0f;
	}

	// FUNCTION: ENGINE 0x102F50E0
	// NONMATCHING: scheduling of the constant loads and stores (51.9 %)
#ifdef NONMATCHING
	TankSolverProperties::Reaction::Reaction()
	{
		suspensionScale = engine::driving::gOne;
		headingFrictionScale = engine::driving::gOne;
		lateralFrictionScale = engine::driving::gOne;
		thrustScale = engine::driving::gOne;
	}
#endif

	// FUNCTION: ENGINE 0x102F5120
	TankSolverProperties::DebugDraw::DebugDraw()
	{
		drawRays = false;
		drawSpringCompression = false;
		drawWheels = false;
		drawThrust = false;
		thrustDrawScale = 0.05f;
		lateralOffset = 0.0f;
		forceOffsetAlongCompression = 0.0f;
		drawFinalForce = false;
		finalForceDrawScale = 0.02f;
		drawFinalTorque = false;
		finalTorqueDrawScale = 0.02f;
		finalForceDisplayHeightOffset = 0.0f;
	}

	// FUNCTION: ENGINE 0x102F52D0
	TankSolverProperties::Animation::Animation()
	{
		treadTextureLength = engine::driving::gOne;
		wheelRadius = 0.25f;
	}

	// FUNCTION: ENGINE 0x102F4C40
	// NONMATCHING: the engine copies the angle for the sine and cosine after the member store (75.2 %)
#ifdef NONMATCHING
	void TankSolverProperties::SensorSpring::SetForwardSensorAngleDegrees(float degrees)
	{
		float angle = degrees * 0.017453292f;
		forwardSensorAngle = angle;
		float sine;
		float cosine;
		math::SinCos(angle, &sine, &cosine);
		float zero = math::WORLD_MIN;
		float negatedSine = zero - sine;
		unknown8[0] = 0.0f;
		unknown8[1] = negatedSine;
		unknown8[2] = zero - cosine;
		unknown20[0] = 0.0f;
		unknown20[1] = cosine;
		unknown20[2] = negatedSine;
	}
#endif

	// FUNCTION: ENGINE 0x102F4CF0
	// NONMATCHING: the engine copies the angle for the sine and cosine after the member store (61.5 %)
#ifdef NONMATCHING
	void TankSolverProperties::SensorSpring::SetReverseSensorAngleDegrees(float degrees)
	{
		float angle = degrees * 0.017453292f;
		reverseSensorAngle = angle;
		float sine;
		float cosine;
		math::SinCos(angle, &sine, &cosine);
		float zero = math::WORLD_MIN;
		unknown14[1] = zero - sine;
		unknown14[0] = 0.0f;
		unknown14[2] = cosine;
		unknown2C[0] = 0.0f;
		unknown2C[1] = zero - cosine;
		unknown2C[2] = sine;
	}
#endif

	// FUNCTION: ENGINE 0x102FBE00
	content::MemberList* TankSolverProperties::CameraParams::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<CameraParams, float, 0>("p"),
				PROTO_OFFSET(CameraParams, baseDistance), "baseDistance" },
			{ content::GetMemberVectorMetaType<CameraParams, 1>("p"),
				PROTO_RAW_OFFSET(CameraParams, targetOffset), "targetOffset" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102FBED0
	content::MemberList* TankSolverProperties::SuspensionSpring::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<SuspensionSpring, float, 0>("p"),
				PROTO_OFFSET(SuspensionSpring, rayBufferHeight), "rayBufferHeight" },
			{ content::GetMemberPrimitiveMetaType<SuspensionSpring, float, 1>("p"),
				PROTO_OFFSET(SuspensionSpring, restHeightOffset), "restHeightOffset" },
			{ content::GetMemberPrimitiveMetaType<SuspensionSpring, float, 2>("p"),
				PROTO_OFFSET(SuspensionSpring, rayCenterOffset), "rayCenterOffset" },
			{ content::GetMemberPrimitiveMetaType<SuspensionSpring, float, 3>("p"),
				PROTO_OFFSET(SuspensionSpring, stretchDistance), "stretchDistance" },
			{ content::GetMemberPrimitiveMetaType<SuspensionSpring, float, 4>("p"),
				PROTO_OFFSET(SuspensionSpring, compressDistance), "compressDistance" },
			{ content::GetMemberPrimitiveMetaType<SuspensionSpring, float, 5>("p"),
				PROTO_OFFSET(SuspensionSpring, maxSpeedForDamping), "maxSpeedForDamping" },
			{ content::GetMemberPrimitiveMetaType<SuspensionSpring, float, 6>("p"),
				PROTO_OFFSET(SuspensionSpring, dampingScale), "dampingScale" },
			{ content::GetMemberVectorMetaType<SuspensionSpring, 7>("p"),
				PROTO_RAW_OFFSET(SuspensionSpring, torqueScale), "torqueScale" },
			{ content::GetMemberPrimitiveMetaType<SuspensionSpring, float, 8>("p"),
				PROTO_OFFSET(SuspensionSpring, maxSpeedForLength), "maxSpeedForLength" }
		};
		sList.members = sMembers;
		sList.count = 9;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102FC100
	content::MemberList* TankSolverProperties::Friction::Scales::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Scales, float, 0>("p"),
				PROTO_OFFSET(Scales, headingScale), "headingScale" },
			{ content::GetMemberVectorMetaType<Scales, 1>("p"),
				PROTO_RAW_OFFSET(Scales, headingTorqueScale), "headingTorqueScale" },
			{ content::GetMemberPrimitiveMetaType<Scales, float, 2>("p"),
				PROTO_OFFSET(Scales, lateralScale), "lateralScale" },
			{ content::GetMemberVectorMetaType<Scales, 3>("p"),
				PROTO_RAW_OFFSET(Scales, lateralTorqueScale), "lateralTorqueScale" },
			{ content::GetMemberPrimitiveMetaType<Scales, float, 4>("p"),
				PROTO_OFFSET(Scales, rollingScale), "rollingScale" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102FC260
	content::MemberList* TankSolverProperties::Reaction::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Reaction, float, 0>("p"),
				PROTO_OFFSET(Reaction, suspensionScale), "suspensionScale" },
			{ content::GetMemberPrimitiveMetaType<Reaction, float, 1>("p"),
				PROTO_OFFSET(Reaction, headingFrictionScale), "headingFrictionScale" },
			{ content::GetMemberPrimitiveMetaType<Reaction, float, 2>("p"),
				PROTO_OFFSET(Reaction, lateralFrictionScale), "lateralFrictionScale" },
			{ content::GetMemberPrimitiveMetaType<Reaction, float, 3>("p"),
				PROTO_OFFSET(Reaction, thrustScale), "thrustScale" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102FC3A0
	content::MemberList* TankSolverProperties::Animation::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Animation, float, 0>("p"),
				PROTO_OFFSET(Animation, treadTextureLength), "treadTextureLength" },
			{ content::GetMemberPrimitiveMetaType<Animation, float, 1>("p"),
				PROTO_OFFSET(Animation, wheelRadius), "wheelRadius" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102FC470
	content::MemberList* TankSolverProperties::DebugDraw::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<DebugDraw, bool, 0>(""),
				PROTO_OFFSET(DebugDraw, drawRays), "drawRays" },
			{ content::GetMemberPrimitiveMetaType<DebugDraw, bool, 1>(""),
				PROTO_OFFSET(DebugDraw, drawSpringCompression), "drawSpringCompression" },
			{ content::GetMemberPrimitiveMetaType<DebugDraw, bool, 2>(""),
				PROTO_OFFSET(DebugDraw, drawWheels), "drawWheels" },
			{ content::GetMemberPrimitiveMetaType<DebugDraw, bool, 3>(""),
				PROTO_OFFSET(DebugDraw, drawThrust), "drawThrust" },
			{ content::GetMemberPrimitiveMetaType<DebugDraw, float, 4>(""),
				PROTO_OFFSET(DebugDraw, thrustDrawScale), "thrustDrawScale" },
			{ content::GetMemberPrimitiveMetaType<DebugDraw, float, 5>(""),
				PROTO_OFFSET(DebugDraw, lateralOffset), "lateralOffset" },
			{ content::GetMemberPrimitiveMetaType<DebugDraw, float, 6>(""),
				PROTO_OFFSET(DebugDraw, forceOffsetAlongCompression), "forceOffsetAlongCompression" },
			{ content::GetMemberPrimitiveMetaType<DebugDraw, bool, 7>(""),
				PROTO_OFFSET(DebugDraw, drawFinalForce), "drawFinalForce" },
			{ content::GetMemberPrimitiveMetaType<DebugDraw, float, 8>(""),
				PROTO_OFFSET(DebugDraw, finalForceDrawScale), "finalForceDrawScale" },
			{ content::GetMemberPrimitiveMetaType<DebugDraw, bool, 9>(""),
				PROTO_OFFSET(DebugDraw, drawFinalTorque), "drawFinalTorque" },
			{ content::GetMemberPrimitiveMetaType<DebugDraw, float, 10>(""),
				PROTO_OFFSET(DebugDraw, finalTorqueDrawScale), "finalTorqueDrawScale" },
			{ content::GetMemberPrimitiveMetaType<DebugDraw, float, 11>(""),
				PROTO_OFFSET(DebugDraw, finalForceDisplayHeightOffset), "finalForceDisplayHeightOffset" }
		};
		sList.members = sMembers;
		sList.count = 12;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102F65F0
	content::MemberList* TankSolverBehaviour::JointData::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<JointData>(true, true, "p"),
				PROTO_NAME_OFFSET(JointData, suspensionJoint), "suspensionJoint" },
			{ content::GetMemberNameMetaType<JointData, 1>(true, true, "p"),
				PROTO_NAME_OFFSET(JointData, wheelJoint), "wheelJoint" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10302C70
	content::MemberList* AlignedAxleConstraintProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<AlignedAxleConstraintProperties, 0>(
				&AlignedAxleConstraintProperties::GetRotationAxis, &AlignedAxleConstraintProperties::SetRotationAxis, "p"),
				0, "rotationAxis" },
			{ content::GetMemberVectorMetaType<AlignedAxleConstraintProperties, 1>(
				&AlignedAxleConstraintProperties::GetFacingAxis, &AlignedAxleConstraintProperties::SetFacingAxis, "p"),
				0, "facingAxis" },
			{ content::GetMemberMetaType<AlignedAxleConstraintProperties, float, 0>(
				&AlignedAxleConstraintProperties::GetMaxForce, &AlignedAxleConstraintProperties::SetMaxForce, "p"),
				0, "maxForce" },
			{ content::GetMemberMetaType<AlignedAxleConstraintProperties, float, 1>(
				&AlignedAxleConstraintProperties::GetMaxVelocity, &AlignedAxleConstraintProperties::SetMaxVelocity, "p"),
				0, "maxVelocity" },
			{ content::GetMemberMetaType<AlignedAxleConstraintProperties, float, 2>(
				&AlignedAxleConstraintProperties::GetDampingConstant,
				&AlignedAxleConstraintProperties::SetDampingConstant, "p"), 0, "dampingConstant" },
			{ content::GetMemberMetaType<AlignedAxleConstraintProperties, float, 3>(
				&AlignedAxleConstraintProperties::GetSpringConstant,
				&AlignedAxleConstraintProperties::SetSpringConstant, "p"), 0, "springConstant" },
			{ content::GetMemberMetaType<AlignedAxleConstraintProperties, float, 4>(
				&AlignedAxleConstraintProperties::GetMaxAngle, &AlignedAxleConstraintProperties::SetMaxAngle, "p"),
				0, "maxAngle" },
			{ content::GetMemberMetaType<AlignedAxleConstraintProperties, float, 5>(
				&AlignedAxleConstraintProperties::GetMinAngle, &AlignedAxleConstraintProperties::SetMinAngle, "p"),
				0, "minAngle" },
			{ content::GetMemberMetaType<AlignedAxleConstraintProperties, float, 6>(
				&AlignedAxleConstraintProperties::GetDistanceForDamper,
				&AlignedAxleConstraintProperties::SetDistanceForDamper, "p"), 0, "distanceForDamper" },
			{ content::GetMemberMetaType<AlignedAxleConstraintProperties, float, 7>(
				&AlignedAxleConstraintProperties::GetDamperFactor, &AlignedAxleConstraintProperties::SetDamperFactor, "p"),
				0, "damperFactor" }
		};
		sList.members = sMembers;
		sList.count = 10;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10302EF0
	content::MemberList* AlignedAxleConstraint::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<AlignedAxleConstraint>(true, true, "p"),
				PROTO_NAME_OFFSET(AlignedAxleConstraint, childJointName), "childJointName" },
			{ content::GetMemberNameMetaType<AlignedAxleConstraint, 1>(true, true, "p"),
				PROTO_NAME_OFFSET(AlignedAxleConstraint, parentJointName), "parentJointName" },
			{ content::GetReferenceMetaType<AlignedAxleConstraint, AlignedAxleConstraintProperties>("p"),
				PROTO_OFFSET(AlignedAxleConstraint, properties), "properties" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10303000
	content::MemberList* TankSolverProperties::SoundParams::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberMetaType<SoundParams, float, 0>(&SoundParams::GetAngleThresholdForMovingTurret,
				&SoundParams::SetAngleThresholdForMovingTurret, "p"), 0, "angleThresholdForMovingTurret" },
			{ content::GetMemberPrimitiveMetaType<SoundParams, float, 1>("p"),
				PROTO_OFFSET(SoundParams, timeThresholdForTurretMoving), "timeThresholdForTurretMoving" },
			{ content::GetMemberPrimitiveMetaType<SoundParams, float, 2>("p"),
				PROTO_OFFSET(SoundParams, timeThresholdForTurretStopped), "timeThresholdForTurretStopped" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10303110
	content::MemberList* TankSolverProperties::SensorSpring::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberMetaType<SensorSpring, float, 0>(&SensorSpring::GetForwardSensorAngleDegrees,
				&SensorSpring::SetForwardSensorAngleDegrees, "p"), 0, "forwardSensorAngleDegrees" },
			{ content::GetMemberMetaType<SensorSpring, float, 1>(&SensorSpring::GetReverseSensorAngleDegrees,
				&SensorSpring::SetReverseSensorAngleDegrees, "p"), 0, "reverseSensorAngleDegrees" },
			{ content::GetMemberVectorMetaType<SensorSpring, 2>("p"),
				PROTO_RAW_OFFSET(SensorSpring, forwardSensorOffset), "forwardSensorOffset" },
			{ content::GetMemberVectorMetaType<SensorSpring, 3>("p"),
				PROTO_RAW_OFFSET(SensorSpring, reverseSensorOffset), "reverseSensorOffset" },
			{ content::GetMemberPrimitiveMetaType<SensorSpring, float, 4>("p"),
				PROTO_OFFSET(SensorSpring, rayBufferDistance), "rayBufferDistance" },
			{ content::GetMemberPrimitiveMetaType<SensorSpring, float, 5>("p"),
				PROTO_OFFSET(SensorSpring, forwardSensorContactOffset), "forwardSensorContactOffset" },
			{ content::GetMemberPrimitiveMetaType<SensorSpring, float, 6>("p"),
				PROTO_OFFSET(SensorSpring, reverseSensorContactOffset), "reverseSensorContactOffset" },
			{ content::GetMemberPrimitiveMetaType<SensorSpring, float, 7>("n"),
				PROTO_OFFSET(SensorSpring, compressDistance), "compressDistance" },
			{ content::GetMemberPrimitiveMetaType<SensorSpring, bool, 8>("p"),
				PROTO_OFFSET(SensorSpring, moveJoint), "moveJoint" },
			{ content::GetMemberPrimitiveMetaType<SensorSpring, float, 9>("p"),
				PROTO_OFFSET(SensorSpring, forwardSensorSpringScale), "forwardSensorSpringScale" },
			{ content::GetMemberPrimitiveMetaType<SensorSpring, float, 10>("p"),
				PROTO_OFFSET(SensorSpring, reverseSensorSpringScale), "reverseSensorSpringScale" },
			{ content::GetMemberPrimitiveMetaType<SensorSpring, float, 11>("p"),
				PROTO_OFFSET(SensorSpring, maxSpeedForDamping), "maxSpeedForDamping" },
			{ content::GetMemberPrimitiveMetaType<SensorSpring, float, 12>("p"),
				PROTO_OFFSET(SensorSpring, dampingScale), "dampingScale" },
			{ content::GetMemberVectorMetaType<SensorSpring, 13>("p"),
				PROTO_RAW_OFFSET(SensorSpring, torqueScale), "torqueScale" }
		};
		sList.members = sMembers;
		sList.count = 14;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10303430
	content::MemberList* TankSolverProperties::Friction::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetClassMetaType<Scales>(), PROTO_OFFSET(Friction, suspension), "suspension" },
			{ content::GetClassMetaType<Scales>(), PROTO_OFFSET(Friction, sensor), "sensor" },
			{ content::GetMemberPrimitiveMetaType<Friction, float, 0>("p"),
				PROTO_OFFSET(Friction, maxSlippingSpeed), "maxSlippingSpeed" },
			{ content::GetMemberPrimitiveMetaType<Friction, float, 1>("p"),
				PROTO_OFFSET(Friction, maxSlidingSpeed), "maxSlidingSpeed" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10303560
	content::MemberList* TankSolverProperties::Thrust::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberMetaType<Thrust, float, 0>(&Thrust::GetMaxForwardSpeedKmh,
				&Thrust::SetMaxForwardSpeedKmh, "p"), 0, "maxForwardSpeedKmh" },
			{ content::GetMemberMetaType<Thrust, float, 1>(&Thrust::GetMaxReverseSpeedKmh,
				&Thrust::SetMaxReverseSpeedKmh, "p"), 0, "maxReverseSpeedKmh" },
			{ content::GetMemberPrimitiveMetaType<Thrust, float, 2>("p"),
				PROTO_OFFSET(Thrust, counterGravityScale), "counterGravityScale" },
			{ content::GetMemberVectorMetaType<Thrust, 3>("p"),
				PROTO_RAW_OFFSET(Thrust, torqueScale), "torqueScale" },
			{ content::GetMemberMetaType<Thrust, float, 4>(&Thrust::GetSensorMaxClimbUpSpeedKmh,
				&Thrust::SetSensorMaxClimbUpSpeedKmh, "p"), 0, "sensorMaxClimbUpSpeedKmh" },
			{ content::GetMemberMetaType<Thrust, float, 5>(&Thrust::GetSensorMaxClimbDownSpeedKmh,
				&Thrust::SetSensorMaxClimbDownSpeedKmh, "p"), 0, "sensorMaxClimbDownSpeedKmh" },
			{ content::GetMemberVectorMetaType<Thrust, 6>("p"),
				PROTO_RAW_OFFSET(Thrust, sensorTorqueScale), "sensorTorqueScale" },
			{ content::GetMemberPrimitiveMetaType<Thrust, float, 7>("p"),
				PROTO_OFFSET(Thrust, counterGravitySensorScale), "counterGravitySensorScale" },
			{ content::GetMemberPrimitiveMetaType<Thrust, float, 8>("p"),
				PROTO_OFFSET(Thrust, maxSpeedForEBrake), "maxSpeedForEBrake" },
			{ content::GetMemberPrimitiveMetaType<Thrust, float, 9>("p"),
				PROTO_OFFSET(Thrust, eBrakeScale), "eBrakeScale" },
			{ content::GetMemberPrimitiveMetaType<Thrust, float, 10>("p"),
				PROTO_OFFSET(Thrust, thrustMultiplierAtZeroSpeed), "thrustMultiplierAtZeroSpeed" },
			{ content::GetMemberPrimitiveMetaType<Thrust, float, 11>("p"),
				PROTO_OFFSET(Thrust, maxSpeedForThrustMultiplier), "maxSpeedForThrustMultiplier" },
			{ content::GetMemberPrimitiveMetaType<Thrust, bool, 12>("p"),
				PROTO_OFFSET(Thrust, disableThrustMultiplierAtFullGrip), "disableThrustMultiplierAtFullGrip" },
			{ content::GetMemberMetaType<Thrust, float, 13>(&Thrust::GetUpwardThrustStartCutoffTiltDegrees,
				&Thrust::SetUpwardThrustStartCutoffTiltDegrees, "p"), 0, "upwardThrustStartCutoffTiltDegrees" },
			{ content::GetMemberMetaType<Thrust, float, 14>(&Thrust::GetUpwardThrustFullCutoffTiltDegrees,
				&Thrust::SetUpwardThrustFullCutoffTiltDegrees, "p"), 0, "upwardThrustFullCutoffTiltDegrees" }
		};
		sList.members = sMembers;
		sList.count = 15;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103038C0
	content::MemberList* TankSolverProperties::Steering::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberMetaType<Steering, float, 0>(&Steering::GetMaxTurnSpeedDegrees,
				&Steering::SetMaxTurnSpeedDegrees, "p"), 0, "maxTurnSpeedDegrees" },
			{ content::GetMemberPrimitiveMetaType<Steering, float, 1>("p"),
				PROTO_OFFSET(Steering, speedFractionAtMaxTurnSpeed), "speedFractionAtMaxTurnSpeed" },
			{ content::GetMemberPrimitiveMetaType<Steering, float, 2>("p"),
				PROTO_OFFSET(Steering, steeringForceScale), "steeringForceScale" },
			{ content::GetMemberVectorMetaType<Steering, 3>("p"),
				PROTO_RAW_OFFSET(Steering, steeringTorqueScale), "steeringTorqueScale" },
			{ content::GetMemberMetaType<Steering, float, 4>(&Steering::GetSensorMaxTurnSpeedDegrees,
				&Steering::SetSensorMaxTurnSpeedDegrees, "p"), 0, "sensorMaxTurnSpeedDegrees" },
			{ content::GetMemberPrimitiveMetaType<Steering, float, 5>("p"),
				PROTO_OFFSET(Steering, sensorSteeringForceScale), "sensorSteeringForceScale" },
			{ content::GetMemberVectorMetaType<Steering, 6>("p"),
				PROTO_RAW_OFFSET(Steering, sensorSteeringTorqueScale), "sensorSteeringTorqueScale" }
		};
		sList.members = sMembers;
		sList.count = 7;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10303A90
	content::MemberList* TankSolverProperties::InAir::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberMetaType<InAir, float, 0>(&InAir::GetMaxDownwardSpeedKmh,
				&InAir::SetMaxDownwardSpeedKmh, "p"), 0, "maxDownwardSpeedKmh" },
			{ content::GetMemberPrimitiveMetaType<InAir, float, 1>("p"),
				PROTO_OFFSET(InAir, headingDragScale), "headingDragScale" },
			{ content::GetMemberPrimitiveMetaType<InAir, float, 2>("p"),
				PROTO_OFFSET(InAir, lateralDragScale), "lateralDragScale" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10306380
	content::MemberList* TankSolverProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<TankSolverProperties, float, 0>("pn"),
				PROTO_OFFSET(TankSolverProperties, gravity), "gravity" },
			{ content::GetMemberMetaType<TankSolverProperties, float, 1>(
				&TankSolverProperties::GetMinSpeedToDamageCollidersKph,
				&TankSolverProperties::SetMinSpeedToDamageCollidersKph, "p"), 0, "minSpeedToDamageCollidersKph" },
			{ content::GetMemberPrimitiveMetaType<TankSolverProperties, float, 2>("p"),
				PROTO_OFFSET(TankSolverProperties, secondsBetweenDamage), "secondsBetweenDamage" },
			{ content::GetMemberPrimitiveMetaType<TankSolverProperties, float, 3>("p"),
				PROTO_OFFSET(TankSolverProperties, secondsBetweenCrushEffect), "secondsBetweenCrushEffect" },
			{ content::GetMemberPrimitiveMetaType<TankSolverProperties, float, 4>("p"),
				PROTO_OFFSET(TankSolverProperties, crushDeformStrength), "crushDeformStrength" },
			{ content::GetMemberPrimitiveMetaType<TankSolverProperties, float, 5>("p"),
				PROTO_OFFSET(TankSolverProperties, crushDeformTime), "crushDeformTime" },
			{ content::GetMemberPrimitiveMetaType<TankSolverProperties, float, 6>("p"),
				PROTO_OFFSET(TankSolverProperties, crushDeformAmount), "crushDeformAmount" },
			{ content::GetMemberMetaType<TankSolverProperties, float, 7>(
				&TankSolverProperties::GetMaxTiltAngleDegrees, &TankSolverProperties::SetMaxTiltAngleDegrees, "p"),
				0, "maxTiltAngleDegrees" },
			{ content::GetEnumMetaType<ForceDistributionType>(),
				PROTO_RAW_OFFSET(TankSolverProperties, treadForceDistributionType), "treadForceDistributionType" },
			{ content::GetClassMetaType<CameraParams>(), PROTO_OFFSET(TankSolverProperties, cameraParams),
				"cameraParams" },
			{ content::GetClassMetaType<SoundParams>(), PROTO_OFFSET(TankSolverProperties, soundParams),
				"soundParams" },
			{ content::GetClassMetaType<SuspensionSpring>(), PROTO_OFFSET(TankSolverProperties, suspensionSpring),
				"suspensionSpring" },
			{ content::GetClassMetaType<SensorSpring>(), PROTO_OFFSET(TankSolverProperties, sensorSpring),
				"sensorSpring" },
			{ content::GetClassMetaType<Friction>(), PROTO_OFFSET(TankSolverProperties, friction), "friction" },
			{ content::GetClassMetaType<Thrust>(), PROTO_OFFSET(TankSolverProperties, thrust), "thrust" },
			{ content::GetClassMetaType<Steering>(), PROTO_OFFSET(TankSolverProperties, steering), "steering" },
			{ content::GetClassMetaType<Reaction>(), PROTO_OFFSET(TankSolverProperties, reaction), "reaction" },
			{ content::GetClassMetaType<Animation>(), PROTO_OFFSET(TankSolverProperties, animation), "animation" },
			{ content::GetClassMetaType<DebugDraw>(), PROTO_OFFSET(TankSolverProperties, debugDraw), "debugDraw" }
		};
		sList.members = sMembers;
		sList.count = 19;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10306780
	content::MemberList* TankSolverBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, TankSolverBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<LeftTreadJoints, JointArray>(
				content::GetClassMetaType<JointData>(), "p"), PROTO_OFFSET(TankSolverBehaviour, leftTreadJoints),
				"leftTreadJoints" },
			{ content::GetArrayDynamicMetaType<RightTreadJoints, JointArray>(
				content::GetClassMetaType<JointData>(), "p"), PROTO_OFFSET(TankSolverBehaviour, rightTreadJoints),
				"rightTreadJoints" },
			{ content::GetArrayDynamicMetaType<ForwardSensorJoints, JointArray>(
				content::GetClassMetaType<JointData>(), "p"), PROTO_OFFSET(TankSolverBehaviour, forwardSensorJoints),
				"forwardSensorJoints" },
			{ content::GetArrayDynamicMetaType<ReverseSensorJoints, JointArray>(
				content::GetClassMetaType<JointData>(), "p"), PROTO_OFFSET(TankSolverBehaviour, reverseSensorJoints),
				"reverseSensorJoints" },
			{ content::GetClassMetaType<TreadEffects>(), PROTO_OFFSET(TankSolverBehaviour, treadEffects),
				"treadEffects" },
			{ content::GetReferenceMetaType<TankSolverBehaviour, TankSolverProperties>("pn"),
				PROTO_OFFSET(TankSolverBehaviour, sharedProperties), "sharedProperties" },
			{ content::GetArrayDynamicMetaType<TankSolverBehaviour, ConstraintArray>(
				content::GetClassMetaType<AlignedAxleConstraint>(), "p"),
				PROTO_OFFSET(TankSolverBehaviour, cannonAxleConstraints), "cannonAxleConstraints" },
			{ content::GetClassMetaType<AlignedAxleConstraint>(),
				PROTO_OFFSET(TankSolverBehaviour, turretAxleConstraint), "turretAxleConstraint" },
			{ content::GetNameMetaType<TankSolverBehaviour>(true, true, "p"),
				PROTO_NAME_OFFSET(TankSolverBehaviour, audioPatchName), "audioPatchName" }
		};
		sList.members = sMembers;
		sList.count = 9;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102F5960
// FUNCTION: ENGINE 0x102F5B10
// FUNCTION: ENGINE 0x102F5B50
// FUNCTION: ENGINE 0x102F5B90
// FUNCTION: ENGINE 0x102F5C20
// FUNCTION: ENGINE 0x102F5C60
// FUNCTION: ENGINE 0x102F5CA0
// FUNCTION: ENGINE 0x102F5D60
// FUNCTION: ENGINE 0x102F5D70
// FUNCTION: ENGINE 0x102F5DB0
// FUNCTION: ENGINE 0x102F5DF0
// FUNCTION: ENGINE 0x102F5E30
// FUNCTION: ENGINE 0x102F5E80
// FUNCTION: ENGINE 0x102F5E90
// FUNCTION: ENGINE 0x102F5EA0
// FUNCTION: ENGINE 0x102F5EB0
// FUNCTION: ENGINE 0x102F5EC0
// FUNCTION: ENGINE 0x102F5ED0
// FUNCTION: ENGINE 0x102F5EE0
// FUNCTION: ENGINE 0x102F5EF0
// FUNCTION: ENGINE 0x102F5F00
// FUNCTION: ENGINE 0x102F5F10
// FUNCTION: ENGINE 0x102F6070
// FUNCTION: ENGINE 0x102F6080
// FUNCTION: ENGINE 0x102F6090
// FUNCTION: ENGINE 0x102F60A0
// FUNCTION: ENGINE 0x102F60B0
// FUNCTION: ENGINE 0x102F60C0
// FUNCTION: ENGINE 0x102F9660
// FUNCTION: ENGINE 0x102F97C0
// FUNCTION: ENGINE 0x102F9800
// FUNCTION: ENGINE 0x102F9A40
// FUNCTION: ENGINE 0x102F9A80
// FUNCTION: ENGINE 0x102F9AC0
// FUNCTION: ENGINE 0x102F9B00
// FUNCTION: ENGINE 0x102F9B40
// FUNCTION: ENGINE 0x102F9B80
// FUNCTION: ENGINE 0x102F9BC0
// FUNCTION: ENGINE 0x102F9C00
// FUNCTION: ENGINE 0x102F9C40
// FUNCTION: ENGINE 0x102F9D40
// FUNCTION: ENGINE 0x102F9D80
// FUNCTION: ENGINE 0x102F9DC0
// FUNCTION: ENGINE 0x102F9E00
// FUNCTION: ENGINE 0x102F9E40
// FUNCTION: ENGINE 0x102F9E80
// FUNCTION: ENGINE 0x102F9EC0
// FUNCTION: ENGINE 0x102F9F00
// FUNCTION: ENGINE 0x102F9F40
// FUNCTION: ENGINE 0x102F9F80
// FUNCTION: ENGINE 0x102F9FC0
// FUNCTION: ENGINE 0x102FA000
// FUNCTION: ENGINE 0x102FA040
// FUNCTION: ENGINE 0x102FA080
// FUNCTION: ENGINE 0x102FA540
// FUNCTION: ENGINE 0x102FA580
// FUNCTION: ENGINE 0x102FA5C0
// FUNCTION: ENGINE 0x102FA600
// FUNCTION: ENGINE 0x102FA640
// FUNCTION: ENGINE 0x102FA680
// FUNCTION: ENGINE 0x103012F0
// FUNCTION: ENGINE 0x10301350
// FUNCTION: ENGINE 0x103013B0
// FUNCTION: ENGINE 0x10301410
// FUNCTION: ENGINE 0x10301470
// FUNCTION: ENGINE 0x103014D0
// FUNCTION: ENGINE 0x10301530
// FUNCTION: ENGINE 0x10301930
// FUNCTION: ENGINE 0x103019B0
// FUNCTION: ENGINE 0x10301A30
// FUNCTION: ENGINE 0x10301AB0
// FUNCTION: ENGINE 0x10301B30
// FUNCTION: ENGINE 0x10301BB0
// FUNCTION: ENGINE 0x10301C30
// FUNCTION: ENGINE 0x10301CB0
// FUNCTION: ENGINE 0x10301D30
// FUNCTION: ENGINE 0x10301DB0
// FUNCTION: ENGINE 0x10301E30
// FUNCTION: ENGINE 0x10301E90
// FUNCTION: ENGINE 0x10301F10
// FUNCTION: ENGINE 0x10301F90
// FUNCTION: ENGINE 0x10302010
// FUNCTION: ENGINE 0x10302090
// FUNCTION: ENGINE 0x10302110
// FUNCTION: ENGINE 0x10302190
// FUNCTION: ENGINE 0x10302210
// FUNCTION: ENGINE 0x10302290
// FUNCTION: ENGINE 0x10302310
// FUNCTION: ENGINE 0x10302390
// FUNCTION: ENGINE 0x10302410
// FUNCTION: ENGINE 0x10302490
// FUNCTION: ENGINE 0x10302510
// FUNCTION: ENGINE 0x10302590
// FUNCTION: ENGINE 0x103025F0
// FUNCTION: ENGINE 0x10302650
// FUNCTION: ENGINE 0x103026B0
// FUNCTION: ENGINE 0x10302710
// FUNCTION: ENGINE 0x10302770
// FUNCTION: ENGINE 0x10305C30
// FUNCTION: ENGINE 0x10305C90
// FUNCTION: ENGINE 0x10305CF0
// FUNCTION: ENGINE 0x10305D50
// FUNCTION: ENGINE 0x10305DB0
// FUNCTION: ENGINE 0x10305E10
// FUNCTION: ENGINE 0x10306BD0
// FUNCTION: ENGINE 0x10D82CC0
// FUNCTION: ENGINE 0x102FA860
// FUNCTION: ENGINE 0x10302AD0
// FUNCTION: ENGINE 0x10302B70
// FUNCTION: ENGINE 0x10306010
// FUNCTION: ENGINE 0x10D82CD0
// FUNCTION: ENGINE 0x102F5A60
// FUNCTION: ENGINE 0x102FAF90
// FUNCTION: ENGINE 0x102FB080
// FUNCTION: ENGINE 0x10306250

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102F4AD0
// FUNCTION: ENGINE 0x102F4C20
// FUNCTION: ENGINE 0x102F4DF0
// FUNCTION: ENGINE 0x102F5890
// FUNCTION: ENGINE 0x102F58F0
// FUNCTION: ENGINE 0x102F5BA0
// FUNCTION: ENGINE 0x102F5BE0
// FUNCTION: ENGINE 0x102F5CE0
// FUNCTION: ENGINE 0x102F5D20
// FUNCTION: ENGINE 0x102F5F20
// FUNCTION: ENGINE 0x102F5F60
// FUNCTION: ENGINE 0x102F6170
// FUNCTION: ENGINE 0x102F6450
// FUNCTION: ENGINE 0x102F6810
// FUNCTION: ENGINE 0x102F6820
// FUNCTION: ENGINE 0x102F9780
// FUNCTION: ENGINE 0x102F9840
// FUNCTION: ENGINE 0x102F9880
// FUNCTION: ENGINE 0x102F98C0
// FUNCTION: ENGINE 0x102F9900
// FUNCTION: ENGINE 0x102F9940
// FUNCTION: ENGINE 0x102F9980
// FUNCTION: ENGINE 0x102F99C0
// FUNCTION: ENGINE 0x102F9A00
// FUNCTION: ENGINE 0x102F9C80
// FUNCTION: ENGINE 0x102F9CC0
// FUNCTION: ENGINE 0x102F9D00
// FUNCTION: ENGINE 0x102FA0C0
// FUNCTION: ENGINE 0x102FA100
// FUNCTION: ENGINE 0x102FA140
// FUNCTION: ENGINE 0x102FA180
// FUNCTION: ENGINE 0x102FA1C0
// FUNCTION: ENGINE 0x102FA200
// FUNCTION: ENGINE 0x102FA240
// FUNCTION: ENGINE 0x102FA280
// FUNCTION: ENGINE 0x102FA2C0
// FUNCTION: ENGINE 0x102FA300
// FUNCTION: ENGINE 0x102FA340
// FUNCTION: ENGINE 0x102FA380
// FUNCTION: ENGINE 0x102FA3C0
// FUNCTION: ENGINE 0x102FA400
// FUNCTION: ENGINE 0x102FA440
// FUNCTION: ENGINE 0x102FA480
// FUNCTION: ENGINE 0x102FA4C0
// FUNCTION: ENGINE 0x102FA500
// FUNCTION: ENGINE 0x102FA770
// FUNCTION: ENGINE 0x102FA780
// FUNCTION: ENGINE 0x102FA7B0
// FUNCTION: ENGINE 0x102FA7F0
// FUNCTION: ENGINE 0x102FA820
// FUNCTION: ENGINE 0x102FA840
// FUNCTION: ENGINE 0x102FA8C0
// FUNCTION: ENGINE 0x102FA9B0
// FUNCTION: ENGINE 0x102FA9C0
// FUNCTION: ENGINE 0x102FA9F0
// FUNCTION: ENGINE 0x102FAA00
// FUNCTION: ENGINE 0x102FAA30
// FUNCTION: ENGINE 0x102FAA60
// FUNCTION: ENGINE 0x102FAAC0
// FUNCTION: ENGINE 0x102FAB30
// FUNCTION: ENGINE 0x102FABA0
// FUNCTION: ENGINE 0x102FABC0
// FUNCTION: ENGINE 0x102FABE0
// FUNCTION: ENGINE 0x102FAC00
// FUNCTION: ENGINE 0x102FAC20
// FUNCTION: ENGINE 0x102FAC40
// FUNCTION: ENGINE 0x102FAC60
// FUNCTION: ENGINE 0x102FAC80
// FUNCTION: ENGINE 0x102FACA0
// FUNCTION: ENGINE 0x102FACC0
// FUNCTION: ENGINE 0x102FACE0
// FUNCTION: ENGINE 0x102FAD00
// FUNCTION: ENGINE 0x102FAD20
// FUNCTION: ENGINE 0x102FAD40
// FUNCTION: ENGINE 0x102FAD60
// FUNCTION: ENGINE 0x102FAD80
// FUNCTION: ENGINE 0x102FADA0
// FUNCTION: ENGINE 0x102FADC0
// FUNCTION: ENGINE 0x102FADE0
// FUNCTION: ENGINE 0x102FAE00
// FUNCTION: ENGINE 0x102FAE20
// FUNCTION: ENGINE 0x102FAE40
// FUNCTION: ENGINE 0x102FAE60
// FUNCTION: ENGINE 0x102FAE80
// FUNCTION: ENGINE 0x102FAEA0
// FUNCTION: ENGINE 0x102FAED0
// FUNCTION: ENGINE 0x102FAEF0
// FUNCTION: ENGINE 0x102FAF50
// FUNCTION: ENGINE 0x102FAF70
// FUNCTION: ENGINE 0x102FB120

// The engine's copies of the property classes of the float properties (the solver's sound parameters): explicit
// instantiations, most members have no caller of their own
// (the reader of the text form is left to the engine: 95 % )
template<> bool om::DynamicProperty<float>::ReadText(const om::TextValue* parent);
template class om::DynamicProperty<float>;
template class om::CommandMember0Const<om::DynamicProperty<float>, om::DynamicProperty<float>, float>;
template class om::CommandMember1<om::DynamicProperty<float>, om::DynamicProperty<float>, void, float>;
template class om::DelegateProperty<float>;
template class om::Command0<float>;
template class om::Command1<void, float>;

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102F4E30
// FUNCTION: ENGINE 0x102F6240
// FUNCTION: ENGINE 0x102F6250
// FUNCTION: ENGINE 0x102F62C0
// FUNCTION: ENGINE 0x102F6360
// FUNCTION: ENGINE 0x102F63E0
// FUNCTION: ENGINE 0x102F6500
// FUNCTION: ENGINE 0x102F6510
// FUNCTION: ENGINE 0x102FB230
// FUNCTION: ENGINE 0x102FB250
// FUNCTION: ENGINE 0x102FB3F0
// FUNCTION: ENGINE 0x102FB420
// FUNCTION: ENGINE 0x102FB530
// FUNCTION: ENGINE 0x102FB540
// FUNCTION: ENGINE 0x102FB550
// FUNCTION: ENGINE 0x102FB570
// FUNCTION: ENGINE 0x102FB580
// FUNCTION: ENGINE 0x102FB590
// FUNCTION: ENGINE 0x102FB5A0
// FUNCTION: ENGINE 0x102FB5B0
// FUNCTION: ENGINE 0x102FB5F0
// FUNCTION: ENGINE 0x102FB610
// FUNCTION: ENGINE 0x102FB620
// FUNCTION: ENGINE 0x102FB630
// FUNCTION: ENGINE 0x102FB660
// FUNCTION: ENGINE 0x102FB690
// FUNCTION: ENGINE 0x102FB6A0
// FUNCTION: ENGINE 0x102FB6C0
// FUNCTION: ENGINE 0x102FB6D0
// FUNCTION: ENGINE 0x102FB6F0
// FUNCTION: ENGINE 0x102FB780
// FUNCTION: ENGINE 0x102FB790
// FUNCTION: ENGINE 0x102FB7B0
// FUNCTION: ENGINE 0x102FB7C0
// FUNCTION: ENGINE 0x102FB7D0
// FUNCTION: ENGINE 0x102FB860
// FUNCTION: ENGINE 0x102FB870
// FUNCTION: ENGINE 0x102FB890
// FUNCTION: ENGINE 0x102FB8C0
// FUNCTION: ENGINE 0x102FB8F0
// FUNCTION: ENGINE 0x102FB920
// FUNCTION: ENGINE 0x102FB940
// FUNCTION: ENGINE 0x102FB970
// FUNCTION: ENGINE 0x102FB990
// FUNCTION: ENGINE 0x102FBB60
// FUNCTION: ENGINE 0x102FBB80
// FUNCTION: ENGINE 0x102FBBA0
// FUNCTION: ENGINE 0x102FBBC0
// FUNCTION: ENGINE 0x102FBBD0
// FUNCTION: ENGINE 0x102FBC00
// FUNCTION: ENGINE 0x102FBC20
// FUNCTION: ENGINE 0x102FBC40
// FUNCTION: ENGINE 0x102FBC50
// FUNCTION: ENGINE 0x102FBC60
// FUNCTION: ENGINE 0x102FBC80
// FUNCTION: ENGINE 0x102FBCB0
// FUNCTION: ENGINE 0x102FBCD0
// FUNCTION: ENGINE 0x102FBD10
// FUNCTION: ENGINE 0x102FBD30
// FUNCTION: ENGINE 0x102FBD50
// FUNCTION: ENGINE 0x102FBD70
// FUNCTION: ENGINE 0x102FBD80
// FUNCTION: ENGINE 0x102FBDA0

// The engine's copies of every member of the arrays of joints and of axle constraints
template class container::ArrayDynamic<proto::TankSolverBehaviour::JointData, container::AllocatorNew>;
template class container::ArrayDynamic<proto::AlignedAxleConstraint, container::AllocatorNew>;

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102F5850
// FUNCTION: ENGINE 0x102F5860
// FUNCTION: ENGINE 0x102F5870
// FUNCTION: ENGINE 0x102F5880
// FUNCTION: ENGINE 0x102F58B0
// FUNCTION: ENGINE 0x102F58D0
// FUNCTION: ENGINE 0x102F5920
// FUNCTION: ENGINE 0x102F59E0
// FUNCTION: ENGINE 0x102F95B0
// FUNCTION: ENGINE 0x102F95C0
// FUNCTION: ENGINE 0x102FAAA0
// FUNCTION: ENGINE 0x102FB030

// Kept copies (more template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10301690
// FUNCTION: ENGINE 0x10301860
// FUNCTION: ENGINE 0x103018B0
// FUNCTION: ENGINE 0x10302880
// FUNCTION: ENGINE 0x10302890
// FUNCTION: ENGINE 0x103028B0
// FUNCTION: ENGINE 0x10302920
// FUNCTION: ENGINE 0x103029B0
// FUNCTION: ENGINE 0x10305E80
// FUNCTION: ENGINE 0x10306A90
// FUNCTION: ENGINE 0x10306AD0
// FUNCTION: ENGINE 0x10306B40
// FUNCTION: ENGINE 0x10306EF0
// FUNCTION: ENGINE 0x10306FC0
// FUNCTION: ENGINE 0x103073C0
// FUNCTION: ENGINE 0x103012E0
// FUNCTION: ENGINE 0x103027E0
// FUNCTION: ENGINE 0x10302810
// FUNCTION: ENGINE 0x103028E0
// FUNCTION: ENGINE 0x10302A90
// FUNCTION: ENGINE 0x10302B20
// FUNCTION: ENGINE 0x10302B60
// FUNCTION: ENGINE 0x10305FE0
// FUNCTION: ENGINE 0x10306130
// FUNCTION: ENGINE 0x10306160
// FUNCTION: ENGINE 0x103061A0
// FUNCTION: ENGINE 0x103061F0
// FUNCTION: ENGINE 0x10306A30
// FUNCTION: ENGINE 0x10306A50
// FUNCTION: ENGINE 0x10306B90
// FUNCTION: ENGINE 0x10306D20
// FUNCTION: ENGINE 0x10306EB0
