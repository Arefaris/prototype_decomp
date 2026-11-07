// engine::SetPropLogicStateMessage (RTTI): asks the logic tree of a prop to go to a state (split off
// gameobjectmessages.h for the units that need it beside the physics messages).
#ifndef ENGINE_GAMEOBJECT_SETPROPLOGICSTATEMESSAGE_H
#define ENGINE_GAMEOBJECT_SETPROPLOGICSTATEMESSAGE_H

#include "code/core/name.h"
#include "code/engine/message.h"

namespace engine
{
	// Asks the logic tree of a prop to go to a state (type 0xb); the constructor is in another unit (0x10259040)
	struct SetPropLogicStateMessage : public IntrusiveMessage
	{
		SetPropLogicStateMessage(core::Name<core::CaseSensitiveKey> newPrefix, const char* newState, bool newFlag,
			bool newOther, float newTime);
		// A state of the prop's tree by its prefix and name (inline: the prop spawner sends one per initial state)
		SetPropLogicStateMessage(core::Name<core::CaseSensitiveKey> newPrefix, core::Name<core::CaseSensitiveKey> newName,
			bool newFlag = false, bool newOther = true)
			: IntrusiveMessage(0xb, 5), prefix(newPrefix), stateName(newName)
		{
			state = 0;
			flag = newFlag;
			other = newOther;
			time = 0.0f;
			unknown2C = 0;
			succeeded = false;
		}

		// The same with the prefix given as text (the door trigger's)
		SetPropLogicStateMessage(const char* newPrefix, core::Name<core::CaseSensitiveKey> newName, bool newFlag,
			bool newOther)
			: IntrusiveMessage(0xb, 5), prefix(newPrefix, 1), stateName(newName)
		{
			state = 0;
			flag = newFlag;
			other = newOther;
			time = 0.0f;
			unknown2C = 0;
			succeeded = false;
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> prefix;
		core::Name<core::CaseSensitiveKey> stateName;
		const char* state;
		bool flag;
		bool other;
		float time;
		int unknown2C;
		bool succeeded;
		// The engine's names are 8-byte aligned, which rounds the message up to 0x38 bytes
		int unknown34;
	};
}

#endif
