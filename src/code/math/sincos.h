// SinCos: the engine computes sine and cosine together with the x87 fsincos instruction in inline assembly; the
// pattern (fld angle; fsincos; two stores through pointers) is inlined into every caller. Name guessed.
#ifndef MATH_SINCOS_H
#define MATH_SINCOS_H

namespace math
{
	inline void SinCos(float angle, float* sine, float* cosine)
	{
		__asm
		{
			fld angle
			fsincos
			mov edx, cosine
			fstp dword ptr [edx]
			mov edx, sine
			fstp dword ptr [edx]
		}
	}
}

#endif
