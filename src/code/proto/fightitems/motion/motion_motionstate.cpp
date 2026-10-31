// Fight items of the motion group: MotionStateCondition, MotionStateTrack (unit 0x101B5FB0 - 0x101B6980; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_motionstate.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gMotionStateConditionProperties;  // 0x11254AF4

			// FUNCTION: ENGINE 0x101B5FB0
			bool MotionStateCondition::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B6060
			bool MotionStateCondition::SetName(const fight::Name& newValue)
			{
				name = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B5FC0
			bool MotionStateCondition::SetMatch(bool newValue)
			{
				match = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B6000
			fight::Property* MotionStateCondition::GetProperty(int index)
			{
				return gMotionStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101B6020
			void MotionStateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gMotionStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x101B60A0
			MotionStateCondition::MotionStateCondition() : fight::Condition(0), state(0), match(true)
			{
			}

			// FUNCTION: ENGINE 0x101B60D0
			MotionStateCondition::~MotionStateCondition()
			{
			}

			// FUNCTION: ENGINE 0x101B65E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MotionStateCondition::RegisterProperties()
			{
				if (gMotionStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<MotionStateCondition>("state", gMotionStateConditionStateTable, gMotionStateConditionStateCount, &MotionStateCondition::SetState);
					properties[0] = property;
					property = new fight::PropertyNameList<MotionStateCondition>("name", &MotionStateCondition::SetName);
					properties[1] = property;
					property = new fight::PropertyBool<MotionStateCondition>("match", &MotionStateCondition::SetMatch);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gMotionStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B6460
			fight::ConditionFactory* CreateMotionStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<MotionStateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101B64C0
			void RegisterMotionStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<MotionStateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gMotionStateTrackProperties;  // 0x11254AF8

			// FUNCTION: ENGINE 0x101B5FD0
			bool MotionStateTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B5FF0
			bool MotionStateTrack::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B6080
			bool MotionStateTrack::SetName(const fight::Name& newValue)
			{
				name = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B6030
			fight::Property* MotionStateTrack::GetProperty(int index)
			{
				return gMotionStateTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101B6050
			void MotionStateTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMotionStateTrackProperties);
			}

			// FUNCTION: ENGINE 0x101B60E0
			MotionStateTrack::MotionStateTrack() : timeBegin(0.0f), state(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101B6120
			float MotionStateTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101B6130
			float MotionStateTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101B6140
			MotionStateTrack::~MotionStateTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B6710
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MotionStateTrack::RegisterProperties()
			{
				if (gMotionStateTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MotionStateTrack>("timeBegin", &MotionStateTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<MotionStateTrack>("state", gMotionStateConditionStateTable, gMotionStateConditionStateCount, &MotionStateTrack::SetState);
					properties[1] = property;
					property = new fight::PropertyNameList<MotionStateTrack>("name", &MotionStateTrack::SetName);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gMotionStateTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B6490
			fight::TrackFactory* CreateMotionStateTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MotionStateTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101B64F0
			void RegisterMotionStateTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MotionStateTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<MotionStateCondition>;
			template class fight::PropertyNameList<MotionStateCondition>;
			template class fight::PropertyBool<MotionStateCondition>;
			template class fight::ConditionFactoryTemplate<MotionStateCondition>;
			template class fight::ConditionFactoryCasterTemplate<MotionStateCondition>;
			template class fight::PropertyFloatConstRange<MotionStateTrack>;
			template class fight::PropertyEnumConstList<MotionStateTrack>;
			template class fight::PropertyNameList<MotionStateTrack>;
			template class fight::TrackFactoryTemplate<MotionStateTrack>;
			template class fight::TrackFactoryCasterTemplate<MotionStateTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101B6150
// FUNCTION: ENGINE 0x101B6160
// FUNCTION: ENGINE 0x101B6190
// FUNCTION: ENGINE 0x101B61A0
// FUNCTION: ENGINE 0x101B61D0
// FUNCTION: ENGINE 0x101B6200
// FUNCTION: ENGINE 0x101B6230
// FUNCTION: ENGINE 0x101B6270
// FUNCTION: ENGINE 0x101B6280
// FUNCTION: ENGINE 0x101B62B0
// FUNCTION: ENGINE 0x101B62D0
// FUNCTION: ENGINE 0x101B62E0
// FUNCTION: ENGINE 0x101B6310
// FUNCTION: ENGINE 0x101B6330
// FUNCTION: ENGINE 0x101B6340
// FUNCTION: ENGINE 0x101B6370
// FUNCTION: ENGINE 0x101B63A0
// FUNCTION: ENGINE 0x101B63B0
// FUNCTION: ENGINE 0x101B63F0
// FUNCTION: ENGINE 0x101B6400
// FUNCTION: ENGINE 0x101B6430
// FUNCTION: ENGINE 0x101B6450
// FUNCTION: ENGINE 0x101B6520
// FUNCTION: ENGINE 0x101B6550
// FUNCTION: ENGINE 0x101B6570
// FUNCTION: ENGINE 0x101B6580
// FUNCTION: ENGINE 0x101B65B0
// FUNCTION: ENGINE 0x101B65D0
// FUNCTION: ENGINE 0x101B6840
// FUNCTION: ENGINE 0x101B6870
// FUNCTION: ENGINE 0x101B6890
// FUNCTION: ENGINE 0x101B68C0
// FUNCTION: ENGINE 0x101B68E0
// FUNCTION: ENGINE 0x101B6930
