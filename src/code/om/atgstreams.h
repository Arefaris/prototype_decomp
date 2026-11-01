// Two streams of the om library that stand on another object (RTTI: om::AtgCoreFileStream and om::ErrorLoggingStream, both
// derived from om::Stream): the first reads and writes a core file, the second hands every call to another stream and logs
// what failed.
#ifndef OM_ATGSTREAMS_H
#define OM_ATGSTREAMS_H

#include "code/core/file/file.h"
#include "code/om/stream.h"

namespace om
{
	class AtgCoreFileStream : public Stream
	{
	public:
		virtual bool Write(const void* data, unsigned int size);
		virtual bool Read(void* data, unsigned int size);
		virtual bool GetSize(unsigned int* size);
		virtual bool GetPosition(unsigned int* position);
		virtual bool Seek(unsigned int position);
		virtual String GetName();
		virtual ~AtgCoreFileStream();
		OM_ALLOCATION(AtgCoreFileStream);

		core::IFile* file;  // 8
	};

	class ErrorLoggingStream : public Stream
	{
	public:
		// 0x10B6A310: the stream the calls go to, and where the failures are logged
		ErrorLoggingStream(Stream* newTarget, Stream** newLog);
		virtual bool Write(const void* data, unsigned int size);
		virtual bool Read(void* data, unsigned int size);
		virtual bool GetSize(unsigned int* size);
		virtual bool GetPosition(unsigned int* position);
		virtual bool Seek(unsigned int position);
		// Slot 8 (0x10B6A340): the name of the target with a note behind it
		virtual String GetDescription();

		Stream* target;  // 8
		Stream** log;  // 0xC
	};
}

#endif
