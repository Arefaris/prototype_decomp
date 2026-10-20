// pure3d::Entity (code/pure3d/src/entity.cpp, file name guessed from the class): the named, reference counted base of
// the render objects. Names are guesses.
#include "code/pure3d/entity.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1072D4B0
	Entity::Entity()
	{
	}

	// FUNCTION: ENGINE 0x1072D4E0
	Entity::~Entity()
	{
	}

	// FUNCTION: ENGINE 0x1072D4F0
	void Entity::SetName(const core::Name<core::CaseSensitiveKey>& name)
	{
		mName = name;
	}

	// FUNCTION: ENGINE 0x1072D500
	void Entity::SetNameFrom(const Entity* other)
	{
		if (other != 0)
		{
			mName = other->mName;
		}
	}

	// FUNCTION: ENGINE 0x1072D520
	void Entity::SetNameText(const char* text)
	{
		mName.SetText(text);
	}

	// FUNCTION: ENGINE 0x1072D530
	void Entity::SetName(unsigned __int64 name)
	{
		mName.SetHash(name);
	}
}
