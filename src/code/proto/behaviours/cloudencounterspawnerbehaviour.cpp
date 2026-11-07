#include "code/proto/behaviours/encounterspawnerbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10554720
	content::ClassInfo* CloudEncounterSpawnerBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CloudEncounterSpawnerBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10554D60
	content::MemberList* CloudEncounterSpawnerBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<EncounterSpawnerBehaviour>();
		static content::BaseClassCasterImpl<EncounterSpawnerBehaviour, CloudEncounterSpawnerBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<CloudEncounterSpawnerBehaviour, unsigned int, 0>("pn"),
				PROTO_OFFSET(CloudEncounterSpawnerBehaviour, minGroupSize), "minGroupSize" },
			{ content::GetMemberPrimitiveMetaType<CloudEncounterSpawnerBehaviour, unsigned int, 1>("pn"),
				PROTO_OFFSET(CloudEncounterSpawnerBehaviour, maxGroupSize), "maxGroupSize" },
			{ content::GetMemberPrimitiveMetaType<CloudEncounterSpawnerBehaviour, bool, 0>("pn"),
				PROTO_OFFSET(CloudEncounterSpawnerBehaviour, timeSlicedWithDeferredSquadMessages),
				"timeSlicedWithDeferredSquadMessages" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10554A60
// FUNCTION: ENGINE 0x10554A70
// FUNCTION: ENGINE 0x10554C40
// FUNCTION: ENGINE 0x10554C80
// FUNCTION: ENGINE 0x10554CC0
