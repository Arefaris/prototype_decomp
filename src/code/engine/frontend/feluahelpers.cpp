// The front end's script helpers (code/engine/frontend/feluahelpers.cpp by its assert path; unit 0x108E1BC0 -
// 0x108E20B0).
#include "code/engine/frontend/feluahelpers.h"
#include "code/core/heap.h"
#include "code/core/debug.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"

namespace engine
{
	#define FELUAHELPERS_FILE "..\\..\\..\\code\\engine\\frontend\\feluahelpers.cpp"

	// The helper the front end made (0x1131AA6C; name guessed)
	FELuaHelper* gFELuaHelper;

	// FUNCTION: ENGINE 0x108E1BD0
	FELuaHelper::~FELuaHelper()
	{
		GetScriptManager()->Unregister(this);
	}

	// FUNCTION: ENGINE 0x108E1C40
	void FELuaHelper::ReleaseAssert(bool ok, const char* message)
	{
		OLD_ASSERT_AT(FELUAHELPERS_FILE, 0xC6, ok, "ok", message);
	}

	// FUNCTION: ENGINE 0x108E1CA0
	const char* FELuaHelper::GetPlatformType()
	{
		return "RAD_WIN32";
	}

	// FUNCTION: ENGINE 0x108E1DF0
	void ReleaseSubsystemAA6C()
	{
		delete gFELuaHelper;
		gFELuaHelper = 0;
	}

	// FUNCTION: ENGINE 0x108E1FB0
	FELuaHelper::FELuaHelper()
	{
		LuaScriptManager* scripts = GetScriptManager();
		scripts->RegisterMethod("fe_GetPlatformType", this, &FELuaHelper::GetPlatformType);
		scripts->RegisterMethod("fe_ReleaseAssert", this, &FELuaHelper::ReleaseAssert);
	}

	// FUNCTION: ENGINE 0x108E20B0
	void Unknown108E20B0(int heap)
	{
		core::HeapScope scope(heap);
		gFELuaHelper = new FELuaHelper;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108E1BC0
// FUNCTION: ENGINE 0x108E1C10
// FUNCTION: ENGINE 0x108E1CB0
