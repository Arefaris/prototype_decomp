// Globals that the engine's static initialisers 0x10D58000 - 0x10D5B2F0 construct in translation units whose code is not
// reconstructed: the incident, reaction, faction, vehicle state and package slot group names, and the names and strings every such unit repeats through its headers (the
// slot group names, the audio file and listener names). Unit name guess; one file holds the runs of several units.
#include "code/core/name.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/om/staticinit.h"

namespace engine
{
	core::Name<core::CaseSensitiveKey> gEmpty193("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup185("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty194("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup186("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty195("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup187("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty196("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup188("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty197("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup189("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty198("", 0);
	MessageListeners gScenario65("scenario", 0);
	core::Name<core::CaseSensitiveKey> gHighLod2("high_lod", 0);
	core::Name<core::CaseSensitiveKey> gMediumLod("medium_lod", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup190("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty199("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup191("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty200("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup192("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty201("", 0);
	core::Name<core::CaseSensitiveKey> gIncidentLanding("IncidentLanding", 0);
	core::Name<core::CaseSensitiveKey> gIncidentPunch("IncidentPunch", 0);
	core::Name<core::CaseSensitiveKey> gIncidentConsume("IncidentConsume", 0);
	core::Name<core::CaseSensitiveKey> gIncidentShapeshift("IncidentShapeshift", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup193("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty202("", 0);
	MessageListeners gScenario66("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup194("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty203("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup195("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty204("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup196("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty205("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup197("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty206("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup198("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty207("", 0);
	MessageListeners gScenario67("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup199("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty208("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup200("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty209("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup201("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty210("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup202("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty211("", 0);
	core::Name<core::CaseSensitiveKey> gThreatBall2("threatBall", 0);
	core::Name<core::CaseSensitiveKey> gThreat("threat", 0);
	core::Name<core::CaseSensitiveKey> gDiversion("diversion", 0);
	core::Name<core::CaseSensitiveKey> gTrafficPanicSource("trafficPanicSource", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup203("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty212("", 0);
	core::Name<core::CaseSensitiveKey> gPoliceCar("police_car", 0);
	core::Name<core::CaseSensitiveKey> gTruckOS003("truckOS003", 0);
	core::Name<core::CaseSensitiveKey> gPedSoldMedLod("ped_sold_med_lod", 0);
	core::Name<core::CaseSensitiveKey> gPedMCauPlc01("ped_m_cau_plc_01", 0);
	core::Name<core::CaseSensitiveKey> gDefault2("default", 0);
	core::Name<core::CaseSensitiveKey> gVehicleState("vehicle_state", 0);
	core::Name<core::CaseSensitiveKey> gInitial("initial", 0);
	core::Name<core::CaseSensitiveKey> gParked("parked", 0);
	core::Name<core::CaseSensitiveKey> gDerelict("derelict", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup204("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty213("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup205("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty214("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup206("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty215("", 0);
	MessageListeners gScenario68("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup207("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty216("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup208("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty217("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup209("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty218("", 0);
	core::Name<core::CaseSensitiveKey> gTranstionAnimation("transtionAnimation", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup210("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty219("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup211("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty220("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup212("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty221("", 0);
	MessageListeners gScenario69("scenario", 0);
	core::Name<core::CaseSensitiveKey> gHuman("human", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup213("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty222("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup214("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty223("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup215("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty224("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup216("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty225("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup217("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty226("", 0);
	core::Name<core::CaseSensitiveKey> gHighLod3("high_lod", 0);
	core::Name<core::CaseSensitiveKey> gMediumLod2("medium_lod", 0);
	core::Name<core::CaseSensitiveKey> gCrushed("crushed", 0);
	core::Name<core::CaseSensitiveKey> gCivilianCar("civilian_car", 0);
	core::Name<core::CaseSensitiveKey> gInitial2("initial", 0);
	core::Name<core::CaseSensitiveKey> gCarCollision("carCollision", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup218("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty227("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup219("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty228("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup220("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty229("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup221("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty230("", 0);
	core::Name<core::CaseInsensitiveKey32> gCaseInsensitiveKey32Object14;
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup222("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty231("", 0);
	core::Name<core::CaseSensitiveKey> gGoto("goto", 0);
	core::Name<core::CaseSensitiveKey> gDumbGoto("dumb_goto", 0);
	core::Name<core::CaseSensitiveKey> gFinal3("final", 0);
	core::Name<core::CaseSensitiveKey> gPatrol("patrol", 0);
	core::Name<core::CaseSensitiveKey> gCombatPatrol("combatPatrol", 0);
	core::Name<core::CaseSensitiveKey> gMotionRoot("Motion_Root", 0);
	core::Name<core::CaseSensitiveKey> gMotionRoot1("Motion_Root1", 0);
	core::Name<core::CaseSensitiveKey> gGunRotate("gun_rotate", 0);
	core::Name<core::CaseSensitiveKey> gGunRotate1("gun_rotate1", 0);
	core::Name<core::CaseSensitiveKey> gGrappleCockpitBackSeat("Grapple_Cockpit_back_seat", 0);
	core::Name<core::CaseSensitiveKey> gGrappleCockpitFrontSeat("Grapple_Cockpit_front_seat", 0);
	core::Name<core::CaseSensitiveKey> gPatrolMode("patrolMode", 0);
	core::Name<core::CaseSensitiveKey> gCombat2("Combat", 0);
	core::Name<core::CaseSensitiveKey> gRocketLauncher("rocketLauncher", 0);
	core::Name<core::CaseSensitiveKey> gGrenadeLauncher("grenadeLauncher", 0);
	core::Name<core::CaseSensitiveKey> gImpale("Impale", 0);
	om::String gAudioGlobalP3d37 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener38 = om::NameOfText("Listener");
	om::ClassName gMaster38 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup223("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty232("", 0);
	core::Name<core::CaseSensitiveKey> gEncounterObject13("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter13("encounter", 0);
	MessageListeners gScenario70("scenario", 0);
	core::Name<core::CaseInsensitiveKey32> gPulse("Pulse", 0);
	MessageListeners gScenario71("scenario", 0);
	core::Name<core::CaseSensitiveKey> gStatRifleShots("Stat: Rifle Shots", 0);
	core::Name<core::CaseSensitiveKey> gStatMachinegunShots("Stat: Machinegun Shots", 0);
	core::Name<core::CaseSensitiveKey> gRifleAmmoPlayer("rifle_ammo_player", 0);
	core::Name<core::CaseSensitiveKey> gSawAmmoPlayer("saw_ammo_player", 0);
	core::Name<core::CaseSensitiveKey> gEncounterObject14("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter14("encounter", 0);
	MessageListeners gScenario72("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup224("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty233("", 0);
	core::Name<core::CaseSensitiveKey> gInitial3("initial", 0);
	core::Name<core::CaseSensitiveKey> gMid("mid", 0);
	core::Name<core::CaseSensitiveKey> gFinal4("final", 0);
	core::Name<core::CaseSensitiveKey> gStatGrenadeShots("Stat: Grenade Shots", 0);
	core::Name<core::CaseSensitiveKey> gStatMissileShots("Stat: Missile Shots", 0);
	core::Name<core::CaseSensitiveKey> gStatHomingShots("Stat: Homing Shots", 0);
	MessageListeners gScenario73("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup225("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty234("", 0);
	MessageListeners gScenario74("scenario", 0);
	MessageListeners gScenario75("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup226("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty235("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup227("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty236("", 0);
	core::Name<core::CaseSensitiveKey> gFaction("faction", 0);
	core::Name<core::CaseSensitiveKey> gCivilian("civilian", 0);
	core::Name<core::CaseSensitiveKey> gMilitary("military", 0);
	core::Name<core::CaseSensitiveKey> gCommander4("commander", 0);
	core::Name<core::CaseSensitiveKey> gInfected3("infected", 0);
	core::Name<core::CaseSensitiveKey> gAlex3("alex", 0);
	core::Name<core::CaseSensitiveKey> gPowered("powered", 0);
	core::Name<core::CaseSensitiveKey> gChameleon("chameleon", 0);
	core::Name<core::CaseSensitiveKey> gBlown("blown", 0);
	core::Name<core::CaseSensitiveKey> gUav3("uav", 0);
	core::Name<core::CaseSensitiveKey> gTank2("tank", 0);
	core::Name<core::CaseSensitiveKey> gHelicopter2("helicopter", 0);
	core::Name<core::CaseSensitiveKey> gBlackwatch3("blackwatch", 0);
	core::Name<core::CaseSensitiveKey> gBwcommander("bwcommander", 0);
	core::Name<core::CaseSensitiveKey> gPedestrian2("pedestrian", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup228("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty237("", 0);
	om::String gAudioGlobalP3d38 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener39 = om::NameOfText("Listener");
	om::ClassName gMaster39 = om::NameOfText("Master");
	MessageListeners gScenario76("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup229("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty238("", 0);
	om::String gAudioGlobalP3d39 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener40 = om::NameOfText("Listener");
	om::ClassName gMaster40 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gEncounterObject15("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter15("encounter", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour27("AlexArmour", 0);
	MessageListeners gScenario77("scenario", 0);
	core::Name<core::CaseSensitiveKey> gPerishable("perishable__", 0);
	core::Name<core::CaseSensitiveKey> gProxyDriver0("ProxyDriver_0", 0);
	fight::EnumEntry gPermanentMissionPackageSlotGroupTable[8] =
		{
			{ fight::Name("PermanentMissionPackageSlotGroup", 0) },
			{ fight::Name("MissionPackageSlotGroup", 0) },
			{ fight::Name("MissionScriptGroup", 0) },
			{ fight::Name("DynamicPackageSlotGroup", 0) },
			{ fight::Name("AirUnitPackageSlotGroup", 0) },
			{ fight::Name("ArmorUnitPackageSlotGroup", 0) },
			{ fight::Name("MissionChapterScriptGroup", 0) },
			{ fight::Name("MissionScriptGroup", 0) }
		};
	core::Name<core::CaseSensitiveKey> gWorldCellGroup("WorldCellGroup", 0);
	core::Name<core::CaseSensitiveKey> gPermanentCharacterPackageSlotGroup("PermanentCharacterPackageSlotGroup", 0);
	MessageListeners gScenario78("scenario", 0);
	core::Name<core::CaseSensitiveKey> gARMORTankRamMarine("ARMOR_tank_ram_marine", 0);
	core::Name<core::CaseSensitiveKey> gARMORApcM2Marine("ARMOR_apc_m2_marine", 0);
	core::Name<core::CaseSensitiveKey> gARMORF45Thunder001Military("ARMOR_f45Thunder001Military", 0);
	core::Name<core::CaseSensitiveKey> gAIRHeliGunshipMarineCore("AIR_heli_gunship_marine_core", 0);
	core::Name<core::CaseSensitiveKey> gAIRHeliBhMarine("AIR_heli_bh_marine", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup230("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty239("", 0);
	core::Name<core::CaseSensitiveKey> gEncounterObject16("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter16("encounter", 0);
	om::String gAudioGlobalP3d40 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener41 = om::NameOfText("Listener");
	om::ClassName gMaster41 = om::NameOfText("Master");
	MessageListeners gScenario79("scenario", 0);
	MessageListeners gScenario80("scenario", 0);
	MessageListeners gScenario81("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup231("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty240("", 0);
	MessageListeners gScenario82("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup232("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty241("", 0);
	MessageListeners gScenario83("scenario", 0);
	core::Name<core::CaseSensitiveKey> gCorpseWeight("corpseWeight", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup233("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty242("", 0);
	om::String gAudioGlobalP3d41 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener42 = om::NameOfText("Listener");
	om::ClassName gMaster42 = om::NameOfText("Master");
	MessageListeners gScenario84("scenario", 0);
	core::Name<core::CaseSensitiveKey> gAttacker2("Attacker", 0);
}

// The dynamic initialisers and atexit stubs of the unit's globals:
// FUNCTION: ENGINE 0x10D58000
// FUNCTION: ENGINE 0x10D58030
// FUNCTION: ENGINE 0x10D58060
// FUNCTION: ENGINE 0x10D58090
// FUNCTION: ENGINE 0x10D580C0
// FUNCTION: ENGINE 0x10D580F0
// FUNCTION: ENGINE 0x10D58120
// FUNCTION: ENGINE 0x10D58150
// FUNCTION: ENGINE 0x10D58180
// FUNCTION: ENGINE 0x10D581B0
// FUNCTION: ENGINE 0x10D581E0
// FUNCTION: ENGINE 0x10D58210
// FUNCTION: ENGINE 0x10D58240
// FUNCTION: ENGINE 0x10D58270
// FUNCTION: ENGINE 0x10D582A0
// FUNCTION: ENGINE 0x10D582D0
// FUNCTION: ENGINE 0x10D58300
// FUNCTION: ENGINE 0x10D58330
// FUNCTION: ENGINE 0x10D58360
// FUNCTION: ENGINE 0x10D58390
// FUNCTION: ENGINE 0x10D583C0
// FUNCTION: ENGINE 0x10D583F0
// FUNCTION: ENGINE 0x10D58420
// FUNCTION: ENGINE 0x10D58450
// FUNCTION: ENGINE 0x10D58480
// FUNCTION: ENGINE 0x10D584B0
// FUNCTION: ENGINE 0x10D584E0
// FUNCTION: ENGINE 0x10D58510
// FUNCTION: ENGINE 0x10D58540
// FUNCTION: ENGINE 0x10D58570
// FUNCTION: ENGINE 0x10D585A0
// FUNCTION: ENGINE 0x10D585D0
// FUNCTION: ENGINE 0x10D58600
// FUNCTION: ENGINE 0x10D58630
// FUNCTION: ENGINE 0x10D58660
// FUNCTION: ENGINE 0x10D58690
// FUNCTION: ENGINE 0x10D586C0
// FUNCTION: ENGINE 0x10D586F0
// FUNCTION: ENGINE 0x10D58720
// FUNCTION: ENGINE 0x10D58750
// FUNCTION: ENGINE 0x10D58780
// FUNCTION: ENGINE 0x10D587B0
// FUNCTION: ENGINE 0x10D587E0
// FUNCTION: ENGINE 0x10D58810
// FUNCTION: ENGINE 0x10D58840
// FUNCTION: ENGINE 0x10D58870
// FUNCTION: ENGINE 0x10D588A0
// FUNCTION: ENGINE 0x10D588D0
// FUNCTION: ENGINE 0x10D58900
// FUNCTION: ENGINE 0x10D58930
// FUNCTION: ENGINE 0x10D58960
// FUNCTION: ENGINE 0x10D58990
// FUNCTION: ENGINE 0x10D589D0
// FUNCTION: ENGINE 0x10D58A00
// FUNCTION: ENGINE 0x10D58A30
// FUNCTION: ENGINE 0x10D58A60
// FUNCTION: ENGINE 0x10D58A90
// FUNCTION: ENGINE 0x10D58AC0
// FUNCTION: ENGINE 0x10D58AF0
// FUNCTION: ENGINE 0x10D58B20
// FUNCTION: ENGINE 0x10D58B50
// FUNCTION: ENGINE 0x10D58F20
// FUNCTION: ENGINE 0x10D58F50
// FUNCTION: ENGINE 0x10D58F80
// FUNCTION: ENGINE 0x10D58FB0
// FUNCTION: ENGINE 0x10D58FE0
// FUNCTION: ENGINE 0x10D59010
// FUNCTION: ENGINE 0x10D59040
// FUNCTION: ENGINE 0x10D59070
// FUNCTION: ENGINE 0x10D590A0
// FUNCTION: ENGINE 0x10D590D0
// FUNCTION: ENGINE 0x10D59100
// FUNCTION: ENGINE 0x10D59130
// FUNCTION: ENGINE 0x10D59160
// FUNCTION: ENGINE 0x10D59190
// FUNCTION: ENGINE 0x10D591C0
// FUNCTION: ENGINE 0x10D591F0
// FUNCTION: ENGINE 0x10D59220
// FUNCTION: ENGINE 0x10D59250
// FUNCTION: ENGINE 0x10D59280
// FUNCTION: ENGINE 0x10D592B0
// FUNCTION: ENGINE 0x10D592E0
// FUNCTION: ENGINE 0x10D59310
// FUNCTION: ENGINE 0x10D594E0
// FUNCTION: ENGINE 0x10D59510
// FUNCTION: ENGINE 0x10D59550
// FUNCTION: ENGINE 0x10D59580
// FUNCTION: ENGINE 0x10D595C0
// FUNCTION: ENGINE 0x10D595F0
// FUNCTION: ENGINE 0x10D59630
// FUNCTION: ENGINE 0x10D59660
// FUNCTION: ENGINE 0x10D596B0
// FUNCTION: ENGINE 0x10D596E0
// FUNCTION: ENGINE 0x10D59720
// FUNCTION: ENGINE 0x10D59750
// FUNCTION: ENGINE 0x10D59780
// FUNCTION: ENGINE 0x10D597B0
// FUNCTION: ENGINE 0x10D597E0
// FUNCTION: ENGINE 0x10D59810
// FUNCTION: ENGINE 0x10D59870
// FUNCTION: ENGINE 0x10D598A0
// FUNCTION: ENGINE 0x10D598D0
// FUNCTION: ENGINE 0x10D59900
// FUNCTION: ENGINE 0x10D59930
// FUNCTION: ENGINE 0x10D59960
// FUNCTION: ENGINE 0x10D59990
// FUNCTION: ENGINE 0x10D599C0
// FUNCTION: ENGINE 0x10D59A00
// FUNCTION: ENGINE 0x10D59A20
// FUNCTION: ENGINE 0x10D59A50
// FUNCTION: ENGINE 0x10D59A80
// FUNCTION: ENGINE 0x10D59AB0
// FUNCTION: ENGINE 0x10D59AE0
// FUNCTION: ENGINE 0x10D59B10
// FUNCTION: ENGINE 0x10D59B40
// FUNCTION: ENGINE 0x10D59B70
// FUNCTION: ENGINE 0x10D59BA0
// FUNCTION: ENGINE 0x10D59BD0
// FUNCTION: ENGINE 0x10D59C00
// FUNCTION: ENGINE 0x10D59C30
// FUNCTION: ENGINE 0x10D59C60
// FUNCTION: ENGINE 0x10D59C90
// FUNCTION: ENGINE 0x10D59CC0
// FUNCTION: ENGINE 0x10D59CF0
// FUNCTION: ENGINE 0x10D59D20
// FUNCTION: ENGINE 0x10D59D50
// FUNCTION: ENGINE 0x10D59D80
// FUNCTION: ENGINE 0x10D59DD0
// FUNCTION: ENGINE 0x10D59E30
// FUNCTION: ENGINE 0x10D59E90
// FUNCTION: ENGINE 0x10D59EC0
// FUNCTION: ENGINE 0x10D59EF0
// FUNCTION: ENGINE 0x10D59F20
// FUNCTION: ENGINE 0x10D59F50
// FUNCTION: ENGINE 0x10D59F80
// FUNCTION: ENGINE 0x10D59FB0
// FUNCTION: ENGINE 0x10D59FE0
// FUNCTION: ENGINE 0x10D5A010
// FUNCTION: ENGINE 0x10D5A040
// FUNCTION: ENGINE 0x10D5A070
// FUNCTION: ENGINE 0x10D5A0A0
// FUNCTION: ENGINE 0x10D5A0D0
// FUNCTION: ENGINE 0x10D5A100
// FUNCTION: ENGINE 0x10D5A130
// FUNCTION: ENGINE 0x10D5A160
// FUNCTION: ENGINE 0x10D5A190
// FUNCTION: ENGINE 0x10D5A1C0
// FUNCTION: ENGINE 0x10D5A1F0
// FUNCTION: ENGINE 0x10D5A220
// FUNCTION: ENGINE 0x10D5A250
// FUNCTION: ENGINE 0x10D5A280
// FUNCTION: ENGINE 0x10D5A2B0
// FUNCTION: ENGINE 0x10D5A2E0
// FUNCTION: ENGINE 0x10D5A310
// FUNCTION: ENGINE 0x10D5A340
// FUNCTION: ENGINE 0x10D5A370
// FUNCTION: ENGINE 0x10D5A3A0
// FUNCTION: ENGINE 0x10D5A3D0
// FUNCTION: ENGINE 0x10D5A400
// FUNCTION: ENGINE 0x10D5A430
// FUNCTION: ENGINE 0x10D5A460
// FUNCTION: ENGINE 0x10D5A490
// FUNCTION: ENGINE 0x10D5A4C0
// FUNCTION: ENGINE 0x10D5A4F0
// FUNCTION: ENGINE 0x10D5A520
// FUNCTION: ENGINE 0x10D5A550
// FUNCTION: ENGINE 0x10D5A580
// FUNCTION: ENGINE 0x10D5A5B0
// FUNCTION: ENGINE 0x10D5A5E0
// FUNCTION: ENGINE 0x10D5A610
// FUNCTION: ENGINE 0x10D5A640
// FUNCTION: ENGINE 0x10D5A670
// FUNCTION: ENGINE 0x10D5A6A0
// FUNCTION: ENGINE 0x10D5A6D0
// FUNCTION: ENGINE 0x10D5A700
// FUNCTION: ENGINE 0x10D5A730
// FUNCTION: ENGINE 0x10D5A760
// FUNCTION: ENGINE 0x10D5A790
// FUNCTION: ENGINE 0x10D5A7E0
// FUNCTION: ENGINE 0x10D5A840
// FUNCTION: ENGINE 0x10D5A8A0
// FUNCTION: ENGINE 0x10D5A8D0
// FUNCTION: ENGINE 0x10D5A900
// FUNCTION: ENGINE 0x10D5A930
// FUNCTION: ENGINE 0x10D5A980
// FUNCTION: ENGINE 0x10D5A9E0
// FUNCTION: ENGINE 0x10D5AA40
// FUNCTION: ENGINE 0x10D5AA70
// FUNCTION: ENGINE 0x10D5AAA0
// FUNCTION: ENGINE 0x10D5AAD0
// FUNCTION: ENGINE 0x10D5AB00
// FUNCTION: ENGINE 0x10D5AB30
// FUNCTION: ENGINE 0x10D5AB60
// FUNCTION: ENGINE 0x10D5AC20
// FUNCTION: ENGINE 0x10D5AC50
// FUNCTION: ENGINE 0x10D5AC80
// FUNCTION: ENGINE 0x10D5ACB0
// FUNCTION: ENGINE 0x10D5ACE0
// FUNCTION: ENGINE 0x10D5AD10
// FUNCTION: ENGINE 0x10D5AD40
// FUNCTION: ENGINE 0x10D5AD70
// FUNCTION: ENGINE 0x10D5ADA0
// FUNCTION: ENGINE 0x10D5ADD0
// FUNCTION: ENGINE 0x10D5AE00
// FUNCTION: ENGINE 0x10D5AE30
// FUNCTION: ENGINE 0x10D5AE60
// FUNCTION: ENGINE 0x10D5AEB0
// FUNCTION: ENGINE 0x10D5AF10
// FUNCTION: ENGINE 0x10D5AF70
// FUNCTION: ENGINE 0x10D5AFA0
// FUNCTION: ENGINE 0x10D5AFD0
// FUNCTION: ENGINE 0x10D5B000
// FUNCTION: ENGINE 0x10D5B030
// FUNCTION: ENGINE 0x10D5B060
// FUNCTION: ENGINE 0x10D5B090
// FUNCTION: ENGINE 0x10D5B0C0
// FUNCTION: ENGINE 0x10D5B0F0
// FUNCTION: ENGINE 0x10D5B120
// FUNCTION: ENGINE 0x10D5B150
// FUNCTION: ENGINE 0x10D5B180
// FUNCTION: ENGINE 0x10D5B1B0
// FUNCTION: ENGINE 0x10D5B200
// FUNCTION: ENGINE 0x10D5B260
// FUNCTION: ENGINE 0x10D5B2C0
// FUNCTION: ENGINE 0x10D5B2F0
// FUNCTION: ENGINE 0x10D83EA0
// FUNCTION: ENGINE 0x10D83EB0
// FUNCTION: ENGINE 0x10D83EC0
// FUNCTION: ENGINE 0x10D83ED0
// FUNCTION: ENGINE 0x10D83EE0
// FUNCTION: ENGINE 0x10D83EF0
// FUNCTION: ENGINE 0x10D83F00
// FUNCTION: ENGINE 0x10D83F10
// FUNCTION: ENGINE 0x10D83F20
// FUNCTION: ENGINE 0x10D83F30
// FUNCTION: ENGINE 0x10D83F40
// FUNCTION: ENGINE 0x10D83F50
// FUNCTION: ENGINE 0x10D83F60
// FUNCTION: ENGINE 0x10D83F70
// FUNCTION: ENGINE 0x10D83F80
// FUNCTION: ENGINE 0x10D83F90
// FUNCTION: ENGINE 0x10D83FA0
// FUNCTION: ENGINE 0x10D83FB0
// FUNCTION: ENGINE 0x10D83FC0
// FUNCTION: ENGINE 0x10D83FD0
// FUNCTION: ENGINE 0x10D83FE0
// FUNCTION: ENGINE 0x10D83FF0
// FUNCTION: ENGINE 0x10D84000
// FUNCTION: ENGINE 0x10D84010
// FUNCTION: ENGINE 0x10D84020
// FUNCTION: ENGINE 0x10D84030
// FUNCTION: ENGINE 0x10D84040
// FUNCTION: ENGINE 0x10D84050
// FUNCTION: ENGINE 0x10D84060
// FUNCTION: ENGINE 0x10D84070
// FUNCTION: ENGINE 0x10D84080
// FUNCTION: ENGINE 0x10D84090
// FUNCTION: ENGINE 0x10D840A0
// FUNCTION: ENGINE 0x10D840B0
// FUNCTION: ENGINE 0x10D840C0
// FUNCTION: ENGINE 0x10D840D0
// FUNCTION: ENGINE 0x10D840E0
// FUNCTION: ENGINE 0x10D840F0
// FUNCTION: ENGINE 0x10D84100
// FUNCTION: ENGINE 0x10D84110
// FUNCTION: ENGINE 0x10D84120
// FUNCTION: ENGINE 0x10D84130
// FUNCTION: ENGINE 0x10D84150
// FUNCTION: ENGINE 0x10D84160
// FUNCTION: ENGINE 0x10D84170
// FUNCTION: ENGINE 0x10D84180
// FUNCTION: ENGINE 0x10D84190
// FUNCTION: ENGINE 0x10D841A0
// FUNCTION: ENGINE 0x10D841B0
// FUNCTION: ENGINE 0x10D841C0
// FUNCTION: ENGINE 0x10D841D0
// FUNCTION: ENGINE 0x10D841E0
// FUNCTION: ENGINE 0x10D841F0
// FUNCTION: ENGINE 0x10D84200
// FUNCTION: ENGINE 0x10D84210
// FUNCTION: ENGINE 0x10D84220
// FUNCTION: ENGINE 0x10D84230
// FUNCTION: ENGINE 0x10D84240
// FUNCTION: ENGINE 0x10D84250
// FUNCTION: ENGINE 0x10D84260
// FUNCTION: ENGINE 0x10D84270
// FUNCTION: ENGINE 0x10D84300
// FUNCTION: ENGINE 0x10D84310
// FUNCTION: ENGINE 0x10D84320
// FUNCTION: ENGINE 0x10D84330
// FUNCTION: ENGINE 0x10D84340
// FUNCTION: ENGINE 0x10D84350
// FUNCTION: ENGINE 0x10D84360
// FUNCTION: ENGINE 0x10D84370
// FUNCTION: ENGINE 0x10D84380
// FUNCTION: ENGINE 0x10D84390
// FUNCTION: ENGINE 0x10D843A0
// FUNCTION: ENGINE 0x10D843B0
// FUNCTION: ENGINE 0x10D843C0
// FUNCTION: ENGINE 0x10D843D0
// FUNCTION: ENGINE 0x10D843E0
// FUNCTION: ENGINE 0x10D843F0
// FUNCTION: ENGINE 0x10D84400
// FUNCTION: ENGINE 0x10D84410
// FUNCTION: ENGINE 0x10D84480
// FUNCTION: ENGINE 0x10D84490
// FUNCTION: ENGINE 0x10D844A0
// FUNCTION: ENGINE 0x10D844B0
// FUNCTION: ENGINE 0x10D844F0
// FUNCTION: ENGINE 0x10D84500
// FUNCTION: ENGINE 0x10D84510
// FUNCTION: ENGINE 0x10D84520
// FUNCTION: ENGINE 0x10D84530
// FUNCTION: ENGINE 0x10D84540
// FUNCTION: ENGINE 0x10D84550
// FUNCTION: ENGINE 0x10D84560
// FUNCTION: ENGINE 0x10D84570
// FUNCTION: ENGINE 0x10D84580
// FUNCTION: ENGINE 0x10D84590
// FUNCTION: ENGINE 0x10D845A0
// FUNCTION: ENGINE 0x10D845B0
// FUNCTION: ENGINE 0x10D845C0
// FUNCTION: ENGINE 0x10D845D0
// FUNCTION: ENGINE 0x10D845E0
// FUNCTION: ENGINE 0x10D84600
// FUNCTION: ENGINE 0x10D84610
// FUNCTION: ENGINE 0x10D84620
// FUNCTION: ENGINE 0x10D84630
// FUNCTION: ENGINE 0x10D84640
// FUNCTION: ENGINE 0x10D84650
// FUNCTION: ENGINE 0x10D84660
// FUNCTION: ENGINE 0x10D84670
// FUNCTION: ENGINE 0x10D84680
// FUNCTION: ENGINE 0x10D84690
// FUNCTION: ENGINE 0x10D846A0
// FUNCTION: ENGINE 0x10D846B0
// FUNCTION: ENGINE 0x10D846C0
// FUNCTION: ENGINE 0x10D846D0
// FUNCTION: ENGINE 0x10D846E0
// FUNCTION: ENGINE 0x10D846F0
// FUNCTION: ENGINE 0x10D84700
// FUNCTION: ENGINE 0x10D84710
// FUNCTION: ENGINE 0x10D84720
// FUNCTION: ENGINE 0x10D84730
// FUNCTION: ENGINE 0x10D84740
// FUNCTION: ENGINE 0x10D84750
// FUNCTION: ENGINE 0x10D84760
// FUNCTION: ENGINE 0x10D84770
// FUNCTION: ENGINE 0x10D84780
// FUNCTION: ENGINE 0x10D84790
// FUNCTION: ENGINE 0x10D847A0
// FUNCTION: ENGINE 0x10D847B0
// FUNCTION: ENGINE 0x10D847C0
// FUNCTION: ENGINE 0x10D847D0
// FUNCTION: ENGINE 0x10D847E0
// FUNCTION: ENGINE 0x10D847F0
// FUNCTION: ENGINE 0x10D84800
// FUNCTION: ENGINE 0x10D84810
// FUNCTION: ENGINE 0x10D84820
// FUNCTION: ENGINE 0x10D84830
// FUNCTION: ENGINE 0x10D84840
// FUNCTION: ENGINE 0x10D84850
// FUNCTION: ENGINE 0x10D84860
// FUNCTION: ENGINE 0x10D84870
// FUNCTION: ENGINE 0x10D84880
// FUNCTION: ENGINE 0x10D84890
// FUNCTION: ENGINE 0x10D848A0
// FUNCTION: ENGINE 0x10D848B0
// FUNCTION: ENGINE 0x10D848C0
// FUNCTION: ENGINE 0x10D848D0
// FUNCTION: ENGINE 0x10D848E0
// FUNCTION: ENGINE 0x10D848F0
// FUNCTION: ENGINE 0x10D84900
// FUNCTION: ENGINE 0x10D84910
// FUNCTION: ENGINE 0x10D84920
// FUNCTION: ENGINE 0x10D84930
// FUNCTION: ENGINE 0x10D84940
// FUNCTION: ENGINE 0x10D84960
// FUNCTION: ENGINE 0x10D84970
// FUNCTION: ENGINE 0x10D849B0
// FUNCTION: ENGINE 0x10D849C0
// FUNCTION: ENGINE 0x10D849D0
// FUNCTION: ENGINE 0x10D849E0
// FUNCTION: ENGINE 0x10D849F0
// FUNCTION: ENGINE 0x10D84A00
// FUNCTION: ENGINE 0x10D84A10
// FUNCTION: ENGINE 0x10D84A20
// FUNCTION: ENGINE 0x10D84A30
// FUNCTION: ENGINE 0x10D84A40
// FUNCTION: ENGINE 0x10D84A50
// FUNCTION: ENGINE 0x10D84A60
// FUNCTION: ENGINE 0x10D84A70
// FUNCTION: ENGINE 0x10D84A80
// FUNCTION: ENGINE 0x10D84A90
// FUNCTION: ENGINE 0x10D84AA0
// FUNCTION: ENGINE 0x10D84AB0
// FUNCTION: ENGINE 0x10D84AC0
// FUNCTION: ENGINE 0x10D84AD0
// FUNCTION: ENGINE 0x10D84AE0
// FUNCTION: ENGINE 0x10D84AF0
// FUNCTION: ENGINE 0x10D84B00
// FUNCTION: ENGINE 0x10D84B10
// FUNCTION: ENGINE 0x10D84B20
// FUNCTION: ENGINE 0x10D84B40
// FUNCTION: ENGINE 0x10D84B50
// FUNCTION: ENGINE 0x10D84B60
// FUNCTION: ENGINE 0x10D84B70
// FUNCTION: ENGINE 0x10D84B80
// FUNCTION: ENGINE 0x10D84B90
// FUNCTION: ENGINE 0x10D84BA0
// FUNCTION: ENGINE 0x10D84BB0
// FUNCTION: ENGINE 0x10D84BC0
// FUNCTION: ENGINE 0x10D84BD0
// FUNCTION: ENGINE 0x10D84BE0
// FUNCTION: ENGINE 0x10D84BF0
// FUNCTION: ENGINE 0x10D84C00
// FUNCTION: ENGINE 0x10D84C10
// FUNCTION: ENGINE 0x10D84C20
// FUNCTION: ENGINE 0x10D84C30
// FUNCTION: ENGINE 0x10D84C40
// FUNCTION: ENGINE 0x10D84C50
// FUNCTION: ENGINE 0x10D84C60
// FUNCTION: ENGINE 0x10D84C70
// FUNCTION: ENGINE 0x10D84C80
// FUNCTION: ENGINE 0x10D84C90
// FUNCTION: ENGINE 0x10D84CA0
// FUNCTION: ENGINE 0x10D84CB0
// FUNCTION: ENGINE 0x10D84CC0
// FUNCTION: ENGINE 0x10D84CD0
// FUNCTION: ENGINE 0x10D84CE0
// FUNCTION: ENGINE 0x10D84CF0
// FUNCTION: ENGINE 0x10D84D00
// FUNCTION: ENGINE 0x10D84D10
// FUNCTION: ENGINE 0x10D84D20
// FUNCTION: ENGINE 0x10D84D30
// FUNCTION: ENGINE 0x10D84D40
// FUNCTION: ENGINE 0x10D84D60
// FUNCTION: ENGINE 0x10D84D70
// FUNCTION: ENGINE 0x10D84D80
// FUNCTION: ENGINE 0x10D84D90
