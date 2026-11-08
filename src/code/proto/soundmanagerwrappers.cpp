// The script method wrappers of proto::SoundManager: the unit that registers the sound manager's natives with the script
// context instantiates engine::Function's Method and Closure templates for their signatures (0x1049BFB0 - 0x1049ED70).
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"
#include "code/proto/soundmanager.h"

template class Method0<proto::SoundManager, void>;
template class Method1<proto::SoundManager, void, const char*>;
template class Method1<proto::SoundManager, void, bool>;
template class Closure0<proto::SoundManager, void>;
template class Closure1<proto::SoundManager, void, const char*>;
template class Closure1<proto::SoundManager, void, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::SoundManager, void>(const char*,
	proto::SoundManager*, void (proto::SoundManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::SoundManager, void, const char*>(const char*,
	proto::SoundManager*, void (proto::SoundManager::*)(const char*));
template void engine::LuaScriptManager::RegisterMethod<proto::SoundManager, void, bool>(const char*,
	proto::SoundManager*, void (proto::SoundManager::*)(bool));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1049BFB0
// FUNCTION: ENGINE 0x1049C000
// FUNCTION: ENGINE 0x1049D110
// FUNCTION: ENGINE 0x1049D170
// FUNCTION: ENGINE 0x1049D1E0
// FUNCTION: ENGINE 0x1049D240
// FUNCTION: ENGINE 0x1049D260
// FUNCTION: ENGINE 0x1049D280
// FUNCTION: ENGINE 0x1049D2E0
// FUNCTION: ENGINE 0x1049D300
// FUNCTION: ENGINE 0x1049EAA0
// FUNCTION: ENGINE 0x1049EC60
// FUNCTION: ENGINE 0x1049ECD0
// FUNCTION: ENGINE 0x1049ECF0
// FUNCTION: ENGINE 0x1049ED00
// FUNCTION: ENGINE 0x1049ED70
