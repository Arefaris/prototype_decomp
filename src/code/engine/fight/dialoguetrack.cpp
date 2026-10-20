// The fight track that plays dialogue lines (RTTI: engine::DialogueTrack) and its action (unit 0x108A85A0 - 0x108A8E50; no assert path, file name guessed). The factory makers are in trackfactory.cpp.
#include "code/engine/fight/dialoguetrack.h"
#include "code/engine/fight/effecttrack.h"
#include <new>

namespace engine
{
	fight::Property** gDialogueTrackProperties;  // 0x11318180

	// FUNCTION: ENGINE 0x108A85A0
	bool DialogueTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108A85E0
	bool DialogueTrack::SetKillOnExit(bool newValue)
	{
		KillOnExit = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108A8600
	bool DialogueTrack::SetFrequency(float newValue)
	{
		Frequency = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108A8620
	bool DialogueTrack::SetInstanceFrequencySensitivity(float newValue)
	{
		InstanceFrequencySensitivity = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108A8640
	bool DialogueTrack::SetMinDelay(int newValue)
	{
		MinDelay = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108A8660
	bool DialogueTrack::SetMaxDelay(int newValue)
	{
		MaxDelay = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108A8680
	bool DialogueTrack::SetIfPlayerCanBeSeen(bool newValue)
	{
		IfPlayerCanBeSeen = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108A8750
	bool DialogueTrack::SetCharacterName(const char* newValue)
	{
		CharacterName = fight::ReplaceString(CharacterName, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x108A8770
	bool DialogueTrack::SetEventName(const char* newValue)
	{
		EventName = fight::ReplaceString(EventName, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x108A8790
	bool DialogueTrack::SetPlayOn(const char* newValue)
	{
		PlayOn = fight::ReplaceString(PlayOn, newValue);
		return true;
	}

	// FUNCTION: ENGINE 0x108A86A0
	fight::Property* DialogueTrack::GetProperty(int index)
	{
		return gDialogueTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108A86B0
	void DialogueTrack::ClearProperties()
	{
		fight::FreePropertyList(&gDialogueTrackProperties);
	}

	// FUNCTION: ENGINE 0x108A86C0
	// ctor stores: [('mov', 'dword', 20, '0'), ('mov', 'dword', 24, '0'), ('mov', 'dword', 28, '0'), ('mov', 'dword', 40, '0'), ('mov', 'dword', 44, '0'), ('mov', 'byte', 48, '0'), ('mov', 'byte', 49, '0'), ('mov', 'dword', 0, '0x10e7956c'), ('movss', 'dword', 16, '0.0f'), ('movss', 'dword', 32, '1.0f'), ('movss', 'dword', 36, '0.0f'), ('mov', 'dword', 12, '1')]
	DialogueTrack::DialogueTrack() : timeBegin(0.0f), CharacterName(0), EventName(0), PlayOn(0), Frequency(1.0f), InstanceFrequencySensitivity(0.0f), MinDelay(0), MaxDelay(0), KillOnExit(false), IfPlayerCanBeSeen(false)
	{
		unknownC = 1;  // TODO base member
	}

	// FUNCTION: ENGINE 0x108A8740
	float DialogueTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108A87B0
	float DialogueTrack::Slot10() const
	{
		return -1.0f;
	}

	// FUNCTION: ENGINE 0x108A8710
	DialogueTrack::~DialogueTrack()
	{
		delete[] CharacterName;
		delete[] EventName;
		delete[] PlayOn;
	}

	// FUNCTION: ENGINE 0x108A8A50
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void DialogueTrack::RegisterProperties()
	{
		if (gDialogueTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<DialogueTrack>("timeBegin", &DialogueTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyString<DialogueTrack>("CharacterName", &DialogueTrack::SetCharacterName);
			properties[1] = property;
			property = new fight::PropertyString<DialogueTrack>("EventName", &DialogueTrack::SetEventName);
			properties[2] = property;
			property = new fight::PropertyString<DialogueTrack>("PlayOn", &DialogueTrack::SetPlayOn);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<DialogueTrack>("Frequency", &DialogueTrack::SetFrequency);
			properties[4] = property;
			property = new fight::PropertyFloatConstRange<DialogueTrack>("InstanceFrequencySensitivity", &DialogueTrack::SetInstanceFrequencySensitivity);
			properties[5] = property;
			property = new fight::PropertyIntConstRange<DialogueTrack>("MinDelay", &DialogueTrack::SetMinDelay);
			properties[6] = property;
			property = new fight::PropertyIntConstRange<DialogueTrack>("MaxDelay", &DialogueTrack::SetMaxDelay);
			properties[7] = property;
			property = new fight::PropertyBool<DialogueTrack>("KillOnExit", &DialogueTrack::SetKillOnExit);
			properties[8] = property;
			property = new fight::PropertyBool<DialogueTrack>("IfPlayerCanBeSeen", &DialogueTrack::SetIfPlayerCanBeSeen);
			properties[9] = property;
			fight::RegisterPropertyList(properties, &gDialogueTrackProperties);
		}
	}

	template class fight::PropertyBool<DialogueTrack>;
	template class fight::PropertyFloatConstRange<DialogueTrack>;
	template class fight::PropertyIntConstRange<DialogueTrack>;
	template class fight::PropertyString<DialogueTrack>;


	int gDialogueActionCounter = 1;  // 0x111D54B8

	// FUNCTION: ENGINE 0x108A8CC0
	DialogueAction::DialogueAction(DialogueTrack* newTrack, GameObjectHandle newTarget, core::IRefCount* newOwner)
		: fight::Action(0x200 + (newTrack->KillOnExit ? 0x400 : 0)), target(newTarget), link(newTrack), owner(newOwner)
	{
		unknown30 = gDialogueActionCounter;
		if (++gDialogueActionCounter == 0)
		{
			gDialogueActionCounter = 1;
		}
	}

	// FUNCTION: ENGINE 0x108A8880
	DialogueAction::~DialogueAction()
	{
	}

	// FUNCTION: ENGINE 0x108A8E40
	fight::Action* DialogueTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new DialogueAction(this, GetObjectHandle(owner), owner);
	}
}
