// The script method wrappers of proto::StatsManager: the unit that registers the manager's methods with the script context
// instantiates engine::Function's Method and Closure templates for their signatures.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/statsmanager.h"

template class Method0<proto::StatsManager, void>;
template class Method2<proto::StatsManager, void, const char*, int>;
template class Method3<proto::StatsManager, void, const char*, int, int>;
template class Method0<proto::StatsManager, int>;
template class Method1<proto::StatsManager, const char*, int>;
template class Method1<proto::StatsManager, int, int>;
template class Method2<proto::StatsManager, int, int, int>;
template class Method1<proto::StatsManager, int, const char*>;
template class Method2<proto::StatsManager, const char*, int, int>;
template class Method1<proto::StatsManager, void, bool>;
template class Closure0<proto::StatsManager, void>;
template class Closure2<proto::StatsManager, void, const char*, int>;
template class Closure3<proto::StatsManager, void, const char*, int, int>;
template class Closure0<proto::StatsManager, int>;
template class Closure1<proto::StatsManager, const char*, int>;
template class Closure1<proto::StatsManager, int, int>;
template class Closure2<proto::StatsManager, int, int, int>;
template class Closure1<proto::StatsManager, int, const char*>;
template class Closure2<proto::StatsManager, const char*, int, int>;
template class Closure1<proto::StatsManager, void, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::StatsManager, void>(const char*,
	proto::StatsManager*, void (proto::StatsManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::StatsManager, void, const char*, int>(const char*,
	proto::StatsManager*, void (proto::StatsManager::*)(const char*, int));
template void engine::LuaScriptManager::RegisterMethod<proto::StatsManager, void, const char*, int, int>(const char*,
	proto::StatsManager*, void (proto::StatsManager::*)(const char*, int, int));
template void engine::LuaScriptManager::RegisterMethod<proto::StatsManager, int>(const char*,
	proto::StatsManager*, int (proto::StatsManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::StatsManager, const char*, int>(const char*,
	proto::StatsManager*, const char* (proto::StatsManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::StatsManager, int, int>(const char*,
	proto::StatsManager*, int (proto::StatsManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::StatsManager, int, int, int>(const char*,
	proto::StatsManager*, int (proto::StatsManager::*)(int, int));
template void engine::LuaScriptManager::RegisterMethod<proto::StatsManager, int, const char*>(const char*,
	proto::StatsManager*, int (proto::StatsManager::*)(const char*));
template void engine::LuaScriptManager::RegisterMethod<proto::StatsManager, const char*, int, int>(const char*,
	proto::StatsManager*, const char* (proto::StatsManager::*)(int, int));
template void engine::LuaScriptManager::RegisterMethod<proto::StatsManager, void, bool>(const char*,
	proto::StatsManager*, void (proto::StatsManager::*)(bool));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10596160
// FUNCTION: ENGINE 0x105961B0
// FUNCTION: ENGINE 0x10597040
// FUNCTION: ENGINE 0x105970A0
// FUNCTION: ENGINE 0x10597180
// FUNCTION: ENGINE 0x105971F0
// FUNCTION: ENGINE 0x10597210
// FUNCTION: ENGINE 0x10597240
// FUNCTION: ENGINE 0x105972D0
// FUNCTION: ENGINE 0x10597300
// FUNCTION: ENGINE 0x10597330
// FUNCTION: ENGINE 0x10597380
// FUNCTION: ENGINE 0x105973A0
// FUNCTION: ENGINE 0x105973D0
// FUNCTION: ENGINE 0x10597430
// FUNCTION: ENGINE 0x10597460
// FUNCTION: ENGINE 0x10597490
// FUNCTION: ENGINE 0x105974F0
// FUNCTION: ENGINE 0x10597520
// FUNCTION: ENGINE 0x10597550
// FUNCTION: ENGINE 0x105975C0
// FUNCTION: ENGINE 0x105975F0
// FUNCTION: ENGINE 0x10597630
// FUNCTION: ENGINE 0x10597690
// FUNCTION: ENGINE 0x105976C0
// FUNCTION: ENGINE 0x105976F0
// FUNCTION: ENGINE 0x10597760
// FUNCTION: ENGINE 0x10597790
// FUNCTION: ENGINE 0x105977D0
// FUNCTION: ENGINE 0x10597830
// FUNCTION: ENGINE 0x10597850
// FUNCTION: ENGINE 0x10597EB0
// FUNCTION: ENGINE 0x10597F70
// FUNCTION: ENGINE 0x10597F90
// FUNCTION: ENGINE 0x10597FD0
// FUNCTION: ENGINE 0x10598000
// FUNCTION: ENGINE 0x10598040
// FUNCTION: ENGINE 0x10598070
// FUNCTION: ENGINE 0x105980D0
// FUNCTION: ENGINE 0x105980F0
// FUNCTION: ENGINE 0x10598160
// FUNCTION: ENGINE 0x10598190
// FUNCTION: ENGINE 0x10598200
// FUNCTION: ENGINE 0x10598230
// FUNCTION: ENGINE 0x10598270
// FUNCTION: ENGINE 0x105982B0
// FUNCTION: ENGINE 0x10598320
// FUNCTION: ENGINE 0x10598350
// FUNCTION: ENGINE 0x10598390
// FUNCTION: ENGINE 0x105983D0
// FUNCTION: ENGINE 0x10598440
// FUNCTION: ENGINE 0x105988D0
// FUNCTION: ENGINE 0x10598940
// FUNCTION: ENGINE 0x105989B0
// FUNCTION: ENGINE 0x10598A50
// FUNCTION: ENGINE 0x10598AB0
// FUNCTION: ENGINE 0x10598B10
// FUNCTION: ENGINE 0x10598B80
// FUNCTION: ENGINE 0x10598BE0
// FUNCTION: ENGINE 0x10598C50
