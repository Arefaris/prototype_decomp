// Fight items of the alert group: DisguiseBlownCondition, BlowDisguiseTrack (unit 0x102689E0 - 0x1026E0E0; no assert path, the file name is a guess).
#include "code/proto/fightitems/alert/alert_disguiseblown.h"

namespace proto
{
	namespace fightitems
	{
		namespace alert
		{
			fight::Property** gDisguiseBlownConditionProperties;  // 0x11256040

			// FUNCTION: ENGINE 0x1026D8D0
			bool DisguiseBlownCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026D8E0
			bool DisguiseBlownCondition::SetValue(float newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026D960
			fight::Property* DisguiseBlownCondition::GetProperty(int index)
			{
				return gDisguiseBlownConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026D980
			void DisguiseBlownCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDisguiseBlownConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026D990
			DisguiseBlownCondition::DisguiseBlownCondition() : fight::Condition(0), value(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x1026D9C0
			DisguiseBlownCondition::~DisguiseBlownCondition()
			{
			}

			// FUNCTION: ENGINE 0x1026DD40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DisguiseBlownCondition::RegisterProperties()
			{
				if (gDisguiseBlownConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<DisguiseBlownCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &DisguiseBlownCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DisguiseBlownCondition>("value", &DisguiseBlownCondition::SetValue);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gDisguiseBlownConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1026DCE0
			fight::ConditionFactory* CreateDisguiseBlownConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DisguiseBlownCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1026DF40
			void RegisterDisguiseBlownConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DisguiseBlownCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gBlowDisguiseTrackProperties;  // 0x11256044

			// FUNCTION: ENGINE 0x1026D900
			bool BlowDisguiseTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026D920
			bool BlowDisguiseTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026D940
			bool BlowDisguiseTrack::SetBlownTime(float newValue)
			{
				blownTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026D9D0
			fight::Property* BlowDisguiseTrack::GetProperty(int index)
			{
				return gBlowDisguiseTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1026D9F0
			void BlowDisguiseTrack::ClearProperties()
			{
				fight::FreePropertyList(&gBlowDisguiseTrackProperties);
			}

			// FUNCTION: ENGINE 0x1026DA00
			BlowDisguiseTrack::BlowDisguiseTrack() : blownTime(-1.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1026DA40
			float BlowDisguiseTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1026DA50
			float BlowDisguiseTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1026DA60
			BlowDisguiseTrack::~BlowDisguiseTrack()
			{
			}

			// FUNCTION: ENGINE 0x1026DE30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void BlowDisguiseTrack::RegisterProperties()
			{
				if (gBlowDisguiseTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<BlowDisguiseTrack>("timeBegin", &BlowDisguiseTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<BlowDisguiseTrack>("timeEnd", &BlowDisguiseTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<BlowDisguiseTrack>("blownTime", &BlowDisguiseTrack::SetBlownTime);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gBlowDisguiseTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1026DD10
			fight::TrackFactory* CreateBlowDisguiseTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<BlowDisguiseTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1026DF70
			void RegisterBlowDisguiseTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<BlowDisguiseTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x10268D40
			BlowDisguiseAction::BlowDisguiseAction(BlowDisguiseTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x10268BD0
			BlowDisguiseAction::~BlowDisguiseAction()
			{
			}

			// FUNCTION: ENGINE 0x10268AA0
			bool BlowDisguiseAction::Slot5(int arg, float value)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x10268AB0
			void BlowDisguiseAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x10268E90
			fight::Action* BlowDisguiseTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new BlowDisguiseAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyEnumConstList<DisguiseBlownCondition>;
			template class fight::PropertyFloatConstRange<DisguiseBlownCondition>;
			template class fight::ConditionFactoryTemplate<DisguiseBlownCondition>;
			template class fight::ConditionFactoryCasterTemplate<DisguiseBlownCondition>;
			template class fight::PropertyFloatConstRange<BlowDisguiseTrack>;
			template class fight::TrackFactoryTemplate<BlowDisguiseTrack>;
			template class fight::TrackFactoryCasterTemplate<BlowDisguiseTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10268B30
// FUNCTION: ENGINE 0x10268B60
// FUNCTION: ENGINE 0x10268DC0
// FUNCTION: ENGINE 0x1026DA70
// FUNCTION: ENGINE 0x1026DAA0
// FUNCTION: ENGINE 0x1026DAD0
// FUNCTION: ENGINE 0x1026DAE0
// FUNCTION: ENGINE 0x1026DB10
// FUNCTION: ENGINE 0x1026DB20
// FUNCTION: ENGINE 0x1026DB50
// FUNCTION: ENGINE 0x1026DB90
// FUNCTION: ENGINE 0x1026DBA0
// FUNCTION: ENGINE 0x1026DBD0
// FUNCTION: ENGINE 0x1026DBF0
// FUNCTION: ENGINE 0x1026DC00
// FUNCTION: ENGINE 0x1026DC30
// FUNCTION: ENGINE 0x1026DC60
// FUNCTION: ENGINE 0x1026DC70
// FUNCTION: ENGINE 0x1026DCA0
// FUNCTION: ENGINE 0x1026DCD0
// FUNCTION: ENGINE 0x1026DFA0
// FUNCTION: ENGINE 0x1026DFD0
// FUNCTION: ENGINE 0x1026DFF0
// FUNCTION: ENGINE 0x1026E020
// FUNCTION: ENGINE 0x1026E040
// FUNCTION: ENGINE 0x1026E090
