// content::Decompressor (names guessed): the object that unpacks a compressed stream, made for a compression level by
// CreateDecompressor (0x106DC260). The class lives in another unit (0x106DBF70 - 0x106DC2B0); only what the content
// library's readers use is declared.
#ifndef CONTENT_DECOMPRESSOR_H
#define CONTENT_DECOMPRESSOR_H

#include "code/core/criticalsection.h"

namespace content
{
	class Decompressor
	{
	public:
		// 0x106DBF70: the state, read under the lock (3: failed)
		int GetState();
		// 0x106DBF90: waits for the event
		void Wait();
		// 0x106DBFA0 / 0x106DBFC0: how much input has been used / how much output has been made
		int GetConsumed();
		int GetProduced();
		// 0x106DBFE0: unpacks input into output (final: it is the last of the data)
		void Decode(const void* input, unsigned int inputSize, void* output, unsigned int outputSize, bool final);

		// Nothing is left to do: it has not failed and no request is pending (the engine has a copy out of line at
		// 0x1060DBB0)
		int IsDone()
		{
			if (GetState() != 3 && core::AtomicRead(&pending) == 0)
			{
				return 1;
			}
			return 0;
		}

		unsigned char unknown0[0x38];
		// The event at +0x38: its count is the requests that are pending
		long pending;
		long unknown3C;
	};

	// 0x106DC260 / 0x106DC2B0: makes one for a level (the second argument is 1 for every caller) / destroys it
	Decompressor* CreateDecompressor(int level, int unused, int heap);
	void DestroyDecompressor(Decompressor* decompressor);
}

#endif
