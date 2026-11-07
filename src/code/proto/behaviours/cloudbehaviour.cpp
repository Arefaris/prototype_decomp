#include "code/proto/behaviours/cloudbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x104F3420
	content::ClassInfo* CloudBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CloudBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104F3470
	CloudBehaviour::CloudBehaviour(engine::GameObject* newOwner) : engine::PropBehaviour(newOwner), maxRadius(5.0f)
	{
	}

	// FUNCTION: ENGINE 0x104F3560
	content::MemberList* CloudBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, CloudBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<CloudBehaviour, float, 0>("p"), PROTO_OFFSET(CloudBehaviour, maxRadius),
				"maxRadius" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}
