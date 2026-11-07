#include "code/proto/npcinstancepool.h"

namespace proto
{
	// FUNCTION: ENGINE 0x1047A150
	content::ClassInfo* NPCInstancePool::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::NPCInstancePool";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1047A3F0
	content::MemberList* NPCInstancePool::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<NPCInstancePool, int, 0>("p"),
				content::MemberOffset(&((NPCInstancePool*)0)->poolSize, (int)&((NPCInstancePool*)0)->poolSize), "poolSize" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1047A7F0
	NPCInstancePool::NPCInstancePool() : poolSize(0)
	{
	}

	// FUNCTION: ENGINE 0x1047A830
	NPCInstancePool::~NPCInstancePool()
	{
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1047A200
// FUNCTION: ENGINE 0x1047A230
// FUNCTION: ENGINE 0x1047A3A0
// FUNCTION: ENGINE 0x1047A590
// FUNCTION: ENGINE 0x1047A7D0
// FUNCTION: ENGINE 0x1047A8A0
