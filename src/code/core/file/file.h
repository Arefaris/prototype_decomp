// core::File (vftables 0x10E47C84 / 0x10E47C78) and core::InstanceDrive (0x10E47D2C / 0x10E47D1C), RTTI names, as
// the file requests see them: the interface slots they call, the fields they touch (offsets from the requests'
// code; the rest is padding) and the non-virtual methods. Not reconstructed yet (0x1064DF30 - 0x1064F760);
// placeholder slots keep the numbering. Field names guessed.
#ifndef CORE_FILE_FILE_H
#define CORE_FILE_FILE_H

#include "code/core/file/drive.h"

namespace core
{
	// core::IFile (33 slots)
	struct IFile
	{
		virtual void AddRef() = 0;
		virtual void Release() = 0;
		virtual ~IFile();
		virtual void Slot3() = 0;
		virtual void Slot4() = 0;
		virtual void Slot5() = 0;
		virtual void Slot6() = 0;
		virtual void Slot7() = 0;
		virtual void Slot8() = 0;
		virtual void Slot9() = 0;
		virtual void Slot10() = 0;
		virtual void Slot11() = 0;
		virtual void Slot12() = 0;
		virtual void Slot13() = 0;
		virtual void Slot14() = 0;
		virtual void Slot15() = 0;
		virtual void Slot16() = 0;
		virtual void Slot17() = 0;
		virtual void Slot18() = 0;
		virtual void Slot19() = 0;
		virtual void Slot20() = 0;
		virtual void Slot21() = 0;
		virtual void Slot22() = 0;
		virtual void Slot23() = 0;
		virtual void Slot24() = 0;
		virtual void Slot25() = 0;
		virtual const char* GetPath() = 0;
		virtual void Slot27() = 0;
		virtual void Slot28() = 0;
		virtual void Slot29() = 0;
		virtual void Slot30() = 0;
		virtual void Slot31() = 0;
		virtual void Slot32() = 0;
	};

	// The read cache inside a file (0x30 bytes at +0x138); methods at 0x10650AB0 - 0x106511C0
	class FileCache
	{
	public:
		// 0x10650E10
		bool IsActive();
		// 0x10650E20: the file whose handle the cache shares
		class File* GetSource();
		// 0x10650E40
		unsigned int GetSize();
		// 0x10650E50
		void Reset();
		// 0x10650CF0: whether this cache holds `path` (and then attaches `target` to it)
		bool Matches(const char* path, FileCache* target);
		// 0x106511C0
		int Read(Drive* drive, int handle, const char* path, unsigned int a, unsigned int position, void* buffer, unsigned int size, unsigned int* done, int b);

		unsigned char data[0x30];
	};

	// The drive's list of file caches, walked in two passes (0x10650640 - 0x10650670)
	class FileCacheList
	{
	public:
		void Begin(int pass);
		FileCache* Next();
		void End();
	};

	// The reference-counted table an open-by-key request looks its file up in
	class FileKeyTable
	{
	public:
		virtual void AddRef() = 0;
		virtual void Release() = 0;

		// 0x10650AB0
		bool Find(int key, FileCache* cache);
	};

	class File : public IFile, public IMutable
	{
	public:
		// 0x1064E790: whether this file may share the handle of a file on `drive`
		bool CanShare(Drive* drive);
		// 0x1064E7F0 / 0x1064E810: a request starts / ends on this file
		void BeginRequest();
		void EndRequest();

		int field8;
		Drive* drive;
		int key;
		int error;
		unsigned char pad18[0x0E];
		bool open;
		bool writable;
		char path[0x104];
		unsigned int field12C;
		unsigned int position;
		unsigned int size;
		FileCache cache;
		int handle;
		int field16C;
		int field170;
	};

	// core::IDrive (45 slots)
	struct IDrive
	{
		virtual void AddRef() = 0;
		virtual void Release() = 0;
		virtual ~IDrive();
	};

	class InstanceDrive : public IDrive, public IMutable
	{
	public:
		// 0x1064F6B0 / 0x1064F6D0: a request starts / ends on this drive instance
		void BeginRequest();
		void EndRequest();

		int field8;
		Drive* drive;
		int key;
		unsigned char pad14[0x10];
		int error;
		int findHandle;
		bool searching;
	};
}

#endif
