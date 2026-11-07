// The script function objects of the faction relation natives (unit 0x1047BA50 - 0x1047D2D0, no assert path; the file name is a
// guess): the instances of engine::Function3 and of the registration for the signatures of the natives that set the
// relations between two factions by name or by game object. The natives themselves are left to the engine.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/luascriptmanager.h"

template class Function3<void, const char*, const char*, unsigned int>;
template class Function3<void, engine::LuaGOH, engine::LuaGOH, unsigned int>;
template class Function3<void, engine::LuaGOH, const char*, unsigned int>;
template void engine::LuaScriptManager::Register<void, const char*, const char*, unsigned int>(const char*, void (*)(const char*, const char*, unsigned int));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, engine::LuaGOH, unsigned int>(const char*, void (*)(engine::LuaGOH, engine::LuaGOH, unsigned int));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, const char*, unsigned int>(const char*, void (*)(engine::LuaGOH, const char*, unsigned int));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1047CC70
// FUNCTION: ENGINE 0x1047CC90
// FUNCTION: ENGINE 0x1047CCC0
// FUNCTION: ENGINE 0x1047CD40
// FUNCTION: ENGINE 0x1047CD60
// FUNCTION: ENGINE 0x1047CD90
// FUNCTION: ENGINE 0x1047CE10
// FUNCTION: ENGINE 0x1047CE30
// FUNCTION: ENGINE 0x1047D090
// FUNCTION: ENGINE 0x1047D0F0
// FUNCTION: ENGINE 0x1047D150
// FUNCTION: ENGINE 0x1047CBF0
