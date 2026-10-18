#include "code/engine/physics/supportinglimb.h"
#include "code/container/arraydynamic.h"
#include "code/math/mathconstants.h"
#include "code/math/mathutils.h"
#include "code/math/sincos.h"
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
			filter.properties.unknown0 = intersectionProperties->unknown3C;
			filter.properties.unknown4 = intersectionProperties->unknown40;
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
	// EQUIVALENT: the engine returns through the argument's stack slot; ours spills the result to a new slot. The first
	// test is `!(first >= velocity)`, as the engine branches on it (an unordered velocity enters the search)
	float SupportingLimbDefinition::SmoothingVelocityMap::Evaluate(float characterVelocity) const
	{
		const Entry* entry = map.Begin();
		float lastVelocity = entry->characterVelocity;
		float smoothing = entry->smoothingVelocity;
		if (!(lastVelocity >= characterVelocity))
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
	// EQUIVALENT: the engine reloads the cast direction after storing the axis; ours keeps its components on the stack.
	// The comparisons are written as the engine branches on them: an unordered pair takes the same side
	void SupportingLimb::UpdateBasis()
	{
		// The axis along the smallest component of the cast direction, then two perpendiculars from it
		int smallest;
		{
			float size[3];
			size[0] = fabsf(castDirection.x);
			size[1] = fabsf(castDirection.y);
			size[2] = fabsf(castDirection.z);
			smallest = size[1] > size[0] ? 0 : 1;
			if (!(size[2] > size[smallest]))
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

	// FUNCTION: ENGINE 0x107F2B20
	// EQUIVALENT: the engine computes the end point as x, z, y (y as length * normal.y) and loads the normal's z
	// before its y; ours x, y, z
	void SupportingLimb::GetSupportPlane(const math::Matrix& m, math::Plane& plane) const
	{
		math::Vector back = -castDirection;
		math::Vector normal;
		m.Rotate(back, normal);
		float length = -unknown68;
		const math::Vector& origin = limbDef->origin;
		math::Vector end(normal.x * length + origin.x, normal.y * length + origin.y, normal.z * length + origin.z);
		plane.normal.Set(normal.x, normal.y, normal.z);
		plane.d = -normal.Dot(end);
	}

	// FUNCTION: ENGINE 0x107F2BF0
	// Moves value towards target by at most maxVelocity * dt, then clamps it to [minValue, maxValue]
	void SmoothValue(float* value, float target, float dt, float maxVelocity, float minValue, float maxValue)
	{
		if (!math::IsEqual(*value, target, math::EPSILON_SMALL))
		{
			float delta = target - *value;
			float step = dt * maxVelocity;
			float fraction = math::Clamp(math::Clamp(delta, -step, step) / delta, 0.0f, 1.0f);
			*value = fraction * delta + *value;
			*value = math::Clamp(*value, minValue, maxValue);
		}
	}

	// Which axis completes a pair of different axes (-1 for the same axis twice)
	static const signed char sThirdAxis[3][3] =
	{
		{ -1, 2, 1 },
		{ 2, -1, 0 },
		{ 1, 0, -1 }
	};

	// FUNCTION: ENGINE 0x107F34D0
	// out = the unit cross product of the two axis vectors, in the order that keeps the axes right-handed
	void CrossAxes(const math::Vector& a, int axisA, const math::Vector& b, int axisB, math::Vector& out)
	{
		const math::Vector* first = &a;
		const math::Vector* second = &b;
		if ((unsigned int)(axisB + 1) % 3 == (unsigned int)axisA)
		{
			first = &b;
			second = &a;
		}
		out.Set(first->y * second->z - first->z * second->y, first->z * second->x - first->x * second->z,
			first->x * second->y - first->y * second->x);
		out.NormalizeFast();
	}

	// FUNCTION: ENGINE 0x107F3560
	// EQUIVALENT: the engine keeps the axis in esi (saved first) and the direction in ecx; ours the axis in ecx and the
	// direction in edx, esi saved later
	// Rotates m so that its axis (ORIENTATION_AXIS) points along direction
	void AlignAxis(int axis, const math::Vector& direction, math::Matrix& m)
	{
		math::Vector target = axis / 3 != 0 ? -direction : direction;
		math::Vector current(*(const math::Vector*)m.m[axis % 3]);
		if (!math::IsEqual(current.x, target.x, math::EPSILON_SMALL)
			|| !math::IsEqual(current.y, target.y, math::EPSILON_SMALL)
			|| !math::IsEqual(current.z, target.z, math::EPSILON_SMALL))
		{
			float cosine = math::Clamp(current.Dot(target), -1.0f, 1.0f);
			if (cosine != 1.0f)
			{
				math::Matrix rotation;
				rotation.Identity();
				rotation.RotationFromTo(current, target);
				m.Multiply3x3(m, rotation);
			}
		}
	}

	// FUNCTION: ENGINE 0x107F36C0
	// EQUIVALENT: the engine loads the direction as y, z, x and sums the dot product as (y + z) + x; ours x, z, y and
	// (x + z) + y (no source order of the terms changes it); the rest is the same
	// Turns direction towards target by at most maxAngularVelocity * dt
	void SmoothDirection(math::Vector& direction, const math::Vector& target, float dt, float maxAngularVelocity)
	{
		math::Vector current(direction);
		float cosine = target.Dot(current);
		if (!math::IsEqual(cosine, 1.0f, math::EPSILON_SMALL))
		{
			float angle = acosf(cosine);
			float fraction = math::Min(angle, dt * maxAngularVelocity) / angle;
			fraction = math::Select(fraction, fraction, 0.0f);
			fraction = math::Select(fraction - 1.0f, 1.0f, fraction);
			direction.x = (target.x - current.x) * fraction + current.x;
			direction.y = (target.y - current.y) * fraction + current.y;
			direction.z = (target.z - current.z) * fraction + current.z;
			direction.NormalizeFast();
		}
	}

	// FUNCTION: ENGINE 0x107F41E0
	void SupportingLimb::ResetDirection(const math::Matrix& m)
	{
		if (limbDef->directionFollowsSurfaceNormal)
		{
			m.Rotate(limbDef->direction, castDirection);
		}
		else
		{
			const math::Vector& direction = limbDef->direction;
			castDirection.x = direction.x;
			castDirection.y = direction.y;
			castDirection.z = direction.z;
		}
		UpdateBasis();
		transform.Identity();
	}

	// FUNCTION: ENGINE 0x107F4240
	// Sets two axes of m (ORIENTATION_AXIS each) from a and b, made orthonormal around a, and the third from them
	void OrientAxes(int axisA, const math::Vector& a, int axisB, const math::Vector& b, math::Matrix& m)
	{
		math::Vector first = axisA / 3 != 0 ? -a : a;
		math::Vector second = axisB / 3 != 0 ? -b : b;
		int rowA = axisA % 3;
		int rowB = axisB % 3;
		int rowC = sThirdAxis[rowA][rowB];
		math::Vector third;
		CrossAxes(first, rowA, second, rowB, third);
		CrossAxes(first, rowA, third, rowC, second);
		math::Vector& x = *(math::Vector*)m.m[rowA];
		x.x = first.x;
		x.y = first.y;
		x.z = first.z;
		math::Vector& y = *(math::Vector*)m.m[rowB];
		y.x = second.x;
		y.y = second.y;
		y.z = second.z;
		math::Vector& z = *(math::Vector*)m.m[rowC];
		z.x = third.x;
		z.y = third.y;
		z.z = third.z;
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
		: name("", 1), sphereRadius(0.2f), intersectionProperties(0), origin(math::kZeroVector),
		direction(0.0f, -1.0f, 0.0f), restingLength(1.0f), maxLength(2.0f), cosineSupportAngleTolerance(0.0f),
		directionFollowsSurfaceNormal(false), smoothDirection(true), smoothRestingLength(true),
		characterSurfaceOrientation(None), characterUpVectorOrientation(None), smoothMaxLinearVelocity(3.0f),
		smoothFractionalMaxLinearVelocity(0.0f), smoothMaxAngularVelocity(1.3f), smoothMinRestingLength(0.0f),
		smoothMaxRestingLength(2.0f), numRandomRays(0), randomRayCircleRadius(0.0f)
	{
		filter.properties.unknown0 = -1;
		filter.properties.unknown4 = 4;
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
namespace engine
{
	// FUNCTION: ENGINE 0x107F2CC0
	SupportingLimb::CastInput::CastInput()
		: filterWord(0), transform(math::Matrix::IDENTITY), down(0.0f, -1.0f, 0.0f), startOffset(0.0f), extraLength(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x107F37F0
	SupportingLimb::CastResult::CastResult()
		: position(1e12f, 1e12f, 1e12f), normal(1e12f, 1e12f, 1e12f), distance(1e12f), unknown1C(-1), unknown20(-1),
		material(0xff)
	{
	}

	// FUNCTION: ENGINE 0x107F5540
	// EQUIVALENT: same calls and blocks (the hit loop unrolled by four as in the engine); the engine keeps this in edi
	// and its frame is 8 bytes larger, ours keeps this in ebp, so stack offsets and registers differ throughout
	bool SupportingLimb::CastRay(const CastInput& input, const math::Vector& origin, float maxDistance,
		CastResult& result)
	{
		math::Matrix inverse;
		inverse = transform;
		inverse.InvertOrthonormal();
		math::Matrix frame;
		frame.Multiply(inverse, input.transform);
		math::Vector limbOrigin;
		frame.Transform(limbDef->origin, limbOrigin);
		math::Vector point;
		frame.Transform(origin, point);
		math::Vector start(point.x - input.down.x * input.startOffset, point.y - input.down.y * input.startOffset,
			point.z - input.down.z * input.startOffset);
		float length = limbDef->maxLength + input.extraLength + unknown6C;
		math::Vector end(input.down.x * length + point.x, input.down.y * length + point.y,
			input.down.z * length + point.z);
		bool found = false;
		unsigned int index = 0;
		ravenphysics::RayQuery query;
		query.start.Set(start.x, start.y, start.z);
		query.end.Set(end.x, end.y, end.z);
		query.filter = limbDef->filter;
		query.filter.unknown8 = input.filterWord;
		RayHitBufferLock lock(true);
		ravenphysics::RayHitArray& hits = lock.Get();
		if (ravenphysics::gContext->CastRay(query, &hits) && maxDistance > hits.begin->distance)
		{
			if (hits.begin->normal.Dot(input.down) > -limbDef->cosineSupportAngleTolerance)
			{
				// The nearest hit facing against the cast direction closely enough
				ravenphysics::SortHits(hits.begin, hits.end);
				unsigned int count = hits.end - hits.begin;
				for (unsigned int i = 1; i < count; i++)
				{
					if (!(maxDistance > hits.begin[i].distance))
					{
						break;
					}
					if (-limbDef->cosineSupportAngleTolerance > hits.begin[i].normal.Dot(input.down))
					{
						index = i;
						found = true;
					}
				}
			}
			else
			{
				found = true;
			}
			if (found)
			{
				const ravenphysics::RayHit& hit = hits.begin[index];
				result.normal.x = hit.normal.x;
				result.normal.y = hit.normal.y;
				result.normal.z = hit.normal.z;
				math::Vector delta(end.x - start.x, end.y - start.y, end.z - start.z);
				float scale = hit.distance / sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
				result.unknown20 = hit.unknown4;
				result.unknown1C = hit.unknown8;
				delta.Scale(scale);
				result.position.x = delta.x + start.x + limbOrigin.x - point.x;
				result.position.y = delta.y + start.y + limbOrigin.y - point.y;
				result.position.z = delta.z + start.z + limbOrigin.z - point.z;
				result.distance = sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z) - input.startOffset;
				result.material = hit.GetMaterial();
			}
		}
		return found;
	}

	// FUNCTION: ENGINE 0x107F5AC0
	// EQUIVALENT: the engine keeps the result flag in bl (ebx saved first) and the inverse matrix below the frame
	// matrix; ours keeps the flag on the stack, saves ebx in the loop and swaps the two matrices
	bool SupportingLimb::Cast(const CastInput& input, CastResult& result, int* rayIndex)
	{
		bool found = false;
		if (limbDef->numRandomRays == 0 || rayIndex == 0)
		{
			return CastRay(input, limbDef->origin, 1e12f, result);
		}
		math::Matrix inverse;
		inverse = transform;
		inverse.InvertOrthonormal();
		math::Matrix frame;
		frame.Multiply(inverse, input.transform);
		math::Vector u;
		frame.Rotate(basisU, u);
		math::Vector v;
		frame.Rotate(basisV, v);
		float nearest = 1e12f;
		int i = 0;
		RandomRay* last = rays.End();
		for (RandomRay* ray = rays.Begin(); ray != last; ray++, i++)
		{
			float sine = 0.0f;
			float cosine = 1.0f;
			math::SinCos(ray->angle, &sine, &cosine);
			const math::Vector& center = limbDef->origin;
			math::Vector origin(center);
			float radius = limbDef->randomRayCircleRadius * ray->radius * cosine;
			origin.x = u.x * radius + origin.x;
			origin.y = u.y * radius + origin.y;
			origin.z = u.z * radius + origin.z;
			radius = limbDef->randomRayCircleRadius * ray->radius * sine;
			origin.x = v.x * radius + origin.x;
			origin.y = v.y * radius + origin.y;
			origin.z = v.z * radius + origin.z;
			if (CastRay(input, origin, nearest, result))
			{
				nearest = result.distance;
				*rayIndex = i;
				found = true;
			}
		}
		return found;
	}

	// The random rays' turn per update while they find nothing (80 degrees) and their step outwards
	static inline float ToRadians(float degrees)
	{
		return degrees * (3.1415927f / 180.0f);
	}
	static float sRayRadiusStep = 0.3f;
	static math::Vector sUp(0.0f, 1.0f, 0.0f);

	// FUNCTION: ENGINE 0x107F5D20
	// EQUIVALENT: same calls in the same order except that the engine calls its kept copy of
	// SmoothingVelocityMap::IsEmpty (0x107F3210) where ours inlines it; registers and stack slots differ throughout
	void SupportingLimb::Update(const math::Matrix& previous, math::Matrix& current, Support& support, bool keep,
		int filterWord, float dt, CastStatus& status, bool predict)
	{
		math::Matrix inverse;
		inverse = transform;
		inverse.InvertOrthonormal();
		math::Matrix previousLocal;
		previousLocal.Multiply(inverse, previous);
		math::Matrix currentLocal;
		currentLocal.Multiply(inverse, current);
		// The move, split into its part along the cast direction and the rest
		math::Vector move(current.m[3][0] - previous.m[3][0], current.m[3][1] - previous.m[3][1],
			current.m[3][2] - previous.m[3][2]);
		float along = castDirection.Dot(move);
		move.x -= castDirection.x * along;
		move.y -= castDirection.y * along;
		move.z -= castDirection.z * along;
		const math::Matrix* frame = &previousLocal;
		if (!status.unknown8 || status.unknown9)
		{
			float startOffset = 0.0f > along ? 0.0f : along;
			RandomRay* last = rays.End();
			if (limbDef->numRandomRays != 0)
			{
				for (RandomRay* ray = rays.Begin(); ray != last; ray++)
				{
					if (!ray->active)
					{
						static float sRayAngleStep = ToRadians(80.0f);
						ray->angle += sRayAngleStep;
						if (ray->angle > 6.2831855f)
						{
							ray->angle -= 6.2831855f;
						}
						ray->radius += sRayRadiusStep;
						if (ray->radius > 1.0f)
						{
							ray->radius -= 1.0f;
						}
					}
				}
			}
			if (keep || !(0.0f < along))
			{
				predict = false;
			}
			float extraLength = 0.0f;
			if (predict)
			{
				extraLength = along * 1.5f;
			}
			CastResult result;
			int rayIndex;
			bool found;
			for (;;)
			{
				support.unknown20 = -1;
				support.unknown24 = -1;
				CastInput input;
				input.transform.m[0][0] = frame->m[0][0];
				input.transform.m[0][1] = frame->m[0][1];
				input.transform.m[0][2] = frame->m[0][2];
				input.transform.m[0][3] = frame->m[0][3];
				input.transform.m[1][0] = frame->m[1][0];
				input.transform.m[1][1] = frame->m[1][1];
				input.transform.m[1][2] = frame->m[1][2];
				input.transform.m[1][3] = frame->m[1][3];
				input.transform.m[2][0] = frame->m[2][0];
				input.transform.m[2][1] = frame->m[2][1];
				input.transform.m[2][2] = frame->m[2][2];
				input.transform.m[2][3] = frame->m[2][3];
				input.transform.m[3][0] = frame->m[3][0];
				input.transform.m[3][1] = frame->m[3][1];
				input.transform.m[3][2] = frame->m[3][2];
				input.transform.m[3][3] = frame->m[3][3];
				input.down.x = castDirection.x;
				input.down.y = castDirection.y;
				input.down.z = castDirection.z;
				input.filterWord = filterWord;
				input.startOffset = startOffset;
				input.extraLength = extraLength;
				rayIndex = 0;
				found = Cast(input, result, &rayIndex);
				status.found = found;
				if (frame == &currentLocal)
				{
					result.position.x -= move.x;
					result.position.y -= move.y;
					result.position.z -= move.z;
				}
				// A predicting cast that finds the ground beyond the resting length tries again from the new frame
				if (!found || !predict || frame != &previousLocal
					|| result.distance < limbDef->restingLength + math::EPSILON_SMALL)
				{
					break;
				}
				frame = &currentLocal;
			}
			if (found)
			{
				support.limb = this;
				support.position.z = result.position.z;
				support.position.x = result.position.x;
				support.position.y = result.position.y;
				support.normal.x = result.normal.x;
				support.normal.y = result.normal.y;
				support.normal.z = result.normal.z;
				status.distance = result.distance;
				support.unknown20 = result.unknown1C;
				support.unknown24 = result.unknown20;
				support.material = result.material;
				support.unsupportedTime = 0.0f;
			}
			else
			{
				support.unsupportedTime = support.unsupportedTime + dt;
			}
			if (limbDef->numRandomRays != 0)
			{
				for (RandomRay* ray = rays.Begin(); ray != last; ray++)
				{
					ray->active = false;
				}
				if (status.found)
				{
					rays[rayIndex].active = true;
				}
			}
		}
		else
		{
			if (support.supported)
			{
				// Slide the support along its plane under the limb's origin
				math::Plane plane;
				plane.normal.Set(support.normal.x, support.normal.y, support.normal.z);
				plane.d = -support.position.Dot(plane.normal);
				math::Vector origin;
				frame->Transform(limbDef->origin, origin);
				plane.IntersectRay(origin, castDirection, &support.position);
			}
			support.unsupportedTime += dt;
		}
		status.unknown8 = true;
		status.unknown9 = false;
		support.supported = false;
		if (!status.found)
		{
			return;
		}
		if (!keep)
		{
			if (!(limbDef->restingLength + math::EPSILON_SMALL > status.distance) || along < -math::EPSILON_SMALL)
			{
				return;
			}
		}
		support.supported = true;
		math::Vector origin;
		frame->Transform(limbDef->origin, origin);
		float* length = &unknown68;
		*length = castDirection.z * (support.position.z - origin.z) + castDirection.y * (support.position.y - origin.y)
			+ (support.position.x - origin.x) * castDirection.x;
		if (frame == &currentLocal)
		{
			unknown70 = true;
		}
		const SupportingLimbDefinition* definition = limbDef;
		if (definition->smoothRestingLength && !unknown70)
		{
			float maxVelocity = 1.0f;
			if (definition->smoothMaxLinearVelocityMap.IsEmpty())
			{
				maxVelocity = definition->smoothMaxLinearVelocity;
				float fractional = definition->smoothFractionalMaxLinearVelocity;
				if (fractional > 0.0f && dt > math::EPSILON_SMALL)
				{
					maxVelocity = sqrtf(move.x * move.x + move.z * move.z + move.y * move.y) / dt * fractional
						+ maxVelocity;
				}
			}
			else if (dt > math::EPSILON_SMALL)
			{
				maxVelocity = definition->smoothMaxLinearVelocityMap.Evaluate(
					sqrtf(move.x * move.x + move.z * move.z + move.y * move.y) / dt);
			}
			SmoothValue(length, definition->restingLength, dt, maxVelocity, definition->smoothMinRestingLength,
				definition->smoothMaxRestingLength);
		}
		else
		{
			*length = definition->restingLength;
		}
		definition = limbDef;
		if (definition->directionFollowsSurfaceNormal)
		{
			if (definition->smoothDirection && !unknown70)
			{
				math::Vector target = -support.normal;
				SmoothDirection(castDirection, target, dt, definition->smoothMaxAngularVelocity);
				UpdateBasis();
			}
			else
			{
				castDirection.Set(-support.normal.x, -support.normal.y, -support.normal.z);
				UpdateBasis();
			}
		}
		definition = limbDef;
		unknown70 = false;
		int surfaceAxis = definition->characterSurfaceOrientation;
		int upAxis = definition->characterUpVectorOrientation;
		if (surfaceAxis != SupportingLimbDefinition::None && upAxis != SupportingLimbDefinition::None)
		{
			if (!math::IsEqual(fabsf(castDirection.y * sUp.y + castDirection.z * sUp.z + castDirection.x * sUp.x),
				1.0f, math::EPSILON_SMALL))
			{
				OrientAxes(surfaceAxis, castDirection, upAxis, sUp, currentLocal);
			}
			else
			{
				AlignAxis(surfaceAxis, castDirection, currentLocal);
			}
		}
		else if (surfaceAxis != SupportingLimbDefinition::None)
		{
			AlignAxis(surfaceAxis, castDirection, currentLocal);
		}
		else if (upAxis != SupportingLimbDefinition::None)
		{
			AlignAxis(upAxis, sUp, currentLocal);
		}
		// Move the character so that the limb's end stays on the support (across the cast direction only)
		math::Vector offset;
		currentLocal.Rotate(limbDef->origin, offset);
		float l = *length;
		math::Vector correction(support.position.x - (castDirection.x * l + offset.x) - previousLocal.m[3][0],
			support.position.y - (castDirection.y * l + offset.y) - previousLocal.m[3][1],
			support.position.z - (castDirection.z * l + offset.z) - previousLocal.m[3][2]);
		float d = castDirection.Dot(correction);
		currentLocal.m[3][0] += correction.x - castDirection.x * d;
		currentLocal.m[3][1] += correction.y - castDirection.y * d;
		currentLocal.m[3][2] += correction.z - castDirection.z * d;
		current.Multiply(transform, currentLocal);
	}

	// FUNCTION: ENGINE 0x107F66B0
	bool SupportingLimb::Cast(const CastInput& input, CastResult& result)
	{
		return Cast(input, result, 0);
	}
}

namespace container
{
	template class ArrayCDynamic<engine::SupportingLimbDefinition::SmoothingVelocityMap::Entry, 3>;
	template class ArrayCDynamic<engine::SupportingLimb::RandomRay, 4>;
	template class ArrayDynamicNew<engine::SupportingLimbDefinition*>;

}

// the default element the reflection helper's Insert used; kept as the engine kept it
template engine::SupportingLimbDefinition::SmoothingVelocityMap::Entry& content::ArrayCDynamicHelper<
	container::ArrayCDynamic<engine::SupportingLimbDefinition::SmoothingVelocityMap::Entry, 3> >::Default();
