// The actions of the object state tracks: velocity, simple message, transform and rotation attribute, puppet animation
// (unit 0x108EC9A0 - 0x108EE690, no assert path; file name guessed). The tracks are in objectstatetracks.cpp.
#include "code/engine/fight/objectstateactions.h"
#include "code/engine/attributemessage.h"
#include "code/engine/physics/physicsmessages.h"

namespace engine
{
	// The messages the simple message track sends, by its message index (0x111E23E0, 12 bytes each)
	extern IntrusiveMessage gSimpleMessages[];
	extern content::ObjectName gTransformName;
	// The name of the puppet attribute of a game object (0x112834F0)
	extern content::ObjectName gPuppetAttributeName;

	// FUNCTION: ENGINE 0x108ED410
	void GameObject::SetMatrixAttribute(const content::ObjectName& name, const math::Matrix& value)
	{
		BaseAttribute* attribute = FindAttribute(name);
		if (attribute != 0)
		{
			((Attribute<math::Matrix>*)attribute)->Get() = value;
			AttributeUpdatedMessage message(name);
			SendMessage(&message);
		}
	}

	// FUNCTION: ENGINE 0x108ECC60
	VelocityLinearAction::VelocityLinearAction(VelocityLinearTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x200), target(newTarget), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x108ECB30
	VelocityLinearAction::~VelocityLinearAction()
	{
	}

	// FUNCTION: ENGINE 0x108ECCE0
	// EQUIVALENT: shrink-wrap (the engine saves esi in the entry block, before the early-exit tests; ours after them and with a second epilogue); every other instruction is the engine's
	bool VelocityLinearAction::Slot5(int arg, float value)
	{
		if (link.object != 0 && target.IsValid())
		{
			GameObject* object = target.Get();
			float x = link.object->linearVelocity.x;
			float y = link.object->linearVelocity.y;
			float z = link.object->linearVelocity.z;
			if (link.object->operation == 1)
			{
				PhysicsGetLinearVelocityMessage query;
				object->PostMessage(&query);
				x = query.velocity.x + x;
				y = query.velocity.y + y;
				z = query.velocity.z + z;
			}
			PhysicsSetLinearVelocityMessage message(x, y, z);
			object->SendMessage(&message);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108ED010
	fight::Action* VelocityLinearTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new VelocityLinearAction(this, handle);
	}

	// FUNCTION: ENGINE 0x108ECE30
	VelocityAngularAction::VelocityAngularAction(VelocityAngularTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x200), link(newTrack), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x108ECB70
	VelocityAngularAction::~VelocityAngularAction()
	{
	}

	// FUNCTION: ENGINE 0x108ECEC0
	// EQUIVALENT: shrink-wrap (the engine saves esi in the entry block, before the early-exit tests; ours after them and with a second epilogue); every other instruction is the engine's
	bool VelocityAngularAction::Slot5(int arg, float value)
	{
		if (link.object != 0 && target.IsValid())
		{
			GameObject* object = target.Get();
			float x = link.object->angularVelocity.x;
			float y = link.object->angularVelocity.y;
			float z = link.object->angularVelocity.z;
			if (link.object->operation == 1)
			{
				PhysicsGetAngularVelocityMessage query;
				object->PostMessage(&query);
				x = query.velocity.x + x;
				y = query.velocity.y + y;
				z = query.velocity.z + z;
			}
			PhysicsSetAngularVelocityMessage message(x, y, z);
			object->SendMessage(&message);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108ED050
	fight::Action* VelocityAngularTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new VelocityAngularAction(this, handle);
	}

	// FUNCTION: ENGINE 0x108ED1B0
	SimpleMessageAction::SimpleMessageAction(SimpleMessageTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x200), target(newTarget), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x108ED120
	SimpleMessageAction::~SimpleMessageAction()
	{
	}

	// FUNCTION: ENGINE 0x108ED230
	bool SimpleMessageAction::Slot5(int arg, float value)
	{
		if (link.object != 0)
		{
			GameObject* object = target.Get();
			if (object != 0)
			{
				object->SendMessage(&gSimpleMessages[link.object->message]);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108ED280
	fight::Action* SimpleMessageTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new SimpleMessageAction(this, handle);
	}

	// FUNCTION: ENGINE 0x108ED650
	// EQUIVALENT: shrink-wrap (the engine saves edi in the entry block, before the early-exit tests; ours after them and with a second epilogue); every other instruction is the engine's
	bool SetRotationAttributeAction::Slot5(int arg, float value)
	{
		if (link.object != 0)
		{
			GameObject* object = target.Get();
			if (object != 0)
			{
				math::Vector axis = link.object->rotationAxis;
				axis.NormalizeFast();
				math::Matrix matrix;
				matrix.Identity();
				matrix.RotationAxisAngle(axis, link.object->rotationDegrees);
				object->SetMatrixAttribute(gTransformName, matrix);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108ED830
	fight::Action* SetRotationAttributeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new SetRotationAttributeAction(this, handle);
	}

	// FUNCTION: ENGINE 0x108ED5D0
	SetRotationAttributeAction::SetRotationAttributeAction(SetRotationAttributeTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x200), target(newTarget), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x108ED4A0
	SetRotationAttributeAction::~SetRotationAttributeAction()
	{
	}

	// FUNCTION: ENGINE 0x108ED770
	// EQUIVALENT: shrink-wrap (edi is saved in the entry block in the engine, after the early-exit tests in ours); the engine loads the three
	// angles before storing them as arguments (x, y, z, then stores z, y, x), ours loads and stores one at a time; every other instruction is the engine's
	bool SetTransformAttributeAction::Slot5(int arg, float value)
	{
		if (link.object != 0)
		{
			GameObject* object = target.Get();
			if (object != 0)
			{
				math::Matrix matrix;
				matrix.Identity();
				const math::Vector* angles = &link.object->rotationEulerAnglesXYZ;
				matrix.RotationEulerXYZ(angles->x, angles->y, angles->z);
				math::Vector position = link.object->transform;
				matrix.SetTranslation(position);
				object->SetTransform(matrix);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108ED870
	fight::Action* SetTransformAttributeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new SetTransformAttributeAction(this, handle);
	}

	// FUNCTION: ENGINE 0x108ED6F0
	SetTransformAttributeAction::SetTransformAttributeAction(SetTransformAttributeTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x200), target(newTarget), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x108ED4E0
	SetTransformAttributeAction::~SetTransformAttributeAction()
	{
	}

	// FUNCTION: ENGINE 0x108EDCE0
	PuppetAnimationAction::PuppetAnimationAction(fight::Track* listener, PuppetAnimationTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0xE00), watch(listener), link(newTrack), target(newTarget), driver(0), unknown3c(0.0f), unknown40(0)
	{
	}

	// FUNCTION: ENGINE 0x108EDB60
	PuppetAnimationAction::~PuppetAnimationAction()
	{
		ReleaseDriver(driver);
	}

	// FUNCTION: ENGINE 0x108EDBA0
	void PuppetAnimationAction::Slot6()
	{
		GameObject* object = target.Get();
		if (object != 0)
		{
			choreo::Puppet* puppet = 0;
			BaseAttribute* attribute = object->FindAttribute(gPuppetAttributeName);
			if (attribute != 0)
			{
				choreo::Puppet** value = &((Attribute<choreo::Puppet*>*)attribute)->value;
				if (value != 0 && *value != 0)
				{
					puppet = *value;
				}
			}
			if (driver != 0 && puppet != 0)
			{
				puppet->SetEndlessLifetime(driver, false, -1.0f);
				ReleaseDriverCopy(driver);
			}
		}
	}

	// FUNCTION: ENGINE 0x108EE670
	fight::Action* PuppetAnimationTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new PuppetAnimationAction(listener, this, handle);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108ECCC0
// FUNCTION: ENGINE 0x108ECEA0
// FUNCTION: ENGINE 0x108ED210
// FUNCTION: ENGINE 0x108ED630
// FUNCTION: ENGINE 0x108ED750
// FUNCTION: ENGINE 0x108EDD60
