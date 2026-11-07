#include "code/proto/worldboundary.h"
#include "code/math/segment.h"

namespace engine
{
	namespace driving
	{
		// 0x10D94F78: 0.0f in the pooled constants
		extern const float gZero;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x103B31B0
	content::ClassInfo* WorldBoundary::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WorldBoundary";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103B31F0
	content::ClassInfo* WorldBoundary::Vertex::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WorldBoundary::Vertex";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103B33C0
	content::MemberList* WorldBoundary::Vertex::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<Vertex, 0>("p"), 0, "point" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103B3D90
	content::MemberList* WorldBoundary::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<WorldBoundary, VertexArray>(content::GetClassMetaType<Vertex>(), "p"),
				PROTO_OFFSET(WorldBoundary, vertexList), "vertexList" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103B3460
	// NONMATCHING: the engine subtracts the previous x before the previous z in the second product (93.4 %)
#ifdef NONMATCHING
	int WorldBoundary::GetWindingNumber(const math::Vector* point)
	{
		if (vertexList.Size() < 2)
		{
			return 0;
		}
		float pointX = point->x;
		float pointZ = point->z;
		Vertex* end = vertexList.end;
		int winding = 0;
		float previousX = end[-1].point.x;
		float previousZ = end[-1].point.z;
		for (Vertex* vertex = vertexList.begin; vertex != end; vertex++)
		{
			float x = vertex->point.x;
			float z = vertex->point.z;
			if (pointZ >= previousZ)
			{
				if (pointZ < z
					&& (x - previousX) * (pointZ - previousZ) - (z - previousZ) * (pointX - previousX) > engine::driving::gZero)
				{
					winding++;
				}
			}
			else if (z <= pointZ
				&& (x - previousX) * (pointZ - previousZ) - (z - previousZ) * (pointX - previousX) < 0.0f)
			{
				winding--;
			}
			previousX = x;
			previousZ = z;
		}
		return winding;
	}
#endif

	// FUNCTION: ENGINE 0x103B3580
	bool WorldBoundary::GetClosestPoint(const math::Vector* point, math::Vector* closest)
	{
		int count = vertexList.Size();
		if (count == 0)
		{
			return false;
		}
		if (count == 1)
		{
			closest->x = vertexList.begin->point.x;
			closest->y = vertexList.begin->point.y;
			closest->z = vertexList.begin->point.z;
			return true;
		}
		Vertex* end = vertexList.end;
		float best = 3.4028234e+38f;
		math::Vector previous;
		previous.x = end[-1].point.x;
		previous.y = end[-1].point.y;
		previous.z = end[-1].point.z;
		math::Vector found;
		for (Vertex* vertex = vertexList.begin; vertex != end; vertex++)
		{
			math::Vector current;
			current.x = vertex->point.x;
			current.y = vertex->point.y;
			current.z = vertex->point.z;
			math::Segment segment;
			segment.start.x = previous.x;
			segment.start.y = previous.y;
			segment.start.z = previous.z;
			segment.end.x = current.x;
			segment.end.y = current.y;
			segment.end.z = current.z;
			float distance = segment.ClosestPoint(*point, found);
			if (distance < best)
			{
				closest->x = found.x;
				closest->y = found.y;
				closest->z = found.z;
				best = distance;
			}
			previous.x = current.x;
			previous.y = current.y;
			previous.z = current.z;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x103B3F80
	WorldBoundary::WorldBoundary()
	{
	}

	// FUNCTION: ENGINE 0x103B3FB0
	WorldBoundary::~WorldBoundary()
	{
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103B3290
// FUNCTION: ENGINE 0x103B3340
// FUNCTION: ENGINE 0x103B3350
// FUNCTION: ENGINE 0x103B3360
// FUNCTION: ENGINE 0x103B3370
// FUNCTION: ENGINE 0x103B33B0
// FUNCTION: ENGINE 0x103B3710
// FUNCTION: ENGINE 0x103B3720
// FUNCTION: ENGINE 0x103B3790
// FUNCTION: ENGINE 0x103B37A0
// FUNCTION: ENGINE 0x103B37D0
// FUNCTION: ENGINE 0x103B37F0
// FUNCTION: ENGINE 0x103B3850
// FUNCTION: ENGINE 0x103B38B0
// FUNCTION: ENGINE 0x103B38F0
// FUNCTION: ENGINE 0x103B3910
// FUNCTION: ENGINE 0x103B39A0
// FUNCTION: ENGINE 0x103B3A60
// FUNCTION: ENGINE 0x103B3AC0
// FUNCTION: ENGINE 0x103B3D40
// FUNCTION: ENGINE 0x103B3E40
// FUNCTION: ENGINE 0x103B3E60
// FUNCTION: ENGINE 0x103B3EC0
// FUNCTION: ENGINE 0x103B3FE0
// FUNCTION: ENGINE 0x103B4030
// FUNCTION: ENGINE 0x103B4060

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103B38D0
// FUNCTION: ENGINE 0x103B39D0
// FUNCTION: ENGINE 0x103B3CF0
