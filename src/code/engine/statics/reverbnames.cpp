// Globals that the engine's static initialisers 0x10D75D00 - 0x10D77F20 construct in translation units whose code is not
// reconstructed: the reverb parameter, front end and audio file names, and the names and strings every such unit repeats through its headers (the
// slot group names, the audio file and listener names). Unit name guess; one file holds the runs of several units.
#include "code/core/name.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/om/staticinit.h"
#include "code/om/tree.h"

namespace engine
{
	core::Name<core::CaseSensitiveKey> gEmpty57("", 0);
	core::Name<core::CaseSensitiveKey> gFEDynamicResources("FEDynamicResources", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup55("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty58("", 0);
	core::Name<core::CaseSensitiveKey> gEmpty59("", 0);
	om::String gAudioGlobalP3d12 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener13 = om::NameOfText("Listener");
	om::ClassName gMaster13 = om::NameOfText("Master");
	om::ClassName gRadverbGeneric = om::NameOfText("radverb_generic");
	om::ClassName gAutomate = om::NameOfText("automate");
	om::ClassName gReverbTime = om::NameOfText("reverb_time");
	om::ClassName gEarlyGain = om::NameOfText("early_gain");
	om::ClassName gLateGain = om::NameOfText("late_gain");
	om::ClassName gInputLpf = om::NameOfText("input_lpf");
	om::ClassName gEarlyLpf = om::NameOfText("early_lpf");
	om::ClassName gLateLpf = om::NameOfText("late_lpf");
	om::ClassName gDampingLpf = om::NameOfText("damping_lpf");
	om::ClassName gDistWall = om::NameOfText("dist_wall");
	om::ClassName gDistWallMin = om::NameOfText("dist_wall_min");
	om::ClassName gEarlyLpfMax = om::NameOfText("early_lpf_max");
	om::ClassName gTimeMax = om::NameOfText("time_max");
	om::ClassName gHorizMin = om::NameOfText("horiz_min");
	om::ClassName gHorizMax = om::NameOfText("horiz_max");
	om::ClassName gVertMin = om::NameOfText("vert_min");
	om::ClassName gVertMax = om::NameOfText("vert_max");
	om::ClassName gOverallMin = om::NameOfText("overall_min");
	om::ClassName gOverallMax = om::NameOfText("overall_max");
	om::TreeHead gTreeHeadObject9;
	om::String gAudioGlobalP3d13 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener14 = om::NameOfText("Listener");
	om::ClassName gMaster14 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup56("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty60("", 0);
	om::ClassName gFiles = om::NameOfText("Files");
	core::Name<core::CaseSensitiveKey> gAmplitude("amplitude", 0);
	om::String gAudioGlobalP3d14 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener15 = om::NameOfText("Listener");
	om::ClassName gMaster15 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gFrontEnd("front_end", 0);
	core::Name<core::CaseSensitiveKey> gFe("fe", 0);
	om::ClassName gLoop2 = om::NameOfText("loop");
	MessageListeners gScenario19("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup57("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty61("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup58("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty62("", 0);
	core::Name<core::CaseSensitiveKey> gCaseSensitiveKeyObject;
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup59("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty63("", 0);
	om::String gAudioGlobalP3d15 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener16 = om::NameOfText("Listener");
	om::ClassName gMaster16 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup60("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty64("", 0);
	core::Name<core::CaseSensitiveKey> gEmpty65("", 0);
	om::String gAudioGlobalP3d16 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener17 = om::NameOfText("Listener");
	om::ClassName gMaster17 = om::NameOfText("Master");
	core::Name<core::CaseInsensitiveKey32> gCaseInsensitiveKey32Object6;
	core::Name<core::CaseInsensitiveKey32> gCaseInsensitiveKey32Object7;
	core::Name<core::CaseInsensitiveKey32> gCaseInsensitiveKey32Object8;
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup61("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty66("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup62("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty67("", 0);
	MessageListeners gScenario20("scenario", 0);
	core::Name<core::CaseSensitiveKey> gFinal("final", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup63("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty68("", 0);
	core::Name<core::CaseSensitiveKey> gLight("light", 0);
	om::String gAudioGlobalP3d17 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener18 = om::NameOfText("Listener");
	om::ClassName gMaster18 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup64("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty69("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup65("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty70("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup66("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty71("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup67("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty72("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup68("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty73("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup69("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty74("", 0);
	MessageListeners gScenario21("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup70("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty75("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup71("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty76("", 0);
	core::Name<core::CaseSensitiveKey> gEmpty77("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup72("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty78("", 0);
	om::String gAudioGlobalP3d18 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener19 = om::NameOfText("Listener");
	om::ClassName gMaster19 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup73("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty79("", 0);
	core::Name<core::CaseSensitiveKey> gEmpty80("", 0);
	fight::EnumEntry gOnTable[3] =
	{
		{ fight::Name("On", 0) },
		{ fight::Name("Off", 0) },
		{ fight::Name("<No Change>", 0) }
	};
	core::Name<core::CaseSensitiveKey> gEmpty81("", 0);
	core::Name<core::CaseSensitiveKey> gNone("none", 0);
}

// The dynamic initialisers and atexit stubs of the unit's globals:
// FUNCTION: ENGINE 0x10D75D00
// FUNCTION: ENGINE 0x10D75D20
// FUNCTION: ENGINE 0x10D75D40
// FUNCTION: ENGINE 0x10D75D60
// FUNCTION: ENGINE 0x10D75DC0
// FUNCTION: ENGINE 0x10D75E70
// FUNCTION: ENGINE 0x10D75EB0
// FUNCTION: ENGINE 0x10D75F00
// FUNCTION: ENGINE 0x10D75F50
// FUNCTION: ENGINE 0x10D75FA0
// FUNCTION: ENGINE 0x10D75FF0
// FUNCTION: ENGINE 0x10D76040
// FUNCTION: ENGINE 0x10D76090
// FUNCTION: ENGINE 0x10D760E0
// FUNCTION: ENGINE 0x10D76130
// FUNCTION: ENGINE 0x10D76180
// FUNCTION: ENGINE 0x10D761D0
// FUNCTION: ENGINE 0x10D76220
// FUNCTION: ENGINE 0x10D76270
// FUNCTION: ENGINE 0x10D762C0
// FUNCTION: ENGINE 0x10D76310
// FUNCTION: ENGINE 0x10D76360
// FUNCTION: ENGINE 0x10D763B0
// FUNCTION: ENGINE 0x10D76400
// FUNCTION: ENGINE 0x10D76450
// FUNCTION: ENGINE 0x10D764A0
// FUNCTION: ENGINE 0x10D764F0
// FUNCTION: ENGINE 0x10D76540
// FUNCTION: ENGINE 0x10D76610
// FUNCTION: ENGINE 0x10D76650
// FUNCTION: ENGINE 0x10D766A0
// FUNCTION: ENGINE 0x10D766F0
// FUNCTION: ENGINE 0x10D76710
// FUNCTION: ENGINE 0x10D76730
// FUNCTION: ENGINE 0x10D76780
// FUNCTION: ENGINE 0x10D767A0
// FUNCTION: ENGINE 0x10D767E0
// FUNCTION: ENGINE 0x10D76830
// FUNCTION: ENGINE 0x10D76880
// FUNCTION: ENGINE 0x10D768A0
// FUNCTION: ENGINE 0x10D76DB0
// FUNCTION: ENGINE 0x10D77100
// FUNCTION: ENGINE 0x10D77120
// FUNCTION: ENGINE 0x10D77140
// FUNCTION: ENGINE 0x10D771C0
// FUNCTION: ENGINE 0x10D771E0
// FUNCTION: ENGINE 0x10D77200
// FUNCTION: ENGINE 0x10D77240
// FUNCTION: ENGINE 0x10D77260
// FUNCTION: ENGINE 0x10D77280
// FUNCTION: ENGINE 0x10D772C0
// FUNCTION: ENGINE 0x10D77310
// FUNCTION: ENGINE 0x10D77360
// FUNCTION: ENGINE 0x10D77380
// FUNCTION: ENGINE 0x10D774A0
// FUNCTION: ENGINE 0x10D774C0
// FUNCTION: ENGINE 0x10D77500
// FUNCTION: ENGINE 0x10D77550
// FUNCTION: ENGINE 0x10D775A0
// FUNCTION: ENGINE 0x10D775C0
// FUNCTION: ENGINE 0x10D775E0
// FUNCTION: ENGINE 0x10D77600
// FUNCTION: ENGINE 0x10D77620
// FUNCTION: ENGINE 0x10D77640
// FUNCTION: ENGINE 0x10D77660
// FUNCTION: ENGINE 0x10D77690
// FUNCTION: ENGINE 0x10D776B0
// FUNCTION: ENGINE 0x10D776D0
// FUNCTION: ENGINE 0x10D776F0
// FUNCTION: ENGINE 0x10D77710
// FUNCTION: ENGINE 0x10D77730
// FUNCTION: ENGINE 0x10D77770
// FUNCTION: ENGINE 0x10D777C0
// FUNCTION: ENGINE 0x10D77810
// FUNCTION: ENGINE 0x10D77830
// FUNCTION: ENGINE 0x10D77850
// FUNCTION: ENGINE 0x10D77870
// FUNCTION: ENGINE 0x10D77890
// FUNCTION: ENGINE 0x10D778B0
// FUNCTION: ENGINE 0x10D778D0
// FUNCTION: ENGINE 0x10D778F0
// FUNCTION: ENGINE 0x10D77910
// FUNCTION: ENGINE 0x10D77930
// FUNCTION: ENGINE 0x10D77950
// FUNCTION: ENGINE 0x10D77970
// FUNCTION: ENGINE 0x10D77990
// FUNCTION: ENGINE 0x10D779B0
// FUNCTION: ENGINE 0x10D779D0
// FUNCTION: ENGINE 0x10D779F0
// FUNCTION: ENGINE 0x10D77A10
// FUNCTION: ENGINE 0x10D77A50
// FUNCTION: ENGINE 0x10D77A70
// FUNCTION: ENGINE 0x10D77A90
// FUNCTION: ENGINE 0x10D77AB0
// FUNCTION: ENGINE 0x10D77AF0
// FUNCTION: ENGINE 0x10D77B40
// FUNCTION: ENGINE 0x10D77B90
// FUNCTION: ENGINE 0x10D77BB0
// FUNCTION: ENGINE 0x10D77D70
// FUNCTION: ENGINE 0x10D77EA0
// FUNCTION: ENGINE 0x10D77EE0
// FUNCTION: ENGINE 0x10D77F20
// FUNCTION: ENGINE 0x10D8A740
// FUNCTION: ENGINE 0x10D8A750
// FUNCTION: ENGINE 0x10D8A760
// FUNCTION: ENGINE 0x10D8A770
// FUNCTION: ENGINE 0x10D8A7A0
// FUNCTION: ENGINE 0x10D8A800
// FUNCTION: ENGINE 0x10D8A810
// FUNCTION: ENGINE 0x10D8A850
// FUNCTION: ENGINE 0x10D8A860
// FUNCTION: ENGINE 0x10D8A870
// FUNCTION: ENGINE 0x10D8A880
// FUNCTION: ENGINE 0x10D8A890
// FUNCTION: ENGINE 0x10D8A8A0
// FUNCTION: ENGINE 0x10D8A8B0
// FUNCTION: ENGINE 0x10D8A8C0
// FUNCTION: ENGINE 0x10D8A900
// FUNCTION: ENGINE 0x10D8A910
// FUNCTION: ENGINE 0x10D8A920
// FUNCTION: ENGINE 0x10D8A930
// FUNCTION: ENGINE 0x10D8A960
// FUNCTION: ENGINE 0x10D8A970
// FUNCTION: ENGINE 0x10D8A980
// FUNCTION: ENGINE 0x10D8A990
// FUNCTION: ENGINE 0x10D8A9A0
// FUNCTION: ENGINE 0x10D8A9B0
// FUNCTION: ENGINE 0x10D8AAC0
// FUNCTION: ENGINE 0x10D8AAD0
// FUNCTION: ENGINE 0x10D8AAE0
// FUNCTION: ENGINE 0x10D8AAF0
// FUNCTION: ENGINE 0x10D8AB00
// FUNCTION: ENGINE 0x10D8AB10
// FUNCTION: ENGINE 0x10D8AB20
// FUNCTION: ENGINE 0x10D8AB30
// FUNCTION: ENGINE 0x10D8AB40
// FUNCTION: ENGINE 0x10D8AB50
// FUNCTION: ENGINE 0x10D8AB60
// FUNCTION: ENGINE 0x10D8AB70
// FUNCTION: ENGINE 0x10D8AB80
// FUNCTION: ENGINE 0x10D8AB90
// FUNCTION: ENGINE 0x10D8ABA0
// FUNCTION: ENGINE 0x10D8ABB0
// FUNCTION: ENGINE 0x10D8ABC0
// FUNCTION: ENGINE 0x10D8ABD0
// FUNCTION: ENGINE 0x10D8ABE0
// FUNCTION: ENGINE 0x10D8ABF0
// FUNCTION: ENGINE 0x10D8AC00
// FUNCTION: ENGINE 0x10D8AC10
// FUNCTION: ENGINE 0x10D8AC20
// FUNCTION: ENGINE 0x10D8AC30
// FUNCTION: ENGINE 0x10D8AC40
// FUNCTION: ENGINE 0x10D8AC50
// FUNCTION: ENGINE 0x10D8AC60
// FUNCTION: ENGINE 0x10D8AC70
// FUNCTION: ENGINE 0x10D8AC80
// FUNCTION: ENGINE 0x10D8AC90
// FUNCTION: ENGINE 0x10D8ACA0
// FUNCTION: ENGINE 0x10D8ACB0
// FUNCTION: ENGINE 0x10D8ACD0
// FUNCTION: ENGINE 0x10D8ACE0
// FUNCTION: ENGINE 0x10D8ACF0
// FUNCTION: ENGINE 0x10D8AD00
// FUNCTION: ENGINE 0x10D8AD10
// FUNCTION: ENGINE 0x10D8AD20
// FUNCTION: ENGINE 0x10D8ADB0
// FUNCTION: ENGINE 0x10D8AE00
// FUNCTION: ENGINE 0x10D8AE10
// FUNCTION: ENGINE 0x10D8AE30
