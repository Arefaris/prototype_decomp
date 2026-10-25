#include "code/ravenphysics/physicsobject.h"
#include <new>

namespace ravenphysics
{
	// Copies the bounds of a volume into the object and into the detector's box of it (the maximum first)
	static __forceinline void TakeBounds(TriggerObject* object, const math::AABB* source)
	{
		const BroadPhaseBox* box = (const BroadPhaseBox*)source;
		object->bounds.Set(*box);
		if (object->detector != 0)
		{
			object->detector->boxes[object->detectorIndex].Set(*box);
		}
	}

	// FUNCTION: ENGINE 0x10677BC0
	// EQUIVALENT: the same test; the engine answers in eax (mov eax, 1), ours in al, 64.3 %
	bool TriggerObject::HasVolumeType(unsigned short type)
	{
		if (volume != 0 && volume->type == type)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10677BE0
	void CollisionObjectTable::AddTrigger(TriggerObject* object, int* id)
	{
		Add(object, reinterpret_cast<CollisionHandle*>(id));
	}

	// FUNCTION: ENGINE 0x10677BF0
	TriggerObject::TriggerObject()
	{
		gCollisionObjectTable->AddTrigger(this, &id);
	}

	// FUNCTION: ENGINE 0x10677C20
	int TriggerObject::GetUnknown48()
	{
		return unknown44;
	}

	// FUNCTION: ENGINE 0x10677C30
	TriggerObject::~TriggerObject()
	{
		gCollisionObjectTable->Remove(&id);
		if (volume != 0)
		{
			delete volume;
		}
	}

	// FUNCTION: ENGINE 0x10677C70
	TriggerObject* CreateTriggerFromBox(const BroadPhaseBox* box, const IntersectionFilter* filter)
	{
		TriggerObject* object = new TriggerObject;
		object->bounds.Set(*box);
		if (object->detector != 0)
		{
			object->detector->boxes[object->detectorIndex].Set(*box);
		}
		object->skipped = 1;
		object->SetCollisionMode(2);
		object->masks.unknown0 = filter->properties.unknown0;
		object->masks.unknown4 = filter->properties.unknown4;
		object->masks.unknown8 = filter->unknown8;
		if (object->detector != 0)
		{
			BroadPhaseMasks* entry = object->detector->masks + object->detectorIndex;
			entry->unknown0 = filter->properties.unknown0;
			entry->unknown4 = filter->properties.unknown4;
			entry->unknown8 = filter->unknown8;
		}
		object->volume = 0;
		object->unknown44 = 0;
		return object;
	}

	// FUNCTION: ENGINE 0x10677F90
	void TriggerObject::SetTransform(const math::Matrix& transform)
	{
		volume->UpdateBounds((CollisionObject*)&transform);
		TakeBounds(this, &volume->bounds);
		SetCollisionMode(2);
	}

	// FUNCTION: ENGINE 0x10678010
	void TriggerObject::SetCapsule(const math::Capsule& capsule, const math::Matrix& transform)
	{
		CollisionCapsule* shape = (CollisionCapsule*)volume;
		shape->SetCapsule(capsule);
		shape->UpdateWorld((CollisionObject*)&transform);
		TakeBounds(this, &volume->bounds);
		SetCollisionMode(2);
	}

	// FUNCTION: ENGINE 0x106780A0
	void TriggerObject::SetBox(const math::OBB& box, const math::Matrix& transform)
	{
		CollisionOBB* shape = (CollisionOBB*)volume;
		shape->SetOBB(box);
		shape->UpdateWorld((CollisionObject*)&transform);
		TakeBounds(this, &volume->bounds);
		SetCollisionMode(2);
	}

	// FUNCTION: ENGINE 0x10678130
	void TriggerObject::SetSphere(const math::Sphere& sphere, const math::Matrix& transform)
	{
		CollisionSphere* shape = (CollisionSphere*)volume;
		shape->SetSphere(sphere);
		shape->UpdateWorld((CollisionObject*)&transform);
		TakeBounds(this, &volume->bounds);
		SetCollisionMode(2);
	}

	// FUNCTION: ENGINE 0x106781C0
	void TriggerObject::SetPlane(const void* plane, const math::Matrix& transform)
	{
		CollisionPlane* shape = (CollisionPlane*)volume;
		shape->SetPlane(plane);
		shape->UpdateWorld((CollisionObject*)&transform);
		TakeBounds(this, &volume->bounds);
		SetCollisionMode(2);
	}

	// FUNCTION: ENGINE 0x10678250
	// EQUIVALENT: the same stores of the volume's two filter words in the other order, 92.5 %
	void TriggerObject::SetFilter(const IntersectionFilter* filter)
	{
		masks.unknown0 = filter->properties.unknown0;
		masks.unknown4 = filter->properties.unknown4;
		masks.unknown8 = filter->unknown8;
		if (detector != 0)
		{
			BroadPhaseMasks* entry = detector->masks + detectorIndex;
			entry->unknown0 = filter->properties.unknown0;
			entry->unknown4 = filter->properties.unknown4;
			entry->unknown8 = filter->unknown8;
		}
		CollisionVolume* shape = volume;
		if (shape != 0)
		{
			unsigned int second = filter->properties.unknown4;
			unsigned int first = filter->properties.unknown0;
			shape->filter.unknown0 = first;
			shape->filter.unknown4 = second;
		}
	}

	// FUNCTION: ENGINE 0x106782A0
	void TriggerObject::SetFilterBits(unsigned int mask, bool set)
	{
		BroadPhaseMasks updated = masks;
		if (set)
		{
			updated.unknown0 |= mask;
		}
		else
		{
			updated.unknown0 &= ~mask;
		}
		masks = updated;
		if (detector != 0)
		{
			detector->masks[detectorIndex] = updated;
		}
		if (volume != 0)
		{
			if (set)
			{
				volume->filter.unknown0 |= mask;
				return;
			}
			volume->filter.unknown0 &= ~mask;
		}
	}

	// FUNCTION: ENGINE 0x10678310
	void TriggerObject::SetFilterBits2(unsigned int mask, bool set)
	{
		BroadPhaseMasks updated = masks;
		if (set)
		{
			updated.unknown4 |= mask;
		}
		else
		{
			updated.unknown4 &= ~mask;
		}
		masks = updated;
		if (detector != 0)
		{
			detector->masks[detectorIndex] = updated;
		}
		if (volume != 0)
		{
			if (set)
			{
				volume->filter.unknown4 |= mask;
				return;
			}
			volume->filter.unknown4 &= ~mask;
		}
	}

	// FUNCTION: ENGINE 0x10677D50
	// EQUIVALENT: the same stores of the volume's two filter words in the other order, 95 %
	TriggerObject* CreateTriggerFromVolume(CollisionVolume* shape, const IntersectionFilter* filter)
	{
		TriggerObject* object = new TriggerObject;
		TakeBounds(object, &shape->bounds);
		object->skipped = 1;
		object->SetCollisionMode(2);
		object->masks.unknown0 = filter->properties.unknown0;
		object->masks.unknown4 = filter->properties.unknown4;
		object->masks.unknown8 = filter->unknown8;
		if (object->detector != 0)
		{
			BroadPhaseMasks* entry = object->detector->masks + object->detectorIndex;
			entry->unknown0 = filter->properties.unknown0;
			entry->unknown4 = filter->properties.unknown4;
			entry->unknown8 = filter->unknown8;
		}
		shape->swapped = 1;
		object->volume = shape;
		unsigned int second = filter->properties.unknown4;
		unsigned int first = filter->properties.unknown0;
		shape->filter.unknown0 = first;
		shape->filter.unknown4 = second;
		object->unknown44 = 0;
		return object;
	}

	// Kept copies: the deleting destructor
	// FUNCTION: ENGINE 0x10678380
}
