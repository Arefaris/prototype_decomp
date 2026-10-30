// The script method wrappers of proto::CityManager: the unit that registers the manager's methods with the script context
// instantiates engine::Function's Method and Closure templates for their signatures.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/citymanager.h"

template class Method0<proto::CityManager, void>;
template class Method1<proto::CityManager, void, const char*>;
template class Closure0<proto::CityManager, void>;
template class Closure1<proto::CityManager, void, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::CityManager, void>(const char*,
	proto::CityManager*, void (proto::CityManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::CityManager, void, const char*>(const char*,
	proto::CityManager*, void (proto::CityManager::*)(const char*));

// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x10565BD0
// FUNCTION: ENGINE 0x10565C20
// FUNCTION: ENGINE 0x105669E0
// FUNCTION: ENGINE 0x10566A40
// FUNCTION: ENGINE 0x10566A60
// FUNCTION: ENGINE 0x10566AC0
// FUNCTION: ENGINE 0x10566AE0
// FUNCTION: ENGINE 0x10566FA0
// FUNCTION: ENGINE 0x10567030
// FUNCTION: ENGINE 0x10567040
// FUNCTION: ENGINE 0x105670B0
// FUNCTION: ENGINE 0x10567370
