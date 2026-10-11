#include <math.h>

#include "code/math/mathutils.h"
#include "code/math/spline.h"

namespace math
{
	// Not reconstructed yet: 0x107D5040 (BuildCatmullRom); GetParameter (0x107D6C40) is NONMATCHING
	// (docs/math_worklist.md).

	// GLOBAL: ENGINE 0x111BBAD0
	// The 15 basis matrices of SplineSegment::Build, by mode; defined by the engine's data (name guessed)
	extern const Matrix* const SPLINE_BASIS[15];

	// FUNCTION: ENGINE 0x107D5000
	SplineSegment::SplineSegment()
	{
		flag = false;
	}

	// FUNCTION: ENGINE 0x107D5010
	SplineSegment::SplineSegment(const SplineSegment& other)
	{
		coefficients = other.coefficients;
		derivative = other.derivative;
		flag = other.flag;
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

	// FUNCTION: ENGINE 0x107D4B40
	void SplineSegment::EvaluateSecondDerivative(Vector& out, float t) const
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
		Vector4 v(0.0f, 0.0f, 2.0f, u * 6.0f);
		v.Transform(coefficients);
		out.x = v.x;
		out.y = v.y;
		out.z = v.z;
	}

	// FUNCTION: ENGINE 0x107D4BC0
	// EQUIVALENT: the same additions and stores; the original loads the three addends and then the three targets of
	// each row into six registers before adding, and reloads every row from memory
	Vector& SplineSegment::Step(Vector& out)
	{
		Vector& r0 = *(Vector*)derivative.m[0];
		Vector& r1 = *(Vector*)derivative.m[1];
		Vector& r2 = *(Vector*)derivative.m[2];
		Vector& r3 = *(Vector*)derivative.m[3];
		r0.Set(r0.x + r1.x, r0.y + r1.y, r0.z + r1.z);
		r1.Set(r1.x + r2.x, r1.y + r2.y, r1.z + r2.z);
		r2.Set(r2.x + r3.x, r2.y + r3.y, r2.z + r3.z);
		out.x = derivative.m[0][0];
		out.y = derivative.m[0][1];
		out.z = derivative.m[0][2];
		return out;
	}

	// FUNCTION: ENGINE 0x107D4C90
	Spline::~Spline()
	{
		delete keys;
		delete tangents;
		delete lengths;
	}

	// FUNCTION: ENGINE 0x107D4CC0
	void Spline::SetMode(int newMode)
	{
		mode = newMode;
		current = -1;
		delete lengths;
		lengths = 0;
		if (mode == 4 || mode == 9 || mode == 14)
		{
			if (tangents == 0 && count > 0)
			{
				tangents = new Vector4[count];
			}
		}
		else
		{
			delete tangents;
			tangents = 0;
		}
	}

	// FUNCTION: ENGINE 0x107D4D60
	void Spline::SetClosed(bool value)
	{
		if (value != closed)
		{
			if (lengths != 0)
			{
				float* resized;
				if (closed)
				{
					// Closed to open: three segments fewer
					resized = new float[count - 2];
					for (unsigned int i = 0; i < count - 3; i++)
					{
						resized[i] = lengths[i];
					}
					resized[count - 3] = -1.0f;
				}
				else
				{
					resized = new float[count + 1];
					unsigned int i;
					for (i = 0; i < count - 3; i++)
					{
						resized[i] = lengths[i];
					}
					for (i = count - 3; i < count + 1; i++)
					{
						resized[i] = -1.0f;
					}
				}
				delete lengths;
				lengths = resized;
			}
			closed = value;
		}
	}

	// FUNCTION: ENGINE 0x107D4EA0
	void Spline::SetKeyCount(unsigned int keyCount)
	{
		current = -1;
		if (count != keyCount)
		{
			delete keys;
			delete tangents;
			delete lengths;
			keys = 0;
			tangents = 0;
			lengths = 0;
			count = keyCount;
			if (keyCount > 0)
			{
				keys = new Vector4[keyCount];
				if (mode == 4 || mode == 9 || mode == 14)
				{
					tangents = new Vector4[count];
				}
			}
		}
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

	// Kochanek-Bartels key parameters as BuildHermite reads them through its tangent pointers (names guessed)
	struct SplineTCB
	{
		float tension;
		float continuity;
		float bias;
		bool adjust;
	};

	// FUNCTION: ENGINE 0x107D5240
	// EQUIVALENT: same operations in the same order (10.3 %, 1394 bytes against 1501); register and stack-slot
	// choices differ throughout. The Build overloads that call it still match with it compiled in the unit
	void SplineSegment::BuildHermite(const Vector4* k0, const Vector4* k1, const Vector4* k2, const Vector4* k3,
		const Vector4* t0, const Vector4* t1, Matrix& geometry) const
	{
		if (t0 == 0 || t1 == 0)
		{
			return;
		}
		const SplineTCB* a = (const SplineTCB*)t0;
		const SplineTCB* b = (const SplineTCB*)t1;
		float d0 = 1.0f;
		float d1 = 1.0f;
		float d2 = 1.0f;
		if (flag)
		{
			d0 = k1->w - k0->w;
			d1 = k2->w - k1->w;
			d2 = k3->w - k2->w;
			if (d0 <= 0.0f || d1 <= 0.0f || d2 <= 0.0f)
			{
				return;
			}
		}
		Vector s0;
		float inv = 1.0f / d0;
		s0.Set((k1->x - k0->x) * inv, (k1->y - k0->y) * inv, (k1->z - k0->z) * inv);
		Vector s1;
		inv = 1.0f / d1;
		s1.Set((k2->x - k1->x) * inv, (k2->y - k1->y) * inv, (k2->z - k1->z) * inv);
		Vector s2;
		inv = 1.0f / d2;
		s2.Set((k3->x - k2->x) * inv, (k3->y - k2->y) * inv, (k3->z - k2->z) * inv);
		// Outgoing tangent at k1 and incoming tangent at k2
		float ta = 1.0f - a->tension;
		float w1 = (1.0f - a->continuity) * (1.0f - a->bias) * ta * 0.5f;
		float w0 = (a->continuity + 1.0f) * (a->bias + 1.0f) * ta * 0.5f;
		Vector out;
		out.Set(w0 * s0.x + w1 * s1.x, s0.y * w0 + s1.y * w1, s0.z * w0 + s1.z * w1);
		float tb = 1.0f - b->tension;
		float w2 = (b->continuity + 1.0f) * (1.0f - b->bias) * tb * 0.5f;
		float w3 = (b->bias + 1.0f) * (1.0f - b->continuity) * tb * 0.5f;
		Vector in;
		in.Set(s1.x * w3 + w2 * s2.x, s1.y * w3 + s2.y * w2, s1.z * w3 + s2.z * w2);
		// With the adjust flag and a continuity, each tangent is rescaled to the length of the other weighting
		if (a->continuity != 0.0f && a->adjust)
		{
			float wa = (a->continuity + 1.0f) * (1.0f - a->bias) * ta * 0.5f;
			float wb = (a->bias + 1.0f) * (1.0f - a->continuity) * ta * 0.5f;
			float x = wb * s0.x + wa * s1.x;
			float y = s0.y * wb + s1.y * wa;
			float z = s0.z * wb + s1.z * wa;
			float length = sqrtf((x * x + z * z) + y * y);
			float s = length * 2.0f / (sqrtf((out.x * out.x + out.z * out.z) + out.y * out.y) + length);
			out.x = s * out.x;
			out.y = out.y * s;
			out.z = out.z * s;
		}
		if (b->continuity != 0.0f && b->adjust)
		{
			float wc = (1.0f - b->continuity) * (1.0f - b->bias) * tb * 0.5f;
			float wd = (b->continuity + 1.0f) * (b->bias + 1.0f) * tb * 0.5f;
			float x = wd * s1.x + wc * s2.x;
			float y = s1.y * wd + s2.y * wc;
			float z = s1.z * wd + s2.z * wc;
			float length = sqrtf((x * x + z * z) + y * y);
			float s = length * 2.0f / (sqrtf((in.x * in.x + in.z * in.z) + in.y * in.y) + length);
			in.x = s * in.x;
			in.y = in.y * s;
			in.z = in.z * s;
		}
		geometry.m[0][0] = k1->x;
		geometry.m[0][1] = k1->y;
		geometry.m[0][2] = k1->z;
		geometry.m[0][3] = k1->w;
		geometry.m[1][0] = out.x * d1;
		geometry.m[1][1] = out.y * d1;
		geometry.m[1][2] = out.z * d1;
		geometry.m[2][0] = k2->x;
		geometry.m[2][1] = k2->y;
		geometry.m[2][2] = k2->z;
		geometry.m[2][3] = k2->w;
		geometry.m[3][0] = in.x * d1;
		geometry.m[3][1] = in.y * d1;
		geometry.m[3][2] = in.z * d1;
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

	// FUNCTION: ENGINE 0x107D6480
	void SplineSegment::Build(int mode, const Matrix& keys, const Vector4* t0, const Vector4* t1)
	{
		Matrix geometry;
		switch (mode)
		{
		case 0:
		case 1:
		case 2:
		case 5:
		case 6:
		case 7:
		case 10:
		case 11:
		case 12:
			coefficients.Multiply(*SPLINE_BASIS[mode], keys);
			break;
		case 3:
		case 8:
		case 13:
			BuildCatmullRom((const Vector4*)keys.m[0], (const Vector4*)keys.m[1], (const Vector4*)keys.m[2],
				(const Vector4*)keys.m[3], geometry);
			coefficients.Multiply(*SPLINE_BASIS[mode], geometry);
			break;
		case 4:
		case 9:
		case 14:
			BuildHermite((const Vector4*)keys.m[0], (const Vector4*)keys.m[1], (const Vector4*)keys.m[2],
				(const Vector4*)keys.m[3], t0, t1, geometry);
			coefficients.Multiply(*SPLINE_BASIS[mode], geometry);
			break;
		}
	}

	// FUNCTION: ENGINE 0x107D6540
	void Spline::SetKey(int index, const Vector& key)
	{
		Vector4& k = keys[index];
		k.x = key.x;
		k.y = key.y;
		k.z = key.z;
		k.w = 1.0f;
		current = -1;
		if (lengths != 0)
		{
			InvalidateLengths(index);
		}
	}

	// FUNCTION: ENGINE 0x107D6630
	bool Spline::SelectSegment(float t)
	{
		int index = (int)t;
		if (index > (int)count - 4)
		{
			index = (int)count - 4;
		}
		if (index == current)
		{
			return false;
		}
		unsigned int n = count;
		const Vector4* k0 = &keys[index % n];
		const Vector4* k1 = &keys[(index + 1) % n];
		const Vector4* k2 = &keys[(index + 2) % n];
		const Vector4* k3 = &keys[(index + 3) % n];
		const Vector4* t0 = 0;
		const Vector4* t1 = 0;
		if (tangents != 0)
		{
			t0 = &tangents[(index + 1) % n];
			t1 = &tangents[(index + 2) % n];
		}
		segment.Build(mode, k0, k1, k2, k3, t0, t1);
		current = index;
		return true;
	}

	// FUNCTION: ENGINE 0x107D6F10
	Vector& Spline::Evaluate(Vector& out, unsigned int key)
	{
		Evaluate(out, (float)key);
		return out;
	}

	// FUNCTION: ENGINE 0x107D5FE0
	void SplineSegment::Build(int mode, const Vector* k0, const Vector* k1, const Vector* k2, const Vector* k3,
		const Vector4* t0, const Vector4* t1)
	{
		Matrix geometry;
		switch (mode)
		{
		case 0:
		case 1:
		case 2:
		case 5:
		case 6:
		case 7:
		case 10:
		case 11:
		case 12:
			geometry.m[0][0] = k0->x;
			geometry.m[0][1] = k0->y;
			geometry.m[0][2] = k0->z;
			geometry.m[0][3] = 1.0f;
			geometry.m[1][0] = k1->x;
			geometry.m[1][1] = k1->y;
			geometry.m[1][2] = k1->z;
			geometry.m[1][3] = 1.0f;
			geometry.m[2][0] = k2->x;
			geometry.m[2][1] = k2->y;
			geometry.m[2][2] = k2->z;
			geometry.m[2][3] = 1.0f;
			geometry.m[3][0] = k3->x;
			geometry.m[3][1] = k3->y;
			geometry.m[3][2] = k3->z;
			geometry.m[3][3] = 1.0f;
			coefficients.Multiply(*SPLINE_BASIS[mode], geometry);
			break;
		case 3:
		case 8:
		case 13:
		{
			Vector4 v0(k0->x, k0->y, k0->z, 1.0f);
			Vector4 v1(k1->x, k1->y, k1->z, 1.0f);
			Vector4 v2(k2->x, k2->y, k2->z, 1.0f);
			Vector4 v3(k3->x, k3->y, k3->z, 1.0f);
			BuildCatmullRom(&v0, &v1, &v2, &v3, geometry);
			coefficients.Multiply(*SPLINE_BASIS[mode], geometry);
			break;
		}
		case 4:
		case 9:
		case 14:
		{
			Vector4 v0(k0->x, k0->y, k0->z, 1.0f);
			Vector4 v1(k1->x, k1->y, k1->z, 1.0f);
			Vector4 v2(k2->x, k2->y, k2->z, 1.0f);
			Vector4 v3(k3->x, k3->y, k3->z, 1.0f);
			BuildHermite(&v0, &v1, &v2, &v3, t0, t1, geometry);
			coefficients.Multiply(*SPLINE_BASIS[mode], geometry);
			break;
		}
		}
	}

	// FUNCTION: ENGINE 0x107D6300
	void SplineSegment::Build(int mode, const Vector4* k0, const Vector4* k1, const Vector4* k2, const Vector4* k3,
		const Vector4* t0, const Vector4* t1)
	{
		// The multiply sits in every case: the original duplicates it for the plain-key case and merges the other two
		Matrix geometry;
		switch (mode)
		{
		case 0:
		case 1:
		case 2:
		case 5:
		case 6:
		case 7:
		case 10:
		case 11:
		case 12:
			geometry.m[0][0] = k0->x;
			geometry.m[0][1] = k0->y;
			geometry.m[0][2] = k0->z;
			geometry.m[0][3] = k0->w;
			geometry.m[1][0] = k1->x;
			geometry.m[1][1] = k1->y;
			geometry.m[1][2] = k1->z;
			geometry.m[1][3] = k1->w;
			geometry.m[2][0] = k2->x;
			geometry.m[2][1] = k2->y;
			geometry.m[2][2] = k2->z;
			geometry.m[2][3] = k2->w;
			geometry.m[3][0] = k3->x;
			geometry.m[3][1] = k3->y;
			geometry.m[3][2] = k3->z;
			geometry.m[3][3] = k3->w;
			coefficients.Multiply(*SPLINE_BASIS[mode], geometry);
			break;
		case 3:
		case 8:
		case 13:
			BuildCatmullRom(k0, k1, k2, k3, geometry);
			coefficients.Multiply(*SPLINE_BASIS[mode], geometry);
			break;
		case 4:
		case 9:
		case 14:
			BuildHermite(k0, k1, k2, k3, t0, t1, geometry);
			coefficients.Multiply(*SPLINE_BASIS[mode], geometry);
			break;
		}
	}

	// GLOBAL: ENGINE 0x10E67D88
	// The five Gauss-Legendre nodes and weights, defined by the engine's data (names guessed)
	extern const float GAUSS_NODES[5];
	// GLOBAL: ENGINE 0x10E67D74
	extern const float GAUSS_WEIGHTS[5];

	// FUNCTION: ENGINE 0x107D5F30
	// |derivative| at t. A static helper of the unit: the compiler gives it its own register convention (segment in
	// ecx, the caller pops t), which is what the original has; noinline keeps it out of line as in the original
	static __declspec(noinline) float DerivativeLength(const SplineSegment* segment, float t)
	{
		Vector d;
		segment->EvaluateDerivative(d, t);
		return sqrtf(d.z * d.z + d.y * d.y + d.x * d.x);
	}

	// FUNCTION: ENGINE 0x107D5F60
	// Arc length over [0, t] by 5-point Gauss-Legendre quadrature (t arrives in xmm0, the segment in edi, the result
	// leaves in xmm0: the compiler's convention for this static)
	static __declspec(noinline) float ArcLength(const SplineSegment* segment, float t)
	{
		float scale = (t - 0.0f) * 0.5f;
		float offset = (t + 0.0f) * 0.5f;
		float sum = 0.0f;
		for (int i = 0; i < 5; i++)
		{
			sum += DerivativeLength(segment, GAUSS_NODES[i] * scale + offset) * GAUSS_WEIGHTS[i];
		}
		return sum * scale;
	}

	// FUNCTION: ENGINE 0x107D6940
	float Spline::GetSegmentLength(unsigned int index)
	{
		unsigned int n = GetSegmentCount();
		if (lengths != 0)
		{
			float cached = lengths[index];
			if (cached >= 0.0f)
			{
				return cached;
			}
		}
		if (lengths == 0)
		{
			unsigned int size = n + 1;
			lengths = new float[size];
			for (unsigned int i = 0; i < size; i++)
			{
				lengths[i] = -1.0f;
			}
		}
		SelectSegment((float)index);
		lengths[index] = ArcLength(&segment, 1.0f);
		return lengths[index];
	}

	// FUNCTION: ENGINE 0x107D6A50
	float Spline::GetTotalLength()
	{
		unsigned int n = GetSegmentCount();
		if (lengths != 0 && lengths[n] >= 0.0f)
		{
			return lengths[n];
		}
		if (lengths == 0)
		{
			unsigned int size = n + 1;
			lengths = new float[size];
			for (unsigned int i = 0; i < size; i++)
			{
				lengths[i] = -1.0f;
			}
		}
		float sum = 0.0f;
		for (unsigned int i = 0; i < n; i++)
		{
			sum += GetSegmentLength(i);
		}
		lengths[n] = sum;
		return sum;
	}

	// FUNCTION: ENGINE 0x107D6B60
	float Spline::GetLength(float t)
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
		float sum = 0.0f;
		unsigned int count = (unsigned int)u;
		for (unsigned int i = 0; i < count; i++)
		{
			sum += GetSegmentLength(i);
		}
		float start = (float)count;
		SelectSegment(start);
		return ArcLength(&segment, u - start) + sum;
	}

	// FUNCTION: ENGINE 0x107D6C40
	// NONMATCHING: the search loop, the Select clamps and the Newton step match; the original converts the segment
	// start to SSE through memory and computes end and the first t with SSE, where we get one x87 expression, and
	// the stack slots and the spills in the loop follow from that (22 %)
#ifdef NONMATCHING
	float Spline::GetParameter(float length)
	{
		if (length < 0.0f)
		{
			length = 0.0f;
		}
		if (length > GetTotalLength())
		{
			length = GetTotalLength();
		}
		// Caches every segment length
		GetTotalLength();
		float sum = 0.0f;
		unsigned int index = 0;
		unsigned int n = GetSegmentCount();
		for (; index < n; index++)
		{
			sum += lengths[index];
			if (sum >= length)
			{
				break;
			}
		}
		float segmentLength = GetSegmentLength(index);
		float start = (float)index;
		float end = start + 1.0f;
		float t = (length - sum + segmentLength) / segmentLength + start;
		SelectSegment(start);
		// Newton iterations on GetLength(t) = length within the segment
		for (unsigned int i = 0; i < 32; i++)
		{
			t = Select(t - start, t, start);
			t = Select(t - end, end, t);
			float error = GetLength(t) - length;
			if (fabsf(error) <= 1e-5f)
			{
				return t;
			}
			Vector derivative;
			segment.EvaluateDerivative(derivative, t - start);
			float speed = sqrtf(derivative.z * derivative.z + derivative.y * derivative.y + derivative.x * derivative.x);
			if (speed != 0.0f)
			{
				t -= error / speed;
			}
			else
			{
				t -= error;
			}
		}
		t = Select(t - start, t, start);
		t = Select(t - end, end, t);
		return t;
	}
#endif

	// FUNCTION: ENGINE 0x107D5820
	void SplineSegment::BeginStepping(Vector& out, int steps)
	{
		// derivative = D(h) * coefficients, D the forward-difference matrix of step h: rows 1, (h, h^2, h^3),
		// (2h^2, 6h^3), (6h^3) on and above the diagonal
		float h = 1.0f / (float)(unsigned int)steps;
		Matrix fd;
		fd.m[0][0] = 1.0f;
		fd.m[0][1] = 0.0f;
		fd.m[0][2] = 0.0f;
		fd.m[0][3] = 0.0f;
		fd.m[1][0] = 0.0f;
		fd.m[1][1] = h;
		fd.m[1][2] = h * h;
		fd.m[1][3] = h * h * h;
		fd.m[2][0] = 0.0f;
		fd.m[2][1] = 0.0f;
		fd.m[2][2] = h * h * 2.0f;
		fd.m[2][3] = h * h * h * 6.0f;
		fd.m[3][0] = 0.0f;
		fd.m[3][1] = 0.0f;
		fd.m[3][2] = 0.0f;
		fd.m[3][3] = h * h * h * 6.0f;
		Matrix& d = derivative;
		d.Multiply(fd, coefficients);
		out.x = d.m[0][0];
		out.y = d.m[0][1];
		out.z = d.m[0][2];
	}

	// FUNCTION: ENGINE 0x107D5900
	Spline::Spline(unsigned int keyCount, int splineMode, bool isClosed)
	{
		closed = isClosed;
		current = -1;
		flag = false;
		mode = splineMode;
		count = keyCount;
		keys = 0;
		tangents = 0;
		lengths = 0;
		step = 0;
		stepsPerSegment = 0;
		if (keyCount > 0)
		{
			keys = new Vector4[keyCount];
			if (mode == 4 || mode == 9 || mode == 14)
			{
				tangents = new Vector4[count];
			}
		}
	}

	// FUNCTION: ENGINE 0x107D59C0
	// EQUIVALENT: same code with ebx and ebp swapped: the original keeps the null in ebp and the loop counters in
	// ebx, and compares other.lengths with an immediate 0
	Spline::Spline(const Spline& other)
	{
		current = other.current;
		segment = other.segment;
		closed = other.closed;
		flag = other.flag;
		mode = other.mode;
		count = other.count;
		keys = 0;
		tangents = 0;
		lengths = 0;
		step = other.step;
		stepsPerSegment = other.stepsPerSegment;
		if (count > 0)
		{
			keys = new Vector4[count];
			for (unsigned int i = 0; i < count; i++)
			{
				const Vector4& source = other.keys[i];
				Vector4& key = keys[i];
				key.x = source.x;
				key.y = source.y;
				key.z = source.z;
				key.w = source.w;
			}
			if (mode == 4 || mode == 9 || mode == 14)
			{
				tangents = new Vector4[count];
				for (unsigned int i = 0; i < count; i++)
				{
					tangents[i] = other.tangents[i];
				}
			}
		}
		unsigned int n = GetSegmentCount() + 1;
		if (other.lengths != 0)
		{
			lengths = new float[n];
			for (unsigned int i = 0; i < n; i++)
			{
				lengths[i] = other.lengths[i];
			}
		}
	}

	// FUNCTION: ENGINE 0x107D5C00
	// EQUIVALENT: as the copy constructor (ebx / ebp swapped)
	Spline& Spline::operator=(const Spline& other)
	{
		current = other.current;
		segment = other.segment;
		closed = other.closed;
		flag = other.flag;
		mode = other.mode;
		count = other.count;
		delete keys;
		delete tangents;
		delete lengths;
		keys = 0;
		tangents = 0;
		lengths = 0;
		step = other.step;
		stepsPerSegment = other.stepsPerSegment;
		if (count > 0)
		{
			keys = new Vector4[count];
			for (unsigned int i = 0; i < count; i++)
			{
				const Vector4& source = other.keys[i];
				Vector4& key = keys[i];
				key.x = source.x;
				key.y = source.y;
				key.z = source.z;
				key.w = source.w;
			}
			if (mode == 4 || mode == 9 || mode == 14)
			{
				tangents = new Vector4[count];
				for (unsigned int i = 0; i < count; i++)
				{
					tangents[i] = other.tangents[i];
				}
			}
		}
		unsigned int n = GetSegmentCount() + 1;
		if (other.lengths != 0)
		{
			lengths = new float[n];
			for (unsigned int i = 0; i < n; i++)
			{
				lengths[i] = other.lengths[i];
			}
		}
		return *this;
	}

	// FUNCTION: ENGINE 0x107D6760
	Vector& Spline::StartStepping(Vector& out, int steps, unsigned int index)
	{
		if ((float)index > GetSegmentCountF())
		{
			index = (unsigned int)GetSegmentCountF();
		}
		step = index * steps;
		stepsPerSegment = steps;
		SelectSegment((float)index);
		segment.BeginStepping(out, stepsPerSegment);
		return out;
	}

	// FUNCTION: ENGINE 0x107D6810
	Vector& Spline::NextStep(Vector& out)
	{
		step++;
		float t = (float)step / (float)stepsPerSegment;
		if (closed && GetSegmentCountF() <= t)
		{
			step = 0;
			t = 0.0f;
		}
		else if (t < 0.0f)
		{
			t = 0.0f;
		}
		if (t > GetSegmentCountF())
		{
			t = GetSegmentCountF();
		}
		if (SelectSegment(t))
		{
			// A new segment: start it and catch up to the current step
			Vector position;
			segment.BeginStepping(position, stepsPerSegment);
			float x, y, z;
			int i = step % stepsPerSegment;
			if (i > 0)
			{
				do
				{
					const Vector& next = segment.Step(position);
					x = next.x;
					y = next.y;
					z = next.z;
				}
				while (--i > 0);
			}
			else
			{
				z = position.z;
				y = position.y;
				x = position.x;
			}
			out.x = x;
			out.y = y;
			out.z = z;
			return out;
		}
		segment.Step(out);
		return out;
	}
}
