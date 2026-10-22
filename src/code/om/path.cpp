// The path helpers of the om library (0x105CAC30 - 0x105CB090).
#include "code/om/path.h"
#include <string.h>

namespace om
{
	// FUNCTION: ENGINE 0x105CAC30
	int IsPathSeparator(char character)
	{
		if (character != '\\' && character != '/')
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105CAC60
	void ReplaceCharacter(String* path, char from, char to)
	{
		if (path->length > 0)
		{
			char* text = path->GetWritableText();
			while (*text != 0)
			{
				if (*text == from)
				{
					*text = to;
				}
				text++;
			}
		}
	}

	// FUNCTION: ENGINE 0x105CAC90
	String* ConvertToBackslashes(String* path)
	{
		if (path->length > 0)
		{
			char* text = path->GetWritableText();
			while (*text != 0)
			{
				if (*text == '/')
				{
					*text = '\\';
				}
				text++;
			}
		}
		return path;
	}

	// FUNCTION: ENGINE 0x105CACC0
	String* RemoveTrailingSeparator(String* path)
	{
		unsigned int length = path->length;
		if (length > 0)
		{
			char* text = path->GetWritableText();
			char last = text[length - 1];
			if (last == '\\' || last == '/')
			{
				text[length - 1] = 0;
				path->SetLength(length - 1);
			}
		}
		return path;
	}

	// FUNCTION: ENGINE 0x105CAD00
	String* RemoveLeadingSeparator(String* path)
	{
		unsigned int length = path->length;
		if (length > 0)
		{
			char* text = path->GetWritableText();
			if (*text == '\\' || *text == '/')
			{
				size_t size = length - 1;
				memmove(text, text + 1, size);
				path->SetLength(size);
			}
		}
		return path;
	}

	// FUNCTION: ENGINE 0x105CAE20
	void GetFileName(const char* path, char* fileName, size_t size)
	{
		*fileName = 0;
		const char* name = path;
		while (*path != 0)
		{
			if (*path == '\\' || *path == '/')
			{
				name = path + 1;
			}
			path++;
		}
		strcpy_s(fileName, size, name);
	}

	// FUNCTION: ENGINE 0x105CAE60
	int IsPathSeparator2(char character)
	{
		if (character != '\\' && character != '/')
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105CAF40
	String* RemoveExtension(String* path)
	{
		char* text = path->GetWritableText();
		unsigned int length = path->length;
		if (length > 0)
		{
			char* position = text + (length - 1);
			while (position >= text)
			{
				if (*position == '.')
				{
					*position = 0;
					path->SetLength(position - text);
					break;
				}
				position--;
			}
		}
		return path;
	}

	// FUNCTION: ENGINE 0x105CAF90
	void RemoveExtension(const char* path, char* result, size_t size)
	{
		strcpy_s(result, size, path);
		size_t length = strlen(result);
		if (length != 0)
		{
			char* position = result + length - 1;
			while (position >= result)
			{
				if (*position == '.')
				{
					*position = 0;
					break;
				}
				position--;
			}
		}
	}

	// FUNCTION: ENGINE 0x105CB050
	void RemoveTrailingSeparator(char* path)
	{
		size_t length = strlen(path);
		if (length != 0)
		{
			char last = path[length - 1];
			if (last == '\\' || last == '/')
			{
				path[length - 1] = 0;
			}
		}
	}

	// FUNCTION: ENGINE 0x105CAEF0
	String* NormalizePath(String* path)
	{
		CollapseSeparators(path);
		ConvertToBackslashes(path);
		ResolveDotSegments(path);
		RemoveTrailingSeparator(path);
		*path = path->ToLower();
		return path;
	}

	// FUNCTION: ENGINE 0x105CAFE0
	String RemoveExtensionOf(const String& path)
	{
		String result(path);
		RemoveExtension(&result);
		return result;
	}

	// FUNCTION: ENGINE 0x105CB000
	String NormalizedPath(const String& path)
	{
		String result(path);
		NormalizePath(&result);
		return result;
	}

	// FUNCTION: ENGINE 0x105CB090
	String* GetDirectory(String* path)
	{
		const char* text = path->GetText();
		const char* directoryEnd = 0;
		for (const char* position = text; *position != 0; position++)
		{
			if (*position == '\\' || *position == '/')
			{
				directoryEnd = position + 1;
			}
		}
		if (directoryEnd != 0)
		{
			*path = String(text, static_cast<unsigned int>(directoryEnd - text));
		}
		return path;
	}

	// FUNCTION: ENGINE 0x105CB110
	String GetDirectoryOf(const String& path)
	{
		String result(path);
		GetDirectory(&result);
		return result;
	}

	// FUNCTION: ENGINE 0x105CAE80
	String* CollapseSeparators(String* path)
	{
		if (path->length > 1)
		{
			char* text = path->GetWritableText();
			char* source = text;
			char* destination = text;
			while (source[1] != 0)
			{
				char nextIsSeparator = IsPathSeparator2(source[1]);
				char isSeparator = 0;
				if (nextIsSeparator)
				{
					isSeparator = IsPathSeparator2(source[0]);
				}
				if (!isSeparator)
				{
					*destination = *source;
					destination++;
				}
				source++;
			}
			*destination = *source;
			destination++;
			*destination = 0;
			path->SetLength(destination - text);
		}
		return path;
	}

	// FUNCTION: ENGINE 0x105CAD40
	// NONMATCHING: loop and register allocation differ throughout; ours loads the characters it compares in other places (best 20.8 %)
#ifdef NONMATCHING
	String* ResolveDotSegments(String* path)
	{
		unsigned int length = path->length;
		if (length != 0)
		{
			char* base = path->GetWritableText();
			char* destination = base;
			char* source = base;
			char* end = base + length + 1;
			while (source < end)
			{
				char current = *source;
				if (current == '.')
				{
					char next = source[1];
					if (next == '.')
					{
						if (destination < base + 2 || destination[-2] == '.' || destination[-3] == '.')
						{
							destination[0] = '.';
							destination[1] = '.';
							destination += 2;
						}
						else
						{
							char previous = destination[-2];
							destination -= 2;
							if (previous != '\\')
							{
								do
								{
									if (previous == '/')
									{
										break;
									}
									if (destination == base)
									{
										source++;
										break;
									}
									previous = destination[-1];
									destination--;
								}
								while (previous != '\\');
							}
						}
						source += 2;
					}
					else if (next == '\\' || next == '/')
					{
						source += 2;
					}
					else if (next == 0)
					{
						if (base < destination)
						{
							destination--;
						}
						*destination = 0;
						source += 2;
					}
					else
					{
						*destination = *source;
						source++;
						destination++;
					}
				}
				else
				{
					*destination = *source;
					source++;
					destination++;
				}
			}
			path->SetLength(strlen(base));
		}
		return path;
	}
#endif
}
