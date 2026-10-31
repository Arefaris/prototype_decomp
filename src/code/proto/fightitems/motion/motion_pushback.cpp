// Fight items of the motion group: PushbackVelocityCondition, PushbackDirectionCondition, ReactionHitPushbackAddTrack (unit 0x101AA2B0 - 0x101AADF0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_pushback.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gPushbackVelocityConditionProperties;  // 0x11254A54

			// FUNCTION: ENGINE 0x101AA2B0
			bool PushbackVelocityCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AA2C0
			bool PushbackVelocityCondition::SetVelocity(float newValue)
			{
				velocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AA360
			fight::Property* PushbackVelocityCondition::GetProperty(int index)
			{
				return gPushbackVelocityConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101AA380
			void PushbackVelocityCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPushbackVelocityConditionProperties);
			}

			// FUNCTION: ENGINE 0x101AA390
			PushbackVelocityCondition::PushbackVelocityCondition() : fight::Condition(0), velocity(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101AA3C0
			PushbackVelocityCondition::~PushbackVelocityCondition()
			{
			}

			// FUNCTION: ENGINE 0x101AA8D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PushbackVelocityCondition::RegisterProperties()
			{
				if (gPushbackVelocityConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<PushbackVelocityCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &PushbackVelocityCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PushbackVelocityCondition>("velocity", &PushbackVelocityCondition::SetVelocity);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gPushbackVelocityConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AA840
			fight::ConditionFactory* CreatePushbackVelocityConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PushbackVelocityCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AAB80
			void RegisterPushbackVelocityConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PushbackVelocityCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPushbackDirectionConditionProperties;  // 0x11254A58

			// FUNCTION: ENGINE 0x101AA2E0
			bool PushbackDirectionCondition::SetDirection(float newValue)
			{
				direction = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101AA300
			bool PushbackDirectionCondition::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101AA3D0
			fight::Property* PushbackDirectionCondition::GetProperty(int index)
			{
				return gPushbackDirectionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101AA3F0
			void PushbackDirectionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPushbackDirectionConditionProperties);
			}

			// FUNCTION: ENGINE 0x101AA400
			PushbackDirectionCondition::PushbackDirectionCondition() : fight::Condition(0), arc(1.5707964f), direction(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x101AA440
			PushbackDirectionCondition::~PushbackDirectionCondition()
			{
			}

			// FUNCTION: ENGINE 0x101AA9C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PushbackDirectionCondition::RegisterProperties()
			{
				if (gPushbackDirectionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PushbackDirectionCondition>("direction", &PushbackDirectionCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PushbackDirectionCondition>("arc", &PushbackDirectionCondition::SetArc);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gPushbackDirectionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AA870
			fight::ConditionFactory* CreatePushbackDirectionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PushbackDirectionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AABB0
			void RegisterPushbackDirectionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PushbackDirectionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitPushbackAddTrackProperties;  // 0x11254A5C

			// FUNCTION: ENGINE 0x101AA320
			bool ReactionHitPushbackAddTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AA340
			bool ReactionHitPushbackAddTrack::SetScale(float newValue)
			{
				scale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AA450
			fight::Property* ReactionHitPushbackAddTrack::GetProperty(int index)
			{
				return gReactionHitPushbackAddTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101AA470
			void ReactionHitPushbackAddTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitPushbackAddTrackProperties);
			}

			// FUNCTION: ENGINE 0x101AA480
			ReactionHitPushbackAddTrack::ReactionHitPushbackAddTrack() : scale(1.0f), timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101AA4C0
			float ReactionHitPushbackAddTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101AA4D0
			float ReactionHitPushbackAddTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101AA4E0
			ReactionHitPushbackAddTrack::~ReactionHitPushbackAddTrack()
			{
			}

			// FUNCTION: ENGINE 0x101AAAA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitPushbackAddTrack::RegisterProperties()
			{
				if (gReactionHitPushbackAddTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReactionHitPushbackAddTrack>("timeBegin", &ReactionHitPushbackAddTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitPushbackAddTrack>("scale", &ReactionHitPushbackAddTrack::SetScale);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionHitPushbackAddTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AA8A0
			fight::TrackFactory* CreateReactionHitPushbackAddTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionHitPushbackAddTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AABE0
			void RegisterReactionHitPushbackAddTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionHitPushbackAddTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<PushbackVelocityCondition>;
			template class fight::PropertyFloatConstRange<PushbackVelocityCondition>;
			template class fight::ConditionFactoryTemplate<PushbackVelocityCondition>;
			template class fight::ConditionFactoryCasterTemplate<PushbackVelocityCondition>;
			template class fight::PropertyFloatConstRange<PushbackDirectionCondition>;
			template class fight::ConditionFactoryTemplate<PushbackDirectionCondition>;
			template class fight::ConditionFactoryCasterTemplate<PushbackDirectionCondition>;
			template class fight::PropertyFloatConstRange<ReactionHitPushbackAddTrack>;
			template class fight::TrackFactoryTemplate<ReactionHitPushbackAddTrack>;
			template class fight::TrackFactoryCasterTemplate<ReactionHitPushbackAddTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101AA4F0
// FUNCTION: ENGINE 0x101AA520
// FUNCTION: ENGINE 0x101AA550
// FUNCTION: ENGINE 0x101AA580
// FUNCTION: ENGINE 0x101AA590
// FUNCTION: ENGINE 0x101AA5C0
// FUNCTION: ENGINE 0x101AA5D0
// FUNCTION: ENGINE 0x101AA600
// FUNCTION: ENGINE 0x101AA610
// FUNCTION: ENGINE 0x101AA640
// FUNCTION: ENGINE 0x101AA680
// FUNCTION: ENGINE 0x101AA690
// FUNCTION: ENGINE 0x101AA6C0
// FUNCTION: ENGINE 0x101AA6E0
// FUNCTION: ENGINE 0x101AA6F0
// FUNCTION: ENGINE 0x101AA720
// FUNCTION: ENGINE 0x101AA750
// FUNCTION: ENGINE 0x101AA760
// FUNCTION: ENGINE 0x101AA790
// FUNCTION: ENGINE 0x101AA7C0
// FUNCTION: ENGINE 0x101AA7D0
// FUNCTION: ENGINE 0x101AA800
// FUNCTION: ENGINE 0x101AA830
// FUNCTION: ENGINE 0x101AAC10
// FUNCTION: ENGINE 0x101AAC40
// FUNCTION: ENGINE 0x101AAC60
// FUNCTION: ENGINE 0x101AAC90
// FUNCTION: ENGINE 0x101AACB0
// FUNCTION: ENGINE 0x101AACE0
// FUNCTION: ENGINE 0x101AAD00
// FUNCTION: ENGINE 0x101AAD50
// FUNCTION: ENGINE 0x101AADA0
