#include "code/engine/effectparams.h"

namespace engine
{
	// FUNCTION: ENGINE 0x1089B580
	// EQUIVALENT: the engine stores the vftable right after the base constructor and loads the handle's address after the
	// first members, ours the other way round (scheduling), 63 %
	EffectParams::EffectParams(int value) : fight::Params(value), unknownC(-1), unknown10(0.0f), handle(), unknown18(0.0f),
		unknown1C(0), track(0), unknown24(0), unknown28(0), effect(0)
	{
	}

	// FUNCTION: ENGINE 0x1089B5D0
	EffectParams::~EffectParams()
	{
		core::SafeReleaseRef(effect);
		if (track != 0)
		{
			track->Unregister(&track);
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1089B600
