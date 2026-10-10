#include "code/core/crc32.h"

namespace core
{
	// GLOBAL: ENGINE 0x1127A480
	static unsigned int sCrc32Table[256];
	// GLOBAL: ENGINE 0x1127A880
	static bool sCrc32TableBuilt;

	// FUNCTION: ENGINE 0x10646050
	void BuildCrc32Table()
	{
		if (sCrc32TableBuilt)
		{
			return;
		}
		for (unsigned int i = 0; i < 256; i++)
		{
			unsigned int c = i << 24;
			// Eight shift steps, unrolled by the compiler
			for (int k = 0; k < 8; k++)
			{
				if (c & 0x80000000)
				{
					c = (c << 1) ^ 0x04C11DB7;
				}
				else
				{
					c <<= 1;
				}
			}
			sCrc32Table[i] = c;
		}
		sCrc32TableBuilt = true;
	}

	// FUNCTION: ENGINE 0x10646100
	unsigned int Crc32(const void* data, unsigned int size, unsigned int crc)
	{
		const unsigned char* bytes = (const unsigned char*)data;
		for (unsigned int i = 0; i < size; i++)
		{
			crc = (crc << 8) ^ sCrc32Table[((crc >> 24) ^ bytes[i]) & 0xFF];
		}
		return crc;
	}
}
