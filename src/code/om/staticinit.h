// How the engine's static initialisers build the om library's names and strings from a text: the string is a named
// temporary (read through the frame, destroyed after the result is stored); the string variables are copied from it.
#ifndef OM_STATICINIT_H
#define OM_STATICINIT_H

#include "code/core/hash.h"
#include "code/om/name.h"
#include "code/om/string.h"

namespace om
{
	// The 64-bit name of a text that the initialiser holds in a string first (the name is stored before the string goes)
	inline ClassName NameOfText(const char* text)
	{
		String string(text, 0);
		return ClassName(core::Hash64(string.GetText(), 0));
	}

	// A string variable's value: a text that stays where it is, copied out of a temporary
	inline String StringOfText(const char* text)
	{
		String string(text, 0);
		return String(string);
	}
}

#endif
