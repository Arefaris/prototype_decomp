#include "code/proto/ai/ambientmanager/behaviours/vehiclebehaviouraicharacter.h"

namespace proto
{
	class NavArea
	{
	public:
		// 0x105680D0: takes the car out of the area's list of cars
		void RemoveVehicle(VehicleBehaviour* vehicle);
	};

	// FUNCTION: ENGINE 0x10444170
	content::ClassInfo* VehicleBehaviourAICharacter::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::VehicleBehaviourAICharacter";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104441B0
	void VehicleBehaviourAICharacter::Slot1()
	{
		Listen2(4, true);
		VehicleBehaviour::Slot1();
		lod.Attach(this);
		lodVehicle = &lod;
		unknownA4 = 3;
		halted = false;
	}

	// FUNCTION: ENGINE 0x10444200
	void VehicleBehaviourAICharacter::OnActiveChanged(bool active)
	{
		Behaviour::OnActiveChanged(active);
	}

	// FUNCTION: ENGINE 0x10444D00
	// NONMATCHING: the engine reserves a stack word it never uses and ends in a jump after restoring the frame (39 %)
#ifdef NONMATCHING
	VehicleBehaviourAICharacter::~VehicleBehaviourAICharacter()
	{
		NavArea* area = unknown74;
		if (area != 0)
		{
			area->RemoveVehicle(this);
		}
		unknown74 = 0;
	}
#endif

	// FUNCTION: ENGINE 0x10444EF0
	VehicleBehaviourAICharacter::VehicleBehaviourAICharacter(engine::GameObject* newOwner) :
		VehicleBehaviour(newOwner), unknownC8(0.0f), unknownCC(0.0f)
	{
		Listen(0x26, true);
	}

	// FUNCTION: ENGINE 0x104443A0
	content::MemberList* VehicleBehaviourAICharacter::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<VehicleBehaviour>();
		static content::BaseClassCasterImpl<VehicleBehaviour, VehicleBehaviourAICharacter> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10444330
// FUNCTION: ENGINE 0x10444340
// FUNCTION: ENGINE 0x10444F50
