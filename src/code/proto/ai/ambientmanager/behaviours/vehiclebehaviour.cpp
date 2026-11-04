// The vehicle layer of proto::VehicleBehaviour: the class info and the small slots and accessors of the unit that
// vehiclebehaviourambient.cpp continues (names of the accessors are guesses).
#include "code/proto/ai/ambientmanager/behaviours/vehiclebehaviourambient.h"

namespace proto
{
	// FUNCTION: ENGINE 0x10442100
	content::ClassInfo* VehicleBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::VehicleBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10442140
	void VehicleBehaviour::OnActiveChanged(bool active)
	{
		Behaviour::OnActiveChanged(active);
	}

	// FUNCTION: ENGINE 0x10442150
	void VehicleBehaviour::OnMessage(engine::Message* message)
	{
	}

	// FUNCTION: ENGINE 0x10442160
	bool VehicleBehaviour::Slot8()
	{
		return unknown9C;
	}

	// FUNCTION: ENGINE 0x10442170
	bool VehicleBehaviour::MarkUnknown9E()
	{
		bool marked = true;
		unknown9E = marked;
		if (0.0f >= unknownA0)
		{
			return marked;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10442190
	int VehicleBehaviour::GetUnknownA4()
	{
		return unknownA4;
	}

	// FUNCTION: ENGINE 0x104421A0
	bool VehicleBehaviour::IsBlocking()
	{
		return false;
	}

	// FUNCTION: ENGINE 0x104421B0
	math::Vector* VehicleBehaviour::GetExtents()
	{
		return &extents;
	}

	// FUNCTION: ENGINE 0x104421C0
	bool VehicleBehaviour::GetUnknown9D()
	{
		return unknown9D;
	}

	// FUNCTION: ENGINE 0x104421D0
	void VehicleBehaviour::ClearUnknown9D()
	{
		unknown9D = false;
	}

	// FUNCTION: ENGINE 0x104421E0
	void VehicleBehaviour::SetUnknown9D()
	{
		unknown9D = true;
	}
}
