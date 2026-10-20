// content::NamedMetaType: the list of the reflected classes' meta types (unit around 0x10600130; the file name is
// guessed).
#include "code/content/metatype.h"
#include <string.h>

namespace content
{
	// The newest named meta type (0x1127694C, name guessed)
	extern NamedMetaType* gFirstNamedMetaType;

	// FUNCTION: ENGINE 0x10600130
	NamedMetaType::NamedMetaType(const char* newName, unsigned short newVersion, const char* code)
		: MetaType(code)
	{
		version = newVersion;
		name = newName;
		next = gFirstNamedMetaType;
		gFirstNamedMetaType = this;
	}

	// FUNCTION: ENGINE 0x10600170
	NamedMetaType* NamedMetaType::GetFirst(NamedMetaType** iterator)
	{
		*iterator = gFirstNamedMetaType;
		return gFirstNamedMetaType;
	}

	// FUNCTION: ENGINE 0x10600190
	void NamedMetaType::Next(NamedMetaType** iterator)
	{
		if (*iterator != 0)
		{
			*iterator = (*iterator)->next;
		}
	}

	// FUNCTION: ENGINE 0x106001A0
	NamedMetaType* NamedMetaType::GetByIndex(unsigned short index)
	{
		NamedMetaType* type = gFirstNamedMetaType;
		for (unsigned short i = 0; i < index && type != 0; i++)
		{
			type = type->next;
		}
		return type;
	}

	// FUNCTION: ENGINE 0x106001D0
	NamedMetaType* NamedMetaType::Find(const char* name, unsigned short version)
	{
		for (NamedMetaType* type = gFirstNamedMetaType; type != 0; type = type->next)
		{
			if (type->name != 0 && strcmp(type->name, name) == 0 && type->version == version)
			{
				return type;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10600230
	const char* NamedMetaType::GetName()
	{
		return name;
	}

	// FUNCTION: ENGINE 0x10600240
	unsigned short NamedMetaType::GetVersion()
	{
		return version;
	}

	// FUNCTION: ENGINE 0x10600250
	int NamedMetaType::GetIndex()
	{
		int index = 0;
		NamedMetaType* type = gFirstNamedMetaType;
		while (type != this)
		{
			type = type->next;
			if (type == 0)
			{
				return index;
			}
			index++;
		}
		return index;
	}
}
