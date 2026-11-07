// The script method wrappers of proto::SmartHintManager: the unit that registers the manager's methods with the script context
// instantiates engine::Function's Method and Closure templates for their signatures.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/smarthint/smarthintmanager.h"

template class Method0<proto::SmartHintManager, void>;
template class Method1<proto::SmartHintManager, void, bool>;
template class Method0<proto::SmartHintManager, bool>;
template class Method1<proto::SmartHintManager, void, float>;
template class Method1<proto::SmartHintManager, void, int>;
template class Method1<proto::SmartHintManager, bool, int>;
template class Method2<proto::SmartHintManager, void, int, bool>;
template class Method1<proto::SmartHintManager, float, int>;
template class Method2<proto::SmartHintManager, void, int, float>;
template class Closure0<proto::SmartHintManager, void>;
template class Closure1<proto::SmartHintManager, void, bool>;
template class Closure0<proto::SmartHintManager, bool>;
template class Closure1<proto::SmartHintManager, void, float>;
template class Closure1<proto::SmartHintManager, void, int>;
template class Closure1<proto::SmartHintManager, bool, int>;
template class Closure2<proto::SmartHintManager, void, int, bool>;
template class Closure1<proto::SmartHintManager, float, int>;
template class Closure2<proto::SmartHintManager, void, int, float>;
template void engine::LuaScriptManager::RegisterMethod<proto::SmartHintManager, void>(const char*,
	proto::SmartHintManager*, void (proto::SmartHintManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::SmartHintManager, void, bool>(const char*,
	proto::SmartHintManager*, void (proto::SmartHintManager::*)(bool));
template void engine::LuaScriptManager::RegisterMethod<proto::SmartHintManager, bool>(const char*,
	proto::SmartHintManager*, bool (proto::SmartHintManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::SmartHintManager, void, float>(const char*,
	proto::SmartHintManager*, void (proto::SmartHintManager::*)(float));
template void engine::LuaScriptManager::RegisterMethod<proto::SmartHintManager, void, int>(const char*,
	proto::SmartHintManager*, void (proto::SmartHintManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::SmartHintManager, bool, int>(const char*,
	proto::SmartHintManager*, bool (proto::SmartHintManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::SmartHintManager, void, int, bool>(const char*,
	proto::SmartHintManager*, void (proto::SmartHintManager::*)(int, bool));
template void engine::LuaScriptManager::RegisterMethod<proto::SmartHintManager, float, int>(const char*,
	proto::SmartHintManager*, float (proto::SmartHintManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::SmartHintManager, void, int, float>(const char*,
	proto::SmartHintManager*, void (proto::SmartHintManager::*)(int, float));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1059B470
// FUNCTION: ENGINE 0x1059B4C0
// FUNCTION: ENGINE 0x1059BDC0
// FUNCTION: ENGINE 0x1059BE20
// FUNCTION: ENGINE 0x1059BE40
// FUNCTION: ENGINE 0x1059BEA0
// FUNCTION: ENGINE 0x1059BEC0
// FUNCTION: ENGINE 0x1059BEE0
// FUNCTION: ENGINE 0x1059BF30
// FUNCTION: ENGINE 0x1059BF50
// FUNCTION: ENGINE 0x1059BF70
// FUNCTION: ENGINE 0x1059BFD0
// FUNCTION: ENGINE 0x1059BFF0
// FUNCTION: ENGINE 0x1059C010
// FUNCTION: ENGINE 0x1059C070
// FUNCTION: ENGINE 0x1059C090
// FUNCTION: ENGINE 0x1059C0B0
// FUNCTION: ENGINE 0x1059C110
// FUNCTION: ENGINE 0x1059C130
// FUNCTION: ENGINE 0x1059C160
// FUNCTION: ENGINE 0x1059C1D0
// FUNCTION: ENGINE 0x1059C1F0
// FUNCTION: ENGINE 0x1059C210
// FUNCTION: ENGINE 0x1059C270
// FUNCTION: ENGINE 0x1059C2A0
// FUNCTION: ENGINE 0x1059C2E0
// FUNCTION: ENGINE 0x1059C350
// FUNCTION: ENGINE 0x1059C370
// FUNCTION: ENGINE 0x1059CD60
// FUNCTION: ENGINE 0x1059CDF0
// FUNCTION: ENGINE 0x1059CE60
// FUNCTION: ENGINE 0x1059CE80
// FUNCTION: ENGINE 0x1059CEE0
// FUNCTION: ENGINE 0x1059CF00
// FUNCTION: ENGINE 0x1059CF10
// FUNCTION: ENGINE 0x1059CF80
// FUNCTION: ENGINE 0x1059CFA0
// FUNCTION: ENGINE 0x1059D010
// FUNCTION: ENGINE 0x1059D030
// FUNCTION: ENGINE 0x1059D0A0
// FUNCTION: ENGINE 0x1059D0D0
// FUNCTION: ENGINE 0x1059D100
// FUNCTION: ENGINE 0x1059D120
// FUNCTION: ENGINE 0x1059D190
// FUNCTION: ENGINE 0x1059D1D0
// FUNCTION: ENGINE 0x1059D200
// FUNCTION: ENGINE 0x1059D610
// FUNCTION: ENGINE 0x1059D670
// FUNCTION: ENGINE 0x1059D700
// FUNCTION: ENGINE 0x1059D760
// FUNCTION: ENGINE 0x1059D7C0
// FUNCTION: ENGINE 0x1059D820
// FUNCTION: ENGINE 0x1059D890
// FUNCTION: ENGINE 0x1059D8F0
