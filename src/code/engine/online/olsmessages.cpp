// The constructors of the online services' messages the engine kept as functions of their own (the callers build the
// messages inline). The file name is a guess.
#include "code/engine/online/ols.h"

namespace engine
{
	// The engine's out-of-line copies of the inline constructor and destructor of the user message (0x10886A30 and
	// 0x10886A60) come from a call that is not expanded
#pragma inline_depth(0)
	void KeepUserMessageCopies()
	{
		OLSUserMessage message(0);
	}
#pragma inline_depth()

	// The same for the game message (0x10887D20)
#pragma inline_depth(0)
	void KeepGameMessageCopies()
	{
		OLSGameMessage message(0);
	}
#pragma inline_depth()

	// FUNCTION: ENGINE 0x1088ACA0
	OLSProfileStorageMessage::OLSProfileStorageMessage(short newId) : OLSMessageWords(0xB, newId)
	{
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10886A30
// FUNCTION: ENGINE 0x10886A60
// FUNCTION: ENGINE 0x10887320
// FUNCTION: ENGINE 0x10887D20
// FUNCTION: ENGINE 0x10887D50
// FUNCTION: ENGINE 0x10888190
// FUNCTION: ENGINE 0x1088ACE0
// FUNCTION: ENGINE 0x1088AF20
