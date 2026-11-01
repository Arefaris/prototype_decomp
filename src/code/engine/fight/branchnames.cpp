// The names of the fight chunk and branch records (context, branch, chunk, name, path, version, conditions, tracks, flags and the
// branch kinds); each is built from a text the unit keeps in a variable (unit name guess: the engine's static initialisers
// 0x10D66110 - 0x10D663E0 construct them in one run).
#include "code/core/hash.h"
#include "code/core/name.h"

namespace fight
{
	extern const char* const gPathSeparator;
	extern const char* const gParentPathText;
	extern const char* const gCurrentPathText;
	extern const char* const gContextText;
	extern const char* const gBranchText;
	extern const char* const gChunkText;
	extern const char* const gBranchNameText;
	extern const char* const gPathText;
	extern const char* const gVersionText;
	extern const char* const gSiblingIndexText;
	extern const char* const gConditionsText;
	extern const char* const gTracksText;
	extern const char* const gTrackDisabledText;
	extern const char* const gTrackSlaveText;
	extern const char* const gDebugOnlyText;
	extern const char* const gReferenceBranchName;
	extern const char* const gStoreBranchName;
	extern const char* const gBankBranchName;
	extern const char* const gNodeBranchName;
	extern const char* const gOverrideText;

	core::Name<core::CaseSensitiveKey> gChunkContextKey(gContextText, 0);
	core::Name<core::CaseSensitiveKey> gBranchKey(gBranchText, 0);
	core::Name<core::CaseSensitiveKey> gChunkKey(gChunkText, 0);
	core::Name<core::CaseSensitiveKey> gChunkNameKey(gBranchNameText, 0);
	core::Name<core::CaseSensitiveKey> gBranchPathKey(gPathText, 0);
	core::Name<core::CaseSensitiveKey> gChunkIndexKey(gVersionText, 0);
	core::Name<core::CaseSensitiveKey> gBranchOffsetKey(gSiblingIndexText, 0);
	core::Name<core::CaseSensitiveKey> gConditionsKey(gConditionsText, 0);
	core::Name<core::CaseSensitiveKey> gTracksKey(gTracksText, 0);
	core::Name<core::CaseSensitiveKey> gConditionFlagName(gTrackDisabledText, 0);
	core::Name<core::CaseSensitiveKey> gSlaveKey(gTrackSlaveText, 0);
	core::Name<core::CaseSensitiveKey> gBranchFlagKey(gDebugOnlyText, 0);
	core::Name<core::CaseSensitiveKey> gReferenceKey(gReferenceBranchName, 0);
	core::Name<core::CaseSensitiveKey> gStoreKey(gStoreBranchName, 0);
	core::Name<core::CaseSensitiveKey> gBankKey(gBankBranchName, 0);
	core::Name<core::CaseSensitiveKey> gNodeKey(gNodeBranchName, 0);
	core::Name<core::CaseSensitiveKey> gOverrideKey(gOverrideText, 0);
	unsigned __int64 gPathSeparatorHash = core::Hash64(gPathSeparator, 0);
	unsigned __int64 gParentPathHash = core::Hash64(gParentPathText, 0);
	unsigned __int64 gCurrentPathHash = core::Hash64(gCurrentPathText, 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D66110
// FUNCTION: ENGINE 0x10D66130
// FUNCTION: ENGINE 0x10D66150
// FUNCTION: ENGINE 0x10D66170
// FUNCTION: ENGINE 0x10D66190
// FUNCTION: ENGINE 0x10D661B0
// FUNCTION: ENGINE 0x10D661D0
// FUNCTION: ENGINE 0x10D661F0
// FUNCTION: ENGINE 0x10D66210
// FUNCTION: ENGINE 0x10D66230
// FUNCTION: ENGINE 0x10D66250
// FUNCTION: ENGINE 0x10D66270
// FUNCTION: ENGINE 0x10D66360
// FUNCTION: ENGINE 0x10D66380
// FUNCTION: ENGINE 0x10D663A0
// FUNCTION: ENGINE 0x10D663C0
// FUNCTION: ENGINE 0x10D663E0
// FUNCTION: ENGINE 0x10D86560
// FUNCTION: ENGINE 0x10D86570
// FUNCTION: ENGINE 0x10D86580
// FUNCTION: ENGINE 0x10D86590
// FUNCTION: ENGINE 0x10D865A0
// FUNCTION: ENGINE 0x10D865B0
// FUNCTION: ENGINE 0x10D865C0
// FUNCTION: ENGINE 0x10D865D0
// FUNCTION: ENGINE 0x10D865E0
// FUNCTION: ENGINE 0x10D865F0
// FUNCTION: ENGINE 0x10D86600
// FUNCTION: ENGINE 0x10D86610
// FUNCTION: ENGINE 0x10D86650
// FUNCTION: ENGINE 0x10D86660
// FUNCTION: ENGINE 0x10D86670
// FUNCTION: ENGINE 0x10D86680
// FUNCTION: ENGINE 0x10D86690
// FUNCTION: ENGINE 0x10D660B0
// FUNCTION: ENGINE 0x10D660D0
// FUNCTION: ENGINE 0x10D660F0
