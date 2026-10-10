#include "code/math/matrix.h"
#include "code/math/sincos.h"

namespace math
{
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
}
