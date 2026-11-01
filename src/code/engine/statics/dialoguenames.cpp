// Globals that the engine's static initialisers 0x10D73B70 - 0x10D75CE0 construct in translation units whose code is not
// reconstructed: the attribute, dialogue, audio message and streaming group names, and the names and strings every such unit repeats through its headers (the
// slot group names, the audio file and listener names). Unit name guess; one file holds the runs of several units.
#include "code/core/name.h"
#include "code/core/time.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/om/staticinit.h"
#include "code/om/tree.h"

namespace engine
{
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup35("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty32("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup36("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty33("", 0);
	fight::EnumEntry gIgnoredByNPCsTable[4] =
	{
		{ fight::Name("ignoredByNPCs", 0) },
		{ fight::Name("unclimbable", 0) },
		{ fight::Name("maxsize", 0) },
		{ fight::Name("propindex", 0) }
	};
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup37("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty34("", 0);
	core::Name<core::CaseInsensitiveKey32> gCaseInsensitiveKey32Object2;
	core::Name<core::CaseSensitiveKey> gEmpty35("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup38("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty36("", 0);
	core::Name<core::CaseSensitiveKey> gDialogue("dialogue", 0);
	core::Name<core::CaseSensitiveKey> gDialogName("dialog", 0);
	core::Name<core::CaseSensitiveKey> gDone("done", 0);
	core::Name<core::CaseSensitiveKey> gEmpty37("", 0);
	om::ClassName gDone2 = om::NameOfText("done");
	om::ClassName gStop = om::NameOfText("stop");
	om::ClassName gNONE = om::NameOfText("!NONE!");
	om::ClassName gLoop = om::NameOfText("loop");
	om::ClassName gPlay = om::NameOfText("play");
	om::ClassName gGroup = om::NameOfText("group");
	om::ClassName gMinRadius = om::NameOfText("min_radius");
	om::ClassName gMaxRadius = om::NameOfText("max_radius");
	om::ClassName gPos2 = om::NameOfText("pos");
	om::String gCollisions = om::StringOfText("collisions");
	om::String gDialogue2 = om::StringOfText("dialogue");
	om::String gOneShotMed = om::StringOfText("one_shot_med");
	om::String gLoopMed = om::StringOfText("loop_med");
	core::Name<core::CaseSensitiveKey> gEmpty38("", 0);
	core::Name<core::CaseSensitiveKey> gEmpty39("", 0);
	fight::EnumEntry gStartupGroupTable[3] =
	{
		{ fight::Name("Startup_Group", 0) },
		{ fight::Name("Location_Group", 0) },
		{ fight::Name("Mission_Group", 0) }
	};
	fight::EnumEntry gStartupPackageTable[3] =
	{
		{ fight::Name("Startup_Package", 0) },
		{ fight::Name("Location_Package", 0) },
		{ fight::Name("Mission_Package", 0) }
	};
	MessageListeners gScenario13("scenario", 0);
	core::Name<core::CaseSensitiveKey> gMasterScenario("master_scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup39("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty40("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup40("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty41("", 0);
	om::String gAudioGlobalP3d7 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener8 = om::NameOfText("Listener");
	om::ClassName gMaster8 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup41("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty42("", 0);
	MessageListeners gScenario14("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup42("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty43("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup43("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty44("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup44("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty45("", 0);
	core::Name<core::CaseInsensitiveKey32> gCaseInsensitiveKey32Object3;
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup45("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty46("", 0);
	om::String gAudioGlobalP3d8 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener9 = om::NameOfText("Listener");
	om::ClassName gMaster9 = om::NameOfText("Master");
	MessageListeners gScenario15("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup46("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty47("", 0);
	core::Name<core::CaseInsensitiveKey32> gCaseInsensitiveKey32Object4;
	core::Name<core::CaseInsensitiveKey32> gCaseInsensitiveKey32Object5;
	core::Name<core::CaseSensitiveKey> gGameLinkLuaCommand("GameLinkLuaCommand", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup47("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty48("", 0);
	MessageListeners gScenario16("scenario", 0);
	om::String gAudioGlobalP3d9 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener10 = om::NameOfText("Listener");
	om::ClassName gMaster10 = om::NameOfText("Master");
	MessageListeners gScenario17("scenario", 0);
	core::Name<core::CaseSensitiveKey> gPlay2("play", 0);
	core::Name<core::CaseSensitiveKey> gFile2("file", 0);
	core::Name<core::CaseSensitiveKey> gBroadcast("Broadcast", 0);
	core::Name<core::CaseSensitiveKey> gAttacker("Attacker", 0);
	core::Name<core::CaseSensitiveKey> gEmpty49("", 0);
	core::Name<core::CaseSensitiveKey> gPos3("pos", 0);
	core::Name<core::CaseSensitiveKey> gDialogue3("Dialogue", 0);
	core::Name<core::CaseSensitiveKey> gAudioDialogueSubtitle("AudioDialogueSubtitle", 0);
	core::Name<core::CaseSensitiveKey> gAudioDialoguePersonality("AudioDialoguePersonality", 0);
	om::TreeHead gTreeHeadObject5;
	om::TreeHead gTreeHeadObject6;
	om::TreeHead gTreeHeadObject7;
	om::TreeHead gTreeHeadObject8;
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup48("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty50("", 0);
	om::String gAudioGlobalP3d10 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener11 = om::NameOfText("Listener");
	om::ClassName gMaster11 = om::NameOfText("Master");
	MessageListeners gScenario18("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup49("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty51("", 0);
	core::Name<core::CaseSensitiveKey> gNofocus("nofocus", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup50("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty52("", 0);
	core::Time gZeroTime(0, 0);
	core::Time gZeroTime2(0, 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup51("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty53("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup52("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty54("", 0);
	core::Name<core::CaseSensitiveKey> gEmpty55("", 0);
	om::String gAudioGlobalP3d11 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener12 = om::NameOfText("Listener");
	om::ClassName gMaster12 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup53("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty56("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup54("Undefined_SlotGroup", 0);
}

// The dynamic initialisers and atexit stubs of the unit's globals:
// FUNCTION: ENGINE 0x10D73B70
// FUNCTION: ENGINE 0x10D73B90
// FUNCTION: ENGINE 0x10D73BC0
// FUNCTION: ENGINE 0x10D73BE0
// FUNCTION: ENGINE 0x10D73FA0
// FUNCTION: ENGINE 0x10D740F0
// FUNCTION: ENGINE 0x10D74110
// FUNCTION: ENGINE 0x10D74130
// FUNCTION: ENGINE 0x10D74170
// FUNCTION: ENGINE 0x10D74190
// FUNCTION: ENGINE 0x10D741B0
// FUNCTION: ENGINE 0x10D741F0
// FUNCTION: ENGINE 0x10D74210
// FUNCTION: ENGINE 0x10D74230
// FUNCTION: ENGINE 0x10D74270
// FUNCTION: ENGINE 0x10D74510
// FUNCTION: ENGINE 0x10D74560
// FUNCTION: ENGINE 0x10D745B0
// FUNCTION: ENGINE 0x10D74600
// FUNCTION: ENGINE 0x10D74650
// FUNCTION: ENGINE 0x10D746A0
// FUNCTION: ENGINE 0x10D746F0
// FUNCTION: ENGINE 0x10D74740
// FUNCTION: ENGINE 0x10D74790
// FUNCTION: ENGINE 0x10D747E0
// FUNCTION: ENGINE 0x10D74820
// FUNCTION: ENGINE 0x10D74860
// FUNCTION: ENGINE 0x10D748A0
// FUNCTION: ENGINE 0x10D74960
// FUNCTION: ENGINE 0x10D74CA0
// FUNCTION: ENGINE 0x10D74D00
// FUNCTION: ENGINE 0x10D74D40
// FUNCTION: ENGINE 0x10D74E00
// FUNCTION: ENGINE 0x10D74E40
// FUNCTION: ENGINE 0x10D74E60
// FUNCTION: ENGINE 0x10D74E80
// FUNCTION: ENGINE 0x10D74EA0
// FUNCTION: ENGINE 0x10D74EC0
// FUNCTION: ENGINE 0x10D74EE0
// FUNCTION: ENGINE 0x10D74F20
// FUNCTION: ENGINE 0x10D74F70
// FUNCTION: ENGINE 0x10D74FC0
// FUNCTION: ENGINE 0x10D74FE0
// FUNCTION: ENGINE 0x10D75000
// FUNCTION: ENGINE 0x10D75020
// FUNCTION: ENGINE 0x10D75040
// FUNCTION: ENGINE 0x10D75060
// FUNCTION: ENGINE 0x10D75080
// FUNCTION: ENGINE 0x10D750A0
// FUNCTION: ENGINE 0x10D750C0
// FUNCTION: ENGINE 0x10D75100
// FUNCTION: ENGINE 0x10D75120
// FUNCTION: ENGINE 0x10D75140
// FUNCTION: ENGINE 0x10D75160
// FUNCTION: ENGINE 0x10D751A0
// FUNCTION: ENGINE 0x10D751F0
// FUNCTION: ENGINE 0x10D75270
// FUNCTION: ENGINE 0x10D75290
// FUNCTION: ENGINE 0x10D752B0
// FUNCTION: ENGINE 0x10D752F0
// FUNCTION: ENGINE 0x10D75390
// FUNCTION: ENGINE 0x10D753C0
// FUNCTION: ENGINE 0x10D753E0
// FUNCTION: ENGINE 0x10D75400
// FUNCTION: ENGINE 0x10D75420
// FUNCTION: ENGINE 0x10D75440
// FUNCTION: ENGINE 0x10D75480
// FUNCTION: ENGINE 0x10D754D0
// FUNCTION: ENGINE 0x10D75520
// FUNCTION: ENGINE 0x10D75540
// FUNCTION: ENGINE 0x10D75560
// FUNCTION: ENGINE 0x10D75580
// FUNCTION: ENGINE 0x10D755A0
// FUNCTION: ENGINE 0x10D755C0
// FUNCTION: ENGINE 0x10D755E0
// FUNCTION: ENGINE 0x10D75600
// FUNCTION: ENGINE 0x10D75620
// FUNCTION: ENGINE 0x10D75640
// FUNCTION: ENGINE 0x10D75670
// FUNCTION: ENGINE 0x10D756B0
// FUNCTION: ENGINE 0x10D756D0
// FUNCTION: ENGINE 0x10D756F0
// FUNCTION: ENGINE 0x10D75710
// FUNCTION: ENGINE 0x10D75730
// FUNCTION: ENGINE 0x10D75770
// FUNCTION: ENGINE 0x10D757B0
// FUNCTION: ENGINE 0x10D75800
// FUNCTION: ENGINE 0x10D75850
// FUNCTION: ENGINE 0x10D75870
// FUNCTION: ENGINE 0x10D75890
// FUNCTION: ENGINE 0x10D758B0
// FUNCTION: ENGINE 0x10D758D0
// FUNCTION: ENGINE 0x10D758F0
// FUNCTION: ENGINE 0x10D75990
// FUNCTION: ENGINE 0x10D759A0
// FUNCTION: ENGINE 0x10D759C0
// FUNCTION: ENGINE 0x10D759E0
// FUNCTION: ENGINE 0x10D75A00
// FUNCTION: ENGINE 0x10D75A20
// FUNCTION: ENGINE 0x10D75AC0
// FUNCTION: ENGINE 0x10D75AE0
// FUNCTION: ENGINE 0x10D75B20
// FUNCTION: ENGINE 0x10D75B70
// FUNCTION: ENGINE 0x10D75CA0
// FUNCTION: ENGINE 0x10D75CC0
// FUNCTION: ENGINE 0x10D75CE0
// FUNCTION: ENGINE 0x10D89A40
// FUNCTION: ENGINE 0x10D89A50
// FUNCTION: ENGINE 0x10D89A70
// FUNCTION: ENGINE 0x10D89A80
// FUNCTION: ENGINE 0x10D89C20
// FUNCTION: ENGINE 0x10D89D20
// FUNCTION: ENGINE 0x10D89D30
// FUNCTION: ENGINE 0x10D89D40
// FUNCTION: ENGINE 0x10D89D60
// FUNCTION: ENGINE 0x10D89D80
// FUNCTION: ENGINE 0x10D89D90
// FUNCTION: ENGINE 0x10D89DA0
// FUNCTION: ENGINE 0x10D89DB0
// FUNCTION: ENGINE 0x10D89DC0
// FUNCTION: ENGINE 0x10D89DD0
// FUNCTION: ENGINE 0x10D89E00
// FUNCTION: ENGINE 0x10D89E10
// FUNCTION: ENGINE 0x10D89E20
// FUNCTION: ENGINE 0x10D89E40
// FUNCTION: ENGINE 0x10D89FB0
// FUNCTION: ENGINE 0x10D8A0B0
// FUNCTION: ENGINE 0x10D8A0E0
// FUNCTION: ENGINE 0x10D8A0F0
// FUNCTION: ENGINE 0x10D8A160
// FUNCTION: ENGINE 0x10D8A170
// FUNCTION: ENGINE 0x10D8A1A0
// FUNCTION: ENGINE 0x10D8A1B0
// FUNCTION: ENGINE 0x10D8A1D0
// FUNCTION: ENGINE 0x10D8A1E0
// FUNCTION: ENGINE 0x10D8A210
// FUNCTION: ENGINE 0x10D8A220
// FUNCTION: ENGINE 0x10D8A230
// FUNCTION: ENGINE 0x10D8A240
// FUNCTION: ENGINE 0x10D8A250
// FUNCTION: ENGINE 0x10D8A260
// FUNCTION: ENGINE 0x10D8A270
// FUNCTION: ENGINE 0x10D8A280
// FUNCTION: ENGINE 0x10D8A290
// FUNCTION: ENGINE 0x10D8A2A0
// FUNCTION: ENGINE 0x10D8A2C0
// FUNCTION: ENGINE 0x10D8A2D0
// FUNCTION: ENGINE 0x10D8A2E0
// FUNCTION: ENGINE 0x10D8A2F0
// FUNCTION: ENGINE 0x10D8A320
// FUNCTION: ENGINE 0x10D8A330
// FUNCTION: ENGINE 0x10D8A340
// FUNCTION: ENGINE 0x10D8A370
// FUNCTION: ENGINE 0x10D8A3A0
// FUNCTION: ENGINE 0x10D8A3C0
// FUNCTION: ENGINE 0x10D8A3D0
// FUNCTION: ENGINE 0x10D8A3E0
// FUNCTION: ENGINE 0x10D8A3F0
// FUNCTION: ENGINE 0x10D8A400
// FUNCTION: ENGINE 0x10D8A410
// FUNCTION: ENGINE 0x10D8A420
// FUNCTION: ENGINE 0x10D8A430
// FUNCTION: ENGINE 0x10D8A440
// FUNCTION: ENGINE 0x10D8A450
// FUNCTION: ENGINE 0x10D8A460
// FUNCTION: ENGINE 0x10D8A470
// FUNCTION: ENGINE 0x10D8A480
// FUNCTION: ENGINE 0x10D8A490
// FUNCTION: ENGINE 0x10D8A4A0
// FUNCTION: ENGINE 0x10D8A4C0
// FUNCTION: ENGINE 0x10D8A4F0
// FUNCTION: ENGINE 0x10D8A500
// FUNCTION: ENGINE 0x10D8A510
// FUNCTION: ENGINE 0x10D8A520
// FUNCTION: ENGINE 0x10D8A530
// FUNCTION: ENGINE 0x10D8A560
// FUNCTION: ENGINE 0x10D8A570
// FUNCTION: ENGINE 0x10D8A580
// FUNCTION: ENGINE 0x10D8A590
// FUNCTION: ENGINE 0x10D8A5A0
// FUNCTION: ENGINE 0x10D8A5E0
// FUNCTION: ENGINE 0x10D8A5F0
// FUNCTION: ENGINE 0x10D8A630
// FUNCTION: ENGINE 0x10D8A640
// FUNCTION: ENGINE 0x10D8A650
// FUNCTION: ENGINE 0x10D8A660
// FUNCTION: ENGINE 0x10D8A6D0
// FUNCTION: ENGINE 0x10D8A6E0
// FUNCTION: ENGINE 0x10D8A710
// FUNCTION: ENGINE 0x10D8A720
// FUNCTION: ENGINE 0x10D8A730
