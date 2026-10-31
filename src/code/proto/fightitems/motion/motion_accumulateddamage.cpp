// Fight items of the motion group: AccumulatedDamageCondition, IsUndamageableCondition, DisableTimeWithNoDamageCounterTrack, IgnoreHitsTrack, TempRegenAbortTrack, HealthSetMultiplierTrack, AccumulatedDamageResetTrack, TempRegenerationTrack (unit 0x10177EA0 - 0x10179BB0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_accumulateddamage.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gAccumulatedDamageConditionProperties;  // 0x112546C0

			// FUNCTION: ENGINE 0x10177EA0
			bool AccumulatedDamageCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10177EB0
			bool AccumulatedDamageCondition::SetValue(float newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10178080
			fight::Property* AccumulatedDamageCondition::GetProperty(int index)
			{
				return gAccumulatedDamageConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101780A0
			void AccumulatedDamageCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAccumulatedDamageConditionProperties);
			}

			// FUNCTION: ENGINE 0x101780B0
			AccumulatedDamageCondition::AccumulatedDamageCondition() : fight::Condition(0), value(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101780E0
			AccumulatedDamageCondition::~AccumulatedDamageCondition()
			{
			}

			// FUNCTION: ENGINE 0x10178F40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AccumulatedDamageCondition::RegisterProperties()
			{
				if (gAccumulatedDamageConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<AccumulatedDamageCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &AccumulatedDamageCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AccumulatedDamageCondition>("value", &AccumulatedDamageCondition::SetValue);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gAccumulatedDamageConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10178DC0
			fight::ConditionFactory* CreateAccumulatedDamageConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AccumulatedDamageCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101795D0
			void RegisterAccumulatedDamageConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AccumulatedDamageCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gIsUndamageableConditionProperties;  // 0x112546C4

			// FUNCTION: ENGINE 0x10178150
			fight::Property* IsUndamageableCondition::GetProperty(int index)
			{
				return gIsUndamageableConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10178170
			void IsUndamageableCondition::ClearProperties()
			{
				fight::FreePropertyList(&gIsUndamageableConditionProperties);
			}

			// FUNCTION: ENGINE 0x10178180
			IsUndamageableCondition::IsUndamageableCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x101781A0
			IsUndamageableCondition::~IsUndamageableCondition()
			{
			}

			// FUNCTION: ENGINE 0x101780F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IsUndamageableCondition::RegisterProperties()
			{
				if (gIsUndamageableConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gIsUndamageableConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10178DF0
			fight::ConditionFactory* CreateIsUndamageableConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsUndamageableCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10179600
			void RegisterIsUndamageableConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsUndamageableCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDisableTimeWithNoDamageCounterTrackProperties;  // 0x112546C8

			// FUNCTION: ENGINE 0x10177ED0
			bool DisableTimeWithNoDamageCounterTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10177EF0
			bool DisableTimeWithNoDamageCounterTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101781B0
			fight::Property* DisableTimeWithNoDamageCounterTrack::GetProperty(int index)
			{
				return gDisableTimeWithNoDamageCounterTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101781D0
			void DisableTimeWithNoDamageCounterTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDisableTimeWithNoDamageCounterTrackProperties);
			}

			// FUNCTION: ENGINE 0x101781E0
			DisableTimeWithNoDamageCounterTrack::DisableTimeWithNoDamageCounterTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10178220
			float DisableTimeWithNoDamageCounterTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10178230
			float DisableTimeWithNoDamageCounterTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10178240
			DisableTimeWithNoDamageCounterTrack::~DisableTimeWithNoDamageCounterTrack()
			{
			}

			// FUNCTION: ENGINE 0x10179030
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DisableTimeWithNoDamageCounterTrack::RegisterProperties()
			{
				if (gDisableTimeWithNoDamageCounterTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DisableTimeWithNoDamageCounterTrack>("timeBegin", &DisableTimeWithNoDamageCounterTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DisableTimeWithNoDamageCounterTrack>("timeEnd", &DisableTimeWithNoDamageCounterTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gDisableTimeWithNoDamageCounterTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10178E20
			fight::TrackFactory* CreateDisableTimeWithNoDamageCounterTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DisableTimeWithNoDamageCounterTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10179630
			void RegisterDisableTimeWithNoDamageCounterTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DisableTimeWithNoDamageCounterTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gIgnoreHitsTrackProperties;  // 0x112546CC

			// FUNCTION: ENGINE 0x10177F10
			bool IgnoreHitsTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10177F30
			bool IgnoreHitsTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10178250
			fight::Property* IgnoreHitsTrack::GetProperty(int index)
			{
				return gIgnoreHitsTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10178270
			void IgnoreHitsTrack::ClearProperties()
			{
				fight::FreePropertyList(&gIgnoreHitsTrackProperties);
			}

			// FUNCTION: ENGINE 0x10178280
			IgnoreHitsTrack::IgnoreHitsTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101782C0
			float IgnoreHitsTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101782D0
			float IgnoreHitsTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101782E0
			IgnoreHitsTrack::~IgnoreHitsTrack()
			{
			}

			// FUNCTION: ENGINE 0x10179110
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IgnoreHitsTrack::RegisterProperties()
			{
				if (gIgnoreHitsTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<IgnoreHitsTrack>("timeBegin", &IgnoreHitsTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<IgnoreHitsTrack>("timeEnd", &IgnoreHitsTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gIgnoreHitsTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10178E50
			fight::TrackFactory* CreateIgnoreHitsTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<IgnoreHitsTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10179660
			void RegisterIgnoreHitsTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<IgnoreHitsTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTempRegenAbortTrackProperties;  // 0x112546D0

			// FUNCTION: ENGINE 0x10177F50
			bool TempRegenAbortTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101782F0
			fight::Property* TempRegenAbortTrack::GetProperty(int index)
			{
				return gTempRegenAbortTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10178310
			void TempRegenAbortTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTempRegenAbortTrackProperties);
			}

			// FUNCTION: ENGINE 0x10178320
			TempRegenAbortTrack::TempRegenAbortTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10178350
			float TempRegenAbortTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10178360
			float TempRegenAbortTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10178370
			TempRegenAbortTrack::~TempRegenAbortTrack()
			{
			}

			// FUNCTION: ENGINE 0x101791F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TempRegenAbortTrack::RegisterProperties()
			{
				if (gTempRegenAbortTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TempRegenAbortTrack>("timeBegin", &TempRegenAbortTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gTempRegenAbortTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10178E80
			fight::TrackFactory* CreateTempRegenAbortTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TempRegenAbortTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10179690
			void RegisterTempRegenAbortTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TempRegenAbortTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gHealthSetMultiplierTrackProperties;  // 0x112546D4

			// FUNCTION: ENGINE 0x10177F70
			bool HealthSetMultiplierTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10177F90
			bool HealthSetMultiplierTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10177FB0
			bool HealthSetMultiplierTrack::SetMultiplier(float newValue)
			{
				multiplier = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10177FD0
			bool HealthSetMultiplierTrack::SetRestoreOriginalOnEnd(bool newValue)
			{
				restoreOriginalOnEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10178380
			fight::Property* HealthSetMultiplierTrack::GetProperty(int index)
			{
				return gHealthSetMultiplierTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101783A0
			void HealthSetMultiplierTrack::ClearProperties()
			{
				fight::FreePropertyList(&gHealthSetMultiplierTrackProperties);
			}

			// FUNCTION: ENGINE 0x101783B0
			HealthSetMultiplierTrack::HealthSetMultiplierTrack() : multiplier(1.0f), timeBegin(0.0f), timeEnd(-1.0f), restoreOriginalOnEnd(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10178400
			float HealthSetMultiplierTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10178410
			float HealthSetMultiplierTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10178420
			HealthSetMultiplierTrack::~HealthSetMultiplierTrack()
			{
			}

			// FUNCTION: ENGINE 0x10179290
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HealthSetMultiplierTrack::RegisterProperties()
			{
				if (gHealthSetMultiplierTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<HealthSetMultiplierTrack>("timeBegin", &HealthSetMultiplierTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HealthSetMultiplierTrack>("timeEnd", &HealthSetMultiplierTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<HealthSetMultiplierTrack>("multiplier", &HealthSetMultiplierTrack::SetMultiplier);
					properties[2] = property;
					property = new fight::PropertyBool<HealthSetMultiplierTrack>("restoreOriginalOnEnd", &HealthSetMultiplierTrack::SetRestoreOriginalOnEnd);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gHealthSetMultiplierTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10178EB0
			fight::TrackFactory* CreateHealthSetMultiplierTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<HealthSetMultiplierTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101796C0
			void RegisterHealthSetMultiplierTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<HealthSetMultiplierTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAccumulatedDamageResetTrackProperties;  // 0x112546D8

			// FUNCTION: ENGINE 0x10177FE0
			bool AccumulatedDamageResetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10178430
			fight::Property* AccumulatedDamageResetTrack::GetProperty(int index)
			{
				return gAccumulatedDamageResetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10178450
			void AccumulatedDamageResetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAccumulatedDamageResetTrackProperties);
			}

			// FUNCTION: ENGINE 0x10178460
			AccumulatedDamageResetTrack::AccumulatedDamageResetTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10178490
			float AccumulatedDamageResetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101784A0
			float AccumulatedDamageResetTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101784B0
			AccumulatedDamageResetTrack::~AccumulatedDamageResetTrack()
			{
			}

			// FUNCTION: ENGINE 0x101793E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AccumulatedDamageResetTrack::RegisterProperties()
			{
				if (gAccumulatedDamageResetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AccumulatedDamageResetTrack>("timeBegin", &AccumulatedDamageResetTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gAccumulatedDamageResetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10178EE0
			fight::TrackFactory* CreateAccumulatedDamageResetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AccumulatedDamageResetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101796F0
			void RegisterAccumulatedDamageResetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AccumulatedDamageResetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTempRegenerationTrackProperties;  // 0x112546DC

			// FUNCTION: ENGINE 0x10178000
			bool TempRegenerationTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10178020
			bool TempRegenerationTrack::SetRegenRate(float newValue)
			{
				regenRate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10178040
			bool TempRegenerationTrack::SetRegenMaxHealthPercentage(float newValue)
			{
				regenMaxHealthPercentage = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10178060
			bool TempRegenerationTrack::SetExpiry(float newValue)
			{
				expiry = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101784C0
			fight::Property* TempRegenerationTrack::GetProperty(int index)
			{
				return gTempRegenerationTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101784E0
			void TempRegenerationTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTempRegenerationTrackProperties);
			}

			// FUNCTION: ENGINE 0x101784F0
			TempRegenerationTrack::TempRegenerationTrack() : expiry(5.0f), regenMaxHealthPercentage(0.3f), regenRate(1.0f), timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10178550
			float TempRegenerationTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10178560
			float TempRegenerationTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10178570
			TempRegenerationTrack::~TempRegenerationTrack()
			{
			}

			// FUNCTION: ENGINE 0x10179480
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TempRegenerationTrack::RegisterProperties()
			{
				if (gTempRegenerationTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TempRegenerationTrack>("timeBegin", &TempRegenerationTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TempRegenerationTrack>("regenRate", &TempRegenerationTrack::SetRegenRate);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TempRegenerationTrack>("regenMaxHealthPercentage", &TempRegenerationTrack::SetRegenMaxHealthPercentage);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<TempRegenerationTrack>("expiry", &TempRegenerationTrack::SetExpiry);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gTempRegenerationTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10178F10
			fight::TrackFactory* CreateTempRegenerationTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TempRegenerationTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10179720
			void RegisterTempRegenerationTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TempRegenerationTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<AccumulatedDamageCondition>;
			template class fight::PropertyFloatConstRange<AccumulatedDamageCondition>;
			template class fight::ConditionFactoryTemplate<AccumulatedDamageCondition>;
			template class fight::ConditionFactoryCasterTemplate<AccumulatedDamageCondition>;
			template class fight::ConditionFactoryTemplate<IsUndamageableCondition>;
			template class fight::ConditionFactoryCasterTemplate<IsUndamageableCondition>;
			template class fight::PropertyFloatConstRange<DisableTimeWithNoDamageCounterTrack>;
			template class fight::TrackFactoryTemplate<DisableTimeWithNoDamageCounterTrack>;
			template class fight::TrackFactoryCasterTemplate<DisableTimeWithNoDamageCounterTrack>;
			template class fight::PropertyFloatConstRange<IgnoreHitsTrack>;
			template class fight::TrackFactoryTemplate<IgnoreHitsTrack>;
			template class fight::TrackFactoryCasterTemplate<IgnoreHitsTrack>;
			template class fight::PropertyFloatConstRange<TempRegenAbortTrack>;
			template class fight::TrackFactoryTemplate<TempRegenAbortTrack>;
			template class fight::TrackFactoryCasterTemplate<TempRegenAbortTrack>;
			template class fight::PropertyFloatConstRange<HealthSetMultiplierTrack>;
			template class fight::PropertyBool<HealthSetMultiplierTrack>;
			template class fight::TrackFactoryTemplate<HealthSetMultiplierTrack>;
			template class fight::TrackFactoryCasterTemplate<HealthSetMultiplierTrack>;
			template class fight::PropertyFloatConstRange<AccumulatedDamageResetTrack>;
			template class fight::TrackFactoryTemplate<AccumulatedDamageResetTrack>;
			template class fight::TrackFactoryCasterTemplate<AccumulatedDamageResetTrack>;
			template class fight::PropertyFloatConstRange<TempRegenerationTrack>;
			template class fight::TrackFactoryTemplate<TempRegenerationTrack>;
			template class fight::TrackFactoryCasterTemplate<TempRegenerationTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10178580
// FUNCTION: ENGINE 0x101785B0
// FUNCTION: ENGINE 0x101785E0
// FUNCTION: ENGINE 0x10178610
// FUNCTION: ENGINE 0x10178640
// FUNCTION: ENGINE 0x10178670
// FUNCTION: ENGINE 0x101786A0
// FUNCTION: ENGINE 0x101786D0
// FUNCTION: ENGINE 0x10178700
// FUNCTION: ENGINE 0x10178710
// FUNCTION: ENGINE 0x10178740
// FUNCTION: ENGINE 0x10178750
// FUNCTION: ENGINE 0x10178780
// FUNCTION: ENGINE 0x101787B0
// FUNCTION: ENGINE 0x101787D0
// FUNCTION: ENGINE 0x10178820
// FUNCTION: ENGINE 0x10178830
// FUNCTION: ENGINE 0x10178860
// FUNCTION: ENGINE 0x10178870
// FUNCTION: ENGINE 0x101788A0
// FUNCTION: ENGINE 0x101788B0
// FUNCTION: ENGINE 0x101788E0
// FUNCTION: ENGINE 0x101788F0
// FUNCTION: ENGINE 0x10178920
// FUNCTION: ENGINE 0x10178930
// FUNCTION: ENGINE 0x10178960
// FUNCTION: ENGINE 0x10178970
// FUNCTION: ENGINE 0x101789A0
// FUNCTION: ENGINE 0x101789E0
// FUNCTION: ENGINE 0x101789F0
// FUNCTION: ENGINE 0x10178A20
// FUNCTION: ENGINE 0x10178A40
// FUNCTION: ENGINE 0x10178A50
// FUNCTION: ENGINE 0x10178A80
// FUNCTION: ENGINE 0x10178AB0
// FUNCTION: ENGINE 0x10178AC0
// FUNCTION: ENGINE 0x10178AF0
// FUNCTION: ENGINE 0x10178B20
// FUNCTION: ENGINE 0x10178B30
// FUNCTION: ENGINE 0x10178B60
// FUNCTION: ENGINE 0x10178B90
// FUNCTION: ENGINE 0x10178BA0
// FUNCTION: ENGINE 0x10178BD0
// FUNCTION: ENGINE 0x10178C00
// FUNCTION: ENGINE 0x10178C10
// FUNCTION: ENGINE 0x10178C40
// FUNCTION: ENGINE 0x10178C70
// FUNCTION: ENGINE 0x10178C80
// FUNCTION: ENGINE 0x10178CB0
// FUNCTION: ENGINE 0x10178CD0
// FUNCTION: ENGINE 0x10178CE0
// FUNCTION: ENGINE 0x10178D10
// FUNCTION: ENGINE 0x10178D40
// FUNCTION: ENGINE 0x10178D50
// FUNCTION: ENGINE 0x10178D80
// FUNCTION: ENGINE 0x10178DB0
// FUNCTION: ENGINE 0x10179750
// FUNCTION: ENGINE 0x10179780
// FUNCTION: ENGINE 0x101797A0
// FUNCTION: ENGINE 0x101797D0
// FUNCTION: ENGINE 0x101797F0
// FUNCTION: ENGINE 0x10179820
// FUNCTION: ENGINE 0x10179840
// FUNCTION: ENGINE 0x10179870
// FUNCTION: ENGINE 0x10179890
// FUNCTION: ENGINE 0x101798C0
// FUNCTION: ENGINE 0x101798E0
// FUNCTION: ENGINE 0x10179910
// FUNCTION: ENGINE 0x10179930
// FUNCTION: ENGINE 0x10179960
// FUNCTION: ENGINE 0x10179980
// FUNCTION: ENGINE 0x101799D0
// FUNCTION: ENGINE 0x10179A20
// FUNCTION: ENGINE 0x10179A70
// FUNCTION: ENGINE 0x10179AC0
// FUNCTION: ENGINE 0x10179B10
// FUNCTION: ENGINE 0x10179B60
