// Text conversion between the core module's encodings (unit 0x1063E730 - 0x106412B5; no assert path, file name
// textconvert.cpp and all names guessed): per-encoding Copy / Count entry points over the codecs
// (code/core/textcodec.h) and ConvertText, which decodes the source one character at a time and encodes it in
// the target encoding.
#ifndef CORE_TEXTCONVERT_H
#define CORE_TEXTCONVERT_H

namespace core
{
	// The encodings, in the order of the converters' dispatch tables
	enum TextEncoding
	{
		ENCODING_ASCII = 0,
		ENCODING_UTF8 = 1,
		ENCODING_UTF16 = 2,
		ENCODING_UTF32 = 3,
		ENCODING_SHIFT_JIS = 4,
		ENCODING_CP1252 = 5
	};

	// Forwarders to the codecs' Copy (whole characters while they fit in `size` bytes with the terminator)
	int AsciiCopy(char* target, const char* source, unsigned int size);
	int Cp1252Copy(char* target, const char* source, unsigned int size);
	int Utf8Copy(char* destination, const char* source, unsigned int size);
	int Utf16Copy(unsigned short* target, const unsigned short* source, unsigned int size);
	int Utf32Copy(unsigned int* target, const unsigned int* source, unsigned int size);
	int ShiftJisCopy(char* target, const char* source, unsigned int size);
	// The number of characters (0 for a null string); *bytes receives the length in bytes
	int AsciiCount(const char* source, unsigned int* bytes);
	int Cp1252Count(const char* source, unsigned int* bytes);
	int Utf8Count(const char* source, unsigned int* bytes);
	int Utf16Count(const unsigned short* source, unsigned int* bytes);
	int Utf32Count(const unsigned int* source, unsigned int* bytes);
	int ShiftJisCount(const char* source, unsigned int* bytes);

	// Converts a terminated string; 0, -1 the target is full (it is terminated), -2 invalid source or
	// unencodable character, -3 no target or unknown encoding, -5 source and target overlap. *bytes / *chars
	// receive what was written. Flags go to the codecs; with no flags and equal encodings the source is copied
	int ConvertText(void* target, int targetEncoding, const void* source, int sourceEncoding, unsigned int replacement, unsigned int size, int flags, unsigned int* bytes, unsigned int* chars);
}

#endif
