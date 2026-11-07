// The script methods and the render events of proto::ProtoRenderManager (unit 0x102E0030 - 0x102E5580; no assert path names
// it, the file name is a guess): the render manager registers methods that read and change the video settings with the script
// context, and queues the changes as render events. The class itself is another file's; it is declared here as far as the
// signatures need it (it has two bases with a vftable each, which asks for method pointers of two words).
#include "code/engine/function.h"
#include "code/engine/render/async/renderevent.h"
#include "code/core/name.h"

namespace pure3d
{
	enum pddiAntialiasMode
	{
		pddiAntialiasModeNone
	};
}

namespace proto
{
	class ProtoRenderManagerBase0
	{
	};
	class ProtoRenderManagerBase1
	{
	};
	class ProtoRenderManager : public ProtoRenderManagerBase0, public ProtoRenderManagerBase1
	{
	};
}

template class Function2<void, unsigned int, float>;
template class Function5<void, unsigned int, float, float, float, float>;
template void engine::LuaScriptManager::Register<void, unsigned int, float>(const char*, void (*)(unsigned int, float));
template void engine::LuaScriptManager::Register<void, unsigned int, float, float, float, float>(const char*,
	void (*)(unsigned int, float, float, float, float));

template class engine::render::ObjRenderEvent1<proto::ProtoRenderManager, core::Name<core::CaseSensitiveKey> >;
template class engine::render::ObjRenderEvent1<proto::ProtoRenderManager, float>;
template class engine::render::ObjRenderEvent1<proto::ProtoRenderManager, bool>;
template class engine::render::ObjRenderEvent1<proto::ProtoRenderManager, pure3d::pddiAntialiasMode>;
template class engine::render::ObjRenderEvent2<proto::ProtoRenderManager, unsigned int, unsigned int>;
template class engine::render::ObjRenderEvent1<proto::ProtoRenderManager, unsigned int>;
template class engine::render::ObjRenderEvent0<proto::ProtoRenderManager>;

template class Method0<proto::ProtoRenderManager, void>;
template class Closure0<proto::ProtoRenderManager, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::ProtoRenderManager, void>(const char*,
	proto::ProtoRenderManager*, void (proto::ProtoRenderManager::*)());

template class Method1<proto::ProtoRenderManager, void, const char*>;
template class Closure1<proto::ProtoRenderManager, void, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::ProtoRenderManager, void, const char*>(const char*,
	proto::ProtoRenderManager*, void (proto::ProtoRenderManager::*)(const char*));

template class Method1<proto::ProtoRenderManager, void, bool>;
template class Closure1<proto::ProtoRenderManager, void, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::ProtoRenderManager, void, bool>(const char*,
	proto::ProtoRenderManager*, void (proto::ProtoRenderManager::*)(bool));

template class Method1<proto::ProtoRenderManager, void, float>;
template class Closure1<proto::ProtoRenderManager, void, float>;
template void engine::LuaScriptManager::RegisterMethod<proto::ProtoRenderManager, void, float>(const char*,
	proto::ProtoRenderManager*, void (proto::ProtoRenderManager::*)(float));

template class Method1<proto::ProtoRenderManager, void, pure3d::pddiAntialiasMode>;
template class Closure1<proto::ProtoRenderManager, void, pure3d::pddiAntialiasMode>;
template void engine::LuaScriptManager::RegisterMethod<proto::ProtoRenderManager, void, pure3d::pddiAntialiasMode>(const char*,
	proto::ProtoRenderManager*, void (proto::ProtoRenderManager::*)(pure3d::pddiAntialiasMode));

template class Method2<proto::ProtoRenderManager, void, unsigned int, unsigned int>;
template class Closure2<proto::ProtoRenderManager, void, unsigned int, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::ProtoRenderManager, void, unsigned int, unsigned int>(const char*,
	proto::ProtoRenderManager*, void (proto::ProtoRenderManager::*)(unsigned int, unsigned int));

template class Method1<proto::ProtoRenderManager, void, unsigned int>;
template class Closure1<proto::ProtoRenderManager, void, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::ProtoRenderManager, void, unsigned int>(const char*,
	proto::ProtoRenderManager*, void (proto::ProtoRenderManager::*)(unsigned int));

template class Method2<proto::ProtoRenderManager, void, float, float>;
template class Closure2<proto::ProtoRenderManager, void, float, float>;
template void engine::LuaScriptManager::RegisterMethod<proto::ProtoRenderManager, void, float, float>(const char*,
	proto::ProtoRenderManager*, void (proto::ProtoRenderManager::*)(float, float));

template class Method1<proto::ProtoRenderManager, int, unsigned int>;
template class Closure1<proto::ProtoRenderManager, int, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::ProtoRenderManager, int, unsigned int>(const char*,
	proto::ProtoRenderManager*, int (proto::ProtoRenderManager::*)(unsigned int));

template class Method0<proto::ProtoRenderManager, int>;
template class Closure0<proto::ProtoRenderManager, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::ProtoRenderManager, int>(const char*,
	proto::ProtoRenderManager*, int (proto::ProtoRenderManager::*)());

template class Method2<proto::ProtoRenderManager, bool, unsigned int, unsigned int>;
template class Closure2<proto::ProtoRenderManager, bool, unsigned int, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::ProtoRenderManager, bool, unsigned int, unsigned int>(const char*,
	proto::ProtoRenderManager*, bool (proto::ProtoRenderManager::*)(unsigned int, unsigned int));

template class Method1<proto::ProtoRenderManager, bool, unsigned int>;
template class Closure1<proto::ProtoRenderManager, bool, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::ProtoRenderManager, bool, unsigned int>(const char*,
	proto::ProtoRenderManager*, bool (proto::ProtoRenderManager::*)(unsigned int));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102E1910
// FUNCTION: ENGINE 0x102E1930
// FUNCTION: ENGINE 0x102E19A0
// FUNCTION: ENGINE 0x102E19C0
// FUNCTION: ENGINE 0x102E19E0
// FUNCTION: ENGINE 0x102E1A80
// FUNCTION: ENGINE 0x102E1AD0
// FUNCTION: ENGINE 0x102E1B20
// FUNCTION: ENGINE 0x102E1B60
// FUNCTION: ENGINE 0x102E1B80
// FUNCTION: ENGINE 0x102E1BC0
// FUNCTION: ENGINE 0x102E1BF0
// FUNCTION: ENGINE 0x102E1C20
// FUNCTION: ENGINE 0x102E1C50
// FUNCTION: ENGINE 0x102E1C80
// FUNCTION: ENGINE 0x102E1CB0
// FUNCTION: ENGINE 0x102E1CF0
// FUNCTION: ENGINE 0x102E1D20
// FUNCTION: ENGINE 0x102E1D50
// FUNCTION: ENGINE 0x102E1D80
// FUNCTION: ENGINE 0x102E1DB0
// FUNCTION: ENGINE 0x102E1DD0
// FUNCTION: ENGINE 0x102E1DF0
// FUNCTION: ENGINE 0x102E1E50
// FUNCTION: ENGINE 0x102E1E70
// FUNCTION: ENGINE 0x102E1E90
// FUNCTION: ENGINE 0x102E1EF0
// FUNCTION: ENGINE 0x102E1F10
// FUNCTION: ENGINE 0x102E1F30
// FUNCTION: ENGINE 0x102E1F90
// FUNCTION: ENGINE 0x102E1FB0
// FUNCTION: ENGINE 0x102E1FE0
// FUNCTION: ENGINE 0x102E2040
// FUNCTION: ENGINE 0x102E2060
// FUNCTION: ENGINE 0x102E2080
// FUNCTION: ENGINE 0x102E20F0
// FUNCTION: ENGINE 0x102E2110
// FUNCTION: ENGINE 0x102E2140
// FUNCTION: ENGINE 0x102E21A0
// FUNCTION: ENGINE 0x102E21C0
// FUNCTION: ENGINE 0x102E21E0
// FUNCTION: ENGINE 0x102E2250
// FUNCTION: ENGINE 0x102E2280
// FUNCTION: ENGINE 0x102E22B0
// FUNCTION: ENGINE 0x102E2310
// FUNCTION: ENGINE 0x102E2340
// FUNCTION: ENGINE 0x102E2370
// FUNCTION: ENGINE 0x102E23C0
// FUNCTION: ENGINE 0x102E23E0
// FUNCTION: ENGINE 0x102E2410
// FUNCTION: ENGINE 0x102E2480
// FUNCTION: ENGINE 0x102E24B0
// FUNCTION: ENGINE 0x102E24F0
// FUNCTION: ENGINE 0x102E2550
// FUNCTION: ENGINE 0x102E2580
// FUNCTION: ENGINE 0x102E26B0
// FUNCTION: ENGINE 0x102E2750
// FUNCTION: ENGINE 0x102E27B0
// FUNCTION: ENGINE 0x102E2B00
// FUNCTION: ENGINE 0x102E2B70
// FUNCTION: ENGINE 0x102E2B90
// FUNCTION: ENGINE 0x102E2C00
// FUNCTION: ENGINE 0x102E2C20
// FUNCTION: ENGINE 0x102E2C90
// FUNCTION: ENGINE 0x102E2CC0
// FUNCTION: ENGINE 0x102E2D30
// FUNCTION: ENGINE 0x102E2D50
// FUNCTION: ENGINE 0x102E2D90
// FUNCTION: ENGINE 0x102E2DC0
// FUNCTION: ENGINE 0x102E2DE0
// FUNCTION: ENGINE 0x102E2E50
// FUNCTION: ENGINE 0x102E2E70
// FUNCTION: ENGINE 0x102E2EB0
// FUNCTION: ENGINE 0x102E2EE0
// FUNCTION: ENGINE 0x102E2F50
// FUNCTION: ENGINE 0x102E2F80
// FUNCTION: ENGINE 0x102E2FE0
// FUNCTION: ENGINE 0x102E3000
// FUNCTION: ENGINE 0x102E3040
// FUNCTION: ENGINE 0x102E3080
// FUNCTION: ENGINE 0x102E30F0
// FUNCTION: ENGINE 0x102E3120
