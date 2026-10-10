// math::Vector4: a Vector with w. Deriving from Vector is what the binary shows: its methods pass *this to
// Matrix::Rotate(const Vector&, Vector&) unchanged. Class and method names are guesses.
#ifndef MATH_VECTOR4_H
#define MATH_VECTOR4_H

#include "code/math/vector.h"

namespace math
{
	class Matrix;

	class Vector4 : public Vector
	{
	public:
		float w;

		Vector4()
		{
		}
		Vector4(float newX, float newY, float newZ, float newW)
		{
			x = newX;
			y = newY;
			z = newZ;
			w = newW;
		}

		// Full 4x4 transform (Matrix::Transform(const Vector4&, Vector4&)), in place or from v
		void Transform(const Matrix& m);
		void Transform(const Vector4& v, const Matrix& m);
		// x, y, z as a direction through the 3x3; w unchanged
		void Rotate(const Matrix& m);
		// Packs x, y, z as 10-bit signed fractions of 511 and w as 2 bits (bits 30-31)
		unsigned int Pack() const;
		void Unpack(unsigned int packed);
		// Nonzero when every component is within tolerance of other's
		int IsClose(const Vector4& other, float tolerance) const;
	};
}

#endif
