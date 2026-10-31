// Fight items of the ai group: CheckTagAvailableSpaceCondition, HasCombatBudgetTokenCondition, RequestCombatBudgetTokenTrack (unit 0x10225F80 - 0x10226DB0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_COMBATBUDGET_H
#define PROTO_FIGHTITEMS_AI_AI_COMBATBUDGET_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::CheckTagAvailableSpaceCondition (10 vftable slots, 0x28 bytes)
			class CheckTagAvailableSpaceCondition : public fight::Condition
			{
			public:
				// 0x102261A0
				CheckTagAvailableSpaceCondition();
				virtual ~CheckTagAvailableSpaceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E8100, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetTag(const fight::Name& newValue);
				bool SetLimit(int newValue);
				bool SetTryDespawnIfFull(bool newValue);
				bool SetMinDespawnDistance(float newValue);
				bool SetObjRadius(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name tag;  // +0x10
					float minDespawnDistance;  // +0x18
					float objRadius;  // +0x1C
					int limit;  // +0x20
					bool tryDespawnIfFull;  // +0x24
					unsigned char unknown25[0x3];
			};

			extern fight::Property** gCheckTagAvailableSpaceConditionProperties;
			fight::ConditionFactory* CreateCheckTagAvailableSpaceConditionFactory(const char* name);
			void RegisterCheckTagAvailableSpaceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::HasCombatBudgetTokenCondition (10 vftable slots, 0x14 bytes)
			class HasCombatBudgetTokenCondition : public fight::Condition
			{
			public:
				// 0x102260A0
				HasCombatBudgetTokenCondition();
				virtual ~HasCombatBudgetTokenCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E8200, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetRequestInAdvance(bool newValue);
				bool SetCombatType(int newValue);
				bool SetHasToken(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int combatType;  // +0xC
					bool hasToken;  // +0x10
					bool requestInAdvance;  // +0x11
					unsigned char unknown12[0x2];
			};

			extern fight::Property** gHasCombatBudgetTokenConditionProperties;
			fight::ConditionFactory* CreateHasCombatBudgetTokenConditionFactory(const char* name);
			void RegisterHasCombatBudgetTokenConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::RequestCombatBudgetTokenTrack (16 vftable slots, 0x18 bytes)
			class RequestCombatBudgetTokenTrack : public fight::Track
			{
			public:
				// 0x10226110
				RequestCombatBudgetTokenTrack();
				virtual ~RequestCombatBudgetTokenTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E84F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetCombatType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					int combatType;  // +0x14
			};

			extern fight::Property** gRequestCombatBudgetTokenTrackProperties;
			fight::TrackFactory* CreateRequestCombatBudgetTokenTrackFactory(const char* name);
			void RegisterRequestCombatBudgetTokenTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
