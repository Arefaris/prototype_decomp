// Data of the engine that the motion group read: the enum tables their properties pick from, the numbers of entries and some
// constants their constructors load (all defined by other units; names are guesses).
#ifndef PROTO_FIGHTITEMS_MOTION_WORLDDAMAGEDATA_H
#define PROTO_FIGHTITEMS_MOTION_WORLDDAMAGEDATA_H

#include "code/engine/fight/trackfactory.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			extern fight::EnumEntry gWorldDamageTrackAttackTypeTable[];  // 0x1125B658
			extern fight::EnumEntry gWorldDamageTrackDamageTypeTable[];  // 0x1125B768
			extern fight::EnumEntry gWorldDamageTrackPropAreaEmissionScaleFunctionTable[];  // 0x1126F468
			extern const int gWorldDamageTrackAttackTypeCount;  // 0x10DE69A0
			extern const int gWorldDamageTrackDamageTypeCount;  // 0x10DE69A4
			extern const int gWorldDamageTrackPropAreaEmissionScaleFunctionCount;  // 0x10E1BE84
		}
	}
}

#endif
