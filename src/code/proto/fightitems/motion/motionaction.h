// What the actions of the motion fight items share: the track link and the object handle every action carries (the part of the
// actions' layout the engine's actions of 0x108F0370 and 0x108BA600 also have).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONACTION_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONACTION_H

#include "code/choreo/puppet.h"
#include "code/choreo/rootdriver.h"
#include "code/math/quaternion.h"
#include "code/core/linklist.h"
#include "code/engine/fight/sequencer.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace engine
{
	// 0x107FC7A0: the handle of the object an effect or action runs on
	GameObjectHandle GetObjectHandle(core::IRefCount* object);
	// 0x100A0C40 / 0x100A0C60: this unit's copies of the helpers that release a driver (clearing the pointer) and replace one
	// 0x107F2010: the puppet of an object (the value of its puppet attribute), or null
	choreo::Puppet* GetPuppet(GameObject* object);
	// the player that controls an object, or -1
	int GetControllingPlayer(GameObject* object);
	void ReleaseDriver(choreo::Driver*& driver);
	void AssignDriver(choreo::Driver*& driver, choreo::Driver* newDriver);
}

namespace choreo
{
	// 0x10945B70: the inverse of the rotation of a matrix (name guess)
	math::Quaternion* InverseRotation(math::Quaternion* quaternion, const math::Matrix& matrix);
}

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// The owner the sequencer hands a condition in its third argument
			inline core::IRefCount* AsOwner(int value)
			{
				return reinterpret_cast<core::IRefCount*>(value);
			}
		}
	}
}

#endif
