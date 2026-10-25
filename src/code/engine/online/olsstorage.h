// engine::OLSStorage (RTTI name; an online services callback): the online services' global files (settings.txt,
// legal.txt, news.txt, faq.txt) that the game downloads into memory or loads from disk and uploads. The storage keeps
// one entry per file, works through the files that wait one at a time (a read or a write the platform's storage
// class starts and finishes through the services' messages) and tells the others about the results with an
// OLSStorageMessage. The reading and writing themselves are virtual functions of the platform's derived class (the
// base has them pure). Its script functions are ols_DownloadGlobalFile, ols_LoadAndUploadAllGlobalFiles,
// ols_LoadAndUploadGlobalFile, ols_ClearGlobalFile, ols_ReadGlobalFileLine and ols_IsGlobalFileAvailable. Unit
// 0x108C5950 - 0x108C6700 (no assert path; the file name is a guess). Names other than the RTTI and script names are
// guesses.
#ifndef ENGINE_ONLINE_OLSSTORAGE_H
#define ENGINE_ONLINE_OLSSTORAGE_H

#include "code/engine/online/ols.h"
#include "code/engine/online/onlinemanager.h"

namespace engine
{
	// The messages of the storage (message type 7; the id says what happened: 0 a read can start, 1 a download is done,
	// 2 an upload is done)
	struct OLSStorageMessage : public OLSMessage
	{
		// 0x108C5950
		explicit OLSStorageMessage(short newId) : OLSMessage(7, newId)
		{
		}
		// 0x108C5F40 is the deleting destructor
		virtual ~OLSStorageMessage()
		{
		}
		// 0x108C5980
		short GetId() const
		{
			return id;
		}
	};

	// What an entry of the storage is doing
	enum OLSStorageState
	{
		OLS_STORAGE_EMPTY,
		OLS_STORAGE_DOWNLOAD_WAITING,
		OLS_STORAGE_UPLOAD_WAITING,
		OLS_STORAGE_DOWNLOADING,
		OLS_STORAGE_UPLOADING,
		OLS_STORAGE_FAILED,
		OLS_STORAGE_READY
	};

	// One global file in memory (0x10 bytes)
	struct OLSStorageEntry
	{
		char* data;
		int size;
		int state;
		const char* name;
	};

	// The user of the downloaded settings (another unit, the global at 0x1130DC60): reads them out of the storage
	class OLSGlobalFileUser
	{
	public:
		// 0x10833C70
		void OnGlobalFile();
	};

	class OLSStorage : public OLS::Callback
	{
	public:
		// 0x108C66A0: the storage for count files; registers the script functions
		explicit OLSStorage(int newCount);
		// 0x108C5F60 (the deleting destructor 0x108C6380)
		virtual ~OLSStorage();
		static void operator delete(void* block)
		{
			FreeManagerObject(block);
		}

		// vftable slot 0 (0x108C5E20): follows the messages of the services
		virtual void OnMessage(OLSMessage* message);
		// Slot 2 (0x108C5FB0): joins the services' callbacks
		virtual void Register();
		// Slots 3 - 8: the platform's storage (pure here); slot 4 (0x108C5FE0) is the default of CloseHandle
		virtual int OpenRead(int unused, const char* name, int size) = 0;
		virtual void CloseHandle(int handle);
		virtual int GetSize(int handle) = 0;
		virtual void Read(int handle, void* buffer, int size) = 0;
		virtual void Slot7() = 0;
		virtual int OpenWrite(int unused, const char* name, void* data, int size) = 0;
		// Slots 9 - 16 (0x108C59A0, 0x108C59D0, 0x108C5D00, 0x108C5CD0, 0x108C5A00, 0x108C5A30, 0x108C60D0, 0x108C5FF0)
		virtual void DownloadAll();
		virtual void Download(int index);
		virtual void Clear(int index);
		virtual void ClearAll();
		virtual void LoadAndUploadAll();
		virtual void LoadAndUpload(int index);
		virtual void Queue(int index, const char* name, int size);
		virtual void LoadFile(int index, const char* path, int maxSize);

		// 0x108C5A60 / 0x108C5E00: whether the file is in memory, and its bytes
		bool IsAvailable(int index);
		char* GetData(int index);
		// 0x108C5D50: the line of the file that is asked for (the lines are read in order; the line is kept in a buffer)
		const char* ReadLine(int index, int line);
		// 0x108C5A80: starts the next file that waits
		void StartNext();
		// 0x108C5B40: the end of a write (failed: it did not work)
		void Finish(int failed);
		// 0x108C5BD0: the read can start
		void OnReadable();

		int count;  // +8
		OLSStorageEntry* entries;  // +0xC
		int current;  // +0x10: the entry that is being worked on, -1 none, -2 it failed
		int handle;  // +0x14
		int lineEntry;  // +0x18
		int lineNumber;  // +0x1C
		int lineOffset;  // +0x20
		char line[0x50];  // +0x24
	};
}

#endif
