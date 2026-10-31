// Fight items of the ai group: InAlertModeCondition, PerceptionEventCondition, TargetFreeHeightRadiusCondition (unit 0x1022CB50 - 0x1022D810; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_ALERTMODE_H
#define PROTO_FIGHTITEMS_AI_AI_ALERTMODE_H

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
			// RTTI: proto::fightitems::ai::InAlertModeCondition (10 vftable slots, 0x14 bytes)
			class InAlertModeCondition : public fight::Condition
			{
			public:
				// 0x1022CC20
				InAlertModeCondition();
				virtual ~InAlertModeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101ED140, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetSeconds(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float seconds;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gInAlertModeConditionProperties;
			fight::ConditionFactory* CreateInAlertModeConditionFactory(const char* name);
			void RegisterInAlertModeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::PerceptionEventCondition (10 vftable slots, 0x10 bytes)
			class PerceptionEventCondition : public fight::Condition
			{
			public:
				// 0x1022CCA0
				PerceptionEventCondition();
				virtual ~PerceptionEventCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101ED120, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetEvent(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int event;  // +0xC
			};

			extern fight::Property** gPerceptionEventConditionProperties;
			fight::ConditionFactory* CreatePerceptionEventConditionFactory(const char* name);
			void RegisterPerceptionEventConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetFreeHeightRadiusCondition (10 vftable slots, 0x1C bytes)
			class TargetFreeHeightRadiusCondition : public fight::Condition
			{
			public:
				// 0x1022CD10
				TargetFreeHeightRadiusCondition();
				virtual ~TargetFreeHeightRadiusCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101ED210, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetRadius(float newValue);
				bool SetHeightTolerance(float newValue);
				bool SetGroundUnit(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float heightTolerance;  // +0xC
					float radius;  // +0x10
					int compare;  // +0x14
					bool groundUnit;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gTargetFreeHeightRadiusConditionProperties;
			fight::ConditionFactory* CreateTargetFreeHeightRadiusConditionFactory(const char* name);
			void RegisterTargetFreeHeightRadiusConditionFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
