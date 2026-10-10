// math::Quaternion (class name guessed): x, y, z, w with w the scalar part, as the axis-angle conversion at
// 0x107CE310 reads it.
#ifndef MATH_QUATERNION_H
#define MATH_QUATERNION_H

namespace math
{
	class Quaternion
	{
	public:
		float x;
		float y;
		float z;
		float w;

		// Negates this quaternion if it lies in the other hemisphere than q, so blending takes the short way
		void MakeClosest(const Quaternion& q);
	};
}

#endif
