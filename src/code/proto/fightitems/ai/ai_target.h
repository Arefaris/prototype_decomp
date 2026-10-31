// Fight items of the ai group: TargetHostileCondition, TargetClassCondition, TargetDefenseCondition, TargetAlertSubStateCondition, AutoTargetConditionGroupCondition, TargetCanSeeCondition, TargetAlertStateCondition, ChangedTargetSinceCondition, TargetableCondition, TargetConditionGroupCondition, TargetIsTankCondition, TargetIsPlayerCondition, TargetingCondition, TargetIsHelicopterCondition, AutoTargetingCondition (unit 0x1024F860 - 0x102527C0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_TARGET_H
#define PROTO_FIGHTITEMS_AI_AI_TARGET_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::TargetHostileCondition (10 vftable slots, 0x10 bytes)
			class TargetHostileCondition : public fight::Condition
			{
			public:
				// 0x1024F9E0
				TargetHostileCondition();
				virtual ~TargetHostileCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10215EE0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIsHostile(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool isHostile;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gTargetHostileConditionProperties;
			fight::ConditionFactory* CreateTargetHostileConditionFactory(const char* name);
			void RegisterTargetHostileConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetClassCondition (10 vftable slots, 0x14 bytes)
			class TargetClassCondition : public fight::Condition
			{
			public:
				// 0x1024FA40
				TargetClassCondition();
				virtual ~TargetClassCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10216BD0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetTargetClass(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int compare;  // +0xC
					int targetClass;  // +0x10
			};

			extern fight::Property** gTargetClassConditionProperties;
			fight::ConditionFactory* CreateTargetClassConditionFactory(const char* name);
			void RegisterTargetClassConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetDefenseCondition (10 vftable slots, 0x18 bytes)
			class TargetDefenseCondition : public fight::Condition
			{
			public:
				// 0x1024FAB0
				TargetDefenseCondition();
				virtual ~TargetDefenseCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x102165B0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDefense(int newValue);
				bool SetCompare(int newValue);
				bool SetValue(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float value;  // +0xC
					int compare;  // +0x10
					int defense;  // +0x14
			};

			extern fight::Property** gTargetDefenseConditionProperties;
			fight::ConditionFactory* CreateTargetDefenseConditionFactory(const char* name);
			void RegisterTargetDefenseConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetAlertSubStateCondition (10 vftable slots, 0x10 bytes)
			class TargetAlertSubStateCondition : public fight::Condition
			{
			public:
				// 0x1024FB30
				TargetAlertSubStateCondition();
				virtual ~TargetAlertSubStateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10216190, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSubState(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int subState;  // +0xC
			};

			extern fight::Property** gTargetAlertSubStateConditionProperties;
			fight::ConditionFactory* CreateTargetAlertSubStateConditionFactory(const char* name);
			void RegisterTargetAlertSubStateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::AutoTargetConditionGroupCondition (10 vftable slots, 0x10 bytes)
			class AutoTargetConditionGroupCondition : public fight::Condition
			{
			public:
				// 0x1024FBA0
				AutoTargetConditionGroupCondition();
				virtual ~AutoTargetConditionGroupCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10215D40, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::ConditionList conditions;  // +0xC
			};

			extern fight::Property** gAutoTargetConditionGroupConditionProperties;
			fight::ConditionFactory* CreateAutoTargetConditionGroupConditionFactory(const char* name);
			void RegisterAutoTargetConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetCanSeeCondition (10 vftable slots, 0x14 bytes)
			class TargetCanSeeCondition : public fight::Condition
			{
			public:
				// 0x1024FC20
				TargetCanSeeCondition();
				virtual ~TargetCanSeeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10216290, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSeen(bool newValue);
				bool SetSince(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float since;  // +0xC
					bool seen;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gTargetCanSeeConditionProperties;
			fight::ConditionFactory* CreateTargetCanSeeConditionFactory(const char* name);
			void RegisterTargetCanSeeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetAlertStateCondition (10 vftable slots, 0x10 bytes)
			class TargetAlertStateCondition : public fight::Condition
			{
			public:
				// 0x1024FC90
				TargetAlertStateCondition();
				virtual ~TargetAlertStateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10215FF0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetState(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int state;  // +0xC
			};

			extern fight::Property** gTargetAlertStateConditionProperties;
			fight::ConditionFactory* CreateTargetAlertStateConditionFactory(const char* name);
			void RegisterTargetAlertStateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ChangedTargetSinceCondition (10 vftable slots, 0x20 bytes)
			class ChangedTargetSinceCondition : public fight::Condition
			{
			public:
				// 0x10250200
				ChangedTargetSinceCondition();
				virtual ~ChangedTargetSinceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x102167E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetTimer(const fight::Name& newValue);
				bool SetTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name timer;  // +0x10
					float time;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gChangedTargetSinceConditionProperties;
			fight::ConditionFactory* CreateChangedTargetSinceConditionFactory(const char* name);
			void RegisterChangedTargetSinceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetableCondition (10 vftable slots, 0x10 bytes)
			class TargetableCondition : public fight::Condition
			{
			public:
				// 0x1024FD30
				TargetableCondition();
				virtual ~TargetableCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10216B00, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIsTargetable(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool isTargetable;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gTargetableConditionProperties;
			fight::ConditionFactory* CreateTargetableConditionFactory(const char* name);
			void RegisterTargetableConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetConditionGroupCondition (10 vftable slots, 0x10 bytes)
			class TargetConditionGroupCondition : public fight::Condition
			{
			public:
				// 0x1024FD90
				TargetConditionGroupCondition();
				virtual ~TargetConditionGroupCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10215A90, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::ConditionList conditions;  // +0xC
			};

			extern fight::Property** gTargetConditionGroupConditionProperties;
			fight::ConditionFactory* CreateTargetConditionGroupConditionFactory(const char* name);
			void RegisterTargetConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetIsTankCondition (10 vftable slots, 0xC bytes)
			class TargetIsTankCondition : public fight::Condition
			{
			public:
				// 0x1024FE70
				TargetIsTankCondition();
				virtual ~TargetIsTankCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10216920, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gTargetIsTankConditionProperties;
			fight::ConditionFactory* CreateTargetIsTankConditionFactory(const char* name);
			void RegisterTargetIsTankConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetIsPlayerCondition (10 vftable slots, 0x10 bytes)
			class TargetIsPlayerCondition : public fight::Condition
			{
			public:
				// 0x1024FED0
				TargetIsPlayerCondition();
				virtual ~TargetIsPlayerCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x102166E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIs(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool is;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gTargetIsPlayerConditionProperties;
			fight::ConditionFactory* CreateTargetIsPlayerConditionFactory(const char* name);
			void RegisterTargetIsPlayerConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetingCondition (10 vftable slots, 0x10 bytes)
			class TargetingCondition : public fight::Condition
			{
			public:
				// 0x1024FF30
				TargetingCondition();
				virtual ~TargetingCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x102158F0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIsTargeting(bool newValue);
				bool SetIncludeAutoTarget(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool includeAutoTarget;  // +0xC
					bool isTargeting;  // +0xD
					unsigned char unknownE[0x2];
			};

			extern fight::Property** gTargetingConditionProperties;
			fight::ConditionFactory* CreateTargetingConditionFactory(const char* name);
			void RegisterTargetingConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetIsHelicopterCondition (10 vftable slots, 0xC bytes)
			class TargetIsHelicopterCondition : public fight::Condition
			{
			public:
				// 0x10250000
				TargetIsHelicopterCondition();
				virtual ~TargetIsHelicopterCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10216A10, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gTargetIsHelicopterConditionProperties;
			fight::ConditionFactory* CreateTargetIsHelicopterConditionFactory(const char* name);
			void RegisterTargetIsHelicopterConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::AutoTargetingCondition (10 vftable slots, 0x10 bytes)
			class AutoTargetingCondition : public fight::Condition
			{
			public:
				// 0x10250060
				AutoTargetingCondition();
				virtual ~AutoTargetingCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10215C30, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIsAutoTargeting(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool isAutoTargeting;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gAutoTargetingConditionProperties;
			fight::ConditionFactory* CreateAutoTargetingConditionFactory(const char* name);
			void RegisterAutoTargetingConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
