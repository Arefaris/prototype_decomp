// om::BufferedStream (RTTI om::BufferedStream, derived from om::Stream): reads another stream through a buffer of its
// own and writes straight through to it; the position is the stream's own.
#ifndef OM_BUFFEREDSTREAM_H
#define OM_BUFFEREDSTREAM_H

#include "code/om/stream.h"

namespace om
{
	// 0x105BC9B0 (name guessed): the smaller of two values
	unsigned int Min(const unsigned int& first, const unsigned int& second);
	// 0x105B7550 (name guessed): the allocation heap the next allocations come from
	void SetAllocationHeap(int heap);

	class BufferedStream : public Stream
	{
	public:
		// 0x105E3EF0: the buffer has capacity bytes
		BufferedStream(Stream* newTarget, unsigned int newCapacity, bool newFlag);
		// Slots 0 to 5 (0x105E3F50 / 0x105E3F80 / 0x105E40A0 / 0x105E3EC0 / 0x105E3ED0 / 0x105E40B0)
		virtual bool Write(const void* data, unsigned int size);
		virtual bool Read(void* data, unsigned int size);
		virtual bool GetSize(unsigned int* result);
		virtual bool GetPosition(unsigned int* result);
		virtual bool Seek(unsigned int newPosition);
		virtual String GetName();

		void* buffer;  // 8
		unsigned int capacity;  // 0xC
		unsigned int unknown10;
		Stream* target;  // 0x14
		unsigned int bufferStart;  // 0x18: the position of the target the buffer starts at
		unsigned int position;  // 0x1C
		bool flag;  // 0x20
	};
}

#endif
