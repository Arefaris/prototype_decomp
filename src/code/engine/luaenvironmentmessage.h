// engine::GetLuaEnvironmentMessage (RTTI name, a NonintrusiveMessage, vftable 0x10E094C8): asks an object for its Lua
// environment; the answer is the reference of the environment table. The scripting unit and the scenario's Lua fight
// nodes both build it on the stack (the constructor is inline).
#ifndef ENGINE_LUAENVIRONMENTMESSAGE_H
#define ENGINE_LUAENVIRONMENTMESSAGE_H

#include "code/engine/message.h"

namespace engine
{
	struct GetLuaEnvironmentMessage : NonintrusiveMessage
	{
		GetLuaEnvironmentMessage() : NonintrusiveMessage(0xd, 9)
		{
			reference = 0;
		}
		virtual ~GetLuaEnvironmentMessage()
		{
		}

		int reference;
	};
}

#endif
