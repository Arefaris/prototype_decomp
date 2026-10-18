#include <math.h>

#include "code/core/report.h"
#include "code/math/worldbounds.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/collision/narrowphase/gjk.h"

#define GJK_FILE "..\\..\\..\\code\\ravenphysics\\collision\\narrowphase\\src\\gjk.cpp"
// The file the engine's header code reports from (the path of the machine it was built on)
#define GJK_HEADER_FILE "c:\\workspace\\outrun\\proto\\atg\\runtime\\code\\ravenphysics/collision/narrowphase/src/gjk.hpp"

// A message the report channel can switch off for good (the static flag), with the arguments of its format and the
// zero the engine ends them with
#define OLD_REPORT_AT(file, line, format, ...) \
	do \
	{ \
		static bool sEnabled = true; \
		if (sEnabled) \
		{ \
			if (core::Report(0, 0, file, line, 0, format, __VA_ARGS__) == 3) \
			{ \
				sEnabled = false; \
			} \
		} \
	} while (0)

namespace ravenphysics
{
	// The support function of a capsule: the end of its axis farthest along the direction (0x10672750)
	// FUNCTION: ENGINE 0x10672750
	// EQUIVALENT: the engine loads the direction's x component ahead of the capsule's in the last product of the dot
	// product and ours the other way round (the product is the same), 89.7 %
	void CapsuleSupport(GjkVolume* volume, const math::Vector* direction, int hint, int* id, math::Vector* point)
	{
		const math::Capsule& capsule = volume->GetCapsule();
		const math::Vector& axis = capsule.direction;
		float along;
		if (axis.z * direction->z + axis.y * direction->y + axis.x * direction->x >= 0.0f)
		{
			*id = 0;
			along = capsule.halfLength;
		}
		else
		{
			*id = 1;
			along = math::WORLD_MIN - capsule.halfLength;
		}
		point->x = capsule.direction.x * along + capsule.centre.x;
		point->y = capsule.direction.y * along + capsule.centre.y;
		point->z = capsule.direction.z * along + capsule.centre.z;
	}

	// FUNCTION: ENGINE 0x106727F0
	void CapsulePoint(GjkVolume* volume, int id, math::Vector* point)
	{
		const math::Capsule& capsule = volume->GetCapsule();
		float along;
		if (id == 0)
		{
			along = capsule.halfLength;
		}
		else
		{
			along = math::WORLD_MIN - capsule.halfLength;
		}
		point->x = capsule.direction.x * along + capsule.centre.x;
		point->y = capsule.direction.y * along + capsule.centre.y;
		point->z = capsule.direction.z * along + capsule.centre.z;
	}

	// FUNCTION: ENGINE 0x10672850
	void CapsuleDump(GjkVolume* volume)
	{
		const math::Capsule& capsule = volume->GetCapsule();
		OLD_REPORT_AT(GJK_FILE, 123, "Capsule: ", 0);
		capsule.centre.Print();
		capsule.direction.Print();
	}

	// The support function of a box: the corner farthest along the direction, the id of which has a bit set for each
	// axis the direction points against (0x106728A0)
	// FUNCTION: ENGINE 0x106728A0
	// NONMATCHING: the engine keeps the direction, the centre and the axes in eight registers and builds the point
	// one axis at a time between the three decisions; ours spills and orders the sums differently, 13 %
#ifdef NONMATCHING
	void BoxSupport(GjkVolume* volume, const math::Vector* direction, int hint, int* id, math::Vector* point)
	{
		const math::OBB& box = volume->GetBox();
		float x = direction->x;
		float y = direction->y;
		float z = direction->z;
		int bits = 0;
		float extent2;
		if (box.axis[2].y * y + box.axis[2].z * z + x * box.axis[2].x >= 0.0f)
		{
			extent2 = box.extents.z;
		}
		else
		{
			extent2 = math::WORLD_MIN - box.extents.z;
			bits = 1;
		}
		float px = box.axis[2].x * extent2 + box.centre.x;
		float py = box.axis[2].y * extent2 + box.centre.y;
		float pz = box.axis[2].z * extent2 + box.centre.z;
		float extent1;
		if (box.axis[1].y * y + box.axis[1].z * z + box.axis[1].x * x >= 0.0f)
		{
			extent1 = box.extents.y;
		}
		else
		{
			extent1 = math::WORLD_MIN - box.extents.y;
			bits |= 2;
		}
		px += box.axis[1].x * extent1;
		py += box.axis[1].y * extent1;
		pz += box.axis[1].z * extent1;
		float extent0;
		if (box.axis[0].y * y + box.axis[0].z * z + box.axis[0].x * x >= 0.0f)
		{
			extent0 = box.extents.x;
		}
		else
		{
			extent0 = math::WORLD_MIN - box.extents.x;
			bits |= 4;
		}
		*id = bits;
		point->x = box.axis[0].x * extent0 + px;
		point->y = box.axis[0].y * extent0 + py;
		point->z = box.axis[0].z * extent0 + pz;
	}
#endif

	// FUNCTION: ENGINE 0x10672A40
	void BoxPoint(GjkVolume* volume, int id, math::Vector* point)
	{
		volume->GetBox().GetCorner(*point, id);
	}

	// FUNCTION: ENGINE 0x10672A60
	void BoxDump(GjkVolume* volume)
	{
		const math::OBB& box = volume->GetBox();
		OLD_REPORT_AT(GJK_FILE, 195, "OBB: ", 0);
		box.centre.Print();
		box.axis[0].Print();
		box.axis[1].Print();
		box.axis[2].Print();
		box.extents.Print();
	}

	// FUNCTION: ENGINE 0x10672AD0
	void SphereSupport(GjkVolume* volume, const math::Vector* direction, int hint, int* id, math::Vector* point)
	{
		const math::Capsule& sphere = volume->GetCapsule();
		*id = 0;
		point->x = sphere.centre.x;
		point->y = sphere.centre.y;
		point->z = sphere.centre.z;
	}

	// FUNCTION: ENGINE 0x10672B00
	void SpherePoint(GjkVolume* volume, int id, math::Vector* point)
	{
		const math::Capsule& sphere = volume->GetCapsule();
		point->x = sphere.centre.x;
		point->y = sphere.centre.y;
		point->z = sphere.centre.z;
	}

	// FUNCTION: ENGINE 0x10672B20
	void SphereDump(GjkVolume* volume)
	{
		const math::Capsule& sphere = volume->GetCapsule();
		OLD_REPORT_AT(GJK_FILE, 223, "Sphere: ", 0);
		sphere.centre.Print();
	}

	// FUNCTION: ENGINE 0x106730C0
	void HullDump(GjkVolume* volume)
	{
		OLD_REPORT_AT(GJK_FILE, 328, "Hull: ", 0);
		volume->volume->DumpHull();
	}

	// FUNCTION: ENGINE 0x10673100
	GjkVolume::GjkVolume(CollisionVolume6* newVolume)
	{
		volume = newVolume;
		support = HullSupport;
		supportFrom = HullSupportFrom;
		pointFromId = HullPoint;
		dump = HullDump;
	}

	// FUNCTION: ENGINE 0x10673130
	GjkVolume::GjkVolume(const GjkShape* source, int type)
	{
		volume = 0;
		shape = *source;
		switch (type)
		{
		case 0:
			support = CapsuleSupport;
			supportFrom = CapsuleSupport;
			pointFromId = CapsulePoint;
			dump = CapsuleDump;
			break;
		case 1:
			support = BoxSupport;
			supportFrom = BoxSupport;
			pointFromId = BoxPoint;
			dump = BoxDump;
			break;
		case 2:
			support = SphereSupport;
			supportFrom = SphereSupport;
			pointFromId = SpherePoint;
			dump = SphereDump;
			break;
		default:
			support = 0;
			supportFrom = 0;
			pointFromId = 0;
			dump = 0;
			break;
		}
	}

	// FUNCTION: ENGINE 0x10673230
	void GjkSimplex::SetId(int index, const int* id)
	{
		ids[index] = *id;
	}

	// FUNCTION: ENGINE 0x10673250
	void GjkPoints::Set(int index, const math::Vector* point)
	{
		math::Vector* slot = points + index;
		slot->x = point->x;
		slot->y = point->y;
		slot->z = point->z;
	}

	// FUNCTION: ENGINE 0x10673280
	math::Vector* GjkPoints::At(int index)
	{
		return points + index;
	}

	// FUNCTION: ENGINE 0x10673290
	void GjkSimplex::Dump()
	{
		OLD_REPORT_AT(GJK_HEADER_FILE, 77, "Num points: %d. Indices: ", count, 0);
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			OLD_REPORT_AT(GJK_HEADER_FILE, 80, "  %d ", ids[i], 0);
		}
	}

	// FUNCTION: ENGINE 0x10673310
	void GjkState::Dump()
	{
		OLD_REPORT_AT(GJK_HEADER_FILE, 101, "Closest point0: ", 0);
		closestA.Print();
		OLD_REPORT_AT(GJK_HEADER_FILE, 104, "Closest point1: ", 0);
		closestB.Print();
		OLD_REPORT_AT(GJK_HEADER_FILE, 107, "Simplex 0: ", 0);
		simplexA.Dump();
		OLD_REPORT_AT(GJK_HEADER_FILE, 109, "Simplex points: ", 0);
		for (unsigned int i = 0; i < (unsigned int)simplexA.count; i++)
		{
			pointsA.points[i].Print();
		}
		OLD_REPORT_AT(GJK_HEADER_FILE, 115, "Simplex 1: ", 0);
		simplexB.Dump();
		OLD_REPORT_AT(GJK_HEADER_FILE, 117, "Simplex points: ", 0);
		for (unsigned int i = 0; i < (unsigned int)simplexB.count; i++)
		{
			pointsB.points[i].Print();
		}
	}

	// FUNCTION: ENGINE 0x10673490
	GjkState::GjkState(const GjkState& other)
		: pointsA(other.pointsA), pointsB(other.pointsB), closestA(other.closestA), closestB(other.closestB),
		  normal(other.normal), simplexA(other.simplexA), simplexB(other.simplexB), unknownAC(other.unknownAC)
	{
	}

	// FUNCTION: ENGINE 0x10673590
	GjkState& GjkState::operator=(const GjkState& other)
	{
		pointsA.points[0].x = other.pointsA.points[0].x;
		pointsA.points[0].y = other.pointsA.points[0].y;
		pointsA.points[0].z = other.pointsA.points[0].z;
		pointsA.points[1].x = other.pointsA.points[1].x;
		pointsA.points[1].y = other.pointsA.points[1].y;
		pointsA.points[1].z = other.pointsA.points[1].z;
		pointsA.points[2].x = other.pointsA.points[2].x;
		pointsA.points[2].y = other.pointsA.points[2].y;
		pointsA.points[2].z = other.pointsA.points[2].z;
		pointsA.points[3].x = other.pointsA.points[3].x;
		pointsA.points[3].y = other.pointsA.points[3].y;
		pointsA.points[3].z = other.pointsA.points[3].z;
		pointsB.points[0].x = other.pointsB.points[0].x;
		pointsB.points[0].y = other.pointsB.points[0].y;
		pointsB.points[0].z = other.pointsB.points[0].z;
		pointsB.points[1].x = other.pointsB.points[1].x;
		pointsB.points[1].y = other.pointsB.points[1].y;
		pointsB.points[1].z = other.pointsB.points[1].z;
		pointsB.points[2].x = other.pointsB.points[2].x;
		pointsB.points[2].y = other.pointsB.points[2].y;
		pointsB.points[2].z = other.pointsB.points[2].z;
		pointsB.points[3].x = other.pointsB.points[3].x;
		pointsB.points[3].y = other.pointsB.points[3].y;
		pointsB.points[3].z = other.pointsB.points[3].z;
		closestA.x = other.closestA.x;
		closestA.y = other.closestA.y;
		closestA.z = other.closestA.z;
		closestB.x = other.closestB.x;
		closestB.y = other.closestB.y;
		closestB.z = other.closestB.z;
		normal.x = other.normal.x;
		normal.y = other.normal.y;
		normal.z = other.normal.z;
		simplexA.ids[0] = other.simplexA.ids[0];
		simplexA.ids[1] = other.simplexA.ids[1];
		simplexA.ids[2] = other.simplexA.ids[2];
		simplexA.ids[3] = other.simplexA.ids[3];
		simplexA.count = other.simplexA.count;
		simplexB.ids[0] = other.simplexB.ids[0];
		simplexB.ids[1] = other.simplexB.ids[1];
		simplexB.ids[2] = other.simplexB.ids[2];
		simplexB.ids[3] = other.simplexB.ids[3];
		simplexB.count = other.simplexB.count;
		unknownAC = other.unknownAC;
		return *this;
	}

	// FUNCTION: ENGINE 0x106736F0
	int GjkSimplex::AddVertex(int id, math::Vector* points, math::Vector position)
	{
		for (int i = 0; i < count; i++)
		{
			if (ids[i] == id)
			{
				return 0;
			}
		}
		ids[count] = id;
		math::Vector* slot = points + count;
		slot->x = position.x;
		slot->y = position.y;
		slot->z = position.z;
		count++;
		return 1;
	}

	// FUNCTION: ENGINE 0x10677180
	// NONMATCHING: the structure follows the original, but the compiler merges the stores of the first support points
	// with the copies of the closest points and schedules the squared distance differently
#ifdef NONMATCHING
	float GjkDistance(GjkState* state, GjkVolume* volumeA, GjkVolume* volumeB, const math::Vector* start)
	{
		math::Vector direction;
		direction.x = start->x;
		direction.y = start->y;
		direction.z = start->z;
		int idA;
		math::Vector pointA;
		volumeA->support(volumeA, &direction, 0, &idA, &pointA);
		math::Vector negated;
		negated.x = math::WORLD_MIN - direction.x;
		negated.y = math::WORLD_MIN - direction.y;
		negated.z = math::WORLD_MIN - direction.z;
		int idB;
		math::Vector pointB;
		volumeB->support(volumeB, &negated, 0, &idB, &pointB);
		state->pointsA[0].x = pointA.x;
		state->pointsA[0].y = pointA.y;
		state->pointsA[0].z = pointA.z;
		state->pointsB[0].x = pointB.x;
		state->pointsB[0].y = pointB.y;
		state->pointsB[0].z = pointB.z;
		state->simplexB.count = 1;
		state->simplexA.count = 1;
		state->simplexA.ids[0] = idA;
		state->simplexB.ids[0] = idB;
		state->closestA.x = state->pointsA[0].x;
		state->closestA.y = state->pointsA[0].y;
		state->closestA.z = state->pointsA[0].z;
		state->closestB.x = state->pointsB[0].x;
		state->closestB.y = state->pointsB[0].y;
		state->closestB.z = state->pointsB[0].z;
		float dx = state->closestB.x - state->closestA.x;
		float dy = state->closestB.y - state->closestA.y;
		float dz = state->closestB.z - state->closestA.z;
		float distanceSquared = dz * dz + dy * dy + dx * dx;
		if (distanceSquared == 0.0f)
		{
			return 0.0f;
		}
		state->unknownAC = 1;
		direction.x = dx;
		direction.y = dy;
		direction.z = dz;
		GjkState first(*state);
		float previousDistance = distanceSquared;
		while (true)
		{
			int newIdA;
			math::Vector newPointA;
			volumeA->supportFrom(volumeA, &direction, state->simplexA.ids[0], &newIdA, &newPointA);
			negated.x = math::WORLD_MIN - direction.x;
			negated.y = math::WORLD_MIN - direction.y;
			negated.z = math::WORLD_MIN - direction.z;
			int newIdB;
			math::Vector newPointB;
			volumeB->supportFrom(volumeB, &negated, state->simplexB.ids[0], &newIdB, &newPointB);
			int addedA = state->simplexA.AddVertex(newIdA, state->pointsA, newPointA);
			int addedB = state->simplexB.AddVertex(newIdB, state->pointsB, newPointB);
			if ((addedB | addedA) == 0)
			{
				break;
			}
			GjkState previous(*state);
			math::Vector input = direction;
			float distance = state->Solve(&direction);
			if (distance == 0.0f)
			{
				return 0.0f;
			}
			if (1e12f <= fabs((double)direction.x) || 1e12f <= fabs((double)direction.y) || 1e12f <= fabs((double)direction.z))
			{
				static bool sInput = true;
				if (sInput && core::Report(0, 0, GJK_FILE, 471, 0, "", 0) == 3)
				{
					sInput = false;
				}
				static bool sNormalInput = true;
				if (sNormalInput && core::Report(0, 0, GJK_FILE, 472, 0, "", 0) == 3)
				{
					sNormalInput = false;
				}
				input.Print();
				static bool sNormalOutput = true;
				if (sNormalOutput && core::Report(0, 0, GJK_FILE, 475, 0, "", 0) == 3)
				{
					sNormalOutput = false;
				}
				direction.Print();
				static bool sSimplexPair = true;
				if (sSimplexPair && core::Report(0, 0, GJK_FILE, 478, 0, "", 0) == 3)
				{
					sSimplexPair = false;
				}
				previous.Dump();
				static bool sVolume0 = true;
				if (sVolume0 && core::Report(0, 0, GJK_FILE, 481, 0, "", 0) == 3)
				{
					sVolume0 = false;
				}
				volumeA->dump(volumeA);
				static bool sVolume1 = true;
				if (sVolume1 && core::Report(0, 0, GJK_FILE, 484, 0, "", 0) == 3)
				{
					sVolume1 = false;
				}
				volumeB->dump(volumeB);
				previous.Solve(&input);
				return 1e12f;
			}
			if (previousDistance <= distance)
			{
				distance = previousDistance;
				*state = previous;
				break;
			}
			previousDistance = distance;
			previous = *state;
		}
		float length = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
		if (length <= 1e-5f)
		{
			state->normal.x = 0.0f;
			state->normal.y = 0.0f;
			state->normal.z = 0.0f;
			return 0.0f;
		}
		float inverse = 1.0f / length;
		state->normal.x = inverse * direction.x;
		state->normal.y = direction.y * inverse;
		state->normal.z = direction.z * inverse;
		return sqrtf(previousDistance);
	}
#endif
}
