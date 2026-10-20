// GFile of the Scaleform GFx library inside the engine DLL: the interface of a file, the file that passes everything on to
// another one (GDelegatedFile), and the reading and writing helpers of the interface. Names are guesses (RTTI).
#ifndef GFX_GFILE_H
#define GFX_GFILE_H

#include "code/gfx/grefcount.h"

class GFileConstants
{
};

// A file; every member of the interface is pure (vftable 0x10E8D3DC, nineteen slots)
class GFile : public GRefCountBase<GFile>, public GFileConstants
{
public:
	// 0x1095BEE0
	GFile()
	{
		SetRefCountMode(1);
	}
	virtual ~GFile();
	virtual const char* GetFilePath() = 0;
	virtual bool IsValid() = 0;
	virtual bool IsWritable() = 0;
	virtual int Tell() = 0;
	virtual long long LTell() = 0;
	virtual int GetLength() = 0;
	virtual long long LGetLength() = 0;
	virtual int GetErrorCode() = 0;
	virtual int Write(const unsigned char* buffer, int count) = 0;
	virtual int Read(unsigned char* buffer, int count) = 0;
	virtual int SkipBytes(int count) = 0;
	virtual int BytesAvailable() = 0;
	virtual bool Flush() = 0;
	virtual int Seek(int offset, int origin) = 0;
	virtual long long LSeek(long long offset, int origin) = 0;
	virtual bool ChangeSize(int size) = 0;
	virtual int CopyFromStream(GFile* source, int count) = 0;
	virtual bool Close() = 0;

	// 0x10959760 / 0x10959740 / 0x10959720 and the same three for the signed values at 0x10959800 / 0x10959820 /
	// 0x10959840: the next value of the file
	unsigned char ReadUByte();
	unsigned short ReadUInt16();
	unsigned int ReadUInt32();
	char ReadSByte();
	short ReadSInt16();
	int ReadSInt32();
	// 0x109597A0 / 0x10959780 / 0x109597C0 / 0x109597E0: a value written to the file
	void WriteUByte(unsigned char value);
	void WriteUInt16(unsigned short value);
	void WriteSByte(char value);
	void WriteSInt16(short value);
};

// A file that does everything through another one (vftable 0x10E8D42C)
class GDelegatedFile : public GFile
{
public:
	// 0x1095BF20
	GDelegatedFile(GFile* file);
	virtual ~GDelegatedFile();
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

	GFile* mFile;                  // 0x10
};

#endif
