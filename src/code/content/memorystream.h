// A content::LoadObject that reads from a block of memory (0x4C bytes; constructor 0x1060AAE0 in another unit; the
// class name is a guess).
#ifndef CONTENT_MEMORYSTREAM_H
#define CONTENT_MEMORYSTREAM_H

#include "code/content/loadinventory.h"

namespace content
{
	class MemoryStream : public LoadObject
	{
	public:
		// 0x1060AAE0
		MemoryStream(const void* data, unsigned int size);

		unsigned char unknown8[0x44];
	};
}

#endif
