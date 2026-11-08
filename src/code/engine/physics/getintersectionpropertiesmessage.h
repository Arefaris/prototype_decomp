// engine::GetIntersectionPropertiesMessage (RTTI name, namespace engine; type 3): in a header of its own because the
// magnetic boots unit needs it together with the messages of gameobjectmessages.h, which clash with those of
// physicsmessages.h.
#ifndef ENGINE_PHYSICS_GETINTERSECTIONPROPERTIESMESSAGE_H
#define ENGINE_PHYSICS_GETINTERSECTIONPROPERTIESMESSAGE_H

#include "code/engine/message.h"
#include "code/ravenphysics/intersectionproperties.h"

namespace engine
{
	// Asks for the intersection properties of the object (id 9)
	struct GetIntersectionPropertiesMessage : public NonintrusiveMessage
	{
		GetIntersectionPropertiesMessage() : NonintrusiveMessage(3, 9)
		{
			result = 0;
		}
		virtual ~GetIntersectionPropertiesMessage()
		{
		}

		ravenphysics::IntersectionProperties properties;  // +0xC (its constructor reads the physics library's defaults)
		int result;  // +0x14
	};
}

#endif
