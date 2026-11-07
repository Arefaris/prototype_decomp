// proto::HitEffectManager::DecalAction: the action half of the decal fight item (see hiteffect_decal.h). The unit starts
// at 0x104FB8A0 with the registration of the decal track; no assert path names it, so the file name is a guess.
#include "code/proto/hiteffects/hiteffect_decal.h"

namespace proto
{
	namespace HitEffectManager
	{
		// FUNCTION: ENGINE 0x104FBA20
		DecalAction::DecalAction(DecalTrack* newTrack, HitEffectParams* newParams) : fight::Action(0x200), link(newTrack), params(0)
		{
			core::RefAssign(params, newParams);
		}

		// FUNCTION: ENGINE 0x104FB980
		DecalAction::~DecalAction()
		{
			core::SafeRelease(params);
		}
	}
}
