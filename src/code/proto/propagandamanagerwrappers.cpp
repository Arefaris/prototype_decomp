// The script method wrappers of proto::PropagandaManager: the unit that registers the manager's methods with the script context
// instantiates engine::Function's Method and Closure templates for their signatures.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/propagandamanager.h"

template class Method1<proto::PropagandaManager, void, int>;
template class Closure1<proto::PropagandaManager, void, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::PropagandaManager, void, int>(const char*,
	proto::PropagandaManager*, void (proto::PropagandaManager::*)(int));

// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x1056F0E0
// FUNCTION: ENGINE 0x1056F140
// FUNCTION: ENGINE 0x1056F160
// FUNCTION: ENGINE 0x1056F210
// FUNCTION: ENGINE 0x1056F280
// FUNCTION: ENGINE 0x1056F460
