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

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104807A0
// FUNCTION: ENGINE 0x104807F0
// FUNCTION: ENGINE 0x104817B0
// FUNCTION: ENGINE 0x10481810
// FUNCTION: ENGINE 0x10481830
// FUNCTION: ENGINE 0x104818A0
// FUNCTION: ENGINE 0x104818C0
// FUNCTION: ENGINE 0x104818E0
// FUNCTION: ENGINE 0x10481940
// FUNCTION: ENGINE 0x10481960
// FUNCTION: ENGINE 0x10481990
// FUNCTION: ENGINE 0x10481A00
// FUNCTION: ENGINE 0x10481A20
// FUNCTION: ENGINE 0x10481A50
// FUNCTION: ENGINE 0x10481AA0
// FUNCTION: ENGINE 0x10481AC0
// FUNCTION: ENGINE 0x10481AE0
// FUNCTION: ENGINE 0x10481B40
// FUNCTION: ENGINE 0x10481B60
// FUNCTION: ENGINE 0x10481B90
// FUNCTION: ENGINE 0x10481BF0
// FUNCTION: ENGINE 0x10481C20
// FUNCTION: ENGINE 0x10483160
// FUNCTION: ENGINE 0x104831F0
// FUNCTION: ENGINE 0x10483200
// FUNCTION: ENGINE 0x10483230
// FUNCTION: ENGINE 0x10483250
// FUNCTION: ENGINE 0x104832C0
// FUNCTION: ENGINE 0x104832F0
// FUNCTION: ENGINE 0x10483320
// FUNCTION: ENGINE 0x10483340
// FUNCTION: ENGINE 0x104833A0
// FUNCTION: ENGINE 0x104833C0
// FUNCTION: ENGINE 0x10483430
// FUNCTION: ENGINE 0x10483460
// FUNCTION: ENGINE 0x104834D0
// FUNCTION: ENGINE 0x10484D70
// FUNCTION: ENGINE 0x10484DE0
// FUNCTION: ENGINE 0x10484E40
// FUNCTION: ENGINE 0x10484EB0
// FUNCTION: ENGINE 0x10484F40
// FUNCTION: ENGINE 0x10484FA0
