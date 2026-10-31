// What the actions of the motion fight items share: the track link and the object handle every action carries (the part of the
// actions' layout the engine's actions of 0x108F0370 and 0x108BA600 also have).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONACTION2_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONACTION2_H

#include "code/choreo/puppet.h"
#include "code/core/linklist.h"
#include "code/core/refptr.h"
#include "code/engine/fight/sequencer.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace engine
{
	// 0x107FC7A0: the handle of the object an effect or action runs on
	GameObjectHandle GetObjectHandle(core::IRefCount* object);
	// 0x107F2010: the puppet of an object (the value of its puppet attribute), or null
	choreo::Puppet* GetPuppet(GameObject* object);
	// 0x100A0C40: releases a driver and clears the pointer
	void ReleaseDriver(choreo::Driver*& driver);
	// 0x10098F50: stores a reference counted object in a slot, releasing the previous one
	void AssignRefCounted(core::IRefCount** slot, core::IRefCount* value);
	// 0x10098FB0: another unit's copy of the helper that releases a driver and clears the pointer
	void ReleaseDriverCopy2(choreo::Driver** driver);
	// 0x100ADA70: another copy of the same helper, taking the pointer by reference (name guess)
	void ReleaseDriverCopy3(choreo::Driver*& driver);
}

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// What the owner of a track's action is when it belongs to a game object: a reference counted object whose kind (0x10000 -
			// 0x2FFFF) says that the object handle is kept at +0xC (name guess)
			struct ActionOwner : core::IRefCount
			{
				int unknown4;
				unsigned int kind;  // +0x8
				engine::GameObjectHandle handle;  // +0xC
			};

			inline ActionOwner* AsActionOwner(core::IRefCount* owner)
			{
				ActionOwner* actionOwner = (ActionOwner*)owner;
				if (actionOwner == 0)
				{
					return 0;
				}
				return (actionOwner->kind - 0x10000 <= 0x1ffff) ? actionOwner : 0;
			}

			// The owner the sequencer hands a condition in its third argument
			inline core::IRefCount* AsOwner(int value)
			{
				return reinterpret_cast<core::IRefCount*>(value);
			}
		}
	}
}

#endif
