#include <math.h>

#include "code/math/mathutils.h"
#include "code/math/spline.h"

namespace math
{
	// Not reconstructed yet: 0x107D4B40 .. 0x107D4EA0, 0x107D5010 .. 0x107D5C00 (segment construction and the
	// evaluators), 0x107D5F30 DerivativeLength and 0x107D5F60 (arc length by a 5-point Gauss-Legendre sum, both
	// compiled with a register calling convention), 0x107D5FE0 .. 0x107D6540, 0x107D6630 SelectSegment and
	// 0x107D6760 onwards (docs/math_worklist.md).

	// FUNCTION: ENGINE 0x107D5000
	SplineSegment::SplineSegment()
	{
		flag = false;
	}

	// FUNCTION: ENGINE 0x107D49F0
	SplineSegment& SplineSegment::operator=(const SplineSegment& other)
	{
		coefficients = other.coefficients;
		derivative = other.derivative;
		flag = other.flag;
		return *this;
	}

	// FUNCTION: ENGINE 0x107D4A20
	void SplineSegment::SetFlag(bool value)
	{
		flag = value;
	}

	// FUNCTION: ENGINE 0x107D4A30
	void SplineSegment::Evaluate(Vector& out, float t) const
	{
		float u = t;
		if (u < 0.0f)
		{
			u = 0.0f;
		}
		else if (u > 1.0f)
		{
			u = 1.0f;
		}
		Vector4 v(1.0f, u, u * u, u * u * u);
		v.Transform(coefficients);
		out.x = v.x;
		out.y = v.y;
		out.z = v.z;
	}

	// FUNCTION: ENGINE 0x107D4AB0
	void SplineSegment::EvaluateDerivative(Vector& out, float t) const
	{
		float u = t;
		if (u < 0.0f)
		{
			u = 0.0f;
		}
		else if (u > 1.0f)
		{
			u = 1.0f;
		}
		Vector4 v(0.0f, 1.0f, u * 2.0f, u * u * 3.0f);
		v.Transform(coefficients);
		out.x = v.x;
		out.y = v.y;
		out.z = v.z;
	}

	// FUNCTION: ENGINE 0x107D4C90
	Spline::~Spline()
	{
		delete keys;
		delete tangents;
		delete lengths;
	}

	// FUNCTION: ENGINE 0x107D4F60
	void Spline::SetFlag(bool value)
	{
		flag = value;
		segment.SetFlag(value);
	}

	// FUNCTION: ENGINE 0x107D4F80
	float Spline::GetSegmentCountF() const
	{
		unsigned int n = count;
		if (!closed)
		{
			n -= 3;
		}
		return (float)n;
	}

	// FUNCTION: ENGINE 0x107D4FB0
	unsigned int Spline::GetSegmentCount() const
	{
		unsigned int n = count;
		if (n < 4)
		{
			if (!closed)
			{
				return 0;
			}
		}
		else if (!closed)
		{
			return n - 3;
		}
		return n;
	}

	// FUNCTION: ENGINE 0x107D4FE0
	Vector4* Spline::GetKey(int index)
	{
		return keys + index;
	}

	// FUNCTION: ENGINE 0x107D5E70
	void Spline::InvalidateLengths(unsigned int index)
	{
		if (lengths != 0)
		{
			int first = index - 3;
			unsigned int start = first > 0 ? first : 0;
			unsigned int end = Min(GetSegmentCount(), index);
			for (unsigned int i = start; i < end; i++)
			{
				lengths[i] = -1.0f;
			}
			lengths[GetSegmentCount()] = -1.0f;
		}
	}

	// FUNCTION: ENGINE 0x107D6590
	void Spline::SetKey(int index, const Vector4& key)
	{
		// Member-wise (the original copies the four floats through the x87 unit; SetTangent copies the struct)
		Vector4& k = keys[index];
		k.x = key.x;
		k.y = key.y;
		k.z = key.z;
		k.w = key.w;
		current = -1;
		if (lengths != 0)
		{
			InvalidateLengths(index);
		}
	}

	// FUNCTION: ENGINE 0x107D65E0
	void Spline::SetTangent(int index, const Vector4& tangent)
	{
		if (tangents != 0)
		{
			tangents[index] = tangent;
			current = -1;
			if (lengths != 0)
			{
				InvalidateLengths(index);
			}
		}
	}

	// FUNCTION: ENGINE 0x107D66F0
	Vector& Spline::Evaluate(Vector& out, float t)
	{
		float u = t;
		if (u < 0.0f)
		{
			u = 0.0f;
		}
		if (u > GetSegmentCountF())
		{
			u = GetSegmentCountF();
		}
		SelectSegment(u);
		segment.Evaluate(out, u - (float)current);
		return out;
	}
}
