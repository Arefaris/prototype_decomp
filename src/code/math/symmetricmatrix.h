// math::SymmetricMatrix: six floats of a symmetric 3x3 matrix. The class and file name come from the assert path
// "..\..\..\code\math\src\symmetricmatrix.cpp" and its format string "xx=%f, yy=%f, zz=%f, xy=%f, xz=%f, yz=%f",
// which also fixes the member order. Method names are guesses.
#ifndef MATH_SYMMETRICMATRIX_H
#define MATH_SYMMETRICMATRIX_H

namespace math
{
	class Matrix;
	class Vector;

	class SymmetricMatrix
	{
	public:
		float xx;
		float yy;
		float zz;
		float xy;
		float xz;
		float yz;

		// Writes the 3x3 block of a Matrix and clears its translation
		void CopyTo(Matrix& out) const;
		// Nonzero when every element is within EPSILON_SMALL of zero
		int IsZero() const;
		void GetDiagonal(float& x, float& y, float& z) const;
	};
}

#endif
