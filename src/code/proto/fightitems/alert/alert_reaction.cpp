// Fight items of the alert group: DisguiseReactionCondition, ReactionTrack (unit 0x10275910 - 0x10276170; no assert path, the file name is a guess).
#include "code/proto/fightitems/alert/alert_reaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace alert
		{
			fight::Property** gDisguiseReactionConditionProperties;  // 0x112560E8

			// FUNCTION: ENGINE 0x10275910
			bool DisguiseReactionCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10275920
			bool DisguiseReactionCondition::SetReaction(int newValue)
			{
				reaction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10275980
			fight::Property* DisguiseReactionCondition::GetProperty(int index)
			{
				return gDisguiseReactionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x102759A0
			void DisguiseReactionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDisguiseReactionConditionProperties);
			}

			// FUNCTION: ENGINE 0x102759B0
			DisguiseReactionCondition::DisguiseReactionCondition() : fight::Condition(0), compare(0), reaction(0)
			{
			}

			// FUNCTION: ENGINE 0x102759E0
			DisguiseReactionCondition::~DisguiseReactionCondition()
			{
			}

			// FUNCTION: ENGINE 0x10275DA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DisguiseReactionCondition::RegisterProperties()
			{
				if (gDisguiseReactionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<DisguiseReactionCondition>("compare", motion::gClassNameConditionCompareTable, motion::gClassNameConditionCompareCount, &DisguiseReactionCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<DisguiseReactionCondition>("reaction", gDisguiseReactionConditionReactionTable, gDisguiseReactionConditionReactionCount, &DisguiseReactionCondition::SetReaction);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gDisguiseReactionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10275D40
			fight::ConditionFactory* CreateDisguiseReactionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DisguiseReactionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10275FD0
			void RegisterDisguiseReactionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DisguiseReactionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionTrackProperties;  // 0x112560EC

			// FUNCTION: ENGINE 0x10275930
			bool ReactionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10275950
			bool ReactionTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10275970
			bool ReactionTrack::SetReaction(int newValue)
			{
				reaction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102759F0
			fight::Property* ReactionTrack::GetProperty(int index)
			{
				return gReactionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10275A10
			void ReactionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReactionTrackProperties);
			}

			// FUNCTION: ENGINE 0x10275A20
			ReactionTrack::ReactionTrack() : timeBegin(0.0f), timeEnd(-1.0f), reaction(0)
			{
			}

			// FUNCTION: ENGINE 0x10275A60
			float ReactionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10275A70
			float ReactionTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10275A80
			ReactionTrack::~ReactionTrack()
			{
			}

			// FUNCTION: ENGINE 0x10275EA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionTrack::RegisterProperties()
			{
				if (gReactionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReactionTrack>("timeBegin", &ReactionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionTrack>("timeEnd", &ReactionTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<ReactionTrack>("reaction", gDisguiseReactionConditionReactionTable, gDisguiseReactionConditionReactionCount, &ReactionTrack::SetReaction);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gReactionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10275D70
			fight::TrackFactory* CreateReactionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10276000
			void RegisterReactionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x1026D740
			ReactionAction::ReactionAction(ReactionTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x1026D5D0
			ReactionAction::~ReactionAction()
			{
			}

			// FUNCTION: ENGINE 0x1026D460
			void ReactionAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x1026D450
			bool ReactionAction::Slot7(int arg, float value)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x1026D880
			fight::Action* ReactionTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ReactionAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyEnumConstList<DisguiseReactionCondition>;
			template class fight::ConditionFactoryTemplate<DisguiseReactionCondition>;
			template class fight::ConditionFactoryCasterTemplate<DisguiseReactionCondition>;
			template class fight::PropertyFloatConstRange<ReactionTrack>;
			template class fight::PropertyEnumConstList<ReactionTrack>;
			template class fight::TrackFactoryTemplate<ReactionTrack>;
			template class fight::TrackFactoryCasterTemplate<ReactionTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10269D70
// FUNCTION: ENGINE 0x1026A250
// FUNCTION: ENGINE 0x1026D7C0
// FUNCTION: ENGINE 0x10275A90
// FUNCTION: ENGINE 0x10275AC0
// FUNCTION: ENGINE 0x10275AF0
// FUNCTION: ENGINE 0x10275B00
// FUNCTION: ENGINE 0x10275B30
// FUNCTION: ENGINE 0x10275B40
// FUNCTION: ENGINE 0x10275B70
// FUNCTION: ENGINE 0x10275BB0
// FUNCTION: ENGINE 0x10275BC0
// FUNCTION: ENGINE 0x10275BF0
// FUNCTION: ENGINE 0x10275C10
// FUNCTION: ENGINE 0x10275C20
// FUNCTION: ENGINE 0x10275C50
// FUNCTION: ENGINE 0x10275C80
// FUNCTION: ENGINE 0x10275C90
// FUNCTION: ENGINE 0x10275CD0
// FUNCTION: ENGINE 0x10275CE0
// FUNCTION: ENGINE 0x10275D10
// FUNCTION: ENGINE 0x10275D30
// FUNCTION: ENGINE 0x10276030
// FUNCTION: ENGINE 0x10276060
// FUNCTION: ENGINE 0x10276080
// FUNCTION: ENGINE 0x102760B0
// FUNCTION: ENGINE 0x102760D0
// FUNCTION: ENGINE 0x10276120
