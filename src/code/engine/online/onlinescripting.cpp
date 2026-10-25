// The script method wrappers of the online classes (engine::ConsoleManager): the
// units that register methods of these classes with the script context instantiate engine::Function's Method and
// Closure templates for them. The class itself is another unit's.
#include "code/engine/function.h"
#include "code/engine/online/onlinemanager.h"

template class Method0<engine::ConsoleManager, bool>;
template class Closure0<engine::ConsoleManager, bool>;
template void engine::LuaScriptManager::RegisterMethod<engine::ConsoleManager, bool>(const char*,
	engine::ConsoleManager*, bool (engine::ConsoleManager::*)());


// The wrappers and registrations this unit instantiates, in address order:
// FUNCTION: ENGINE 0x108C4880
// FUNCTION: ENGINE 0x108C48C0
// FUNCTION: ENGINE 0x108C48E0

// The wrappers and registrations this unit instantiates, in address order:
// FUNCTION: ENGINE 0x108C5340
// FUNCTION: ENGINE 0x108C5390
// The wrappers and registrations this unit instantiates, in address order:
// FUNCTION: ENGINE 0x108C5580
