// The GJK distance / intersection code (assert path code/ravenphysics/collision/narrowphase/src/gjk.cpp). Names and
// layout are guesses.
#ifndef RAVENPHYSICS_COLLISION_NARROWPHASE_GJK_H
#define RAVENPHYSICS_COLLISION_NARROWPHASE_GJK_H

#include "code/math/capsule.h"
#include "code/math/obb.h"
#include "code/math/vector.h"

namespace ravenphysics
{
	struct CollisionVolume6;

	// The ids of the support points of up to four simplex vertices
	struct GjkSimplex
	{
		// Appends a vertex of the given id and position to points unless the id is already in the simplex; returns
		// 1 when it was added (0x106736F0)
		int AddVertex(int id, math::Vector* points, math::Vector point);
		// Prints the number of points and their ids (0x10673290)
		void Dump();
		// Sets one id (0x10673230)
		void SetId(int index, const int* id);

		int ids[4];
		int count;
	};

	// Four points (the points of one simplex)
	struct GjkPoints
	{
		// Sets / gives one point (0x10673250 / 0x10673280)
		void Set(int index, const math::Vector* point);
		math::Vector* At(int index);

		math::Vector points[4];
	};

	struct GjkVolume;

	// Finds the point of a volume farthest along a direction: the point and its id are the results; hint is the id
	// of a good start (0 for none)
	typedef void (*GjkSupportFunction)(GjkVolume* volume, const math::Vector* direction, int hint, int* id,
		math::Vector* point);
	// The point of a volume with an id, and the function that prints a volume
	typedef void (*GjkPointFunction)(GjkVolume* volume, int id, math::Vector* point);
	typedef void (*GjkDumpFunction)(GjkVolume* volume);

	// The support functions of the shapes and their companions (0x10672750 on); the hull's are the volume's own
	void CapsuleSupport(GjkVolume* volume, const math::Vector* direction, int hint, int* id, math::Vector* point);
	void CapsulePoint(GjkVolume* volume, int id, math::Vector* point);
	void CapsuleDump(GjkVolume* volume);
	void BoxSupport(GjkVolume* volume, const math::Vector* direction, int hint, int* id, math::Vector* point);
	void BoxPoint(GjkVolume* volume, int id, math::Vector* point);
	void BoxDump(GjkVolume* volume);
	void SphereSupport(GjkVolume* volume, const math::Vector* direction, int hint, int* id, math::Vector* point);
	void SpherePoint(GjkVolume* volume, int id, math::Vector* point);
	void SphereDump(GjkVolume* volume);
	void HullSupport(GjkVolume* volume, const math::Vector* direction, int hint, int* id, math::Vector* point);
	void HullSupportFrom(GjkVolume* volume, const math::Vector* direction, int hint, int* id, math::Vector* point);
	void HullPoint(GjkVolume* volume, int id, math::Vector* point);
	void HullDump(GjkVolume* volume);

	// The sixteen floats of a shape: a capsule, a box or a sphere's centre, laid out as math::Capsule and math::OBB
	struct GjkShape
	{
		float values[16];
	};

	// A convex volume as the GJK sees it: the volume it was made from (for a hull) or the shape it stands for (a
	// capsule, a box or a sphere's centre, copied here), the support functions, the function that gives a point back
	// by its id and a function that prints it
	struct GjkVolume
	{
		// A hull of the collision volume (0x10673100; the constructors set everything)
		GjkVolume(CollisionVolume6* newVolume);
		// A shape of the given type, 0 a capsule, 1 a box, 2 a sphere, copied from sixteen floats (0x10673130)
		GjkVolume(const GjkShape* source, int type);

		// The shape's data, read as the type says
		const math::Capsule& GetCapsule() const
		{
			return *(const math::Capsule*)&shape;
		}
		const math::OBB& GetBox() const
		{
			return *(const math::OBB*)&shape;
		}

		CollisionVolume6* volume;         // 0x00
		GjkShape shape;                   // 0x04
		GjkSupportFunction support;       // 0x44
		GjkSupportFunction supportFrom;   // 0x48
		GjkPointFunction pointFromId;     // 0x4C
		GjkDumpFunction dump;             // 0x50
	};

	// The state of one GJK run (0xB0 bytes): the simplex of each volume with the support points, the closest
	// points found and the separating direction
	struct GjkState
	{
		// Copies (0x10673490 / 0x10673590)
		GjkState(const GjkState& other);
		GjkState& operator=(const GjkState& other);
		// Moves the simplexes towards the closest point to the origin of their difference, lands the direction to
		// it in direction and returns the squared distance, 0 when they touch (0x10673750)
		float Solve(math::Vector* direction);
		// Prints the simplexes and their points (0x10673310)
		void Dump();

		GjkPoints pointsA;
		GjkPoints pointsB;
		math::Vector closestA;
		math::Vector closestB;
		math::Vector normal;
		GjkSimplex simplexA;
		GjkSimplex simplexB;
		int unknownAC;
	};

	// The distance between two convex volumes along the search direction start (0x10677180)
	float GjkDistance(GjkState* state, GjkVolume* volumeA, GjkVolume* volumeB, const math::Vector* start);
}

#endif
