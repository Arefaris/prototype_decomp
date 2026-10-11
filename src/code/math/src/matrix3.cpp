#include "code/math/matrix.h"
#include "code/math/matrix3.h"
#include "code/math/vector.h"

namespace math
{
	// FUNCTION: ENGINE 0x107D3D90
	void Matrix3::Identity()
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
	}

	// FUNCTION: ENGINE 0x107D3CF0
	void Matrix3::CopyTo(Matrix& out) const
	{
		for (int i = 3; i--; )
		{
			for (int j = 3; j--; )
			{
				out.m[i][j] = m[i][j];
			}
		}
	}

	// FUNCTION: ENGINE 0x107D3D40
	void Matrix3::CopyFrom(const Matrix& in)
	{
		for (int i = 3; i--; )
		{
			for (int j = 3; j--; )
			{
				m[i][j] = in.m[i][j];
			}
		}
	}

	// The two transforms compute all three results before storing them (out may be v): an inline Set
	// FUNCTION: ENGINE 0x107D3DD0
	void Matrix3::Transform(const Vector& v, Vector& out) const
	{
		out.Set(v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0], v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1],
			v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2]);
	}

	// FUNCTION: ENGINE 0x107D3E60
	void Matrix3::TransformTransposed(const Vector& v, Vector& out) const
	{
		out.Set(m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z, m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
	}
}
