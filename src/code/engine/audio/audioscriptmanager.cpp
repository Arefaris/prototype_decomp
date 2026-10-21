// The scripts' access to the audio system (see the header). The unit instantiates the script method wrappers
// (engine::Function's Method and Closure templates) for the signatures of the snd_* functions.
#include "code/engine/audio/audioscriptmanager.h"

#include "code/engine/function.h"

namespace engine
{
	AudioScriptManager* gAudioScriptManager;  // 0x11318928
}

template class Method0<engine::AudioScriptManager, void>;
template class Closure0<engine::AudioScriptManager, void>;
template class Method1<engine::AudioScriptManager, void, bool>;
template class Method2<engine::AudioScriptManager, void, const char*, const char*>;
template class Method3<engine::AudioScriptManager, void, const char*, const char*, engine::LuaGOH>;
template class Method1<engine::AudioScriptManager, void, const char*>;
template class Method1<engine::AudioScriptManager, void, float>;
template class Method3<engine::AudioScriptManager, void, const char*, unsigned int, unsigned int>;
template class Method2<engine::AudioScriptManager, void, const char*, bool>;
template class Method4<engine::AudioScriptManager, void, const char*, const char*, int, bool>;
template class Method3<engine::AudioScriptManager, void, float, float, float>;
template class Method4<engine::AudioScriptManager, void, engine::LuaGOH, char*, char*, char*>;
template class Method7<engine::AudioScriptManager, void, char*, char*, char*, float, float, char*, char*>;
template class Method8<engine::AudioScriptManager, void, engine::LuaGOH, char*, char*, char*, float, float, char*, char*>;
template class Method4<engine::AudioScriptManager, void, const char*, const char*, bool, float>;
template class Method0<engine::AudioScriptManager, float>;
template class Closure1<engine::AudioScriptManager, void, bool>;
template class Closure2<engine::AudioScriptManager, void, const char*, const char*>;
template class Closure3<engine::AudioScriptManager, void, const char*, const char*, engine::LuaGOH>;
template class Closure1<engine::AudioScriptManager, void, const char*>;
template class Closure1<engine::AudioScriptManager, void, float>;
template class Closure3<engine::AudioScriptManager, void, const char*, unsigned int, unsigned int>;
template class Closure2<engine::AudioScriptManager, void, const char*, bool>;
template class Closure4<engine::AudioScriptManager, void, const char*, const char*, int, bool>;
template class Closure3<engine::AudioScriptManager, void, float, float, float>;
template class Closure4<engine::AudioScriptManager, void, engine::LuaGOH, char*, char*, char*>;
template class Closure7<engine::AudioScriptManager, void, char*, char*, char*, float, float, char*, char*>;
template class Closure8<engine::AudioScriptManager, void, engine::LuaGOH, char*, char*, char*, float, float, char*, char*>;
template class Closure4<engine::AudioScriptManager, void, const char*, const char*, bool, float>;
template class Closure0<engine::AudioScriptManager, float>;

template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void>(const char*,
	engine::AudioScriptManager*, void (engine::AudioScriptManager::*)());
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, bool>(const char*,
	engine::AudioScriptManager*, void (engine::AudioScriptManager::*)(bool));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, const char*, const char*>(
	const char*, engine::AudioScriptManager*, void (engine::AudioScriptManager::*)(const char*, const char*));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, const char*, const char*,
	engine::LuaGOH>(const char*, engine::AudioScriptManager*,
	void (engine::AudioScriptManager::*)(const char*, const char*, engine::LuaGOH));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, const char*>(const char*,
	engine::AudioScriptManager*, void (engine::AudioScriptManager::*)(const char*));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, float>(const char*,
	engine::AudioScriptManager*, void (engine::AudioScriptManager::*)(float));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, const char*, unsigned int,
	unsigned int>(const char*, engine::AudioScriptManager*,
	void (engine::AudioScriptManager::*)(const char*, unsigned int, unsigned int));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, const char*, bool>(
	const char*, engine::AudioScriptManager*, void (engine::AudioScriptManager::*)(const char*, bool));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, const char*, const char*,
	int, bool>(const char*, engine::AudioScriptManager*,
	void (engine::AudioScriptManager::*)(const char*, const char*, int, bool));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, float, float, float>(
	const char*, engine::AudioScriptManager*, void (engine::AudioScriptManager::*)(float, float, float));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, engine::LuaGOH, char*,
	char*, char*>(const char*, engine::AudioScriptManager*,
	void (engine::AudioScriptManager::*)(engine::LuaGOH, char*, char*, char*));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, char*, char*, char*, float,
	float, char*, char*>(const char*, engine::AudioScriptManager*,
	void (engine::AudioScriptManager::*)(char*, char*, char*, float, float, char*, char*));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, engine::LuaGOH, char*,
	char*, char*, float, float, char*, char*>(const char*, engine::AudioScriptManager*,
	void (engine::AudioScriptManager::*)(engine::LuaGOH, char*, char*, char*, float, float, char*, char*));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, const char*, const char*,
	bool, float>(const char*, engine::AudioScriptManager*,
	void (engine::AudioScriptManager::*)(const char*, const char*, bool, float));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, float>(const char*,
	engine::AudioScriptManager*, float (engine::AudioScriptManager::*)());

// The wrappers and registrations this unit instantiates, in address order:
// FUNCTION: ENGINE 0x108D1320
// FUNCTION: ENGINE 0x108D1360
// FUNCTION: ENGINE 0x108D1780
// FUNCTION: ENGINE 0x108D17D0
// FUNCTION: ENGINE 0x108D17E0
// FUNCTION: ENGINE 0x108D1830
// FUNCTION: ENGINE 0x108D1850
// FUNCTION: ENGINE 0x108D1870
// FUNCTION: ENGINE 0x108D18D0
// FUNCTION: ENGINE 0x108D18F0
// FUNCTION: ENGINE 0x108D1910
// FUNCTION: ENGINE 0x108D1980
// FUNCTION: ENGINE 0x108D19A0
// FUNCTION: ENGINE 0x108D19C0
// FUNCTION: ENGINE 0x108D1A10
// FUNCTION: ENGINE 0x108D1A20
// FUNCTION: ENGINE 0x108D1A40
// FUNCTION: ENGINE 0x108D1A90
// FUNCTION: ENGINE 0x108D1AB0
// FUNCTION: ENGINE 0x108D1AD0
// FUNCTION: ENGINE 0x108D1B40
// FUNCTION: ENGINE 0x108D1B60
// FUNCTION: ENGINE 0x108D1B80
// FUNCTION: ENGINE 0x108D1BE0
// FUNCTION: ENGINE 0x108D1C00
// FUNCTION: ENGINE 0x108D1C20
// FUNCTION: ENGINE 0x108D1CC0
// FUNCTION: ENGINE 0x108D1CF0
// FUNCTION: ENGINE 0x108D1D60
// FUNCTION: ENGINE 0x108D1D90
// FUNCTION: ENGINE 0x108D1DC0
// FUNCTION: ENGINE 0x108D1E60
// FUNCTION: ENGINE 0x108D1E90
// FUNCTION: ENGINE 0x108D1F30
// FUNCTION: ENGINE 0x108D1F80
// FUNCTION: ENGINE 0x108D1FD0
// FUNCTION: ENGINE 0x108D2080
// FUNCTION: ENGINE 0x108D20D0
// FUNCTION: ENGINE 0x108D2130
// FUNCTION: ENGINE 0x108D21D0
// FUNCTION: ENGINE 0x108D2200
// FUNCTION: ENGINE 0x108D2240
// FUNCTION: ENGINE 0x108D2260
// FUNCTION: ENGINE 0x108D23A0
// FUNCTION: ENGINE 0x108D2410
// FUNCTION: ENGINE 0x108D2460
// FUNCTION: ENGINE 0x108D2480
// FUNCTION: ENGINE 0x108D24B0
// FUNCTION: ENGINE 0x108D24D0
// FUNCTION: ENGINE 0x108D2500
// FUNCTION: ENGINE 0x108D2520
// FUNCTION: ENGINE 0x108D2570
// FUNCTION: ENGINE 0x108D2590
// FUNCTION: ENGINE 0x108D25E0
// FUNCTION: ENGINE 0x108D2600
// FUNCTION: ENGINE 0x108D2630
// FUNCTION: ENGINE 0x108D2650
// FUNCTION: ENGINE 0x108D2680
// FUNCTION: ENGINE 0x108D26A0
// FUNCTION: ENGINE 0x108D26B0
// FUNCTION: ENGINE 0x108D26E0
// FUNCTION: ENGINE 0x108D2710
// FUNCTION: ENGINE 0x108D2740
// FUNCTION: ENGINE 0x108D2770
// FUNCTION: ENGINE 0x108D27A0
// FUNCTION: ENGINE 0x108D27D0
// FUNCTION: ENGINE 0x108D2800
// FUNCTION: ENGINE 0x108D2850
// FUNCTION: ENGINE 0x108D2880
// FUNCTION: ENGINE 0x108D2890
// FUNCTION: ENGINE 0x108D28C0
// FUNCTION: ENGINE 0x108D28F0
// FUNCTION: ENGINE 0x108D2940
// FUNCTION: ENGINE 0x108D2970
// FUNCTION: ENGINE 0x108D29C0
// FUNCTION: ENGINE 0x108D2A20
// FUNCTION: ENGINE 0x108D2A80
// FUNCTION: ENGINE 0x108D2AD0
// FUNCTION: ENGINE 0x108D2B20
// FUNCTION: ENGINE 0x108D2B80
// FUNCTION: ENGINE 0x108D2BE0
// FUNCTION: ENGINE 0x108D2C40
// FUNCTION: ENGINE 0x108D2CA0
// FUNCTION: ENGINE 0x108D2D00
// FUNCTION: ENGINE 0x108D2D60
// FUNCTION: ENGINE 0x108D2DC0
// FUNCTION: ENGINE 0x108D2E20
