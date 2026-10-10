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
		// Sets the translation row
		void SetTranslation(const Vector& v);
		// Sets the upper 3x3 to a scale (leaving translation and the last column)
		void Scale(float sx, float sy, float sz);
		void Scale(float s);
		// Transposes the whole 4x4 / only the upper 3x3, in place
		void Transpose();
		void Transpose3x3();
		// Sets this matrix to the transpose of src (src must not be this matrix)
		void Transpose(const Matrix& src);
		// Inverts a rotation-plus-translation matrix in place: transposed 3x3, translation rotated back and negated
		void InvertOrthonormal();
		// Multiplies the upper 3x3 by s
		void Scale3x3(float s);
		// this = a * s, element-wise
		void Multiply(const Matrix& a, float s);
		// this += other, all 16 elements / only the upper 3x3
		void Add(const Matrix& other);
		void Add3x3(const Matrix& other);
		// this -= other, all 16 elements / only the upper 3x3
		void Subtract(const Matrix& other);
		void Subtract3x3(const Matrix& other);
		// The outer product a * b^T in the upper 3x3, zeros elsewhere (m[3][3] too)
		void OuterProduct(const Vector& a, const Vector& b);
		// Rotation matrix about a unit axis by angle radians (identity rotation when |angle| <= EPSILON_SMALL)
		void RotationAxisAngle(const Vector& axis, float angle);
		// Rotation matrix about a unit axis from the angle's cosine and sine; the axis is normalised if it is not
		void FromAxisCosSin(const Vector& axis, float c, float s);
		// this *= s, all 16 elements
		void Multiply(float s);
		// Left-handed off-centre perspective projection (Direct3D PerspectiveOffCenterLH layout)
		void PerspectiveOffCenter(float left, float right, float bottom, float top, float nearZ, float farZ);
		// Right-handed perspective projection (Direct3D PerspectiveFovRH layout: w = -z, z in [0, 1])
		void PerspectiveFovRH(float fov, float aspect, float nearZ, float farZ);
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
