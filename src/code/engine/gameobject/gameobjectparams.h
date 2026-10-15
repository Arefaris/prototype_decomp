// engine::GameObjectParams (RTTI name, 3 vftable slots, base fight::Params): the parameters of a fight node that
// belongs to a game object - the owner's handle at +0xC and two members nothing in this tree writes. Its unit is not
// this one (the constructor is 0x107FC710); only what the behaviours read is declared here.
#ifndef ENGINE_GAMEOBJECT_GAMEOBJECTPARAMS_H
#define ENGINE_GAMEOBJECT_GAMEOBJECTPARAMS_H

#include "code/engine/fight/params.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace engine
{
	class GameObjectParams : public fight::Params
	{
	public:
		explicit GameObjectParams(int value);

		// The object the parameters belong to (the class's constructor leaves it invalid)
		HandleBase handle;
		int unknown10;
		unsigned short unknown14;
	};
}

#endif
