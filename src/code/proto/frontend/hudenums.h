// The enumerations of the head-up display that the scripts name (reflection names proto::HUDTransformationSlot and
// proto::HUDPower; the values are original). Unit 0x104B0950 - 0x104B09D0 (no assert path; the file name is a guess).
#ifndef PROTO_FRONTEND_HUDENUMS_H
#define PROTO_FRONTEND_HUDENUMS_H

#include "code/content/metatype.h"

namespace proto
{
	// The four slots of the transformation powers
	enum HUDTransformationSlot
	{
		HUDSLOT_ATTACK = 0,
		HUDSLOT_DEFENSE = 1,
		HUDSLOT_SENSES = 2,
		HUDSLOT_DISGUISE = 3
	};

	// The powers the interface knows
	enum HUDPower
	{
		HUDPOWER_NONE = 0,
		HUDPOWER_CLAWS = 1,
		HUDPOWER_BLADES = 2,
		HUDPOWER_HAMMERFIST = 3,
		HUDPOWER_WHIPFIST = 4,
		HUDPOWER_MUSCLEMASS = 5,
		HUDPOWER_ARMOUR = 6,
		HUDPOWER_SPINES = 7,
		HUDPOWER_SHIELD = 8,
		HUDPOWER_CHAMELEONICSKIN = 9,
		HUDPOWER_THERMALVISION = 10,
		HUDPOWER_MOTHERVISION = 11,
		HUDPOWER_DISGUISE = 12,
		HUDPOWER_ALEX = 13
	};
}

#endif
