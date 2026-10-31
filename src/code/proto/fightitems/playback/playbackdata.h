// Data of the engine that the playback fight items read: the enum tables their properties pick from, the numbers of entries and some
// constants their constructors load (all defined by other units; names are guesses).
#ifndef PROTO_FIGHTITEMS_PLAYBACK_DATA_H
#define PROTO_FIGHTITEMS_PLAYBACK_DATA_H

#include "code/engine/fight/trackfactory.h"

namespace proto
{
	namespace fightitems
	{
		namespace playback
		{
			extern fight::EnumEntry gShootingEventConditionEventTable[];  // 0x11255D10
			extern fight::EnumEntry gFogTrackFadingFunctionTable[];  // 0x11255D68
			extern fight::EnumEntry gFogTrackEmitSpaceTable[];  // 0x11255D80
			extern fight::EnumEntry gTimeOfDayBlendTrackLevelTable[];  // 0x11255DA8
			extern fight::EnumEntry gScenarioMessageTrackEventTable[];  // 0x11255E80
			extern fight::EnumEntry gAlertVariableConditionVariableTable[];  // 0x11255EA0
			extern fight::EnumEntry gDisguiseReactionConditionReactionTable[];  // 0x11255F58
			extern fight::EnumEntry gSetPanicStateTrackPanicTypeTable[];  // 0x11256158
			extern fight::EnumEntry gInZoneConditionZoneTypeTable[];  // 0x112561E0
			extern fight::EnumEntry gOnlineSetPairingVolumeStateTrackVolumeTypeTable[];  // 0x1126E3B8
			extern fight::EnumEntry gOnlineTestForRespawnStateConditionStateTable[];  // 0x1126E3C0
			extern const int gFogTrackEmitSpaceCount;  // 0x10DDCB94
			extern const int gFogTrackFadingFunctionCount;  // 0x10DDCB98
			extern const int gTimeOfDayBlendTrackLevelCount;  // 0x10DDCE84
			extern const int gAlertVariableConditionVariableCount;  // 0x10DDE784
			extern const int gScenarioMessageTrackEventCount;  // 0x10DDE788
			extern const int gDisguiseReactionConditionReactionCount;  // 0x10DDEE84
			extern const int gSetPanicStateTrackPanicTypeCount;  // 0x10DE0C34
			extern const int gInZoneConditionZoneTypeCount;  // 0x10DE1994
			extern const int gOnlineTestForRespawnStateConditionStateCount;  // 0x10E17B34
			extern const int gOnlineSetPairingVolumeStateTrackVolumeTypeCount;  // 0x10E17B3C
			extern const int gWaitOnCollisionTrackCollideWithDefault;  // 0x11060100
			extern const int gOnCollisionTrackCollideWithDefault;  // 0x11060104
		}
	}
}

#endif
