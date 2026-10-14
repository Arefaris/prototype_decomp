// engine::StreamTriggerHull (RTTI: a reflected struct, no virtuals): a convex hull of planes. Only one accessor of
// the unit (0x108C6xxx - 0x108C7xxx) is reconstructed here; the rest is not done yet. Names are guesses.
namespace engine
{
	// The hull pool the unit works through (0x113188C8; name guessed)
	void* gStreamHullPool;

	// FUNCTION: ENGINE 0x108C7750
	void* GetStreamHullPool()
	{
		return gStreamHullPool;
	}
}
