// math::Matrix: 4x4 floats, rows of 16 bytes. The class name is a guess (the engine names math::Vector, Plane,
// AABB, Sphere, OBB, Colour; no matrix name survives in the strings).
#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#include "code/math/vector.h"

namespace math
{
	class Quaternion;
	class Vector4;

	class Matrix
	{
	public:
		float m[4][4];

		// The identity matrix, a constant in the engine's data (0x111BB9E0)
		static const Matrix IDENTITY;

		// Member-wise copy; the engine keeps this out of line (0x100600B0, outside matrix.cpp's code)
		Matrix& operator=(const Matrix& other);
		// *this = IDENTITY
		void Identity();

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
		// Copies the translation row into out (inlined by the engine, seen in Plane::Transform; name guessed)
		void GetTranslation(Vector& out) const
		{
			out.x = m[3][0];
			out.y = m[3][1];
			out.z = m[3][2];
		}
		// Sets the upper 3x3 to a scale (leaving translation and the last column)
		void Scale(float sx, float sy, float sz);
		void Scale(float s);
		// Transposes the whole 4x4 / only the upper 3x3, in place
		void Transpose();
		void Transpose3x3();
		// Sets this matrix to the transpose of src (src must not be this matrix)
		void Transpose(const Matrix& src);
		// The transposed upper 3x3 of src into this one; the rest unchanged
		void Transpose3x3(const Matrix& src);
		// The rotation of q (Quaternion::ToMatrix)
		void FromQuaternion(const Quaternion& q);
		// Inverts a rotation-plus-translation matrix in place: transposed 3x3, translation rotated back and negated
		void InvertOrthonormal();
		// Multiplies the upper 3x3 by s
		void Scale3x3(float s);
		// this = a * s, element-wise
		void Multiply(const Matrix& a, float s);
		// this = a * b (0x107D2C00, not reconstructed yet)
		void Multiply(const Matrix& a, const Matrix& b);
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
		// True when the sum of squares of all 16 elements is below tolerance squared
		bool IsZero(float tolerance) const;
		// this = a + b / a - b, all 16 elements
		void Add(const Matrix& a, const Matrix& b);
		void Subtract(const Matrix& a, const Matrix& b);
		// Rotation by the vector's length about its direction (through RotationAxisAngle with the negated angle)
		void RotateByVector(const Vector& rotation);
		// Exact element-wise equality of all 16 elements
		bool operator==(const Matrix& other) const;
		// this *= s, all 16 elements
		void Multiply(float s);
		// Left-handed off-centre perspective projection (Direct3D PerspectiveOffCenterLH layout)
		void PerspectiveOffCenter(float left, float right, float bottom, float top, float nearZ, float farZ);
		// Left-handed perspective projection (Direct3D PerspectiveFovLH layout) over an identity matrix
		void PerspectiveFovLH(float fov, float aspect, float nearZ, float farZ);
		// Orthographic projections (Direct3D OrthoLH / OrthoRH / OrthoOffCenterLH / OrthoOffCenterRH layouts)
		void OrthoLH(float width, float height, float nearZ, float farZ);
		void OrthoRH(float width, float height, float nearZ, float farZ);
		void OrthoOffCenterLH(float left, float right, float bottom, float top, float nearZ, float farZ);
		void OrthoOffCenterRH(float left, float right, float bottom, float top, float nearZ, float farZ);
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
		// out = v times the full 4x4 (0x107CF990, not reconstructed yet)
		void Transform(const Vector4& v, Vector4& out) const;
		// Transform for count Vector4s from in to out
		void Transform(int count, const Vector4* in, Vector4* out) const;

		// Vector4 wrappers (vector4.cpp); names guessed
		void Reset();
		void SetTranslation(const Vector4& v);
		void SetTranslation(float x, float y, float z);
		void SetPosition(const Vector4& v);
		void SetPosition(float x, float y, float z);
		// Fills row i of the upper 3x3 with v's i-th component
		void SetRows(const Vector4& v);
		void SetScale(const Vector4& s);
		void SetScale(float x, float y, float z);
		void SetScale(float s);
		// out.xyz = v.xyz as a point through this matrix, out.w = v.w
		void TransformPoint(const Vector4& v, Vector4& out) const;
		Matrix& GetMatrix();
	};
}

#endif
