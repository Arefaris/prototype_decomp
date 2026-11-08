// proto::CityManager: see the header. The file name, the layout and the names are guesses.
#include "code/proto/citymanager.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/math/matrix.h"
#include "code/math/worldbounds.h"
#include "code/proto/zonebehaviour.h"
#include <math.h>
#include <new>

namespace engine
{
	namespace driving
	{
		extern const float gOne;
		extern const float gHalf;
	}
}

namespace choreo
{
	extern const float gMinusOne;
}

namespace audio
{
	extern const float gZero;
}

namespace proto
{
	// FUNCTION: ENGINE 0x105661E0
	// The blend of two numbers by a weight, kept in [0, 1)
	float Blend(const float& first, const float& second, const float& weight)
	{
		float result = (first - second) * weight + second;
		float clamp = 0.0f;
		if (result < 0.0f || (clamp = engine::driving::gOne, !(engine::driving::gOne > result)))
		{
			result = clamp;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105659E0
	// The slot a new distance takes in a list of the nearest ones (-1 when the farthest one is nearer)
	unsigned int FindFarthestSlot(float* distances, unsigned int capacity, unsigned int filled, float distance)
	{
		if (filled >= capacity)
		{
			float farthest = distances[0];
			filled = 0;
			for (unsigned int i = 1; i < capacity; i++)
			{
				if (farthest < distances[i])
				{
					farthest = distances[i];
					filled = i;
				}
			}
			if (!(distance < farthest))
			{
				filled = 0xFFFFFFFF;
			}
		}
		return filled;
	}

	// FUNCTION: ENGINE 0x10565D70
	// NONMATCHING: the engine subtracts the positions in the order x, z, y and keeps them in the frame, ours loads z and y first (95 %)
#ifdef NONMATCHING
	unsigned int CityManager::FindNearestZones(const math::Vector* position, engine::GameObjectHandle* handles,
		unsigned int count, bool onlyRendering)
	{
		float* distances = new float[count];
		unsigned int found = 0;
		for (ZoneBehaviour** it = objects.begin; it != objects.end; it++)
		{
			ZoneBehaviour* zone = *it;
			if (zone->IsActive() && (!onlyRendering || zone->renderEffectsState))
			{
				engine::GameObject* owner = zone->owner;
				math::Vector zonePosition(*(math::Vector*)&owner->transform->value.m[3][0]);
				math::Vector delta;
				delta.x = zonePosition.x - position->x;
				delta.z = zonePosition.z - position->z;
				delta.y = zonePosition.y - position->y;
				float distance = (float)sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
				int slot = FindFarthestSlot(distances, count, found, distance);
				if (slot >= 0)
				{
					distances[slot] = distance;
					handles[slot] = engine::GetHandle(owner);
					if (found < count)
					{
						found++;
					}
				}
			}
		}
		delete[] distances;
		return found;
	}
#endif

	// FUNCTION: ENGINE 0x10565F10
	// NONMATCHING: the engine subtracts the positions in the order x, z, y and keeps them in the frame, ours loads z and y first (95 %)
#ifdef NONMATCHING
	unsigned int CityManager::FindNearestZonesOfType(const math::Vector* position, ZoneBehaviour** zones,
		unsigned int count, int zoneType, bool onlyRendering)
	{
		float* distances = new float[count];
		unsigned int found = 0;
		for (ZoneBehaviour** it = objects.begin; it != objects.end; it++)
		{
			ZoneBehaviour* zone = *it;
			if (zone->IsActive() && (!onlyRendering || zone->renderEffectsState) && zone->zoneType == zoneType)
			{
				math::Vector zonePosition;
				zone->owner->transform->value.GetTranslation(zonePosition);
				float dx = zonePosition.x - position->x;
				float dz = zonePosition.z - position->z;
				float dy = zonePosition.y - position->y;
				float distance = (float)sqrt(dx * dx + dz * dz + dy * dy);
				int slot = FindFarthestSlot(distances, count, found, distance);
				if (slot >= 0)
				{
					distances[slot] = distance;
					zones[slot] = zone;
					if (found < count)
					{
						found++;
					}
				}
			}
		}
		delete[] distances;
		return found;
	}
#endif

	// FUNCTION: ENGINE 0x105660A0
	// NONMATCHING: the radius is loaded into the x87 stack before the squares and the delta stays in the frame (39 %)
#ifdef NONMATCHING
	bool CityManager::GetEdgeDistance(const math::Vector* position, int zoneType, float* distance, bool onlyRendering)
	{
		ZoneBehaviour** it = objects.begin;
		ZoneBehaviour** end = objects.end;
		bool found = false;
		*distance = 999999995904.0f;
		for (; it != end; it++)
		{
			ZoneBehaviour* zone = *it;
			if (zone->IsActive() && (!onlyRendering || zone->renderEffectsState) && zone->zoneType == zoneType)
			{
				engine::GameObject* owner = zone->owner;
				math::Vector zonePosition;
				owner->transform->value.GetTranslation(zonePosition);
				math::Vector delta;
				delta.x = zonePosition.x - position->x;
				delta.y = zonePosition.y - position->y;
				delta.z = zonePosition.z - position->z;
				float edge = (float)(sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z) - zone->radius);
				if (edge < *distance)
				{
					*distance = edge;
					found = true;
				}
			}
		}
		return found;
	}
#endif

	// FUNCTION: ENGINE 0x10566240
	void CityManager::AddZoneEffects(ZoneBehaviour* zone, float* result, float weight, bool skipPrimary)
	{
		float* e = zone->effects.values;
		float value = Blend(e[6], e[7], weight);
		if (e[10] != 0.0f)
		{
			value -= e[10];
		}
		if (!(value > result[2]))
		{
			value = result[2];
		}
		result[2] = value;
		value = Blend(e[8], e[9], weight);
		float current3 = result[3];
		if (current3 < value)
		{
			current3 = value;
		}
		result[3] = current3;
		value = Blend(e[2], e[5], weight);
		if (e[11] != 0.0f)
		{
			value = e[11] + value;
		}
		if (!(value > result[4]))
		{
			value = result[4];
		}
		result[4] = value;
		if (!skipPrimary)
		{
			value = Blend(e[0], e[3], weight);
			float current0 = result[0];
			if (current0 < value)
			{
				current0 = value;
			}
			result[0] = current0;
			value = Blend(e[1], e[4], weight);
			float current1 = result[1];
			if (current1 < value)
			{
				current1 = value;
			}
			result[1] = current1;
		}
	}

	// FUNCTION: ENGINE 0x105663D0
	// NONMATCHING: the position is copied and subtracted in a different order of the loads and the frame slots (12 %)
#ifdef NONMATCHING
	void CityManager::GetZoneEffects(const math::Vector* position, float* militaryEffects, float* outbreakEffects,
		float* nearestEdge, float* nearestPosition, bool skipPrimary)
	{
		outbreakEffects[0] = choreo::gMinusOne;
		outbreakEffects[1] = choreo::gMinusOne;
		outbreakEffects[2] = choreo::gMinusOne;
		outbreakEffects[3] = 0.0f;
		outbreakEffects[4] = choreo::gMinusOne;
		militaryEffects[0] = choreo::gMinusOne;
		militaryEffects[1] = choreo::gMinusOne;
		militaryEffects[2] = choreo::gMinusOne;
		militaryEffects[3] = 0.0f;
		militaryEffects[4] = choreo::gMinusOne;
		for (ZoneBehaviour** it = objects.begin; it != objects.end; it++)
		{
			ZoneBehaviour* zone = *it;
			if (zone->IsActive())
			{
				math::Vector zonePosition;
				zone->owner->transform->value.GetTranslation(zonePosition);
				float radius = zone->radius;
				if (0.0f < radius)
				{
					math::Vector delta;
					delta.x = zonePosition.x - position->x;
					delta.y = zonePosition.y - position->y;
					delta.z = zonePosition.z - position->z;
					float strength = zone->targetStrength;
					float edge = (float)sqrt(delta.z * delta.z + delta.y * delta.y + delta.x * delta.x) - radius;
					if (0.0f <= edge)
					{
						if (edge < *nearestEdge && 0.0f < strength && zone->zoneType == 1)
						{
							*nearestEdge = edge;
						}
					}
					else if (0.0f < strength)
					{
						float weight = ((math::WORLD_MIN - edge) / radius) * strength;
						if (zone->zoneType == 1)
						{
							if (edge < *nearestEdge && zone->effects.values[10] < engine::driving::gOne)
							{
								*nearestEdge = edge;
								nearestPosition[0] = zonePosition.x;
								nearestPosition[1] = zonePosition.y;
								nearestPosition[2] = zonePosition.z;
							}
							AddZoneEffects(zone, outbreakEffects, weight, skipPrimary);
						}
						else if (zone->zoneType == 0)
						{
							AddZoneEffects(zone, militaryEffects, weight, skipPrimary);
						}
					}
				}
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x10566650
	// NONMATCHING: the order of the subtractions and the register of the radius differ (73 %)
#ifdef NONMATCHING
	void CityManager::GetZoneStrengths(const math::Vector* position, float* military, float* outbreak)
	{
		*military = 0.0f;
		*outbreak = 0.0f;
		for (ZoneBehaviour** it = objects.begin; it != objects.end; it++)
		{
			ZoneBehaviour* zone = *it;
			if (zone->IsActive())
			{
				math::Vector zonePosition;
				zone->owner->transform->value.GetTranslation(zonePosition);
				math::Vector delta;
				delta.x = zonePosition.x - position->x;
				delta.y = zonePosition.y - position->y;
				delta.z = zonePosition.z - position->z;
				float radius = zone->radius;
				float distance = (float)sqrt(delta.z * delta.z + delta.y * delta.y + delta.x * delta.x);
				if (distance < radius && audio::gZero < radius)
				{
					float strength = (float)((cos((1.0 - (radius - distance) / radius) * 3.1415927410125732) + 1.0) *
						zone->targetStrength * engine::driving::gHalf);
					if (zone->zoneType == 1)
					{
						if (*outbreak < strength)
						{
							*outbreak = strength;
						}
					}
					else if (zone->zoneType == 0)
					{
						if (*military < strength)
						{
							*military = strength;
						}
					}
				}
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x105667D0
	void CityManager::HideZoneEffects()
	{
		for (ZoneBehaviour** it = objects.begin; it != objects.end; it++)
		{
			(*it)->ResetEffects();
		}
	}

	// FUNCTION: ENGINE 0x10566800
	// NONMATCHING: the single precision sums are scheduled with the subtractions in another order (88 %)
#ifdef NONMATCHING
	bool CityManager::IsInsideZone(const math::Vector* position, int zoneType)
	{
		for (ZoneBehaviour** it = objects.begin; it != objects.end; it++)
		{
			ZoneBehaviour* zone = *it;
			if (zone->IsActive() && (zone->zoneType == zoneType || zone->zoneType == 2))
			{
				math::Matrix& transform = zone->owner->transform->value;
				float radiusSquared = zone->radius * zone->radius;
				float dy = transform.m[3][1] - position->y;
				float dz = transform.m[3][2] - position->z;
				float dx = transform.m[3][0] - position->x;
				if (dx * dx + dz * dz + dy * dy < radiusSquared && audio::gZero < radiusSquared)
				{
					return true;
				}
			}
		}
		return false;
	}
#endif
}

namespace proto
{

	// FUNCTION: ENGINE 0x105675E0
	// EQUIVALENT: the engine keeps this in esi across the call of ClearCellProgression (57.1 %), ours knows that the
	// callee leaves ecx alone and keeps it there; the calls and their order are the engine's
	bool CityManager::ReleaseScript()
	{
		ClearCellProgression();
		engine::GetScriptManager()->Unregister(this);
		return true;
	}

	// FUNCTION: ENGINE 0x105673D0
	void CityManager::ClearCellProgression()
	{
		duringCells.Reset();
		afterCells.Reset();
	}

	// FUNCTION: ENGINE 0x10566EB0
	void CityManager::AddCellProgressionDuring(const char* name)
	{
		core::Name<core::CaseSensitiveKey> cell(name, 1);
		duringCells.PushBack(cell);
	}

	// FUNCTION: ENGINE 0x10566F10
	void CityManager::AddCellProgressionAfter(const char* name)
	{
		core::Name<core::CaseSensitiveKey> cell(name, 1);
		afterCells.PushBack(cell);
	}
}

// Kept copies (template instances and wrappers of this unit):

namespace proto
{
	// FUNCTION: ENGINE 0x10567520
	void CityManager::RegisterScript()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->SetOwner(this);
		manager->RegisterMethod("city_ClearCellProgression", this, &CityManager::ClearCellProgression);
		manager->RegisterMethod("city_AddCellProgressionDuring", this, &CityManager::AddCellProgressionDuring);
		manager->RegisterMethod("city_AddCellProgressionAfter", this, &CityManager::AddCellProgressionAfter);
		manager->ClearOwner();
	}

	// FUNCTION: ENGINE 0x105673F0
	CityManager::CityManager() : districtName("protodistrict", 1), unknown424(0.01f), unknown428(0.01f), objects(100)
	{
		gCityManager = this;
	}

	// FUNCTION: ENGINE 0x105674C0
	CityManager::~CityManager()
	{
		gCityManager = 0;
	}
}
// FUNCTION: ENGINE 0x10566F80
// FUNCTION: ENGINE 0x10567600
// FUNCTION: ENGINE 0x10565B10
