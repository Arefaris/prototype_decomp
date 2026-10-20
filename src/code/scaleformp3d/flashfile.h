// scaleformp3d::FlashFile (RTTI name; derives from GFile, vftable 0x10E8D4CC): a file of the Scaleform player whose
// contents sit in memory (the engine keeps the contents of the files it opened in a cache of 25 entries). Member names
// are guesses.
#ifndef SCALEFORMP3D_FLASHFILE_H
#define SCALEFORMP3D_FLASHFILE_H

#include "code/gfx/gfile.h"

namespace scaleformp3d
{
	// scaleformp3d::FlashFileHandler (RTTI name; derives from GDelegatedFile, vftable 0x10E8D47C): the file the player
	// reads through, which closes the file it passes everything on to when it is closed itself
	class FlashFileHandler : public GDelegatedFile
	{
	public:
		// 0x1095C0A0
		FlashFileHandler();
		// 0x1095C890: opens the file of path
		FlashFileHandler(const char* path, int flags, int flags2);
		// 0x1095C0D0 (the deleting destructor is 0x1095C590)
		virtual ~FlashFileHandler();
		virtual bool Close();
		// 0x1095C920: opens the file of path in place of the one it had; whether it could
		bool Open(const char* path, int flags, int flags2);
	};

	class FlashFile : public GFile
	{
	public:
		// 0x1095C5C0: opens the file (from the cache, or from the file system) and reads it into memory
		FlashFile(const char* path, int flags, int flags2);
		// 0x1095C990 (the deleting destructor is 0x1095C9C0)
		virtual ~FlashFile();
		virtual const char* GetFilePath();
		virtual bool IsValid();
		virtual bool IsWritable();
		virtual int Tell();
		virtual long long LTell();
		virtual int GetLength();
		virtual long long LGetLength();
		virtual int GetErrorCode();
		virtual int Write(const unsigned char* buffer, int count);
		virtual int Read(unsigned char* buffer, int count);
		virtual int SkipBytes(int count);
		virtual int BytesAvailable();
		virtual bool Flush();
		virtual int Seek(int offset, int origin);
		virtual long long LSeek(long long offset, int origin);
		virtual bool ChangeSize(int size);
		virtual int CopyFromStream(GFile* source, int count);
		virtual bool Close();

		char* mPath;                   // 0x10
		bool mValid;                   // 0x14
		unsigned char* mData;          // 0x18
		unsigned int mSize;            // 0x1C
		unsigned int mPosition;        // 0x20
		int mFlags;                    // 0x24
		int mError;                    // 0x28
		int mUnknown2C;                // 0x2C
	};
}

#endif
