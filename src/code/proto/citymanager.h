// The city manager (RTTI proto::CityManager, vftable 0x10E24390, the one manager is 0x112730A0): the districts of the
// open world and the order the cells of the city are opened in. The script natives city_ClearCellProgression,
// city_AddCellProgressionDuring and city_AddCellProgressionAfter fill the two lists of cell names. The layout and the
// member names are guesses.
#ifndef PROTO_CITYMANAGER_H
#define PROTO_CITYMANAGER_H

#include "code/container/arrayfixed.h"
#include "code/container/arraydynamicnew.h"
#include "code/core/name.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/vector.h"

namespace proto
{
	class ZoneBehaviour;

	// RTTI: proto::CityManager
	class CityManager
	{
	public:
		// RTTI proto::CityManager::DecayState: the state of decay of a part of the city (the names of the values are the
		// reflected ones)
		enum DecayState
		{
			DECAY_STATE_DEFAULT = 0,
			DECAY_STATE_PRISTINE = 1,
			DECAY_STATE_MILITARY = 2,
			DECAY_STATE_INFECTED = 3,
			DECAY_STATE_BEFORE = 4,
			DECAY_STATE_DURING = 5,
			DECAY_STATE_AFTER = 6
		};

		// 0x105673F0
		CityManager();
		// 0x105674C0
		virtual ~CityManager();

		// 0x105673D0: empties both lists of cell names
		void ClearCellProgression();
		// 0x10566EB0 / 0x10566F10: appends a cell name to the list of the cells opened during or after the mission
		void AddCellProgressionDuring(const char* name);
		void AddCellProgressionAfter(const char* name);
		// 0x10565D70: fills the lists of the nearest zones (their object handles and distances' order) and answers how
		// many there are; with onlyRendering only the zones that render their effects count
		unsigned int FindNearestZones(const math::Vector* position, engine::GameObjectHandle* handles,
			unsigned int count, bool onlyRendering);
		// 0x10565F10: the same for the zones of one type, answering the zones themselves
		unsigned int FindNearestZonesOfType(const math::Vector* position, ZoneBehaviour** zones, unsigned int count,
			int zoneType, bool onlyRendering);
		// 0x105660A0: the distance to the edge of the nearest zone of a type (negative inside), whether there was one
		bool GetEdgeDistance(const math::Vector* position, int zoneType, float* distance, bool onlyRendering);
		// 0x10566240: raises the five effect values of a result by what a zone contributes at a weight
		void AddZoneEffects(ZoneBehaviour* zone, float* result, float weight, bool skipPrimary);
		// 0x105663D0: what the zones around a position do to the military and the outbreak effect values
		void GetZoneEffects(const math::Vector* position, float* militaryEffects, float* outbreakEffects,
			float* nearestEdge, float* nearestPosition, bool skipPrimary);
		// 0x10566650: how strong the military and the outbreak zones are at a position
		void GetZoneStrengths(const math::Vector* position, float* military, float* outbreak);
		// 0x105667D0: tells every zone to hide its effects
		void HideZoneEffects();
		// 0x10566800: whether a position is inside a zone of a type (or of the war type)
		bool IsInsideZone(const math::Vector* position, int zoneType);
		// 0x10567520: binds the script natives
		void RegisterScript();
		// 0x105675E0: empties the lists and takes the object back out of the script manager
		bool ReleaseScript();

		int unknown4;
		engine::HandleBase unknown8;
		int unknownC;
		core::Name<core::CaseSensitiveKey> districtName;  // +0x10
		engine::HandleBase unknown18;
		container::ArrayFixed<core::Name<core::CaseSensitiveKey>, 64> duringCells;  // +0x1C
		container::ArrayFixed<core::Name<core::CaseSensitiveKey>, 64> afterCells;  // +0x220
		float unknown424;
		float unknown428;
		container::ArrayDynamicNew<ZoneBehaviour*> objects;  // +0x42C
	};

	// 0x112730A0: the one city manager (null: none)
	extern CityManager* gCityManager;
}

#endif
