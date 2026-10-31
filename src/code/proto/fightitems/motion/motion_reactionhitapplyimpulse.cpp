// Fight items of the motion group: ReactionHitApplyImpulseTrack (unit 0x101A9F10 - 0x101AA2B0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_reactionhitapplyimpulse.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gReactionHitApplyImpulseTrackProperties;  // 0x11254A50

			// FUNCTION: ENGINE 0x101A9F10
			bool ReactionHitApplyImpulseTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A9F30
			bool ReactionHitApplyImpulseTrack::SetImpulseScale(float newValue)
			{
				impulseScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A9F50
			fight::Property* ReactionHitApplyImpulseTrack::GetProperty(int index)
			{
				return gReactionHitApplyImpulseTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101A9F70
			void ReactionHitApplyImpulseTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitApplyImpulseTrackProperties);
			}

			// FUNCTION: ENGINE 0x101A9F80
			ReactionHitApplyImpulseTrack::ReactionHitApplyImpulseTrack() : impulseScale(1.0f), timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101A9FC0
			float ReactionHitApplyImpulseTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101A9FD0
			float ReactionHitApplyImpulseTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101A9FE0
			ReactionHitApplyImpulseTrack::~ReactionHitApplyImpulseTrack()
			{
			}

			// FUNCTION: ENGINE 0x101AA100
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitApplyImpulseTrack::RegisterProperties()
			{
				if (gReactionHitApplyImpulseTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReactionHitApplyImpulseTrack>("timeBegin", &ReactionHitApplyImpulseTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitApplyImpulseTrack>("impulseScale", &ReactionHitApplyImpulseTrack::SetImpulseScale);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionHitApplyImpulseTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AA0D0
			fight::TrackFactory* CreateReactionHitApplyImpulseTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionHitApplyImpulseTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AA1E0
			void RegisterReactionHitApplyImpulseTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionHitApplyImpulseTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<ReactionHitApplyImpulseTrack>;
			template class fight::TrackFactoryTemplate<ReactionHitApplyImpulseTrack>;
			template class fight::TrackFactoryCasterTemplate<ReactionHitApplyImpulseTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101A9FF0
// FUNCTION: ENGINE 0x101AA020
// FUNCTION: ENGINE 0x101AA030
// FUNCTION: ENGINE 0x101AA060
// FUNCTION: ENGINE 0x101AA090
// FUNCTION: ENGINE 0x101AA0C0
// FUNCTION: ENGINE 0x101AA210
// FUNCTION: ENGINE 0x101AA240
// FUNCTION: ENGINE 0x101AA260
