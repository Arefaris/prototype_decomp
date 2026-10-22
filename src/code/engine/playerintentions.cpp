#include "code/core/refptr.h"
#include "code/engine/controller/characterintentioninputmap.h"

namespace engine
{
	// The input map of each of the eight players (0x113154E8), and the two axes the locomotion intention reads
	// (0x11315510, 0x111C844C; names guessed)
	extern CharacterIntentionInputMap* gPlayerIntentionMaps[8];
	extern int gLocoAxisA;
	extern int gLocoAxisB;

	// FUNCTION: ENGINE 0x1085B810
	CharacterIntentionInputMap* GetPlayerIntentionMap(unsigned int playerIndex)
	{
		return gPlayerIntentionMaps[playerIndex];
	}

	// FUNCTION: ENGINE 0x1085B820
	int GetLocoAxisA()
	{
		return gLocoAxisA;
	}

	// FUNCTION: ENGINE 0x1085B830
	int GetLocoAxisB()
	{
		return gLocoAxisB;
	}

	// FUNCTION: ENGINE 0x1085BD10
	void SetPlayerIntentionMap(CharacterIntentionInputMap* map, unsigned int playerIndex)
	{
		core::RefAssign(gPlayerIntentionMaps[playerIndex], map);
	}
}

// FUNCTION: ENGINE 0x1085B940
