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

		SymmetricMatrix()
		{
		}
		// Elements in row-major order of the upper triangle (the same order Set takes)
		SymmetricMatrix(float xx, float xy, float xz, float yy, float yz, float zz);
		void Set(float xx, float xy, float xz, float yy, float yz, float zz);
		// The upper triangle of m's 3x3 block
		void CopyFrom(const Matrix& m);
		// out = identity with this matrix as its 3x3 block
		void ToMatrix(Matrix& out) const;
		// this += other / this = a + b
		void Add(const SymmetricMatrix& other);
		void Add(const SymmetricMatrix& a, const SymmetricMatrix& b);
		// this *= s / this = a * s
		void Multiply(float s);
		void Multiply(const SymmetricMatrix& a, float s);
		// this = the upper triangle of a * b
		void Multiply(const SymmetricMatrix& a, const SymmetricMatrix& b);
		// Writes the 3x3 block of a Matrix and clears its translation
		void CopyTo(Matrix& out) const;
		// Nonzero when every element is within EPSILON_SMALL of zero
		int IsZero() const;
		// Reports the six elements through core::Report (debug output)
		void Print() const;
		void GetDiagonal(float& x, float& y, float& z) const;
	};
}

#endif
