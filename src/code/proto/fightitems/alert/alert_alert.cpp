// Fight items of the alert group: InsideAlertedAreaCondition, ShouldCallStrikeTeamCondition, RadioedCondition, GraceSwitchDisguisesCondition, PlayerSeenCondition, FriendlyFireVariableCondition, AlertVariableCondition, HostileWithMilitaryCondition, InsideAlertCircleCondition, PursuitGuysCondition, AllyWithMilitaryCondition, AlertVariableIncreasedSinceCondition, BeginCombatGuysCondition, ValidMilitaryDisguiseCondition, SeenCondition, PursuitTimeCondition, AlertCircleDistanceCondition, MilitaryDisguiseCondition, ReportBackToIdleTrack, ReportEnterBeginCombatTrack, RadioedSetTrack, DisablePoliceTrack, AlertReportTrack, CallStrikeTeamTrack, PlayerCallStrikeTeamTrack, SetInPursuitTrack, StartStrikeTeamMeterTrack, SetAlertVariableTrack, ResetAlertVariablesTrack, ScenarioMessageTrack, StopStrikeTeamMeterTrack, HoldOnAlertEventsTrack (unit 0x1026E0E0 - 0x10275910; no assert path, the file name is a guess).
#include "code/proto/fightitems/alert/alert_alert.h"

namespace proto
{
	namespace fightitems
	{
		namespace alert
		{
			fight::Property** gInsideAlertedAreaConditionProperties;  // 0x1125604C

			// FUNCTION: ENGINE 0x1026E0E0
			bool InsideAlertedAreaCondition::SetInside(bool newValue)
			{
				inside = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E0F0
			bool InsideAlertedAreaCondition::SetPlayerOnly(bool newValue)
			{
				playerOnly = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E6B0
			fight::Property* InsideAlertedAreaCondition::GetProperty(int index)
			{
				return gInsideAlertedAreaConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026E6D0
			void InsideAlertedAreaCondition::ClearProperties()
			{
				fight::FreePropertyList(&gInsideAlertedAreaConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026E6E0
			InsideAlertedAreaCondition::InsideAlertedAreaCondition() : fight::Condition(0), inside(true), playerOnly(false)
			{
			}

			// FUNCTION: ENGINE 0x1026E710
			InsideAlertedAreaCondition::~InsideAlertedAreaCondition()
			{
			}

			// FUNCTION: ENGINE 0x102724A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void InsideAlertedAreaCondition::RegisterProperties()
			{
				if (gInsideAlertedAreaConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<InsideAlertedAreaCondition>("inside", &InsideAlertedAreaCondition::SetInside);
					properties[0] = property;
					property = new fight::PropertyBool<InsideAlertedAreaCondition>("playerOnly", &InsideAlertedAreaCondition::SetPlayerOnly);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gInsideAlertedAreaConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10271EA0
			fight::ConditionFactory* CreateInsideAlertedAreaConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InsideAlertedAreaCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274050
			void RegisterInsideAlertedAreaConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InsideAlertedAreaCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gShouldCallStrikeTeamConditionProperties;  // 0x11256050

			// FUNCTION: ENGINE 0x1026E100
			bool ShouldCallStrikeTeamCondition::SetShould(bool newValue)
			{
				should = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E720
			fight::Property* ShouldCallStrikeTeamCondition::GetProperty(int index)
			{
				return gShouldCallStrikeTeamConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026E740
			void ShouldCallStrikeTeamCondition::ClearProperties()
			{
				fight::FreePropertyList(&gShouldCallStrikeTeamConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026E750
			ShouldCallStrikeTeamCondition::ShouldCallStrikeTeamCondition() : fight::Condition(0), should(true)
			{
			}

			// FUNCTION: ENGINE 0x1026E770
			ShouldCallStrikeTeamCondition::~ShouldCallStrikeTeamCondition()
			{
			}

			// FUNCTION: ENGINE 0x10272580
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShouldCallStrikeTeamCondition::RegisterProperties()
			{
				if (gShouldCallStrikeTeamConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ShouldCallStrikeTeamCondition>("should", &ShouldCallStrikeTeamCondition::SetShould);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gShouldCallStrikeTeamConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10271ED0
			fight::ConditionFactory* CreateShouldCallStrikeTeamConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShouldCallStrikeTeamCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274080
			void RegisterShouldCallStrikeTeamConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShouldCallStrikeTeamCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gRadioedConditionProperties;  // 0x11256054

			// FUNCTION: ENGINE 0x1026E110
			bool RadioedCondition::SetRadioed(bool newValue)
			{
				radioed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E780
			fight::Property* RadioedCondition::GetProperty(int index)
			{
				return gRadioedConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026E7A0
			void RadioedCondition::ClearProperties()
			{
				fight::FreePropertyList(&gRadioedConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026E7B0
			RadioedCondition::RadioedCondition() : fight::Condition(0), radioed(true)
			{
			}

			// FUNCTION: ENGINE 0x1026E7D0
			RadioedCondition::~RadioedCondition()
			{
			}

			// FUNCTION: ENGINE 0x10272620
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RadioedCondition::RegisterProperties()
			{
				if (gRadioedConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<RadioedCondition>("radioed", &RadioedCondition::SetRadioed);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gRadioedConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10271F00
			fight::ConditionFactory* CreateRadioedConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RadioedCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102740B0
			void RegisterRadioedConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RadioedCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGraceSwitchDisguisesConditionProperties;  // 0x11256058

			// FUNCTION: ENGINE 0x1026E120
			bool GraceSwitchDisguisesCondition::SetSince(int newValue)
			{
				since = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E130
			bool GraceSwitchDisguisesCondition::SetTime(float newValue)
			{
				time = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E7E0
			fight::Property* GraceSwitchDisguisesCondition::GetProperty(int index)
			{
				return gGraceSwitchDisguisesConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026E800
			void GraceSwitchDisguisesCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGraceSwitchDisguisesConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026E810
			GraceSwitchDisguisesCondition::GraceSwitchDisguisesCondition() : fight::Condition(0), time(0.0f), since(0)
			{
			}

			// FUNCTION: ENGINE 0x1026E840
			GraceSwitchDisguisesCondition::~GraceSwitchDisguisesCondition()
			{
			}

			// FUNCTION: ENGINE 0x102726C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GraceSwitchDisguisesCondition::RegisterProperties()
			{
				if (gGraceSwitchDisguisesConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<GraceSwitchDisguisesCondition>("since", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &GraceSwitchDisguisesCondition::SetSince);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GraceSwitchDisguisesCondition>("time", &GraceSwitchDisguisesCondition::SetTime);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gGraceSwitchDisguisesConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10271F30
			fight::ConditionFactory* CreateGraceSwitchDisguisesConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GraceSwitchDisguisesCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102740E0
			void RegisterGraceSwitchDisguisesConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GraceSwitchDisguisesCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPlayerSeenConditionProperties;  // 0x1125605C

			// FUNCTION: ENGINE 0x1026E150
			bool PlayerSeenCondition::SetSeen(bool newValue)
			{
				seen = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E160
			bool PlayerSeenCondition::SetSince(int newValue)
			{
				since = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E170
			bool PlayerSeenCondition::SetTime(float newValue)
			{
				time = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E850
			fight::Property* PlayerSeenCondition::GetProperty(int index)
			{
				return gPlayerSeenConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026E870
			void PlayerSeenCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPlayerSeenConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026E880
			PlayerSeenCondition::PlayerSeenCondition() : fight::Condition(0), time(0.0f), since(0), seen(false)
			{
			}

			// FUNCTION: ENGINE 0x1026E8B0
			PlayerSeenCondition::~PlayerSeenCondition()
			{
			}

			// FUNCTION: ENGINE 0x102727B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PlayerSeenCondition::RegisterProperties()
			{
				if (gPlayerSeenConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<PlayerSeenCondition>("seen", &PlayerSeenCondition::SetSeen);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<PlayerSeenCondition>("since", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &PlayerSeenCondition::SetSince);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<PlayerSeenCondition>("time", &PlayerSeenCondition::SetTime);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gPlayerSeenConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10271F60
			fight::ConditionFactory* CreatePlayerSeenConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PlayerSeenCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274110
			void RegisterPlayerSeenConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PlayerSeenCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gFriendlyFireVariableConditionProperties;  // 0x11256060

			// FUNCTION: ENGINE 0x1026E190
			bool FriendlyFireVariableCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E1A0
			bool FriendlyFireVariableCondition::SetValue(float newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E8C0
			fight::Property* FriendlyFireVariableCondition::GetProperty(int index)
			{
				return gFriendlyFireVariableConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026E8E0
			void FriendlyFireVariableCondition::ClearProperties()
			{
				fight::FreePropertyList(&gFriendlyFireVariableConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026E8F0
			FriendlyFireVariableCondition::FriendlyFireVariableCondition() : fight::Condition(0), value(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x1026E920
			FriendlyFireVariableCondition::~FriendlyFireVariableCondition()
			{
			}

			// FUNCTION: ENGINE 0x102728E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FriendlyFireVariableCondition::RegisterProperties()
			{
				if (gFriendlyFireVariableConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<FriendlyFireVariableCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &FriendlyFireVariableCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FriendlyFireVariableCondition>("value", &FriendlyFireVariableCondition::SetValue);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gFriendlyFireVariableConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10271F90
			fight::ConditionFactory* CreateFriendlyFireVariableConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FriendlyFireVariableCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274140
			void RegisterFriendlyFireVariableConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FriendlyFireVariableCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gAlertVariableConditionProperties;  // 0x11256064

			// FUNCTION: ENGINE 0x1026E1C0
			bool AlertVariableCondition::SetVariable(int newValue)
			{
				variable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E1D0
			bool AlertVariableCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E1E0
			bool AlertVariableCondition::SetValue(float newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E930
			fight::Property* AlertVariableCondition::GetProperty(int index)
			{
				return gAlertVariableConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026E950
			void AlertVariableCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAlertVariableConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026E960
			AlertVariableCondition::AlertVariableCondition() : fight::Condition(0), value(0.0f), compare(0), variable(0)
			{
			}

			// FUNCTION: ENGINE 0x1026E9A0
			AlertVariableCondition::~AlertVariableCondition()
			{
			}

			// FUNCTION: ENGINE 0x102729D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AlertVariableCondition::RegisterProperties()
			{
				if (gAlertVariableConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<AlertVariableCondition>("variable", gAlertVariableConditionVariableTable, gAlertVariableConditionVariableCount, &AlertVariableCondition::SetVariable);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<AlertVariableCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &AlertVariableCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<AlertVariableCondition>("value", &AlertVariableCondition::SetValue);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gAlertVariableConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10271FC0
			fight::ConditionFactory* CreateAlertVariableConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AlertVariableCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274170
			void RegisterAlertVariableConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AlertVariableCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHostileWithMilitaryConditionProperties;  // 0x11256068

			// FUNCTION: ENGINE 0x1026EA10
			fight::Property* HostileWithMilitaryCondition::GetProperty(int index)
			{
				return gHostileWithMilitaryConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026EA30
			void HostileWithMilitaryCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHostileWithMilitaryConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026EA40
			HostileWithMilitaryCondition::HostileWithMilitaryCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1026EA60
			HostileWithMilitaryCondition::~HostileWithMilitaryCondition()
			{
			}

			// FUNCTION: ENGINE 0x1026E9B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HostileWithMilitaryCondition::RegisterProperties()
			{
				if (gHostileWithMilitaryConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gHostileWithMilitaryConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10271FF0
			fight::ConditionFactory* CreateHostileWithMilitaryConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HostileWithMilitaryCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102741A0
			void RegisterHostileWithMilitaryConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HostileWithMilitaryCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gInsideAlertCircleConditionProperties;  // 0x1125606C

			// FUNCTION: ENGINE 0x1026E200
			bool InsideAlertCircleCondition::SetInside(bool newValue)
			{
				inside = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026EA70
			fight::Property* InsideAlertCircleCondition::GetProperty(int index)
			{
				return gInsideAlertCircleConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026EA90
			void InsideAlertCircleCondition::ClearProperties()
			{
				fight::FreePropertyList(&gInsideAlertCircleConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026EAA0
			InsideAlertCircleCondition::InsideAlertCircleCondition() : fight::Condition(0), inside(true)
			{
			}

			// FUNCTION: ENGINE 0x1026EAC0
			InsideAlertCircleCondition::~InsideAlertCircleCondition()
			{
			}

			// FUNCTION: ENGINE 0x10272B10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void InsideAlertCircleCondition::RegisterProperties()
			{
				if (gInsideAlertCircleConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<InsideAlertCircleCondition>("inside", &InsideAlertCircleCondition::SetInside);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gInsideAlertCircleConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272020
			fight::ConditionFactory* CreateInsideAlertCircleConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InsideAlertCircleCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102741D0
			void RegisterInsideAlertCircleConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InsideAlertCircleCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPursuitGuysConditionProperties;  // 0x11256070

			// FUNCTION: ENGINE 0x1026E210
			bool PursuitGuysCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E220
			bool PursuitGuysCondition::SetGuys(int newValue)
			{
				guys = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026EAD0
			fight::Property* PursuitGuysCondition::GetProperty(int index)
			{
				return gPursuitGuysConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026EAF0
			void PursuitGuysCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPursuitGuysConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026EB00
			PursuitGuysCondition::PursuitGuysCondition() : fight::Condition(0), compare(0), guys(0)
			{
			}

			// FUNCTION: ENGINE 0x1026EB30
			PursuitGuysCondition::~PursuitGuysCondition()
			{
			}

			// FUNCTION: ENGINE 0x10272BB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PursuitGuysCondition::RegisterProperties()
			{
				if (gPursuitGuysConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<PursuitGuysCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &PursuitGuysCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyIntConstRange<PursuitGuysCondition>("guys", &PursuitGuysCondition::SetGuys);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gPursuitGuysConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272050
			fight::ConditionFactory* CreatePursuitGuysConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PursuitGuysCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274200
			void RegisterPursuitGuysConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PursuitGuysCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gAllyWithMilitaryConditionProperties;  // 0x11256074

			// FUNCTION: ENGINE 0x1026E230
			bool AllyWithMilitaryCondition::SetAlly(bool newValue)
			{
				ally = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026EB40
			fight::Property* AllyWithMilitaryCondition::GetProperty(int index)
			{
				return gAllyWithMilitaryConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026EB60
			void AllyWithMilitaryCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAllyWithMilitaryConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026EB70
			AllyWithMilitaryCondition::AllyWithMilitaryCondition() : fight::Condition(0), ally(true)
			{
			}

			// FUNCTION: ENGINE 0x1026EB90
			AllyWithMilitaryCondition::~AllyWithMilitaryCondition()
			{
			}

			// FUNCTION: ENGINE 0x10272CA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AllyWithMilitaryCondition::RegisterProperties()
			{
				if (gAllyWithMilitaryConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<AllyWithMilitaryCondition>("ally", &AllyWithMilitaryCondition::SetAlly);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gAllyWithMilitaryConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272080
			fight::ConditionFactory* CreateAllyWithMilitaryConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AllyWithMilitaryCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274230
			void RegisterAllyWithMilitaryConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AllyWithMilitaryCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gAlertVariableIncreasedSinceConditionProperties;  // 0x11256078

			// FUNCTION: ENGINE 0x1026E240
			bool AlertVariableIncreasedSinceCondition::SetVariable(int newValue)
			{
				variable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E250
			bool AlertVariableIncreasedSinceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E260
			bool AlertVariableIncreasedSinceCondition::SetValue(float newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026EBA0
			fight::Property* AlertVariableIncreasedSinceCondition::GetProperty(int index)
			{
				return gAlertVariableIncreasedSinceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026EBC0
			void AlertVariableIncreasedSinceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAlertVariableIncreasedSinceConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026EBD0
			AlertVariableIncreasedSinceCondition::AlertVariableIncreasedSinceCondition() : fight::Condition(0), value(0.0f), compare(0), variable(0)
			{
			}

			// FUNCTION: ENGINE 0x1026EC10
			AlertVariableIncreasedSinceCondition::~AlertVariableIncreasedSinceCondition()
			{
			}

			// FUNCTION: ENGINE 0x10272D40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AlertVariableIncreasedSinceCondition::RegisterProperties()
			{
				if (gAlertVariableIncreasedSinceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<AlertVariableIncreasedSinceCondition>("variable", gAlertVariableConditionVariableTable, gAlertVariableConditionVariableCount, &AlertVariableIncreasedSinceCondition::SetVariable);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<AlertVariableIncreasedSinceCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &AlertVariableIncreasedSinceCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<AlertVariableIncreasedSinceCondition>("value", &AlertVariableIncreasedSinceCondition::SetValue);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gAlertVariableIncreasedSinceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102720B0
			fight::ConditionFactory* CreateAlertVariableIncreasedSinceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AlertVariableIncreasedSinceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274260
			void RegisterAlertVariableIncreasedSinceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AlertVariableIncreasedSinceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gBeginCombatGuysConditionProperties;  // 0x1125607C

			// FUNCTION: ENGINE 0x1026E280
			bool BeginCombatGuysCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E290
			bool BeginCombatGuysCondition::SetGuys(int newValue)
			{
				guys = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026EC20
			fight::Property* BeginCombatGuysCondition::GetProperty(int index)
			{
				return gBeginCombatGuysConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026EC40
			void BeginCombatGuysCondition::ClearProperties()
			{
				fight::FreePropertyList(&gBeginCombatGuysConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026EC50
			BeginCombatGuysCondition::BeginCombatGuysCondition() : fight::Condition(0), compare(0), guys(0)
			{
			}

			// FUNCTION: ENGINE 0x1026EC80
			BeginCombatGuysCondition::~BeginCombatGuysCondition()
			{
			}

			// FUNCTION: ENGINE 0x10272E80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void BeginCombatGuysCondition::RegisterProperties()
			{
				if (gBeginCombatGuysConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<BeginCombatGuysCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &BeginCombatGuysCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyIntConstRange<BeginCombatGuysCondition>("guys", &BeginCombatGuysCondition::SetGuys);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gBeginCombatGuysConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102720E0
			fight::ConditionFactory* CreateBeginCombatGuysConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<BeginCombatGuysCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274290
			void RegisterBeginCombatGuysConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<BeginCombatGuysCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gValidMilitaryDisguiseConditionProperties;  // 0x11256080

			// FUNCTION: ENGINE 0x1026E2A0
			bool ValidMilitaryDisguiseCondition::SetValid(bool newValue)
			{
				valid = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026EC90
			fight::Property* ValidMilitaryDisguiseCondition::GetProperty(int index)
			{
				return gValidMilitaryDisguiseConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026ECB0
			void ValidMilitaryDisguiseCondition::ClearProperties()
			{
				fight::FreePropertyList(&gValidMilitaryDisguiseConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026ECC0
			ValidMilitaryDisguiseCondition::ValidMilitaryDisguiseCondition() : fight::Condition(0), valid(true)
			{
			}

			// FUNCTION: ENGINE 0x1026ECE0
			ValidMilitaryDisguiseCondition::~ValidMilitaryDisguiseCondition()
			{
			}

			// FUNCTION: ENGINE 0x10272F70
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ValidMilitaryDisguiseCondition::RegisterProperties()
			{
				if (gValidMilitaryDisguiseConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ValidMilitaryDisguiseCondition>("valid", &ValidMilitaryDisguiseCondition::SetValid);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gValidMilitaryDisguiseConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272110
			fight::ConditionFactory* CreateValidMilitaryDisguiseConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ValidMilitaryDisguiseCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102742C0
			void RegisterValidMilitaryDisguiseConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ValidMilitaryDisguiseCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSeenConditionProperties;  // 0x11256084

			// FUNCTION: ENGINE 0x1026E2B0
			bool SeenCondition::SetSeen(bool newValue)
			{
				seen = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E2C0
			bool SeenCondition::SetSince(int newValue)
			{
				since = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E2D0
			bool SeenCondition::SetTime(float newValue)
			{
				time = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026ECF0
			fight::Property* SeenCondition::GetProperty(int index)
			{
				return gSeenConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026ED10
			void SeenCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSeenConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026ED20
			SeenCondition::SeenCondition() : fight::Condition(0), time(0.0f), since(0), seen(false)
			{
			}

			// FUNCTION: ENGINE 0x1026ED50
			SeenCondition::~SeenCondition()
			{
			}

			// FUNCTION: ENGINE 0x10273010
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SeenCondition::RegisterProperties()
			{
				if (gSeenConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<SeenCondition>("seen", &SeenCondition::SetSeen);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<SeenCondition>("since", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &SeenCondition::SetSince);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<SeenCondition>("time", &SeenCondition::SetTime);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gSeenConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272140
			fight::ConditionFactory* CreateSeenConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SeenCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102742F0
			void RegisterSeenConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SeenCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPursuitTimeConditionProperties;  // 0x11256088

			// FUNCTION: ENGINE 0x1026E2F0
			bool PursuitTimeCondition::SetSince(int newValue)
			{
				since = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E300
			bool PursuitTimeCondition::SetTime(float newValue)
			{
				time = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026ED60
			fight::Property* PursuitTimeCondition::GetProperty(int index)
			{
				return gPursuitTimeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026ED80
			void PursuitTimeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPursuitTimeConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026ED90
			PursuitTimeCondition::PursuitTimeCondition() : fight::Condition(0), time(0.0f), since(0)
			{
			}

			// FUNCTION: ENGINE 0x1026EDC0
			PursuitTimeCondition::~PursuitTimeCondition()
			{
			}

			// FUNCTION: ENGINE 0x10273140
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PursuitTimeCondition::RegisterProperties()
			{
				if (gPursuitTimeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<PursuitTimeCondition>("since", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &PursuitTimeCondition::SetSince);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PursuitTimeCondition>("time", &PursuitTimeCondition::SetTime);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gPursuitTimeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272170
			fight::ConditionFactory* CreatePursuitTimeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PursuitTimeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274320
			void RegisterPursuitTimeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PursuitTimeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gAlertCircleDistanceConditionProperties;  // 0x1125608C

			// FUNCTION: ENGINE 0x1026E320
			bool AlertCircleDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E330
			bool AlertCircleDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026EDD0
			fight::Property* AlertCircleDistanceCondition::GetProperty(int index)
			{
				return gAlertCircleDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026EDF0
			void AlertCircleDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAlertCircleDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026EE00
			AlertCircleDistanceCondition::AlertCircleDistanceCondition() : fight::Condition(0), distance(5e+01f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x1026EE40
			AlertCircleDistanceCondition::~AlertCircleDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x10273230
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AlertCircleDistanceCondition::RegisterProperties()
			{
				if (gAlertCircleDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<AlertCircleDistanceCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &AlertCircleDistanceCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AlertCircleDistanceCondition>("distance", &AlertCircleDistanceCondition::SetDistance);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gAlertCircleDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102721A0
			fight::ConditionFactory* CreateAlertCircleDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AlertCircleDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274350
			void RegisterAlertCircleDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AlertCircleDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gMilitaryDisguiseConditionProperties;  // 0x11256090

			// FUNCTION: ENGINE 0x1026EEB0
			fight::Property* MilitaryDisguiseCondition::GetProperty(int index)
			{
				return gMilitaryDisguiseConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1026EED0
			void MilitaryDisguiseCondition::ClearProperties()
			{
				fight::FreePropertyList(&gMilitaryDisguiseConditionProperties);
			}

			// FUNCTION: ENGINE 0x1026EEE0
			MilitaryDisguiseCondition::MilitaryDisguiseCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1026EF00
			MilitaryDisguiseCondition::~MilitaryDisguiseCondition()
			{
			}

			// FUNCTION: ENGINE 0x1026EE50
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MilitaryDisguiseCondition::RegisterProperties()
			{
				if (gMilitaryDisguiseConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gMilitaryDisguiseConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102721D0
			fight::ConditionFactory* CreateMilitaryDisguiseConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<MilitaryDisguiseCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274380
			void RegisterMilitaryDisguiseConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<MilitaryDisguiseCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReportBackToIdleTrackProperties;  // 0x11256094

			// FUNCTION: ENGINE 0x1026E350
			bool ReportBackToIdleTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E370
			bool ReportBackToIdleTrack::SetEvade(bool newValue)
			{
				evade = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026EF10
			fight::Property* ReportBackToIdleTrack::GetProperty(int index)
			{
				return gReportBackToIdleTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1026EF30
			void ReportBackToIdleTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReportBackToIdleTrackProperties);
			}

			// FUNCTION: ENGINE 0x1026EF40
			ReportBackToIdleTrack::ReportBackToIdleTrack() : timeBegin(0.0f), evade(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1026EF70
			float ReportBackToIdleTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1026EF80
			float ReportBackToIdleTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1026EF90
			ReportBackToIdleTrack::~ReportBackToIdleTrack()
			{
			}

			// FUNCTION: ENGINE 0x10273320
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReportBackToIdleTrack::RegisterProperties()
			{
				if (gReportBackToIdleTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReportBackToIdleTrack>("timeBegin", &ReportBackToIdleTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyBool<ReportBackToIdleTrack>("evade", &ReportBackToIdleTrack::SetEvade);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReportBackToIdleTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272200
			fight::TrackFactory* CreateReportBackToIdleTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReportBackToIdleTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102743B0
			void RegisterReportBackToIdleTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReportBackToIdleTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gReportEnterBeginCombatTrackProperties;  // 0x11256098

			// FUNCTION: ENGINE 0x1026E380
			bool ReportEnterBeginCombatTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026EFA0
			fight::Property* ReportEnterBeginCombatTrack::GetProperty(int index)
			{
				return gReportEnterBeginCombatTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1026EFC0
			void ReportEnterBeginCombatTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReportEnterBeginCombatTrackProperties);
			}

			// FUNCTION: ENGINE 0x1026EFD0
			ReportEnterBeginCombatTrack::ReportEnterBeginCombatTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1026F000
			float ReportEnterBeginCombatTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F010
			float ReportEnterBeginCombatTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1026F020
			ReportEnterBeginCombatTrack::~ReportEnterBeginCombatTrack()
			{
			}

			// FUNCTION: ENGINE 0x10273400
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReportEnterBeginCombatTrack::RegisterProperties()
			{
				if (gReportEnterBeginCombatTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReportEnterBeginCombatTrack>("timeBegin", &ReportEnterBeginCombatTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gReportEnterBeginCombatTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272230
			fight::TrackFactory* CreateReportEnterBeginCombatTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReportEnterBeginCombatTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102743E0
			void RegisterReportEnterBeginCombatTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReportEnterBeginCombatTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gRadioedSetTrackProperties;  // 0x1125609C

			// FUNCTION: ENGINE 0x1026E3A0
			bool RadioedSetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E3C0
			bool RadioedSetTrack::SetRadioed(bool newValue)
			{
				radioed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026F030
			fight::Property* RadioedSetTrack::GetProperty(int index)
			{
				return gRadioedSetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1026F050
			void RadioedSetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gRadioedSetTrackProperties);
			}

			// FUNCTION: ENGINE 0x1026F060
			RadioedSetTrack::RadioedSetTrack() : timeBegin(0.0f), radioed(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1026F090
			float RadioedSetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F0A0
			float RadioedSetTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1026F0B0
			RadioedSetTrack::~RadioedSetTrack()
			{
			}

			// FUNCTION: ENGINE 0x102734A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RadioedSetTrack::RegisterProperties()
			{
				if (gRadioedSetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<RadioedSetTrack>("timeBegin", &RadioedSetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyBool<RadioedSetTrack>("radioed", &RadioedSetTrack::SetRadioed);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gRadioedSetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272260
			fight::TrackFactory* CreateRadioedSetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<RadioedSetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274410
			void RegisterRadioedSetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<RadioedSetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDisablePoliceTrackProperties;  // 0x112560A0

			// FUNCTION: ENGINE 0x1026E3D0
			bool DisablePoliceTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E3F0
			bool DisablePoliceTrack::SetDisable(bool newValue)
			{
				disable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E400
			bool DisablePoliceTrack::SetDelay(float newValue)
			{
				delay = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026F0C0
			fight::Property* DisablePoliceTrack::GetProperty(int index)
			{
				return gDisablePoliceTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1026F0E0
			void DisablePoliceTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDisablePoliceTrackProperties);
			}

			// FUNCTION: ENGINE 0x1026F0F0
			DisablePoliceTrack::DisablePoliceTrack() : delay(0.0f), timeBegin(0.0f), disable(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1026F130
			float DisablePoliceTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F140
			float DisablePoliceTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1026F150
			DisablePoliceTrack::~DisablePoliceTrack()
			{
			}

			// FUNCTION: ENGINE 0x10273580
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DisablePoliceTrack::RegisterProperties()
			{
				if (gDisablePoliceTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DisablePoliceTrack>("timeBegin", &DisablePoliceTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyBool<DisablePoliceTrack>("disable", &DisablePoliceTrack::SetDisable);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DisablePoliceTrack>("delay", &DisablePoliceTrack::SetDelay);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gDisablePoliceTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272290
			fight::TrackFactory* CreateDisablePoliceTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DisablePoliceTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274440
			void RegisterDisablePoliceTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DisablePoliceTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAlertReportTrackProperties;  // 0x112560A4

			// FUNCTION: ENGINE 0x1026E420
			bool AlertReportTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E440
			bool AlertReportTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E460
			bool AlertReportTrack::SetTimeout(float newValue)
			{
				timeout = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026F160
			fight::Property* AlertReportTrack::GetProperty(int index)
			{
				return gAlertReportTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1026F180
			void AlertReportTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAlertReportTrackProperties);
			}

			// FUNCTION: ENGINE 0x1026F190
			AlertReportTrack::AlertReportTrack() : timeBegin(0.0f), timeEnd(-1.0f), timeout(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1026F1D0
			float AlertReportTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F1E0
			float AlertReportTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F1F0
			AlertReportTrack::~AlertReportTrack()
			{
			}

			// FUNCTION: ENGINE 0x10273690
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AlertReportTrack::RegisterProperties()
			{
				if (gAlertReportTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AlertReportTrack>("timeBegin", &AlertReportTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AlertReportTrack>("timeEnd", &AlertReportTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<AlertReportTrack>("timeout", &AlertReportTrack::SetTimeout);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gAlertReportTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102722C0
			fight::TrackFactory* CreateAlertReportTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AlertReportTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274470
			void RegisterAlertReportTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AlertReportTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gCallStrikeTeamTrackProperties;  // 0x112560A8

			// FUNCTION: ENGINE 0x1026E480
			bool CallStrikeTeamTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026F200
			fight::Property* CallStrikeTeamTrack::GetProperty(int index)
			{
				return gCallStrikeTeamTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1026F220
			void CallStrikeTeamTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCallStrikeTeamTrackProperties);
			}

			// FUNCTION: ENGINE 0x1026F230
			CallStrikeTeamTrack::CallStrikeTeamTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1026F260
			float CallStrikeTeamTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F270
			float CallStrikeTeamTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1026F280
			CallStrikeTeamTrack::~CallStrikeTeamTrack()
			{
			}

			// FUNCTION: ENGINE 0x102737A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CallStrikeTeamTrack::RegisterProperties()
			{
				if (gCallStrikeTeamTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CallStrikeTeamTrack>("timeBegin", &CallStrikeTeamTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gCallStrikeTeamTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102722F0
			fight::TrackFactory* CreateCallStrikeTeamTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CallStrikeTeamTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102744A0
			void RegisterCallStrikeTeamTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CallStrikeTeamTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gPlayerCallStrikeTeamTrackProperties;  // 0x112560AC

			// FUNCTION: ENGINE 0x1026E4A0
			bool PlayerCallStrikeTeamTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026F290
			fight::Property* PlayerCallStrikeTeamTrack::GetProperty(int index)
			{
				return gPlayerCallStrikeTeamTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1026F2B0
			void PlayerCallStrikeTeamTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPlayerCallStrikeTeamTrackProperties);
			}

			// FUNCTION: ENGINE 0x1026F2C0
			PlayerCallStrikeTeamTrack::PlayerCallStrikeTeamTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1026F2F0
			float PlayerCallStrikeTeamTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F300
			float PlayerCallStrikeTeamTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1026F310
			PlayerCallStrikeTeamTrack::~PlayerCallStrikeTeamTrack()
			{
			}

			// FUNCTION: ENGINE 0x10273840
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PlayerCallStrikeTeamTrack::RegisterProperties()
			{
				if (gPlayerCallStrikeTeamTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PlayerCallStrikeTeamTrack>("timeBegin", &PlayerCallStrikeTeamTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gPlayerCallStrikeTeamTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272320
			fight::TrackFactory* CreatePlayerCallStrikeTeamTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PlayerCallStrikeTeamTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102744D0
			void RegisterPlayerCallStrikeTeamTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PlayerCallStrikeTeamTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSetInPursuitTrackProperties;  // 0x112560B0

			// FUNCTION: ENGINE 0x1026E4C0
			bool SetInPursuitTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E4E0
			bool SetInPursuitTrack::SetPursuit(bool newValue)
			{
				pursuit = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026F320
			fight::Property* SetInPursuitTrack::GetProperty(int index)
			{
				return gSetInPursuitTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1026F340
			void SetInPursuitTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetInPursuitTrackProperties);
			}

			// FUNCTION: ENGINE 0x1026F350
			SetInPursuitTrack::SetInPursuitTrack() : timeBegin(0.0f), pursuit(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1026F380
			float SetInPursuitTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F390
			float SetInPursuitTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1026F3A0
			SetInPursuitTrack::~SetInPursuitTrack()
			{
			}

			// FUNCTION: ENGINE 0x102738E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetInPursuitTrack::RegisterProperties()
			{
				if (gSetInPursuitTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetInPursuitTrack>("timeBegin", &SetInPursuitTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyBool<SetInPursuitTrack>("pursuit", &SetInPursuitTrack::SetPursuit);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gSetInPursuitTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272350
			fight::TrackFactory* CreateSetInPursuitTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetInPursuitTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274500
			void RegisterSetInPursuitTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetInPursuitTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gStartStrikeTeamMeterTrackProperties;  // 0x112560B4

			// FUNCTION: ENGINE 0x1026E4F0
			bool StartStrikeTeamMeterTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E510
			bool StartStrikeTeamMeterTrack::SetTimeToSpawn(float newValue)
			{
				timeToSpawn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026F3B0
			fight::Property* StartStrikeTeamMeterTrack::GetProperty(int index)
			{
				return gStartStrikeTeamMeterTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1026F3D0
			void StartStrikeTeamMeterTrack::ClearProperties()
			{
				fight::FreePropertyList(&gStartStrikeTeamMeterTrackProperties);
			}

			// FUNCTION: ENGINE 0x1026F3E0
			StartStrikeTeamMeterTrack::StartStrikeTeamMeterTrack() : timeBegin(0.0f), timeToSpawn(5.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1026F420
			float StartStrikeTeamMeterTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F430
			float StartStrikeTeamMeterTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1026F440
			StartStrikeTeamMeterTrack::~StartStrikeTeamMeterTrack()
			{
			}

			// FUNCTION: ENGINE 0x102739C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void StartStrikeTeamMeterTrack::RegisterProperties()
			{
				if (gStartStrikeTeamMeterTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<StartStrikeTeamMeterTrack>("timeBegin", &StartStrikeTeamMeterTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<StartStrikeTeamMeterTrack>("timeToSpawn", &StartStrikeTeamMeterTrack::SetTimeToSpawn);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gStartStrikeTeamMeterTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272380
			fight::TrackFactory* CreateStartStrikeTeamMeterTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<StartStrikeTeamMeterTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274530
			void RegisterStartStrikeTeamMeterTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<StartStrikeTeamMeterTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSetAlertVariableTrackProperties;  // 0x112560B8

			// FUNCTION: ENGINE 0x1026E530
			bool SetAlertVariableTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E550
			bool SetAlertVariableTrack::SetVariable(int newValue)
			{
				variable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E560
			bool SetAlertVariableTrack::SetValue(float newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026F450
			fight::Property* SetAlertVariableTrack::GetProperty(int index)
			{
				return gSetAlertVariableTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1026F470
			void SetAlertVariableTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetAlertVariableTrackProperties);
			}

			// FUNCTION: ENGINE 0x1026F480
			SetAlertVariableTrack::SetAlertVariableTrack() : timeBegin(0.0f), value(0.0f), variable(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1026F4C0
			float SetAlertVariableTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F4D0
			float SetAlertVariableTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1026F4E0
			SetAlertVariableTrack::~SetAlertVariableTrack()
			{
			}

			// FUNCTION: ENGINE 0x10273AA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetAlertVariableTrack::RegisterProperties()
			{
				if (gSetAlertVariableTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetAlertVariableTrack>("timeBegin", &SetAlertVariableTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<SetAlertVariableTrack>("variable", gAlertVariableConditionVariableTable, gAlertVariableConditionVariableCount, &SetAlertVariableTrack::SetVariable);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<SetAlertVariableTrack>("value", &SetAlertVariableTrack::SetValue);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gSetAlertVariableTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102723B0
			fight::TrackFactory* CreateSetAlertVariableTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetAlertVariableTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274560
			void RegisterSetAlertVariableTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetAlertVariableTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gResetAlertVariablesTrackProperties;  // 0x112560BC

			// FUNCTION: ENGINE 0x1026E580
			bool ResetAlertVariablesTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E5A0
			bool ResetAlertVariablesTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E5C0
			bool ResetAlertVariablesTrack::SetResetJustTime(bool newValue)
			{
				resetJustTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E5D0
			bool ResetAlertVariablesTrack::SetDontResetFactionIfSniffer(bool newValue)
			{
				dontResetFactionIfSniffer = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026F4F0
			fight::Property* ResetAlertVariablesTrack::GetProperty(int index)
			{
				return gResetAlertVariablesTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1026F510
			void ResetAlertVariablesTrack::ClearProperties()
			{
				fight::FreePropertyList(&gResetAlertVariablesTrackProperties);
			}

			// FUNCTION: ENGINE 0x1026F520
			ResetAlertVariablesTrack::ResetAlertVariablesTrack() : timeBegin(0.0f), timeEnd(-1.0f), dontResetFactionIfSniffer(false), resetJustTime(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1026F570
			float ResetAlertVariablesTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F580
			float ResetAlertVariablesTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F590
			ResetAlertVariablesTrack::~ResetAlertVariablesTrack()
			{
			}

			// FUNCTION: ENGINE 0x10273BD0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ResetAlertVariablesTrack::RegisterProperties()
			{
				if (gResetAlertVariablesTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ResetAlertVariablesTrack>("timeBegin", &ResetAlertVariablesTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ResetAlertVariablesTrack>("timeEnd", &ResetAlertVariablesTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<ResetAlertVariablesTrack>("resetJustTime", &ResetAlertVariablesTrack::SetResetJustTime);
					properties[2] = property;
					property = new fight::PropertyBool<ResetAlertVariablesTrack>("dontResetFactionIfSniffer", &ResetAlertVariablesTrack::SetDontResetFactionIfSniffer);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gResetAlertVariablesTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102723E0
			fight::TrackFactory* CreateResetAlertVariablesTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ResetAlertVariablesTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274590
			void RegisterResetAlertVariablesTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ResetAlertVariablesTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gScenarioMessageTrackProperties;  // 0x112560C0

			// FUNCTION: ENGINE 0x1026E5E0
			bool ScenarioMessageTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E600
			bool ScenarioMessageTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E620
			bool ScenarioMessageTrack::SetEvent(int newValue)
			{
				event = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E630
			bool ScenarioMessageTrack::SetOnBegin(bool newValue)
			{
				onBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E640
			bool ScenarioMessageTrack::SetOnEnd(bool newValue)
			{
				onEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026F5A0
			fight::Property* ScenarioMessageTrack::GetProperty(int index)
			{
				return gScenarioMessageTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1026F5C0
			void ScenarioMessageTrack::ClearProperties()
			{
				fight::FreePropertyList(&gScenarioMessageTrackProperties);
			}

			// FUNCTION: ENGINE 0x1026F5D0
			ScenarioMessageTrack::ScenarioMessageTrack() : timeBegin(0.0f), timeEnd(-1.0f), event(0), onBegin(false), onEnd(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1026F620
			float ScenarioMessageTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F630
			float ScenarioMessageTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F640
			ScenarioMessageTrack::~ScenarioMessageTrack()
			{
			}

			// FUNCTION: ENGINE 0x10273D20
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ScenarioMessageTrack::RegisterProperties()
			{
				if (gScenarioMessageTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ScenarioMessageTrack>("timeBegin", &ScenarioMessageTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ScenarioMessageTrack>("timeEnd", &ScenarioMessageTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<ScenarioMessageTrack>("event", gScenarioMessageTrackEventTable, gScenarioMessageTrackEventCount, &ScenarioMessageTrack::SetEvent);
					properties[2] = property;
					property = new fight::PropertyBool<ScenarioMessageTrack>("onBegin", &ScenarioMessageTrack::SetOnBegin);
					properties[3] = property;
					property = new fight::PropertyBool<ScenarioMessageTrack>("onEnd", &ScenarioMessageTrack::SetOnEnd);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gScenarioMessageTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272410
			fight::TrackFactory* CreateScenarioMessageTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ScenarioMessageTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102745C0
			void RegisterScenarioMessageTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ScenarioMessageTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gStopStrikeTeamMeterTrackProperties;  // 0x112560C4

			// FUNCTION: ENGINE 0x1026E650
			bool StopStrikeTeamMeterTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026F650
			fight::Property* StopStrikeTeamMeterTrack::GetProperty(int index)
			{
				return gStopStrikeTeamMeterTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1026F670
			void StopStrikeTeamMeterTrack::ClearProperties()
			{
				fight::FreePropertyList(&gStopStrikeTeamMeterTrackProperties);
			}

			// FUNCTION: ENGINE 0x1026F680
			StopStrikeTeamMeterTrack::StopStrikeTeamMeterTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1026F6B0
			float StopStrikeTeamMeterTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F6C0
			float StopStrikeTeamMeterTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1026F6D0
			StopStrikeTeamMeterTrack::~StopStrikeTeamMeterTrack()
			{
			}

			// FUNCTION: ENGINE 0x10273ED0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void StopStrikeTeamMeterTrack::RegisterProperties()
			{
				if (gStopStrikeTeamMeterTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<StopStrikeTeamMeterTrack>("timeBegin", &StopStrikeTeamMeterTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gStopStrikeTeamMeterTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272440
			fight::TrackFactory* CreateStopStrikeTeamMeterTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<StopStrikeTeamMeterTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102745F0
			void RegisterStopStrikeTeamMeterTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<StopStrikeTeamMeterTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gHoldOnAlertEventsTrackProperties;  // 0x112560C8

			// FUNCTION: ENGINE 0x1026E670
			bool HoldOnAlertEventsTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026E690
			bool HoldOnAlertEventsTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1026F6E0
			fight::Property* HoldOnAlertEventsTrack::GetProperty(int index)
			{
				return gHoldOnAlertEventsTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1026F700
			void HoldOnAlertEventsTrack::ClearProperties()
			{
				fight::FreePropertyList(&gHoldOnAlertEventsTrackProperties);
			}

			// FUNCTION: ENGINE 0x1026F710
			HoldOnAlertEventsTrack::HoldOnAlertEventsTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1026F750
			float HoldOnAlertEventsTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1026F760
			float HoldOnAlertEventsTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1026F770
			HoldOnAlertEventsTrack::~HoldOnAlertEventsTrack()
			{
			}

			// FUNCTION: ENGINE 0x10273F70
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HoldOnAlertEventsTrack::RegisterProperties()
			{
				if (gHoldOnAlertEventsTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<HoldOnAlertEventsTrack>("timeBegin", &HoldOnAlertEventsTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HoldOnAlertEventsTrack>("timeEnd", &HoldOnAlertEventsTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gHoldOnAlertEventsTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10272470
			fight::TrackFactory* CreateHoldOnAlertEventsTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<HoldOnAlertEventsTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10274620
			void RegisterHoldOnAlertEventsTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<HoldOnAlertEventsTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyBool<InsideAlertedAreaCondition>;
			template class fight::ConditionFactoryTemplate<InsideAlertedAreaCondition>;
			template class fight::ConditionFactoryCasterTemplate<InsideAlertedAreaCondition>;
			template class fight::PropertyBool<ShouldCallStrikeTeamCondition>;
			template class fight::ConditionFactoryTemplate<ShouldCallStrikeTeamCondition>;
			template class fight::ConditionFactoryCasterTemplate<ShouldCallStrikeTeamCondition>;
			template class fight::PropertyBool<RadioedCondition>;
			template class fight::ConditionFactoryTemplate<RadioedCondition>;
			template class fight::ConditionFactoryCasterTemplate<RadioedCondition>;
			template class fight::PropertyEnumConstList<GraceSwitchDisguisesCondition>;
			template class fight::PropertyFloatConstRange<GraceSwitchDisguisesCondition>;
			template class fight::ConditionFactoryTemplate<GraceSwitchDisguisesCondition>;
			template class fight::ConditionFactoryCasterTemplate<GraceSwitchDisguisesCondition>;
			template class fight::PropertyBool<PlayerSeenCondition>;
			template class fight::PropertyEnumConstList<PlayerSeenCondition>;
			template class fight::PropertyFloatConstRange<PlayerSeenCondition>;
			template class fight::ConditionFactoryTemplate<PlayerSeenCondition>;
			template class fight::ConditionFactoryCasterTemplate<PlayerSeenCondition>;
			template class fight::PropertyEnumConstList<FriendlyFireVariableCondition>;
			template class fight::PropertyFloatConstRange<FriendlyFireVariableCondition>;
			template class fight::ConditionFactoryTemplate<FriendlyFireVariableCondition>;
			template class fight::ConditionFactoryCasterTemplate<FriendlyFireVariableCondition>;
			template class fight::PropertyEnumConstList<AlertVariableCondition>;
			template class fight::PropertyFloatConstRange<AlertVariableCondition>;
			template class fight::ConditionFactoryTemplate<AlertVariableCondition>;
			template class fight::ConditionFactoryCasterTemplate<AlertVariableCondition>;
			template class fight::ConditionFactoryTemplate<HostileWithMilitaryCondition>;
			template class fight::ConditionFactoryCasterTemplate<HostileWithMilitaryCondition>;
			template class fight::PropertyBool<InsideAlertCircleCondition>;
			template class fight::ConditionFactoryTemplate<InsideAlertCircleCondition>;
			template class fight::ConditionFactoryCasterTemplate<InsideAlertCircleCondition>;
			template class fight::PropertyEnumConstList<PursuitGuysCondition>;
			template class fight::PropertyIntConstRange<PursuitGuysCondition>;
			template class fight::ConditionFactoryTemplate<PursuitGuysCondition>;
			template class fight::ConditionFactoryCasterTemplate<PursuitGuysCondition>;
			template class fight::PropertyBool<AllyWithMilitaryCondition>;
			template class fight::ConditionFactoryTemplate<AllyWithMilitaryCondition>;
			template class fight::ConditionFactoryCasterTemplate<AllyWithMilitaryCondition>;
			template class fight::PropertyEnumConstList<AlertVariableIncreasedSinceCondition>;
			template class fight::PropertyFloatConstRange<AlertVariableIncreasedSinceCondition>;
			template class fight::ConditionFactoryTemplate<AlertVariableIncreasedSinceCondition>;
			template class fight::ConditionFactoryCasterTemplate<AlertVariableIncreasedSinceCondition>;
			template class fight::PropertyEnumConstList<BeginCombatGuysCondition>;
			template class fight::PropertyIntConstRange<BeginCombatGuysCondition>;
			template class fight::ConditionFactoryTemplate<BeginCombatGuysCondition>;
			template class fight::ConditionFactoryCasterTemplate<BeginCombatGuysCondition>;
			template class fight::PropertyBool<ValidMilitaryDisguiseCondition>;
			template class fight::ConditionFactoryTemplate<ValidMilitaryDisguiseCondition>;
			template class fight::ConditionFactoryCasterTemplate<ValidMilitaryDisguiseCondition>;
			template class fight::PropertyBool<SeenCondition>;
			template class fight::PropertyEnumConstList<SeenCondition>;
			template class fight::PropertyFloatConstRange<SeenCondition>;
			template class fight::ConditionFactoryTemplate<SeenCondition>;
			template class fight::ConditionFactoryCasterTemplate<SeenCondition>;
			template class fight::PropertyEnumConstList<PursuitTimeCondition>;
			template class fight::PropertyFloatConstRange<PursuitTimeCondition>;
			template class fight::ConditionFactoryTemplate<PursuitTimeCondition>;
			template class fight::ConditionFactoryCasterTemplate<PursuitTimeCondition>;
			template class fight::PropertyEnumConstList<AlertCircleDistanceCondition>;
			template class fight::PropertyFloatConstRange<AlertCircleDistanceCondition>;
			template class fight::ConditionFactoryTemplate<AlertCircleDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<AlertCircleDistanceCondition>;
			template class fight::ConditionFactoryTemplate<MilitaryDisguiseCondition>;
			template class fight::ConditionFactoryCasterTemplate<MilitaryDisguiseCondition>;
			template class fight::PropertyFloatConstRange<ReportBackToIdleTrack>;
			template class fight::PropertyBool<ReportBackToIdleTrack>;
			template class fight::TrackFactoryTemplate<ReportBackToIdleTrack>;
			template class fight::TrackFactoryCasterTemplate<ReportBackToIdleTrack>;
			template class fight::PropertyFloatConstRange<ReportEnterBeginCombatTrack>;
			template class fight::TrackFactoryTemplate<ReportEnterBeginCombatTrack>;
			template class fight::TrackFactoryCasterTemplate<ReportEnterBeginCombatTrack>;
			template class fight::PropertyFloatConstRange<RadioedSetTrack>;
			template class fight::PropertyBool<RadioedSetTrack>;
			template class fight::TrackFactoryTemplate<RadioedSetTrack>;
			template class fight::TrackFactoryCasterTemplate<RadioedSetTrack>;
			template class fight::PropertyFloatConstRange<DisablePoliceTrack>;
			template class fight::PropertyBool<DisablePoliceTrack>;
			template class fight::TrackFactoryTemplate<DisablePoliceTrack>;
			template class fight::TrackFactoryCasterTemplate<DisablePoliceTrack>;
			template class fight::PropertyFloatConstRange<AlertReportTrack>;
			template class fight::TrackFactoryTemplate<AlertReportTrack>;
			template class fight::TrackFactoryCasterTemplate<AlertReportTrack>;
			template class fight::PropertyFloatConstRange<CallStrikeTeamTrack>;
			template class fight::TrackFactoryTemplate<CallStrikeTeamTrack>;
			template class fight::TrackFactoryCasterTemplate<CallStrikeTeamTrack>;
			template class fight::PropertyFloatConstRange<PlayerCallStrikeTeamTrack>;
			template class fight::TrackFactoryTemplate<PlayerCallStrikeTeamTrack>;
			template class fight::TrackFactoryCasterTemplate<PlayerCallStrikeTeamTrack>;
			template class fight::PropertyFloatConstRange<SetInPursuitTrack>;
			template class fight::PropertyBool<SetInPursuitTrack>;
			template class fight::TrackFactoryTemplate<SetInPursuitTrack>;
			template class fight::TrackFactoryCasterTemplate<SetInPursuitTrack>;
			template class fight::PropertyFloatConstRange<StartStrikeTeamMeterTrack>;
			template class fight::TrackFactoryTemplate<StartStrikeTeamMeterTrack>;
			template class fight::TrackFactoryCasterTemplate<StartStrikeTeamMeterTrack>;
			template class fight::PropertyFloatConstRange<SetAlertVariableTrack>;
			template class fight::PropertyEnumConstList<SetAlertVariableTrack>;
			template class fight::TrackFactoryTemplate<SetAlertVariableTrack>;
			template class fight::TrackFactoryCasterTemplate<SetAlertVariableTrack>;
			template class fight::PropertyFloatConstRange<ResetAlertVariablesTrack>;
			template class fight::PropertyBool<ResetAlertVariablesTrack>;
			template class fight::TrackFactoryTemplate<ResetAlertVariablesTrack>;
			template class fight::TrackFactoryCasterTemplate<ResetAlertVariablesTrack>;
			template class fight::PropertyFloatConstRange<ScenarioMessageTrack>;
			template class fight::PropertyEnumConstList<ScenarioMessageTrack>;
			template class fight::PropertyBool<ScenarioMessageTrack>;
			template class fight::TrackFactoryTemplate<ScenarioMessageTrack>;
			template class fight::TrackFactoryCasterTemplate<ScenarioMessageTrack>;
			template class fight::PropertyFloatConstRange<StopStrikeTeamMeterTrack>;
			template class fight::TrackFactoryTemplate<StopStrikeTeamMeterTrack>;
			template class fight::TrackFactoryCasterTemplate<StopStrikeTeamMeterTrack>;
			template class fight::PropertyFloatConstRange<HoldOnAlertEventsTrack>;
			template class fight::TrackFactoryTemplate<HoldOnAlertEventsTrack>;
			template class fight::TrackFactoryCasterTemplate<HoldOnAlertEventsTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1026F780
// FUNCTION: ENGINE 0x1026F7B0
// FUNCTION: ENGINE 0x1026F7E0
// FUNCTION: ENGINE 0x1026F810
// FUNCTION: ENGINE 0x1026F840
// FUNCTION: ENGINE 0x1026F870
// FUNCTION: ENGINE 0x1026F8A0
// FUNCTION: ENGINE 0x1026F8D0
// FUNCTION: ENGINE 0x1026F900
// FUNCTION: ENGINE 0x1026F930
// FUNCTION: ENGINE 0x1026F960
// FUNCTION: ENGINE 0x1026F990
// FUNCTION: ENGINE 0x1026F9C0
// FUNCTION: ENGINE 0x1026F9F0
// FUNCTION: ENGINE 0x1026FA20
// FUNCTION: ENGINE 0x1026FA50
// FUNCTION: ENGINE 0x1026FA80
// FUNCTION: ENGINE 0x1026FAB0
// FUNCTION: ENGINE 0x1026FAE0
// FUNCTION: ENGINE 0x1026FB10
// FUNCTION: ENGINE 0x1026FB40
// FUNCTION: ENGINE 0x1026FB70
// FUNCTION: ENGINE 0x1026FBA0
// FUNCTION: ENGINE 0x1026FBD0
// FUNCTION: ENGINE 0x1026FC00
// FUNCTION: ENGINE 0x1026FC30
// FUNCTION: ENGINE 0x1026FC60
// FUNCTION: ENGINE 0x1026FC90
// FUNCTION: ENGINE 0x1026FCC0
// FUNCTION: ENGINE 0x1026FCF0
// FUNCTION: ENGINE 0x1026FD20
// FUNCTION: ENGINE 0x1026FD50
// FUNCTION: ENGINE 0x1026FD80
// FUNCTION: ENGINE 0x1026FD90
// FUNCTION: ENGINE 0x1026FDC0
// FUNCTION: ENGINE 0x1026FDD0
// FUNCTION: ENGINE 0x1026FE00
// FUNCTION: ENGINE 0x1026FE10
// FUNCTION: ENGINE 0x1026FE40
// FUNCTION: ENGINE 0x1026FE50
// FUNCTION: ENGINE 0x1026FE80
// FUNCTION: ENGINE 0x1026FE90
// FUNCTION: ENGINE 0x1026FEC0
// FUNCTION: ENGINE 0x1026FED0
// FUNCTION: ENGINE 0x1026FF00
// FUNCTION: ENGINE 0x1026FF10
// FUNCTION: ENGINE 0x1026FF40
// FUNCTION: ENGINE 0x1026FF50
// FUNCTION: ENGINE 0x1026FF80
// FUNCTION: ENGINE 0x1026FFB0
// FUNCTION: ENGINE 0x1026FFD0
// FUNCTION: ENGINE 0x10270020
// FUNCTION: ENGINE 0x10270030
// FUNCTION: ENGINE 0x10270060
// FUNCTION: ENGINE 0x10270070
// FUNCTION: ENGINE 0x102700A0
// FUNCTION: ENGINE 0x102700B0
// FUNCTION: ENGINE 0x102700E0
// FUNCTION: ENGINE 0x102700F0
// FUNCTION: ENGINE 0x10270120
// FUNCTION: ENGINE 0x10270130
// FUNCTION: ENGINE 0x10270160
// FUNCTION: ENGINE 0x10270170
// FUNCTION: ENGINE 0x102701A0
// FUNCTION: ENGINE 0x102701B0
// FUNCTION: ENGINE 0x102701E0
// FUNCTION: ENGINE 0x102701F0
// FUNCTION: ENGINE 0x10270220
// FUNCTION: ENGINE 0x10270230
// FUNCTION: ENGINE 0x10270260
// FUNCTION: ENGINE 0x10270270
// FUNCTION: ENGINE 0x102702A0
// FUNCTION: ENGINE 0x102702D0
// FUNCTION: ENGINE 0x102702F0
// FUNCTION: ENGINE 0x10270340
// FUNCTION: ENGINE 0x10270350
// FUNCTION: ENGINE 0x10270380
// FUNCTION: ENGINE 0x10270390
// FUNCTION: ENGINE 0x102703C0
// FUNCTION: ENGINE 0x102703D0
// FUNCTION: ENGINE 0x10270400
// FUNCTION: ENGINE 0x10270410
// FUNCTION: ENGINE 0x10270440
// FUNCTION: ENGINE 0x10270450
// FUNCTION: ENGINE 0x10270480
// FUNCTION: ENGINE 0x10270490
// FUNCTION: ENGINE 0x102704C0
// FUNCTION: ENGINE 0x102704D0
// FUNCTION: ENGINE 0x10270500
// FUNCTION: ENGINE 0x10270510
// FUNCTION: ENGINE 0x10270540
// FUNCTION: ENGINE 0x10270550
// FUNCTION: ENGINE 0x10270580
// FUNCTION: ENGINE 0x10270590
// FUNCTION: ENGINE 0x102705C0
// FUNCTION: ENGINE 0x102705D0
// FUNCTION: ENGINE 0x10270600
// FUNCTION: ENGINE 0x10270610
// FUNCTION: ENGINE 0x10270640
// FUNCTION: ENGINE 0x10270650
// FUNCTION: ENGINE 0x10270680
// FUNCTION: ENGINE 0x10270690
// FUNCTION: ENGINE 0x102706C0
// FUNCTION: ENGINE 0x102706F0
// FUNCTION: ENGINE 0x10270710
// FUNCTION: ENGINE 0x10270720
// FUNCTION: ENGINE 0x10270750
// FUNCTION: ENGINE 0x10270770
// FUNCTION: ENGINE 0x10270780
// FUNCTION: ENGINE 0x102707B0
// FUNCTION: ENGINE 0x102707D0
// FUNCTION: ENGINE 0x102707E0
// FUNCTION: ENGINE 0x10270820
// FUNCTION: ENGINE 0x10270830
// FUNCTION: ENGINE 0x10270860
// FUNCTION: ENGINE 0x10270880
// FUNCTION: ENGINE 0x10270890
// FUNCTION: ENGINE 0x102708C0
// FUNCTION: ENGINE 0x102708F0
// FUNCTION: ENGINE 0x10270900
// FUNCTION: ENGINE 0x10270930
// FUNCTION: ENGINE 0x10270950
// FUNCTION: ENGINE 0x10270960
// FUNCTION: ENGINE 0x102709A0
// FUNCTION: ENGINE 0x102709B0
// FUNCTION: ENGINE 0x102709E0
// FUNCTION: ENGINE 0x10270A00
// FUNCTION: ENGINE 0x10270A10
// FUNCTION: ENGINE 0x10270A40
// FUNCTION: ENGINE 0x10270A70
// FUNCTION: ENGINE 0x10270A80
// FUNCTION: ENGINE 0x10270AC0
// FUNCTION: ENGINE 0x10270AD0
// FUNCTION: ENGINE 0x10270B00
// FUNCTION: ENGINE 0x10270B20
// FUNCTION: ENGINE 0x10270B30
// FUNCTION: ENGINE 0x10270B60
// FUNCTION: ENGINE 0x10270B90
// FUNCTION: ENGINE 0x10270BA0
// FUNCTION: ENGINE 0x10270BE0
// FUNCTION: ENGINE 0x10270BF0
// FUNCTION: ENGINE 0x10270C20
// FUNCTION: ENGINE 0x10270C40
// FUNCTION: ENGINE 0x10270C50
// FUNCTION: ENGINE 0x10270C80
// FUNCTION: ENGINE 0x10270CB0
// FUNCTION: ENGINE 0x10270CC0
// FUNCTION: ENGINE 0x10270CF0
// FUNCTION: ENGINE 0x10270D10
// FUNCTION: ENGINE 0x10270D20
// FUNCTION: ENGINE 0x10270D60
// FUNCTION: ENGINE 0x10270D70
// FUNCTION: ENGINE 0x10270DA0
// FUNCTION: ENGINE 0x10270DC0
// FUNCTION: ENGINE 0x10270DD0
// FUNCTION: ENGINE 0x10270E00
// FUNCTION: ENGINE 0x10270E20
// FUNCTION: ENGINE 0x10270E30
// FUNCTION: ENGINE 0x10270E60
// FUNCTION: ENGINE 0x10270E80
// FUNCTION: ENGINE 0x10270E90
// FUNCTION: ENGINE 0x10270ED0
// FUNCTION: ENGINE 0x10270EE0
// FUNCTION: ENGINE 0x10270F10
// FUNCTION: ENGINE 0x10270F30
// FUNCTION: ENGINE 0x10270F40
// FUNCTION: ENGINE 0x10270F70
// FUNCTION: ENGINE 0x10270FA0
// FUNCTION: ENGINE 0x10270FB0
// FUNCTION: ENGINE 0x10270FF0
// FUNCTION: ENGINE 0x10271000
// FUNCTION: ENGINE 0x10271030
// FUNCTION: ENGINE 0x10271050
// FUNCTION: ENGINE 0x10271060
// FUNCTION: ENGINE 0x10271090
// FUNCTION: ENGINE 0x102710B0
// FUNCTION: ENGINE 0x102710C0
// FUNCTION: ENGINE 0x102710F0
// FUNCTION: ENGINE 0x10271110
// FUNCTION: ENGINE 0x10271120
// FUNCTION: ENGINE 0x10271150
// FUNCTION: ENGINE 0x10271170
// FUNCTION: ENGINE 0x10271180
// FUNCTION: ENGINE 0x102711C0
// FUNCTION: ENGINE 0x102711D0
// FUNCTION: ENGINE 0x10271200
// FUNCTION: ENGINE 0x10271220
// FUNCTION: ENGINE 0x10271230
// FUNCTION: ENGINE 0x10271260
// FUNCTION: ENGINE 0x10271290
// FUNCTION: ENGINE 0x102712A0
// FUNCTION: ENGINE 0x102712E0
// FUNCTION: ENGINE 0x102712F0
// FUNCTION: ENGINE 0x10271320
// FUNCTION: ENGINE 0x10271340
// FUNCTION: ENGINE 0x10271350
// FUNCTION: ENGINE 0x10271380
// FUNCTION: ENGINE 0x102713B0
// FUNCTION: ENGINE 0x102713C0
// FUNCTION: ENGINE 0x10271400
// FUNCTION: ENGINE 0x10271410
// FUNCTION: ENGINE 0x10271440
// FUNCTION: ENGINE 0x10271460
// FUNCTION: ENGINE 0x10271470
// FUNCTION: ENGINE 0x102714A0
// FUNCTION: ENGINE 0x102714D0
// FUNCTION: ENGINE 0x102714E0
// FUNCTION: ENGINE 0x10271510
// FUNCTION: ENGINE 0x10271540
// FUNCTION: ENGINE 0x10271550
// FUNCTION: ENGINE 0x10271580
// FUNCTION: ENGINE 0x102715A0
// FUNCTION: ENGINE 0x102715B0
// FUNCTION: ENGINE 0x102715E0
// FUNCTION: ENGINE 0x10271610
// FUNCTION: ENGINE 0x10271620
// FUNCTION: ENGINE 0x10271650
// FUNCTION: ENGINE 0x10271680
// FUNCTION: ENGINE 0x10271690
// FUNCTION: ENGINE 0x102716C0
// FUNCTION: ENGINE 0x102716E0
// FUNCTION: ENGINE 0x102716F0
// FUNCTION: ENGINE 0x10271720
// FUNCTION: ENGINE 0x10271750
// FUNCTION: ENGINE 0x10271760
// FUNCTION: ENGINE 0x10271790
// FUNCTION: ENGINE 0x102717B0
// FUNCTION: ENGINE 0x102717C0
// FUNCTION: ENGINE 0x102717F0
// FUNCTION: ENGINE 0x10271820
// FUNCTION: ENGINE 0x10271830
// FUNCTION: ENGINE 0x10271860
// FUNCTION: ENGINE 0x10271890
// FUNCTION: ENGINE 0x102718A0
// FUNCTION: ENGINE 0x102718D0
// FUNCTION: ENGINE 0x10271900
// FUNCTION: ENGINE 0x10271910
// FUNCTION: ENGINE 0x10271940
// FUNCTION: ENGINE 0x10271970
// FUNCTION: ENGINE 0x10271980
// FUNCTION: ENGINE 0x102719B0
// FUNCTION: ENGINE 0x102719D0
// FUNCTION: ENGINE 0x102719E0
// FUNCTION: ENGINE 0x10271A10
// FUNCTION: ENGINE 0x10271A40
// FUNCTION: ENGINE 0x10271A50
// FUNCTION: ENGINE 0x10271A80
// FUNCTION: ENGINE 0x10271AB0
// FUNCTION: ENGINE 0x10271AC0
// FUNCTION: ENGINE 0x10271B00
// FUNCTION: ENGINE 0x10271B10
// FUNCTION: ENGINE 0x10271B40
// FUNCTION: ENGINE 0x10271B60
// FUNCTION: ENGINE 0x10271B70
// FUNCTION: ENGINE 0x10271BA0
// FUNCTION: ENGINE 0x10271BD0
// FUNCTION: ENGINE 0x10271BE0
// FUNCTION: ENGINE 0x10271C10
// FUNCTION: ENGINE 0x10271C30
// FUNCTION: ENGINE 0x10271C40
// FUNCTION: ENGINE 0x10271C70
// FUNCTION: ENGINE 0x10271CA0
// FUNCTION: ENGINE 0x10271CB0
// FUNCTION: ENGINE 0x10271CF0
// FUNCTION: ENGINE 0x10271D00
// FUNCTION: ENGINE 0x10271D30
// FUNCTION: ENGINE 0x10271D50
// FUNCTION: ENGINE 0x10271D60
// FUNCTION: ENGINE 0x10271D90
// FUNCTION: ENGINE 0x10271DB0
// FUNCTION: ENGINE 0x10271DC0
// FUNCTION: ENGINE 0x10271DF0
// FUNCTION: ENGINE 0x10271E20
// FUNCTION: ENGINE 0x10271E30
// FUNCTION: ENGINE 0x10271E60
// FUNCTION: ENGINE 0x10271E90
// FUNCTION: ENGINE 0x10274650
// FUNCTION: ENGINE 0x10274680
// FUNCTION: ENGINE 0x102746A0
// FUNCTION: ENGINE 0x102746D0
// FUNCTION: ENGINE 0x102746F0
// FUNCTION: ENGINE 0x10274720
// FUNCTION: ENGINE 0x10274740
// FUNCTION: ENGINE 0x10274770
// FUNCTION: ENGINE 0x10274790
// FUNCTION: ENGINE 0x102747C0
// FUNCTION: ENGINE 0x102747E0
// FUNCTION: ENGINE 0x10274810
// FUNCTION: ENGINE 0x10274830
// FUNCTION: ENGINE 0x10274860
// FUNCTION: ENGINE 0x10274880
// FUNCTION: ENGINE 0x102748B0
// FUNCTION: ENGINE 0x102748D0
// FUNCTION: ENGINE 0x10274900
// FUNCTION: ENGINE 0x10274920
// FUNCTION: ENGINE 0x10274950
// FUNCTION: ENGINE 0x10274970
// FUNCTION: ENGINE 0x102749A0
// FUNCTION: ENGINE 0x102749C0
// FUNCTION: ENGINE 0x102749F0
// FUNCTION: ENGINE 0x10274A10
// FUNCTION: ENGINE 0x10274A40
// FUNCTION: ENGINE 0x10274A60
// FUNCTION: ENGINE 0x10274A90
// FUNCTION: ENGINE 0x10274AB0
// FUNCTION: ENGINE 0x10274AE0
// FUNCTION: ENGINE 0x10274B00
// FUNCTION: ENGINE 0x10274B30
// FUNCTION: ENGINE 0x10274B50
// FUNCTION: ENGINE 0x10274B80
// FUNCTION: ENGINE 0x10274BA0
// FUNCTION: ENGINE 0x10274BD0
// FUNCTION: ENGINE 0x10274BF0
// FUNCTION: ENGINE 0x10274C20
// FUNCTION: ENGINE 0x10274C40
// FUNCTION: ENGINE 0x10274C70
// FUNCTION: ENGINE 0x10274C90
// FUNCTION: ENGINE 0x10274CC0
// FUNCTION: ENGINE 0x10274CE0
// FUNCTION: ENGINE 0x10274D10
// FUNCTION: ENGINE 0x10274D30
// FUNCTION: ENGINE 0x10274D60
// FUNCTION: ENGINE 0x10274D80
// FUNCTION: ENGINE 0x10274DB0
// FUNCTION: ENGINE 0x10274DD0
// FUNCTION: ENGINE 0x10274E00
// FUNCTION: ENGINE 0x10274E20
// FUNCTION: ENGINE 0x10274E50
// FUNCTION: ENGINE 0x10274E70
// FUNCTION: ENGINE 0x10274EA0
// FUNCTION: ENGINE 0x10274EC0
// FUNCTION: ENGINE 0x10274EF0
// FUNCTION: ENGINE 0x10274F10
// FUNCTION: ENGINE 0x10274F40
// FUNCTION: ENGINE 0x10274F60
// FUNCTION: ENGINE 0x10274F90
// FUNCTION: ENGINE 0x10274FB0
// FUNCTION: ENGINE 0x10275000
// FUNCTION: ENGINE 0x10275050
// FUNCTION: ENGINE 0x102750A0
// FUNCTION: ENGINE 0x102750F0
// FUNCTION: ENGINE 0x10275140
// FUNCTION: ENGINE 0x10275190
// FUNCTION: ENGINE 0x102751E0
// FUNCTION: ENGINE 0x10275230
// FUNCTION: ENGINE 0x10275280
// FUNCTION: ENGINE 0x102752D0
// FUNCTION: ENGINE 0x10275320
// FUNCTION: ENGINE 0x10275370
// FUNCTION: ENGINE 0x102753C0
// FUNCTION: ENGINE 0x10275410
// FUNCTION: ENGINE 0x10275460
// FUNCTION: ENGINE 0x102754B0
// FUNCTION: ENGINE 0x10275500
// FUNCTION: ENGINE 0x10275550
// FUNCTION: ENGINE 0x102755A0
// FUNCTION: ENGINE 0x102755F0
// FUNCTION: ENGINE 0x10275640
// FUNCTION: ENGINE 0x10275690
// FUNCTION: ENGINE 0x102756E0
// FUNCTION: ENGINE 0x10275730
// FUNCTION: ENGINE 0x10275780
// FUNCTION: ENGINE 0x102757D0
// FUNCTION: ENGINE 0x10275820
// FUNCTION: ENGINE 0x10275870
// FUNCTION: ENGINE 0x102758C0
