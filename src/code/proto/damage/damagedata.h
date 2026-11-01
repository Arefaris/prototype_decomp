// Data of the engine that the damage tracks read: the enum tables their properties pick from, the numbers of entries and some
// constants their constructors load (all defined by other units; names are guesses).
#ifndef PROTO_DAMAGEDATA_H
#define PROTO_DAMAGEDATA_H

#include "code/engine/fight/trackfactory.h"

namespace proto
{
	extern fight::EnumEntry gCauseDamageTrackAttackTypeTable[];  // 0x1125B658
	extern fight::EnumEntry gDebugDamageTrackDamageTypeTable[];  // 0x1125B768
	extern fight::EnumEntry gCauseDamageTrackOriginatorTable[];  // 0x1126F4F8
	extern const int gCauseDamageTrackAttackTypeCount;  // 0x10DE69A0
	extern const int gDebugDamageTrackDamageTypeCount;  // 0x10DE69A4
	extern const int gCauseDamageTrackOriginatorCount;  // 0x10E1D284
}

#endif
