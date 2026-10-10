#include <math.h>

#include "code/math/mathconstants.h"
#include "code/math/matrix.h"
#include "code/math/symmetricmatrix.h"

namespace math
{
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
