#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "code/core/language.h"
#include "code/core/platform.h"
#include "code/core/strings.h"

// The advapi32 imports (see controllerdirectinput.cpp)
extern "C"
{
	__declspec(dllimport) long __stdcall RegOpenKeyExA(void* key, const char* subKey, unsigned long options,
		unsigned long access, void** result);
	__declspec(dllimport) long __stdcall RegCreateKeyExA(void* key, const char* subKey, unsigned long reserved,
		char* className, unsigned long options, unsigned long access, void* security, void** result,
		unsigned long* disposition);
	__declspec(dllimport) long __stdcall RegCloseKey(void* key);
	__declspec(dllimport) long __stdcall RegSetValueExA(void* key, const char* name, unsigned long reserved,
		unsigned long type, const void* data, unsigned long size);
	__declspec(dllimport) long __stdcall RegQueryValueExA(void* key, const char* name, unsigned long* reserved,
		unsigned long* type, void* data, unsigned long* size);
}
#pragma comment(linker, "/alternatename:__imp__RegOpenKeyExA@20=__imp__RegOpenKeyExA")
#pragma comment(linker, "/alternatename:__imp__RegCreateKeyExA@36=__imp__RegCreateKeyExA")
#pragma comment(linker, "/alternatename:__imp__RegCloseKey@4=__imp__RegCloseKey")
#pragma comment(linker, "/alternatename:__imp__RegSetValueExA@24=__imp__RegSetValueExA")
#pragma comment(linker, "/alternatename:__imp__RegQueryValueExA@24=__imp__RegQueryValueExA")

#define HKEY_LOCAL_MACHINE ((void*)0x80000002)
#define KEY_READ 0x20019
#define KEY_ALL_ACCESS 0xF003F
#define REG_SZ 1

// The language entry points and the system language (all names guessed; unit 0x10643EF0 - 0x106444C5, file name
// guessed): the installer's language from the registry key named by the platform, and the conversions between
// language codes and names
namespace core
{
	// FUNCTION: ENGINE 0x10643EF0
	int GetLanguage()
	{
		return gLanguage;
	}

	// FUNCTION: ENGINE 0x10643F00
	void LanguageInit()
	{
		InitLanguage();
	}

	// FUNCTION: ENGINE 0x10643F10
	void LanguageShutdown()
	{
		ShutdownLanguage();
	}

	// FUNCTION: ENGINE 0x10643F20
	// Writes the number as a string value under HKEY_LOCAL_MACHINE (creating the key)
	bool WriteRegistryInt(const char* subKey, const char* name, int value)
	{
		if (name == 0)
		{
			return false;
		}
		void* key;
		unsigned long disposition;
		char text[0x20];
		if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, subKey, 0, KEY_ALL_ACCESS, &key) != 0 &&
			RegCreateKeyExA(HKEY_LOCAL_MACHINE, subKey, 0, 0, 0, KEY_ALL_ACCESS, 0, &key, &disposition) != 0)
		{
			RegCloseKey(key);
			return false;
		}
		sprintf(text, "%d", value);
		long result = RegSetValueExA(key, name, 0, REG_SZ, text, 4);
		RegCloseKey(key);
		return result == 0;
	}

	// FUNCTION: ENGINE 0x10643FE0
	// A string value under HKEY_LOCAL_MACHINE as a number, -1 when it cannot be read
	int ReadRegistryInt(const char* subKey, const char* name)
	{
		void* key;
		unsigned long size;
		unsigned long type;
		char text[0x20];
		if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, subKey, 0, KEY_READ, &key) != 0)
		{
			RegCloseKey(key);
			return -1;
		}
		type = REG_SZ;
		size = 0x20;
		if (RegQueryValueExA(key, name, 0, &type, text, &size) == 0)
		{
			RegCloseKey(key);
			return atoi(text);
		}
		RegCloseKey(key);
		return -1;
	}

	// FUNCTION: ENGINE 0x10644080
	// The language the game was installed in: the platform's two strings name the registry key and value
	int GetSystemLanguage()
	{
		char key[0x100];
		char name[0x100];
		GetPlatform()->GetName(key);
		GetPlatform()->GetPath(name);
		switch (ReadRegistryInt(key, name))
		{
		case '?':
			return '?';
		case 'C':
			return 'C';
		case 'D':
			return 'D';
		case 'E':
			return 'E';
		case 'F':
			return 'F';
		case 'G':
			return 'G';
		case 'I':
			return 'I';
		case 'J':
			return 'J';
		case 'K':
			return 'K';
		case 'P':
			return 'P';
		case 'Q':
			return 'Q';
		case 'R':
			return 'R';
		case 'S':
			return 'S';
		case 'U':
			return 'U';
		case 'W':
			return 'W';
		case 'V':
			return 'V';
		case 'N':
			return 'N';
		}
		return '?';
	}

	// FUNCTION: ENGINE 0x10644210
	void LanguageSet(int language)
	{
		SetLanguage(language);
	}

	// FUNCTION: ENGINE 0x10644220
	int LanguageGet()
	{
		return gLanguage;
	}

	// FUNCTION: ENGINE 0x10644230
	void LanguageAddListener(ILanguageListener* listener)
	{
		AddLanguageListener(listener);
	}

	// FUNCTION: ENGINE 0x10644240
	void LanguageRemoveListener(ILanguageListener* listener)
	{
		RemoveLanguageListener(listener);
	}

	// FUNCTION: ENGINE 0x10644250
	const char* GetLanguageName(int language)
	{
		switch (language)
		{
		case '?':
			return "unknown";
		case 'C':
			return "chinese";
		case 'D':
			return "dutch";
		case 'E':
			return "english";
		case 'F':
			return "french";
		case 'G':
			return "german";
		case 'I':
			return "italian";
		case 'J':
			return "japanese";
		case 'K':
			return "korean";
		case 'P':
			return "portuguese";
		case 'Q':
			return "chinesesimplified";
		case 'R':
			return "russian";
		case 'S':
			return "spanish";
		case 'U':
			return "finnish";
		case 'W':
			return "swedish";
		case 'V':
			return "danish";
		case 'N':
			return "norwegian";
		}
		return "unknown";
	}

	// FUNCTION: ENGINE 0x10644330
	int GetLanguageCode(const char* name)
	{
		if (StrICmp(name, "english") == 0)
		{
			return 'E';
		}
		if (StrICmp(name, "french") == 0)
		{
			return 'F';
		}
		if (StrICmp(name, "spanish") == 0)
		{
			return 'S';
		}
		if (StrICmp(name, "chinese") == 0)
		{
			return 'C';
		}
		if (StrICmp(name, "dutch") == 0)
		{
			return 'D';
		}
		if (StrICmp(name, "german") == 0)
		{
			return 'G';
		}
		if (StrICmp(name, "italian") == 0)
		{
			return 'I';
		}
		if (StrICmp(name, "japanese") == 0)
		{
			return 'J';
		}
		if (StrICmp(name, "korean") == 0)
		{
			return 'K';
		}
		if (StrICmp(name, "portuguese") == 0)
		{
			return 'P';
		}
		if (StrICmp(name, "chinesesimplified") == 0)
		{
			return 'Q';
		}
		if (StrICmp(name, "russian") == 0)
		{
			return 'R';
		}
		if (StrICmp(name, "finnish") == 0)
		{
			return 'U';
		}
		if (StrICmp(name, "swedish") == 0)
		{
			return 'W';
		}
		if (StrICmp(name, "danish") == 0)
		{
			return 'V';
		}
		if (StrICmp(name, "norwegian") == 0)
		{
			return 'N';
		}
		return '?';
	}
}
