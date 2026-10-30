// The content library's stream interfaces (RTTI names: content::IReadStream, content::LoadStreamWrapper,
// content::IWriteStream, content::SaveStream; the member names are guesses). A read stream hands out bytes, a write
// stream takes them; the wrapper reads through a LoadStream and the save stream writes a file through a buffer.
#ifndef CONTENT_STREAMS_H
#define CONTENT_STREAMS_H

#include "code/content/chunkhandler.h"

namespace content
{
	struct IReadStream
	{
		virtual void Read(void* destination, unsigned int size) = 0;
		virtual unsigned int GetPosition() = 0;
		virtual void Seek(unsigned int position) = 0;
		virtual unsigned int GetSize() = 0;
	};

	class LoadStreamWrapper : public IReadStream
	{
	public:
		// 0x1060ACC0: takes a reference to the stream
		explicit LoadStreamWrapper(LoadStream* newStream);
		// 0x1060A920
		~LoadStreamWrapper();
		// Slots 0 - 3: 0x1060B380, 0x1060A930, 0x1060B3A0, 0x1060A940
		virtual void Read(void* destination, unsigned int size);
		virtual unsigned int GetPosition();
		virtual void Seek(unsigned int position);
		virtual unsigned int GetSize();

		LoadStream* stream;
	};

	struct IWriteStream
	{
		virtual void Write(const void* source, unsigned int size) = 0;
		virtual unsigned int GetPosition() = 0;
		virtual void Seek(unsigned int position) = 0;
		virtual unsigned int GetSize() = 0;
	};

	// A file written through a buffer
	class SaveStream : public IWriteStream
	{
	public:
		// 0x1060ACE0
		SaveStream();
		// 0x1060AD00: flushes and closes the file
		~SaveStream();
		// 0x1060A960: opens the file for writing (a buffer of bufferSize bytes when that is not zero)
		bool Open(const char* path, unsigned int bufferSize);
		// 0x1060A9D0: writes what the buffer holds
		void Flush();
		// Slots 0 - 3: 0x1060AD50, 0x1060ADD0, 0x1060ADF0, 0x1060AE10
		virtual void Write(const void* source, unsigned int size);
		virtual unsigned int GetPosition();
		virtual void Seek(unsigned int position);
		virtual unsigned int GetSize();

		core::IFile* file;
		unsigned char* buffer;
		unsigned int used;
		unsigned int capacity;
	};

	// 0x1060AE30 / 0x1060AE70 / 0x1060AEC0 / 0x1060AF10 / 0x1060B200: make a stream and hand back a reference to it
	// (with a job: also hands the stream to it)
	void CreateLoadStream(LoadStream** result, LoadArguments* arguments, int unused, int mode);
	void CreateLoadStream(LoadStream** result, const char* path, LoadJob* job, int mode);
	void CreateLoadStream(LoadStream** result, core::IFile* file, LoadJob* job, int mode, int blocking);
	void CreateLoadStream(LoadStream** result, const void* data, unsigned int size);
	void CreateLoadStream(LoadStream** result, CompressedReader* compressed, int offset, int size, int blocking);
}

#endif
