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

		// Whether the position is before the end (inline; name guessed)
		__forceinline bool HasMore()
		{
			return GetPosition() < GetSize();
		}
	};

	class MetaType;

	// What a meta type puts in the table it lists the values of an object in (slot 10 of the meta types): the value
	// and its meta type, which writes it again through slot 11
	struct MemberEntry
	{
		void* object;
		MetaType* type;
	};

	// 0x105FBF70 (constructor) and 0x105FC030
	class BinaryReader
	{
	public:
		// 0x105FBF70
		BinaryReader(ByteStream* newStream, bool newSwap);
		// 0x105FBF90 / 0x105FBFA0 (returns the previous setting)
		bool GetSwap() const;
		bool SetSwap(bool newSwap);
		// count items of size bytes
		void Read(void* destination, int count, int size);

		ByteStream* stream;
		bool swap;
	};

	// 0x105FBFB0 (constructor) and 0x105FC070
	class BinaryWriter
	{
	public:
		// 0x105FBFB0
		BinaryWriter(ByteStream* newStream, bool newSwap);
		// 0x105FBFD0 / 0x105FBFE0 (returns the previous setting)
		bool GetSwap() const;
		bool SetSwap(bool newSwap);
		void Write(const void* source, int count, int size);

		ByteStream* stream;
		bool swap;
	};

	// What the binary slots are given: a pointer to the reader or writer
	struct ReadContext
	{
		// 0x105FCBD0: a string stored as its length (four bytes) and its characters, ended here; the second argument is not
		// used (names guessed)
		void ReadString(char* destination, int size);

		BinaryReader* reader;
	};

	struct WriteContext
	{
		// 0x105FCC10: the length of the string and its characters
		void WriteString(const char* text);

		BinaryWriter* writer;
	};

	// RTTI content::TextReadStream (constructor 0x105FC0F0): the text of a meta type file, token by token
	class TextReadStream
	{
	public:
		// 0x105FC0F0: reads from stream; name is copied (up to 0x100 characters) for the error messages (null for none)
		TextReadStream(ByteStream* newStream, bool newFlag, const char* newName);
		// Slot 0 (0x105FC1F0): reads the next token (a quoted string when quoted is set) into buffer
		virtual bool ReadToken(char* buffer, unsigned int size, bool quoted);
		// 0x105FC140 / 0x105FC150: the line the reader is on
		int GetLine();
		void SetLine(int newLine);
		// 0x105FC180 / 0x105FC190: the position in the byte stream under the reader
		unsigned int GetPosition();
		void SetPosition(unsigned int position);
		// 0x105FC1B0: puts a message in the reader's error text (printf style)
		void Error(const char* format, ...);
		// 0x105FC720: reads a float
		bool ReadFloat(float* value);
		// 0x105FC500 / 0x105FC550 / 0x105FC5A0 / 0x105FC600 / 0x105FC660 / 0x105FC6C0 / 0x105FC770: read a token and
		// take the number (as unsigned or with a base prefix, within the range of the type) or true / false in it
		bool ReadUInt(unsigned int* value);
		bool ReadInt(int* value);
		bool ReadUShort(unsigned short* value);
		bool ReadShort(short* value);
		bool ReadUChar(unsigned char* value);
		bool ReadChar(char* value);
		bool ReadBool(bool* value);
		// 0x105FC160 / 0x105FC170: the flag at +0xC (the reader skips comments from // to the end of the line
		// when it is set)
		void SetFlag(bool newFlag);
		bool GetFlag() const;
		// 0x105FC1A0: the size of the byte stream under the reader
		unsigned int GetSize();
		// 0x105FC1E0: the name given to the constructor
		const char* GetName();

		ByteStream* stream;
		int line;
		bool flag;  // +0xC (names of the members from here on guessed)
		char errorText[0x200];  // +0xD: what Error wrote last
		char name[0x100];  // +0x20D
	};

	// content::MemoryReadStream (RTTI, 4 slots, base content::IReadStream; another unit, constructor 0x1060E670): a
	// byte stream over a block of memory
	class MemoryReadStream : public ByteStream
	{
	public:
		MemoryReadStream(const void* data, unsigned int size);

		virtual void Transfer(void* buffer, unsigned int size);
		virtual unsigned int GetPosition();
		virtual void SetPosition(unsigned int position);
		virtual unsigned int GetSize();

		const void* data;
		unsigned int size;
		unsigned int position;
	};

	// 0x105FC7F0 (constructor): writes text to a byte stream
	class TextWriter
	{
	public:
		explicit TextWriter(ByteStream* newStream);
		// 0x105FC810: does nothing
		void Flush();
		// 0x105FC820
		void SetUnknown8(int value);
		// 0x105FC930 / 0x105FC970 / 0x105FC9B0 / 0x105FC9F0 / 0x105FCA30 / 0x105FCA70 / 0x105FCAF0: a number in
		// decimal, or true / false
		void WriteUInt(const unsigned int* value);
		void WriteInt(const int* value);
		void WriteUShort(const unsigned short* value);
		void WriteShort(const short* value);
		void WriteUChar(const unsigned char* value);
		void WriteChar(const char* value);
		void WriteBool(const bool* value);
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

	// 0x105FCBA0: a 64-bit key made of a name (case ignored; the name of the class and the use are guesses)
	struct NameKey64
	{
		explicit NameKey64(const char* text);

		unsigned __int64 value;
	};

	// The names of the primitive types (0x105FCB20 - 0x105FCB90 and 0x105FCC60; names guessed): the codes of the
	// meta types are strings of their own
	const char* GetUIntTypeName();
	const char* GetIntTypeName();
	const char* GetUShortTypeName();
	const char* GetShortTypeName();
	const char* GetUCharTypeName();
	const char* GetCharTypeName();
	const char* GetFloatTypeName();
	const char* GetBoolTypeName();
	const char* GetNameTypeName();
}

#endif
