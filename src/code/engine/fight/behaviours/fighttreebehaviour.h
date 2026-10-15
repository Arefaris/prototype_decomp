// engine::FightTreeBehaviour (RTTI name, vftable 0x10E7311C, 8 slots, base engine::Behaviour): the behaviour that
// runs a fight tree on its owner. It owns a fight::Sequencer at +0x18, the tree's parameters at +0x60 and the branch
// it runs at +0xC (the node of the branch's listener list). Unit 0x108638C0 - 0x108642B7; the assert path of its
// debug dump names the file code/engine/fight/behaviours/fighttreebehaviour.cpp. Member and method names are guesses
// until the binary names them.
#ifndef ENGINE_FIGHT_BEHAVIOURS_FIGHTTREEBEHAVIOUR_H
#define ENGINE_FIGHT_BEHAVIOURS_FIGHTTREEBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/fight/branch.h"
#include "code/engine/fight/sequencer.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobjectparams.h"
#include "code/engine/message.h"

namespace engine
{
	// The message the fight behaviours run branches with (message type 0xb; its class and members are guesses, the
	// two payloads share the word at +0xC because the ids tell them apart)
	struct FightTreeMessage : public Message
	{
		FightTreeMessage(int newType, short newId) : Message(newType, newId)
		{
		}

		union
		{
			// id 8: the track to look for in the running one's chain
			fight::Branch* track;
			// id 0x10: the parameters to fill in when the message carries none
			GameObjectParams* params;
		};
		// id 8: whether the chain is to be walked at all, and the answer
		bool walk;
		bool found;
	};

	class FightTreeBehaviour : public Behaviour
	{
	public:
		explicit FightTreeBehaviour(GameObject* newOwner, GameObjectParams* newParams);
		virtual ~FightTreeBehaviour();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 0 is the base's (empty), slot 2 its "still alive", slots 4 and 7 its update and destructor
		// vftable slot 1: the controller calls it when the object's flags changed; it refreshes the parameters'
		// handle and advances the engine's generator
		virtual void Slot1();
		// vftable slot 3: the base activation; deactivating stops the running actions
		virtual void OnActiveChanged(bool active);
		virtual void OnPostedMessage(Message* message);
		virtual void OnMessage(Message* message);

		// 0x108639A0: the parameters with the owner's handle written into them
		GameObjectParams* GetParams();

		// 0x10863970 / 0x10863980: the actions the tree advances
		fight::Sequencer* GetSequencer();
		const fight::Sequencer* GetSequencer() const;
		// 0x10863B90: the branch the tree runs
		fight::Branch* GetBranch() const;
		// 0x10863BA0: hands the branch to the sequencer's listener list and tells a playback set about it
		void SetBranch(fight::Branch* newBranch);
		// 0x10863C50: the "Fight Pre" dump of the tree
		void Dump(fight::Sequencer* sequencer, bool children, bool header, int indent);

		// The branch the tree runs (the node of the branch's listener list) and two unknown members
		fight::Branch* branch;
		int unknown10;
		int unknown14;
		// The actions the tree advances
		fight::Sequencer sequencer;
		// Padding up to the parameters: the sequencer ends at +0x5C, they sit at +0x60
		int unknown5C;
		// What the tree runs on
		GameObjectParams* params;
	};
}

#endif
