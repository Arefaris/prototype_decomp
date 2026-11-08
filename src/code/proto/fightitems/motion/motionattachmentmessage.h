// The message that asks an object what it is attached to (declared by another unit of the engine; RTTI name, the constructor is inline there).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONATTACHMENTMESSAGE_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONATTACHMENTMESSAGE_H

#include "code/engine/message.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/core/name.h"
#include "code/engine/gameobject/gameobjectparams.h"
#include "code/engine/fightgetgameobjectparamsmessage.h"

namespace engine
{
	// 0x11283540: the name of the attribute that holds the handle of the object an object is attached to
	extern core::Name<core::CaseSensitiveKey> gAttachmentState;

	// RTTI: engine::AttachmentGetAttachmentStateMessage: the object answers with the handle of the object it is attached to (a
	// pointer to the handle, or null)
	struct AttachmentGetAttachmentStateMessage : public NonintrusiveMessage
	{
		AttachmentGetAttachmentStateMessage() : NonintrusiveMessage(0xf, 6), parent(0)
		{
		}
		virtual ~AttachmentGetAttachmentStateMessage()
		{
		}

		GameObjectHandle* parent;  // +0xC
	};
}

#endif
