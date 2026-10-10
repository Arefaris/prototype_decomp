// math::Quaternion (class name guessed): x, y, z, w with w the scalar part, as the axis-angle conversion at
// 0x107CE310 reads it.
#ifndef MATH_QUATERNION_H
#define MATH_QUATERNION_H

namespace math
{
	class Vector;

	class Quaternion
	{
	public:
		float x;
		float y;
		float z;
		float w;

		// Scales to unit length without a check for zero length
		void NormalizeFast();
		// Nonzero when the squared length is within EPSILON_SMALL of one
		int IsNormalized() const;
		// Rotation by angle radians about a unit axis
		void FromAxisAngle(float angle, const Vector& axis);
		// Rotation by angle radians about X / Y / Z
		void RotationX(float angle);
		void RotationY(float angle);
		void RotationZ(float angle);
		// Negates this quaternion if it lies in the other hemisphere than q, so blending takes the short way
		void MakeClosest(const Quaternion& q);
	};

	// out = a * b (out may be a or b); a free function in the original (cdecl, three pointers)
	void Multiply(Quaternion& out, const Quaternion& a, const Quaternion& b);
}

#endif
