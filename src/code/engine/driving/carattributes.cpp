// The reflected attribute classes of the car code: see the header.
#include "code/engine/driving/carattributes.h"
#include "code/math/mathutils.h"

namespace engine
{
	namespace driving
	{
		// FUNCTION: ENGINE 0x10934540
		content::ClassInfo* CarSuspensionAttributes::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::driving::CarSuspensionAttributes";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10935470
		// EQUIVALENT: scheduling; the engine loads the first setter's argument before it stores the two curve values and moves the object pointer back into ecx after the argument is pushed, ours stores first; every call, argument and store is the engine's
		CarSuspensionAttributes::CarSuspensionAttributes()
		{
			gravity = 20.0f;
			pitchScale = 1.0f;
			rollScale = 1.0f;
			curve.SetKnots(knots.knots);
			knots.SetKnot(2, 0.0f);
			curve.SetValue(0, 0.0f);
			curve.SetValue(2, gOne);
			SetMaxCompressionDistance(gPointThree);
			SetMaxStretchDistance(gPointThree);
			SetMaxGScale(gTwo);
			SetIntermediateCompressionFactor(gHalf);
			SetIntermediateStretchFactor(gHalf);
			SetIntermediateCompressionForceFactor(gHalf);
			SetIntermediateStretchForceFactor(gHalf);
			SetMaxCompressionSpeedKmh(gThirty);
			SetMaxStretchSpeedKmh(gThirty);
		}

		// FUNCTION: ENGINE 0x10934580
		float CarSuspensionAttributes::GetMaxCompressionSpeedKmh() const
		{
			return speed.GetMaxPositiveKmh();
		}

		// FUNCTION: ENGINE 0x10934590
		void CarSuspensionAttributes::SetMaxCompressionSpeedKmh(float kmh)
		{
			speed.SetMaxPositiveKmh(kmh);
		}

		// FUNCTION: ENGINE 0x109345B0
		float CarSuspensionAttributes::GetMaxStretchSpeedKmh() const
		{
			return speed.GetMaxNegativeKmh();
		}

		// FUNCTION: ENGINE 0x109345C0
		void CarSuspensionAttributes::SetMaxStretchSpeedKmh(float kmh)
		{
			speed.SetMaxNegativeKmh(kmh);
		}

		// FUNCTION: ENGINE 0x109345E0
		float CarSuspensionAttributes::GetGravity() const
		{
			return gravity;
		}

		// FUNCTION: ENGINE 0x109345F0
		void CarSuspensionAttributes::SetGravity(float value)
		{
			gravity = value;
		}

		// FUNCTION: ENGINE 0x10934600
		float CarSuspensionAttributes::GetPitchScale() const
		{
			return pitchScale;
		}

		// FUNCTION: ENGINE 0x10934610
		float CarSuspensionAttributes::GetRollScale() const
		{
			return rollScale;
		}

		// FUNCTION: ENGINE 0x10934770
		float CarSuspensionAttributes::GetMaxCompressionDistance() const
		{
			return knots.knots[4];
		}

		// FUNCTION: ENGINE 0x10934780
		float CarSuspensionAttributes::GetMaxStretchDistance() const
		{
			return -knots.knots[0];
		}

		// FUNCTION: ENGINE 0x10934790
		float CarSuspensionAttributes::GetMaxGScale() const
		{
			return curve.values[4];
		}

		// FUNCTION: ENGINE 0x109347A0
		void CarSuspensionAttributes::SetMaxGScale(float scale)
		{
			if (!(scale > gMinGScale))
			{
				scale = gMinGScale;
			}
			curve.values[4] = scale;
		}

		// FUNCTION: ENGINE 0x109347D0
		float CarSuspensionAttributes::GetIntermediateCompressionFactor() const
		{
			return knots.knots[3] / GetMaxCompressionDistance();
		}

		// FUNCTION: ENGINE 0x109347E0
		float CarSuspensionAttributes::GetIntermediateStretchFactor() const
		{
			return -(knots.knots[1] / GetMaxStretchDistance());
		}

		// FUNCTION: ENGINE 0x109347F0
		float CarSuspensionAttributes::GetIntermediateCompressionForceFactor() const
		{
			return (curve.values[3] - 1.0f) / (GetMaxGScale() - 1.0f);
		}

		// FUNCTION: ENGINE 0x10934810
		void CarSuspensionAttributes::SetIntermediateCompressionForceFactor(float factor)
		{
			factor = math::Clamp(factor, 0.001f, gMaxFraction);
			curve.values[3] = (GetMaxGScale() - 1.0f) * factor + 1.0f;
		}

		// FUNCTION: ENGINE 0x10934870
		float CarSuspensionAttributes::GetIntermediateStretchForceFactor() const
		{
			return 1.0f - curve.values[1];
		}

		// FUNCTION: ENGINE 0x10934880
		void CarSuspensionAttributes::SetIntermediateStretchForceFactor(float factor)
		{
			factor = math::Clamp(factor, 0.001f, gMaxFraction);
			curve.values[1] = 1.0f - factor;
		}

		// FUNCTION: ENGINE 0x109348D0
		void CarSuspensionAttributes::SetPitchScale(float scale)
		{
			pitchScale = scale > 0.001f ? scale : 0.001f;
		}

		// FUNCTION: ENGINE 0x109348F0
		void CarSuspensionAttributes::SetRollScale(float scale)
		{
			rollScale = scale > 0.001f ? scale : 0.001f;
		}

		// FUNCTION: ENGINE 0x10934AF0
		float CarSuspensionAttributes::GetForce(float compression, float speedValue) const
		{
			float curveValue = curve.Evaluate(compression, InterpolateGraph);
			float scale = GetMaxGScale();
			if (speedValue >= choreo::gZero)
			{
				return (NormalizeBounded(speedValue, speed.maxPositive, 0.001f) * scale + curveValue) * gravity;
			}
			float stretch = -(NormalizeBounded(-speedValue, speed.maxNegative, 0.001f) * scale);
			return (stretch + curveValue) * gravity;
		}

		// FUNCTION: ENGINE 0x10934BB0
		void CarSuspensionAttributes::SetMaxCompressionDistance(float distance)
		{
			if (!(distance > 0.01f))
			{
				distance = 0.01f;
			}
			knots.SetKnot(4, distance);
		}

		// FUNCTION: ENGINE 0x10934BE0
		void CarSuspensionAttributes::SetMaxStretchDistance(float distance)
		{
			if (!(distance > 0.01f))
			{
				distance = 0.01f;
			}
			knots.SetKnot(0, -distance);
		}

		// FUNCTION: ENGINE 0x10934C20
		void CarSuspensionAttributes::SetIntermediateCompressionFactor(float factor)
		{
			factor = math::Clamp(factor, 0.001f, gMaxFraction);
			knots.SetKnot(3, GetMaxCompressionDistance() * factor);
		}

		// FUNCTION: ENGINE 0x10934C80
		void CarSuspensionAttributes::SetIntermediateStretchFactor(float factor)
		{
			factor = math::Clamp(factor, 0.001f, gMaxFraction);
			knots.SetKnot(1, -(GetMaxStretchDistance() * factor));
		}

		// FUNCTION: ENGINE 0x10935220
		content::MemberList* CarSuspensionAttributes::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetMemberMetaType<CarSuspensionAttributes, float, 0>(&CarSuspensionAttributes::GetMaxCompressionDistance,
					&CarSuspensionAttributes::SetMaxCompressionDistance, "p"), 0, "maxCompressionDistance" },
				{ content::GetMemberMetaType<CarSuspensionAttributes, float, 1>(&CarSuspensionAttributes::GetMaxStretchDistance,
					&CarSuspensionAttributes::SetMaxStretchDistance, "p"), 0, "maxStretchDistance" },
				{ content::GetMemberMetaType<CarSuspensionAttributes, float, 2>(&CarSuspensionAttributes::GetMaxGScale,
					&CarSuspensionAttributes::SetMaxGScale, "p"), 0, "maxGScale" },
				{ content::GetMemberMetaType<CarSuspensionAttributes, float, 3>(&CarSuspensionAttributes::GetIntermediateCompressionFactor,
					&CarSuspensionAttributes::SetIntermediateCompressionFactor, "p"), 0, "intermediateCompressionFactor" },
				{ content::GetMemberMetaType<CarSuspensionAttributes, float, 4>(&CarSuspensionAttributes::GetIntermediateStretchFactor,
					&CarSuspensionAttributes::SetIntermediateStretchFactor, "p"), 0, "intermediateStretchFactor" },
				{ content::GetMemberMetaType<CarSuspensionAttributes, float, 5>(&CarSuspensionAttributes::GetIntermediateCompressionForceFactor,
					&CarSuspensionAttributes::SetIntermediateCompressionForceFactor, "p"), 0, "intermediateCompressionForceFactor" },
				{ content::GetMemberMetaType<CarSuspensionAttributes, float, 6>(&CarSuspensionAttributes::GetIntermediateStretchForceFactor,
					&CarSuspensionAttributes::SetIntermediateStretchForceFactor, "p"), 0, "intermediateStretchForceFactor" },
				{ content::GetMemberMetaType<CarSuspensionAttributes, float, 7>(&CarSuspensionAttributes::GetMaxCompressionSpeedKmh,
					&CarSuspensionAttributes::SetMaxCompressionSpeedKmh, "p"), 0, "maxCompressionSpeedKmh" },
				{ content::GetMemberMetaType<CarSuspensionAttributes, float, 8>(&CarSuspensionAttributes::GetMaxStretchSpeedKmh,
					&CarSuspensionAttributes::SetMaxStretchSpeedKmh, "p"), 0, "maxStretchSpeedKmh" },
				{ content::GetMemberMetaType<CarSuspensionAttributes, float, 9>(&CarSuspensionAttributes::GetGravity,
					&CarSuspensionAttributes::SetGravity, "p"), 0, "gravity" },
				{ content::GetMemberMetaType<CarSuspensionAttributes, float, 10>(&CarSuspensionAttributes::GetPitchScale,
					&CarSuspensionAttributes::SetPitchScale, "p"), 0, "pitchScale" },
				{ content::GetMemberMetaType<CarSuspensionAttributes, float, 11>(&CarSuspensionAttributes::GetRollScale,
					&CarSuspensionAttributes::SetRollScale, "p"), 0, "rollScale" }
			};
			sList.members = sMembers;
			sList.count = 12;
			return &sList;
		}

#define ENGINE_DRIVING_FLOAT(Class, index, member) 	{ content::GetMemberPrimitiveMetaType<Class, float, index>("p"), 		content::MemberOffset(&((Class*)0)->member, (int)&((Class*)0)->member), #member }
#define ENGINE_DRIVING_OBJECT(Class, Type, member) 	{ content::GetClassMetaType<Type>(), 		content::MemberOffset(&((Class*)0)->member, (int)&((Class*)0)->member), #member }

		// FUNCTION: ENGINE 0x109355B0
		content::ClassInfo* CarControlAttributes::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::driving::CarControlAttributes";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x109355F0
		CarControlAttributes::CarControlAttributes()
			: forwardForceScale(1.0f), forwardPitchTorqueScale(1.0f), reverseForceScale(1.0f),
			reversePitchTorqueScale(1.0f), lateralSteeringForceScale(1.0f), steeringRollTorqueScale(1.0f),
			steeringYawTorqueScale(1.0f), forwardThrottleIncreaseRate(1.0f), forwardThrottleDecreaseRate(10.0f),
			steeringFactorIncreaseRate(1.0f), steeringFactorDecreaseRate(10.0f)
		{
		}

		// FUNCTION: ENGINE 0x10935A70
		content::MemberList* CarControlAttributes::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				ENGINE_DRIVING_OBJECT(CarControlAttributes, BoundedSpeedGraphAttributes, forwardSpeed),
				ENGINE_DRIVING_OBJECT(CarControlAttributes, BoundedSymmetricSpeedGraphAttributes, sidewaysSpeed),
				ENGINE_DRIVING_OBJECT(CarControlAttributes, BoundedSymmetricAngleGraphAttributes, yawSpeed),
				ENGINE_DRIVING_FLOAT(CarControlAttributes, 0, forwardForceScale),
				ENGINE_DRIVING_FLOAT(CarControlAttributes, 1, forwardPitchTorqueScale),
				ENGINE_DRIVING_FLOAT(CarControlAttributes, 2, reverseForceScale),
				ENGINE_DRIVING_FLOAT(CarControlAttributes, 3, reversePitchTorqueScale),
				ENGINE_DRIVING_FLOAT(CarControlAttributes, 4, lateralSteeringForceScale),
				ENGINE_DRIVING_FLOAT(CarControlAttributes, 5, steeringRollTorqueScale),
				ENGINE_DRIVING_FLOAT(CarControlAttributes, 6, steeringYawTorqueScale),
				ENGINE_DRIVING_FLOAT(CarControlAttributes, 7, forwardThrottleIncreaseRate),
				ENGINE_DRIVING_FLOAT(CarControlAttributes, 8, forwardThrottleDecreaseRate),
				ENGINE_DRIVING_FLOAT(CarControlAttributes, 9, steeringFactorIncreaseRate),
				ENGINE_DRIVING_FLOAT(CarControlAttributes, 10, steeringFactorDecreaseRate)
			};
			sList.members = sMembers;
			sList.count = 14;
			return &sList;
		}

		// FUNCTION: ENGINE 0x10936C80
		content::ClassInfo* HelicopterControlAttributes::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::driving::HelicopterControlAttributes";
			sInfo.code = "pn";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10936CC0
		HelicopterControlAttributes::HelicopterControlAttributes()
			: upwardForceScale(1.0f), forwardForceScale(1.0f), forwardPitchTorqueScale(1.0f), reverseForceScale(1.0f),
			reversePitchTorqueScale(1.0f), lateralSteeringForceScale(1.0f), steeringRollTorqueScale(1.0f),
			steeringYawTorqueScale(1.0f), upwardThrottleIncreaseRate(1.0f), upwardThrottleDecreaseRate(1.0f),
			forwardThrottleIncreaseRate(1.0f), forwardThrottleDecreaseRate(10.0f), steeringFactorIncreaseRate(1.0f),
			steeringFactorDecreaseRate(10.0f), gravity(10.0f)
		{
		}

		// FUNCTION: ENGINE 0x10936D70
		BoundedSpeedGraphAttributes& HelicopterControlAttributes::GetUpwardSpeed()
		{
			return upwardSpeed;
		}

		// FUNCTION: ENGINE 0x10936D80
		BoundedSpeedGraphAttributes& HelicopterControlAttributes::GetForwardSpeed()
		{
			return forwardSpeed;
		}

		// FUNCTION: ENGINE 0x10936D90
		BoundedSymmetricSpeedGraphAttributes& HelicopterControlAttributes::GetSidewaysSpeed()
		{
			return sidewaysSpeed;
		}

		// FUNCTION: ENGINE 0x10936DA0
		BoundedSymmetricAngleGraphAttributes& HelicopterControlAttributes::GetPitchSpeed()
		{
			return pitchSpeed;
		}

		// FUNCTION: ENGINE 0x10936DB0
		BoundedSymmetricAngleGraphAttributes& HelicopterControlAttributes::GetYawSpeed()
		{
			return yawSpeed;
		}

		// FUNCTION: ENGINE 0x10936DC0
		BoundedSymmetricAngleGraphAttributes& HelicopterControlAttributes::GetRollSpeed()
		{
			return rollSpeed;
		}

		// FUNCTION: ENGINE 0x10936DD0
		BoundedSymmetricAngleGraphAttributes& HelicopterControlAttributes::GetPitchAngle()
		{
			return pitchAngle;
		}

		// FUNCTION: ENGINE 0x10936DE0
		BoundedSymmetricAngleGraphAttributes& HelicopterControlAttributes::GetRollAngle()
		{
			return rollAngle;
		}

		// FUNCTION: ENGINE 0x109371B0
		content::MemberList* HelicopterControlAttributes::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				ENGINE_DRIVING_OBJECT(HelicopterControlAttributes, BoundedSpeedGraphAttributes, upwardSpeed),
				ENGINE_DRIVING_OBJECT(HelicopterControlAttributes, BoundedSpeedGraphAttributes, forwardSpeed),
				ENGINE_DRIVING_OBJECT(HelicopterControlAttributes, BoundedSymmetricSpeedGraphAttributes, sidewaysSpeed),
				ENGINE_DRIVING_OBJECT(HelicopterControlAttributes, BoundedSymmetricAngleGraphAttributes, pitchSpeed),
				ENGINE_DRIVING_OBJECT(HelicopterControlAttributes, BoundedSymmetricAngleGraphAttributes, yawSpeed),
				ENGINE_DRIVING_OBJECT(HelicopterControlAttributes, BoundedSymmetricAngleGraphAttributes, rollSpeed),
				ENGINE_DRIVING_OBJECT(HelicopterControlAttributes, BoundedSymmetricAngleGraphAttributes, pitchAngle),
				ENGINE_DRIVING_OBJECT(HelicopterControlAttributes, BoundedSymmetricAngleGraphAttributes, rollAngle),
				ENGINE_DRIVING_FLOAT(HelicopterControlAttributes, 0, upwardForceScale),
				ENGINE_DRIVING_FLOAT(HelicopterControlAttributes, 1, forwardForceScale),
				ENGINE_DRIVING_FLOAT(HelicopterControlAttributes, 2, forwardPitchTorqueScale),
				ENGINE_DRIVING_FLOAT(HelicopterControlAttributes, 3, reverseForceScale),
				ENGINE_DRIVING_FLOAT(HelicopterControlAttributes, 4, reversePitchTorqueScale),
				ENGINE_DRIVING_FLOAT(HelicopterControlAttributes, 5, lateralSteeringForceScale),
				ENGINE_DRIVING_FLOAT(HelicopterControlAttributes, 6, steeringRollTorqueScale),
				ENGINE_DRIVING_FLOAT(HelicopterControlAttributes, 7, steeringYawTorqueScale),
				ENGINE_DRIVING_FLOAT(HelicopterControlAttributes, 8, upwardThrottleIncreaseRate),
				ENGINE_DRIVING_FLOAT(HelicopterControlAttributes, 9, upwardThrottleDecreaseRate),
				ENGINE_DRIVING_FLOAT(HelicopterControlAttributes, 10, forwardThrottleIncreaseRate),
				ENGINE_DRIVING_FLOAT(HelicopterControlAttributes, 11, forwardThrottleDecreaseRate),
				ENGINE_DRIVING_FLOAT(HelicopterControlAttributes, 12, steeringFactorIncreaseRate),
				ENGINE_DRIVING_FLOAT(HelicopterControlAttributes, 13, steeringFactorDecreaseRate),
				ENGINE_DRIVING_FLOAT(HelicopterControlAttributes, 14, gravity)
			};
			sList.members = sMembers;
			sList.count = 23;
			return &sList;
		}
	}
}
