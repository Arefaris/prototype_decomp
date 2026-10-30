// The actions of the light, teleport and spawn object tracks (unit 0x108F2C10 - 0x108F4550, no assert path; file name
// guessed). The tracks are in spawntracks.cpp.
#include "code/engine/fight/spawnactions.h"
#include "code/engine/gameobject/gameobjectsystem.h"

namespace choreo
{
	extern const float gZero;
}

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}

	// Sends the light of an object the properties between the ones it started with and the ones of the track: t is the
	// share of the track's. Only the properties the track overrides are written. The engine passes the track in esi and
	// the start values in edi (a function of this unit only).
	// FUNCTION: ENGINE 0x108F2C90
	// EQUIVALENT: scheduling and the changed-mask in memory: the engine keeps the mask in eax across the blocks and loads the
	// four colour channels ahead of the arithmetic (every float operation is the engine's, in its order; 22 %)
	static bool BlendLight(GameObjectHandle handle, float t, const LightTrack* track, const GetLightPropertiesMessage* start)
	{
		GameObject* object = handle.Get();
		if (object == 0)
		{
			return false;
		}
		float rest = driving::gOne - t;
		SetLightPropertiesMessage message;
		if (track->colour)
		{
			math::Colour128 colour(track->colourColour.r * t + start->colour.r * rest,
				track->colourColour.g * t + start->colour.g * rest,
				track->colourColour.b * t + start->colour.b * rest,
				track->colourColour.a * t + start->colour.a * rest);
			message.colour = colour;
			message.changed |= 2;
		}
		if (track->intensity)
		{
			message.changed |= 4;
			message.intensity = start->intensity * rest + track->intensityIntensity * t;
		}
		if (track->shadowCaster)
		{
			message.shadowOffset = start->shadowOffset * rest + track->shadowCasterShadowOffset * t;
			message.shadowRadiusMultiplier = start->shadowRadiusMultiplier * rest + track->shadowCasterRadiusMultiplier * t;
			message.shadowRangeMultiplier = start->shadowRangeMultiplier * rest + track->shadowCasterRangeMultiplier * t;
			message.changed |= 0x1438;
			message.shadowMaxRadius = start->shadowMaxRadius * rest + track->shadowCasterMaxRadius * t;
			message.shadowCaster = true;
		}
		if (track->umbra)
		{
			message.umbra = start->umbra * rest + track->umbraUmbra * t;
			message.changed |= 0x300;
			message.penumbra = start->penumbra * rest + track->umbraPenumbra * t;
		}
		if (track->decay)
		{
			message.decayInner = start->decayInner * rest + track->decayInner * t;
			message.changed |= 0x40;
			message.decayOuter = start->decayOuter * rest + track->decayOuter * t;
		}
		object->SendMessage(&message);
		return true;
	}

	// FUNCTION: ENGINE 0x108F3060
	LightAction::LightAction(LightTrack* newTrack)
		: fight::Action(0xE00), link(newTrack)
	{
		elapsed = 0.0f;
	}

	// FUNCTION: ENGINE 0x108F2F60
	// EQUIVALENT: scheduling, the engine forms the address of the link before it stores the two vftables (88.1 %)
	LightAction::~LightAction()
	{
	}

	// FUNCTION: ENGINE 0x108F30F0
	bool LightAction::Slot5(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		target = FindGameObject(link.object->lightName, *(const content::ObjectName*)"");
		GameObject* object = target.Get();
		if (object != 0)
		{
			if (link.object->shadowCaster)
			{
				SetLightPropertiesMessage message;
				message.changed |= 0x400;
				message.shadowCaster = false;
				BroadcastMessage(&message);
			}
			if (unknown14 != choreo::gZero)
			{
				object->PostMessage(&start);
				return true;
			}
			BlendLight(target, 1.0f, link.object, &start);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108F2F90
	void LightAction::Slot6()
	{
		GameObject* object = target.Get();
		if (object != 0 && unknown14 != choreo::gZero)
		{
			SetLightPropertiesMessage message;
			message.changed |= 0x400;
			message.shadowCaster = false;
			object->SendMessage(&message);
		}
	}

	// FUNCTION: ENGINE 0x108F31D0
	bool LightAction::Slot7(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		elapsed += value;
		if (value != 0.0f)
		{
			float t;
			if (unknown14 == 0.0f)
			{
				t = driving::gOne;
			}
			else
			{
				float ratio = elapsed / unknown14;
				t = driving::gOne > ratio ? ratio : driving::gOne;
			}
			BlendLight(target, t, link.object, &start);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108F3260
	fight::Action* LightTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new LightAction(this);
	}

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
// FUNCTION: ENGINE 0x108F30D0
