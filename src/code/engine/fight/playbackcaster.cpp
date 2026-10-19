// The playback track's factory caster constructor. A function compiled in the same unit as its callers would be
// known to them (the callers would use the register it returns its object in), so the engine's out-of-line copy is
// written apart from the unit that calls it.
#include "code/engine/fight/trackfactory.h"

namespace fight
{
	// FUNCTION: ENGINE 0x108079C0
	template<> TrackFactoryCasterTemplate<engine::PlaybackTrack>::TrackFactoryCasterTemplate()
	{
	}
}
