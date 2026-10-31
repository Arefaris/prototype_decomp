// Fight items of the motion group: VariableNameCompareCondition, TimerCompareCondition, OutOfCombatTimerCondition, VariableIntCompareCondition, TimerContinousSetTrack, VariableNameSetTrack, TimerSetTrack, VariableIntSetTrack, VariableIntTemporarySetTrack (unit 0x101C5300 - 0x101C8410; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_variable.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gVariableNameCompareConditionProperties;  // 0x11254C24

			// FUNCTION: ENGINE 0x101C5790
			bool VariableNameCompareCondition::SetVariable(const fight::Name& newValue)
			{
				variable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5300
			bool VariableNameCompareCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C57B0
			bool VariableNameCompareCondition::SetValue(const fight::Name& newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C55A0
			fight::Property* VariableNameCompareCondition::GetProperty(int index)
			{
				return gVariableNameCompareConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101C55C0
			void VariableNameCompareCondition::ClearProperties()
			{
				fight::FreePropertyList(&gVariableNameCompareConditionProperties);
			}

			// FUNCTION: ENGINE 0x101C58F0
			VariableNameCompareCondition::VariableNameCompareCondition() : fight::Condition(0), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101C5930
			VariableNameCompareCondition::~VariableNameCompareCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C7220
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void VariableNameCompareCondition::RegisterProperties()
			{
				if (gVariableNameCompareConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<VariableNameCompareCondition>("variable", &VariableNameCompareCondition::SetVariable);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<VariableNameCompareCondition>("compare", gClassNameConditionCompareTable, gClassNameConditionCompareCount, &VariableNameCompareCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyName<VariableNameCompareCondition>("value", &VariableNameCompareCondition::SetValue);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gVariableNameCompareConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C6AA0
			fight::ConditionFactory* CreateVariableNameCompareConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<VariableNameCompareCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C6D40
			void RegisterVariableNameCompareConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<VariableNameCompareCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTimerCompareConditionProperties;  // 0x11254C28

			// FUNCTION: ENGINE 0x101C57D0
			bool TimerCompareCondition::SetTimer(const fight::Name& newValue)
			{
				timer = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5310
			bool TimerCompareCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5320
			bool TimerCompareCondition::SetTime(float newValue)
			{
				time = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C55D0
			fight::Property* TimerCompareCondition::GetProperty(int index)
			{
				return gTimerCompareConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101C55F0
			void TimerCompareCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTimerCompareConditionProperties);
			}

			// FUNCTION: ENGINE 0x101C5940
			TimerCompareCondition::TimerCompareCondition() : fight::Condition(0), time(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101C5980
			TimerCompareCondition::~TimerCompareCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C7350
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TimerCompareCondition::RegisterProperties()
			{
				if (gTimerCompareConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<TimerCompareCondition>("timer", &TimerCompareCondition::SetTimer);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<TimerCompareCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &TimerCompareCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TimerCompareCondition>("time", &TimerCompareCondition::SetTime);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gTimerCompareConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C6AD0
			fight::ConditionFactory* CreateTimerCompareConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TimerCompareCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C6D70
			void RegisterTimerCompareConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TimerCompareCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gOutOfCombatTimerConditionProperties;  // 0x11254C2C

			// FUNCTION: ENGINE 0x101C5340
			bool OutOfCombatTimerCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5350
			bool OutOfCombatTimerCondition::SetTime(float newValue)
			{
				time = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5600
			fight::Property* OutOfCombatTimerCondition::GetProperty(int index)
			{
				return gOutOfCombatTimerConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101C5620
			void OutOfCombatTimerCondition::ClearProperties()
			{
				fight::FreePropertyList(&gOutOfCombatTimerConditionProperties);
			}

			// FUNCTION: ENGINE 0x101C5630
			OutOfCombatTimerCondition::OutOfCombatTimerCondition() : fight::Condition(0), time(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101C5660
			OutOfCombatTimerCondition::~OutOfCombatTimerCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C6C50
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void OutOfCombatTimerCondition::RegisterProperties()
			{
				if (gOutOfCombatTimerConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<OutOfCombatTimerCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &OutOfCombatTimerCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<OutOfCombatTimerCondition>("time", &OutOfCombatTimerCondition::SetTime);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gOutOfCombatTimerConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C6B00
			fight::ConditionFactory* CreateOutOfCombatTimerConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<OutOfCombatTimerCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C6DA0
			void RegisterOutOfCombatTimerConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<OutOfCombatTimerCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gVariableIntCompareConditionProperties;  // 0x11254C30

			// FUNCTION: ENGINE 0x101C57F0
			bool VariableIntCompareCondition::SetVariable(const fight::Name& newValue)
			{
				variable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5370
			bool VariableIntCompareCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5380
			bool VariableIntCompareCondition::SetValue(int newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5670
			fight::Property* VariableIntCompareCondition::GetProperty(int index)
			{
				return gVariableIntCompareConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101C5690
			void VariableIntCompareCondition::ClearProperties()
			{
				fight::FreePropertyList(&gVariableIntCompareConditionProperties);
			}

			// FUNCTION: ENGINE 0x101C59C0
			VariableIntCompareCondition::VariableIntCompareCondition() : fight::Condition(0), compare(0), value(0)
			{
			}

			// FUNCTION: ENGINE 0x101C5A00
			VariableIntCompareCondition::~VariableIntCompareCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C7480
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void VariableIntCompareCondition::RegisterProperties()
			{
				if (gVariableIntCompareConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<VariableIntCompareCondition>("variable", &VariableIntCompareCondition::SetVariable);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<VariableIntCompareCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &VariableIntCompareCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyIntConstRange<VariableIntCompareCondition>("value", &VariableIntCompareCondition::SetValue);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gVariableIntCompareConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C6B30
			fight::ConditionFactory* CreateVariableIntCompareConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<VariableIntCompareCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C6DD0
			void RegisterVariableIntCompareConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<VariableIntCompareCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTimerContinousSetTrackProperties;  // 0x11254C34

			// FUNCTION: ENGINE 0x101C5390
			bool TimerContinousSetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C53B0
			bool TimerContinousSetTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5810
			bool TimerContinousSetTrack::SetTimer(const fight::Name& newValue)
			{
				timer = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C53D0
			bool TimerContinousSetTrack::SetTime(float newValue)
			{
				time = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C53F0
			bool TimerContinousSetTrack::SetIncrementing(bool newValue)
			{
				incrementing = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5400
			bool TimerContinousSetTrack::SetRandomRange(float newValue)
			{
				randomRange = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C56A0
			fight::Property* TimerContinousSetTrack::GetProperty(int index)
			{
				return gTimerContinousSetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C56C0
			void TimerContinousSetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTimerContinousSetTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C5A10
			TimerContinousSetTrack::TimerContinousSetTrack() : randomRange(0.0f), time(0.0f), timeBegin(0.0f), timeEnd(-1.0f), incrementing(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C5A70
			float TimerContinousSetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C5A80
			float TimerContinousSetTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101C5A90
			TimerContinousSetTrack::~TimerContinousSetTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C75B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TimerContinousSetTrack::RegisterProperties()
			{
				if (gTimerContinousSetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TimerContinousSetTrack>("timeBegin", &TimerContinousSetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TimerContinousSetTrack>("timeEnd", &TimerContinousSetTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<TimerContinousSetTrack>("timer", &TimerContinousSetTrack::SetTimer);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<TimerContinousSetTrack>("time", &TimerContinousSetTrack::SetTime);
					properties[3] = property;
					property = new fight::PropertyBool<TimerContinousSetTrack>("incrementing", &TimerContinousSetTrack::SetIncrementing);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<TimerContinousSetTrack>("randomRange", &TimerContinousSetTrack::SetRandomRange);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gTimerContinousSetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C6B60
			fight::TrackFactory* CreateTimerContinousSetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TimerContinousSetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C6E00
			void RegisterTimerContinousSetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TimerContinousSetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gVariableNameSetTrackProperties;  // 0x11254C38

			// FUNCTION: ENGINE 0x101C5420
			bool VariableNameSetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5830
			bool VariableNameSetTrack::SetVariable(const fight::Name& newValue)
			{
				variable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5850
			bool VariableNameSetTrack::SetValue(const fight::Name& newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5440
			bool VariableNameSetTrack::SetPersistent(bool newValue)
			{
				persistent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C56D0
			fight::Property* VariableNameSetTrack::GetProperty(int index)
			{
				return gVariableNameSetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C56F0
			void VariableNameSetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gVariableNameSetTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C5AA0
			VariableNameSetTrack::VariableNameSetTrack() : timeBegin(0.0f), persistent(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C5AF0
			float VariableNameSetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C5B00
			float VariableNameSetTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C5B10
			VariableNameSetTrack::~VariableNameSetTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C7780
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void VariableNameSetTrack::RegisterProperties()
			{
				if (gVariableNameSetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<VariableNameSetTrack>("timeBegin", &VariableNameSetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyName<VariableNameSetTrack>("variable", &VariableNameSetTrack::SetVariable);
					properties[1] = property;
					property = new fight::PropertyName<VariableNameSetTrack>("value", &VariableNameSetTrack::SetValue);
					properties[2] = property;
					property = new fight::PropertyBool<VariableNameSetTrack>("persistent", &VariableNameSetTrack::SetPersistent);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gVariableNameSetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C6B90
			fight::TrackFactory* CreateVariableNameSetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<VariableNameSetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C6E30
			void RegisterVariableNameSetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<VariableNameSetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTimerSetTrackProperties;  // 0x11254C3C

			// FUNCTION: ENGINE 0x101C5450
			bool TimerSetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5870
			bool TimerSetTrack::SetTimer(const fight::Name& newValue)
			{
				timer = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5470
			bool TimerSetTrack::SetTime(float newValue)
			{
				time = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5490
			bool TimerSetTrack::SetIncrementing(bool newValue)
			{
				incrementing = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C54A0
			bool TimerSetTrack::SetRandomRange(float newValue)
			{
				randomRange = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5700
			fight::Property* TimerSetTrack::GetProperty(int index)
			{
				return gTimerSetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C5720
			void TimerSetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTimerSetTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C5B20
			TimerSetTrack::TimerSetTrack() : randomRange(0.0f), time(0.0f), timeBegin(0.0f), incrementing(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C5B70
			float TimerSetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C5B80
			float TimerSetTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C5B90
			TimerSetTrack::~TimerSetTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C78D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TimerSetTrack::RegisterProperties()
			{
				if (gTimerSetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TimerSetTrack>("timeBegin", &TimerSetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyName<TimerSetTrack>("timer", &TimerSetTrack::SetTimer);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TimerSetTrack>("time", &TimerSetTrack::SetTime);
					properties[2] = property;
					property = new fight::PropertyBool<TimerSetTrack>("incrementing", &TimerSetTrack::SetIncrementing);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<TimerSetTrack>("randomRange", &TimerSetTrack::SetRandomRange);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gTimerSetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C6BC0
			fight::TrackFactory* CreateTimerSetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TimerSetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C6E60
			void RegisterTimerSetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TimerSetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gVariableIntSetTrackProperties;  // 0x11254C40

			// FUNCTION: ENGINE 0x101C54C0
			bool VariableIntSetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5890
			bool VariableIntSetTrack::SetVariable(const fight::Name& newValue)
			{
				variable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C54E0
			bool VariableIntSetTrack::SetOperator(int newValue)
			{
				operatorValue = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C54F0
			bool VariableIntSetTrack::SetValue(int newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5500
			bool VariableIntSetTrack::SetPersistent(bool newValue)
			{
				persistent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5730
			fight::Property* VariableIntSetTrack::GetProperty(int index)
			{
				return gVariableIntSetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C5750
			void VariableIntSetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gVariableIntSetTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C5BA0
			VariableIntSetTrack::VariableIntSetTrack() : timeBegin(0.0f), operatorValue(0), value(0), persistent(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C5BF0
			float VariableIntSetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C5C00
			float VariableIntSetTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C5C10
			VariableIntSetTrack::~VariableIntSetTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C7A60
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void VariableIntSetTrack::RegisterProperties()
			{
				if (gVariableIntSetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<VariableIntSetTrack>("timeBegin", &VariableIntSetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyName<VariableIntSetTrack>("variable", &VariableIntSetTrack::SetVariable);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<VariableIntSetTrack>("operator", gVariableIntSetTrackOperatorTable, gVariableIntSetTrackOperatorCount, &VariableIntSetTrack::SetOperator);
					properties[2] = property;
					property = new fight::PropertyIntConstRange<VariableIntSetTrack>("value", &VariableIntSetTrack::SetValue);
					properties[3] = property;
					property = new fight::PropertyBool<VariableIntSetTrack>("persistent", &VariableIntSetTrack::SetPersistent);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gVariableIntSetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C6BF0
			fight::TrackFactory* CreateVariableIntSetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<VariableIntSetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C6E90
			void RegisterVariableIntSetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<VariableIntSetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gVariableIntTemporarySetTrackProperties;  // 0x11254C44

			// FUNCTION: ENGINE 0x101C5510
			bool VariableIntTemporarySetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5530
			bool VariableIntTemporarySetTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C58B0
			bool VariableIntTemporarySetTrack::SetVariable(const fight::Name& newValue)
			{
				variable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C58D0
			bool VariableIntTemporarySetTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5550
			bool VariableIntTemporarySetTrack::SetUseGrabber(bool newValue)
			{
				useGrabber = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5560
			bool VariableIntTemporarySetTrack::SetOperatorBegin(int newValue)
			{
				operatorBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5570
			bool VariableIntTemporarySetTrack::SetOperatorEnd(int newValue)
			{
				operatorEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5580
			bool VariableIntTemporarySetTrack::SetBeginValue(int newValue)
			{
				beginValue = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5590
			bool VariableIntTemporarySetTrack::SetEndValue(int newValue)
			{
				endValue = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C5760
			fight::Property* VariableIntTemporarySetTrack::GetProperty(int index)
			{
				return gVariableIntTemporarySetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C5780
			void VariableIntTemporarySetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gVariableIntTemporarySetTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C5C20
			VariableIntTemporarySetTrack::VariableIntTemporarySetTrack() : timeBegin(0.0f), timeEnd(-1.0f), beginValue(-1), endValue(-1), operatorBegin(0), operatorEnd(0), useGrabber(false)
			{
			}

			// FUNCTION: ENGINE 0x101C5C80
			float VariableIntTemporarySetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C5C90
			float VariableIntTemporarySetTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101C5CA0
			VariableIntTemporarySetTrack::~VariableIntTemporarySetTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C7C10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void VariableIntTemporarySetTrack::RegisterProperties()
			{
				if (gVariableIntTemporarySetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<VariableIntTemporarySetTrack>("timeBegin", &VariableIntTemporarySetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<VariableIntTemporarySetTrack>("timeEnd", &VariableIntTemporarySetTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<VariableIntTemporarySetTrack>("variable", &VariableIntTemporarySetTrack::SetVariable);
					properties[2] = property;
					property = new fight::PropertyNameList<VariableIntTemporarySetTrack>("grabSlot", &VariableIntTemporarySetTrack::SetGrabSlot);
					properties[3] = property;
					property = new fight::PropertyBool<VariableIntTemporarySetTrack>("useGrabber", &VariableIntTemporarySetTrack::SetUseGrabber);
					properties[4] = property;
					property = new fight::PropertyEnumConstList<VariableIntTemporarySetTrack>("operatorBegin", gVariableIntSetTrackOperatorTable, gVariableIntSetTrackOperatorCount, &VariableIntTemporarySetTrack::SetOperatorBegin);
					properties[5] = property;
					property = new fight::PropertyEnumConstList<VariableIntTemporarySetTrack>("operatorEnd", gVariableIntSetTrackOperatorTable, gVariableIntSetTrackOperatorCount, &VariableIntTemporarySetTrack::SetOperatorEnd);
					properties[6] = property;
					property = new fight::PropertyIntConstRange<VariableIntTemporarySetTrack>("beginValue", &VariableIntTemporarySetTrack::SetBeginValue);
					properties[7] = property;
					property = new fight::PropertyIntConstRange<VariableIntTemporarySetTrack>("endValue", &VariableIntTemporarySetTrack::SetEndValue);
					properties[8] = property;
					fight::RegisterPropertyList(properties, &gVariableIntTemporarySetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C6C20
			fight::TrackFactory* CreateVariableIntTemporarySetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<VariableIntTemporarySetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C6EC0
			void RegisterVariableIntTemporarySetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<VariableIntTemporarySetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyName<VariableNameCompareCondition>;
			template class fight::PropertyEnumConstList<VariableNameCompareCondition>;
			template class fight::ConditionFactoryTemplate<VariableNameCompareCondition>;
			template class fight::ConditionFactoryCasterTemplate<VariableNameCompareCondition>;
			template class fight::PropertyName<TimerCompareCondition>;
			template class fight::PropertyEnumConstList<TimerCompareCondition>;
			template class fight::PropertyFloatConstRange<TimerCompareCondition>;
			template class fight::ConditionFactoryTemplate<TimerCompareCondition>;
			template class fight::ConditionFactoryCasterTemplate<TimerCompareCondition>;
			template class fight::PropertyEnumConstList<OutOfCombatTimerCondition>;
			template class fight::PropertyFloatConstRange<OutOfCombatTimerCondition>;
			template class fight::ConditionFactoryTemplate<OutOfCombatTimerCondition>;
			template class fight::ConditionFactoryCasterTemplate<OutOfCombatTimerCondition>;
			template class fight::PropertyName<VariableIntCompareCondition>;
			template class fight::PropertyEnumConstList<VariableIntCompareCondition>;
			template class fight::PropertyIntConstRange<VariableIntCompareCondition>;
			template class fight::ConditionFactoryTemplate<VariableIntCompareCondition>;
			template class fight::ConditionFactoryCasterTemplate<VariableIntCompareCondition>;
			template class fight::PropertyFloatConstRange<TimerContinousSetTrack>;
			template class fight::PropertyName<TimerContinousSetTrack>;
			template class fight::PropertyBool<TimerContinousSetTrack>;
			template class fight::TrackFactoryTemplate<TimerContinousSetTrack>;
			template class fight::TrackFactoryCasterTemplate<TimerContinousSetTrack>;
			template class fight::PropertyFloatConstRange<VariableNameSetTrack>;
			template class fight::PropertyName<VariableNameSetTrack>;
			template class fight::PropertyBool<VariableNameSetTrack>;
			template class fight::TrackFactoryTemplate<VariableNameSetTrack>;
			template class fight::TrackFactoryCasterTemplate<VariableNameSetTrack>;
			template class fight::PropertyFloatConstRange<TimerSetTrack>;
			template class fight::PropertyName<TimerSetTrack>;
			template class fight::PropertyBool<TimerSetTrack>;
			template class fight::TrackFactoryTemplate<TimerSetTrack>;
			template class fight::TrackFactoryCasterTemplate<TimerSetTrack>;
			template class fight::PropertyFloatConstRange<VariableIntSetTrack>;
			template class fight::PropertyName<VariableIntSetTrack>;
			template class fight::PropertyEnumConstList<VariableIntSetTrack>;
			template class fight::PropertyIntConstRange<VariableIntSetTrack>;
			template class fight::PropertyBool<VariableIntSetTrack>;
			template class fight::TrackFactoryTemplate<VariableIntSetTrack>;
			template class fight::TrackFactoryCasterTemplate<VariableIntSetTrack>;
			template class fight::PropertyFloatConstRange<VariableIntTemporarySetTrack>;
			template class fight::PropertyName<VariableIntTemporarySetTrack>;
			template class fight::PropertyNameList<VariableIntTemporarySetTrack>;
			template class fight::PropertyBool<VariableIntTemporarySetTrack>;
			template class fight::PropertyEnumConstList<VariableIntTemporarySetTrack>;
			template class fight::PropertyIntConstRange<VariableIntTemporarySetTrack>;
			template class fight::TrackFactoryTemplate<VariableIntTemporarySetTrack>;
			template class fight::TrackFactoryCasterTemplate<VariableIntTemporarySetTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101C5990
// FUNCTION: ENGINE 0x101C5CB0
// FUNCTION: ENGINE 0x101C5CC0
// FUNCTION: ENGINE 0x101C5CF0
// FUNCTION: ENGINE 0x101C5D00
// FUNCTION: ENGINE 0x101C5D30
// FUNCTION: ENGINE 0x101C5D40
// FUNCTION: ENGINE 0x101C5D70
// FUNCTION: ENGINE 0x101C5D80
// FUNCTION: ENGINE 0x101C5DB0
// FUNCTION: ENGINE 0x101C5DC0
// FUNCTION: ENGINE 0x101C5DF0
// FUNCTION: ENGINE 0x101C5E00
// FUNCTION: ENGINE 0x101C5E30
// FUNCTION: ENGINE 0x101C5E40
// FUNCTION: ENGINE 0x101C5E70
// FUNCTION: ENGINE 0x101C5E80
// FUNCTION: ENGINE 0x101C5EB0
// FUNCTION: ENGINE 0x101C5EC0
// FUNCTION: ENGINE 0x101C5EF0
// FUNCTION: ENGINE 0x101C5F20
// FUNCTION: ENGINE 0x101C5F50
// FUNCTION: ENGINE 0x101C5F80
// FUNCTION: ENGINE 0x101C5FB0
// FUNCTION: ENGINE 0x101C5FE0
// FUNCTION: ENGINE 0x101C6010
// FUNCTION: ENGINE 0x101C6040
// FUNCTION: ENGINE 0x101C6070
// FUNCTION: ENGINE 0x101C60B0
// FUNCTION: ENGINE 0x101C60C0
// FUNCTION: ENGINE 0x101C60F0
// FUNCTION: ENGINE 0x101C6110
// FUNCTION: ENGINE 0x101C6120
// FUNCTION: ENGINE 0x101C6160
// FUNCTION: ENGINE 0x101C6170
// FUNCTION: ENGINE 0x101C61A0
// FUNCTION: ENGINE 0x101C61C0
// FUNCTION: ENGINE 0x101C61D0
// FUNCTION: ENGINE 0x101C6200
// FUNCTION: ENGINE 0x101C6230
// FUNCTION: ENGINE 0x101C6240
// FUNCTION: ENGINE 0x101C6280
// FUNCTION: ENGINE 0x101C6290
// FUNCTION: ENGINE 0x101C62C0
// FUNCTION: ENGINE 0x101C62E0
// FUNCTION: ENGINE 0x101C62F0
// FUNCTION: ENGINE 0x101C6320
// FUNCTION: ENGINE 0x101C6350
// FUNCTION: ENGINE 0x101C6360
// FUNCTION: ENGINE 0x101C63A0
// FUNCTION: ENGINE 0x101C63B0
// FUNCTION: ENGINE 0x101C63E0
// FUNCTION: ENGINE 0x101C6400
// FUNCTION: ENGINE 0x101C6410
// FUNCTION: ENGINE 0x101C6440
// FUNCTION: ENGINE 0x101C6460
// FUNCTION: ENGINE 0x101C6470
// FUNCTION: ENGINE 0x101C64A0
// FUNCTION: ENGINE 0x101C64D0
// FUNCTION: ENGINE 0x101C64E0
// FUNCTION: ENGINE 0x101C6510
// FUNCTION: ENGINE 0x101C6530
// FUNCTION: ENGINE 0x101C6540
// FUNCTION: ENGINE 0x101C6570
// FUNCTION: ENGINE 0x101C65A0
// FUNCTION: ENGINE 0x101C65B0
// FUNCTION: ENGINE 0x101C65E0
// FUNCTION: ENGINE 0x101C6600
// FUNCTION: ENGINE 0x101C6610
// FUNCTION: ENGINE 0x101C6640
// FUNCTION: ENGINE 0x101C6670
// FUNCTION: ENGINE 0x101C6680
// FUNCTION: ENGINE 0x101C66B0
// FUNCTION: ENGINE 0x101C66D0
// FUNCTION: ENGINE 0x101C66E0
// FUNCTION: ENGINE 0x101C6710
// FUNCTION: ENGINE 0x101C6740
// FUNCTION: ENGINE 0x101C6750
// FUNCTION: ENGINE 0x101C6790
// FUNCTION: ENGINE 0x101C67A0
// FUNCTION: ENGINE 0x101C67D0
// FUNCTION: ENGINE 0x101C67F0
// FUNCTION: ENGINE 0x101C6800
// FUNCTION: ENGINE 0x101C6830
// FUNCTION: ENGINE 0x101C6850
// FUNCTION: ENGINE 0x101C6860
// FUNCTION: ENGINE 0x101C6890
// FUNCTION: ENGINE 0x101C68B0
// FUNCTION: ENGINE 0x101C68C0
// FUNCTION: ENGINE 0x101C68F0
// FUNCTION: ENGINE 0x101C6920
// FUNCTION: ENGINE 0x101C6930
// FUNCTION: ENGINE 0x101C6960
// FUNCTION: ENGINE 0x101C6980
// FUNCTION: ENGINE 0x101C6990
// FUNCTION: ENGINE 0x101C69D0
// FUNCTION: ENGINE 0x101C69E0
// FUNCTION: ENGINE 0x101C6A10
// FUNCTION: ENGINE 0x101C6A30
// FUNCTION: ENGINE 0x101C6A40
// FUNCTION: ENGINE 0x101C6A70
// FUNCTION: ENGINE 0x101C6A90
// FUNCTION: ENGINE 0x101C6EF0
// FUNCTION: ENGINE 0x101C6F20
// FUNCTION: ENGINE 0x101C6F40
// FUNCTION: ENGINE 0x101C6F70
// FUNCTION: ENGINE 0x101C6F90
// FUNCTION: ENGINE 0x101C6FC0
// FUNCTION: ENGINE 0x101C6FE0
// FUNCTION: ENGINE 0x101C7010
// FUNCTION: ENGINE 0x101C7030
// FUNCTION: ENGINE 0x101C7060
// FUNCTION: ENGINE 0x101C7080
// FUNCTION: ENGINE 0x101C70B0
// FUNCTION: ENGINE 0x101C70D0
// FUNCTION: ENGINE 0x101C7100
// FUNCTION: ENGINE 0x101C7120
// FUNCTION: ENGINE 0x101C7150
// FUNCTION: ENGINE 0x101C7170
// FUNCTION: ENGINE 0x101C71A0
// FUNCTION: ENGINE 0x101C71C0
// FUNCTION: ENGINE 0x101C71D0
// FUNCTION: ENGINE 0x101C7200
// FUNCTION: ENGINE 0x101C7EC0
// FUNCTION: ENGINE 0x101C7F10
// FUNCTION: ENGINE 0x101C7F40
// FUNCTION: ENGINE 0x101C7F60
// FUNCTION: ENGINE 0x101C7F90
// FUNCTION: ENGINE 0x101C7FB0
// FUNCTION: ENGINE 0x101C7FE0
// FUNCTION: ENGINE 0x101C8000
// FUNCTION: ENGINE 0x101C8030
// FUNCTION: ENGINE 0x101C8050
// FUNCTION: ENGINE 0x101C8080
// FUNCTION: ENGINE 0x101C80A0
// FUNCTION: ENGINE 0x101C80D0
// FUNCTION: ENGINE 0x101C80F0
// FUNCTION: ENGINE 0x101C8120
// FUNCTION: ENGINE 0x101C8140
// FUNCTION: ENGINE 0x101C8170
// FUNCTION: ENGINE 0x101C8190
// FUNCTION: ENGINE 0x101C81E0
// FUNCTION: ENGINE 0x101C8230
// FUNCTION: ENGINE 0x101C8280
// FUNCTION: ENGINE 0x101C82D0
// FUNCTION: ENGINE 0x101C8320
// FUNCTION: ENGINE 0x101C8370
// FUNCTION: ENGINE 0x101C83C0
