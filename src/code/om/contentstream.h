// om::ContentStream (RTTI: derived from om::Stream): reads the bytes of a content load stream; it cannot write.
#ifndef OM_CONTENTSTREAM_H
#define OM_CONTENTSTREAM_H

#include "code/content/chunkhandler.h"
#include "code/content/streams.h"
#include "code/om/stream.h"

namespace om
{
	class ContentStream : public Stream
	{
	public:
		// 0x10AAAC70: opens the file of the path
		ContentStream(const char* path, int unused);
		// 0x10AAACA0: reads through a stream that is open
		explicit ContentStream(content::LoadStream* newStream);
		// Slots 0 to 5 (0x10AAACD0 / 0x10AAACE0 / 0x10AAAD00 / 0x10AAAD30 / 0x10AAAD50 / 0x10AAADD0)
		virtual bool Write(const void* data, unsigned int size);
		virtual bool Read(void* data, unsigned int size);
		virtual bool GetSize(unsigned int* size);
		virtual bool GetPosition(unsigned int* position);
		virtual bool Seek(unsigned int position);
		virtual String GetName();
		// Slot 7 (0x10AAAD80 is the body, the deleting destructor 0x10AAADA0)
		virtual ~ContentStream();

		content::LoadStream* stream;  // 8
	};
}

#endif
