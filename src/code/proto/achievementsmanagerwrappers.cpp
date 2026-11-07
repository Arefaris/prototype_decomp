// The script method wrappers of proto::AchievementsManager: the unit that registers the manager's methods with the script context
// instantiates engine::Function's Method and Closure templates for their signatures.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/achievementsmanager.h"

template class Method0<proto::AchievementsManager, void>;
template class Method1<proto::AchievementsManager, void, const char*>;
template class Method1<proto::AchievementsManager, void, bool>;
template class Closure0<proto::AchievementsManager, void>;
template class Closure1<proto::AchievementsManager, void, const char*>;
template class Closure1<proto::AchievementsManager, void, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::AchievementsManager, void>(const char*,
	proto::AchievementsManager*, void (proto::AchievementsManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::AchievementsManager, void, const char*>(const char*,
	proto::AchievementsManager*, void (proto::AchievementsManager::*)(const char*));
template void engine::LuaScriptManager::RegisterMethod<proto::AchievementsManager, void, bool>(const char*,
	proto::AchievementsManager*, void (proto::AchievementsManager::*)(bool));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10593CC0
// FUNCTION: ENGINE 0x10593D10
// FUNCTION: ENGINE 0x10594180
// FUNCTION: ENGINE 0x105941E0
// FUNCTION: ENGINE 0x10594200
// FUNCTION: ENGINE 0x10594260
// FUNCTION: ENGINE 0x10594280
// FUNCTION: ENGINE 0x105942A0
// FUNCTION: ENGINE 0x10594300
// FUNCTION: ENGINE 0x10594320
// FUNCTION: ENGINE 0x105947D0
// FUNCTION: ENGINE 0x10594870
// FUNCTION: ENGINE 0x10594880
// FUNCTION: ENGINE 0x105948F0
// FUNCTION: ENGINE 0x10594910
// FUNCTION: ENGINE 0x10594980
// FUNCTION: ENGINE 0x10594DA0
// FUNCTION: ENGINE 0x10594E00
