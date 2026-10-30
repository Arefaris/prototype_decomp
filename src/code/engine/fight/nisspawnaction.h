// engine::NISSpawnAction (RTTI name): the action that runs a non-interactive sequence node. Unit 0x108EC8B0 - 0x108ECC60
// (no assert path; file name guessed). Names other than the RTTI ones are guesses.
#ifndef ENGINE_FIGHT_NISSPAWNACTION_H
#define ENGINE_FIGHT_NISSPAWNACTION_H

#include "code/engine/fight/sequencer.h"
#include "code/engine/fight/branch.h"

namespace engine
{
	class StreamPackage;

	// 0x108A7CA0: the stream package of a non-interactive sequence node, found once by the node's name (the member
	// function of engine::NISNode, which the engine's other units declare)
	StreamPackage* __fastcall GetNISNodeStreamPackage(fight::Branch* node);

	// RTTI: engine::NISSpawnAction (9 vftable slots, size 0x40): follows the sequencer of a sequence node it spawned
	class NISSpawnAction : public fight::Action
	{
	public:
		// 0x108EC8E0
		NISSpawnAction(fight::Branch* node, core::IRefCount* newOwner);
		// 0x108EC940 (deleting destructor 0x108EC9C0)
		virtual ~NISSpawnAction();

		// vftable slot 3 (0x108EC8B0): the sequencer the action owns
		virtual fight::Sequencer* GetChild();
		// vftable slot 5 (0x108EC9A0), slot 6 (0x108EC8D0) and slot 7 (0x108EC8C0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		fight::BranchWatch watch;  // +0x1C
		core::IRefCount* owner;  // +0x28
		fight::Sequencer sequencer;  // +0x30
	};
}

#endif
