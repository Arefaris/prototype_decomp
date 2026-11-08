// The unit of the marker manager (0x104B56A0 - 0x104BA3C0): the out-of-line copies of the marker messages' members. The
// file name is a guess.
#include "code/proto/frontend/markermessages.h"

namespace proto
{
	// Makes one of each message with inlining off, so that the unit has the out-of-line copies the engine's unit has (this
	// function is not the engine's)
#pragma inline_depth(0)
	void ReferenceMarkerMessages()
	{
		SetIsMarkedMessage marked(0, 0);
		GetMarkerCallerTypeMessage caller;
		delete new SetIsMarkedMessage(0, 0);
		delete new GetMarkerCallerTypeMessage;
	}
#pragma inline_depth()
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104B56A0
// FUNCTION: ENGINE 0x104B56E0
// FUNCTION: ENGINE 0x104B56F0
// FUNCTION: ENGINE 0x104B5720
// FUNCTION: ENGINE 0x104B5CB0
// FUNCTION: ENGINE 0x104B5CE0
