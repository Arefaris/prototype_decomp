// core::Request and its file / drive request classes (RTTI names; vftables 0x10E4787C - 0x10E47C04): the work items
// the drives execute. Requests come from one pool (0x114-byte blocks, "FileRequest") under one lock; every request
// class constructor ends with CoreName(). Unit 0x1064C4A0 - 0x1064DF2B (file name file/common/request.cpp guessed,
// next to the asserted file/common/file.cpp). Method and member names guessed from what the slots do.
#ifndef CORE_FILE_REQUEST_H
#define CORE_FILE_REQUEST_H

#include "code/core/file/file.h"

namespace core
{
	const char* CoreName();


	class Request
	{
	public:
		Request();
		virtual ~Request();
		// The work; the result code (1 success, 3 queued)
		virtual int Execute() = 0;
		// Whether the request belongs to the given file or drive instance
		virtual bool IsFor(void* owner) = 0;
		virtual Drive* GetDrive() = 0;
		// Readies the drive before Execute (1 when there is nothing to do)
		virtual int Prepare() = 0;
		virtual const char* GetPath() = 0;
		virtual int GetType() = 0;

		static void* operator new(unsigned int size);
		static void operator delete(void* block);

		Request* next;
	};

	// Sets up / tears down the request pool and its lock
	void InitRequests(unsigned int count, int heap);
	void ShutdownRequests();

	// Releases a semaphore when executed
	class CompletionEventRequest : public Request
	{
	public:
		CompletionEventRequest(void* semaphore, Drive* drive);
		virtual ~CompletionEventRequest();
		virtual int Execute();
		virtual bool IsFor(void* owner);
		virtual Drive* GetDrive();
		virtual int Prepare();
		virtual const char* GetPath();
		virtual int GetType();

		void* semaphore;
		Drive* drive;
	};

	class CompletionCallbackRequest : public Request
	{
	public:
		CompletionCallbackRequest(int value);
		virtual bool IsFor(void* owner);
		virtual int Prepare();
		virtual const char* GetPath();
		// Runs the callback once the drive has handled the request
		virtual void Complete() = 0;

		// Whether the request was made on the given thread (Drive::Update completes only the caller's)
		bool IsFromThread(int thread);

		int value;
	};

	class FileCompletionRequest : public CompletionCallbackRequest
	{
	public:
		FileCompletionRequest(int value, File* file, IFileCompletionCallback* callback, void* userData);
		virtual ~FileCompletionRequest();
		virtual int Execute();
		virtual Drive* GetDrive();
		virtual int GetType();
		virtual void Complete();

		File* file;
		IFileCompletionCallback* callback;
		void* userData;
	};

	class DriveCompletionRequest : public CompletionCallbackRequest
	{
	public:
		DriveCompletionRequest(int value, InstanceDrive* instance, IFileCompletionCallback* callback, void* userData);
		virtual ~DriveCompletionRequest();
		virtual int Execute();
		virtual Drive* GetDrive();
		virtual int GetType();
		virtual void Complete();

		InstanceDrive* instance;
		IFileCompletionCallback* callback;
		void* userData;
	};

	class FileRequest : public Request
	{
	public:
		FileRequest(File* file);
		virtual ~FileRequest();
		virtual bool IsFor(void* owner);
		virtual Drive* GetDrive();
		virtual int Prepare();
		virtual const char* GetPath();

		// Stores the drive error in the file and passes the result through
		int Finish(int result, int error);

		File* file;
	};

	class FileOpenRequest : public FileRequest
	{
	public:
		FileOpenRequest(File* file, int mode, bool flag, int option);
		virtual ~FileOpenRequest();
		virtual int Execute();
		virtual int GetType();

		// Opens the file on the handle of a cached one (inlined twice into Execute)
		__forceinline int OpenShared()
		{
			if (file->writable || mode == 3)
			{
				file->cache.Reset();
				return Finish(0, 8);
			}
			File* source = file->cache.GetSource();
			if (!file->CanShare(source->drive))
			{
				file->cache.Reset();
				return Finish(0, 8);
			}
			file->handle = source->handle;
			file->size = file->cache.GetSize();
			file->open = true;
			file->granularity = source->granularity;
			return Finish(1, 0);
		}

		int mode;
		bool flag;
		int option;
	};

	class FileOpenByKeyRequest : public FileRequest
	{
	public:
		FileOpenByKeyRequest(File* file, int key, CementLibrary* library);
		virtual ~FileOpenByKeyRequest();
		virtual int Execute();
		virtual int GetType();

		int key;
		CementLibrary* table;
	};

	class SaveGameOpenRequest : public FileRequest
	{
	public:
		SaveGameOpenRequest(File* file, int mode, bool flag, int a, int b);
		virtual ~SaveGameOpenRequest();
		virtual int Execute();
		virtual int GetType();

		int mode;
		bool flag;
		int a;
		int b;
	};

	class FileCloseRequest : public FileRequest
	{
	public:
		FileCloseRequest(File* file);
		virtual ~FileCloseRequest();
		virtual int Execute();
		virtual int Prepare();
		virtual int GetType();
	};

	class FileCommitRequest : public FileRequest
	{
	public:
		FileCommitRequest(File* file);
		virtual ~FileCommitRequest();
		virtual int Execute();
		virtual int GetType();
	};

	class FileReadRequest : public FileRequest
	{
	public:
		FileReadRequest(File* file, void* buffer, unsigned int size, int option);
		virtual ~FileReadRequest();
		virtual int Execute();
		virtual int GetType();

		void* buffer;
		unsigned int size;
		int option;
	};

	class FileWriteRequest : public FileRequest
	{
	public:
		FileWriteRequest(File* file, const void* buffer, unsigned int size, int option);
		virtual ~FileWriteRequest();
		virtual int Execute();
		virtual int GetType();

		const void* buffer;
		unsigned int size;
		int option;
	};

	class FileSetPositionRequest : public FileRequest
	{
	public:
		FileSetPositionRequest(File* file, unsigned int position);
		virtual ~FileSetPositionRequest();
		virtual int Execute();
		virtual int GetType();

		unsigned int position;
	};

	class FileGetPositionRequest : public FileRequest
	{
	public:
		FileGetPositionRequest(File* file, unsigned int* position);
		virtual ~FileGetPositionRequest();
		virtual int Execute();
		virtual int GetType();

		unsigned int* position;
	};

	class FileGetSizeRequest : public FileRequest
	{
	public:
		FileGetSizeRequest(File* file, unsigned int* size);
		virtual ~FileGetSizeRequest();
		virtual int Execute();
		virtual int GetType();

		unsigned int* size;
	};

	class FileCancelRequest : public FileRequest
	{
	public:
		FileCancelRequest(File* file);
		virtual ~FileCancelRequest();
		virtual int Execute();
		virtual int Prepare();
		virtual int GetType();
	};

	class DriveRequest : public Request
	{
	public:
		DriveRequest(InstanceDrive* instance);
		virtual ~DriveRequest();
		virtual bool IsFor(void* owner);
		virtual Drive* GetDrive();
		virtual int Prepare();
		virtual const char* GetPath();

		// Stores the drive error in the instance and passes the result through
		int Finish(int result, int error);

		InstanceDrive* instance;
	};

	class DriveOpenRequest : public DriveRequest
	{
	public:
		DriveOpenRequest(InstanceDrive* instance);
		virtual ~DriveOpenRequest();
		virtual int Execute();
		virtual int Prepare();
		virtual int GetType();
	};

	class DriveMediaRequest : public DriveRequest
	{
	public:
		DriveMediaRequest(InstanceDrive* instance, DriveInfo* info);
		virtual ~DriveMediaRequest();
		virtual int Execute();
		virtual int Prepare();
		virtual int GetType();

		DriveInfo* info;
	};

	class DriveCanCreateFileRequest : public DriveRequest
	{
	public:
		DriveCanCreateFileRequest(InstanceDrive* instance, int a, int b, int* result);
		virtual ~DriveCanCreateFileRequest();
		virtual int Execute();
		virtual int Prepare();
		virtual int GetType();

		int a;
		int b;
		int* result;
	};

	class DriveFormatRequest : public DriveRequest
	{
	public:
		DriveFormatRequest(InstanceDrive* instance);
		virtual ~DriveFormatRequest();
		virtual int Execute();
		virtual int Prepare();
		virtual int GetType();
	};

	// The requests that carry a path (256 characters, always terminated)
	class DriveCreateDirectoryRequest : public DriveRequest
	{
	public:
		DriveCreateDirectoryRequest(InstanceDrive* instance, const char* path);
		virtual ~DriveCreateDirectoryRequest();
		virtual int Execute();
		virtual const char* GetPath();
		virtual int GetType();

		char path[0x101];
	};

	class DriveDestroyDirectoryRequest : public DriveRequest
	{
	public:
		DriveDestroyDirectoryRequest(InstanceDrive* instance, const char* path);
		virtual ~DriveDestroyDirectoryRequest();
		virtual int Execute();
		virtual const char* GetPath();
		virtual int GetType();

		char path[0x101];
	};

	class DriveFindFirstRequest : public DriveRequest
	{
	public:
		DriveFindFirstRequest(InstanceDrive* instance, const char* path, int flags);
		virtual ~DriveFindFirstRequest();
		virtual int Execute();
		virtual const char* GetPath();
		virtual int GetType();

		char path[0x101];
		int flags;
	};

	class DriveFindNextRequest : public DriveRequest
	{
	public:
		DriveFindNextRequest(InstanceDrive* instance, void* data);
		virtual ~DriveFindNextRequest();
		virtual int Execute();
		virtual int GetType();

		void* data;
	};

	class DriveFindCloseRequest : public DriveRequest
	{
	public:
		DriveFindCloseRequest(InstanceDrive* instance);
		virtual ~DriveFindCloseRequest();
		virtual int Execute();
		virtual int Prepare();
		virtual int GetType();
	};

	class DriveFileDestroyRequest : public DriveRequest
	{
	public:
		DriveFileDestroyRequest(InstanceDrive* instance, const char* path);
		virtual ~DriveFileDestroyRequest();
		virtual int Execute();
		virtual const char* GetPath();
		virtual int GetType();

		char path[0x101];
	};

	class DriveCancelRequest : public DriveRequest
	{
	public:
		DriveCancelRequest(InstanceDrive* instance);
		virtual ~DriveCancelRequest();
		virtual int Execute();
		virtual int Prepare();
		virtual int GetType();
	};
}

#endif
