// The sources a fight reader takes its text and its bytes from (RTTI: fight::StringReader and fight::DataReader with
// a reader over a buffer, over a file and over a chunk stream each; base fight::RefCounted). Unit 0x105A2440 -
// 0x105B3680 (no assert path; the file name is a guess). Names are guesses.
#ifndef ENGINE_FIGHT_STREAMREADERS_H
#define ENGINE_FIGHT_STREAMREADERS_H

#include "code/content/chunkhandler.h"
#include "code/core/file/file.h"
#include "code/engine/fight/sequencer.h"

namespace fight
{
	// RTTI: fight::StringReader (7 vftable slots): a source of characters
	class StringReader : public RefCounted
	{
	public:
		// 0x105AAFF0 (the engine keeps a copy)
		StringReader()
		{
		}

		// vftable slot 3: the name of what is read (for the messages)
		virtual const char* GetName() = 0;
		// vftable slot 4: the next character without taking it
		virtual char Peek() = 0;
		// vftable slot 5: takes the next character
		virtual char Read() = 0;
		// vftable slot 6: whether nothing is left
		virtual bool AtEnd() = 0;
	};

	// RTTI: fight::BufferStringReader (0x18 bytes): a text in memory
	class BufferStringReader : public StringReader
	{
	public:
		// 0x105AB040
		BufferStringReader(const char* newBuffer, unsigned int newSize, const char* newName);
		virtual ~BufferStringReader();
		virtual const char* GetName();
		virtual char Peek();
		virtual char Read();
		virtual bool AtEnd();

		const char* buffer;  // +8
		const char* name;  // +0xC
		unsigned int size;  // +0x10
		unsigned int position;  // +0x14
	};

	// RTTI: fight::IFileStringReader (0x10 bytes): a file, one character looked at ahead
	class IFileStringReader : public StringReader
	{
	public:
		// 0x105AB0E0
		explicit IFileStringReader(core::IFile* newFile);
		virtual ~IFileStringReader();
		virtual const char* GetName();
		virtual char Peek();
		virtual char Read();
		virtual bool AtEnd();

		core::IFile* file;  // +8
		char peeked;  // +0xC
		bool hasPeeked;  // +0xD
	};

	// RTTI: fight::StreamStringReader (0x14 bytes): a chunk stream, one character looked at ahead
	class StreamStringReader : public StringReader
	{
	public:
		// 0x105AB200
		StreamStringReader(content::ChunkStream* newStream, const char* newName);
		virtual ~StreamStringReader();
		virtual const char* GetName();
		virtual char Peek();
		virtual char Read();
		virtual bool AtEnd();

		const char* name;  // +8
		content::ChunkStream* stream;  // +0xC
		char peeked;  // +0x10
		bool hasPeeked;  // +0x11
	};

	// RTTI: fight::DataReader (6 vftable slots): a source of bytes
	class DataReader : public RefCounted
	{
	public:
		// 0x105AC540 (the engine keeps a copy)
		DataReader()
		{
		}

		// vftable slot 3: the name of what is read
		virtual const char* GetName() = 0;
		// vftable slot 4: reads a number of bytes, answers how many
		virtual unsigned int Read(void* destination, unsigned int count) = 0;
		// vftable slot 5: whether nothing is left
		virtual bool AtEnd() = 0;
	};

	// RTTI: fight::BufferDataReader (0x18 bytes)
	class BufferDataReader : public DataReader
	{
	public:
		// 0x105AC8C0
		BufferDataReader(const char* newBuffer, unsigned int newSize, const char* newName);
		virtual ~BufferDataReader();
		virtual const char* GetName();
		virtual unsigned int Read(void* destination, unsigned int count);
		virtual bool AtEnd();

		const char* buffer;  // +8
		const char* name;  // +0xC
		unsigned int size;  // +0x10
		unsigned int position;  // +0x14
	};

	// RTTI: fight::IFileDataReader (0xC bytes)
	class IFileDataReader : public DataReader
	{
	public:
		// 0x105AC600
		explicit IFileDataReader(core::IFile* newFile);
		virtual ~IFileDataReader();
		virtual const char* GetName();
		virtual unsigned int Read(void* destination, unsigned int count);
		virtual bool AtEnd();

		core::IFile* file;  // +8
	};

	// RTTI: fight::StreamDataReader (0x10 bytes)
	class StreamDataReader : public DataReader
	{
	public:
		// 0x105AC6E0
		StreamDataReader(content::ChunkStream* newStream, const char* newName);
		virtual ~StreamDataReader();
		virtual const char* GetName();
		virtual unsigned int Read(void* destination, unsigned int count);
		virtual bool AtEnd();

		content::ChunkStream* stream;  // +8
		const char* name;  // +0xC
	};
}

#endif
