#include "code/proto/behaviours/buttonhintbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10061C80
	content::ClassInfo* ButtonHintBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ButtonHintBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10063020
	void ButtonHintBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 2:
			Reset();
			break;
		case 0x37:
			switch ((unsigned short)message->id)
			{
			case 0:
				AddHint(static_cast<AddButtonHintMessage*>(message));
				break;
			case 1:
				RemoveHint(static_cast<RemoveButtonHintMessage*>(message)->scenarioMessage);
				break;
			case 2:
				EnableHints(static_cast<EnableButtonHintsMessage*>(message)->enable);
				break;
			case 3:
				IsHintShowing(static_cast<IsButtonHintShowingMessasge*>(message));
				break;
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x100625F0
	content::MemberList* ButtonHintBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, ButtonHintBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10062120
// FUNCTION: ENGINE 0x10062130
