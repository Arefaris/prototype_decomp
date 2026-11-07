// Colour tables that the engine's static initialisers convert from packed colours into floats in translation units whose code
// is not reconstructed (unit name guess).
#include "code/math/colour128.h"
#include "code/pure3d/renderscheme.h"

namespace engine
{
	// A packed colour's channels as floats (these units convert through the signed integer instructions)
	static inline math::Colour128 ToFloats(const math::pddiColour& colour)
	{
		math::Colour128 result;
		result.r = (float)(int)colour.r * (1.0f / 255.0f);
		result.g = (float)(int)colour.g * (1.0f / 255.0f);
		result.b = (float)(int)colour.b * (1.0f / 255.0f);
		result.a = (float)(int)colour.a * (1.0f / 255.0f);
		return result;
	}

	// The colours the converted table below starts from (another unit)
	extern const math::pddiColour gSwatches[5];

	math::Colour128 gColourPalette[8] =
	{
		ToFloats(math::pddiColour::LAVENDER),
		ToFloats(math::pddiColour::LIME_GREEN),
		ToFloats(math::pddiColour::BROWN),
		ToFloats(math::pddiColour::BLUE),
		ToFloats(reinterpret_cast<const math::pddiColour&>(pure3d::gDebugColour)),
		ToFloats(math::pddiColour::TURQUOISE),
		ToFloats(math::pddiColour::GREY),
		ToFloats(math::pddiColour::YELLOW)
	};

	math::Colour128 gSwatchColours[5] =
	{
		ToFloats(gSwatches[0]),
		ToFloats(gSwatches[1]),
		ToFloats(gSwatches[2]),
		ToFloats(gSwatches[3]),
		ToFloats(gSwatches[4])
	};
}

// The dynamic initialisers of the unit's tables:
// FUNCTION: ENGINE 0x10D58B80
// FUNCTION: ENGINE 0x10D5FAA0
