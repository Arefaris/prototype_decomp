// Fight items of the motion group: NPCAnimationVersionCondition, PedestrianFirstFrameUpgradedCondition, PedestrianStateCondition, PedestrianAngleToTargetCondition, CharacterCloudStateCondition, PedestrianRequestDowngradeCondition, PedestrianLowMoraleCondition, PedestrianAlertStateCondition, SetPedestrianReadyForDowngradeTrack, SpreadPedestrianAlertStateTrack, SetPedestrianAlertStateTrack, SetPedestrianStateTrack, CharacterCloudStateTrack (unit 0x1019C4A0 - 0x1019F890; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_PEDESTRIAN_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_PEDESTRIAN_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction2.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::NPCAnimationVersionCondition (10 vftable slots, 0x14 bytes)
			class NPCAnimationVersionCondition : public fight::Condition
			{
			public:
				// 0x1019C720
				NPCAnimationVersionCondition();
				virtual ~NPCAnimationVersionCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10103390, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetMatch(bool newValue);
				bool SetVersion(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int version;  // +0xC
					bool match;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gNPCAnimationVersionConditionProperties;
			fight::ConditionFactory* CreateNPCAnimationVersionConditionFactory(const char* name);
			void RegisterNPCAnimationVersionConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::PedestrianFirstFrameUpgradedCondition (10 vftable slots, 0x10 bytes)
			class PedestrianFirstFrameUpgradedCondition : public fight::Condition
			{
			public:
				// 0x1019C790
				PedestrianFirstFrameUpgradedCondition();
				virtual ~PedestrianFirstFrameUpgradedCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10103230, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetMatch(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool match;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gPedestrianFirstFrameUpgradedConditionProperties;
			fight::ConditionFactory* CreatePedestrianFirstFrameUpgradedConditionFactory(const char* name);
			void RegisterPedestrianFirstFrameUpgradedConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::PedestrianStateCondition (10 vftable slots, 0x14 bytes)
			class PedestrianStateCondition : public fight::Condition
			{
			public:
				// 0x1019C7F0
				PedestrianStateCondition();
				virtual ~PedestrianStateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101028C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetMatch(bool newValue);
				bool SetState(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int state;  // +0xC
					bool match;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gPedestrianStateConditionProperties;
			fight::ConditionFactory* CreatePedestrianStateConditionFactory(const char* name);
			void RegisterPedestrianStateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::PedestrianAngleToTargetCondition (10 vftable slots, 0x14 bytes)
			class PedestrianAngleToTargetCondition : public fight::Condition
			{
			public:
				// 0x1019C860
				PedestrianAngleToTargetCondition();
				virtual ~PedestrianAngleToTargetCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10102F00, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompareTime(int newValue);
				bool SetAngle(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float angle;  // +0xC
					int compareTime;  // +0x10
			};

			extern fight::Property** gPedestrianAngleToTargetConditionProperties;
			fight::ConditionFactory* CreatePedestrianAngleToTargetConditionFactory(const char* name);
			void RegisterPedestrianAngleToTargetConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::CharacterCloudStateCondition (10 vftable slots, 0x14 bytes)
			class CharacterCloudStateCondition : public fight::Condition
			{
			public:
				// 0x1019C8D0
				CharacterCloudStateCondition();
				virtual ~CharacterCloudStateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10102820, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetMatch(bool newValue);
				bool SetState(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int state;  // +0xC
					bool match;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gCharacterCloudStateConditionProperties;
			fight::ConditionFactory* CreateCharacterCloudStateConditionFactory(const char* name);
			void RegisterCharacterCloudStateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::PedestrianRequestDowngradeCondition (10 vftable slots, 0x10 bytes)
			class PedestrianRequestDowngradeCondition : public fight::Condition
			{
			public:
				// 0x1019C940
				PedestrianRequestDowngradeCondition();
				virtual ~PedestrianRequestDowngradeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101032F0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetMatch(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool match;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gPedestrianRequestDowngradeConditionProperties;
			fight::ConditionFactory* CreatePedestrianRequestDowngradeConditionFactory(const char* name);
			void RegisterPedestrianRequestDowngradeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::PedestrianLowMoraleCondition (10 vftable slots, 0x10 bytes)
			class PedestrianLowMoraleCondition : public fight::Condition
			{
			public:
				// 0x1019C9A0
				PedestrianLowMoraleCondition();
				virtual ~PedestrianLowMoraleCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10103170, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetMatch(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool match;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gPedestrianLowMoraleConditionProperties;
			fight::ConditionFactory* CreatePedestrianLowMoraleConditionFactory(const char* name);
			void RegisterPedestrianLowMoraleConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::PedestrianAlertStateCondition (10 vftable slots, 0x14 bytes)
			class PedestrianAlertStateCondition : public fight::Condition
			{
			public:
				// 0x1019CA00
				PedestrianAlertStateCondition();
				virtual ~PedestrianAlertStateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10102E30, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetMatch(bool newValue);
				bool SetState(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int state;  // +0xC
					bool match;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gPedestrianAlertStateConditionProperties;
			fight::ConditionFactory* CreatePedestrianAlertStateConditionFactory(const char* name);
			void RegisterPedestrianAlertStateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SetPedestrianReadyForDowngradeTrack (16 vftable slots, 0x18 bytes)
			class SetPedestrianReadyForDowngradeTrack : public fight::Track
			{
			public:
				// 0x1019CA70
				SetPedestrianReadyForDowngradeTrack();
				virtual ~SetPedestrianReadyForDowngradeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10103DA0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetReady(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					bool ready;  // +0x14
					unsigned char unknown15[0x3];
			};

			extern fight::Property** gSetPedestrianReadyForDowngradeTrackProperties;
			fight::TrackFactory* CreateSetPedestrianReadyForDowngradeTrackFactory(const char* name);
			void RegisterSetPedestrianReadyForDowngradeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SpreadPedestrianAlertStateTrack (16 vftable slots, 0x2C bytes)
			class SpreadPedestrianAlertStateTrack : public fight::Track
			{
			public:
				// 0x1019CB00
				SpreadPedestrianAlertStateTrack();
				virtual ~SpreadPedestrianAlertStateTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10103CB0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetState(int newValue);
				bool SetRadius(float newValue);
				bool SetMaxDistanceFromSource(float newValue);
				bool SetMaxPasses(int newValue);
				bool SetAlertFrequency(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float maxDistanceFromSource;  // +0x10
					float radius;  // +0x14
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
					int alertFrequency;  // +0x20
					int maxPasses;  // +0x24
					int state;  // +0x28
			};

			extern fight::Property** gSpreadPedestrianAlertStateTrackProperties;
			fight::TrackFactory* CreateSpreadPedestrianAlertStateTrackFactory(const char* name);
			void RegisterSpreadPedestrianAlertStateTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SetPedestrianAlertStateTrack (16 vftable slots, 0x18 bytes)
			class SetPedestrianAlertStateTrack : public fight::Track
			{
			public:
				// 0x1019CBD0
				SetPedestrianAlertStateTrack();
				virtual ~SetPedestrianAlertStateTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10103D00, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetState(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					int state;  // +0x14
			};

			extern fight::Property** gSetPedestrianAlertStateTrackProperties;
			fight::TrackFactory* CreateSetPedestrianAlertStateTrackFactory(const char* name);
			void RegisterSetPedestrianAlertStateTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SetPedestrianStateTrack (16 vftable slots, 0x18 bytes)
			class SetPedestrianStateTrack : public fight::Track
			{
			public:
				// 0x1019CC70
				SetPedestrianStateTrack();
				virtual ~SetPedestrianStateTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10103D50, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetState(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					int state;  // +0x14
			};

			extern fight::Property** gSetPedestrianStateTrackProperties;
			fight::TrackFactory* CreateSetPedestrianStateTrackFactory(const char* name);
			void RegisterSetPedestrianStateTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::CharacterCloudStateTrack (16 vftable slots, 0x18 bytes)
			class CharacterCloudStateTrack : public fight::Track
			{
			public:
				// 0x1019CD10
				CharacterCloudStateTrack();
				virtual ~CharacterCloudStateTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10103C60, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetState(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					int state;  // +0x14
			};

			extern fight::Property** gCharacterCloudStateTrackProperties;
			fight::TrackFactory* CreateCharacterCloudStateTrackFactory(const char* name);
			void RegisterCharacterCloudStateTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::SetPedestrianReadyForDowngradeAction (9 vftable slots, 0x2C bytes)
			class SetPedestrianReadyForDowngradeAction : public fight::Action
			{
			public:
				// 0x10103B40
				SetPedestrianReadyForDowngradeAction(SetPedestrianReadyForDowngradeTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10102AC0
				virtual ~SetPedestrianReadyForDowngradeAction();

				// vftable slot 5 (0x10103BF0)
				virtual bool Slot5(int arg, float value);

				core::Link<SetPedestrianReadyForDowngradeTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::motion::SpreadPedestrianAlertStateAction (9 vftable slots, 0x2C bytes)
			class SpreadPedestrianAlertStateAction : public fight::Action
			{
			public:
				// 0x101035D0
				SpreadPedestrianAlertStateAction(SpreadPedestrianAlertStateTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101029D0
				virtual ~SpreadPedestrianAlertStateAction();

				// vftable slot 7 (0x10103670)
				virtual bool Slot7(int arg, float value);

				core::Link<SpreadPedestrianAlertStateTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				int unknown2C;  // +0x2C
				int unknown30;  // +0x30
			};

			// RTTI: proto::fightitems::motion::SetPedestrianAlertStateAction (9 vftable slots, 0x2C bytes)
			class SetPedestrianAlertStateAction : public fight::Action
			{
			public:
				// 0x101038A0
				SetPedestrianAlertStateAction(SetPedestrianAlertStateTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10102A20
				virtual ~SetPedestrianAlertStateAction();

				// vftable slot 5 (0x10103950)
				virtual bool Slot5(int arg, float value);

				core::Link<SetPedestrianAlertStateTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::motion::SetPedestrianStateAction (9 vftable slots, 0x2C bytes)
			class SetPedestrianStateAction : public fight::Action
			{
			public:
				// 0x101039F0
				SetPedestrianStateAction(SetPedestrianStateTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10102A70
				virtual ~SetPedestrianStateAction();

				// vftable slot 5 (0x10103AA0)
				virtual bool Slot5(int arg, float value);

				core::Link<SetPedestrianStateTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::motion::CharacterCloudStateAction (9 vftable slots, 0x2C bytes)
			class CharacterCloudStateAction : public fight::Action
			{
			public:
				// 0x10103460
				CharacterCloudStateAction(CharacterCloudStateTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10102980
				virtual ~CharacterCloudStateAction();

				// vftable slot 5 (0x10103500)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10102360)
				virtual void Slot6();

				core::Link<CharacterCloudStateTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				int unknown2C;  // +0x2C
			};

			// ---- actions end
		}
	}
}

#endif
