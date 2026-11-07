#include "code/proto/helipathfindingloader.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10397710
	content::ClassInfo* HeliPathfindingLoader::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "HeliPathfindingLoader";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103979D0
	content::MemberList* HeliPathfindingLoader::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<HeliPathfindingLoader, int, 0>("p"),
				PROTO_OFFSET(HeliPathfindingLoader, sizeX), "sizex" },
			{ content::GetMemberPrimitiveMetaType<HeliPathfindingLoader, int, 1>("p"),
				PROTO_OFFSET(HeliPathfindingLoader, sizeZ), "sizez" },
			{ content::GetArrayCMetaType<HeliPathfindingLoader, container::ArrayC<float, CELL_COUNT> >(CELL_COUNT, 4,
				content::GetMemberPrimitiveMetaType<HeliPathfindingLoader, float, 0>("p"), "p"),
				PROTO_OFFSET(HeliPathfindingLoader, data), "data" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103978E0
	HeliPathfindingLoader::HeliPathfindingLoader()
	{
		sizeX = 0;
		sizeZ = 0;
		nextNodeNumber = 0;
		for (int i = 0; i < CELL_COUNT; i++)
		{
			nodes[i].parent = 0xffff;
		}
	}

	// FUNCTION: ENGINE 0x10397750
	bool HeliPathfindingLoader::HasData()
	{
		return sizeX != 0;
	}

	// FUNCTION: ENGINE 0x10397760
	short HeliPathfindingLoader::TakeNodeNumber()
	{
		return nextNodeNumber++;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103977A0
// FUNCTION: ENGINE 0x103977B0
// FUNCTION: ENGINE 0x103977C0
// FUNCTION: ENGINE 0x10397800
// FUNCTION: ENGINE 0x10397840
// FUNCTION: ENGINE 0x10397880
// FUNCTION: ENGINE 0x10397890
// FUNCTION: ENGINE 0x103978B0
// FUNCTION: ENGINE 0x103978C0
// FUNCTION: ENGINE 0x10397930
// FUNCTION: ENGINE 0x10397940
// FUNCTION: ENGINE 0x10397970
