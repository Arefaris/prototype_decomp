// fight::Action: the flag word of one node of a sequencer (see sequencer.h). SetFlag sits in its own unit so the
// sequencer's unit calls it without knowing which registers it keeps, as the original's callers did.
#include "code/engine/fight/sequencer.h"

namespace fight
{
	// FUNCTION: ENGINE 0x105A2440
	void Action::SetFlag(unsigned int flag, bool value)
	{
		if (value)
		{
			flags.all |= flag;
		}
		else
		{
			flags.all &= ~flag;
		}
	}
}
