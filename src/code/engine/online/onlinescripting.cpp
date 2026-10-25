// The script method wrappers of the online classes (engine::ConsoleManager, engine::OLSStorage): the
// units that register methods of these classes with the script context instantiate engine::Function's Method and
// Closure templates for them. The classes themselves are other units'; the classes with several bases have method
// pointers of two words, which the declarations below ask for.
#include "code/engine/function.h"
#include "code/engine/online/onlinemanager.h"

template class Method0<engine::ConsoleManager, bool>;
template class Closure0<engine::ConsoleManager, bool>;
template void engine::LuaScriptManager::RegisterMethod<engine::ConsoleManager, bool>(const char*,
	engine::ConsoleManager*, bool (engine::ConsoleManager::*)());


#pragma pointers_to_members(full_generality, multiple_inheritance)

namespace engine
{
	class OLSStorage;
}

template class Method0<engine::OLSStorage, void>;
template class Method1<engine::OLSStorage, void, int>;
template class Method2<engine::OLSStorage, const char*, int, int>;
template class Method1<engine::OLSStorage, bool, int>;
template class Closure0<engine::OLSStorage, void>;
template class Closure1<engine::OLSStorage, void, int>;
template class Closure2<engine::OLSStorage, const char*, int, int>;
template class Closure1<engine::OLSStorage, bool, int>;
template void engine::LuaScriptManager::RegisterMethod<engine::OLSStorage, void>(const char*, engine::OLSStorage*,
	void (engine::OLSStorage::*)());
template void engine::LuaScriptManager::RegisterMethod<engine::OLSStorage, void, int>(const char*,
	engine::OLSStorage*, void (engine::OLSStorage::*)(int));
template void engine::LuaScriptManager::RegisterMethod<engine::OLSStorage, const char*, int, int>(const char*,
	engine::OLSStorage*, const char* (engine::OLSStorage::*)(int, int));
template void engine::LuaScriptManager::RegisterMethod<engine::OLSStorage, bool, int>(const char*,
	engine::OLSStorage*, bool (engine::OLSStorage::*)(int));

// The wrappers and registrations this unit instantiates, in address order:
// FUNCTION: ENGINE 0x108C4880
// FUNCTION: ENGINE 0x108C48C0
// FUNCTION: ENGINE 0x108C48E0

// The wrappers and registrations this unit instantiates, in address order:
// FUNCTION: ENGINE 0x108C5340
// FUNCTION: ENGINE 0x108C5390

// The wrappers and registrations this unit instantiates, in address order:
// FUNCTION: ENGINE 0x108C5580

// The wrappers and registrations this unit instantiates, in address order:
// FUNCTION: ENGINE 0x108C5EB0
// FUNCTION: ENGINE 0x108C5EF0
// FUNCTION: ENGINE 0x108C6120
// FUNCTION: ENGINE 0x108C6170
// FUNCTION: ENGINE 0x108C6190
// FUNCTION: ENGINE 0x108C61E0
// FUNCTION: ENGINE 0x108C6200
// FUNCTION: ENGINE 0x108C6220
// FUNCTION: ENGINE 0x108C6280
// FUNCTION: ENGINE 0x108C62B0
// FUNCTION: ENGINE 0x108C62E0
// FUNCTION: ENGINE 0x108C6330
// FUNCTION: ENGINE 0x108C6350
// FUNCTION: ENGINE 0x108C63A0
// FUNCTION: ENGINE 0x108C6420
// FUNCTION: ENGINE 0x108C6480
// FUNCTION: ENGINE 0x108C64A0
// FUNCTION: ENGINE 0x108C64E0
// FUNCTION: ENGINE 0x108C6510
// FUNCTION: ENGINE 0x108C6570
// FUNCTION: ENGINE 0x108C65A0
// FUNCTION: ENGINE 0x108C65F0
// FUNCTION: ENGINE 0x108C6650

// ---- annotations of the functions mapped in symbols.txt (generated) ----

