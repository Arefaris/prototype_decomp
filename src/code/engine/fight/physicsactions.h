// The actions of the physics and collision tracks and the decal and effect timer tracks (unit 0x108AAFB0 - 0x108AD070, no assert path; file name guessed). The tracks are in physicstracks.cpp and effecttimertracks.cpp.
#ifndef ENGINE_FIGHT_PHYSICSACTIONS_H
#define ENGINE_FIGHT_PHYSICSACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/physicstracks.h"
#include "code/engine/fight/effecttimertracks.h"
#include "code/engine/fight/effecttrack.h"

namespace engine
{
	// RTTI: engine::PhysicsEnableAction (9 vftable slots, size 0x30)
	class PhysicsEnableAction : public fight::Action
	{
	public:
		// 0x108ABB90
		PhysicsEnableAction(PhysicsEnableTrack* newTrack, GameObjectHandle newTarget);
		// 0x108AB560
		virtual ~PhysicsEnableAction();

		// vftable slot 5 (0x108ABC00)
		virtual bool Slot5(int arg, float value);
		// vftable slot 6 (0x108ABCE0)
		virtual void Slot6();

		core::Link<PhysicsEnableTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		bool unknown2c;  // +0x2C
	};

	// RTTI: engine::PhysicsDisallowSleepingAction (9 vftable slots, size 0x2C)
	class PhysicsDisallowSleepingAction : public fight::Action
	{
	public:
		// 0x108AC3A0
		PhysicsDisallowSleepingAction(PhysicsDisallowSleepingTrack* newTrack, GameObjectHandle newTarget);
		// 0x108AB910
		virtual ~PhysicsDisallowSleepingAction();

		// vftable slot 5 (0x108AC430)
		virtual bool Slot5(int arg, float value);
		// vftable slot 6 (0x108AC4B0)
		virtual void Slot6();

		core::Link<PhysicsDisallowSleepingTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};

	// RTTI: engine::PhysicsSetKeyframedAction (9 vftable slots, size 0x2C)
	class PhysicsSetKeyframedAction : public fight::Action
	{
	public:
		// 0x108AC200
		PhysicsSetKeyframedAction(PhysicsSetKeyframedTrack* newTrack, GameObjectHandle newTarget);
		// 0x108AB800
		virtual ~PhysicsSetKeyframedAction();

		// vftable slot 5 (0x108AC290)
		virtual bool Slot5(int arg, float value);

		core::Link<PhysicsSetKeyframedTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};

	// RTTI: engine::DeleteAllDecalsAction (9 vftable slots, size 0x28)
	class DeleteAllDecalsAction : public fight::Action
	{
	public:
		// 0x108AC870
		DeleteAllDecalsAction(DeleteAllDecalsTrack* newTrack, core::IRefCount* owner);
		// 0x108AC800
		virtual ~DeleteAllDecalsAction();

		// vftable slot 5 (0x108AC780)
		virtual bool Slot5(int arg, float value);

		core::Link<DeleteAllDecalsTrack> link;  // +0x1C
	};

	// RTTI: engine::SetEffectTimerAction (9 vftable slots, size 0x28)
	class SetEffectTimerAction : public fight::Action
	{
	public:
		// 0x108ACB00
		SetEffectTimerAction(SetEffectTimerTrack* newTrack, core::IRefCount* owner);
		// 0x108ACA80
		virtual ~SetEffectTimerAction();

		// vftable slot 5 (0x108ACB70)
		virtual bool Slot5(int arg, float value);

		core::Link<SetEffectTimerTrack> link;  // +0x1C
	};

	namespace animation
	{
		// RTTI: engine::animation::ShaderAnimationAction (9 vftable slots, size 0x2C)
		class ShaderAnimationAction : public fight::Action
		{
		public:
			// 0x108ACD50
			ShaderAnimationAction(ShaderAnimationTrack* newTrack, GameObjectHandle newTarget);
			// 0x108ACCC0
			virtual ~ShaderAnimationAction();

			// vftable slot 5 (0x108ACDE0)
			virtual bool Slot5(int arg, float value);
			// vftable slot 6 (0x108ACF90)
			virtual void Slot6();

			core::Link<ShaderAnimationTrack> link;  // +0x1C
			GameObjectHandle target;  // +0x28
		};

	}

}

#endif
