// engine::OLSFriend: see olsfriend.h.
#include "code/engine/online/olsfriend.h"
#include "code/engine/luascriptmanager.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108E9C30
	OLSFriendEntry::~OLSFriendEntry()
	{
	}

	// FUNCTION: ENGINE 0x108EA320
	// EQUIVALENT: register allocation (the engine keeps this in ebx, the element count in esi and the end of the array in edi, ours this in esi); every other instruction is the engine's
	OLSFriend::~OLSFriend()
	{
		GetScriptManager()->Unregister(this);
		if (entries != 0)
		{
			// The element count sits in the word before the array
			int* block = (int*)entries - 1;
			int index = *block;
			OLSFriendEntry* element = entries + index;
			while (--index >= 0)
			{
				element--;
				element->~OLSFriendEntry();
			}
			operator delete[](block);
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108EA390
// FUNCTION: ENGINE 0x108EA3A0
// FUNCTION: ENGINE 0x108EA3B0
// FUNCTION: ENGINE 0x108EA3C0
// FUNCTION: ENGINE 0x108EA3D0
// FUNCTION: ENGINE 0x108EA3E0
// FUNCTION: ENGINE 0x108EA3F0
// FUNCTION: ENGINE 0x108EA400
// FUNCTION: ENGINE 0x108EA410
// FUNCTION: ENGINE 0x108EA420
// FUNCTION: ENGINE 0x108EA430
// FUNCTION: ENGINE 0x108EA440
// FUNCTION: ENGINE 0x108EA450
// FUNCTION: ENGINE 0x108EA460
// FUNCTION: ENGINE 0x108EA470
// FUNCTION: ENGINE 0x108EA480
// FUNCTION: ENGINE 0x108EA490
// FUNCTION: ENGINE 0x108EA4A0
// FUNCTION: ENGINE 0x108EA4B0
// FUNCTION: ENGINE 0x108EA4C0
// FUNCTION: ENGINE 0x108EA4D0
// FUNCTION: ENGINE 0x108EA4E0
// FUNCTION: ENGINE 0x108EA8A0
