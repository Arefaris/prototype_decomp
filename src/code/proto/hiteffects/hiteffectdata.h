// Data of the engine that the hit effects read: the enum tables their properties pick from, the numbers of entries and some
// constants their constructors load (all defined by other units; names are guesses).
#ifndef PROTO_HITEFFECTMANAGER_HITEFFECTDATA_H
#define PROTO_HITEFFECTMANAGER_HITEFFECTDATA_H

#include "code/engine/fight/trackfactory.h"

namespace proto
{
	namespace HitEffectManager
	{
		extern fight::EnumEntry gAttackTypeConditionAttackTypeTable[];  // 0x1125B658
		extern fight::EnumEntry gDamageTypeConditionDamageTypeTable[];  // 0x1125B768
		extern fight::EnumEntry gDecalTrackDecalStoreTable[];  // 0x1126F530
		extern fight::EnumEntry gFXLight_PointTrackAttachToTable[];  // 0x1126F570
		extern fight::EnumEntry gFXLight_PointTrackEmitSpaceTable[];  // 0x1126F588
		extern fight::EnumEntry gFXLight_PointTrackAttachSpaceTable[];  // 0x1126F5B0
		extern fight::EnumEntry gDamageTakenConditionCompareTable[];  // 0x11276158
		extern fight::EnumEntry gReceiverGrabbableClassConditionCompareTable[];  // 0x112761B0
		extern const int gAttackTypeConditionAttackTypeCount;  // 0x10DE69A0
		extern const int gDamageTypeConditionDamageTypeCount;  // 0x10DE69A4
		extern const int gDecalTrackDecalStoreCount;  // 0x10E1D4A8
		extern const int gFXLight_PointTrackAttachToCount;  // 0x10E1D6FC
		extern const int gFXLight_PointTrackAttachSpaceCount;  // 0x10E1D880
		extern const int gFXLight_PointTrackEmitSpaceCount;  // 0x10E1D884
		extern const int gDamageTakenConditionCompareCount;  // 0x10E2C7D8
		extern const int gReceiverGrabbableClassConditionCompareCount;  // 0x10E2C7DC
	}
}

#endif
