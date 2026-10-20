// The actions of the physics and collision tracks and the decal and effect timer tracks (unit 0x108AAFB0 - 0x108AD070, no assert path; file name guessed). The tracks are in physicstracks.cpp and effecttimertracks.cpp.
#include "code/engine/fight/physicsactions.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108ABB90
	PhysicsEnableAction::PhysicsEnableAction(PhysicsEnableTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x600), link(newTrack), target(newTarget), unknown2c(false)
	{
	}

	// FUNCTION: ENGINE 0x108AB560
	PhysicsEnableAction::~PhysicsEnableAction()
	{
	}

	// FUNCTION: ENGINE 0x108AC540
	fight::Action* PhysicsEnableTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new PhysicsEnableAction(this, handle);
	}

	// FUNCTION: ENGINE 0x108AC3A0
	PhysicsDisallowSleepingAction::PhysicsDisallowSleepingAction(PhysicsDisallowSleepingTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x600), link(newTrack), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x108AB910
	PhysicsDisallowSleepingAction::~PhysicsDisallowSleepingAction()
	{
	}

	// FUNCTION: ENGINE 0x108AC6E0
	fight::Action* PhysicsDisallowSleepingTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new PhysicsDisallowSleepingAction(this, handle);
	}

	// FUNCTION: ENGINE 0x108AC200
	PhysicsSetKeyframedAction::PhysicsSetKeyframedAction(PhysicsSetKeyframedTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x200), link(newTrack), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x108AB800
	PhysicsSetKeyframedAction::~PhysicsSetKeyframedAction()
	{
	}

	// FUNCTION: ENGINE 0x108AC6A0
	fight::Action* PhysicsSetKeyframedTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new PhysicsSetKeyframedAction(this, handle);
	}

	// FUNCTION: ENGINE 0x108AC870
	DeleteAllDecalsAction::DeleteAllDecalsAction(DeleteAllDecalsTrack* newTrack, core::IRefCount* owner)
		: fight::Action(0xE00), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x108AC800
	DeleteAllDecalsAction::~DeleteAllDecalsAction()
	{
	}

	// FUNCTION: ENGINE 0x108AC8E0
	fight::Action* DeleteAllDecalsTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new DeleteAllDecalsAction(this, owner);
	}

	// FUNCTION: ENGINE 0x108ACB00
	SetEffectTimerAction::SetEffectTimerAction(SetEffectTimerTrack* newTrack, core::IRefCount* owner)
		: fight::Action(0xE00), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x108ACA80
	SetEffectTimerAction::~SetEffectTimerAction()
	{
	}

	// FUNCTION: ENGINE 0x108ACBA0
	fight::Action* SetEffectTimerTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new SetEffectTimerAction(this, owner);
	}

	namespace animation
	{
		// FUNCTION: ENGINE 0x108ACD50
		ShaderAnimationAction::ShaderAnimationAction(ShaderAnimationTrack* newTrack, GameObjectHandle newTarget)
			: fight::Action(0xE00), link(newTrack), target(newTarget)
		{
		}

		// FUNCTION: ENGINE 0x108ACCC0
		ShaderAnimationAction::~ShaderAnimationAction()
		{
		}

		// FUNCTION: ENGINE 0x108AD070
		fight::Action* ShaderAnimationTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			GameObjectHandle handle = GetObjectHandle(owner);
			return new ShaderAnimationAction(this, handle);
		}

	}

}
