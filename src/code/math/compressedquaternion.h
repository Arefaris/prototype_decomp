// math::CompressedQuaternion6 and math::CompressedQuaternion8 (RTTI names of the key types of the compressed
// quaternion channels): a unit quaternion stored as its x, y, z components in 16 bits (six bytes) or 8 bits (three
// bytes) each, scaled by a factor kept in the data section; w is recovered from the unit length. The member and
// scale names are guesses.
#ifndef MATH_COMPRESSEDQUATERNION_H
#define MATH_COMPRESSEDQUATERNION_H

#include "code/math/quaternion.h"

namespace math
{
	class CompressedQuaternion6
	{
	public:
		// 0x111BB9BC: 1 / 32767
		static float sScale;

		// 0x106E3E10 (the copy kept in the animation unit)
		Quaternion ToQuaternion() const;

		short x;
		short y;
		short z;
	};

	class CompressedQuaternion8
	{
	public:
		// 0x111BB9C8: 1 / 127
		static float sScale;

		// 0x106E3F50 (the copy kept in the animation unit)
		Quaternion ToQuaternion() const;

		signed char x;
		signed char y;
		signed char z;
	};
}

#endif
