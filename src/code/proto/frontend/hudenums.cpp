#include "code/proto/frontend/hudenums.h"

namespace content
{
	static const EnumValue sHUDTransformationSlotValues[] =
	{
		{ "Attack", 0 },
		{ "Defense", 1 },
		{ "Senses", 2 },
		{ "Disguise", 3 }
	};

	// FUNCTION: ENGINE 0x104B0950
	template<> void EnumInfo<proto::HUDTransformationSlot>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::HUDTransformationSlot";
		*code = "p";
		*values = sHUDTransformationSlotValues;
		*count = 4;
	}

	static const EnumValue sHUDPowerValues[] =
	{
		{ "None", 0 },
		{ "Claws", 1 },
		{ "Blades", 2 },
		{ "HammerFist", 3 },
		{ "WhipFist", 4 },
		{ "MuscleMass", 5 },
		{ "Armour", 6 },
		{ "Spines", 7 },
		{ "Shield", 8 },
		{ "ChameleonicSkin", 9 },
		{ "ThermalVision", 10 },
		{ "MotherVision", 11 },
		{ "Disguise", 12 },
		{ "Alex", 13 }
	};

	// FUNCTION: ENGINE 0x104B0990
	template<> void EnumInfo<proto::HUDPower>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::HUDPower";
		*code = "p";
		*values = sHUDPowerValues;
		*count = 14;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
