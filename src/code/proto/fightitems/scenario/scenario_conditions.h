// Fight items of the scenario group: TransformationDescriptionNameCondition, AlertStatusCondition, InMissionCondition, IsPlayerCharacterCondition, TriggerVolumeEventCondition, MissionCondition (unit 0x101DBA70 - 0x101DD720; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_SCENARIO_SCENARIO_CONDITIONS_H
#define PROTO_FIGHTITEMS_SCENARIO_SCENARIO_CONDITIONS_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/engine/scenario/scenariolisters.h"
#include "code/proto/fightitems/scenario/scenariodata.h"

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			// RTTI: proto::fightitems::scenario::TransformationDescriptionNameCondition (10 vftable slots, 0x20 bytes)
			class TransformationDescriptionNameCondition : public fight::Condition
			{
			public:
				// 0x101DC1C0
				TransformationDescriptionNameCondition();
				virtual ~TransformationDescriptionNameCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101D90E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetAffiliate(int newValue);
				bool SetName(const fight::Name& newValue);
				bool SetIsActive(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name name;  // +0x10
					int affiliate;  // +0x18
					bool isActive;  // +0x1C
					unsigned char unknown1D[0x3];
			};

			extern fight::Property** gTransformationDescriptionNameConditionProperties;
			fight::ConditionFactory* CreateTransformationDescriptionNameConditionFactory(const char* name);
			void RegisterTransformationDescriptionNameConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::scenario::AlertStatusCondition (10 vftable slots, 0x14 bytes)
			class AlertStatusCondition : public fight::Condition
			{
			public:
				// 0x101DBB50
				AlertStatusCondition();
				virtual ~AlertStatusCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101D8F50, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetAffiliate(int newValue);
				bool SetAlert(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int affiliate;  // +0xC
					bool alert;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gAlertStatusConditionProperties;
			fight::ConditionFactory* CreateAlertStatusConditionFactory(const char* name);
			void RegisterAlertStatusConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::scenario::InMissionCondition (10 vftable slots, 0xC bytes)
			class InMissionCondition : public fight::Condition
			{
			public:
				// 0x101DBC20
				InMissionCondition();
				virtual ~InMissionCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101D8EE0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gInMissionConditionProperties;
			fight::ConditionFactory* CreateInMissionConditionFactory(const char* name);
			void RegisterInMissionConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::scenario::IsPlayerCharacterCondition (10 vftable slots, 0x10 bytes)
			class IsPlayerCharacterCondition : public fight::Condition
			{
			public:
				// 0x101DBC80
				IsPlayerCharacterCondition();
				virtual ~IsPlayerCharacterCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101D9040, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetAffiliate(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int affiliate;  // +0xC
			};

			extern fight::Property** gIsPlayerCharacterConditionProperties;
			fight::ConditionFactory* CreateIsPlayerCharacterConditionFactory(const char* name);
			void RegisterIsPlayerCharacterConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::scenario::TriggerVolumeEventCondition (11 vftable slots, 0x50 bytes)
			class TriggerVolumeEventCondition : public fight::Condition
			{
			public:
				// 0x101DBCF0
				TriggerVolumeEventCondition();
				virtual ~TriggerVolumeEventCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101D8E10, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);
				// vftable slot 10: whether the condition overrides a property
				virtual bool Slot10(int index);

				// The members the properties write
				bool SetType(int newValue);
				bool SetTriggerVolumeName(const char* newValue);
				bool SetTriggerVolumeAttributesTags(bool newValue);
				bool SetTriggerVolumeAttributesTagsTriggerAttributeKey1(const char* newValue);
				bool SetTriggerVolumeAttributesTagsTriggerAttributeValue1(const char* newValue);
				bool SetTriggerVolumeAttributesTagsTriggerAttributeKey2(const char* newValue);
				bool SetTriggerVolumeAttributesTagsTriggerAttributeValue2(const char* newValue);
				bool SetTriggerVolumeAttributesTagsTriggerTagList(const char* newValue);
				bool SetTouchName(const char* newValue);
				bool SetTouchAttributesTags(bool newValue);
				bool SetTouchAttributesTagsTouchAttributeKey1(const char* newValue);
				bool SetTouchAttributesTagsTouchAttributeValue1(const char* newValue);
				bool SetTouchAttributesTagsTouchAttributeKey2(const char* newValue);
				bool SetTouchAttributesTagsTouchAttributeValue2(const char* newValue);
				bool SetTouchAttributesTagsTouchTagList(const char* newValue);

				// 0x101DBE30: sets or clears the override bits of a group's members (name guess)
				void ApplyGroup(int group, bool value);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned __int64 overrideMask;  // +0x10
					char* touchAttributesTagsTouchAttributeKey1;  // +0x18
					char* touchAttributesTagsTouchAttributeKey2;  // +0x1C
					char* touchAttributesTagsTouchAttributeValue1;  // +0x20
					char* touchAttributesTagsTouchAttributeValue2;  // +0x24
					char* touchAttributesTagsTouchTagList;  // +0x28
					char* touchName;  // +0x2C
					char* triggerVolumeAttributesTagsTriggerAttributeKey1;  // +0x30
					char* triggerVolumeAttributesTagsTriggerAttributeKey2;  // +0x34
					char* triggerVolumeAttributesTagsTriggerAttributeValue1;  // +0x38
					char* triggerVolumeAttributesTagsTriggerAttributeValue2;  // +0x3C
					char* triggerVolumeAttributesTagsTriggerTagList;  // +0x40
					char* triggerVolumeName;  // +0x44
					int type;  // +0x48
					bool touchAttributesTags;  // +0x4C
					bool triggerVolumeAttributesTags;  // +0x4D
					unsigned char unknown4E[0x2];
			};

			extern fight::Property** gTriggerVolumeEventConditionProperties;
			fight::ConditionFactory* CreateTriggerVolumeEventConditionFactory(const char* name);
			void RegisterTriggerVolumeEventConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::scenario::MissionCondition (10 vftable slots, 0x14 bytes)
			class MissionCondition : public fight::Condition
			{
			public:
				// 0x101DC160
				MissionCondition();
				virtual ~MissionCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101D8E70, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetEpisode(int newValue);
				bool SetMission(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int episode;  // +0xC
					int mission;  // +0x10
			};

			extern fight::Property** gMissionConditionProperties;
			fight::ConditionFactory* CreateMissionConditionFactory(const char* name);
			void RegisterMissionConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
