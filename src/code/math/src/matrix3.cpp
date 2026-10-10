#include "code/math/matrix.h"
#include "code/math/matrix3.h"

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
}
