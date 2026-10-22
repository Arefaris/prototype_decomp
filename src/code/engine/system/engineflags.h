// The engine's flag word (0x1130DC64): bits the game states and the online layer test and change. The functions are
// out of line in another unit (0x10833E00 - 0x10833E3C); every name is a guess.
#ifndef ENGINE_SYSTEM_ENGINEFLAGS_H
#define ENGINE_SYSTEM_ENGINEFLAGS_H

namespace engine
{
	// 0x10833E00: whether every bit of the mask is set
	bool HasEngineFlags(unsigned int mask);
	// 0x10833E20 / 0x10833E30
	void SetEngineFlags(unsigned int mask);
	void ClearEngineFlags(unsigned int mask);
}

#endif
