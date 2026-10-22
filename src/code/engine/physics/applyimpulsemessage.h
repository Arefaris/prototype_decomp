// engine::ApplyImpulseMessage (RTTI name, namespace engine; type 3, id 0): in a header of its own because the unit of the
// hit reaction behaviour needs it without the other physics messages (they clash with those of gameobjectmessages.h).
#ifndef ENGINE_PHYSICS_APPLYIMPULSEMESSAGE_H
#define ENGINE_PHYSICS_APPLYIMPULSEMESSAGE_H

#include "code/engine/message.h"
#include "code/math/vector.h"

namespace engine
{
	// Pushes the physics object: the impulse and the world point it is applied at (member names guessed)
	struct ApplyImpulseMessage : public IntrusiveMessage
	{
		ApplyImpulseMessage(const math::Vector& newImpulse, const math::Vector& newPoint) : IntrusiveMessage(3, 0)
		{
			impulse.x = newImpulse.x;
			impulse.y = newImpulse.y;
			impulse.z = newImpulse.z;
			point.x = newPoint.x;
			point.y = newPoint.y;
			point.z = newPoint.z;
		}
		virtual ~ApplyImpulseMessage()
		{
		}

		math::Vector impulse;
		math::Vector point;
	};
}

#endif
