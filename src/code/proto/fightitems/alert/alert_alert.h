// Fight items of the alert group: InsideAlertedAreaCondition, ShouldCallStrikeTeamCondition, RadioedCondition, GraceSwitchDisguisesCondition, PlayerSeenCondition, FriendlyFireVariableCondition, AlertVariableCondition, HostileWithMilitaryCondition, InsideAlertCircleCondition, PursuitGuysCondition, AllyWithMilitaryCondition, AlertVariableIncreasedSinceCondition, BeginCombatGuysCondition, ValidMilitaryDisguiseCondition, SeenCondition, PursuitTimeCondition, AlertCircleDistanceCondition, MilitaryDisguiseCondition, ReportBackToIdleTrack, ReportEnterBeginCombatTrack, RadioedSetTrack, DisablePoliceTrack, AlertReportTrack, CallStrikeTeamTrack, PlayerCallStrikeTeamTrack, SetInPursuitTrack, StartStrikeTeamMeterTrack, SetAlertVariableTrack, ResetAlertVariablesTrack, ScenarioMessageTrack, StopStrikeTeamMeterTrack, HoldOnAlertEventsTrack (unit 0x1026E0E0 - 0x10275910; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_ALERT_ALERT_ALERT_H
#define PROTO_FIGHTITEMS_ALERT_ALERT_ALERT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/alert/alertdata.h"

namespace proto
{
	namespace fightitems
	{
		namespace alert
		{
			// RTTI: proto::fightitems::alert::InsideAlertedAreaCondition (10 vftable slots, 0x10 bytes)
			class InsideAlertedAreaCondition : public fight::Condition
			{
			public:
				// 0x1026E6E0
				InsideAlertedAreaCondition();
				virtual ~InsideAlertedAreaCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026B550, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetInside(bool newValue);
				bool SetPlayerOnly(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool inside;  // +0xC
					bool playerOnly;  // +0xD
					unsigned char unknownE[0x2];
			};

			extern fight::Property** gInsideAlertedAreaConditionProperties;
			fight::ConditionFactory* CreateInsideAlertedAreaConditionFactory(const char* name);
			void RegisterInsideAlertedAreaConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::ShouldCallStrikeTeamCondition (10 vftable slots, 0x10 bytes)
			class ShouldCallStrikeTeamCondition : public fight::Condition
			{
			public:
				// 0x1026E750
				ShouldCallStrikeTeamCondition();
				virtual ~ShouldCallStrikeTeamCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026B620, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetShould(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool should;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gShouldCallStrikeTeamConditionProperties;
			fight::ConditionFactory* CreateShouldCallStrikeTeamConditionFactory(const char* name);
			void RegisterShouldCallStrikeTeamConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::RadioedCondition (10 vftable slots, 0x10 bytes)
			class RadioedCondition : public fight::Condition
			{
			public:
				// 0x1026E7B0
				RadioedCondition();
				virtual ~RadioedCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026B4A0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetRadioed(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool radioed;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gRadioedConditionProperties;
			fight::ConditionFactory* CreateRadioedConditionFactory(const char* name);
			void RegisterRadioedConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::GraceSwitchDisguisesCondition (10 vftable slots, 0x14 bytes)
			class GraceSwitchDisguisesCondition : public fight::Condition
			{
			public:
				// 0x1026E810
				GraceSwitchDisguisesCondition();
				virtual ~GraceSwitchDisguisesCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026AEA0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSince(int newValue);
				bool SetTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float time;  // +0xC
					int since;  // +0x10
			};

			extern fight::Property** gGraceSwitchDisguisesConditionProperties;
			fight::ConditionFactory* CreateGraceSwitchDisguisesConditionFactory(const char* name);
			void RegisterGraceSwitchDisguisesConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::PlayerSeenCondition (10 vftable slots, 0x18 bytes)
			class PlayerSeenCondition : public fight::Condition
			{
			public:
				// 0x1026E880
				PlayerSeenCondition();
				virtual ~PlayerSeenCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026AD10, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSeen(bool newValue);
				bool SetSince(int newValue);
				bool SetTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float time;  // +0xC
					int since;  // +0x10
					bool seen;  // +0x14
					unsigned char unknown15[0x3];
			};

			extern fight::Property** gPlayerSeenConditionProperties;
			fight::ConditionFactory* CreatePlayerSeenConditionFactory(const char* name);
			void RegisterPlayerSeenConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::FriendlyFireVariableCondition (10 vftable slots, 0x14 bytes)
			class FriendlyFireVariableCondition : public fight::Condition
			{
			public:
				// 0x1026E8F0
				FriendlyFireVariableCondition();
				virtual ~FriendlyFireVariableCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026A940, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetValue(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float value;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gFriendlyFireVariableConditionProperties;
			fight::ConditionFactory* CreateFriendlyFireVariableConditionFactory(const char* name);
			void RegisterFriendlyFireVariableConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::AlertVariableCondition (10 vftable slots, 0x18 bytes)
			class AlertVariableCondition : public fight::Condition
			{
			public:
				// 0x1026E960
				AlertVariableCondition();
				virtual ~AlertVariableCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026A850, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetVariable(int newValue);
				bool SetCompare(int newValue);
				bool SetValue(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float value;  // +0xC
					int compare;  // +0x10
					int variable;  // +0x14
			};

			extern fight::Property** gAlertVariableConditionProperties;
			fight::ConditionFactory* CreateAlertVariableConditionFactory(const char* name);
			void RegisterAlertVariableConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::HostileWithMilitaryCondition (10 vftable slots, 0xC bytes)
			class HostileWithMilitaryCondition : public fight::Condition
			{
			public:
				// 0x1026EA40
				HostileWithMilitaryCondition();
				virtual ~HostileWithMilitaryCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026B400, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gHostileWithMilitaryConditionProperties;
			fight::ConditionFactory* CreateHostileWithMilitaryConditionFactory(const char* name);
			void RegisterHostileWithMilitaryConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::InsideAlertCircleCondition (10 vftable slots, 0x10 bytes)
			class InsideAlertCircleCondition : public fight::Condition
			{
			public:
				// 0x1026EAA0
				InsideAlertCircleCondition();
				virtual ~InsideAlertCircleCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026B290, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetInside(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool inside;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gInsideAlertCircleConditionProperties;
			fight::ConditionFactory* CreateInsideAlertCircleConditionFactory(const char* name);
			void RegisterInsideAlertCircleConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::PursuitGuysCondition (10 vftable slots, 0x14 bytes)
			class PursuitGuysCondition : public fight::Condition
			{
			public:
				// 0x1026EB00
				PursuitGuysCondition();
				virtual ~PursuitGuysCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026B040, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetGuys(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int compare;  // +0xC
					int guys;  // +0x10
			};

			extern fight::Property** gPursuitGuysConditionProperties;
			fight::ConditionFactory* CreatePursuitGuysConditionFactory(const char* name);
			void RegisterPursuitGuysConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::AllyWithMilitaryCondition (10 vftable slots, 0x10 bytes)
			class AllyWithMilitaryCondition : public fight::Condition
			{
			public:
				// 0x1026EB70
				AllyWithMilitaryCondition();
				virtual ~AllyWithMilitaryCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026B350, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetAlly(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool ally;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gAllyWithMilitaryConditionProperties;
			fight::ConditionFactory* CreateAllyWithMilitaryConditionFactory(const char* name);
			void RegisterAllyWithMilitaryConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::AlertVariableIncreasedSinceCondition (10 vftable slots, 0x18 bytes)
			class AlertVariableIncreasedSinceCondition : public fight::Condition
			{
			public:
				// 0x1026EBD0
				AlertVariableIncreasedSinceCondition();
				virtual ~AlertVariableIncreasedSinceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026AAA0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetVariable(int newValue);
				bool SetCompare(int newValue);
				bool SetValue(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float value;  // +0xC
					int compare;  // +0x10
					int variable;  // +0x14
			};

			extern fight::Property** gAlertVariableIncreasedSinceConditionProperties;
			fight::ConditionFactory* CreateAlertVariableIncreasedSinceConditionFactory(const char* name);
			void RegisterAlertVariableIncreasedSinceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::BeginCombatGuysCondition (10 vftable slots, 0x14 bytes)
			class BeginCombatGuysCondition : public fight::Condition
			{
			public:
				// 0x1026EC50
				BeginCombatGuysCondition();
				virtual ~BeginCombatGuysCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026B100, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetGuys(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int compare;  // +0xC
					int guys;  // +0x10
			};

			extern fight::Property** gBeginCombatGuysConditionProperties;
			fight::ConditionFactory* CreateBeginCombatGuysConditionFactory(const char* name);
			void RegisterBeginCombatGuysConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::ValidMilitaryDisguiseCondition (10 vftable slots, 0x10 bytes)
			class ValidMilitaryDisguiseCondition : public fight::Condition
			{
			public:
				// 0x1026ECC0
				ValidMilitaryDisguiseCondition();
				virtual ~ValidMilitaryDisguiseCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026B6F0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetValid(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool valid;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gValidMilitaryDisguiseConditionProperties;
			fight::ConditionFactory* CreateValidMilitaryDisguiseConditionFactory(const char* name);
			void RegisterValidMilitaryDisguiseConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::SeenCondition (10 vftable slots, 0x18 bytes)
			class SeenCondition : public fight::Condition
			{
			public:
				// 0x1026ED20
				SeenCondition();
				virtual ~SeenCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026AB90, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSeen(bool newValue);
				bool SetSince(int newValue);
				bool SetTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float time;  // +0xC
					int since;  // +0x10
					bool seen;  // +0x14
					unsigned char unknown15[0x3];
			};

			extern fight::Property** gSeenConditionProperties;
			fight::ConditionFactory* CreateSeenConditionFactory(const char* name);
			void RegisterSeenConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::PursuitTimeCondition (10 vftable slots, 0x14 bytes)
			class PursuitTimeCondition : public fight::Condition
			{
			public:
				// 0x1026ED90
				PursuitTimeCondition();
				virtual ~PursuitTimeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026AF70, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSince(int newValue);
				bool SetTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float time;  // +0xC
					int since;  // +0x10
			};

			extern fight::Property** gPursuitTimeConditionProperties;
			fight::ConditionFactory* CreatePursuitTimeConditionFactory(const char* name);
			void RegisterPursuitTimeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::AlertCircleDistanceCondition (10 vftable slots, 0x14 bytes)
			class AlertCircleDistanceCondition : public fight::Condition
			{
			public:
				// 0x1026EE00
				AlertCircleDistanceCondition();
				virtual ~AlertCircleDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026B1C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distance;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gAlertCircleDistanceConditionProperties;
			fight::ConditionFactory* CreateAlertCircleDistanceConditionFactory(const char* name);
			void RegisterAlertCircleDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::MilitaryDisguiseCondition (10 vftable slots, 0xC bytes)
			class MilitaryDisguiseCondition : public fight::Condition
			{
			public:
				// 0x1026EEE0
				MilitaryDisguiseCondition();
				virtual ~MilitaryDisguiseCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026B760, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gMilitaryDisguiseConditionProperties;
			fight::ConditionFactory* CreateMilitaryDisguiseConditionFactory(const char* name);
			void RegisterMilitaryDisguiseConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::ReportBackToIdleTrack (16 vftable slots, 0x18 bytes)
			class ReportBackToIdleTrack : public fight::Track
			{
			public:
				// 0x1026EF40
				ReportBackToIdleTrack();
				virtual ~ReportBackToIdleTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1026D300, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetEvade(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					bool evade;  // +0x14
					unsigned char unknown15[0x3];
			};

			extern fight::Property** gReportBackToIdleTrackProperties;
			fight::TrackFactory* CreateReportBackToIdleTrackFactory(const char* name);
			void RegisterReportBackToIdleTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::ReportEnterBeginCombatTrack (16 vftable slots, 0x14 bytes)
			class ReportEnterBeginCombatTrack : public fight::Track
			{
			public:
				// 0x1026EFD0
				ReportEnterBeginCombatTrack();
				virtual ~ReportEnterBeginCombatTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1026D350, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gReportEnterBeginCombatTrackProperties;
			fight::TrackFactory* CreateReportEnterBeginCombatTrackFactory(const char* name);
			void RegisterReportEnterBeginCombatTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::RadioedSetTrack (16 vftable slots, 0x18 bytes)
			class RadioedSetTrack : public fight::Track
			{
			public:
				// 0x1026F060
				RadioedSetTrack();
				virtual ~RadioedSetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1026D170, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetRadioed(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					bool radioed;  // +0x14
					unsigned char unknown15[0x3];
			};

			extern fight::Property** gRadioedSetTrackProperties;
			fight::TrackFactory* CreateRadioedSetTrackFactory(const char* name);
			void RegisterRadioedSetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::DisablePoliceTrack (16 vftable slots, 0x1C bytes)
			class DisablePoliceTrack : public fight::Track
			{
			public:
				// 0x1026F0F0
				DisablePoliceTrack();
				virtual ~DisablePoliceTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1026D2B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetDisable(bool newValue);
				bool SetDelay(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float delay;  // +0x10
					float timeBegin;  // +0x14
					bool disable;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gDisablePoliceTrackProperties;
			fight::TrackFactory* CreateDisablePoliceTrackFactory(const char* name);
			void RegisterDisablePoliceTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::AlertReportTrack (16 vftable slots, 0x1C bytes)
			class AlertReportTrack : public fight::Track
			{
			public:
				// 0x1026F190
				AlertReportTrack();
				virtual ~AlertReportTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1026D1C0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTimeout(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					float timeout;  // +0x18
			};

			extern fight::Property** gAlertReportTrackProperties;
			fight::TrackFactory* CreateAlertReportTrackFactory(const char* name);
			void RegisterAlertReportTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::CallStrikeTeamTrack (16 vftable slots, 0x14 bytes)
			class CallStrikeTeamTrack : public fight::Track
			{
			public:
				// 0x1026F230
				CallStrikeTeamTrack();
				virtual ~CallStrikeTeamTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1026D210, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gCallStrikeTeamTrackProperties;
			fight::TrackFactory* CreateCallStrikeTeamTrackFactory(const char* name);
			void RegisterCallStrikeTeamTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::PlayerCallStrikeTeamTrack (16 vftable slots, 0x14 bytes)
			class PlayerCallStrikeTeamTrack : public fight::Track
			{
			public:
				// 0x1026F2C0
				PlayerCallStrikeTeamTrack();
				virtual ~PlayerCallStrikeTeamTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1026D260, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gPlayerCallStrikeTeamTrackProperties;
			fight::TrackFactory* CreatePlayerCallStrikeTeamTrackFactory(const char* name);
			void RegisterPlayerCallStrikeTeamTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::SetInPursuitTrack (16 vftable slots, 0x18 bytes)
			class SetInPursuitTrack : public fight::Track
			{
			public:
				// 0x1026F350
				SetInPursuitTrack();
				virtual ~SetInPursuitTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1026CF40, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetPursuit(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					bool pursuit;  // +0x14
					unsigned char unknown15[0x3];
			};

			extern fight::Property** gSetInPursuitTrackProperties;
			fight::TrackFactory* CreateSetInPursuitTrackFactory(const char* name);
			void RegisterSetInPursuitTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::StartStrikeTeamMeterTrack (16 vftable slots, 0x18 bytes)
			class StartStrikeTeamMeterTrack : public fight::Track
			{
			public:
				// 0x1026F3E0
				StartStrikeTeamMeterTrack();
				virtual ~StartStrikeTeamMeterTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1026D080, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeToSpawn(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeToSpawn;  // +0x14
			};

			extern fight::Property** gStartStrikeTeamMeterTrackProperties;
			fight::TrackFactory* CreateStartStrikeTeamMeterTrackFactory(const char* name);
			void RegisterStartStrikeTeamMeterTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::SetAlertVariableTrack (16 vftable slots, 0x1C bytes)
			class SetAlertVariableTrack : public fight::Track
			{
			public:
				// 0x1026F480
				SetAlertVariableTrack();
				virtual ~SetAlertVariableTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1026CEF0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetVariable(int newValue);
				bool SetValue(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float value;  // +0x14
					int variable;  // +0x18
			};

			extern fight::Property** gSetAlertVariableTrackProperties;
			fight::TrackFactory* CreateSetAlertVariableTrackFactory(const char* name);
			void RegisterSetAlertVariableTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::ResetAlertVariablesTrack (16 vftable slots, 0x1C bytes)
			class ResetAlertVariablesTrack : public fight::Track
			{
			public:
				// 0x1026F520
				ResetAlertVariablesTrack();
				virtual ~ResetAlertVariablesTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1026CF90, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetResetJustTime(bool newValue);
				bool SetDontResetFactionIfSniffer(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool dontResetFactionIfSniffer;  // +0x18
					bool resetJustTime;  // +0x19
					unsigned char unknown1A[0x2];
			};

			extern fight::Property** gResetAlertVariablesTrackProperties;
			fight::TrackFactory* CreateResetAlertVariablesTrackFactory(const char* name);
			void RegisterResetAlertVariablesTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::ScenarioMessageTrack (16 vftable slots, 0x20 bytes)
			class ScenarioMessageTrack : public fight::Track
			{
			public:
				// 0x1026F5D0
				ScenarioMessageTrack();
				virtual ~ScenarioMessageTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1026CFE0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetEvent(int newValue);
				bool SetOnBegin(bool newValue);
				bool SetOnEnd(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int event;  // +0x18
					bool onBegin;  // +0x1C
					bool onEnd;  // +0x1D
					unsigned char unknown1E[0x2];
			};

			extern fight::Property** gScenarioMessageTrackProperties;
			fight::TrackFactory* CreateScenarioMessageTrackFactory(const char* name);
			void RegisterScenarioMessageTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::StopStrikeTeamMeterTrack (16 vftable slots, 0x14 bytes)
			class StopStrikeTeamMeterTrack : public fight::Track
			{
			public:
				// 0x1026F680
				StopStrikeTeamMeterTrack();
				virtual ~StopStrikeTeamMeterTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1026D0D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gStopStrikeTeamMeterTrackProperties;
			fight::TrackFactory* CreateStopStrikeTeamMeterTrackFactory(const char* name);
			void RegisterStopStrikeTeamMeterTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::HoldOnAlertEventsTrack (16 vftable slots, 0x18 bytes)
			class HoldOnAlertEventsTrack : public fight::Track
			{
			public:
				// 0x1026F710
				HoldOnAlertEventsTrack();
				virtual ~HoldOnAlertEventsTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1026D120, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
			};

			extern fight::Property** gHoldOnAlertEventsTrackProperties;
			fight::TrackFactory* CreateHoldOnAlertEventsTrackFactory(const char* name);
			void RegisterHoldOnAlertEventsTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
