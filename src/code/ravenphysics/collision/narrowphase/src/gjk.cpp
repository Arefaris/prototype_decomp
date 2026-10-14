#include <math.h>

#include "code/core/report.h"
#include "code/math/worldbounds.h"
#include "code/ravenphysics/collision/narrowphase/gjk.h"

#define GJK_FILE "..\\..\\..\\code\\ravenphysics\\collision\\narrowphase\\src\\gjk.cpp"

namespace ravenphysics
{
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
