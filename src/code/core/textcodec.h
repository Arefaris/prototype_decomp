// The character codecs of the core module's text conversion (unit 0x10646E20 - 0x10647BEA; no assert path, file
// name textcodec.cpp and all names guessed): ASCII, Windows-1252, UTF-8 (the decoder of Unicode, Inc.'s
// ConvertUTF.c), UTF-16, UTF-32 and Shift-JIS, each with the same four entry points the converters
// (0x1063E750 - 0x10640850) call:
//   bool Decode(source, &bytes, &code, flags): one character; false when it is not valid
//   int Encode(code, target, size, replacement, &bytes, flags): 0, -1 no room, -2 not encodable, -4 not encodable
//     and no replacement, -6 the replacement is not encodable either (unencodable characters are retried as
//     `replacement`)
//   int Copy(target, source, size): copies whole characters while they fit and terminates; the length, -1 when the
//     source is not valid
//   int Count(source, &bytes): the number of characters, -1 when the source is not valid
#ifndef CORE_TEXTCODEC_H
#define CORE_TEXTCODEC_H

namespace core
{
	bool AsciiDecodeChar(const char* source, unsigned int* bytes, unsigned int* code, int flags);
	// Also maps the full-width forms of ASCII (U+FF01 - U+FF5E) and the ideographic space
	int AsciiEncodeChar(unsigned int code, char* target, unsigned int size, unsigned int replacement, unsigned int* bytes, int flags);
	int AsciiCopyString(char* target, const char* source, unsigned int size);
	int AsciiCountChars(const char* source, unsigned int* bytes);
	// Never returns for a string whose first character has bit 7 set (the loop does not advance)
	bool AsciiValidate(const char* source);

	// 0x80 - 0x9F through a table, everything else as Latin-1
	bool Cp1252DecodeChar(const char* source, unsigned int* bytes, unsigned int* code, int flags);
	int Cp1252EncodeChar(unsigned int code, char* target, unsigned int size, unsigned int replacement, unsigned int* bytes, int flags);
	int Cp1252CopyString(char* target, const char* source, unsigned int size);
	int Cp1252CountChars(const char* source, unsigned int* bytes);

	// The compatibility mapping of the half-width and full-width forms (U+FF01 - U+FFEE); false for anything else
	bool DecomposeWidthForm(unsigned int code, unsigned int* result);

	bool Utf8DecodeChar(const char* source, unsigned int* bytes, unsigned int* code, int flags);
	int Utf8EncodeChar(unsigned int code, char* target, unsigned int size, unsigned int replacement, unsigned int* bytes, int flags);
	int Utf8CopyString(char* target, const char* source, unsigned int size);
	int Utf8CountChars(const char* source, unsigned int* bytes);

	bool Utf16DecodeChar(const unsigned short* source, unsigned int* bytes, unsigned int* code, int flags);
	int Utf16EncodeChar(unsigned int code, unsigned short* target, unsigned int size, unsigned int replacement, unsigned int* bytes, int flags);
	int Utf16CopyString(unsigned short* target, const unsigned short* source, unsigned int size);
	int Utf16CountChars(const unsigned short* source, unsigned int* bytes);

	bool Utf32DecodeChar(const unsigned int* source, unsigned int* bytes, unsigned int* code, int flags);
	int Utf32EncodeChar(unsigned int code, unsigned int* target, unsigned int size, unsigned int replacement, unsigned int* bytes, int flags);
	int Utf32CopyString(unsigned int* target, const unsigned int* source, unsigned int size);
	int Utf32CountChars(const unsigned int* source, unsigned int* bytes);

	// Flags 1: ASCII and half-width katakana are written as their full-width double-byte forms
	bool ShiftJisDecodeChar(const char* source, unsigned int* bytes, unsigned int* code, int flags);
	int ShiftJisEncodeChar(unsigned int code, char* target, unsigned int size, unsigned int replacement, unsigned int* bytes, int flags);
	int ShiftJisCopyString(char* target, const char* source, unsigned int size);
	int ShiftJisCountChars(const char* source, unsigned int* bytes);
}

#endif
