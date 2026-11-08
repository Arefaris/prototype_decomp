// proto::AddTargetLockMessage and proto::RemoveTargetLockMessage (RTTI names; type 0x3B, ids 7 and 8): an object is told
// that another one locks onto it (or no longer does); the message carries the place the lock is kept at, and the added
// lock is answered in flag. The units that send them keep their own copies of these small classes.
#ifndef PROTO_BEHAVIOURS_TARGETLOCKMESSAGES_H
#define PROTO_BEHAVIOURS_TARGETLOCKMESSAGES_H

#include "code/proto/fightitems/ai/aicodemessages.h"

namespace engine
{
	class GameObject;
}

namespace proto
{
	struct AddTargetLockMessage : public TargetableMessage
	{
		explicit AddTargetLockMessage(engine::GameObject** newLock) : TargetableMessage(7), lock(newLock), flag(false)
		{
		}
		virtual ~AddTargetLockMessage()
		{
		}

		engine::GameObject** lock;  // +0xC
		bool flag;  // +0x10
	};

	struct RemoveTargetLockMessage : public TargetableMessage
	{
		explicit RemoveTargetLockMessage(engine::GameObject** newLock) : TargetableMessage(8), lock(newLock)
		{
		}
		virtual ~RemoveTargetLockMessage()
		{
		}

		engine::GameObject** lock;  // +0xC
	};
}

#endif
