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

	// FUNCTION: ENGINE 0x10567DD0
	content::ClassInfo* AmbientNavMesh::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AmbientNavMesh";
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

	// FUNCTION: ENGINE 0x1056CB40
	content::MemberList* Edge::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Edge, unsigned short, 0>("p"), PROTO_OFFSET(Edge, start), "start" },
			{ content::GetMemberPrimitiveMetaType<Edge, unsigned short, 1>("p"), PROTO_OFFSET(Edge, ajacentArea),
				"ajacentArea" },
			{ content::GetMemberPrimitiveMetaType<Edge, unsigned short, 2>("p"), PROTO_OFFSET(Edge, intersectionIndex),
				"intersectionIndex" },
			{ content::GetMemberPrimitiveMetaType<Edge, unsigned char, 3>("p"), PROTO_OFFSET(Edge, numLanes),
				"numLanes" },
			{ content::GetArrayDynamicMetaType<Edge, LaneDataArray>(content::GetClassMetaType<LaneData>(), "p"),
				PROTO_OFFSET(Edge, laneData), "laneData" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1056D7F0
	content::MemberList* Area::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Area, unsigned short, 0>("p"), PROTO_OFFSET(Area, index), "index" },
			{ content::GetEnumMetaType<AreaType>(), 0x20, "type" },
			{ content::GetArrayDynamicMetaType<Area, EdgeArray>(content::GetClassMetaType<Edge>(), "p"),
				PROTO_OFFSET(Area, edges), "edges" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1056DFA0
	content::MemberList* AmbientNavMesh::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<AmbientNavMesh, HackVectorArray>(content::GetClassMetaType<HackVector>(),
				"p"), PROTO_OFFSET(AmbientNavMesh, vertices), "vertices" },
			{ content::GetArrayDynamicMetaType<AmbientNavMesh, JointNameArray>(
				content::GetNameMetaType<AmbientNavMesh>(true, true, "p"), "p"),
				PROTO_OFFSET(AmbientNavMesh, intersectionNames), "intersectionNames" },
			{ content::GetArrayDynamicMetaType<AmbientNavMesh, AreaArray>(content::GetClassMetaType<Area>(), "p"),
				PROTO_OFFSET(AmbientNavMesh, areas), "areas" }
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

namespace content
{
#define PROTO_NAV_HELPER_SLOTS(ArrayType) 	int ArrayDynamicHelper<ArrayType>::Size(void* array) 	{ 		return ((ArrayType*)array)->Size(); 	} 	void* ArrayDynamicHelper<ArrayType>::Get(void* array, int index) 	{ 		return ((ArrayType*)array)->begin + index; 	} 	void* ArrayDynamicHelper<ArrayType>::GetConst(void* array, int index) 	{ 		return ((ArrayType*)array)->begin + index; 	} 	int ArrayDynamicHelper<ArrayType>::Capacity(void* array) 	{ 		return ((ArrayType*)array)->Capacity(); 	}

#define PROTO_NAV_HELPER_EXPAND(ArrayType, allocate) 	void ArrayDynamicHelper<ArrayType>::Expand(void* array, unsigned int count) 	{ 		ArrayType* a = (ArrayType*)array; 		if (a->Capacity() == 0) 		{ 			allocate; 		} 		else if (count + a->Size() > a->Capacity()) 		{ 			a->Reserve(count + a->Size()); 		} 	}

	PROTO_NAV_HELPER_EXPAND(proto::LaneDataArray, a->Allocate(count))
	PROTO_NAV_HELPER_EXPAND(proto::EdgeArray, a->Create(count))
	PROTO_NAV_HELPER_EXPAND(proto::AreaArray, a->Allocate(count))
	PROTO_NAV_HELPER_EXPAND(proto::HackVectorArray, a->Allocate(count))

	PROTO_NAV_HELPER_SLOTS(proto::LaneDataArray)
	PROTO_NAV_HELPER_SLOTS(proto::EdgeArray)
	PROTO_NAV_HELPER_SLOTS(proto::AreaArray)
	PROTO_NAV_HELPER_SLOTS(proto::HackVectorArray)
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
// FUNCTION: ENGINE 0x10569F20
// FUNCTION: ENGINE 0x10569F60
// FUNCTION: ENGINE 0x10569FA0
// FUNCTION: ENGINE 0x10569FE0
// FUNCTION: ENGINE 0x10569E20
// FUNCTION: ENGINE 0x10568920
// FUNCTION: ENGINE 0x10568940
// FUNCTION: ENGINE 0x10568960
// FUNCTION: ENGINE 0x105688C0
// FUNCTION: ENGINE 0x10568910
// FUNCTION: ENGINE 0x105688D0
// FUNCTION: ENGINE 0x10568590
// FUNCTION: ENGINE 0x1056B980
// FUNCTION: ENGINE 0x1056B820
// FUNCTION: ENGINE 0x1056B700
// FUNCTION: ENGINE 0x1056B760
// FUNCTION: ENGINE 0x1056B7C0
// FUNCTION: ENGINE 0x1056B670
// FUNCTION: ENGINE 0x1056C7D0
// FUNCTION: ENGINE 0x1056A4F0
// FUNCTION: ENGINE 0x1056A510
// FUNCTION: ENGINE 0x1056A7E0
// FUNCTION: ENGINE 0x1056A800
// FUNCTION: ENGINE 0x1056A450
// FUNCTION: ENGINE 0x1056A4A0
// FUNCTION: ENGINE 0x1056A480
// FUNCTION: ENGINE 0x1056A6B0
// FUNCTION: ENGINE 0x1056A210
// FUNCTION: ENGINE 0x1056A250
// FUNCTION: ENGINE 0x1056A230
// FUNCTION: ENGINE 0x1056A690
// FUNCTION: ENGINE 0x1056A610
// FUNCTION: ENGINE 0x1056A080
// FUNCTION: ENGINE 0x1056A640
// FUNCTION: ENGINE 0x1056A660
// FUNCTION: ENGINE 0x105689B0
// FUNCTION: ENGINE 0x105689E0
// FUNCTION: ENGINE 0x10568A20
// FUNCTION: ENGINE 0x10568DF0
// FUNCTION: ENGINE 0x1056C910
// FUNCTION: ENGINE 0x1056E400
// FUNCTION: ENGINE 0x1056EC00
// FUNCTION: ENGINE 0x1056C8A0
// FUNCTION: ENGINE 0x1056A270
// FUNCTION: ENGINE 0x1056A530
// FUNCTION: ENGINE 0x1056BD40
// FUNCTION: ENGINE 0x1056A280
// FUNCTION: ENGINE 0x10568730
// FUNCTION: ENGINE 0x1056A130
// FUNCTION: ENGINE 0x1056A100
// FUNCTION: ENGINE 0x1056A0A0
// FUNCTION: ENGINE 0x10568570
// FUNCTION: ENGINE 0x1056A310
// FUNCTION: ENGINE 0x1056A2B0
// FUNCTION: ENGINE 0x1056A050
// FUNCTION: ENGINE 0x1056A200
// FUNCTION: ENGINE 0x1056A440
// FUNCTION: ENGINE 0x1056A4E0
