// The actions of the expression, joint lock, puppet move and undamageable tracks (unit 0x108F4630 - 0x108F6660, no
// assert path; file name guessed). The tracks are in expressiontracks.cpp.
#include "code/engine/fight/expressionactions.h"
#include "code/engine/expressionmessages.h"
#include "code/engine/gameobject/gameobjectmessages.h"

namespace engine
{
	// What the owner is seen as: an IRefCount-derived object whose kind says which handle it holds
	struct ExpressionOwner : core::IRefCount
	{
		int unknown4;
		unsigned int kind;  // +0x8
		GameObjectHandle handle;  // +0xC
	};

	namespace animation
	{
		// FUNCTION: ENGINE 0x108F48C0
		EnableMotionTrackedExpressionAction::EnableMotionTrackedExpressionAction(EnableMotionTrackedExpressionTrack* newTrack, GameObjectHandle newTarget)
			: fight::Action(0xE00), link(newTrack), target(newTarget)
		{
		}

		// FUNCTION: ENGINE 0x108F4790
		EnableMotionTrackedExpressionAction::~EnableMotionTrackedExpressionAction()
		{
		}

		// FUNCTION: ENGINE 0x108F4950
		bool EnableMotionTrackedExpressionAction::Slot5(int arg, float value)
		{
			EnableMotionTrackedExpressionTrack* track = link.object;
			if (track != 0 && target.IsValid())
			{
				GameObject* object = target.Get();
				SetExpressionBlendingEnabledMessage message(true, track->blendDuration);
				object->SendMessage(&message);
			}
			return false;
		}

		// FUNCTION: ENGINE 0x108F4B20
		fight::Action* EnableMotionTrackedExpressionTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			GameObjectHandle handle = GetObjectHandle(owner);
			return new EnableMotionTrackedExpressionAction(this, handle);
		}

		// FUNCTION: ENGINE 0x108F49F0
		DisableMotionTrackedExpressionAction::DisableMotionTrackedExpressionAction(DisableMotionTrackedExpressionTrack* newTrack, GameObjectHandle newTarget)
			: fight::Action(0xE00), link(newTrack), target(newTarget)
		{
		}

		// FUNCTION: ENGINE 0x108F47D0
		DisableMotionTrackedExpressionAction::~DisableMotionTrackedExpressionAction()
		{
		}

		// FUNCTION: ENGINE 0x108F4A80
		bool DisableMotionTrackedExpressionAction::Slot5(int arg, float value)
		{
			DisableMotionTrackedExpressionTrack* track = link.object;
			if (track != 0 && target.IsValid())
			{
				GameObject* object = target.Get();
				SetExpressionBlendingEnabledMessage message(false, track->blendDuration);
				object->SendMessage(&message);
			}
			return false;
		}

		// FUNCTION: ENGINE 0x108F4B60
		fight::Action* DisableMotionTrackedExpressionTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			GameObjectHandle handle = GetObjectHandle(owner);
			return new DisableMotionTrackedExpressionAction(this, handle);
		}

		// FUNCTION: ENGINE 0x108F4D50
		ExpressionAnimationAction::ExpressionAnimationAction(ExpressionAnimationTrack* newTrack, GameObjectHandle newTarget)
			: fight::Action(0xE00), link(newTrack), target(newTarget)
		{
		}

		// FUNCTION: ENGINE 0x108F4C90
		ExpressionAnimationAction::~ExpressionAnimationAction()
		{
		}

		// FUNCTION: ENGINE 0x108F4C00
		void ExpressionAnimationAction::Slot6()
		{
		}

		// FUNCTION: ENGINE 0x108F4CC0
		bool ExpressionAnimationAction::Slot7(int arg, float value)
		{
			if (!target.IsValid())
			{
				return false;
			}
			return true;
		}

		// FUNCTION: ENGINE 0x108F4F00
		fight::Action* ExpressionAnimationTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			GameObjectHandle handle = GetObjectHandle(owner);
			return new ExpressionAnimationAction(this, handle);
		}

		// FUNCTION: ENGINE 0x108F5E20
		// EQUIVALENT: the engine stores the driver pointer after the three float members, ours before them; every other instruction is the engine's
		PuppetMoveAction::PuppetMoveAction(PuppetMoveTrack* newTrack, GameObjectHandle newTarget)
			: fight::Action(0xE00), link(newTrack), target(newTarget)
		{
			unknown2c = 0.0f;
			unknown30 = 0.0f;
			unknown34 = 0.0f;
			driver = 0;
		}

		// FUNCTION: ENGINE 0x108F5BF0
		PuppetMoveAction::~PuppetMoveAction()
		{
			ReleaseDriverCopy2(&driver);
		}

		// FUNCTION: ENGINE 0x108F6470
		fight::Action* PuppetMoveTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			GameObjectHandle handle = GetObjectHandle(owner);
			return new PuppetMoveAction(this, handle);
		}

		// FUNCTION: ENGINE 0x108F5B00
		void ReleaseJointDriver(choreo::Driver** driver)
		{
			if (*driver != 0)
			{
				(*driver)->Release();
				*driver = 0;
			}
		}

		// FUNCTION: ENGINE 0x108F6150
		JointLockAction::JointLockAction(JointLockTrack* newTrack, GameObjectHandle newTarget)
			: fight::Action(0xE00), link(newTrack), target(newTarget), driver(0)
		{
		}

		// FUNCTION: ENGINE 0x108F5CA0
		JointLockAction::~JointLockAction()
		{
			ReleaseJointDriver(&driver);
		}

		// FUNCTION: ENGINE 0x108F5D00
		void JointLockAction::Slot6()
		{
			if (driver != 0)
			{
				GameObject* object = target.Get();
				if (object != 0)
				{
					choreo::Puppet* puppet = GetPuppet(object);
					if (puppet != 0)
					{
						puppet->RemoveDriver(driver, false);
						ReleaseJointDriver(&driver);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x108F64B0
		fight::Action* JointLockTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			GameObjectHandle handle = GetObjectHandle(owner);
			return new JointLockAction(this, handle);
		}
	}

	// FUNCTION: ENGINE 0x108F64F0
	UndamageableAction::UndamageableAction(GameObjectHandle newTarget)
		: fight::Action(0x600), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x108F6510
	UndamageableAction::~UndamageableAction()
	{
	}

	// FUNCTION: ENGINE 0x108F6590
	bool UndamageableAction::Slot5(int arg, float value)
	{
		GameObject* object = target.Get();
		if (object == 0)
		{
			return false;
		}
		SetUndamageableMessage message(true);
		object->SendMessage(&message);
		return true;
	}

	// FUNCTION: ENGINE 0x108F6600
	void UndamageableAction::Slot6()
	{
		GameObject* object = target.Get();
		if (object != 0)
		{
			SetUndamageableMessage message(false);
			object->SendMessage(&message);
		}
	}

	// FUNCTION: ENGINE 0x108F6520
	// EQUIVALENT: block order and add ecx, 0xFFFF0000 where ours has sub ecx, 0x10000 (the same value); the engine keeps the null return
	// between the range test and the allocation, ours puts it last
	fight::Action* UndamageableTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		ExpressionOwner* trackOwner = (ExpressionOwner*)owner;
		if (trackOwner == 0 || trackOwner->kind - 0x10000 > 0x1ffff)
		{
			return 0;
		}
		GameObjectHandle handle = trackOwner->handle;
		return new UndamageableAction(handle);
	}
}
