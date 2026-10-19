// math::Colour128 (RTTI name: TimeOfDayVarChannel<class math::Colour128>): a colour of four floats, red to alpha in 0 - 1.
// Only what the engine's units need so far; names are guesses.
#ifndef MATH_COLOUR128_H
#define MATH_COLOUR128_H

#include "code/math/pddicolour.h"

namespace math
{
	class Colour128
	{
	public:
		Colour128()
		{
		}
		// User-defined like Vector's: the engine copies the channels one by one
		Colour128(const Colour128& other)
		{
			r = other.r;
			g = other.g;
			b = other.b;
			a = other.a;
		}
		// The channels of a packed colour as floats (a byte over 255)
		explicit Colour128(const pddiColour& colour)
		{
			r = (float)colour.r * (1.0f / 255.0f);
			g = (float)colour.g * (1.0f / 255.0f);
			b = (float)colour.b * (1.0f / 255.0f);
			a = (float)colour.a * (1.0f / 255.0f);
		}

		float r;
		float g;
		float b;
		float a;
	};
}

#endif
