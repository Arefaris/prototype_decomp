#include "code/content/metafactory.h"
#include "code/content/vectormetatype.h"
#include "code/core/refptr.h"
#include "code/math/mathconstants.h"
#include "code/ravenphysics/collisionvolumefactory.h"
#include "code/ravenphysics/context.h"
#include <new>

namespace ravenphysics
{
	// The unit's references to the volume classes of other units
	struct Axes3
	{
		float values[9];
	};

	// The three axes of an untransformed box, a table of the engine (0x111BBAA8; name guess)
	extern const Axes3 gBoxAxes;

	template struct content::BaseClassCasterImpl<CollisionVolumeFactory, CollisionCapsuleFactory>;
	template struct content::BaseClassCasterImpl<CollisionVolumeFactory, CollisionCylinderFactory>;
	template struct content::BaseClassCasterImpl<CollisionVolumeFactory, CollisionOBBFactory>;
	template struct content::BaseClassCasterImpl<CollisionVolumeFactory, CollisionPlaneFactory>;
	template struct content::BaseClassCasterImpl<CollisionVolumeFactory, CollisionSphereFactory>;

	// FUNCTION: ENGINE 0x10679D00
	content::ClassInfo* CollisionVolumeFactory::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::CollisionVolumeFactory";
		sInfo.code = "n";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10679D40
	content::ClassInfo* CollisionCapsuleFactory::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::CollisionCapsuleFactory";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10679D80
	content::ClassInfo* CollisionCylinderFactory::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::CollisionCylinderFactory";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10679DC0
	content::ClassInfo* CollisionOBBFactory::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::CollisionOBBFactory";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10679E00
	content::ClassInfo* CollisionPlaneFactory::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::CollisionPlaneFactory";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10679E40
	content::ClassInfo* CollisionSphereFactory::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::CollisionSphereFactory";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10679E80
	CollisionVolumeFactory::CollisionVolumeFactory() :
		material(0),
		intersectionProperties(0),
		type(0xFF)
	{
	}

	// FUNCTION: ENGINE 0x10679EA0
	CollisionVolumeFactory::CollisionVolumeFactory(unsigned char newType) :
		material(0),
		intersectionProperties(0),
		type(newType)
	{
	}

	// FUNCTION: ENGINE 0x10679EC0
	MaterialLoader* CollisionVolumeFactory::GetMaterial() const
	{
		return material;
	}

	// FUNCTION: ENGINE 0x10679ED0
	IntersectionPropertiesLoader* CollisionVolumeFactory::GetIntersectionProperties() const
	{
		return intersectionProperties;
	}

	// FUNCTION: ENGINE 0x10679EE0
	void CollisionVolumeFactory::ApplyTo(CollisionVolume* volume)
	{
		MaterialLoader* loader = material;
		if (loader)
		{
			unsigned char index = loader->index;
			if (volume->type == 4)
			{
				((CollisionVolume3*)((unsigned char*)volume + 0x60))->SetMaterial(index);
			}
			volume->material = index;
		}
		IntersectionPropertiesLoader* properties = intersectionProperties;
		if (properties)
		{
			volume->filter.unknown0 = properties->unknown3C;
			volume->filter.unknown4 = properties->unknown40;
		}
	}

	// FUNCTION: ENGINE 0x10679F30
	CollisionVolume* CollisionCapsuleFactory::CreateVolume()
	{
		CollisionCapsule* volume = new CollisionCapsule(capsule);
		ApplyTo(volume);
		return volume;
	}

	// FUNCTION: ENGINE 0x10679F70
	void CollisionCapsuleFactory::SetOnObject(CollisionObject* object, int index)
	{
		object->SetCapsuleVolume(index, capsule);
	}

	// FUNCTION: ENGINE 0x10679F90
	void CollisionCapsuleFactory::GetBounds(math::AABB* bounds)
	{
		capsule.GetAABB(*bounds);
	}

	// FUNCTION: ENGINE 0x10679FA0
	math::Capsule* CollisionCapsuleFactory::GetCapsule()
	{
		return &capsule;
	}

	// FUNCTION: ENGINE 0x10679FB0
	const math::Vector* CollisionCapsuleFactory::GetDirection() const
	{
		return &capsule.direction;
	}

	// FUNCTION: ENGINE 0x10679FC0
	void CollisionCapsuleFactory::SetDirection(const math::Vector* direction)
	{
		math::Vector* target = &capsule.direction;
		target->x = direction->x;
		target->y = direction->y;
		target->z = direction->z;
		float length = target->Normalize();
		if (length < math::EPSILON_SMALL)
		{
			target->x = 0.0f;
			target->y = 1.0f;
			target->z = 0.0f;
		}
	}

	// FUNCTION: ENGINE 0x1067A010
	CollisionVolume* CollisionCylinderFactory::CreateVolume()
	{
		CollisionVolume4* volume = new CollisionVolume4(cylinder);
		ApplyTo(volume);
		return volume;
	}

	// FUNCTION: ENGINE 0x1067A060
	void CollisionCylinderFactory::GetBounds(math::AABB* bounds)
	{
		cylinder.GetAABB(*bounds);
	}

	// FUNCTION: ENGINE 0x1067A070
	math::Cylinder* CollisionCylinderFactory::GetCylinder()
	{
		return &cylinder;
	}

	// FUNCTION: ENGINE 0x1067A0C0
	const math::Vector* CollisionCylinderFactory::GetDirection() const
	{
		return &cylinder.direction;
	}

	// FUNCTION: ENGINE 0x1067A0D0
	void CollisionCylinderFactory::SetDirection(const math::Vector* direction)
	{
		math::Vector* target = &cylinder.direction;
		target->x = direction->x;
		target->y = direction->y;
		target->z = direction->z;
		float length = target->Normalize();
		if (length < math::EPSILON_SMALL)
		{
			target->x = 0.0f;
			target->y = 1.0f;
			target->z = 0.0f;
		}
	}

	// FUNCTION: ENGINE 0x1067A120
	CollisionVolume* CollisionOBBFactory::CreateVolume()
	{
		CollisionOBB* volume = new CollisionOBB(box);
		ApplyTo(volume);
		return volume;
	}

	// FUNCTION: ENGINE 0x1067A160
	void CollisionOBBFactory::SetOnObject(CollisionObject* object, int index)
	{
		object->SetOBBVolume(index, box);
	}

	// FUNCTION: ENGINE 0x1067A180
	void CollisionOBBFactory::GetBounds(math::AABB* bounds)
	{
		box.GetAABB(*bounds);
	}

	// FUNCTION: ENGINE 0x1067A190
	math::OBB* CollisionOBBFactory::GetBox()
	{
		return &box;
	}

	// FUNCTION: ENGINE 0x1067A1A0
	const math::Vector* CollisionOBBFactory::GetAxis1() const
	{
		return &box.axis[0];
	}

	// FUNCTION: ENGINE 0x1067A1B0
	const math::Vector* CollisionOBBFactory::GetAxis2() const
	{
		return &box.axis[1];
	}

	// FUNCTION: ENGINE 0x1067A1C0
	// EQUIVALENT: the same products and differences; the engine loads the components of both axes ahead of the first product, 20.5 %
	void CollisionOBBFactory::UpdateAxis3()
	{
		float firstX = box.axis[0].x;
		float secondX = box.axis[1].x;
		float firstZ = box.axis[0].z;
		float secondZ = box.axis[1].z;
		float secondY = box.axis[1].y;
		float firstY = box.axis[0].y;
		box.axis[2].x = firstY * secondZ - secondY * firstZ;
		box.axis[2].y = secondX * firstZ - firstX * secondZ;
		box.axis[2].z = secondY * firstX - firstY * secondX;
	}

	// FUNCTION: ENGINE 0x1067A220
	CollisionVolume* CollisionPlaneFactory::CreateVolume()
	{
		CollisionPlane* volume = new CollisionPlane(&plane);
		ApplyTo(volume);
		return volume;
	}

	// FUNCTION: ENGINE 0x1067A260
	void CollisionPlaneFactory::SetOnObject(CollisionObject* object, int index)
	{
		object->SetPlaneVolume(index, &plane);
	}

	// FUNCTION: ENGINE 0x1067A290
	math::Plane* CollisionPlaneFactory::GetPlane()
	{
		return &plane;
	}

	// FUNCTION: ENGINE 0x1067A2A0
	CollisionVolume* CollisionSphereFactory::CreateVolume()
	{
		CollisionSphere* volume = new CollisionSphere(sphere);
		ApplyTo(volume);
		return volume;
	}

	// FUNCTION: ENGINE 0x1067A2E0
	void CollisionSphereFactory::SetOnObject(CollisionObject* object, int index)
	{
		object->SetSphereVolume(index, sphere);
	}

	// FUNCTION: ENGINE 0x1067A300
	void CollisionSphereFactory::GetBounds(math::AABB* bounds)
	{
		sphere.GetAABB(*bounds);
	}

	// FUNCTION: ENGINE 0x1067A310
	math::Sphere* CollisionSphereFactory::GetSphere()
	{
		return &sphere;
	}

	// FUNCTION: ENGINE 0x1067A350
	CollisionVolume* CollisionConvexHullFactory::CreateVolume()
	{
		CollisionVolume3* volume = new CollisionVolume3(hull->data);
		ApplyTo(volume);
		return volume;
	}

	// FUNCTION: ENGINE 0x1067A3A0
	void CollisionConvexHullFactory::GetBounds(math::AABB* bounds)
	{
		math::AABB* source = &hull->data->bounds;
		math::Vector* highest = &bounds->max;
		highest->x = source->max.x;
		highest->y = source->max.y;
		highest->z = source->max.z;
		math::Vector* lowest = &bounds->min;
		lowest->x = source->min.x;
		lowest->y = source->min.y;
		lowest->z = source->min.z;
	}

	// FUNCTION: ENGINE 0x1067A400
	CollisionVolume* CollisionMeshFactory::CreateVolume()
	{
		CollisionVolume6* volume = new CollisionVolume6(*grid);
		if (material)
		{
			unsigned char index = material->index;
			if (volume->type == 4)
			{
				((CollisionVolume3*)((unsigned char*)volume + 0x60))->SetMaterial(index);
			}
			volume->material = index;
		}
		if (grid->unknownC8)
		{
			volume->filter.unknown0 = filter.unknown0;
			volume->filter.unknown4 = filter.unknown4;
			return volume;
		}
		IntersectionPropertiesLoader* properties = intersectionProperties;
		if (properties)
		{
			volume->filter.unknown0 = properties->unknown3C;
			volume->filter.unknown4 = properties->unknown40;
			return volume;
		}
		IntersectionPropertiesEntry* entry = GetIntersectionProperty(0);
		volume->filter.unknown0 = entry->properties.unknown0;
		volume->filter.unknown4 = entry->properties.unknown4;
		return volume;
	}

	// FUNCTION: ENGINE 0x1067A4B0
	void CollisionMeshFactory::GetBounds(math::AABB* bounds)
	{
		math::AABB* source = &grid->bounds;
		math::Vector* highest = &bounds->max;
		highest->x = source->max.x;
		highest->y = source->max.y;
		highest->z = source->max.z;
		math::Vector* lowest = &bounds->min;
		lowest->x = source->min.x;
		lowest->y = source->min.y;
		lowest->z = source->min.z;
	}

	// FUNCTION: ENGINE 0x1067A950
	CollisionVolumeFactory::~CollisionVolumeFactory()
	{
		core::SafeRelease(material);
		core::SafeRelease(intersectionProperties);
	}

	// FUNCTION: ENGINE 0x1067A990
	void CollisionVolumeFactory::SetIntersectionProperties(IntersectionPropertiesLoader* properties)
	{
		core::RefAssign(intersectionProperties, properties);
	}

	// FUNCTION: ENGINE 0x1067A9B0
	CollisionCapsuleFactory::CollisionCapsuleFactory() :
		CollisionVolumeFactory(0)
	{
		capsule.centre.x = 0.0f;
		capsule.centre.y = 0.0f;
		capsule.centre.z = 0.0f;
		capsule.halfLength = 1.0f;
		capsule.direction.x = 0.0f;
		capsule.direction.y = 1.0f;
		capsule.direction.z = 0.0f;
		capsule.radius = 1.0f;
	}

	// FUNCTION: ENGINE 0x1067AA00
	CollisionCapsuleFactory::CollisionCapsuleFactory(const math::Capsule& newCapsule) :
		CollisionVolumeFactory(0)
	{
		capsule.centre.x = newCapsule.centre.x;
		capsule.centre.y = newCapsule.centre.y;
		capsule.centre.z = newCapsule.centre.z;
		capsule.halfLength = newCapsule.halfLength;
		capsule.direction.x = newCapsule.direction.x;
		capsule.direction.y = newCapsule.direction.y;
		capsule.direction.z = newCapsule.direction.z;
		capsule.radius = newCapsule.radius;
	}

	// FUNCTION: ENGINE 0x1067AA50
	CollisionCapsuleFactory::~CollisionCapsuleFactory()
	{
	}

	// FUNCTION: ENGINE 0x1067AA60
	void CollisionCapsuleFactory::Clone(CollisionVolumeFactory** copy)
	{
		*copy = new CollisionCapsuleFactory(*GetCapsule());
	}

	// FUNCTION: ENGINE 0x1067AAA0
	void CollisionCapsuleFactory::SetCapsule(const math::Capsule* newCapsule)
	{
		capsule.centre.x = newCapsule->centre.x;
		capsule.centre.y = newCapsule->centre.y;
		capsule.centre.z = newCapsule->centre.z;
		capsule.halfLength = newCapsule->halfLength;
		capsule.direction.x = newCapsule->direction.x;
		capsule.direction.y = newCapsule->direction.y;
		capsule.direction.z = newCapsule->direction.z;
		capsule.radius = newCapsule->radius;
	}

	// FUNCTION: ENGINE 0x1067AAE0
	CollisionCylinderFactory::CollisionCylinderFactory() :
		CollisionVolumeFactory(4)
	{
		cylinder.centre.x = 0.0f;
		cylinder.centre.y = 0.0f;
		cylinder.centre.z = 0.0f;
		cylinder.direction.x = 0.0f;
		cylinder.direction.y = 1.0f;
		cylinder.direction.z = 0.0f;
		cylinder.halfLength = 1.0f;
		cylinder.radius = 1.0f;
	}

	// FUNCTION: ENGINE 0x1067AB30
	CollisionCylinderFactory::CollisionCylinderFactory(const math::Cylinder& newCylinder) :
		CollisionVolumeFactory(4)
	{
		cylinder.centre.x = newCylinder.centre.x;
		cylinder.centre.y = newCylinder.centre.y;
		cylinder.centre.z = newCylinder.centre.z;
		cylinder.direction.x = newCylinder.direction.x;
		cylinder.direction.y = newCylinder.direction.y;
		cylinder.direction.z = newCylinder.direction.z;
		cylinder.halfLength = newCylinder.halfLength;
		cylinder.radius = newCylinder.radius;
	}

	// FUNCTION: ENGINE 0x1067AB80
	CollisionCylinderFactory::~CollisionCylinderFactory()
	{
	}

	// FUNCTION: ENGINE 0x1067AB90
	void CollisionCylinderFactory::Clone(CollisionVolumeFactory** copy)
	{
		*copy = new CollisionCylinderFactory(*GetCylinder());
	}

	// FUNCTION: ENGINE 0x1067ABD0
	void CollisionCylinderFactory::SetCylinder(const math::Cylinder* newCylinder)
	{
		cylinder.centre.x = newCylinder->centre.x;
		cylinder.centre.y = newCylinder->centre.y;
		cylinder.centre.z = newCylinder->centre.z;
		cylinder.direction.x = newCylinder->direction.x;
		cylinder.direction.y = newCylinder->direction.y;
		cylinder.direction.z = newCylinder->direction.z;
		cylinder.halfLength = newCylinder->halfLength;
		cylinder.radius = newCylinder->radius;
	}

	// FUNCTION: ENGINE 0x1067AC10
	CollisionOBBFactory::~CollisionOBBFactory()
	{
	}

	// FUNCTION: ENGINE 0x1067AC20
	void CollisionOBBFactory::SetBox(const math::OBB* newBox)
	{
		box = *newBox;
	}

	// FUNCTION: ENGINE 0x1067AC30
	void CollisionOBBFactory::SetAxis1(const math::Vector* axis)
	{
		box.axis[0].x = axis->x;
		box.axis[0].y = axis->y;
		box.axis[0].z = axis->z;
		UpdateAxis3();
	}

	// FUNCTION: ENGINE 0x1067AC50
	void CollisionOBBFactory::SetAxis2(const math::Vector* axis)
	{
		box.axis[1].x = axis->x;
		box.axis[1].y = axis->y;
		box.axis[1].z = axis->z;
		UpdateAxis3();
	}

	// FUNCTION: ENGINE 0x1067AC70
	CollisionPlaneFactory::CollisionPlaneFactory() :
		CollisionVolumeFactory(5)
	{
		plane.normal.x = 0.0f;
		plane.normal.y = 1.0f;
		plane.normal.z = 0.0f;
		plane.d = 0.0f;
	}

	// FUNCTION: ENGINE 0x1067ACB0
	CollisionPlaneFactory::CollisionPlaneFactory(const math::Plane& newPlane) :
		CollisionVolumeFactory(5)
	{
		plane.normal.x = newPlane.normal.x;
		plane.normal.y = newPlane.normal.y;
		plane.normal.z = newPlane.normal.z;
		plane.d = newPlane.d;
	}

	// FUNCTION: ENGINE 0x1067ACE0
	CollisionPlaneFactory::~CollisionPlaneFactory()
	{
	}

	// FUNCTION: ENGINE 0x1067ACF0
	void CollisionPlaneFactory::Clone(CollisionVolumeFactory** copy)
	{
		*copy = new CollisionPlaneFactory(*GetPlane());
	}

	// FUNCTION: ENGINE 0x1067AD30
	void CollisionPlaneFactory::SetPlane(const math::Plane* newPlane)
	{
		float distance = newPlane->d;
		plane.normal.x = newPlane->normal.x;
		plane.normal.y = newPlane->normal.y;
		plane.normal.z = newPlane->normal.z;
		plane.d = distance;
	}

	// FUNCTION: ENGINE 0x1067AD60
	// EQUIVALENT: the same stores; the engine stores the vftable ahead of the unit radius's load, ours behind it, 57.1 %
	CollisionSphereFactory::CollisionSphereFactory() :
		CollisionVolumeFactory(2)
	{
		sphere.centre.x = 0.0f;
		sphere.centre.y = 0.0f;
		sphere.centre.z = 0.0f;
		sphere.radius = 1.0f;
	}

	// FUNCTION: ENGINE 0x1067ADA0
	CollisionSphereFactory::CollisionSphereFactory(const math::Sphere& newSphere) :
		CollisionVolumeFactory(2)
	{
		sphere.centre.x = newSphere.centre.x;
		sphere.centre.y = newSphere.centre.y;
		sphere.centre.z = newSphere.centre.z;
		sphere.radius = newSphere.radius;
	}

	// FUNCTION: ENGINE 0x1067ADD0
	CollisionSphereFactory::~CollisionSphereFactory()
	{
	}

	// FUNCTION: ENGINE 0x1067ADE0
	void CollisionSphereFactory::Clone(CollisionVolumeFactory** copy)
	{
		*copy = new CollisionSphereFactory(*GetSphere());
	}

	// FUNCTION: ENGINE 0x1067AE20
	void CollisionSphereFactory::SetSphere(const math::Sphere* newSphere)
	{
		sphere.centre.x = newSphere->centre.x;
		sphere.centre.y = newSphere->centre.y;
		sphere.centre.z = newSphere->centre.z;
		sphere.radius = newSphere->radius;
	}

	// FUNCTION: ENGINE 0x1067AE40
	CollisionConvexHullFactory::CollisionConvexHullFactory() :
		CollisionVolumeFactory(3)
	{
		hull = new ConvexHullHolder;
	}

	// FUNCTION: ENGINE 0x1067AE80
	CollisionConvexHullFactory::~CollisionConvexHullFactory()
	{
		delete hull;
	}

	// FUNCTION: ENGINE 0x1067AEB0
	CollisionMeshFactory::CollisionMeshFactory() :
		CollisionVolumeFactory(6)
	{
		grid = new BroadPhaseGrid;
	}

	// FUNCTION: ENGINE 0x1067AEF0
	CollisionMeshFactory::~CollisionMeshFactory()
	{
		BroadPhaseGrid* owned = grid;
		if (owned)
		{
			owned->Destroy();
			delete owned;
		}
	}

	// FUNCTION: ENGINE 0x1067B300
	// EQUIVALENT: the same stores; the engine stores the vftable before the first member, 90.3 %
	CollisionOBBFactory::CollisionOBBFactory() :
		CollisionVolumeFactory(1)
	{
		box.centre.x = 0.0f;
		box.centre.y = 0.0f;
		box.centre.z = 0.0f;
		box.axis[0].x = gBoxAxes.values[0];
		box.axis[0].y = gBoxAxes.values[1];
		box.axis[0].z = gBoxAxes.values[2];
		box.axis[1].x = gBoxAxes.values[3];
		box.axis[1].y = gBoxAxes.values[4];
		box.axis[1].z = gBoxAxes.values[5];
		box.axis[2].x = gBoxAxes.values[6];
		box.axis[2].y = gBoxAxes.values[7];
		box.axis[2].z = gBoxAxes.values[8];
		box.extents.x = 1.0f;
		box.extents.y = 1.0f;
		box.extents.z = 1.0f;
	}

	// FUNCTION: ENGINE 0x1067B3D0
	CollisionOBBFactory::CollisionOBBFactory(const math::OBB& newBox) :
		CollisionVolumeFactory(1),
		box(newBox)
	{
	}

	// FUNCTION: ENGINE 0x1067B430
	void CollisionOBBFactory::Clone(CollisionVolumeFactory** copy)
	{
		*copy = new CollisionOBBFactory(*GetBox());
	}

	// FUNCTION: ENGINE 0x1067B7E0
	content::MemberList* CollisionVolumeFactory::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<CollisionVolumeFactory, MaterialLoader>("pn"),
				content::MemberOffset(&((CollisionVolumeFactory*)0)->material,
				(int)&((CollisionVolumeFactory*)0)->material), "material" },
			{ content::GetReferenceMetaType<CollisionVolumeFactory, IntersectionPropertiesLoader>("pn"),
				content::MemberOffset(&((CollisionVolumeFactory*)0)->intersectionProperties,
				(int)&((CollisionVolumeFactory*)0)->intersectionProperties), "intersectionProperties" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

#define FACTORY_OFFSET(Class, member) \
	content::MemberOffset(&((Class*)0)->member, (int)&((Class*)0)->member)
#define FACTORY_BASE(Class) \
	sList.baseType = content::GetClassMetaType<CollisionVolumeFactory>(); \
	static content::BaseClassCasterImpl<CollisionVolumeFactory, Class> sCaster; \
	sList.baseCaster = &sCaster;

	// FUNCTION: ENGINE 0x1067B890
	// EQUIVALENT: the same table, masks and loops; the registers hold the counts, the table and the factory in other places, 24.8 %
	void CollisionMeshFactory::SetFaceProperties(const UShortArray* groups, const UShortArray* propertyIndices,
		bool addDefault)
	{
		BroadPhaseGrid* target = grid;
		target->unknownC8 = true;
		unsigned int count = groups->Size();
		unsigned int total = count;
		if (addDefault)
		{
			total = count + 1;
		}
		IntersectionProperties* table = new IntersectionProperties[total];
		target->materialsBegin = (MeshMaterial*)table;
		target->materialsEnd = (MeshMaterial*)(table + total);
		unsigned int i = 0;
		filter.unknown0 = 0;
		filter.unknown4 = 0;
		unsigned int propertyCount = GetIntersectionPropertyCount();
		unsigned short* remap = 0;
		if (propertyCount != 0)
		{
			remap = (unsigned short*)core::HeapAllocAligned(1, propertyCount * 2, 16);
		}
		for (; i < count; i++)
		{
			unsigned short number = (*propertyIndices)[(*groups)[i]];
			IntersectionPropertiesEntry* entry = GetIntersectionProperty(number);
			table[i].unknown0 = entry->properties.unknown0;
			table[i].unknown4 = entry->properties.unknown4;
			filter.unknown0 |= entry->properties.unknown0;
			filter.unknown4 |= entry->properties.unknown4;
			remap[number] = (unsigned short)i;
		}
		if (addDefault)
		{
			IntersectionPropertiesLoader* properties = intersectionProperties;
			const IntersectionProperties* source;
			unsigned int number;
			if (properties)
			{
				number = properties->index;
				source = (const IntersectionProperties*)&properties->unknown3C;
			}
			else
			{
				source = &GetIntersectionProperty(0)->properties;
				number = 0;
			}
			table[count].unknown0 = source->unknown0;
			table[count].unknown4 = source->unknown4;
			filter.unknown0 |= source->unknown0;
			filter.unknown4 |= source->unknown4;
			remap[number] = (unsigned short)count;
		}
		GridFace* face = target->faces;
		for (unsigned int k = 0; k < target->unknown92; k++)
		{
			unsigned short flags = face->flags;
			face->flags = (((remap[(flags >> 9) & 0x3F] << 9) ^ flags) & 0x7E00) ^ flags;
			face++;
		}
		if (remap)
		{
			core::HeapFreeAligned(1, remap);
		}
	}

	// FUNCTION: ENGINE 0x1067BA60
	content::MemberList* CollisionCapsuleFactory::GetMembers()
	{
		static content::MemberList sList;
		FACTORY_BASE(CollisionCapsuleFactory)
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<CollisionCapsuleFactory, 0>("pn"),
				(int)&((CollisionCapsuleFactory*)0)->capsule.centre, "centre" },
			{ content::GetMemberVectorMetaType<CollisionCapsuleFactory, 1>(&CollisionCapsuleFactory::GetDirection,
				&CollisionCapsuleFactory::SetDirection, "pn"), 0, "axis" },
			{ content::GetMemberPrimitiveMetaType<CollisionCapsuleFactory, float, 0>("pn"),
				FACTORY_OFFSET(CollisionCapsuleFactory, capsule.halfLength), "extent" },
			{ content::GetMemberPrimitiveMetaType<CollisionCapsuleFactory, float, 1>("pn"),
				FACTORY_OFFSET(CollisionCapsuleFactory, capsule.radius), "radius" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1067BB90
	content::MemberList* CollisionCylinderFactory::GetMembers()
	{
		static content::MemberList sList;
		FACTORY_BASE(CollisionCylinderFactory)
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<CollisionCylinderFactory, 0>("pn"),
				(int)&((CollisionCylinderFactory*)0)->cylinder.centre, "centre" },
			{ content::GetMemberVectorMetaType<CollisionCylinderFactory, 1>(&CollisionCylinderFactory::GetDirection,
				&CollisionCylinderFactory::SetDirection, "pn"), 0, "axis" },
			{ content::GetMemberPrimitiveMetaType<CollisionCylinderFactory, float, 0>("pn"),
				FACTORY_OFFSET(CollisionCylinderFactory, cylinder.halfLength), "extent" },
			{ content::GetMemberPrimitiveMetaType<CollisionCylinderFactory, float, 1>("pn"),
				FACTORY_OFFSET(CollisionCylinderFactory, cylinder.radius), "radius" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1067BCC0
	content::MemberList* CollisionOBBFactory::GetMembers()
	{
		static content::MemberList sList;
		FACTORY_BASE(CollisionOBBFactory)
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<CollisionOBBFactory, 0>("pn"),
				(int)&((CollisionOBBFactory*)0)->box.centre, "centre" },
			{ content::GetMemberVectorMetaType<CollisionOBBFactory, 1>(&CollisionOBBFactory::GetAxis1,
				&CollisionOBBFactory::SetAxis1, "pn"), 0, "axis1" },
			{ content::GetMemberVectorMetaType<CollisionOBBFactory, 2>(&CollisionOBBFactory::GetAxis2,
				&CollisionOBBFactory::SetAxis2, "pn"), 0, "axis2" },
			{ content::GetMemberVectorMetaType<CollisionOBBFactory, 3>("pn"),
				(int)&((CollisionOBBFactory*)0)->box.extents, "extents" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1067BDF0
	content::MemberList* CollisionPlaneFactory::GetMembers()
	{
		static content::MemberList sList;
		FACTORY_BASE(CollisionPlaneFactory)
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<CollisionPlaneFactory, 0>("pn"),
				(int)&((CollisionPlaneFactory*)0)->plane.normal, "normal" },
			{ content::GetMemberPrimitiveMetaType<CollisionPlaneFactory, float, 0>("pn"),
				FACTORY_OFFSET(CollisionPlaneFactory, plane.d), "distance" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1067BEC0
	content::MemberList* CollisionSphereFactory::GetMembers()
	{
		static content::MemberList sList;
		FACTORY_BASE(CollisionSphereFactory)
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<CollisionSphereFactory, 0>("pn"),
				(int)&((CollisionSphereFactory*)0)->sphere.centre, "centre" },
			{ content::GetMemberPrimitiveMetaType<CollisionSphereFactory, float, 0>("pn"),
				FACTORY_OFFSET(CollisionSphereFactory, sphere.radius), "radius" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

#undef FACTORY_OFFSET
#undef FACTORY_BASE

	// FUNCTION: ENGINE 0x1067C2B0
	void RegisterCollisionVolumeFactories()
	{
		content::RegisterMetaInstanceCreator<CollisionCapsuleFactory>();
		content::RegisterMetaInstanceCreator<CollisionCylinderFactory>();
		content::RegisterMetaInstanceCreator<CollisionOBBFactory>();
		content::RegisterMetaInstanceCreator<CollisionPlaneFactory>();
		content::RegisterMetaInstanceCreator<CollisionSphereFactory>();
	}

	// The instances of the class templates the factories use
	template void core::RefAssign<MaterialLoader>(MaterialLoader*&, MaterialLoader*);
	template class content::MetaInstanceCreatorImpl<CollisionCapsuleFactory, 1>;
	template class content::MetaInstanceCreatorImpl<CollisionCylinderFactory, 1>;
	template class content::MetaInstanceCreatorImpl<CollisionOBBFactory, 1>;
	template class content::MetaInstanceCreatorImpl<CollisionPlaneFactory, 1>;
	template class content::MetaInstanceCreatorImpl<CollisionSphereFactory, 1>;
	template content::ClassMetaType* content::GetClassMetaType<CollisionCapsuleFactory>();
	template content::ClassMetaType* content::GetClassMetaType<CollisionCylinderFactory>();
	template content::ClassMetaType* content::GetClassMetaType<CollisionOBBFactory>();
	template content::ClassMetaType* content::GetClassMetaType<CollisionPlaneFactory>();
	template content::ClassMetaType* content::GetClassMetaType<CollisionSphereFactory>();
	template void content::RegisterMetaInstanceCreator<CollisionCapsuleFactory>();
	template void content::RegisterMetaInstanceCreator<CollisionCylinderFactory>();
	template void content::RegisterMetaInstanceCreator<CollisionOBBFactory>();
	template void content::RegisterMetaInstanceCreator<CollisionPlaneFactory>();
	template void content::RegisterMetaInstanceCreator<CollisionSphereFactory>();
	// Kept copies of the unit: the empty overrides, the destructors, the casters and the creators, the meta type getters
	// FUNCTION: ENGINE 0x1067A520
	// FUNCTION: ENGINE 0x1067A540
	// FUNCTION: ENGINE 0x1067A590
	// FUNCTION: ENGINE 0x1067A050
	// FUNCTION: ENGINE 0x1067A280
	// FUNCTION: ENGINE 0x1067A320
	// FUNCTION: ENGINE 0x1067A340
	// FUNCTION: ENGINE 0x1067A390
	// FUNCTION: ENGINE 0x1067A3F0
	// FUNCTION: ENGINE 0x1067A4A0
	// FUNCTION: ENGINE 0x1067A5A0
	// FUNCTION: ENGINE 0x1067A5D0
	// FUNCTION: ENGINE 0x1067A600
	// FUNCTION: ENGINE 0x1067A630
	// FUNCTION: ENGINE 0x1067A660
	// FUNCTION: ENGINE 0x1067A690
	// FUNCTION: ENGINE 0x1067A6C0
	// FUNCTION: ENGINE 0x1067A6E0
	// FUNCTION: ENGINE 0x1067A710
	// FUNCTION: ENGINE 0x1067A740
	// FUNCTION: ENGINE 0x1067A770
	// FUNCTION: ENGINE 0x1067A7A0
	// FUNCTION: ENGINE 0x1067A7D0
	// FUNCTION: ENGINE 0x1067A810
	// FUNCTION: ENGINE 0x1067A820
	// FUNCTION: ENGINE 0x1067A850
	// FUNCTION: ENGINE 0x1067A860
	// FUNCTION: ENGINE 0x1067A890
	// FUNCTION: ENGINE 0x1067A8A0
	// FUNCTION: ENGINE 0x1067A8D0
	// FUNCTION: ENGINE 0x1067A8E0
	// FUNCTION: ENGINE 0x1067A910
	// FUNCTION: ENGINE 0x1067A920
	// FUNCTION: ENGINE 0x1067AF70
	// FUNCTION: ENGINE 0x1067AFB0
	// FUNCTION: ENGINE 0x1067AFF0
	// FUNCTION: ENGINE 0x1067B030
	// FUNCTION: ENGINE 0x1067B070
	// FUNCTION: ENGINE 0x1067B0B0
	// FUNCTION: ENGINE 0x1067B100
	// FUNCTION: ENGINE 0x1067B110
	// FUNCTION: ENGINE 0x1067B130
	// FUNCTION: ENGINE 0x1067B150
	// FUNCTION: ENGINE 0x1067B160
	// FUNCTION: ENGINE 0x1067B180
	// FUNCTION: ENGINE 0x1067B1A0
	// FUNCTION: ENGINE 0x1067B1B0
	// FUNCTION: ENGINE 0x1067B1D0
	// FUNCTION: ENGINE 0x1067B1F0
	// FUNCTION: ENGINE 0x1067B200
	// FUNCTION: ENGINE 0x1067B220
	// FUNCTION: ENGINE 0x1067B240
	// FUNCTION: ENGINE 0x1067B260
	// FUNCTION: ENGINE 0x1067B280
	// FUNCTION: ENGINE 0x1067B2A0
	// FUNCTION: ENGINE 0x1067B2C0
	// FUNCTION: ENGINE 0x1067B2E0
	// FUNCTION: ENGINE 0x1067B3B0
	// FUNCTION: ENGINE 0x1067B470
	// FUNCTION: ENGINE 0x1067B490
	// FUNCTION: ENGINE 0x1067B4B0
	// FUNCTION: ENGINE 0x1067B4D0
	// FUNCTION: ENGINE 0x1067B560
	// FUNCTION: ENGINE 0x1067B5B0
	// FUNCTION: ENGINE 0x1067B600
	// FUNCTION: ENGINE 0x1067B670
	// FUNCTION: ENGINE 0x1067B6E0
	// FUNCTION: ENGINE 0x1067B750
	// FUNCTION: ENGINE 0x1067B7C0
	// FUNCTION: ENGINE 0x1067BF90
	// FUNCTION: ENGINE 0x1067BFE0
	// FUNCTION: ENGINE 0x1067C030
	// FUNCTION: ENGINE 0x1067C080
	// FUNCTION: ENGINE 0x1067C0D0
	// FUNCTION: ENGINE 0x1067C120
	// FUNCTION: ENGINE 0x1067C170
	// FUNCTION: ENGINE 0x1067C1C0
	// FUNCTION: ENGINE 0x1067C210
	// FUNCTION: ENGINE 0x1067C260

}

template class VectorMemberGetSetter<ravenphysics::CollisionCapsuleFactory>;
template class VectorMemberGetSetter<ravenphysics::CollisionCylinderFactory>;
template class VectorMemberGetSetter<ravenphysics::CollisionOBBFactory>;

// Kept copies of inline functions and template members this unit makes (compiler-made or header-defined, so the
// annotations stand without a definition)
// FUNCTION: ENGINE 0x1067C460
// FUNCTION: ENGINE 0x1067C610
// FUNCTION: ENGINE 0x1067C680
