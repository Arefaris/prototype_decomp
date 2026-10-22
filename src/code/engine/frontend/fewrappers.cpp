// The script method wrappers of engine::PauseState and engine::FEInputHandler (the frontend's input handler): the
// units that register methods of these classes with the script context instantiate engine::Function's Method and
// Closure templates for them. The classes themselves are other files'; the input handler has several bases, so its
// method pointers are two words, which the declarations below ask for.
#include "code/engine/function.h"

namespace engine
{
	// One base: method pointers of one word
	class PauseState
	{
	};
}

template class Method1<engine::PauseState, void, const char*>;
template class Closure1<engine::PauseState, void, const char*>;
template void engine::LuaScriptManager::RegisterMethod<engine::PauseState, void, const char*>(const char*,
	engine::PauseState*, void (engine::PauseState::*)(const char*));

#pragma pointers_to_members(full_generality, multiple_inheritance)

namespace engine
{
	class FEInputHandler;
}

template class Method1<engine::FEInputHandler, void, bool>;
template class Method1<engine::FEInputHandler, float, float>;
template class Method0<engine::FEInputHandler, bool>;
template class Method1<engine::FEInputHandler, void, const char*>;
template class Closure1<engine::FEInputHandler, void, bool>;
template class Closure1<engine::FEInputHandler, float, float>;
template class Closure0<engine::FEInputHandler, bool>;
template class Closure1<engine::FEInputHandler, void, const char*>;
template void engine::LuaScriptManager::RegisterMethod<engine::FEInputHandler, void, bool>(const char*,
	engine::FEInputHandler*, void (engine::FEInputHandler::*)(bool));
template void engine::LuaScriptManager::RegisterMethod<engine::FEInputHandler, float, float>(const char*,
	engine::FEInputHandler*, float (engine::FEInputHandler::*)(float));
template void engine::LuaScriptManager::RegisterMethod<engine::FEInputHandler, bool>(const char*,
	engine::FEInputHandler*, bool (engine::FEInputHandler::*)());
template void engine::LuaScriptManager::RegisterMethod<engine::FEInputHandler, void, const char*>(const char*,
	engine::FEInputHandler*, void (engine::FEInputHandler::*)(const char*));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10881990
// FUNCTION: ENGINE 0x108819E0
// FUNCTION: ENGINE 0x10881A00
// FUNCTION: ENGINE 0x10881A20
// FUNCTION: ENGINE 0x10881A70
// FUNCTION: ENGINE 0x10881AA0
// FUNCTION: ENGINE 0x10881AE0
// FUNCTION: ENGINE 0x10881B20
// FUNCTION: ENGINE 0x10881B40
// FUNCTION: ENGINE 0x10881B60
// FUNCTION: ENGINE 0x10881BB0
// FUNCTION: ENGINE 0x10881BD0
// FUNCTION: ENGINE 0x10881C20
// FUNCTION: ENGINE 0x10881C80
// FUNCTION: ENGINE 0x10881CA0
// FUNCTION: ENGINE 0x10881D00
// FUNCTION: ENGINE 0x10881D40
// FUNCTION: ENGINE 0x10881D90
// FUNCTION: ENGINE 0x10881DB0
// FUNCTION: ENGINE 0x10881E10
// FUNCTION: ENGINE 0x10881E50
// FUNCTION: ENGINE 0x10881EA0
// FUNCTION: ENGINE 0x10881EF0
// FUNCTION: ENGINE 0x10881F70
// FUNCTION: ENGINE 0x108824E0
// FUNCTION: ENGINE 0x10882530
// FUNCTION: ENGINE 0x10882540
// FUNCTION: ENGINE 0x10882560
// FUNCTION: ENGINE 0x108825B0
// FUNCTION: ENGINE 0x108825D0
