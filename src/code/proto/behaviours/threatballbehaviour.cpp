#include "code/proto/reflectedstubs.h"

// proto::ThreatBallBehaviour (RTTI name "ThreatBallBehaviour" without the namespace in its ClassInfo; base
// engine::TriggerBehaviour): the trigger that carries a threat. No members of its own; the class itself is declared in
// proto/reflectedstubs.h until its layout is recovered. Unit 0x10407440 - 0x10408070.
namespace proto
{
	// FUNCTION: ENGINE 0x10407440
	content::ClassInfo* ThreatBallBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ThreatBallBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10407970
	content::MemberList* ThreatBallBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::TriggerBehaviour>();
		static content::BaseClassCasterImpl<engine::TriggerBehaviour, ThreatBallBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}
