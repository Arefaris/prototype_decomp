// C-string utilities of the core module (file and function names guessed; the unit is 0x1063AFA0 - 0x1063BB20).
// strlen / strcpy / strcmp families read whole 32-bit words while the pointers are aligned (the 0x01010101 /
// 0x80808080 zero-byte test), a null source counts as "", and the case-insensitive variants go through
// ToLowerChar. The size-limited copies (StrNCpy / StrNCat with int sizes) always terminate the destination.
#ifndef CORE_STRINGS_H
#define CORE_STRINGS_H

#include <stdarg.h>

namespace core
{
	// 'a'..'z' -> 'A'..'Z' and 'A'..'Z' -> 'a'..'z'; everything else unchanged
	int ToUpperChar(int c);
	int ToLowerChar(int c);

	char* StrCpy(char* destination, const char* source);
	char* StrCat(char* destination, const char* source);
	// Appends at most size - 1 - strlen(destination) characters, always terminating
	char* StrNCat(char* destination, const char* source, unsigned int size);
	// As above; *remaining receives the room left in the buffer (0 when it is full)
	char* StrNCat(char* destination, const char* source, unsigned int size, int* remaining);
	// Returns the first occurrence of c (the terminator counts), or null
	const char* StrChr(const char* string, char c);
	// Returns the first occurrence of find (null or "" matches at the start), or null
	const char* StrStr(const char* string, const char* find);
	// Tokeniser with an explicit context (strtok_r); without skipEmpty consecutive delimiters yield empty tokens.
	// The two-argument form keeps the context in a static of the unit (strtok)
	char* StrTok(char* string, const char* delimiters, char** context, bool skipEmpty);
	char* StrTok(char* string, const char* delimiters, char** context);
	char* StrTok(char* string, const char* delimiters);
	unsigned int StrLen(const char* string);
	// Length of the string, or count if no terminator is found before
	unsigned int StrNLen(const char* string, unsigned int count);
	// In-place case conversion of the ASCII letters; returns the string
	char* StrLower(char* string);
	char* StrUpper(char* string);
	int StrCmp(const char* a, const char* b);
	int StrNCmp(const char* a, const char* b, unsigned int count);
	int StrICmp(const char* a, const char* b);
	int StrNICmp(const char* a, const char* b, unsigned int count);
	// The string heap: StrDup allocates from it (HeapAlloc); while none is set (-1) it returns the placeholder
	// "?Name?" instead. The two counters are only exposed through their accessors.
	const char* GetDefaultString();
	int* GetStringHeapCounter1();
	int* GetStringHeapCounter2();
	void SetStringHeap(int heap);
	int GetStringHeap();
	char* StrDup(const char* string);
	// Entry points that only forward to StrCpy / StrLen (the compiler turned them into jumps)
	char* StrCpyAlias(char* destination, const char* source);
	unsigned int StrLenAlias(const char* string);
	// Matches string against a pattern with '*' and '?'; returns 1 or 0
	bool MatchWildcard(const char* string, const char* pattern);
	// 0x1063BB30: MatchWildcard on dotted names part by part (the first part, then the rest; the pattern has a dot)
	bool MatchChannel(const char* name, const char* pattern);
	// Removes "." and ".." components in place ('\\' and '/' separate); returns the path (not matched yet)
	char* NormalisePath(char* path);
	// _vsnprintf that always terminates the buffer
	void VSNPrintf(char* buffer, int size, const char* format, va_list arguments);
	void SNPrintf(char* buffer, int size, const char* format, ...);
	// Copies at most size - 1 characters and terminates; *count receives (or continues) the number written
	char* StrNCpyCount(char* destination, const char* source, int size, int* count);
	char* StrNCpyAppend(char* destination, const char* source, int size, int* count);
	char* StrNCpy(char* destination, const char* source, int size);
	// 0x1063B0D0: the unsigned overload, a plain forward to the copy loop (AllocatorBase_Name::SetName uses it)
	char* StrNCpy(char* destination, const char* source, unsigned int count);
	// 0x1063B0F0: the same, *length (when given) receiving the number of characters copied
	char* StrNCpy(char* destination, const char* source, unsigned int count, unsigned int* length);
	// 0x1120983C
	extern char gHexDigits[17];
	// 0x1063E750 (a jump to 0x10647430): copies whole UTF-8 sequences while they fit in `size` bytes (with the
	// terminator); the length copied, negative on bad input
	int Utf8Copy(char* destination, const char* source, unsigned int size);
	// SNPrintf with one argument, returning the buffer
	char* FormatValue(char* buffer, int size, const char* format, int value);
}

#endif
