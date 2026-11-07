#include "code/engine/system/engineflags.h"

namespace engine
{
	// GLOBAL: ENGINE 0x1130DC64
	unsigned int gEngineFlags;

	// FUNCTION: ENGINE 0x10833E00
	bool HasEngineFlags(unsigned int mask)
	{
		return (gEngineFlags & mask) == mask;
	}

	// FUNCTION: ENGINE 0x10833E20
	void SetEngineFlags(unsigned int mask)
	{
		gEngineFlags |= mask;
	}

	// FUNCTION: ENGINE 0x10833E30
	void ClearEngineFlags(unsigned int mask)
	{
		gEngineFlags &= ~mask;
	}
}
