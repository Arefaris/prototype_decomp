#include "code/proto/behaviours/tanksolver.h"
#include "code/core/refptr.h"

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
