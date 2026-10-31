// The reaction events the conditions and actions of the motion reaction items read (the events an object's reaction behaviour
// hands them: a hit, a grab, a throw, a scripted reaction). Kind 0x21000 + n; the class and member names are guesses from the users.
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONREACTION2_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONREACTION2_H

#include "code/core/name.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/vector.h"
#include "code/core/memory/imemoryallocator.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// The base of the reaction events: a reference counted object with its kind at +0x8
			struct ReactionEvent : core::IRefCount
			{
				int unknown4;
				int kind;  // +0x8
				engine::GameObjectHandle receiver;  // +0xC
			};

			// Kind 0x21001: a hit
			struct ReactionHitEvent : ReactionEvent
			{
				unsigned char unknown10[0x8];
				engine::GameObjectHandle giver;  // +0x18
				engine::GameObjectHandle unknown1C;  // +0x1C
				float charge;  // +0x20
				unsigned char unknown24[0x4];
				core::Name<core::CaseSensitiveKey> collisionFlag;  // +0x28
				unsigned char unknown30[0x1C];
				float damage;  // +0x4C
				float damageRatio;  // +0x50
				int attackType;  // +0x54
				core::Name<core::CaseSensitiveKey> hitType;  // +0x58
				int damageType;  // +0x60
				unsigned char unknown64[0x4];
				int unknown68;  // +0x68
				unsigned char unknown6C[0x4];
				math::Vector impulse;  // +0x70
				unsigned char unknown7C[0x8];
				bool muscleMass;  // +0x84
			};

			// Kind 0x21002: a grab
			struct ReactionGrabEvent : ReactionEvent
			{
				unsigned char unknown10[0x18];
				unsigned char isGrabbed;  // +0x28
			};

			// Kind 0x21003: a throw
			struct ReactionThrowEvent : ReactionEvent
			{
				unsigned char unknown10[0x8];
				engine::GameObjectHandle giver;  // +0x18
				unsigned char unknown1C[0x4];
				float charge;  // +0x20
				unsigned char unknown24[0x34];
				core::Name<core::CaseSensitiveKey> hitType;  // +0x58
			};

			// Kind 0x21004: a scripted reaction
			struct ReactionScriptedEvent : ReactionEvent
			{
				unsigned char unknown10[0x10];
				core::Name<core::CaseSensitiveKey> subType;  // +0x20
			};

			// Kind 0x21006: a supporting surface event
			struct SupportingSurfaceEvent : ReactionEvent
			{
				unsigned char unknown10[0x24];
				float x;  // +0x34
				float y;  // +0x38
				float z;  // +0x3C
				unsigned char unknown40[0xD];
				bool switchSurfaces;  // +0x4D
			};
		}
	}
}

#endif
