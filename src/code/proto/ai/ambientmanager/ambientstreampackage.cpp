#include "code/proto/ai/ambientmanager/ambientstreampackage.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10421200
	content::ClassInfo* AmbientStreamPackage::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AmbientStreamPackage";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10423CF0
	content::MemberList* AmbientStreamPackage::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<AmbientStreamPackage>(true, true, "p"),
				content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((AmbientStreamPackage*)0)->name,
					(int)&((AmbientStreamPackage*)0)->name), "name" },
			{ content::GetMemberPrimitiveMetaType<AmbientStreamPackage, float, 0>("p"),
				PROTO_OFFSET(AmbientStreamPackage, percent), "percent" },
			{ content::GetMemberPrimitiveMetaType<AmbientStreamPackage, int, 0>("p"),
				PROTO_OFFSET(AmbientStreamPackage, maxNumberSpawned), "maxNumberSpawned" },
			{ content::GetMemberPrimitiveMetaType<AmbientStreamPackage, int, 1>("p"),
				PROTO_OFFSET(AmbientStreamPackage, priority), "priority" },
			{ content::GetMemberPrimitiveMetaType<AmbientStreamPackage, unsigned int, 0>("p"),
				PROTO_OFFSET(AmbientStreamPackage, packageType), "packageType" },
			{ content::GetMemberPrimitiveMetaType<AmbientStreamPackage, bool, 0>("p"),
				PROTO_OFFSET(AmbientStreamPackage, recycle), "recycle" }
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10421890
// FUNCTION: ENGINE 0x10423030
// FUNCTION: ENGINE 0x10423070
// FUNCTION: ENGINE 0x104230B0
// FUNCTION: ENGINE 0x104230F0
// FUNCTION: ENGINE 0x10423130
