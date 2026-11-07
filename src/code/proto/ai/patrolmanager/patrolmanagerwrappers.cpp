// The script method wrappers of proto::PatrolManager: the ai_patrol_* functions the manager registers with the script
// context are the Method and Closure templates of engine::Function, instantiated for the signatures of its members.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/luascriptmanager.h"
#include "code/proto/ai/patrolmanager/patrolmanager.h"

template class Method0<proto::PatrolManager, void>;
template class Method1<proto::PatrolManager, void, bool>;
template class Method0<proto::PatrolManager, bool>;
template class Method1<proto::PatrolManager, void, int>;
template class Method1<proto::PatrolManager, void, engine::LuaGOH>;
template class Method0<proto::PatrolManager, int>;
template class Method1<proto::PatrolManager, void, float>;
template class Method2<proto::PatrolManager, int, int, float>;
template class Method3<proto::PatrolManager, void, int, const char*, float>;
template class Method2<proto::PatrolManager, void, float, float>;
template class Closure0<proto::PatrolManager, void>;
template class Closure1<proto::PatrolManager, void, bool>;
template class Closure0<proto::PatrolManager, bool>;
template class Closure1<proto::PatrolManager, void, int>;
template class Closure1<proto::PatrolManager, void, engine::LuaGOH>;
template class Closure0<proto::PatrolManager, int>;
template class Closure1<proto::PatrolManager, void, float>;
template class Closure2<proto::PatrolManager, int, int, float>;
template class Closure3<proto::PatrolManager, void, int, const char*, float>;
template class Closure2<proto::PatrolManager, void, float, float>;
template void engine::LuaScriptManager::RegisterMethod<proto::PatrolManager, void>(const char*,
	proto::PatrolManager*, void (proto::PatrolManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::PatrolManager, void, bool>(const char*,
	proto::PatrolManager*, void (proto::PatrolManager::*)(bool));
template void engine::LuaScriptManager::RegisterMethod<proto::PatrolManager, bool>(const char*,
	proto::PatrolManager*, bool (proto::PatrolManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::PatrolManager, void, int>(const char*,
	proto::PatrolManager*, void (proto::PatrolManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::PatrolManager, void, engine::LuaGOH>(const char*,
	proto::PatrolManager*, void (proto::PatrolManager::*)(engine::LuaGOH));
template void engine::LuaScriptManager::RegisterMethod<proto::PatrolManager, int>(const char*,
	proto::PatrolManager*, int (proto::PatrolManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::PatrolManager, void, float>(const char*,
	proto::PatrolManager*, void (proto::PatrolManager::*)(float));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10428F70
// FUNCTION: ENGINE 0x10428FC0
// FUNCTION: ENGINE 0x10429B40
// FUNCTION: ENGINE 0x10429BA0
// FUNCTION: ENGINE 0x10429BC0
// FUNCTION: ENGINE 0x10429C20
// FUNCTION: ENGINE 0x10429C40
// FUNCTION: ENGINE 0x10429C60
// FUNCTION: ENGINE 0x10429CB0
// FUNCTION: ENGINE 0x10429CD0
// FUNCTION: ENGINE 0x10429CF0
// FUNCTION: ENGINE 0x10429D50
// FUNCTION: ENGINE 0x10429D70
// FUNCTION: ENGINE 0x10429D90
// FUNCTION: ENGINE 0x10429DF0
// FUNCTION: ENGINE 0x10429E10
// FUNCTION: ENGINE 0x10429E30
// FUNCTION: ENGINE 0x10429E80
// FUNCTION: ENGINE 0x10429EA0
// FUNCTION: ENGINE 0x10429EC0
// FUNCTION: ENGINE 0x10429F20
// FUNCTION: ENGINE 0x10429F40
// FUNCTION: ENGINE 0x10429F60
// FUNCTION: ENGINE 0x10429FD0
// FUNCTION: ENGINE 0x1042A000
// FUNCTION: ENGINE 0x1042A030
// FUNCTION: ENGINE 0x1042A0B0
// FUNCTION: ENGINE 0x1042A0E0
// FUNCTION: ENGINE 0x1042A110
// FUNCTION: ENGINE 0x1042A180
// FUNCTION: ENGINE 0x1042A1B0
// FUNCTION: ENGINE 0x1042A610
// FUNCTION: ENGINE 0x1042A6F0
// FUNCTION: ENGINE 0x1042A760
// FUNCTION: ENGINE 0x1042A780
// FUNCTION: ENGINE 0x1042A790
// FUNCTION: ENGINE 0x1042A7F0
// FUNCTION: ENGINE 0x1042A810
// FUNCTION: ENGINE 0x1042A880
// FUNCTION: ENGINE 0x1042A8A0
// FUNCTION: ENGINE 0x1042A910
// FUNCTION: ENGINE 0x1042A930
// FUNCTION: ENGINE 0x1042A990
// FUNCTION: ENGINE 0x1042A9B0
// FUNCTION: ENGINE 0x1042AA20
// FUNCTION: ENGINE 0x1042AA40
// FUNCTION: ENGINE 0x1042AA70
// FUNCTION: ENGINE 0x1042AAA0
// FUNCTION: ENGINE 0x1042AAD0
// FUNCTION: ENGINE 0x1042AB00
// FUNCTION: ENGINE 0x1042AB30
// FUNCTION: ENGINE 0x1042AEA0
// FUNCTION: ENGINE 0x1042AF00
// FUNCTION: ENGINE 0x1042AF90
// FUNCTION: ENGINE 0x1042AFF0
// FUNCTION: ENGINE 0x1042B050
// FUNCTION: ENGINE 0x1042B0E0
