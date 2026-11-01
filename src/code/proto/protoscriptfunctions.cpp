// The script functions of the game object natives that live in the proto game's script binding unit (0x10280020 -
// 0x1028DB50; no assert path names it, the file name is a guess): the instances of engine::Function1..7 and of the
// script manager's registration templates for their signatures. The natives themselves follow in the unit.
#include "code/core/name.h"
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/genericscriptvalue.h"
#include "code/engine/luascriptmanager.h"
#include "code/math/vector.h"

template class Function2<bool, engine::LuaGOH, bool>;
template class Function0<bool>;
template class Function2<math::Vector, engine::LuaGOH, const char*>;
template class Function2<void, const char*, math::Vector>;
template class Function4<void, engine::LuaGOH, int, core::Name<core::CaseSensitiveKey>, float>;
template class Function5<void, engine::LuaGOH, const char*, const char*, engine::LuaGOH, float>;
template class Function2<engine::LuaGOH, engine::LuaGOH, const char*>;
template class Function3<void, engine::LuaGOH, const char*, const char*>;
template class Function1<bool, bool>;
template class Function2<bool, engine::LuaGOH, const char*>;
template class Function2<int, const char*, const char*>;
template class Function3<void, const char*, const char*, int>;
template class Function2<int, engine::LuaGOH, const char*>;
template class Function3<void, engine::LuaGOH, const char*, int>;
template class Function2<float, engine::LuaGOH, const char*>;
template class Function4<void, engine::LuaGOH, const char*, float, bool>;
template class Function3<void, const char*, const char*, const char*>;
template class Function2<math::Vector, engine::LuaGOH, int>;
template class Function4<void, engine::LuaGOH, float, math::Vector, math::Vector>;
template class Function1<engine::LuaGOH, engine::LuaGOH>;
template class Function3<bool, engine::LuaGOH, engine::LuaGOH, const char*>;
template class Function1<int, engine::LuaGOH>;
template class Function7<void, engine::LuaGOH, float, float, float, float, float, float>;
template class Function2<void, engine::LuaGOH, int>;
template class Function2<void, const char*, engine::LuaGOH>;
template class Function2<void, engine::LuaGOH, engine::LuaGOH>;
template class Function3<void, engine::LuaGOH, engine::LuaGOH, math::Vector>;
template class Function4<bool, engine::LuaGOH, const char*, const char*, bool>;
template class Function2<bool, engine::LuaGOH, float>;
template class Function1<void, float>;
template class Function3<void, engine::LuaGOH, bool, bool>;
template class Function1<void, const char*>;
template class Function1<float, float>;
template class Function3<void, engine::LuaGOH, int, float>;
template class Function2<math::Vector, engine::LuaGOH, math::Vector>;
template class Function2<void, engine::LuaGOH, math::Vector>;
template class Function3<void, engine::LuaGOH, engine::LuaGOH, bool>;
template class Function4<engine::LuaGOH, const char*, const char*, math::Vector, float>;
template class Function3<engine::LuaGOH, const char*, math::Vector, math::Vector>;
template class Function4<engine::LuaGOH, const char*, const char*, float, engine::LuaGOH>;
template class Function2<void, const char*, bool>;
template class Function1<bool, const char*>;
template class Function2<bool, const char*, bool>;
template class Function1<const char*, const char*>;
template class Function0<int>;
template class Function1<void, math::Vector>;
template class Function4<engine::LuaGOH, core::Name<core::CaseSensitiveKey>, core::Name<core::CaseSensitiveKey>, math::Vector, math::Vector>;
template class Function2<void, float, float>;
template class Function2<void, const char*, const char*>;
template class Function4<void, engine::LuaGOH, float, const char*, float>;
template class Function1<float, math::Vector>;
template class Function2<math::Vector, float, math::Vector>;
template class Function2<void, int, bool>;
template class Function3<void, int, bool, const char*>;
template class Function1<void, bool>;

// The one-argument registration is defined here only (the units that register one call the engine's copies)
template<class R, class A> inline void engine::LuaScriptManager::Register(const char* name, R (*function)(A))
{
	AddFunction(name, new Function1<R, A>(name, function));
}

template void engine::LuaScriptManager::Register<void>(const char*,
	void (*)());
template void engine::LuaScriptManager::Register<bool, engine::LuaGOH, bool>(const char*,
	bool (*)(engine::LuaGOH, bool));
template void engine::LuaScriptManager::Register<bool>(const char*,
	bool (*)());
template void engine::LuaScriptManager::Register<math::Vector, engine::LuaGOH, const char*>(const char*,
	math::Vector (*)(engine::LuaGOH, const char*));
template void engine::LuaScriptManager::Register<void, const char*, math::Vector>(const char*,
	void (*)(const char*, math::Vector));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, int, core::Name<core::CaseSensitiveKey>, float>(const char*,
	void (*)(engine::LuaGOH, int, core::Name<core::CaseSensitiveKey>, float));
template void engine::LuaScriptManager::Register<engine::LuaGOH, engine::LuaGOH, const char*>(const char*,
	engine::LuaGOH (*)(engine::LuaGOH, const char*));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, const char*, const char*>(const char*,
	void (*)(engine::LuaGOH, const char*, const char*));
template void engine::LuaScriptManager::Register<bool, bool>(const char*,
	bool (*)(bool));
template void engine::LuaScriptManager::Register<bool, engine::LuaGOH, const char*>(const char*,
	bool (*)(engine::LuaGOH, const char*));
template void engine::LuaScriptManager::Register<int, const char*, const char*>(const char*,
	int (*)(const char*, const char*));
template void engine::LuaScriptManager::Register<void, const char*, const char*, int>(const char*,
	void (*)(const char*, const char*, int));
template void engine::LuaScriptManager::Register<int, engine::LuaGOH, const char*>(const char*,
	int (*)(engine::LuaGOH, const char*));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, const char*, int>(const char*,
	void (*)(engine::LuaGOH, const char*, int));
template void engine::LuaScriptManager::Register<float, engine::LuaGOH, const char*>(const char*,
	float (*)(engine::LuaGOH, const char*));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, const char*, float, bool>(const char*,
	void (*)(engine::LuaGOH, const char*, float, bool));
template void engine::LuaScriptManager::Register<void, const char*, const char*, const char*>(const char*,
	void (*)(const char*, const char*, const char*));
template void engine::LuaScriptManager::Register<math::Vector, engine::LuaGOH, int>(const char*,
	math::Vector (*)(engine::LuaGOH, int));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, float, math::Vector, math::Vector>(const char*,
	void (*)(engine::LuaGOH, float, math::Vector, math::Vector));
template void engine::LuaScriptManager::Register<engine::LuaGOH, engine::LuaGOH>(const char*,
	engine::LuaGOH (*)(engine::LuaGOH));
template void engine::LuaScriptManager::Register<bool, engine::LuaGOH, engine::LuaGOH, const char*>(const char*,
	bool (*)(engine::LuaGOH, engine::LuaGOH, const char*));
template void engine::LuaScriptManager::Register<int, engine::LuaGOH>(const char*,
	int (*)(engine::LuaGOH));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, int>(const char*,
	void (*)(engine::LuaGOH, int));
template void engine::LuaScriptManager::Register<void, const char*, engine::LuaGOH>(const char*,
	void (*)(const char*, engine::LuaGOH));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, engine::LuaGOH>(const char*,
	void (*)(engine::LuaGOH, engine::LuaGOH));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, engine::LuaGOH, math::Vector>(const char*,
	void (*)(engine::LuaGOH, engine::LuaGOH, math::Vector));
template void engine::LuaScriptManager::Register<bool, engine::LuaGOH, const char*, const char*, bool>(const char*,
	bool (*)(engine::LuaGOH, const char*, const char*, bool));
template void engine::LuaScriptManager::Register<bool, engine::LuaGOH, float>(const char*,
	bool (*)(engine::LuaGOH, float));
template void engine::LuaScriptManager::Register<void, float>(const char*,
	void (*)(float));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, bool, bool>(const char*,
	void (*)(engine::LuaGOH, bool, bool));
template void engine::LuaScriptManager::Register<void, const char*>(const char*,
	void (*)(const char*));
template void engine::LuaScriptManager::Register<float, float>(const char*,
	float (*)(float));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, int, float>(const char*,
	void (*)(engine::LuaGOH, int, float));
template void engine::LuaScriptManager::Register<math::Vector, engine::LuaGOH, math::Vector>(const char*,
	math::Vector (*)(engine::LuaGOH, math::Vector));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, math::Vector>(const char*,
	void (*)(engine::LuaGOH, math::Vector));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, engine::LuaGOH, bool>(const char*,
	void (*)(engine::LuaGOH, engine::LuaGOH, bool));
template void engine::LuaScriptManager::Register<engine::LuaGOH, const char*, const char*, math::Vector, float>(const char*,
	engine::LuaGOH (*)(const char*, const char*, math::Vector, float));
template void engine::LuaScriptManager::Register<engine::LuaGOH, const char*, math::Vector, math::Vector>(const char*,
	engine::LuaGOH (*)(const char*, math::Vector, math::Vector));
template void engine::LuaScriptManager::Register<engine::LuaGOH, const char*, const char*, float, engine::LuaGOH>(const char*,
	engine::LuaGOH (*)(const char*, const char*, float, engine::LuaGOH));
template void engine::LuaScriptManager::Register<void, const char*, bool>(const char*,
	void (*)(const char*, bool));
template void engine::LuaScriptManager::Register<bool, const char*>(const char*,
	bool (*)(const char*));
template void engine::LuaScriptManager::Register<bool, const char*, bool>(const char*,
	bool (*)(const char*, bool));
template void engine::LuaScriptManager::Register<const char*, const char*>(const char*,
	const char* (*)(const char*));
template void engine::LuaScriptManager::Register<int>(const char*,
	int (*)());
template void engine::LuaScriptManager::Register<void, math::Vector>(const char*,
	void (*)(math::Vector));
template void engine::LuaScriptManager::Register<engine::LuaGOH, core::Name<core::CaseSensitiveKey>, core::Name<core::CaseSensitiveKey>, math::Vector, math::Vector>(const char*,
	engine::LuaGOH (*)(core::Name<core::CaseSensitiveKey>, core::Name<core::CaseSensitiveKey>, math::Vector, math::Vector));
template void engine::LuaScriptManager::Register<void, float, float>(const char*,
	void (*)(float, float));
template void engine::LuaScriptManager::Register<void, const char*, const char*>(const char*,
	void (*)(const char*, const char*));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, float, const char*, float>(const char*,
	void (*)(engine::LuaGOH, float, const char*, float));
template void engine::LuaScriptManager::Register<float, math::Vector>(const char*,
	float (*)(math::Vector));
template void engine::LuaScriptManager::Register<math::Vector, float, math::Vector>(const char*,
	math::Vector (*)(float, math::Vector));
template void engine::LuaScriptManager::Register<void, int, bool>(const char*,
	void (*)(int, bool));
template void engine::LuaScriptManager::Register<void, int, bool, const char*>(const char*,
	void (*)(int, bool, const char*));
template void engine::LuaScriptManager::Register<void, bool>(const char*,
	void (*)(bool));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10280020
// FUNCTION: ENGINE 0x102800E0
// FUNCTION: ENGINE 0x102800F0
// FUNCTION: ENGINE 0x10280190
// FUNCTION: ENGINE 0x10280330
// FUNCTION: ENGINE 0x10280380
// FUNCTION: ENGINE 0x102803A0
// FUNCTION: ENGINE 0x102803C0
// FUNCTION: ENGINE 0x10280490
// FUNCTION: ENGINE 0x102804F0
// FUNCTION: ENGINE 0x102805B0
// FUNCTION: ENGINE 0x10280600
// FUNCTION: ENGINE 0x10280690
// FUNCTION: ENGINE 0x102806F0
// FUNCTION: ENGINE 0x10280750
// FUNCTION: ENGINE 0x102807F0
// FUNCTION: ENGINE 0x10280830
// FUNCTION: ENGINE 0x10280880
// FUNCTION: ENGINE 0x102808F0
// FUNCTION: ENGINE 0x10280920
// FUNCTION: ENGINE 0x10280950
// FUNCTION: ENGINE 0x102809F0
// FUNCTION: ENGINE 0x10280A20
// FUNCTION: ENGINE 0x10280A80
// FUNCTION: ENGINE 0x10280AB0
// FUNCTION: ENGINE 0x10280AE0
// FUNCTION: ENGINE 0x10280B50
// FUNCTION: ENGINE 0x10280B80
// FUNCTION: ENGINE 0x10280DF0
// FUNCTION: ENGINE 0x10280E90
// FUNCTION: ENGINE 0x10280EC0
// FUNCTION: ENGINE 0x10280F60
// FUNCTION: ENGINE 0x10280F90
// FUNCTION: ENGINE 0x10281030
// FUNCTION: ENGINE 0x10281060
// FUNCTION: ENGINE 0x10281100
// FUNCTION: ENGINE 0x10281130
// FUNCTION: ENGINE 0x102811A0
// FUNCTION: ENGINE 0x102811E0
// FUNCTION: ENGINE 0x10281220
// FUNCTION: ENGINE 0x102812B0
// FUNCTION: ENGINE 0x102812E0
// FUNCTION: ENGINE 0x10281320
// FUNCTION: ENGINE 0x102813C0
// FUNCTION: ENGINE 0x102813F0
// FUNCTION: ENGINE 0x102814C0
// FUNCTION: ENGINE 0x102817A0
// FUNCTION: ENGINE 0x10281830
// FUNCTION: ENGINE 0x102818C0
// FUNCTION: ENGINE 0x10281950
// FUNCTION: ENGINE 0x102819B0
// FUNCTION: ENGINE 0x102819E0
// FUNCTION: ENGINE 0x10281B80
// FUNCTION: ENGINE 0x10281C00
// FUNCTION: ENGINE 0x10281C30
// FUNCTION: ENGINE 0x10281C60
// FUNCTION: ENGINE 0x10281CC0
// FUNCTION: ENGINE 0x10281CE0
// FUNCTION: ENGINE 0x10281D10
// FUNCTION: ENGINE 0x10281DE0
// FUNCTION: ENGINE 0x10281E40
// FUNCTION: ENGINE 0x10281EA0
// FUNCTION: ENGINE 0x10281F30
// FUNCTION: ENGINE 0x10281F50
// FUNCTION: ENGINE 0x10281FC0
// FUNCTION: ENGINE 0x10281FE0
// FUNCTION: ENGINE 0x10282000
// FUNCTION: ENGINE 0x10282090
// FUNCTION: ENGINE 0x102820B0
// FUNCTION: ENGINE 0x10282130
// FUNCTION: ENGINE 0x10282180
// FUNCTION: ENGINE 0x102821D0
// FUNCTION: ENGINE 0x10282260
// FUNCTION: ENGINE 0x102822B0
// FUNCTION: ENGINE 0x10282300
// FUNCTION: ENGINE 0x10282370
// FUNCTION: ENGINE 0x102823A0
// FUNCTION: ENGINE 0x102823D0
// FUNCTION: ENGINE 0x10282430
// FUNCTION: ENGINE 0x10282450
// FUNCTION: ENGINE 0x10282470
// FUNCTION: ENGINE 0x102824F0
// FUNCTION: ENGINE 0x10282520
// FUNCTION: ENGINE 0x10282550
// FUNCTION: ENGINE 0x102825B0
// FUNCTION: ENGINE 0x102825C0
// FUNCTION: ENGINE 0x102825E0
// FUNCTION: ENGINE 0x10282640
// FUNCTION: ENGINE 0x10282680
// FUNCTION: ENGINE 0x10282760
// FUNCTION: ENGINE 0x10282810
// FUNCTION: ENGINE 0x10282840
// FUNCTION: ENGINE 0x102828B0
// FUNCTION: ENGINE 0x10282930
// FUNCTION: ENGINE 0x102829B0
// FUNCTION: ENGINE 0x10282A70
// FUNCTION: ENGINE 0x10282AC0
// FUNCTION: ENGINE 0x10282B40
// FUNCTION: ENGINE 0x10282B70
// FUNCTION: ENGINE 0x10282BA0
// FUNCTION: ENGINE 0x10282C30
// FUNCTION: ENGINE 0x10282CA0
// FUNCTION: ENGINE 0x10282D10
// FUNCTION: ENGINE 0x10282D90
// FUNCTION: ENGINE 0x10282E20
// FUNCTION: ENGINE 0x10282EB0
// FUNCTION: ENGINE 0x10282F40
// FUNCTION: ENGINE 0x10282F90
// FUNCTION: ENGINE 0x102830F0
// FUNCTION: ENGINE 0x10283160
// FUNCTION: ENGINE 0x10283180
// FUNCTION: ENGINE 0x102831A0
// FUNCTION: ENGINE 0x10283200
// FUNCTION: ENGINE 0x10283220
// FUNCTION: ENGINE 0x10283250
// FUNCTION: ENGINE 0x102832F0
// FUNCTION: ENGINE 0x10283330
// FUNCTION: ENGINE 0x10283390
// FUNCTION: ENGINE 0x102833B0
// FUNCTION: ENGINE 0x102833E0
// FUNCTION: ENGINE 0x10283430
// FUNCTION: ENGINE 0x10283450
// FUNCTION: ENGINE 0x10283470
// FUNCTION: ENGINE 0x102834D0
// FUNCTION: ENGINE 0x10283510
// FUNCTION: ENGINE 0x10283550
// FUNCTION: ENGINE 0x102835E0
// FUNCTION: ENGINE 0x102836B0
// FUNCTION: ENGINE 0x102836E0
// FUNCTION: ENGINE 0x10283750
// FUNCTION: ENGINE 0x10283780
// FUNCTION: ENGINE 0x102837B0
// FUNCTION: ENGINE 0x10283820
// FUNCTION: ENGINE 0x10283840
// FUNCTION: ENGINE 0x10283860
// FUNCTION: ENGINE 0x102838F0
// FUNCTION: ENGINE 0x10283920
// FUNCTION: ENGINE 0x10283A40
// FUNCTION: ENGINE 0x10283AA0
// FUNCTION: ENGINE 0x10283B00
// FUNCTION: ENGINE 0x10283B60
// FUNCTION: ENGINE 0x10283BD0
// FUNCTION: ENGINE 0x10283C50
// FUNCTION: ENGINE 0x10283CD0
// FUNCTION: ENGINE 0x10283D40
// FUNCTION: ENGINE 0x10283D60
// FUNCTION: ENGINE 0x10283D80
// FUNCTION: ENGINE 0x10283E00
// FUNCTION: ENGINE 0x10283E20
// FUNCTION: ENGINE 0x10288F90
// FUNCTION: ENGINE 0x102890E0
// FUNCTION: ENGINE 0x10289160
// FUNCTION: ENGINE 0x102891C0
// FUNCTION: ENGINE 0x10289220
// FUNCTION: ENGINE 0x102892E0
// FUNCTION: ENGINE 0x10289340
// FUNCTION: ENGINE 0x10289430
// FUNCTION: ENGINE 0x10289610
// FUNCTION: ENGINE 0x10289670
// FUNCTION: ENGINE 0x102896D0
// FUNCTION: ENGINE 0x10289730
// FUNCTION: ENGINE 0x10289790
// FUNCTION: ENGINE 0x102897F0
// FUNCTION: ENGINE 0x10289850
// FUNCTION: ENGINE 0x102898B0
// FUNCTION: ENGINE 0x10289A60
// FUNCTION: ENGINE 0x10289BB0
// FUNCTION: ENGINE 0x10289D00
// FUNCTION: ENGINE 0x10289D60
// FUNCTION: ENGINE 0x10289DC0
// FUNCTION: ENGINE 0x10289E20
// FUNCTION: ENGINE 0x10289E80
// FUNCTION: ENGINE 0x10289EE0
// FUNCTION: ENGINE 0x10289FD0
// FUNCTION: ENGINE 0x1028A1E0
// FUNCTION: ENGINE 0x1028A240
// FUNCTION: ENGINE 0x1028A2A0
// FUNCTION: ENGINE 0x1028A300
// FUNCTION: ENGINE 0x1028A360
// FUNCTION: ENGINE 0x1028A3C0
// FUNCTION: ENGINE 0x1028A420
// FUNCTION: ENGINE 0x1028A510
// FUNCTION: ENGINE 0x1028A600
// FUNCTION: ENGINE 0x1028A6F0
// FUNCTION: ENGINE 0x1028A800
// FUNCTION: ENGINE 0x1028A860
// FUNCTION: ENGINE 0x1028A8C0
// FUNCTION: ENGINE 0x1028A920
// FUNCTION: ENGINE 0x1028AA70
// FUNCTION: ENGINE 0x1028AAD0
// FUNCTION: ENGINE 0x1028AB30

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102893A0
// FUNCTION: ENGINE 0x10289AC0
// FUNCTION: ENGINE 0x10289C10
// FUNCTION: ENGINE 0x10289F40
// FUNCTION: ENGINE 0x1028A030
// FUNCTION: ENGINE 0x1028A0C0
// FUNCTION: ENGINE 0x1028A150
// FUNCTION: ENGINE 0x1028A570
// FUNCTION: ENGINE 0x1028A660
// FUNCTION: ENGINE 0x1028A770
// FUNCTION: ENGINE 0x1028A9E0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10280160
// FUNCTION: ENGINE 0x10280E60
// FUNCTION: ENGINE 0x10281000
// FUNCTION: ENGINE 0x102832C0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10280560
// FUNCTION: ENGINE 0x10282A20

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10280430
// FUNCTION: ENGINE 0x10281460

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102809D0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10280F40

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102810E0
// FUNCTION: ENGINE 0x102813A0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10281F10
// FUNCTION: ENGINE 0x10282070

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102827E0
