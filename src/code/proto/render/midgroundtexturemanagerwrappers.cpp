// The script method wrappers of proto::MidgroundTextureManager: the unit that registers the manager's methods with the script context
// instantiates engine::Function's Method and Closure templates for their signatures.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/render/midgroundtexturemanager.h"

template class Method1<proto::MidgroundTextureManager, void, int>;
template class Closure1<proto::MidgroundTextureManager, void, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::MidgroundTextureManager, void, int>(const char*,
	proto::MidgroundTextureManager*, void (proto::MidgroundTextureManager::*)(int));

// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x10567880
// FUNCTION: ENGINE 0x105678E0
// FUNCTION: ENGINE 0x10567900
// FUNCTION: ENGINE 0x105679B0
// FUNCTION: ENGINE 0x10567A20
// FUNCTION: ENGINE 0x10567BD0
