// engine::SetIntersectionPropertiesMessage (RTTI name, namespace engine; type 3): in a header of its own because the
// motion fight items need it together with the messages of gameobjectmessages.h, which clash with those of
// physicsmessages.h.
#ifndef ENGINE_PHYSICS_SETINTERSECTIONPROPERTIESMESSAGE_H
#define ENGINE_PHYSICS_SETINTERSECTIONPROPERTIESMESSAGE_H

#include "code/engine/message.h"

namespace engine
{
	// Sets what the object's collision tests include (id 10)
	struct SetIntersectionPropertiesMessage : public IntrusiveMessage
	{
		SetIntersectionPropertiesMessage(unsigned int newMask, bool newEnable, int newValue, bool newFlag)
			: IntrusiveMessage(3, 10)
		{
			mask = newMask;
			enable = newEnable;
			value = newValue;
			flag = newFlag;
		}
		virtual ~SetIntersectionPropertiesMessage()
		{
		}

		unsigned int mask;
		bool enable;
		int value;
		bool flag;
	};
}

#endif
