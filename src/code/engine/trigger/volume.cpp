#include "code/engine/trigger/volume.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/math/matrix3.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/context.h"
#include "code/ravenphysics/physicsobject.h"

namespace ravenphysics
{
	// What the physics library takes to make an object: the properties it collides with and one more word that is zero here
	// (name guessed)
	struct ObjectProperties
	{
		ObjectProperties()
		{
			unknown8 = 0;
		}

		IntersectionProperties properties;
		int unknown8;
	};

	// 0x1066AA80 (another unit): makes the physics object of a volume with the properties; answers out (name guessed)
	ObjectHandle* CreateObject(ObjectHandle* out, CollisionVolume* shape, const ObjectProperties* properties);
}

namespace engine
{
	namespace trigger
	{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

		// FUNCTION: ENGINE 0x10841550
		content::ClassInfo* Volume::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::trigger::Volume";
			sInfo.code = "pn";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10841590
		content::ClassInfo* SphereVolume::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::trigger::SphereVolume";
			sInfo.code = "pn";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x108415D0
		content::ClassInfo* OBBVolume::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::trigger::OBBVolume";
			sInfo.code = "pn";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10841BC0
		Volume::Volume()
			: interactionMask(0xFFFFFFFF)
		{
			handle.value = 0xFFFFFFFF;
			owner = 0;
		}

		// 0x10841BE0 is the compiler's scalar deleting destructor of this class
		// FUNCTION: ENGINE 0x10841BE0
		// FUNCTION: ENGINE 0x10841830
		Volume::~Volume()
		{
			if (handle.IsValid())
			{
				handle.DestroyObject();
			}
		}

		// FUNCTION: ENGINE 0x10841610
		bool Volume::IsOwnerReady()
		{
			return owner->IsReady();
		}

		// FUNCTION: ENGINE 0x10841630
		void Volume::Slot4()
		{
		}

		// FUNCTION: ENGINE 0x10841640
		void Volume::Slot5()
		{
		}

		// FUNCTION: ENGINE 0x10841620
		ravenphysics::ObjectHandle* Volume::GetHandle()
		{
			return &handle;
		}

		// FUNCTION: ENGINE 0x10841650
		GameObjectHandle Volume::GetOwnerHandle()
		{
			return engine::GetHandle(owner);
		}
		// FUNCTION: ENGINE 0x10841870
		void Volume::SetObjectTransform(const math::Matrix& transform)
		{
			if (handle.IsValid())
			{
				((ravenphysics::TriggerObject*)handle.GetObjectUnchecked())->SetTransform(transform);
			}
		}

		// FUNCTION: ENGINE 0x108418B0
		void Volume::GetOwnerTransform(math::Matrix* out)
		{
			*out = owner->transform->value;
		}

		// FUNCTION: ENGINE 0x108418D0
		void Volume::ApplyFilter()
		{
			if (handle.IsValid())
			{
				ravenphysics::IntersectionFilter filter;
				if (kind == 1)
				{
					filter.properties.unknown0 = 0x80000000;
					filter.properties.unknown4 = interactionMask & 0x7FFFFFFF;
				}
				else
				{
					filter.properties.unknown0 = interactionMask & 0x7FFFFFFF;
					filter.properties.unknown4 = 0x80000000;
				}
				((ravenphysics::TriggerObject*)handle.GetObjectUnchecked())->SetFilter(&filter);
			}
		}

		// FUNCTION: ENGINE 0x10841C00
		void Volume::SetKind(int newKind)
		{
			kind = newKind;
			if (interactionMask == 0)
			{
				interactionMask = 0x400;
			}
			CreateObject();
			ApplyFilter();
		}

		// FUNCTION: ENGINE 0x10841C30
		void Volume::SetOwner(GameObjectHandle newOwner)
		{
			owner = newOwner.Get();
		}

		// FUNCTION: ENGINE 0x10841C70
		void Volume::SetInteractionMask(unsigned int mask)
		{
			interactionMask = mask;
			ApplyFilter();
		}

		// FUNCTION: ENGINE 0x10841CD0
		SphereVolume::SphereVolume()
		{
			sphere.centre.x = 0.0f;
			sphere.centre.y = 0.0f;
			sphere.centre.z = 0.0f;
			sphere.radius = 0.0f;
		}

		// FUNCTION: ENGINE 0x10841C80
		SphereVolume::SphereVolume(const math::Sphere& newSphere)
		{
			sphere.centre.x = newSphere.centre.x;
			sphere.centre.y = newSphere.centre.y;
			sphere.centre.z = newSphere.centre.z;
			sphere.radius = newSphere.radius;
		}

		// FUNCTION: ENGINE 0x10841670
		void SphereVolume::Slot4()
		{
		}

		// FUNCTION: ENGINE 0x10841680
		void SphereVolume::CreateObject()
		{
			ravenphysics::CollisionSphere* shape = new ravenphysics::CollisionSphere(sphere);
			ravenphysics::ObjectProperties properties;
			ravenphysics::ObjectHandle created;
			handle.value = ravenphysics::CreateObject(&created, shape, &properties)->value;
		}

		// FUNCTION: ENGINE 0x108419D0
		void SphereVolume::ApplyShape()
		{
			if (handle.IsValid())
			{
				math::Matrix transform;
				GetOwnerTransform(&transform);
				((ravenphysics::TriggerObject*)handle.GetObjectUnchecked())->SetSphere(sphere, transform);
			}
			ApplyFilter();
		}

		// FUNCTION: ENGINE 0x10841960
		void SphereVolume::SetSphere(const math::Sphere& newSphere)
		{
			sphere.centre.x = newSphere.centre.x;
			sphere.centre.y = newSphere.centre.y;
			sphere.centre.z = newSphere.centre.z;
			sphere.radius = newSphere.radius;
			if (handle.IsValid())
			{
				math::Matrix transform;
				GetOwnerTransform(&transform);
				((ravenphysics::TriggerObject*)handle.GetObjectUnchecked())->SetSphere(newSphere, transform);
			}
		}

		// FUNCTION: ENGINE 0x10841740
		void OBBVolume::Slot4()
		{
		}

		// FUNCTION: ENGINE 0x108416E0
		void OBBVolume::CreateObject()
		{
			ravenphysics::CollisionOBB* shape = new ravenphysics::CollisionOBB(box);
			ravenphysics::ObjectProperties properties;
			ravenphysics::ObjectHandle created;
			handle.value = ravenphysics::CreateObject(&created, shape, &properties)->value;
		}

		// FUNCTION: ENGINE 0x10841AA0
		void OBBVolume::ApplyShape()
		{
			if (handle.IsValid())
			{
				math::Matrix transform;
				GetOwnerTransform(&transform);
				((ravenphysics::TriggerObject*)handle.GetObjectUnchecked())->SetBox(box, transform);
			}
			ApplyFilter();
		}

		// FUNCTION: ENGINE 0x10841A30
		void OBBVolume::SetBox(const math::OBB& newBox)
		{
			box = newBox;
			if (handle.IsValid())
			{
				math::Matrix transform;
				GetOwnerTransform(&transform);
				((ravenphysics::TriggerObject*)handle.GetObjectUnchecked())->SetBox(newBox, transform);
			}
		}
		// FUNCTION: ENGINE 0x10841D90
		OBBVolume::OBBVolume()
		{
			math::Matrix3 rotation;
			rotation.Identity();
			box.centre.x = 0.0f;
			box.centre.y = 0.0f;
			box.centre.z = 0.0f;
			box.axis[0].x = rotation.m[0][0];
			box.axis[0].y = rotation.m[0][1];
			box.axis[0].z = rotation.m[0][2];
			box.axis[1].x = rotation.m[1][0];
			box.axis[1].y = rotation.m[1][1];
			box.axis[1].z = rotation.m[1][2];
			box.axis[2].x = rotation.m[2][0];
			box.axis[2].y = rotation.m[2][1];
			box.axis[2].z = rotation.m[2][2];
			box.extents.x = 1.0f;
			box.extents.y = 1.0f;
			box.extents.z = 1.0f;
		}

		// FUNCTION: ENGINE 0x10841D00
		OBBVolume::OBBVolume(const math::OBB& newBox)
			: box(newBox)
		{
		}

		// FUNCTION: ENGINE 0x10841B40
		content::MemberList* Volume::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetMemberPrimitiveMetaType<Volume, unsigned int, 0>("pn"), ENGINE_OFFSET(Volume, interactionMask),
					"interactionMask" }
			};
			sList.members = sMembers;
			sList.count = 1;
			return &sList;
		}

		// FUNCTION: ENGINE 0x10841E40
		content::MemberList* SphereVolume::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<Volume>();
			static content::BaseClassCasterImpl<Volume, SphereVolume> sCaster;
			sList.baseCaster = &sCaster;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetClassMetaType<math::Sphere>(), ENGINE_OFFSET(SphereVolume, sphere), "sphere" }
			};
			sList.members = sMembers;
			sList.count = 1;
			return &sList;
		}

		// FUNCTION: ENGINE 0x10841EE0
		content::MemberList* OBBVolume::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<Volume>();
			static content::BaseClassCasterImpl<Volume, OBBVolume> sCaster;
			sList.baseCaster = &sCaster;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetClassMetaType<math::OBB>(), ENGINE_OFFSET(OBBVolume, box), "box" }
			};
			sList.members = sMembers;
			sList.count = 1;
			return &sList;
		}
	}
}

// Kept copies (template instances of this unit):
// FUNCTION: ENGINE 0x10841750
// FUNCTION: ENGINE 0x108417A0
// FUNCTION: ENGINE 0x108417B0
// FUNCTION: ENGINE 0x108417C0
// FUNCTION: ENGINE 0x108417F0
// FUNCTION: ENGINE 0x10841800
// FUNCTION: ENGINE 0x10841B00
// FUNCTION: ENGINE 0x10841CB0
// FUNCTION: ENGINE 0x10841D70
