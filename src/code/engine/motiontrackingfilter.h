// engine::MotionTrackingFilter and its reflected filters (RTTI and reflection names): each frame a filter moves a
// tracked transform (MotionState) towards a target transform, limiting the linear or the angular motion and
// keeping the state's velocities and accelerations. Unit 0x107FC800 - 0x107FE2A6 (no assert path; directory and file
// name are guesses). The reflected member names are original; MotionState, TimeStep and the method names are guesses.
#ifndef ENGINE_MOTIONTRACKINGFILTER_H
#define ENGINE_MOTIONTRACKINGFILTER_H

#include "code/content/metatype.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"

namespace engine
{
	// The velocity of point (local to the transforms) moving from from to to in a step of 1 / invDt into velocity;
	// true when it changed by more than 0.001 (0x10661CB0, another unit; name guessed)
	bool ComputeLinearVelocity(const math::Matrix& from, const math::Matrix& to, const math::Vector& point, float invDt,
		math::Vector& velocity);
	// The angular velocity (axis times angle per second) of the rotation from from to to; true when it changed by more
	// than 0.01 (0x10662810, another unit; name guessed)
	bool ComputeAngularVelocity(const math::Matrix& from, const math::Matrix& to, float invDt, math::Vector& velocity);

	// Both velocities of a point moving from one transform to another in a step of dt, each when its pointer is not
	// null; true when either changed (0x106628D0, another unit; name guessed)
	bool ComputeVelocities(const math::Matrix& from, const math::Matrix& to, const math::Vector& point, float dt,
		math::Vector* linearVelocity, math::Vector* angularVelocity);

	// A tracked transform with its velocities and accelerations (0x74 bytes)
	struct MotionState
	{
		MotionState();

		// Follows target's position / rotation, updating the linear / angular velocity and acceleration
		void UpdateLinearVelocity(const math::Matrix& target, float invDt);
		void UpdateAngularVelocity(const math::Matrix& target, float invDt);

		math::Matrix transform;
		math::Vector linearVelocity;
		math::Vector linearAcceleration;
		math::Vector angularVelocity;
		math::Vector angularAcceleration;
		float unknown70;
	};

	class MotionTrackingFilter
	{
	public:
		// The step of an update: its length and the reciprocal
		struct TimeStep
		{
			TimeStep(float newDt);

			float dt;
			float invDt;
		};

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		virtual ~MotionTrackingFilter()
		{
		}
		// Moves state towards target (the third argument is not used by the engine's filters)
		virtual void Update(const TimeStep& step, const math::Matrix& target, const void* unknown,
			MotionState& state) = 0;
	};

	// Follows the target exactly
	class RigidMotionTrackingFilter : public MotionTrackingFilter
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		virtual void Update(const TimeStep& step, const math::Matrix& target, const void* unknown, MotionState& state);
	};

	// Follows the target's position at most at maximumSpeed, never lagging more than maximumDistanceLag (when >= 0)
	class DampedLinearMotionTrackingFilter : public MotionTrackingFilter
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		DampedLinearMotionTrackingFilter();
		virtual ~DampedLinearMotionTrackingFilter()
		{
		}

		virtual void Update(const TimeStep& step, const math::Matrix& target, const void* unknown, MotionState& state);

		float maximumSpeed;
		float maximumDistanceLag;
	};

	// Follows the target's position on a damped spring, never lagging more than maximumDistanceLag
	class SpringBasedLinearMotionFilter : public MotionTrackingFilter
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		SpringBasedLinearMotionFilter();
		virtual ~SpringBasedLinearMotionFilter()
		{
		}

		virtual void Update(const TimeStep& step, const math::Matrix& target, const void* unknown, MotionState& state);

		float springConstant;
		float dampingConstant;
		float maximumDistanceLag;
	};

	// Follows the target's rotation at most at maximumAngularSpeed, never lagging more than maximumAngleLag (when >= 0)
	class DampedAngularMotionTrackingFilter : public MotionTrackingFilter
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		DampedAngularMotionTrackingFilter();
		virtual ~DampedAngularMotionTrackingFilter()
		{
		}

		virtual void Update(const TimeStep& step, const math::Matrix& target, const void* unknown, MotionState& state);

		float maximumAngularSpeed;
		float maximumAngleLag;
	};

	// Follows the target's rotation on a damped spring, never lagging more than maximumAngleLag
	class SpringBasedAngularMotionFilter : public MotionTrackingFilter
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		SpringBasedAngularMotionFilter();
		virtual ~SpringBasedAngularMotionFilter()
		{
		}

		virtual void Update(const TimeStep& step, const math::Matrix& target, const void* unknown, MotionState& state);

		float springConstant;
		float dampingConstant;
		float maximumAngleLag;
	};
}

#endif
