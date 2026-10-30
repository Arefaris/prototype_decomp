// The script method wrappers of proto::WebOfIntrigueManager: the unit that registers the manager's methods with the script context
// instantiates engine::Function's Method and Closure templates for their signatures.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/webofintrigue/webofintriguemanager.h"

template class Method0<proto::WebOfIntrigueManager, void>;
template class Method1<proto::WebOfIntrigueManager, void, int>;
template class Method0<proto::WebOfIntrigueManager, bool>;
template class Method0<proto::WebOfIntrigueManager, int>;
template class Method1<proto::WebOfIntrigueManager, float, int>;
template class Method1<proto::WebOfIntrigueManager, int, int>;
template class Method2<proto::WebOfIntrigueManager, int, float, float>;
template class Method1<proto::WebOfIntrigueManager, void, bool>;
template class Method2<proto::WebOfIntrigueManager, void, int, bool>;
template class Method1<proto::WebOfIntrigueManager, bool, engine::LuaGOH>;
template class Method2<proto::WebOfIntrigueManager, int, int, int>;
template class Method2<proto::WebOfIntrigueManager, bool, int, int>;
template class Method2<proto::WebOfIntrigueManager, void, int, int>;
template class Method4<proto::WebOfIntrigueManager, void, int, bool, math::Vector, math::Vector>;
template class Method1<proto::WebOfIntrigueManager, bool, int>;
template class Method2<proto::WebOfIntrigueManager, void, int, engine::LuaGOH>;
template class Method2<proto::WebOfIntrigueManager, void, int, const char*>;
template class Method2<proto::WebOfIntrigueManager, void, bool, bool>;
template class Method2<proto::WebOfIntrigueManager, void, float, bool>;
template class Method1<proto::WebOfIntrigueManager, void, float>;
template class Method1<proto::WebOfIntrigueManager, core::Name<core::CaseSensitiveKey>, int>;
template class Closure0<proto::WebOfIntrigueManager, void>;
template class Closure1<proto::WebOfIntrigueManager, void, int>;
template class Closure0<proto::WebOfIntrigueManager, bool>;
template class Closure0<proto::WebOfIntrigueManager, int>;
template class Closure1<proto::WebOfIntrigueManager, float, int>;
template class Closure1<proto::WebOfIntrigueManager, int, int>;
template class Closure2<proto::WebOfIntrigueManager, int, float, float>;
template class Closure1<proto::WebOfIntrigueManager, void, bool>;
template class Closure2<proto::WebOfIntrigueManager, void, int, bool>;
template class Closure1<proto::WebOfIntrigueManager, bool, engine::LuaGOH>;
template class Closure2<proto::WebOfIntrigueManager, int, int, int>;
template class Closure2<proto::WebOfIntrigueManager, bool, int, int>;
template class Closure2<proto::WebOfIntrigueManager, void, int, int>;
template class Closure4<proto::WebOfIntrigueManager, void, int, bool, math::Vector, math::Vector>;
template class Closure1<proto::WebOfIntrigueManager, bool, int>;
template class Closure2<proto::WebOfIntrigueManager, void, int, engine::LuaGOH>;
template class Closure2<proto::WebOfIntrigueManager, void, int, const char*>;
template class Closure2<proto::WebOfIntrigueManager, void, bool, bool>;
template class Closure2<proto::WebOfIntrigueManager, void, float, bool>;
template class Closure1<proto::WebOfIntrigueManager, void, float>;
template class Closure1<proto::WebOfIntrigueManager, core::Name<core::CaseSensitiveKey>, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, void>(const char*,
	proto::WebOfIntrigueManager*, void (proto::WebOfIntrigueManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, void, int>(const char*,
	proto::WebOfIntrigueManager*, void (proto::WebOfIntrigueManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, bool>(const char*,
	proto::WebOfIntrigueManager*, bool (proto::WebOfIntrigueManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, int>(const char*,
	proto::WebOfIntrigueManager*, int (proto::WebOfIntrigueManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, float, int>(const char*,
	proto::WebOfIntrigueManager*, float (proto::WebOfIntrigueManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, int, int>(const char*,
	proto::WebOfIntrigueManager*, int (proto::WebOfIntrigueManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, int, float, float>(const char*,
	proto::WebOfIntrigueManager*, int (proto::WebOfIntrigueManager::*)(float, float));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, void, bool>(const char*,
	proto::WebOfIntrigueManager*, void (proto::WebOfIntrigueManager::*)(bool));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, void, int, bool>(const char*,
	proto::WebOfIntrigueManager*, void (proto::WebOfIntrigueManager::*)(int, bool));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, bool, engine::LuaGOH>(const char*,
	proto::WebOfIntrigueManager*, bool (proto::WebOfIntrigueManager::*)(engine::LuaGOH));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, int, int, int>(const char*,
	proto::WebOfIntrigueManager*, int (proto::WebOfIntrigueManager::*)(int, int));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, bool, int, int>(const char*,
	proto::WebOfIntrigueManager*, bool (proto::WebOfIntrigueManager::*)(int, int));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, void, int, int>(const char*,
	proto::WebOfIntrigueManager*, void (proto::WebOfIntrigueManager::*)(int, int));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, void, int, bool, math::Vector, math::Vector>(const char*,
	proto::WebOfIntrigueManager*, void (proto::WebOfIntrigueManager::*)(int, bool, math::Vector, math::Vector));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, bool, int>(const char*,
	proto::WebOfIntrigueManager*, bool (proto::WebOfIntrigueManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, void, int, engine::LuaGOH>(const char*,
	proto::WebOfIntrigueManager*, void (proto::WebOfIntrigueManager::*)(int, engine::LuaGOH));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, void, int, const char*>(const char*,
	proto::WebOfIntrigueManager*, void (proto::WebOfIntrigueManager::*)(int, const char*));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, void, bool, bool>(const char*,
	proto::WebOfIntrigueManager*, void (proto::WebOfIntrigueManager::*)(bool, bool));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, void, float, bool>(const char*,
	proto::WebOfIntrigueManager*, void (proto::WebOfIntrigueManager::*)(float, bool));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, void, float>(const char*,
	proto::WebOfIntrigueManager*, void (proto::WebOfIntrigueManager::*)(float));
template void engine::LuaScriptManager::RegisterMethod<proto::WebOfIntrigueManager, core::Name<core::CaseSensitiveKey>, int>(const char*,
	proto::WebOfIntrigueManager*, core::Name<core::CaseSensitiveKey> (proto::WebOfIntrigueManager::*)(int));

// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x1055C790
// FUNCTION: ENGINE 0x1055C7E0
// FUNCTION: ENGINE 0x1055D020
// FUNCTION: ENGINE 0x1055D080
// FUNCTION: ENGINE 0x1055D0A0
// FUNCTION: ENGINE 0x1055D100
// FUNCTION: ENGINE 0x1055D120
// FUNCTION: ENGINE 0x1055D140
// FUNCTION: ENGINE 0x1055D190
// FUNCTION: ENGINE 0x1055D1B0
// FUNCTION: ENGINE 0x1055D1D0
// FUNCTION: ENGINE 0x1055D220
// FUNCTION: ENGINE 0x1055D240
// FUNCTION: ENGINE 0x1055D260
// FUNCTION: ENGINE 0x1055D2C0
// FUNCTION: ENGINE 0x1055D2F0
// FUNCTION: ENGINE 0x1055D330
// FUNCTION: ENGINE 0x1055D390
// FUNCTION: ENGINE 0x1055D3B0
// FUNCTION: ENGINE 0x1055D3E0
// FUNCTION: ENGINE 0x1055D450
// FUNCTION: ENGINE 0x1055D480
// FUNCTION: ENGINE 0x1055D4C0
// FUNCTION: ENGINE 0x1055D520
// FUNCTION: ENGINE 0x1055D540
// FUNCTION: ENGINE 0x1055D560
// FUNCTION: ENGINE 0x1055D5D0
// FUNCTION: ENGINE 0x1055D5F0
// FUNCTION: ENGINE 0x1055D610
// FUNCTION: ENGINE 0x1055D670
// FUNCTION: ENGINE 0x1055D690
// FUNCTION: ENGINE 0x1055D6C0
// FUNCTION: ENGINE 0x1055D730
// FUNCTION: ENGINE 0x1055D760
// FUNCTION: ENGINE 0x1055D790
// FUNCTION: ENGINE 0x1055D800
// FUNCTION: ENGINE 0x1055D830
// FUNCTION: ENGINE 0x1055D860
// FUNCTION: ENGINE 0x1055D8D0
// FUNCTION: ENGINE 0x1055D8F0
// FUNCTION: ENGINE 0x1055D910
// FUNCTION: ENGINE 0x1055D9A0
// FUNCTION: ENGINE 0x1055DA30
// FUNCTION: ENGINE 0x1055DAC0
// FUNCTION: ENGINE 0x1055DB20
// FUNCTION: ENGINE 0x1055DB40
// FUNCTION: ENGINE 0x1055DB70
// FUNCTION: ENGINE 0x1055DBE0
// FUNCTION: ENGINE 0x1055DC00
// FUNCTION: ENGINE 0x1055DC20
// FUNCTION: ENGINE 0x1055DC90
// FUNCTION: ENGINE 0x1055DCB0
// FUNCTION: ENGINE 0x1055DCD0
// FUNCTION: ENGINE 0x1055DD40
// FUNCTION: ENGINE 0x1055DD60
// FUNCTION: ENGINE 0x1055DD90
// FUNCTION: ENGINE 0x1055DE00
// FUNCTION: ENGINE 0x1055DE20
// FUNCTION: ENGINE 0x1055DE50
// FUNCTION: ENGINE 0x1055DEB0
// FUNCTION: ENGINE 0x1055DED0
// FUNCTION: ENGINE 0x1055DEF0
// FUNCTION: ENGINE 0x1055DF50
// FUNCTION: ENGINE 0x1055DFA0
// FUNCTION: ENGINE 0x1055F250
// FUNCTION: ENGINE 0x1055F2E0
// FUNCTION: ENGINE 0x1055F350
// FUNCTION: ENGINE 0x1055F370
// FUNCTION: ENGINE 0x1055F3D0
// FUNCTION: ENGINE 0x1055F3F0
// FUNCTION: ENGINE 0x1055F400
// FUNCTION: ENGINE 0x1055F460
// FUNCTION: ENGINE 0x1055F480
// FUNCTION: ENGINE 0x1055F4F0
// FUNCTION: ENGINE 0x1055F530
// FUNCTION: ENGINE 0x1055F5A0
// FUNCTION: ENGINE 0x1055F5D0
// FUNCTION: ENGINE 0x1055F600
// FUNCTION: ENGINE 0x1055F640
// FUNCTION: ENGINE 0x1055F6B0
// FUNCTION: ENGINE 0x1055F6D0
// FUNCTION: ENGINE 0x1055F700
// FUNCTION: ENGINE 0x1055F720
// FUNCTION: ENGINE 0x1055F790
// FUNCTION: ENGINE 0x1055F7C0
// FUNCTION: ENGINE 0x1055F7F0
// FUNCTION: ENGINE 0x1055F820
// FUNCTION: ENGINE 0x1055F850
// FUNCTION: ENGINE 0x1055F880
// FUNCTION: ENGINE 0x1055F8B0
// FUNCTION: ENGINE 0x1055F8D0
// FUNCTION: ENGINE 0x1055F900
// FUNCTION: ENGINE 0x1055F990
// FUNCTION: ENGINE 0x1055FA00
// FUNCTION: ENGINE 0x1055FA30
// FUNCTION: ENGINE 0x1055FA60
// FUNCTION: ENGINE 0x1055FA80
// FUNCTION: ENGINE 0x1055FAB0
// FUNCTION: ENGINE 0x1055FAD0
// FUNCTION: ENGINE 0x1055FB00
// FUNCTION: ENGINE 0x1055FB20
// FUNCTION: ENGINE 0x1055FB50
// FUNCTION: ENGINE 0x1055FB80
// FUNCTION: ENGINE 0x1055FBF0
// FUNCTION: ENGINE 0x1055FC10
// FUNCTION: ENGINE 0x1055FC80
// FUNCTION: ENGINE 0x10560B10
// FUNCTION: ENGINE 0x10560B70
// FUNCTION: ENGINE 0x10560C00
// FUNCTION: ENGINE 0x10560C90
// FUNCTION: ENGINE 0x10560CF0
// FUNCTION: ENGINE 0x10560D50
// FUNCTION: ENGINE 0x10560DC0
// FUNCTION: ENGINE 0x10560E20
// FUNCTION: ENGINE 0x10560E90
// FUNCTION: ENGINE 0x10560EF0
// FUNCTION: ENGINE 0x10560F60
// FUNCTION: ENGINE 0x10560FD0
// FUNCTION: ENGINE 0x10561040
// FUNCTION: ENGINE 0x105610B0
// FUNCTION: ENGINE 0x10561110
// FUNCTION: ENGINE 0x10561180
// FUNCTION: ENGINE 0x105611F0
// FUNCTION: ENGINE 0x10561260
// FUNCTION: ENGINE 0x105612D0
// FUNCTION: ENGINE 0x10561330
