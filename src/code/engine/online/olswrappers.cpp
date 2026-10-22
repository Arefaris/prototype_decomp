// The script method wrappers of the online classes engine::OLSProfile, engine::OLSGame and engine::OLSProfileStorage:
// the units that register methods of these classes with the script context instantiate engine::Function's Method and
// Closure templates for them. The classes themselves are other files'; the classes with several bases have method
// pointers of two words, which the declarations below ask for.
#include "code/engine/function.h"

namespace engine
{
	// One base: method pointers of one word
	class OLSProfile
	{
	};
}

template class Method1<engine::OLSProfile, void, bool>;
template class Method0<engine::OLSProfile, int>;
template class Closure1<engine::OLSProfile, void, bool>;
template class Closure0<engine::OLSProfile, int>;
template void engine::LuaScriptManager::RegisterMethod<engine::OLSProfile, void, bool>(const char*,
	engine::OLSProfile*, void (engine::OLSProfile::*)(bool));
template void engine::LuaScriptManager::RegisterMethod<engine::OLSProfile, int>(const char*, engine::OLSProfile*,
	int (engine::OLSProfile::*)());

#pragma pointers_to_members(full_generality, multiple_inheritance)

namespace engine
{
	class OLSGame;
	class OLSProfileStorage;
}

template class Method0<engine::OLSGame, void>;
template class Method1<engine::OLSGame, void, bool>;
template class Closure0<engine::OLSGame, void>;
template class Closure1<engine::OLSGame, void, bool>;
template void engine::LuaScriptManager::RegisterMethod<engine::OLSGame, void>(const char*, engine::OLSGame*,
	void (engine::OLSGame::*)());
template void engine::LuaScriptManager::RegisterMethod<engine::OLSGame, void, bool>(const char*, engine::OLSGame*,
	void (engine::OLSGame::*)(bool));

template class Method1<engine::OLSProfileStorage, void, unsigned int>;
template class Closure1<engine::OLSProfileStorage, void, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<engine::OLSProfileStorage, void, unsigned int>(const char*,
	engine::OLSProfileStorage*, void (engine::OLSProfileStorage::*)(unsigned int));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10888120
// FUNCTION: ENGINE 0x10888160
// FUNCTION: ENGINE 0x10888390
// FUNCTION: ENGINE 0x108883E0
// FUNCTION: ENGINE 0x10888400
// FUNCTION: ENGINE 0x10888450
// FUNCTION: ENGINE 0x10888470
// FUNCTION: ENGINE 0x108886E0
// FUNCTION: ENGINE 0x10888760
// FUNCTION: ENGINE 0x108887C0
// FUNCTION: ENGINE 0x108887E0
// FUNCTION: ENGINE 0x10889B30
// FUNCTION: ENGINE 0x10889B80
// FUNCTION: ENGINE 0x10889BA0
// FUNCTION: ENGINE 0x10889BC0
// FUNCTION: ENGINE 0x10889C00
// FUNCTION: ENGINE 0x10889C20
// FUNCTION: ENGINE 0x10889E90
// FUNCTION: ENGINE 0x10889EE0
// FUNCTION: ENGINE 0x10889F00
// FUNCTION: ENGINE 0x10889F50
// FUNCTION: ENGINE 0x10889F90
// FUNCTION: ENGINE 0x10889FE0
// FUNCTION: ENGINE 0x1088B040
// FUNCTION: ENGINE 0x1088B090
// FUNCTION: ENGINE 0x1088B0B0
