// The reflected classes of the tank solver (RTTI and reflection names; unit 0x102F3D40 - 0x10307xxx, no assert path
// names it, the file name is a guess): the properties of the solver (proto::TankSolverProperties and the parameter
// groups it embeds) and of its axle constraints (proto::AlignedAxleConstraintProperties), the axle constraint
// (proto::AlignedAxleConstraint) and the element of the tread joint arrays (proto::TankSolverBehaviour::JointData).
// The reflected names are original, the remaining names and the layouts between the reflected members are guessed.
// The reflection and the array helpers are reconstructed; the accessors of the properties, the constructors and the
// solver's own code are left to the engine (declared with their addresses, mapped in symbols.txt).
#ifndef PROTO_BEHAVIOURS_TANKSOLVER_H
#define PROTO_BEHAVIOURS_TANKSOLVER_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/content/vectormetatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/proto/arrayhelper.h"
#include "code/math/vector.h"

namespace proto
{
	// The properties of an axle constraint that keeps a turret or cannon aligned with its parent (0x4C bytes). The
	// angles are kept in radians and reflected in degrees.
	class AlignedAxleConstraintProperties : public content::MetaLoadObject
	{
	public:
		AlignedAxleConstraintProperties(); //@0x102F6850
		static content::ClassInfo* GetClassInfo(); //@0x102F3D40
		static content::MemberList* GetMembers();

		const math::Vector* GetRotationAxis() const; //@0x102F4280
		void SetRotationAxis(const math::Vector* axis); //@0x102F6920
		const math::Vector* GetFacingAxis() const; //@0x102F4290
		void SetFacingAxis(const math::Vector* axis); //@0x102F6960
		float GetMaxForce() const; //@0x102F42D0
		void SetMaxForce(float value); //@0x102F42B0
		float GetMaxVelocity() const; //@0x102F4300
		void SetMaxVelocity(float degrees); //@0x102F42E0
		float GetDampingConstant() const; //@0x102F4340
		void SetDampingConstant(float value); //@0x102F4320
		float GetSpringConstant() const; //@0x102F4370
		void SetSpringConstant(float value); //@0x102F4350
		float GetMaxAngle() const; //@0x102F43A0
		void SetMaxAngle(float degrees); //@0x102F4380
		float GetMinAngle() const; //@0x102F43E0
		void SetMinAngle(float degrees); //@0x102F43C0
		float GetDistanceForDamper() const; //@0x102F4420
		void SetDistanceForDamper(float degrees); //@0x102F4400
		float GetDamperFactor() const; //@0x102F4460
		void SetDamperFactor(float value); //@0x102F4440

		math::Vector rotationAxis;  // +8
		math::Vector facingAxis;  // +0x14
		math::Vector perpendicularAxis;  // +0x20
		float maxForce;  // +0x2C
		float maxVelocity;  // +0x30
		float dampingConstant;  // +0x34
		float springConstant;  // +0x38
		float maxAngle;  // +0x3C
		float minAngle;  // +0x40
		float distanceForDamper;  // +0x44
		float damperFactor;  // +0x48
	};

	// One axle constraint of a solver (0x38 bytes): the two joints it ties and its properties
	class AlignedAxleConstraint
	{
	public:
		AlignedAxleConstraint(); //@0x102FC830
		// 0x102FAAC0 / 0x102FAB30 are the out-of-line copies of these; the containers' code has them inline
		AlignedAxleConstraint(const AlignedAxleConstraint& other)
			: childJointName(other.childJointName), parentJointName(other.parentJointName)
		{
			unknown10 = other.unknown10;
			unknown14 = other.unknown14;
			unknown18 = other.unknown18;
			unknown1C = other.unknown1C;
			handles[0] = other.handles[0];
			handles[1] = other.handles[1];
			handles[2] = other.handles[2];
			handles[3] = other.handles[3];
			properties = other.properties;
		}
		AlignedAxleConstraint& operator=(const AlignedAxleConstraint& other)
		{
			childJointName = other.childJointName;
			parentJointName = other.parentJointName;
			unknown10 = other.unknown10;
			unknown14 = other.unknown14;
			unknown18 = other.unknown18;
			unknown1C = other.unknown1C;
			handles[0] = other.handles[0];
			handles[1] = other.handles[1];
			handles[2] = other.handles[2];
			handles[3] = other.handles[3];
			properties = other.properties;
			return *this;
		}
		~AlignedAxleConstraint(); //@0x102F69D0
		static content::ClassInfo* GetClassInfo(); //@0x102F3D80
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> childJointName;  // +0
		core::Name<core::CaseSensitiveKey> parentJointName;  // +8
		int unknown10;
		int unknown14;
		unsigned short unknown18;
		int unknown1C;
		int handles[4];  // +0x20
		AlignedAxleConstraintProperties* properties;  // +0x30
		int unknown34;
	};

	class TankSolverProperties : public content::MetaLoadObject
	{
	public:
		// The solver's camera (0x10 bytes)
		struct CameraParams
		{
			static content::ClassInfo* GetClassInfo(); //@0x102F3DC0
			static content::MemberList* GetMembers(); //@0x102FBE00

			float baseDistance;  // +0
			math::Vector targetOffset;  // +4
		};

		// What the turret does to the sound (0xC bytes)
		struct SoundParams
		{
			static content::ClassInfo* GetClassInfo(); //@0x102F3E00
			static content::MemberList* GetMembers();

			float GetAngleThresholdForMovingTurret() const; //@0x102F4A40
			void SetAngleThresholdForMovingTurret(float degrees); //@0x102F4A20

			float angleThresholdForMovingTurret;  // +0 (radians)
			float timeThresholdForTurretMoving;  // +4
			float timeThresholdForTurretStopped;  // +8
		};

		// The spring of a wheel's suspension (0x2C bytes)
		struct SuspensionSpring
		{
			static content::ClassInfo* GetClassInfo(); //@0x102F3E40
			static content::MemberList* GetMembers(); //@0x102FBED0

			float rayBufferHeight;  // +0
			float restHeightOffset;  // +4
			float rayCenterOffset;  // +8
			float stretchDistance;  // +0xC
			float compressDistance;  // +0x10
			float maxSpeedForDamping;  // +0x14
			float dampingScale;  // +0x18
			math::Vector torqueScale;  // +0x1C
			float maxSpeedForLength;  // +0x28
		};

		// The springs of the sensors in front of and behind the tank (0x80 bytes)
		struct SensorSpring
		{
			static content::ClassInfo* GetClassInfo(); //@0x102F3E80
			static content::MemberList* GetMembers();

			float GetForwardSensorAngleDegrees() const; //@0x102F4C30
			void SetForwardSensorAngleDegrees(float degrees); //@0x102F4C40
			float GetReverseSensorAngleDegrees() const; //@0x102F4CE0
			void SetReverseSensorAngleDegrees(float degrees); //@0x102F4CF0

			float forwardSensorAngle;  // +0 (radians)
			float reverseSensorAngle;  // +4
			float unknown8[3];
			float unknown14[3];
			float unknown20[3];
			float unknown2C[3];
			math::Vector forwardSensorOffset;  // +0x38
			math::Vector reverseSensorOffset;  // +0x44
			float rayBufferDistance;  // +0x50
			float forwardSensorContactOffset;  // +0x54
			float reverseSensorContactOffset;  // +0x58
			float compressDistance;  // +0x5C
			bool moveJoint;  // +0x60
			float forwardSensorSpringScale;  // +0x64
			float reverseSensorSpringScale;  // +0x68
			float maxSpeedForDamping;  // +0x6C
			float dampingScale;  // +0x70
			math::Vector torqueScale;  // +0x74
		};

		// How the force of a tread is spread over its joints (names from the reflection)
		enum ForceDistributionType
		{
			ForceDistributionConstant,
			ForceDistributionUnknown1,
			ForceDistributionUnknown2
		};

		// The friction of the suspension and of the sensors
		struct Friction
		{
			// The scales of one group of friction (0x24 bytes)
			struct Scales
			{
				static content::ClassInfo* GetClassInfo(); //@0x102F3F00
				static content::MemberList* GetMembers(); //@0x102FC100

				float headingScale;  // +0
				math::Vector headingTorqueScale;  // +4
				float lateralScale;  // +0x10
				math::Vector lateralTorqueScale;  // +0x14
				float rollingScale;  // +0x20
			};

			static content::ClassInfo* GetClassInfo(); //@0x102F3F40
			static content::MemberList* GetMembers();

			Scales suspension;  // +0
			Scales sensor;  // +0x24
			float maxSlippingSpeed;  // +0x48
			float maxSlidingSpeed;  // +0x4C
		};

		// The thrust (0x54 bytes); the speeds are reflected in kilometres per hour
		struct Thrust
		{
			static content::ClassInfo* GetClassInfo(); //@0x102F3F80
			static content::MemberList* GetMembers();

			float GetMaxForwardSpeedKmh() const; //@0x102F4E50
			void SetMaxForwardSpeedKmh(float kmh); //@0x102F4E60
			float GetMaxReverseSpeedKmh() const; //@0x102F4E80
			void SetMaxReverseSpeedKmh(float kmh); //@0x102F4E90
			float GetSensorMaxClimbUpSpeedKmh() const; //@0x102F4EB0
			void SetSensorMaxClimbUpSpeedKmh(float kmh); //@0x102F4EC0
			float GetSensorMaxClimbDownSpeedKmh() const; //@0x102F4EE0
			void SetSensorMaxClimbDownSpeedKmh(float kmh); //@0x102F4EF0
			float GetUpwardThrustStartCutoffTiltDegrees() const; //@0x102F4F10
			void SetUpwardThrustStartCutoffTiltDegrees(float degrees); //@0x102F4F20
			float GetUpwardThrustFullCutoffTiltDegrees() const; //@0x102F4F50
			void SetUpwardThrustFullCutoffTiltDegrees(float degrees); //@0x102F4F60

			float maxForwardSpeed;  // +0 (metres per second)
			float maxReverseSpeed;  // +4
			float counterGravityScale;  // +8
			math::Vector torqueScale;  // +0xC
			float sensorMaxClimbUpSpeed;  // +0x18
			float sensorMaxClimbDownSpeed;  // +0x1C
			math::Vector sensorTorqueScale;  // +0x20
			float counterGravitySensorScale;  // +0x2C
			float maxSpeedForEBrake;  // +0x30
			float eBrakeScale;  // +0x34
			float thrustMultiplierAtZeroSpeed;  // +0x38
			float maxSpeedForThrustMultiplier;  // +0x3C
			bool disableThrustMultiplierAtFullGrip;  // +0x40
			float upwardThrustStartCutoffTilt;  // +0x44 (radians)
			float upwardThrustStartCutoffCosine;  // +0x48
			float upwardThrustFullCutoffTilt;  // +0x4C
			float upwardThrustFullCutoffCosine;  // +0x50
		};

		// The steering (0x38 bytes)
		struct Steering
		{
			static content::ClassInfo* GetClassInfo(); //@0x102F3FC0
			static content::MemberList* GetMembers();

			float GetMaxTurnSpeedDegrees() const; //@0x102F5010
			void SetMaxTurnSpeedDegrees(float degrees); //@0x102F5020
			float GetSensorMaxTurnSpeedDegrees() const; //@0x102F5040
			void SetSensorMaxTurnSpeedDegrees(float degrees); //@0x102F5050

			float maxTurnSpeed;  // +0 (radians per second)
			float speedFractionAtMaxTurnSpeed;  // +4
			float steeringForceScale;  // +8
			math::Vector steeringTorqueScale;  // +0xC
			float sensorMaxTurnSpeed;  // +0x18
			float sensorSteeringForceScale;  // +0x1C
			math::Vector sensorSteeringTorqueScale;  // +0x20
			int unknown2C[3];
		};

		// The drag in the air (0xC bytes)
		struct InAir
		{
			static content::ClassInfo* GetClassInfo(); //@0x102F4000
			static content::MemberList* GetMembers();

			float GetMaxDownwardSpeedKmh() const; //@0x102F50B0
			void SetMaxDownwardSpeedKmh(float kmh); //@0x102F50C0

			float maxDownwardSpeed;  // +0 (metres per second)
			float headingDragScale;  // +4
			float lateralDragScale;  // +8
		};

		// The reaction to the tank's own movement (0x10 bytes)
		struct Reaction
		{
			static content::ClassInfo* GetClassInfo(); //@0x102F4040
			static content::MemberList* GetMembers(); //@0x102FC260

			float suspensionScale;  // +0
			float headingFrictionScale;  // +4
			float lateralFrictionScale;  // +8
			float thrustScale;  // +0xC
		};

		// The animation of the treads (8 bytes)
		struct Animation
		{
			static content::ClassInfo* GetClassInfo(); //@0x102F4080
			static content::MemberList* GetMembers(); //@0x102FC3A0

			float treadTextureLength;  // +0
			float wheelRadius;  // +4
		};

		// What the solver draws for debugging (0x24 bytes)
		struct DebugDraw
		{
			static content::ClassInfo* GetClassInfo(); //@0x102F40C0
			static content::MemberList* GetMembers(); //@0x102FC470

			bool drawRays;  // +0
			bool drawSpringCompression;
			bool drawWheels;
			bool drawThrust;
			float thrustDrawScale;  // +4
			float lateralOffset;  // +8
			float forceOffsetAlongCompression;  // +0xC
			bool drawFinalForce;  // +0x10
			float finalForceDrawScale;  // +0x14
			bool drawFinalTorque;  // +0x18
			float finalTorqueDrawScale;  // +0x1C
			float finalForceDisplayHeightOffset;  // +0x20
		};

		TankSolverProperties(); //@0x102F7F30
		static content::ClassInfo* GetClassInfo(); //@0x102F4100
		static content::MemberList* GetMembers();

		float GetMinSpeedToDamageCollidersKph() const; //@0x102F5320
		void SetMinSpeedToDamageCollidersKph(float kph); //@0x102F5330
		float GetMaxTiltAngleDegrees() const; //@0x102F5370
		void SetMaxTiltAngleDegrees(float degrees); //@0x102F5350

		float gravity;  // +8
		float minSpeedToDamageColliders;  // +0xC (metres per second)
		float secondsBetweenDamage;  // +0x10
		float secondsBetweenCrushEffect;  // +0x14
		float crushDeformStrength;  // +0x18
		float crushDeformTime;  // +0x1C
		float crushDeformAmount;  // +0x20
		float maxTiltAngle;  // +0x24 (radians)
		CameraParams cameraParams;  // +0x28
		SoundParams soundParams;  // +0x38
		SuspensionSpring suspensionSpring;  // +0x44
		SensorSpring sensorSpring;  // +0x70
		ForceDistributionType treadForceDistributionType;  // +0xF0
		Friction friction;  // +0xF4
		Thrust thrust;  // +0x144
		Steering steering;  // +0x198
		Reaction reaction;  // +0x1D0
		Animation animation;  // +0x1E0
		DebugDraw debugDraw;  // +0x1E8
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::AlignedAxleConstraint>
	{
		enum
		{
			value = 0
		};
	};
}

PROTO_ARRAY_HELPER_CREATE(proto::AlignedAxleConstraint)

namespace proto
{
	// The tread effects of a tank (0x78 bytes; the shader patch and the two sides' effects)
	struct TreadEffects
	{
		static content::ClassInfo* GetClassInfo(); //@0x102F4200
		static content::MemberList* GetMembers(); //@0x102FC730

		unsigned char unknown0[0x78];
	};

	class TankSolverBehaviour : public engine::Behaviour
	{
	public:
		// One joint of a tread or of a sensor (0x50 bytes)
		struct JointData
		{
			JointData(); //@0x102F80C0
			JointData(const JointData& other); //@0x102FA8E0
			JointData& operator=(const JointData& other); //@0x102FB150
			static content::ClassInfo* GetClassInfo(); //@0x102F4140
			static content::MemberList* GetMembers(); //@0x102F65F0

			bool unknown0;
			int unknown4;
			int unknown8;
			int unknownC;
			int unknown10;
			int unknown14;
			core::Name<core::CaseSensitiveKey> suspensionJoint;  // +0x18
			int unknown20;
			int unknown24;
			core::Name<core::CaseSensitiveKey> wheelJoint;  // +0x28
			int unknown30;
			int unknown34;
			int unknown38;
			int unknown3C;
			bool unknown40;
			int unknown44;
			int unknown48;
			int unknown4C;
		};

		// Tell the four joint arrays' meta types apart (each has its own in the engine)
		struct LeftTreadJoints
		{
		};
		struct RightTreadJoints
		{
		};
		struct ForwardSensorJoints
		{
		};
		struct ReverseSensorJoints
		{
		};

		typedef container::ArrayDynamic<JointData, container::AllocatorNew> JointArray;
		typedef container::ArrayDynamic<AlignedAxleConstraint, container::AllocatorNew> ConstraintArray;

		explicit TankSolverBehaviour(engine::GameObject* newOwner); //@0x10307090
		static content::ClassInfo* GetClassInfo(); //@0x102F4240
		static content::MemberList* GetMembers();

		unsigned char unknownC[8];
		JointArray leftTreadJoints;  // +0x14
		int unknown20;
		JointArray rightTreadJoints;  // +0x24
		int unknown30;
		JointArray forwardSensorJoints;  // +0x34
		int unknown40;
		JointArray reverseSensorJoints;  // +0x44
		int unknown50;
		unsigned char unknown54[4];
		TreadEffects treadEffects;  // +0x58
		TankSolverProperties* sharedProperties;  // +0xD0
		unsigned char unknownD4[0x28];
		ConstraintArray cannonAxleConstraints;  // +0xFC
		int unknown108;
		int unknown10C;
		AlignedAxleConstraint turretAxleConstraint;  // +0x110
		unsigned char unknown148[0x70];
		core::Name<core::CaseSensitiveKey> audioPatchName;  // +0x1B8
		unsigned char unknown1C0[0x18];
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::TankSolverBehaviour::JointData>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayReserveBeginFirst<proto::TankSolverBehaviour::JointData>
	{
		enum
		{
			value = 1
		};
	};
}


#endif
