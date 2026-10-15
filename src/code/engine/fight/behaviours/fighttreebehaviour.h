// engine::FightTreeBehaviour (RTTI name, vftable 0x10E7311C, 8 slots, base engine::Behaviour): the behaviour that
// runs a fight tree on its owner. It owns a fight::Sequencer at +0x18 and keeps what the tree's branches address by
// name at +0x60. Unit 0x108638C0 - 0x108642B7; the assert path of its debug dump names the file
// code/engine/fight/behaviours/fighttreebehaviour.cpp. Member and method names are guesses until the binary names
// them.
#ifndef ENGINE_FIGHT_BEHAVIOURS_FIGHTTREEBEHAVIOUR_H
#define ENGINE_FIGHT_BEHAVIOURS_FIGHTTREEBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/fight/sequencer.h"
#include "code/engine/gameobject/behaviour.h"

namespace engine
{
	// The node a fight tree runs in: a fight context whose handle slot (+0xC) the behaviour fills in (another unit)
	class FightTreeContext;

	class FightTreeBehaviour : public Behaviour
	{
	public:
		explicit FightTreeBehaviour(GameObject* newOwner);

		static content::ClassInfo* GetClassInfo();

		// vftable slot 0
		virtual void Slot0();
		// vftable slot 3: the base activation; deactivating stops the running actions
		virtual void OnActiveChanged(bool active);
		virtual void Update(float dt, unsigned short mask);
		virtual void OnPostedMessage(Message* message);
		virtual void OnMessage(Message* message);

		// 0x10863970 / 0x10863980: the actions the tree advances
		fight::Sequencer* GetSequencer();
		const fight::Sequencer* GetSequencer() const;
		// 0x10863B90: the branch (a fight::Track) the tree runs
		fight::Track* GetBranch() const;

		// The branch the tree runs (an intrusive list node of fight::Track) and two unknown members
		fight::Track* branch;
		int unknown10;
		int unknown14;
		// The actions the tree advances
		fight::Sequencer sequencer;
		// Padding up to the context pointer: the sequencer ends at +0x5C, the context sits at +0x60
		int unknown5C;
		// What the tree's branches address by name
		FightTreeContext* context;
	};
}

#endif
