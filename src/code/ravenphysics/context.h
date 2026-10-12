// The parts of the physics library (ravenphysics, assert path code/ravenphysics/src/context.cpp) that the engine's
// units call: the query filter, the ray query and its hits, and the context behind the global 0x1128356C. Only the
// members those callers touch are named; everything here is a guess except the class names the RTTI gives.
#ifndef RAVENPHYSICS_CONTEXT_H
#define RAVENPHYSICS_CONTEXT_H

#include "code/content/loadinventory.h"
#include "code/math/vector.h"

namespace ravenphysics
{
	// What a query collides with (0x10653860 constructs it from the physics library's defaults; meanings unknown)
	struct IntersectionProperties
	{
		IntersectionProperties();

		int unknown0;
		int unknown4;
	};

	// ravenphysics::IntersectionPropertiesLoader (RTTI; a load object of the physics library)
	class IntersectionPropertiesLoader : public content::LoadObject
	{
	public:
		unsigned char unknown8[0x3c - 8];
		int unknown3C;
		int unknown40;
	};

	// The properties plus one more word, copied as a whole into a query
	struct IntersectionFilter
	{
		IntersectionFilter()
		{
			unknown8 = 0;
		}

		IntersectionProperties properties;
		int unknown8;
	};

	// A segment query from start to end
	struct RayQuery
	{
		RayQuery()
		{
			unknown24 = 3;
		}

		math::Vector start;
		math::Vector end;
		IntersectionFilter filter;
		int unknown24;
	};

	// One hit of a query (0x30 bytes): the distance from the start, the object hit and the surface normal
	struct RayHit
	{
		// The material byte of the surface hit (0x1066C4C0)
		unsigned char GetMaterial() const;

		float distance;
		int unknown4;
		int unknown8;
		math::Vector normal;
		unsigned char unknown18[0x30 - 0x18];
	};

	// The hits a query appends to (begin / end / capacity)
	struct RayHitArray
	{
		RayHit* begin;
		RayHit* end;
		RayHit* capacity;
	};

	class Context
	{
	public:
		// The hits along the query's segment, appended to hits after clearing it; false when there are none
		// (0x106593A0)
		bool CastRay(const RayQuery& query, RayHitArray* hits);
	};

	// The physics context (0x1128356C)
	extern Context* gContext;

	// Sorts hits by distance (another unit's instance of a sort template, 0x1006DC30)
	void SortHits(RayHit* begin, RayHit* end);
}

namespace engine
{
	// The engine's shared buffer of query hits, held for the length of a query (another unit, 0x107E3C20 -
	// 0x107E6CD0; the class name is a guess)
	class RayHitBufferLock
	{
	public:
		// Takes the buffer, emptied when clear is set (0x107E6CD0)
		RayHitBufferLock(bool clear);
		// 0x107E3C20
		~RayHitBufferLock();
		// 0x107E3C30
		ravenphysics::RayHitArray& Get();
	};
}

#endif
