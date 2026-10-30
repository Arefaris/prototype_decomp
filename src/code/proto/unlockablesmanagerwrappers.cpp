// The script method wrappers of proto::UnlockablesManager: the unit that registers the manager's methods with the script context
// instantiates engine::Function's Method and Closure templates for their signatures.
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/unlockablesmanager.h"

template class Method2<proto::UnlockablesManager, bool, unsigned int, unsigned int>;
template class Method3<proto::UnlockablesManager, void, unsigned int, unsigned int, bool>;
template class Method2<proto::UnlockablesManager, void, unsigned int, bool>;
template class Method4<proto::UnlockablesManager, void, core::Name<core::CaseSensitiveKey>, bool, bool, bool>;
template class Method2<proto::UnlockablesManager, int, unsigned int, core::Name<core::CaseSensitiveKey>>;
template class Method1<proto::UnlockablesManager, void, int>;
template class Method0<proto::UnlockablesManager, int>;
template class Method1<proto::UnlockablesManager, void, unsigned int>;
template class Method2<proto::UnlockablesManager, bool, int, int>;
template class Method1<proto::UnlockablesManager, bool, int>;
template class Method2<proto::UnlockablesManager, int, int, int>;
template class Method2<proto::UnlockablesManager, const char*, int, int>;
template class Method1<proto::UnlockablesManager, int, int>;
template class Method3<proto::UnlockablesManager, void, int, int, bool>;
template class Closure2<proto::UnlockablesManager, bool, unsigned int, unsigned int>;
template class Closure3<proto::UnlockablesManager, void, unsigned int, unsigned int, bool>;
template class Closure2<proto::UnlockablesManager, void, unsigned int, bool>;
template class Closure4<proto::UnlockablesManager, void, core::Name<core::CaseSensitiveKey>, bool, bool, bool>;
template class Closure2<proto::UnlockablesManager, int, unsigned int, core::Name<core::CaseSensitiveKey>>;
template class Closure1<proto::UnlockablesManager, void, int>;
template class Closure0<proto::UnlockablesManager, int>;
template class Closure1<proto::UnlockablesManager, void, unsigned int>;
template class Closure2<proto::UnlockablesManager, bool, int, int>;
template class Closure1<proto::UnlockablesManager, bool, int>;
template class Closure2<proto::UnlockablesManager, int, int, int>;
template class Closure2<proto::UnlockablesManager, const char*, int, int>;
template class Closure1<proto::UnlockablesManager, int, int>;
template class Closure3<proto::UnlockablesManager, void, int, int, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::UnlockablesManager, bool, unsigned int, unsigned int>(const char*,
	proto::UnlockablesManager*, bool (proto::UnlockablesManager::*)(unsigned int, unsigned int));
template void engine::LuaScriptManager::RegisterMethod<proto::UnlockablesManager, void, unsigned int, unsigned int, bool>(const char*,
	proto::UnlockablesManager*, void (proto::UnlockablesManager::*)(unsigned int, unsigned int, bool));
template void engine::LuaScriptManager::RegisterMethod<proto::UnlockablesManager, void, unsigned int, bool>(const char*,
	proto::UnlockablesManager*, void (proto::UnlockablesManager::*)(unsigned int, bool));
template void engine::LuaScriptManager::RegisterMethod<proto::UnlockablesManager, void, core::Name<core::CaseSensitiveKey>, bool, bool, bool>(const char*,
	proto::UnlockablesManager*, void (proto::UnlockablesManager::*)(core::Name<core::CaseSensitiveKey>, bool, bool, bool));
template void engine::LuaScriptManager::RegisterMethod<proto::UnlockablesManager, int, unsigned int, core::Name<core::CaseSensitiveKey>>(const char*,
	proto::UnlockablesManager*, int (proto::UnlockablesManager::*)(unsigned int, core::Name<core::CaseSensitiveKey>));
template void engine::LuaScriptManager::RegisterMethod<proto::UnlockablesManager, void, int>(const char*,
	proto::UnlockablesManager*, void (proto::UnlockablesManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::UnlockablesManager, int>(const char*,
	proto::UnlockablesManager*, int (proto::UnlockablesManager::*)());
template void engine::LuaScriptManager::RegisterMethod<proto::UnlockablesManager, void, unsigned int>(const char*,
	proto::UnlockablesManager*, void (proto::UnlockablesManager::*)(unsigned int));
template void engine::LuaScriptManager::RegisterMethod<proto::UnlockablesManager, bool, int, int>(const char*,
	proto::UnlockablesManager*, bool (proto::UnlockablesManager::*)(int, int));
template void engine::LuaScriptManager::RegisterMethod<proto::UnlockablesManager, bool, int>(const char*,
	proto::UnlockablesManager*, bool (proto::UnlockablesManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::UnlockablesManager, int, int, int>(const char*,
	proto::UnlockablesManager*, int (proto::UnlockablesManager::*)(int, int));
template void engine::LuaScriptManager::RegisterMethod<proto::UnlockablesManager, const char*, int, int>(const char*,
	proto::UnlockablesManager*, const char* (proto::UnlockablesManager::*)(int, int));
template void engine::LuaScriptManager::RegisterMethod<proto::UnlockablesManager, int, int>(const char*,
	proto::UnlockablesManager*, int (proto::UnlockablesManager::*)(int));
template void engine::LuaScriptManager::RegisterMethod<proto::UnlockablesManager, void, int, int, bool>(const char*,
	proto::UnlockablesManager*, void (proto::UnlockablesManager::*)(int, int, bool));

// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x1057A760
// FUNCTION: ENGINE 0x1057A7D0
// FUNCTION: ENGINE 0x1057A800
// FUNCTION: ENGINE 0x1057A830
// FUNCTION: ENGINE 0x1057A8B0
// FUNCTION: ENGINE 0x1057A8E0
// FUNCTION: ENGINE 0x1057A910
// FUNCTION: ENGINE 0x1057A980
// FUNCTION: ENGINE 0x1057A9A0
// FUNCTION: ENGINE 0x1057A9C0
// FUNCTION: ENGINE 0x1057AA50
// FUNCTION: ENGINE 0x1057AAC0
// FUNCTION: ENGINE 0x1057AAF0
// FUNCTION: ENGINE 0x1057AB60
// FUNCTION: ENGINE 0x1057ABB0
// FUNCTION: ENGINE 0x1057AC10
// FUNCTION: ENGINE 0x1057AC70
// FUNCTION: ENGINE 0x1057AC90
// FUNCTION: ENGINE 0x1057ACB0
// FUNCTION: ENGINE 0x1057AD00
// FUNCTION: ENGINE 0x1057AD20
// FUNCTION: ENGINE 0x1057AD40
// FUNCTION: ENGINE 0x1057ADA0
// FUNCTION: ENGINE 0x1057ADC0
// FUNCTION: ENGINE 0x1057ADE0
// FUNCTION: ENGINE 0x1057AE50
// FUNCTION: ENGINE 0x1057AE80
// FUNCTION: ENGINE 0x1057AEB0
// FUNCTION: ENGINE 0x1057AF10
// FUNCTION: ENGINE 0x1057AF30
// FUNCTION: ENGINE 0x1057AF60
// FUNCTION: ENGINE 0x1057AFD0
// FUNCTION: ENGINE 0x1057B000
// FUNCTION: ENGINE 0x1057B030
// FUNCTION: ENGINE 0x1057B0A0
// FUNCTION: ENGINE 0x1057B0D0
// FUNCTION: ENGINE 0x1057B100
// FUNCTION: ENGINE 0x1057B160
// FUNCTION: ENGINE 0x1057B180
// FUNCTION: ENGINE 0x1057B1B0
// FUNCTION: ENGINE 0x1057B230
// FUNCTION: ENGINE 0x1057B260
// FUNCTION: ENGINE 0x1057BB00
// FUNCTION: ENGINE 0x1057BB30
// FUNCTION: ENGINE 0x1057BB60
// FUNCTION: ENGINE 0x1057BB90
// FUNCTION: ENGINE 0x1057BBC0
// FUNCTION: ENGINE 0x1057BBF0
// FUNCTION: ENGINE 0x1057BC10
// FUNCTION: ENGINE 0x1057BC40
// FUNCTION: ENGINE 0x1057BC70
// FUNCTION: ENGINE 0x1057BCA0
// FUNCTION: ENGINE 0x1057BD00
// FUNCTION: ENGINE 0x1057BD70
// FUNCTION: ENGINE 0x1057BD90
// FUNCTION: ENGINE 0x1057BDF0
// FUNCTION: ENGINE 0x1057BE10
// FUNCTION: ENGINE 0x1057BE80
// FUNCTION: ENGINE 0x1057BEA0
// FUNCTION: ENGINE 0x1057BED0
// FUNCTION: ENGINE 0x1057BF00
// FUNCTION: ENGINE 0x1057BF70
// FUNCTION: ENGINE 0x1057BFA0
// FUNCTION: ENGINE 0x1057BFD0
// FUNCTION: ENGINE 0x1057C000
// FUNCTION: ENGINE 0x1057C030
// FUNCTION: ENGINE 0x1057C060
// FUNCTION: ENGINE 0x1057C0D0
// FUNCTION: ENGINE 0x1057C100
// FUNCTION: ENGINE 0x1057C130
// FUNCTION: ENGINE 0x1057C4F0
// FUNCTION: ENGINE 0x1057C560
// FUNCTION: ENGINE 0x1057C5D0
// FUNCTION: ENGINE 0x1057C640
// FUNCTION: ENGINE 0x1057C6B0
// FUNCTION: ENGINE 0x1057C720
// FUNCTION: ENGINE 0x1057C780
// FUNCTION: ENGINE 0x1057C810
// FUNCTION: ENGINE 0x1057C870
// FUNCTION: ENGINE 0x1057C8E0
// FUNCTION: ENGINE 0x1057C940
// FUNCTION: ENGINE 0x1057C9B0
// FUNCTION: ENGINE 0x1057CA20
// FUNCTION: ENGINE 0x1057CA80
