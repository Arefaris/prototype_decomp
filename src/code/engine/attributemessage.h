// engine::AttributeUpdatedMessage (RTTI name): sent to a game object when one of its attributes was written; it
// carries the attribute's name. Layout from the code that builds it on its stack: type 1, id 0, the name at +0x10.
#ifndef ENGINE_ATTRIBUTEMESSAGE_H
#define ENGINE_ATTRIBUTEMESSAGE_H

#include "code/core/name.h"
#include "code/engine/message.h"

namespace engine
{
	struct AttributeUpdatedMessage : public IntrusiveMessage
	{
		explicit AttributeUpdatedMessage(core::Name<core::CaseSensitiveKey> newName) : IntrusiveMessage(1, 0), name(newName)
		{
		}
		virtual ~AttributeUpdatedMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> name;
	};
}

#endif
