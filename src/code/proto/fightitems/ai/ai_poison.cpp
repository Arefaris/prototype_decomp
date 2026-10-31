// Fight items of the ai group: IsPoisonedCondition, PoisonedTimeCondition, CurePoisonTrack, PoisonTrack, SetPoisonCloudParametersTrack (unit 0x10244F30 - 0x10246860; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_poison.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gIsPoisonedConditionProperties;  // 0x11255B3C

			// FUNCTION: ENGINE 0x10244F30
			bool IsPoisonedCondition::SetPoisonType(int newValue)
			{
				poisonType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10245110
			fight::Property* IsPoisonedCondition::GetProperty(int index)
			{
				return gIsPoisonedConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10245130
			void IsPoisonedCondition::ClearProperties()
			{
				fight::FreePropertyList(&gIsPoisonedConditionProperties);
			}

			// FUNCTION: ENGINE 0x10245140
			IsPoisonedCondition::IsPoisonedCondition() : fight::Condition(0), poisonType(0)
			{
			}

			// FUNCTION: ENGINE 0x10245170
			IsPoisonedCondition::~IsPoisonedCondition()
			{
			}

			// FUNCTION: ENGINE 0x10245CB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IsPoisonedCondition::RegisterProperties()
			{
				if (gIsPoisonedConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyIntConstRange<IsPoisonedCondition>("poisonType", &IsPoisonedCondition::SetPoisonType);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gIsPoisonedConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10245BC0
			fight::ConditionFactory* CreateIsPoisonedConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsPoisonedCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10246140
			void RegisterIsPoisonedConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsPoisonedCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPoisonedTimeConditionProperties;  // 0x11255B40

			// FUNCTION: ENGINE 0x10244F40
			bool PoisonedTimeCondition::SetCompareTime(int newValue)
			{
				compareTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10244F50
			bool PoisonedTimeCondition::SetTime(float newValue)
			{
				time = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10244F70
			bool PoisonedTimeCondition::SetPoisonType(int newValue)
			{
				poisonType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10245180
			fight::Property* PoisonedTimeCondition::GetProperty(int index)
			{
				return gPoisonedTimeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x102451A0
			void PoisonedTimeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPoisonedTimeConditionProperties);
			}

			// FUNCTION: ENGINE 0x102451B0
			PoisonedTimeCondition::PoisonedTimeCondition() : fight::Condition(0), time(0.0f), compareTime(4), poisonType(0)
			{
			}

			// FUNCTION: ENGINE 0x102451F0
			PoisonedTimeCondition::~PoisonedTimeCondition()
			{
			}

			// FUNCTION: ENGINE 0x10245D50
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PoisonedTimeCondition::RegisterProperties()
			{
				if (gPoisonedTimeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<PoisonedTimeCondition>("compareTime", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &PoisonedTimeCondition::SetCompareTime);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PoisonedTimeCondition>("time", &PoisonedTimeCondition::SetTime);
					properties[1] = property;
					property = new fight::PropertyIntConstRange<PoisonedTimeCondition>("poisonType", &PoisonedTimeCondition::SetPoisonType);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gPoisonedTimeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10245BF0
			fight::ConditionFactory* CreatePoisonedTimeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PoisonedTimeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10246170
			void RegisterPoisonedTimeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PoisonedTimeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gCurePoisonTrackProperties;  // 0x11255B44

			// FUNCTION: ENGINE 0x10244F80
			bool CurePoisonTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10244FA0
			bool CurePoisonTrack::SetPoisonType(int newValue)
			{
				poisonType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10245200
			fight::Property* CurePoisonTrack::GetProperty(int index)
			{
				return gCurePoisonTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10245220
			void CurePoisonTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCurePoisonTrackProperties);
			}

			// FUNCTION: ENGINE 0x10245230
			CurePoisonTrack::CurePoisonTrack() : timeBegin(0.0f), poisonType(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10245270
			float CurePoisonTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10245280
			float CurePoisonTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10245290
			CurePoisonTrack::~CurePoisonTrack()
			{
			}

			// FUNCTION: ENGINE 0x10245E80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CurePoisonTrack::RegisterProperties()
			{
				if (gCurePoisonTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CurePoisonTrack>("timeBegin", &CurePoisonTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<CurePoisonTrack>("poisonType", motion::gTendrilDevastatorTrackAttackTypeTable, motion::gTendrilDevastatorTrackAttackTypeCount, &CurePoisonTrack::SetPoisonType);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gCurePoisonTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10245C20
			fight::TrackFactory* CreateCurePoisonTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CurePoisonTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102461A0
			void RegisterCurePoisonTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CurePoisonTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gPoisonTrackProperties;  // 0x11255B48

			// FUNCTION: ENGINE 0x10244FB0
			bool PoisonTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10244FD0
			bool PoisonTrack::SetPoisonType(int newValue)
			{
				poisonType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10244FE0
			bool PoisonTrack::SetDamageRate(float newValue)
			{
				damageRate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10245000
			bool PoisonTrack::SetDamageSpikes(float newValue)
			{
				damageSpikes = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10245020
			bool PoisonTrack::SetTimeToHit(float newValue)
			{
				timeToHit = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10245040
			bool PoisonTrack::SetExtraRandomTime(float newValue)
			{
				extraRandomTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10245060
			bool PoisonTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10245070
			bool PoisonTrack::SetWho(int newValue)
			{
				who = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10245380
			bool PoisonTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102452A0
			fight::Property* PoisonTrack::GetProperty(int index)
			{
				return gPoisonTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102452C0
			void PoisonTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPoisonTrackProperties);
			}

			// FUNCTION: ENGINE 0x10245430
			PoisonTrack::PoisonTrack() : damageRate(-1.0f), damageSpikes(-1.0f), extraRandomTime(-1.0f), timeBegin(0.0f), timeToHit(-1.0f), poisonType(0), priority(0), who(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x102454A0
			float PoisonTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x102454B0
			float PoisonTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x102454C0
			PoisonTrack::~PoisonTrack()
			{
			}

			// FUNCTION: ENGINE 0x102463D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PoisonTrack::RegisterProperties()
			{
				if (gPoisonTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PoisonTrack>("timeBegin", &PoisonTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<PoisonTrack>("poisonType", motion::gTendrilDevastatorTrackAttackTypeTable, motion::gTendrilDevastatorTrackAttackTypeCount, &PoisonTrack::SetPoisonType);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<PoisonTrack>("damageRate", &PoisonTrack::SetDamageRate);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<PoisonTrack>("damageSpikes", &PoisonTrack::SetDamageSpikes);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<PoisonTrack>("timeToHit", &PoisonTrack::SetTimeToHit);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<PoisonTrack>("extraRandomTime", &PoisonTrack::SetExtraRandomTime);
					properties[5] = property;
					property = new fight::PropertyIntConstRange<PoisonTrack>("priority", &PoisonTrack::SetPriority);
					properties[6] = property;
					property = new fight::PropertyEnumConstList<PoisonTrack>("who", gPoisonTrackWhoTable, gPoisonTrackWhoCount, &PoisonTrack::SetWho);
					properties[7] = property;
					property = new fight::PropertyNameList<PoisonTrack>("grabSlot", &PoisonTrack::SetGrabSlot);
					properties[8] = property;
					fight::RegisterPropertyList(properties, &gPoisonTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10245C50
			fight::TrackFactory* CreatePoisonTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PoisonTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102461D0
			void RegisterPoisonTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PoisonTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSetPoisonCloudParametersTrackProperties;  // 0x11255B4C

			// FUNCTION: ENGINE 0x10245080
			bool SetPoisonCloudParametersTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102450A0
			bool SetPoisonCloudParametersTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102450C0
			bool SetPoisonCloudParametersTrack::SetGrowFacingDir(bool newValue)
			{
				growFacingDir = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102450D0
			bool SetPoisonCloudParametersTrack::SetGrowDownDir(bool newValue)
			{
				growDownDir = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102450E0
			bool SetPoisonCloudParametersTrack::SetInheritFacingDir(bool newValue)
			{
				inheritFacingDir = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102450F0
			bool SetPoisonCloudParametersTrack::SetFallToGroundSpeed(float newValue)
			{
				fallToGroundSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102452D0
			fight::Property* SetPoisonCloudParametersTrack::GetProperty(int index)
			{
				return gSetPoisonCloudParametersTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102452F0
			void SetPoisonCloudParametersTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetPoisonCloudParametersTrackProperties);
			}

			// FUNCTION: ENGINE 0x10245300
			SetPoisonCloudParametersTrack::SetPoisonCloudParametersTrack() : fallToGroundSpeed(0.0f), timeBegin(0.0f), timeEnd(-1.0f), growDownDir(false), growFacingDir(false), inheritFacingDir(false)
			{
			}

			// FUNCTION: ENGINE 0x10245350
			float SetPoisonCloudParametersTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10245360
			float SetPoisonCloudParametersTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10245370
			SetPoisonCloudParametersTrack::~SetPoisonCloudParametersTrack()
			{
			}

			// FUNCTION: ENGINE 0x10245F70
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetPoisonCloudParametersTrack::RegisterProperties()
			{
				if (gSetPoisonCloudParametersTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetPoisonCloudParametersTrack>("timeBegin", &SetPoisonCloudParametersTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SetPoisonCloudParametersTrack>("timeEnd", &SetPoisonCloudParametersTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<SetPoisonCloudParametersTrack>("growFacingDir", &SetPoisonCloudParametersTrack::SetGrowFacingDir);
					properties[2] = property;
					property = new fight::PropertyBool<SetPoisonCloudParametersTrack>("growDownDir", &SetPoisonCloudParametersTrack::SetGrowDownDir);
					properties[3] = property;
					property = new fight::PropertyBool<SetPoisonCloudParametersTrack>("inheritFacingDir", &SetPoisonCloudParametersTrack::SetInheritFacingDir);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<SetPoisonCloudParametersTrack>("fallToGroundSpeed", &SetPoisonCloudParametersTrack::SetFallToGroundSpeed);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gSetPoisonCloudParametersTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10245C80
			fight::TrackFactory* CreateSetPoisonCloudParametersTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetPoisonCloudParametersTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10246200
			void RegisterSetPoisonCloudParametersTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetPoisonCloudParametersTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyIntConstRange<IsPoisonedCondition>;
			template class fight::ConditionFactoryTemplate<IsPoisonedCondition>;
			template class fight::ConditionFactoryCasterTemplate<IsPoisonedCondition>;
			template class fight::PropertyEnumConstList<PoisonedTimeCondition>;
			template class fight::PropertyFloatConstRange<PoisonedTimeCondition>;
			template class fight::PropertyIntConstRange<PoisonedTimeCondition>;
			template class fight::ConditionFactoryTemplate<PoisonedTimeCondition>;
			template class fight::ConditionFactoryCasterTemplate<PoisonedTimeCondition>;
			template class fight::PropertyFloatConstRange<CurePoisonTrack>;
			template class fight::PropertyEnumConstList<CurePoisonTrack>;
			template class fight::TrackFactoryTemplate<CurePoisonTrack>;
			template class fight::TrackFactoryCasterTemplate<CurePoisonTrack>;
			template class fight::PropertyFloatConstRange<PoisonTrack>;
			template class fight::PropertyEnumConstList<PoisonTrack>;
			template class fight::PropertyIntConstRange<PoisonTrack>;
			template class fight::PropertyNameList<PoisonTrack>;
			template class fight::TrackFactoryTemplate<PoisonTrack>;
			template class fight::TrackFactoryCasterTemplate<PoisonTrack>;
			template class fight::PropertyFloatConstRange<SetPoisonCloudParametersTrack>;
			template class fight::PropertyBool<SetPoisonCloudParametersTrack>;
			template class fight::TrackFactoryTemplate<SetPoisonCloudParametersTrack>;
			template class fight::TrackFactoryCasterTemplate<SetPoisonCloudParametersTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102453A0
// FUNCTION: ENGINE 0x102453D0
// FUNCTION: ENGINE 0x10245400
// FUNCTION: ENGINE 0x102454D0
// FUNCTION: ENGINE 0x10245500
// FUNCTION: ENGINE 0x10245510
// FUNCTION: ENGINE 0x10245540
// FUNCTION: ENGINE 0x10245550
// FUNCTION: ENGINE 0x10245580
// FUNCTION: ENGINE 0x10245590
// FUNCTION: ENGINE 0x102455C0
// FUNCTION: ENGINE 0x102455D0
// FUNCTION: ENGINE 0x10245600
// FUNCTION: ENGINE 0x10245610
// FUNCTION: ENGINE 0x10245640
// FUNCTION: ENGINE 0x10245670
// FUNCTION: ENGINE 0x102456A0
// FUNCTION: ENGINE 0x102456C0
// FUNCTION: ENGINE 0x102456D0
// FUNCTION: ENGINE 0x10245710
// FUNCTION: ENGINE 0x10245720
// FUNCTION: ENGINE 0x10245750
// FUNCTION: ENGINE 0x10245770
// FUNCTION: ENGINE 0x10245780
// FUNCTION: ENGINE 0x102457B0
// FUNCTION: ENGINE 0x102457E0
// FUNCTION: ENGINE 0x102457F0
// FUNCTION: ENGINE 0x10245820
// FUNCTION: ENGINE 0x10245840
// FUNCTION: ENGINE 0x10245850
// FUNCTION: ENGINE 0x10245880
// FUNCTION: ENGINE 0x102458B0
// FUNCTION: ENGINE 0x102458C0
// FUNCTION: ENGINE 0x10245900
// FUNCTION: ENGINE 0x10245910
// FUNCTION: ENGINE 0x10245940
// FUNCTION: ENGINE 0x10245960
// FUNCTION: ENGINE 0x10245970
// FUNCTION: ENGINE 0x102459A0
// FUNCTION: ENGINE 0x102459D0
// FUNCTION: ENGINE 0x102459E0
// FUNCTION: ENGINE 0x10245A20
// FUNCTION: ENGINE 0x10245A30
// FUNCTION: ENGINE 0x10245A60
// FUNCTION: ENGINE 0x10245A80
// FUNCTION: ENGINE 0x10245A90
// FUNCTION: ENGINE 0x10245AC0
// FUNCTION: ENGINE 0x10245AE0
// FUNCTION: ENGINE 0x10245AF0
// FUNCTION: ENGINE 0x10245B20
// FUNCTION: ENGINE 0x10245B50
// FUNCTION: ENGINE 0x10245B60
// FUNCTION: ENGINE 0x10245B90
// FUNCTION: ENGINE 0x10245BB0
// FUNCTION: ENGINE 0x10246230
// FUNCTION: ENGINE 0x10246260
// FUNCTION: ENGINE 0x10246280
// FUNCTION: ENGINE 0x10246290
// FUNCTION: ENGINE 0x102462C0
// FUNCTION: ENGINE 0x102462E0
// FUNCTION: ENGINE 0x10246310
// FUNCTION: ENGINE 0x10246330
// FUNCTION: ENGINE 0x10246360
// FUNCTION: ENGINE 0x10246380
// FUNCTION: ENGINE 0x102463B0
// FUNCTION: ENGINE 0x10246680
// FUNCTION: ENGINE 0x102466D0
// FUNCTION: ENGINE 0x10246720
// FUNCTION: ENGINE 0x10246770
// FUNCTION: ENGINE 0x102467C0
// FUNCTION: ENGINE 0x102467F0
// FUNCTION: ENGINE 0x10246810
