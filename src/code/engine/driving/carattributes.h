// The reflected attribute classes of the car code (namespace engine::driving; the code sits in 0x10934540 -
// 0x10936E30, no assert path; directory and file names guessed). The classes are plain data the car behaviours read;
// the member names are the reflected ones, the derived values are in the units the reflection shows.
#ifndef ENGINE_DRIVING_CARATTRIBUTES_H
#define ENGINE_DRIVING_CARATTRIBUTES_H

#include "code/content/metatype.h"
#include "code/engine/driving/boundedgraphs.h"

namespace choreo
{
	// 0x10D94F78 (symbols.txt): 0.0f in the data
	extern const float gZero;
}

namespace engine
{
	namespace driving
	{
		// 0x111EB19C / 0x111EB198 (symbols.txt): the smallest G scale of a suspension and the largest fraction the
		// intermediate factors take (names guessed)
		extern float gMinGScale;
		extern float gMaxFraction;

		// The pooled constants the car attributes' defaults are read from, kept as data of the engine (0x10D946E0 and
		// the following; symbols.txt; names guessed): a use of one is a load from memory, never a literal
		extern const float gOne;
		extern const float gHalf;
		extern const float gPointThree;
		extern const float gTwo;
		extern const float gThirty;

		// Five positions along an axis, in order and a little apart (0, 0.1 ... 0.4 at the start)
		struct GraphKnots
		{
			GraphKnots()
			{
				knots[0] = 0.0f;
				knots[1] = 0.1f;
				knots[2] = 0.2f;
				knots[3] = 0.3f;
				knots[4] = 0.4f;
			}

			// 0x10934910: sets one knot and moves the others away from it where they would cross it
			void SetKnot(unsigned int index, float value);

			float knots[5];  // +0x0
		};

		// The function a GraphCurve is read with (0x1093D440 is the one in use)
		typedef float (*GraphFunction)(float x, unsigned int count, const float* xs, const float* ys);

		// A piecewise linear graph: five values over the positions of a GraphKnots
		struct GraphCurve
		{
			GraphCurve()
			{
				values[0] = 0.0f;
				values[1] = 0.0f;
				values[2] = 0.0f;
				values[3] = 0.0f;
				values[4] = 0.0f;
			}

			// 0x10934690 (kept copy)
			void SetKnots(const float* newKnots)
			{
				knots = newKnots;
			}
			// 0x109346B0 (kept copy)
			void SetValue(unsigned int index, float value)
			{
				if (index < 5)
				{
					values[index] = value;
				}
			}

			// 0x109346D0 (kept copy): the graph at x, 0 without a function or knots
			float Evaluate(float x, GraphFunction function) const
			{
				float result = 0.0f;
				if (function != 0 && knots != 0)
				{
					result = function(x, 5, knots, values);
				}
				return result;
			}

			const float* knots;  // +0x0
			float values[5];  // +0x4
		};

		// How a car's suspension pushes back (struct in the RTTI of its reflection helpers; 0x40 bytes). The graph
		// runs from the maximum stretch (negative) through the rest position to the maximum compression; the
		// reflected members are derived from the knots and values
		struct CarSuspensionAttributes
		{
			// 0x10935470
			CarSuspensionAttributes();

			// 0x10934AF0: the force at a compression (distance) and a speed: the graph plus the speed's share of the
			// maximum G scale, times gravity
			float GetForce(float compression, float speedValue) const;

			// 0x10934540 / 0x10935220
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x10934770 / 0x10934BB0
			float GetMaxCompressionDistance() const;
			void SetMaxCompressionDistance(float distance);
			// 0x10934780 / 0x10934BE0
			float GetMaxStretchDistance() const;
			void SetMaxStretchDistance(float distance);
			// 0x10934790 / 0x109347A0
			float GetMaxGScale() const;
			void SetMaxGScale(float scale);
			// 0x109347D0 / 0x10934C20
			float GetIntermediateCompressionFactor() const;
			void SetIntermediateCompressionFactor(float factor);
			// 0x109347E0 / 0x10934C80
			float GetIntermediateStretchFactor() const;
			void SetIntermediateStretchFactor(float factor);
			// 0x109347F0 / 0x10934810
			float GetIntermediateCompressionForceFactor() const;
			void SetIntermediateCompressionForceFactor(float factor);
			// 0x10934870 / 0x10934880
			float GetIntermediateStretchForceFactor() const;
			void SetIntermediateStretchForceFactor(float factor);
			// 0x10934580 / 0x10934590
			float GetMaxCompressionSpeedKmh() const;
			void SetMaxCompressionSpeedKmh(float kmh);
			// 0x109345B0 / 0x109345C0
			float GetMaxStretchSpeedKmh() const;
			void SetMaxStretchSpeedKmh(float kmh);
			// 0x109345E0 / 0x109345F0
			float GetGravity() const;
			void SetGravity(float value);
			// 0x10934600 / 0x109348D0
			float GetPitchScale() const;
			void SetPitchScale(float scale);
			// 0x10934610 / 0x109348F0
			float GetRollScale() const;
			void SetRollScale(float scale);

			GraphKnots knots;  // +0x0
			GraphCurve curve;  // +0x14
			BoundedSpeedGraphAttributes speed;  // +0x2C
			float gravity;  // +0x34
			float pitchScale;  // +0x38
			float rollScale;  // +0x3C
		};

		// How hard a car's controls push it (struct; 0x3C bytes): the force and torque scales of the throttle and the
		// steering, how quickly both build up and fade, and how fast the car may go in each direction
		struct CarControlAttributes
		{
			// 0x109355F0
			CarControlAttributes();

			// 0x109355B0 / 0x10935A70
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float forwardForceScale;  // +0x0
			float forwardPitchTorqueScale;  // +0x4
			float reverseForceScale;  // +0x8
			float reversePitchTorqueScale;  // +0xC
			float lateralSteeringForceScale;  // +0x10
			float steeringRollTorqueScale;  // +0x14
			float steeringYawTorqueScale;  // +0x18
			float forwardThrottleIncreaseRate;  // +0x1C
			float forwardThrottleDecreaseRate;  // +0x20
			float steeringFactorIncreaseRate;  // +0x24
			float steeringFactorDecreaseRate;  // +0x28
			BoundedSpeedGraphAttributes forwardSpeed;  // +0x2C
			BoundedSymmetricSpeedGraphAttributes sidewaysSpeed;  // +0x34
			BoundedSymmetricAngleGraphAttributes yawSpeed;  // +0x38
		};

		// How hard a helicopter's controls push it (struct; 0x64 bytes): the car's control scales with an upward
		// axis, and the speeds and angles it may reach
		struct HelicopterControlAttributes
		{
			// 0x10936CC0
			HelicopterControlAttributes();

			// 0x10936C80 / 0x109371B0
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x10936D70, 0x10936D80, 0x10936D90, 0x10936DA0, 0x10936DB0, 0x10936DC0, 0x10936DD0, 0x10936DE0 (kept
			// copies of the accessors)
			BoundedSpeedGraphAttributes& GetUpwardSpeed();
			BoundedSpeedGraphAttributes& GetForwardSpeed();
			BoundedSymmetricSpeedGraphAttributes& GetSidewaysSpeed();
			BoundedSymmetricAngleGraphAttributes& GetPitchSpeed();
			BoundedSymmetricAngleGraphAttributes& GetYawSpeed();
			BoundedSymmetricAngleGraphAttributes& GetRollSpeed();
			BoundedSymmetricAngleGraphAttributes& GetPitchAngle();
			BoundedSymmetricAngleGraphAttributes& GetRollAngle();

			float upwardForceScale;  // +0x0
			float forwardForceScale;  // +0x4
			float forwardPitchTorqueScale;  // +0x8
			float reverseForceScale;  // +0xC
			float reversePitchTorqueScale;  // +0x10
			float lateralSteeringForceScale;  // +0x14
			float steeringRollTorqueScale;  // +0x18
			float steeringYawTorqueScale;  // +0x1C
			float upwardThrottleIncreaseRate;  // +0x20
			float upwardThrottleDecreaseRate;  // +0x24
			float forwardThrottleIncreaseRate;  // +0x28
			float forwardThrottleDecreaseRate;  // +0x2C
			float steeringFactorIncreaseRate;  // +0x30
			float steeringFactorDecreaseRate;  // +0x34
			float gravity;  // +0x38
			BoundedSpeedGraphAttributes upwardSpeed;  // +0x3C
			BoundedSpeedGraphAttributes forwardSpeed;  // +0x44
			BoundedSymmetricSpeedGraphAttributes sidewaysSpeed;  // +0x4C
			BoundedSymmetricAngleGraphAttributes pitchSpeed;  // +0x50
			BoundedSymmetricAngleGraphAttributes yawSpeed;  // +0x54
			BoundedSymmetricAngleGraphAttributes rollSpeed;  // +0x58
			BoundedSymmetricAngleGraphAttributes pitchAngle;  // +0x5C
			BoundedSymmetricAngleGraphAttributes rollAngle;  // +0x60
		};
	}
}

#endif
