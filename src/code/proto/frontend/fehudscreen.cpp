#include "code/proto/frontend/fehudscreen.h"

#include "code/proto/frontend/fehudcombatconclusion.h"
#include "code/proto/frontend/fehudkeycard.h"
#include "code/proto/frontend/fehudtextlog.h"

namespace proto
{
	// The screen deletes its elements; the delete expressions make the compiler emit the deleting destructors the engine's
	// screen unit holds (0x104C0650, 0x104C0680, 0x104C06B0, 0x104C06E0, 0x104C0710, 0x104C0740, 0x104C0770, 0x104C07A0, 0x104C07D0, 0x104C0800, 0x104C0830, 0x104C0860, 0x104C0890, 0x104C08C0, 0x104C08F0). The
	// destructor itself is not reconstructed (the engine's also lets go of the other elements).
	FEHudScreen::~FEHudScreen()
	{
		delete miniMap;
		delete health;
		delete powers;
		delete buttonHint;
		delete evolutionPoints;
		delete meter;
		delete typewriter;
		delete targeting;
		delete popup;
		delete eventPopup;
		delete opportunityEventPopup;
		delete missionPopup;
		delete keyCard;
		delete combatConclusion;
		delete textLog;
	}
}
