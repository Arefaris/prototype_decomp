// The action of the non-interactive sequence node spawn (unit 0x108EC8B0 - 0x108ECC60; no assert path, file name guessed).
#include "code/engine/fight/nisspawnaction.h"
#include "code/engine/fight/lodactions.h"
#include "code/engine/system/streampackage.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108EC8E0
	NISSpawnAction::NISSpawnAction(fight::Branch* node, core::IRefCount* newOwner)
		: fight::Action(0xF40), watch(node), owner(0)
	{
		AssignRefCounted(&owner, newOwner);
		flags.all &= 0xfffffffc;
	}

	// FUNCTION: ENGINE 0x108EC940
	NISSpawnAction::~NISSpawnAction()
	{
		if (watch.branch != 0 && owner != 0)
		{
			StreamPackage* package = GetNISNodeStreamPackage(watch.branch);
			if (package != 0)
			{
				package->Unload(0, false);
			}
		}
		core::SafeReleaseRef(owner);
		sequencer.End();
	}

	// FUNCTION: ENGINE 0x108EC8B0
	fight::Sequencer* NISSpawnAction::GetChild()
	{
		return &sequencer;
	}

	// FUNCTION: ENGINE 0x108EC9A0
	bool NISSpawnAction::Slot5(int arg, float value)
	{
		if (watch.branch == 0)
		{
			return false;
		}
		return sequencer.Unknown105A45A0(true);
	}

	// FUNCTION: ENGINE 0x108EC8D0
	void NISSpawnAction::Slot6()
	{
		sequencer.Reset();
	}

	// FUNCTION: ENGINE 0x108EC8C0
	bool NISSpawnAction::Slot7(int arg, float value)
	{
		return sequencer.Unknown105A45A0(true);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108EC9C0
