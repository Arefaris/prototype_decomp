// A path as the engine's code passes it to the file system when it comes from a variable: a small class that holds the
// pointer and has a copy constructor of its own, so that the callers copy it into the argument slot (the file system's
// entry point takes it by value; the one with the plain pointer is the same entry point). The name is a guess.
#ifndef CORE_FILE_FILEPATH_H
#define CORE_FILE_FILEPATH_H

#include "code/core/file/filesystem.h"

namespace core
{
	class FilePath
	{
	public:
		FilePath(const char* newPath) :
			path(newPath)
		{
		}
		FilePath(const FilePath& other) :
			path(other.path)
		{
		}

		const char* path;
	};

	// The same entry point as FileSystemOpenFile (0x10643C60)
	void FileSystemOpenFile(IFile** file, FilePath path, bool writable, int mode, int key, int unused1, int unused2,
		int unused3, int option);
}

#endif
