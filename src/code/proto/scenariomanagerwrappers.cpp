// The script method wrappers of proto::scenario::ScenarioManager: the unit that registers the manager's methods with the
// script context (0x10489C70 - 0x1048B3B0; the class is in scenario/scenariomanager.h) instantiates engine::Function's
// Method and Closure templates for their signatures.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/luascriptmanager.h"
#include "code/math/vector.h"
#include "code/proto/scenario/scenariomanager.h"

template class Method2<proto::scenario::ScenarioManager, int, float, const char*>;
template class Method1<proto::scenario::ScenarioManager, void, int>;
template class Method0<proto::scenario::ScenarioManager, float>;
template class Method2<proto::scenario::ScenarioManager, void, unsigned int, unsigned int>;
template class Method2<proto::scenario::ScenarioManager, void, const char*, const char*>;
template class Method0<proto::scenario::ScenarioManager, bool>;
template class Closure2<proto::scenario::ScenarioManager, int, float, const char*>;
template class Closure1<proto::scenario::ScenarioManager, void, int>;
template class Closure0<proto::scenario::ScenarioManager, float>;
template class Closure2<proto::scenario::ScenarioManager, void, unsigned int, unsigned int>;
template class Closure2<proto::scenario::ScenarioManager, void, const char*, const char*>;
template class Closure0<proto::scenario::ScenarioManager, bool>;

template void engine::LuaScriptManager::RegisterMethod<proto::scenario::ScenarioManager, int, float, const char*>(
	const char*, proto::scenario::ScenarioManager*, int (proto::scenario::ScenarioManager::*)(float, const char*));
template void engine::LuaScriptManager::RegisterMethod<proto::scenario::ScenarioManager, void, int>(const char*,
	proto::scenario::ScenarioManager*, void (proto::scenario::ScenarioManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::scenario::ScenarioManager, float>(const char*,
	proto::scenario::ScenarioManager*, float (proto::scenario::ScenarioManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::scenario::ScenarioManager, void, unsigned int, unsigned int>(
	const char*, proto::scenario::ScenarioManager*,
	void (proto::scenario::ScenarioManager::*)(unsigned int, unsigned int));
template void engine::LuaScriptManager::RegisterMethod<proto::scenario::ScenarioManager, void, const char*, const char*>(
	const char*, proto::scenario::ScenarioManager*,
	void (proto::scenario::ScenarioManager::*)(const char*, const char*));
template void engine::LuaScriptManager::RegisterMethod<proto::scenario::ScenarioManager, bool>(const char*,
	proto::scenario::ScenarioManager*, bool (proto::scenario::ScenarioManager::*)());

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10489F00
// FUNCTION: ENGINE 0x10489F70
// FUNCTION: ENGINE 0x10489FA0
// FUNCTION: ENGINE 0x10489FD0
// FUNCTION: ENGINE 0x1048A030
// FUNCTION: ENGINE 0x1048A050
// FUNCTION: ENGINE 0x1048A070
// FUNCTION: ENGINE 0x1048A0C0
// FUNCTION: ENGINE 0x1048A0F0
// FUNCTION: ENGINE 0x1048A130
// FUNCTION: ENGINE 0x1048A1A0
// FUNCTION: ENGINE 0x1048A1C0
// FUNCTION: ENGINE 0x1048A1E0
// FUNCTION: ENGINE 0x1048A250
// FUNCTION: ENGINE 0x1048A270
// FUNCTION: ENGINE 0x1048A290
// FUNCTION: ENGINE 0x1048A2E0
// FUNCTION: ENGINE 0x1048A300
// FUNCTION: ENGINE 0x1048A690
// FUNCTION: ENGINE 0x1048A6C0
// FUNCTION: ENGINE 0x1048A6F0
// FUNCTION: ENGINE 0x1048A760
// FUNCTION: ENGINE 0x1048A780
// FUNCTION: ENGINE 0x1048A7E0
// FUNCTION: ENGINE 0x1048A810
// FUNCTION: ENGINE 0x1048A840
// FUNCTION: ENGINE 0x1048A860
// FUNCTION: ENGINE 0x1048A890
// FUNCTION: ENGINE 0x1048A8B0
// FUNCTION: ENGINE 0x1048A910
// FUNCTION: ENGINE 0x1048AF10
// FUNCTION: ENGINE 0x1048AF80
// FUNCTION: ENGINE 0x1048AFE0
// FUNCTION: ENGINE 0x1048B070
// FUNCTION: ENGINE 0x1048B0E0
// FUNCTION: ENGINE 0x1048B150
