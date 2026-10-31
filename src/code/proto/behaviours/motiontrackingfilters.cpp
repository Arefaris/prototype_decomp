#include "code/proto/behaviours/motiontrackingfilters.h"
#include "code/math/mathutils.h"
#include "code/math/worldbounds.h"
#include <math.h>

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10088090
	content::ClassInfo* DistanceAcceleratedMotionTrackingFilter::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DistanceAcceleratedMotionTrackingFilter";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x100880D0
	content::ClassInfo* LinearVelocityNoiseTrackingFilter::WaveGenerator::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::LinearVelocityNoiseTrackingFilter::WaveGenerator";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10088110
	content::ClassInfo* LinearVelocityNoiseTrackingFilter::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::LinearVelocityNoiseTrackingFilter";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10088160
	// EQUIVALENT: the engine loads the constant one into a register before the first store and zeroes the other register first, the stores are the same (72.5 %)
	LinearVelocityNoiseTrackingFilter::WaveGenerator::WaveGenerator()
	{
		float one = engine::driving::gOne;
		minSpeed = 0.0f;
		maxSpeed = one;
		maxAmplitude = one;
		maxOffsetFraction = 0.0f;
		numWavesPerCycle = 1;
	}


	// FUNCTION: ENGINE 0x100881A0
	float LinearVelocityNoiseTrackingFilter::WaveGenerator::Evaluate(float time, float speed, float cycleDuration) const
	{
		float clamped = math::Clamp(speed, minSpeed, maxSpeed);
		float frequency;
		if (math::WORLD_MIN - cycleDuration >= 0.0f)
		{
			frequency = 0.0f;
		}
		else
		{
			frequency = (float)(int)numWavesPerCycle / cycleDuration;
		}
		float range = maxSpeed - minSpeed;
		float offset;
		if (minSpeed - maxSpeed >= 0.0f)
		{
			offset = 0.0f;
		}
		else
		{
			offset = clamped - minSpeed;
		}
		float ratio;
		if (math::WORLD_MIN - range >= 0.0f)
		{
			ratio = 0.0f;
		}
		else
		{
			ratio = offset / range;
		}
		float wave = (sinf(frequency * time * 6.2831855f - 1.5707964f) + 1.0f) * engine::driving::gHalf;
		float fraction = math::Clamp(maxOffsetFraction, 0.0f, engine::driving::gOne);
		return ((1.0f - fraction) * wave + fraction) * maxAmplitude * ratio;
	}

	// FUNCTION: ENGINE 0x10088A10
	float LinearVelocityNoiseTrackingFilter::EvaluateWaves(float* time, float speed)
	{
		float sum = 0.0f;
		WaveGenerator* end = waveGenerators.end;
		WaveGenerator* wave = waveGenerators.begin;
		if (wave != end)
		{
			do
			{
				sum += wave->Evaluate(*time, speed, overallCycleDuration);
				wave++;
			}
			while (wave != end);
		}
		if (*time >= overallCycleDuration)
		{
			float duration = math::Max(0.00001f, overallCycleDuration);
			float cycles = (1.0f / duration) * *time;
			*time = (cycles - floorf(cycles)) * duration;
		}
		return sum;
	}

	// FUNCTION: ENGINE 0x10088450
	// EQUIVALENT: the engine loads both constants before the first store and stores the vftable behind three members, ours schedules the loads and the vftable store earlier (53.4 %)
	DistanceAcceleratedMotionTrackingFilter::DistanceAcceleratedMotionTrackingFilter()
	{
		float one = engine::driving::gOne;
		distanceMax = 10.0f;
		velocityMin = one;
		velocityMax = 10.0f;
		accelerationMin = 10.0f;
		accelerationMax = 100.0f;
	}

	// FUNCTION: ENGINE 0x10088560
	// NONMATCHING: the engine computes the position difference with SSE and the length with the x87 square root, and schedules the loads of the state in a different order (16 %)
#ifdef NONMATCHING
	void DistanceAcceleratedMotionTrackingFilter::Update(const TimeStep& step, const math::Matrix& target,
		const void* unknown, engine::MotionState& state)
	{
		float invDt = step.invDt;
		float dt = step.dt;
		state.UpdateAngularVelocity(target, invDt);
		math::Vector delta(target.m[3][0] - state.transform.m[3][0], target.m[3][1] - state.transform.m[3][1],
			target.m[3][2] - state.transform.m[3][2]);
		float blend = sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z) / distanceMax;
		blend = math::Clamp(blend, 0.0f, engine::driving::gOne);
		math::Vector old(state.linearVelocity.x, state.linearVelocity.y, state.linearVelocity.z);
		math::Vector velocity(delta.x * invDt, delta.y * invDt, delta.z * invDt);
		math::Vector acceleration(velocity.x - old.x, velocity.y - old.y, velocity.z - old.z);
		float maxAcceleration = ((accelerationMax - accelerationMin) * blend + accelerationMin) * dt;
		if (maxAcceleration * maxAcceleration <= acceleration.z * acceleration.z + acceleration.y * acceleration.y +
			acceleration.x * acceleration.x)
		{
			acceleration.Normalize();
			velocity.y = acceleration.y * maxAcceleration + old.y;
			velocity.z = acceleration.z * maxAcceleration + old.z;
			velocity.x = acceleration.x * maxAcceleration + old.x;
		}
		float maxSpeed = (velocityMax - velocityMin) * blend + velocityMin;
		if (maxSpeed * maxSpeed < velocity.z * velocity.z + velocity.y * velocity.y + velocity.x * velocity.x)
		{
			acceleration.Set(velocity.x, velocity.y, velocity.z);
			acceleration.Normalize();
			velocity.x = acceleration.x * maxSpeed;
			velocity.y = acceleration.y * maxSpeed;
			velocity.z = acceleration.z * maxSpeed;
		}
		state.linearAcceleration.x = velocity.x - old.x;
		state.linearAcceleration.y = velocity.y - old.y;
		state.linearAcceleration.z = velocity.z - old.z;
		state.linearAcceleration.Scale(invDt);
		state.linearVelocity.x = velocity.x;
		state.linearVelocity.y = velocity.y;
		state.linearVelocity.z = velocity.z;
		math::Vector offset(velocity.x * dt + state.transform.m[3][0], velocity.y * dt + state.transform.m[3][1],
			velocity.z * dt + state.transform.m[3][2]);
		state.transform.m[3][0] = offset.x;
		state.transform.m[3][1] = offset.y;
		state.transform.m[3][2] = offset.z;
		offset.x -= target.m[3][0];
		offset.y -= target.m[3][1];
		offset.z -= target.m[3][2];
		acceleration.Set(velocity.x, velocity.y, velocity.z);
		float distance = offset.Normalize();
		if (distanceMax < distance)
		{
			state.transform.m[3][0] = target.m[3][0];
			state.transform.m[3][1] = target.m[3][1];
			state.transform.m[3][2] = target.m[3][2];
			state.transform.m[3][0] = offset.x * distanceMax + state.transform.m[3][0];
			state.transform.m[3][1] = offset.y * distanceMax + state.transform.m[3][1];
			state.transform.m[3][2] = offset.z * distanceMax + state.transform.m[3][2];
		}
	}
#endif

	// FUNCTION: ENGINE 0x100891A0
	content::MemberList* DistanceAcceleratedMotionTrackingFilter::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::MotionTrackingFilter>();
		static content::BaseClassCasterImpl<engine::MotionTrackingFilter, DistanceAcceleratedMotionTrackingFilter>
			sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<DistanceAcceleratedMotionTrackingFilter, float, 0>("pn"),
				PROTO_OFFSET(DistanceAcceleratedMotionTrackingFilter, distanceMax), "distanceMax" },
			{ content::GetMemberPrimitiveMetaType<DistanceAcceleratedMotionTrackingFilter, float, 1>("pn"),
				PROTO_OFFSET(DistanceAcceleratedMotionTrackingFilter, velocityMin), "velocityMin" },
			{ content::GetMemberPrimitiveMetaType<DistanceAcceleratedMotionTrackingFilter, float, 2>("pn"),
				PROTO_OFFSET(DistanceAcceleratedMotionTrackingFilter, velocityMax), "velocityMax" },
			{ content::GetMemberPrimitiveMetaType<DistanceAcceleratedMotionTrackingFilter, float, 3>("pn"),
				PROTO_OFFSET(DistanceAcceleratedMotionTrackingFilter, accelerationMin), "accelerationMin" },
			{ content::GetMemberPrimitiveMetaType<DistanceAcceleratedMotionTrackingFilter, float, 4>("pn"),
				PROTO_OFFSET(DistanceAcceleratedMotionTrackingFilter, accelerationMax), "accelerationMax" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10089340
	content::MemberList* LinearVelocityNoiseTrackingFilter::WaveGenerator::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<WaveGenerator, float, 0>("pn"),
				PROTO_OFFSET(WaveGenerator, minSpeed), "minSpeed" },
			{ content::GetMemberPrimitiveMetaType<WaveGenerator, float, 1>("pn"),
				PROTO_OFFSET(WaveGenerator, maxSpeed), "maxSpeed" },
			{ content::GetMemberPrimitiveMetaType<WaveGenerator, float, 2>("pn"),
				PROTO_OFFSET(WaveGenerator, maxAmplitude), "maxAmplitude" },
			{ content::GetMemberPrimitiveMetaType<WaveGenerator, float, 3>("pn"),
				PROTO_OFFSET(WaveGenerator, maxOffsetFraction), "maxOffsetFraction" },
			{ content::GetMemberPrimitiveMetaType<WaveGenerator, unsigned int, 0>("pn"),
				PROTO_OFFSET(WaveGenerator, numWavesPerCycle), "numWavesPerCycle" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10089DA0
	// EQUIVALENT: the engine stores the vftable and the zeros first and loads the constants once, ours stores the array's words first (23.4 %)
	LinearVelocityNoiseTrackingFilter::LinearVelocityNoiseTrackingFilter()
	{
		float one = engine::driving::gOne;
		noiseDirectionLocalSpace.x = 0.0f;
		noiseDirectionLocalSpace.y = one;
		noiseDirectionLocalSpace.z = 0.0f;
		overallCycleDuration = one;
		maxAcceleration = 10.0f;
	}

	// FUNCTION: ENGINE 0x100894B0
	// NONMATCHING: the engine copies the matrix's rows with the SSE stores of the state and keeps the squares of the velocity in the x87 stack in another order (11 %)
#ifdef NONMATCHING
	void LinearVelocityNoiseTrackingFilter::Update(const TimeStep& step, const math::Matrix& target,
		const void* unknown, engine::MotionState& state)
	{
		const math::Matrix& previous = *(const math::Matrix*)unknown;
		float invDt = step.invDt;
		float dt = step.dt;
		state.UpdateAngularVelocity(target, invDt);
		math::Vector direction((target.m[3][0] - previous.m[3][0]) * invDt, (target.m[3][1] - previous.m[3][1]) * invDt,
			(target.m[3][2] - previous.m[3][2]) * invDt);
		math::Vector acceleration(direction.x - state.linearVelocity.x, direction.y - state.linearVelocity.y,
			direction.z - state.linearVelocity.z);
		math::Vector velocity(direction.x, direction.y, direction.z);
		float speed = direction.Normalize();
		float currentSpeed = sqrtf(state.linearVelocity.x * state.linearVelocity.x +
			state.linearVelocity.y * state.linearVelocity.y + state.linearVelocity.z * state.linearVelocity.z);
		float maxStep = maxAcceleration * dt;
		if (maxStep < fabsf(speed - currentSpeed))
		{
			speed = math::Clamp(speed, currentSpeed - maxStep, maxStep + currentSpeed);
			velocity.x = speed * direction.x;
			velocity.y = direction.y * speed;
			velocity.z = direction.z * speed;
			acceleration.x = velocity.x - state.linearVelocity.x;
			acceleration.y = velocity.y - state.linearVelocity.y;
			acceleration.z = velocity.z - state.linearVelocity.z;
		}
		state.linearVelocity.x = velocity.x;
		state.linearVelocity.y = velocity.y;
		state.linearVelocity.z = velocity.z;
		state.linearAcceleration.x = acceleration.x * invDt;
		state.linearAcceleration.y = acceleration.y * invDt;
		state.linearAcceleration.z = acceleration.z * invDt;
		math::Matrix result;
		for (int row = 0; row < 3; row++)
		{
			for (int column = 0; column < 4; column++)
			{
				result.m[row][column] = target.m[row][column];
			}
		}
		result.m[3][3] = target.m[3][3];
		velocity.x = target.m[3][0];
		velocity.y = target.m[3][1];
		velocity.z = target.m[3][2];
		float waves = EvaluateWaves(&state.unknown70, speed);
		math::Vector noise;
		target.Rotate(noiseDirectionLocalSpace, noise);
		result.m[3][0] = noise.x * waves + velocity.x;
		result.m[3][1] = noise.y * waves + velocity.y;
		result.m[3][2] = noise.z * waves + velocity.z;
		state.transform = result;
	}
#endif

	// FUNCTION: ENGINE 0x10089B40
	content::MemberList* LinearVelocityNoiseTrackingFilter::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::MotionTrackingFilter>();
		static content::BaseClassCasterImpl<engine::MotionTrackingFilter, LinearVelocityNoiseTrackingFilter> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<LinearVelocityNoiseTrackingFilter, 0>("pn"), 4,
				"noiseDirectionLocalSpace" },
			{ content::GetMemberPrimitiveMetaType<LinearVelocityNoiseTrackingFilter, float, 0>("pn"),
				PROTO_OFFSET(LinearVelocityNoiseTrackingFilter, overallCycleDuration), "overallCycleDuration" },
			{ content::GetMemberPrimitiveMetaType<LinearVelocityNoiseTrackingFilter, float, 1>("pn"),
				PROTO_OFFSET(LinearVelocityNoiseTrackingFilter, maxAcceleration), "maxAcceleration" },
			{ content::GetArrayDynamicMetaType<LinearVelocityNoiseTrackingFilter, WaveArray>(
				content::GetClassMetaType<WaveGenerator>(), "pn"),
				PROTO_OFFSET(LinearVelocityNoiseTrackingFilter, waveGenerators), "waveGenerators" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}
}

// Members of the wave array that the engine's unit holds copies of (the code that uses them is not reconstructed)
namespace container
{
	typedef proto::LinearVelocityNoiseTrackingFilter::WaveGenerator WaveGenerator;
	typedef proto::LinearVelocityNoiseTrackingFilter::WaveArray WaveArray;

	template bool WaveArray::Create(unsigned int);
	template WaveGenerator* WaveArray::Begin();
	template WaveGenerator& WaveArray::operator[](int);
	template const WaveGenerator& WaveArray::operator[](int) const;
	template void WaveArray::Clear();
	template void WaveArray::Free();
	template WaveGenerator* WaveArray::Insert(WaveGenerator*, const WaveGenerator&);
	template WaveGenerator* WaveArray::Insert(WaveGenerator*, unsigned int, const WaveGenerator&);
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10087E30
// FUNCTION: ENGINE 0x10087E40
// FUNCTION: ENGINE 0x10087E90
// FUNCTION: ENGINE 0x10088150
// FUNCTION: ENGINE 0x100882F0
// FUNCTION: ENGINE 0x10088310
// FUNCTION: ENGINE 0x10088370
// FUNCTION: ENGINE 0x100883E0
// FUNCTION: ENGINE 0x100883F0
// FUNCTION: ENGINE 0x10088430
// FUNCTION: ENGINE 0x10088440
// FUNCTION: ENGINE 0x100884A0
// FUNCTION: ENGINE 0x100884B0
// FUNCTION: ENGINE 0x100884C0
// FUNCTION: ENGINE 0x100884F0
// FUNCTION: ENGINE 0x10088500
// FUNCTION: ENGINE 0x10088530
// FUNCTION: ENGINE 0x10088B00
// FUNCTION: ENGINE 0x10088B10
// FUNCTION: ENGINE 0x10088B50
// FUNCTION: ENGINE 0x10088B90
// FUNCTION: ENGINE 0x10088BD0
// FUNCTION: ENGINE 0x10088C10
// FUNCTION: ENGINE 0x10088C50
// FUNCTION: ENGINE 0x10088C90
// FUNCTION: ENGINE 0x10088CD0
// FUNCTION: ENGINE 0x10088D10
// FUNCTION: ENGINE 0x10088D50
// FUNCTION: ENGINE 0x10088D90
// FUNCTION: ENGINE 0x10088DD0
// FUNCTION: ENGINE 0x10088E20
// FUNCTION: ENGINE 0x10088E30
// FUNCTION: ENGINE 0x10088E90
// FUNCTION: ENGINE 0x10088EC0
// FUNCTION: ENGINE 0x10088EE0
// FUNCTION: ENGINE 0x10088F00
// FUNCTION: ENGINE 0x10088F50
// FUNCTION: ENGINE 0x10088F90
// FUNCTION: ENGINE 0x10088FE0
// FUNCTION: ENGINE 0x10089030
// FUNCTION: ENGINE 0x10089060
// FUNCTION: ENGINE 0x10089080
// FUNCTION: ENGINE 0x100890A0
// FUNCTION: ENGINE 0x100890D0
// FUNCTION: ENGINE 0x10089100
// FUNCTION: ENGINE 0x10089140
// FUNCTION: ENGINE 0x100898C0
// FUNCTION: ENGINE 0x10089920
// FUNCTION: ENGINE 0x10089930
// FUNCTION: ENGINE 0x10089990
// FUNCTION: ENGINE 0x100899D0
// FUNCTION: ENGINE 0x10089AF0
// FUNCTION: ENGINE 0x10089CB0
// FUNCTION: ENGINE 0x10089CD0
// FUNCTION: ENGINE 0x10089D40
// FUNCTION: ENGINE 0x10089DF0
// FUNCTION: ENGINE 0x10089E20
// FUNCTION: ENGINE 0x10089F10
