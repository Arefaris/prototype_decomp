// content::CompressedFile (RTTI: a core::IFile, 0x54 bytes; the member names are guesses): a file whose data the
// decompression thread unpacks (the CompressedFileFactory in code/content/loadstream.cpp queues the reads). Reads go
// to the thread, the other calls to the file inside it.
#ifndef CONTENT_COMPRESSEDFILE_H
#define CONTENT_COMPRESSEDFILE_H

#include "code/core/file/file.h"

namespace content
{
	class CompressedFileFactory;
	class CompressedFile;

	// What the thread is asked to do: read size bytes of the file into the buffer
	struct DecompressRequest
	{
		CompressedFile* file;
		void* buffer;
		unsigned int size;
	};

	class CompressedFile : public core::IFile
	{
	public:
		// 0x1060E3F0: a file that reads the part of the file inside through the buffers of the pool, and starts
		// reading
		CompressedFile(core::IFile* newInner, int newPassthrough, unsigned int newStart, unsigned int newSize,
			int newHeap, CompressedFileFactory* newFactory);
		// 0x1060E480
		CompressedFile(core::IFile* newInner, int level, unsigned int newUnpacked, unsigned int newStart,
			unsigned int newSize, int newHeap, CompressedFileFactory* newFactory);
		// 0x1060DDF0 (the scalar deleting destructor is 0x1060E3C0)
		virtual ~CompressedFile();

		// 0x1060DDC0 / 0x1060DDE0: from the heap the second argument names / back to its heap
		static void* operator new(unsigned int size, int heap);
		static void operator delete(void* block);

		// 0x1060E2F0: the part of the constructors both share
		void Init(core::IFile* newInner, int newPassthrough, int level, unsigned int newUnpacked, unsigned int newStart,
			unsigned int newSize, int newHeap, CompressedFileFactory* newFactory);

		// The slots, in the order of core::IFile
		virtual void AddRef();
		virtual void Release();
		virtual int Read(void* buffer, unsigned int size, int option);
		virtual int Write(const void* buffer, unsigned int size, int option);
		virtual int SetPosition(unsigned int position);
		virtual int GetPosition(unsigned int* position);
		virtual int GetSize(unsigned int* size);
		virtual int Commit();
		virtual void ReadWait(void* buffer, unsigned int size, int option);
		virtual void WriteWait(const void* buffer, unsigned int size, int option);
		virtual void SetPositionWait(unsigned int position);
		virtual void GetPositionWait(unsigned int* position);
		virtual void GetSizeWait(unsigned int* size);
		virtual void CommitWait();
		virtual unsigned int GetCurrentSize();
		virtual int GetGranularity();
		virtual int Cancel();
		virtual int Notify(core::IFileCompletionCallback* callback, void* userData);
		virtual int Signal(void* signalEvent);
		virtual bool IsIdle();
		virtual void Wait();
		virtual void WaitSignal();
		virtual int GetError();
		virtual bool IsOpen();
		virtual const char* GetName();
		virtual const char* GetPath();
		virtual int GetDriveId();
		virtual void SetUnused(int value);
		virtual int GetKey();
		virtual bool GetFlag();
		virtual void SetField12C(unsigned int value);

		CompressedFileFactory* factory;
		int passthrough;
		core::IFile* inner;
		unsigned int innerSize;
		unsigned int unpackedSize;
		unsigned int unknown18;
		unsigned int unknown1C;
		unsigned int unknown20;
		unsigned int start;
		unsigned int secondStart;
		unsigned int half;
		unsigned int unknown30;
		unsigned int unknown34;
		unsigned int unknown38;
		unsigned int unknown3C;
		int heap;
		void* decompressor;
		long event[2];
		volatile long refCount;
	};
}

#endif
