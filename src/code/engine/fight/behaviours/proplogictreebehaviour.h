// engine::PropLogicTreeBehaviour (RTTI name, vftable 0x10E887B4, 8 slots, base engine::FightTreeBehaviour): the fight
// tree behaviour of the props' logic. It listens to the fight (0xB), health (0x14) and NIS (0x17) messages and
// names its sequencer after the "PropLogic" fight context. Unit 0x10921440 - 0x10921A10; no assert path names it, the
// file name is a guess.
#ifndef ENGINE_FIGHT_BEHAVIOURS_PROPLOGICTREEBEHAVIOUR_H
#define ENGINE_FIGHT_BEHAVIOURS_PROPLOGICTREEBEHAVIOUR_H

#include "code/engine/fight/behaviours/fighttreebehaviour.h"

namespace engine
{
	class PropLogicTreeBehaviour : public FightTreeBehaviour
	{
	public:
		// 0x109214F0
		explicit PropLogicTreeBehaviour(GameObject* newOwner);

		// 0x10921440 / 0x109215C0
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 4 (0x10921480): advances the sequencer, or stops listening when it has nothing to do
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x10921800)
		virtual void OnMessage(Message* message);
		// vftable slot 7: the compiler's scalar deleting destructor
	};
}

#endif
