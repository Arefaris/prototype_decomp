#define _CRT_SECURE_NO_DEPRECATE

#include <string.h>

#include "code/core/criticalsection.h"
#include "code/core/file/cementlibrary.h"
#include "code/core/file/request.h"
#include "code/core/memory/memorypool.h"

namespace core
{
	// The pool the requests come from and its lock
	// GLOBAL: ENGINE 0x1127CA44
	static int sRequestLock[6];
	// GLOBAL: ENGINE 0x1127CA5C
	static MemoryPool* sRequestPool;

	// FUNCTION: ENGINE 0x1064C4A0
	void InitRequests(unsigned int count, int heap)
	{
		CriticalSectionInit(sRequestLock);
		CreateMemoryPool(&sRequestPool, 0x114, count, heap, "FileRequest", 16);
		sRequestPool->SetSafetyMode(0);
	}

	// FUNCTION: ENGINE 0x1064C4E0
	void* Request::operator new(unsigned int size)
	{
		CriticalSectionEnter(sRequestLock);
		void* block = sRequestPool->AllocBlock();
		CriticalSectionLeave(sRequestLock);
		return block;
	}

	// FUNCTION: ENGINE 0x1064C510
	void Request::operator delete(void* block)
	{
		CriticalSectionEnter(sRequestLock);
		sRequestPool->Free(block);
		CriticalSectionLeave(sRequestLock);
	}

	// FUNCTION: ENGINE 0x1064C540
	Request::~Request()
	{
	}

	// FUNCTION: ENGINE 0x1064C550
	CompletionEventRequest::~CompletionEventRequest()
	{
		drive->Release();
	}

	// FUNCTION: ENGINE 0x1064C570
	int CompletionEventRequest::Execute()
	{
		SemaphoreRelease(semaphore, 1);
		return 1;
	}

	// FUNCTION: ENGINE 0x1064C590
	bool CompletionEventRequest::IsFor(void* owner)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x1064C5A0
	Drive* CompletionEventRequest::GetDrive()
	{
		return drive;
	}

	// FUNCTION: ENGINE 0x1064C5B0
	int CompletionEventRequest::Prepare()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1064C5C0
	const char* CompletionEventRequest::GetPath()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1064C5D0
	int CompletionEventRequest::GetType()
	{
		return 0x17;
	}

	// FUNCTION: ENGINE 0x1064C5F0
	bool CompletionCallbackRequest::IsFor(void* owner)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x1064C600
	bool CompletionCallbackRequest::IsFromThread(int thread)
	{
		return thread == value;
	}

	// FUNCTION: ENGINE 0x1064C610
	int CompletionCallbackRequest::Prepare()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1064C620
	const char* CompletionCallbackRequest::GetPath()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1064C630
	FileCompletionRequest::~FileCompletionRequest()
	{
		callback->Release();
		file->Release();
	}

	// FUNCTION: ENGINE 0x1064C660
	int FileCompletionRequest::Execute()
	{
		file->drive->Queue(this);
		return 3;
	}

	// FUNCTION: ENGINE 0x1064C680
	void FileCompletionRequest::Complete()
	{
		file->EndRequest();
		callback->OnComplete(userData);
	}

	// FUNCTION: ENGINE 0x1064C6A0
	Drive* FileCompletionRequest::GetDrive()
	{
		return file->drive;
	}

	// FUNCTION: ENGINE 0x1064C6B0
	int FileCompletionRequest::GetType()
	{
		return 10;
	}

	// FUNCTION: ENGINE 0x1064C6C0
	DriveCompletionRequest::~DriveCompletionRequest()
	{
		callback->Release();
		instance->Release();
	}

	// FUNCTION: ENGINE 0x1064C6F0
	int DriveCompletionRequest::Execute()
	{
		instance->drive->Queue(this);
		return 3;
	}

	// FUNCTION: ENGINE 0x1064C710
	void DriveCompletionRequest::Complete()
	{
		instance->EndRequest();
		callback->OnComplete(userData);
	}

	// FUNCTION: ENGINE 0x1064C730
	Drive* DriveCompletionRequest::GetDrive()
	{
		return instance->drive;
	}

	// FUNCTION: ENGINE 0x1064C740
	int DriveCompletionRequest::GetType()
	{
		return 0x16;
	}

	// FUNCTION: ENGINE 0x1064C750
	FileRequest::~FileRequest()
	{
		file->EndRequest();
		file->Release();
	}

	// FUNCTION: ENGINE 0x1064C780
	int FileRequest::Finish(int result, int value)
	{
		file->Lock();
		file->error = value;
		file->Unlock();
		return result;
	}

	// FUNCTION: ENGINE 0x1064C7B0
	bool FileRequest::IsFor(void* owner)
	{
		return owner == file;
	}

	// FUNCTION: ENGINE 0x1064C7C0
	Drive* FileRequest::GetDrive()
	{
		return file->drive;
	}

	// FUNCTION: ENGINE 0x1064C7D0
	int FileRequest::Prepare()
	{
		Drive* drive = file->drive;
		int result = drive->Mount();
		return Finish(result, drive->GetError());
	}

	// FUNCTION: ENGINE 0x1064C800
	const char* FileRequest::GetPath()
	{
		return file->GetPath();
	}

	// FUNCTION: ENGINE 0x1064C810
	FileOpenRequest::~FileOpenRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064C820
	// Opens the file from a Cement library of the drive's list 0 when one holds it, on the drive otherwise; list 1
	// follows a failed (or skipped, option 1) open
	int FileOpenRequest::Execute()
	{
		Drive* drive = file->drive;
		CementLibraryList* libraries = drive->GetLibraries();
		libraries->Begin(0);
		for (CementLibrary* library = libraries->Next(); library != 0; library = libraries->Next())
		{
			if (library->Matches(file->path, &file->cache))
			{
				libraries->End();
				return OpenShared();
			}
		}
		libraries->End();
		int result = 0;
		if (option == 1)
		{
			drive->SetState(1);
		}
		else
		{
			result = drive->Open(file->path, mode, flag, &file->handle, &file->size);
			if (result == 1)
			{
				file->open = true;
				file->granularity = drive->GetInfo()->data[3];
				return Finish(result, drive->GetError());
			}
		}
		libraries->Begin(1);
		for (CementLibrary* library = libraries->Next(); library != 0; library = libraries->Next())
		{
			if (library->Matches(file->path, &file->cache))
			{
				libraries->End();
				return OpenShared();
			}
		}
		libraries->End();
		return Finish(result, drive->GetError());
	}

	// FUNCTION: ENGINE 0x1064CAB0
	int FileOpenRequest::GetType()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1064CAC0
	FileOpenByKeyRequest::~FileOpenByKeyRequest()
	{
		table->Release();
	}

	// FUNCTION: ENGINE 0x1064CAE0
	int FileOpenByKeyRequest::Execute()
	{
		Drive* drive = file->drive;
		if (table->Find(key, &file->cache))
		{
			if (file->writable)
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
		drive->SetState(1);
		return Finish(0, 1);
	}

	// FUNCTION: ENGINE 0x1064CBB0
	int FileOpenByKeyRequest::GetType()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1064CBC0
	SaveGameOpenRequest::~SaveGameOpenRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064CBD0
	int SaveGameOpenRequest::Execute()
	{
		Drive* drive = file->drive;
		int result = drive->OpenSaveGame(file->path, mode, flag, a, b, &file->handle, &file->size);
		if (result == 1)
		{
			file->open = true;
			file->granularity = drive->GetInfo()->data[3];
		}
		return Finish(result, drive->GetError());
	}

	// FUNCTION: ENGINE 0x1064CC40
	int SaveGameOpenRequest::GetType()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1064CC50
	FileCloseRequest::~FileCloseRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064CC60
	int FileCloseRequest::Prepare()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1064CC70
	int FileCloseRequest::Execute()
	{
		Drive* drive = file->drive;
		if (!file->cache.IsActive())
		{
			drive->Close(file->handle, file->path);
		}
		else
		{
			file->cache.Reset();
		}
		file->open = false;
		return Finish(1, 0);
	}

	// FUNCTION: ENGINE 0x1064CCD0
	int FileCloseRequest::GetType()
	{
		return 2;
	}

	// FUNCTION: ENGINE 0x1064CCE0
	FileCommitRequest::~FileCommitRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064CCF0
	int FileCommitRequest::Execute()
	{
		Drive* drive = file->drive;
		int result = drive->Commit(file->handle, file->path);
		return Finish(result, drive->GetError());
	}

	// FUNCTION: ENGINE 0x1064CD30
	int FileCommitRequest::GetType()
	{
		return 3;
	}

	// FUNCTION: ENGINE 0x1064CD40
	FileReadRequest::~FileReadRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064CD50
	// Reads up to the end of the file rounded to the drive's granularity, through the cache when it is active
	int FileReadRequest::Execute()
	{
		unsigned int done;
		unsigned int fileSize = file->size;
		Drive* drive = file->drive;
		unsigned int count = size;
		if (file->position >= fileSize)
		{
			count = 0;
		}
		unsigned int limit = RoundUp(fileSize, drive->GetInfo()->data[3]);
		if (file->position + count > limit)
		{
			count = limit - file->position;
		}
		int result;
		if (count > 0)
		{
			if (file->cache.IsActive())
			{
				result = file->cache.Read(drive, file->handle, file->path, file->field12C, file->position, buffer, count, &done, option);
			}
			else
			{
				result = drive->Read(file->handle, file->path, file->field12C, file->position, buffer, count, &done, option);
			}
			if (result == 1)
			{
				file->position += done;
			}
		}
		else
		{
			result = 1;
		}
		return Finish(result, drive->GetError());
	}

	// FUNCTION: ENGINE 0x1064CE50
	int FileReadRequest::GetType()
	{
		return 4;
	}

	// FUNCTION: ENGINE 0x1064CE60
	FileWriteRequest::~FileWriteRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064CE70
	int FileWriteRequest::Execute()
	{
		if (!file->writable)
		{
			return Finish(0, 8);
		}
		unsigned int done;
		Drive* drive = file->drive;
		int result;
		if (size > 0)
		{
			result = drive->Write(file->handle, file->path, file->field12C, file->position, buffer, size, &done, &file->size, option);
			if (result == 1)
			{
				file->position += done;
			}
		}
		else
		{
			result = 1;
		}
		return Finish(result, drive->GetError());
	}

	// FUNCTION: ENGINE 0x1064CF00
	int FileWriteRequest::GetType()
	{
		return 5;
	}

	// FUNCTION: ENGINE 0x1064CF10
	FileSetPositionRequest::~FileSetPositionRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064CF20
	// A file that cannot be written stops at its end
	int FileSetPositionRequest::Execute()
	{
		if (!file->writable && position > file->size)
		{
			position = file->size;
		}
		file->position = position;
		return Finish(1, 0);
	}

	// FUNCTION: ENGINE 0x1064CF50
	int FileSetPositionRequest::GetType()
	{
		return 6;
	}

	// FUNCTION: ENGINE 0x1064CF60
	FileGetPositionRequest::~FileGetPositionRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064CF70
	int FileGetPositionRequest::Execute()
	{
		*position = file->position;
		return Finish(1, 0);
	}

	// FUNCTION: ENGINE 0x1064CF90
	int FileGetPositionRequest::GetType()
	{
		return 7;
	}

	// FUNCTION: ENGINE 0x1064CFA0
	FileGetSizeRequest::~FileGetSizeRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064CFB0
	int FileGetSizeRequest::Execute()
	{
		*size = file->size;
		return Finish(1, 0);
	}

	// FUNCTION: ENGINE 0x1064CFD0
	int FileGetSizeRequest::GetType()
	{
		return 8;
	}

	// FUNCTION: ENGINE 0x1064CFE0
	FileCancelRequest::~FileCancelRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064CFF0
	int FileCancelRequest::Execute()
	{
		file->drive->CancelRequests(file, file->key);
		return Finish(1, 0);
	}

	// FUNCTION: ENGINE 0x1064D010
	int FileCancelRequest::Prepare()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1064D020
	int FileCancelRequest::GetType()
	{
		return 9;
	}

	// FUNCTION: ENGINE 0x1064D030
	DriveRequest::~DriveRequest()
	{
		instance->EndRequest();
		instance->Release();
	}

	// FUNCTION: ENGINE 0x1064D060
	int DriveRequest::Finish(int result, int value)
	{
		instance->Lock();
		instance->error = value;
		instance->Unlock();
		return result;
	}

	// FUNCTION: ENGINE 0x1064D090
	bool DriveRequest::IsFor(void* owner)
	{
		return owner == instance;
	}

	// FUNCTION: ENGINE 0x1064D0A0
	Drive* DriveRequest::GetDrive()
	{
		return instance->drive;
	}

	// FUNCTION: ENGINE 0x1064D0B0
	int DriveRequest::Prepare()
	{
		Drive* drive = instance->drive;
		int result = drive->Mount();
		return Finish(result, drive->GetError());
	}

	// FUNCTION: ENGINE 0x1064D0E0
	const char* DriveRequest::GetPath()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1064D0F0
	DriveOpenRequest::~DriveOpenRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064D100
	int DriveOpenRequest::Execute()
	{
		Drive* drive = instance->drive;
		int result = drive->Mount();
		return Finish(result, drive->GetError());
	}

	// FUNCTION: ENGINE 0x1064D130
	int DriveOpenRequest::Prepare()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1064D140
	int DriveOpenRequest::GetType()
	{
		return 0xB;
	}

	// FUNCTION: ENGINE 0x1064D150
	DriveMediaRequest::~DriveMediaRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064D160
	int DriveMediaRequest::Execute()
	{
		Drive* drive = instance->drive;
		drive->Mount();
		*info = *drive->GetInfo();
		return Finish(1, 0);
	}

	// FUNCTION: ENGINE 0x1064D1A0
	int DriveMediaRequest::Prepare()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1064D1B0
	int DriveMediaRequest::GetType()
	{
		return 0xC;
	}

	// FUNCTION: ENGINE 0x1064D1C0
	DriveCanCreateFileRequest::~DriveCanCreateFileRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064D1D0
	int DriveCanCreateFileRequest::Execute()
	{
		*result = instance->drive->CanCreateFile(a, b);
		return Finish(1, 0);
	}

	// FUNCTION: ENGINE 0x1064D200
	int DriveCanCreateFileRequest::Prepare()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1064D210
	int DriveCanCreateFileRequest::GetType()
	{
		return 0xD;
	}

	// FUNCTION: ENGINE 0x1064D220
	DriveFormatRequest::~DriveFormatRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064D230
	int DriveFormatRequest::Execute()
	{
		Drive* drive = instance->drive;
		int result = drive->Format();
		return Finish(result, drive->GetError());
	}

	// FUNCTION: ENGINE 0x1064D260
	int DriveFormatRequest::GetType()
	{
		return 0xE;
	}

	// FUNCTION: ENGINE 0x1064D270
	int DriveFormatRequest::Prepare()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1064D280
	DriveCreateDirectoryRequest::~DriveCreateDirectoryRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064D290
	int DriveCreateDirectoryRequest::Execute()
	{
		Drive* drive = instance->drive;
		int result = drive->CreateDirectory(path);
		return Finish(result, drive->GetError());
	}

	// FUNCTION: ENGINE 0x1064D2C0
	const char* DriveCreateDirectoryRequest::GetPath()
	{
		return path;
	}

	// FUNCTION: ENGINE 0x1064D2D0
	int DriveCreateDirectoryRequest::GetType()
	{
		return 0xF;
	}

	// FUNCTION: ENGINE 0x1064D2E0
	DriveDestroyDirectoryRequest::~DriveDestroyDirectoryRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064D2F0
	int DriveDestroyDirectoryRequest::Execute()
	{
		Drive* drive = instance->drive;
		int result = drive->DestroyDirectory(path);
		return Finish(result, drive->GetError());
	}

	// FUNCTION: ENGINE 0x1064D320
	const char* DriveDestroyDirectoryRequest::GetPath()
	{
		return path;
	}

	// FUNCTION: ENGINE 0x1064D330
	int DriveDestroyDirectoryRequest::GetType()
	{
		return 0x10;
	}

	// FUNCTION: ENGINE 0x1064D340
	DriveFindFirstRequest::~DriveFindFirstRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064D350
	int DriveFindFirstRequest::Execute()
	{
		Drive* drive = instance->drive;
		int result = drive->FindFirst(path, flags, &instance->findHandle, !instance->searching);
		if (result == 1)
		{
			instance->searching = true;
			return Finish(result, drive->GetError());
		}
		instance->searching = false;
		return Finish(result, drive->GetError());
	}

	// FUNCTION: ENGINE 0x1064D3C0
	const char* DriveFindFirstRequest::GetPath()
	{
		return path;
	}

	// FUNCTION: ENGINE 0x1064D3D0
	int DriveFindFirstRequest::GetType()
	{
		return 0x11;
	}

	// FUNCTION: ENGINE 0x1064D3E0
	DriveFindNextRequest::~DriveFindNextRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064D3F0
	int DriveFindNextRequest::Execute()
	{
		Drive* drive = instance->drive;
		int result = drive->FindNext(&instance->findHandle, data);
		return Finish(result, drive->GetError());
	}

	// FUNCTION: ENGINE 0x1064D430
	int DriveFindNextRequest::GetType()
	{
		return 0x12;
	}

	// FUNCTION: ENGINE 0x1064D440
	DriveFindCloseRequest::~DriveFindCloseRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064D450
	int DriveFindCloseRequest::Execute()
	{
		Drive* drive = instance->drive;
		instance->searching = false;
		drive->FindClose(&instance->findHandle);
		return Finish(1, 0);
	}

	// FUNCTION: ENGINE 0x1064D480
	int DriveFindCloseRequest::Prepare()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1064D490
	int DriveFindCloseRequest::GetType()
	{
		return 0x13;
	}

	// FUNCTION: ENGINE 0x1064D4A0
	DriveFileDestroyRequest::~DriveFileDestroyRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064D4B0
	int DriveFileDestroyRequest::Execute()
	{
		Drive* drive = instance->drive;
		int result = drive->DestroyFile(path);
		return Finish(result, drive->GetError());
	}

	// FUNCTION: ENGINE 0x1064D4E0
	const char* DriveFileDestroyRequest::GetPath()
	{
		return path;
	}

	// FUNCTION: ENGINE 0x1064D4F0
	int DriveFileDestroyRequest::GetType()
	{
		return 0x14;
	}

	// FUNCTION: ENGINE 0x1064D500
	DriveCancelRequest::~DriveCancelRequest()
	{
	}

	// FUNCTION: ENGINE 0x1064D510
	int DriveCancelRequest::Execute()
	{
		instance->drive->CancelRequests(instance, instance->key);
		return Finish(1, 0);
	}

	// FUNCTION: ENGINE 0x1064D530
	int DriveCancelRequest::Prepare()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1064D540
	int DriveCancelRequest::GetType()
	{
		return 0x15;
	}

	// FUNCTION: ENGINE 0x1064D550
	// The statistic read before the pool goes is not used (a check compiled out)
	void ShutdownRequests()
	{
		CriticalSectionDelete(sRequestLock);
		int used = 0;
		sRequestPool->GetStat(0, &used);
		sRequestPool->Release();
		sRequestPool = 0;
	}

	// FUNCTION: ENGINE 0x1064D5A0
	Request::Request()
	{
		next = 0;
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064D5E0
	CompletionEventRequest::CompletionEventRequest(void* event, Drive* owner)
	{
		semaphore = event;
		drive = owner;
		CoreName();
		drive->AddRef();
	}

	// FUNCTION: ENGINE 0x1064D630
	CompletionCallbackRequest::CompletionCallbackRequest(int data)
	{
		value = data;
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064D670
	FileCompletionRequest::FileCompletionRequest(int data, File* target, IFileCompletionCallback* function, void* user)
		: CompletionCallbackRequest(data)
	{
		file = target;
		callback = function;
		userData = user;
		CoreName();
		callback->AddRef();
		file->BeginRequest();
		file->AddRef();
	}

	// FUNCTION: ENGINE 0x1064D6E0
	DriveCompletionRequest::DriveCompletionRequest(int data, InstanceDrive* target, IFileCompletionCallback* function, void* user)
		: CompletionCallbackRequest(data)
	{
		instance = target;
		callback = function;
		userData = user;
		CoreName();
		callback->AddRef();
		instance->BeginRequest();
		instance->AddRef();
	}

	// FUNCTION: ENGINE 0x1064D750
	FileRequest::FileRequest(File* target)
	{
		file = target;
		CoreName();
		file->BeginRequest();
		file->AddRef();
	}

	// FUNCTION: ENGINE 0x1064D7B0
	FileOpenRequest::FileOpenRequest(File* target, int value, bool option, int extra)
		: FileRequest(target)
	{
		mode = value;
		flag = option;
		this->option = extra;
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064D810
	FileOpenByKeyRequest::FileOpenByKeyRequest(File* target, int value, CementLibrary* keys)
		: FileRequest(target)
	{
		key = value;
		table = keys;
		CoreName();
		table->AddRef();
	}

	// FUNCTION: ENGINE 0x1064D870
	SaveGameOpenRequest::SaveGameOpenRequest(File* target, int value, bool option, int first, int second)
		: FileRequest(target)
	{
		mode = value;
		flag = option;
		a = first;
		b = second;
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064D8D0
	FileCloseRequest::FileCloseRequest(File* target)
		: FileRequest(target)
	{
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064D910
	FileCommitRequest::FileCommitRequest(File* target)
		: FileRequest(target)
	{
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064D950
	FileReadRequest::FileReadRequest(File* target, void* data, unsigned int count, int extra)
		: FileRequest(target)
	{
		buffer = data;
		size = count;
		option = extra;
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064D9B0
	FileWriteRequest::FileWriteRequest(File* target, const void* data, unsigned int count, int extra)
		: FileRequest(target)
	{
		buffer = data;
		size = count;
		option = extra;
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064DA10
	FileSetPositionRequest::FileSetPositionRequest(File* target, unsigned int value)
		: FileRequest(target)
	{
		position = value;
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064DA60
	FileGetPositionRequest::FileGetPositionRequest(File* target, unsigned int* out)
		: FileRequest(target)
	{
		position = out;
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064DAB0
	FileGetSizeRequest::FileGetSizeRequest(File* target, unsigned int* out)
		: FileRequest(target)
	{
		size = out;
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064DB00
	FileCancelRequest::FileCancelRequest(File* target)
		: FileRequest(target)
	{
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064DB40
	DriveRequest::DriveRequest(InstanceDrive* target)
	{
		instance = target;
		CoreName();
		instance->BeginRequest();
		instance->AddRef();
	}

	// FUNCTION: ENGINE 0x1064DBA0
	DriveOpenRequest::DriveOpenRequest(InstanceDrive* target)
		: DriveRequest(target)
	{
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064DBE0
	DriveMediaRequest::DriveMediaRequest(InstanceDrive* target, DriveInfo* out)
		: DriveRequest(target)
	{
		info = out;
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064DC30
	DriveCanCreateFileRequest::DriveCanCreateFileRequest(InstanceDrive* target, int first, int second, int* out)
		: DriveRequest(target)
	{
		a = first;
		b = second;
		result = out;
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064DC90
	DriveFormatRequest::DriveFormatRequest(InstanceDrive* target)
		: DriveRequest(target)
	{
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064DCD0
	DriveCreateDirectoryRequest::DriveCreateDirectoryRequest(InstanceDrive* target, const char* name)
		: DriveRequest(target)
	{
		CoreName();
		strncpy(path, name, 0x100);
		path[0x100] = 0;
	}

	// FUNCTION: ENGINE 0x1064DD30
	DriveDestroyDirectoryRequest::DriveDestroyDirectoryRequest(InstanceDrive* target, const char* name)
		: DriveRequest(target)
	{
		CoreName();
		strncpy(path, name, 0x100);
		path[0x100] = 0;
	}

	// FUNCTION: ENGINE 0x1064DD90
	DriveFindFirstRequest::DriveFindFirstRequest(InstanceDrive* target, const char* name, int value)
		: DriveRequest(target)
	{
		flags = value;
		CoreName();
		strncpy(path, name, 0x100);
		path[0x100] = 0;
	}

	// FUNCTION: ENGINE 0x1064DE00
	DriveFindNextRequest::DriveFindNextRequest(InstanceDrive* target, void* out)
		: DriveRequest(target)
	{
		data = out;
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064DE50
	DriveFindCloseRequest::DriveFindCloseRequest(InstanceDrive* target)
		: DriveRequest(target)
	{
		CoreName();
	}

	// FUNCTION: ENGINE 0x1064DE90
	DriveFileDestroyRequest::DriveFileDestroyRequest(InstanceDrive* target, const char* name)
		: DriveRequest(target)
	{
		CoreName();
		strncpy(path, name, 0x100);
		path[0x100] = 0;
	}

	// FUNCTION: ENGINE 0x1064DEF0
	DriveCancelRequest::DriveCancelRequest(InstanceDrive* target)
		: DriveRequest(target)
	{
		CoreName();
	}
}
