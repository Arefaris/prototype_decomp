// proto::WorldBoundary (RTTI and reflection names; a content library object): the outline of the playable world as a
// list of points. Unit 0x103B31B0 - 0x103B4180 (no assert path; the file name is a guess). The reflected names are
// original, the rest is guessed.
#ifndef PROTO_WORLDBOUNDARY_H
#define PROTO_WORLDBOUNDARY_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/math/vector.h"

namespace proto
{
	class WorldBoundary : public content::MetaLoadObject
	{
	public:
		// One corner of the outline (RTTI proto::WorldBoundary::Vertex; reflected: point)
		struct Vertex
		{
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			Vertex()
			{
			}
			Vertex(const Vertex& other) : point(other.point)
			{
			}
			Vertex& operator=(const Vertex& other)
			{
				point.x = other.point.x;
				point.y = other.point.y;
				point.z = other.point.z;
				return *this;
			}

			math::Vector point;
		};

		typedef container::ArrayDynamic<Vertex, container::AllocatorNew> VertexArray;

		// 0x103B3F80
		WorldBoundary();
		// 0x103B3FB0 (deleting destructor 0x103B4030)
		virtual ~WorldBoundary();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		VertexArray vertexList;  // +8
		int unknown14;
	};
}

namespace container
{
	// The engine moves the elements down in Erase with the loop of the pointer arrays' helper
	template<> struct ArrayEraseInline<proto::WorldBoundary::Vertex>
	{
		enum
		{
			value = 3
		};
	};
}

#endif
