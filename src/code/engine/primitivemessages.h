// The messages the primitive visibility and animation control tracks send to an object (RTTI names, namespace
// engine). The constructors are inline unless noted; the member names are guesses.
#ifndef ENGINE_PRIMITIVEMESSAGES_H
#define ENGINE_PRIMITIVEMESSAGES_H

#include "code/core/name.h"
#include "code/engine/message.h"

namespace engine
{
	// Shows or hides every primitive of the object's drawable (type 8, id 2)
	struct SetAllVisibilityMessage : public IntrusiveMessage
	{
		explicit SetAllVisibilityMessage(bool newVisible) : IntrusiveMessage(8, 2)
		{
			visible = newVisible;
		}
		virtual ~SetAllVisibilityMessage()
		{
		}

		bool visible;
	};

	// Shows or hides the named primitive (type 8, id 0)
	struct SetPrimitiveVisibilityMessage : public IntrusiveMessage
	{
		// 0x1046D720 (another unit's copy)
		SetPrimitiveVisibilityMessage(const core::Name<core::CaseSensitiveKey>& newName, bool newVisible, bool newFlag);
		virtual ~SetPrimitiveVisibilityMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> name;  // +0x10
		bool visible;  // +0x18
		bool flag;  // +0x19
		int unknown1C;
	};

	// Plays a range of the object's animation (type 0xA, id 1)
	struct AnimationControlMessage : public IntrusiveMessage
	{
		AnimationControlMessage(float newStartFrame, float newEndFrame, float newRelativeSpeed, int newCycleMode, int newNumCycles)
			: IntrusiveMessage(0xa, 1)
		{
			startFrame = newStartFrame;
			endFrame = newEndFrame;
			relativeSpeed = newRelativeSpeed;
			cycleMode = newCycleMode;
			numCycles = newNumCycles;
		}
		virtual ~AnimationControlMessage()
		{
		}

		float startFrame;  // +0xC
		float endFrame;  // +0x10
		float relativeSpeed;  // +0x14
		int cycleMode;  // +0x18
		int numCycles;  // +0x1C
	};
}

#endif
