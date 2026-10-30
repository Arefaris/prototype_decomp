// The actions of the light, teleport and spawn object tracks (unit 0x108F2C10 - 0x108F4550, no assert path; file name
// guessed). The tracks are in spawntracks.cpp.
#include "code/engine/fight/spawnactions.h"
#include "code/engine/gameobject/gameobjectsystem.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108F3400
	TeleportAction::TeleportAction(TeleportTrack* newTrack, GameObjectHandle newOwner)
		: fight::Action(0xE00), link(newTrack), owner(newOwner)
	{
		savedTransform.Identity();
	}

	// FUNCTION: ENGINE 0x108F34D0
	// EQUIVALENT: the engine loads the three angles onto the x87 stack (x, y, z) before storing them as arguments, ours loads and stores one at a time; every other instruction is the engine's
	bool TeleportAction::Slot5(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		GameObject* ownerObject = owner.Get();
		if (ownerObject == 0)
		{
			return false;
		}
		target = FindGameObject(link.object->object, *(const content::ObjectName*)"");
		GameObject* object = target.Get();
		if (object == 0)
		{
			return false;
		}
		savedTransform = object->transform->value;
		math::Matrix matrix = math::Matrix::IDENTITY;
		math::Vector position = link.object->offset;
		matrix.SetTranslation(position);
		const math::Vector* angles = &link.object->orientation;
		matrix.RotationEulerXYZ(angles->x, angles->y, angles->z);
		switch (link.object->space)
		{
		case 2:
		{
			AttributePtr<proto::PartLookup*> attribute = ownerObject->GetAttributePtr<proto::PartLookup*>(proto::gDrawableAttributeName);
			if (attribute.value != 0)
			{
				proto::PartLookup* lookup = *attribute.value;
				if (lookup != 0)
				{
					int part = lookup->FindPart(link.object->spaceJoint);
					if (part != 0xffff)
					{
						matrix.Multiply(matrix, lookup->matrices[part]);
					}
				}
			}
		}
		case 1:
			matrix.Multiply(matrix, ownerObject->transform->value);
			break;
		}
		object->SetTransform(matrix);
		return true;
	}

	// FUNCTION: ENGINE 0x108F3740
	void TeleportAction::Slot6()
	{
		GameObject* object = target.Get();
		if (object != 0 && link.object->restorePosition)
		{
			object->SetTransform(savedTransform);
		}
	}

	// FUNCTION: ENGINE 0x108F3310
	bool TeleportAction::Slot7(int arg, float value)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x108F3780
	fight::Action* TeleportTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		if (handle.Get() != 0)
		{
			return new TeleportAction(this, handle);
		}
		return 0;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108F3470
// FUNCTION: ENGINE 0x108F3490
