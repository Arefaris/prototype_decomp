// Data of the engine that the proplogic fight items read: the enum tables their properties pick from, the numbers of entries and some
// constants their constructors load (all defined by other units; names are guesses).
#ifndef PROTO_FIGHTITEMS_PROPLOGIC_DATA_H
#define PROTO_FIGHTITEMS_PROPLOGIC_DATA_H

#include "code/engine/fight/trackfactory.h"

namespace proto
{
	namespace fightitems
	{
		namespace proplogic
		{
			extern fight::EnumEntry gShootingEventConditionEventTable[];  // 0x11255D10
			extern const int gWaitOnCollisionTrackCollideWithDefault;  // 0x11060100
			extern const int gOnCollisionTrackCollideWithDefault;  // 0x11060104
		}
	}
}

#endif
