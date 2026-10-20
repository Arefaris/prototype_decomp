// The factory makers of three fight nodes whose classes belong to other units: the exit track (RTTI:
// engine::ExitTrack) and the message and print message conditions (engine::MessageCondition /
// engine::PrintMessageCondition). The unit runs 0x108123A0 - 0x108127E0 (no assert path; file name guessed); the
// classes keep their constructors, property lists and slot bodies in 0x108B6C40 - 0x108B71E0, so only what the
// factory templates touch is declared here: the sizes, the constructors and the property list functions.
#ifndef ENGINE_FIGHT_EXITFACTORIES_H
#define ENGINE_FIGHT_EXITFACTORIES_H

#include "code/engine/fight/exittracks.h"

namespace engine
{
	// 0x108127A0 / 0x108127C0 / 0x108127E0
	fight::TrackFactory* CreateExitTrackFactory(const char* name);
	fight::ConditionFactory* CreateMessageConditionFactory(const char* name);
	fight::ConditionFactory* CreatePrintMessageConditionFactory(const char* name);
}

#endif
