// math::Matrix: 4x4 floats, rows of 16 bytes. The class name is a guess (the engine names math::Vector, Plane,
// AABB, Sphere, OBB, Colour; no matrix name survives in the strings).
#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

namespace math
{
	class Vector;

	class Matrix
	{
	public:
		float m[4][4];

		// Resets the upper 3x3 (rotation) to identity, leaving the translation row and the last column; name guessed
		void IdentityRotation();
		// Zeroes the translation row (m[3][0..2])
		void ClearTranslation();
		// Sets the last column to (0, 0, 0, 1)
		void ClearProjection();
		// Sets the upper 3x3 to a rotation about X / Y / Z by angle radians, leaving translation and the last column
		void RotationX(float angle);
		void RotationY(float angle);
		void RotationZ(float angle);
		// out = v as a point through this matrix (row vector times the 3x3, plus the translation row)
		void Transform(const Vector& v, Vector& out) const;
		// out = v as a direction (row vector times the 3x3)
		void Rotate(const Vector& v, Vector& out) const;
		// out = v times the transposed 3x3 (the inverse rotation of an orthonormal matrix)
		void RotateInverse(const Vector& v, Vector& out) const;
		// Transform for count points from in to out
		void Transform(int count, const Vector* in, Vector* out) const;
	};
}

#endif
