#include "code/engine/motiontrackingfilter.h"
#include "code/math/mathutils.h"
#include <math.h>

namespace math
{
	// The zero vector (another unit's constant)
	extern const Vector kZeroVector;
}

namespace math
{
	// a . b summed as x + (y + z) (the order the engine's code shows; name guessed)
	inline float DotProduct(const Vector& a, const Vector& b)
	{
		return a.x * b.x + (a.y * b.y + a.z * b.z);
	}
}

namespace engine
{
	// FUNCTION: ENGINE 0x107FC800
	content::ClassInfo* MotionTrackingFilter::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::MotionTrackingFilter";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107FC840
	content::MemberList* MotionTrackingFilter::GetMembers()
	{
		static content::MemberList sList;
		return &sList;
	}

	// FUNCTION: ENGINE 0x107FC870
	content::ClassInfo* RigidMotionTrackingFilter::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::RigidMotionTrackingFilter";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107FC8B0
	content::ClassInfo* DampedLinearMotionTrackingFilter::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::DampedLinearMotionTrackingFilter";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107FC8F0
	content::ClassInfo* SpringBasedLinearMotionFilter::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SpringBasedLinearMotionFilter";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107FC930
	content::ClassInfo* DampedAngularMotionTrackingFilter::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::DampedAngularMotionTrackingFilter";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107FC970
	content::ClassInfo* SpringBasedAngularMotionFilter::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SpringBasedAngularMotionFilter";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107FC9B0
	MotionTrackingFilter::TimeStep::TimeStep(float newDt)
	{
		dt = newDt;
		invDt = 1.0f / newDt;
	}

	// FUNCTION: ENGINE 0x107FC9D0
	void RigidMotionTrackingFilter::Update(const TimeStep& step, const math::Matrix& target, const void* unknown,
		MotionState& state)
	{
		float invDt = step.invDt;
		state.UpdateLinearVelocity(target, invDt);
		state.UpdateAngularVelocity(target, invDt);
		state.transform = target;
	}

	// FUNCTION: ENGINE 0x107FCA10
	SpringBasedLinearMotionFilter::SpringBasedLinearMotionFilter()
	{
		springConstant = 1.0f;
		dampingConstant = 1.0f;
		maximumDistanceLag = -1.0f;
	}

	// FUNCTION: ENGINE 0x107FCA50
	DampedAngularMotionTrackingFilter::DampedAngularMotionTrackingFilter()
	{
		maximumAngularSpeed = 1.0f;
		maximumAngleLag = -1.0f;
	}

	// FUNCTION: ENGINE 0x107FCA90
	SpringBasedAngularMotionFilter::SpringBasedAngularMotionFilter()
	{
		springConstant = 1.0f;
		dampingConstant = 1.0f;
		maximumAngleLag = -1.0f;
	}

	// FUNCTION: ENGINE 0x107FCC10
	DampedLinearMotionTrackingFilter::DampedLinearMotionTrackingFilter()
	{
		maximumSpeed = 1.0f;
		maximumDistanceLag = -1.0f;
	}

	// FUNCTION: ENGINE 0x107FCC70
	void DampedLinearMotionTrackingFilter::Update(const TimeStep& step, const math::Matrix& target, const void* unknown,
		MotionState& state)
	{
		float maxStep = step.dt * maximumSpeed;
		float invDt = step.invDt;
		state.UpdateAngularVelocity(target, invDt);
		math::Vector position(state.transform.m[3][0], state.transform.m[3][1], state.transform.m[3][2]);
		math::Vector oldVelocity(state.linearVelocity.x, state.linearVelocity.y, state.linearVelocity.z);
		math::Vector targetPosition(target.m[3][0], target.m[3][1], target.m[3][2]);
		math::Vector delta(targetPosition.x - position.x, targetPosition.y - position.y,
			targetPosition.z - position.z);
		if (math::DistanceSquared(targetPosition, position) > maxStep * maxStep)
		{
			float distance = delta.Normalize();
			float speed = maximumSpeed;
			if (maximumDistanceLag >= 0.0f)
			{
				maxStep = math::Max(maxStep, distance - maximumDistanceLag);
			}
			math::Vector current(state.transform.m[3][0], state.transform.m[3][1], state.transform.m[3][2]);
			math::Vector newPosition(delta.x * maxStep + current.x, delta.y * maxStep + current.y,
				delta.z * maxStep + current.z);
			state.transform = target;
			state.transform.m[3][0] = newPosition.x;
			state.transform.m[3][1] = newPosition.y;
			state.transform.m[3][2] = newPosition.z;
			state.linearVelocity.x = delta.x * speed;
			state.linearVelocity.y = delta.y * speed;
			state.linearVelocity.z = delta.z * speed;
		}
		else
		{
			state.transform = target;
			state.linearVelocity.x = delta.x * invDt;
			state.linearVelocity.y = delta.y * invDt;
			state.linearVelocity.z = delta.z * invDt;
		}
		math::Vector& acceleration = state.linearAcceleration;
		acceleration.Sub(state.linearVelocity, oldVelocity);
		acceleration.Scale(invDt);
	}

	// FUNCTION: ENGINE 0x107FCEF0
	// EQUIVALENT: scheduling and register choice (the engine reloads the state's velocity for each use)
	void SpringBasedLinearMotionFilter::Update(const TimeStep& step, const math::Matrix& target, const void* unknown,
		MotionState& state)
	{
		float invDt = step.invDt;
		state.UpdateAngularVelocity(target, invDt);
		math::Vector targetPosition(target.m[3][0], target.m[3][1], target.m[3][2]);
		math::Vector position(state.transform.m[3][0], state.transform.m[3][1], state.transform.m[3][2]);
		math::Vector delta(targetPosition.x - position.x, targetPosition.y - position.y,
			targetPosition.z - position.z);
		math::Vector change(delta.x * invDt - state.linearVelocity.x, delta.y * invDt - state.linearVelocity.y,
			delta.z * invDt - state.linearVelocity.z);
		float damping = -dampingConstant;
		math::Vector acceleration(state.linearVelocity.x * damping + delta.x * springConstant,
			state.linearVelocity.y * damping + delta.y * springConstant,
			state.linearVelocity.z * damping + delta.z * springConstant);
		math::Vector magnitude(fabsf(acceleration.x), fabsf(acceleration.y), fabsf(acceleration.z));
		math::Vector limit(magnitude.x * step.dt, magnitude.y * step.dt, magnitude.z * step.dt);
		change.x = math::Clamp(change.x, -limit.x, limit.x);
		change.y = math::Clamp(change.y, -limit.y, limit.y);
		change.z = math::Clamp(change.z, -limit.z, limit.z);
		math::Vector velocity(state.linearVelocity.x + change.x, state.linearVelocity.y + change.y,
			state.linearVelocity.z + change.z);
		math::Vector displacement(velocity.x * step.dt, velocity.y * step.dt, velocity.z * step.dt);
		math::Vector current(state.transform.m[3][0], state.transform.m[3][1], state.transform.m[3][2]);
		math::Vector newPosition(displacement.x + current.x, displacement.y + current.y, displacement.z + current.z);
		math::Vector toTarget(targetPosition.x - newPosition.x, targetPosition.y - newPosition.y,
			targetPosition.z - newPosition.z);
		if (math::DistanceSquared(targetPosition, newPosition) > maximumDistanceLag * maximumDistanceLag)
		{
			float excess = toTarget.Normalize() - maximumDistanceLag;
			math::Vector lagged(toTarget.x * excess + newPosition.x, toTarget.y * excess + newPosition.y,
				toTarget.z * excess + newPosition.z);
			math::Vector before(state.transform.m[3][0], state.transform.m[3][1], state.transform.m[3][2]);
			math::Vector laggedVelocity((lagged.x - before.x) * invDt, (lagged.y - before.y) * invDt,
				(lagged.z - before.z) * invDt);
			change.x = laggedVelocity.x - state.linearVelocity.x;
			change.y = laggedVelocity.y - state.linearVelocity.y;
			change.z = laggedVelocity.z - state.linearVelocity.z;
			state.linearVelocity.x = laggedVelocity.x;
			state.linearVelocity.y = laggedVelocity.y;
			state.linearVelocity.z = laggedVelocity.z;
			state.transform.m[3][0] = lagged.x;
			state.transform.m[3][1] = lagged.y;
			state.transform.m[3][2] = lagged.z;
		}
		else
		{
			state.linearVelocity.x = velocity.x;
			state.linearVelocity.y = velocity.y;
			state.linearVelocity.z = velocity.z;
			math::Vector before(state.transform.m[3][0], state.transform.m[3][1], state.transform.m[3][2]);
			state.transform.m[3][0] = displacement.x + before.x;
			state.transform.m[3][1] = displacement.y + before.y;
			state.transform.m[3][2] = displacement.z + before.z;
		}
		state.linearAcceleration.Set(change.x * invDt, change.y * invDt, change.z * invDt);
	}

	// The rotation from from to to as a unit axis and an angle in [0, pi] (name guessed)
	void GetRotationDelta(const math::Matrix& from, const math::Matrix& to, math::Vector& axis, float& angle);

	// FUNCTION: ENGINE 0x107FD340
	// EQUIVALENT: in the else branch the engine loads axis.y / axis.z into a register where ours multiplies from
	// memory, and the last two scale products are scheduled differently
	void DampedAngularMotionTrackingFilter::Update(const TimeStep& step, const math::Matrix& target,
		const void* unknown, MotionState& state)
	{
		float invDt = step.invDt;
		state.UpdateLinearVelocity(target, invDt);
		math::Vector& velocity = state.angularVelocity;
		math::Vector oldVelocity(velocity.x, velocity.y, velocity.z);
		float maxAngle = step.dt * maximumAngularSpeed;
		math::Vector axis;
		float angle;
		GetRotationDelta(state.transform, target, axis, angle);
		if (angle > maxAngle)
		{
			float speed = maximumAngularSpeed;
			if (maximumAngleLag >= 0.0f)
			{
				maxAngle = math::Max(maxAngle, angle - maximumAngleLag);
			}
			math::Matrix rotation;
			rotation.Identity();
			rotation.RotationAxisAngle(axis, -maxAngle);
			state.transform.m[3][0] = math::kZeroVector.x;
			state.transform.m[3][1] = math::kZeroVector.y;
			state.transform.m[3][2] = math::kZeroVector.z;
			state.transform.Multiply(state.transform, rotation);
			math::Vector position(target.m[3][0], target.m[3][1], target.m[3][2]);
			state.transform.m[3][0] = position.x;
			state.transform.m[3][1] = position.y;
			state.transform.m[3][2] = position.z;
			velocity.x = axis.x * speed;
			velocity.y = axis.y * speed;
			velocity.z = axis.z * speed;
		}
		else
		{
			state.transform = target;
			float rate = angle * invDt;
			velocity.x = axis.x * rate;
			velocity.y = axis.y * rate;
			velocity.z = axis.z * rate;
		}
		math::Vector& acceleration = state.angularAcceleration;
		acceleration.Sub(velocity, oldVelocity);
		acceleration.Scale(invDt);
	}

	// FUNCTION: ENGINE 0x107FD580
	// EQUIVALENT: scheduling and register choice (the engine reloads the state's angular velocity for each use)
	void SpringBasedAngularMotionFilter::Update(const TimeStep& step, const math::Matrix& target, const void* unknown,
		MotionState& state)
	{
		float invDt = step.invDt;
		state.UpdateLinearVelocity(target, invDt);
		math::Vector axis;
		float angle;
		GetRotationDelta(state.transform, target, axis, angle);
		float rate = angle * invDt;
		math::Vector change(axis.x * rate - state.angularVelocity.x, axis.y * rate - state.angularVelocity.y,
			axis.z * rate - state.angularVelocity.z);
		float spring = springConstant * angle;
		float damping = -dampingConstant;
		math::Vector acceleration(state.angularVelocity.x * damping + spring * axis.x,
			state.angularVelocity.y * damping + axis.y * spring, state.angularVelocity.z * damping + axis.z * spring);
		math::Vector oldVelocity(state.angularVelocity.x, state.angularVelocity.y, state.angularVelocity.z);
		math::Vector magnitude(fabsf(acceleration.x), fabsf(acceleration.y), fabsf(acceleration.z));
		math::Vector limit(magnitude.x * step.dt, magnitude.y * step.dt, magnitude.z * step.dt);
		change.x = math::Clamp(change.x, -limit.x, limit.x);
		change.y = math::Clamp(change.y, -limit.y, limit.y);
		change.z = math::Clamp(change.z, -limit.z, limit.z);
		math::Vector velocity(state.angularVelocity.x + change.x, state.angularVelocity.y + change.y,
			state.angularVelocity.z + change.z);
		float stepAngle = math::DotProduct(velocity, axis) * step.dt;
		state.angularVelocity.x = velocity.x;
		state.angularVelocity.y = velocity.y;
		state.angularVelocity.z = velocity.z;
		float lag = angle - stepAngle;
		if (lag > maximumAngleLag)
		{
			stepAngle = lag - maximumAngleLag + stepAngle;
		}
		math::Matrix rotation;
		rotation.Identity();
		rotation.RotationAxisAngle(axis, -stepAngle);
		math::Vector position(state.transform.m[3][0], state.transform.m[3][1], state.transform.m[3][2]);
		state.transform.Multiply(state.transform, rotation);
		state.transform.m[3][0] = position.x;
		state.transform.m[3][1] = position.y;
		state.transform.m[3][2] = position.z;
		// The engine takes the linear velocity here, not the angular one
		state.angularAcceleration.Sub(state.linearVelocity, oldVelocity);
		state.angularAcceleration.Scale(invDt);
	}

	// FUNCTION: ENGINE 0x107FDB50
	content::MemberList* RigidMotionTrackingFilter::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<MotionTrackingFilter>();
		static content::BaseClassCasterImpl<MotionTrackingFilter, RigidMotionTrackingFilter> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

#define ENGINE_FLOAT_MEMBER(Class, index, member) \
	{ content::GetMemberPrimitiveMetaType<Class, float, index>("pn"), \
		content::MemberOffset(&((Class*)0)->member, (int)&((Class*)0)->member), #member }

	// FUNCTION: ENGINE 0x107FDBB0
	content::MemberList* DampedLinearMotionTrackingFilter::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<MotionTrackingFilter>();
		static content::BaseClassCasterImpl<MotionTrackingFilter, DampedLinearMotionTrackingFilter> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			ENGINE_FLOAT_MEMBER(DampedLinearMotionTrackingFilter, 0, maximumSpeed),
			ENGINE_FLOAT_MEMBER(DampedLinearMotionTrackingFilter, 1, maximumDistanceLag)
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x107FDC80
	content::MemberList* SpringBasedLinearMotionFilter::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<MotionTrackingFilter>();
		static content::BaseClassCasterImpl<MotionTrackingFilter, SpringBasedLinearMotionFilter> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			ENGINE_FLOAT_MEMBER(SpringBasedLinearMotionFilter, 0, springConstant),
			ENGINE_FLOAT_MEMBER(SpringBasedLinearMotionFilter, 1, dampingConstant),
			ENGINE_FLOAT_MEMBER(SpringBasedLinearMotionFilter, 2, maximumDistanceLag)
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x107FDD80
	content::MemberList* DampedAngularMotionTrackingFilter::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<MotionTrackingFilter>();
		static content::BaseClassCasterImpl<MotionTrackingFilter, DampedAngularMotionTrackingFilter> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			ENGINE_FLOAT_MEMBER(DampedAngularMotionTrackingFilter, 0, maximumAngularSpeed),
			ENGINE_FLOAT_MEMBER(DampedAngularMotionTrackingFilter, 1, maximumAngleLag)
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x107FDE50
	content::MemberList* SpringBasedAngularMotionFilter::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<MotionTrackingFilter>();
		static content::BaseClassCasterImpl<MotionTrackingFilter, SpringBasedAngularMotionFilter> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			ENGINE_FLOAT_MEMBER(SpringBasedAngularMotionFilter, 0, springConstant),
			ENGINE_FLOAT_MEMBER(SpringBasedAngularMotionFilter, 1, dampingConstant),
			ENGINE_FLOAT_MEMBER(SpringBasedAngularMotionFilter, 2, maximumAngleLag)
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x107FDF50
	void MotionState::UpdateLinearVelocity(const math::Matrix& target, float invDt)
	{
		math::Vector velocity(linearVelocity.x, linearVelocity.y, linearVelocity.z);
		ComputeLinearVelocity(transform, target, math::kZeroVector, invDt, velocity);
		linearAcceleration.Sub(velocity, linearVelocity);
		linearAcceleration.Scale(invDt);
		linearVelocity.x = velocity.x;
		linearVelocity.y = velocity.y;
		linearVelocity.z = velocity.z;
	}

	// FUNCTION: ENGINE 0x107FE020
	void MotionState::UpdateAngularVelocity(const math::Matrix& target, float invDt)
	{
		math::Vector velocity(angularVelocity.x, angularVelocity.y, angularVelocity.z);
		ComputeAngularVelocity(transform, target, invDt, velocity);
		angularAcceleration.Sub(velocity, angularVelocity);
		angularAcceleration.Scale(invDt);
		angularVelocity.x = velocity.x;
		angularVelocity.y = velocity.y;
		angularVelocity.z = velocity.z;
	}

	// FUNCTION: ENGINE 0x107FE0F0
	void GetRotationDelta(const math::Matrix& from, const math::Matrix& to, math::Vector& axis, float& angle)
	{
		math::Matrix inverse;
		inverse = from;
		inverse.InvertOrthonormal();
		math::Matrix delta;
		delta.Multiply(inverse, to);
		delta.ToAxisAngle(axis, angle);
		if (angle > 3.14159274f)
		{
			angle = 6.28318548f - angle;
			math::Vector negated(-axis.x, -axis.y, -axis.z);
			axis.x = negated.x;
			axis.y = negated.y;
			axis.z = negated.z;
		}
	}

	// FUNCTION: ENGINE 0x107FE190
	MotionState::MotionState()
		: transform(math::Matrix::IDENTITY), linearVelocity(0.0f, 0.0f, 0.0f), linearAcceleration(0.0f, 0.0f, 0.0f),
		angularVelocity(0.0f, 0.0f, 0.0f), angularAcceleration(0.0f, 0.0f, 0.0f)
	{
		unknown70 = 0.0f;
	}

	// Kept copies: the filters' destructors and scalar deleting destructors, the base class casters and the member
	// meta types of the reflected members
	// FUNCTION: ENGINE 0x107FCA40
	// FUNCTION: ENGINE 0x107FCA80
	// FUNCTION: ENGINE 0x107FCAC0
	// FUNCTION: ENGINE 0x107FCC40
	// FUNCTION: ENGINE 0x107FCC50
	// FUNCTION: ENGINE 0x107FCED0
	// FUNCTION: ENGINE 0x107FD320
	// FUNCTION: ENGINE 0x107FD560
	// FUNCTION: ENGINE 0x107FCAD0
	// FUNCTION: ENGINE 0x107FCAE0
	// FUNCTION: ENGINE 0x107FCB10
	// FUNCTION: ENGINE 0x107FCB20
	// FUNCTION: ENGINE 0x107FCB50
	// FUNCTION: ENGINE 0x107FCB60
	// FUNCTION: ENGINE 0x107FCB90
	// FUNCTION: ENGINE 0x107FCBA0
	// FUNCTION: ENGINE 0x107FCBD0
	// FUNCTION: ENGINE 0x107FCBE0
	// FUNCTION: ENGINE 0x107FD8D0
	// FUNCTION: ENGINE 0x107FD910
	// FUNCTION: ENGINE 0x107FD950
	// FUNCTION: ENGINE 0x107FD990
	// FUNCTION: ENGINE 0x107FD9D0
	// FUNCTION: ENGINE 0x107FDA10
	// FUNCTION: ENGINE 0x107FDA50
	// FUNCTION: ENGINE 0x107FDA90
	// FUNCTION: ENGINE 0x107FDAD0
	// FUNCTION: ENGINE 0x107FDB10
}
