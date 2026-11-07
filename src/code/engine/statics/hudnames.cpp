// Globals that the engine's static initialisers 0x10D5F020 - 0x10D5FFC0 construct in translation units whose code is not
// reconstructed: the hud, attack mode and online condition names, and the names and strings every such unit repeats through its headers (the
// slot group names, the audio file and listener names). Unit name guess; one file holds the runs of several units.
#include "code/core/name.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/om/staticinit.h"

namespace engine
{
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup234("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty244("", 0);
	MessageListeners gScenario86("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup235("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty245("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup236("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty246("", 0);
	om::String gAudioGlobalP3d42 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener43 = om::NameOfText("Listener");
	om::ClassName gMaster43 = om::NameOfText("Master");
	MessageListeners gScenario87("scenario", 0);
	core::Name<core::CaseSensitiveKey> gHUDPlayerTransform("HUDPlayerTransform", 0);
	fight::EnumEntry gAttackTable[4] =
		{
			{ fight::Name("Attack", 0) },
			{ fight::Name("Defense", 0) },
			{ fight::Name("Senses", 0) },
			{ fight::Name("Disguise", 0) }
		};
	fight::EnumEntry gNoneTable3[14] =
		{
			{ fight::Name("None", 0) },
			{ fight::Name("Claws", 0) },
			{ fight::Name("Blades", 0) },
			{ fight::Name("HammerFist", 0) },
			{ fight::Name("WhipFist", 0) },
			{ fight::Name("MuscleMass", 0) },
			{ fight::Name("Armour", 0) },
			{ fight::Name("Spines", 0) },
			{ fight::Name("Shield", 0) },
			{ fight::Name("ChameleonicSkin", 0) },
			{ fight::Name("ThermalVision", 0) },
			{ fight::Name("MotherVision", 0) },
			{ fight::Name("Disguise", 0) },
			{ fight::Name("Alex", 0) }
		};
	fight::EnumEntry gUiHudPowerSelectTable[20] =
		{
			{ fight::Name("ui_hud_power_select", 0) },
			{ fight::Name("ui_hud_power_nav", 0) },
			{ fight::Name("ui_fe_ht_locked", 0) },
			{ fight::Name("ui_hud_power_select", 0) },
			{ fight::Name("ui_hud_power_deselect", 0) },
			{ fight::Name("ui_fe_woi_bg_loop", 0) },
			{ fight::Name("ui_fe_woi_nav", 0) },
			{ fight::Name("ui_fe_woi_node_tendrils", 0) },
			{ fight::Name("ui_hud_disguise_hint01", 0) },
			{ fight::Name("ui_hud_disguise_hint02", 0) },
			{ fight::Name("ui_hud_disguise_hint03", 0) },
			{ fight::Name("ui_hud_poison_effect", 0) },
			{ fight::Name("ui_hud_passive_hint01", 0) },
			{ fight::Name("ui_hud_passive_hint02", 0) },
			{ fight::Name("ui_hud_passive_hint03", 0) },
			{ fight::Name("pause_menu_music", 0) },
			{ fight::Name("ui_hud_target_lock", 0) },
			{ fight::Name("ui_hud_target_release", 0) },
			{ fight::Name("ui_fe_loading_hint_one_shot", 0) },
			{ fight::Name("ui_hud_rubber_stamp", 0) }
		};
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup237("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty247("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup238("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty248("", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour28("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup239("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty249("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup240("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty250("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup241("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty251("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup242("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty252("", 0);
	core::Name<core::CaseSensitiveKey> gMaxVisibleDistance("maxVisibleDistance", 0);
	MessageListeners gScenario88("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup243("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty253("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup244("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty254("", 0);
	om::String gAudioGlobalP3d43 = om::StringOfText("audio\\global.p3d");
}

namespace proto
{
	namespace fightitems
	{
		namespace online
		{
			fight::EnumEntry gOnlineTestForRespawnStateConditionStateTable[5] =
				{
					{ fight::Name("AnyNonNull", 0) },
					{ fight::Name("Requested", 0) },
					{ fight::Name("Ready", 0) },
					{ fight::Name("Pending", 0) },
					{ fight::Name("Commencing", 0) }
				};
		}
	}
}

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::EnumEntry gGrabPlayerTrackGrabbingPlayerTable[8] =
				{
					{ fight::Name("Me", 0) },
					{ fight::Name("Other", 0) },
					{ fight::Name("Player0", 0) },
					{ fight::Name("Player1", 0) },
					{ fight::Name("Local", 0) },
					{ fight::Name("Remote", 0) },
					{ fight::Name("Nearest", 0) },
					{ fight::Name("Furthest", 0) }
				};
		}
	}
}

// The dynamic initialisers and atexit stubs of the unit's globals:
// FUNCTION: ENGINE 0x10D5F020
// FUNCTION: ENGINE 0x10D5F050
// FUNCTION: ENGINE 0x10D5F080
// FUNCTION: ENGINE 0x10D5F0B0
// FUNCTION: ENGINE 0x10D5F0E0
// FUNCTION: ENGINE 0x10D5F110
// FUNCTION: ENGINE 0x10D5F140
// FUNCTION: ENGINE 0x10D5F170
// FUNCTION: ENGINE 0x10D5F1C0
// FUNCTION: ENGINE 0x10D5F220
// FUNCTION: ENGINE 0x10D5F280
// FUNCTION: ENGINE 0x10D5F2B0
// FUNCTION: ENGINE 0x10D5F2E0
// FUNCTION: ENGINE 0x10D5F350
// FUNCTION: ENGINE 0x10D5F490
// FUNCTION: ENGINE 0x10D5F650
// FUNCTION: ENGINE 0x10D5F680
// FUNCTION: ENGINE 0x10D5F6B0
// FUNCTION: ENGINE 0x10D5F6E0
// FUNCTION: ENGINE 0x10D5F8A0
// FUNCTION: ENGINE 0x10D5F8D0
// FUNCTION: ENGINE 0x10D5F900
// FUNCTION: ENGINE 0x10D5F930
// FUNCTION: ENGINE 0x10D5F960
// FUNCTION: ENGINE 0x10D5F990
// FUNCTION: ENGINE 0x10D5F9C0
// FUNCTION: ENGINE 0x10D5F9F0
// FUNCTION: ENGINE 0x10D5FA20
// FUNCTION: ENGINE 0x10D5FA70
// FUNCTION: ENGINE 0x10D5FD30
// FUNCTION: ENGINE 0x10D5FD60
// FUNCTION: ENGINE 0x10D5FD90
// FUNCTION: ENGINE 0x10D5FDC0
// FUNCTION: ENGINE 0x10D5FE40
// FUNCTION: ENGINE 0x10D5FF60
// FUNCTION: ENGINE 0x10D5FF90
// FUNCTION: ENGINE 0x10D5FFC0
// FUNCTION: ENGINE 0x10D85320
// FUNCTION: ENGINE 0x10D85330
// FUNCTION: ENGINE 0x10D85340
// FUNCTION: ENGINE 0x10D85350
// FUNCTION: ENGINE 0x10D85360
// FUNCTION: ENGINE 0x10D85370
// FUNCTION: ENGINE 0x10D85380
// FUNCTION: ENGINE 0x10D85390
// FUNCTION: ENGINE 0x10D853A0
// FUNCTION: ENGINE 0x10D853B0
// FUNCTION: ENGINE 0x10D853C0
// FUNCTION: ENGINE 0x10D853D0
// FUNCTION: ENGINE 0x10D853E0
// FUNCTION: ENGINE 0x10D853F0
// FUNCTION: ENGINE 0x10D85400
// FUNCTION: ENGINE 0x10D85410
// FUNCTION: ENGINE 0x10D85420
// FUNCTION: ENGINE 0x10D85440
// FUNCTION: ENGINE 0x10D85450
// FUNCTION: ENGINE 0x10D85460
// FUNCTION: ENGINE 0x10D85470
// FUNCTION: ENGINE 0x10D85480
// FUNCTION: ENGINE 0x10D85490
// FUNCTION: ENGINE 0x10D854A0
// FUNCTION: ENGINE 0x10D854B0
// FUNCTION: ENGINE 0x10D854C0
// FUNCTION: ENGINE 0x10D854D0
// FUNCTION: ENGINE 0x10D854F0
// FUNCTION: ENGINE 0x10D85500
// FUNCTION: ENGINE 0x10D85510
// FUNCTION: ENGINE 0x10D85520
// FUNCTION: ENGINE 0x10D85530
// FUNCTION: ENGINE 0x10D85550
// FUNCTION: ENGINE 0x10D85560
// FUNCTION: ENGINE 0x10D85570
