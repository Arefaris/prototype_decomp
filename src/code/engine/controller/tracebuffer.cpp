// The small buffer the engine keeps the first few trace records in (code/engine/controller/tracebuffer.cpp; the file
// name is a guess, the unit starts at 0x108A1D20). Names are guesses.
#include <new>
#include <string.h>

namespace core
{
	// One record: a number and up to 32 bytes of data
	struct TraceRecord
	{
		int id;
		unsigned char data[0x20];
		unsigned int size;  // +0x24
	};

	// The first five records (0xCC bytes)
	struct TraceBuffer
	{
		// 0x108A1D20
		TraceBuffer();

		TraceRecord records[5];
		unsigned int count;  // +0xC8
	};

	// 0x1131808C: the buffer, made on first use (0x108A1DB0)
	TraceBuffer* gTraceBuffer;

	// FUNCTION: ENGINE 0x108A1D20
	TraceBuffer::TraceBuffer()
	{
		count = 0;
	}

	// FUNCTION: ENGINE 0x108A1D40
	void Trace(int id, const void* data, int size)
	{
		if (gTraceBuffer->count < 5)
		{
			gTraceBuffer->records[gTraceBuffer->count].id = id;
			if ((unsigned int)size > 0x20)
			{
				size = 0x20;
			}
			gTraceBuffer->records[gTraceBuffer->count].size = size;
			TraceRecord* record = &gTraceBuffer->records[gTraceBuffer->count];
			memcpy(record->data, data, record->size);
			gTraceBuffer->count = gTraceBuffer->count + 1;
		}
	}

	// FUNCTION: ENGINE 0x108A1DB0
	void InitTraceBuffer()
	{
		if (gTraceBuffer == 0)
		{
			gTraceBuffer = new TraceBuffer;
		}
	}
}
