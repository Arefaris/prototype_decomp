// The four-wide vector constants of the pose data unit (the unit axes, zero, one and the sign mask) and the matrix
// helpers it builds on. The constants are data of the original image; the names are guesses.
#ifndef PURE3D_POSEDATASIMD_H
#define PURE3D_POSEDATASIMD_H

#include <xmmintrin.h>

namespace pure3d
{
	// 0x10E58B40: the sign bit of every lane
	extern const __m128 gPoseSignMask;
	// 0x10E58B80
	extern const __m128 gPoseZero;
	// 0x10E58B90
	extern const __m128 gPoseOne;
	// 0x10E58BA0, 0x10E58BB0, 0x10E58BC0, 0x10E58BD0: (1, 0, 0, 0), (0, 1, 0, 0), (0, 0, 1, 0), (0, 0, 0, 1)
	extern const __m128 gPoseUnitX;
	extern const __m128 gPoseUnitY;
	extern const __m128 gPoseUnitZ;
	extern const __m128 gPoseUnitW;
}

#endif
