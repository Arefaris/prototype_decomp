// The fight track that plays dialogue lines (RTTI: engine::DialogueTrack) and its action (unit 0x108A85A0 - 0x108A8E50; no assert path, file name guessed). The factory makers are in trackfactory.cpp.
#ifndef ENGINE_FIGHT_DIALOGUETRACK_H
#define ENGINE_FIGHT_DIALOGUETRACK_H

#include "code/core/linklist.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace engine
{
	// RTTI: engine::DialogueTrack (16 vftable slots, 0x34 bytes)
	class DialogueTrack : public fight::Track
	{
	public:
		// 0x108A86C0
		DialogueTrack();
		virtual ~DialogueTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (0x108A8E40)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write
		bool SetTimeBegin(float value);
		bool SetCharacterName(const char* value);
		bool SetEventName(const char* value);
		bool SetPlayOn(const char* value);
		bool SetFrequency(float value);
		bool SetInstanceFrequencySensitivity(float value);
		bool SetMinDelay(int value);
		bool SetMaxDelay(int value);
		bool SetKillOnExit(bool value);
		bool SetIfPlayerCanBeSeen(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		char* CharacterName;  // +0x14
		char* EventName;  // +0x18
		char* PlayOn;  // +0x1C
		float Frequency;  // +0x20
		float InstanceFrequencySensitivity;  // +0x24
		int MinDelay;  // +0x28
		int MaxDelay;  // +0x2C
		bool KillOnExit;  // +0x30
		bool IfPlayerCanBeSeen;  // +0x31
	};

	extern fight::Property** gDialogueTrackProperties;

	// RTTI: engine::DialogueAction (9 vftable slots, size 0x34): plays the line on the object; killed with it when the
	// track says so
	class DialogueAction : public fight::Action
	{
	public:
		// 0x108A8CC0
		DialogueAction(DialogueTrack* newTrack, GameObjectHandle newTarget, core::IRefCount* newOwner);
		// 0x108A8880
		virtual ~DialogueAction();

		// vftable slot 5 (0x108A8D60) and slot 6 (0x108A87C0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		GameObjectHandle target;  // +0x1C
		core::Link<DialogueTrack> link;  // +0x20
		core::IRefCount* owner;  // +0x2C
		int unknown30;
	};

	// The number the next dialogue action is given (0x111D54B8; name guess)
	extern int gDialogueActionCounter;
}

#endif
