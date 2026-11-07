#include "code/proto/coopbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x104DAE80
	content::ClassInfo* CoOpBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CoOpBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104DAEC0
	CoOpBehaviour::CoOpBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
		respawnPendingState = 0;
		partnerDeadState = 0;
		pairingVolumeState = 0;
		Listen(0x30, true);
		Listen(2, true);
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x104DAF20
	void CoOpBehaviour::Slot1()
	{
	}

	// FUNCTION: ENGINE 0x104DB780
	content::MemberList* CoOpBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, CoOpBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetObjectMetaType<RespawnState>("pn"), PROTO_OFFSET(CoOpBehaviour, respawnPendingState),
				"respawnPendingState" },
			{ content::GetObjectMetaType<PlayerDeadState>("pn"), PROTO_OFFSET(CoOpBehaviour, partnerDeadState),
				"partnerDeadState" },
			{ content::GetObjectMetaType<PairingVolumeState>("pn"), PROTO_OFFSET(CoOpBehaviour, pairingVolumeState),
				"pairingVolumeState" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104DAFF0
// FUNCTION: ENGINE 0x104DB000
// FUNCTION: ENGINE 0x104DB010
// FUNCTION: ENGINE 0x104DB180
// FUNCTION: ENGINE 0x104DB190
// FUNCTION: ENGINE 0x104DB1E0
// FUNCTION: ENGINE 0x104DB210
// FUNCTION: ENGINE 0x104DB220
// FUNCTION: ENGINE 0x104DB5C0
// FUNCTION: ENGINE 0x104DB620
// FUNCTION: ENGINE 0x104DB680
