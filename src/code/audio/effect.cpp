// The helpers shared by the mixer's effects (0x105C3980 - 0x105C4B10).
#include "code/audio/effect.h"
#include <math.h>

namespace audio
{
	// FUNCTION: ENGINE 0x105C3980
	float Cosine(float angle)
	{
		return cosf(angle);
	}

	// FUNCTION: ENGINE 0x105C3990
	float Sine(float angle)
	{
		return sinf(angle);
	}

	// FUNCTION: ENGINE 0x105C39A0
	float Select(float test, float whenPositive, float whenNegative)
	{
		if (test >= gZero)
		{
			return whenPositive;
		}
		return whenNegative;
	}

	// FUNCTION: ENGINE 0x105C4A30
	float Exponential(float exponent)
	{
		return expf(exponent);
	}

	// FUNCTION: ENGINE 0x105C4A50
	float SquareRoot(float value)
	{
		return sqrtf(value);
	}

	// FUNCTION: ENGINE 0x105C4A60
	float SquareRootOfPower(float value)
	{
		return sqrtf(value);
	}

	// FUNCTION: ENGINE 0x105C4B00
	float* EffectBuffer::GetAligned()
	{
		return aligned;
	}

	// FUNCTION: ENGINE 0x105C4B10
	template unsigned int Clamp<unsigned int>(const unsigned int&, const unsigned int&, const unsigned int&);
}
