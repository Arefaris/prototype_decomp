#include "code/proto/reflectedstubs.h"

// The reflection of the pedestrian behaviours (RTTI and reflection names): none of them reflects members of its own
// (the ClassInfo of PedBehaviourTunables, the load object with their tuning values, is here too).
// The classes themselves are declared in proto/reflectedstubs.h until their layouts are recovered. Unit
// 0x1042EEE0 - 0x10433050, 0x104388C0 - 0x10438A20 (scattered; no assert path names it, the file name is a guess).
namespace proto
{
	// FUNCTION: ENGINE 0x10432E90
	content::ClassInfo* PedBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PedBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10432F10
	content::ClassInfo* CharacterPedBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CharacterPedBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1042EEE0
	content::ClassInfo* CopPedBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CopPedBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1042EF20
	content::ClassInfo* SoldierPedBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::SoldierPedBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1042FBB0
	content::ClassInfo* InfectedPedBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::InfectedPedBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10433010
	content::ClassInfo* PedBehaviourTunables::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PedBehaviourTunables";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1042FB20
	content::MemberList* SoldierPedBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<CopPedBehaviour>();
		static content::BaseClassCasterImpl<CopPedBehaviour, SoldierPedBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1042F490
	content::MemberList* CopPedBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<PedBehaviour>();
		static content::BaseClassCasterImpl<PedBehaviour, CopPedBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10430550
	content::MemberList* InfectedPedBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<PedBehaviour>();
		static content::BaseClassCasterImpl<PedBehaviour, InfectedPedBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x104388C0
	content::MemberList* PedBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, PedBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x104389C0
	content::MemberList* CharacterPedBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, CharacterPedBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}
