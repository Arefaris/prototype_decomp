// math::CompressedQuaternion8, 6, 4 and 3 (RTTI names of the key types of the compressed quaternion channels; the
// number is the size in bytes): a unit quaternion stored as its x, y, z (and w for the two whose size has a fourth
// component) components in 16 bits or 8 bits each, scaled by a factor kept in the data section; w is recovered from
// the unit length in the three-component forms. The member and scale names are guesses.
#ifndef MATH_COMPRESSEDQUATERNION_H
#define MATH_COMPRESSEDQUATERNION_H

#include "code/math/quaternion.h"

namespace math
{
	// Four 16-bit components
	class CompressedQuaternion8
	{
	public:
		short x;
		short y;
		short z;
		short w;
	};

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

	// Four 8-bit components
	class CompressedQuaternion4
	{
	public:
		signed char x;
		signed char y;
		signed char z;
		signed char w;
	};

	class CompressedQuaternion3
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
