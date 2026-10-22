// The script method wrappers of engine::controller::DefaultControllerHandler: the unit that registers methods of this
// class with the script context instantiates engine::Function's Method and Closure templates for it. The class itself
// is another file's; it has several bases, so its method pointers are two words, which the declarations below ask
// for.
#include "code/engine/function.h"

#pragma pointers_to_members(full_generality, multiple_inheritance)

namespace engine
{
	namespace controller
	{
		class DefaultControllerHandler;
	}
}

template class Method0<engine::controller::DefaultControllerHandler, void>;
template class Method1<engine::controller::DefaultControllerHandler, void, unsigned int>;
template class Closure0<engine::controller::DefaultControllerHandler, void>;
template class Closure1<engine::controller::DefaultControllerHandler, void, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<engine::controller::DefaultControllerHandler, void>(
	const char*, engine::controller::DefaultControllerHandler*, void (engine::controller::DefaultControllerHandler::*)());
template void engine::LuaScriptManager::RegisterMethod<engine::controller::DefaultControllerHandler, void,
	unsigned int>(const char*, engine::controller::DefaultControllerHandler*,
	void (engine::controller::DefaultControllerHandler::*)(unsigned int));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10895FB0
// FUNCTION: ENGINE 0x10895FF0
// FUNCTION: ENGINE 0x108960E0
// FUNCTION: ENGINE 0x10896130
// FUNCTION: ENGINE 0x10896150
// FUNCTION: ENGINE 0x108961A0
// FUNCTION: ENGINE 0x108961C0
// FUNCTION: ENGINE 0x108961E0
// FUNCTION: ENGINE 0x10896260
// FUNCTION: ENGINE 0x108962C0
// FUNCTION: ENGINE 0x108962E0
