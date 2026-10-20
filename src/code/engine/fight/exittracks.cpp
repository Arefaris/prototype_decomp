// The exit track and the message conditions of the fight tree (unit 0x108B6C10 - 0x108B71F0; no assert path, file name guessed). The factory makers are in exitfactories.cpp.
#include "code/engine/fight/exittracks.h"

namespace engine
{
	fight::Property** gExitTrackProperties;  // 0x113183DC

	// FUNCTION: ENGINE 0x108B6C10
	bool ExitTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B6C20
	bool ExitTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B6C30
	fight::ConditionList* ExitTrack::GetConditions()
	{
		return &conditions;
	}

	// FUNCTION: ENGINE 0x108B6C40
	fight::Property* ExitTrack::GetProperty(int index)
	{
		return gExitTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108B6C50
	void ExitTrack::ClearProperties()
	{
		fight::FreePropertyList(&gExitTrackProperties);
	}

	// FUNCTION: ENGINE 0x108B6C60
	// ctor stores: [('movss', 'dword', 16, '0.0f'), ('mov', 'dword', 0, '0x10e7c62c'), ('movss', 'dword', 20, '-1.0f'), ('mov', 'dword', 12, '0')]
	ExitTrack::ExitTrack() : timeBegin(0.0f), timeEnd(-1.0f)
	{
		unknownC = 0;  // TODO base member
	}

	// FUNCTION: ENGINE 0x108B6CA0
	float ExitTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108B6CB0
	float ExitTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108B6CC0
	ExitTrack::~ExitTrack()
	{
	}

	// FUNCTION: ENGINE 0x108B6DC0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void ExitTrack::RegisterProperties()
	{
		if (gExitTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<ExitTrack>("timeBegin", &ExitTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<ExitTrack>("timeEnd", &ExitTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyConditionGroup<ExitTrack>("conditions", &ExitTrack::GetConditions);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gExitTrackProperties);
		}
	}

	template class fight::PropertyConditionGroup<ExitTrack>;
	template class fight::PropertyFloatConstRange<ExitTrack>;

	extern fight::EnumEntry gMessageConditionTypeTable[];

	fight::Property** gMessageConditionProperties;  // 0x113183E0

	// FUNCTION: ENGINE 0x108B6FA0
	bool MessageCondition::SetType(int newValue)
	{
		type = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B6F00
	fight::Property* MessageCondition::GetProperty(int index)
	{
		return gMessageConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108B6F10
	void MessageCondition::ClearProperties()
	{
		fight::FreePropertyList(&gMessageConditionProperties);
	}

	// FUNCTION: ENGINE 0x108B6EA0
	// ctor stores: [('mov', 'dword', 0, '0x10e7c7e4'), ('mov', 'dword', 12, '0')]
	MessageCondition::MessageCondition() : fight::Condition(0), type(0)
	{
	}

	// FUNCTION: ENGINE 0x108B6F20
	// EQUIVALENT: block order; the engine keeps the false return between the range test and the call, ours puts the call first
	bool MessageCondition::Evaluate(int a, int b, int c, int d)
	{
		const Message* message = (const Message*)c;
		// The id and the flags are read as one word: the flags must be 1 or 2
		if (message != 0 && *(const unsigned int*)&message->id - 0x10000 <= 0x1ffff)
		{
			return Matches((const MessageKey*)message);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108B6F50
	bool MessageCondition::Matches(const MessageKey* key)
	{
		int index = type;
		return key->type == gMessageTable[index].type && key->id == gMessageTable[index].id;
	}

	// FUNCTION: ENGINE 0x108B7040
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void MessageCondition::RegisterProperties()
	{
		if (gMessageConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyEnumConstList<MessageCondition>("type", gMessageConditionTypeTable, 8, &MessageCondition::SetType);
			properties[0] = property;
			fight::RegisterPropertyList(properties, &gMessageConditionProperties);
		}
	}

	template class fight::PropertyEnumConstList<MessageCondition>;

	fight::Property** gPrintMessageConditionProperties;  // 0x11318428

	// FUNCTION: ENGINE 0x108B7150
	bool PrintMessageCondition::SetMessage(const fight::Name& newValue)
	{
		message = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108B70D0
	fight::Property* PrintMessageCondition::GetProperty(int index)
	{
		return gPrintMessageConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108B70E0
	void PrintMessageCondition::ClearProperties()
	{
		fight::FreePropertyList(&gPrintMessageConditionProperties);
	}

	// FUNCTION: ENGINE 0x108B7120
	// ctor stores: [('mov', 'dword', 0, '0x10e7c8a4')]
	PrintMessageCondition::PrintMessageCondition()
	{
	}

	// FUNCTION: ENGINE 0x108B7100
	bool PrintMessageCondition::Evaluate(int a, int b, int c, int d)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x108B7110
	bool PrintMessageCondition::Slot11(int arg)
	{
		return true;
	}


	// FUNCTION: ENGINE 0x108B71E0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void PrintMessageCondition::RegisterProperties()
	{
		if (gPrintMessageConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyName<PrintMessageCondition>("Message", &PrintMessageCondition::SetMessage);
			properties[0] = property;
			fight::RegisterPropertyList(properties, &gPrintMessageConditionProperties);
		}
	}

	template class fight::PropertyName<PrintMessageCondition>;

}
