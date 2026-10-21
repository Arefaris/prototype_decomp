// The fight conditions on the online session: the player's index and the number of players (unit 0x108B0840 and
// 0x108EEFF0 - 0x108EF780; no assert path, file name guessed).
#ifndef ENGINE_FIGHT_ONLINECONDITIONS_H
#define ENGINE_FIGHT_ONLINECONDITIONS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::OnlinePlayerIndexCondition (10 vftable slots, 0x14 bytes)
	class OnlinePlayerIndexCondition : public fight::Condition
	{
	public:
		// 0x108EF030
		OnlinePlayerIndexCondition();
		virtual ~OnlinePlayerIndexCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x1092CF50)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetCompare(int value);
		bool SetIndex(int value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		int compare;  // +0xC
		int index;  // +0x10
	};

	extern fight::Property** gOnlinePlayerIndexConditionProperties;
	// 0x108EF1B0
	// 0x108EF290
	fight::ConditionFactory* CreateOnlinePlayerIndexConditionFactory(const char* name);
	void RegisterOnlinePlayerIndexConditionFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::OnlineNumPlayersCondition (10 vftable slots, 0x14 bytes)
	class OnlineNumPlayersCondition : public fight::Condition
	{
	public:
		// 0x108EF390
		OnlineNumPlayersCondition();
		virtual ~OnlineNumPlayersCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x1092CFE0)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetCompare(int value);
		bool SetCount(int value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		int compare;  // +0xC
		int count;  // +0x10
	};

	extern fight::Property** gOnlineNumPlayersConditionProperties;
	// 0x108EF510
	// 0x108EF5F0
	fight::ConditionFactory* CreateOnlineNumPlayersConditionFactory(const char* name);
	void RegisterOnlineNumPlayersConditionFactory(fight::TrackRegistry* registry, const char* name);
}

#endif
