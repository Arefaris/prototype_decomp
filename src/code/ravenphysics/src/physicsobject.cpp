#include <new>

#include "code/core/debug.h"
#include "code/core/refptr.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/physicsobject.h"

#define PHYSICSOBJECT_FILE "..\\..\\..\\code\\ravenphysics\\src\\physicsobject.cpp"

// The check at the top of every function that touches the bodies while the library is simulating
#define NOT_LOCKED(line) OLD_ASSERT_AT(PHYSICSOBJECT_FILE, line, !gLock.IsLocked(), "!gLock.IsLocked()", "")

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x1065FCB0
	PhysicsLink::PhysicsLink()
	{
		refCount = 0;
		skeletonJointCount = 0;
		jointOfObject = 0;
		objectOfJoint = 0;
		pairMask = 0;
		joints = 0;
	}

	// FUNCTION: ENGINE 0x1065FCD0
	void PhysicsLink::AddRef()
	{
		refCount++;
	}

	// FUNCTION: ENGINE 0x1065FCE0
	void DoNothing()
	{
	}

	// FUNCTION: ENGINE 0x1065FCF0
	BroadPhaseBox* BoxArray::At(int index)
	{
		return items + index;
	}

	// FUNCTION: ENGINE 0x1065FD00
	math::Vector* VectorArray::At(int index)
	{
		return items + index;
	}

	// FUNCTION: ENGINE 0x1065FD10
	BroadPhaseMasks* MaskArray::At(int index)
	{
		return items + index;
	}

	// FUNCTION: ENGINE 0x1065FD20
	void CollisionObjectTable::AddPhysicsObject(PhysicsObject* object, int* id)
	{
		Add(object, reinterpret_cast<CollisionHandle*>(id));
	}

	// FUNCTION: ENGINE 0x1065FB20
	// EQUIVALENT: the engine loads the pointer into edx ahead of the add, ours folds the argument from the stack
	// into it (14.3 %); the same reads and writes
	void SetBit(unsigned char* bits, unsigned int index, bool value)
	{
		unsigned char* byte = (index >> 3) + bits;
		unsigned char mask = 1 << (index & 7);
		if (value)
		{
			*byte |= mask;
		}
		else
		{
			*byte &= ~mask;
		}
	}

	// FUNCTION: ENGINE 0x1065FB50
	unsigned int CountPairs(int n)
	{
		return (unsigned int)((n - 1) * n) >> 1;
	}

	// FUNCTION: ENGINE 0x1065FC30
	// EQUIVALENT: the engine keeps the smaller index in ecx and the count in eax, ours the other way round; the
	// same operations in the same order (72.7 %)
	int GetPairIndex(int count, unsigned int first, unsigned int second)
	{
		unsigned short low;
		unsigned short high;
		if (first < second)
		{
			low = first;
			high = second;
		}
		else
		{
			low = second;
			high = first;
		}
		unsigned int last = count - 2;
		unsigned int rest = last - low;
		return ((((last + 1) * last) - ((rest + 1) * rest)) >> 1) + high - 1;
	}

	// FUNCTION: ENGINE 0x10661040
	PhysicsObject* PhysicsObject::Create(CollisionObject* object)
	{
		NOT_LOCKED(52);
		PhysicsObject* body = new PhysicsObject;
		body->skipped = false;
		body->objectCount = 0;
		if (object->shape != 0)
		{
			body->SetCollisionMode(2);
		}
		else
		{
			body->SetCollisionMode(0);
		}
		body->masks.unknown0 = object->properties.unknown0;
		body->masks.unknown4 = object->properties.unknown4;
		body->StoreMasks();
		body->name = object->name;
		body->unknown48 = 0;
		body->unknown4C = 1.0f;
		body->unknown50 = 2;
		body->objectCount = 1;
		body->link = 0;
		body->objects = new CollisionObject*[1];
		body->objects[0] = object;
		body->jointCount = 0;
		body->joints = 0;
		body->UpdateBounds();
		object->owner = body;
		return body;
	}

	// FUNCTION: ENGINE 0x10661140
	PhysicsObject* CreatePhysicsObject(CollisionVolume* volume, bool flag, float size)
	{
		return PhysicsObject::Create(CreateCollisionObject(volume, flag, size));
	}

	// FUNCTION: ENGINE 0x10661170
	PhysicsObject* PhysicsObject::Create(CollisionObject** newObjects, unsigned int count, PhysicsLink* newLink)
	{
		NOT_LOCKED(112);
		JointSet* jointSet = 0;
		if (newLink)
		{
			jointSet = newLink->joints;
		}
		PhysicsObject* body = new PhysicsObject;
		body->skipped = false;
		body->objects = newObjects;
		body->objectCount = count;
		body->SetCollisionMode(2);
		for (unsigned int i = 0; i < count; i++)
		{
			if (newObjects[i]->shape == 0)
			{
				body->SetCollisionMode(0);
				break;
			}
		}
		for (unsigned int i = 0; i < count; i++)
		{
			newObjects[i]->owner = body;
		}
		body->SetUnknown48(0);
		body->unknown4C = 1.0f;
		body->unknown50 = 2;
		body->UpdateFilters();
		if (newLink)
		{
			body->link = newLink;
			newLink->AddRef();
		}
		else
		{
			body->link = 0;
		}
		body->jointCount = jointSet ? jointSet->Count() : 0;
		body->joints = jointSet ? jointSet->CreateJoints(body) : 0;
		body->UpdateBounds();
		return body;
	}

	// FUNCTION: ENGINE 0x1065FF00
	PhysicsObject::PhysicsObject()
	{
		NOT_LOCKED(184);
		gCollisionObjectTable->AddPhysicsObject(this, &id);
	}

	// FUNCTION: ENGINE 0x10661420
	PhysicsObject::~PhysicsObject()
	{
		NOT_LOCKED(191);
		gCollisionObjectTable->Remove(&id);
		if (joints != 0)
		{
			for (unsigned int i = 0; i != jointCount; i++)
			{
				delete joints[i];
			}
			delete[] joints;
		}
		for (unsigned int i = 0; i != objectCount; i++)
		{
			CollisionObject* object = objects[i];
			if (object != 0)
			{
				object->~CollisionObject();
				operator delete(object);
			}
		}
		delete[] objects;
		if (link != 0)
		{
			link->Release();
		}
	}

	// FUNCTION: ENGINE 0x1065F8C0
	void PhysicsObject::CheckBounds()
	{
		NOT_LOCKED(254);
		for (unsigned int i = 0; i < objectCount; i++)
		{
			CollisionObject* object = objects[i];
			if ((object->state & 0x80000000) != 0)
			{
				for (unsigned int j = 0; j < object->volumeCount; j++)
				{
					const math::Vector* bounds = &object->volumes[j]->bounds.min;
					if (!(this->bounds.boundsMax.x >= bounds[1].x && bounds[0].x >= this->bounds.boundsMin.x
						&& this->bounds.boundsMax.y >= bounds[1].y
						&& bounds[0].y >= this->bounds.boundsMin.y && this->bounds.boundsMax.z >= bounds[1].z
						&& bounds[0].z >= this->bounds.boundsMin.z))
					{
						Print();
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1065F9B0
	void PhysicsObject::SetUnknown48(int value)
	{
		unknown48 = value;
	}

	// FUNCTION: ENGINE 0x1065F9C0
	void PhysicsObject::SetCollisionModeOne()
	{
		SetCollisionMode(1);
	}

	// FUNCTION: ENGINE 0x1065F9D0
	bool PhysicsObject::HasVolumeType(unsigned short type)
	{
		for (unsigned int i = 0; i != objectCount; i++)
		{
			if (objects[i]->HasVolumeType(type))
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1065FA10
	void PhysicsObject::SetPairMask(const unsigned char* mask, unsigned int size)
	{
		link->pairMask = new unsigned char[size];
		for (unsigned int i = 0; i < size; i++)
		{
			link->pairMask[i] = mask[i];
		}
	}

	// FUNCTION: ENGINE 0x1065FA50
	void PhysicsObject::NotifyJoints(const void* argument)
	{
		if (joints != 0)
		{
			for (unsigned int i = 0; i < jointCount; i++)
			{
				if (joints[i] != 0)
				{
					joints[i]->SetQuery(argument);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1065FAA0
	void PhysicsObject::SetMaterial(unsigned char material)
	{
		NOT_LOCKED(905);
		for (unsigned int i = 0; i < objectCount; i++)
		{
			objects[i]->SetMaterial(material);
		}
	}

	// FUNCTION: ENGINE 0x1065FB60
	void PhysicsObject::ForEachPair(int a, int b, int c, int d)
	{
		if (objectCount >= 2)
		{
			PhysicsLink* pairs = link;
			unsigned int bit = 0;
			for (unsigned int i = 0; i + 1 != objectCount; i++)
			{
				CollisionObject* first = objects[i];
				for (unsigned int j = i + 1; j != objectCount; j++)
				{
					if ((pairs->pairMask[bit >> 3] & (1 << (bit & 7))) != 0)
					{
						ProcessObjectPair(this, first, objects[j], a, b, c, d);
					}
					bit++;
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1065FC80
	int PhysicsObject::GetActiveCount()
	{
		int count = 0;
		for (unsigned int i = 0; i < objectCount; i++)
		{
			if ((objects[i]->state & 0x80000000) != 0)
			{
				count++;
			}
		}
		return count;
	}

	// FUNCTION: ENGINE 0x1065FD80
	void BroadPhaseDetector::SetBox(unsigned short index, const BroadPhaseBox* box)
	{
		BroadPhaseBox* entry = boxes + index;
		entry->boundsMax.x = box->boundsMax.x;
		entry->boundsMax.y = box->boundsMax.y;
		entry->boundsMax.z = box->boundsMax.z;
		entry->boundsMin.x = box->boundsMin.x;
		entry->boundsMin.y = box->boundsMin.y;
		entry->boundsMin.z = box->boundsMin.z;
	}

	// FUNCTION: ENGINE 0x1065FDC0
	void BroadPhaseDetector::SetMasks(unsigned short index, const BroadPhaseMasks* newMasks)
	{
		BroadPhaseMasks* entry = masks + index;
		entry->unknown0 = newMasks->unknown0;
		entry->unknown4 = newMasks->unknown4;
		entry->unknown8 = newMasks->unknown8;
	}

	// FUNCTION: ENGINE 0x1065FDF0
	void PhysicsObject::SetBounds(const BroadPhaseBox* box)
	{
		bounds.Set(*box);
		if (detector != 0)
		{
			BroadPhaseBox* entry = detector->boxes + detectorIndex;
			entry->Set(*box);
		}
	}

	// FUNCTION: ENGINE 0x1065FE90
	void PhysicsObject::SetFilterWords(const int* words)
	{
		masks.unknown0 = words[0];
		masks.unknown4 = words[1];
		StoreMasks();
	}

	// FUNCTION: ENGINE 0x1065FED0
	void CollisionObject::TransformBy(const math::Matrix& matrix)
	{
		math::Matrix result;
		result.Multiply(transform, matrix);
		SetTransform(result);
	}

	// FUNCTION: ENGINE 0x1065FF70
	int PhysicsObject::GetUnknown48()
	{
		return unknown48;
	}

	// FUNCTION: ENGINE 0x1065FF80
	void PhysicsObject::SetName(core::Name<core::CaseSensitiveKey> newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x1065FF90
	void PhysicsObject::UpdateFilters()
	{
		NOT_LOCKED(361);
		IntersectionProperties combined;
		combined.unknown0 = 0;
		combined.unknown4 = 0;
		for (unsigned int i = 0; i < objectCount; i++)
		{
			IntersectionProperties* other = &objects[i]->properties;
			combined.unknown0 |= other->unknown0;
			combined.unknown4 |= other->unknown4;
		}
		masks.SetProperties(combined);
		StoreMasks();
	}

	// FUNCTION: ENGINE 0x10660050
	void PhysicsObject::SetFilter(const BroadPhaseMasks* newMasks)
	{
		NOT_LOCKED(387);
		CollisionFilter filter;
		filter.unknown0 = newMasks->unknown0;
		filter.unknown4 = newMasks->unknown4;
		for (unsigned int i = 0; i < objectCount; i++)
		{
			unsigned int volumeCount = objects[i]->volumeCount;
			for (unsigned int j = 0; j < volumeCount; j++)
			{
				objects[i]->volumes[j]->SetFilter(&filter);
			}
			CollisionObject* object = objects[i];
			object->properties.unknown0 = filter.unknown0;
			object->properties.unknown4 = filter.unknown4;
		}
		masks.unknown0 = newMasks->unknown0;
		masks.unknown4 = newMasks->unknown4;
		masks.unknown8 = newMasks->unknown8;
		if (detector != 0)
		{
			BroadPhaseMasks* entry = detector->masks + detectorIndex;
			entry->unknown0 = newMasks->unknown0;
			entry->unknown4 = newMasks->unknown4;
			entry->unknown8 = newMasks->unknown8;
		}
	}

	// FUNCTION: ENGINE 0x10660150
	void PhysicsObject::SetObjectFilter(int object, const CollisionFilter* filter)
	{
		NOT_LOCKED(422);
		CollisionObject* target = objects[object];
		for (unsigned int j = 0; j < target->volumeCount; j++)
		{
			target->volumes[j]->SetFilter(filter);
		}
		target->properties.unknown0 = filter->unknown0;
		target->properties.unknown4 = filter->unknown4;
		UpdateFilters();
	}

	// FUNCTION: ENGINE 0x106601E0
	void PhysicsObject::SetVolumeFilter(int object, int volume, const CollisionFilter* filter)
	{
		NOT_LOCKED(457);
		objects[object]->volumes[volume]->SetFilter(filter);
		objects[object]->UpdateProperties();
		UpdateFilters();
	}

	// FUNCTION: ENGINE 0x10660260
	void PhysicsObject::SetFilterBits(unsigned int mask, bool set)
	{
		NOT_LOCKED(486);
		for (unsigned int i = 0; i < objectCount; i++)
		{
			unsigned int volumeCount = objects[i]->volumeCount;
			for (unsigned int j = 0; j < volumeCount; j++)
			{
				objects[i]->volumes[j]->SetFilterBits(mask, set);
			}
			IntersectionProperties* target = &objects[i]->properties;
			if (set)
			{
				target->unknown0 |= mask;
			}
			else
			{
				target->unknown0 &= ~mask;
			}
		}
		BroadPhaseMasks changed = masks;
		if (set)
		{
			changed.unknown0 |= mask;
		}
		else
		{
			changed.unknown0 &= ~mask;
		}
		masks = changed;
		if (detector != 0)
		{
			detector->masks[detectorIndex] = changed;
		}
	}

	// FUNCTION: ENGINE 0x10660360
	void PhysicsObject::SetObjectFilterBits(int object, unsigned int mask, bool set)
	{
		NOT_LOCKED(521);
		CollisionObject* target = objects[object];
		for (unsigned int j = 0; j < target->volumeCount; j++)
		{
			target->volumes[j]->SetFilterBits(mask, set);
		}
		if (set)
		{
			target->properties.unknown0 |= mask;
		}
		else
		{
			target->properties.unknown0 &= ~mask;
		}
		UpdateFilters();
	}

	// FUNCTION: ENGINE 0x10660410
	void PhysicsObject::SetVolumeFilterBits(int object, int volume, unsigned int mask, bool set)
	{
		NOT_LOCKED(556);
		objects[object]->volumes[volume]->SetFilterBits(mask, set);
		objects[object]->UpdateProperties();
		UpdateFilters();
	}

	// FUNCTION: ENGINE 0x106604A0
	void PhysicsObject::SetFilterBits2(unsigned int mask, bool set)
	{
		NOT_LOCKED(585);
		for (unsigned int i = 0; i < objectCount; i++)
		{
			unsigned int volumeCount = objects[i]->volumeCount;
			for (unsigned int j = 0; j < volumeCount; j++)
			{
				objects[i]->volumes[j]->SetFilterBits2(mask, set);
			}
			IntersectionProperties* target = &objects[i]->properties;
			if (set)
			{
				target->unknown4 |= mask;
			}
			else
			{
				target->unknown4 &= ~mask;
			}
		}
		BroadPhaseMasks changed = masks;
		if (set)
		{
			changed.unknown4 |= mask;
		}
		else
		{
			changed.unknown4 &= ~mask;
		}
		masks = changed;
		if (detector != 0)
		{
			detector->masks[detectorIndex] = changed;
		}
	}

	// FUNCTION: ENGINE 0x106605A0
	void PhysicsObject::SetObjectFilterBits2(int object, unsigned int mask, bool set)
	{
		NOT_LOCKED(620);
		CollisionObject* target = objects[object];
		for (unsigned int j = 0; j < target->volumeCount; j++)
		{
			target->volumes[j]->SetFilterBits2(mask, set);
		}
		if (set)
		{
			target->properties.unknown4 |= mask;
		}
		else
		{
			target->properties.unknown4 &= ~mask;
		}
		UpdateFilters();
	}

	// FUNCTION: ENGINE 0x10660650
	void PhysicsObject::SetVolumeFilterBits2(int object, int volume, unsigned int mask, bool set)
	{
		NOT_LOCKED(655);
		objects[object]->volumes[volume]->SetFilterBits2(mask, set);
		objects[object]->UpdateProperties();
		UpdateFilters();
	}

	// FUNCTION: ENGINE 0x106606E0
	PhysicsObject* PhysicsObject::Clone()
	{
		PhysicsObject* copy = new PhysicsObject;
		copy->bounds.Set(bounds);
		if (copy->detector != 0)
		{
			copy->detector->boxes[copy->detectorIndex].Set(bounds);
		}
		copy->skipped = skipped;
		copy->SetCollisionMode(collisionMode & 3);
		copy->SetMasks(masks);
		copy->name = name;
		copy->unknown48 = unknown48;
		copy->unknown4C = 1.0f;
		copy->unknown50 = unknown50;
		copy->objectCount = objectCount;
		copy->objects = new CollisionObject*[objectCount];
		for (unsigned int i = 0; i != objectCount; i++)
		{
			copy->objects[i] = objects[i]->Clone(false);
			copy->objects[i]->owner = copy;
		}
		JointSet* jointSet = 0;
		copy->link = link;
		if (link != 0)
		{
			copy->link->AddRef();
			jointSet = link->joints;
		}
		copy->jointCount = jointSet ? jointSet->Count() : 0;
		copy->joints = jointSet ? jointSet->CreateJoints(copy) : 0;
		return copy;
	}

	// FUNCTION: ENGINE 0x106609F0
	void PhysicsObject::TransformBy(const math::Matrix& matrix)
	{
		NOT_LOCKED(837);
		for (unsigned int i = 0; i != objectCount; i++)
		{
			CollisionObject* object = objects[i];
			math::Matrix result;
			result.Multiply(object->transform, matrix);
			object->SetTransform(result);
		}
		UpdateBounds();
	}

	// FUNCTION: ENGINE 0x10660A90
	void PhysicsObject::UpdateTransform(const math::Matrix& matrix, int index)
	{
		NOT_LOCKED(883);
		if (index == -1)
		{
			for (unsigned int i = 0; i != objectCount; i++)
			{
				objects[i]->UpdateTransform(matrix);
			}
		}
		else
		{
			objects[index]->UpdateTransform(matrix);
		}
		UpdateBounds();
	}

	// FUNCTION: ENGINE 0x10660B30
	void PhysicsObject::SetObjectActive(int index, bool active)
	{
		NOT_LOCKED(915);
		CollisionObject* object = objects[index];
		object->SetActive(active);
		if (detector != 0)
		{
			detector->UpdateCollisionObject(object);
		}
		UpdateBounds();
	}

	// FUNCTION: ENGINE 0x10660BB0
	void PhysicsObject::ReadPose(const pure3d::Pose* pose, const math::Matrix* offset)
	{
		NOT_LOCKED(934);
		if (offset != 0)
		{
			for (unsigned int i = 0; i != objectCount; i++)
			{
				math::Matrix result;
				result.Multiply(pose->mData.mWorldMatrices[link->jointOfObject[i]], *offset);
				result.Orthonormalize();
				objects[i]->SetTransform(result);
			}
		}
		else
		{
			for (unsigned int i = 0; i != objectCount; i++)
			{
				math::Matrix result(pose->mData.mWorldMatrices[link->jointOfObject[i]]);
				result.Orthonormalize();
				objects[i]->SetTransform(result);
			}
		}
	}

	// FUNCTION: ENGINE 0x10660D70
	void PhysicsObject::WritePose(pure3d::Pose* pose, const math::Matrix* offset)
	{
		NOT_LOCKED(974);
		math::Matrix inverse;
		math::Matrix result;
		unsigned short object = link->objectOfJoint[0];
		if (object != 0xFFFF)
		{
			if (offset == 0)
			{
				*pose->mData.mWorldMatrices = objects[object]->transform;
			}
			else
			{
				inverse = *offset;
				inverse.Invert();
				result.Multiply(objects[link->objectOfJoint[0]]->transform, inverse);
				*pose->mData.mWorldMatrices = result;
			}
		}
		else
		{
			*pose->mData.mWorldMatrices = *pose->mData.mLocalMatrices;
		}
		if (link->skeletonJointCount > 1)
		{
			pure3d::Skeleton* skeleton = pose->mSkeleton;
			math::Matrix* destination = pose->mData.mWorldMatrices + 1;
			math::Matrix* local = pose->mData.mLocalMatrices + 1;
			for (unsigned int i = 1; i != link->skeletonJointCount; i++)
			{
				if (link->objectOfJoint[i] != 0xFFFF)
				{
					if (offset == 0)
					{
						pose->mData.mWorldMatrices[i] = objects[link->objectOfJoint[i]]->transform;
					}
					else
					{
						inverse = *offset;
						inverse.Invert();
						result.Multiply(objects[link->objectOfJoint[i]]->transform, inverse);
						pose->mData.mWorldMatrices[i] = result;
					}
				}
				else
				{
					destination->Multiply(*local, pose->mData.mWorldMatrices[skeleton->mData.mParents[i]]);
				}
				destination++;
				local++;
			}
		}
	}

	// FUNCTION: ENGINE 0x10660880
	void PhysicsObject::SetJointSet(JointSet* set)
	{
		if (set != 0)
		{
			core::RefAssign(link->joints, set);
		}
	}

	// FUNCTION: ENGINE 0x106608A0
	void PhysicsObject::UpdateBounds()
	{
		OLD_ASSERT_AT(PHYSICSOBJECT_FILE, 804, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		float minX = 1e12f;
		float minY = 1e12f;
		float minZ = 1e12f;
		float maxX = -1e12f;
		float maxY = -1e12f;
		float maxZ = -1e12f;
		unsigned int total = objectCount;
		for (unsigned int i = 0; i < total; i++)
		{
			CollisionObject* object = objects[i];
			if ((object->state & 0x80000000) != 0)
			{
				unsigned int volumesLeft = object->volumeCount;
				if (volumesLeft > 0)
				{
					CollisionVolume** volumePointer = object->volumes;
					do
					{
						const float* bounds = &(*volumePointer)->bounds.min.x;
						if (!(bounds[0] > minX))
						{
							minX = bounds[0];
						}
						if (!(bounds[1] > minY))
						{
							minY = bounds[1];
						}
						if (!(bounds[2] > minZ))
						{
							minZ = bounds[2];
						}
						if (maxX < bounds[3])
						{
							maxX = bounds[3];
						}
						if (maxY < bounds[4])
						{
							maxY = bounds[4];
						}
						if (maxZ < bounds[5])
						{
							maxZ = bounds[5];
						}
						volumePointer++;
						volumesLeft--;
					}
					while (volumesLeft != 0);
				}
			}
		}
		bounds.boundsMax.Set(maxX, maxY, maxZ);
		bounds.boundsMin.Set(minX, minY, minZ);
		if (detector != 0)
		{
			BroadPhaseBox* box = detector->boxes + detectorIndex;
			box->boundsMax.Set(maxX, maxY, maxZ);
			box->boundsMin.Set(minX, minY, minZ);
		}
	}

	// FUNCTION: ENGINE 0x106612C0
	void PhysicsObject::RefreshBounds(bool unused)
	{
		OLD_ASSERT_AT(PHYSICSOBJECT_FILE, 328, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		bool changed = false;
		for (unsigned int i = 0; i != objectCount; i++)
		{
			changed = changed || objects[i]->TestAndClearChanged();
		}
		if (changed)
		{
			UpdateBounds();
		}
	}

	// FUNCTION: ENGINE 0x10660F50
	void PhysicsObject::SetPairEnabled(unsigned int pair, bool enabled)
	{
		NOT_LOCKED(1042);
		SetBit(link->pairMask, pair, enabled);
	}

	// FUNCTION: ENGINE 0x10660FC0
	void PhysicsObject::GetJointPair(int index, int* first, int* second)
	{
		JointDefinition* definition = link->joints->begin + index;
		if (first != 0)
		{
			*first = definition->unknown0;
		}
		if (second != 0)
		{
			*second = definition->unknown4;
		}
	}

	// FUNCTION: ENGINE 0x10660FF0
	PhysicsLink::~PhysicsLink()
	{
		delete[] jointOfObject;
		delete[] objectOfJoint;
		delete[] pairMask;
		core::SafeRelease(joints);
	}

	// FUNCTION: ENGINE 0x10661350
	void PhysicsObject::SetVolumeQuery(const void* query)
	{
		NOT_LOCKED(855);
		for (unsigned int i = 0; i < objectCount; i++)
		{
			objects[i]->SetVolumeQuery(query);
		}
		RefreshBounds(false);
		for (unsigned int i = 0; i < jointCount; i++)
		{
			joints[i]->Update(query);
		}
	}

	// FUNCTION: ENGINE 0x106613F0
	void PhysicsLink::Release()
	{
		refCount--;
		if (refCount < 1)
		{
			refCount = 0xBAAD;
			this->~PhysicsLink();
			operator delete(this);
		}
	}
}

// Kept copies of inline functions and template members this unit makes (compiler-made or header-defined, so the
// annotations stand without a definition)
// FUNCTION: ENGINE 0x10661510
