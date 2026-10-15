// engine::FightTreeBehaviour: see the header. The unit has no name of its own in the binary; the debug dump of the
// tree carries the file path code/engine/fight/behaviours/fighttreebehaviour.cpp.
#include "code/engine/fight/behaviours/fighttreebehaviour.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108638C0
	content::ClassInfo* FightTreeBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::FightTreeBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10863950
	void FightTreeBehaviour::OnActiveChanged(bool active)
	{
		Behaviour::OnActiveChanged(active);
		if (!active)
		{
			sequencer.EndPending();
		}
	}

	// FUNCTION: ENGINE 0x10863970
	fight::Sequencer* FightTreeBehaviour::GetSequencer()
	{
		return &sequencer;
	}

	// FUNCTION: ENGINE 0x10863980
	const fight::Sequencer* FightTreeBehaviour::GetSequencer() const
	{
		return &sequencer;
	}

	// FUNCTION: ENGINE 0x10863990
	void FightTreeBehaviour::Slot0()
	{
	}

	// FUNCTION: ENGINE 0x10863B90
	fight::Track* FightTreeBehaviour::GetBranch() const
	{
		return branch;
	}
}
