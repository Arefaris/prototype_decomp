// The script method wrappers of proto::StreamManager: the unit that registers the manager's methods with the script context
// instantiates engine::Function's Method and Closure templates for their signatures.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/streammanager.h"

template class Method0<proto::StreamManager, void>;
template class Method1<proto::StreamManager, void, math::Vector>;
template class Method1<proto::StreamManager, void, int>;
template class Method7<proto::StreamManager, void, int, int, int, int, int, int, int>;
template class Method7<proto::StreamManager, void, math::Vector, math::Vector, math::Vector, math::Vector, math::Vector, math::Vector, math::Vector>;
template class Method0<proto::StreamManager, bool>;
template class Method1<proto::StreamManager, math::Vector, int>;
template class Closure0<proto::StreamManager, void>;
template class Closure1<proto::StreamManager, void, math::Vector>;
template class Closure1<proto::StreamManager, void, int>;
template class Closure7<proto::StreamManager, void, int, int, int, int, int, int, int>;
template class Closure7<proto::StreamManager, void, math::Vector, math::Vector, math::Vector, math::Vector, math::Vector, math::Vector, math::Vector>;
template class Closure0<proto::StreamManager, bool>;
template class Closure1<proto::StreamManager, math::Vector, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::StreamManager, void>(const char*,
	proto::StreamManager*, void (proto::StreamManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::StreamManager, void, math::Vector>(const char*,
	proto::StreamManager*, void (proto::StreamManager::*)(math::Vector));
template void engine::LuaScriptManager::RegisterMethod<proto::StreamManager, void, int>(const char*,
	proto::StreamManager*, void (proto::StreamManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::StreamManager, void, int, int, int, int, int, int, int>(const char*,
	proto::StreamManager*, void (proto::StreamManager::*)(int, int, int, int, int, int, int));
template void engine::LuaScriptManager::RegisterMethod<proto::StreamManager, void, math::Vector, math::Vector, math::Vector, math::Vector, math::Vector, math::Vector, math::Vector>(const char*,
	proto::StreamManager*, void (proto::StreamManager::*)(math::Vector, math::Vector, math::Vector, math::Vector, math::Vector, math::Vector, math::Vector));
template void engine::LuaScriptManager::RegisterMethod<proto::StreamManager, bool>(const char*,
	proto::StreamManager*, bool (proto::StreamManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::StreamManager, math::Vector, int>(const char*,
	proto::StreamManager*, math::Vector (proto::StreamManager::*)(int));

// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x1056F9D0
// FUNCTION: ENGINE 0x1056FA20
// FUNCTION: ENGINE 0x1056FD10
// FUNCTION: ENGINE 0x1056FD70
// FUNCTION: ENGINE 0x1056FD90
// FUNCTION: ENGINE 0x1056FDF0
// FUNCTION: ENGINE 0x1056FE30
// FUNCTION: ENGINE 0x1056FE70
// FUNCTION: ENGINE 0x1056FED0
// FUNCTION: ENGINE 0x1056FEF0
// FUNCTION: ENGINE 0x1056FF10
// FUNCTION: ENGINE 0x1056FFE0
// FUNCTION: ENGINE 0x10570030
// FUNCTION: ENGINE 0x10570090
// FUNCTION: ENGINE 0x10570160
// FUNCTION: ENGINE 0x10570380
// FUNCTION: ENGINE 0x105703B0
// FUNCTION: ENGINE 0x10570400
// FUNCTION: ENGINE 0x10570420
// FUNCTION: ENGINE 0x10570440
// FUNCTION: ENGINE 0x105704A0
// FUNCTION: ENGINE 0x105704F0
// FUNCTION: ENGINE 0x105707E0
// FUNCTION: ENGINE 0x10570870
// FUNCTION: ENGINE 0x105708E0
// FUNCTION: ENGINE 0x10570920
// FUNCTION: ENGINE 0x10570990
// FUNCTION: ENGINE 0x105709B0
// FUNCTION: ENGINE 0x105709C0
// FUNCTION: ENGINE 0x105709F0
// FUNCTION: ENGINE 0x10570A50
// FUNCTION: ENGINE 0x10570A80
// FUNCTION: ENGINE 0x10570AB0
// FUNCTION: ENGINE 0x10570B10
// FUNCTION: ENGINE 0x10570B30
// FUNCTION: ENGINE 0x10570BA0
// FUNCTION: ENGINE 0x10570C40
// FUNCTION: ENGINE 0x10570CA0
// FUNCTION: ENGINE 0x10570D00
// FUNCTION: ENGINE 0x10570D70
// FUNCTION: ENGINE 0x10570DE0
// FUNCTION: ENGINE 0x10570E70
