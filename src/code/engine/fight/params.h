// fight::Params (RTTI name, 3 vftable slots - the reference counter's, base fight::RefCounted): what a fight node is
// created with. Its own unit is unknown; only the classes a behaviour touches are declared here. The value the
// constructor stores at +8 is the node's flags.
#ifndef ENGINE_FIGHT_PARAMS_H
#define ENGINE_FIGHT_PARAMS_H

#include "code/engine/fight/sequencer.h"

namespace fight
{
	class Params : public RefCounted
	{
	public:
		// 0x105AA820 (the fight params' unit)
		explicit Params(int value);
		// 0x105AA840 (0x105AA850 is the deleting destructor)
		virtual ~Params();
		int value;
	};
}

#endif
