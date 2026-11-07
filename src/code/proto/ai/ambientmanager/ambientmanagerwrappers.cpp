// The script method wrappers of proto::AmbientManager: the unit that registers the manager's methods with the script
// context instantiates engine::Function's Method and Closure templates for their signatures.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/luascriptmanager.h"
#include "code/math/vector.h"
#include "code/proto/ai/ambientmanager/ambientmanager.h"

using proto::AmbientManager;

template class Method0<AmbientManager, void>;
template class Method0<AmbientManager, bool>;
template class Method1<AmbientManager, void, unsigned int>;
template class Method1<AmbientManager, void, float>;
template class Method1<AmbientManager, void, const char*>;
template class Method1<AmbientManager, void, bool>;
template class Method1<AmbientManager, core::Name<core::CaseSensitiveKey>, engine::LuaGOH>;
template class Method1<AmbientManager, void, engine::LuaGOH>;
template class Method2<AmbientManager, int, int, float>;
template class Method2<AmbientManager, void, bool, bool>;
template class Method2<AmbientManager, void, engine::LuaGOH, float>;
template class Method3<AmbientManager, void, float, math::Vector, float>;
template class Method3<AmbientManager, void, engine::LuaGOH, float, bool>;
template class Closure0<AmbientManager, void>;
template class Closure0<AmbientManager, bool>;
template class Closure1<AmbientManager, void, unsigned int>;
template class Closure1<AmbientManager, void, float>;
template class Closure1<AmbientManager, void, const char*>;
template class Closure1<AmbientManager, void, bool>;
template class Closure1<AmbientManager, core::Name<core::CaseSensitiveKey>, engine::LuaGOH>;
template class Closure1<AmbientManager, void, engine::LuaGOH>;
template class Closure2<AmbientManager, int, int, float>;
template class Closure2<AmbientManager, void, bool, bool>;
template class Closure2<AmbientManager, void, engine::LuaGOH, float>;
template class Closure3<AmbientManager, void, float, math::Vector, float>;
template class Closure3<AmbientManager, void, engine::LuaGOH, float, bool>;
template void engine::LuaScriptManager::RegisterMethod<AmbientManager, void>(const char*, AmbientManager*, void (AmbientManager::*)());
template void engine::LuaScriptManager::RegisterMethod<AmbientManager, bool>(const char*, AmbientManager*, bool (AmbientManager::*)());
template void engine::LuaScriptManager::RegisterMethod<AmbientManager, void, unsigned int>(const char*, AmbientManager*, void (AmbientManager::*)(unsigned int));
template void engine::LuaScriptManager::RegisterMethod<AmbientManager, void, float>(const char*, AmbientManager*, void (AmbientManager::*)(float));
template void engine::LuaScriptManager::RegisterMethod<AmbientManager, void, const char*>(const char*, AmbientManager*, void (AmbientManager::*)(const char*));
template void engine::LuaScriptManager::RegisterMethod<AmbientManager, void, bool>(const char*, AmbientManager*, void (AmbientManager::*)(bool));
template void engine::LuaScriptManager::RegisterMethod<AmbientManager, core::Name<core::CaseSensitiveKey>, engine::LuaGOH>(const char*, AmbientManager*, core::Name<core::CaseSensitiveKey> (AmbientManager::*)(engine::LuaGOH));
template void engine::LuaScriptManager::RegisterMethod<AmbientManager, void, engine::LuaGOH>(const char*, AmbientManager*, void (AmbientManager::*)(engine::LuaGOH));
template void engine::LuaScriptManager::RegisterMethod<AmbientManager, int, int, float>(const char*, AmbientManager*, int (AmbientManager::*)(int, float));
template void engine::LuaScriptManager::RegisterMethod<AmbientManager, void, bool, bool>(const char*, AmbientManager*, void (AmbientManager::*)(bool, bool));
template void engine::LuaScriptManager::RegisterMethod<AmbientManager, void, engine::LuaGOH, float>(const char*, AmbientManager*, void (AmbientManager::*)(engine::LuaGOH, float));
template void engine::LuaScriptManager::RegisterMethod<AmbientManager, void, float, math::Vector, float>(const char*, AmbientManager*, void (AmbientManager::*)(float, math::Vector, float));
template void engine::LuaScriptManager::RegisterMethod<AmbientManager, void, engine::LuaGOH, float, bool>(const char*, AmbientManager*, void (AmbientManager::*)(engine::LuaGOH, float, bool));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1040C1A0
// FUNCTION: ENGINE 0x1040C1F0
// FUNCTION: ENGINE 0x10410DB0
// FUNCTION: ENGINE 0x10410E10
// FUNCTION: ENGINE 0x10410E30
// FUNCTION: ENGINE 0x10410E90
// FUNCTION: ENGINE 0x10410EB0
// FUNCTION: ENGINE 0x10410ED0
// FUNCTION: ENGINE 0x10410F30
// FUNCTION: ENGINE 0x10410F50
// FUNCTION: ENGINE 0x10410F70
// FUNCTION: ENGINE 0x10410FD0
// FUNCTION: ENGINE 0x10410FF0
// FUNCTION: ENGINE 0x10411010
// FUNCTION: ENGINE 0x10411080
// FUNCTION: ENGINE 0x104110B0
// FUNCTION: ENGINE 0x104110E0
// FUNCTION: ENGINE 0x10411150
// FUNCTION: ENGINE 0x10411170
// FUNCTION: ENGINE 0x104111A0
// FUNCTION: ENGINE 0x10411200
// FUNCTION: ENGINE 0x10411220
// FUNCTION: ENGINE 0x10411240
// FUNCTION: ENGINE 0x104112A0
// FUNCTION: ENGINE 0x104112F0
// FUNCTION: ENGINE 0x10411340
// FUNCTION: ENGINE 0x104113C0
// FUNCTION: ENGINE 0x10411410
// FUNCTION: ENGINE 0x10411470
// FUNCTION: ENGINE 0x104114E0
// FUNCTION: ENGINE 0x10411500
// FUNCTION: ENGINE 0x10411530
// FUNCTION: ENGINE 0x104115B0
// FUNCTION: ENGINE 0x104115E0
// FUNCTION: ENGINE 0x10411610
// FUNCTION: ENGINE 0x10411670
// FUNCTION: ENGINE 0x10411690
// FUNCTION: ENGINE 0x104116B0
// FUNCTION: ENGINE 0x10411700
// FUNCTION: ENGINE 0x10411720
// FUNCTION: ENGINE 0x10415AB0
// FUNCTION: ENGINE 0x10415B90
// FUNCTION: ENGINE 0x10415C00
// FUNCTION: ENGINE 0x10415C20
// FUNCTION: ENGINE 0x10415C90
// FUNCTION: ENGINE 0x10415CB0
// FUNCTION: ENGINE 0x10415D20
// FUNCTION: ENGINE 0x10415D40
// FUNCTION: ENGINE 0x10415D70
// FUNCTION: ENGINE 0x10415DA0
// FUNCTION: ENGINE 0x10415DD0
// FUNCTION: ENGINE 0x10415DF0
// FUNCTION: ENGINE 0x10415E60
// FUNCTION: ENGINE 0x10415E80
// FUNCTION: ENGINE 0x10415EF0
// FUNCTION: ENGINE 0x10415F40
// FUNCTION: ENGINE 0x10415F70
// FUNCTION: ENGINE 0x10415FD0
// FUNCTION: ENGINE 0x10416000
// FUNCTION: ENGINE 0x10416030
// FUNCTION: ENGINE 0x10416040
// FUNCTION: ENGINE 0x10416070
// FUNCTION: ENGINE 0x104160A0
// FUNCTION: ENGINE 0x10416110
// FUNCTION: ENGINE 0x10416130
// FUNCTION: ENGINE 0x10416190
// FUNCTION: ENGINE 0x1041A1F0
// FUNCTION: ENGINE 0x1041A250
// FUNCTION: ENGINE 0x1041A2B0
// FUNCTION: ENGINE 0x1041A310
// FUNCTION: ENGINE 0x1041A380
// FUNCTION: ENGINE 0x1041A3F0
// FUNCTION: ENGINE 0x1041A450
// FUNCTION: ENGINE 0x1041A4B0
// FUNCTION: ENGINE 0x1041A520
// FUNCTION: ENGINE 0x1041A590
// FUNCTION: ENGINE 0x1041A600
// FUNCTION: ENGINE 0x1041A660
