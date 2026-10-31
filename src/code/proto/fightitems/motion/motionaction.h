// What the actions of the motion fight items share: the track link and the object handle every action carries (the part of the
// actions' layout the engine's actions of 0x108F0370 and 0x108BA600 also have).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONACTION_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONACTION_H

#include "code/choreo/puppet.h"
#include "code/core/linklist.h"
#include "code/engine/fight/sequencer.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace engine
{
	// 0x107FC7A0: the handle of the object an effect or action runs on
	GameObjectHandle GetObjectHandle(core::IRefCount* object);
	// 0x100A0C40 / 0x100A0C60: this unit's copies of the helpers that release a driver (clearing the pointer) and replace one
	void ReleaseDriver(choreo::Driver*& driver);
	void AssignDriver(choreo::Driver*& driver, choreo::Driver* newDriver);
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
