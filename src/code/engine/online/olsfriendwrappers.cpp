// The script method wrappers of the online classes engine::OLSFriend and engine::OLSPeer (the unit that registers
// their methods with the script context instantiates engine::Function's Method and Closure templates for them). The
// classes themselves are other files'; OLSPeer has several bases, so its method pointers have two words.
#include "code/engine/function.h"
#include "code/engine/online/olsfriend.h"

template class Method0<engine::OLSFriend, void>;
template class Method1<engine::OLSFriend, int, int>;
template class Method0<engine::OLSFriend, const char*>;
template class Method0<engine::OLSFriend, int>;
template class Method1<engine::OLSFriend, void, const char*>;
template class Method1<engine::OLSFriend, void, int>;
template class Method2<engine::OLSFriend, void, int, const char*>;
template class Closure0<engine::OLSFriend, void>;
template class Closure1<engine::OLSFriend, int, int>;
template class Closure0<engine::OLSFriend, const char*>;
template class Closure0<engine::OLSFriend, int>;
template class Closure1<engine::OLSFriend, void, const char*>;
template class Closure1<engine::OLSFriend, void, int>;
template class Closure2<engine::OLSFriend, void, int, const char*>;
template void engine::LuaScriptManager::RegisterMethod<engine::OLSFriend, void>(const char*, engine::OLSFriend*,
	void (engine::OLSFriend::*)());
template void engine::LuaScriptManager::RegisterMethod<engine::OLSFriend, int, int>(const char*, engine::OLSFriend*,
	int (engine::OLSFriend::*)(int));
template void engine::LuaScriptManager::RegisterMethod<engine::OLSFriend, const char*>(const char*, engine::OLSFriend*,
	const char* (engine::OLSFriend::*)());
template void engine::LuaScriptManager::RegisterMethod<engine::OLSFriend, int>(const char*, engine::OLSFriend*,
	int (engine::OLSFriend::*)());
template void engine::LuaScriptManager::RegisterMethod<engine::OLSFriend, void, const char*>(const char*, engine::OLSFriend*,
	void (engine::OLSFriend::*)(const char*));
template void engine::LuaScriptManager::RegisterMethod<engine::OLSFriend, void, int>(const char*, engine::OLSFriend*,
	void (engine::OLSFriend::*)(int));
template void engine::LuaScriptManager::RegisterMethod<engine::OLSFriend, void, int, const char*>(const char*,
	engine::OLSFriend*, void (engine::OLSFriend::*)(int, const char*));

#pragma pointers_to_members(full_generality, multiple_inheritance)

namespace engine
{
	class OLSPeer;
}

template class Method0<engine::OLSPeer, bool>;
template class Closure0<engine::OLSPeer, bool>;
template void engine::LuaScriptManager::RegisterMethod<engine::OLSPeer, bool>(const char*, engine::OLSPeer*,
	bool (engine::OLSPeer::*)());

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108E9420
// FUNCTION: ENGINE 0x108E9460
// FUNCTION: ENGINE 0x108E9480
// FUNCTION: ENGINE 0x108E9630
// FUNCTION: ENGINE 0x108E9680
// FUNCTION: ENGINE 0x108E96A0
// FUNCTION: ENGINE 0x108EA1F0
// FUNCTION: ENGINE 0x108EA230
// FUNCTION: ENGINE 0x108EA510
// FUNCTION: ENGINE 0x108EA560
// FUNCTION: ENGINE 0x108EA570
// FUNCTION: ENGINE 0x108EA5C0
// FUNCTION: ENGINE 0x108EA5E0
// FUNCTION: ENGINE 0x108EA600
// FUNCTION: ENGINE 0x108EA640
// FUNCTION: ENGINE 0x108EA660
// FUNCTION: ENGINE 0x108EA680
// FUNCTION: ENGINE 0x108EA6C0
// FUNCTION: ENGINE 0x108EA6E0
// FUNCTION: ENGINE 0x108EA700
// FUNCTION: ENGINE 0x108EA750
// FUNCTION: ENGINE 0x108EA760
// FUNCTION: ENGINE 0x108EA780
// FUNCTION: ENGINE 0x108EA7D0
// FUNCTION: ENGINE 0x108EA7E0
// FUNCTION: ENGINE 0x108EA800
// FUNCTION: ENGINE 0x108EA860
// FUNCTION: ENGINE 0x108EA880
// FUNCTION: ENGINE 0x108EA8C0
// FUNCTION: ENGINE 0x108EA930
// FUNCTION: ENGINE 0x108EA980
// FUNCTION: ENGINE 0x108EA9A0
// FUNCTION: ENGINE 0x108EA9B0
// FUNCTION: ENGINE 0x108EAA00
// FUNCTION: ENGINE 0x108EAA20
// FUNCTION: ENGINE 0x108EAA70
// FUNCTION: ENGINE 0x108EAA90
// FUNCTION: ENGINE 0x108EAAE0
// FUNCTION: ENGINE 0x108EAB00
// FUNCTION: ENGINE 0x108EAB50
// FUNCTION: ENGINE 0x108EAB70
// FUNCTION: ENGINE 0x108EABA0
// FUNCTION: ENGINE 0x108EABC0
// FUNCTION: ENGINE 0x108EAC10
// FUNCTION: ENGINE 0x108EAC80
// FUNCTION: ENGINE 0x108EACF0
// FUNCTION: ENGINE 0x108EAD40
// FUNCTION: ENGINE 0x108EAD90
