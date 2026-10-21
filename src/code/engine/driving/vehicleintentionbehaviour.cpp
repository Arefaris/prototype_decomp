// engine::driving::VehicleIntentionBehaviour: see the header.
#include "code/engine/driving/vehicleintentionbehaviour.h"
#include "code/engine/message.h"

namespace engine
{
	// The message type 0xE (PlayerControlChangedMessage in the RTTI): the player that now controls the object
	struct PlayerControlChangedMessage : public Message
	{
		PlayerControlChangedMessage() : Message(0xe, 0)
		{
		}

		PlayerControlInfo control;  // +0xC
	};
}

namespace engine
{
	namespace driving
	{
		// FUNCTION: ENGINE 0x109379C0
		content::ClassInfo* VehicleIntentionBehaviour::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "VehicleIntentionBehaviour";
			sInfo.code = "pn";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10937A00
		VehicleIntentionBehaviour::VehicleIntentionBehaviour(GameObject* newOwner) : Behaviour(newOwner)
		{
			Listen2(4, true);
			Listen(0xe, true);
		}

		// FUNCTION: ENGINE 0x10937A40
		void VehicleIntentionBehaviour::Update(float dt, unsigned short mask)
		{
			if (control.Get() != 0)
			{
				void* input = control.Get();
				if (input != 0)
				{
					ApplyInput(input);
				}
			}
		}

		// FUNCTION: ENGINE 0x10937A70
		void VehicleIntentionBehaviour::OnMessage(Message* message)
		{
			if (message->type == 0xe)
			{
				PlayerControlChangedMessage* changed = (PlayerControlChangedMessage*)message;
				control.slot = changed->control.slot;
				control.unknown4 = changed->control.unknown4;
			}
		}

		// FUNCTION: ENGINE 0x10937A90
		int VehicleIntentionBehaviour::GetPlayerSlot() const
		{
			return control.slot;
		}

		// FUNCTION: ENGINE 0x10937AA0
		void VehicleIntentionBehaviour::SetPlayerSlot(int newSlot)
		{
			control.slot = newSlot;
		}

		// FUNCTION: ENGINE 0x10937BD0
		content::MemberList* VehicleIntentionBehaviour::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<Behaviour>();
			static content::BaseClassCasterImpl<Behaviour, VehicleIntentionBehaviour> sCaster;
			sList.baseCaster = &sCaster;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetMemberMetaType<VehicleIntentionBehaviour, int>(&VehicleIntentionBehaviour::GetPlayerSlot,
					&VehicleIntentionBehaviour::SetPlayerSlot, "n"), 0, "playerSlot" }
			};
			sList.members = sMembers;
			sList.count = 1;
			return &sList;
		}
	}
}
