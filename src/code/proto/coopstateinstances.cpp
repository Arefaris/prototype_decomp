// The reflection of the online co-op states and the instance helpers their pointer members use (content::MetaInstanceHelper
// deletes the object a pointer member refers to). The states are plain data with no reflected members; their layouts are
// not recovered. The file name is a guess.
#include "code/proto/coopbehaviour.h"

namespace proto
{
	// FUNCTION: ENGINE 0x104DAD00
	content::ClassInfo* RespawnState::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::RespawnState";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104DAD40
	content::MemberList* RespawnState::GetMembers()
	{
		static content::MemberList sList;
		return &sList;
	}

	// FUNCTION: ENGINE 0x104DAD80
	content::ClassInfo* PlayerDeadState::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PlayerDeadState";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104DADC0
	content::MemberList* PlayerDeadState::GetMembers()
	{
		static content::MemberList sList;
		return &sList;
	}

	// FUNCTION: ENGINE 0x104DAE00
	content::ClassInfo* PairingVolumeState::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PairingVolumeState";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104DAE40
	content::MemberList* PairingVolumeState::GetMembers()
	{
		static content::MemberList sList;
		return &sList;
	}
}

template class content::MetaInstanceHelper<proto::RespawnState, 1>;
template class content::MetaInstanceHelper<proto::PlayerDeadState, 1>;
template class content::MetaInstanceHelper<proto::PairingVolumeState, 1>;
template content::ClassMetaType* content::GetClassMetaType<proto::RespawnState>();
template content::ClassMetaType* content::GetClassMetaType<proto::PlayerDeadState>();
template content::ClassMetaType* content::GetClassMetaType<proto::PairingVolumeState>();

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104DB1C0
// FUNCTION: ENGINE 0x104DB1F0
// FUNCTION: ENGINE 0x104DB230
// FUNCTION: ENGINE 0x104DB250
