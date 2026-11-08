// content::CompressedFile (RTTI: a core::IFile, 0x54 bytes; the member names are guesses): a file whose data the
// decompression thread unpacks (the CompressedFileFactory in code/content/loadstream.cpp queues the reads). Reads go
// to the thread, the other calls to the file inside it.
#ifndef CONTENT_COMPRESSEDFILE_H
#define CONTENT_COMPRESSEDFILE_H

#include "code/compress/compress.h"
#include "code/core/file/file.h"
#include "code/core/thread.h"

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

	// The thread that unpacks compressed files (the object at 0x11276A98, 0xE4 bytes; names guessed): the requests are
	// queued one at a time and the thread works them off
	class CompressedFileFactory
	{
	public:
		// 0x1060BBF0 (the global's constructor)
		CompressedFileFactory();
		// 0x1060BE40: starts the thread (from the heap)
		void Start(int heap);
		// 0x1060BC20: stops it
		void Stop();
		// 0x1060BCE0: queues a request
		void Queue(DecompressRequest* request);
		// 0x1060BEA0: a file that reads the part of file inside through the buffers at start (size bytes), when the path
		// of file names a compressed file; the result stays null otherwise
		void Create(core::IFile** result, core::IFile* file, unsigned int start, unsigned int size, int heap);
		// 0x1060BC70: the same for a file whose data is known to be compressed with that level
		void Create(core::IFile** result, core::IFile* file, int level, unsigned int unpacked, unsigned int start,
			unsigned int size, int heap);
		// 0x1060BD40: the thread's loop; 0x1060BE30 is its entry
		void Run();
		static int ThreadMain(void* argument);

		core::Thread thread;
		void* semaphore;
		unsigned char lock[0x18];
		DecompressRequest request;
		int pending;
		bool stopRequested;
		bool started;
	};

	// 0x1060BBD0 / 0x1060DD90: whether a file name extension is the one of compressed files (".rz")
	bool IsCompressedExtension(const char* extension);
	int MatchesCompressedExtension(const char* extension);

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

		// 0x1060DE80: unpacks the next size bytes into the buffer (the thread calls it for every request)
		void Unpack(void* buffer, unsigned int size);
		// 0x1060DE30: reads the header of the packed data (its level and the size of the unpacked data) and makes the
		// decompressor
		void StartBlock();

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
		// The two buffers the file is read into (the unpacked part of the file is worked off from one while the other
		// fills); unknown3C says which one the data is taken from
		unsigned int buffers[2];
		unsigned int half;
		unsigned int unknown30;
		unsigned int unknown34;
		unsigned int unknown38;
		unsigned int unknown3C;
		int heap;
		compress::Stream* decompressor;
		long event[2];
		volatile long refCount;
	};
}

#endif
