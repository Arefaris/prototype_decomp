// The classes the navigation mesh's reflection lists (RTTI and reflection names, namespace proto): a vertex, an area
// of the mesh, one of its edges and the lanes of an edge. Only the class infos are reconstructed (unit 0x10567D90 -
// 0x1056EF20, no assert path); the layouts are in navmesh.h as far as they are known.
#ifndef PROTO_NAVMESHREFLECTION_H
#define PROTO_NAVMESHREFLECTION_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/proto/arrayhelper.h"

namespace proto
{
	// A vertex of the mesh (three floats; RTTI proto::HackVector)
	struct HackVector
	{
		// 0x10567D90
		static content::ClassInfo* GetClassInfo();
		// 0x1056AB70
		static content::MemberList* GetMembers();

		float x;
		float y;
		float z;
	};

	// One lane of an edge (RTTI proto::LaneData, 4 bytes): the lane the vehicle is in, where it goes next and the light
	// it waits for. The reflected names are original, the rest is guessed.
	struct LaneData
	{
		// 0x10567F20: lane 0, edge 0, lane 0, light 0, active
		LaneData();

		// 0x10567E90
		static content::ClassInfo* GetClassInfo();
		// 0x1056C190
		static content::MemberList* GetMembers();

		// 0x10567F60 / 0x10567F40: the low four bits of the fourth byte
		char GetNextLightIndex() const;
		void SetNextLightIndex(char value);
		// 0x10567F90 / 0x10567F70: the bit above them
		bool GetActive() const;
		void SetActive(bool value);

		union
		{
			// The first two bytes compare as one key
			unsigned short key;
			struct
			{
				char currentLane;
				char nextEdge;
			};
		};
		char nextLane;  // +2
		unsigned char nextLightIndex : 4;  // +3
		unsigned char active : 1;
		unsigned char unknown3 : 3;
	};

	typedef container::ArrayDynamic<LaneData, container::AllocatorNew> LaneDataArray;
	typedef container::ArrayDynamic<HackVector, container::AllocatorNew> HackVectorArray;

	// One edge of an area (RTTI proto::Edge, 0x1C bytes): the vertex it starts at, the area behind it and its lanes
	struct Edge
	{
		Edge()
		{
		}
		Edge(const Edge& other) : laneData(other.laneData)
		{
			CopyFields(other);
		}
		Edge& operator=(const Edge& other)
		{
			laneData = other.laneData;
			CopyFields(other);
			return *this;
		}

		// 0x10567ED0
		static content::ClassInfo* GetClassInfo();
		// 0x1056CB40
		static content::MemberList* GetMembers();

		void CopyFields(const Edge& other)
		{
			start = other.start;
			intersectionIndex = other.intersectionIndex;
			ajacentArea = other.ajacentArea;
			numLanes = other.numLanes;
		}

		unsigned short start;  // +0
		unsigned short intersectionIndex;  // +2
		unsigned short ajacentArea;  // +4
		unsigned char numLanes;  // +6
		unsigned char unknown7;
		unsigned char unknown8[4];
		LaneDataArray laneData;  // +0xC
		int unknown18;  // behind the array: its allocator word
	};

	typedef container::ArrayDynamic<Edge, container::AllocatorNew> EdgeArray;

	// An area of the mesh (RTTI proto::Area, 0x40 bytes: the record navarea.h calls NavArea and navmesh.h calls
	// NavMeshHull is this one)
	struct Area
	{
		Area()
		{
		}
		Area(const Area& other) : edges(other.edges)
		{
			CopyFields(other);
		}
		Area& operator=(const Area& other)
		{
			edges = other.edges;
			CopyFields(other);
			return *this;
		}

		// The kinds of area (reflected as proto::Area::AreaType)
		enum AreaType
		{
			AREA_UNKNOWN = 0,
			AREA_INTERSECTION = 1,
			AREA_ROAD = 2,
			AREA_CROSSWALK = 3,
			AREA_SIDEWALK = 4,
			AREA_CROSSWALK_CORNER = 5,
			AREA_ALLYWAY = 6,
			AREA_ROOFTOP = 7,
			AREA_STAIRWAY = 8,
			AREA_NO_SPAWN = 9
		};

		// 0x10567E50
		static content::ClassInfo* GetClassInfo();
		// 0x1056D7F0
		static content::MemberList* GetMembers();

		void CopyFields(const Area& other)
		{
			unknown10[0] = other.unknown10[0];
		}

		EdgeArray edges;  // +0
		int unknownC;  // behind the array: its allocator word
		unsigned char unknown10[0x10];
		int areaType;  // +0x20
		unsigned char unknown24[0x16];
		unsigned short index;  // +0x3A
		unsigned char unknown3C[4];
	};

	typedef container::ArrayDynamic<Area, container::AllocatorNew> AreaArray;

	// The navigation mesh as a load object (RTTI proto::AmbientNavMesh, 0x4C bytes)
	class AmbientNavMesh : public content::MetaLoadObject
	{
	public:
		AmbientNavMesh();
		static content::ClassInfo* GetClassInfo();
		// 0x1056DFA0
		static content::MemberList* GetMembers();

		HackVectorArray vertices;  // +8
		int unknown14;  // behind the array: its allocator word
		JointNameArray intersectionNames;  // +0x18
		int unknown24;
		unsigned char unknown28[0x10];
		AreaArray areas;  // +0x38
		int unknown44;
	};
}

#endif
