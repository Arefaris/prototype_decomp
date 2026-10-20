#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/physicsobject.h"
#include "code/core/debug.h"
#include "code/core/refptr.h"
#include "code/engine/system/enginememory.h"
#include <math.h>

#define COLLISIONOBJECT_FILE "..\\..\\..\\code\\ravenphysics\\collision\\src\\collisionobject.cpp"

namespace ravenphysics
{
	// Builds the shape an object with a single volume of this description is seen through (0x1066A1B0, another unit)
	CollisionShape* CreateVolumeShape(CollisionVolume* volume, float size, CollisionObject* object);
	// The same for a box (0x1066A220, another unit)
	CollisionShape* CreateBoxShape(float size, int a, int b, CollisionObject* object);

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
				((CollisionVolume4*)volume)->materials.SetMaterial(material);
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
			detector->UpdateCollisionObject(this);
		}
		return oldShape;
	}

	// FUNCTION: ENGINE 0x10654820
	void CollisionObject::SetCapsuleVolume(int index, const math::Capsule& capsule)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 556, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		CollisionCapsule* volume = static_cast<CollisionCapsule*>(volumes[index]);
		volume->SetCapsule(capsule);
		volume->UpdateWorld(this);
	}

	// FUNCTION: ENGINE 0x10654890
	void CollisionObject::SetOBBVolume(int index, const math::OBB& box)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 557, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		CollisionOBB* volume = static_cast<CollisionOBB*>(volumes[index]);
		volume->SetOBB(box);
		volume->UpdateWorld(this);
	}

	// FUNCTION: ENGINE 0x10654900
	void CollisionObject::SetPlaneVolume(int index, const void* description)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 558, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		CollisionPlane* volume = static_cast<CollisionPlane*>(volumes[index]);
		volume->SetPlane(description);
		volume->UpdateWorld(this);
	}

	// FUNCTION: ENGINE 0x10654970
	void CollisionObject::SetSphereVolume(int index, const math::Sphere& sphere)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 559, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		CollisionSphere* volume = static_cast<CollisionSphere*>(volumes[index]);
		volume->SetSphere(sphere);
		volume->UpdateWorld(this);
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
	math::SymmetricMatrix* CollisionObject::GetUnknown58()
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 881, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		return &shape->unknown58;
	}

	// FUNCTION: ENGINE 0x10655510
	float CollisionObject::GetScale()
	{
		return shape->unknown88;
	}

	// FUNCTION: ENGINE 0x10655580
	float CollisionObject::GetInverseScale()
	{
		return shape->unknown8C;
	}

	// FUNCTION: ENGINE 0x10654CE0
	void CollisionObject::Clear()
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 742, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->Clear();
	}

	// FUNCTION: ENGINE 0x10654DD0
	void CollisionObject::MoveTo(math::Vector position)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 766, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->MoveTo(position, 1);
	}

	// FUNCTION: ENGINE 0x10654E50
	void CollisionObject::Translate(math::Vector offset)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 774, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->Translate(offset, 1);
	}

	// FUNCTION: ENGINE 0x10654ED0
	void CollisionObject::GetVelocityAt(math::Vector point, math::Vector* velocity)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 782, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->GetPointVelocity(point, velocity);
	}

	// FUNCTION: ENGINE 0x10654F50
	void CollisionObject::AddVelocity(math::Vector velocity)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 790, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->AddVelocity(velocity, 1);
	}

	// FUNCTION: ENGINE 0x10654FD0
	void CollisionObject::AddImpulse(math::Vector impulse, math::Vector point)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 798, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->AddImpulse(impulse, point, 1);
	}

	// FUNCTION: ENGINE 0x10655070
	void CollisionObject::AddAngularVelocity(math::Vector velocity)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 806, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->AddAngularVelocity(velocity, 1);
	}

	// FUNCTION: ENGINE 0x106550F0
	void CollisionObject::MoveFromTo(math::Vector from, math::Vector to)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 814, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->MoveTo(from, to, 1);
	}

	// FUNCTION: ENGINE 0x10655190
	void CollisionObject::MoveToCenter(math::Vector from)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 822, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->MoveTo(from, shape->center, 1);
	}

	// FUNCTION: ENGINE 0x106553E0
	void CollisionObject::SetPosition(math::Vector position)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 875, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->SetPosition(position);
	}

	// FUNCTION: ENGINE 0x106554B0
	void CollisionObject::SetVectors(const void* values)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 887, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->SetVectors(values);
	}

	// FUNCTION: ENGINE 0x10655520
	void CollisionObject::SetScale(float scale)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 898, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->SetScale(scale);
	}

	// FUNCTION: ENGINE 0x10655590
	void CollisionObject::SetInverseScale(float inverse)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 909, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->SetInverseScale(inverse);
	}

	// FUNCTION: ENGINE 0x106555F0
	bool CollisionObject::IsFlag2()
	{
		return shape->flag2;
	}

	// FUNCTION: ENGINE 0x10655600
	void CollisionObject::SetWorld(void* world)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 922, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->SetFlag2((int)world);
		BroadPhaseDetector* detector = owner->detector;
		if (detector != 0)
		{
			detector->UpdateCollisionObject(this);
		}
	}

	// FUNCTION: ENGINE 0x10655670
	void CollisionObject::SetSize(int a, int b, float size)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 935, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		shape->SetSize(a, b, size);
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

	// FUNCTION: ENGINE 0x106557A0
	// NONMATCHING: as GetRelativeVelocity, with the previous vectors
#ifdef NONMATCHING
	void CollisionObject::GetPreviousRelativeVelocity(const math::Vector* point, math::Vector* velocity)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 984, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		float px = point->x;
		float py = point->y;
		float pz = point->z;
		CollisionShape* body = shape;
		float cy = body->unknown34.z * px - body->unknown34.x * pz;
		float cz = body->unknown34.x * py - body->unknown34.y * px;
		float cx = body->unknown34.y * pz - body->unknown34.z * py;
		velocity->y = cy;
		velocity->z = cz;
		velocity->x = cx;
		velocity->x = cx + body->unknown28.x;
		velocity->y = body->unknown28.y + cy;
		velocity->z = body->unknown28.z + cz;
	}
#endif

	// FUNCTION: ENGINE 0x10655880
	// NONMATCHING: the shape's velocity at a point, the cross product of the angular velocity with the point added
	// to the linear velocity, inlined from the shape's accessor. Every instruction and the store order are the
	// engine's, but it computes x behind z (ours before the stores of y) and adds the linear x to the register of
	// the cross product, 67.8 %
#ifdef NONMATCHING
	void CollisionObject::GetRelativeVelocity(const math::Vector* point, math::Vector* velocity)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 992, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		float px = point->x;
		float py = point->y;
		float pz = point->z;
		CollisionShape* body = shape;
		float cy = body->unknown1C.z * px - body->unknown1C.x * pz;
		float cz = body->unknown1C.x * py - body->unknown1C.y * px;
		float cx = body->unknown1C.y * pz - body->unknown1C.z * py;
		velocity->y = cy;
		velocity->z = cz;
		velocity->x = cx;
		velocity->x = cx + body->unknown10.x;
		velocity->y = body->unknown10.y + cy;
		velocity->z = body->unknown10.z + cz;
	}
#endif

	// FUNCTION: ENGINE 0x10655960
	void CollisionObject::SetFlag4(bool value)
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 1000, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		CollisionShape* currentShape = shape;
		if (currentShape != 0)
		{
			currentShape->flag4 = value;
		}
	}

	// FUNCTION: ENGINE 0x106559C0
	void CollisionObject::UpdateProperties()
	{
		OLD_ASSERT_AT(COLLISIONOBJECT_FILE, 1016, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		IntersectionProperties accumulated;
		accumulated.unknown0 = 0;
		accumulated.unknown4 = 0;
		for (unsigned int i = 0; i < volumeCount; i++)
		{
			CollisionVolume* current = volumes[i];
			IntersectionProperties* filter = &current->filter;
			accumulated.unknown0 |= filter->unknown0;
			accumulated.unknown4 |= filter->unknown4;
		}
		properties = accumulated;
	}

	// FUNCTION: ENGINE 0x10655D90
	void CollisionObject::SetName(core::Name<core::CaseSensitiveKey> newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x10655A60
	void CollisionObject::Print()
	{
		transform.Print();
		for (unsigned int i = 0; i < volumeCount; i++)
		{
			volumes[i]->Print();
		}
		if (shape != 0)
		{
			shape->Print();
		}
	}

	// FUNCTION: ENGINE 0x10655AA0
	int MeshGeometry::Count() const
	{
		return end - begin;
	}

	// FUNCTION: ENGINE 0x10655AB0
	void CollisionObjectTable::Register(void* object, CollisionHandle* handle)
	{
		Add(object, handle);
	}

	// FUNCTION: ENGINE 0x10655AC0
	unsigned short MinSlots(unsigned short a, unsigned short b)
	{
		return a < b ? a : b;
	}

	// FUNCTION: ENGINE 0x10655AE0
	CollisionObject::CollisionObject()
		: name()
		, handle()
		, changed(true)
		, properties()
	{
		volumes = 0;
		shape = 0;
		owner = 0;
		unknown70 = 0;
		mesh = 0;
		unknown4C = 0;
		gCollisionObjectTable->Add(this, &handle);
	}

	// FUNCTION: ENGINE 0x10655B60
	void CollisionObject::Initialize(CollisionVolume** newVolumes, unsigned int count)
	{
		mesh = 0;
		shape = 0;
		volumes = newVolumes;
		volumeCount = count;
		owner = 0;
		unknown70 = 0;
		state = (1 << (volumeCount < 31 ? volumeCount : 31)) - 1;
		SetActive(true);
		transform.Identity();
		UpdateProperties();
		for (unsigned int i = 0; i < count; i++)
		{
			newVolumes[i]->Retain();
		}
	}

	// FUNCTION: ENGINE 0x10655DA0
	// NONMATCHING: the six accumulators, 7.9 %: the engine keeps them in xmm6/xmm5/xmm4 and xmm0/xmm1/xmm2
	// across the loop and computes the three sizes with SSE, ours spills all six to the stack and finishes in
	// x87 (the frame is 8 bytes larger)
#ifdef NONMATCHING
	float CollisionObject::GetRadius() const
	{
		float minX = 1e12f;
		float minY = 1e12f;
		float minZ = 1e12f;
		float maxX = -1e12f;
		float maxY = -1e12f;
		float maxZ = -1e12f;
		unsigned int count = volumeCount;
		if (count > 0)
		{
			CollisionVolume** volume = volumes;
			do
			{
				CollisionVolume* current = *volume;
				if (current->bounds.min.x <= minX)
				{
					minX = current->bounds.min.x;
				}
				if (current->bounds.min.y <= minY)
				{
					minY = current->bounds.min.y;
				}
				if (current->bounds.min.z <= minZ)
				{
					minZ = current->bounds.min.z;
				}
				if (current->bounds.max.x > maxX)
				{
					maxX = current->bounds.max.x;
				}
				if (current->bounds.max.y > maxY)
				{
					maxY = current->bounds.max.y;
				}
				if (current->bounds.max.z > maxZ)
				{
					maxZ = current->bounds.max.z;
				}
				volume++;
			}
			while (--count != 0);
			if (minX <= maxX && minY <= maxY && minZ <= maxZ)
			{
				float sizeZ = (maxZ - minZ) * 0.5f;
				float sizeY = (maxY - minY) * 0.5f;
				float sizeX = (maxX - minX) * 0.5f;
				return sqrtf(sizeX * sizeX + sizeY * sizeY + sizeZ * sizeZ);
			}
		}
		return 0.0f;
	}
#endif

	// FUNCTION: ENGINE 0x10655EA0
	// NONMATCHING: the null checks of the four deletes, 59.6 %: the engine emits `test esi, esi` before every
	// destructor call, ours drops it because the volume pointer was just dereferenced for its type byte
#ifdef NONMATCHING
	CollisionObject::~CollisionObject()
	{
		gCollisionObjectTable->Remove(&handle);
		if (mesh != 0)
		{
			mesh->Release();
		}
		for (unsigned int i = 0; i < volumeCount; i++)
		{
			volumes[i]->Release();
			CollisionVolume* volume = volumes[i];
			if (volume->type == 6)
			{
				delete (CollisionVolume6*)volume;
			}
			else if (volume->type == 3)
			{
				delete (CollisionVolume3*)volume;
			}
			else if (volume->type == 4)
			{
				delete (CollisionVolume4*)volume;
			}
			else
			{
				delete volume;
			}
		}
		delete[] volumes;
		if (shape != 0)
		{
			delete shape;
		}
	}
#endif

	// FUNCTION: ENGINE 0x10655B30
	void* CollisionVolume4::DestroyAndFree(unsigned int flags)
	{
		materials.~CollisionVolume3();
		MarkDestroyed();
		if (flags & 1)
		{
			operator delete(this);
		}
		return this;
	}

	// FUNCTION: ENGINE 0x10655BE0
	CollisionObject* CollisionObject::Clone(bool unused)
	{
		CollisionObject* copy = new CollisionObject();
		copy->properties = properties;
		copy->name = name;
		copy->unknown70 = unknown70;
		copy->transform = transform;
		copy->volumeCount = volumeCount;
		copy->state = state;
		copy->volumes = new CollisionVolume*[volumeCount];
		if (mesh != 0)
		{
			copy->mesh = new ConvexMesh();
			mesh->AddRef();
			MeshGeometry& geometry = mesh->geometry;
			copy->mesh->Reserve(geometry.end - geometry.begin);
			for (unsigned int i = 0; i < volumeCount; i++)
			{
				copy->volumes[i] = volumes[i]->Clone();
				if (volumes[i]->Clone()->type == 6
					&& ((CollisionVolume6*)copy->volumes[i])->grid.slot->unknown4 != 0)
				{
					copy->mesh->AddVolume(copy->volumes[i]);
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < volumeCount; i++)
			{
				copy->volumes[i] = volumes[i]->Clone();
			}
		}
		for (unsigned int i = 0; i < volumeCount; i++)
		{
			copy->volumes[i]->Retain();
		}
		if (!unused && shape != 0)
		{
			copy->shape = new CollisionShape(*shape, copy);
		}
		else
		{
			copy->shape = 0;
		}
		return copy;
	}

	// FUNCTION: ENGINE 0x10655F60
	CollisionObject* CreateCollisionObject(CollisionVolume* volume, bool makeShape, float size)
	{
		CollisionObject* object = new CollisionObject();
		CollisionVolume** volumes = new CollisionVolume*[1];
		volumes[0] = volume;
		object->Initialize(volumes, 1);
		if (makeShape)
		{
			object->shape = CreateVolumeShape(volume, size, object);
		}
		return object;
	}

	// FUNCTION: ENGINE 0x10655FC0
	CollisionObject* CreateCollisionObject(CollisionVolume** volumes, unsigned int count, bool makeShape, float size,
		int a, int b)
	{
		CollisionObject* object = new CollisionObject();
		object->Initialize(volumes, count);
		if (makeShape)
		{
			object->shape = CreateBoxShape(size, a, b, object);
		}
		return object;
	}
}
