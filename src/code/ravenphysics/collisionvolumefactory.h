// The collision volume factories (RTTI: ravenphysics::CollisionVolumeFactory and its capsule, cylinder, OBB, plane,
// sphere, convex hull and mesh kinds): the plain objects a physics object description lists its volumes as. A factory
// holds the numbers of one shape and the material and intersection properties of the volume, makes the volume
// (CreateVolume) or sets it on a collision object, and tells its bounds. The five geometric kinds are reflected and
// made by the content library through instance creators. Unit 0x10679D00 - 0x1067C400 (no assert path, so the file
// name is a guess); the reflected member names are the engine's own.
#ifndef RAVENPHYSICS_COLLISIONVOLUMEFACTORY_H
#define RAVENPHYSICS_COLLISIONVOLUMEFACTORY_H

#include "code/container/arraydynamicstatic.h"
#include "code/content/metatype.h"
#include "code/math/aabb.h"
#include "code/math/capsule.h"
#include "code/math/obb.h"
#include "code/math/plane.h"
#include "code/math/sphere.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/intersectionproperties.h"
#include "code/ravenphysics/material.h"

namespace ravenphysics
{
	class IntersectionPropertiesLoader;

	// The pointer a convex hull factory keeps its hull in (4 bytes; 0x1067FB00 / 0x10680600, another unit)
	struct ConvexHullHolder
	{
		ConvexHullHolder();
		~ConvexHullHolder();

		ConvexHullData* data;
	};

	// Makes the instance creators of the five geometric kinds known to the content library (0x1067C2B0)
	void RegisterCollisionVolumeFactories();

	// The base class (5 vftable slots)
	class CollisionVolumeFactory
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// A factory of no kind (0x10679E80) and one of the given volume type (0x10679EA0)
		CollisionVolumeFactory();
		explicit CollisionVolumeFactory(unsigned char newType);
		// 0: lets go of the material and the properties (0x1067A950; deleting destructor 0x1067B2A0)
		virtual ~CollisionVolumeFactory();
		// 1: a new volume of the factory's shape, with the material and the filter of the properties set
		virtual CollisionVolume* CreateVolume() = 0;
		// 2: a copy of the factory
		virtual void Clone(CollisionVolumeFactory** copy) = 0;
		// 3: sets the factory's shape as the volume of an object
		virtual void SetOnObject(CollisionObject* object, int index) = 0;
		// 4: the box around the shape
		virtual void GetBounds(math::AABB* bounds) = 0;

		// The material loader (0x10679EC0) and the intersection properties (0x10679ED0)
		MaterialLoader* GetMaterial() const;
		IntersectionPropertiesLoader* GetIntersectionProperties() const;
		// Takes the properties (0x1067A990)
		void SetIntersectionProperties(IntersectionPropertiesLoader* properties);
		// Gives a volume the factory's material and filter (0x10679EE0)
		void ApplyTo(CollisionVolume* volume);

		MaterialLoader* material;                             // 0x04
		IntersectionPropertiesLoader* intersectionProperties; // 0x08
		unsigned char type;                                   // 0x0C (the volume type, 0xFF for none)
	};

	class CollisionCapsuleFactory : public CollisionVolumeFactory
	{
	public:
		virtual ~CollisionCapsuleFactory();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The unit capsule (0x1067A9B0) and a copy of one (0x1067AA00)
		CollisionCapsuleFactory();
		explicit CollisionCapsuleFactory(const math::Capsule& newCapsule);
		virtual CollisionVolume* CreateVolume();
		virtual void Clone(CollisionVolumeFactory** copy);
		virtual void SetOnObject(CollisionObject* object, int index);
		virtual void GetBounds(math::AABB* bounds);

		// The capsule (0x10679FA0 / 0x1067AAA0) and its direction (0x10679FB0 / 0x10679FC0; the setter normalises)
		math::Capsule* GetCapsule();
		void SetCapsule(const math::Capsule* newCapsule);
		const math::Vector* GetDirection() const;
		void SetDirection(const math::Vector* direction);

		math::Capsule capsule;        // 0x10
	};

	class CollisionCylinderFactory : public CollisionVolumeFactory
	{
	public:
		virtual ~CollisionCylinderFactory();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The unit cylinder (0x1067AAE0) and a copy of one (0x1067AB30)
		CollisionCylinderFactory();
		explicit CollisionCylinderFactory(const math::Cylinder& newCylinder);
		virtual CollisionVolume* CreateVolume();
		virtual void Clone(CollisionVolumeFactory** copy);
		// The cylinder is not set on an object (empty)
		virtual void SetOnObject(CollisionObject* object, int index)
		{
		}
		virtual void GetBounds(math::AABB* bounds);

		// The cylinder (0x1067A070 / 0x1067ABD0) and its axis (0x1067A0C0 / 0x1067A0D0; the setter normalises)
		math::Cylinder* GetCylinder();
		void SetCylinder(const math::Cylinder* newCylinder);
		const math::Vector* GetDirection() const;
		void SetDirection(const math::Vector* direction);

		math::Cylinder cylinder;      // 0x10
	};

	class CollisionOBBFactory : public CollisionVolumeFactory
	{
	public:
		virtual ~CollisionOBBFactory();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The unit box (0x1067B300) and a copy of one (0x1067B3D0)
		CollisionOBBFactory();
		explicit CollisionOBBFactory(const math::OBB& newBox);
		virtual CollisionVolume* CreateVolume();
		virtual void Clone(CollisionVolumeFactory** copy);
		virtual void SetOnObject(CollisionObject* object, int index);
		virtual void GetBounds(math::AABB* bounds);

		// The box (0x1067A190 / 0x1067AC20)
		math::OBB* GetBox();
		void SetBox(const math::OBB* newBox);
		// The first two axes (0x1067A1A0 / 0x1067AC30 and 0x1067A1B0 / 0x1067AC50); the setters work the third out
		const math::Vector* GetAxis1() const;
		void SetAxis1(const math::Vector* axis);
		const math::Vector* GetAxis2() const;
		void SetAxis2(const math::Vector* axis);
		// The third axis from the first two (0x1067A1C0)
		void UpdateAxis3();

		math::OBB box;                // 0x10
	};

	class CollisionPlaneFactory : public CollisionVolumeFactory
	{
	public:
		virtual ~CollisionPlaneFactory();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The plane through the origin with the up normal (0x1067AC70) and a copy of one (0x1067ACB0)
		CollisionPlaneFactory();
		explicit CollisionPlaneFactory(const math::Plane& newPlane);
		virtual CollisionVolume* CreateVolume();
		virtual void Clone(CollisionVolumeFactory** copy);
		virtual void SetOnObject(CollisionObject* object, int index);
		// A plane has no bounds (empty)
		virtual void GetBounds(math::AABB* bounds)
		{
		}

		// The plane (0x1067A290 / 0x1067AD30)
		math::Plane* GetPlane();
		void SetPlane(const math::Plane* newPlane);

		math::Plane plane;            // 0x10
	};

	class CollisionSphereFactory : public CollisionVolumeFactory
	{
	public:
		virtual ~CollisionSphereFactory();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The unit sphere (0x1067AD60) and a copy of one (0x1067ADA0)
		CollisionSphereFactory();
		explicit CollisionSphereFactory(const math::Sphere& newSphere);
		virtual CollisionVolume* CreateVolume();
		virtual void Clone(CollisionVolumeFactory** copy);
		virtual void SetOnObject(CollisionObject* object, int index);
		virtual void GetBounds(math::AABB* bounds);

		// The sphere (0x1067A310 / 0x1067AE20)
		math::Sphere* GetSphere();
		void SetSphere(const math::Sphere* newSphere);

		math::Sphere sphere;          // 0x10
	};

	class CollisionConvexHullFactory : public CollisionVolumeFactory
	{
	public:
		// A factory with a hull holder of its own (0x1067AE40)
		CollisionConvexHullFactory();
		virtual ~CollisionConvexHullFactory();
		virtual CollisionVolume* CreateVolume();
		virtual void Clone(CollisionVolumeFactory** copy)
		{
		}
		virtual void SetOnObject(CollisionObject* object, int index)
		{
		}
		virtual void GetBounds(math::AABB* bounds);

		ConvexHullHolder* hull;       // 0x10
	};

	class CollisionMeshFactory : public CollisionVolumeFactory
	{
	public:
		// A factory with an empty grid of its own (0x1067AEB0)
		CollisionMeshFactory();
		virtual ~CollisionMeshFactory();
		virtual CollisionVolume* CreateVolume();
		virtual void Clone(CollisionVolumeFactory** copy)
		{
		}
		virtual void SetOnObject(CollisionObject* object, int index)
		{
		}
		virtual void GetBounds(math::AABB* bounds);

		// The numbers of the faces' properties (a list of face groups, each naming one of the properties) become the
		// grid's own table of properties; the factory's own are added when asked (0x1067B890; name guess)
		typedef container::ArrayDynamic<unsigned short, container::AllocatorCoreStatic<1, 16> > UShortArray;
		void SetFaceProperties(const UShortArray* groups, const UShortArray* propertyIndices, bool addDefault);

		BroadPhaseGrid* grid;         // 0x10
		IntersectionProperties filter;  // 0x14
	};
}

#endif
