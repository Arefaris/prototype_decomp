#include "code/proto/behaviours/threatreceiverbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10403000
	content::ClassInfo* ThreatReceiverBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ThreatReceiverBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10403690
	ThreatReceiverBehaviour::ThreatReceiverBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
		Listen(0x35, true);
		Listen(2, true);
		ClearThreatenedBy();
	}

	// FUNCTION: ENGINE 0x10403580
	void ThreatReceiverBehaviour::ClearThreatenedBy()
	{
		threatenedBy.Reset();
	}

	// FUNCTION: ENGINE 0x104036F0
	ThreatReceiverBehaviour::~ThreatReceiverBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10403650
	void ThreatReceiverBehaviour::Update(float dt, unsigned short mask)
	{
		if (automaticallyClearThreats)
		{
			threatenedBy.Reset();
		}
		Listen2(8, false);
	}

	// FUNCTION: ENGINE 0x10403300
	content::MemberList* ThreatReceiverBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, ThreatReceiverBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ThreatReceiverBehaviour, bool, 0>("pn"),
				PROTO_OFFSET(ThreatReceiverBehaviour, automaticallyClearThreats), "automaticallyClearThreats" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}
