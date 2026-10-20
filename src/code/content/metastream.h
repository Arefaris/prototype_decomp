// The streams the content library's meta types read and write through (names guessed; the classes are in another
// unit, 0x105FBF70 - 0x105FCB00, and only what the meta types' slots call is declared). A binary reader or writer
// wraps a byte stream and swaps the bytes of each item when its flag is set; the text reader is content::TextReadStream
// (RTTI) over the same byte stream; the text writer indents what it writes.
#ifndef CONTENT_METASTREAM_H
#define CONTENT_METASTREAM_H

namespace content
{
	// The byte stream under the readers and writers (slot 0 reads or writes a block; the others are the position and
	// the size)
	class ByteStream
	{
	public:
		virtual void Transfer(void* buffer, unsigned int size) = 0;
		virtual unsigned int GetPosition() = 0;
		virtual void SetPosition(unsigned int position) = 0;
		virtual unsigned int GetSize() = 0;
	};

	class MetaType;

	// What a meta type puts in the table it describes itself in (slot 10 of the meta types)
	struct MemberEntry
	{
		int key;
		MetaType* type;
	};

	// 0x105FBF70 (constructor) and 0x105FC030
	class BinaryReader
	{
	public:
		// count items of size bytes
		void Read(void* destination, int count, int size);

		ByteStream* stream;
		bool swap;
	};

	// 0x105FBFB0 (constructor) and 0x105FC070
	class BinaryWriter
	{
	public:
		void Write(const void* source, int count, int size);

		ByteStream* stream;
		bool swap;
	};

	// What the binary slots are given: a pointer to the reader or writer
	struct ReadContext
	{
		BinaryReader* reader;
	};

	struct WriteContext
	{
		BinaryWriter* writer;
	};

	// RTTI content::TextReadStream (constructor 0x105FC0F0): the text of a meta type file, token by token
	class TextReadStream
	{
	public:
		// Slot 0 (0x105FC1F0): reads the next token (a quoted string when quoted is set) into buffer
		virtual bool ReadToken(char* buffer, unsigned int size, bool quoted);
		// 0x105FC140: the line the reader is on
		int GetLine();
		// 0x105FC1B0: puts a message in the reader's error text (printf style)
		void Error(const char* format, ...);
		// 0x105FC720: reads a float
		bool ReadFloat(float* value);

		ByteStream* stream;
		int line;
	};

	// 0x105FC7F0 (constructor): writes text to a byte stream
	class TextWriter
	{
	public:
		// 0x105FC850: ends the line
		void NewLine();
		// 0x105FC830 / 0x105FC840: one level of indentation more or less
		void Indent();
		void Unindent();
		// 0x105FC890: the text, in quotes when asked for
		void Write(const char* text, bool quoted);
		// 0x105FCAB0: a float
		void WriteFloat(const float* value);

		ByteStream* stream;
		int indent;
		int unknown8;
		bool atLineStart;
	};
}

#endif
