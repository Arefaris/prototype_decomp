// The script method wrappers of proto::FREventManager: the unit that registers the manager's methods with the script context
// instantiates engine::Function's Method and Closure templates for their signatures.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/freeroamevents/freventmanager.h"

template class Method0<proto::FREventManager, void>;
template class Method2<proto::FREventManager, void, const char*, engine::LuaGOH>;
template class Method1<proto::FREventManager, void, bool>;
template class Method0<proto::FREventManager, bool>;
template class Method1<proto::FREventManager, void, const char*>;
template class Method2<proto::FREventManager, void, const char*, float>;
template class Method3<proto::FREventManager, void, const char*, bool, float>;
template class Method1<proto::FREventManager, math::Vector, const char*>;
template class Method2<proto::FREventManager, void, const char*, const char*>;
template class Method2<proto::FREventManager, float, const char*, int>;
template class Method1<proto::FREventManager, bool, int>;
template class Method1<proto::FREventManager, bool, const char*>;
template class Method2<proto::FREventManager, void, core::Name<core::CaseSensitiveKey>, bool>;
template class Method0<proto::FREventManager, int>;
template class Method2<proto::FREventManager, bool, core::Name<core::CaseSensitiveKey>, int>;
template class Method2<proto::FREventManager, void, core::Name<core::CaseSensitiveKey>, core::Name<core::CaseSensitiveKey> >;
template class Method0<proto::FREventManager, core::Name<core::CaseSensitiveKey> >;
template class Method2<proto::FREventManager, void, const char*, bool>;
template class Method2<proto::FREventManager, void, int, bool>;
template class Method1<proto::FREventManager, const char*, unsigned int>;
template class Method1<proto::FREventManager, int, int>;
template class Method2<proto::FREventManager, int, unsigned int, unsigned int>;
template class Method2<proto::FREventManager, bool, unsigned int, unsigned int>;
template class Method2<proto::FREventManager, void, int, int>;
template class Method2<proto::FREventManager, void, engine::LuaGOH, float>;
template class Method2<proto::FREventManager, float, const char*, const char*>;
template class Method2<proto::FREventManager, int, const char*, const char*>;
template class Method2<proto::FREventManager, const char*, const char*, const char*>;
template class Closure0<proto::FREventManager, void>;
template class Closure2<proto::FREventManager, void, const char*, engine::LuaGOH>;
template class Closure1<proto::FREventManager, void, bool>;
template class Closure0<proto::FREventManager, bool>;
template class Closure1<proto::FREventManager, void, const char*>;
template class Closure2<proto::FREventManager, void, const char*, float>;
template class Closure3<proto::FREventManager, void, const char*, bool, float>;
template class Closure1<proto::FREventManager, math::Vector, const char*>;
template class Closure2<proto::FREventManager, void, const char*, const char*>;
template class Closure2<proto::FREventManager, float, const char*, int>;
template class Closure1<proto::FREventManager, bool, int>;
template class Closure1<proto::FREventManager, bool, const char*>;
template class Closure2<proto::FREventManager, void, core::Name<core::CaseSensitiveKey>, bool>;
template class Closure0<proto::FREventManager, int>;
template class Closure2<proto::FREventManager, bool, core::Name<core::CaseSensitiveKey>, int>;
template class Closure2<proto::FREventManager, void, core::Name<core::CaseSensitiveKey>, core::Name<core::CaseSensitiveKey> >;
template class Closure0<proto::FREventManager, core::Name<core::CaseSensitiveKey> >;
template class Closure2<proto::FREventManager, void, const char*, bool>;
template class Closure2<proto::FREventManager, void, int, bool>;
template class Closure1<proto::FREventManager, const char*, unsigned int>;
template class Closure1<proto::FREventManager, int, int>;
template class Closure2<proto::FREventManager, int, unsigned int, unsigned int>;
template class Closure2<proto::FREventManager, bool, unsigned int, unsigned int>;
template class Closure2<proto::FREventManager, void, int, int>;
template class Closure2<proto::FREventManager, void, engine::LuaGOH, float>;
template class Closure2<proto::FREventManager, float, const char*, const char*>;
template class Closure2<proto::FREventManager, int, const char*, const char*>;
template class Closure2<proto::FREventManager, const char*, const char*, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, void>(const char*,
	proto::FREventManager*, void (proto::FREventManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, void, const char*, engine::LuaGOH>(const char*,
	proto::FREventManager*, void (proto::FREventManager::*)(const char*, engine::LuaGOH));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, void, bool>(const char*,
	proto::FREventManager*, void (proto::FREventManager::*)(bool));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, bool>(const char*,
	proto::FREventManager*, bool (proto::FREventManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, void, const char*>(const char*,
	proto::FREventManager*, void (proto::FREventManager::*)(const char*));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, void, const char*, float>(const char*,
	proto::FREventManager*, void (proto::FREventManager::*)(const char*, float));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, void, const char*, bool, float>(const char*,
	proto::FREventManager*, void (proto::FREventManager::*)(const char*, bool, float));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, math::Vector, const char*>(const char*,
	proto::FREventManager*, math::Vector (proto::FREventManager::*)(const char*));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, void, const char*, const char*>(const char*,
	proto::FREventManager*, void (proto::FREventManager::*)(const char*, const char*));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, float, const char*, int>(const char*,
	proto::FREventManager*, float (proto::FREventManager::*)(const char*, int));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, bool, int>(const char*,
	proto::FREventManager*, bool (proto::FREventManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, bool, const char*>(const char*,
	proto::FREventManager*, bool (proto::FREventManager::*)(const char*));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, void, core::Name<core::CaseSensitiveKey>, bool>(const char*,
	proto::FREventManager*, void (proto::FREventManager::*)(core::Name<core::CaseSensitiveKey>, bool));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, int>(const char*,
	proto::FREventManager*, int (proto::FREventManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, bool, core::Name<core::CaseSensitiveKey>, int>(const char*,
	proto::FREventManager*, bool (proto::FREventManager::*)(core::Name<core::CaseSensitiveKey>, int));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, void, core::Name<core::CaseSensitiveKey>, core::Name<core::CaseSensitiveKey> >(const char*,
	proto::FREventManager*, void (proto::FREventManager::*)(core::Name<core::CaseSensitiveKey>, core::Name<core::CaseSensitiveKey>));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, core::Name<core::CaseSensitiveKey> >(const char*,
	proto::FREventManager*, core::Name<core::CaseSensitiveKey> (proto::FREventManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, void, const char*, bool>(const char*,
	proto::FREventManager*, void (proto::FREventManager::*)(const char*, bool));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, void, int, bool>(const char*,
	proto::FREventManager*, void (proto::FREventManager::*)(int, bool));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, const char*, unsigned int>(const char*,
	proto::FREventManager*, const char* (proto::FREventManager::*)(unsigned int));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, int, int>(const char*,
	proto::FREventManager*, int (proto::FREventManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, int, unsigned int, unsigned int>(const char*,
	proto::FREventManager*, int (proto::FREventManager::*)(unsigned int, unsigned int));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, bool, unsigned int, unsigned int>(const char*,
	proto::FREventManager*, bool (proto::FREventManager::*)(unsigned int, unsigned int));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, void, int, int>(const char*,
	proto::FREventManager*, void (proto::FREventManager::*)(int, int));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, void, engine::LuaGOH, float>(const char*,
	proto::FREventManager*, void (proto::FREventManager::*)(engine::LuaGOH, float));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, float, const char*, const char*>(const char*,
	proto::FREventManager*, float (proto::FREventManager::*)(const char*, const char*));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, int, const char*, const char*>(const char*,
	proto::FREventManager*, int (proto::FREventManager::*)(const char*, const char*));
template void engine::LuaScriptManager::RegisterMethod<proto::FREventManager, const char*, const char*, const char*>(const char*,
	proto::FREventManager*, const char* (proto::FREventManager::*)(const char*, const char*));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x105882A0
// FUNCTION: ENGINE 0x105882F0
// FUNCTION: ENGINE 0x105889F0
// FUNCTION: ENGINE 0x10588A50
// FUNCTION: ENGINE 0x10588A70
// FUNCTION: ENGINE 0x10588AE0
// FUNCTION: ENGINE 0x10588B00
// FUNCTION: ENGINE 0x10588B20
// FUNCTION: ENGINE 0x10588B80
// FUNCTION: ENGINE 0x10588BA0
// FUNCTION: ENGINE 0x10588BC0
// FUNCTION: ENGINE 0x10588C10
// FUNCTION: ENGINE 0x10588C30
// FUNCTION: ENGINE 0x10588C50
// FUNCTION: ENGINE 0x10588CB0
// FUNCTION: ENGINE 0x10588CD0
// FUNCTION: ENGINE 0x10588CF0
// FUNCTION: ENGINE 0x10588D60
// FUNCTION: ENGINE 0x10588D80
// FUNCTION: ENGINE 0x10588DB0
// FUNCTION: ENGINE 0x10588E30
// FUNCTION: ENGINE 0x10588E60
// FUNCTION: ENGINE 0x10588E90
// FUNCTION: ENGINE 0x10588EF0
// FUNCTION: ENGINE 0x10588F40
// FUNCTION: ENGINE 0x10588FA0
// FUNCTION: ENGINE 0x10589010
// FUNCTION: ENGINE 0x10589030
// FUNCTION: ENGINE 0x10589050
// FUNCTION: ENGINE 0x105890C0
// FUNCTION: ENGINE 0x10589100
// FUNCTION: ENGINE 0x10589150
// FUNCTION: ENGINE 0x105891B0
// FUNCTION: ENGINE 0x105891D0
// FUNCTION: ENGINE 0x10589200
// FUNCTION: ENGINE 0x10589260
// FUNCTION: ENGINE 0x10589280
// FUNCTION: ENGINE 0x105892B0
// FUNCTION: ENGINE 0x10589320
// FUNCTION: ENGINE 0x10589370
// FUNCTION: ENGINE 0x105893C0
// FUNCTION: ENGINE 0x10589410
// FUNCTION: ENGINE 0x10589430
// FUNCTION: ENGINE 0x10589450
// FUNCTION: ENGINE 0x105894C0
// FUNCTION: ENGINE 0x10589510
// FUNCTION: ENGINE 0x10589570
// FUNCTION: ENGINE 0x105895E0
// FUNCTION: ENGINE 0x10589640
// FUNCTION: ENGINE 0x105896B0
// FUNCTION: ENGINE 0x10589700
// FUNCTION: ENGINE 0x10589740
// FUNCTION: ENGINE 0x10589780
// FUNCTION: ENGINE 0x105897F0
// FUNCTION: ENGINE 0x10589810
// FUNCTION: ENGINE 0x10589830
// FUNCTION: ENGINE 0x105898A0
// FUNCTION: ENGINE 0x105898C0
// FUNCTION: ENGINE 0x105898E0
// FUNCTION: ENGINE 0x10589940
// FUNCTION: ENGINE 0x10589960
// FUNCTION: ENGINE 0x10589990
// FUNCTION: ENGINE 0x105899F0
// FUNCTION: ENGINE 0x10589A10
// FUNCTION: ENGINE 0x10589A40
// FUNCTION: ENGINE 0x10589AB0
// FUNCTION: ENGINE 0x10589AE0
// FUNCTION: ENGINE 0x10589B10
// FUNCTION: ENGINE 0x10589B80
// FUNCTION: ENGINE 0x10589BB0
// FUNCTION: ENGINE 0x10589BE0
// FUNCTION: ENGINE 0x10589C50
// FUNCTION: ENGINE 0x10589C70
// FUNCTION: ENGINE 0x10589C90
// FUNCTION: ENGINE 0x10589D00
// FUNCTION: ENGINE 0x10589D20
// FUNCTION: ENGINE 0x10589D50
// FUNCTION: ENGINE 0x10589DC0
// FUNCTION: ENGINE 0x10589E00
// FUNCTION: ENGINE 0x10589E50
// FUNCTION: ENGINE 0x10589EC0
// FUNCTION: ENGINE 0x10589EF0
// FUNCTION: ENGINE 0x10589F20
// FUNCTION: ENGINE 0x10589F90
// FUNCTION: ENGINE 0x10589FC0
// FUNCTION: ENGINE 0x1058B3B0
// FUNCTION: ENGINE 0x1058B440
// FUNCTION: ENGINE 0x1058B470
// FUNCTION: ENGINE 0x1058B490
// FUNCTION: ENGINE 0x1058B500
// FUNCTION: ENGINE 0x1058B520
// FUNCTION: ENGINE 0x1058B580
// FUNCTION: ENGINE 0x1058B5A0
// FUNCTION: ENGINE 0x1058B610
// FUNCTION: ENGINE 0x1058B630
// FUNCTION: ENGINE 0x1058B660
// FUNCTION: ENGINE 0x1058B690
// FUNCTION: ENGINE 0x1058B6C0
// FUNCTION: ENGINE 0x1058B6F0
// FUNCTION: ENGINE 0x1058B760
// FUNCTION: ENGINE 0x1058B7C0
// FUNCTION: ENGINE 0x1058B7F0
// FUNCTION: ENGINE 0x1058B810
// FUNCTION: ENGINE 0x1058B840
// FUNCTION: ENGINE 0x1058B890
// FUNCTION: ENGINE 0x1058B900
// FUNCTION: ENGINE 0x1058B930
// FUNCTION: ENGINE 0x1058B940
// FUNCTION: ENGINE 0x1058B9B0
// FUNCTION: ENGINE 0x1058B9E0
// FUNCTION: ENGINE 0x1058BA10
// FUNCTION: ENGINE 0x1058BA70
// FUNCTION: ENGINE 0x1058BAD0
// FUNCTION: ENGINE 0x1058BAF0
// FUNCTION: ENGINE 0x1058BB20
// FUNCTION: ENGINE 0x1058BB80
// FUNCTION: ENGINE 0x1058BBB0
// FUNCTION: ENGINE 0x1058BC20
// FUNCTION: ENGINE 0x1058BC80
// FUNCTION: ENGINE 0x1058BCC0
// FUNCTION: ENGINE 0x1058BCF0
// FUNCTION: ENGINE 0x1058BD10
// FUNCTION: ENGINE 0x1058BD40
// FUNCTION: ENGINE 0x1058BD60
// FUNCTION: ENGINE 0x1058BDD0
// FUNCTION: ENGINE 0x1058BE00
// FUNCTION: ENGINE 0x1058BE70
// FUNCTION: ENGINE 0x1058BEA0
// FUNCTION: ENGINE 0x1058BED0
// FUNCTION: ENGINE 0x1058BF00
// FUNCTION: ENGINE 0x1058BF30
// FUNCTION: ENGINE 0x1058BF60
// FUNCTION: ENGINE 0x1058BF90
// FUNCTION: ENGINE 0x1058BFB0
// FUNCTION: ENGINE 0x1058BFE0
// FUNCTION: ENGINE 0x1058C010
// FUNCTION: ENGINE 0x1058C040
// FUNCTION: ENGINE 0x1058C090
// FUNCTION: ENGINE 0x1058C0C0
// FUNCTION: ENGINE 0x1058C0F0
// FUNCTION: ENGINE 0x1058C120
// FUNCTION: ENGINE 0x1058C380
// FUNCTION: ENGINE 0x1058C3F0
// FUNCTION: ENGINE 0x1058C450
// FUNCTION: ENGINE 0x1058C4E0
// FUNCTION: ENGINE 0x1058C540
// FUNCTION: ENGINE 0x1058C5B0
// FUNCTION: ENGINE 0x1058C620
// FUNCTION: ENGINE 0x1058C680
// FUNCTION: ENGINE 0x1058C6F0
// FUNCTION: ENGINE 0x1058C760
// FUNCTION: ENGINE 0x1058C7C0
// FUNCTION: ENGINE 0x1058C820
// FUNCTION: ENGINE 0x1058C890
// FUNCTION: ENGINE 0x1058C920
// FUNCTION: ENGINE 0x1058C990
// FUNCTION: ENGINE 0x1058CA00
// FUNCTION: ENGINE 0x1058CA90
// FUNCTION: ENGINE 0x1058CB00
// FUNCTION: ENGINE 0x1058CB70
// FUNCTION: ENGINE 0x1058CBD0
// FUNCTION: ENGINE 0x1058CC30
// FUNCTION: ENGINE 0x1058CCA0
// FUNCTION: ENGINE 0x1058CD10
// FUNCTION: ENGINE 0x1058CD80
// FUNCTION: ENGINE 0x1058CDF0
// FUNCTION: ENGINE 0x1058CE60
// FUNCTION: ENGINE 0x1058CED0
