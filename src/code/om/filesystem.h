// The om library's file system interface (RTTI: om::FileSystem, implemented by om::AtgCoreFileSystem over the core
// module's drives) and the small file helpers over the host's file functions (names guessed).
#ifndef OM_FILESYSTEM_H
#define OM_FILESYSTEM_H

#include "code/om/string.h"

namespace om
{
	// A time of the host's file system (a FILETIME)
	struct FileTime
	{
		unsigned int low;
		unsigned int high;
	};

	class FileSystem
	{
	public:
		// 0x105C1040
		FileSystem();
		// Slot 0 (0x105C1080): moves a file to a new place, making the directories and removing what is there
		virtual bool Rename(const String& source, const String& destination);
		// Slot 1: not recovered
		virtual void Slot1() = 0;
		// Slot 2 (0x105C1050 is the body, the deleting destructor 0x105C1060)
		virtual ~FileSystem();
		// Slot 3: not recovered
		virtual void Slot3() = 0;
	};

	// 0x105CAEF0 (path.cpp): brings the path into the engine's normal form
	String* NormalizePath(String* path);
	// 0x105CB4D0: makes every directory of the path
	bool CreateDirectories(const String& path);
	// 0x105CB6A0 / 0x105CB850 / 0x105CB8A0
	bool RenameFile(const String& source, const String& destination);
	bool FileExists(const String& path);
	bool RemoveFile(const String& path);
	// 0x105CB8D0: the time of the last write of a file (a FILETIME)
	bool GetFileWriteTime(const String& path, FileTime* time);
	// 0x105CB550: true unless both files exist and the first is not newer than the second
	bool IsFileNewer(const String& first, const String& second);
	// 0x105CB610: copies a file over another, making the directories
	bool CopyFileTo(const String& destination, const String& source);
}

#endif
