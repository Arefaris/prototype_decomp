// Globals that the engine's static initialisers 0x10D78260 - 0x10D7A040 construct in translation units whose code is not
// reconstructed: the fade, audio settings and collision audio names, and the names and strings every such unit repeats through its headers (the
// slot group names, the audio file and listener names). Unit name guess; one file holds the runs of several units.
#include "code/core/name.h"
#include "code/core/time.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/om/staticinit.h"
#include "code/om/string.h"
#include "code/om/tree.h"
#include "code/math/matrix.h"

namespace engine
{
	core::Name<core::CaseSensitiveKey> gEnable("enable", 0);
	fight::EnumEntry gFadeToBlackTable[6] =
	{
		{ fight::Name("Fade to black", 0) },
		{ fight::Name("Fade from black", 0) },
		{ fight::Name("Fade to white", 0) },
		{ fight::Name("Fade from white", 0) },
		{ fight::Name("Saturate to white", 0) },
		{ fight::Name("Desaturate from white", 0) }
	};
	core::Time gZeroTime3(0, 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup74("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty82("", 0);
	MessageListeners gScenario22("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup75("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty83("", 0);
	om::String gAudioGlobalP3d19 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener20 = om::NameOfText("Listener");
	om::ClassName gMaster20 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup76("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty84("", 0);
	om::String gAudioSettingsManager("AudioSettingsManager", 0);
	om::String gAudioGlobalP3d20 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener21 = om::NameOfText("Listener");
	om::ClassName gMaster21 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gAudioCollisionType("audioCollisionType", 0);
	om::ClassName gMinRetriggerTime = om::NameOfText("min_retrigger_time");
	om::ClassName gMaxRetriggerTime = om::NameOfText("max_retrigger_time");
	om::ClassName gMinImpulse = om::NameOfText("min_impulse");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup77("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty85("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup78("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty86("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup79("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty87("", 0);
	om::String gAudioGlobalP3d21 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener22 = om::NameOfText("Listener");
	om::ClassName gMaster22 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup80("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty88("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup81("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty89("", 0);
	om::String gAudioGlobalP3d22 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener23 = om::NameOfText("Listener");
	om::ClassName gMaster23 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup82("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty90("", 0);
	MessageListeners gScenario23("scenario", 0);
	om::String gAudioGlobalP3d23 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener24 = om::NameOfText("Listener");
	om::ClassName gMaster24 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup83("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty91("", 0);
	om::String gAudioGlobalP3d24 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener25 = om::NameOfText("Listener");
	om::ClassName gMaster25 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup84("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty92("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup85("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty93("", 0);
	om::String gAudioGlobalP3d25 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener26 = om::NameOfText("Listener");
	om::ClassName gMaster26 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup86("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty94("", 0);
	om::String gAudioGlobalP3d26 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener27 = om::NameOfText("Listener");
	om::ClassName gMaster27 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup87("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty95("", 0);
	MessageListeners gScenario24("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup88("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty96("", 0);
	core::Name<core::CaseInsensitiveKey32> gCaseInsensitiveKey32Object9;
	core::Name<core::CaseSensitiveKey> gEyePointName("EYEPOINT", 0);
	om::String gAudioGlobalP3d27 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener28 = om::NameOfText("Listener");
	om::ClassName gMaster28 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gPlayer("player", 0);
	core::Name<core::CaseSensitiveKey> gNpc("npc", 0);
	om::String gAudioGlobalP3d28 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener29 = om::NameOfText("Listener");
	om::ClassName gMaster29 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup89("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty97("", 0);
	core::Name<core::CaseSensitiveKey> gCaseSensitiveKeyObject2;
	core::Time gZeroTime4(0, 0);
	core::Time gZeroTime5(0, 0);
	core::Time gZeroTime6(0, 0);
	MessageListeners gScenario25("scenario", 0);
	om::String gAudioGlobalP3d29 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener30 = om::NameOfText("Listener");
	om::ClassName gMaster30 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup90("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty98("", 0);
	om::String gAudioGlobalP3d30 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener31 = om::NameOfText("Listener");
	om::ClassName gMaster31 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup91("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty99("", 0);
	core::Name<core::CaseInsensitiveKey32> gSPlane("SPlane", 0);
	core::Name<core::CaseInsensitiveKey32> gTPlane("TPlane", 0);
	core::Name<core::CaseInsensitiveKey32> gFillColour("FillColour", 0);
	core::Name<core::CaseInsensitiveKey32> gCxmul("cxmul", 0);
	core::Name<core::CaseInsensitiveKey32> gCxadd("cxadd", 0);
	core::Name<core::CaseInsensitiveKey32> gAddcolourfactor("addcolourfactor", 0);
	core::Name<core::CaseInsensitiveKey32> gAddcolour("addcolour", 0);
	om::String gRadp = om::StringOfText("radp");
	om::String gWav = om::StringOfText("wav");
	om::String gP3d = om::StringOfText("p3d");
	om::TreeHead gTreeHeadObject10;
	om::TreeHead gTreeHeadObject11;
	core::Name<core::CaseInsensitiveKey32> gCaseInsensitiveKey32Object10;
	math::Matrix gIdentityMatrix3 = math::Matrix::IDENTITY;
}

// The dynamic initialisers and atexit stubs of the unit's globals:
// FUNCTION: ENGINE 0x10D78260
// FUNCTION: ENGINE 0x10D78280
// FUNCTION: ENGINE 0x10D78300
// FUNCTION: ENGINE 0x10D78320
// FUNCTION: ENGINE 0x10D78340
// FUNCTION: ENGINE 0x10D78360
// FUNCTION: ENGINE 0x10D783B0
// FUNCTION: ENGINE 0x10D783D0
// FUNCTION: ENGINE 0x10D783F0
// FUNCTION: ENGINE 0x10D78430
// FUNCTION: ENGINE 0x10D78480
// FUNCTION: ENGINE 0x10D784D0
// FUNCTION: ENGINE 0x10D784F0
// FUNCTION: ENGINE 0x10D785B0
// FUNCTION: ENGINE 0x10D785D0
// FUNCTION: ENGINE 0x10D78610
// FUNCTION: ENGINE 0x10D78660
// FUNCTION: ENGINE 0x10D786B0
// FUNCTION: ENGINE 0x10D786D0
// FUNCTION: ENGINE 0x10D78720
// FUNCTION: ENGINE 0x10D78770
// FUNCTION: ENGINE 0x10D787C0
// FUNCTION: ENGINE 0x10D787E0
// FUNCTION: ENGINE 0x10D78810
// FUNCTION: ENGINE 0x10D78830
// FUNCTION: ENGINE 0x10D78850
// FUNCTION: ENGINE 0x10D78870
// FUNCTION: ENGINE 0x10D78890
// FUNCTION: ENGINE 0x10D788D0
// FUNCTION: ENGINE 0x10D78920
// FUNCTION: ENGINE 0x10D78990
// FUNCTION: ENGINE 0x10D789B0
// FUNCTION: ENGINE 0x10D789E0
// FUNCTION: ENGINE 0x10D78A00
// FUNCTION: ENGINE 0x10D78AC0
// FUNCTION: ENGINE 0x10D78B00
// FUNCTION: ENGINE 0x10D78B50
// FUNCTION: ENGINE 0x10D78BA0
// FUNCTION: ENGINE 0x10D78BC0
// FUNCTION: ENGINE 0x10D78BE0
// FUNCTION: ENGINE 0x10D78C80
// FUNCTION: ENGINE 0x10D78CC0
// FUNCTION: ENGINE 0x10D78D10
// FUNCTION: ENGINE 0x10D78D60
// FUNCTION: ENGINE 0x10D78D80
// FUNCTION: ENGINE 0x10D78DA0
// FUNCTION: ENGINE 0x10D78DE0
// FUNCTION: ENGINE 0x10D78E30
// FUNCTION: ENGINE 0x10D78E80
// FUNCTION: ENGINE 0x10D78EA0
// FUNCTION: ENGINE 0x10D78EC0
// FUNCTION: ENGINE 0x10D78EE0
// FUNCTION: ENGINE 0x10D78F00
// FUNCTION: ENGINE 0x10D78F40
// FUNCTION: ENGINE 0x10D78F90
// FUNCTION: ENGINE 0x10D78FE0
// FUNCTION: ENGINE 0x10D79000
// FUNCTION: ENGINE 0x10D79020
// FUNCTION: ENGINE 0x10D79060
// FUNCTION: ENGINE 0x10D790B0
// FUNCTION: ENGINE 0x10D79100
// FUNCTION: ENGINE 0x10D79120
// FUNCTION: ENGINE 0x10D792A0
// FUNCTION: ENGINE 0x10D792C0
// FUNCTION: ENGINE 0x10D792E0
// FUNCTION: ENGINE 0x10D79320
// FUNCTION: ENGINE 0x10D79450
// FUNCTION: ENGINE 0x10D79470
// FUNCTION: ENGINE 0x10D794B0
// FUNCTION: ENGINE 0x10D79500
// FUNCTION: ENGINE 0x10D79550
// FUNCTION: ENGINE 0x10D79570
// FUNCTION: ENGINE 0x10D79590
// FUNCTION: ENGINE 0x10D795D0
// FUNCTION: ENGINE 0x10D79620
// FUNCTION: ENGINE 0x10D79670
// FUNCTION: ENGINE 0x10D79690
// FUNCTION: ENGINE 0x10D796D0
// FUNCTION: ENGINE 0x10D796F0
// FUNCTION: ENGINE 0x10D79700
// FUNCTION: ENGINE 0x10D79710
// FUNCTION: ENGINE 0x10D79720
// FUNCTION: ENGINE 0x10D79880
// FUNCTION: ENGINE 0x10D798C0
// FUNCTION: ENGINE 0x10D79910
// FUNCTION: ENGINE 0x10D79960
// FUNCTION: ENGINE 0x10D79980
// FUNCTION: ENGINE 0x10D799A0
// FUNCTION: ENGINE 0x10D799E0
// FUNCTION: ENGINE 0x10D79A30
// FUNCTION: ENGINE 0x10D79A80
// FUNCTION: ENGINE 0x10D79AA0
// FUNCTION: ENGINE 0x10D79BA0
// FUNCTION: ENGINE 0x10D79BC0
// FUNCTION: ENGINE 0x10D79BE0
// FUNCTION: ENGINE 0x10D79C00
// FUNCTION: ENGINE 0x10D79C20
// FUNCTION: ENGINE 0x10D79C40
// FUNCTION: ENGINE 0x10D79C60
// FUNCTION: ENGINE 0x10D79E30
// FUNCTION: ENGINE 0x10D79E80
// FUNCTION: ENGINE 0x10D79ED0
// FUNCTION: ENGINE 0x10D79FE0
// FUNCTION: ENGINE 0x10D7A000
// FUNCTION: ENGINE 0x10D7A040
// FUNCTION: ENGINE 0x10D8AF00
// FUNCTION: ENGINE 0x10D8AF10
// FUNCTION: ENGINE 0x10D8AF20
// FUNCTION: ENGINE 0x10D8AF30
// FUNCTION: ENGINE 0x10D8AF40
// FUNCTION: ENGINE 0x10D8AF60
// FUNCTION: ENGINE 0x10D8AF70
// FUNCTION: ENGINE 0x10D8AF80
// FUNCTION: ENGINE 0x10D8AF90
// FUNCTION: ENGINE 0x10D8AFA0
// FUNCTION: ENGINE 0x10D8AFB0
// FUNCTION: ENGINE 0x10D8B010
// FUNCTION: ENGINE 0x10D8B020
// FUNCTION: ENGINE 0x10D8B030
// FUNCTION: ENGINE 0x10D8B040
// FUNCTION: ENGINE 0x10D8B050
// FUNCTION: ENGINE 0x10D8B060
// FUNCTION: ENGINE 0x10D8B070
// FUNCTION: ENGINE 0x10D8B080
// FUNCTION: ENGINE 0x10D8B090
// FUNCTION: ENGINE 0x10D8B0F0
// FUNCTION: ENGINE 0x10D8B100
// FUNCTION: ENGINE 0x10D8B110
// FUNCTION: ENGINE 0x10D8B120
// FUNCTION: ENGINE 0x10D8B160
// FUNCTION: ENGINE 0x10D8B170
// FUNCTION: ENGINE 0x10D8B180
// FUNCTION: ENGINE 0x10D8B190
// FUNCTION: ENGINE 0x10D8B1B0
// FUNCTION: ENGINE 0x10D8B1C0
// FUNCTION: ENGINE 0x10D8B1D0
// FUNCTION: ENGINE 0x10D8B1E0
// FUNCTION: ENGINE 0x10D8B1F0
// FUNCTION: ENGINE 0x10D8B200
// FUNCTION: ENGINE 0x10D8B210
// FUNCTION: ENGINE 0x10D8B220
// FUNCTION: ENGINE 0x10D8B230
// FUNCTION: ENGINE 0x10D8B240
// FUNCTION: ENGINE 0x10D8B250
// FUNCTION: ENGINE 0x10D8B260
// FUNCTION: ENGINE 0x10D8B270
// FUNCTION: ENGINE 0x10D8B280
// FUNCTION: ENGINE 0x10D8B2F0
// FUNCTION: ENGINE 0x10D8B300
// FUNCTION: ENGINE 0x10D8B310
// FUNCTION: ENGINE 0x10D8B340
// FUNCTION: ENGINE 0x10D8B390
// FUNCTION: ENGINE 0x10D8B3D0
// FUNCTION: ENGINE 0x10D8B3E0
// FUNCTION: ENGINE 0x10D8B3F0
// FUNCTION: ENGINE 0x10D8B400
// FUNCTION: ENGINE 0x10D8B410
// FUNCTION: ENGINE 0x10D8B420
// FUNCTION: ENGINE 0x10D8B440
// FUNCTION: ENGINE 0x10D8B450
// FUNCTION: ENGINE 0x10D8B4E0
// FUNCTION: ENGINE 0x10D8B4F0
// FUNCTION: ENGINE 0x10D8B500
// FUNCTION: ENGINE 0x10D8B510
// FUNCTION: ENGINE 0x10D8B520
// FUNCTION: ENGINE 0x10D8B530
// FUNCTION: ENGINE 0x10D8B600
// FUNCTION: ENGINE 0x10D8B610
// FUNCTION: ENGINE 0x10D8B620
// FUNCTION: ENGINE 0x10D8B630
// FUNCTION: ENGINE 0x10D8B640
// FUNCTION: ENGINE 0x10D8B650
// FUNCTION: ENGINE 0x10D8B660
// FUNCTION: ENGINE 0x10D8B910
// FUNCTION: ENGINE 0x10D8B940
// FUNCTION: ENGINE 0x10D8B970
// FUNCTION: ENGINE 0x10D8BA00
// FUNCTION: ENGINE 0x10D8BA10
// FUNCTION: ENGINE 0x10D8BA20
// FUNCTION: ENGINE 0x10D79340
