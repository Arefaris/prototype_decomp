// math::Matrix3 (class name guessed): a 3x3 of floats, rows of 12 bytes, used as a temporary for the rotation
// part of math::Matrix (0x107D0E20 and neighbours build one and copy it into a Matrix).
#ifndef MATH_MATRIX3_H
#define MATH_MATRIX3_H

namespace math
{
	class Matrix;
	class Vector;

	class Matrix3
	{
	public:
		float m[3][3];

		void Identity();
		// Copies the nine elements into / out of the upper 3x3 of a Matrix
		void CopyTo(Matrix& out) const;
		void CopyFrom(const Matrix& in);
		// out = the row v times this matrix
		void Transform(const Vector& v, Vector& out) const;
		// out = this matrix times the column v (each row dotted with v); the inverse rotation of a row-vector
		// matrix, used to bring vectors into an OBB's axis space (name guessed)
		void TransformTransposed(const Vector& v, Vector& out) const;
	};
}

#endif
