// The velocity helpers the motion tracking filters use, as compiled into the physics library's neighbourhood
// (0x10661CB0 - 0x106628D0; no assert path, file name guessed).
#include "code/engine/motiontrackingfilter.h"
#include "code/math/mathutils.h"
#include <math.h>

namespace engine
{
	// Whether two vectors differ by at most the tolerance in every component (name guessed)
	inline int IsEqual(const math::Vector& a, const math::Vector& b, float tolerance)
	{
		if (!math::IsEqual(a.x, b.x, tolerance) || !math::IsEqual(a.y, b.y, tolerance) ||
			!math::IsEqual(a.z, b.z, tolerance))
		{
			return 0;
		}
		return 1;
	}

	// The rotation from one transform to another as an axis and an angle up to pi (a copy of the filters' own helper)
	void ComputeRotationDelta(const math::Matrix& from, const math::Matrix& to, math::Vector& axis, float& angle);

	// FUNCTION: ENGINE 0x10661CB0
	// EQUIVALENT: the engine keeps the flag in eax (mov eax, 1 / xor eax, eax, then test al, al and sete al) where ours
	// keeps it in a byte register and copies the answer through dl; the same comparisons in the same order, 88.4 %
	bool ComputeLinearVelocity(const math::Matrix& from, const math::Matrix& to, const math::Vector& point, float invDt,
		math::Vector& velocity)
	{
		math::Vector start;
		math::Vector end;
		from.Transform(point, start);
		to.Transform(point, end);
		end.Sub(end, start);
		end.Scale(invDt);
		int same = IsEqual(velocity, end, 0.001f);
		velocity.x = end.x;
		velocity.y = end.y;
		velocity.z = end.z;
		return same == 0;
	}

	// FUNCTION: ENGINE 0x10661D80
	void ComputeRotationDelta(const math::Matrix& from, const math::Matrix& to, math::Vector& axis, float& angle)
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
		axis.Normalize();
	}

	// FUNCTION: ENGINE 0x10662810
	// EQUIVALENT: the same difference in the flag's registers as ComputeLinearVelocity, 85.5 %
	bool ComputeAngularVelocity(const math::Matrix& from, const math::Matrix& to, float invDt, math::Vector& velocity)
	{
		math::Vector axis;
		float angle;
		ComputeRotationDelta(from, to, axis, angle);
		angle *= invDt;
		math::Vector target(axis.x * angle, axis.y * angle, axis.z * angle);
		int same = IsEqual(velocity, target, 0.01f);
		velocity.x = target.x;
		velocity.y = target.y;
		velocity.z = target.z;
		return same == 0;
	}

	// FUNCTION: ENGINE 0x106628D0
	// EQUIVALENT: shrink-wrap: the engine saves esi / edi only behind the early exit and ends in two exits, 72.4 %
	bool ComputeVelocities(const math::Matrix& from, const math::Matrix& to, const math::Vector& point, float dt,
		math::Vector* linearVelocity, math::Vector* angularVelocity)
	{
		bool changed = false;
		if (dt > 0.00001f)
		{
			float invDt = 1.0f / dt;
			if (linearVelocity != 0)
			{
				if (ComputeLinearVelocity(from, to, point, invDt, *linearVelocity))
				{
					changed = true;
				}
			}
			if (angularVelocity != 0)
			{
				if (ComputeAngularVelocity(from, to, invDt, *angularVelocity))
				{
					return true;
				}
			}
		}
		return changed;
	}
}
