#include "code/proto/ai/ambientmanager/behaviours/aicharacterlodvehicle.h"

namespace proto
{
	// FUNCTION: ENGINE 0x10440A00
	void AICharacterLODVehicle::Attach(VehicleBehaviour* newVehicle)
	{
		vehicle = newVehicle;
		unknown4 = newVehicle->owner;
	}

	// FUNCTION: ENGINE 0x10440A20
	void AICharacterLODVehicle::Detach()
	{
		vehicle = 0;
		unknown4 = 0;
	}

	// FUNCTION: ENGINE 0x10440A30
	void AICharacterLODVehicle::Slot2(int a)
	{
	}

	// FUNCTION: ENGINE 0x10440A40
	void AICharacterLODVehicle::Slot3()
	{
	}

	// FUNCTION: ENGINE 0x10440A50
	bool AICharacterLODVehicle::Slot4()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10440A60
	bool AICharacterLODVehicle::Slot5()
	{
		return Slot4();
	}

	// FUNCTION: ENGINE 0x10440A70
	void AICharacterLODVehicle::Slot6()
	{
	}

	// FUNCTION: ENGINE 0x10440A80
	void AICharacterLODVehicle::Slot7()
	{
	}

	// FUNCTION: ENGINE 0x10440B50
	AICharacterLODVehicle::AICharacterLODVehicle()
	{
		unknownC = false;
		unknown4 = 0;
		vehicle = 0;
	}

	// FUNCTION: ENGINE 0x10440B70
	AICharacterLODVehicle::~AICharacterLODVehicle()
	{
		Detach();
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104409F0
