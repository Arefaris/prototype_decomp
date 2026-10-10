#include "code/math/matrix.h"
#include "code/math/sincos.h"
#include "code/math/vector.h"

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
}
