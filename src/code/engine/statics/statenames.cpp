// The names of the state, state machine, transition and camera inventory texts, each built from a text the unit keeps in a variable (unit
// name guess: the engine's static initialisers 0x10D4FF80 - 0x10D54A30).
#include "code/core/name.h"

namespace engine
{
	extern const char* const gStateText;
	extern const char* const gStatemachineText;
	extern const char* const gTransitionText;
	extern const char* const gCameraInventoryText;

	core::Name<core::CaseSensitiveKey> gStateKey(gStateText, 0);
	core::Name<core::CaseSensitiveKey> gStatemachineKey(gStatemachineText, 0);
	core::Name<core::CaseSensitiveKey> gTransitionKey(gTransitionText, 0);
	core::Name<core::CaseSensitiveKey> gCameraInventoryKey(gCameraInventoryText, 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D4FF80
// FUNCTION: ENGINE 0x10D4FFB0
// FUNCTION: ENGINE 0x10D50010
// FUNCTION: ENGINE 0x10D54A30
// FUNCTION: ENGINE 0x10D81C60
// FUNCTION: ENGINE 0x10D81C70
// FUNCTION: ENGINE 0x10D81C90
// FUNCTION: ENGINE 0x10D82E00
