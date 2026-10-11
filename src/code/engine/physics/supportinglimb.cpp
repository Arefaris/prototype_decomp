#include "code/engine/physics/supportinglimb.h"
#include "code/container/arraydynamic.h"
#include <float.h>
#include <math.h>

namespace math
{
	// The zero vector (another unit's constant)
	extern const Vector kZeroVector;
}

namespace content
{
	static const EnumValue sOrientationAxisValues[] =
	{
		{ "None", -1 },
		{ "PositiveX", 0 },
		{ "PositiveY", 1 },
		{ "PositiveZ", 2 },
		{ "NegativeX", 3 },
		{ "NegativeY", 4 },
		{ "NegativeZ", 5 }
	};

	// FUNCTION: ENGINE 0x107F2970
	template<> void EnumInfo<engine::SupportingLimbDefinition::ORIENTATION_AXIS>::Get(const char** name,
		const EnumValue** values, int* count, const char** code)
	{
		*name = "engine::SupportingLimbDefinition::ORIENTATION_AXIS";
		*code = "p";
		*values = sOrientationAxisValues;
		*count = 7;
	}
}

namespace engine
{
	// FUNCTION: ENGINE 0x107F29A0
	content::ClassInfo* SupportingLimbDefinition::SmoothingVelocityMap::Entry::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SupportingLimbDefinition::SmoothingVelocityMap::Entry";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107F29E0
	content::ClassInfo* SupportingLimbDefinition::SmoothingVelocityMap::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SupportingLimbDefinition::SmoothingVelocityMap";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107F2A20
	content::ClassInfo* SupportingLimbDefinition::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "SupportingLimbDefinition";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107F2A60
	content::ClassInfo* SupportingLimbDefinitionList::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "SupportingLimbDefinitionList";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107F2AA0
	content::ClassInfo* SupportingLimb::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SupportingLimb";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107F2AE0
	void SupportingLimbDefinition::Slot3(int unused)
	{
		if (intersectionProperties != 0)
		{
			properties.unknown0 = intersectionProperties->unknown3C;
			properties.unknown4 = intersectionProperties->unknown40;
		}
	}

	// FUNCTION: ENGINE 0x107F2B00
	SupportingLimb::RandomRay::RandomRay()
	{
		angle = 0.0f;
		radius = 0.0f;
		active = true;
	}

	// FUNCTION: ENGINE 0x107F3220
	bool SupportingLimbDefinition::SmoothingVelocityMap::IsSorted() const
	{
		bool sorted = true;
		float last = -FLT_MAX;
		for (const Entry* entry = map.Begin(); entry != map.End(); entry++)
		{
			if (last >= entry->characterVelocity)
			{
				sorted = false;
				break;
			}
			last = entry->characterVelocity;
		}
		return sorted;
	}

	// FUNCTION: ENGINE 0x107F3250
	// EQUIVALENT: the engine returns through the argument's stack slot; ours spills the result to a new slot
	float SupportingLimbDefinition::SmoothingVelocityMap::Evaluate(float characterVelocity) const
	{
		const Entry* entry = map.Begin();
		float lastVelocity = entry->characterVelocity;
		float smoothing = entry->smoothingVelocity;
		if (lastVelocity < characterVelocity)
		{
			for (entry++; entry != map.End(); entry++)
			{
				if (entry->characterVelocity > characterVelocity)
				{
					break;
				}
				smoothing = entry->smoothingVelocity;
				lastVelocity = entry->characterVelocity;
			}
			if (entry != map.End())
			{
				smoothing = (entry->smoothingVelocity - smoothing) * (characterVelocity - lastVelocity)
					/ (entry->characterVelocity - lastVelocity) + smoothing;
			}
		}
		return smoothing;
	}

	// FUNCTION: ENGINE 0x107F32D0
	// EQUIVALENT: the engine swaps the vectors component by component through the FPU, ours with dword moves
	void SupportingLimb::Swap(SupportingLimb& other)
	{
		container::Swap(limbDef, other.limbDef);
		container::Swap(castDirection, other.castDirection);
		container::Swap(basisU, other.basisU);
		container::Swap(basisV, other.basisV);
		container::Swap(transform, other.transform);
		container::Swap(unknown68, other.unknown68);
		container::Swap(unknown70, other.unknown70);
	}

	// FUNCTION: ENGINE 0x107F33B0
	// EQUIVALENT: the engine reloads the cast direction after storing the axis; ours keeps its components on the stack
	void SupportingLimb::UpdateBasis()
	{
		// The axis along the smallest component of the cast direction, then two perpendiculars from it
		int smallest;
		{
			float size[3];
			size[0] = fabsf(castDirection.x);
			size[1] = fabsf(castDirection.y);
			size[2] = fabsf(castDirection.z);
			smallest = size[1] <= size[0] ? 1 : 0;
			if (size[2] <= size[smallest])
			{
				smallest = 2;
			}
		}
		math::Vector axis(0.0f, 0.0f, 0.0f);
		(&axis.x)[smallest] = 1.0f;
		basisU.x = axis.y * castDirection.z - axis.z * castDirection.y;
		basisU.y = axis.z * castDirection.x - axis.x * castDirection.z;
		basisU.z = axis.x * castDirection.y - axis.y * castDirection.x;
		basisV.x = castDirection.y * basisU.z - castDirection.z * basisU.y;
		basisV.y = castDirection.z * basisU.x - castDirection.x * basisU.z;
		basisV.z = castDirection.x * basisU.y - castDirection.y * basisU.x;
	}

	// FUNCTION: ENGINE 0x107F4130
	content::MemberList* SupportingLimbDefinition::SmoothingVelocityMap::Entry::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Entry, float, 0>("p"),
				content::MemberOffset(&((Entry*)0)->characterVelocity, (int)&((Entry*)0)->characterVelocity),
				"characterVelocity" },
			{ content::GetMemberPrimitiveMetaType<Entry, float, 1>("p"),
				content::MemberOffset(&((Entry*)0)->smoothingVelocity, (int)&((Entry*)0)->smoothingVelocity),
				"smoothingVelocity" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x107F4830
	content::MemberList* SupportingLimbDefinition::SmoothingVelocityMap::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayCDynamicMetaType<SmoothingVelocityMap, container::ArrayCDynamic<Entry, 3> >(3,
				content::GetClassMetaType<Entry>(), "p"),
				content::MemberOffset(&((SmoothingVelocityMap*)0)->map, (int)&((SmoothingVelocityMap*)0)->map), "map" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x107F48C0
	content::MemberList* SupportingLimbDefinitionList::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<SupportingLimbDefinitionList,
				container::ArrayDynamicNew<SupportingLimbDefinition*> >(
				content::GetReferenceMetaType<SupportingLimbDefinitionList, SupportingLimbDefinition>("p"), "p"),
				content::MemberOffset(&((SupportingLimbDefinitionList*)0)->limbDefs,
				(int)&((SupportingLimbDefinitionList*)0)->limbDefs), "limbDefs" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x107F4950
	// EQUIVALENT: stack slots of the step and angle locals
	void SupportingLimb::SetDefinition(SupportingLimbDefinition* definition)
	{
		core::RefAssign(limbDef, definition);
		if (limbDef != 0)
		{
			castDirection.x = limbDef->direction.x;
			castDirection.y = limbDef->direction.y;
			castDirection.z = limbDef->direction.z;
			UpdateBasis();
			unsigned int count = limbDef->numRandomRays;
			if (count >= 4)
			{
				count = 4;
			}
			else if (count == 0)
			{
				return;
			}
			float radiusStep = 1.0f / (int)count;
			float angleStep = radiusStep * 6.2831855f;
			float angle = 0.0f;
			float radius = 0.0f;
			rays.Insert(rays.End(), count, RandomRay());
			RandomRay* end = rays.End();
			for (RandomRay* ray = rays.Begin(); ray != end; ray++)
			{
				ray->angle = angle;
				ray->radius = radius;
				angle += angleStep;
				radius += radiusStep;
			}
		}
	}

#define ENGINE_LIMB_FLOAT(index, member) \
	{ content::GetMemberPrimitiveMetaType<SupportingLimbDefinition, float, index>("p"), \
		content::MemberOffset(&((SupportingLimbDefinition*)0)->member, (int)&((SupportingLimbDefinition*)0)->member), \
		#member }
#define ENGINE_LIMB_BOOL(index, member) \
	{ content::GetMemberPrimitiveMetaType<SupportingLimbDefinition, bool, index>("p"), \
		content::MemberOffset(&((SupportingLimbDefinition*)0)->member, (int)&((SupportingLimbDefinition*)0)->member), \
		#member }
#define ENGINE_LIMB_VECTOR(index, member) \
	{ content::GetMemberVectorMetaType<SupportingLimbDefinition, index>("p"), \
		(int)&((SupportingLimbDefinition*)0)->member, #member }
#define ENGINE_LIMB_ORIENTATION(member) \
	{ content::GetEnumMetaType<SupportingLimbDefinition::ORIENTATION_AXIS>(), \
		(int)&((SupportingLimbDefinition*)0)->member, #member }

	// FUNCTION: ENGINE 0x107F4B70
	content::MemberList* SupportingLimbDefinition::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<SupportingLimbDefinition>(true, true, "p"),
				content::MemberOffset(&((SupportingLimbDefinition*)0)->name, (int)&((SupportingLimbDefinition*)0)->name),
				"name" },
			ENGINE_LIMB_FLOAT(1, sphereRadius),
			{ content::GetReferenceMetaType<SupportingLimbDefinition, ravenphysics::IntersectionPropertiesLoader>("p"),
				content::MemberOffset(&((SupportingLimbDefinition*)0)->intersectionProperties,
				(int)&((SupportingLimbDefinition*)0)->intersectionProperties), "intersectionProperties" },
			ENGINE_LIMB_VECTOR(3, origin),
			ENGINE_LIMB_VECTOR(4, direction),
			ENGINE_LIMB_FLOAT(5, restingLength),
			ENGINE_LIMB_FLOAT(6, maxLength),
			ENGINE_LIMB_FLOAT(7, cosineSupportAngleTolerance),
			ENGINE_LIMB_BOOL(8, directionFollowsSurfaceNormal),
			ENGINE_LIMB_ORIENTATION(characterSurfaceOrientation),
			ENGINE_LIMB_ORIENTATION(characterUpVectorOrientation),
			ENGINE_LIMB_BOOL(11, smoothRestingLength),
			ENGINE_LIMB_FLOAT(12, smoothMaxLinearVelocity),
			ENGINE_LIMB_FLOAT(13, smoothFractionalMaxLinearVelocity),
			{ content::GetClassMetaType<SmoothingVelocityMap>(),
				content::MemberOffset(&((SupportingLimbDefinition*)0)->smoothMaxLinearVelocityMap,
				(int)&((SupportingLimbDefinition*)0)->smoothMaxLinearVelocityMap), "smoothMaxLinearVelocityMap" },
			ENGINE_LIMB_FLOAT(15, smoothMinRestingLength),
			ENGINE_LIMB_FLOAT(16, smoothMaxRestingLength),
			ENGINE_LIMB_BOOL(17, smoothDirection),
			ENGINE_LIMB_FLOAT(18, smoothMaxAngularVelocity),
			{ content::GetMemberPrimitiveMetaType<SupportingLimbDefinition, unsigned int, 19>("p"),
				content::MemberOffset(&((SupportingLimbDefinition*)0)->numRandomRays,
				(int)&((SupportingLimbDefinition*)0)->numRandomRays), "numRandomRays" },
			ENGINE_LIMB_FLOAT(20, randomRayCircleRadius)
		};
		sList.members = sMembers;
		sList.count = 21;
		return &sList;
	}

#undef ENGINE_LIMB_FLOAT
#undef ENGINE_LIMB_BOOL
#undef ENGINE_LIMB_VECTOR
#undef ENGINE_LIMB_ORIENTATION

	// FUNCTION: ENGINE 0x107F4F00
	content::MemberList* SupportingLimb::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMemberMetaType(&SupportingLimb::GetDefinition, &SupportingLimb::SetDefinition, "p"),
				0, "limbDef" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x107F4FA0
	SupportingLimbDefinition::~SupportingLimbDefinition()
	{
		core::SafeRelease(intersectionProperties);
	}

	// FUNCTION: ENGINE 0x107F4FD0
	SupportingLimbDefinitionList::SupportingLimbDefinitionList()
	{
	}

	// FUNCTION: ENGINE 0x107F4FF0
	SupportingLimbDefinitionList::~SupportingLimbDefinitionList()
	{
		for (unsigned int i = 0; i < limbDefs.Size(); i++)
		{
			core::SafeRelease(limbDefs[i]);
		}
	}

	// FUNCTION: ENGINE 0x107F5050
	// EQUIVALENT: the engine computes the ray array's address before the two stores, ours after them
	SupportingLimb::SupportingLimb()
		: limbDef(0), castDirection(0.0f, 1.0f, 0.0f), transform(math::Matrix::IDENTITY)
	{
		unknown68 = 0.0f;
		unknown70 = false;
		UpdateBasis();
	}

	// FUNCTION: ENGINE 0x107F5160
	SupportingLimb::SupportingLimb(const SupportingLimb& other)
		: limbDef(0), castDirection(0.0f, 1.0f, 0.0f), transform(math::Matrix::IDENTITY), unknown68(0.0f),
		unknown6C(0.0f), unknown70(false)
	{
		core::RefAssign(limbDef, other.limbDef);
		castDirection.x = other.castDirection.x;
		castDirection.y = other.castDirection.y;
		castDirection.z = other.castDirection.z;
		basisU.x = other.basisU.x;
		basisU.y = other.basisU.y;
		basisU.z = other.basisU.z;
		basisV.x = other.basisV.x;
		basisV.y = other.basisV.y;
		basisV.z = other.basisV.z;
		transform = other.transform;
		unknown68 = other.unknown68;
		unknown70 = other.unknown70;
	}

	// FUNCTION: ENGINE 0x107F52E0
	SupportingLimb::~SupportingLimb()
	{
		core::SafeRelease(limbDef);
	}

	// FUNCTION: ENGINE 0x107F5300
	SupportingLimb& SupportingLimb::operator=(const SupportingLimb& other)
	{
		SupportingLimb copy(other);
		Swap(copy);
		return *this;
	}

	// FUNCTION: ENGINE 0x107F53F0
	// EQUIVALENT: the engine stores LoadObject's vftable before pushing the name's arguments, ours after
	SupportingLimbDefinition::SupportingLimbDefinition()
		: name("", 1), sphereRadius(0.2f), unknown1C(0), intersectionProperties(0), origin(math::kZeroVector),
		direction(0.0f, -1.0f, 0.0f), restingLength(1.0f), maxLength(2.0f), cosineSupportAngleTolerance(0.0f),
		directionFollowsSurfaceNormal(false), smoothDirection(true), smoothRestingLength(true),
		characterSurfaceOrientation(None), characterUpVectorOrientation(None), smoothMaxLinearVelocity(3.0f),
		smoothFractionalMaxLinearVelocity(0.0f), smoothMaxAngularVelocity(1.3f), smoothMinRestingLength(0.0f),
		smoothMaxRestingLength(2.0f), numRandomRays(0), randomRayCircleRadius(0.0f)
	{
		properties.unknown0 = -1;
		properties.unknown4 = 4;
	}

	// Kept copies: the containers' explicitly instantiated members, the reflection helpers and meta type getters,
	// the scalar deleting destructors and the copies of SafeRelease / RefAssign / Swap / ConstructAt
	// FUNCTION: ENGINE 0x107F2DC0
	// FUNCTION: ENGINE 0x107F2DD0
	// FUNCTION: ENGINE 0x107F2DE0
	// FUNCTION: ENGINE 0x107F2DF0
	// FUNCTION: ENGINE 0x107F2E00
	// FUNCTION: ENGINE 0x107F2E10
	// FUNCTION: ENGINE 0x107F2E20
	// FUNCTION: ENGINE 0x107F2E30
	// FUNCTION: ENGINE 0x107F2E40
	// FUNCTION: ENGINE 0x107F2E50
	// FUNCTION: ENGINE 0x107F2E60
	// FUNCTION: ENGINE 0x107F2E70
	// FUNCTION: ENGINE 0x107F2E80
	// FUNCTION: ENGINE 0x107F2F30
	// FUNCTION: ENGINE 0x107F2F50
	// FUNCTION: ENGINE 0x107F2F70
	// FUNCTION: ENGINE 0x107F2F80
	// FUNCTION: ENGINE 0x107F2FC0
	// FUNCTION: ENGINE 0x107F2FF0
	// FUNCTION: ENGINE 0x107F3030
	// FUNCTION: ENGINE 0x107F3040
	// FUNCTION: ENGINE 0x107F3050
	// FUNCTION: ENGINE 0x107F3070
	// FUNCTION: ENGINE 0x107F30A0
	// FUNCTION: ENGINE 0x107F30C0
	// FUNCTION: ENGINE 0x107F31C0
	// FUNCTION: ENGINE 0x107F3830
	// FUNCTION: ENGINE 0x107F3880
	// FUNCTION: ENGINE 0x107F38C0
	// FUNCTION: ENGINE 0x107F3900
	// FUNCTION: ENGINE 0x107F3940
	// FUNCTION: ENGINE 0x107F3980
	// FUNCTION: ENGINE 0x107F39C0
	// FUNCTION: ENGINE 0x107F3A00
	// FUNCTION: ENGINE 0x107F3A40
	// FUNCTION: ENGINE 0x107F3A80
	// FUNCTION: ENGINE 0x107F3AC0
	// FUNCTION: ENGINE 0x107F3B00
	// FUNCTION: ENGINE 0x107F3B40
	// FUNCTION: ENGINE 0x107F3B80
	// FUNCTION: ENGINE 0x107F3BC0
	// FUNCTION: ENGINE 0x107F3C00
	// FUNCTION: ENGINE 0x107F3C40
	// FUNCTION: ENGINE 0x107F3CF0
	// FUNCTION: ENGINE 0x107F3D00
	// FUNCTION: ENGINE 0x107F3D30
	// FUNCTION: ENGINE 0x107F3D40
	// FUNCTION: ENGINE 0x107F3D50
	// FUNCTION: ENGINE 0x107F3D60
	// FUNCTION: ENGINE 0x107F3DD0
	// FUNCTION: ENGINE 0x107F3DF0
	// FUNCTION: ENGINE 0x107F3E00
	// FUNCTION: ENGINE 0x107F3E20
	// FUNCTION: ENGINE 0x107F3E30
	// FUNCTION: ENGINE 0x107F3E40
	// FUNCTION: ENGINE 0x107F3EA0
	// FUNCTION: ENGINE 0x107F3EB0
	// FUNCTION: ENGINE 0x107F3EC0
	// FUNCTION: ENGINE 0x107F3ED0
	// FUNCTION: ENGINE 0x107F3EE0
	// FUNCTION: ENGINE 0x107F3F60
	// FUNCTION: ENGINE 0x107F3F70
	// FUNCTION: ENGINE 0x107F3F80
	// FUNCTION: ENGINE 0x107F3F90
	// FUNCTION: ENGINE 0x107F3FA0
	// FUNCTION: ENGINE 0x107F3FB0
	// FUNCTION: ENGINE 0x107F3FD0
	// FUNCTION: ENGINE 0x107F3FE0
	// FUNCTION: ENGINE 0x107F4070
	// FUNCTION: ENGINE 0x107F4430
	// FUNCTION: ENGINE 0x107F4480
	// FUNCTION: ENGINE 0x107F4490
	// FUNCTION: ENGINE 0x107F44A0
	// FUNCTION: ENGINE 0x107F44B0
	// FUNCTION: ENGINE 0x107F4500
	// FUNCTION: ENGINE 0x107F4550
	// FUNCTION: ENGINE 0x107F45A0
	// FUNCTION: ENGINE 0x107F45F0
	// FUNCTION: ENGINE 0x107F4660
	// FUNCTION: ENGINE 0x107F4A40
	// FUNCTION: ENGINE 0x107F4A50
	// FUNCTION: ENGINE 0x107F4A70
	// FUNCTION: ENGINE 0x107F4A80
	// FUNCTION: ENGINE 0x107F4AD0
	// FUNCTION: ENGINE 0x107F4B10
	// FUNCTION: ENGINE 0x107F4F80
	// FUNCTION: ENGINE 0x107F4F90
	// FUNCTION: ENGINE 0x107F5500
	// FUNCTION: ENGINE 0x107F5520
}

// The containers' explicit instantiations
namespace container
{
	template class ArrayCDynamic<engine::SupportingLimbDefinition::SmoothingVelocityMap::Entry, 3>;
	template class ArrayCDynamic<engine::SupportingLimb::RandomRay, 4>;
	template class ArrayDynamicNew<engine::SupportingLimbDefinition*>;
}
