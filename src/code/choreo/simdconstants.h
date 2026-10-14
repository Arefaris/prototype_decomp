// The constants of the choreo module's four-wide math (spherical interpolation of rotations): masks, polynomial
// coefficients packed four to a vector (a coefficient is used by shuffling its lane across the vector), angles and a
// tolerance. They are data of the original image; the names are guesses.
#ifndef CHOREO_SIMDCONSTANTS_H
#define CHOREO_SIMDCONSTANTS_H

#include <emmintrin.h>

namespace choreo
{
	// 0x10E8C7C0: the sign bit of every lane
	extern const __m128 gSignMask;
	// 0x10E8C7D0: everything but the sign bit
	extern const __m128 gAbsMask;
	// 0x10E8C800
	extern const __m128 gOne;
	// 0x10E8C8A0, 0x10E8C8B0: the coefficients of the sine polynomial in x^2 (-1/3!, 1/5!, -1/7!, ...), four to a
	// vector
	extern const __m128 gSinCoefficients0;
	extern const __m128 gSinCoefficients1;
	// 0x10E8C8C0, 0x10E8C8D0: the coefficients of the arctangent polynomial in x^2, four to a vector
	extern const __m128 gAtanCoefficients0;
	extern const __m128 gAtanCoefficients1;
	// 0x111EC550: below this 1 - cos^2 the rotations count as parallel
	extern const __m128 gParallelTolerance;
	// 0x111EC560, 0x111EC570, 0x111EC590, 0x111EC5B0: pi, 2 pi, pi / 2, 1 / (2 pi)
	extern const __m128 gPi;
	extern const __m128 gTwoPi;
	extern const __m128 gHalfPi;
	extern const __m128 gInvTwoPi;
}

#endif
