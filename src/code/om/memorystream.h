// om::MemoryStream (RTTI om::MemoryStream, derived from om::Stream): a stream on a block of memory the caller
// supplies. It reads and writes at a cursor and fails an operation that would pass the end of the block.
#ifndef OM_MEMORYSTREAM_H
#define OM_MEMORYSTREAM_H

#include "code/om/stream.h"

namespace om
{
	class MemoryStream : public Stream
	{
	public:
		// 0x105E4630
		MemoryStream(void* newBegin, unsigned int newSize, bool newWriting);
		// Slots 0 to 4 (0x105E4690 / 0x105E46E0 / 0x105E4730 / 0x105E4750 / 0x105E4770)
		virtual bool Write(const void* data, unsigned int size);
		virtual bool Read(void* data, unsigned int size);
		virtual bool GetSize(unsigned int* size);
		virtual bool GetPosition(unsigned int* position);
		virtual bool Seek(unsigned int position);
		// Slot 7 (0x105E4660 is the deleting destructor)
		virtual ~MemoryStream()
		{
		}
		// Slot 8 (0x105E4780)
		virtual String GetDescription();

		unsigned int size;  // 8
		unsigned char* begin;  // 0xC
		unsigned char* cursor;  // 0x10
		bool writing;  // 0x14
	};
}

#endif
