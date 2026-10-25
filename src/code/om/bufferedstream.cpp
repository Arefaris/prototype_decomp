// The om library's buffered stream (0x105E3EC0 - 0x105E40C0).
#include "code/om/bufferedstream.h"
#include <string.h>

namespace om
{
	// FUNCTION: ENGINE 0x105E3EF0
	// EQUIVALENT: scheduling: the engine stores the vftable before it pushes the argument of the heap call, ours after (96.0 %)
	BufferedStream::BufferedStream(Stream* newTarget, unsigned int newCapacity, bool newFlag)
	{
		buffer = 0;
		capacity = 0;
		unknown10 = 0;
		SetAllocationHeap(0);
		capacity = newCapacity;
		unknown10 = 4;
		buffer = Allocate("Buffered Stream", newCapacity, 4);
		position = 0;
		target = newTarget;
		bufferStart = 0xFFFFFFFF;
		flag = newFlag;
	}

	// FUNCTION: ENGINE 0x105E3F50
	bool BufferedStream::Write(const void* data, unsigned int size)
	{
		target->Seek(position);
		bool written = target->Write(data, size);
		position += size;
		return written;
	}

	// FUNCTION: ENGINE 0x105E3F80
	// EQUIVALENT: register allocation: the engine keeps the stream, the buffer and the vftable in ebx, ebp and edi and the count in memory (about 85 %)
	bool BufferedStream::Read(void* data, unsigned int size)
	{
		unsigned int done = 0;
		unsigned int first;
		unsigned int second;
		if (size != 0)
		{
			do
			{
				unsigned int current = position;
				unsigned int start = bufferStart;
				if (current >= start && current < capacity + start)
				{
					second = capacity - current + start;
					first = size - done;
					unsigned int count = Min(second, first);
					memcpy(static_cast<char*>(data) + done, static_cast<char*>(buffer) - start + current, count);
					position += count;
					done += count;
				}
				else
				{
					unsigned int total = 0;
					if (!target->GetSize(&total))
					{
						return false;
					}
					second = total - position;
					first = capacity;
					Stream* stream = target;
					void* destination = buffer;
					bool ok = target->Seek(position) && stream->Read(destination, Min(second, first));
					bufferStart = position;
					if (!ok)
					{
						return false;
					}
				}
			}
			while (done < size);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105E40A0
	bool BufferedStream::GetSize(unsigned int* result)
	{
		return target->GetSize(result);
	}

	// FUNCTION: ENGINE 0x105E3EC0
	bool BufferedStream::GetPosition(unsigned int* result)
	{
		*result = position;
		return true;
	}

	// FUNCTION: ENGINE 0x105E3ED0
	bool BufferedStream::Seek(unsigned int newPosition)
	{
		position = newPosition;
		return true;
	}

	// FUNCTION: ENGINE 0x105E40B0
	String BufferedStream::GetName()
	{
		return target->GetName();
	}
}
