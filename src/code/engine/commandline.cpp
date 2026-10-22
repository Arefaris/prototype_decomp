// The command line options of the engine (this unit 0x10848C70 - 0x10849090; no assert path, file name is a guess): the
// words of the command line and of an options file are kept one after the other in a buffer of their own, with a table
// of the words; an option is "name" or "name=value". The two script functions opt_GetKey and opt_GetKeyValue ask
// them.
#include "code/core/file/filesystem.h"
#include "code/content/metastream.h"
#include "code/core/heap.h"
#include "code/core/strings.h"
#include "code/engine/luascriptmanager.h"
#include <new>
#include <stdlib.h>
#include <string.h>

namespace engine
{
	// The words of the options: characters one after the other (0x1130EAD0), the table of their starts (0x1130EED0),
	// the characters used and the words in the table (names guessed)
	char gCommandLineBuffer[0x400];
	char* gCommandLineWords[0x40];
	int gCommandLineLength;
	unsigned int gCommandLineCount;

	// FUNCTION: ENGINE 0x10848C70
	void ParseCommandLine(const char* commandLine)
	{
		gCommandLineLength = strlen(commandLine) + 1;
		core::StrCpy(gCommandLineBuffer, commandLine);
		char* word = core::StrTok(gCommandLineBuffer, " \t,");
		while (word != 0)
		{
			gCommandLineWords[gCommandLineCount] = word;
			gCommandLineCount++;
			word = core::StrTok(0, " \t,");
		}
	}

	// FUNCTION: ENGINE 0x10848CF0
	// EQUIVALENT: shrink-wrap (the engine saves esi and edi in the entry block, ours after the early exit), 34.8 %
	bool LoadCommandLineFile(const char* path)
	{
		core::IFile* file;
		core::FileSystemOpenFile(&file, path, false, 0, 1, 0, 1, 1, 0);
		if (!file->IsOpen())
		{
			file->Release();
			return false;
		}
		unsigned int size = file->GetCurrentSize();
		char* buffer;
		{
			core::HeapScope scope(1);
			buffer = new char[size];
		}
		file->ReadWait(buffer, size, 1);
		file->Release();
		content::MemoryReadStream stream(buffer, size);
		content::TextReadStream reader(&stream, false, 0);
		char word[0x100];
		while (reader.ReadToken(word, 0x100, false))
		{
			char* start = gCommandLineBuffer + gCommandLineLength;
			gCommandLineWords[gCommandLineCount] = start;
			gCommandLineCount++;
			core::StrCpy(start, word);
			gCommandLineLength += strlen(word) + 1;
		}
		delete[] buffer;
		return true;
	}

	// FUNCTION: ENGINE 0x10848E50
	void UnregisterCommandLineScripts()
	{
		LuaScriptManager* manager = GetScriptManager();
		manager->Unregister(gCommandLineBuffer);
	}

	// FUNCTION: ENGINE 0x10848E70
	bool HasCommandLineOption(const char* option)
	{
		unsigned int length = strlen(option);
		for (unsigned int i = 0; i < gCommandLineCount; i++)
		{
			if (core::StrNICmp(gCommandLineWords[i], option, length) == 0)
			{
				char next = gCommandLineWords[i][length];
				if (next == 0 || next == '=')
				{
					return true;
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10848EE0
	const char* GetCommandLineValue(const char* option)
	{
		unsigned int length = strlen(option);
		for (unsigned int i = 0; i < gCommandLineCount; i++)
		{
			if (core::StrNICmp(gCommandLineWords[i], option, length) == 0 && gCommandLineWords[i][length] == '=')
			{
				return gCommandLineWords[i] + length + 1;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10848F50
	int GetCommandLineInt(const char* option, int defaultValue)
	{
		const char* value = GetCommandLineValue(option);
		if (value != 0)
		{
			char* end = 0;
			long number = strtol(value, &end, 10);
			if (end != value && number + 0x7fffffffU <= 0xfffffffdU)
			{
				return number;
			}
		}
		return defaultValue;
	}

	// FUNCTION: ENGINE 0x10848FA0
	void AddCommandLineOption(const char* option)
	{
		if (!HasCommandLineOption(option))
		{
			char* word = gCommandLineBuffer + gCommandLineLength;
			gCommandLineWords[gCommandLineCount] = word;
			gCommandLineCount++;
			core::StrCpy(word, option);
			gCommandLineLength += strlen(option) + 1;
		}
	}

	// FUNCTION: ENGINE 0x10849000
	// EQUIVALENT: the same tests and results, the engine places the block that returns the minimum last, ours first, 70.5 %
	int GetCommandLineIntClamped(const char* option, int defaultValue, int minimum, int maximum)
	{
		int value = GetCommandLineInt(option, defaultValue);
		if (value < minimum)
		{
			if (value <= maximum)
			{
				return minimum;
			}
		}
		else if (value <= maximum)
		{
			return value;
		}
		return maximum;
	}

	// FUNCTION: ENGINE 0x10849030
	void RegisterCommandLineScripts()
	{
		LuaScriptManager* manager = GetScriptManager();
		manager->SetOwner(gCommandLineBuffer);
		manager->Register("opt_GetKey", HasCommandLineOption);
		manager->Register("opt_GetKeyValue", GetCommandLineValue);
		manager->ClearOwner();
	}
}
