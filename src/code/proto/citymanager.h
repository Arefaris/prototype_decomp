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

namespace proto
{
	// RTTI: proto::CityManager
	class CityManager
	{
	public:
		// 0x105673F0
		CityManager();
		// 0x105674C0
		virtual ~CityManager();

		// 0x105673D0: empties both lists of cell names
		void ClearCellProgression();
		// 0x10566EB0 / 0x10566F10: appends a cell name to the list of the cells opened during or after the mission
		void AddCellProgressionDuring(const char* name);
		void AddCellProgressionAfter(const char* name);
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
		container::ArrayDynamicNew<void*> objects;  // +0x42C
	};

	// 0x112730A0: the one city manager (null: none)
	extern CityManager* gCityManager;
}

#endif
