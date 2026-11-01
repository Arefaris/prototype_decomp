// The om library's file system interface (RTTI: om::FileSystem, implemented by om::AtgCoreFileSystem over the core
// module's drives) and the small file helpers over the host's file functions (names guessed).
#ifndef OM_FILESYSTEM_H
#define OM_FILESYSTEM_H

#include "code/om/stream.h"
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
		virtual ~FileSystem()
		{
		}
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
	// 0x105CB650: takes the read-only attribute off a file
	bool MakeFileWritable(const String& path);
	// 0x105CB930: calls the function with the path of every file below the directory of the root (the root's own files
	// when the directory is empty), directories first met in the order the host lists them; answers 0 when the search
	// or the function stopped, 1 when it went through all
	typedef bool (*FileVisitor)(const char* path, void* data);
	int VisitFiles(const String& root, const String& directory, FileVisitor visitor, void* data);
	// 0x105CBBB0: all the files below the root
	bool VisitAllFiles(const String& root, FileVisitor visitor, void* data);
	// 0x105CBBF0: the file name of a path
	String GetFileNameOf(const String& path);
	// 0x105CBC10: copies a file (making the directories) and takes the read-only attribute off the copy
	void CopyFileWritable(const String& destination, const String& source);
	// 0x105CBC40: makes an empty file (an existing one is only emptied when asked to)
	bool CreateEmptyFile(const String& path, bool overwrite);
	// 0x105CBD90: removes the files below a directory, reporting each to the streams
	struct FileRemovalLog
	{
		Stream* errors;
		Stream* unknown4;
		Stream* removed;
	};
	bool RemoveFilesBelow(const String& directory, FileRemovalLog* log);
	// 0x105E4150: the host's text for the last error
	bool GetLastErrorText(char* buffer, unsigned int size);
}

#endif
