// The script functions of the scenario unit (0x10480000 - 0x104A0000; no assert path names it, the file name is a
// guess): the instances of engine::Function1 and Function3 for the signatures its natives use and the script manager's
// one-argument registrations for them. The natives themselves follow in the unit.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/luascriptmanager.h"
#include "code/math/vector.h"

template class Function3<bool, const char*, math::Vector, math::Vector>;
template class Function1<math::Vector, const char*>;
template class Function1<engine::LuaGOH, int>;
template class Function1<const char*, engine::LuaGOH>;

// The one-argument registration (each unit that registers one keeps a copy)
template<class R, class A> inline void engine::LuaScriptManager::Register(const char* name, R (*function)(A))
{
	AddFunction(name, new Function1<R, A>(name, function));
}

template void engine::LuaScriptManager::Register<engine::LuaGOH, int>(const char*, engine::LuaGOH (*)(int));
template void engine::LuaScriptManager::Register<const char*, engine::LuaGOH>(const char*, const char* (*)(engine::LuaGOH));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10489C70
// FUNCTION: ENGINE 0x10489CF0
// FUNCTION: ENGINE 0x10489D70
// FUNCTION: ENGINE 0x10489DF0
// FUNCTION: ENGINE 0x10489E50
// FUNCTION: ENGINE 0x10489EA0
// FUNCTION: ENGINE 0x10493C50
// FUNCTION: ENGINE 0x10493CB0
// FUNCTION: ENGINE 0x10493CE0
// FUNCTION: ENGINE 0x10493D10
// FUNCTION: ENGINE 0x10494C50
// FUNCTION: ENGINE 0x10494CE0
