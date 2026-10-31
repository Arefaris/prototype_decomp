// Fight items of the motion group: StunnedCondition, StunTrack (unit 0x101B6980 - 0x101B7170; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_stun.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gStunnedConditionProperties;  // 0x11254B00

			// FUNCTION: ENGINE 0x101B6980
			bool StunnedCondition::SetStunned(bool newValue)
			{
				stunned = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B69F0
			fight::Property* StunnedCondition::GetProperty(int index)
			{
				return gStunnedConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101B6A10
			void StunnedCondition::ClearProperties()
			{
				fight::FreePropertyList(&gStunnedConditionProperties);
			}

			// FUNCTION: ENGINE 0x101B6A20
			StunnedCondition::StunnedCondition() : fight::Condition(0), stunned(true)
			{
			}

			// FUNCTION: ENGINE 0x101B6A40
			StunnedCondition::~StunnedCondition()
			{
			}

			// FUNCTION: ENGINE 0x101B6DB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void StunnedCondition::RegisterProperties()
			{
				if (gStunnedConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<StunnedCondition>("stunned", &StunnedCondition::SetStunned);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gStunnedConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B6D50
			fight::ConditionFactory* CreateStunnedConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<StunnedCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101B6FD0
			void RegisterStunnedConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<StunnedCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gStunTrackProperties;  // 0x11254B04

			// FUNCTION: ENGINE 0x101B6990
			bool StunTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B69B0
			bool StunTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B69D0
			bool StunTrack::SetOnBegin(int newValue)
			{
				onBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B69E0
			bool StunTrack::SetOnEnd(int newValue)
			{
				onEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B6A50
			fight::Property* StunTrack::GetProperty(int index)
			{
				return gStunTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101B6A70
			void StunTrack::ClearProperties()
			{
				fight::FreePropertyList(&gStunTrackProperties);
			}

			// FUNCTION: ENGINE 0x101B6A80
			StunTrack::StunTrack() : timeBegin(0.0f), timeEnd(-1.0f), onBegin(0), onEnd(0)
			{
			}

			// FUNCTION: ENGINE 0x101B6AC0
			float StunTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101B6AD0
			float StunTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101B6AE0
			StunTrack::~StunTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B6E50
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void StunTrack::RegisterProperties()
			{
				if (gStunTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<StunTrack>("timeBegin", &StunTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<StunTrack>("timeEnd", &StunTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<StunTrack>("onBegin", gStunTrackOnBeginTable, gStunTrackOnBeginCount, &StunTrack::SetOnBegin);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<StunTrack>("onEnd", gStunTrackOnEndTable, gStunTrackOnEndCount, &StunTrack::SetOnEnd);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gStunTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B6D80
			fight::TrackFactory* CreateStunTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<StunTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101B7000
			void RegisterStunTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<StunTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x1011A2B0
			StunAction::StunAction(StunTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x600), link(newTrack), target(newTarget), unknown2C(false)
			{
			}

			// FUNCTION: ENGINE 0x1011A160
			StunAction::~StunAction()
			{
			}

			// FUNCTION: ENGINE 0x1011A4C0
			fight::Action* StunTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new StunAction(this, handle);
			}

			// FUNCTION: ENGINE 0x1011A190
			// EQUIVALENT: block order (the engine falls into the failure return and jumps to the body) (61.4 %)
			bool StunnedCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object != 0)
				{
					GetStunnedMovementMessage message;
					object->SendMessage(&message);
					return stunned == message.stunned;
				}
				return false;
			}

			// ---- actions end
			template class fight::PropertyBool<StunnedCondition>;
			template class fight::ConditionFactoryTemplate<StunnedCondition>;
			template class fight::ConditionFactoryCasterTemplate<StunnedCondition>;
			template class fight::PropertyFloatConstRange<StunTrack>;
			template class fight::PropertyEnumConstList<StunTrack>;
			template class fight::TrackFactoryTemplate<StunTrack>;
			template class fight::TrackFactoryCasterTemplate<StunTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10119F60
// FUNCTION: ENGINE 0x10119F70
// FUNCTION: ENGINE 0x1011A090
// FUNCTION: ENGINE 0x1011A0C0
// FUNCTION: ENGINE 0x1011A0F0
// FUNCTION: ENGINE 0x1011A320
// FUNCTION: ENGINE 0x101B6AF0
// FUNCTION: ENGINE 0x101B6B20
// FUNCTION: ENGINE 0x101B6B50
// FUNCTION: ENGINE 0x101B6B60
// FUNCTION: ENGINE 0x101B6B90
// FUNCTION: ENGINE 0x101B6BA0
// FUNCTION: ENGINE 0x101B6BD0
// FUNCTION: ENGINE 0x101B6C00
// FUNCTION: ENGINE 0x101B6C20
// FUNCTION: ENGINE 0x101B6C30
// FUNCTION: ENGINE 0x101B6C60
// FUNCTION: ENGINE 0x101B6C90
// FUNCTION: ENGINE 0x101B6CA0
// FUNCTION: ENGINE 0x101B6CE0
// FUNCTION: ENGINE 0x101B6CF0
// FUNCTION: ENGINE 0x101B6D20
// FUNCTION: ENGINE 0x101B6D40
// FUNCTION: ENGINE 0x101B7030
// FUNCTION: ENGINE 0x101B7060
// FUNCTION: ENGINE 0x101B7080
// FUNCTION: ENGINE 0x101B70B0
// FUNCTION: ENGINE 0x101B70D0
// FUNCTION: ENGINE 0x101B7120
