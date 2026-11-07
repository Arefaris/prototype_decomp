// The script functions of the game object natives (second part of the script binding unit, 0x10369600 - 0x1036C3B0 and
// the registration forms 0x10374740 - 0x10375870; no assert path names it, the file name is a guess): the instances of
// engine::Function0..8 and of the script manager's registration templates for their signatures.
#include "code/core/name.h"
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/genericscriptvalue.h"
#include "code/engine/luascriptmanager.h"
#include "code/math/vector.h"

template class Function3<engine::LuaGOH, const char*, const char*, engine::LuaGOH>;
template class Function4<engine::LuaGOH, const char*, const char*, math::Vector, math::Vector>;
template class Function1<int, int>;
template class Function2<void, int, int>;
template class Function3<void, int, int, bool>;
template class Function1<void, int>;
template class Function2<engine::LuaGOH, const char*, const char*>;
template class Function2<engine::LuaGOH, engine::LuaGOH, int>;
template class Function4<void, engine::LuaGOH, math::Vector, math::Vector, float>;
template class Function4<void, engine::LuaGOH, engine::LuaGOH, math::Vector, float>;
template class Function4<void, engine::LuaGOH, math::Vector, math::Vector, engine::LuaGOH>;
template class Function4<void, engine::LuaGOH, math::Vector, math::Vector, const char*>;
template class Function3<void, engine::LuaGOH, math::Vector, float>;
template class Function3<void, engine::LuaGOH, bool, float>;
template class Function3<void, engine::LuaGOH, engine::LuaGOH, float>;
template class Function2<bool, engine::LuaGOH, math::Vector>;
template class Function4<void, engine::LuaGOH, float, float, float>;
template class Function1<bool, math::Vector>;
template class Function1<engine::LuaGOH, math::Vector>;
template class Function3<void, int, float, float>;
template class Function3<void, float, float, float>;
template class Function2<void, const char*, int>;
template class Function6<void, engine::LuaGOH, float, float, int, int, bool>;
template class Function6<void, const char*, float, float, int, int, bool>;
template class Function3<void, engine::LuaGOH, float, float>;
template class Function8<void, float, float, float, float, float, float, float, float>;
template class Function5<void, engine::LuaGOH, float, float, float, float>;
template class Function2<engine::LuaGOH, math::Vector, bool>;
template class Function6<int, math::Vector, math::Vector, int, int, const char*, float>;
template class Function3<void, engine::LuaGOH, int, int>;
template class Function2<int, engine::LuaGOH, int>;
template class Function2<void, math::Vector, float>;
template class Function4<void, math::Vector, int, float, bool>;
template class Function2<void, math::Vector, math::Vector>;
template class Function1<void, unsigned int>;
template class Function0<math::Vector>;
template class Function0<engine::LuaGOH>;
template class Function2<bool, engine::LuaGOH, engine::LuaGOH>;
template class Function2<void, const char*, float>;
template class Function6<void, engine::LuaGOH, const char*, math::Vector, engine::LuaGOH, const char*, math::Vector>;
template class Function1<int, float>;
template class Function2<void, int, const char*>;

// The one-argument registration is defined here only (the units that register one call the engine's copies)
template<class R, class A> inline void engine::LuaScriptManager::Register(const char* name, R (*function)(A))
{
	AddFunction(name, new Function1<R, A>(name, function));
}

template void engine::LuaScriptManager::Register<engine::LuaGOH, const char*, const char*, engine::LuaGOH>(const char*,
	engine::LuaGOH (*)(const char*, const char*, engine::LuaGOH));
template void engine::LuaScriptManager::Register<engine::LuaGOH, const char*, const char*, math::Vector, math::Vector>(const char*,
	engine::LuaGOH (*)(const char*, const char*, math::Vector, math::Vector));
template void engine::LuaScriptManager::Register<int, int>(const char*,
	int (*)(int));
template void engine::LuaScriptManager::Register<void, int, int>(const char*,
	void (*)(int, int));
template void engine::LuaScriptManager::Register<void, int, int, bool>(const char*,
	void (*)(int, int, bool));
template void engine::LuaScriptManager::Register<void, int>(const char*,
	void (*)(int));
template void engine::LuaScriptManager::Register<engine::LuaGOH, const char*, const char*>(const char*,
	engine::LuaGOH (*)(const char*, const char*));
template void engine::LuaScriptManager::Register<engine::LuaGOH, engine::LuaGOH, int>(const char*,
	engine::LuaGOH (*)(engine::LuaGOH, int));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, math::Vector, math::Vector, float>(const char*,
	void (*)(engine::LuaGOH, math::Vector, math::Vector, float));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, engine::LuaGOH, math::Vector, float>(const char*,
	void (*)(engine::LuaGOH, engine::LuaGOH, math::Vector, float));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, math::Vector, math::Vector, engine::LuaGOH>(const char*,
	void (*)(engine::LuaGOH, math::Vector, math::Vector, engine::LuaGOH));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, math::Vector, math::Vector, const char*>(const char*,
	void (*)(engine::LuaGOH, math::Vector, math::Vector, const char*));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, math::Vector, float>(const char*,
	void (*)(engine::LuaGOH, math::Vector, float));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, bool, float>(const char*,
	void (*)(engine::LuaGOH, bool, float));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, engine::LuaGOH, float>(const char*,
	void (*)(engine::LuaGOH, engine::LuaGOH, float));
template void engine::LuaScriptManager::Register<bool, engine::LuaGOH, math::Vector>(const char*,
	bool (*)(engine::LuaGOH, math::Vector));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, float, float, float>(const char*,
	void (*)(engine::LuaGOH, float, float, float));
template void engine::LuaScriptManager::Register<bool, math::Vector>(const char*,
	bool (*)(math::Vector));
template void engine::LuaScriptManager::Register<engine::LuaGOH, math::Vector>(const char*,
	engine::LuaGOH (*)(math::Vector));
template void engine::LuaScriptManager::Register<void, int, float, float>(const char*,
	void (*)(int, float, float));
template void engine::LuaScriptManager::Register<void, float, float, float>(const char*,
	void (*)(float, float, float));
template void engine::LuaScriptManager::Register<void, const char*, int>(const char*,
	void (*)(const char*, int));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, float, float, int, int, bool>(const char*,
	void (*)(engine::LuaGOH, float, float, int, int, bool));
template void engine::LuaScriptManager::Register<void, const char*, float, float, int, int, bool>(const char*,
	void (*)(const char*, float, float, int, int, bool));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, float, float>(const char*,
	void (*)(engine::LuaGOH, float, float));
template void engine::LuaScriptManager::Register<void, float, float, float, float, float, float, float, float>(const char*,
	void (*)(float, float, float, float, float, float, float, float));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, float, float, float, float>(const char*,
	void (*)(engine::LuaGOH, float, float, float, float));
template void engine::LuaScriptManager::Register<engine::LuaGOH, math::Vector, bool>(const char*,
	engine::LuaGOH (*)(math::Vector, bool));
template void engine::LuaScriptManager::Register<int, math::Vector, math::Vector, int, int, const char*, float>(const char*,
	int (*)(math::Vector, math::Vector, int, int, const char*, float));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, int, int>(const char*,
	void (*)(engine::LuaGOH, int, int));
template void engine::LuaScriptManager::Register<int, engine::LuaGOH, int>(const char*,
	int (*)(engine::LuaGOH, int));
template void engine::LuaScriptManager::Register<void, math::Vector, float>(const char*,
	void (*)(math::Vector, float));
template void engine::LuaScriptManager::Register<void, math::Vector, int, float, bool>(const char*,
	void (*)(math::Vector, int, float, bool));
template void engine::LuaScriptManager::Register<void, math::Vector, math::Vector>(const char*,
	void (*)(math::Vector, math::Vector));
template void engine::LuaScriptManager::Register<void, unsigned int>(const char*,
	void (*)(unsigned int));
template void engine::LuaScriptManager::Register<math::Vector>(const char*,
	math::Vector (*)());
template void engine::LuaScriptManager::Register<engine::LuaGOH>(const char*,
	engine::LuaGOH (*)());
template void engine::LuaScriptManager::Register<bool, engine::LuaGOH, engine::LuaGOH>(const char*,
	bool (*)(engine::LuaGOH, engine::LuaGOH));
template void engine::LuaScriptManager::Register<void, const char*, float>(const char*,
	void (*)(const char*, float));
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, const char*, math::Vector, engine::LuaGOH, const char*, math::Vector>(const char*,
	void (*)(engine::LuaGOH, const char*, math::Vector, engine::LuaGOH, const char*, math::Vector));
template void engine::LuaScriptManager::Register<int, float>(const char*,
	int (*)(float));
template void engine::LuaScriptManager::Register<void, int, const char*>(const char*,
	void (*)(int, const char*));

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10369600
// FUNCTION: ENGINE 0x10369680
// FUNCTION: ENGINE 0x103696C0
// FUNCTION: ENGINE 0x10369700
// FUNCTION: ENGINE 0x10369790
// FUNCTION: ENGINE 0x10369820
// FUNCTION: ENGINE 0x103698C0
// FUNCTION: ENGINE 0x10369920
// FUNCTION: ENGINE 0x10369940
// FUNCTION: ENGINE 0x10369970
// FUNCTION: ENGINE 0x103699E0
// FUNCTION: ENGINE 0x10369A00
// FUNCTION: ENGINE 0x10369A20
// FUNCTION: ENGINE 0x10369AA0
// FUNCTION: ENGINE 0x10369AC0
// FUNCTION: ENGINE 0x10369AF0
// FUNCTION: ENGINE 0x10369B50
// FUNCTION: ENGINE 0x10369B60
// FUNCTION: ENGINE 0x10369B80
// FUNCTION: ENGINE 0x10369BF0
// FUNCTION: ENGINE 0x10369C20
// FUNCTION: ENGINE 0x10369C50
// FUNCTION: ENGINE 0x10369CC0
// FUNCTION: ENGINE 0x10369CF0
// FUNCTION: ENGINE 0x10369D20
// FUNCTION: ENGINE 0x10369DB0
// FUNCTION: ENGINE 0x10369E30
// FUNCTION: ENGINE 0x10369EB0
// FUNCTION: ENGINE 0x10369F40
// FUNCTION: ENGINE 0x10369FA0
// FUNCTION: ENGINE 0x1036A000
// FUNCTION: ENGINE 0x1036A090
// FUNCTION: ENGINE 0x1036A110
// FUNCTION: ENGINE 0x1036A190
// FUNCTION: ENGINE 0x1036A220
// FUNCTION: ENGINE 0x1036A2A0
// FUNCTION: ENGINE 0x1036A320
// FUNCTION: ENGINE 0x1036A3A0
// FUNCTION: ENGINE 0x1036A3F0
// FUNCTION: ENGINE 0x1036A440
// FUNCTION: ENGINE 0x1036A4C0
// FUNCTION: ENGINE 0x1036A4F0
// FUNCTION: ENGINE 0x1036A520
// FUNCTION: ENGINE 0x1036A5A0
// FUNCTION: ENGINE 0x1036A5D0
// FUNCTION: ENGINE 0x1036A600
// FUNCTION: ENGINE 0x1036A670
// FUNCTION: ENGINE 0x1036A6C0
// FUNCTION: ENGINE 0x1036A710
// FUNCTION: ENGINE 0x1036A7A0
// FUNCTION: ENGINE 0x1036A7E0
// FUNCTION: ENGINE 0x1036A820
// FUNCTION: ENGINE 0x1036A880
// FUNCTION: ENGINE 0x1036A8D0
// FUNCTION: ENGINE 0x1036A920
// FUNCTION: ENGINE 0x1036A980
// FUNCTION: ENGINE 0x1036A9D0
// FUNCTION: ENGINE 0x1036AA30
// FUNCTION: ENGINE 0x1036AAB0
// FUNCTION: ENGINE 0x1036AAE0
// FUNCTION: ENGINE 0x1036AB10
// FUNCTION: ENGINE 0x1036AB90
// FUNCTION: ENGINE 0x1036ABC0
// FUNCTION: ENGINE 0x1036ABF0
// FUNCTION: ENGINE 0x1036AC60
// FUNCTION: ENGINE 0x1036AC80
// FUNCTION: ENGINE 0x1036ACA0
// FUNCTION: ENGINE 0x1036AD60
// FUNCTION: ENGINE 0x1036ADB0
// FUNCTION: ENGINE 0x1036AE00
// FUNCTION: ENGINE 0x1036AEC0
// FUNCTION: ENGINE 0x1036AF10
// FUNCTION: ENGINE 0x1036AF60
// FUNCTION: ENGINE 0x1036AFE0
// FUNCTION: ENGINE 0x1036B010
// FUNCTION: ENGINE 0x1036B040
// FUNCTION: ENGINE 0x1036B120
// FUNCTION: ENGINE 0x1036B1B0
// FUNCTION: ENGINE 0x1036B1E0
// FUNCTION: ENGINE 0x1036B280
// FUNCTION: ENGINE 0x1036B2D0
// FUNCTION: ENGINE 0x1036B320
// FUNCTION: ENGINE 0x1036B390
// FUNCTION: ENGINE 0x1036B3F0
// FUNCTION: ENGINE 0x1036B450
// FUNCTION: ENGINE 0x1036B510
// FUNCTION: ENGINE 0x1036B5B0
// FUNCTION: ENGINE 0x1036B660
// FUNCTION: ENGINE 0x1036B6E0
// FUNCTION: ENGINE 0x1036B700
// FUNCTION: ENGINE 0x1036B730
// FUNCTION: ENGINE 0x1036B7A0
// FUNCTION: ENGINE 0x1036B7D0
// FUNCTION: ENGINE 0x1036B800
// FUNCTION: ENGINE 0x1036B870
// FUNCTION: ENGINE 0x1036B8C0
// FUNCTION: ENGINE 0x1036B910
// FUNCTION: ENGINE 0x1036B9A0
// FUNCTION: ENGINE 0x1036BA00
// FUNCTION: ENGINE 0x1036BB20
// FUNCTION: ENGINE 0x1036BB90
// FUNCTION: ENGINE 0x1036BC00
// FUNCTION: ENGINE 0x1036BC70
// FUNCTION: ENGINE 0x1036BCD0
// FUNCTION: ENGINE 0x1036BCE0
// FUNCTION: ENGINE 0x1036BD00
// FUNCTION: ENGINE 0x1036BD50
// FUNCTION: ENGINE 0x1036BDA0
// FUNCTION: ENGINE 0x1036BDF0
// FUNCTION: ENGINE 0x1036BE40
// FUNCTION: ENGINE 0x1036BE60
// FUNCTION: ENGINE 0x1036BE90
// FUNCTION: ENGINE 0x1036BF00
// FUNCTION: ENGINE 0x1036BF30
// FUNCTION: ENGINE 0x1036BF60
// FUNCTION: ENGINE 0x1036BFD0
// FUNCTION: ENGINE 0x1036BFF0
// FUNCTION: ENGINE 0x1036C010
// FUNCTION: ENGINE 0x1036C0D0
// FUNCTION: ENGINE 0x1036C160
// FUNCTION: ENGINE 0x1036C200
// FUNCTION: ENGINE 0x1036C260
// FUNCTION: ENGINE 0x1036C290
// FUNCTION: ENGINE 0x1036C2C0
// FUNCTION: ENGINE 0x1036C330
// FUNCTION: ENGINE 0x1036C350
// FUNCTION: ENGINE 0x10374740
// FUNCTION: ENGINE 0x103747A0
// FUNCTION: ENGINE 0x10374800
// FUNCTION: ENGINE 0x10374890
// FUNCTION: ENGINE 0x103748F0
// FUNCTION: ENGINE 0x10374950
// FUNCTION: ENGINE 0x103749E0
// FUNCTION: ENGINE 0x10374A40
// FUNCTION: ENGINE 0x10374AA0
// FUNCTION: ENGINE 0x10374B00
// FUNCTION: ENGINE 0x10374B60
// FUNCTION: ENGINE 0x10374BC0
// FUNCTION: ENGINE 0x10374C20
// FUNCTION: ENGINE 0x10374C80
// FUNCTION: ENGINE 0x10374CE0
// FUNCTION: ENGINE 0x10374D40
// FUNCTION: ENGINE 0x10374DA0
// FUNCTION: ENGINE 0x10374E00
// FUNCTION: ENGINE 0x10374E90
// FUNCTION: ENGINE 0x10374F20
// FUNCTION: ENGINE 0x10374F80
// FUNCTION: ENGINE 0x10374FE0
// FUNCTION: ENGINE 0x10375040
// FUNCTION: ENGINE 0x103750A0
// FUNCTION: ENGINE 0x10375100
// FUNCTION: ENGINE 0x10375160
// FUNCTION: ENGINE 0x103751C0
// FUNCTION: ENGINE 0x10375220
// FUNCTION: ENGINE 0x10375280
// FUNCTION: ENGINE 0x103752E0
// FUNCTION: ENGINE 0x10375340
// FUNCTION: ENGINE 0x103753A0
// FUNCTION: ENGINE 0x10375400
// FUNCTION: ENGINE 0x103754C0
// FUNCTION: ENGINE 0x10375520
// FUNCTION: ENGINE 0x103755B0
// FUNCTION: ENGINE 0x10375630
// FUNCTION: ENGINE 0x103756B0
// FUNCTION: ENGINE 0x10375710
// FUNCTION: ENGINE 0x10375770
// FUNCTION: ENGINE 0x103757D0
// FUNCTION: ENGINE 0x10375860
