// The exit track and the message conditions of the fight tree (unit 0x108B6C10 - 0x108B71F0; no assert path, file name guessed). The factory makers are in exitfactories.cpp.
#ifndef ENGINE_FIGHT_EXITTRACKS_H
#define ENGINE_FIGHT_EXITTRACKS_H

#include "code/engine/fight/trackfactory.h"
#include "code/engine/message.h"

namespace engine
{
	// RTTI: engine::ExitTrack (16 vftable slots, 0x1C bytes)
	class ExitTrack : public fight::Track
	{
	public:
		// 0x108B6C60
		ExitTrack();
		virtual ~ExitTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108B6CE0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetTimeEnd(float value);
		fight::ConditionList* GetConditions();

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		float timeEnd;  // +0x14
		fight::ConditionList conditions;  // +0x18
	};

	extern fight::Property** gExitTrackProperties;

	// What the message conditions compare a message against: the message's type and id sit at +0x10 and +0x14 of the
	// object the sequencer hands them (names guessed)
	struct MessageKey
	{
		int unknown0[4];
		int type;
		short id;
	};

	// The messages a condition can wait for: the type and id of each, and its name (0x111DA134, name guess)
	struct MessageTableEntry
	{
		int type;
		short id;
		short unknown6;
		const char* name;
	};

	extern const MessageTableEntry gMessageTable[];

	// RTTI: engine::MessageCondition (11 vftable slots, 0x10 bytes)
	class MessageCondition : public fight::Condition
	{
	public:
		// 0x108B6EA0
		MessageCondition();
		virtual ~MessageCondition()
		{
		}

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x108B6F20): the third argument is the message; one with a flag of 1 or 2 is matched
		virtual bool Evaluate(int a, int b, int c, int d);
		// vftable slot 10 (0x108B6F50): whether the message is the one the condition's type names
		virtual bool Matches(const MessageKey* key);

		// The members the properties write
		bool SetType(int value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		int type;  // +0xC
	};

	extern fight::Property** gMessageConditionProperties;

	// RTTI: engine::PrintMessageCondition (12 vftable slots, 0x18 bytes)
	class PrintMessageCondition : public engine::MessageCondition
	{
	public:
		// 0x108B7120
		PrintMessageCondition();
		virtual ~PrintMessageCondition()
		{
		}

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x108B7100)
		virtual bool Evaluate(int a, int b, int c, int d);
		// vftable slot 11 (0x108B7110)
		virtual bool Slot11(int arg);

		// The members the properties write
		bool SetMessage(const fight::Name& value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name message;  // +0x10
	};

	extern fight::Property** gPrintMessageConditionProperties;

}

#endif
