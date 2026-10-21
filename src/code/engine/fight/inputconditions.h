// The fight conditions on the character input, the locomotion input and on a turn (unit 0x108F6660 - 0x108F7220; no assert path, file name guessed).
#ifndef ENGINE_FIGHT_INPUTCONDITIONS_H
#define ENGINE_FIGHT_INPUTCONDITIONS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::CharacterInputCondition (10 vftable slots, 0x24 bytes)
	class CharacterInputCondition : public fight::Condition
	{
	public:
		// 0x108F6790
		CharacterInputCondition();
		virtual ~CharacterInputCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x1092D830)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetButton(int value);
		// 0x1092D810 / 0x1092D820 (another unit): the entries of the enum and how many there are
		const fight::EnumEntry* GetButtonEntry(int index);
		int GetButtonCount();
		bool SetButtonState(int value);
		bool SetCompareTime(int value);
		bool SetTime(float value);
		bool SetCompareValue(int value);
		bool SetValue(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float time;  // +0xC
		float value;  // +0x10
		int button;  // +0x14
		int buttonState;  // +0x18
		int compareTime;  // +0x1C
		int compareValue;  // +0x20
	};

	extern fight::Property** gCharacterInputConditionProperties;
	// 0x108F6D10
	// 0x108F71C0
	fight::ConditionFactory* CreateCharacterInputConditionFactory(const char* name);
	void RegisterCharacterInputConditionFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::LocoInputCondition (10 vftable slots, 0x20 bytes)
	class LocoInputCondition : public fight::Condition
	{
	public:
		// 0x108F6800
		LocoInputCondition();
		virtual ~LocoInputCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x1092D960)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetInputType(int value);
		bool SetCompareTime(int value);
		bool SetTime(float value);
		bool SetCompareValue(int value);
		bool SetValue(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float time;  // +0xC
		float value;  // +0x10
		int compareTime;  // +0x14
		int compareValue;  // +0x18
		int inputType;  // +0x1C
	};

	extern fight::Property** gLocoInputConditionProperties;
	// 0x108F6D30
	// 0x108F71F0
	fight::ConditionFactory* CreateLocoInputConditionFactory(const char* name);
	void RegisterLocoInputConditionFactory(fight::TrackRegistry* registry, const char* name);

	// RTTI: engine::TurnInputCondition (10 vftable slots, 0x1C bytes)
	class TurnInputCondition : public fight::Condition
	{
	public:
		// 0x108F6870
		TurnInputCondition();
		virtual ~TurnInputCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x1092DAA0)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetPreviousDirection(int value);
		bool SetMinAngle(float value);
		bool SetMaxAngle(float value);
		bool SetRangeType(int value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float maxAngle;  // +0xC
		float minAngle;  // +0x10
		int previousDirection;  // +0x14
		int rangeType;  // +0x18
	};

	extern fight::Property** gTurnInputConditionProperties;
	// 0x108F6D50
	// 0x108F7220
	fight::ConditionFactory* CreateTurnInputConditionFactory(const char* name);
	void RegisterTurnInputConditionFactory(fight::TrackRegistry* registry, const char* name);

}

#endif
