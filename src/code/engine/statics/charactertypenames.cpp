// Globals that the engine's static initialisers 0x10D54090 - 0x10D57FD0 construct in translation units whose code is not
// reconstructed: the character, vehicle and ai system names of the scenario and fight item units, and the names and strings every such unit repeats through its headers (the
// slot group names, the audio file and listener names). Unit name guess; one file holds the runs of several units.
#include "code/core/name.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/om/staticinit.h"

namespace engine
{
	MessageListeners gScenario50("scenario", 0);
	MessageListeners gScenario51("scenario", 0);
	MessageListeners gScenario52("scenario", 0);
	MessageListeners gScenario53("scenario", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour24("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gPrototype("prototype", 0);
	MessageListeners gScenario54("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup152("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty161("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup153("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty162("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup154("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty163("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup155("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty164("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup156("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty165("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup157("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty166("", 0);
	core::Name<core::CaseSensitiveKey> gLightDecalDrawable("light_decal_drawable", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup158("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty167("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup159("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty168("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup160("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty169("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup161("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty170("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup162("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty171("", 0);
	core::Name<core::CaseSensitiveKey> gRpm("rpm", 0);
	core::Name<core::CaseSensitiveKey> gStartup("startup", 0);
	core::Name<core::CaseSensitiveKey> gWinddown("winddown", 0);
	core::Name<core::CaseSensitiveKey> gTurnValue("turn_value", 0);
	core::Name<core::CaseSensitiveKey> gHighLod("high_lod", 0);
	fight::EnumEntry gBusShelterOS001Table[12] =
		{
			{ fight::Name("busShelterOS001", 0) },
			{ fight::Name("parkingElevator001", 0) },
			{ fight::Name("planter004", 0) },
			{ fight::Name("planter005", 0) },
			{ fight::Name("streetlight001", 0) },
			{ fight::Name("streetlight006", 0) },
			{ fight::Name("streetlightOS003", 0) },
			{ fight::Name("trafficSignal001", 0) },
			{ fight::Name("trafficSignal005", 0) },
			{ fight::Name("tree003", 0) },
			{ fight::Name("tree004", 0) },
			{ fight::Name("vendorOS004", 0) }
		};
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup163("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty172("", 0);
	MessageListeners gScenario55("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup164("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty173("", 0);
	core::Name<core::CaseSensitiveKey> gProtoProfileMouseWheelInvHeli("Proto_Profile_MouseWheelInv_Heli", 0);
	MessageListeners gScenario56("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup165("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty174("", 0);
	MessageListeners gScenario57("scenario", 0);
	core::Name<core::CaseInsensitiveKey32> gCaseInsensitiveKey32Object11;
	core::Name<core::CaseInsensitiveKey32> gCaseInsensitiveKey32Object12;
	core::Name<core::CaseSensitiveKey> gCameraFadeWhenHeld("cameraFadeWhenHeld", 0);
	core::Name<core::CaseSensitiveKey> gHunterCameraFade("hunterCameraFade", 0);
	core::Name<core::CaseSensitiveKey> gHolding2("Holding", 0);
	core::Name<core::CaseSensitiveKey> g2hnd("2hnd", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup166("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty175("", 0);
	MessageListeners gScenario58("scenario", 0);
	fight::EnumEntry gCharacterChaseTable[5] =
		{
			{ fight::Name("Character_chase", 0) },
			{ fight::Name("Ground_vehicle", 0) },
			{ fight::Name("Ground_vehicle_gunner", 0) },
			{ fight::Name("Air_vehicle", 0) },
			{ fight::Name("Air_vehicle_gunner", 0) }
		};
	fight::EnumEntry gSlideTable[17] =
		{
			{ fight::Name("Slide", 0) },
			{ fight::Name("Falling", 0) },
			{ fight::Name("Running", 0) },
			{ fight::Name("Jumping", 0) },
			{ fight::Name("Climbing", 0) },
			{ fight::Name("WallRun", 0) },
			{ fight::Name("Float", 0) },
			{ fight::Name("QuickTurn", 0) },
			{ fight::Name("HopJump", 0) },
			{ fight::Name("Parkour", 0) },
			{ fight::Name("Grapple", 0) },
			{ fight::Name("RollLeft", 0) },
			{ fight::Name("RollRight", 0) },
			{ fight::Name("AutoTarget", 0) },
			{ fight::Name("Glide", 0) },
			{ fight::Name("AirDash", 0) },
			{ fight::Name("LockControls", 0) }
		};
	fight::EnumEntry gSmallTable[3] =
		{
			{ fight::Name("small", 0) },
			{ fight::Name("medium", 0) },
			{ fight::Name("large", 0) }
		};
	fight::EnumEntry gFromAnimationTable[3] =
		{
			{ fight::Name("From Animation", 0) },
			{ fight::Name("Not Cyclic", 0) },
			{ fight::Name("Cyclic", 0) }
		};
	core::Name<core::CaseSensitiveKey> gSteering("steering", 0);
	core::Name<core::CaseSensitiveKey> gEngage("engage", 0);
	core::Name<core::CaseSensitiveKey> gThreatBall("threatBall", 0);
	core::Name<core::CaseSensitiveKey> gCharBudgetMgr("charBudgetMgr", 0);
	core::Name<core::CaseSensitiveKey> gMovement("movement", 0);
	core::Name<core::CaseSensitiveKey> gFlying("flying", 0);
	core::Name<core::CaseSensitiveKey> gPerception("perception", 0);
	core::Name<core::CaseSensitiveKey> gSquads("squads", 0);
	core::Name<core::CaseSensitiveKey> gCharInfo("charInfo", 0);
	core::Name<core::CaseSensitiveKey> gTaskGoalInfo("taskGoalInfo", 0);
	core::Name<core::CaseSensitiveKey> gTaskGoalHistory("taskGoalHistory", 0);
	core::Name<core::CaseSensitiveKey> gPosition("position", 0);
	core::Name<core::CaseSensitiveKey> gTooltip("tooltip", 0);
	core::Name<core::CaseSensitiveKey> gHunterMovement("hunterMovement", 0);
	core::Name<core::CaseSensitiveKey> gLODAI("LODAI", 0);
	core::Name<core::CaseSensitiveKey> gTargetSelection("targetSelection", 0);
	core::Name<core::CaseSensitiveKey> gIntention("intention", 0);
	core::Name<core::CaseSensitiveKey> gRoadMesh("roadMesh", 0);
	core::Name<core::CaseSensitiveKey> gMagneticBoots("magneticBoots", 0);
	core::Name<core::CaseSensitiveKey> gDisguise2("disguise", 0);
	core::Name<core::CaseSensitiveKey> gAiming("aiming", 0);
	core::Name<core::CaseSensitiveKey> gMinPerception("minPerception", 0);
	core::Name<core::CaseSensitiveKey> gDefendArea("defendArea", 0);
	core::Name<core::CaseSensitiveKey> gSymbolic("symbolic", 0);
	core::Name<core::CaseSensitiveKey> gMarkerInSoldiers("markerInSoldiers", 0);
	core::Name<core::CaseSensitiveKey> gMarkerInPlayer("markerInPlayer", 0);
	core::Name<core::CaseSensitiveKey> gHeightmap("heightmap", 0);
	core::Name<core::CaseSensitiveKey> gDisguiseState("disguiseState", 0);
	core::Name<core::CaseSensitiveKey> gHealth("health", 0);
	core::Name<core::CaseSensitiveKey> gBullets("bullets", 0);
	core::Name<core::CaseSensitiveKey> gFiring("firing", 0);
	core::Name<core::CaseSensitiveKey> gTankMovement("tankMovement", 0);
	core::Name<core::CaseSensitiveKey> gGrabSelection("grabSelection", 0);
	core::Name<core::CaseSensitiveKey> gAlert("alert", 0);
	core::Name<core::CaseSensitiveKey> gSpatialQuery("spatialQuery", 0);
	core::Name<core::CaseSensitiveKey> gFormations("formations", 0);
	core::Name<core::CaseSensitiveKey> gPatrols("patrols", 0);
	core::Name<core::CaseSensitiveKey> gDetailedTargeting("detailedTargeting", 0);
	core::Name<core::CaseSensitiveKey> gDiversions("diversions", 0);
	core::Name<core::CaseSensitiveKey> gEvents("events", 0);
	core::Name<core::CaseSensitiveKey> gCrosshair("crosshair", 0);
	core::Name<core::CaseSensitiveKey> gDisguiseIntention("disguise_intention", 0);
	core::Name<core::CaseSensitiveKey> gHelicopterMovement("helicopter_movement", 0);
	core::Name<core::CaseSensitiveKey> gCombatBudget("combat_budget", 0);
	core::Name<core::CaseSensitiveKey> gFlyingPathfinder("flyingPathfinder", 0);
	core::Name<core::CaseSensitiveKey> gToken("token", 0);
	core::Name<core::CaseSensitiveKey> gCurrentTest("currentTest", 0);
	core::Name<core::CaseSensitiveKey> gBloodtox("bloodtox", 0);
	core::Name<core::CaseSensitiveKey> gLof("lof", 0);
	core::Name<core::CaseSensitiveKey> gDisguiseDebug("disguise_debug", 0);
	core::Name<core::CaseSensitiveKey> gBaseVolumes("base_volumes", 0);
	core::Name<core::CaseSensitiveKey> gIntersectionProperties("intersection_properties", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup167("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty176("", 0);
	core::Name<core::CaseSensitiveKey> gAgent("agent__", 0);
	core::Name<core::CaseSensitiveKey> gSquad("squad__", 0);
	core::Name<core::CaseInsensitiveKey32> gCaseInsensitiveKey32Object13;
	core::Name<core::CaseSensitiveKey> gAlex2("alex", 0);
	core::Name<core::CaseSensitiveKey> gUav("uav", 0);
	core::Name<core::CaseSensitiveKey> gSupersoldier("supersoldier", 0);
	core::Name<core::CaseSensitiveKey> gHeliGunshipMarineCore("heli_gunship_marine_core", 0);
	core::Name<core::CaseSensitiveKey> gHeliBhMarine("heli_bh_marine", 0);
	core::Name<core::CaseSensitiveKey> gTankRamMarine("tank_ram_marine", 0);
	core::Name<core::CaseSensitiveKey> gTankRamThermobaric("tank_ram_thermobaric", 0);
	core::Name<core::CaseSensitiveKey> gApcM2Marine("apc_m2_marine", 0);
	core::Name<core::CaseSensitiveKey> gBrawler("brawler", 0);
	core::Name<core::CaseSensitiveKey> gLeaderHunter("leader_hunter", 0);
	core::Name<core::CaseSensitiveKey> gHydra("hydra", 0);
	core::Name<core::CaseSensitiveKey> gInfected1("infected1", 0);
	core::Name<core::CaseSensitiveKey> gInfected22("infected2", 0);
	core::Name<core::CaseSensitiveKey> gSoldier("soldier", 0);
	core::Name<core::CaseSensitiveKey> gCommander("commander", 0);
	core::Name<core::CaseSensitiveKey> gPedestrian("pedestrian", 0);
	core::Name<core::CaseSensitiveKey> gBlackwatch("blackwatch", 0);
	core::Name<core::CaseSensitiveKey> gCop("cop", 0);
	core::Name<core::CaseSensitiveKey> gTankGunner("TankGunner", 0);
	core::Name<core::CaseSensitiveKey> gBwplainclothes("bwplainclothes", 0);
	core::Name<core::CaseSensitiveKey> gSpecialist("specialist", 0);
	core::Name<core::CaseSensitiveKey> gDummy("Dummy", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup168("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty177("", 0);
	core::Name<core::CaseSensitiveKey> gDriverAI("Driver_AI", 0);
	core::Name<core::CaseSensitiveKey> gGunnerAI("Gunner_AI", 0);
	MessageListeners gScenario59("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup169("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty178("", 0);
	core::Name<core::CaseSensitiveKey> gEncounterObject10("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter10("encounter", 0);
	core::Name<core::CaseSensitiveKey> gStatAlertsCaused("Stat: Alerts Caused", 0);
	core::Name<core::CaseSensitiveKey> gStatAlertsAvoided("Stat: Alerts Avoided", 0);
	core::Name<core::CaseSensitiveKey> gStatStrikeTeamsAvoided("Stat: Strike Teams Avoided", 0);
	core::Name<core::CaseSensitiveKey> gStatStrikeTeamsKilled("Stat: Strike Teams Killed", 0);
	core::Name<core::CaseSensitiveKey> gSoldierSquad("SoldierSquad", 0);
	core::Name<core::CaseSensitiveKey> gStrikeTeamHeliHighPriority("StrikeTeamHeli_HighPriority", 0);
	core::Name<core::CaseSensitiveKey> gInfected12("infected1", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup170("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty179("", 0);
	core::Name<core::CaseSensitiveKey> gSoldier2("soldier", 0);
	core::Name<core::CaseSensitiveKey> gCommander2("commander", 0);
	core::Name<core::CaseSensitiveKey> gSupersoldier2("supersoldier", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup171("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty180("", 0);
	core::Name<core::CaseSensitiveKey> gEncounterObject11("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter11("encounter", 0);
	core::Name<core::CaseSensitiveKey> gSoldier3("soldier", 0);
	core::Name<core::CaseSensitiveKey> gBlackwatch2("blackwatch", 0);
	core::Name<core::CaseSensitiveKey> gCommander3("commander", 0);
	core::Name<core::CaseSensitiveKey> gPedMPilotCau("ped_m_pilot_cau", 0);
	core::Name<core::CaseSensitiveKey> gTankGunner2("TankGunner", 0);
	core::Name<core::CaseSensitiveKey> gCop2("Cop", 0);
	core::Name<core::CaseSensitiveKey> gTankRamMarine2("tank_ram_marine", 0);
	core::Name<core::CaseSensitiveKey> gApcM2Marine2("apc_m2_marine", 0);
	core::Name<core::CaseSensitiveKey> gBloodtoxDriller001("bloodtoxDriller001", 0);
	core::Name<core::CaseSensitiveKey> gTankRamThermobaric2("tank_ram_thermobaric", 0);
	core::Name<core::CaseSensitiveKey> gHeliGunshipMarineCore2("heli_gunship_marine_core", 0);
	core::Name<core::CaseSensitiveKey> gHeliBhMarine2("heli_bh_marine", 0);
	core::Name<core::CaseSensitiveKey> gF45Thunder001("f45Thunder001", 0);
	core::Name<core::CaseSensitiveKey> gUav2("uav", 0);
	core::Name<core::CaseSensitiveKey> gSupersoldier3("supersoldier", 0);
	core::Name<core::CaseSensitiveKey> gInfected13("infected1", 0);
	core::Name<core::CaseSensitiveKey> gInfected23("infected2", 0);
	core::Name<core::CaseSensitiveKey> gBrawler2("brawler", 0);
	core::Name<core::CaseSensitiveKey> gStealth("stealth", 0);
	core::Name<core::CaseSensitiveKey> gHydra2("hydra", 0);
	core::Name<core::CaseSensitiveKey> gLeaderHunter2("leader_hunter", 0);
	core::Name<core::CaseSensitiveKey> gGunTurret("gun_turret", 0);
	core::Name<core::CaseSensitiveKey> gSniffer("sniffer", 0);
	core::Name<core::CaseSensitiveKey> gKarenparker("karenparker", 0);
	core::Name<core::CaseSensitiveKey> gBwplainclothes2("bwplainclothes", 0);
	core::Name<core::CaseSensitiveKey> gMissionPed("MissionPed", 0);
	core::Name<core::CaseSensitiveKey> gBwscientist("bwscientist", 0);
	core::Name<core::CaseSensitiveKey> gDanaMercer("dana_mercer", 0);
	core::Name<core::CaseSensitiveKey> gFemale2("female", 0);
	core::Name<core::CaseSensitiveKey> gRagland("ragland", 0);
	core::Name<core::CaseSensitiveKey> gCombatPriority("combatPriority", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup172("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty181("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup173("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty182("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup174("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty183("", 0);
	MessageListeners gScenario60("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup175("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty184("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup176("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty185("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup177("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty186("", 0);
	MessageListeners gScenario61("scenario", 0);
	core::Name<core::CaseSensitiveKey> gWorldTriggerManager("world_trigger_manager", 0);
	core::Name<core::CaseSensitiveKey> gWaterImpact("water_impact", 0);
	core::Name<core::CaseSensitiveKey> gCanGoUnderground("canGoUnderground", 0);
	core::Name<core::CaseSensitiveKey> gWater("Water", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup178("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty187("", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour25("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gHolding3("Holding", 0);
	core::Name<core::CaseSensitiveKey> gFirearm2("firearm", 0);
	core::Name<core::CaseSensitiveKey> gDrawable("drawable", 0);
	core::Name<core::CaseSensitiveKey> gDriver("Driver", 0);
	core::Name<core::CaseSensitiveKey> gGunner("Gunner", 0);
	core::Name<core::CaseSensitiveKey> gDriverAI2("Driver_AI", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup179("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty188("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup180("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty189("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup181("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty190("", 0);
	MessageListeners gScenario62("scenario", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour26("AlexArmour", 0);
	MessageListeners gScenario63("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup182("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty191("", 0);
	om::String gAudioGlobalP3d36 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener37 = om::NameOfText("Listener");
	om::ClassName gMaster37 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gStatSoldiersPatsied("Stat: Soldiers Patsied", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup183("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty192("", 0);
	MessageListeners gScenario64("scenario", 0);
	core::Name<core::CaseSensitiveKey> gEncounterObject12("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter12("encounter", 0);
	core::Name<core::CaseSensitiveKey> gDriverPlayer("DriverPlayer", 0);
	core::Name<core::CaseSensitiveKey> gDriverAI3("DriverAI", 0);
	core::Name<core::CaseSensitiveKey> gNoDriver("NoDriver", 0);
	core::Name<core::CaseSensitiveKey> gDriverAILanded("DriverAILanded", 0);
	core::Name<core::CaseSensitiveKey> gDriverAILandedEngineOn("DriverAILandedEngineOn", 0);
	core::Name<core::CaseSensitiveKey> gDriverAITakingOff("DriverAITakingOff", 0);
	core::Name<core::CaseSensitiveKey> gDriverAIPlayerGunner("DriverAIPlayerGunner", 0);
	core::Name<core::CaseSensitiveKey> gIdle("Idle", 0);
	core::Name<core::CaseSensitiveKey> gCombat("Combat", 0);
	core::Name<core::CaseSensitiveKey> gApologizing("Apologizing", 0);
	core::Name<core::CaseSensitiveKey> gAdmiring("Admiring", 0);
	core::Name<core::CaseSensitiveKey> gCurious("Curious", 0);
	core::Name<core::CaseSensitiveKey> gDropit("Dropit", 0);
	core::Name<core::CaseSensitiveKey> gSaluting("Saluting", 0);
	core::Name<core::CaseSensitiveKey> gSaluteOpposite("SaluteOpposite", 0);
	core::Name<core::CaseSensitiveKey> gStartled("Startled", 0);
	core::Name<core::CaseSensitiveKey> gStartled2("Startled2", 0);
	core::Name<core::CaseSensitiveKey> gStartled2Combat("Startled2Combat", 0);
	core::Name<core::CaseSensitiveKey> gNotMe("NotMe", 0);
	core::Name<core::CaseSensitiveKey> gNotMeCombat("NotMeCombat", 0);
	core::Name<core::CaseSensitiveKey> gReactToPatsy("ReactToPatsy", 0);
	core::Name<core::CaseSensitiveKey> gGetHim("GetHim", 0);
	core::Name<core::CaseSensitiveKey> gConfused("Confused", 0);
	core::Name<core::CaseSensitiveKey> gAngry("Angry", 0);
	core::Name<core::CaseSensitiveKey> gRecognition("Recognition", 0);
	core::Name<core::CaseSensitiveKey> gStopThat("StopThat", 0);
	core::Name<core::CaseSensitiveKey> gStopThat2("StopThat2", 0);
	core::Name<core::CaseSensitiveKey> gSearch("Search", 0);
	core::Name<core::CaseSensitiveKey> gSuspicious("Suspicious", 0);
	core::Name<core::CaseSensitiveKey> gAnnoyed("Annoyed", 0);
	core::Name<core::CaseSensitiveKey> gLetsGoBack("LetsGoBack", 0);
	core::Name<core::CaseSensitiveKey> gLetsGoBackSupport("LetsGoBackSupport", 0);
	core::Name<core::CaseSensitiveKey> gCheckBody("CheckBody", 0);
	core::Name<core::CaseSensitiveKey> gCheckBodyPed("CheckBodyPed", 0);
	core::Name<core::CaseSensitiveKey> gDisoriented("Disoriented", 0);
	core::Name<core::CaseSensitiveKey> gVictorious("Victorious", 0);
	core::Name<core::CaseSensitiveKey> gReportToHQ("ReportToHQ", 0);
	core::Name<core::CaseSensitiveKey> gRadioHQ("RadioHQ", 0);
	core::Name<core::CaseSensitiveKey> gCallStrikeTeam("CallStrikeTeam", 0);
	core::Name<core::CaseSensitiveKey> gPursuit("Pursuit", 0);
	core::Name<core::CaseSensitiveKey> gSearchFast("SearchFast", 0);
	core::Name<core::CaseSensitiveKey> gSearchScan("SearchScan", 0);
	core::Name<core::CaseSensitiveKey> gStopPursuit("StopPursuit", 0);
	core::Name<core::CaseSensitiveKey> gAlerting("Alerting", 0);
	core::Name<core::CaseSensitiveKey> gPanicked("Panicked", 0);
	core::Name<core::CaseSensitiveKey> gFleeing("Fleeing", 0);
	core::Name<core::CaseSensitiveKey> gDodging("Dodging", 0);
	core::Name<core::CaseSensitiveKey> gPointing("Pointing", 0);
	core::Name<core::CaseSensitiveKey> gMissionAccomplished("MissionAccomplished", 0);
	core::Name<core::CaseSensitiveKey> gDenyPatsy("DenyPatsy", 0);
	core::Name<core::CaseSensitiveKey> gSupportDenyPatsy("SupportDenyPatsy", 0);
	core::Name<core::CaseSensitiveKey> gInvestigatePlayerDiversion("InvestigatePlayerDiversion", 0);
	core::Name<core::CaseSensitiveKey> gDenyPlayerDiversion("DenyPlayerDiversion", 0);
	core::Name<core::CaseSensitiveKey> gInvestigatePlayerDiversionSupport("InvestigatePlayerDiversionSupport", 0);
	core::Name<core::CaseSensitiveKey> gDetecting("Detecting", 0);
	core::Name<core::CaseSensitiveKey> gSupportCheckBody("SupportCheckBody", 0);
	core::Name<core::CaseSensitiveKey> gGettingPushed("GettingPushed", 0);
	core::Name<core::CaseSensitiveKey> gFriendlyFire("FriendlyFire", 0);
	core::Name<core::CaseSensitiveKey> gCivilianFire("CivilianFire", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup184("Undefined_SlotGroup", 0);
}

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::EnumEntry gPedestrianAlertStateConditionStateTable[24] =
				{
					{ fight::Name("None", 0) },
					{ fight::Name("Explosion", 0) },
					{ fight::Name("Throw", 0) },
					{ fight::Name("Shapeshift", 0) },
					{ fight::Name("Gunfire", 0) },
					{ fight::Name("Grab", 0) },
					{ fight::Name("Hit", 0) },
					{ fight::Name("Shove", 0) },
					{ fight::Name("ExtremeLocomotion", 0) },
					{ fight::Name("Landing", 0) },
					{ fight::Name("Consume", 0) },
					{ fight::Name("Death", 0) },
					{ fight::Name("BulletHit", 0) },
					{ fight::Name("ScatterPeds", 0) },
					{ fight::Name("MissileFire", 0) },
					{ fight::Name("PanicingPedestrian", 0) },
					{ fight::Name("DeadBody", 0) },
					{ fight::Name("GrabScream", 0) },
					{ fight::Name("FlyingObject", 0) },
					{ fight::Name("ThrowLand", 0) },
					{ fight::Name("EnterVehicle", 0) },
					{ fight::Name("GenerateDiversion", 0) },
					{ fight::Name("BurningVehicle", 0) },
					{ fight::Name("CarAccident", 0) }
				};
		}
	}
}

// The dynamic initialisers and atexit stubs of the unit's globals:
// FUNCTION: ENGINE 0x10D54090
// FUNCTION: ENGINE 0x10D540C0
// FUNCTION: ENGINE 0x10D540F0
// FUNCTION: ENGINE 0x10D54120
// FUNCTION: ENGINE 0x10D54150
// FUNCTION: ENGINE 0x10D54180
// FUNCTION: ENGINE 0x10D541B0
// FUNCTION: ENGINE 0x10D541E0
// FUNCTION: ENGINE 0x10D54210
// FUNCTION: ENGINE 0x10D54240
// FUNCTION: ENGINE 0x10D54270
// FUNCTION: ENGINE 0x10D542A0
// FUNCTION: ENGINE 0x10D542D0
// FUNCTION: ENGINE 0x10D54300
// FUNCTION: ENGINE 0x10D54330
// FUNCTION: ENGINE 0x10D54360
// FUNCTION: ENGINE 0x10D54390
// FUNCTION: ENGINE 0x10D543C0
// FUNCTION: ENGINE 0x10D543F0
// FUNCTION: ENGINE 0x10D54420
// FUNCTION: ENGINE 0x10D54450
// FUNCTION: ENGINE 0x10D54480
// FUNCTION: ENGINE 0x10D544B0
// FUNCTION: ENGINE 0x10D544E0
// FUNCTION: ENGINE 0x10D54510
// FUNCTION: ENGINE 0x10D54540
// FUNCTION: ENGINE 0x10D54570
// FUNCTION: ENGINE 0x10D545A0
// FUNCTION: ENGINE 0x10D545D0
// FUNCTION: ENGINE 0x10D54600
// FUNCTION: ENGINE 0x10D54630
// FUNCTION: ENGINE 0x10D54660
// FUNCTION: ENGINE 0x10D54690
// FUNCTION: ENGINE 0x10D546C0
// FUNCTION: ENGINE 0x10D546F0
// FUNCTION: ENGINE 0x10D54720
// FUNCTION: ENGINE 0x10D54830
// FUNCTION: ENGINE 0x10D54860
// FUNCTION: ENGINE 0x10D54890
// FUNCTION: ENGINE 0x10D548C0
// FUNCTION: ENGINE 0x10D548F0
// FUNCTION: ENGINE 0x10D54920
// FUNCTION: ENGINE 0x10D549A0
// FUNCTION: ENGINE 0x10D549D0
// FUNCTION: ENGINE 0x10D54A00
// FUNCTION: ENGINE 0x10D54A80
// FUNCTION: ENGINE 0x10D54AB0
// FUNCTION: ENGINE 0x10D54AD0
// FUNCTION: ENGINE 0x10D54AF0
// FUNCTION: ENGINE 0x10D54B20
// FUNCTION: ENGINE 0x10D54B70
// FUNCTION: ENGINE 0x10D54BA0
// FUNCTION: ENGINE 0x10D54BD0
// FUNCTION: ENGINE 0x10D54C00
// FUNCTION: ENGINE 0x10D54C30
// FUNCTION: ENGINE 0x10D54C60
// FUNCTION: ENGINE 0x10D54CE0
// FUNCTION: ENGINE 0x10D54E60
// FUNCTION: ENGINE 0x10D54EB0
// FUNCTION: ENGINE 0x10D54F10
// FUNCTION: ENGINE 0x10D54F40
// FUNCTION: ENGINE 0x10D54F70
// FUNCTION: ENGINE 0x10D54FA0
// FUNCTION: ENGINE 0x10D54FD0
// FUNCTION: ENGINE 0x10D55000
// FUNCTION: ENGINE 0x10D55030
// FUNCTION: ENGINE 0x10D55060
// FUNCTION: ENGINE 0x10D55090
// FUNCTION: ENGINE 0x10D550C0
// FUNCTION: ENGINE 0x10D550F0
// FUNCTION: ENGINE 0x10D55120
// FUNCTION: ENGINE 0x10D55150
// FUNCTION: ENGINE 0x10D55180
// FUNCTION: ENGINE 0x10D551B0
// FUNCTION: ENGINE 0x10D551E0
// FUNCTION: ENGINE 0x10D55210
// FUNCTION: ENGINE 0x10D55240
// FUNCTION: ENGINE 0x10D55270
// FUNCTION: ENGINE 0x10D552A0
// FUNCTION: ENGINE 0x10D552D0
// FUNCTION: ENGINE 0x10D55300
// FUNCTION: ENGINE 0x10D55330
// FUNCTION: ENGINE 0x10D55360
// FUNCTION: ENGINE 0x10D55390
// FUNCTION: ENGINE 0x10D553C0
// FUNCTION: ENGINE 0x10D553F0
// FUNCTION: ENGINE 0x10D55420
// FUNCTION: ENGINE 0x10D55450
// FUNCTION: ENGINE 0x10D55480
// FUNCTION: ENGINE 0x10D554B0
// FUNCTION: ENGINE 0x10D554E0
// FUNCTION: ENGINE 0x10D55510
// FUNCTION: ENGINE 0x10D55540
// FUNCTION: ENGINE 0x10D55570
// FUNCTION: ENGINE 0x10D555A0
// FUNCTION: ENGINE 0x10D555D0
// FUNCTION: ENGINE 0x10D55600
// FUNCTION: ENGINE 0x10D55630
// FUNCTION: ENGINE 0x10D55660
// FUNCTION: ENGINE 0x10D55690
// FUNCTION: ENGINE 0x10D556C0
// FUNCTION: ENGINE 0x10D556F0
// FUNCTION: ENGINE 0x10D55720
// FUNCTION: ENGINE 0x10D55750
// FUNCTION: ENGINE 0x10D55780
// FUNCTION: ENGINE 0x10D557B0
// FUNCTION: ENGINE 0x10D557E0
// FUNCTION: ENGINE 0x10D55810
// FUNCTION: ENGINE 0x10D55840
// FUNCTION: ENGINE 0x10D55870
// FUNCTION: ENGINE 0x10D558A0
// FUNCTION: ENGINE 0x10D558D0
// FUNCTION: ENGINE 0x10D55900
// FUNCTION: ENGINE 0x10D55930
// FUNCTION: ENGINE 0x10D55960
// FUNCTION: ENGINE 0x10D55990
// FUNCTION: ENGINE 0x10D559B0
// FUNCTION: ENGINE 0x10D55CD0
// FUNCTION: ENGINE 0x10D55D00
// FUNCTION: ENGINE 0x10D55D30
// FUNCTION: ENGINE 0x10D55D60
// FUNCTION: ENGINE 0x10D55D90
// FUNCTION: ENGINE 0x10D55DC0
// FUNCTION: ENGINE 0x10D55DF0
// FUNCTION: ENGINE 0x10D55E20
// FUNCTION: ENGINE 0x10D55E50
// FUNCTION: ENGINE 0x10D55E80
// FUNCTION: ENGINE 0x10D55EB0
// FUNCTION: ENGINE 0x10D55EE0
// FUNCTION: ENGINE 0x10D55F10
// FUNCTION: ENGINE 0x10D55F40
// FUNCTION: ENGINE 0x10D55F70
// FUNCTION: ENGINE 0x10D55FA0
// FUNCTION: ENGINE 0x10D55FD0
// FUNCTION: ENGINE 0x10D56000
// FUNCTION: ENGINE 0x10D56030
// FUNCTION: ENGINE 0x10D56060
// FUNCTION: ENGINE 0x10D56090
// FUNCTION: ENGINE 0x10D560C0
// FUNCTION: ENGINE 0x10D560F0
// FUNCTION: ENGINE 0x10D56120
// FUNCTION: ENGINE 0x10D56150
// FUNCTION: ENGINE 0x10D56180
// FUNCTION: ENGINE 0x10D561B0
// FUNCTION: ENGINE 0x10D561E0
// FUNCTION: ENGINE 0x10D56210
// FUNCTION: ENGINE 0x10D56240
// FUNCTION: ENGINE 0x10D56270
// FUNCTION: ENGINE 0x10D562A0
// FUNCTION: ENGINE 0x10D562D0
// FUNCTION: ENGINE 0x10D56300
// FUNCTION: ENGINE 0x10D56330
// FUNCTION: ENGINE 0x10D56360
// FUNCTION: ENGINE 0x10D56390
// FUNCTION: ENGINE 0x10D563C0
// FUNCTION: ENGINE 0x10D563F0
// FUNCTION: ENGINE 0x10D56420
// FUNCTION: ENGINE 0x10D56450
// FUNCTION: ENGINE 0x10D56480
// FUNCTION: ENGINE 0x10D564B0
// FUNCTION: ENGINE 0x10D564E0
// FUNCTION: ENGINE 0x10D56510
// FUNCTION: ENGINE 0x10D56540
// FUNCTION: ENGINE 0x10D56570
// FUNCTION: ENGINE 0x10D565A0
// FUNCTION: ENGINE 0x10D565D0
// FUNCTION: ENGINE 0x10D56600
// FUNCTION: ENGINE 0x10D56630
// FUNCTION: ENGINE 0x10D56660
// FUNCTION: ENGINE 0x10D56690
// FUNCTION: ENGINE 0x10D566C0
// FUNCTION: ENGINE 0x10D566F0
// FUNCTION: ENGINE 0x10D56720
// FUNCTION: ENGINE 0x10D56750
// FUNCTION: ENGINE 0x10D56780
// FUNCTION: ENGINE 0x10D567B0
// FUNCTION: ENGINE 0x10D567E0
// FUNCTION: ENGINE 0x10D56810
// FUNCTION: ENGINE 0x10D56840
// FUNCTION: ENGINE 0x10D56870
// FUNCTION: ENGINE 0x10D568A0
// FUNCTION: ENGINE 0x10D568D0
// FUNCTION: ENGINE 0x10D56900
// FUNCTION: ENGINE 0x10D56930
// FUNCTION: ENGINE 0x10D56960
// FUNCTION: ENGINE 0x10D56990
// FUNCTION: ENGINE 0x10D569C0
// FUNCTION: ENGINE 0x10D569F0
// FUNCTION: ENGINE 0x10D56A20
// FUNCTION: ENGINE 0x10D56A50
// FUNCTION: ENGINE 0x10D56A80
// FUNCTION: ENGINE 0x10D56AB0
// FUNCTION: ENGINE 0x10D56AE0
// FUNCTION: ENGINE 0x10D56B10
// FUNCTION: ENGINE 0x10D56B40
// FUNCTION: ENGINE 0x10D56B70
// FUNCTION: ENGINE 0x10D56BA0
// FUNCTION: ENGINE 0x10D56BD0
// FUNCTION: ENGINE 0x10D56C00
// FUNCTION: ENGINE 0x10D56C30
// FUNCTION: ENGINE 0x10D56C60
// FUNCTION: ENGINE 0x10D56C90
// FUNCTION: ENGINE 0x10D56CC0
// FUNCTION: ENGINE 0x10D56CF0
// FUNCTION: ENGINE 0x10D56D20
// FUNCTION: ENGINE 0x10D56D50
// FUNCTION: ENGINE 0x10D56D80
// FUNCTION: ENGINE 0x10D56DB0
// FUNCTION: ENGINE 0x10D56DE0
// FUNCTION: ENGINE 0x10D56E10
// FUNCTION: ENGINE 0x10D56E40
// FUNCTION: ENGINE 0x10D56E70
// FUNCTION: ENGINE 0x10D56EA0
// FUNCTION: ENGINE 0x10D56ED0
// FUNCTION: ENGINE 0x10D56F00
// FUNCTION: ENGINE 0x10D56F30
// FUNCTION: ENGINE 0x10D56F60
// FUNCTION: ENGINE 0x10D56F90
// FUNCTION: ENGINE 0x10D56FC0
// FUNCTION: ENGINE 0x10D56FF0
// FUNCTION: ENGINE 0x10D57020
// FUNCTION: ENGINE 0x10D57050
// FUNCTION: ENGINE 0x10D57080
// FUNCTION: ENGINE 0x10D570B0
// FUNCTION: ENGINE 0x10D570E0
// FUNCTION: ENGINE 0x10D57110
// FUNCTION: ENGINE 0x10D57140
// FUNCTION: ENGINE 0x10D57170
// FUNCTION: ENGINE 0x10D571A0
// FUNCTION: ENGINE 0x10D571D0
// FUNCTION: ENGINE 0x10D57200
// FUNCTION: ENGINE 0x10D57230
// FUNCTION: ENGINE 0x10D57260
// FUNCTION: ENGINE 0x10D57290
// FUNCTION: ENGINE 0x10D572E0
// FUNCTION: ENGINE 0x10D57340
// FUNCTION: ENGINE 0x10D573A0
// FUNCTION: ENGINE 0x10D573D0
// FUNCTION: ENGINE 0x10D57400
// FUNCTION: ENGINE 0x10D57430
// FUNCTION: ENGINE 0x10D57460
// FUNCTION: ENGINE 0x10D57490
// FUNCTION: ENGINE 0x10D574C0
// FUNCTION: ENGINE 0x10D574F0
// FUNCTION: ENGINE 0x10D57520
// FUNCTION: ENGINE 0x10D57550
// FUNCTION: ENGINE 0x10D57580
// FUNCTION: ENGINE 0x10D575B0
// FUNCTION: ENGINE 0x10D575E0
// FUNCTION: ENGINE 0x10D57610
// FUNCTION: ENGINE 0x10D57640
// FUNCTION: ENGINE 0x10D57670
// FUNCTION: ENGINE 0x10D576A0
// FUNCTION: ENGINE 0x10D576D0
// FUNCTION: ENGINE 0x10D57700
// FUNCTION: ENGINE 0x10D57730
// FUNCTION: ENGINE 0x10D57760
// FUNCTION: ENGINE 0x10D57790
// FUNCTION: ENGINE 0x10D577C0
// FUNCTION: ENGINE 0x10D577F0
// FUNCTION: ENGINE 0x10D57820
// FUNCTION: ENGINE 0x10D57850
// FUNCTION: ENGINE 0x10D57880
// FUNCTION: ENGINE 0x10D578B0
// FUNCTION: ENGINE 0x10D578E0
// FUNCTION: ENGINE 0x10D57910
// FUNCTION: ENGINE 0x10D57940
// FUNCTION: ENGINE 0x10D57970
// FUNCTION: ENGINE 0x10D579A0
// FUNCTION: ENGINE 0x10D579D0
// FUNCTION: ENGINE 0x10D57A00
// FUNCTION: ENGINE 0x10D57A30
// FUNCTION: ENGINE 0x10D57A60
// FUNCTION: ENGINE 0x10D57A90
// FUNCTION: ENGINE 0x10D57AC0
// FUNCTION: ENGINE 0x10D57AF0
// FUNCTION: ENGINE 0x10D57B20
// FUNCTION: ENGINE 0x10D57B50
// FUNCTION: ENGINE 0x10D57B80
// FUNCTION: ENGINE 0x10D57BB0
// FUNCTION: ENGINE 0x10D57BE0
// FUNCTION: ENGINE 0x10D57C10
// FUNCTION: ENGINE 0x10D57C40
// FUNCTION: ENGINE 0x10D57C70
// FUNCTION: ENGINE 0x10D57CA0
// FUNCTION: ENGINE 0x10D57CD0
// FUNCTION: ENGINE 0x10D57D00
// FUNCTION: ENGINE 0x10D57D30
// FUNCTION: ENGINE 0x10D57D60
// FUNCTION: ENGINE 0x10D57D90
// FUNCTION: ENGINE 0x10D57DC0
// FUNCTION: ENGINE 0x10D57DF0
// FUNCTION: ENGINE 0x10D57E20
// FUNCTION: ENGINE 0x10D57E50
// FUNCTION: ENGINE 0x10D57E80
// FUNCTION: ENGINE 0x10D57EB0
// FUNCTION: ENGINE 0x10D57EE0
// FUNCTION: ENGINE 0x10D57F10
// FUNCTION: ENGINE 0x10D57F40
// FUNCTION: ENGINE 0x10D57F70
// FUNCTION: ENGINE 0x10D57FA0
// FUNCTION: ENGINE 0x10D57FD0
// FUNCTION: ENGINE 0x10D828A0
// FUNCTION: ENGINE 0x10D828E0
// FUNCTION: ENGINE 0x10D828F0
// FUNCTION: ENGINE 0x10D82910
// FUNCTION: ENGINE 0x10D82920
// FUNCTION: ENGINE 0x10D82930
// FUNCTION: ENGINE 0x10D82940
// FUNCTION: ENGINE 0x10D82970
// FUNCTION: ENGINE 0x10D82980
// FUNCTION: ENGINE 0x10D82990
// FUNCTION: ENGINE 0x10D829A0
// FUNCTION: ENGINE 0x10D82A00
// FUNCTION: ENGINE 0x10D82A10
// FUNCTION: ENGINE 0x10D82A30
// FUNCTION: ENGINE 0x10D82A40
// FUNCTION: ENGINE 0x10D82A50
// FUNCTION: ENGINE 0x10D82A60
// FUNCTION: ENGINE 0x10D82A70
// FUNCTION: ENGINE 0x10D82A80
// FUNCTION: ENGINE 0x10D82A90
// FUNCTION: ENGINE 0x10D82AA0
// FUNCTION: ENGINE 0x10D82AB0
// FUNCTION: ENGINE 0x10D82AE0
// FUNCTION: ENGINE 0x10D82AF0
// FUNCTION: ENGINE 0x10D82BC0
// FUNCTION: ENGINE 0x10D82BD0
// FUNCTION: ENGINE 0x10D82BF0
// FUNCTION: ENGINE 0x10D82C00
// FUNCTION: ENGINE 0x10D82C40
// FUNCTION: ENGINE 0x10D82C50
// FUNCTION: ENGINE 0x10D82C60
// FUNCTION: ENGINE 0x10D82C70
// FUNCTION: ENGINE 0x10D82C80
// FUNCTION: ENGINE 0x10D82C90
// FUNCTION: ENGINE 0x10D82CA0
// FUNCTION: ENGINE 0x10D82CB0
// FUNCTION: ENGINE 0x10D82D10
// FUNCTION: ENGINE 0x10D82D20
// FUNCTION: ENGINE 0x10D82D70
// FUNCTION: ENGINE 0x10D82D80
// FUNCTION: ENGINE 0x10D82D90
// FUNCTION: ENGINE 0x10D82DA0
// FUNCTION: ENGINE 0x10D82DD0
// FUNCTION: ENGINE 0x10D82DE0
// FUNCTION: ENGINE 0x10D82DF0
// FUNCTION: ENGINE 0x10D82E20
// FUNCTION: ENGINE 0x10D82E30
// FUNCTION: ENGINE 0x10D82E40
// FUNCTION: ENGINE 0x10D82E50
// FUNCTION: ENGINE 0x10D82E60
// FUNCTION: ENGINE 0x10D82E70
// FUNCTION: ENGINE 0x10D82E80
// FUNCTION: ENGINE 0x10D82E90
// FUNCTION: ENGINE 0x10D82EA0
// FUNCTION: ENGINE 0x10D82EB0
// FUNCTION: ENGINE 0x10D82EC0
// FUNCTION: ENGINE 0x10D82ED0
// FUNCTION: ENGINE 0x10D82EE0
// FUNCTION: ENGINE 0x10D82EF0
// FUNCTION: ENGINE 0x10D82F00
// FUNCTION: ENGINE 0x10D82F10
// FUNCTION: ENGINE 0x10D82F20
// FUNCTION: ENGINE 0x10D82F30
// FUNCTION: ENGINE 0x10D82F40
// FUNCTION: ENGINE 0x10D82F50
// FUNCTION: ENGINE 0x10D82F60
// FUNCTION: ENGINE 0x10D82F70
// FUNCTION: ENGINE 0x10D82F80
// FUNCTION: ENGINE 0x10D82F90
// FUNCTION: ENGINE 0x10D82FA0
// FUNCTION: ENGINE 0x10D82FB0
// FUNCTION: ENGINE 0x10D82FC0
// FUNCTION: ENGINE 0x10D82FD0
// FUNCTION: ENGINE 0x10D82FE0
// FUNCTION: ENGINE 0x10D82FF0
// FUNCTION: ENGINE 0x10D83000
// FUNCTION: ENGINE 0x10D83010
// FUNCTION: ENGINE 0x10D83020
// FUNCTION: ENGINE 0x10D83030
// FUNCTION: ENGINE 0x10D83040
// FUNCTION: ENGINE 0x10D83050
// FUNCTION: ENGINE 0x10D83060
// FUNCTION: ENGINE 0x10D83070
// FUNCTION: ENGINE 0x10D83080
// FUNCTION: ENGINE 0x10D83090
// FUNCTION: ENGINE 0x10D830A0
// FUNCTION: ENGINE 0x10D830B0
// FUNCTION: ENGINE 0x10D830C0
// FUNCTION: ENGINE 0x10D830D0
// FUNCTION: ENGINE 0x10D830E0
// FUNCTION: ENGINE 0x10D830F0
// FUNCTION: ENGINE 0x10D83100
// FUNCTION: ENGINE 0x10D83110
// FUNCTION: ENGINE 0x10D83120
// FUNCTION: ENGINE 0x10D83130
// FUNCTION: ENGINE 0x10D83140
// FUNCTION: ENGINE 0x10D83150
// FUNCTION: ENGINE 0x10D83160
// FUNCTION: ENGINE 0x10D83170
// FUNCTION: ENGINE 0x10D83180
// FUNCTION: ENGINE 0x10D83190
// FUNCTION: ENGINE 0x10D831A0
// FUNCTION: ENGINE 0x10D831B0
// FUNCTION: ENGINE 0x10D831C0
// FUNCTION: ENGINE 0x10D831D0
// FUNCTION: ENGINE 0x10D831E0
// FUNCTION: ENGINE 0x10D831F0
// FUNCTION: ENGINE 0x10D83200
// FUNCTION: ENGINE 0x10D83210
// FUNCTION: ENGINE 0x10D83220
// FUNCTION: ENGINE 0x10D83230
// FUNCTION: ENGINE 0x10D83250
// FUNCTION: ENGINE 0x10D83260
// FUNCTION: ENGINE 0x10D83270
// FUNCTION: ENGINE 0x10D83280
// FUNCTION: ENGINE 0x10D83290
// FUNCTION: ENGINE 0x10D832B0
// FUNCTION: ENGINE 0x10D832C0
// FUNCTION: ENGINE 0x10D832D0
// FUNCTION: ENGINE 0x10D832E0
// FUNCTION: ENGINE 0x10D832F0
// FUNCTION: ENGINE 0x10D83300
// FUNCTION: ENGINE 0x10D83310
// FUNCTION: ENGINE 0x10D83320
// FUNCTION: ENGINE 0x10D83330
// FUNCTION: ENGINE 0x10D83340
// FUNCTION: ENGINE 0x10D83350
// FUNCTION: ENGINE 0x10D83360
// FUNCTION: ENGINE 0x10D83370
// FUNCTION: ENGINE 0x10D83380
// FUNCTION: ENGINE 0x10D83390
// FUNCTION: ENGINE 0x10D833A0
// FUNCTION: ENGINE 0x10D833B0
// FUNCTION: ENGINE 0x10D833C0
// FUNCTION: ENGINE 0x10D833D0
// FUNCTION: ENGINE 0x10D833E0
// FUNCTION: ENGINE 0x10D833F0
// FUNCTION: ENGINE 0x10D83400
// FUNCTION: ENGINE 0x10D83410
// FUNCTION: ENGINE 0x10D83420
// FUNCTION: ENGINE 0x10D83430
// FUNCTION: ENGINE 0x10D83440
// FUNCTION: ENGINE 0x10D83450
// FUNCTION: ENGINE 0x10D83460
// FUNCTION: ENGINE 0x10D83470
// FUNCTION: ENGINE 0x10D83480
// FUNCTION: ENGINE 0x10D83490
// FUNCTION: ENGINE 0x10D834A0
// FUNCTION: ENGINE 0x10D834B0
// FUNCTION: ENGINE 0x10D834C0
// FUNCTION: ENGINE 0x10D834D0
// FUNCTION: ENGINE 0x10D834E0
// FUNCTION: ENGINE 0x10D834F0
// FUNCTION: ENGINE 0x10D83500
// FUNCTION: ENGINE 0x10D83510
// FUNCTION: ENGINE 0x10D83520
// FUNCTION: ENGINE 0x10D83530
// FUNCTION: ENGINE 0x10D83540
// FUNCTION: ENGINE 0x10D83550
// FUNCTION: ENGINE 0x10D83560
// FUNCTION: ENGINE 0x10D83570
// FUNCTION: ENGINE 0x10D83580
// FUNCTION: ENGINE 0x10D83590
// FUNCTION: ENGINE 0x10D835A0
// FUNCTION: ENGINE 0x10D835B0
// FUNCTION: ENGINE 0x10D835C0
// FUNCTION: ENGINE 0x10D835D0
// FUNCTION: ENGINE 0x10D835E0
// FUNCTION: ENGINE 0x10D835F0
// FUNCTION: ENGINE 0x10D83600
// FUNCTION: ENGINE 0x10D83610
// FUNCTION: ENGINE 0x10D83620
// FUNCTION: ENGINE 0x10D83630
// FUNCTION: ENGINE 0x10D83640
// FUNCTION: ENGINE 0x10D83650
// FUNCTION: ENGINE 0x10D83660
// FUNCTION: ENGINE 0x10D83670
// FUNCTION: ENGINE 0x10D83680
// FUNCTION: ENGINE 0x10D83690
// FUNCTION: ENGINE 0x10D836A0
// FUNCTION: ENGINE 0x10D836B0
// FUNCTION: ENGINE 0x10D836C0
// FUNCTION: ENGINE 0x10D836D0
// FUNCTION: ENGINE 0x10D836E0
// FUNCTION: ENGINE 0x10D836F0
// FUNCTION: ENGINE 0x10D83700
// FUNCTION: ENGINE 0x10D83710
// FUNCTION: ENGINE 0x10D83720
// FUNCTION: ENGINE 0x10D83730
// FUNCTION: ENGINE 0x10D83740
// FUNCTION: ENGINE 0x10D83750
// FUNCTION: ENGINE 0x10D83760
// FUNCTION: ENGINE 0x10D83770
// FUNCTION: ENGINE 0x10D83780
// FUNCTION: ENGINE 0x10D837A0
// FUNCTION: ENGINE 0x10D837B0
// FUNCTION: ENGINE 0x10D837C0
// FUNCTION: ENGINE 0x10D837D0
// FUNCTION: ENGINE 0x10D837E0
// FUNCTION: ENGINE 0x10D837F0
// FUNCTION: ENGINE 0x10D83800
// FUNCTION: ENGINE 0x10D83810
// FUNCTION: ENGINE 0x10D83820
// FUNCTION: ENGINE 0x10D83830
// FUNCTION: ENGINE 0x10D83840
// FUNCTION: ENGINE 0x10D83850
// FUNCTION: ENGINE 0x10D83860
// FUNCTION: ENGINE 0x10D83870
// FUNCTION: ENGINE 0x10D83880
// FUNCTION: ENGINE 0x10D83890
// FUNCTION: ENGINE 0x10D838A0
// FUNCTION: ENGINE 0x10D838B0
// FUNCTION: ENGINE 0x10D838C0
// FUNCTION: ENGINE 0x10D838D0
// FUNCTION: ENGINE 0x10D838E0
// FUNCTION: ENGINE 0x10D838F0
// FUNCTION: ENGINE 0x10D83900
// FUNCTION: ENGINE 0x10D83910
// FUNCTION: ENGINE 0x10D83920
// FUNCTION: ENGINE 0x10D83930
// FUNCTION: ENGINE 0x10D83940
// FUNCTION: ENGINE 0x10D83950
// FUNCTION: ENGINE 0x10D83960
// FUNCTION: ENGINE 0x10D83970
// FUNCTION: ENGINE 0x10D83980
// FUNCTION: ENGINE 0x10D83990
// FUNCTION: ENGINE 0x10D839A0
// FUNCTION: ENGINE 0x10D839B0
// FUNCTION: ENGINE 0x10D839C0
// FUNCTION: ENGINE 0x10D839D0
// FUNCTION: ENGINE 0x10D839E0
// FUNCTION: ENGINE 0x10D839F0
// FUNCTION: ENGINE 0x10D83A00
// FUNCTION: ENGINE 0x10D83A10
// FUNCTION: ENGINE 0x10D83A20
// FUNCTION: ENGINE 0x10D83A90
// FUNCTION: ENGINE 0x10D83AA0
// FUNCTION: ENGINE 0x10D83AB0
// FUNCTION: ENGINE 0x10D83AC0
// FUNCTION: ENGINE 0x10D83AD0
// FUNCTION: ENGINE 0x10D83AE0
// FUNCTION: ENGINE 0x10D83AF0
// FUNCTION: ENGINE 0x10D83B00
// FUNCTION: ENGINE 0x10D83B10
// FUNCTION: ENGINE 0x10D83B20
// FUNCTION: ENGINE 0x10D83B30
// FUNCTION: ENGINE 0x10D83B40
// FUNCTION: ENGINE 0x10D83B50
// FUNCTION: ENGINE 0x10D83B60
// FUNCTION: ENGINE 0x10D83B70
// FUNCTION: ENGINE 0x10D83B80
// FUNCTION: ENGINE 0x10D83B90
// FUNCTION: ENGINE 0x10D83BA0
// FUNCTION: ENGINE 0x10D83BB0
// FUNCTION: ENGINE 0x10D83BC0
// FUNCTION: ENGINE 0x10D83BD0
// FUNCTION: ENGINE 0x10D83BE0
// FUNCTION: ENGINE 0x10D83BF0
// FUNCTION: ENGINE 0x10D83C00
// FUNCTION: ENGINE 0x10D83C10
// FUNCTION: ENGINE 0x10D83C20
// FUNCTION: ENGINE 0x10D83C30
// FUNCTION: ENGINE 0x10D83C40
// FUNCTION: ENGINE 0x10D83C50
// FUNCTION: ENGINE 0x10D83C60
// FUNCTION: ENGINE 0x10D83C70
// FUNCTION: ENGINE 0x10D83C80
// FUNCTION: ENGINE 0x10D83C90
// FUNCTION: ENGINE 0x10D83CA0
// FUNCTION: ENGINE 0x10D83CB0
// FUNCTION: ENGINE 0x10D83CC0
// FUNCTION: ENGINE 0x10D83CD0
// FUNCTION: ENGINE 0x10D83CE0
// FUNCTION: ENGINE 0x10D83CF0
// FUNCTION: ENGINE 0x10D83D00
// FUNCTION: ENGINE 0x10D83D10
// FUNCTION: ENGINE 0x10D83D20
// FUNCTION: ENGINE 0x10D83D30
// FUNCTION: ENGINE 0x10D83D40
// FUNCTION: ENGINE 0x10D83D50
// FUNCTION: ENGINE 0x10D83D60
// FUNCTION: ENGINE 0x10D83D70
// FUNCTION: ENGINE 0x10D83D80
// FUNCTION: ENGINE 0x10D83D90
// FUNCTION: ENGINE 0x10D83DA0
// FUNCTION: ENGINE 0x10D83DB0
// FUNCTION: ENGINE 0x10D83DC0
// FUNCTION: ENGINE 0x10D83DD0
// FUNCTION: ENGINE 0x10D83DE0
// FUNCTION: ENGINE 0x10D83DF0
// FUNCTION: ENGINE 0x10D83E00
// FUNCTION: ENGINE 0x10D83E10
// FUNCTION: ENGINE 0x10D83E20
// FUNCTION: ENGINE 0x10D83E30
// FUNCTION: ENGINE 0x10D83E40
// FUNCTION: ENGINE 0x10D83E50
// FUNCTION: ENGINE 0x10D83E60
// FUNCTION: ENGINE 0x10D83E70
// FUNCTION: ENGINE 0x10D83E80
// FUNCTION: ENGINE 0x10D83E90
