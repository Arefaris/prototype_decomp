// pure3d::Light and the light bit sets (unit around 0x1075B000 - 0x1075CD00; file name guessed). Names are guesses.
#include "code/pure3d/lighting.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1075C750
	void MergeLightBits(LightBits* out, const LightBits* a, const LightBits* b, const LightGroups* layout,
		unsigned int groups)
	{
		for (unsigned int i = 0; i < 14; i++, groups >>= 1)
		{
			if (!groups)
			{
				return;
			}
			if (groups & 1)
			{
				unsigned int first = layout->first[i] << 5;
				unsigned int last = ((layout->count[i] << 5) + first - 1) >> 5;
				for (unsigned int word = first >> 5; word <= last; word++)
				{
					out->words[word] = a->words[word] | b->words[word];
				}
			}
		}
	}
}
