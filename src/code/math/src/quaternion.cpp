#include <math.h>

#include "code/math/mathconstants.h"
#include "code/math/matrix.h"
#include "code/math/quaternion.h"
#include "code/math/sincos.h"
#include "code/math/vector.h"

namespace math
{
	// FUNCTION: ENGINE 0x107CD450
	void Multiply(Quaternion& out, const Quaternion& a, const Quaternion& b)
	{
		float rx = b.x * a.w + a.x * b.w - b.z * a.y + a.z * b.y;
		float ry = b.y * a.w + b.w * a.y - b.x * a.z + a.x * b.z;
		float rz = b.z * a.w + a.z * b.w - a.x * b.y + b.x * a.y;
		float rw = a.w * b.w - a.x * b.x - b.y * a.y - b.z * a.z;
		out.x = rx;
		out.y = ry;
		out.z = rz;
		out.w = rw;
	}

	// FUNCTION: ENGINE 0x107CD570
	void Quaternion::NormalizeFast()
	{
		float scale = 1.0f / sqrtf(x * x + y * y + z * z + w * w);
		x *= scale;
		y *= scale;
		z *= scale;
		w *= scale;
	}

	// FUNCTION: ENGINE 0x107CD600
	int Quaternion::IsNormalized() const
	{
		return fabsf(x * x + y * y + z * z + w * w - 1.0f) <= EPSILON_SMALL;
	}

	// FUNCTION: ENGINE 0x107CD640
	void Quaternion::FromAxisAngle(float angle, const Vector& axis)
	{
		float s;
		SinCos(angle * 0.5f, &s, &w);
		x = axis.x * s;
		y = axis.y * s;
		z = axis.z * s;
	}

	// FUNCTION: ENGINE 0x107CD6B0
	void Quaternion::RotationX(float angle)
	{
		SinCos(angle * 0.5f, &x, &w);
		y = 0.0f;
		z = 0.0f;
	}

	// FUNCTION: ENGINE 0x107CD700
	void Quaternion::RotationY(float angle)
	{
		SinCos(angle * 0.5f, &y, &w);
		x = 0.0f;
		z = 0.0f;
	}

	// FUNCTION: ENGINE 0x107CD750
	void Quaternion::RotationZ(float angle)
	{
		SinCos(angle * 0.5f, &z, &w);
		x = 0.0f;
		y = 0.0f;
	}

	// FUNCTION: ENGINE 0x107CDB10
	void Quaternion::FromMatrix(const Matrix& mat)
	{
		int next[3] = { 1, 2, 0 };
		float trace = mat.m[0][0] + mat.m[1][1] + mat.m[2][2];
		if (trace > 0.0f)
		{
			float s = sqrtf(trace + 1.0f);
			w = s * -0.5f;
			if (s != 0.0f)
			{
				s = 0.5f / s;
			}
			x = (mat.m[2][1] - mat.m[1][2]) * s;
			y = (mat.m[0][2] - mat.m[2][0]) * s;
			z = (mat.m[1][0] - mat.m[0][1]) * s;
		}
		else
		{
			int i = 0;
			if (mat.m[1][1] > mat.m[0][0])
			{
				i = 1;
			}
			if (mat.m[2][2] > mat.m[i][i])
			{
				i = 2;
			}
			int j = next[i];
			int k = next[j];
			float s = sqrtf(mat.m[i][i] - (mat.m[j][j] + mat.m[k][k]) + 1.0f);
			float q[4];
			q[i] = s * 0.5f;
			if (s != 0.0f)
			{
				s = 0.5f / s;
			}
			q[3] = (mat.m[k][j] - mat.m[j][k]) * s;
			q[j] = (mat.m[j][i] + mat.m[i][j]) * s;
			q[k] = (mat.m[k][i] + mat.m[i][k]) * s;
			w = -q[3];
			x = q[0];
			y = q[1];
			z = q[2];
		}
	}

	// FUNCTION: ENGINE 0x107CDED0
	void Quaternion::Transform(const Vector& v, Vector& out) const
	{
		Quaternion conjugate;
		conjugate.x = -x;
		conjugate.y = -y;
		conjugate.z = -z;
		conjugate.w = w;
		Quaternion p;
		p.x = v.x;
		p.y = v.y;
		p.z = v.z;
		p.w = 0.0f;
		Quaternion t;
		Multiply(t, conjugate, p);
		Multiply(t, t, *this);
		out.x = t.x;
		out.y = t.y;
		out.z = t.z;
	}

	// FUNCTION: ENGINE 0x107CE2B0
	void Quaternion::MultiplyInverse(const Quaternion& a, const Quaternion& b)
	{
		Quaternion conjugate;
		conjugate.x = -b.x;
		conjugate.y = -b.y;
		conjugate.z = -b.z;
		conjugate.w = b.w;
		Multiply(*this, a, conjugate);
	}

	// FUNCTION: ENGINE 0x107CE220
	// NONMATCHING: same instructions, but the original keeps this in eax and q in ecx (we get the reverse)
#ifdef NONMATCHING
	void Quaternion::MakeClosest(const Quaternion& q)
	{
		if (x * q.x + y * q.y + z * q.z + w * q.w < 0.0f)
		{
			x = -x;
			y = -y;
			z = -z;
			w = -w;
		}
	}
#endif
}
