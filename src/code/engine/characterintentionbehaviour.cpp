#include "code/engine/characterintentionbehaviour.h"

namespace engine
{
	// FUNCTION: ENGINE 0x1091C500
	content::ClassInfo* CharacterIntentionBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "CharacterIntentionBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1091C600
	int CharacterIntentionBehaviour::GetPlayerSlot() const
	{
		return control.slot;
	}

	// FUNCTION: ENGINE 0x1091C610
	void CharacterIntentionBehaviour::SetPlayerSlot(int newSlot)
	{
		control.slot = newSlot;
	}

	// FUNCTION: ENGINE 0x1091C660
	unsigned int CharacterIntentionBehaviour::GetInputMapIndex() const
	{
		return control.unknown4;
	}

	// FUNCTION: ENGINE 0x1091C670
	void CharacterIntentionBehaviour::SetInputMapIndex(unsigned int index)
	{
		control.unknown4 = index;
	}

	// FUNCTION: ENGINE 0x1091CA80
	content::MemberList* CharacterIntentionBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, CharacterIntentionBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberMetaType<CharacterIntentionBehaviour, int>(&CharacterIntentionBehaviour::GetPlayerSlot,
				&CharacterIntentionBehaviour::SetPlayerSlot, "n"), 0, "playerSlot" },
			{ content::GetMemberMetaType<CharacterIntentionBehaviour, unsigned int>(
				&CharacterIntentionBehaviour::GetInputMapIndex, &CharacterIntentionBehaviour::SetInputMapIndex, "n"), 0,
				"inputMapIndex" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1091C730
// FUNCTION: ENGINE 0x1091C740
// FUNCTION: ENGINE 0x1091C890
// FUNCTION: ENGINE 0x1091C8B0
// FUNCTION: ENGINE 0x1091C8C0
// FUNCTION: ENGINE 0x1091C8E0
// FUNCTION: ENGINE 0x1091C900
// FUNCTION: ENGINE 0x1091C910
// FUNCTION: ENGINE 0x1091C9A0
// FUNCTION: ENGINE 0x1091CA10
