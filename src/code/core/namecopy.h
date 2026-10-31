// The static name tables of the render units build their 32-bit names through two by-value copies (the engine's
// initialisers construct the name from its text, copy it into a temporary and copy that into the variable).
#ifndef CORE_NAMECOPY_H
#define CORE_NAMECOPY_H

#include "code/core/name.h"

namespace core
{
	inline Name<CaseInsensitiveKey32> PassName32(Name<CaseInsensitiveKey32> name)
	{
		return name;
	}
}

#endif
