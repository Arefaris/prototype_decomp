// The reflection of the math types (math::Vector, Plane, AABB, Sphere, OBB) and of the two message base classes
// (engine::IntrusiveMessage, engine::NonintrusiveMessage): this unit 0x108475A0 - 0x10847E60 (no assert path; file
// name is a guess). The members of the math types are reflected with the meta types of the vector and float members.
#include "code/content/metatype.h"
#include "code/engine/message.h"
#include "code/math/aabb.h"
#include "code/math/obb.h"
#include "code/math/plane.h"
#include "code/math/sphere.h"
#include "code/math/vector.h"

#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

namespace math
{
	// FUNCTION: ENGINE 0x108475A0
	content::ClassInfo* Vector::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "math::Vector";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x108475E0
	content::ClassInfo* Plane::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "math::Plane";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10847620
	content::ClassInfo* AABB::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "math::AABB";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10847660
	content::ClassInfo* Sphere::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "math::Sphere";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x108476A0
	content::ClassInfo* OBB::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "math::OBB";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10847970
	content::MemberList* AABB::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<AABB, 0>("p"), 0, "low" },
			{ content::GetMemberVectorMetaType<AABB, 1>("p"), 0xc, "high" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10847A10
	content::MemberList* OBB::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<OBB, 0>("p"), 0, "centre" },
			{ content::GetMemberVectorMetaType<OBB, 1>("p"), 0xc, "xAxis" },
			{ content::GetMemberVectorMetaType<OBB, 2>("p"), 0x18, "yAxis" },
			{ content::GetMemberVectorMetaType<OBB, 3>("p"), 0x24, "zAxis" },
			{ content::GetMemberVectorMetaType<OBB, 4>("p"), 0x30, "extents" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10847C60
	content::MemberList* Vector::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Vector, float, 0>("p"), ENGINE_OFFSET(Vector, x), "x" },
			{ content::GetMemberPrimitiveMetaType<Vector, float, 1>("p"), ENGINE_OFFSET(Vector, y), "y" },
			{ content::GetMemberPrimitiveMetaType<Vector, float, 2>("p"), ENGINE_OFFSET(Vector, z), "z" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10847D30
	content::MemberList* Plane::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<Plane, 0>("p"), 0, "normal" },
			{ content::GetMemberPrimitiveMetaType<Plane, float, 0>("p"), ENGINE_OFFSET(Plane, d), "distance" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10847DD0
	content::MemberList* Sphere::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<Sphere, 0>("p"), 0, "centre" },
			{ content::GetMemberPrimitiveMetaType<Sphere, float, 0>("p"), ENGINE_OFFSET(Sphere, radius), "radius" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}

namespace engine
{
	// FUNCTION: ENGINE 0x108476E0
	content::ClassInfo* IntrusiveMessage::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::IntrusiveMessage";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10847720
	content::MemberList* IntrusiveMessage::GetMembers()
	{
		static content::MemberList sList;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10847750
	content::ClassInfo* NonintrusiveMessage::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::NonintrusiveMessage";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10847790
	content::MemberList* NonintrusiveMessage::GetMembers()
	{
		static content::MemberList sList;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108477C0
// FUNCTION: ENGINE 0x108477F0
// FUNCTION: ENGINE 0x10847820
// FUNCTION: ENGINE 0x10847850
// FUNCTION: ENGINE 0x10847880
// FUNCTION: ENGINE 0x108478B0
// FUNCTION: ENGINE 0x108478E0
// FUNCTION: ENGINE 0x10847910
// FUNCTION: ENGINE 0x10847940
// FUNCTION: ENGINE 0x10847B20
// FUNCTION: ENGINE 0x10847B60
// FUNCTION: ENGINE 0x10847BA0
// FUNCTION: ENGINE 0x10847BE0
// FUNCTION: ENGINE 0x10847C20
