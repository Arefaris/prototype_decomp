// The reflected properties of a helicopter's solver (RTTI and reflection names; unit 0x1031DFE0 - 0x10324E80, no
// assert path names it, the file name is a guess): proto::HelicopterSolverGenericProperties (what every helicopter
// has: camera, effects, health, power, rotor and sound groups, the inertia scales and the centre of mass) and
// proto::HelicopterSolverProperties (how the solver moves the helicopter: the hover, the lateral, longitudinal,
// vertical and yaw axes and the AI). Angles are kept in radians and speeds in metres per second; the reflection
// shows degrees and kilometres per hour. The group classes are plain data without virtual functions. The reflected
// names are original, the rest is guessed.
#ifndef PROTO_BEHAVIOURS_HELICOPTERSOLVERPROPERTIES_H
#define PROTO_BEHAVIOURS_HELICOPTERSOLVERPROPERTIES_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/math/symmetricmatrix.h"
#include "code/math/vector.h"

namespace ravenphysics
{
	class MassProperties;
}

namespace choreo
{
	// 0x10D94FF8 (symbols.txt): minus one
	extern const float gMinusOne;
}

namespace proto
{
	// 0x10DA3664 / 0x10D977EC (symbols.txt): fifty and ten in the pooled constants (names guessed)
	extern const float gFifty;
	extern const float gTen;

	// 0x1031F720: this unit's copy of the release helper for a mass properties reference (name guess)
	void ReleaseMassProperties(ravenphysics::MassProperties*& object);

	class HelicopterSolverGenericProperties : public content::MetaLoadObject
	{
	public:
		// Where the camera follows the helicopter (0x18 bytes)
		class CameraParams
		{
		public:
			CameraParams(); //@0x1031E3E0
			static content::ClassInfo* GetClassInfo(); //@0x1031DFE0

			void SetMaxElevationAngleDegrees(float degrees); //@0x1031E410
			float GetMaxElevationAngleDegrees() const; //@0x1031E430
			float GetMaxElevationAngle() const; //@0x1031E440
			void SetMinElevationAngleDegrees(float degrees); //@0x1031E450
			float GetMinElevationAngleDegrees() const; //@0x1031E470
			float GetMinElevationAngle() const; //@0x1031E480
			void SetElevationVelocityDegrees(float degrees); //@0x1031E490
			float GetElevationVelocityDegrees() const; //@0x1031E4B0
			float GetElevationVelocity() const; //@0x1031E4C0
			float GetRollPercentage() const; //@0x1031E4D0
			float GetRollTime() const; //@0x1031E4E0
			float GetHeightOffset() const; //@0x1031E4F0

			float maxElevationAngle;  // +0
			float minElevationAngle;  // +4
			float elevationVelocity;  // +8
			float rollPercentage;  // +0xC
			float rollTime;  // +0x10
			float heightOffset;  // +0x14
		};

		// How often the effects of the rotor wash and the damage appear (0x14 bytes)
		class EffectsParams
		{
		public:
			EffectsParams(); //@0x1031E500
			static content::ClassInfo* GetClassInfo(); //@0x1031E020

			float GetWashEffectFrequency() const; //@0x1031E550
			float GetMaxWashEffectHeight() const; //@0x1031E560
			float GetBloodtoxSpawnFrequency() const; //@0x1031E570
			float GetRotorCollisionEffectFrequency() const; //@0x1031E580
			float GetOffsetForRaycast() const; //@0x1031E590

			float washEffectFrequency;  // +0
			float maxWashEffectHeight;  // +4
			float bloodtoxSpawnFrequency;  // +8
			float rotorCollisionEffectFrequency;  // +0xC
			float offsetForRaycast;  // +0x10
		};

		// How the helicopter is hurt (8 bytes)
		class HealthParams
		{
		public:
			HealthParams(); //@0x1031E790
			static content::ClassInfo* GetClassInfo(); //@0x1031E060

			void SetDamagePerKph(float damagePerKph); //@0x1031E7B0
			float GetDamagePerKph() const; //@0x1031E7D0
			float GetDamagePerSpeed() const; //@0x1031E7E0
			float GetRotorDamageTimeTillZeroHealth() const; //@0x1031E7F0

			float damagePerSpeed;  // +0
			float rotorDamageTimeTillZeroHealth;  // +4
		};

		// When the helicopter powers up and down (0x18 bytes)
		class PowerParams
		{
		public:
			PowerParams(); //@0x1031E800
			static content::ClassInfo* GetClassInfo(); //@0x1031E0A0

			float GetPowerUpTime() const; //@0x1031E850
			float GetPowerDownTime() const; //@0x1031E860
			float GetHoldLastIntentionTime() const; //@0x1031E870
			float GetTimeOnGroundForPhysicsOff() const; //@0x1031E880
			float GetTimeInAirToClearTimeOnGround() const; //@0x1031E890
			float GetTimeOnGroundForPowerDown() const; //@0x1031E8A0

			float powerUpTime;  // +0
			float powerDownTime;  // +4
			float holdLastIntentionTime;  // +8
			float timeOnGroundForPhysicsOff;  // +0xC
			float timeInAirToClearTimeOnGround;  // +0x10
			float timeOnGroundForPowerDown;  // +0x14
		};

		// How far the helicopter's rotor tilts it (0x14 bytes)
		class RotorParams
		{
		public:
			RotorParams(); //@0x1031E8B0
			static content::ClassInfo* GetClassInfo(); //@0x1031E0E0

			void SetMaxPitchAngleDegrees(float degrees); //@0x1031E8E0
			float GetMaxPitchAngleDegrees() const; //@0x1031E900
			float GetMaxPitchAngle() const; //@0x1031E910
			float GetTimeToMaxPitch() const; //@0x1031E920
			void SetMaxRollAngleDegrees(float degrees); //@0x1031E930
			float GetMaxRollAngleDegrees() const; //@0x1031E950
			float GetMaxRollAngle() const; //@0x1031E960
			float GetTimeToMaxRoll() const; //@0x1031E970
			bool GetInvertPitch() const; //@0x1031E980
			bool GetInvertRoll() const; //@0x1031E990

			float maxPitchAngle;  // +0
			float timeToMaxPitch;  // +4
			float maxRollAngle;  // +8
			float timeToMaxRoll;  // +0xC
			bool invertPitch;  // +0x10
			bool invertRoll;  // +0x11
		};

		// The names of the sound patch and its controls (0x28 bytes)
		class SoundParams
		{
		public:
			SoundParams(); //@0x1031F8C0
			static content::ClassInfo* GetClassInfo(); //@0x1031E120
			static content::MemberList* GetMembers(); //@0x1031F740

			const core::Name<core::CaseSensitiveKey>* GetPatchName() const; //@0x1031E9A0
			const core::Name<core::CaseSensitiveKey>* GetStartupTriggerName() const; //@0x1031E9B0
			const core::Name<core::CaseSensitiveKey>* GetThrottleControlName() const; //@0x1031E9C0
			const core::Name<core::CaseSensitiveKey>* GetVelocityControlName() const; //@0x1031E9D0
			const core::Name<core::CaseSensitiveKey>* GetWindDownTriggerName() const; //@0x1031E9E0
			void SetStartupTriggerName(const core::Name<core::CaseSensitiveKey>* name); //@0x1031F910
			void SetThrottleControlName(const core::Name<core::CaseSensitiveKey>* name); //@0x1031F920
			void SetVelocityControlName(const core::Name<core::CaseSensitiveKey>* name); //@0x1031F930
			void SetWindDownTriggerName(const core::Name<core::CaseSensitiveKey>* name); //@0x1031F940

			core::Name<core::CaseSensitiveKey> patchName;  // +0
			core::Name<core::CaseSensitiveKey> startupTriggerName;  // +8
			core::Name<core::CaseSensitiveKey> throttleControlName;  // +0x10
			core::Name<core::CaseSensitiveKey> velocityControlName;  // +0x18
			core::Name<core::CaseSensitiveKey> windDownTriggerName;  // +0x20
		};

		HelicopterSolverGenericProperties(); //@0x10321520
		virtual ~HelicopterSolverGenericProperties(); //@0x1031F960 (vector deleting destructor 0x103215F0)
		static content::ClassInfo* GetClassInfo(); //@0x1031E360
		static content::MemberList* GetMembers(); //@0x10324450

		bool GetIsJet() const; //@0x1031E5A0
		void SetCenterOfMass(const math::Vector* position); //@0x1031E5B0
		const math::Vector* GetCenterOfMass() const; //@0x1031E5F0
		int GetCenterOfMassVersion() const; //@0x1031E600
		bool GetCenterOfMassDraw() const; //@0x1031E610
		float GetForwardDeadzoneSizeAtMaxStrafe() const; //@0x1031E620
		float GetStrafeDeadzoneSizeAtMaxForward() const; //@0x1031E630
		void SetInertiaScaleXX(float scale); //@0x1031E640
		void SetInertiaScaleYY(float scale); //@0x1031E660
		void SetInertiaScaleZZ(float scale); //@0x1031E680
		void SetInertiaScaleXY(float scale); //@0x1031E6A0
		void SetInertiaScaleXZ(float scale); //@0x1031E6C0
		void SetInertiaScaleYZ(float scale); //@0x1031E6E0
		float GetInertiaScaleXX() const; //@0x1031E700
		float GetInertiaScaleYY() const; //@0x1031E710
		float GetInertiaScaleZZ() const; //@0x1031E720
		float GetInertiaScaleXY() const; //@0x1031E730
		float GetInertiaScaleXZ() const; //@0x1031E740
		float GetInertiaScaleYZ() const; //@0x1031E750
		const math::SymmetricMatrix* GetInertiaScales() const; //@0x1031E760
		int GetInertiaScaleVersion() const; //@0x1031E770
		ravenphysics::MassProperties* GetRestingMassProperties() const; //@0x1031E780

		CameraParams cameraParams;  // +8
		EffectsParams effectsParams;  // +0x20
		HealthParams healthParams;  // +0x34
		PowerParams powerParams;  // +0x3C
		RotorParams rotorParams;  // +0x54
		SoundParams soundParams;  // +0x68
		bool isJet;  // +0x90
		math::Vector centerOfMass;  // +0x94
		int centerOfMassVersion;  // +0xA0
		bool centerOfMassDraw;  // +0xA4
		float forwardDeadzoneSizeAtMaxStrafe;  // +0xA8
		float strafeDeadzoneSizeAtMaxForward;  // +0xAC
		math::SymmetricMatrix inertiaScale;  // +0xB0
		int inertiaScaleVersion;  // +0xC8
		ravenphysics::MassProperties* restingMassProperties;  // +0xCC
	};

	class HelicopterSolverProperties : public content::MetaLoadObject
	{
	public:
		// What the AI helicopter does (2 bytes)
		class AIParams
		{
		public:
			AIParams(); //@0x1031E9F0
			static content::ClassInfo* GetClassInfo(); //@0x1031E160

			bool GetUseDrag() const; //@0x1031EA00
			bool GetIntentionSpeed() const; //@0x1031EA10

			bool useDrag;  // +0
			bool intentionSpeed;  // +1
		};

		// How the helicopter hovers (0x44 bytes)
		class HoverParams
		{
		public:
			HoverParams(); //@0x1031EA20
			static content::ClassInfo* GetClassInfo(); //@0x1031E1A0

			float GetThrottleForHover() const; //@0x1031EAB0
			float GetHoverOffsetAtMaxForwardSpeed() const; //@0x1031EAC0
			float GetHoverOffsetAtMaxForwardAcceleration() const; //@0x1031EAD0
			float GetHoverHeight() const; //@0x1031EAE0
			float GetHoverForce() const; //@0x1031EAF0
			float GetHeightForHorizontalControl() const; //@0x1031EB00
			const math::Vector* GetDriftAmount() const; //@0x1031EB10
			float GetTimeToDriftMax() const; //@0x1031EB20
			float GetTimeToDriftMin() const; //@0x1031EB30
			float GetTimeToStartDrift() const; //@0x1031EB40

			float throttleForHover;  // +0
			float throttleHoverDeadzoneNoTarget;  // +4
			float throttleHoverDeadzoneTarget;  // +8
			float throttleForHoverPS3;  // +0xC
			float throttleHoverDeadzoneNoTargetPS3;  // +0x10
			float throttleHoverDeadzoneTargetPS3;  // +0x14
			float hoverOffsetAtMaxForwardSpeed;  // +0x18
			float hoverOffsetAtMaxForwardAcceleration;  // +0x1C
			float hoverHeight;  // +0x20
			float hoverForce;  // +0x24
			float heightForHorizontalControl;  // +0x28
			math::Vector driftAmount;  // +0x2C
			float timeToDriftMax;  // +0x38
			float timeToDriftMin;  // +0x3C
			float timeToStartDrift;  // +0x40
		};

		// Sideways movement (0x1C bytes)
		class LateralAxisLinearParams
		{
		public:
			LateralAxisLinearParams(); //@0x1031EB50
			static content::ClassInfo* GetClassInfo(); //@0x1031E1E0

			float GetMaxLateralAcceleration() const; //@0x1031EBA0
			float GetMaxLateralSpeedKph() const; //@0x1031EBB0
			float ScaleMaxLateralSpeed(float scale) const; //@0x1031EBC0
			float GetLowspeedDragMaxVelocityKph() const; //@0x1031EBD0
			float GetLowspeedDragMaxVelocity() const; //@0x1031EBE0
			float GetLowSpeedDragTimeToStopFromMaxVelocity() const; //@0x1031EBF0
			float GetMaxInputForLowspeedDrag() const; //@0x1031EC00
			float GetDragCoefficient() const; //@0x1031EC10
			float GetLowspeedDrag() const; //@0x1031EC20
			float ScaleMaxLateralSpeedAgain(float scale) const; //@0x1031EC30
			void UpdateDerivedValues(); //@0x1031FAE0

			float maxLateralAcceleration;  // +0
			float maxLateralSpeed;  // +4
			float dragCoefficient;  // +8
			float lowspeedDragMaxVelocity;  // +0xC
			float lowSpeedDragTimeToStopFromMaxVelocity;  // +0x10
			float maxInputForLowspeedDrag;  // +0x14
			float lowspeedDrag;  // +0x18
		};

		// Rolling (8 bytes)
		class LateralAxisAngularParams
		{
		public:
			LateralAxisAngularParams(); //@0x1031EC40
			static content::ClassInfo* GetClassInfo(); //@0x1031E220

			void SetMaxRollAccelerationDegrees(float degrees); //@0x1031EC70
			float GetMaxRollAccelerationDegrees() const; //@0x1031EC90
			float GetMaxRollAcceleration() const; //@0x1031ECA0
			void SetMaxRollAngleDegrees(float degrees); //@0x1031ECB0
			float GetMaxRollAngleDegrees() const; //@0x1031ECD0
			float GetMaxRollAngle() const; //@0x1031ECE0

			float maxRollAcceleration;  // +0
			float maxRollAngle;  // +4
		};

		// Forward and backward movement (0x28 bytes)
		class LongitudinalAxisLinearParams
		{
		public:
			LongitudinalAxisLinearParams(); //@0x1031ECF0
			static content::ClassInfo* GetClassInfo(); //@0x1031E260

			float GetMaxSpeedForDirection(float direction) const; //@0x1031ED60
			float GetMaxForwardSpeedKph() const; //@0x1031ED90
			float ScaleMaxForwardSpeed(float scale) const; //@0x1031EDA0
			float GetMaxBackwardSpeedKph() const; //@0x1031EDB0
			float ScaleMaxBackwardSpeed(float scale) const; //@0x1031EDC0
			float GetMaxForwardAcceleration() const; //@0x1031EDD0
			float GetMaxBackwardAcceleration() const; //@0x1031EDE0
			float GetLowspeedDragMaxVelocityKph() const; //@0x1031EDF0
			float GetLowspeedDragMaxVelocity() const; //@0x1031EE00
			float GetLowSpeedDragTimeToStopFromMaxVelocity() const; //@0x1031EE10
			float GetMaxInputForLowspeedDrag() const; //@0x1031EE20
			float GetForwardDragCoefficient() const; //@0x1031EE30
			float GetBackwardDragCoefficient() const; //@0x1031EE40
			float GetLowspeedDrag() const; //@0x1031EE50
			void UpdateDerivedValues(); //@0x1031FB20

			float maxForwardAcceleration;  // +0
			float maxBackwardAcceleration;  // +4
			float maxForwardSpeed;  // +8
			float maxBackwardSpeed;  // +0xC
			float forwardDragCoefficient;  // +0x10
			float backwardDragCoefficient;  // +0x14
			float lowspeedDragMaxVelocity;  // +0x18
			float lowSpeedDragTimeToStopFromMaxVelocity;  // +0x1C
			float maxInputForLowspeedDrag;  // +0x20
			float lowspeedDrag;  // +0x24
		};

		// Pitching (0x20 bytes)
		class LongitudinalAxisAngularParams
		{
		public:
			LongitudinalAxisAngularParams(); //@0x1031EE60
			static content::ClassInfo* GetClassInfo(); //@0x1031E2A0

			float ScaleMaxPitchSpeed(float scale) const; //@0x1031EED0
			void SetMaxPitchAccelerationDegrees(float degrees); //@0x1031EEE0
			float GetMaxPitchAccelerationDegrees() const; //@0x1031EF00
			float GetMaxPitchAcceleration() const; //@0x1031EF10
			void SetMaxPitchSpeedDegrees(float degrees); //@0x1031EF20
			float GetMaxPitchSpeedDegrees() const; //@0x1031EF40
			float GetMaxPitchSpeed() const; //@0x1031EF50
			void SetMaxAccelerationForwardPitchDegrees(float degrees); //@0x1031EF60
			float GetMaxAccelerationForwardPitchDegrees() const; //@0x1031EF80
			float GetMaxAccelerationForwardPitch() const; //@0x1031EF90
			void SetMaxVelocityForwardPitchDegrees(float degrees); //@0x1031EFA0
			float GetMaxVelocityForwardPitchDegrees() const; //@0x1031EFC0
			float GetMaxVelocityForwardPitch() const; //@0x1031EFD0
			void SetMaxAccelerationBackwardPitchDegrees(float degrees); //@0x1031EFE0
			float GetMaxAccelerationBackwardPitchDegrees() const; //@0x1031F000
			float GetMaxAccelerationBackwardPitch() const; //@0x1031F010
			void SetMaxVelocityBackwardPitchDegrees(float degrees); //@0x1031F020
			float GetMaxVelocityBackwardPitchDegrees() const; //@0x1031F040
			float GetMaxVelocityBackwardPitch() const; //@0x1031F050
			float GetForwardPitchAccelerationFactor() const; //@0x1031F060
			float GetForwardPitchVelocityFactor() const; //@0x1031F070

			float maxPitchAcceleration;  // +0
			float maxPitchSpeed;  // +4
			float maxAccelerationForwardPitch;  // +8
			float maxVelocityForwardPitch;  // +0xC
			float maxAccelerationBackwardPitch;  // +0x10
			float maxVelocityBackwardPitch;  // +0x14
			float forwardPitchVelocityFactor;  // +0x18
			float forwardPitchAccelerationFactor;  // +0x1C
		};

		// Climbing and descending (0x48 bytes)
		class VerticalAxisParams
		{
		public:
			VerticalAxisParams(); //@0x1031F080
			static content::ClassInfo* GetClassInfo(); //@0x1031E2E0

			float GetMaxUpSpeedForDirection(float direction) const; //@0x1031F130
			float GetMaxUpAcceleration() const; //@0x1031F160
			void SetMaxUpAccelerationWithPitch(float acceleration); //@0x1031F170
			float GetMaxUpAccelerationWithPitch() const; //@0x1031F190
			float GetMaxDownAcceleration() const; //@0x1031F1A0
			void SetMaxDownAccelerationWithPitch(float acceleration); //@0x1031F1B0
			float GetMaxDownAccelerationWithPitch() const; //@0x1031F1D0
			float GetMaxUpVelocityKph() const; //@0x1031F1E0
			float ScaleMaxUpVelocity(float scale) const; //@0x1031F1F0
			float GetMaxDownVelocityKph() const; //@0x1031F200
			float ScaleMaxDownVelocity(float scale) const; //@0x1031F210
			float GetMaxDownVelocityWithPitchKph() const; //@0x1031F220
			float GetMaxDownVelocityWithPitch() const; //@0x1031F230
			float GetLowspeedDragMaxVelocityKph() const; //@0x1031F240
			void SetLowspeedDragMaxVelocityKph(float kph); //@0x1031FB80
			void SetLowSpeedDragTimeToStopFromMaxVelocity(float time); //@0x1031FBB0
			float GetLowspeedDragMaxVelocity() const; //@0x1031F250
			float GetLowSpeedDragTimeToStopFromMaxVelocity() const; //@0x1031F260
			float GetMaxInputForLowspeedDrag() const; //@0x1031F270
			void UpdateLowspeedDrag(); //@0x1031F280
			float GetUpDragCoefficient() const; //@0x1031F2A0
			float GetDownDragCoefficient() const; //@0x1031F2B0
			float GetDownWithPitchDragCoefficient() const; //@0x1031F2C0
			float GetLowspeedDrag() const; //@0x1031F2D0
			float GetMaxHeight() const; //@0x1031F2E0
			float GetDragCoefficientMaxHeight() const; //@0x1031F2F0
			float GetMaxTiltFromVertical() const; //@0x1031F300
			float GetMaxTiltFromVerticalDegrees() const; //@0x1031F310
			void SetMaxTiltFromVerticalDegrees(float degrees); //@0x1031F320
			float GetMaxAutomaticDownwardAcceleration() const; //@0x1031F340
			void UpdateUpDragCoefficient(); //@0x1031FBD0
			void UpdateDownDragCoefficients(); //@0x1031FBF0

			float maxUpAcceleration;  // +0
			float maxUpAccelerationWithPitch;  // +4
			float maxDownAcceleration;  // +8
			float maxDownAccelerationWithPitch;  // +0xC
			float maxUpVelocity;  // +0x10
			float maxDownVelocity;  // +0x14
			float maxDownVelocityWithPitch;  // +0x18
			float upDragCoefficient;  // +0x1C
			float downDragCoefficient;  // +0x20
			float downWithPitchDragCoefficient;  // +0x24
			float maxHeight;  // +0x28
			float dragCoefficientMaxHeight;  // +0x2C
			float lowspeedDragMaxVelocity;  // +0x30
			float lowSpeedDragTimeToStopFromMaxVelocity;  // +0x34
			float maxInputForLowspeedDrag;  // +0x38
			float lowspeedDrag;  // +0x3C
			float maxTiltFromVertical;  // +0x40
			float maxAutomaticDownwardAcceleration;  // +0x44
		};

		// Turning (0x20 bytes)
		class YawAxisParams
		{
		public:
			YawAxisParams(); //@0x1031F350
			static content::ClassInfo* GetClassInfo(); //@0x1031E320

			float GetMaxYawAccelerationDegrees() const; //@0x1031F3B0
			float GetMaxYawAcceleration() const; //@0x1031F3C0
			float GetMaxVelocityDegrees() const; //@0x1031F3D0
			float GetMaxVelocity() const; //@0x1031F3E0
			void SetYawAmountAtMaxForwardAndSidewayVelocity(float amount); //@0x1031F3F0
			float GetYawAmountAtMaxForwardAndSidewayVelocity() const; //@0x1031F440
			float GetLowspeedDragMaxVelocityDegrees() const; //@0x1031F450
			float GetLowspeedDragMaxVelocity() const; //@0x1031F460
			float GetLowSpeedDragTimeToStopFromMaxVelocity() const; //@0x1031F470
			float GetMaxInputForLowspeedDrag() const; //@0x1031F480
			float GetLowspeedDrag() const; //@0x1031F490
			float GetDragCoefficient() const; //@0x1031F4A0
			void UpdateDerivedValues(); //@0x1031FC40

			float maxYawAcceleration;  // +0
			float maxVelocity;  // +4
			float yawAmountAtMaxForwardAndSidewayVelocity;  // +8
			float lowspeedDragMaxVelocity;  // +0xC
			float lowSpeedDragTimeToStopFromMaxVelocity;  // +0x10
			float maxInputForLowspeedDrag;  // +0x14
			float lowspeedDrag;  // +0x18
			float dragCoefficient;  // +0x1C
		};

		HelicopterSolverProperties(); //@0x1031FC80
		static content::ClassInfo* GetClassInfo(); //@0x1031E3A0
		static content::MemberList* GetMembers(); //@0x10324850

		AIParams aiParams;  // +8
		HoverParams hoverParams;  // +0xC
		LateralAxisLinearParams lateralAxisLinearParams;  // +0x50
		LateralAxisAngularParams lateralAxisAngularParams;  // +0x6C
		LongitudinalAxisLinearParams longitudinalAxisLinearParams;  // +0x74
		LongitudinalAxisAngularParams longitudinalAxisAngularParams;  // +0x9C
		VerticalAxisParams verticalAxisParams;  // +0xBC
		YawAxisParams yawAxisParams;  // +0x104
	};
}

#endif
