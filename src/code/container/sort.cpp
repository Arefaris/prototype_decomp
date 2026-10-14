// A byte-radix sort of an index array (unit around 0x1060E960 - 0x10610E40, the container namespace's tree, list,
// string and sort helpers). File and function names are guesses.
#include <string.h>

namespace container
{
	// Sorts `count` indices into ascending order of the key bytes of `data` (records of `stride` bytes each) with an
	// LSD byte radix sort. keyDesc is a sequence of 4-bit passes, least significant first: bits 0-1 the byte offset in
	// the record, bit 2 set for the final (signed / float) byte, bit 3 set on the last pass. indices is initialised to
	// 0 .. count - 1 first when initIndices; out is scratch. Returns the sorted index array (indices or out).
	// FUNCTION: ENGINE 0x10610E40
	// NONMATCHING: the prefix sums of the signed pass are a separate array here, where the original keeps the high-byte
	// sums in place over the histogram; compiled into the game it crashes at start-up, so the body is not trusted yet
#ifdef NONMATCHING
	unsigned short* RadixSort(unsigned char* data, unsigned short count, unsigned short* indices,
		unsigned short* out, unsigned int keyDesc, unsigned short stride, bool initIndices)
	{
		if (count == 0)
		{
			return 0;
		}
		if (initIndices)
		{
			for (unsigned short i = 0; i != count; i++)
			{
				indices[i] = i;
			}
		}

		unsigned short counts[4][256];
		if ((keyDesc & 0xffffff00) == 0)
		{
			unsigned int offset = keyDesc & 3;
			memset(counts[offset], 0, sizeof(counts[offset]));
			for (unsigned char* p = data + offset; p != data + (unsigned int)stride * count + offset; p += stride)
			{
				counts[offset][*p]++;
			}
		}
		else
		{
			memset(counts, 0, sizeof(counts));
			for (unsigned char* p = data; p != data + (unsigned int)stride * count; p += stride)
			{
				counts[0][p[0]]++;
				counts[1][p[1]]++;
				counts[2][p[2]]++;
				counts[3][p[3]]++;
			}
		}

		while ((keyDesc & 8) == 0)
		{
			unsigned int offset = keyDesc & 3;
			unsigned char first = data[offset];
			unsigned short prefix[256];

			if ((keyDesc & 4) == 0)
			{
				if (counts[offset][first] != count)
				{
					prefix[0] = 0;
					for (unsigned int i = 0; i != 0xff; i++)
					{
						prefix[i + 1] = prefix[i] + counts[offset][i];
					}
					for (unsigned short* p = indices; p != indices + count; p++)
					{
						unsigned short v = *p;
						out[prefix[data[(unsigned int)v * stride + offset]]++] = v;
					}
					unsigned short* t = indices;
					indices = out;
					out = t;
				}
			}
			else if (counts[offset][first] == count)
			{
				if ((signed char)first < 0)
				{
					for (unsigned int i = 0; i != count; i++)
					{
						out[i] = indices[count - 1 - i];
					}
					unsigned short* t = indices;
					indices = out;
					out = t;
				}
			}
			else
			{
				prefix[0] = 0;
				for (unsigned int i = 0x80; i != 0x100; i++)
				{
					prefix[0] += counts[offset][i];
				}
				for (unsigned int i = 0; i != 0x7f; i++)
				{
					prefix[i + 1] = prefix[i] + counts[offset][i];
				}
				prefix[0x80] = 0;
				for (unsigned int i = 0x80; i != 0xff; i++)
				{
					prefix[i + 1] = prefix[i] + counts[offset][i];
				}
				for (unsigned short* p = indices; p != indices + count; p++)
				{
					unsigned short v = *p;
					out[prefix[data[(unsigned int)v * stride + offset]]++] = v;
				}
				unsigned short* t = indices;
				indices = out;
				out = t;
			}
			keyDesc >>= 4;
		}
		return indices;
	}
#endif
}
