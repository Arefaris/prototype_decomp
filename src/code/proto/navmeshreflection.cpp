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
#define PROTO_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

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

namespace proto
{
	// FUNCTION: ENGINE 0x1056AB70
	content::MemberList* HackVector::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<HackVector, float, 0>("p"), PROTO_OFFSET(HackVector, x), "x" },
			{ content::GetMemberPrimitiveMetaType<HackVector, float, 1>("p"), PROTO_OFFSET(HackVector, y), "y" },
			{ content::GetMemberPrimitiveMetaType<HackVector, float, 2>("p"), PROTO_OFFSET(HackVector, z), "z" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10567F20
	LaneData::LaneData() : currentLane(0), nextEdge(0), nextLane(0), nextLightIndex(0), active(1)
	{
	}

	// FUNCTION: ENGINE 0x10567F40
	void LaneData::SetNextLightIndex(char value)
	{
		nextLightIndex = value;
	}

	// FUNCTION: ENGINE 0x10567F60
	char LaneData::GetNextLightIndex() const
	{
		return nextLightIndex;
	}

	// FUNCTION: ENGINE 0x10567F70
	void LaneData::SetActive(bool value)
	{
		active = value;
	}

	// FUNCTION: ENGINE 0x10567F90
	bool LaneData::GetActive() const
	{
		return active;
	}

	// FUNCTION: ENGINE 0x1056C190
	content::MemberList* LaneData::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<LaneData, char, 0>("p"), PROTO_OFFSET(LaneData, currentLane),
				"currentLane" },
			{ content::GetMemberPrimitiveMetaType<LaneData, char, 1>("p"), PROTO_OFFSET(LaneData, nextEdge),
				"nextEdge" },
			{ content::GetMemberPrimitiveMetaType<LaneData, char, 2>("p"), PROTO_OFFSET(LaneData, nextLane),
				"nextLane" },
			{ content::GetMemberMetaType<LaneData, char>(&LaneData::GetNextLightIndex, &LaneData::SetNextLightIndex, "p"),
				0, "nextLightIndex" },
			{ content::GetMemberMetaType<LaneData, bool>(&LaneData::GetActive, &LaneData::SetActive, "p"), 0,
				"active" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}
}

// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x10569E60
// FUNCTION: ENGINE 0x10569EA0
// FUNCTION: ENGINE 0x10569EE0
// FUNCTION: ENGINE 0x1056A6E0
// FUNCTION: ENGINE 0x1056A700
// FUNCTION: ENGINE 0x1056A720
// FUNCTION: ENGINE 0x1056A740
// FUNCTION: ENGINE 0x1056A760
// FUNCTION: ENGINE 0x1056A780
// FUNCTION: ENGINE 0x1056B880
// FUNCTION: ENGINE 0x1056B900
// FUNCTION: ENGINE 0x10569D60
// FUNCTION: ENGINE 0x10569DA0
// FUNCTION: ENGINE 0x10569DE0
