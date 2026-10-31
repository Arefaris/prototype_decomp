#include "code/proto/powers/whipfistpower.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1008C970
	content::ClassInfo* WhipFistPower::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WhipFistPower";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1008CB30
	bool WhipFistPower::GetMessageMask(unsigned int* mask)
	{
		*mask = 0x1e;
		return true;
	}

	// FUNCTION: ENGINE 0x1008EB80
	content::MemberList* WhipFistPower::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Power>();
		static content::BaseClassCasterImpl<Power, WhipFistPower> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<WhipFistPower, int, 0>("p"),
				PROTO_OFFSET(WhipFistPower, segmentCount), "segmentCount" },
			{ content::GetMemberPrimitiveMetaType<WhipFistPower, float, 0>("p"),
				PROTO_OFFSET(WhipFistPower, segmentLength), "segmentLength" },
			{ content::GetReferenceMetaType<WhipFistPower, engine::render::DrawableArchetype>("p"),
				PROTO_OFFSET(WhipFistPower, segmentDrawable), "segmentDrawable" },
			{ content::GetNameMetaType<WhipFistPower>(true, true, "p"),
				PROTO_NAME_OFFSET(WhipFistPower, preStartJoint), "preStartJoint" },
			{ content::GetNameMetaTypeCopy<WhipFistPower>(true, true, "p"),
				PROTO_NAME_OFFSET(WhipFistPower, startJoint), "startJoint" },
			{ content::GetMemberNameMetaType<WhipFistPower, 1>(true, true, "p"),
				PROTO_NAME_OFFSET(WhipFistPower, endJoint), "endJoint" },
			{ content::GetMemberVectorMetaType<WhipFistPower, 0>("p"), 0xe8, "endJointRotationOffset" },
			{ content::GetMemberPrimitiveMetaType<WhipFistPower, int, 1>("p"),
				PROTO_OFFSET(WhipFistPower, fixedSegmentCount), "fixedSegmentCount" },
			{ content::GetMemberPrimitiveMetaType<WhipFistPower, int, 2>("p"),
				PROTO_OFFSET(WhipFistPower, moveEndJoint), "moveEndJoint" }
		};
		sList.members = sMembers;
		sList.count = 9;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1008CC50
// FUNCTION: ENGINE 0x1008CC60
// FUNCTION: ENGINE 0x1008CCA0
// FUNCTION: ENGINE 0x1008CCE0
// FUNCTION: ENGINE 0x1008CD20
// FUNCTION: ENGINE 0x1008CF90
// FUNCTION: ENGINE 0x1008CFA0
// FUNCTION: ENGINE 0x1008DEE0
// FUNCTION: ENGINE 0x1008DF20
// FUNCTION: ENGINE 0x1008DF60
// FUNCTION: ENGINE 0x1008DFA0
// FUNCTION: ENGINE 0x1008EB20
