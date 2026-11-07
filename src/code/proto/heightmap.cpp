#include "code/proto/heightmap.h"
#include <math.h>

namespace engine
{
	namespace driving
	{
		extern const float gOne;
		extern const float gHalf;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10393120
	content::ClassInfo* Heightmap::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::Heightmap";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10394BC0
	content::MemberList* Heightmap::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Heightmap, float, 0>("p"),
				PROTO_OFFSET(Heightmap, gridSize), "gridSize" },
			{ content::GetMemberPrimitiveMetaType<Heightmap, int, 0>("p"),
				PROTO_OFFSET(Heightmap, sizeX), "sizex" },
			{ content::GetMemberPrimitiveMetaType<Heightmap, int, 1>("p"),
				PROTO_OFFSET(Heightmap, sizeY), "sizey" },
			{ content::GetMemberPrimitiveMetaType<Heightmap, int, 2>("p"),
				PROTO_OFFSET(Heightmap, marginX), "marginx" },
			{ content::GetMemberPrimitiveMetaType<Heightmap, int, 3>("p"),
				PROTO_OFFSET(Heightmap, marginY), "marginy" },
			{ content::GetMemberVectorMetaType<Heightmap, 0>("p"), 0x20, "minVec" },
			{ content::GetMemberPrimitiveMetaType<Heightmap, float, 1>("p"),
				PROTO_OFFSET(Heightmap, minHeight), "minHeight" },
			{ content::GetMemberPrimitiveMetaType<Heightmap, float, 2>("p"),
				PROTO_OFFSET(Heightmap, maxHeight), "maxHeight" },
			{ content::GetMemberPrimitiveMetaType<Heightmap, float, 3>("p"),
				PROTO_OFFSET(Heightmap, quantum), "quantum" },
			{ content::GetClassMetaType<math::AABB>(), PROTO_OFFSET(Heightmap, aabb), "aabb" },
			{ content::GetArrayDynamicMetaType<Heightmap, HeightArray>(
				content::GetMemberPrimitiveMetaType<Heightmap, unsigned short, 0>("p"), "p"),
				PROTO_OFFSET(Heightmap, data), "data" }
		};
		sList.members = sMembers;
		sList.count = 11;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103951D0
	void Heightmap::SetName(const content::ObjectName& name)
	{
	}

	// FUNCTION: ENGINE 0x10393160
	// NONMATCHING: the engine stores the inverse grid size after reserving the call frame (88 %)
#ifdef NONMATCHING
	bool Heightmap::Slot5()
	{
		inverseGridSize = engine::driving::gOne / gridSize;
		halfRows = (int)ceil((float)sizeY * engine::driving::gHalf);
		return true;
	}
#endif
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103931F0
// FUNCTION: ENGINE 0x103932C0
// FUNCTION: ENGINE 0x103933B0
// FUNCTION: ENGINE 0x103933F0
// FUNCTION: ENGINE 0x10393400
// FUNCTION: ENGINE 0x103937E0
// FUNCTION: ENGINE 0x103938D0
// FUNCTION: ENGINE 0x10393910
// FUNCTION: ENGINE 0x10393950
// FUNCTION: ENGINE 0x10393990
// FUNCTION: ENGINE 0x103939D0
// FUNCTION: ENGINE 0x10393A10
// FUNCTION: ENGINE 0x10393A50
// FUNCTION: ENGINE 0x10393A90
// FUNCTION: ENGINE 0x10393AD0
// FUNCTION: ENGINE 0x10393B20
// FUNCTION: ENGINE 0x10393B30
// FUNCTION: ENGINE 0x10393B50
// FUNCTION: ENGINE 0x10393B70
// FUNCTION: ENGINE 0x10393BD0
// FUNCTION: ENGINE 0x10393BF0
// FUNCTION: ENGINE 0x10393C10
// FUNCTION: ENGINE 0x10393C30
// FUNCTION: ENGINE 0x10393CD0
// FUNCTION: ENGINE 0x10393CF0
// FUNCTION: ENGINE 0x10393D10
// FUNCTION: ENGINE 0x10393D50
// FUNCTION: ENGINE 0x103949F0
// FUNCTION: ENGINE 0x10394A50
// FUNCTION: ENGINE 0x10394AA0
// FUNCTION: ENGINE 0x10394F90
// FUNCTION: ENGINE 0x10395260
