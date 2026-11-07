// The script method wrappers of proto::CameraManager: the unit that registers the camera manager's methods (cm_*, sc_*) with the
// script context (0x1032D500 - 0x10331D80, no assert path; the file name is a guess) instantiates engine::Function's Method and Closure
// templates for their signatures.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/luascriptmanager.h"
#include "code/math/vector.h"
#include "code/proto/camera/cameramanager.h"

using proto::CameraManager;

template class Method0<CameraManager, bool>;
template class Method0<CameraManager, float>;
template class Method0<CameraManager, int>;
template class Method0<CameraManager, math::Vector>;
template class Method0<CameraManager, void>;
template class Method1<CameraManager, bool, int>;
template class Method1<CameraManager, bool, math::Vector>;
template class Method1<CameraManager, float, int>;
template class Method1<CameraManager, math::Vector, int>;
template class Method1<CameraManager, void, bool>;
template class Method1<CameraManager, void, float>;
template class Method1<CameraManager, void, int>;
template class Method1<CameraManager, void, unsigned int>;
template class Method2<CameraManager, bool, int, const char*>;
template class Method2<CameraManager, bool, int, float>;
template class Method2<CameraManager, bool, int, math::Vector>;
template class Method2<CameraManager, bool, math::Vector, float>;
template class Method2<CameraManager, int, math::Vector, math::Vector>;
template class Method2<CameraManager, void, float, float>;
template class Method2<CameraManager, void, int, bool>;
template class Method2<CameraManager, void, int, const char*>;
template class Method2<CameraManager, void, int, engine::LuaGOH>;
template class Method2<CameraManager, void, int, float>;
template class Method2<CameraManager, void, int, math::Vector>;
template class Method2<CameraManager, void, math::Vector, float>;
template class Method3<CameraManager, bool, math::Vector, CameraManager::ShakeArgument, CameraManager::ShakeArgument>;
template class Method4<CameraManager, bool, const char*, bool, bool, float>;
template class Method5<CameraManager, bool, int, float, float, float, float>;
template class Method5<CameraManager, void, float, float, float, math::Vector, math::Vector>;
template class Method6<CameraManager, bool, engine::LuaGOH, math::Vector, bool, float, float, float>;
template class Method6<CameraManager, bool, float, math::Vector, float, float, float, bool>;
template class Method6<CameraManager, bool, int, engine::LuaGOH, const char*, math::Vector, int, bool>;
template class Method6<CameraManager, bool, int, float, float, float, bool, bool>;
template class Closure0<CameraManager, bool>;
template class Closure0<CameraManager, float>;
template class Closure0<CameraManager, int>;
template class Closure0<CameraManager, math::Vector>;
template class Closure0<CameraManager, void>;
template class Closure1<CameraManager, bool, int>;
template class Closure1<CameraManager, bool, math::Vector>;
template class Closure1<CameraManager, float, int>;
template class Closure1<CameraManager, math::Vector, int>;
template class Closure1<CameraManager, void, bool>;
template class Closure1<CameraManager, void, float>;
template class Closure1<CameraManager, void, int>;
template class Closure1<CameraManager, void, unsigned int>;
template class Closure2<CameraManager, bool, int, const char*>;
template class Closure2<CameraManager, bool, int, float>;
template class Closure2<CameraManager, bool, int, math::Vector>;
template class Closure2<CameraManager, bool, math::Vector, float>;
template class Closure2<CameraManager, int, math::Vector, math::Vector>;
template class Closure2<CameraManager, void, float, float>;
template class Closure2<CameraManager, void, int, bool>;
template class Closure2<CameraManager, void, int, const char*>;
template class Closure2<CameraManager, void, int, engine::LuaGOH>;
template class Closure2<CameraManager, void, int, float>;
template class Closure2<CameraManager, void, int, math::Vector>;
template class Closure2<CameraManager, void, math::Vector, float>;
template class Closure3<CameraManager, bool, math::Vector, CameraManager::ShakeArgument, CameraManager::ShakeArgument>;
template class Closure4<CameraManager, bool, const char*, bool, bool, float>;
template class Closure5<CameraManager, bool, int, float, float, float, float>;
template class Closure5<CameraManager, void, float, float, float, math::Vector, math::Vector>;
template class Closure6<CameraManager, bool, engine::LuaGOH, math::Vector, bool, float, float, float>;
template class Closure6<CameraManager, bool, float, math::Vector, float, float, float, bool>;
template class Closure6<CameraManager, bool, int, engine::LuaGOH, const char*, math::Vector, int, bool>;
template class Closure6<CameraManager, bool, int, float, float, float, bool, bool>;

template void engine::LuaScriptManager::RegisterMethod<CameraManager, bool>(const char*, CameraManager*, bool (CameraManager::*)());
template void engine::LuaScriptManager::RegisterMethod<CameraManager, float>(const char*, CameraManager*, float (CameraManager::*)());
template void engine::LuaScriptManager::RegisterMethod<CameraManager, int>(const char*, CameraManager*, int (CameraManager::*)());
template void engine::LuaScriptManager::RegisterMethod<CameraManager, math::Vector>(const char*, CameraManager*, math::Vector (CameraManager::*)());
template void engine::LuaScriptManager::RegisterMethod<CameraManager, void>(const char*, CameraManager*, void (CameraManager::*)());
template void engine::LuaScriptManager::RegisterMethod<CameraManager, bool, int>(const char*, CameraManager*, bool (CameraManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, bool, math::Vector>(const char*, CameraManager*, bool (CameraManager::*)(math::Vector));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, float, int>(const char*, CameraManager*, float (CameraManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, math::Vector, int>(const char*, CameraManager*, math::Vector (CameraManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, void, bool>(const char*, CameraManager*, void (CameraManager::*)(bool));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, void, float>(const char*, CameraManager*, void (CameraManager::*)(float));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, void, int>(const char*, CameraManager*, void (CameraManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, void, unsigned int>(const char*, CameraManager*, void (CameraManager::*)(unsigned int));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, bool, int, const char*>(const char*, CameraManager*, bool (CameraManager::*)(int, const char*));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, bool, int, float>(const char*, CameraManager*, bool (CameraManager::*)(int, float));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, bool, int, math::Vector>(const char*, CameraManager*, bool (CameraManager::*)(int, math::Vector));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, bool, math::Vector, float>(const char*, CameraManager*, bool (CameraManager::*)(math::Vector, float));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, int, math::Vector, math::Vector>(const char*, CameraManager*, int (CameraManager::*)(math::Vector, math::Vector));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, void, float, float>(const char*, CameraManager*, void (CameraManager::*)(float, float));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, void, int, bool>(const char*, CameraManager*, void (CameraManager::*)(int, bool));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, void, int, const char*>(const char*, CameraManager*, void (CameraManager::*)(int, const char*));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, void, int, engine::LuaGOH>(const char*, CameraManager*, void (CameraManager::*)(int, engine::LuaGOH));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, void, int, float>(const char*, CameraManager*, void (CameraManager::*)(int, float));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, void, int, math::Vector>(const char*, CameraManager*, void (CameraManager::*)(int, math::Vector));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, void, math::Vector, float>(const char*, CameraManager*, void (CameraManager::*)(math::Vector, float));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, bool, math::Vector, CameraManager::ShakeArgument, CameraManager::ShakeArgument>(const char*, CameraManager*, bool (CameraManager::*)(math::Vector, CameraManager::ShakeArgument, CameraManager::ShakeArgument));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, bool, const char*, bool, bool, float>(const char*, CameraManager*, bool (CameraManager::*)(const char*, bool, bool, float));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, bool, int, float, float, float, float>(const char*, CameraManager*, bool (CameraManager::*)(int, float, float, float, float));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, void, float, float, float, math::Vector, math::Vector>(const char*, CameraManager*, void (CameraManager::*)(float, float, float, math::Vector, math::Vector));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, bool, engine::LuaGOH, math::Vector, bool, float, float, float>(const char*, CameraManager*, bool (CameraManager::*)(engine::LuaGOH, math::Vector, bool, float, float, float));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, bool, float, math::Vector, float, float, float, bool>(const char*, CameraManager*, bool (CameraManager::*)(float, math::Vector, float, float, float, bool));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, bool, int, engine::LuaGOH, const char*, math::Vector, int, bool>(const char*, CameraManager*, bool (CameraManager::*)(int, engine::LuaGOH, const char*, math::Vector, int, bool));
template void engine::LuaScriptManager::RegisterMethod<CameraManager, bool, int, float, float, float, bool, bool>(const char*, CameraManager*, bool (CameraManager::*)(int, float, float, float, bool, bool));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1032D530
// FUNCTION: ENGINE 0x1032D590
// FUNCTION: ENGINE 0x1032D5B0
// FUNCTION: ENGINE 0x1032D600
// FUNCTION: ENGINE 0x1032D620
// FUNCTION: ENGINE 0x1032D640
// FUNCTION: ENGINE 0x1032D6B0
// FUNCTION: ENGINE 0x1032D6D0
// FUNCTION: ENGINE 0x1032D700
// FUNCTION: ENGINE 0x1032D770
// FUNCTION: ENGINE 0x1032D790
// FUNCTION: ENGINE 0x1032D7B0
// FUNCTION: ENGINE 0x1032D820
// FUNCTION: ENGINE 0x1032D840
// FUNCTION: ENGINE 0x1032D860
// FUNCTION: ENGINE 0x1032D8C0
// FUNCTION: ENGINE 0x1032D910
// FUNCTION: ENGINE 0x1032D970
// FUNCTION: ENGINE 0x1032D9E0
// FUNCTION: ENGINE 0x1032DA30
// FUNCTION: ENGINE 0x1032DA80
// FUNCTION: ENGINE 0x1032DAE0
// FUNCTION: ENGINE 0x1032DB10
// FUNCTION: ENGINE 0x1032DB50
// FUNCTION: ENGINE 0x1032DBA0
// FUNCTION: ENGINE 0x1032DBD0
// FUNCTION: ENGINE 0x1032DC10
// FUNCTION: ENGINE 0x1032DC70
// FUNCTION: ENGINE 0x1032DC90
// FUNCTION: ENGINE 0x1032DCB0
// FUNCTION: ENGINE 0x1032DD20
// FUNCTION: ENGINE 0x1032DD70
// FUNCTION: ENGINE 0x1032DDC0
// FUNCTION: ENGINE 0x1032DE30
// FUNCTION: ENGINE 0x1032DE60
// FUNCTION: ENGINE 0x1032DE90
// FUNCTION: ENGINE 0x1032DEF0
// FUNCTION: ENGINE 0x1032DF10
// FUNCTION: ENGINE 0x1032DF30
// FUNCTION: ENGINE 0x1032DFA0
// FUNCTION: ENGINE 0x1032DFF0
// FUNCTION: ENGINE 0x1032E040
// FUNCTION: ENGINE 0x1032E100
// FUNCTION: ENGINE 0x1032E180
// FUNCTION: ENGINE 0x1032E210
// FUNCTION: ENGINE 0x1032E280
// FUNCTION: ENGINE 0x1032E2B0
// FUNCTION: ENGINE 0x1032E2E0
// FUNCTION: ENGINE 0x1032E3A0
// FUNCTION: ENGINE 0x1032E410
// FUNCTION: ENGINE 0x1032E440
// FUNCTION: ENGINE 0x1032E4B0
// FUNCTION: ENGINE 0x1032E4E0
// FUNCTION: ENGINE 0x1032E510
// FUNCTION: ENGINE 0x1032E5B0
// FUNCTION: ENGINE 0x1032E610
// FUNCTION: ENGINE 0x1032E670
// FUNCTION: ENGINE 0x1032E6E0
// FUNCTION: ENGINE 0x1032E700
// FUNCTION: ENGINE 0x1032E720
// FUNCTION: ENGINE 0x1032E780
// FUNCTION: ENGINE 0x1032E7A0
// FUNCTION: ENGINE 0x1032E7D0
// FUNCTION: ENGINE 0x1032E890
// FUNCTION: ENGINE 0x1032E930
// FUNCTION: ENGINE 0x1032E960
// FUNCTION: ENGINE 0x1032E9C0
// FUNCTION: ENGINE 0x1032E9E0
// FUNCTION: ENGINE 0x1032EA00
// FUNCTION: ENGINE 0x1032EA60
// FUNCTION: ENGINE 0x1032EA80
// FUNCTION: ENGINE 0x1032EAA0
// FUNCTION: ENGINE 0x1032EAF0
// FUNCTION: ENGINE 0x1032EB10
// FUNCTION: ENGINE 0x1032EB30
// FUNCTION: ENGINE 0x1032EBB0
// FUNCTION: ENGINE 0x1032EC10
// FUNCTION: ENGINE 0x1032EC70
// FUNCTION: ENGINE 0x1032ED10
// FUNCTION: ENGINE 0x1032EDE0
// FUNCTION: ENGINE 0x1032EE10
// FUNCTION: ENGINE 0x1032EEA0
// FUNCTION: ENGINE 0x1032EF00
// FUNCTION: ENGINE 0x1032EF60
// FUNCTION: ENGINE 0x1032F020
// FUNCTION: ENGINE 0x1032F0B0
// FUNCTION: ENGINE 0x1032F0E0
// FUNCTION: ENGINE 0x1032F130
// FUNCTION: ENGINE 0x1032F180
// FUNCTION: ENGINE 0x1032F1D0
// FUNCTION: ENGINE 0x1032F240
// FUNCTION: ENGINE 0x1032F290
// FUNCTION: ENGINE 0x1032F2F0
// FUNCTION: ENGINE 0x1032F350
// FUNCTION: ENGINE 0x1032F3A0
// FUNCTION: ENGINE 0x1032F3F0
// FUNCTION: ENGINE 0x1032F460
// FUNCTION: ENGINE 0x1032F4E0
// FUNCTION: ENGINE 0x1032FA80
// FUNCTION: ENGINE 0x1032FB60
// FUNCTION: ENGINE 0x1032FB70
// FUNCTION: ENGINE 0x1032FBD0
// FUNCTION: ENGINE 0x1032FBF0
// FUNCTION: ENGINE 0x1032FC20
// FUNCTION: ENGINE 0x1032FC50
// FUNCTION: ENGINE 0x1032FC80
// FUNCTION: ENGINE 0x1032FCA0
// FUNCTION: ENGINE 0x1032FCD0
// FUNCTION: ENGINE 0x1032FCF0
// FUNCTION: ENGINE 0x1032FD60
// FUNCTION: ENGINE 0x1032FDC0
// FUNCTION: ENGINE 0x1032FDF0
// FUNCTION: ENGINE 0x1032FE40
// FUNCTION: ENGINE 0x1032FEB0
// FUNCTION: ENGINE 0x1032FEF0
// FUNCTION: ENGINE 0x1032FF50
// FUNCTION: ENGINE 0x1032FF80
// FUNCTION: ENGINE 0x1032FFF0
// FUNCTION: ENGINE 0x10330010
// FUNCTION: ENGINE 0x10330040
// FUNCTION: ENGINE 0x10330090
// FUNCTION: ENGINE 0x103300C0
// FUNCTION: ENGINE 0x103300F0
// FUNCTION: ENGINE 0x10330160
// FUNCTION: ENGINE 0x10330180
// FUNCTION: ENGINE 0x103301B0
// FUNCTION: ENGINE 0x10330210
// FUNCTION: ENGINE 0x10330240
// FUNCTION: ENGINE 0x103302D0
// FUNCTION: ENGINE 0x10330300
// FUNCTION: ENGINE 0x10330330
// FUNCTION: ENGINE 0x10330360
// FUNCTION: ENGINE 0x10330390
// FUNCTION: ENGINE 0x103303C0
// FUNCTION: ENGINE 0x103303F0
// FUNCTION: ENGINE 0x10330420
// FUNCTION: ENGINE 0x10330480
// FUNCTION: ENGINE 0x103304B0
// FUNCTION: ENGINE 0x103304D0
// FUNCTION: ENGINE 0x10330540
// FUNCTION: ENGINE 0x10330570
// FUNCTION: ENGINE 0x103305A0
// FUNCTION: ENGINE 0x103305D0
// FUNCTION: ENGINE 0x10330640
// FUNCTION: ENGINE 0x10330660
// FUNCTION: ENGINE 0x103306D0
// FUNCTION: ENGINE 0x103306F0
// FUNCTION: ENGINE 0x10330750
// FUNCTION: ENGINE 0x10330770
// FUNCTION: ENGINE 0x103307A0
// FUNCTION: ENGINE 0x10330800
// FUNCTION: ENGINE 0x10330830
// FUNCTION: ENGINE 0x10330860
// FUNCTION: ENGINE 0x10330890
// FUNCTION: ENGINE 0x103308F0
// FUNCTION: ENGINE 0x10330920
// FUNCTION: ENGINE 0x10330950
// FUNCTION: ENGINE 0x103309B0
// FUNCTION: ENGINE 0x10330A00
// FUNCTION: ENGINE 0x10330A30
// FUNCTION: ENGINE 0x10330A90
// FUNCTION: ENGINE 0x10330B00
// FUNCTION: ENGINE 0x10330B50
// FUNCTION: ENGINE 0x10330B80
// FUNCTION: ENGINE 0x10330D30
// FUNCTION: ENGINE 0x10330DC0
// FUNCTION: ENGINE 0x10330E30
// FUNCTION: ENGINE 0x10330EA0
// FUNCTION: ENGINE 0x10330F10
// FUNCTION: ENGINE 0x10330F70
// FUNCTION: ENGINE 0x10330FE0
// FUNCTION: ENGINE 0x10331040
// FUNCTION: ENGINE 0x103310D0
// FUNCTION: ENGINE 0x10331130
// FUNCTION: ENGINE 0x103311A0
// FUNCTION: ENGINE 0x10331210
// FUNCTION: ENGINE 0x10331270
// FUNCTION: ENGINE 0x103312E0
// FUNCTION: ENGINE 0x10331350
// FUNCTION: ENGINE 0x103313C0
// FUNCTION: ENGINE 0x10331430
// FUNCTION: ENGINE 0x103314A0
// FUNCTION: ENGINE 0x10331510
// FUNCTION: ENGINE 0x10331580
// FUNCTION: ENGINE 0x103315E0
// FUNCTION: ENGINE 0x10331650
// FUNCTION: ENGINE 0x103316B0
// FUNCTION: ENGINE 0x10331710
// FUNCTION: ENGINE 0x103317A0
// FUNCTION: ENGINE 0x10331810
// FUNCTION: ENGINE 0x10331880
// FUNCTION: ENGINE 0x103318F0
// FUNCTION: ENGINE 0x10331960
// FUNCTION: ENGINE 0x103319F0
// FUNCTION: ENGINE 0x10331A60
// FUNCTION: ENGINE 0x10331AC0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1032C650
// FUNCTION: ENGINE 0x1032C6A0
