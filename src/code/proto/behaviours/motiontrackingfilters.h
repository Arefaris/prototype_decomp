// proto::DistanceAcceleratedMotionTrackingFilter and proto::LinearVelocityNoiseTrackingFilter (RTTI and reflection
// names; base engine::MotionTrackingFilter): the filters that follow a target transform with a speed limit that grows
// with the distance, and that follow it with a linear velocity noise (sine waves along a direction) added. Unit
// 0x10087E30 - 0x10089F50 (no assert path; the file name is a guess). The reflected names are original, the rest is
// guessed.
#ifndef PROTO_BEHAVIOURS_MOTIONTRACKINGFILTERS_H
#define PROTO_BEHAVIOURS_MOTIONTRACKINGFILTERS_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/engine/motiontrackingfilter.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
		extern const float gHalf;
	}
}

namespace proto
{
	// Follows the target; the limits of the speed and of the acceleration are blended by the distance to the target
	class DistanceAcceleratedMotionTrackingFilter : public engine::MotionTrackingFilter
	{
	public:
		// 0x10088450
		DistanceAcceleratedMotionTrackingFilter();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10088560)
		virtual void Update(const TimeStep& step, const math::Matrix& target, const void* unknown,
			engine::MotionState& state);

		float distanceMax;  // +4
		float velocityMin;  // +8
		float velocityMax;  // +0xC
		float accelerationMin;  // +0x10
		float accelerationMax;  // +0x14
	};

	// Follows the target and adds the sum of sine waves to the position along a direction
	class LinearVelocityNoiseTrackingFilter : public engine::MotionTrackingFilter
	{
	public:
		// One wave of the noise (RTTI proto::LinearVelocityNoiseTrackingFilter::WaveGenerator; 0x14 bytes)
		class WaveGenerator
		{
		public:
			// 0x10088160
			WaveGenerator();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x100881A0: the wave's contribution at time for a moving speed, within a cycle of cycleDuration seconds
			float Evaluate(float time, float speed, float cycleDuration) const;

			float minSpeed;  // +0
			float maxSpeed;  // +4
			float maxAmplitude;  // +8
			float maxOffsetFraction;  // +0xC
			unsigned int numWavesPerCycle;  // +0x10
		};

		typedef container::ArrayDynamic<WaveGenerator, container::AllocatorNew> WaveArray;

		// 0x10089DA0
		LinearVelocityNoiseTrackingFilter();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x100894B0)
		virtual void Update(const TimeStep& step, const math::Matrix& target, const void* unknown,
			engine::MotionState& state);

		// 0x10088A10: the sum of the waves at time; wraps time into the cycle
		float EvaluateWaves(float* time, float speed);

		math::Vector noiseDirectionLocalSpace;  // +4
		float overallCycleDuration;  // +0x10
		float maxAcceleration;  // +0x14
		WaveArray waveGenerators;  // +0x18
		int unknown24;  // behind the array: its allocator word
	};
}

namespace container
{
	// Erase moves the elements down with a copy that answers the end of the destination
	template<> struct ArrayEraseInline<proto::LinearVelocityNoiseTrackingFilter::WaveGenerator>
	{
		enum
		{
			value = 4
		};
	};
}

#endif
