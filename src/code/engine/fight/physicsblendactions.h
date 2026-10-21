// The actions of the physics blend tracks (the code sits in 0x1092D040 - 0x1092D810, no assert path; file name guessed).
// The tracks are in physicsblend.cpp.
#ifndef ENGINE_FIGHT_PHYSICSBLENDACTIONS_H
#define ENGINE_FIGHT_PHYSICSBLENDACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/physicsblend.h"

namespace engine
{
	// RTTI: engine::PhysicsPoseBlendFactorAction (9 vftable slots, size 0x2C): blends the object's physics towards its
	// pose
	class PhysicsPoseBlendFactorAction : public fight::Action
	{
	public:
		// 0x1092D420
		PhysicsPoseBlendFactorAction(PhysicsPoseBlendFactorTrack* newTrack, GameObjectHandle newTarget);
		// 0x1092D320
		virtual ~PhysicsPoseBlendFactorAction();

		// vftable slot 5 (0x1092D4B0)
		virtual bool Slot5(int arg, float value);

		core::Link<PhysicsPoseBlendFactorTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};

	// RTTI: engine::PhysicsJointBlendFactorAction (9 vftable slots, size 0x2C): blends the physics of one joint
	class PhysicsJointBlendFactorAction : public fight::Action
	{
	public:
		// 0x1092D540
		PhysicsJointBlendFactorAction(PhysicsJointBlendFactorTrack* newTrack, GameObjectHandle newTarget);

		// vftable slot 5 (0x1092D610)
		virtual bool Slot5(int arg, float value);

		core::Link<PhysicsJointBlendFactorTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};
}

#endif
