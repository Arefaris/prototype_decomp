#include "code/proto/behaviours/motherhealthbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102C02F0
	content::MemberList* MotherHealthBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<AdvancedHealthBehaviour>();
		static content::BaseClassCasterImpl<AdvancedHealthBehaviour, MotherHealthBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<MotherHealthBehaviour, float, 0>("p"),
				PROTO_OFFSET(MotherHealthBehaviour, redirectMultiplier), "redirectMultiplier" },
			{ content::GetMemberPrimitiveMetaType<MotherHealthBehaviour, bool, 0>("p"),
				PROTO_OFFSET(MotherHealthBehaviour, alwaysDoOwn), "alwaysDoOwn" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}
