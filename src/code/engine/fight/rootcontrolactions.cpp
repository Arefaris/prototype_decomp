// The actions of the root control, strafe adjust and steering tracks: see the header.
#include "code/engine/fight/rootcontrolactions.h"
#include "code/engine/fight/driverrefs.h"
#include "code/engine/gameobject/gameobjectmessages.h"
#include "code/engine/physics/supportinglimbmessages.h"

namespace engine
{
	choreo::Puppet* GetPuppet(GameObject* object);
	int GetLocoAxisA();
	int GetLocoAxisB();

	// FUNCTION: ENGINE 0x10931C30
	// NONMATCHING: the engine passes the object in ecx and the result pointer on the stack (a cdecl-style call), ours passes both in registers (54 %)
#ifdef NONMATCHING
	// What the character's input asks of the strafe: the sideways and the forward axis, both turned around and kept in [-1, 1]
	static math::Vector ReadStrafeInput(GameObject* object)
	{
		math::Vector result;
		CharacterQueryIntentionMessage message;
		object->SendMessage(&message);
		if (message.intention == 0)
		{
			result.x = 0.0f;
			result.y = 0.0f;
			result.z = -1.0f;
			return result;
		}
		float forward = -message.intention->GetAxis(GetLocoAxisA())->x;
		if (forward - -1.0f < 0.0f)
		{
			forward = -1.0f;
		}
		float clampedForward = forward;
		if (forward - 1.0f >= 0.0f)
		{
			clampedForward = 1.0f;
		}
		float sideways = -message.intention->GetAxis(GetLocoAxisB())->x;
		if (sideways - -1.0f < 0.0f)
		{
			sideways = -1.0f;
		}
		if (sideways - 1.0f >= 0.0f)
		{
			sideways = 1.0f;
		}
		result.x = sideways;
		result.y = 0.0f;
		result.z = clampedForward;
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x10932510
	CharacterSteerAction::CharacterSteerAction(CharacterSteerTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0xE00), link(newTrack), target(newTarget), driver(0), unknown30(5.0f)
	{
	}

	// FUNCTION: ENGINE 0x109320B0
	CharacterSteerAction::~CharacterSteerAction()
	{
		ReleaseDriverRef(driver);
	}

	// FUNCTION: ENGINE 0x109320E0
	void CharacterSteerAction::Slot6()
	{
		if (target.Get() != 0 && driver != 0)
		{
			GameObject* object = target.Get();
			if (object != 0)
			{
				choreo::Puppet* puppet = GetPuppet(object);
				if (puppet != 0)
				{
					puppet->SetEndlessLifetime(driver, false, -1.0f);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x109336A0
	fight::Action* CharacterSteerTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new CharacterSteerAction(this, handle);
	}

	// FUNCTION: ENGINE 0x10932CB0
	ControlRootAction::ControlRootAction(ControlRootTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0xE00), link(newTrack), driver(0), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x10932170
	ControlRootAction::~ControlRootAction()
	{
		ReleaseDriverRef(driver);
	}

	// FUNCTION: ENGINE 0x10932D20
	bool ControlRootAction::Slot5(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		GameObject* object = target.Get();
		choreo::Puppet* puppet = GetPuppet(object);
		AssignDriverRef(driver, new choreo::RootDriver);
		driver->SetMask((link.object->steeringEnabled ? 2 : 0) | (link.object->movementEnabled ? 1 : 0));
		float length = link.object->Slot10();
		puppet->SetDriver(driver, length, link.object->priority, 1.0f, link.object->blendInTime, link.object->blendOutTime, -1.0f);
		StickToSupportingSurfaceMessage message(true);
		object->SendMessage(&message);
		return true;
	}

	// FUNCTION: ENGINE 0x109321A0
	void ControlRootAction::Slot6()
	{
		if (driver != 0)
		{
			GameObject* object = target.Get();
			if (object != 0)
			{
				choreo::Puppet* puppet = GetPuppet(object);
				if (puppet != 0)
				{
					puppet->SetEndlessLifetime(driver, false, -1.0f);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x109336E0
	fight::Action* ControlRootTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new ControlRootAction(this, handle);
	}

	// FUNCTION: ENGINE 0x109330A0
	StrafeAdjustRootAction::StrafeAdjustRootAction(StrafeAdjustRootTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0xE00), link(newTrack), driver(0), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x10932210
	StrafeAdjustRootAction::~StrafeAdjustRootAction()
	{
		ReleaseDriverRef(driver);
	}

	// FUNCTION: ENGINE 0x109332B0
	// NONMATCHING: calls the strafe input helper, which does not match; the branch order is the engine's (the rest 69 %)
#ifdef NONMATCHING
	bool StrafeAdjustRootAction::Slot7(int arg, float value)
	{
		if (arg == 0)
		{
			if (driver != 0 && link.object != 0)
			{
				GameObject* object = target.Get();
				if (object != 0)
				{
					driver->SetDirection(ReadStrafeInput(object));
					return true;
				}
			}
			return false;
		}
		return true;
	}
#endif

	// FUNCTION: ENGINE 0x10932240
	void StrafeAdjustRootAction::Slot6()
	{
		if (driver != 0)
		{
			GameObject* object = target.Get();
			if (object != 0)
			{
				choreo::Puppet* puppet = GetPuppet(object);
				if (puppet != 0)
				{
					puppet->SetEndlessLifetime(driver, false, -1.0f);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10933720
	fight::Action* StrafeAdjustRootTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new StrafeAdjustRootAction(this, handle);
	}

	// FUNCTION: ENGINE 0x10933320
	ChoreoTestsAction::ChoreoTestsAction(ChoreoTestsTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0xE00), link(newTrack), poseDriver(0), restPoseDriver(0), copyDriver(0), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x109322B0
	ChoreoTestsAction::~ChoreoTestsAction()
	{
		ReleaseDriverRef(poseDriver);
		ReleaseDriverRef(restPoseDriver);
		ReleaseDriverRef(copyDriver);
	}

	// FUNCTION: ENGINE 0x10932300
	void ChoreoTestsAction::Slot6()
	{
		GameObject* object = target.Get();
		if (object != 0)
		{
			choreo::Puppet* puppet = GetPuppet(object);
			if (puppet != 0)
			{
				if (poseDriver != 0)
				{
					puppet->SetEndlessLifetime(poseDriver, false, -1.0f);
				}
				if (restPoseDriver != 0)
				{
					puppet->SetEndlessLifetime(restPoseDriver, false, -1.0f);
				}
				if (copyDriver != 0)
				{
					puppet->SetEndlessLifetime(copyDriver, false, -1.0f);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10933760
	fight::Action* ChoreoTestsTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new ChoreoTestsAction(this, handle);
	}
}
