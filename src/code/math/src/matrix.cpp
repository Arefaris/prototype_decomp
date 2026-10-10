#include "code/math/matrix.h"

namespace math
{
	// FUNCTION: ENGINE 0x107CEAF0
	void Matrix::IdentityRotation()
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
	}
}
