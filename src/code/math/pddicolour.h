// math::pddiColour (RTTI type argument of engine::render::ParameterInterpolator<class math::pddiColour>): a packed
// 32-bit colour, blue in the low byte. The channel names follow the byte order the engine converts them in (red is
// byte 2 where a colour becomes floats); WHITE is the constant at 0x111BBA24 (another unit, name guessed).
#ifndef MATH_PDDICOLOUR_H
#define MATH_PDDICOLOUR_H

namespace math
{
	class pddiColour
	{
	public:
		// 0x111BBA24
		static const pddiColour WHITE;

		unsigned int b : 8;
		unsigned int g : 8;
		unsigned int r : 8;
		unsigned int a : 8;
	};
}

#endif
