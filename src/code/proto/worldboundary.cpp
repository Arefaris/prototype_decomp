#include "code/proto/worldboundary.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x103B31B0
	content::ClassInfo* WorldBoundary::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WorldBoundary";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103B31F0
	content::ClassInfo* WorldBoundary::Vertex::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WorldBoundary::Vertex";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103B33C0
	content::MemberList* WorldBoundary::Vertex::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<Vertex, 0>("p"), 0, "point" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103B3D90
	content::MemberList* WorldBoundary::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<WorldBoundary, VertexArray>(content::GetClassMetaType<Vertex>(), "p"),
				PROTO_OFFSET(WorldBoundary, vertexList), "vertexList" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103B3F80
	WorldBoundary::WorldBoundary()
	{
	}

	// FUNCTION: ENGINE 0x103B3FB0
	WorldBoundary::~WorldBoundary()
	{
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103B3290
// FUNCTION: ENGINE 0x103B3340
// FUNCTION: ENGINE 0x103B3350
// FUNCTION: ENGINE 0x103B3360
// FUNCTION: ENGINE 0x103B3370
// FUNCTION: ENGINE 0x103B33B0
// FUNCTION: ENGINE 0x103B3710
// FUNCTION: ENGINE 0x103B3720
// FUNCTION: ENGINE 0x103B3790
// FUNCTION: ENGINE 0x103B37A0
// FUNCTION: ENGINE 0x103B37D0
// FUNCTION: ENGINE 0x103B37F0
// FUNCTION: ENGINE 0x103B3850
// FUNCTION: ENGINE 0x103B38B0
// FUNCTION: ENGINE 0x103B38F0
// FUNCTION: ENGINE 0x103B3910
// FUNCTION: ENGINE 0x103B39A0
// FUNCTION: ENGINE 0x103B3A60
// FUNCTION: ENGINE 0x103B3AC0
// FUNCTION: ENGINE 0x103B3D40
// FUNCTION: ENGINE 0x103B3E40
// FUNCTION: ENGINE 0x103B3E60
// FUNCTION: ENGINE 0x103B3EC0
// FUNCTION: ENGINE 0x103B3FE0
// FUNCTION: ENGINE 0x103B4030
// FUNCTION: ENGINE 0x103B4060

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103B38D0
// FUNCTION: ENGINE 0x103B39D0
// FUNCTION: ENGINE 0x103B3CF0
