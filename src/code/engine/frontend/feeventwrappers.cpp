// The script method wrappers of the front end classes engine::FEEventHandler and engine::FELuaHelper (the unit that
// registers their methods with the script context instantiates engine::Function's Method and Closure templates for
// them). The classes themselves are other files'; FEEventHandler has several bases, so its method pointers have two
// words, FELuaHelper has one base and one-word pointers.
#include "code/engine/frontend/feluahelpers.h"
#include "code/engine/function.h"

template class Method0<engine::FELuaHelper, const char*>;
template class Method2<engine::FELuaHelper, void, bool, const char*>;
template class Closure0<engine::FELuaHelper, const char*>;
template class Closure2<engine::FELuaHelper, void, bool, const char*>;
template void engine::LuaScriptManager::RegisterMethod<engine::FELuaHelper, const char*>(const char*,
	engine::FELuaHelper*, const char* (engine::FELuaHelper::*)());
template void engine::LuaScriptManager::RegisterMethod<engine::FELuaHelper, void, bool, const char*>(const char*,
	engine::FELuaHelper*, void (engine::FELuaHelper::*)(bool, const char*));

#pragma pointers_to_members(full_generality, multiple_inheritance)

namespace engine
{
	class FEEventHandler;
}

template class Method2<engine::FEEventHandler, void, const char*, const char*>;
template class Closure2<engine::FEEventHandler, void, const char*, const char*>;
template void engine::LuaScriptManager::RegisterMethod<engine::FEEventHandler, void, const char*, const char*>(const char*,
	engine::FEEventHandler*, void (engine::FEEventHandler::*)(const char*, const char*));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108E1460
// FUNCTION: ENGINE 0x108E14C0
// FUNCTION: ENGINE 0x108E14E0
// FUNCTION: ENGINE 0x108E1550
// FUNCTION: ENGINE 0x108E1580
// FUNCTION: ENGINE 0x108E1600
// FUNCTION: ENGINE 0x108E1CD0
// FUNCTION: ENGINE 0x108E1D10
// FUNCTION: ENGINE 0x108E1D30
// FUNCTION: ENGINE 0x108E1D50
// FUNCTION: ENGINE 0x108E1DB0
// FUNCTION: ENGINE 0x108E1DD0
// FUNCTION: ENGINE 0x108E1E20
// FUNCTION: ENGINE 0x108E1E70
// FUNCTION: ENGINE 0x108E1E90
// FUNCTION: ENGINE 0x108E1EC0
// FUNCTION: ENGINE 0x108E1EE0
// FUNCTION: ENGINE 0x108E1F50
