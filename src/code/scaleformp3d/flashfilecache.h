// The cache of the files of the Flash player (the unit around 0x1095BA00 - 0x1095CA60, with flashfile.cpp; names
// guessed): the contents of the files that were opened are kept in a table of 25 entries, so that opening a file twice
// reads it once. A name is the 64-bit key of the path with the path itself.
#ifndef SCALEFORMP3D_FLASHFILECACHE_H
#define SCALEFORMP3D_FLASHFILECACHE_H

#include "code/core/file/file.h"

namespace core
{
	// 0x1063B7E0: gives a string of StrDup back (name guess)
	void StrFree(char* text);
}

namespace engine
{
	// 0x108366F0: lets the other fibers run
	void YieldFiber();
}

namespace scaleformp3d
{
	// The key of a path: its 64-bit hash, ignoring case (8 bytes)
	class FlashFileKey
	{
	public:
		// 0x1095BE70: the empty key
		FlashFileKey();
		// 0x105FCE40 (another unit): the key of text; the second argument is passed as 1 and its meaning is unknown
		FlashFileKey(const char* text, int unknown);
		// 0x1095BDE0
		unsigned int GetLow() const;
		// 0x1095BE10 / 0x1095BE40
		bool operator==(const FlashFileKey& other) const;
		bool operator!=(const FlashFileKey& other) const;

		unsigned int low;     // 0x00
		unsigned int high;    // 0x04
	};

	// A path with its key; the text is a copy of the name's own or one the caller keeps (0x10 bytes)
	class FlashFileName : public FlashFileKey
	{
	public:
		// 0x1095C170: no path
		FlashFileName();
		// 0x1095C130: the path of text, as a copy of it when copy is 1
		FlashFileName(const char* text, int copy);
		// 0x1095C190
		~FlashFileName();
		// 0x1095C1B0
		FlashFileName& operator=(const FlashFileName& other);
		// 0x1095BE80: the text becomes a copy of text
		void SetText(const char* text);

		const char* mText;    // 0x08
		bool mOwned;          // 0x0C
	};

	// One file of the cache: its name and its contents (0x18 bytes)
	class FlashFileCacheEntry : public FlashFileName
	{
	public:
		// 0x1095C230
		FlashFileCacheEntry();
		// 0x1095C250
		~FlashFileCacheEntry();

		unsigned int mSize;   // 0x10
		void* mData;          // 0x14
	};

	static const unsigned int FLASH_FILE_CACHE_SIZE = 25;

	// 0x1131FD40: the table of the cache (made when the first file is opened)
	extern FlashFileCacheEntry* gFlashFileCache;
	// 0x1131FD44: the file that is being read into the cache
	extern core::IFile* gFlashFileLoading;

	// 0x1095C260: reads the file into the first free entry from the heap's memory
	bool LoadFlashFile(const char* path, int heap);
	// 0x1095C3F0: the size and contents of a cached file
	bool FindFlashFile(const char* path, unsigned int* size, void** data);
	// 0x1095C470: whether the file is cached
	bool HasFlashFile(const char* path);
	// 0x1095C4D0 / 0x1095C7C0: takes a file out of the cache and gives its memory back to the heap / all of them
	bool RemoveFlashFile(const char* path, int heap);
	void ClearFlashFiles(int heap);
}

#endif
