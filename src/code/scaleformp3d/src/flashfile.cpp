// CFLAGS: !/arch
// scaleformp3d::FlashFile (the unit starting at 0x1095BA10; file name guessed from the class). Names are guesses.
#include "code/scaleformp3d/flashfile.h"
#include <string.h>

namespace scaleformp3d
{
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
}
