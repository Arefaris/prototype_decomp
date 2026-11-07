// Globals that the engine's static initialisers 0x10D5C400 - 0x10D5EFF0 construct in translation units whose code is not
// reconstructed: the radio dialogue names and the helicopter and vehicle audio parameter keys, and the names and strings every such unit repeats through its headers (the
// slot group names, the audio file and listener names). Unit name guess; one file holds the runs of several units.
#include "code/core/name.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/om/staticinit.h"

namespace engine
{
	core::Name<core::CaseSensitiveKey> gPlay3("play", 0);
	core::Name<core::CaseSensitiveKey> gWinddown2("winddown", 0);
	core::Name<core::CaseSensitiveKey> gStop2("stop", 0);
	om::ClassName gStartupSound = om::NameOfText("startup_sound");
	om::ClassName gRotorSound = om::NameOfText("rotor_sound");
	om::ClassName gEngineSound = om::NameOfText("engine_sound");
	om::ClassName gJetSound = om::NameOfText("jet_sound");
	om::ClassName gWinddownSound = om::NameOfText("winddown_sound");
	om::ClassName gBusses = om::NameOfText("busses");
	om::ClassName gThrottle = om::NameOfText("throttle");
	om::ClassName gVelocity = om::NameOfText("velocity");
	om::ClassName gMin = om::NameOfText("min");
	om::ClassName gMax = om::NameOfText("max");
	om::ClassName gXfadeMs = om::NameOfText("xfade_ms");
	om::ClassName gRotorsVolume = om::NameOfText("rotors_volume");
	om::ClassName gJetVolume = om::NameOfText("jet_volume");
	om::ClassName gEngineVolume = om::NameOfText("engine_volume");
	om::ClassName gStartupWinddownVolume = om::NameOfText("startup_winddown_volume");
	om::ClassName gVelocityPitchMap = om::NameOfText("velocity_pitch_map");
	om::ClassName gThrottlePitchMap = om::NameOfText("throttle_pitch_map");
	om::ClassName gLoop3 = om::NameOfText("loop");
	om::ClassName gGroup2 = om::NameOfText("group");
	om::ClassName gVelocitySmoothUp = om::NameOfText("velocity_smooth_up");
	om::ClassName gVelocitySmoothDown = om::NameOfText("velocity_smooth_down");
	om::ClassName gThrottleSmoothUp = om::NameOfText("throttle_smooth_up");
	om::ClassName gThrottleSmoothDown = om::NameOfText("throttle_smooth_down");
	om::ClassName gReverbSend2 = om::NameOfText("reverb_send");
	om::ClassName gRotorDamageFile = om::NameOfText("rotor_damage_file");
	om::ClassName gAlarmDamageFile = om::NameOfText("alarm_damage_file");
	om::ClassName gRotorDamageVol = om::NameOfText("rotor_damage_vol");
	om::ClassName gAlarmDamageVol = om::NameOfText("alarm_damage_vol");
	om::ClassName gRotorDamage = om::NameOfText("rotor_damage");
	om::ClassName gAlarmDamage = om::NameOfText("alarm_damage");
	om::ClassName gDisabled = om::NameOfText("disabled");
	core::Name<core::CaseSensitiveKey> gStartup2("startup", 0);
	core::Name<core::CaseSensitiveKey> gWinddown3("winddown", 0);
	core::Name<core::CaseSensitiveKey> gIdle2("idle", 0);
	core::Name<core::CaseSensitiveKey> gStop3("stop", 0);
	om::ClassName gStartupSound2 = om::NameOfText("startup_sound");
	om::ClassName gIdleSound = om::NameOfText("idle_sound");
	om::ClassName gMoveSound = om::NameOfText("move_sound");
	om::ClassName gWinddownSound2 = om::NameOfText("winddown_sound");
	om::ClassName gBusnames = om::NameOfText("busnames");
	om::ClassName gRpm2 = om::NameOfText("rpm");
	om::ClassName gTurnValue2 = om::NameOfText("turn_value");
	om::ClassName gMin2 = om::NameOfText("min");
	om::ClassName gMax2 = om::NameOfText("max");
	om::ClassName gMoveFadeTime = om::NameOfText("move_fade_time");
	om::ClassName gIdleVol = om::NameOfText("idle_vol");
	om::ClassName gRpmMap = om::NameOfText("rpm_map");
	om::ClassName gTurnMap = om::NameOfText("turn_map");
	om::ClassName gLoop4 = om::NameOfText("loop");
	om::ClassName gGroup3 = om::NameOfText("group");
	om::ClassName gReverbSend3 = om::NameOfText("reverb_send");
	om::ClassName gIdleSmoothUp = om::NameOfText("idle_smooth_up");
	om::ClassName gIdleSmoothDown = om::NameOfText("idle_smooth_down");
	om::ClassName gRpmSmoothUp = om::NameOfText("rpm_smooth_up");
	om::ClassName gRpmSmoothDown = om::NameOfText("rpm_smooth_down");
	MessageListeners gScenario85("scenario", 0);
}

// The dynamic initialisers and atexit stubs of the unit's globals:
// FUNCTION: ENGINE 0x10D5DB80
// FUNCTION: ENGINE 0x10D5DBB0
// FUNCTION: ENGINE 0x10D5DBE0
// FUNCTION: ENGINE 0x10D5DC10
// FUNCTION: ENGINE 0x10D5DC70
// FUNCTION: ENGINE 0x10D5DCD0
// FUNCTION: ENGINE 0x10D5DD30
// FUNCTION: ENGINE 0x10D5DD90
// FUNCTION: ENGINE 0x10D5DDF0
// FUNCTION: ENGINE 0x10D5DE50
// FUNCTION: ENGINE 0x10D5DEB0
// FUNCTION: ENGINE 0x10D5DF10
// FUNCTION: ENGINE 0x10D5DF70
// FUNCTION: ENGINE 0x10D5DFD0
// FUNCTION: ENGINE 0x10D5E030
// FUNCTION: ENGINE 0x10D5E090
// FUNCTION: ENGINE 0x10D5E0F0
// FUNCTION: ENGINE 0x10D5E150
// FUNCTION: ENGINE 0x10D5E1B0
// FUNCTION: ENGINE 0x10D5E210
// FUNCTION: ENGINE 0x10D5E270
// FUNCTION: ENGINE 0x10D5E2D0
// FUNCTION: ENGINE 0x10D5E330
// FUNCTION: ENGINE 0x10D5E390
// FUNCTION: ENGINE 0x10D5E3F0
// FUNCTION: ENGINE 0x10D5E450
// FUNCTION: ENGINE 0x10D5E4B0
// FUNCTION: ENGINE 0x10D5E510
// FUNCTION: ENGINE 0x10D5E570
// FUNCTION: ENGINE 0x10D5E5D0
// FUNCTION: ENGINE 0x10D5E630
// FUNCTION: ENGINE 0x10D5E690
// FUNCTION: ENGINE 0x10D5E6F0
// FUNCTION: ENGINE 0x10D5E750
// FUNCTION: ENGINE 0x10D5E7B0
// FUNCTION: ENGINE 0x10D5E7E0
// FUNCTION: ENGINE 0x10D5E810
// FUNCTION: ENGINE 0x10D5E840
// FUNCTION: ENGINE 0x10D5E870
// FUNCTION: ENGINE 0x10D5E8D0
// FUNCTION: ENGINE 0x10D5E930
// FUNCTION: ENGINE 0x10D5E990
// FUNCTION: ENGINE 0x10D5E9F0
// FUNCTION: ENGINE 0x10D5EA50
// FUNCTION: ENGINE 0x10D5EAB0
// FUNCTION: ENGINE 0x10D5EB10
// FUNCTION: ENGINE 0x10D5EB70
// FUNCTION: ENGINE 0x10D5EBD0
// FUNCTION: ENGINE 0x10D5EC30
// FUNCTION: ENGINE 0x10D5EC90
// FUNCTION: ENGINE 0x10D5ECF0
// FUNCTION: ENGINE 0x10D5ED50
// FUNCTION: ENGINE 0x10D5EDB0
// FUNCTION: ENGINE 0x10D5EE10
// FUNCTION: ENGINE 0x10D5EE70
// FUNCTION: ENGINE 0x10D5EED0
// FUNCTION: ENGINE 0x10D5EF30
// FUNCTION: ENGINE 0x10D5EF90
// FUNCTION: ENGINE 0x10D5EFF0
// FUNCTION: ENGINE 0x10D852A0
// FUNCTION: ENGINE 0x10D852B0
// FUNCTION: ENGINE 0x10D852C0
// FUNCTION: ENGINE 0x10D852D0
// FUNCTION: ENGINE 0x10D852E0
// FUNCTION: ENGINE 0x10D852F0
// FUNCTION: ENGINE 0x10D85300
// FUNCTION: ENGINE 0x10D85310
