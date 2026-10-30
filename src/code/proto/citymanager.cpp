// proto::CityManager: see the header. The file name, the layout and the names are guesses.
#include "code/proto/citymanager.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"

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
