// The om library's file system interface and file helpers (0x105C1040 - 0x105C10C0 and 0x105CB6A0 - 0x105CB92C).
#include "code/om/filesystem.h"
#include "code/om/path.h"
#include "code/om/stream.h"
#include <string.h>

// The kernel32 imports (see win32drive.cpp)
extern "C"
{
	struct _FILETIME
	{
		unsigned long dwLowDateTime;
		unsigned long dwHighDateTime;
	};

	struct _WIN32_FIND_DATAA
	{
		unsigned long dwFileAttributes;
		_FILETIME ftCreationTime;
		_FILETIME ftLastAccessTime;
		_FILETIME ftLastWriteTime;
		unsigned long nFileSizeHigh;
		unsigned long nFileSizeLow;
		unsigned long dwReserved0;
		unsigned long dwReserved1;
		char cFileName[260];
		char cAlternateFileName[14];
	};

	__declspec(dllimport) int __stdcall FindClose(void* find);
	__declspec(dllimport) int __stdcall FindNextFileA(void* find, _WIN32_FIND_DATAA* data);
	__declspec(dllimport) unsigned long __stdcall GetFileAttributesA(const char* path);
	__declspec(dllimport) int __stdcall SetFileAttributesA(const char* path, unsigned long attributes);
	__declspec(dllimport) void* __stdcall FindFirstFileA(const char* pattern, _WIN32_FIND_DATAA* data);
	__declspec(dllimport) int __stdcall DeleteFileA(const char* path);
	__declspec(dllimport) int __stdcall MoveFileA(const char* existing, const char* replacement);
	__declspec(dllimport) int __stdcall CopyFileA(const char* existing, const char* replacement, int failIfExists);
	__declspec(dllimport) int __stdcall CreateDirectoryA(const char* path, void* security);
	__declspec(dllimport) void* __stdcall CreateFileA(const char* path, unsigned long access, unsigned long share,
		void* security, unsigned long creation, unsigned long attributes, void* templateFile);
	__declspec(dllimport) int __stdcall GetFileTime(void* file, _FILETIME* creation, _FILETIME* access, _FILETIME* write);
	__declspec(dllimport) long __stdcall CompareFileTime(const _FILETIME* first, const _FILETIME* second);
	__declspec(dllimport) int __stdcall CloseHandle(void* handle);
}
#pragma comment(linker, "/alternatename:__imp__FindClose@4=__imp__FindClose")
#pragma comment(linker, "/alternatename:__imp__FindNextFileA@8=__imp__FindNextFileA")
#pragma comment(linker, "/alternatename:__imp__GetFileAttributesA@4=__imp__GetFileAttributesA")
#pragma comment(linker, "/alternatename:__imp__SetFileAttributesA@8=__imp__SetFileAttributesA")
#pragma comment(linker, "/alternatename:__imp__FindFirstFileA@8=__imp__FindFirstFileA")
#pragma comment(linker, "/alternatename:__imp__DeleteFileA@4=__imp__DeleteFileA")
#pragma comment(linker, "/alternatename:__imp__MoveFileA@8=__imp__MoveFileA")
#pragma comment(linker, "/alternatename:__imp__CopyFileA@12=__imp__CopyFileA")
#pragma comment(linker, "/alternatename:__imp__CreateDirectoryA@8=__imp__CreateDirectoryA")
#pragma comment(linker, "/alternatename:__imp__CreateFileA@28=__imp__CreateFileA")
#pragma comment(linker, "/alternatename:__imp__GetFileTime@16=__imp__GetFileTime")
#pragma comment(linker, "/alternatename:__imp__CompareFileTime@8=__imp__CompareFileTime")
#pragma comment(linker, "/alternatename:__imp__CloseHandle@4=__imp__CloseHandle")

namespace om
{
	// FUNCTION: ENGINE 0x105C1040
	FileSystem::FileSystem()
	{
	}

	// FUNCTION: ENGINE 0x105C1080
	bool FileSystem::Rename(const String& source, const String& destination)
	{
		CreateDirectories(destination);
		if (!FileExists(destination) || RemoveFile(destination))
		{
			if (RenameFile(source, destination))
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105CB6A0
	bool RenameFile(const String& source, const String& destination)
	{
		return MoveFileA(source.GetText(), destination.GetText()) != 0;
	}

	// FUNCTION: ENGINE 0x105CB850
	bool FileExists(const String& path)
	{
		_WIN32_FIND_DATAA data;
		void* find = FindFirstFileA(path.GetText(), &data);
		if (find != reinterpret_cast<void*>(-1))
		{
			FindClose(find);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105CB8A0
	bool RemoveFile(const String& path)
	{
		return DeleteFileA(path.GetText()) != 0;
	}

	// FUNCTION: ENGINE 0x105CB8D0
	// EQUIVALENT: the engine stores the low word as a zero and then or's the value into it, ours stores the value once (72.1 %)
	bool GetFileWriteTime(const String& path, FileTime* time)
	{
		_WIN32_FIND_DATAA data;
		void* find = FindFirstFileA(path.GetText(), &data);
		if (find != reinterpret_cast<void*>(-1))
		{
			time->high = data.ftLastWriteTime.dwHighDateTime;
			time->low = 0;
			time->low |= data.ftLastWriteTime.dwLowDateTime;
			FindClose(find);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105CB4D0
	bool CreateDirectories(const String& path)
	{
		int created = 0;
		unsigned int index = 0;
		String normalized(path);
		NormalizePath(&normalized);
		char* text = normalized.data;
		if (text != gEmptyStringData && *text != 0)
		{
			do
			{
				if (text[index] == '\\' && index != 0)
				{
					text[index] = 0;
					created = CreateDirectoryA(text, 0);
					text[index] = '\\';
				}
				index++;
			}
			while (text[index] != 0);
		}
		return created == 1;
	}

	// FUNCTION: ENGINE 0x105CB550
	bool IsFileNewer(const String& first, const String& second)
	{
		bool newer = true;
		void* firstFile = CreateFileA(first.GetText(), 0x80000000, 3, 0, 3, 0x80, 0);
		void* secondFile = CreateFileA(second.GetText(), 0x80000000, 3, 0, 3, 0x80, 0);
		if (firstFile != reinterpret_cast<void*>(-1) && secondFile != reinterpret_cast<void*>(-1))
		{
			_FILETIME firstTime;
			_FILETIME secondTime;
			GetFileTime(firstFile, 0, 0, &firstTime);
			GetFileTime(secondFile, 0, 0, &secondTime);
			newer = CompareFileTime(&firstTime, &secondTime) > 0;
		}
		CloseHandle(firstFile);
		CloseHandle(secondFile);
		return newer;
	}

	// FUNCTION: ENGINE 0x105CB610
	bool CopyFileTo(const String& destination, const String& source)
	{
		CreateDirectories(destination);
		return CopyFileA(source.GetText(), destination.GetText(), 0) != 0;
	}

	// FUNCTION: ENGINE 0x105CB650
	bool MakeFileWritable(const String& path)
	{
		unsigned long attributes = GetFileAttributesA(path.GetText());
		if (attributes == 0xFFFFFFFF)
		{
			return false;
		}
		attributes &= 0xFFFFFFFE;
		return SetFileAttributesA(path.GetText(), attributes) != 0;
	}

	// FUNCTION: ENGINE 0x105CB930
	int VisitFiles(const String& root, const String& directory, FileVisitor visitor, void* data)
	{
		String pattern;
		if (directory.length > 0)
		{
			Sprintf(pattern, "%s\\%s\\*", root.GetText(), directory.GetText());
		}
		else
		{
			Sprintf(pattern, "%s\\*", root.GetText());
		}
		_WIN32_FIND_DATAA found;
		void* find = FindFirstFileA(pattern.GetTextOutOfLine(), &found);
		if (find == reinterpret_cast<void*>(-1))
		{
			return 0;
		}
		do
		{
			if (found.dwFileAttributes & 0x10)
			{
				if (strcmp(found.cFileName, ".") != 0 && strcmp(found.cFileName, "..") != 0)
				{
					String subdirectory;
					if (directory.length > 0)
					{
						Sprintf(subdirectory, "%s\\%s", directory.GetText(), found.cFileName);
					}
					else
					{
						Sprintf(subdirectory, "%s", found.cFileName);
					}
					if (VisitFiles(root, subdirectory, visitor, data) == 2)
					{
						FindClose(find);
						return 2;
					}
				}
			}
			else
			{
				String path;
				if (directory.length > 0)
				{
					Sprintf(path, "%s\\%s", directory.GetText(), found.cFileName);
				}
				else
				{
					Sprintf(path, "%s", found.cFileName);
				}
				if (!visitor(path.GetTextOutOfLine(), data))
				{
					FindClose(find);
					return 0;
				}
			}
		}
		while (FindNextFileA(find, &found));
		FindClose(find);
		return 1;
	}

	// FUNCTION: ENGINE 0x105CBBB0
	bool VisitAllFiles(const String& root, FileVisitor visitor, void* data)
	{
		int result = VisitFiles(root, String(), visitor, data);
		if (result == 0)
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105CBBF0
	String GetFileNameOf(const String& path)
	{
		String result(path);
		ReduceToFileName(&result);
		return result;
	}

	// FUNCTION: ENGINE 0x105CBC10
	void CopyFileWritable(const String& destination, const String& source)
	{
		CreateDirectories(destination);
		if (CopyFileTo(destination, source))
		{
			MakeFileWritable(destination);
		}
	}

	// FUNCTION: ENGINE 0x105CBC40
	bool CreateEmptyFile(const String& path, bool overwrite)
	{
		bool exists = FileExists(path);
		if (overwrite || !exists)
		{
			CreateDirectories(path);
			void* file = CreateFileA(path.GetText(), 0x40000000, 0, 0, 2, 0x80, 0);
			if (file == reinterpret_cast<void*>(-1))
			{
				return false;
			}
			CloseHandle(file);
			return true;
		}
		return false;
	}

	// What the removal hands to the visitor
	struct FileRemovalContext
	{
		FileRemovalLog* log;
		const char* directory;
	};

	// FUNCTION: ENGINE 0x105CBCA0
	// EQUIVALENT: register allocation: the engine keeps the log's error stream in edi and returns the flag from bl, ours reuses esi and returns the constants (66.8 %)
	static bool RemoveVisitedFile(const char* name, void* data)
	{
		FileRemovalContext* context = static_cast<FileRemovalContext*>(data);
		FileRemovalLog* log = context->log;
		String path = Format(0, "%s\\%s", context->directory, name);
		bool removed = RemoveFile(path);
		if (removed)
		{
			Stream* stream = log->removed;
			StreamPrintf(stream, "", path.GetTextOutOfLine());
			return removed;
		}
		Stream* errors = log->errors;
		StreamPrintf(errors, "", path.GetTextOutOfLine());
		char message[256];
		if (GetLastErrorText(message, 256))
		{
			StreamPrintf(errors, "", message);
			return false;
		}
		StreamPrintf(errors, "");
		return false;
	}

	// FUNCTION: ENGINE 0x105CBD90
	bool RemoveFilesBelow(const String& directory, FileRemovalLog* log)
	{
		if (FileExists(directory))
		{
			const char* text = directory.GetText();
			FileRemovalContext context;
			context.directory = text;
			context.log = log;
			return VisitAllFiles(directory, RemoveVisitedFile, &context);
		}
		return true;
	}
}
