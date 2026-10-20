// CFLAGS: !/arch
// scaleformp3d::FlashFile (the unit starting at 0x1095BA10; file name guessed from the class). Names are guesses.
#include "code/scaleformp3d/flashfile.h"
#include "code/core/file/filesystem.h"
#include "code/core/heap.h"
#include "code/core/strings.h"
#include "code/scaleformp3d/flashfilecache.h"
#include <new>
#include <string.h>

namespace scaleformp3d
{

	FlashFileCacheEntry* gFlashFileCache;
	core::IFile* gFlashFileLoading;

	// FUNCTION: ENGINE 0x1095BE70
	inline __declspec(noinline) FlashFileKey::FlashFileKey()
	{
		low = 0;
		high = 0;
	}

	// FUNCTION: ENGINE 0x1095C170
	inline __declspec(noinline) FlashFileName::FlashFileName()
	{
		mText = "";
		mOwned = false;
	}

	// FUNCTION: ENGINE 0x1095C260
	// NONMATCHING: the engine passes the address of the loading file through a stack slot it fills after the other arguments, and keeps the path in a register (72.5 %)
#ifdef NONMATCHING
	bool LoadFlashFile(const char* path, int heap)
	{
		for (unsigned int i = 0; i < FLASH_FILE_CACHE_SIZE; i++)
		{
			FlashFileName empty;
			FlashFileCacheEntry* entry = gFlashFileCache + i;
			if (*entry == empty)
			{
				core::FileSystemOpenFileAsync(&gFlashFileLoading, path, false, 0, 1, 0, 1, 1, 0);
				while (!gFlashFileLoading->IsIdle())
				{
					engine::YieldFiber();
				}
				if (!gFlashFileLoading->IsOpen())
				{
					return false;
				}
				entry->FlashFileName::operator=(FlashFileName(path, 1));
				gFlashFileLoading->GetSize(&entry->mSize);
				while (!gFlashFileLoading->IsIdle())
				{
					engine::YieldFiber();
				}
				entry->mData = core::HeapAllocAligned(heap, entry->mSize, 16);
				gFlashFileLoading->Read(entry->mData, entry->mSize, 1);
				while (!gFlashFileLoading->IsIdle())
				{
					engine::YieldFiber();
				}
				gFlashFileLoading->Release();
				gFlashFileLoading = 0;
				return true;
			}
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x1095C3F0
	bool FindFlashFile(const char* path, unsigned int* size, void** data)
	{
		FlashFileName name(path, 1);
		for (unsigned int i = 0; i < FLASH_FILE_CACHE_SIZE; i++)
		{
			if (name == gFlashFileCache[i])
			{
				*size = gFlashFileCache[i].mSize;
				*data = gFlashFileCache[i].mData;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1095C470
	bool HasFlashFile(const char* path)
	{
		FlashFileName name(path, 1);
		for (unsigned int i = 0; i < FLASH_FILE_CACHE_SIZE; i++)
		{
			if (name == gFlashFileCache[i])
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1095C4D0
	bool RemoveFlashFile(const char* path, int heap)
	{
		FlashFileName name(path, 1);
		for (unsigned int i = 0; i < FLASH_FILE_CACHE_SIZE; i++)
		{
			if (name == gFlashFileCache[i])
			{
				gFlashFileCache[i].FlashFileName::operator=(FlashFileName());
				gFlashFileCache[i].mSize = 0;
				core::HeapFreeAligned(heap, gFlashFileCache[i].mData);
				gFlashFileCache[i].mData = 0;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1095C7C0
	void ClearFlashFiles(int heap)
	{
		FlashFileName empty;
		for (unsigned int i = 0; i < FLASH_FILE_CACHE_SIZE; i++)
		{
			if (empty != gFlashFileCache[i])
			{
				gFlashFileCache[i].FlashFileName::operator=(FlashFileName());
				gFlashFileCache[i].mSize = 0;
				core::HeapFreeAligned(heap, gFlashFileCache[i].mData);
				gFlashFileCache[i].mData = 0;
			}
		}
		delete[] gFlashFileCache;
	}

	// FUNCTION: ENGINE 0x1095C5C0
	// NONMATCHING: the engine keeps the address of the local file in the stack slot of the path argument and clears the loop with a jump the compiler does not make for ours (38.6 %)
#ifdef NONMATCHING
	FlashFile::FlashFile(const char* path, int flags, int flags2)
	{
		if (gFlashFileCache == 0)
		{
			gFlashFileCache = new FlashFileCacheEntry[FLASH_FILE_CACHE_SIZE];
		}
		unsigned int length = strlen(path) + 1;
		mPath = (char*)GMemory::Alloc(length);
		memcpy(mPath, path, length);
		mData = 0;
		mSize = 0;
		mPosition = 0;
		mFlags = flags;
		mValid = false;
		mError = 0;
		if (FindFlashFile(mPath, &mSize, (void**)&mData))
		{
			mUnknown2C = 0;
			mValid = true;
			return;
		}
		core::IFile* file = 0;
		core::FileSystemOpenFile(&file, mPath, false, 0, 1, 0, 1, 1, 0);
		if (file->IsOpen())
		{
			file->SetPositionWait(0);
			mValid = true;
			mSize = file->GetCurrentSize();
			mData = (unsigned char*)core::HeapAllocAligned(1, mSize, 16);
			file->ReadWait(mData, mSize, 1);
		}
		file->Release();
		mUnknown2C = 0;
	}
#endif

	// FUNCTION: ENGINE 0x1095C780
	bool FlashFile::Close()
	{
		if (!HasFlashFile(mPath))
		{
			core::HeapFreeAligned(1, mData);
		}
		mData = 0;
		mSize = 0;
		mPosition = 0;
		mValid = false;
		mError = 0;
		return true;
	}


	// FUNCTION: ENGINE 0x1095C0A0
	FlashFileHandler::FlashFileHandler()
	{
	}

	// FUNCTION: ENGINE 0x1095C0D0
	// NONMATCHING: the engine stores no vftable in the destructors of the chain, ours stores the one of the file
	// that delegates and the one of the counted base (50 %)
#ifdef NONMATCHING
	FlashFileHandler::~FlashFileHandler()
	{
	}
#endif

	// FUNCTION: ENGINE 0x1095C0F0
	bool FlashFileHandler::Close()
	{
		if (IsValid())
		{
			mFile->Close();
			if (mFile)
			{
				mFile->Release();
			}
			mFile = 0;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1095BA10
	const char* FlashFile::GetFilePath()
	{
		return mPath;
	}

	// FUNCTION: ENGINE 0x1095BA20
	bool FlashFile::IsValid()
	{
		return mValid;
	}

	// FUNCTION: ENGINE 0x1095BA30
	bool FlashFile::IsWritable()
	{
		return IsValid() && (mFlags & 2) != 0;
	}

	// FUNCTION: ENGINE 0x1095BA50
	int FlashFile::Tell()
	{
		return mPosition;
	}

	// FUNCTION: ENGINE 0x1095BA60
	long long FlashFile::LTell()
	{
		return mPosition;
	}

	// FUNCTION: ENGINE 0x1095BA70
	int FlashFile::GetLength()
	{
		return mSize;
	}

	// FUNCTION: ENGINE 0x1095BA80
	long long FlashFile::LGetLength()
	{
		return GetLength();
	}

	// FUNCTION: ENGINE 0x1095BA90
	int FlashFile::GetErrorCode()
	{
		return mError;
	}

	// FUNCTION: ENGINE 0x1095BAA0
	int FlashFile::Write(const unsigned char* buffer, int count)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1095BAB0
	int FlashFile::Read(unsigned char* buffer, int count)
	{
		unsigned int left = mSize - mPosition;
		mUnknown2C = 1;
		if (left <= (unsigned int)count)
		{
			count = left;
		}
		memcpy(buffer, mData + mPosition, count);
		mPosition += count;
		return count;
	}

	// FUNCTION: ENGINE 0x1095BAF0
	int FlashFile::SkipBytes(int count)
	{
		long long position = LTell();
		long long target = LSeek(count, 1);
		if (position != -1 && target != -1)
		{
			return (int)target - (int)position;
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x1095BB40
	int FlashFile::BytesAvailable()
	{
		long long position = LTell();
		long long length = LGetLength();
		if (position != -1 && length != -1)
		{
			mError = 0;
			return (int)length - (int)position;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1095BB80
	bool FlashFile::Flush()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x1095BB90
	int FlashFile::Seek(int offset, int origin)
	{
		unsigned int position = 0;
		unsigned int size = mSize;
		switch (origin)
		{
		case 1:
			position = mPosition + offset;
			goto check;
		case 0:
			position = offset;
		check:
			if (position > size)
			{
				return -1;
			}
			break;
		case 2:
			position = size;
			break;
		}
		mPosition = position;
		return position;
	}

	// FUNCTION: ENGINE 0x1095BBD0
	long long FlashFile::LSeek(long long offset, int origin)
	{
		return Seek((int)offset, origin);
	}

	// FUNCTION: ENGINE 0x1095BBF0
	bool FlashFile::ChangeSize(int size)
	{
		mError = 0x1003;
		return false;
	}

	// FUNCTION: ENGINE 0x1095BC00
	// EQUIVALENT: shrink-wrap (the engine pushes ebx and esi after the early exit and enters the loop with a jump), 11.5 %
	int FlashFile::CopyFromStream(GFile* source, int count)
	{
		unsigned char buffer[0x4000];
		int total = 0;
		while (count != 0)
		{
			int chunk = 1;
			if (count <= 0x4000)
			{
				chunk = count;
			}
			int got = source->Read(buffer, chunk);
			int written = 0;
			if (got > 0)
			{
				written = Write(buffer, got);
			}
			total += written;
			count -= written;
			if (written >= chunk && count != 0)
			{
				continue;
			}
			break;
		}
		return total;
	}

	// FUNCTION: ENGINE 0x1095C990
	FlashFile::~FlashFile()
	{
		if (mValid)
		{
			FlashFile::Close();
		}
		if (mPath)
		{
			GMemory::Free(mPath);
		}
	}

	// FUNCTION: ENGINE 0x1095C230
	FlashFileCacheEntry::FlashFileCacheEntry()
	{
		mSize = 0;
		mData = 0;
	}

	// FUNCTION: ENGINE 0x1095C250
	FlashFileCacheEntry::~FlashFileCacheEntry()
	{
	}

	// FUNCTION: ENGINE 0x1095BE80
	void FlashFileName::SetText(const char* text)
	{
		if (text != mText)
		{
			if (mOwned)
			{
				core::StrFree((char*)mText);
			}
			if (text != 0 && *text != 0)
			{
				mText = core::StrDup(text);
				mOwned = mText != core::GetDefaultString();
			}
			else
			{
				mOwned = false;
				mText = "";
			}
		}
	}

	// FUNCTION: ENGINE 0x1095C130
	FlashFileName::FlashFileName(const char* text, int copy) : FlashFileKey(text, 1)
	{
		mText = "";
		mOwned = false;
		if (copy == 1)
		{
			SetText(text);
		}
		else
		{
			mText = text;
			mOwned = false;
		}
	}

	// FUNCTION: ENGINE 0x1095C190
	FlashFileName::~FlashFileName()
	{
		if (mOwned)
		{
			core::StrFree((char*)mText);
		}
	}

	// FUNCTION: ENGINE 0x1095C1B0
	FlashFileName& FlashFileName::operator=(const FlashFileName& other)
	{
		low = other.low;
		high = other.high;
		if (other.mOwned)
		{
			SetText(other.mText);
			return *this;
		}
		if (mOwned)
		{
			core::StrFree((char*)mText);
		}
		mText = other.mText;
		mOwned = false;
		return *this;
	}

	// FUNCTION: ENGINE 0x1095BDE0
	unsigned int FlashFileKey::GetLow() const
	{
		return low;
	}

	// FUNCTION: ENGINE 0x1095BE10
	// EQUIVALENT: the same reads and compares; the engine loads the second word of this key after the first compare
	// (78.4 %)
	bool FlashFileKey::operator==(const FlashFileKey& other) const
	{
		FlashFileKey a = other;
		FlashFileKey b = *this;
		return b.low == a.low && b.high == a.high;
	}

	// FUNCTION: ENGINE 0x1095BE40
	// EQUIVALENT: the same reads and compares; the engine loads the second word of this key after the first compare
	bool FlashFileKey::operator!=(const FlashFileKey& other) const
	{
		FlashFileKey a = other;
		FlashFileKey b = *this;
		return b.low != a.low || b.high != a.high;
	}

	__forceinline bool FlashFileHandler::Open(const char* path, int flags, int flags2)
	{
		FlashFile* file = new FlashFile(path, flags, flags2);
		if (mFile)
		{
			mFile->Release();
		}
		mFile = file;
		if (file && file->IsValid())
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1095C890
	// EQUIVALENT: the same calls and stores; the engine clears the file before the allocation and stores the vftable after
	// it, and loads the new file into the register of the virtual call first (84.6 %)
	FlashFileHandler::FlashFileHandler(const char* path, int flags, int flags2)
	{
		Open(path, flags, flags2);
	}

	// The engine keeps a copy of Open besides the one the constructor expands
	// FUNCTION: ENGINE 0x1095C920 ; scaleformp3d::FlashFileHandler::Open
	// EQUIVALENT: the same calls and stores; the engine keeps this and the new file in the other two registers and
	// restores the saved registers before the virtual call (67.6 %)
	bool (FlashFileHandler::*gKeepFlashFileHandlerOpen)(const char*, int, int) = &FlashFileHandler::Open;
}
