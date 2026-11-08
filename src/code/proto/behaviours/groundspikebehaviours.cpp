#include "code/proto/behaviours/groundspikebehaviours.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10069C30
	content::ClassInfo* GroundSpikeBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GroundSpikeBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1006B260
	content::MemberList* GroundSpikeBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, GroundSpikeBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10069C70
	content::ClassInfo* GroundSpikeMasterBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GroundSpikeMasterBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1006C2D0
	content::MemberList* GroundSpikeMasterBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<GroundSpikeBehaviour>();
		static content::BaseClassCasterImpl<GroundSpikeBehaviour, GroundSpikeMasterBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10069CB0
	content::ClassInfo* GroundSpikeShardBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GroundSpikeShardBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1006B2E0
	content::MemberList* GroundSpikeShardBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, GroundSpikeShardBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<GroundSpikeShardBehaviour, float, 0>("p"),
				PROTO_OFFSET(GroundSpikeShardBehaviour, height), "height" },
			{ content::GetMemberPrimitiveMetaType<GroundSpikeShardBehaviour, float, 1>("p"),
				PROTO_OFFSET(GroundSpikeShardBehaviour, minEmergeOffset), "minEmergeOffset" },
			{ content::GetMemberPrimitiveMetaType<GroundSpikeShardBehaviour, float, 2>("p"),
				PROTO_OFFSET(GroundSpikeShardBehaviour, maxEmergeOffset), "minEmergeOffset" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10069F50
	void GroundSpikeBehaviour::OnPostedMessage(engine::Message* message)
	{
		if (message->type == 3 && message->id == 9)
		{
			GetQueriedVector(message);
		}
	}

	// FUNCTION: ENGINE 0x10069FE0
	void GroundSpikeShardBehaviour::OnPostedMessage(engine::Message* message)
	{
		if (message->type == 3 && message->id == 9)
		{
			GetQueriedVector(message);
		}
	}

}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1006A940
// FUNCTION: ENGINE 0x1006A950
// FUNCTION: ENGINE 0x1006A980
// FUNCTION: ENGINE 0x1006A990
// FUNCTION: ENGINE 0x1006A9C0
// FUNCTION: ENGINE 0x1006A9D0
// FUNCTION: ENGINE 0x1006ACA0
// FUNCTION: ENGINE 0x1006ACE0
// FUNCTION: ENGINE 0x1006AD20
// FUNCTION: ENGINE 0x1006BFB0
