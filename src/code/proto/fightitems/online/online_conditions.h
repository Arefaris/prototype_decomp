// Fight items of the online group: PlayerConditionGroupCondition, OnlineTestForRespawnStateCondition, DistanceToPlayerCondition, OnlineTestForPlayerDeathCondition, OnlinePlayerTypeCondition (unit 0x10264E40 - 0x10267A90; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_ONLINE_ONLINE_CONDITIONS_H
#define PROTO_FIGHTITEMS_ONLINE_ONLINE_CONDITIONS_H

#include "code/proto/messages/coopmessages.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/online/onlinedata.h"

namespace engine
{
	int GetControllingPlayer(GameObject* object);
}

namespace proto
{
	namespace fightitems
	{
		namespace online
		{
			// RTTI: proto::fightitems::online::PlayerConditionGroupCondition (10 vftable slots, 0x10 bytes)
			class PlayerConditionGroupCondition : public fight::Condition
			{
			public:
				// 0x10266930
				PlayerConditionGroupCondition();
				virtual ~PlayerConditionGroupCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10265410, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::ConditionList conditions;  // +0xC
			};

			extern fight::Property** gPlayerConditionGroupConditionProperties;
			fight::ConditionFactory* CreatePlayerConditionGroupConditionFactory(const char* name);
			void RegisterPlayerConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::online::OnlineTestForRespawnStateCondition (10 vftable slots, 0x14 bytes)
			class OnlineTestForRespawnStateCondition : public fight::Condition
			{
			public:
				// 0x102669B0
				OnlineTestForRespawnStateCondition();
				virtual ~OnlineTestForRespawnStateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x102650E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetPlayer(int newValue);
				bool SetState(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int player;  // +0xC
					int state;  // +0x10
			};

			extern fight::Property** gOnlineTestForRespawnStateConditionProperties;
			fight::ConditionFactory* CreateOnlineTestForRespawnStateConditionFactory(const char* name);
			void RegisterOnlineTestForRespawnStateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::online::DistanceToPlayerCondition (10 vftable slots, 0x18 bytes)
			class DistanceToPlayerCondition : public fight::Condition
			{
			public:
				// 0x10266A20
				DistanceToPlayerCondition();
				virtual ~DistanceToPlayerCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10265290, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetPlayer(int newValue);
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distance;  // +0xC
					int compare;  // +0x10
					int player;  // +0x14
			};

			extern fight::Property** gDistanceToPlayerConditionProperties;
			fight::ConditionFactory* CreateDistanceToPlayerConditionFactory(const char* name);
			void RegisterDistanceToPlayerConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::online::OnlineTestForPlayerDeathCondition (10 vftable slots, 0x10 bytes)
			class OnlineTestForPlayerDeathCondition : public fight::Condition
			{
			public:
				// 0x10266AA0
				OnlineTestForPlayerDeathCondition();
				virtual ~OnlineTestForPlayerDeathCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x102651C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetPlayer(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int player;  // +0xC
			};

			extern fight::Property** gOnlineTestForPlayerDeathConditionProperties;
			fight::ConditionFactory* CreateOnlineTestForPlayerDeathConditionFactory(const char* name);
			void RegisterOnlineTestForPlayerDeathConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::online::OnlinePlayerTypeCondition (10 vftable slots, 0x14 bytes)
			class OnlinePlayerTypeCondition : public fight::Condition
			{
			public:
				// 0x10266B10
				OnlinePlayerTypeCondition();
				virtual ~OnlinePlayerTypeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10264FF0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetPlayer(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int compare;  // +0xC
					int player;  // +0x10
			};

			extern fight::Property** gOnlinePlayerTypeConditionProperties;
			fight::ConditionFactory* CreateOnlinePlayerTypeConditionFactory(const char* name);
			void RegisterOnlinePlayerTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// 0x104DBFF0: the handle of the player of a type (name guess)
			engine::GameObjectHandle FindPlayerHandle(engine::GameObjectHandle owner, int playerType);
		}
	}
}

#endif
