// Matrix::operator= is out of line in the original at 0x100600B0, far from matrix.cpp's code (0x107CEAE0-0x107D2EC0):
// its own translation unit, or a header-defined member the linker placed elsewhere. It must stay outside matrix.cpp
// so that matrix.cpp's callers of Identity() see an external call, as the original compiler did.
#include "code/math/matrix.h"

namespace math
{
	// FUNCTION: ENGINE 0x100600B0
	Matrix& Matrix::operator=(const Matrix& o)
	{
		m[0][0] = o.m[0][0]; m[0][1] = o.m[0][1]; m[0][2] = o.m[0][2]; m[0][3] = o.m[0][3];
		m[1][0] = o.m[1][0]; m[1][1] = o.m[1][1]; m[1][2] = o.m[1][2]; m[1][3] = o.m[1][3];
		m[2][0] = o.m[2][0]; m[2][1] = o.m[2][1]; m[2][2] = o.m[2][2]; m[2][3] = o.m[2][3];
		m[3][0] = o.m[3][0]; m[3][1] = o.m[3][1]; m[3][2] = o.m[3][2]; m[3][3] = o.m[3][3];
		return *this;
	}
}
