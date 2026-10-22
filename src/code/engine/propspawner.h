// engine::PropSpawner (RTTI name; 13 vftable slots, bases GameObjectSpawner / content::MetaLoadObject): the spawner
// of the props a level places. Only what the PropBehaviour reads is declared so far: the spawner's position is the
// translation of the transform it inherits.
#ifndef ENGINE_PROPSPAWNER_H
#define ENGINE_PROPSPAWNER_H

#include "code/engine/gameobject/gameobjectspawner.h"

namespace engine
{
	class PropSpawner : public GameObjectSpawner
	{
	};
}

#endif
