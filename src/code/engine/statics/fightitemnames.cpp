// Globals that the engine's static initialisers 0x10D60010 - 0x10D626E0 construct in translation units whose code is not
// reconstructed: the slot group, listener and enum names of the fight item units (motion, hit, space and surface tables), and the names and strings every such unit repeats through its headers (the
// slot group names, the audio file and listener names). Unit name guess; one file holds the runs of several units.
#include "code/core/name.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/om/staticinit.h"

namespace engine
{
	om::ClassName gListener = om::NameOfText("Listener");
	om::ClassName gMaster = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gLocationGroup("LocationGroup", 0);
	om::String gAudioGlobalP3d = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener2 = om::NameOfText("Listener");
	om::ClassName gMaster2 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup5("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty("", 0);
	om::String gAudioGlobalP3d2 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener3 = om::NameOfText("Listener");
	om::ClassName gMaster3 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup6("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty2("", 0);
	MessageListeners gScenario("scenario", 0);
	core::Name<core::CaseSensitiveKey> gAd256x128("Ad256x128", 0);
	core::Name<core::CaseSensitiveKey> gAd128x256A("Ad128x256A", 0);
	core::Name<core::CaseSensitiveKey> gAd128x256B("Ad128x256B", 0);
	om::String gAudioGlobalP3d3 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener4 = om::NameOfText("Listener");
	om::ClassName gMaster4 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup7("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty3("", 0);
	MessageListeners gScenario2("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup8("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty4("", 0);
	om::String gAudioGlobalP3d4 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener5 = om::NameOfText("Listener");
	om::ClassName gMaster5 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup9("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty5("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup10("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty6("", 0);
	core::Name<core::CaseSensitiveKey> gHintCollectible("hintCollectible", 0);
	core::Name<core::CaseSensitiveKey> gLocationCollectible("locationCollectible", 0);
	fight::EnumEntry gHitOriginatorTable[5] =
	{
		{ fight::Name("Hit Originator", 0) },
		{ fight::Name("Game Object", 0) },
		{ fight::Name("Grab Slot", 0) },
		{ fight::Name("Parent Game Object", 0) },
		{ fight::Name("Player", 0) }
	};
	om::String gAudioGlobalP3d5 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener6 = om::NameOfText("Listener");
	om::ClassName gMaster6 = om::NameOfText("Master");
	fight::EnumEntry gGeneralTable[2] =
	{
		{ fight::Name("General", 0) },
		{ fight::Name("Treadmark", 0) }
	};
	om::String gAudioGlobalP3d6 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener7 = om::NameOfText("Listener");
	om::ClassName gMaster7 = om::NameOfText("Master");
	fight::EnumEntry gNoneTable[3] =
	{
		{ fight::Name("none", 0) },
		{ fight::Name("Receiver", 0) },
		{ fight::Name("Giver", 0) }
	};
	fight::EnumEntry gGameObjectSpaceTable[3] =
	{
		{ fight::Name("Game Object Space", 0) },
		{ fight::Name("Joint Space", 0) },
		{ fight::Name("Find Nearest Joint Space", 0) }
	};
	fight::EnumEntry gSurfaceNormalSpaceTable[5] =
	{
		{ fight::Name("Surface Normal Space", 0) },
		{ fight::Name("Impulse Direction Space", 0) },
		{ fight::Name("Hit Volume Direction Space", 0) },
		{ fight::Name("Interpolate Between Impulse and Hit Volume Direction Space", 0) },
		{ fight::Name("Joint Space", 0) }
	};
	fight::EnumEntry gGeneralTable2[12] =
	{
		{ fight::Name("General", 0) },
		{ fight::Name("Main character", 0) },
		{ fight::Name("Character", 0) },
		{ fight::Name("Ambient", 0) },
		{ fight::Name("Persistent", 0) },
		{ fight::Name("Explosion", 0) },
		{ fight::Name("Squib", 0) },
		{ fight::Name("Tracer", 0) },
		{ fight::Name("Bloodtox", 0) },
		{ fight::Name("Gameplay", 0) },
		{ fight::Name("Devastator", 0) },
		{ fight::Name("Collectible", 0) }
	};
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup11("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty7("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup12("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty8("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup13("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty9("", 0);
	core::Name<core::CaseSensitiveKey> gDefault0("default[0]", 0);
	core::Name<core::CaseSensitiveKey> gDay0("day[0]", 0);
	core::Name<core::CaseSensitiveKey> gInfected("infected", 0);
	core::Name<core::CaseSensitiveKey> gInfected2("Infected", 0);
	core::Name<core::CaseSensitiveKey> gDay02("day[0]", 0);
	core::Name<core::CaseSensitiveKey> gLowhealth("Lowhealth", 0);
	core::Name<core::CaseSensitiveKey> gFx("fx", 0);
	core::Name<core::CaseSensitiveKey> gLowhealth2("lowhealth", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup14("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty10("", 0);
	core::Name<core::CaseSensitiveKey> gEncounterObject("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter("encounter", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup15("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty11("", 0);
	core::Name<core::CaseSensitiveKey> gEncounterObject2("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter2("encounter", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup16("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty12("", 0);
	MessageListeners gScenario3("scenario", 0);
	core::Name<core::CaseSensitiveKey> gEncounterObject3("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter3("encounter", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup17("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty13("", 0);
	MessageListeners gScenario4("scenario", 0);
	core::Name<core::CaseSensitiveKey> gEncounterObject4("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter4("encounter", 0);
	MessageListeners gScenario5("scenario", 0);
	core::Name<core::CaseSensitiveKey> gEncounterObject5("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter5("encounter", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup18("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty14("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup19("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty15("", 0);
	MessageListeners gScenario6("scenario", 0);
	core::Name<core::CaseSensitiveKey> gWoi("Woi", 0);
	core::Name<core::CaseSensitiveKey> gWOITargetPresentation("WOITargetPresentation", 0);
	core::Name<core::CaseSensitiveKey> gMale("male", 0);
	core::Name<core::CaseSensitiveKey> gFemale("female", 0);
	core::Name<core::CaseSensitiveKey> gConsumed("Consumed", 0);
	MessageListeners gScenario7("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup20("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty16("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup21("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty17("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup22("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty18("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup23("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty19("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup24("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty20("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup25("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty21("", 0);
	core::Name<core::CaseSensitiveKey> gDefault("default", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup26("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty22("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup27("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty23("", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour("AlexArmour", 0);
	MessageListeners gScenario8("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup28("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty24("", 0);
	MessageListeners gScenario9("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup29("Undefined_SlotGroup", 0);
}

// The dynamic initialisers and atexit stubs of the unit's globals:
// FUNCTION: ENGINE 0x10D60010
// FUNCTION: ENGINE 0x10D60070
// FUNCTION: ENGINE 0x10D600D0
// FUNCTION: ENGINE 0x10D60100
// FUNCTION: ENGINE 0x10D60150
// FUNCTION: ENGINE 0x10D601B0
// FUNCTION: ENGINE 0x10D60210
// FUNCTION: ENGINE 0x10D60240
// FUNCTION: ENGINE 0x10D60970
// FUNCTION: ENGINE 0x10D609C0
// FUNCTION: ENGINE 0x10D60A20
// FUNCTION: ENGINE 0x10D60A80
// FUNCTION: ENGINE 0x10D60AB0
// FUNCTION: ENGINE 0x10D60AE0
// FUNCTION: ENGINE 0x10D60B10
// FUNCTION: ENGINE 0x10D60B40
// FUNCTION: ENGINE 0x10D60B70
// FUNCTION: ENGINE 0x10D60FB0
// FUNCTION: ENGINE 0x10D61000
// FUNCTION: ENGINE 0x10D61060
// FUNCTION: ENGINE 0x10D610C0
// FUNCTION: ENGINE 0x10D610F0
// FUNCTION: ENGINE 0x10D61120
// FUNCTION: ENGINE 0x10D61150
// FUNCTION: ENGINE 0x10D61180
// FUNCTION: ENGINE 0x10D611B0
// FUNCTION: ENGINE 0x10D61200
// FUNCTION: ENGINE 0x10D61260
// FUNCTION: ENGINE 0x10D612C0
// FUNCTION: ENGINE 0x10D612F0
// FUNCTION: ENGINE 0x10D61340
// FUNCTION: ENGINE 0x10D61370
// FUNCTION: ENGINE 0x10D613A0
// FUNCTION: ENGINE 0x10D613D0
// FUNCTION: ENGINE 0x10D61480
// FUNCTION: ENGINE 0x10D61500
// FUNCTION: ENGINE 0x10D61550
// FUNCTION: ENGINE 0x10D615B0
// FUNCTION: ENGINE 0x10D61610
// FUNCTION: ENGINE 0x10D61650
// FUNCTION: ENGINE 0x10D616A0
// FUNCTION: ENGINE 0x10D61700
// FUNCTION: ENGINE 0x10D61760
// FUNCTION: ENGINE 0x10D617B0
// FUNCTION: ENGINE 0x10D61800
// FUNCTION: ENGINE 0x10D61880
// FUNCTION: ENGINE 0x10D61990
// FUNCTION: ENGINE 0x10D619C0
// FUNCTION: ENGINE 0x10D619F0
// FUNCTION: ENGINE 0x10D61A20
// FUNCTION: ENGINE 0x10D61A50
// FUNCTION: ENGINE 0x10D61A80
// FUNCTION: ENGINE 0x10D61AB0
// FUNCTION: ENGINE 0x10D61AE0
// FUNCTION: ENGINE 0x10D61B10
// FUNCTION: ENGINE 0x10D61B40
// FUNCTION: ENGINE 0x10D61B70
// FUNCTION: ENGINE 0x10D61BA0
// FUNCTION: ENGINE 0x10D61BD0
// FUNCTION: ENGINE 0x10D61C00
// FUNCTION: ENGINE 0x10D61C30
// FUNCTION: ENGINE 0x10D61C60
// FUNCTION: ENGINE 0x10D61C90
// FUNCTION: ENGINE 0x10D61CC0
// FUNCTION: ENGINE 0x10D61CF0
// FUNCTION: ENGINE 0x10D61D20
// FUNCTION: ENGINE 0x10D61D50
// FUNCTION: ENGINE 0x10D61D80
// FUNCTION: ENGINE 0x10D61DB0
// FUNCTION: ENGINE 0x10D61DE0
// FUNCTION: ENGINE 0x10D61E10
// FUNCTION: ENGINE 0x10D61E40
// FUNCTION: ENGINE 0x10D61E70
// FUNCTION: ENGINE 0x10D61EA0
// FUNCTION: ENGINE 0x10D61ED0
// FUNCTION: ENGINE 0x10D61F00
// FUNCTION: ENGINE 0x10D61F30
// FUNCTION: ENGINE 0x10D61F60
// FUNCTION: ENGINE 0x10D61F90
// FUNCTION: ENGINE 0x10D61FC0
// FUNCTION: ENGINE 0x10D61FF0
// FUNCTION: ENGINE 0x10D62020
// FUNCTION: ENGINE 0x10D62050
// FUNCTION: ENGINE 0x10D62080
// FUNCTION: ENGINE 0x10D620B0
// FUNCTION: ENGINE 0x10D620E0
// FUNCTION: ENGINE 0x10D62110
// FUNCTION: ENGINE 0x10D62140
// FUNCTION: ENGINE 0x10D62170
// FUNCTION: ENGINE 0x10D621A0
// FUNCTION: ENGINE 0x10D621D0
// FUNCTION: ENGINE 0x10D62200
// FUNCTION: ENGINE 0x10D62230
// FUNCTION: ENGINE 0x10D62260
// FUNCTION: ENGINE 0x10D62290
// FUNCTION: ENGINE 0x10D622C0
// FUNCTION: ENGINE 0x10D622F0
// FUNCTION: ENGINE 0x10D62320
// FUNCTION: ENGINE 0x10D62360
// FUNCTION: ENGINE 0x10D62390
// FUNCTION: ENGINE 0x10D623C0
// FUNCTION: ENGINE 0x10D623F0
// FUNCTION: ENGINE 0x10D62420
// FUNCTION: ENGINE 0x10D62450
// FUNCTION: ENGINE 0x10D62480
// FUNCTION: ENGINE 0x10D624B0
// FUNCTION: ENGINE 0x10D624E0
// FUNCTION: ENGINE 0x10D62510
// FUNCTION: ENGINE 0x10D62540
// FUNCTION: ENGINE 0x10D62570
// FUNCTION: ENGINE 0x10D625A0
// FUNCTION: ENGINE 0x10D625D0
// FUNCTION: ENGINE 0x10D62600
// FUNCTION: ENGINE 0x10D626B0
// FUNCTION: ENGINE 0x10D626E0
// FUNCTION: ENGINE 0x10D85580
// FUNCTION: ENGINE 0x10D85590
// FUNCTION: ENGINE 0x10D855A0
// FUNCTION: ENGINE 0x10D855B0
// FUNCTION: ENGINE 0x10D85820
// FUNCTION: ENGINE 0x10D85830
// FUNCTION: ENGINE 0x10D85840
// FUNCTION: ENGINE 0x10D85850
// FUNCTION: ENGINE 0x10D85860
// FUNCTION: ENGINE 0x10D85870
// FUNCTION: ENGINE 0x10D85880
// FUNCTION: ENGINE 0x10D85920
// FUNCTION: ENGINE 0x10D85930
// FUNCTION: ENGINE 0x10D85940
// FUNCTION: ENGINE 0x10D85950
// FUNCTION: ENGINE 0x10D85960
// FUNCTION: ENGINE 0x10D85970
// FUNCTION: ENGINE 0x10D85980
// FUNCTION: ENGINE 0x10D85990
// FUNCTION: ENGINE 0x10D859A0
// FUNCTION: ENGINE 0x10D859F0
// FUNCTION: ENGINE 0x10D85A00
// FUNCTION: ENGINE 0x10D85A10
// FUNCTION: ENGINE 0x10D85A20
// FUNCTION: ENGINE 0x10D85A70
// FUNCTION: ENGINE 0x10D85A80
// FUNCTION: ENGINE 0x10D85A90
// FUNCTION: ENGINE 0x10D85AA0
// FUNCTION: ENGINE 0x10D85AB0
// FUNCTION: ENGINE 0x10D85AC0
// FUNCTION: ENGINE 0x10D85AD0
// FUNCTION: ENGINE 0x10D85AE0
// FUNCTION: ENGINE 0x10D85B00
// FUNCTION: ENGINE 0x10D85B10
// FUNCTION: ENGINE 0x10D85B20
// FUNCTION: ENGINE 0x10D85B30
// FUNCTION: ENGINE 0x10D85B40
// FUNCTION: ENGINE 0x10D85B50
// FUNCTION: ENGINE 0x10D85B60
// FUNCTION: ENGINE 0x10D85B70
// FUNCTION: ENGINE 0x10D85B80
// FUNCTION: ENGINE 0x10D85B90
// FUNCTION: ENGINE 0x10D85BA0
// FUNCTION: ENGINE 0x10D85BB0
// FUNCTION: ENGINE 0x10D85BC0
// FUNCTION: ENGINE 0x10D85BD0
// FUNCTION: ENGINE 0x10D85C50
// FUNCTION: ENGINE 0x10D85C60
// FUNCTION: ENGINE 0x10D85D70
// FUNCTION: ENGINE 0x10D85D80
// FUNCTION: ENGINE 0x10D85D90
// FUNCTION: ENGINE 0x10D85DA0
// FUNCTION: ENGINE 0x10D85DB0
// FUNCTION: ENGINE 0x10D85DC0
// FUNCTION: ENGINE 0x10D85DD0
// FUNCTION: ENGINE 0x10D85DE0
// FUNCTION: ENGINE 0x10D85DF0
// FUNCTION: ENGINE 0x10D85E00
// FUNCTION: ENGINE 0x10D85E10
// FUNCTION: ENGINE 0x10D85E20
// FUNCTION: ENGINE 0x10D85E30
// FUNCTION: ENGINE 0x10D85E40
// FUNCTION: ENGINE 0x10D85E50
// FUNCTION: ENGINE 0x10D85E60
// FUNCTION: ENGINE 0x10D85E70
// FUNCTION: ENGINE 0x10D85E80
// FUNCTION: ENGINE 0x10D85E90
// FUNCTION: ENGINE 0x10D85EA0
// FUNCTION: ENGINE 0x10D85EB0
// FUNCTION: ENGINE 0x10D85EC0
// FUNCTION: ENGINE 0x10D85ED0
// FUNCTION: ENGINE 0x10D85EE0
// FUNCTION: ENGINE 0x10D85EF0
// FUNCTION: ENGINE 0x10D85F00
// FUNCTION: ENGINE 0x10D85F10
// FUNCTION: ENGINE 0x10D85F20
// FUNCTION: ENGINE 0x10D85F30
// FUNCTION: ENGINE 0x10D85F40
// FUNCTION: ENGINE 0x10D85F50
// FUNCTION: ENGINE 0x10D85F60
// FUNCTION: ENGINE 0x10D85F70
// FUNCTION: ENGINE 0x10D85F80
// FUNCTION: ENGINE 0x10D85F90
// FUNCTION: ENGINE 0x10D85FA0
// FUNCTION: ENGINE 0x10D86010
// FUNCTION: ENGINE 0x10D86020
// FUNCTION: ENGINE 0x10D86030
// FUNCTION: ENGINE 0x10D86040
// FUNCTION: ENGINE 0x10D86050
// FUNCTION: ENGINE 0x10D86060
// FUNCTION: ENGINE 0x10D86070
// FUNCTION: ENGINE 0x10D86090
// FUNCTION: ENGINE 0x10D860A0
// FUNCTION: ENGINE 0x10D860B0
// FUNCTION: ENGINE 0x10D860C0
// FUNCTION: ENGINE 0x10D860D0
// FUNCTION: ENGINE 0x10D860E0
// FUNCTION: ENGINE 0x10D860F0
// FUNCTION: ENGINE 0x10D86100
// FUNCTION: ENGINE 0x10D86120
// FUNCTION: ENGINE 0x10D86130
