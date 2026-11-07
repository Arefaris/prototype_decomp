// Globals that the engine's static initialisers 0x10D5B320 - 0x10D5C2E0 construct in translation units whose code is not
// reconstructed: the audio mix, bus and volume names, and the names and strings every such unit repeats through its headers (the
// slot group names, the audio file and listener names). Unit name guess; one file holds the runs of several units.
#include "code/core/name.h"
#include "code/om/staticinit.h"

namespace engine
{
	core::Name<core::CaseSensitiveKey> gVehicle("Vehicle", 0);
	core::Name<core::CaseSensitiveKey> gPauseMenu("pause_menu", 0);
	core::Name<core::CaseSensitiveKey> gFrontEnd2("front_end", 0);
	core::Name<core::CaseSensitiveKey> gFadeToBlack("fade_to_black", 0);
	core::Name<core::CaseSensitiveKey> gHudDucker("hud_ducker", 0);
	core::Name<core::CaseSensitiveKey> gTextbox("textbox", 0);
	core::Name<core::CaseSensitiveKey> gThermalMix("thermal_mix", 0);
	core::Name<core::CaseSensitiveKey> gInfectedMix("infected_mix", 0);
	core::Name<core::CaseSensitiveKey> gBloodtoxMix("bloodtox_mix", 0);
	core::Name<core::CaseSensitiveKey> gThermalVision("thermal_vision", 0);
	core::Name<core::CaseSensitiveKey> gInfectedVision("infected_vision", 0);
	core::Name<core::CaseSensitiveKey> gUiHudPoisonEffect("ui_hud_poison_effect", 0);
	core::Name<core::CaseSensitiveKey> gCreditsMix("credits_mix", 0);
	core::Name<core::CaseSensitiveKey> gFeSoundsDuck("fe_sounds_duck", 0);
	core::Name<core::CaseSensitiveKey> gScriptedSequence("scripted_sequence", 0);
	core::Name<core::CaseSensitiveKey> gUiHudAdrenalineBoost("ui_hud_adrenaline_boost", 0);
	core::Name<core::CaseSensitiveKey> gUiHudCriticalMassFull("ui_hud_critical_mass_full", 0);
	core::Name<core::CaseSensitiveKey> gUiHudRubberStamp("ui_hud_rubber_stamp", 0);
	core::Name<core::CaseSensitiveKey> gCredits("credits", 0);
	core::Name<core::CaseSensitiveKey> gAmbience("ambience", 0);
	core::Name<core::CaseSensitiveKey> gReverbSend("reverb_send", 0);
	core::Name<core::CaseSensitiveKey> gCrowdPanicVol("crowd_panic_vol", 0);
	core::Name<core::CaseSensitiveKey> gCrowdLocalVol("crowd_local_vol", 0);
	core::Name<core::CaseSensitiveKey> gTrafficIdleVol("traffic_idle_vol", 0);
	core::Name<core::CaseSensitiveKey> gTrafficPanicVol("traffic_panic_vol", 0);
	core::Name<core::CaseSensitiveKey> gRooftopVolume("rooftop_volume", 0);
	core::Name<core::CaseSensitiveKey> gInfectedVol("infected_vol", 0);
	core::Name<core::CaseSensitiveKey> gInfectedLocalVol("infected_local_vol", 0);
	core::Name<core::CaseSensitiveKey> gCityVol("city_vol", 0);
	core::Name<core::CaseSensitiveKey> gParkVol("park_vol", 0);
	core::Name<core::CaseSensitiveKey> gDistanceFilter("distance_filter", 0);
	core::Name<core::CaseSensitiveKey> gWorldPointDistance("world_point_distance", 0);
	core::Name<core::CaseSensitiveKey> gWorldPointRadius("world_point_radius", 0);
	core::Name<core::CaseSensitiveKey> gMultichanVolumeLeak("multichan_volume_leak", 0);
	core::Name<core::CaseSensitiveKey> gRooftopOffset("rooftop_offset", 0);
	core::Name<core::CaseSensitiveKey> gMinRadius2("min_radius", 0);
	core::Name<core::CaseSensitiveKey> gInfectedZoneMinVolume("infected_zone_min_volume", 0);
	core::Name<core::CaseSensitiveKey> gListenerYOffsetMax("listener_y_offset_max", 0);
	core::Name<core::CaseSensitiveKey> gListenerMoveConst("listener_move_const", 0);
	core::Name<core::CaseSensitiveKey> gInfUp("inf_up", 0);
	core::Name<core::CaseSensitiveKey> gInfDown("inf_down", 0);
	core::Name<core::CaseSensitiveKey> gInfUpChannel("inf_up_channel", 0);
	core::Name<core::CaseSensitiveKey> gInfDownChannel("inf_down_channel", 0);
	core::Name<core::CaseSensitiveKey> gCrowdUp("crowd_up", 0);
	core::Name<core::CaseSensitiveKey> gCrowdDown("crowd_down", 0);
	core::Name<core::CaseSensitiveKey> gCrowdUpChannel("crowd_up_channel", 0);
	core::Name<core::CaseSensitiveKey> gCrowdDownChannel("crowd_down_channel", 0);
	core::Name<core::CaseSensitiveKey> gMedSphereMult("med_sphere_mult", 0);
	core::Name<core::CaseSensitiveKey> gSmallSphereMult("small_sphere_mult", 0);
	core::Name<core::CaseSensitiveKey> gEmpty243("", 0);
	core::Name<core::CaseSensitiveKey> gFe2("fe", 0);
	core::Name<core::CaseSensitiveKey> gFrontEnd3("front_end", 0);
	core::Name<core::CaseSensitiveKey> gDrone("drone", 0);
	core::Name<core::CaseSensitiveKey> gMusic("music", 0);
	core::Name<core::CaseSensitiveKey> gInfRfMult("inf_rf_mult", 0);
	core::Name<core::CaseSensitiveKey> gInfRsMult("inf_rs_mult", 0);
	core::Name<core::CaseSensitiveKey> gInfLsMult("inf_ls_mult", 0);
	core::Name<core::CaseSensitiveKey> gInfLfMult("inf_lf_mult", 0);
	core::Name<core::CaseSensitiveKey> gCrowdRfMult("crowd_rf_mult", 0);
	core::Name<core::CaseSensitiveKey> gCrowdRsMult("crowd_rs_mult", 0);
	core::Name<core::CaseSensitiveKey> gCrowdLsMult("crowd_ls_mult", 0);
	core::Name<core::CaseSensitiveKey> gCrowdLfMult("crowd_lf_mult", 0);
	core::Name<core::CaseSensitiveKey> gIdleRfMult("idle_rf_mult", 0);
	core::Name<core::CaseSensitiveKey> gIdleRsMult("idle_rs_mult", 0);
	core::Name<core::CaseSensitiveKey> gIdleLsMult("idle_ls_mult", 0);
	core::Name<core::CaseSensitiveKey> gIdleLfMult("idle_lf_mult", 0);
	core::Name<core::CaseSensitiveKey> gInfLocalRfMult("inf_local_rf_mult", 0);
	core::Name<core::CaseSensitiveKey> gInfLocalRsMult("inf_local_rs_mult", 0);
	core::Name<core::CaseSensitiveKey> gInfLocalLsMult("inf_local_ls_mult", 0);
	core::Name<core::CaseSensitiveKey> gInfLocalLfMult("inf_local_lf_mult", 0);
	core::Name<core::CaseSensitiveKey> gCrowdLocalRfMult("crowd_local_rf_mult", 0);
	core::Name<core::CaseSensitiveKey> gCrowdLocalRsMult("crowd_local_rs_mult", 0);
	core::Name<core::CaseSensitiveKey> gCrowdLocalLsMult("crowd_local_ls_mult", 0);
	core::Name<core::CaseSensitiveKey> gCrowdLocalLfMult("crowd_local_lf_mult", 0);
	core::Name<core::CaseSensitiveKey> gDefaultText("default_text", 0);
	om::ClassName gRadiodialogue = om::NameOfText("radiodialogue");
	om::ClassName gPositionalradio = om::NameOfText("positionalradio");
	om::ClassName gMissionradiodialogue = om::NameOfText("missionradiodialogue");
	core::Name<core::CaseSensitiveKey> gWalkieSquelch2D("walkie_squelch2D", 0);
	core::Name<core::CaseSensitiveKey> gWalkieSquelch3D("walkie_squelch3D", 0);
}

// The dynamic initialisers and atexit stubs of the unit's globals:
// FUNCTION: ENGINE 0x10D5B320
// FUNCTION: ENGINE 0x10D5B350
// FUNCTION: ENGINE 0x10D5B380
// FUNCTION: ENGINE 0x10D5B3B0
// FUNCTION: ENGINE 0x10D5B3E0
// FUNCTION: ENGINE 0x10D5B410
// FUNCTION: ENGINE 0x10D5B440
// FUNCTION: ENGINE 0x10D5B470
// FUNCTION: ENGINE 0x10D5B4A0
// FUNCTION: ENGINE 0x10D5B4D0
// FUNCTION: ENGINE 0x10D5B500
// FUNCTION: ENGINE 0x10D5B530
// FUNCTION: ENGINE 0x10D5B560
// FUNCTION: ENGINE 0x10D5B590
// FUNCTION: ENGINE 0x10D5B5C0
// FUNCTION: ENGINE 0x10D5B5F0
// FUNCTION: ENGINE 0x10D5B620
// FUNCTION: ENGINE 0x10D5B650
// FUNCTION: ENGINE 0x10D5B680
// FUNCTION: ENGINE 0x10D5B6B0
// FUNCTION: ENGINE 0x10D5B6E0
// FUNCTION: ENGINE 0x10D5B710
// FUNCTION: ENGINE 0x10D5B740
// FUNCTION: ENGINE 0x10D5B770
// FUNCTION: ENGINE 0x10D5B7A0
// FUNCTION: ENGINE 0x10D5B7D0
// FUNCTION: ENGINE 0x10D5B800
// FUNCTION: ENGINE 0x10D5B830
// FUNCTION: ENGINE 0x10D5B860
// FUNCTION: ENGINE 0x10D5B890
// FUNCTION: ENGINE 0x10D5B8C0
// FUNCTION: ENGINE 0x10D5B8F0
// FUNCTION: ENGINE 0x10D5B920
// FUNCTION: ENGINE 0x10D5B950
// FUNCTION: ENGINE 0x10D5B980
// FUNCTION: ENGINE 0x10D5B9B0
// FUNCTION: ENGINE 0x10D5B9E0
// FUNCTION: ENGINE 0x10D5BA10
// FUNCTION: ENGINE 0x10D5BA40
// FUNCTION: ENGINE 0x10D5BA70
// FUNCTION: ENGINE 0x10D5BAA0
// FUNCTION: ENGINE 0x10D5BAD0
// FUNCTION: ENGINE 0x10D5BB00
// FUNCTION: ENGINE 0x10D5BB30
// FUNCTION: ENGINE 0x10D5BB60
// FUNCTION: ENGINE 0x10D5BB90
// FUNCTION: ENGINE 0x10D5BBC0
// FUNCTION: ENGINE 0x10D5BBF0
// FUNCTION: ENGINE 0x10D5BC20
// FUNCTION: ENGINE 0x10D5BC50
// FUNCTION: ENGINE 0x10D5BC80
// FUNCTION: ENGINE 0x10D5BCB0
// FUNCTION: ENGINE 0x10D5BCE0
// FUNCTION: ENGINE 0x10D5BD10
// FUNCTION: ENGINE 0x10D5BD40
// FUNCTION: ENGINE 0x10D5BD70
// FUNCTION: ENGINE 0x10D5BDA0
// FUNCTION: ENGINE 0x10D5BDD0
// FUNCTION: ENGINE 0x10D5BE00
// FUNCTION: ENGINE 0x10D5BE30
// FUNCTION: ENGINE 0x10D5BE60
// FUNCTION: ENGINE 0x10D5BE90
// FUNCTION: ENGINE 0x10D5BEC0
// FUNCTION: ENGINE 0x10D5BEF0
// FUNCTION: ENGINE 0x10D5BF20
// FUNCTION: ENGINE 0x10D5BF50
// FUNCTION: ENGINE 0x10D5BF80
// FUNCTION: ENGINE 0x10D5BFB0
// FUNCTION: ENGINE 0x10D5BFE0
// FUNCTION: ENGINE 0x10D5C010
// FUNCTION: ENGINE 0x10D5C040
// FUNCTION: ENGINE 0x10D5C070
// FUNCTION: ENGINE 0x10D5C0A0
// FUNCTION: ENGINE 0x10D5C0D0
// FUNCTION: ENGINE 0x10D5C110
// FUNCTION: ENGINE 0x10D5C160
// FUNCTION: ENGINE 0x10D5C1C0
// FUNCTION: ENGINE 0x10D5C220
// FUNCTION: ENGINE 0x10D5C280
// FUNCTION: ENGINE 0x10D5C2B0
// FUNCTION: ENGINE 0x10D84DA0
// FUNCTION: ENGINE 0x10D84DB0
// FUNCTION: ENGINE 0x10D84DC0
// FUNCTION: ENGINE 0x10D84DD0
// FUNCTION: ENGINE 0x10D84DE0
// FUNCTION: ENGINE 0x10D84DF0
// FUNCTION: ENGINE 0x10D84E00
// FUNCTION: ENGINE 0x10D84E10
// FUNCTION: ENGINE 0x10D84E20
// FUNCTION: ENGINE 0x10D84E30
// FUNCTION: ENGINE 0x10D84E40
// FUNCTION: ENGINE 0x10D84E50
// FUNCTION: ENGINE 0x10D84E60
// FUNCTION: ENGINE 0x10D84E70
// FUNCTION: ENGINE 0x10D84E80
// FUNCTION: ENGINE 0x10D84E90
// FUNCTION: ENGINE 0x10D84EA0
// FUNCTION: ENGINE 0x10D84EB0
// FUNCTION: ENGINE 0x10D84EC0
// FUNCTION: ENGINE 0x10D84ED0
// FUNCTION: ENGINE 0x10D84EE0
// FUNCTION: ENGINE 0x10D84EF0
// FUNCTION: ENGINE 0x10D84F00
// FUNCTION: ENGINE 0x10D84F10
// FUNCTION: ENGINE 0x10D84F20
// FUNCTION: ENGINE 0x10D84F30
// FUNCTION: ENGINE 0x10D84F40
// FUNCTION: ENGINE 0x10D84F50
// FUNCTION: ENGINE 0x10D84F60
// FUNCTION: ENGINE 0x10D84F70
// FUNCTION: ENGINE 0x10D84F80
// FUNCTION: ENGINE 0x10D84F90
// FUNCTION: ENGINE 0x10D84FA0
// FUNCTION: ENGINE 0x10D84FB0
// FUNCTION: ENGINE 0x10D84FC0
// FUNCTION: ENGINE 0x10D84FD0
// FUNCTION: ENGINE 0x10D84FE0
// FUNCTION: ENGINE 0x10D84FF0
// FUNCTION: ENGINE 0x10D85000
// FUNCTION: ENGINE 0x10D85010
// FUNCTION: ENGINE 0x10D85020
// FUNCTION: ENGINE 0x10D85030
// FUNCTION: ENGINE 0x10D85040
// FUNCTION: ENGINE 0x10D85050
// FUNCTION: ENGINE 0x10D85060
// FUNCTION: ENGINE 0x10D85070
// FUNCTION: ENGINE 0x10D85080
// FUNCTION: ENGINE 0x10D85090
// FUNCTION: ENGINE 0x10D850A0
// FUNCTION: ENGINE 0x10D850B0
// FUNCTION: ENGINE 0x10D850C0
// FUNCTION: ENGINE 0x10D850D0
// FUNCTION: ENGINE 0x10D850E0
// FUNCTION: ENGINE 0x10D850F0
// FUNCTION: ENGINE 0x10D85100
// FUNCTION: ENGINE 0x10D85110
// FUNCTION: ENGINE 0x10D85120
// FUNCTION: ENGINE 0x10D85130
// FUNCTION: ENGINE 0x10D85140
// FUNCTION: ENGINE 0x10D85150
// FUNCTION: ENGINE 0x10D85160
// FUNCTION: ENGINE 0x10D85170
// FUNCTION: ENGINE 0x10D85180
// FUNCTION: ENGINE 0x10D85190
// FUNCTION: ENGINE 0x10D851A0
// FUNCTION: ENGINE 0x10D851B0
// FUNCTION: ENGINE 0x10D851C0
// FUNCTION: ENGINE 0x10D851D0
// FUNCTION: ENGINE 0x10D851E0
// FUNCTION: ENGINE 0x10D851F0
// FUNCTION: ENGINE 0x10D85200
// FUNCTION: ENGINE 0x10D85210
// FUNCTION: ENGINE 0x10D85220
// FUNCTION: ENGINE 0x10D85230
// FUNCTION: ENGINE 0x10D85240
// FUNCTION: ENGINE 0x10D85250
// FUNCTION: ENGINE 0x10D85260
