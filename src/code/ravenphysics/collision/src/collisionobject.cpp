#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/physicsobject.h"
#include "code/core/debug.h"

#define COLLISIONOBJECT_FILE "..\\..\\..\\code\\ravenphysics\\collision\\src\\collisionobject.cpp"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x106544E0
	void CollisionObject::UpdateTransform(const math::Matrix& matrix)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 322, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		transform = matrix;
		for (unsigned int i = 0; i < volumeCount; i++)
		{
			volumes[i]->UpdateBounds(this);
		}
		changed = true;
		if ((owner->collisionMode & 3) != 0)
		{
			shape->Update(this);
		}
	}

	// FUNCTION: ENGINE 0x10654580
	void CollisionObject::SetTransform(const math::Matrix& matrix)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 367, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		UpdateTransform(matrix);
		owner->UpdateBounds();
	}

	// FUNCTION: ENGINE 0x10654670
	void CollisionObject::SetMaterial(unsigned char material)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 417, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		for (unsigned int i = 0; i < volumeCount; i++)
		{
			CollisionVolume* volume = volumes[i];
			if (volume->type == 4)
			{
				volume->materials.SetMaterial(material);
			}
			volume->material = material;
		}
	}

	// FUNCTION: ENGINE 0x106546F0
	void CollisionObject::SetVolumeQuery(const void* query)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 434, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		for (unsigned int i = 0; i < volumeCount; i++)
		{
			CollisionVolume* volume = volumes[i];
			volume->SetQuery(query);
			volume->UpdateBounds(this);
		}
		changed = volumeCount > 0;
		if (shape != 0)
		{
			shape->Refresh();
		}
	}

	// FUNCTION: ENGINE 0x10654790
	// NONMATCHING: the detector test, 89.6 %: the engine keeps the loaded pointer in a register and tests that
	// (`mov ecx, [owner + 0x34]; test ecx, ecx`), ours compares the member against zero
	CollisionShape* CollisionObject::SetShape(CollisionShape* newShape)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 498, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		CollisionShape* oldShape = shape;
		shape = newShape;
		if (newShape != 0)
		{
			if ((owner->collisionMode & 3) != 0)
			{
				newShape->Update(this);
			}
		}
		else
		{
			owner->SetCollisionMode(0);
		}
		BroadPhaseDetector* detector = owner->detector;
		if (detector != 0)
		{
			owner->UpdateCollisionObject(this);
		}
		return oldShape;
	}

	// FUNCTION: ENGINE 0x10654820
	void CollisionObject::SetCapsuleVolume(int index, const math::Capsule& capsule)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 556, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		CollisionVolume* volume = volumes[index];
		volume->SetCapsule(capsule);
		volume->UpdateCapsuleBounds(this);
	}

	// FUNCTION: ENGINE 0x10654890
	void CollisionObject::SetSphereVolume(int index, const math::Sphere& sphere)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 557, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		CollisionVolume* volume = volumes[index];
		volume->SetSphere(sphere);
		volume->UpdateSphereBounds(this);
	}

	// FUNCTION: ENGINE 0x10654900
	void CollisionObject::SetVolume2(int index, const void* description)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 558, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		CollisionVolume* volume = volumes[index];
		volume->SetVolume2(description);
		volume->UpdateBounds6(this);
	}

	// FUNCTION: ENGINE 0x10654970
	void CollisionObject::SetVolume4(int index, const void* description)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 559, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		CollisionVolume* volume = volumes[index];
		volume->SetVolume4(description);
		volume->UpdateBounds2(this);
	}

	// FUNCTION: ENGINE 0x106549E0
	void CollisionObject::SetVolume6(int index, const void* description)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 560, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		CollisionVolume* volume = volumes[index];
		volume->SetVolume6(description);
		volume->UpdateBounds4(this);
	}

	// FUNCTION: ENGINE 0x10654AB0
	void CollisionObject::CastQuery(const void* query, math::Vector* point, float* distance, unsigned int* index)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 591, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		*distance = 1e12f;
		*index = 0xffffffff;
		for (unsigned int i = 0; i < volumeCount; i++)
		{
			math::Vector hitPoint;
			float hitDistance = 1e12f;
			if (volumes[i]->CastVolume(query, &hitPoint, &hitDistance) && hitDistance < *distance)
			{
				*distance = hitDistance;
				point->x = hitPoint.x;
				point->y = hitPoint.y;
				point->z = hitPoint.z;
				*index = i;
			}
		}
	}

	// FUNCTION: ENGINE 0x10654BB0
	void CollisionObject::SetVolumeEnabled(unsigned int index, bool enabled)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 625, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		if (index < 31)
		{
			if (enabled)
			{
				state |= 1 << index;
			}
			else
			{
				state &= ~(1 << index);
			}
		}
		if (shape != 0)
		{
			shape->Refresh();
		}
	}

	// FUNCTION: ENGINE 0x10654C30
	void CollisionObject::SetMatrix(const math::Matrix& matrix)
	{
		transform = matrix;
		for (unsigned int i = 0; i < volumeCount; i++)
		{
			volumes[i]->UpdateBounds(this);
		}
		changed = true;
	}

	// FUNCTION: ENGINE 0x106544B0
	void CollisionObject::SetUnknown70(int value)
	{
		unknown70 = value;
	}

	// FUNCTION: ENGINE 0x106544C0
	void CollisionObject::SetActive(bool active)
	{
		if (active)
		{
			state |= 0x80000000;
		}
		else
		{
			state &= 0x7fffffff;
		}
	}

	// FUNCTION: ENGINE 0x106545E0
	unsigned char CollisionObject::GetVolumeMaterial(int index)
	{
		return volumes[index]->material;
	}

	// FUNCTION: ENGINE 0x10654A50
	void CollisionObject::SetVolumeSwapped(int index, bool swapped)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 569, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		volumes[index]->swapped = swapped;
	}

	// FUNCTION: ENGINE 0x10654C70
	bool CollisionObject::HasVolumeType(unsigned short type)
	{
		unsigned int i = 0;
		unsigned int count = volumeCount;
		if (count != 0)
		{
			CollisionVolume** volume = volumes;
			do
			{
				if ((*volume)->type == type)
				{
					return true;
				}
				i++;
				volume++;
			}
			while (i != count);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10654CB0
	void CollisionObject::SetMesh(ConvexMesh* newMesh)
	{
		if (newMesh != 0)
		{
			newMesh->AddRef();
		}
		if (mesh != 0)
		{
			mesh->Release();
		}
		mesh = newMesh;
	}

	// FUNCTION: ENGINE 0x10654D30
	math::Vector* CollisionObject::GetUnknown10()
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 750, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		return &shape->unknown10;
	}

	// FUNCTION: ENGINE 0x10654D80
	math::Vector* CollisionObject::GetUnknown1C()
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 758, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		return &shape->unknown1C;
	}

	// FUNCTION: ENGINE 0x10655230
	math::Vector* CollisionObject::GetUnknown40()
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 830, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		return &shape->unknown40;
	}

	// FUNCTION: ENGINE 0x10655280
	math::Vector* CollisionObject::GetUnknown4C()
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 838, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		return &shape->unknown4C;
	}

	// FUNCTION: ENGINE 0x106552D0
	void CollisionObject::SetFlag3(bool value)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 846, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->flag3 = value;
	}

	// FUNCTION: ENGINE 0x10655330
	bool CollisionObject::IsFlag3()
	{
		return shape->flag3;
	}

	// FUNCTION: ENGINE 0x10655340
	math::Vector* CollisionObject::GetUnknown90()
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 861, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		return &shape->unknown90;
	}

	// FUNCTION: ENGINE 0x10655390
	math::Vector* CollisionObject::GetUnknown9C()
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 867, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		return &shape->center;
	}

	// FUNCTION: ENGINE 0x10655460
	math::Vector* CollisionObject::GetUnknown58()
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 881, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		return &shape->unknown58;
	}

	// FUNCTION: ENGINE 0x10655510
	float CollisionObject::GetUnknown88()
	{
		return shape->unknown88;
	}

	// FUNCTION: ENGINE 0x10655580
	float CollisionObject::GetUnknown8C()
	{
		return shape->unknown8C;
	}

	// FUNCTION: ENGINE 0x106555F0
	bool CollisionObject::IsFlag2()
	{
		return shape->flag2;
	}

	// FUNCTION: ENGINE 0x106556E0
	void CollisionObject::SetFlag1(bool value)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 943, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->flag1 = value;
	}

	// FUNCTION: ENGINE 0x10655740
	bool CollisionObject::IsFlag1()
	{
		return shape->flag1;
	}

	// FUNCTION: ENGINE 0x10655750
	math::Vector* CollisionObject::GetUnknown34()
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 976, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		return &shape->unknown34;
	}

	// FUNCTION: ENGINE 0x10655960
	void CollisionObject::SetFlag4(bool value)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 1000, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		if (shape != 0)
		{
			shape->flag4 = value;
		}
	}

	// FUNCTION: ENGINE 0x106559C0
	// NONMATCHING: register allocation, 64.4 %: the engine tests the count in memory and loads it into edi inside
	// the loop, ours loads it before the guard; the volume pointer is biased to the element in the engine
	void CollisionObject::UpdateProperties()
	{
#ifdef NONMATCHING
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 1016, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		IntersectionProperties accumulated;
		accumulated.unknown0 = 0;
		accumulated.unknown4 = 0;
		if (volumeCount > 0)
		{
			CollisionVolume** volume = volumes;
			unsigned int left = volumeCount;
			do
			{
				CollisionVolume* current = *volume;
				accumulated.unknown0 |= current->unknown1C;
				accumulated.unknown4 |= current->unknown20;
				volume++;
			}
			while (--left != 0);
		}
		properties = accumulated;
#endif
	}

	// FUNCTION: ENGINE 0x10655D90
	void CollisionObject::SetName(core::Name<core::CaseSensitiveKey> newName)
	{
		name = newName;
	}
}
