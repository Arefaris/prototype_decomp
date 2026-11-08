// engine::FightGetGameObjectParamsMessage (RTTI name): the object answers the parameters its fight is created with (null
// when it has none).
#ifndef ENGINE_FIGHTGETGAMEOBJECTPARAMSMESSAGE_H
#define ENGINE_FIGHTGETGAMEOBJECTPARAMSMESSAGE_H

#include "code/engine/message.h"
#include "code/engine/gameobject/gameobjectparams.h"

namespace engine
{
	struct FightGetGameObjectParamsMessage : public NonintrusiveMessage
	{
		FightGetGameObjectParamsMessage() : NonintrusiveMessage(0xb, 0x10), params(0)
		{
		}
		virtual ~FightGetGameObjectParamsMessage()
		{
		}

		GameObjectParams* params;  // +0xC
	};
}

#endif
