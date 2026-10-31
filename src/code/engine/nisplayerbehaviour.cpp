#include "code/engine/nisplayerbehaviour.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/messagerouter.h"

namespace engine
{
	// The name of the NIS fight context (0x111C17DC, fightsystem.cpp)
	extern const char* gNISContextName;

	// 0x1131D370: the listeners of the scenario messages the player sends
	MessageListeners gNISPlayerListeners("scenario", 0);

	// FUNCTION: ENGINE 0x1091F890
	content::ClassInfo* NISPlayerBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::NISPlayerBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1091FA50
	NISPlayerBehaviour::NISPlayerBehaviour(GameObject* newOwner) : Behaviour(newOwner)
	{
		params = 0;
		camera = -1;
		package = 0;
		track = 0;
		state = 0;
		unknown78 = 0.0f;
		unknown70 = -1;
		sequencer.contextName.SetText(gNISContextName);
		Listen(0x17, true);
		Listen(0xd, true);
		Listen(0x18, true);
	}

	// FUNCTION: ENGINE 0x1091FB30
	void NISPlayerBehaviour::OnPostedMessage(Message* message)
	{
		if (message->type == 0x17)
		{
			NISQueryMessage* query = static_cast<NISQueryMessage*>(message);
			switch ((unsigned short)message->id)
			{
			case 10:
				if (state == 4 || state == 5 || state == 6)
				{
					query->name = nisName;
				}
				break;
			case 11:
				query->state = state;
				break;
			case 12:
				if (track != 0)
				{
					query->length = track->length;
				}
				else
				{
					query->length = 0.0f;
				}
				break;
			}
		}
	}

	// FUNCTION: ENGINE 0x1091FD20
	void NISPlayerBehaviour::SendBeginMessage()
	{
		ScenarioNISBeginMessage message(nisName);
		message.handles[0] = GetHandle(owner);
		SendMessage(&message, &gNISPlayerListeners);
	}

	// FUNCTION: ENGINE 0x1091FD80
	void NISPlayerBehaviour::SendEndMessage()
	{
		ScenarioNISEndMessage message(nisName);
		message.handles[0] = GetHandle(owner);
		SendMessage(&message, &gNISPlayerListeners);
	}

	// FUNCTION: ENGINE 0x1091FDE0
	void NISPlayerBehaviour::SendLoadCompleteMessage()
	{
		ScenarioNISLoadCompleteMessage message(nisName);
		message.handles[0] = GetHandle(owner);
		SendMessage(&message, &gNISPlayerListeners);
	}

	// FUNCTION: ENGINE 0x1091FFD0
	void NISPlayerBehaviour::OnLoaded()
	{
		SendLoadCompleteMessage();
		state = 3;
	}

	// FUNCTION: ENGINE 0x1091FEA0
	content::MemberList* NISPlayerBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, NISPlayerBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<NISPlayerBehaviour>(true, true, "pn"),
				content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((NISPlayerBehaviour*)0)->nisName,
				(int)&((NISPlayerBehaviour*)0)->nisName), "nisName" },
			{ content::GetClassMetaType<fight::Sequencer>(),
				content::MemberOffset(&((NISPlayerBehaviour*)0)->sequencer, (int)&((NISPlayerBehaviour*)0)->sequencer),
				"sequencer" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D796B0
// FUNCTION: ENGINE 0x10D8B430


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1091F9A0
// FUNCTION: ENGINE 0x1091FA10
// FUNCTION: ENGINE 0x1091FA20
