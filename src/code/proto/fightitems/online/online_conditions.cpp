// Fight items of the online group: PlayerConditionGroupCondition, OnlineTestForRespawnStateCondition, DistanceToPlayerCondition, OnlineTestForPlayerDeathCondition, OnlinePlayerTypeCondition (unit 0x10264E40 - 0x10267A90; no assert path, the file name is a guess).
#include "code/proto/fightitems/online/online_conditions.h"

namespace proto
{
	namespace fightitems
	{
		namespace online
		{
			fight::Property** gPlayerConditionGroupConditionProperties;  // 0x11255E3C

			// FUNCTION: ENGINE 0x10266860
			fight::ConditionList* PlayerConditionGroupCondition::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x10266900
			fight::Property* PlayerConditionGroupCondition::GetProperty(int index)
			{
				return gPlayerConditionGroupConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10266920
			void PlayerConditionGroupCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPlayerConditionGroupConditionProperties);
			}

			// FUNCTION: ENGINE 0x10266930
			PlayerConditionGroupCondition::PlayerConditionGroupCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x10266960
			PlayerConditionGroupCondition::~PlayerConditionGroupCondition()
			{
			}

			// FUNCTION: ENGINE 0x102671F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PlayerConditionGroupCondition::RegisterProperties()
			{
				if (gPlayerConditionGroupConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyConditionGroup<PlayerConditionGroupCondition>("conditions", &PlayerConditionGroupCondition::SetConditions);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gPlayerConditionGroupConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10267100
			fight::ConditionFactory* CreatePlayerConditionGroupConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PlayerConditionGroupCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10267680
			void RegisterPlayerConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PlayerConditionGroupCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gOnlineTestForRespawnStateConditionProperties;  // 0x11255E40

			// FUNCTION: ENGINE 0x10266870
			bool OnlineTestForRespawnStateCondition::SetPlayer(int newValue)
			{
				player = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10266880
			bool OnlineTestForRespawnStateCondition::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10266980
			fight::Property* OnlineTestForRespawnStateCondition::GetProperty(int index)
			{
				return gOnlineTestForRespawnStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x102669A0
			void OnlineTestForRespawnStateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gOnlineTestForRespawnStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x102669B0
			OnlineTestForRespawnStateCondition::OnlineTestForRespawnStateCondition() : fight::Condition(0), player(0), state(0)
			{
			}

			// FUNCTION: ENGINE 0x102669E0
			OnlineTestForRespawnStateCondition::~OnlineTestForRespawnStateCondition()
			{
			}

			// FUNCTION: ENGINE 0x10267290
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void OnlineTestForRespawnStateCondition::RegisterProperties()
			{
				if (gOnlineTestForRespawnStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<OnlineTestForRespawnStateCondition>("player", motion::gGrabPlayerTrackGrabbingPlayerTable, motion::gGrabPlayerTrackGrabbingPlayerCount, &OnlineTestForRespawnStateCondition::SetPlayer);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<OnlineTestForRespawnStateCondition>("state", gOnlineTestForRespawnStateConditionStateTable, gOnlineTestForRespawnStateConditionStateCount, &OnlineTestForRespawnStateCondition::SetState);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gOnlineTestForRespawnStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10267130
			fight::ConditionFactory* CreateOnlineTestForRespawnStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<OnlineTestForRespawnStateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102676B0
			void RegisterOnlineTestForRespawnStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<OnlineTestForRespawnStateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDistanceToPlayerConditionProperties;  // 0x11255E44

			// FUNCTION: ENGINE 0x10266890
			bool DistanceToPlayerCondition::SetPlayer(int newValue)
			{
				player = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102668A0
			bool DistanceToPlayerCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102668B0
			bool DistanceToPlayerCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102669F0
			fight::Property* DistanceToPlayerCondition::GetProperty(int index)
			{
				return gDistanceToPlayerConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10266A10
			void DistanceToPlayerCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDistanceToPlayerConditionProperties);
			}

			// FUNCTION: ENGINE 0x10266A20
			DistanceToPlayerCondition::DistanceToPlayerCondition() : fight::Condition(0), distance(0.0f), compare(0), player(0)
			{
			}

			// FUNCTION: ENGINE 0x10266A60
			DistanceToPlayerCondition::~DistanceToPlayerCondition()
			{
			}

			// FUNCTION: ENGINE 0x10267390
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DistanceToPlayerCondition::RegisterProperties()
			{
				if (gDistanceToPlayerConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<DistanceToPlayerCondition>("player", motion::gGrabPlayerTrackGrabbingPlayerTable, motion::gGrabPlayerTrackGrabbingPlayerCount, &DistanceToPlayerCondition::SetPlayer);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<DistanceToPlayerCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &DistanceToPlayerCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DistanceToPlayerCondition>("distance", &DistanceToPlayerCondition::SetDistance);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gDistanceToPlayerConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10267160
			fight::ConditionFactory* CreateDistanceToPlayerConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DistanceToPlayerCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102676E0
			void RegisterDistanceToPlayerConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DistanceToPlayerCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gOnlineTestForPlayerDeathConditionProperties;  // 0x11255E48

			// FUNCTION: ENGINE 0x102668D0
			bool OnlineTestForPlayerDeathCondition::SetPlayer(int newValue)
			{
				player = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10266A70
			fight::Property* OnlineTestForPlayerDeathCondition::GetProperty(int index)
			{
				return gOnlineTestForPlayerDeathConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10266A90
			void OnlineTestForPlayerDeathCondition::ClearProperties()
			{
				fight::FreePropertyList(&gOnlineTestForPlayerDeathConditionProperties);
			}

			// FUNCTION: ENGINE 0x10266AA0
			OnlineTestForPlayerDeathCondition::OnlineTestForPlayerDeathCondition() : fight::Condition(0), player(0)
			{
			}

			// FUNCTION: ENGINE 0x10266AD0
			OnlineTestForPlayerDeathCondition::~OnlineTestForPlayerDeathCondition()
			{
			}

			// FUNCTION: ENGINE 0x102674D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void OnlineTestForPlayerDeathCondition::RegisterProperties()
			{
				if (gOnlineTestForPlayerDeathConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<OnlineTestForPlayerDeathCondition>("player", motion::gGrabPlayerTrackGrabbingPlayerTable, motion::gGrabPlayerTrackGrabbingPlayerCount, &OnlineTestForPlayerDeathCondition::SetPlayer);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gOnlineTestForPlayerDeathConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10267190
			fight::ConditionFactory* CreateOnlineTestForPlayerDeathConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<OnlineTestForPlayerDeathCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10267710
			void RegisterOnlineTestForPlayerDeathConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<OnlineTestForPlayerDeathCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gOnlinePlayerTypeConditionProperties;  // 0x11255E4C

			// FUNCTION: ENGINE 0x102668E0
			bool OnlinePlayerTypeCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102668F0
			bool OnlinePlayerTypeCondition::SetPlayer(int newValue)
			{
				player = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10266AE0
			fight::Property* OnlinePlayerTypeCondition::GetProperty(int index)
			{
				return gOnlinePlayerTypeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10266B00
			void OnlinePlayerTypeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gOnlinePlayerTypeConditionProperties);
			}

			// FUNCTION: ENGINE 0x10266B10
			OnlinePlayerTypeCondition::OnlinePlayerTypeCondition() : fight::Condition(0), compare(0), player(0)
			{
			}

			// FUNCTION: ENGINE 0x10266B40
			OnlinePlayerTypeCondition::~OnlinePlayerTypeCondition()
			{
			}

			// FUNCTION: ENGINE 0x10267580
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void OnlinePlayerTypeCondition::RegisterProperties()
			{
				if (gOnlinePlayerTypeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<OnlinePlayerTypeCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &OnlinePlayerTypeCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<OnlinePlayerTypeCondition>("player", motion::gGrabPlayerTrackGrabbingPlayerTable, motion::gGrabPlayerTrackGrabbingPlayerCount, &OnlinePlayerTypeCondition::SetPlayer);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gOnlinePlayerTypeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102671C0
			fight::ConditionFactory* CreateOnlinePlayerTypeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<OnlinePlayerTypeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10267740
			void RegisterOnlinePlayerTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<OnlinePlayerTypeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyConditionGroup<PlayerConditionGroupCondition>;
			template class fight::ConditionFactoryTemplate<PlayerConditionGroupCondition>;
			template class fight::ConditionFactoryCasterTemplate<PlayerConditionGroupCondition>;
			template class fight::PropertyEnumConstList<OnlineTestForRespawnStateCondition>;
			template class fight::ConditionFactoryTemplate<OnlineTestForRespawnStateCondition>;
			template class fight::ConditionFactoryCasterTemplate<OnlineTestForRespawnStateCondition>;
			template class fight::PropertyEnumConstList<DistanceToPlayerCondition>;
			template class fight::PropertyFloatConstRange<DistanceToPlayerCondition>;
			template class fight::ConditionFactoryTemplate<DistanceToPlayerCondition>;
			template class fight::ConditionFactoryCasterTemplate<DistanceToPlayerCondition>;
			template class fight::PropertyEnumConstList<OnlineTestForPlayerDeathCondition>;
			template class fight::ConditionFactoryTemplate<OnlineTestForPlayerDeathCondition>;
			template class fight::ConditionFactoryCasterTemplate<OnlineTestForPlayerDeathCondition>;
			template class fight::PropertyEnumConstList<OnlinePlayerTypeCondition>;
			template class fight::ConditionFactoryTemplate<OnlinePlayerTypeCondition>;
			template class fight::ConditionFactoryCasterTemplate<OnlinePlayerTypeCondition>;

			// FUNCTION: ENGINE 0x102650E0
			bool OnlineTestForRespawnStateCondition::Evaluate(int a, int b, int c, int d)
			{
				int playerType = player;
				engine::GameObjectHandle handle = FindPlayerHandle(engine::GetObjectHandle(ai::AsOwner(c)), playerType);
				engine::GameObject* object = handle.Get();
				if (object == 0)
				{
					return false;
				}
				CoOpMessageGetRespawnState message;
				object->SendMessage(&message);
				if (state == 0)
				{
					return message.state != 0;
				}
				return message.state == state;
			}

			// FUNCTION: ENGINE 0x102651C0
			bool OnlineTestForPlayerDeathCondition::Evaluate(int a, int b, int c, int d)
			{
				int playerType = player;
				engine::GameObjectHandle handle = FindPlayerHandle(engine::GetObjectHandle(ai::AsOwner(c)), playerType);
				engine::GameObject* object = handle.Get();
				if (object == 0)
				{
					return false;
				}
				CoOpMessageGetPlayerDeathState message(engine::GetControllingPlayer(object));
				object->SendMessage(&message);
				return message.dead;
			}
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10265050
// FUNCTION: ENGINE 0x10265080
// FUNCTION: ENGINE 0x102650B0
// FUNCTION: ENGINE 0x10266B50
// FUNCTION: ENGINE 0x10266B80
// FUNCTION: ENGINE 0x10266BB0
// FUNCTION: ENGINE 0x10266BE0
// FUNCTION: ENGINE 0x10266C10
// FUNCTION: ENGINE 0x10266C40
// FUNCTION: ENGINE 0x10266C50
// FUNCTION: ENGINE 0x10266C80
// FUNCTION: ENGINE 0x10266C90
// FUNCTION: ENGINE 0x10266CC0
// FUNCTION: ENGINE 0x10266CD0
// FUNCTION: ENGINE 0x10266D00
// FUNCTION: ENGINE 0x10266D10
// FUNCTION: ENGINE 0x10266D40
// FUNCTION: ENGINE 0x10266D50
// FUNCTION: ENGINE 0x10266D80
// FUNCTION: ENGINE 0x10266DB0
// FUNCTION: ENGINE 0x10266DD0
// FUNCTION: ENGINE 0x10266E10
// FUNCTION: ENGINE 0x10266E20
// FUNCTION: ENGINE 0x10266E50
// FUNCTION: ENGINE 0x10266E70
// FUNCTION: ENGINE 0x10266E80
// FUNCTION: ENGINE 0x10266EC0
// FUNCTION: ENGINE 0x10266ED0
// FUNCTION: ENGINE 0x10266F00
// FUNCTION: ENGINE 0x10266F20
// FUNCTION: ENGINE 0x10266F30
// FUNCTION: ENGINE 0x10266F60
// FUNCTION: ENGINE 0x10266F90
// FUNCTION: ENGINE 0x10266FA0
// FUNCTION: ENGINE 0x10266FE0
// FUNCTION: ENGINE 0x10266FF0
// FUNCTION: ENGINE 0x10267020
// FUNCTION: ENGINE 0x10267040
// FUNCTION: ENGINE 0x10267050
// FUNCTION: ENGINE 0x10267090
// FUNCTION: ENGINE 0x102670A0
// FUNCTION: ENGINE 0x102670D0
// FUNCTION: ENGINE 0x102670F0
// FUNCTION: ENGINE 0x10267770
// FUNCTION: ENGINE 0x102677A0
// FUNCTION: ENGINE 0x102677C0
// FUNCTION: ENGINE 0x102677F0
// FUNCTION: ENGINE 0x10267810
// FUNCTION: ENGINE 0x10267840
// FUNCTION: ENGINE 0x10267860
// FUNCTION: ENGINE 0x10267890
// FUNCTION: ENGINE 0x102678B0
// FUNCTION: ENGINE 0x102678E0
// FUNCTION: ENGINE 0x10267900
// FUNCTION: ENGINE 0x10267950
// FUNCTION: ENGINE 0x102679A0
// FUNCTION: ENGINE 0x102679F0
// FUNCTION: ENGINE 0x10267A40
