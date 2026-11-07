#include "code/proto/ai/ambientmanager/ambientenums.h"
#include "code/proto/ai/ambientmanager/intersectiondata.h"

namespace content
{
	static const EnumValue sAmbientExcludeTypeValues[] =
	{
		{ "AmbientExcludeType_Pedestrians", 0 },
		{ "AmbientExcludeType_TrafficVehicles", 1 }
	};

	static const EnumValue sAlertTargetChoiceValues[] =
	{
		{ "AlertTargetChoice_Closest", 0 },
		{ "AlertTargetChoice_Giver", 1 },
		{ "AlertTargetChoice_Taker", 2 },
		{ "AlertTargetChoice_ClosestWeightedGiver", 3 },
		{ "AlertTargetChoice_ClosestWeightedTaker", 4 }
	};

	static const EnumValue sIntersectionStateValues[] =
	{
		{ "none", 0 },
		{ "green", 1 },
		{ "yellow", 2 },
		{ "red", 3 }
	};

	// FUNCTION: ENGINE 0x104098C0
	template<> void EnumInfo<proto::AmbientExcludeType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::AmbientExcludeType";
		*code = "p";
		*values = sAmbientExcludeTypeValues;
		*count = 2;
	}

	// FUNCTION: ENGINE 0x10430630
	template<> void EnumInfo<proto::IntersectionData::State>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::IntersectionData::State";
		*code = "pn";
		*values = sIntersectionStateValues;
		*count = 4;
	}

	// FUNCTION: ENGINE 0x10432F50
	template<> void EnumInfo<proto::AlertTargetChoice>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::AlertTargetChoice";
		*code = "p";
		*values = sAlertTargetChoiceValues;
		*count = 5;
	}
}
