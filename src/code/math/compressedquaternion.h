// math::CompressedQuaternion8, 6, 4 and 3 (RTTI names of the key types of the compressed quaternion channels; the
// number is the size in bytes): a unit quaternion stored as its x, y, z (and w for the one whose size has a fourth
// component) components in 16 bits or 8 bits each, or the three packed in 32 bits, scaled by a factor kept in the data section; w is recovered from
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
		// 0x106E2F50 (the copy kept in the animation unit; it scales with CompressedQuaternion6::sScale)
		Quaternion ToQuaternion() const;

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

	// Three components packed in one word: x in the low 11 bits, y in the next 11 and z in the top 10
	class CompressedQuaternion4
	{
	public:
		// 0x111BB9C0: 1 / 1023 (x and y); 0x111BB9C4: 1 / 511 (z)
		static float sScale;
		static float sScaleZ;

		// 0x106E3EA0 (the copy kept in the animation unit)
		Quaternion ToQuaternion() const;

		unsigned int packed;
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
