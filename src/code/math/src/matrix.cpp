#include "code/math/mathconstants.h"
#include "code/math/matrix.h"
#include "code/math/matrix3.h"
#include "code/math/quaternion.h"
#include "code/math/sincos.h"
#include "code/math/vector.h"
#include "code/math/vector4.h"

#include <math.h>

namespace math
{
	// GLOBAL: ENGINE 0x111BB9E0
	// Matrix::IDENTITY is defined by the engine's data; declared in matrix.h so our code links against it
	// (the definition stays in the image until the data of the math module is reconstructed).
	// Matrix::operator= lives in another unit (matrix_assign.cpp): inside matrix.cpp the original compiler saw it as an
	// external call, which shows in the register use of Identity's callers.

	// FUNCTION: ENGINE 0x107CEAE0
	void Matrix::Identity()
	{
		*this = IDENTITY;
	}

	// FUNCTION: ENGINE 0x107CEAF0
	void Matrix::IdentityRotation()
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
	}

	// FUNCTION: ENGINE 0x107CEB30
	void Matrix::ClearTranslation()
	{
		m[3][2] = 0.0f;
		m[3][1] = 0.0f;
		m[3][0] = 0.0f;
	}

	// FUNCTION: ENGINE 0x107CEB50
	void Matrix::ClearProjection()
	{
		m[2][3] = 0.0f;
		m[1][3] = 0.0f;
		m[0][3] = 0.0f;
		m[3][3] = 1.0f;
	}

	// FUNCTION: ENGINE 0x107CEB70
	void Matrix::FromQuaternion(const Quaternion& q)
	{
		q.ToMatrix(*this);
	}

	// FUNCTION: ENGINE 0x107CEB80
	void Matrix::RotationX(float angle)
	{
		float s, c;
		SinCos(angle, &s, &c);
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = c; m[1][2] = s;
		m[2][0] = 0.0f; m[2][1] = -s; m[2][2] = c;
	}

	// FUNCTION: ENGINE 0x107CEC00
	void Matrix::RotationY(float angle)
	{
		float s, c;
		SinCos(angle, &s, &c);
		m[0][0] = c; m[0][1] = 0.0f; m[0][2] = -s;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
		m[2][0] = s; m[2][1] = 0.0f; m[2][2] = c;
	}

	// FUNCTION: ENGINE 0x107CEC80
	void Matrix::RotationZ(float angle)
	{
		float s, c;
		SinCos(angle, &s, &c);
		m[0][0] = c; m[0][1] = s; m[0][2] = 0.0f;
		m[1][0] = -s; m[1][1] = c; m[1][2] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
	}

	// FUNCTION: ENGINE 0x107CF1D0
	void Matrix::SetTranslation(const Vector& v)
	{
		m[3][0] = v.x;
		m[3][1] = v.y;
		m[3][2] = v.z;
	}

	// FUNCTION: ENGINE 0x107CF1F0
	void Matrix::Scale(float sx, float sy, float sz)
	{
		m[0][0] = sx; m[0][1] = 0.0f; m[0][2] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = sy; m[1][2] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = sz;
	}

	// FUNCTION: ENGINE 0x107CF240
	void Matrix::Scale(float s)
	{
		m[0][0] = s; m[0][1] = 0.0f; m[0][2] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = s; m[1][2] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = s;
	}

	// FUNCTION: ENGINE 0x107CF3D0
	void Matrix::Transpose()
	{
		float m01 = m[0][1];
		float m02 = m[0][2];
		float m03 = m[0][3];
		float m12 = m[1][2];
		float m13 = m[1][3];
		float m23 = m[2][3];
		m[0][1] = m[1][0];
		m[0][2] = m[2][0];
		m[0][3] = m[3][0];
		m[1][0] = m01;
		m[1][2] = m[2][1];
		m[2][0] = m02;
		m[2][1] = m12;
		m[1][3] = m[3][1];
		m[3][0] = m03;
		m[3][1] = m13;
		m[2][3] = m[3][2];
		m[3][2] = m23;
	}

	// FUNCTION: ENGINE 0x107CF440
	void Matrix::Transpose3x3()
	{
		float m01 = m[0][1];
		float m02 = m[0][2];
		float m12 = m[1][2];
		m[0][1] = m[1][0];
		m[0][2] = m[2][0];
		m[1][0] = m01;
		m[2][0] = m02;
		m[1][2] = m[2][1];
		m[2][1] = m12;
	}

	// FUNCTION: ENGINE 0x107CF480
	void Matrix::Transpose(const Matrix& src)
	{
		m[0][0] = src.m[0][0]; m[0][1] = src.m[1][0]; m[0][2] = src.m[2][0]; m[0][3] = src.m[3][0];
		m[1][0] = src.m[0][1]; m[1][1] = src.m[1][1]; m[1][2] = src.m[2][1]; m[1][3] = src.m[3][1];
		m[2][0] = src.m[0][2]; m[2][1] = src.m[1][2]; m[2][2] = src.m[2][2]; m[2][3] = src.m[3][2];
		m[3][0] = src.m[0][3]; m[3][1] = src.m[1][3]; m[3][2] = src.m[2][3]; m[3][3] = src.m[3][3];
	}

	// FUNCTION: ENGINE 0x107CF4F0
	void Matrix::Transpose3x3(const Matrix& src)
	{
		m[0][0] = src.m[0][0]; m[0][1] = src.m[1][0]; m[0][2] = src.m[2][0];
		m[1][0] = src.m[0][1]; m[1][1] = src.m[1][1]; m[1][2] = src.m[2][1];
		m[2][0] = src.m[0][2]; m[2][1] = src.m[1][2]; m[2][2] = src.m[2][2];
	}

	// FUNCTION: ENGINE 0x107CF530
	void Matrix::InvertOrthonormal()
	{
		Transpose3x3();
		float x = -m[3][0];
		float y = -m[3][1];
		float z = -m[3][2];
		m[3][0] = m[2][0] * z + m[1][0] * y + m[0][0] * x;
		m[3][1] = m[2][1] * z + m[1][1] * y + m[0][1] * x;
		m[3][2] = m[2][2] * z + m[1][2] * y + m[0][2] * x;
	}

	// FUNCTION: ENGINE 0x107CF8F0
	// EQUIVALENT: same operations in the same order; the original keeps v.y in xmm1 and v.z in xmm0, we get the reverse
	void Matrix::Transform(const Vector& v, Vector& out) const
	{
		float y = v.y;
		float z = v.z;
		float x = v.x;
		out.x = m[1][0] * y + m[2][0] * z + x * m[0][0] + m[3][0];
		out.y = m[0][1] * x + m[1][1] * y + m[2][1] * z + m[3][1];
		out.z = m[0][2] * x + m[1][2] * y + m[2][2] * z + m[3][2];
	}

	// FUNCTION: ENGINE 0x107CF990
	// EQUIVALENT: the same products and sums in the same order; the original keeps v.z, v.y, v.w in xmm1, xmm2,
	// xmm0 (we get xmm0, xmm1, xmm2) and multiplies a copy of x by m[0][0] from memory. Without the explicit
	// grouping the compiler moves the w product first. Transform(count, in, out) relies on it being compiled here
	void Matrix::Transform(const Vector4& v, Vector4& out) const
	{
		float z = v.z;
		float y = v.y;
		float w = v.w;
		float x = v.x;
		out.x = ((m[1][0] * y + m[2][0] * z) + m[3][0] * w) + x * m[0][0];
		out.y = ((m[0][1] * x + m[1][1] * y) + m[2][1] * z) + m[3][1] * w;
		out.z = ((m[0][2] * x + m[1][2] * y) + m[2][2] * z) + m[3][2] * w;
		out.w = ((m[0][3] * x + m[1][3] * y) + m[2][3] * z) + m[3][3] * w;
	}

	// FUNCTION: ENGINE 0x107CFA80
	// EQUIVALENT: as Transform, without the translation
	void Matrix::Rotate(const Vector& v, Vector& out) const
	{
		float y = v.y;
		float z = v.z;
		float x = v.x;
		out.x = m[1][0] * y + m[2][0] * z + x * m[0][0];
		out.y = m[0][1] * x + m[1][1] * y + m[2][1] * z;
		out.z = m[0][2] * x + m[1][2] * y + m[2][2] * z;
	}

	// FUNCTION: ENGINE 0x107CFB10
	// EQUIVALENT: as Rotate, with the transposed matrix
	void Matrix::RotateInverse(const Vector& v, Vector& out) const
	{
		float y = v.y;
		float z = v.z;
		float x = v.x;
		out.x = m[0][1] * y + m[0][2] * z + x * m[0][0];
		out.y = m[1][0] * x + m[1][1] * y + m[1][2] * z;
		out.z = m[2][0] * x + m[2][1] * y + m[2][2] * z;
	}

	// FUNCTION: ENGINE 0x107CFBA0
	void Matrix::Transform(int count, const Vector* in, Vector* out) const
	{
		for (int i = 0; i < count; i++)
		{
			Transform(*in, *out);
			in++;
			out++;
		}
	}

	// FUNCTION: ENGINE 0x107CFBD0
	void Matrix::Transform(int count, const Vector4* in, Vector4* out) const
	{
		for (int i = 0; i < count; i++)
		{
			Transform(*in, *out);
			in++;
			out++;
		}
	}

	// FUNCTION: ENGINE 0x107D0D90
	// EQUIVALENT: the same multiplications in the same order; the original loads m[0][0] before s (94.7 %)
	void Matrix::Scale3x3(float s)
	{
		m[0][0] *= s; m[0][1] *= s; m[0][2] *= s;
		m[1][0] *= s; m[1][1] *= s; m[1][2] *= s;
		m[2][0] *= s; m[2][1] *= s; m[2][2] *= s;
	}

	// FUNCTION: ENGINE 0x107CFC00
	void Matrix::PerspectiveFovLH(float fov, float aspect, float nearZ, float farZ)
	{
		float cot = 1.0f / tanf(fov * 0.5f);
		Identity();
		m[2][2] = farZ / (farZ - nearZ);
		m[3][2] = -(nearZ * farZ) / (farZ - nearZ);
		m[2][3] = 1.0f;
		m[3][3] = 0.0f;
		m[0][0] = cot / aspect;
		m[1][1] = cot;
	}

	// The projections below assign all 16 elements in memory order; that order (not the order of the
	// computations) is what reproduces the original's schedule
	// FUNCTION: ENGINE 0x107CFC80
	void Matrix::OrthoLH(float width, float height, float nearZ, float farZ)
	{
		m[0][0] = 2.0f / width; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 2.0f / height; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f / (farZ - nearZ); m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = nearZ / (nearZ - farZ); m[3][3] = 1.0f;
	}

	// FUNCTION: ENGINE 0x107CFD20
	void Matrix::OrthoRH(float width, float height, float nearZ, float farZ)
	{
		m[0][0] = 2.0f / width; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 2.0f / height; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f / (nearZ - farZ); m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = nearZ / (nearZ - farZ); m[3][3] = 1.0f;
	}

	// FUNCTION: ENGINE 0x107CFDB0
	void Matrix::OrthoOffCenterLH(float left, float right, float bottom, float top, float nearZ, float farZ)
	{
		m[0][0] = 2.0f / (right - left); m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 2.0f / (top - bottom); m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f / (farZ - nearZ); m[2][3] = 0.0f;
		m[3][0] = (left + right) / (left - right); m[3][1] = (bottom + top) / (bottom - top);
		m[3][2] = nearZ / (nearZ - farZ); m[3][3] = 1.0f;
	}

	// FUNCTION: ENGINE 0x107CFE90
	void Matrix::OrthoOffCenterRH(float left, float right, float bottom, float top, float nearZ, float farZ)
	{
		m[0][0] = 2.0f / (right - left); m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 2.0f / (top - bottom); m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f / (nearZ - farZ); m[2][3] = 0.0f;
		m[3][0] = (left + right) / (left - right); m[3][1] = (bottom + top) / (bottom - top);
		m[3][2] = nearZ / (nearZ - farZ); m[3][3] = 1.0f;
	}

	// FUNCTION: ENGINE 0x107D0300
	void Matrix::PerspectiveFovRH(float fov, float aspect, float nearZ, float farZ)
	{
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;
		m[1][0] = 0.0f;
		m[1][2] = 0.0f;
		m[2][2] = farZ / (nearZ - farZ);
		m[1][3] = 0.0f;
		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][3] = -1.0f;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = nearZ * farZ / (nearZ - farZ);
		m[3][3] = 0.0f;
		m[0][0] = (1.0f / tanf(fov * 0.5f)) / aspect;
		m[1][1] = 1.0f / tanf(fov * 0.5f);
	}

	// FUNCTION: ENGINE 0x107D0730
	bool Matrix::operator==(const Matrix& o) const
	{
		int equal = 1;
		equal &= m[0][0] == o.m[0][0]; equal &= m[0][1] == o.m[0][1]; equal &= m[0][2] == o.m[0][2]; equal &= m[0][3] == o.m[0][3];
		equal &= m[1][0] == o.m[1][0]; equal &= m[1][1] == o.m[1][1]; equal &= m[1][2] == o.m[1][2]; equal &= m[1][3] == o.m[1][3];
		equal &= m[2][0] == o.m[2][0]; equal &= m[2][1] == o.m[2][1]; equal &= m[2][2] == o.m[2][2]; equal &= m[2][3] == o.m[2][3];
		equal &= m[3][0] == o.m[3][0]; equal &= m[3][1] == o.m[3][1]; equal &= m[3][2] == o.m[3][2]; equal &= m[3][3] == o.m[3][3];
		return equal != 0;
	}

	// FUNCTION: ENGINE 0x107D08F0
	// EQUIVALENT: the original loads s after the first element of this; we load it first (one instruction)
	void Matrix::Multiply(float s)
	{
		m[0][0] *= s; m[0][1] *= s; m[0][2] *= s; m[0][3] *= s;
		m[1][0] *= s; m[1][1] *= s; m[1][2] *= s; m[1][3] *= s;
		m[2][0] *= s; m[2][1] *= s; m[2][2] *= s; m[2][3] *= s;
		m[3][0] *= s; m[3][1] *= s; m[3][2] *= s; m[3][3] *= s;
	}

	// FUNCTION: ENGINE 0x107D09E0
	void Matrix::Multiply(const Matrix& a, float s)
	{
		for (int i = 0; i < 4; i++)
		{
			m[i][0] = a.m[i][0] * s; m[i][1] = a.m[i][1] * s; m[i][2] = a.m[i][2] * s; m[i][3] = a.m[i][3] * s;
		}
	}

	// FUNCTION: ENGINE 0x107D0AD0
	void Matrix::Add(const Matrix& o)
	{
		for (int i = 0; i < 4; i++)
		{
			m[i][0] += o.m[i][0]; m[i][1] += o.m[i][1]; m[i][2] += o.m[i][2]; m[i][3] += o.m[i][3];
		}
	}

	// FUNCTION: ENGINE 0x107D0BD0
	// EQUIVALENT: the original loads the address of o after the first element of this; we hoist it (one instruction)
	void Matrix::Subtract(const Matrix& o)
	{
		for (int i = 0; i < 4; i++)
		{
			m[i][0] -= o.m[i][0]; m[i][1] -= o.m[i][1]; m[i][2] -= o.m[i][2]; m[i][3] -= o.m[i][3];
		}
	}

	// FUNCTION: ENGINE 0x107D0CD0
	void Matrix::OuterProduct(const Vector& a, const Vector& b)
	{
		m[0][0] = a.x * b.x; m[0][1] = b.y * a.x; m[0][2] = a.x * b.z; m[0][3] = 0.0f;
		m[1][0] = b.x * a.y; m[1][1] = b.y * a.y; m[1][2] = a.y * b.z; m[1][3] = 0.0f;
		m[2][0] = a.z * b.x; m[2][1] = a.z * b.y; m[2][2] = a.z * b.z; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 0.0f;
	}

	// FUNCTION: ENGINE 0x107D0ED0
	void Matrix::Add3x3(const Matrix& o)
	{
		m[0][0] += o.m[0][0]; m[0][1] += o.m[0][1]; m[0][2] += o.m[0][2];
		m[1][0] += o.m[1][0]; m[1][1] += o.m[1][1]; m[1][2] += o.m[1][2];
		m[2][0] += o.m[2][0]; m[2][1] += o.m[2][1]; m[2][2] += o.m[2][2];
	}

	// FUNCTION: ENGINE 0x107D1010
	// EQUIVALENT: as Subtract, the address load of o one instruction later in the original
	void Matrix::Subtract3x3(const Matrix& o)
	{
		m[0][0] -= o.m[0][0]; m[0][1] -= o.m[0][1]; m[0][2] -= o.m[0][2];
		m[1][0] -= o.m[1][0]; m[1][1] -= o.m[1][1]; m[1][2] -= o.m[1][2];
		m[2][0] -= o.m[2][0]; m[2][1] -= o.m[2][1]; m[2][2] -= o.m[2][2];
	}

	// FUNCTION: ENGINE 0x107D0E20
	void Matrix::Scale3x3(const Matrix& a, float s)
	{
		Matrix3 t;
		t.m[0][0] = a.m[0][0] * s;
		t.m[0][1] = a.m[0][1] * s;
		t.m[0][2] = a.m[0][2] * s;
		t.m[1][0] = a.m[1][0] * s;
		t.m[1][1] = a.m[1][1] * s;
		t.m[1][2] = a.m[1][2] * s;
		t.m[2][0] = a.m[2][0] * s;
		t.m[2][1] = a.m[2][1] * s;
		t.m[2][2] = a.m[2][2] * s;
		t.CopyTo(*this);
	}

	// FUNCTION: ENGINE 0x107D0F60
	void Matrix::Add3x3(const Matrix& a, const Matrix& b)
	{
		Matrix3 t;
		t.m[0][0] = a.m[0][0] + b.m[0][0];
		t.m[0][1] = a.m[0][1] + b.m[0][1];
		t.m[0][2] = a.m[0][2] + b.m[0][2];
		t.m[1][0] = a.m[1][0] + b.m[1][0];
		t.m[1][1] = a.m[1][1] + b.m[1][1];
		t.m[1][2] = a.m[1][2] + b.m[1][2];
		t.m[2][0] = a.m[2][0] + b.m[2][0];
		t.m[2][1] = a.m[2][1] + b.m[2][1];
		t.m[2][2] = a.m[2][2] + b.m[2][2];
		t.CopyTo(*this);
	}

	// FUNCTION: ENGINE 0x107D10A0
	void Matrix::Subtract3x3(const Matrix& a, const Matrix& b)
	{
		Matrix3 t;
		t.m[0][0] = a.m[0][0] - b.m[0][0];
		t.m[0][1] = a.m[0][1] - b.m[0][1];
		t.m[0][2] = a.m[0][2] - b.m[0][2];
		t.m[1][0] = a.m[1][0] - b.m[1][0];
		t.m[1][1] = a.m[1][1] - b.m[1][1];
		t.m[1][2] = a.m[1][2] - b.m[1][2];
		t.m[2][0] = a.m[2][0] - b.m[2][0];
		t.m[2][1] = a.m[2][1] - b.m[2][1];
		t.m[2][2] = a.m[2][2] - b.m[2][2];
		t.CopyTo(*this);
	}

	// FUNCTION: ENGINE 0x107D1150
	void Matrix::Multiply3x3(const Matrix& a, const Matrix& b)
	{
		Matrix3 t;
		t.m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0];
		t.m[0][1] = a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1];
		t.m[0][2] = a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2];
		t.m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0];
		t.m[1][1] = a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1];
		t.m[1][2] = a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2];
		t.m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0];
		t.m[2][1] = a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1];
		t.m[2][2] = a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2];
		t.CopyTo(*this);
	}

	// FUNCTION: ENGINE 0x107D1320
	void Matrix::MultiplyTranspose3x3(const Matrix& a, const Matrix& b)
	{
		Matrix3 t;
		t.m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[0][1] + a.m[0][2] * b.m[0][2];
		t.m[0][1] = a.m[0][0] * b.m[1][0] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[1][2];
		t.m[0][2] = a.m[0][0] * b.m[2][0] + a.m[0][1] * b.m[2][1] + a.m[0][2] * b.m[2][2];
		t.m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[0][1] + a.m[1][2] * b.m[0][2];
		t.m[1][1] = a.m[1][0] * b.m[1][0] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[1][2];
		t.m[1][2] = a.m[1][0] * b.m[2][0] + a.m[1][1] * b.m[2][1] + a.m[1][2] * b.m[2][2];
		t.m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[0][1] + a.m[2][2] * b.m[0][2];
		t.m[2][1] = a.m[2][0] * b.m[1][0] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[1][2];
		t.m[2][2] = a.m[2][0] * b.m[2][0] + a.m[2][1] * b.m[2][1] + a.m[2][2] * b.m[2][2];
		t.CopyTo(*this);
	}

	// FUNCTION: ENGINE 0x107D1A20
	void Matrix::RotationAxisAngle(const Vector& axis, float angle)
	{
		if (fabsf(angle) <= EPSILON_SMALL)
		{
			IdentityRotation();
			return;
		}
		float s, c;
		SinCos(-angle, &s, &c);
		FromAxisCosSin(axis, c, s);
	}

	// FUNCTION: ENGINE 0x107D14F0
	void Matrix::PerspectiveOffCenter(float left, float right, float bottom, float top, float nearZ, float farZ)
	{
		m[0][0] = (nearZ * 2.0f) / (right - left);
		m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f; m[1][0] = 0.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[1][1] = (nearZ * 2.0f) / (top - bottom);
		m[2][0] = (left + right) / (left - right);
		m[2][1] = (bottom + top) / (bottom - top);
		m[2][2] = farZ / (farZ - nearZ);
		m[3][0] = 0.0f; m[3][1] = 0.0f;
		m[2][3] = 1.0f;
		m[3][2] = (nearZ * farZ) / (nearZ - farZ);
		m[3][3] = 0.0f;
	}

	// FUNCTION: ENGINE 0x107D17F0
	bool Matrix::IsZero(float tolerance) const
	{
		float d = m[0][0] * m[0][0] + m[0][1] * m[0][1] + m[0][2] * m[0][2] + m[0][3] * m[0][3]
			+ m[1][0] * m[1][0] + m[1][1] * m[1][1] + m[1][2] * m[1][2] + m[1][3] * m[1][3]
			+ m[2][0] * m[2][0] + m[2][1] * m[2][1] + m[2][2] * m[2][2] + m[2][3] * m[2][3]
			+ m[3][0] * m[3][0] + m[3][1] * m[3][1] + m[3][2] * m[3][2] + m[3][3] * m[3][3];
		return d < tolerance * tolerance;
	}

	// FUNCTION: ENGINE 0x107D29C0
	void Matrix::Add(const Matrix& a, const Matrix& b)
	{
		Matrix t;
		for (int i = 0; i < 4; i++)
		{
			t.m[i][0] = a.m[i][0] + b.m[i][0]; t.m[i][1] = a.m[i][1] + b.m[i][1]; t.m[i][2] = a.m[i][2] + b.m[i][2]; t.m[i][3] = a.m[i][3] + b.m[i][3];
		}
		*this = t;
	}

	// FUNCTION: ENGINE 0x107D2AE0
	void Matrix::Subtract(const Matrix& a, const Matrix& b)
	{
		Matrix t;
		for (int i = 0; i < 4; i++)
		{
			t.m[i][0] = a.m[i][0] - b.m[i][0]; t.m[i][1] = a.m[i][1] - b.m[i][1]; t.m[i][2] = a.m[i][2] - b.m[i][2]; t.m[i][3] = a.m[i][3] - b.m[i][3];
		}
		*this = t;
	}

	// FUNCTION: ENGINE 0x107D2E70
	void Matrix::RotateByVector(const Vector& rotation)
	{
		Vector axis;
		axis.x = rotation.x;
		axis.y = rotation.y;
		axis.z = rotation.z;
		float angle = axis.Normalize();
		RotationAxisAngle(axis, -angle);
	}
}
