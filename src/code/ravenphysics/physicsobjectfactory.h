// The content library objects that make physics objects (RTTI: ravenphysics::AbstractPhysicsObjectFactory, the
// simple kind that makes a body of one volume, and ravenphysics::PhysicsObjectFactory, which makes a body of several
// collision objects tied to a skeleton, with the constraints between them). Unit 0x1066C680 - 0x1066F5C0 (no assert
// path, so the file name is a guess); the reflected member names are the engine's own, the others are guesses.
#ifndef RAVENPHYSICS_PHYSICSOBJECTFACTORY_H
#define RAVENPHYSICS_PHYSICSOBJECTFACTORY_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/collisionvolumefactory.h"
#include "code/ravenphysics/massproperties.h"

namespace pure3d
{
	class Skeleton;
}

namespace ravenphysics
{
	class ConstraintListFactory;
	class PhysicsObject;
	struct PhysicsLink;

	// The base of the factories: makes a physics object and answers its handle (slot 7)
	class AbstractPhysicsObjectFactory : public content::MetaLoadObject
	{
	public:
		// How the objects made move (reflected as "ravenphysics::AbstractPhysicsObjectFactory::CollisionType")
		enum CollisionType
		{
			Static = 0,
			Keyframed = 1,
			Simulating = 2
		};

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// Slot 2 is the deleting destructor of the compiler (0x1066D1E0), slot 6 takes the name (0x1066D190)
		virtual void SetName(const content::ObjectName& newName);
		// The name the factory is kept under (0x1066C820; name guess)
		core::Name<core::CaseSensitiveKey>* GetName();
		// Slot 7: makes the physics object and answers its handle
		virtual CollisionHandle CreatePhysicsObject() = 0;

		core::Name<core::CaseSensitiveKey> name;   // 0x08
	};

	// A factory of a body made of one collision object around one volume
	class SimplePhysicsObjectFactory : public AbstractPhysicsObjectFactory
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x1066DF60
		SimplePhysicsObjectFactory();
		// Lets go of the volume factory and the mass properties (0x1066D200; deleting destructor 0x1066DF90)
		virtual ~SimplePhysicsObjectFactory();
		// Slot 7: a collision object around the volume of the factory, and a body around it (0x1066D240)
		virtual CollisionHandle CreatePhysicsObject();

		// The volume factory, which the factory owns (0x1066C850 / 0x1066C860)
		CollisionVolumeFactory* GetVolumeFactory() const;
		void SetVolumeFactory(CollisionVolumeFactory* newFactory);
		// The mass properties the body is given (0x1066C890 / 0x1066D2D0)
		MassProperties* GetMassProperties() const;
		void SetMassProperties(MassProperties* newProperties);
		// How the body moves, and whether it is a rigid body (0x1066C8A0 / 0x1066C8B0 and 0x1066C8C0 / 0x1066C8D0)
		CollisionType GetCollisionType() const;
		void SetCollisionType(CollisionType type);
		bool GetCreateRigidBody() const;
		void SetCreateRigidBody(bool value);
		// Marks the object's shape as keyframed when the factory says so (0x1066C8E0; name guess)
		void ApplyCollisionType(CollisionObject* object) const;

		CollisionVolumeFactory* volumeFactory;     // 0x10
		CollisionType collisionType;               // 0x14
		bool createRigidBody;                      // 0x18
		MassProperties* massProperties;            // 0x1C
	};

	class PhysicsObjectFactory : public AbstractPhysicsObjectFactory
	{
	public:
		// The volume of an object: a factory the description owns (RTTI: PhysicsObjectFactory::VolumeDescription)
		struct VolumeDescription
		{
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// A description of no factory (0x1066C910)
			VolumeDescription();
			// Deletes the factory (0x1066C920)
			~VolumeDescription();
			// Makes the volume (0x1066C940), sets it on a collision object (0x1066C950), adds its bounds (0x1066C970)
			CollisionVolume* CreateVolume() const;
			void SetOnObject(CollisionObject* object, int index) const;
			void GetBounds(math::AABB* bounds) const;

			CollisionVolumeFactory* factory;
		};

		typedef container::ArrayDynamic<VolumeDescription, container::AllocatorNew> VolumeArray;

		// Six numbers of an object, copied as a whole (name guess)
		struct Extents
		{
			float values[6];
		};

		// A collision object of the body (RTTI: PhysicsObjectFactory::ObjectDescription, 0x50 bytes)
		struct ObjectDescription
		{
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// The defaults (0x1066EC70), a copy (0x1066EA60), the assignment (0x1066E5E0) and the end (0x1066ECE0)
			ObjectDescription();
			ObjectDescription(const ObjectDescription& other);
			ObjectDescription& operator=(const ObjectDescription& other);
			~ObjectDescription();

			// The accessors of the description (0x1066C9C0 - 0x1066CB30)
			const core::Name<core::CaseSensitiveKey>& GetName() const;
			AbstractPhysicsObjectFactory::CollisionType GetCollisionType() const;
			void SetCollisionType(AbstractPhysicsObjectFactory::CollisionType type);
			bool GetCreateRigidBody() const;
			void SetCreateRigidBody(bool value);
			bool GetUnknown1D() const;
			void SetUnknown1D(bool value);
			math::Vector* GetOffset();
			void SetOffset(const math::Vector* value);
			Extents* GetExtents();
			void SetExtents(const Extents* value);
			float GetScale() const;
			void SetScale(float value);
			MassProperties* GetMassProperties() const;
			void SetMassProperties(MassProperties* newProperties);

			// Marks the object's shape as keyframed when the description says so (0x1066CB40; name guess)
			void ApplyCollisionType(CollisionObject* object) const;

			// A collision object around the volumes (0x1066D2F0), the volumes set on an object (0x1066D3C0), and the
			// bounds of the volumes (0x1066D420)
			CollisionObject* CreateCollisionObject();
			void SetVolumes(CollisionObject* object);
			void GetBounds(float* bounds);

			core::Name<core::CaseSensitiveKey> parentJoint;     // 0x00
			VolumeArray volumes;                                // 0x08
			int unknown14;                                      // 0x14
			AbstractPhysicsObjectFactory::CollisionType collisionType;  // 0x18
			bool createRigidBody;                               // 0x1C
			bool unknown1D;                                     // 0x1D
			math::Vector offset;                                // 0x20
			Extents extents;                                    // 0x2C
			float scale;                                        // 0x44
			MassProperties* massProperties;                     // 0x48
			int unknown4C;                                      // 0x4C
		};

		typedef container::ArrayDynamic<ObjectDescription, container::AllocatorNew> ObjectArray;

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// Starts with a link of its own (0x1066F430)
		PhysicsObjectFactory();
		// Lets go of the objects, the skeleton and the link (0x1066F4A0; deleting destructor 0x1066F5A0)
		virtual ~PhysicsObjectFactory();
		// Slot 3 (0x1066E050): fills the link's tables once the factory is complete
		virtual void Slot3(int unused);
		// Slot 7: the collision objects, the body around them and the constraints (0x1066E110)
		virtual CollisionHandle CreatePhysicsObject();

		// The constraints the link carries (0x1066CC60 / 0x1066D960)
		ConstraintListFactory* GetConstraintsFactory() const;
		void SetConstraintsFactory(ConstraintListFactory* factory);
		// The skeleton the objects follow (0x1066D780)
		void SetSkeleton(pure3d::Skeleton* newSkeleton);
		// The number of objects and the object at an index (0x1066D760 / 0x1066D7A0)
		int GetObjectCount() const;
		ObjectDescription* GetObject(int index);
		// Turns the collision between two of the objects on or off (0x1066D7E0)
		void SetPairEnabled(unsigned int first, unsigned int second, bool enabled);
		// The joints of the skeleton and the objects that follow them (0x1066D830)
		void MapJoints();
		// The box around all the volumes (0x1066D620)
		void GetBounds(float* bounds);

		pure3d::Skeleton* skeleton;            // 0x10
		ObjectArray objects;                   // 0x14
		int unknown20;                         // 0x20
		PhysicsLink* link;                     // 0x24
		PhysicsObjectFactory* sourcePhysicsObject;  // 0x28
	};
}

namespace container
{
	// The volume descriptions are moved like pointers (the loop keeps the distance of its two pointers in a register),
	// the object descriptions are too large for the compiler to inline the assignment of their elements
	template<> struct ArrayEraseInline<ravenphysics::PhysicsObjectFactory::VolumeDescription>
	{
		enum
		{
			value = 3
		};
	};
	template<> struct ArrayEraseInline<ravenphysics::PhysicsObjectFactory::ObjectDescription>
	{
		enum
		{
			value = 0
		};
	};

	template<> struct ArrayReserveBeginFirst<ravenphysics::PhysicsObjectFactory::VolumeDescription>
	{
		enum
		{
			value = 1
		};
	};
	template<> struct ArrayReserveBeginFirst<ravenphysics::PhysicsObjectFactory::ObjectDescription>
	{
		enum
		{
			value = 1
		};
	};
}

#endif
