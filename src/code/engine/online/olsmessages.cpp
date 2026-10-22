// The constructors of the online services' messages the engine kept as functions of their own (the callers build the
// messages inline). The file name is a guess.
#include "code/engine/online/ols.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10886A30
	OLSUserMessage::OLSUserMessage(short newId) : OLSMessage(5, newId)
	{
	}

	// FUNCTION: ENGINE 0x10887D20
	OLSGameMessage::OLSGameMessage(short newId) : OLSMessage(3, newId)
	{
	}

	// FUNCTION: ENGINE 0x1088ACA0
	OLSProfileStorageMessage::OLSProfileStorageMessage(short newId) : OLSMessage(0xB, newId)
	{
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10886A60
// FUNCTION: ENGINE 0x10887320
// FUNCTION: ENGINE 0x10887D50
// FUNCTION: ENGINE 0x10888190
// FUNCTION: ENGINE 0x1088ACE0
// FUNCTION: ENGINE 0x1088AF20
