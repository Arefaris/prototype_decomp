// The classes the navigation mesh's reflection lists (RTTI and reflection names, namespace proto): a vertex, an area
// of the mesh, one of its edges and the lanes of an edge. Only the class infos are reconstructed (unit 0x10567D90 -
// 0x1056EF20, no assert path); the layouts are in navmesh.h as far as they are known.
#ifndef PROTO_NAVMESHREFLECTION_H
#define PROTO_NAVMESHREFLECTION_H

#include "code/content/metatype.h"

namespace proto
{
	// A vertex of the mesh (three floats; RTTI proto::HackVector)
	struct HackVector
	{
		// 0x10567D90
		static content::ClassInfo* GetClassInfo();
	};

	// An area of the mesh (RTTI proto::Area)
	struct Area
	{
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
	};

	// One lane of an edge (RTTI proto::LaneData)
	struct LaneData
	{
		// 0x10567E90
		static content::ClassInfo* GetClassInfo();
	};

	// One edge of an area (RTTI proto::Edge)
	struct Edge
	{
		// 0x10567ED0
		static content::ClassInfo* GetClassInfo();
	};
}

#endif
