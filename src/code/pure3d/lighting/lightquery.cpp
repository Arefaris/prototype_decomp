// pure3d::LightQuery (unit around 0x1060F840 - 0x1060FE00, next to the container helpers). Names are guesses.
#include "code/pure3d/lighting.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1060F840
	// EQUIVALENT: the original keeps the four output counters in separate stack slots and reloads them; our compiler
	// keeps the base in a register and derives the word offsets from it
	unsigned int BuildLightIndices(unsigned int* out, unsigned int* masks, unsigned int count)
	{
		unsigned int* start = out;
		unsigned int w0 = masks[0];
		unsigned int w1 = masks[1];
		unsigned int w2 = masks[2];
		unsigned int w3 = masks[3];
		unsigned int v0 = 0;
		unsigned int v1 = 0x20;
		unsigned int v2 = 0x40;
		unsigned int v3 = 0x60;
		if ((int)(count * 4 - 4) >= 0)
		{
			unsigned int groups = count;
			do
			{
				if ((w0 | w1 | w2 | w3) == 0)
				{
					v0 += 0x80;
					v1 += 0x80;
					v2 += 0x80;
					v3 += 0x80;
				}
				else
				{
					for (unsigned int j = 0; j != 0x10; j++)
					{
						*out = v0;
						out += (w0 & 1);
						*out = v1;
						out += (w1 & 1);
						*out = v2;
						out += (w2 & 1);
						*out = v3;
						out += (w3 & 1);
						unsigned int* q = out + ((w0 >> 1) & 1);
						*out = v0 + 1;
						*q = v1 + 1;
						v1 += 2;
						q += ((w1 >> 1) & 1);
						*q = v2 + 1;
						v2 += 2;
						unsigned int w2s = w2 >> 1;
						q[w2s & 1] = v3 + 1;
						v3 += 2;
						unsigned int w3s = w3 >> 1;
						v0 += 2;
						w0 >>= 2;
						w1 >>= 2;
						w2 >>= 2;
						w3 >>= 2;
						out = q + (w2s & 1) + (w3s & 1);
					}
					v0 += 0x60;
					v1 += 0x60;
					v2 += 0x60;
					v3 += 0x60;
				}
				w0 = masks[4];
				w1 = masks[5];
				w2 = masks[6];
				w3 = masks[7];
				masks += 4;
				groups--;
			} while (groups != 0);
		}
		return out - start;
	}

	// FUNCTION: ENGINE 0x1060FE00
	// EQUIVALENT: the three arguments load into eax / esi / ecx in the original, ecx / edx / eax in ours
	unsigned int LightQuery::Select(unsigned int* indices, unsigned int count, const unsigned int* region)
	{
		SetRegionMask(&bitCount, region);
		return BuildLightIndices(indices, mask, bitCount >> 7);
	}
}
