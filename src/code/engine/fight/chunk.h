// fight::Chunk (RTTI name; 2 vftable slots at +0x10 and 18 at +0, base fight::Branch): the root branch of a loaded
// fight file. Only what the branch tree needs is declared here so far.
#ifndef ENGINE_FIGHT_CHUNK_H
#define ENGINE_FIGHT_CHUNK_H

#include "code/engine/fight/branch.h"

namespace fight
{
	class Chunk : public Branch
	{
	public:
		int unknown28;
		// The last index handed out to a branch of the chunk (0x105AAAB0 counts it up)
		int indexCounter;  // +0x2C
		// 0x105AAAB0
		int NextIndex();
	};
}

#endif
