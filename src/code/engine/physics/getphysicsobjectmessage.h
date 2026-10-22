// engine::GetPhysicsObjectMessage (RTTI name, namespace engine; type 3): in a header of its own because the unit of the
// health behaviour needs it without the other physics messages (they clash with those of gameobjectmessages.h).
#ifndef ENGINE_PHYSICS_GETPHYSICSOBJECTMESSAGE_H
#define ENGINE_PHYSICS_GETPHYSICSOBJECTMESSAGE_H

#include "code/engine/message.h"
#include "code/ravenphysics/context.h"

namespace engine
{
	// Asks for the object's physics object (id 0xB); the handle comes back in the message
	struct GetPhysicsObjectMessage : public NonintrusiveMessage
	{
		GetPhysicsObjectMessage() : NonintrusiveMessage(3, 0xb)
		{
			handle.value = 0xffffffff;
		}
		virtual ~GetPhysicsObjectMessage()
		{
		}

		ravenphysics::ObjectHandle handle;
	};
}

#endif
