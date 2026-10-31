// Fight items of the motion group: ReactionTargetGiverTrack (unit 0x101A8000 - 0x101A8330; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_reactiontargetgiver.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gReactionTargetGiverTrackProperties;  // 0x11254A10

			// FUNCTION: ENGINE 0x101A8000
			bool ReactionTargetGiverTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A8020
			fight::Property* ReactionTargetGiverTrack::GetProperty(int index)
			{
				return gReactionTargetGiverTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101A8040
			void ReactionTargetGiverTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReactionTargetGiverTrackProperties);
			}

			// FUNCTION: ENGINE 0x101A8050
			ReactionTargetGiverTrack::ReactionTargetGiverTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101A8080
			float ReactionTargetGiverTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101A8090
			float ReactionTargetGiverTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101A80A0
			ReactionTargetGiverTrack::~ReactionTargetGiverTrack()
			{
			}

			// FUNCTION: ENGINE 0x101A81C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionTargetGiverTrack::RegisterProperties()
			{
				if (gReactionTargetGiverTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReactionTargetGiverTrack>("timeBegin", &ReactionTargetGiverTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gReactionTargetGiverTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A8190
			fight::TrackFactory* CreateReactionTargetGiverTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionTargetGiverTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A8260
			void RegisterReactionTargetGiverTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionTargetGiverTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<ReactionTargetGiverTrack>;
			template class fight::TrackFactoryTemplate<ReactionTargetGiverTrack>;
			template class fight::TrackFactoryCasterTemplate<ReactionTargetGiverTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101A80B0
// FUNCTION: ENGINE 0x101A80E0
// FUNCTION: ENGINE 0x101A80F0
// FUNCTION: ENGINE 0x101A8120
// FUNCTION: ENGINE 0x101A8150
// FUNCTION: ENGINE 0x101A8180
// FUNCTION: ENGINE 0x101A8290
// FUNCTION: ENGINE 0x101A82C0
// FUNCTION: ENGINE 0x101A82E0
