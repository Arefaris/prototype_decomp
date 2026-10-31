// Fight items of the ai group: EnabledCondition, TaskCondition, GoalCondition (unit 0x10239F70 - 0x1023A830; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_ENABLED_H
#define PROTO_FIGHTITEMS_AI_AI_ENABLED_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::EnabledCondition (10 vftable slots, 0x10 bytes)
			class EnabledCondition : public fight::Condition
			{
			public:
				// 0x10239FB0
				EnabledCondition();
				virtual ~EnabledCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101FCE90, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIsEnabled(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool isEnabled;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gEnabledConditionProperties;
			fight::ConditionFactory* CreateEnabledConditionFactory(const char* name);
			void RegisterEnabledConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TaskCondition (10 vftable slots, 0x18 bytes)
			class TaskCondition : public fight::Condition
			{
			public:
				// 0x1023A0B0
				TaskCondition();
				virtual ~TaskCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101FCF40, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetTask(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name task;  // +0x10
			};

			extern fight::Property** gTaskConditionProperties;
			fight::ConditionFactory* CreateTaskConditionFactory(const char* name);
			void RegisterTaskConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::GoalCondition (10 vftable slots, 0x18 bytes)
			class GoalCondition : public fight::Condition
			{
			public:
				// 0x1023A0F0
				GoalCondition();
				virtual ~GoalCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101FD000, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetGoal(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name goal;  // +0x10
			};

			extern fight::Property** gGoalConditionProperties;
			fight::ConditionFactory* CreateGoalConditionFactory(const char* name);
			void RegisterGoalConditionFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
