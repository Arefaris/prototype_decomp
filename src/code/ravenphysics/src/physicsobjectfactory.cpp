// The factories that make physics objects, their reflection and the arrays their descriptions live in (unit
// 0x1066C680 - 0x1066F5C0, no assert path, so the file name is a guess).
#include "code/container/arraydynamicallocatornew.h"
#include "code/container/arraydynamicstatic.h"
#include "code/content/vectormetatype.h"
#include "code/core/refptr.h"
#include "code/ravenphysics/constraintlistfactory.h"
#include "code/pure3d/pose.h"
#include "code/ravenphysics/physicsobject.h"
#include "code/ravenphysics/physicsobjectfactory.h"
#include <new>

namespace content
{
	static const EnumValue sCollisionTypeValues[] =
	{
		{ "Static", 0 },
		{ "Keyframed", 1 },
		{ "Simulating", 2 }
	};

	// FUNCTION: ENGINE 0x1066C680
	template<> void EnumInfo<ravenphysics::AbstractPhysicsObjectFactory::CollisionType>::Get(const char** name,
		const EnumValue** values, int* count, const char** code)
	{
		*name = "ravenphysics::AbstractPhysicsObjectFactory::CollisionType";
		*code = "pn";
		*values = sCollisionTypeValues;
		*count = 3;
	}
}

namespace ravenphysics
{
#define PHYSICSFACTORY_OFFSET(Class, member) \
	content::MemberOffset(&((Class*)0)->member, (int)&((Class*)0)->member)

	// FUNCTION: ENGINE 0x1066C6B0
	content::ClassInfo* AbstractPhysicsObjectFactory::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::AbstractPhysicsObjectFactory";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1066C6F0
	content::MemberList* AbstractPhysicsObjectFactory::GetMembers()
	{
		static content::MemberList sList;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1066C720
	content::ClassInfo* SimplePhysicsObjectFactory::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::SimplePhysicsObjectFactory";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1066C760
	content::ClassInfo* PhysicsObjectFactory::VolumeDescription::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::PhysicsObjectFactory::VolumeDescription";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1066C7A0
	content::ClassInfo* PhysicsObjectFactory::ObjectDescription::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::PhysicsObjectFactory::ObjectDescription";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1066C7E0
	content::ClassInfo* PhysicsObjectFactory::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::PhysicsObjectFactory";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1066C820
	core::Name<core::CaseSensitiveKey>* AbstractPhysicsObjectFactory::GetName()
	{
		return &name;
	}

	// FUNCTION: ENGINE 0x1066D190
	void AbstractPhysicsObjectFactory::SetName(const content::ObjectName& newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x1066DF60
	// EQUIVALENT: the same stores and the same call; the engine drops the dead store of the base class's vftable before the name's constructor, ours keeps it, 63.5 %
	SimplePhysicsObjectFactory::SimplePhysicsObjectFactory() :
		volumeFactory(0),
		collisionType(Static),
		createRigidBody(false),
		massProperties(0)
	{
	}

	// FUNCTION: ENGINE 0x1066D200
	SimplePhysicsObjectFactory::~SimplePhysicsObjectFactory()
	{
		if (volumeFactory != 0)
		{
			delete volumeFactory;
			volumeFactory = 0;
		}
		core::SafeRelease(massProperties);
	}
}

namespace ravenphysics
{
	// The mass properties applied to the object's shape (0x1066C830; the engine passes the properties in ecx and the
	// object in eax)
	static void ApplyMassProperties(MassProperties* properties, CollisionObject* object)
	{
		if (properties != 0 && object->shape != 0)
		{
			properties->ApplyTo(object);
		}
	}

	// FUNCTION: ENGINE 0x1066C850
	CollisionVolumeFactory* SimplePhysicsObjectFactory::GetVolumeFactory() const
	{
		return volumeFactory;
	}

	// FUNCTION: ENGINE 0x1066C860
	void SimplePhysicsObjectFactory::SetVolumeFactory(CollisionVolumeFactory* newFactory)
	{
		if (volumeFactory != 0)
		{
			delete volumeFactory;
		}
		volumeFactory = newFactory;
	}

	// FUNCTION: ENGINE 0x1066C890
	MassProperties* SimplePhysicsObjectFactory::GetMassProperties() const
	{
		return massProperties;
	}

	// FUNCTION: ENGINE 0x1066C8A0
	SimplePhysicsObjectFactory::CollisionType SimplePhysicsObjectFactory::GetCollisionType() const
	{
		return collisionType;
	}

	// FUNCTION: ENGINE 0x1066C8B0
	void SimplePhysicsObjectFactory::SetCollisionType(CollisionType type)
	{
		collisionType = type;
	}

	// FUNCTION: ENGINE 0x1066C8C0
	bool SimplePhysicsObjectFactory::GetCreateRigidBody() const
	{
		return createRigidBody;
	}

	// FUNCTION: ENGINE 0x1066C8D0
	void SimplePhysicsObjectFactory::SetCreateRigidBody(bool value)
	{
		createRigidBody = value;
	}
}


namespace ravenphysics
{
	// FUNCTION: ENGINE 0x1066C8E0
	void SimplePhysicsObjectFactory::ApplyCollisionType(CollisionObject* object) const
	{
		if (object->shape != 0 && collisionType != Static && collisionType == Keyframed)
		{
			object->shape->SetFlag2(1);
		}
	}

	// FUNCTION: ENGINE 0x1066C910
	PhysicsObjectFactory::VolumeDescription::VolumeDescription()
	{
		factory = 0;
	}

	// FUNCTION: ENGINE 0x1066C920
	PhysicsObjectFactory::VolumeDescription::~VolumeDescription()
	{
		if (factory != 0)
		{
			delete factory;
			factory = 0;
		}
	}

	// FUNCTION: ENGINE 0x1066C940
	CollisionVolume* PhysicsObjectFactory::VolumeDescription::CreateVolume() const
	{
		return factory->CreateVolume();
	}

	// FUNCTION: ENGINE 0x1066C950
	void PhysicsObjectFactory::VolumeDescription::SetOnObject(CollisionObject* object, int index) const
	{
		if (factory != 0 && object != 0)
		{
			factory->SetOnObject(object, index);
		}
	}

	// FUNCTION: ENGINE 0x1066C970
	void PhysicsObjectFactory::VolumeDescription::GetBounds(math::AABB* bounds) const
	{
		if (factory == 0)
		{
			bounds->Reset();
			return;
		}
		factory->GetBounds(bounds);
	}

	const core::Name<core::CaseSensitiveKey>& PhysicsObjectFactory::ObjectDescription::GetName() const
	{
		return parentJoint;
	}

	AbstractPhysicsObjectFactory::CollisionType PhysicsObjectFactory::ObjectDescription::GetCollisionType() const
	{
		return collisionType;
	}

	void PhysicsObjectFactory::ObjectDescription::SetCollisionType(AbstractPhysicsObjectFactory::CollisionType type)
	{
		collisionType = type;
	}

	bool PhysicsObjectFactory::ObjectDescription::GetCreateRigidBody() const
	{
		return createRigidBody;
	}

	void PhysicsObjectFactory::ObjectDescription::SetCreateRigidBody(bool value)
	{
		createRigidBody = value;
	}

	bool PhysicsObjectFactory::ObjectDescription::GetUnknown1D() const
	{
		return unknown1D;
	}

	void PhysicsObjectFactory::ObjectDescription::SetUnknown1D(bool value)
	{
		unknown1D = value;
	}

	math::Vector* PhysicsObjectFactory::ObjectDescription::GetOffset()
	{
		return &offset;
	}

	void PhysicsObjectFactory::ObjectDescription::SetOffset(const math::Vector* value)
	{
		offset.x = value->x;
		offset.y = value->y;
		offset.z = value->z;
	}

	PhysicsObjectFactory::Extents* PhysicsObjectFactory::ObjectDescription::GetExtents()
	{
		return &extents;
	}

	void PhysicsObjectFactory::ObjectDescription::SetExtents(const Extents* value)
	{
		extents = *value;
	}

	float PhysicsObjectFactory::ObjectDescription::GetScale() const
	{
		return scale;
	}

	void PhysicsObjectFactory::ObjectDescription::SetScale(float value)
	{
		scale = value;
	}

	MassProperties* PhysicsObjectFactory::ObjectDescription::GetMassProperties() const
	{
		return massProperties;
	}

	// FUNCTION: ENGINE 0x1066CB40
	void PhysicsObjectFactory::ObjectDescription::ApplyCollisionType(CollisionObject* object) const
	{
		if (object->shape != 0 && collisionType != Static && collisionType == Keyframed)
		{
			object->shape->SetFlag2(1);
		}
	}
}


namespace ravenphysics
{
	// FUNCTION: ENGINE 0x1066D240
	CollisionHandle SimplePhysicsObjectFactory::CreatePhysicsObject()
	{
		CollisionHandle handle;
		if (volumeFactory != 0)
		{
			core::Name<core::CaseSensitiveKey>* objectName = GetName();
			CollisionObject* object = CreateCollisionObject(volumeFactory->CreateVolume(), createRigidBody, 1.0f);
			object->SetName(*objectName);
			ApplyCollisionType(object);
			ApplyMassProperties(massProperties, object);
			PhysicsObject* body = PhysicsObject::Create(object);
			body->SetName(*objectName);
			body->AddRef();
			handle.value = body->id;
		}
		return handle;
	}

	// FUNCTION: ENGINE 0x1066D2D0
	void SimplePhysicsObjectFactory::SetMassProperties(MassProperties* newProperties)
	{
		core::RefAssign(massProperties, newProperties);
	}

	// FUNCTION: ENGINE 0x1066D2F0
	CollisionObject* PhysicsObjectFactory::ObjectDescription::CreateCollisionObject()
	{
		CollisionObject* object = 0;
		unsigned int count = volumes.Size();
		if (count != 0)
		{
			CollisionVolume** array = new CollisionVolume*[count];
			VolumeDescription* last = volumes.end;
			unsigned int index = 0;
			for (VolumeDescription* volume = volumes.begin; volume != last; volume++, index++)
			{
				array[index] = volume->CreateVolume();
			}
			const math::Vector* first = unknown1D ? 0 : &offset;
			const Extents* second = unknown1D ? 0 : &extents;
			object = ravenphysics::CreateCollisionObject(array, count, createRigidBody, scale, (int)first, (int)second);
			object->SetName(parentJoint);
			ApplyMassProperties(massProperties, object);
			ApplyCollisionType(object);
		}
		return object;
	}

	// FUNCTION: ENGINE 0x1066D3C0
	void PhysicsObjectFactory::ObjectDescription::SetVolumes(CollisionObject* object)
	{
		ApplyCollisionType(object);
		VolumeDescription* last = volumes.end;
		int index = 0;
		for (VolumeDescription* volume = volumes.begin; volume != last; volume++)
		{
			volume->SetOnObject(object, index);
			index++;
		}
		if (unknown1D && object->shape != 0)
		{
			object->shape->Refresh();
		}
	}

	// A box grown by another (the engine's inline form)
	static inline void GrowBounds(float* total, const math::AABB& box)
	{
		float low = total[0];
		if (!(box.min.x > low))
		{
			low = box.min.x;
		}
		total[0] = low;
		low = total[1];
		if (!(box.min.y > low))
		{
			low = box.min.y;
		}
		total[1] = low;
		low = total[2];
		if (!(box.min.z > low))
		{
			low = box.min.z;
		}
		total[2] = low;
		float high = total[3];
		if (high < box.max.x)
		{
			high = box.max.x;
		}
		total[3] = high;
		high = total[4];
		if (high < box.max.y)
		{
			high = box.max.y;
		}
		total[4] = high;
		high = total[5];
		if (high < box.max.z)
		{
			high = box.max.z;
		}
		total[5] = high;
	}

	// FUNCTION: ENGINE 0x1066D420
	// EQUIVALENT: the same loop and the same comparisons; the engine loads the two constants for the next box in the other order, 99.3 %
	void PhysicsObjectFactory::ObjectDescription::GetBounds(float* bounds)
	{
		math::AABB* total = (math::AABB*)bounds;
		total->Reset();
		VolumeDescription* last = volumes.end;
		for (VolumeDescription* volume = volumes.begin; volume != last; volume++)
		{
			math::AABB box;
			box.Reset();
			volume->GetBounds(&box);
			GrowBounds(bounds, box);
		}
	}

	// FUNCTION: ENGINE 0x1066D620
	// EQUIVALENT: the same loop and the same comparisons; the engine loads the two constants for the next box in the other order, 99.3 %
	void PhysicsObjectFactory::GetBounds(float* bounds)
	{
		math::AABB* total = (math::AABB*)bounds;
		total->Reset();
		ObjectDescription* last = objects.end;
		for (ObjectDescription* object = objects.begin; object != last; object++)
		{
			math::AABB box;
			box.Reset();
			object->GetBounds((float*)&box);
			GrowBounds(bounds, box);
		}
	}

	// FUNCTION: ENGINE 0x1066D600
	void PhysicsObjectFactory::ObjectDescription::SetMassProperties(MassProperties* newProperties)
	{
		core::RefAssign(massProperties, newProperties);
	}

	// FUNCTION: ENGINE 0x1066D760
	int PhysicsObjectFactory::GetObjectCount() const
	{
		return objects.Size();
	}

	// FUNCTION: ENGINE 0x1066D780
	void PhysicsObjectFactory::SetSkeleton(pure3d::Skeleton* newSkeleton)
	{
		core::RefAssign(skeleton, newSkeleton);
	}

	// FUNCTION: ENGINE 0x1066D7A0
	PhysicsObjectFactory::ObjectDescription* PhysicsObjectFactory::GetObject(int index)
	{
		return &objects.begin[index];
	}

	// FUNCTION: ENGINE 0x1066D7E0
	void PhysicsObjectFactory::SetPairEnabled(unsigned int first, unsigned int second, bool enabled)
	{
		SetBit(link->pairMask, GetPairIndex(objects.Size(), first, second), enabled);
	}

	// FUNCTION: ENGINE 0x1066D830
	// EQUIVALENT: the same stores and calls in the same order; the engine keeps the object index in ebp and the name pointer in ebx and has a stack slot less, ours the other way round, 37.3 %
	void PhysicsObjectFactory::MapJoints()
	{
		unsigned int object = 0;
		if (link->skeletonJointCount == 0 && skeleton != 0)
		{
			link->skeletonJointCount = (unsigned short)skeleton->mData.mJointCount;
			unsigned int count = objects.Size();
			link->jointOfObject = new unsigned short[count];
			link->objectOfJoint = new unsigned short[link->skeletonJointCount];
			for (unsigned int joint = 0; joint < link->skeletonJointCount; joint++)
			{
				link->objectOfJoint[joint] = 0xFFFF;
			}
			if (count > 0)
			{
				do
				{
					const core::Name<core::CaseSensitiveKey>* jointName = &objects.begin[object].GetName();
					__declspec(align(8)) core::Name<core::CaseSensitiveKey> empty(0, 1);
					unsigned int joint;
					if (*jointName != empty)
					{
						joint = skeleton->FindJoint(*jointName);
					}
					else
					{
						joint = 0xFFFF;
					}
					link->jointOfObject[object] = (unsigned short)joint;
					if (joint < link->skeletonJointCount)
					{
						link->objectOfJoint[joint] = (unsigned short)object;
					}
					object++;
				}
				while (object < count);
			}
		}
	}

	// FUNCTION: ENGINE 0x1066D960
	void PhysicsObjectFactory::SetConstraintsFactory(ConstraintListFactory* factory)
	{
		core::RefAssign(link->joints, (JointSet*)factory);
	}

	// FUNCTION: ENGINE 0x1066CC60
	ConstraintListFactory* PhysicsObjectFactory::GetConstraintsFactory() const
	{
		return (ConstraintListFactory*)link->joints;
	}
}


namespace ravenphysics
{
	// The bytes of a mask of the pairs among count objects (0x1066CB70; the engine passes the count in eax)
	static unsigned int PairMaskSize(int count)
	{
		return (CountPairs(count) + 7) >> 3;
	}

	// Makes the mask with every pair on, unless there is one (0x1066CB80; the engine passes the mask's address in edi
	// and the count in esi)
	static void CreatePairMask(unsigned char** mask, int count)
	{
		if (*mask == 0)
		{
			unsigned int size = PairMaskSize(count);
			*mask = new unsigned char[size];
			for (unsigned int i = 0; i < size; i++)
			{
				(*mask)[i] = 0xFF;
			}
		}
	}

	// FUNCTION: ENGINE 0x1066E050
	void PhysicsObjectFactory::Slot3(int unused)
	{
		PhysicsLink* current = link;
		if (current->joints != 0)
		{
			unsigned int count;
			if (sourcePhysicsObject != 0)
			{
				count = sourcePhysicsObject->objects.Size();
			}
			else
			{
				count = objects.Size();
			}
			if (current->pairMask == 0 && count > 0)
			{
				CreatePairMask(&current->pairMask, count);
				((ConstraintListFactory*)link->joints)->ApplyPairMask(link->pairMask, count);
			}
			if (sourcePhysicsObject != 0)
			{
				sourcePhysicsObject->SetConstraintsFactory((ConstraintListFactory*)link->joints);
				if (count > 0)
				{
					unsigned int size = PairMaskSize(count);
					sourcePhysicsObject->link->pairMask = new unsigned char[size];
					for (unsigned int i = 0; i < size; i++)
					{
						sourcePhysicsObject->link->pairMask[i] = link->pairMask[i];
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1066E110
	CollisionHandle PhysicsObjectFactory::CreatePhysicsObject()
	{
		CollisionHandle handle;
		if (sourcePhysicsObject != 0)
		{
			handle = sourcePhysicsObject->CreatePhysicsObject();
		}
		else
		{
			unsigned int count = objects.Size();
			if (count != 0)
			{
				CollisionObject** array = new CollisionObject*[count];
				unsigned int i;
				for (i = 0; i < count; i++)
				{
					array[i] = objects.begin[i].CreateCollisionObject();
				}
				MapJoints();
				PhysicsLink* usedLink = link->skeletonJointCount != 0 ? link : 0;
				PhysicsObject* body = PhysicsObject::Create(array, count, usedLink);
				if (body == 0)
				{
					delete[] array;
				}
				body->SetName(*GetName());
				body->AddRef();
				handle.value = body->id;
				for (i = 0; i < count; i++)
				{
					array[i]->owner = body;
				}
			}
		}
		return handle;
	}

	// FUNCTION: ENGINE 0x1066E5E0
	PhysicsObjectFactory::ObjectDescription& PhysicsObjectFactory::ObjectDescription::operator=(
		const ObjectDescription& other)
	{
		parentJoint = other.parentJoint;
		volumes = other.volumes;
		collisionType = other.collisionType;
		createRigidBody = other.createRigidBody;
		unknown1D = other.unknown1D;
		offset.x = other.offset.x;
		offset.y = other.offset.y;
		offset.z = other.offset.z;
		extents = other.extents;
		scale = other.scale;
		massProperties = other.massProperties;
		return *this;
	}

	// FUNCTION: ENGINE 0x1066EA60
	PhysicsObjectFactory::ObjectDescription::ObjectDescription(const ObjectDescription& other) :
		parentJoint(other.parentJoint),
		volumes(other.volumes),
		collisionType(other.collisionType),
		createRigidBody(other.createRigidBody),
		unknown1D(other.unknown1D),
		offset(other.offset),
		extents(other.extents),
		scale(other.scale),
		massProperties(other.massProperties)
	{
	}

	// FUNCTION: ENGINE 0x1066EC70
	PhysicsObjectFactory::ObjectDescription::ObjectDescription() :
		collisionType(Static),
		createRigidBody(false),
		unknown1D(true),
		offset(0.0f, 0.0f, 0.0f),
		massProperties(0)
	{
		scale = 1.0f;
		extents.values[2] = 1.0f;
		extents.values[1] = 1.0f;
		extents.values[0] = 1.0f;
		extents.values[5] = 0.0f;
		extents.values[4] = 0.0f;
		extents.values[3] = 0.0f;
	}

	// FUNCTION: ENGINE 0x1066ECE0
	PhysicsObjectFactory::ObjectDescription::~ObjectDescription()
	{
		core::SafeRelease(massProperties);
	}

	// FUNCTION: ENGINE 0x1066F430
	// EQUIVALENT: the same stores and calls; the engine drops the dead store of the base class's vftable before the name's constructor, ours keeps it, 48.5 %
	PhysicsObjectFactory::PhysicsObjectFactory() :
		skeleton(0),
		link(0),
		sourcePhysicsObject(0)
	{
		link = new PhysicsLink;
		link->AddRef();
	}

	// FUNCTION: ENGINE 0x1066F4A0
	PhysicsObjectFactory::~PhysicsObjectFactory()
	{
		core::SafeRelease(sourcePhysicsObject);
		core::SafeRelease(link);
		core::SafeRelease(skeleton);
	}
}


namespace ravenphysics
{
	// FUNCTION: ENGINE 0x1066E7B0
	content::MemberList* SimplePhysicsObjectFactory::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<AbstractPhysicsObjectFactory>();
		static content::BaseClassCasterImpl<AbstractPhysicsObjectFactory, SimplePhysicsObjectFactory> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetObjectMetaType<CollisionVolumeFactory>("pn"),
				PHYSICSFACTORY_OFFSET(SimplePhysicsObjectFactory, volumeFactory), "volumeFactory" },
			{ content::GetEnumMetaType<CollisionType>(),
				(int)&((SimplePhysicsObjectFactory*)0)->collisionType, "collisionType" },
			{ content::GetMemberPrimitiveMetaType<SimplePhysicsObjectFactory, bool, 0>("pn"),
				PHYSICSFACTORY_OFFSET(SimplePhysicsObjectFactory, createRigidBody), "createRigidBody" },
			{ content::GetReferenceMetaType<SimplePhysicsObjectFactory, MassProperties>("pn"),
				PHYSICSFACTORY_OFFSET(SimplePhysicsObjectFactory, massProperties), "massProperties" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1066E8D0
	content::MemberList* PhysicsObjectFactory::VolumeDescription::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetObjectMetaTypeCopy<CollisionVolumeFactory>("pn"),
				PHYSICSFACTORY_OFFSET(VolumeDescription, factory), "factory" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1066EB50
	content::MemberList* PhysicsObjectFactory::ObjectDescription::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<ObjectDescription>(true, true, "pn"),
				PHYSICSFACTORY_OFFSET(ObjectDescription, parentJoint), "parentJoint" },
			{ content::GetArrayDynamicMetaType<ObjectDescription, VolumeArray>(
				content::GetClassMetaType<VolumeDescription>(), "pn"),
				PHYSICSFACTORY_OFFSET(ObjectDescription, volumes), "volumes" },
			{ content::GetEnumMetaType<AbstractPhysicsObjectFactory::CollisionType>(),
				(int)&((ObjectDescription*)0)->collisionType, "collisionType" },
			{ content::GetMemberPrimitiveMetaType<ObjectDescription, bool, 0>("pn"),
				PHYSICSFACTORY_OFFSET(ObjectDescription, createRigidBody), "createRigidBody" },
			{ content::GetReferenceMetaType<ObjectDescription, MassProperties>("pn"),
				PHYSICSFACTORY_OFFSET(ObjectDescription, massProperties), "massProperties" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1066EE80
	content::MemberList* PhysicsObjectFactory::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<AbstractPhysicsObjectFactory>();
		static content::BaseClassCasterImpl<AbstractPhysicsObjectFactory, PhysicsObjectFactory> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<PhysicsObjectFactory, pure3d::Skeleton>("pn"),
				PHYSICSFACTORY_OFFSET(PhysicsObjectFactory, skeleton), "skeleton" },
			{ content::GetArrayDynamicMetaType<PhysicsObjectFactory, ObjectArray>(
				content::GetClassMetaType<ObjectDescription>(), "pn"),
				PHYSICSFACTORY_OFFSET(PhysicsObjectFactory, objects), "objects" },
			{ content::GetReferenceMetaType<PhysicsObjectFactory, PhysicsObjectFactory>("pn"),
				PHYSICSFACTORY_OFFSET(PhysicsObjectFactory, sourcePhysicsObject), "sourcePhysicsObject" },
			{ content::GetReferenceMemberMetaType(&PhysicsObjectFactory::GetConstraintsFactory,
				&PhysicsObjectFactory::SetConstraintsFactory, "pn"), 0, "constraintsFactory" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}
}

namespace container
{
	template class ArrayDynamic<ravenphysics::PhysicsObjectFactory::VolumeDescription, AllocatorNew>;
	template class ArrayDynamic<ravenphysics::PhysicsObjectFactory::ObjectDescription, AllocatorNew>;
}

namespace content
{
	template ClassMetaType* GetClassMetaType<ravenphysics::AbstractPhysicsObjectFactory>();
	template ClassMetaType* GetClassMetaType<ravenphysics::PhysicsObjectFactory::VolumeDescription>();
	template ClassMetaType* GetClassMetaType<ravenphysics::PhysicsObjectFactory::ObjectDescription>();
	template ClassMetaType* GetClassMetaType<ravenphysics::CollisionVolumeFactory>();
}

// Kept copies of the unit's inline functions and template instances
// FUNCTION: ENGINE 0x1066C830
// FUNCTION: ENGINE 0x1066CA40
// FUNCTION: ENGINE 0x1066CA50
// FUNCTION: ENGINE 0x1066CA60
// FUNCTION: ENGINE 0x1066CA70
// FUNCTION: ENGINE 0x1066CA80
// FUNCTION: ENGINE 0x1066CA90
// FUNCTION: ENGINE 0x1066CAA0
// FUNCTION: ENGINE 0x1066CAB0
// FUNCTION: ENGINE 0x1066CAD0
// FUNCTION: ENGINE 0x1066CAE0
// FUNCTION: ENGINE 0x1066CB10
// FUNCTION: ENGINE 0x1066CB20
// FUNCTION: ENGINE 0x1066CB30
// FUNCTION: ENGINE 0x1066CB70
// FUNCTION: ENGINE 0x1066CB80
// FUNCTION: ENGINE 0x1066CCB0
// FUNCTION: ENGINE 0x1066CD00
// FUNCTION: ENGINE 0x1066CD20
// FUNCTION: ENGINE 0x1066CD30
// FUNCTION: ENGINE 0x1066CD50
// FUNCTION: ENGINE 0x1066CDB0
// FUNCTION: ENGINE 0x1066CE00
// FUNCTION: ENGINE 0x1066CE70
// FUNCTION: ENGINE 0x1066CF00
// FUNCTION: ENGINE 0x1066CF60
// FUNCTION: ENGINE 0x1066CF90
// FUNCTION: ENGINE 0x1066CFB0
// FUNCTION: ENGINE 0x1066CFE0
// FUNCTION: ENGINE 0x1066D000
// FUNCTION: ENGINE 0x1066D030
// FUNCTION: ENGINE 0x1066D050
// FUNCTION: ENGINE 0x1066D0A0
// FUNCTION: ENGINE 0x1066D0B0
// FUNCTION: ENGINE 0x1066D0E0
// FUNCTION: ENGINE 0x1066D120
// FUNCTION: ENGINE 0x1066D160
// FUNCTION: ENGINE 0x1066D1A0
// EQUIVALENT: the same stores; the engine loads the address of the name between the stores of the reference count and of the second vftable, ours before the reference count, 73.5 %
// FUNCTION: ENGINE 0x1066D1D0
// FUNCTION: ENGINE 0x1066D1E0
// FUNCTION: ENGINE 0x1066D980
// FUNCTION: ENGINE 0x1066D990
// FUNCTION: ENGINE 0x1066D9E0
// FUNCTION: ENGINE 0x1066DA10
// FUNCTION: ENGINE 0x1066DA20
// FUNCTION: ENGINE 0x1066DA70
// FUNCTION: ENGINE 0x1066DAB0
// FUNCTION: ENGINE 0x1066DAF0
// FUNCTION: ENGINE 0x1066DB00
// FUNCTION: ENGINE 0x1066DB40
// FUNCTION: ENGINE 0x1066DB70
// FUNCTION: ENGINE 0x1066DB80
// FUNCTION: ENGINE 0x1066DBA0
// FUNCTION: ENGINE 0x1066DBE0
// FUNCTION: ENGINE 0x1066DC00
// FUNCTION: ENGINE 0x1066DC20
// FUNCTION: ENGINE 0x1066DC40
// FUNCTION: ENGINE 0x1066DC70
// FUNCTION: ENGINE 0x1066DE10
// FUNCTION: ENGINE 0x1066DE20
// FUNCTION: ENGINE 0x1066DE30
// FUNCTION: ENGINE 0x1066DE50
// FUNCTION: ENGINE 0x1066DE70
// FUNCTION: ENGINE 0x1066DE80
// FUNCTION: ENGINE 0x1066DF20
// FUNCTION: ENGINE 0x1066DF90
// FUNCTION: ENGINE 0x1066E2C0
// FUNCTION: ENGINE 0x1066E2F0
// FUNCTION: ENGINE 0x1066E340
// FUNCTION: ENGINE 0x1066E390
// FUNCTION: ENGINE 0x1066E3E0
// FUNCTION: ENGINE 0x1066E430
// FUNCTION: ENGINE 0x1066E480
// FUNCTION: ENGINE 0x1066E4D0
// FUNCTION: ENGINE 0x1066E520
// FUNCTION: ENGINE 0x1066E570
// FUNCTION: ENGINE 0x1066E990
// FUNCTION: ENGINE 0x1066E9D0
// FUNCTION: ENGINE 0x1066EA20
// FUNCTION: ENGINE 0x1066EAE0
// FUNCTION: ENGINE 0x1066EB20
// FUNCTION: ENGINE 0x1066ED30
// FUNCTION: ENGINE 0x1066ED80
// FUNCTION: ENGINE 0x1066EDA0
// FUNCTION: ENGINE 0x1066EDC0
// FUNCTION: ENGINE 0x1066EE40
// FUNCTION: ENGINE 0x1066EFC0
// FUNCTION: ENGINE 0x1066EFF0
// FUNCTION: ENGINE 0x1066F000
// FUNCTION: ENGINE 0x1066F0B0
// FUNCTION: ENGINE 0x1066F170
// FUNCTION: ENGINE 0x1066F2E0
// FUNCTION: ENGINE 0x1066F360
// FUNCTION: ENGINE 0x1066F3A0
// FUNCTION: ENGINE 0x1066F400
// FUNCTION: ENGINE 0x1066F500
// FUNCTION: ENGINE 0x1066F5A0
// FUNCTION: ENGINE 0x1066E660
// FUNCTION: ENGINE 0x1066F1A0
// FUNCTION: ENGINE 0x1066F1E0
// FUNCTION: ENGINE 0x1066E6A0
