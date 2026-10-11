#include <math.h>

#include "code/math/mathconstants.h"
#include "code/math/matrix.h"
#include "code/math/symmetricmatrix.h"

namespace math
{
	// FUNCTION: ENGINE 0x107D8E20
	SymmetricMatrix::SymmetricMatrix(float xx_, float xy_, float xz_, float yy_, float yz_, float zz_)
	{
		xx = xx_;
		xy = xy_;
		xz = xz_;
		yy = yy_;
		yz = yz_;
		zz = zz_;
	}

	// FUNCTION: ENGINE 0x107D8E70
	void SymmetricMatrix::Set(float xx_, float xy_, float xz_, float yy_, float yz_, float zz_)
	{
		xx = xx_;
		xy = xy_;
		xz = xz_;
		yy = yy_;
		yz = yz_;
		zz = zz_;
	}

	// FUNCTION: ENGINE 0x107D8EC0
	void SymmetricMatrix::CopyFrom(const Matrix& m)
	{
		xx = m.m[0][0];
		xy = m.m[0][1];
		xz = m.m[0][2];
		yy = m.m[1][1];
		yz = m.m[1][2];
		zz = m.m[2][2];
	}

	// FUNCTION: ENGINE 0x107D8EF0
	void SymmetricMatrix::ToMatrix(Matrix& out) const
	{
		out.Identity();
		out.m[0][0] = xx;
		out.m[0][1] = xy;
		out.m[1][0] = xy;
		out.m[0][2] = xz;
		out.m[2][0] = xz;
		out.m[1][1] = yy;
		out.m[1][2] = yz;
		out.m[2][1] = yz;
		out.m[2][2] = zz;
	}

	// FUNCTION: ENGINE 0x107D8F40
	void SymmetricMatrix::Add(const SymmetricMatrix& other)
	{
		xx += other.xx;
		xy += other.xy;
		xz += other.xz;
		yy += other.yy;
		yz += other.yz;
		zz += other.zz;
	}

	// FUNCTION: ENGINE 0x107D8FA0
	void SymmetricMatrix::Add(const SymmetricMatrix& a, const SymmetricMatrix& b)
	{
		// The sum is built in a temporary and copied as a whole (six dword moves in the original)
		SymmetricMatrix result;
		result.xx = a.xx + b.xx;
		result.xy = a.xy + b.xy;
		result.xz = a.xz + b.xz;
		result.yy = a.yy + b.yy;
		result.yz = a.yz + b.yz;
		result.zz = a.zz + b.zz;
		*this = result;
	}

	// FUNCTION: ENGINE 0x107D9040
	void SymmetricMatrix::Multiply(float s)
	{
		xx *= s;
		xy *= s;
		xz *= s;
		yy *= s;
		yz *= s;
		zz *= s;
	}

	// FUNCTION: ENGINE 0x107D90A0
	void SymmetricMatrix::Multiply(const SymmetricMatrix& a, float s)
	{
		xx = a.xx * s;
		xy = a.xy * s;
		xz = a.xz * s;
		yy = a.yy * s;
		yz = a.yz * s;
		zz = a.zz * s;
	}

	// FUNCTION: ENGINE 0x107D9100
	void SymmetricMatrix::Multiply(const SymmetricMatrix& a, const SymmetricMatrix& b)
	{
		// The product's upper triangle (a times b is symmetric when they commute), built in a temporary like Add
		SymmetricMatrix result;
		result.xx = a.xx * b.xx + a.xy * b.xy + a.xz * b.xz;
		result.xy = a.xx * b.xy + a.xy * b.yy + a.xz * b.yz;
		result.xz = a.xx * b.xz + a.xy * b.yz + a.xz * b.zz;
		result.yy = a.xy * b.xy + a.yy * b.yy + a.yz * b.yz;
		result.yz = a.xy * b.xz + a.yy * b.yz + a.yz * b.zz;
		result.zz = a.xz * b.xz + a.yz * b.yz + a.zz * b.zz;
		*this = result;
	}

	// FUNCTION: ENGINE 0x107D9240
	void SymmetricMatrix::CopyTo(Matrix& out) const
	{
		out.m[0][0] = xx;
		out.m[0][1] = xy;
		out.m[1][0] = xy;
		out.m[0][2] = xz;
		out.m[2][0] = xz;
		out.m[1][1] = yy;
		out.m[1][2] = yz;
		out.m[2][1] = yz;
		out.m[2][2] = zz;
		out.ClearTranslation();
	}

	// FUNCTION: ENGINE 0x107D9750
	int SymmetricMatrix::IsZero() const
	{
		return fabsf(xx) < EPSILON_SMALL && fabsf(yy) < EPSILON_SMALL && fabsf(zz) < EPSILON_SMALL
			&& fabsf(xy) < EPSILON_SMALL && fabsf(xz) < EPSILON_SMALL && fabsf(yz) < EPSILON_SMALL;
	}

	// FUNCTION: ENGINE 0x107D9A00
	void SymmetricMatrix::GetDiagonal(float& x, float& y, float& z) const
	{
		x = xx;
		y = yy;
		z = zz;
	}
}
