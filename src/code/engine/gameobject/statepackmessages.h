// The messages that move the state of a spawned object into a spawner and back (RTTI names; message type 0x16). A
// "pack" message asks the object to write one part of its state to the address it carries, an "unpack" message hands
// the object that part to take over. Parts: the health, the playback trees (the names of the trees' states), one
// generic byte. The member names are guesses.
#ifndef ENGINE_GAMEOBJECT_STATEPACKMESSAGES_H
#define ENGINE_GAMEOBJECT_STATEPACKMESSAGES_H

#include "code/container/arrayfixed.h"
#include "code/core/name.h"
#include "code/engine/message.h"

namespace engine
{
	struct HealthPackStateMessage : public NonintrusiveMessage
	{
		explicit HealthPackStateMessage(float* newHealth) : NonintrusiveMessage(0x16, 0), health(newHealth)
		{
		}

		float* health;  // +0xC
	};

	struct HealthUnPackStateMessage : public IntrusiveMessage
	{
		explicit HealthUnPackStateMessage(float* newHealth) : IntrusiveMessage(0x16, 1), health(newHealth)
		{
		}

		float* health;  // +0xC
	};

	typedef container::ArrayFixed<core::Name<core::CaseSensitiveKey>, 3> TreeNameList;

	struct PlaybackTreePackStateMessage : public IntrusiveMessage
	{
		explicit PlaybackTreePackStateMessage(TreeNameList* newNames) : IntrusiveMessage(0x16, 2), names(newNames)
		{
		}

		TreeNameList* names;  // +0xC
	};

	struct PlaybackTreeUnPackStateMessage : public IntrusiveMessage
	{
		// 0x102A71F0 (another unit)
		explicit PlaybackTreeUnPackStateMessage(TreeNameList* newNames);

		TreeNameList* names;  // +0xC
		float unknown10;  // +0x10
	};

	struct GenericBytePackStateMessage : public NonintrusiveMessage
	{
		explicit GenericBytePackStateMessage(unsigned char* newValue) : NonintrusiveMessage(0x16, 6), value(newValue)
		{
		}

		unsigned char* value;  // +0xC
	};

	struct GenericByteUnPackStateMessage : public IntrusiveMessage
	{
		explicit GenericByteUnPackStateMessage(unsigned char newValue) : IntrusiveMessage(0x16, 7), value(newValue)
		{
		}

		unsigned char value;  // +0xC
	};

	// Clears the logic trees of a prop (message type 0xB)
	struct PropLogicTreeClearMessage : public IntrusiveMessage
	{
		PropLogicTreeClearMessage() : IntrusiveMessage(0xb, 0xc)
		{
		}
	};
}

#endif
