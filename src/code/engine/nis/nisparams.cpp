// engine::NISParams: see the header.
#include "code/engine/nis/nisparams.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108A7140
	NISParams::NISParams(int value) : GameObjectParams(value), inventory(0), unknown20(0)
	{
	}

	// FUNCTION: ENGINE 0x108A7170
	void NISParams::SetInventory(content::LoadInventory* value)
	{
		inventory = value;
	}

	// FUNCTION: ENGINE 0x108A7180
	int NISParams::GetUnknown1C() const
	{
		return unknown1C;
	}

	// FUNCTION: ENGINE 0x108A7190
	void NISParams::SetUnknown1C(int value)
	{
		unknown1C = value;
	}

	// FUNCTION: ENGINE 0x108A71A0
	float NISParams::GetUnknown24() const
	{
		return unknown24;
	}
}
