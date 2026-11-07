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
		// FUNCTION: ENGINE 0x104FB7E0
		const fight::Name& DecalTrack::GetShaderName() const
		{
			return shaderName;
		}

		// FUNCTION: ENGINE 0x104FB7F0
		int DecalTrack::GetRandomSelect() const
		{
			return randomSelect;
		}

		// FUNCTION: ENGINE 0x104FB800
		float DecalTrack::GetRandomOrientation() const
		{
			return randomOrientation;
		}

		// FUNCTION: ENGINE 0x104FB810
		bool DecalTrack::GetScaleByDamage() const
		{
			return scaleByDamage;
		}

		// FUNCTION: ENGINE 0x104FB820
		float DecalTrack::GetScaleX() const
		{
			return scaleX;
		}

		// FUNCTION: ENGINE 0x104FB830
		float DecalTrack::GetScaleY() const
		{
			return scaleY;
		}

		// FUNCTION: ENGINE 0x104FB840
		const char* DecalTrack::GetPatch() const
		{
			return patch;
		}

		// FUNCTION: ENGINE 0x104FB850
		int DecalTrack::GetDecalStore() const
		{
			return decalStore;
		}

		// FUNCTION: ENGINE 0x104FB860
		bool DecalTrack::GetCullOffscreen() const
		{
			return cullOffscreen;
		}
	}
}
