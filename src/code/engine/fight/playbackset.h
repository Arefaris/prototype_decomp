// engine::PlaybackSet (RTTI name, 18 vftable slots - the same as its base fight::Branch, 0x10E7B204): the branch of
// a fight tree that plays a playback. Its unit is not this one; only what the behaviours call is declared here.
#ifndef ENGINE_FIGHT_PLAYBACKSET_H
#define ENGINE_FIGHT_PLAYBACKSET_H

#include "code/engine/fight/branch.h"

namespace engine
{
	class GameObject;

	class PlaybackSet : public fight::Branch
	{
	public:
		// 0x108B0880 (another unit; a stub in this build): gives the set the object it plays on
		bool SetOwner(GameObject* newOwner);
	};
}

#endif
