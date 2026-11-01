// The names of the persistent group and the NIS and playback nodes, each built from a text the unit keeps in a variable (unit
// name guess: the engine's static initialisers 0x10D74CC0 - 0x10D77F40).
#include "code/core/name.h"

namespace engine
{
	extern const char* const gPersistentText;
	extern const char* const gNISNodeText;
	extern const char* const gNISRootNodeText;
	extern const char* const gPlaybackSetText;
	extern const char* const gPlaybackNodeText;

	core::Name<core::CaseSensitiveKey> gPersistentKey(gPersistentText, 0);
	core::Name<core::CaseSensitiveKey> gNISNodeKey(gNISNodeText, 0);
	core::Name<core::CaseSensitiveKey> gNISRootNodeKey(gNISRootNodeText, 0);
	core::Name<core::CaseSensitiveKey> gPlaybackSetKey(gPlaybackSetText, 0);
	core::Name<core::CaseSensitiveKey> gPlaybackNodeKey(gPlaybackNodeText, 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D74CC0
// FUNCTION: ENGINE 0x10D77BD0
// FUNCTION: ENGINE 0x10D77BF0
// FUNCTION: ENGINE 0x10D77F00
// FUNCTION: ENGINE 0x10D77F40
// FUNCTION: ENGINE 0x10D8A0C0
// FUNCTION: ENGINE 0x10D8AD30
// FUNCTION: ENGINE 0x10D8AD40
// FUNCTION: ENGINE 0x10D8AE20
// FUNCTION: ENGINE 0x10D8AE40
