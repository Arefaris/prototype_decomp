// The script method wrappers of proto::SaveGameManager: the manager registers its natives (sgm_LoadGame,
// sgm_NewGameFromExistingSlot, sgm_IsStoryComplete, sgm_SaveCheckpoint, sgm_IsCheckpointAvailable,
// PlutoConvertGOHToIndex, ...) with the script context (0x10487380) through engine::Function's Method and Closure
// templates and LuaScriptManager::RegisterMethod, instantiated for the signatures of its members.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/luascriptmanager.h"
#include "code/proto/savegamemanager.h"

template class Method0<proto::SaveGameManager, void>;
template class Method2<proto::SaveGameManager, void, const char*, int>;
template class Method1<proto::SaveGameManager, bool, int>;
template class Method2<proto::SaveGameManager, void, bool, bool>;
template class Method0<proto::SaveGameManager, bool>;
template class Method1<proto::SaveGameManager, int, engine::LuaGOH>;
template class Method1<proto::SaveGameManager, engine::LuaGOH, int>;
template class Closure0<proto::SaveGameManager, void>;
template class Closure2<proto::SaveGameManager, void, const char*, int>;
template class Closure1<proto::SaveGameManager, bool, int>;
template class Closure2<proto::SaveGameManager, void, bool, bool>;
template class Closure0<proto::SaveGameManager, bool>;
template class Closure1<proto::SaveGameManager, int, engine::LuaGOH>;
template class Closure1<proto::SaveGameManager, engine::LuaGOH, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::SaveGameManager, void>(const char*,
	proto::SaveGameManager*, void (proto::SaveGameManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::SaveGameManager, bool>(const char*,
	proto::SaveGameManager*, bool (proto::SaveGameManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::SaveGameManager, int, engine::LuaGOH>(const char*,
	proto::SaveGameManager*, int (proto::SaveGameManager::*)(engine::LuaGOH));
template void engine::LuaScriptManager::RegisterMethod<proto::SaveGameManager, engine::LuaGOH, int>(const char*,
	proto::SaveGameManager*, engine::LuaGOH (proto::SaveGameManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::SaveGameManager, void, const char*, int>(const char*,
	proto::SaveGameManager*, void (proto::SaveGameManager::*)(const char*, int));
template void engine::LuaScriptManager::RegisterMethod<proto::SaveGameManager, bool, int>(const char*,
	proto::SaveGameManager*, bool (proto::SaveGameManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::SaveGameManager, void, bool, bool>(const char*,
	proto::SaveGameManager*, void (proto::SaveGameManager::*)(bool, bool));
