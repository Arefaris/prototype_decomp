// The script method wrappers of proto::NISManager: the unit that registers the manager's methods with the script context
// instantiates engine::Function's Method and Closure templates for their signatures.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/nismanager.h"

template class Method0<proto::NISManager, void>;
template class Method1<proto::NISManager, bool, const char*>;
template class Method0<proto::NISManager, bool>;
template class Method0<proto::NISManager, core::Name<core::CaseSensitiveKey>>;
template class Method1<proto::NISManager, void, float>;
template class Method1<proto::NISManager, void, unsigned int>;
template class Method1<proto::NISManager, void, const char*>;
template class Method2<proto::NISManager, void, const char*, float>;
template class Closure0<proto::NISManager, void>;
template class Closure1<proto::NISManager, bool, const char*>;
template class Closure0<proto::NISManager, bool>;
template class Closure0<proto::NISManager, core::Name<core::CaseSensitiveKey>>;
template class Closure1<proto::NISManager, void, float>;
template class Closure1<proto::NISManager, void, unsigned int>;
template class Closure1<proto::NISManager, void, const char*>;
template class Closure2<proto::NISManager, void, const char*, float>;
template void engine::LuaScriptManager::RegisterMethod<proto::NISManager, void>(const char*,
	proto::NISManager*, void (proto::NISManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::NISManager, bool, const char*>(const char*,
	proto::NISManager*, bool (proto::NISManager::*)(const char*));
template void engine::LuaScriptManager::RegisterMethod<proto::NISManager, bool>(const char*,
	proto::NISManager*, bool (proto::NISManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::NISManager, core::Name<core::CaseSensitiveKey>>(const char*,
	proto::NISManager*, core::Name<core::CaseSensitiveKey> (proto::NISManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::NISManager, void, float>(const char*,
	proto::NISManager*, void (proto::NISManager::*)(float));
template void engine::LuaScriptManager::RegisterMethod<proto::NISManager, void, unsigned int>(const char*,
	proto::NISManager*, void (proto::NISManager::*)(unsigned int));
template void engine::LuaScriptManager::RegisterMethod<proto::NISManager, void, const char*>(const char*,
	proto::NISManager*, void (proto::NISManager::*)(const char*));
template void engine::LuaScriptManager::RegisterMethod<proto::NISManager, void, const char*, float>(const char*,
	proto::NISManager*, void (proto::NISManager::*)(const char*, float));

// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x10573570
// FUNCTION: ENGINE 0x105735C0
// FUNCTION: ENGINE 0x10573B50
// FUNCTION: ENGINE 0x10573BB0
// FUNCTION: ENGINE 0x10573BD0
// FUNCTION: ENGINE 0x10573C30
// FUNCTION: ENGINE 0x10573C50
// FUNCTION: ENGINE 0x10573C80
// FUNCTION: ENGINE 0x10573CD0
// FUNCTION: ENGINE 0x10573CF0
// FUNCTION: ENGINE 0x10573D10
// FUNCTION: ENGINE 0x10573D60
// FUNCTION: ENGINE 0x10573DA0
// FUNCTION: ENGINE 0x10573DE0
// FUNCTION: ENGINE 0x10573E40
// FUNCTION: ENGINE 0x10573E60
// FUNCTION: ENGINE 0x10573E80
// FUNCTION: ENGINE 0x10573EE0
// FUNCTION: ENGINE 0x10573F00
// FUNCTION: ENGINE 0x10573F20
// FUNCTION: ENGINE 0x10573F80
// FUNCTION: ENGINE 0x10573FA0
// FUNCTION: ENGINE 0x10573FC0
// FUNCTION: ENGINE 0x10574030
// FUNCTION: ENGINE 0x10574050
// FUNCTION: ENGINE 0x10574B70
// FUNCTION: ENGINE 0x10574C00
// FUNCTION: ENGINE 0x10574C70
// FUNCTION: ENGINE 0x10574CA0
// FUNCTION: ENGINE 0x10574D00
// FUNCTION: ENGINE 0x10574D20
// FUNCTION: ENGINE 0x10574D80
// FUNCTION: ENGINE 0x10574DC0
// FUNCTION: ENGINE 0x10574E30
// FUNCTION: ENGINE 0x10574E50
// FUNCTION: ENGINE 0x10574E60
// FUNCTION: ENGINE 0x10574ED0
// FUNCTION: ENGINE 0x10574EF0
// FUNCTION: ENGINE 0x10574F60
// FUNCTION: ENGINE 0x10574F80
// FUNCTION: ENGINE 0x10574FB0
// FUNCTION: ENGINE 0x105756B0
// FUNCTION: ENGINE 0x10575710
// FUNCTION: ENGINE 0x105757A0
// FUNCTION: ENGINE 0x10575830
// FUNCTION: ENGINE 0x10575890
// FUNCTION: ENGINE 0x105758F0
// FUNCTION: ENGINE 0x10575950
