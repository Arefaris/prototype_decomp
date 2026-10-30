#include "code/proto/navmeshreflection.h"

namespace content
{
	static const EnumValue sAreaTypeValues[] =
	{
		{ "unknown", 0 },
		{ "intersection", 1 },
		{ "road", 2 },
		{ "crosswalk", 3 },
		{ "sidewalk", 4 },
		{ "crosswalkCorner", 5 },
		{ "Allyway", 6 },
		{ "rooftop", 7 },
		{ "stairway", 8 },
		{ "NoSpawn", 9 }
	};

	// FUNCTION: ENGINE 0x10567E10
	template<> void EnumInfo<proto::Area::AreaType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::Area::AreaType";
		*code = "p";
		*values = sAreaTypeValues;
		*count = 10;
	}
}

namespace proto
{
	// FUNCTION: ENGINE 0x10567D90
	content::ClassInfo* HackVector::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HackVector";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10567E50
	content::ClassInfo* Area::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::Area";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10567E90
	content::ClassInfo* LaneData::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::LaneData";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10567ED0
	content::ClassInfo* Edge::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::Edge";
		sInfo.code = "p";
		return &sInfo;
	}
}

// Kept copies (template instances and wrappers of this unit):
