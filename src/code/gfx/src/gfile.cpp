// GFile and GDelegatedFile of the Scaleform GFx library inside the engine DLL (the unit starting at 0x10959720; file name
// guessed).
#include "code/gfx/gfile.h"

// FUNCTION: ENGINE 0x10959720
unsigned int GFile::ReadUInt32()
{
	unsigned int value = 0;
	Read((unsigned char*)&value, 4);
	return value;
}

// FUNCTION: ENGINE 0x10959740
unsigned short GFile::ReadUInt16()
{
	unsigned short value = 0;
	Read((unsigned char*)&value, 2);
	return value;
}

// FUNCTION: ENGINE 0x10959760
unsigned char GFile::ReadUByte()
{
	unsigned char value = 0;
	Read(&value, 1);
	return value;
}

// FUNCTION: ENGINE 0x10959780
void GFile::WriteUInt16(unsigned short value)
{
	Write((unsigned char*)&value, 2);
}

// FUNCTION: ENGINE 0x109597A0
void GFile::WriteUByte(unsigned char value)
{
	Write(&value, 1);
}

// FUNCTION: ENGINE 0x109597C0
// EQUIVALENT: the engine also copies the argument through the (identity) conversion into its slot; the call is the same, 0 %
void GFile::WriteSByte(char value)
{
	Write((unsigned char*)&value, 1);
}

// FUNCTION: ENGINE 0x109597E0
// EQUIVALENT: the engine also copies the argument through the (identity) conversion into its slot; the call is the same, 0 %
void GFile::WriteSInt16(short value)
{
	Write((unsigned char*)&value, 2);
}

// FUNCTION: ENGINE 0x10959800
char GFile::ReadSByte()
{
	char value = 0;
	Read((unsigned char*)&value, 1);
	return value;
}

// FUNCTION: ENGINE 0x10959820
short GFile::ReadSInt16()
{
	short value = 0;
	Read((unsigned char*)&value, 2);
	return value;
}

// FUNCTION: ENGINE 0x10959840
int GFile::ReadSInt32()
{
	int value = 0;
	Read((unsigned char*)&value, 4);
	return value;
}


GFile::~GFile()
{
}

// FUNCTION: ENGINE 0x1095BF20
GDelegatedFile::GDelegatedFile(GFile* file)
{
	if (file)
	{
		file->AddRef();
	}
	mFile = file;
}

GDelegatedFile::~GDelegatedFile()
{
	if (mFile)
	{
		mFile->Release();
	}
}

// FUNCTION: ENGINE 0x1095BF60
const char* GDelegatedFile::GetFilePath()
{
	return mFile->GetFilePath();
}

// FUNCTION: ENGINE 0x1095BF70
bool GDelegatedFile::IsValid()
{
	GFile* file = mFile;
	return file != 0 && file->IsValid();
}

// FUNCTION: ENGINE 0x1095BF90
bool GDelegatedFile::IsWritable()
{
	return mFile->IsWritable();
}

// FUNCTION: ENGINE 0x1095BFA0
int GDelegatedFile::Tell()
{
	return mFile->Tell();
}

// FUNCTION: ENGINE 0x1095BFB0
long long GDelegatedFile::LTell()
{
	return mFile->LTell();
}

// FUNCTION: ENGINE 0x1095BFC0
int GDelegatedFile::GetLength()
{
	return mFile->GetLength();
}

// FUNCTION: ENGINE 0x1095BFD0
long long GDelegatedFile::LGetLength()
{
	return mFile->LGetLength();
}

// FUNCTION: ENGINE 0x1095BFE0
int GDelegatedFile::GetErrorCode()
{
	return mFile->GetErrorCode();
}

// FUNCTION: ENGINE 0x1095BFF0
int GDelegatedFile::Write(const unsigned char* buffer, int count)
{
	return mFile->Write(buffer, count);
}

// FUNCTION: ENGINE 0x1095C000
int GDelegatedFile::Read(unsigned char* buffer, int count)
{
	return mFile->Read(buffer, count);
}

// FUNCTION: ENGINE 0x1095C010
int GDelegatedFile::SkipBytes(int count)
{
	return mFile->SkipBytes(count);
}

// FUNCTION: ENGINE 0x1095C020
int GDelegatedFile::BytesAvailable()
{
	return mFile->BytesAvailable();
}

// FUNCTION: ENGINE 0x1095C030
bool GDelegatedFile::Flush()
{
	return mFile->Flush();
}

// FUNCTION: ENGINE 0x1095C040
int GDelegatedFile::Seek(int offset, int origin)
{
	return mFile->Seek(offset, origin);
}

// FUNCTION: ENGINE 0x1095C050
long long GDelegatedFile::LSeek(long long offset, int origin)
{
	return mFile->LSeek(offset, origin);
}

// FUNCTION: ENGINE 0x1095C070
bool GDelegatedFile::ChangeSize(int size)
{
	return mFile->ChangeSize(size);
}

// FUNCTION: ENGINE 0x1095C080
int GDelegatedFile::CopyFromStream(GFile* source, int count)
{
	return mFile->CopyFromStream(source, count);
}

// FUNCTION: ENGINE 0x1095C090
bool GDelegatedFile::Close()
{
	return mFile->Close();
}
