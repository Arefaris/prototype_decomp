// The path helpers of the om library (names guessed): paths are om::Strings or plain character arrays; the separators
// are the backslash and the slash.
#ifndef OM_PATH_H
#define OM_PATH_H

#include "code/om/string.h"
#include <stddef.h>

namespace om
{
	// 0x105CAC30 and 0x105CAE60 (the second is a copy kept in another unit)
	int IsPathSeparator(char character);
	int IsPathSeparator2(char character);
	// 0x105CAC60: replaces every one character of the string by another
	void ReplaceCharacter(String* path, char from, char to);
	// 0x105CAC90: the slashes become backslashes
	String* ConvertToBackslashes(String* path);
	// 0x105CACC0 / 0x105CAD00
	String* RemoveTrailingSeparator(String* path);
	String* RemoveLeadingSeparator(String* path);
	// 0x105CAE20: the part behind the last separator
	void GetFileName(const char* path, char* fileName, size_t size);
	// 0x105CAE80: runs of separators become one
	String* CollapseSeparators(String* path);
	// 0x105CAF40 / 0x105CAF90: cuts the text from the last dot on
	String* RemoveExtension(String* path);
	void RemoveExtension(const char* path, char* result, size_t size);
	// 0x105CB050
	void RemoveTrailingSeparator(char* path);
	// 0x105CAD40: removes the "." and ".." parts
	String* ResolveDotSegments(String* path);
	// 0x105CAEF0: separators one backslash, no dot parts, no trailing separator, small letters
	String* NormalizePath(String* path);
	// 0x105CAFE0 / 0x105CB000 / 0x105CB110
	String RemoveExtensionOf(const String& path);
	String NormalizedPath(const String& path);
	String GetDirectoryOf(const String& path);
	// 0x105CB090: the part up to the last separator
	String* GetDirectory(String* path);
}

#endif
