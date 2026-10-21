// The bounds of the vehicle graphs: see the header.
#include "code/engine/driving/boundedgraphs.h"
#include <math.h>

namespace engine
{
	namespace driving
	{
		// FUNCTION: ENGINE 0x1093CE40
		content::ClassInfo* BoundedSpeedGraphAttributes::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::driving::BoundedSpeedGraphAttributes";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x1093CE80
		content::ClassInfo* BoundedSymmetricSpeedGraphAttributes::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::driving::BoundedSymmetricSpeedGraphAttributes";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x1093CEC0
		BoundedSpeedGraphAttributes::BoundedSpeedGraphAttributes()
		{
			maxPositive = 1.0f;
			maxNegative = 1.0f;
		}

		// FUNCTION: ENGINE 0x1093CEE0
		float BoundedSpeedGraphAttributes::GetMaxPositiveKmh() const
		{
			return maxPositive * 3.6f;
		}

		// FUNCTION: ENGINE 0x1093CEF0
		float BoundedSpeedGraphAttributes::GetMaxNegativeKmh() const
		{
			return maxNegative * 3.6f;
		}

		// FUNCTION: ENGINE 0x1093CF00
		BoundedSymmetricSpeedGraphAttributes::BoundedSymmetricSpeedGraphAttributes()
		{
			maxSpeed = 1.0f;
		}

		// FUNCTION: ENGINE 0x1093CF10
		float BoundedSymmetricSpeedGraphAttributes::GetMaxKmh() const
		{
			return maxSpeed * 3.6f;
		}

		// FUNCTION: ENGINE 0x1093CF20
		void BoundedSpeedGraphAttributes::SetMaxPositiveKmh(float kmh)
		{
			float speed = gKmhToMetresPerSecond * kmh;
			if (!(speed > 0.01f))
			{
				speed = 0.01f;
			}
			maxPositive = speed;
		}

		// FUNCTION: ENGINE 0x1093CF50
		void BoundedSpeedGraphAttributes::SetMaxNegativeKmh(float kmh)
		{
			float speed = gKmhToMetresPerSecond * kmh;
			if (!(speed > 0.01f))
			{
				speed = 0.01f;
			}
			maxNegative = speed;
		}

		// FUNCTION: ENGINE 0x1093CF80
		void BoundedSymmetricSpeedGraphAttributes::SetMaxKmh(float kmh)
		{
			float speed = gKmhToMetresPerSecond * kmh;
			if (!(speed > 0.01f))
			{
				speed = 0.01f;
			}
			maxSpeed = speed;
		}

		// FUNCTION: ENGINE 0x1093D1A0
		content::MemberList* BoundedSpeedGraphAttributes::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetMemberMetaType<BoundedSpeedGraphAttributes, float, 0>(&BoundedSpeedGraphAttributes::GetMaxPositiveKmh,
					&BoundedSpeedGraphAttributes::SetMaxPositiveKmh, "p"), 0, "maxPositiveKmh" },
				{ content::GetMemberMetaType<BoundedSpeedGraphAttributes, float, 1>(&BoundedSpeedGraphAttributes::GetMaxNegativeKmh,
					&BoundedSpeedGraphAttributes::SetMaxNegativeKmh, "p"), 0, "maxNegativeKmh" }
			};
			sList.members = sMembers;
			sList.count = 2;
			return &sList;
		}

		// FUNCTION: ENGINE 0x1093D250
		content::MemberList* BoundedSymmetricSpeedGraphAttributes::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetMemberMetaType<BoundedSymmetricSpeedGraphAttributes, float, 0>(&BoundedSymmetricSpeedGraphAttributes::GetMaxKmh,
					&BoundedSymmetricSpeedGraphAttributes::SetMaxKmh, "p"), 0, "maxKmh" }
			};
			sList.members = sMembers;
			sList.count = 1;
			return &sList;
		}

		// FUNCTION: ENGINE 0x1093D2D0
		// NONMATCHING: the engine takes the limit's magnitude on the x87 stack, stores it back to the argument and does the division in SSE; ours does all of it on the x87 stack (38 %)
#ifdef NONMATCHING
		float NormalizeBounded(float value, float limit, float slope)
		{
			limit = fabsf(limit);
			if (value <= limit)
			{
				return value / limit;
			}
			return ((value - limit) / limit) * slope + 1.0f;
		}
#endif

		// FUNCTION: ENGINE 0x1093D330
		// NONMATCHING: same x87 / SSE split as 0x1093D2D0 (15 %)
#ifdef NONMATCHING
		float NormalizeBoundedSigned(float value, float positiveLimit, float negativeLimit, float slope)
		{
			positiveLimit = fabsf(positiveLimit);
			negativeLimit = fabsf(negativeLimit);
			if (value < 0.0f)
			{
				if (value < -negativeLimit)
				{
					return ((value + negativeLimit) / negativeLimit) * slope - 1.0f;
				}
			}
			else
			{
				negativeLimit = positiveLimit;
				if (positiveLimit < value)
				{
					return ((value - positiveLimit) / positiveLimit) * slope + 1.0f;
				}
			}
			return value / negativeLimit;
		}
#endif

		// FUNCTION: ENGINE 0x1093D3D0
		// NONMATCHING: same x87 / SSE split as 0x1093D2D0 (14 %)
#ifdef NONMATCHING
		float MoveTowardsBound(float value, float target, float stepIfFaster, float stepOtherwise, float scale)
		{
			float step = stepOtherwise;
			if (fabsf(target) < fabsf(value))
			{
				step = stepIfFaster;
			}
			step = step * scale;
			float delta = value - target;
			float lo = -step;
			if (!(delta - lo >= 0.0f))
			{
				delta = lo;
			}
			value = delta;
			if (delta - step >= 0.0f)
			{
				value = step;
			}
			return target + value;
		}
#endif

		// FUNCTION: ENGINE 0x1093D440
		// NONMATCHING: same x87 / SSE split as 0x1093D2D0, and the engine calls the clamp through its jump table (15 %)
#ifdef NONMATCHING
		float InterpolateGraph(float x, unsigned int count, const float* xs, const float* ys)
		{
			if (xs == 0 || ys == 0)
			{
				return 0.0f;
			}
			if (count == 0)
			{
				return 0.0f;
			}
			if (count == 1)
			{
				return ys[0];
			}
			if (count == 2)
			{
				float x0 = xs[0];
				float x1 = xs[1];
				float y0 = ys[0];
				float clamped = ClampFloat(x, x0, x1);
				return ((clamped - x0) * (ys[1] - y0)) / (x1 - x0) + y0;
			}
			float clamped = ClampFloat(x, xs[0], xs[count - 1]);
			unsigned int next = 1;
			if (1 < count)
			{
				while (xs[next] <= clamped)
				{
					next++;
					if (count <= next)
					{
						return ys[count - 1];
					}
				}
				int previous = next - 1;
				if (-1 < previous)
				{
					if (0.00001f < fabsf(xs[previous] - xs[next]))
					{
						return ((ys[next] - ys[previous]) * (clamped - xs[previous])) / (xs[next] - xs[previous]) + ys[previous];
					}
					return ys[next];
				}
			}
			return ys[count - 1];
		}
#endif

		// FUNCTION: ENGINE 0x1093D5F0
		content::ClassInfo* BoundedAngleGraphAttributes::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::driving::BoundedAngleGraphAttributes";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x1093D630
		content::ClassInfo* BoundedSymmetricAngleGraphAttributes::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::driving::BoundedSymmetricAngleGraphAttributes";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x1093D670
		BoundedAngleGraphAttributes::BoundedAngleGraphAttributes()
		{
			maxPositive = 1.0471976f;
			maxNegative = 1.0471976f;
		}

		// FUNCTION: ENGINE 0x1093D690
		float BoundedAngleGraphAttributes::GetMaxPositiveDegrees() const
		{
			return maxPositive * 57.295776f;
		}

		// FUNCTION: ENGINE 0x1093D6A0
		void BoundedAngleGraphAttributes::SetMaxPositiveDegrees(float degrees)
		{
			maxPositive = degrees * 0.017453292f;
		}

		// FUNCTION: ENGINE 0x1093D6C0
		float BoundedAngleGraphAttributes::GetMaxNegativeDegrees() const
		{
			return maxNegative * 57.295776f;
		}

		// FUNCTION: ENGINE 0x1093D6D0
		void BoundedAngleGraphAttributes::SetMaxNegativeDegrees(float degrees)
		{
			maxNegative = degrees * 0.017453292f;
		}

		// FUNCTION: ENGINE 0x1093D6F0
		BoundedSymmetricAngleGraphAttributes::BoundedSymmetricAngleGraphAttributes()
		{
			maxAngle = 1.0471976f;
		}

		// FUNCTION: ENGINE 0x1093D700
		float BoundedSymmetricAngleGraphAttributes::GetMaxDegrees() const
		{
			return maxAngle * 57.295776f;
		}

		// FUNCTION: ENGINE 0x1093D710
		void BoundedSymmetricAngleGraphAttributes::SetMaxDegrees(float degrees)
		{
			maxAngle = degrees * 0.017453292f;
		}

		// FUNCTION: ENGINE 0x1093D920
		content::MemberList* BoundedAngleGraphAttributes::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetMemberMetaType<BoundedAngleGraphAttributes, float, 0>(&BoundedAngleGraphAttributes::GetMaxPositiveDegrees,
					&BoundedAngleGraphAttributes::SetMaxPositiveDegrees, "p"), 0, "maxPositiveDegrees" },
				{ content::GetMemberMetaType<BoundedAngleGraphAttributes, float, 1>(&BoundedAngleGraphAttributes::GetMaxNegativeDegrees,
					&BoundedAngleGraphAttributes::SetMaxNegativeDegrees, "p"), 0, "maxNegativeDegrees" }
			};
			sList.members = sMembers;
			sList.count = 2;
			return &sList;
		}

		// FUNCTION: ENGINE 0x1093D9D0
		content::MemberList* BoundedSymmetricAngleGraphAttributes::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetMemberMetaType<BoundedSymmetricAngleGraphAttributes, float, 0>(&BoundedSymmetricAngleGraphAttributes::GetMaxDegrees,
					&BoundedSymmetricAngleGraphAttributes::SetMaxDegrees, "p"), 0, "maxDegrees" }
			};
			sList.members = sMembers;
			sList.count = 1;
			return &sList;
		}
	}
}
