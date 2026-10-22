// The om library's streams (RTTI: om::Stream and its derived classes om::TextOutStream, om::NullStream, om::MemoryStream
// and others): a byte stream that can be written, read and asked for its size and position; every operation answers
// whether it worked, the base class's all say no. Only the base and the text writer are described so far.
#ifndef OM_STREAM_H
#define OM_STREAM_H

#include "code/om/allocation.h"
#include "code/om/string.h"

namespace om
{
	class Stream
	{
	public:
		// 0x105C0E00 (called, not inlined, by the derived classes' constructors)
		Stream();
		// Slot 0 (0x105B86E0): writes the bytes
		virtual bool Write(const void* data, unsigned int size);
		// Slot 1 (0x105B86F0): reads the bytes
		virtual bool Read(void* data, unsigned int size);
		// Slots 2 and 3 (0x105B8700 / 0x105B8710): the size and the position
		virtual bool GetSize(unsigned int* size);
		virtual bool GetPosition(unsigned int* position);
		// Slot 4 (0x105B8720)
		virtual bool Seek(unsigned int position);
		// Slot 5 (0x105B8730): the name of what the stream is on (empty)
		virtual String GetName();
		// Slot 6 (0x105B8770)
		virtual bool HasFailed();
		// Slot 7 (the deleting destructor is 0x105B8780)
		virtual ~Stream()
		{
		}
		OM_ALLOCATION(Stream);

		bool failed;  // 4
	};

	// Writes text to another stream, putting a space or the indentation in front of every line
	class TextOutStream : public Stream
	{
	public:
		// 0x105C0EA0
		explicit TextOutStream(Stream* newTarget);
		// Slot 0 (0x105C0F90): writes the text line by line
		virtual bool Write(const void* data, unsigned int size);

		Stream* target;  // 8
		bool atLineStart;  // 0xC
		unsigned int indent;  // 0x10
		bool indentWithTabs;  // 0x14

	private:
		// 0x105C0ED0: the tabs of the indentation
		bool WriteIndent();
		// 0x105C0F20: a part of a line, with what stands in front of the first
		bool WriteLinePart(const char* text, unsigned int length);
	};

	// 0x105C0E10: formats into a buffer of 2048 characters and writes it (cdecl, the stream first)
	void StreamPrintf(Stream* stream, const char* format, ...);
}

#endif
