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

	// FUNCTION: ENGINE 0x10433280
	void PedBehaviour::Slot1()
	{
	}

	// FUNCTION: ENGINE 0x10433290
	void PedBehaviour::OnActiveChanged(bool active)
	{
		Behaviour::OnActiveChanged(active);
		Listen2(4, active);
	}

	// FUNCTION: ENGINE 0x1042FC10
	float PedBehaviour::GetSpeed()
	{
		return speed;
	}

	// FUNCTION: ENGINE 0x1042FC20
	bool PedBehaviour::Slot9()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10433370
	int PedBehaviour::GetPedType()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1042F040
	float CopPedBehaviour::GetSpeed()
	{
		if (!unknownE4 && unknown18 != 0)
		{
			return speed * 0.2f;
		}
		return speed;
	}

	// FUNCTION: ENGINE 0x1042F070
	bool CopPedBehaviour::Slot9()
	{
		if (!unknownE4 && unknown18 != 0)
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x1042EFE0
	void CopPedBehaviour::Slot12()
	{
		unknownE4 = false;
		PedBehaviour::Slot12();
	}

	// FUNCTION: ENGINE 0x1042F0D0
	void CopPedBehaviour::Slot16()
	{
		PedBehaviour::Slot16();
		if (state == 0xF)
		{
			speed = speed * 0.25f;
		}
	}

	// FUNCTION: ENGINE 0x1042EFF0
	void CopPedBehaviour::SetState(int newState)
	{
		if (((!unknownE4 && unknown18 != 0) || state == 0xF) && newState != 0xC && newState != 0xB && newState != 0xD)
		{
			return;
		}
		PedBehaviour::SetState(newState);
	}

	// FUNCTION: ENGINE 0x1042EFD0
	int CopPedBehaviour::GetPedType()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1042EF60
	int SoldierPedBehaviour::GetPedType()
	{
		return 3;
	}

	// FUNCTION: ENGINE 0x1042FC40
	int InfectedPedBehaviour::GetPedType()
	{
		return 2;
	}

	// FUNCTION: ENGINE 0x1042FC80
	void InfectedPedBehaviour::SetState(int newState)
	{
		if (newState != 5)
		{
			PedBehaviour::SetState(newState);
		}
	}
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1042F190
// FUNCTION: ENGINE 0x1042F1A0
// FUNCTION: ENGINE 0x1042F1D0
// FUNCTION: ENGINE 0x1042F1E0
// FUNCTION: ENGINE 0x1042FCA0
// FUNCTION: ENGINE 0x1042FCB0
// FUNCTION: ENGINE 0x104341F0
// FUNCTION: ENGINE 0x10434200
// FUNCTION: ENGINE 0x10434270
// FUNCTION: ENGINE 0x10434280
