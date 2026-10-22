// The messages the non-interactive sequence and light group tracks send to an object (RTTI names, namespace engine).
// The constructors are inline; the member names are guesses.
#ifndef ENGINE_NISMESSAGES_H
#define ENGINE_NISMESSAGES_H

#include "code/core/name.h"
#include "code/engine/message.h"

namespace fight
{
	class Branch;
}

namespace engine
{
	// Starts playing a branch of the fight tree on the object (type 0xB, id 2)
	struct PlayBranchMessage : public IntrusiveMessage
	{
		__forceinline PlayBranchMessage(fight::Branch* newBranch, int newPriority) : IntrusiveMessage(0xb, 2)
		{
			branch = newBranch;
			unknown10 = 0;
			priority = newPriority;
			unknown18 = true;
			unknown1C = 0;
			unknown20 = false;
		}
		virtual ~PlayBranchMessage()
		{
		}

		fight::Branch* branch;  // +0xC
		int unknown10;
		int priority;  // +0x14
		bool unknown18;
		int unknown1C;
		bool unknown20;
	};

	// Puts the object in a light group (type 9, id 5)
	struct SetLightGroupMessage : public IntrusiveMessage
	{
		explicit SetLightGroupMessage(const core::Name<core::CaseSensitiveKey>& newName) : IntrusiveMessage(9, 5), name(newName)
		{
		}
		virtual ~SetLightGroupMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	// A message to the non-interactive sequence player (type 0x17): the Lua natives nis_Load (id 0), nis_Play (id 1),
	// nis_Stop (id 5) and nis_Unload (id 8) send them to the sequence they name. The constructors are inline.
	struct NISMessage : public IntrusiveMessage
	{
		NISMessage(short newId, const core::Name<core::CaseSensitiveKey>& newName) : IntrusiveMessage(0x17, newId),
			name(newName)
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	// Starts the sequence (id 1); the start time is zero and the flag clear when a native sends it
	struct NISPlayMessage : public NISMessage
	{
		explicit NISPlayMessage(const core::Name<core::CaseSensitiveKey>& newName) : NISMessage(1, newName)
		{
			time = 0.0f;
			unknown1C = false;
		}

		float time;  // +0x18
		bool unknown1C;
	};
}

#endif
