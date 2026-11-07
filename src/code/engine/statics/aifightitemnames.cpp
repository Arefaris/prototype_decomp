// Globals that the engine's static initialisers 0x10D50010 - 0x10D53D60 construct in translation units whose code is not
// reconstructed: the track, condition and enumeration names of the fight item units (ai, motion, hud) and the spawner property names, and the names and strings every such unit repeats through its headers (the
// slot group names, the audio file and listener names). Unit name guess; one file holds the runs of several units.
#include "code/core/name.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/om/staticinit.h"

namespace engine
{
	MessageListeners gScenario36("scenario", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour22("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup117("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty126("", 0);
	MessageListeners gScenario37("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup118("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty127("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup119("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty128("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup120("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty129("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup121("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty130("", 0);
	core::Name<core::CaseSensitiveKey> gKnockback("knockback", 0);
	core::Name<core::CaseSensitiveKey> gFloat("float", 0);
	fight::EnumEntry gOrderAttackTable[9] =
		{
			{ fight::Name("Order Attack", 0) },
			{ fight::Name("Suspicion", 0) },
			{ fight::Name("Lost Him", 0) },
			{ fight::Name("Check Body", 0) },
			{ fight::Name("Radio HQ", 0) },
			{ fight::Name("Call Strike Team", 0) },
			{ fight::Name("Stop Pursuit", 0) },
			{ fight::Name("Recognize Patsy", 0) },
			{ fight::Name("Deny Patsy", 0) }
		};
	core::Name<core::CaseSensitiveKey> gAlex("alex", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup122("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty131("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup123("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty132("", 0);
	MessageListeners gScenario38("scenario", 0);
	fight::EnumEntry gGotoTable[8] =
		{
			{ fight::Name("goto", 0) },
			{ fight::Name("goto_strafe", 0) },
			{ fight::Name("patrolTraffic", 0) },
			{ fight::Name("gotoCombat", 0) },
			{ fight::Name("gotoNoFreeArea", 0) },
			{ fight::Name("gotoLand", 0) },
			{ fight::Name("traffic", 0) },
			{ fight::Name("jumpto", 0) }
		};
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup124("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty133("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup125("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty134("", 0);
	MessageListeners gScenario39("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup126("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty135("", 0);
	MessageListeners gScenario40("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup127("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty136("", 0);
	MessageListeners gScenario41("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup128("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty137("", 0);
	MessageListeners gScenario42("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup129("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty138("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup130("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty139("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup131("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty140("", 0);
	MessageListeners gScenario43("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup132("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty141("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup133("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty142("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup134("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty143("", 0);
	core::Name<core::CaseSensitiveKey> gEncounterObject7("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter7("encounter", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup135("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty144("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup136("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty145("", 0);
	core::Name<core::CaseSensitiveKey> gFinal2("final", 0);
	core::Name<core::CaseSensitiveKey> gEncounterObject8("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter8("encounter", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup137("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty146("", 0);
	MessageListeners gScenario44("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup138("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty147("", 0);
	MessageListeners gScenario45("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup139("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty148("", 0);
	MessageListeners gScenario46("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup140("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty149("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup141("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty150("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup142("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty151("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup143("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty152("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup144("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty153("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup145("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty154("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup146("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty155("", 0);
	MessageListeners gScenario47("scenario", 0);
	core::Name<core::CaseSensitiveKey> gCharge("charge", 0);
	core::Name<core::CaseSensitiveKey> gGender("gender", 0);
	core::Name<core::CaseSensitiveKey> gStoAgentSpawner("sto_agent_spawner", 0);
	core::Name<core::CaseSensitiveKey> gObstacleArray("obstacle array", 0);
	core::Name<core::CaseSensitiveKey> gPedestrianPath("pedestrian path", 0);
	core::Name<core::CaseSensitiveKey> gCharacterBehaviour("characterBehaviour", 0);
	core::Name<core::CaseSensitiveKey> gSoldierBehaviour("soldierBehaviour", 0);
	core::Name<core::CaseSensitiveKey> gInstancePaletteIndex("instancePaletteIndex", 0);
	core::Name<core::CaseSensitiveKey> gReticuleType("reticuleType", 0);
	core::Name<core::CaseSensitiveKey> gSpawner("spawner", 0);
	core::Name<core::CaseSensitiveKey> gLightDecalName("lightDecalName", 0);
	core::Name<core::CaseSensitiveKey> gGroundSpikeCollisionName("groundSpikeCollisionName", 0);
	core::Name<core::CaseSensitiveKey> gHudMarkerOffset("hudMarkerOffset", 0);
	core::Name<core::CaseSensitiveKey> gHudMarkerScale("hudMarkerScale", 0);
	core::Name<core::CaseSensitiveKey> gHudMarkerKillClass("hudMarkerKillClass", 0);
	core::Name<core::CaseSensitiveKey> gCameraScore("cameraScore", 0);
	core::Name<core::CaseSensitiveKey> gCameraMinDist("cameraMinDist", 0);
	core::Name<core::CaseSensitiveKey> gCameraReqOffset("cameraReqOffset", 0);
	core::Name<core::CaseSensitiveKey> gImportantAsset("importantAsset", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup147("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty156("", 0);
	MessageListeners gScenario48("scenario", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour23("AlexArmour", 0);
	om::String gAudioGlobalP3d34 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener35 = om::NameOfText("Listener");
	om::ClassName gMaster35 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gMissionVolume("MissionVolume", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup148("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty157("", 0);
	core::Name<core::CaseSensitiveKey> gEncounterObject9("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter9("encounter", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup149("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty158("", 0);
	core::Name<core::CaseSensitiveKey> gEffectsProp("EffectsProp", 0);
	MessageListeners gScenario49("scenario", 0);
	om::String gAudioGlobalP3d35 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener36 = om::NameOfText("Listener");
	om::ClassName gMaster36 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup150("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty159("", 0);
	core::Name<core::CaseSensitiveKey> gHelicopter("helicopter", 0);
	core::Name<core::CaseSensitiveKey> gTank("tank", 0);
	core::Name<core::CaseSensitiveKey> gFirearm("firearm", 0);
	core::Name<core::CaseSensitiveKey> gHolding("Holding", 0);
	core::Name<core::CaseSensitiveKey> gMotherTargeting("motherTargeting", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup151("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty160("", 0);
}

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::EnumEntry gCombatDestinationFindTrackHeuristicTable[4] =
				{
					{ fight::Name("firstValid", 0) },
					{ fight::Name("lowestValid", 0) },
					{ fight::Name("hydraBest", 0) },
					{ fight::Name("closestToReference", 0) }
				};
			fight::EnumEntry gCombatDestinationFindTrackCameraVisibilityTable[3] =
				{
					{ fight::Name("none", 0) },
					{ fight::Name("outside", 0) },
					{ fight::Name("inside", 0) }
				};
			fight::EnumEntry gCombatDestinationFindTrackReferencePositionTable[3] =
				{
					{ fight::Name("target", 0) },
					{ fight::Name("me", 0) },
					{ fight::Name("fixedArea", 0) }
				};
			fight::EnumEntry gCombatDestinationFindTrackAllowedAreasTable[8] =
				{
					{ fight::Name("unknow", 0) },
					{ fight::Name("intersection", 0) },
					{ fight::Name("road", 0) },
					{ fight::Name("crosswalk", 0) },
					{ fight::Name("sidewalk", 0) },
					{ fight::Name("crosswalkCorner", 0) },
					{ fight::Name("allyway", 0) },
					{ fight::Name("rooftop", 0) }
				};
			fight::EnumEntry gTargetHasLoFConditionCollisionFlagsTable[4] =
				{
					{ fight::Name("collide_none", 0) },
					{ fight::Name("collide_static", 0) },
					{ fight::Name("collide_moving", 0) },
					{ fight::Name("collide_static_and_moving", 0) }
				};
			fight::EnumEntry gCombatDestinationFindTrackHeightDifferenceCheckTable[3] =
				{
					{ fight::Name("Absolute", 0) },
					{ fight::Name("GreaterThan", 0) },
					{ fight::Name("LessThan", 0) }
				};
			fight::EnumEntry gAimTrackWhereTable[10] =
				{
					{ fight::Name("At target", 0) },
					{ fight::Name("Moving direction", 0) },
					{ fight::Name("At grab target", 0) },
					{ fight::Name("Physics Moving direction", 0) },
					{ fight::Name("Restricted direction", 0) },
					{ fight::Name("At target melee", 0) },
					{ fight::Name("At target feet", 0) },
					{ fight::Name("fixed direction", 0) },
					{ fight::Name("fixed destination", 0) },
					{ fight::Name("At last threat", 0) }
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
			fight::EnumEntry gHaveIconTypeConditionTypeTable[39] =
				{
					{ fight::Name("DESTROY", 0) },
					{ fight::Name("PROTECT", 0) },
					{ fight::Name("CONSUME", 0) },
					{ fight::Name("GOTO", 0) },
					{ fight::Name("MISSION", 0) },
					{ fight::Name("WEBNODE", 0) },
					{ fight::Name("PLAYER", 0) },
					{ fight::Name("UAV", 0) },
					{ fight::Name("RECTANGLE_AREA", 0) },
					{ fight::Name("CIRCLE_AREA", 0) },
					{ fight::Name("RING_AREA", 0) },
					{ fight::Name("STRIKETEAM_AREA", 0) },
					{ fight::Name("DOT", 0) },
					{ fight::Name("SMALL_DOT", 0) },
					{ fight::Name("ENEMY_STRIKETEAM", 0) },
					{ fight::Name("ENEMY_HELICOPTER", 0) },
					{ fight::Name("RADIO", 0) },
					{ fight::Name("EVENT_LOCOMOTION", 0) },
					{ fight::Name("EVENT_GLIDING", 0) },
					{ fight::Name("EVENT_THREEWAYWAR", 0) },
					{ fight::Name("EVENT_KILL", 0) },
					{ fight::Name("EVENT_MILITARY_OPPORTUNITY", 0) },
					{ fight::Name("EVENT_INFECTED_OPPORTUNITY", 0) },
					{ fight::Name("EVENT_SCIENTIST", 0) },
					{ fight::Name("EVENT_SELECTED_LOCOMOTION", 0) },
					{ fight::Name("EVENT_SELECTED_GLIDING", 0) },
					{ fight::Name("EVENT_SELECTED_THREEWAYWAR", 0) },
					{ fight::Name("EVENT_SELECTED_KILL", 0) },
					{ fight::Name("EVENT_SELECTED_MILITARY_OPPORTUNITY", 0) },
					{ fight::Name("EVENT_SELECTED_INFECTED_OPPORTUNITY", 0) },
					{ fight::Name("EVENT_SELECTED_SCIENTIST", 0) },
					{ fight::Name("EVENT_GOTO", 0) },
					{ fight::Name("HIVE", 0) },
					{ fight::Name("HIVE_UPGRADES", 0) },
					{ fight::Name("BASE", 0) },
					{ fight::Name("BASE_UPGRADES", 0) },
					{ fight::Name("CONSUME_NOW", 0) },
					{ fight::Name("OBJECTIVE_CONSUME_NOW", 0) },
					{ fight::Name("NONE", 0) }
				};
			fight::EnumEntry gHUDMarkerTrackColorTable[24] =
				{
					{ fight::Name("EVENT", 0) },
					{ fight::Name("OBJECTIVE", 0) },
					{ fight::Name("MISSION", 0) },
					{ fight::Name("OPPORTUNITY", 0) },
					{ fight::Name("SCIENTIST", 0) },
					{ fight::Name("META_GAME", 0) },
					{ fight::Name("ZONE_INFECTED", 0) },
					{ fight::Name("ZONE_MILITARY", 0) },
					{ fight::Name("AWARENESS_PERCEPTION", 0) },
					{ fight::Name("AWARENESS_LOW", 0) },
					{ fight::Name("AWARENESS_MED_SOUND", 0) },
					{ fight::Name("AWARENESS_MED", 0) },
					{ fight::Name("AWARENESS_HIGH", 0) },
					{ fight::Name("AWARENESS_HIGH_OUTOFSIGHT", 0) },
					{ fight::Name("STRIKE_TEAM", 0) },
					{ fight::Name("BASE", 0) },
					{ fight::Name("HIVE", 0) },
					{ fight::Name("MISSION_AREA", 0) },
					{ fight::Name("MEDAL_NONE", 0) },
					{ fight::Name("MEDAL_BRONZE", 0) },
					{ fight::Name("MEDAL_SILVER", 0) },
					{ fight::Name("MEDAL_GOLD", 0) },
					{ fight::Name("MEDAL_PLATINUM", 0) },
					{ fight::Name("DESTROY", 0) }
				};
			fight::EnumEntry gHUDMarkerTrackDisplayTypeTable[4] =
				{
					{ fight::Name("mainmap", 0) },
					{ fight::Name("minimap", 0) },
					{ fight::Name("onscreen", 0) },
					{ fight::Name("offscreen", 0) }
				};
			fight::EnumEntry gHUDMarkerTrackAnimTypeTable[5] =
				{
					{ fight::Name("NONE", 0) },
					{ fight::Name("PULSE_SLOW", 0) },
					{ fight::Name("PULSE_FAST", 0) },
					{ fight::Name("INTRO", 0) },
					{ fight::Name("OUTRO", 0) }
				};
			fight::EnumEntry gShootTrackFixedDirectionSpaceTable[5] =
				{
					{ fight::Name("World Space", 0) },
					{ fight::Name("Game Object Space", 0) },
					{ fight::Name("Joint Space", 0) },
					{ fight::Name("Collision Space", 0) },
					{ fight::Name("AI Destination", 0) }
				};
			fight::EnumEntry gAutoTargetTrackMinPriorityTargetClassTable[54] =
				{
					{ fight::Name("none", 0) },
					{ fight::Name("player", 0) },
					{ fight::Name("dead", 0) },
					{ fight::Name("prop", 0) },
					{ fight::Name("vehicle", 0) },
					{ fight::Name("pedestrian", 0) },
					{ fight::Name("firearm", 0) },
					{ fight::Name("alert", 0) },
					{ fight::Name("unmannedVehicle", 0) },
					{ fight::Name("groundSpike", 0) },
					{ fight::Name("protect", 0) },
					{ fight::Name("civilianWOI", 0) },
					{ fight::Name("thrownObject", 0) },
					{ fight::Name("tank", 0) },
					{ fight::Name("gunship", 0) },
					{ fight::Name("transportHeli", 0) },
					{ fight::Name("cop", 0) },
					{ fight::Name("copCar", 0) },
					{ fight::Name("rifleSoldier", 0) },
					{ fight::Name("missileSoldier", 0) },
					{ fight::Name("commander", 0) },
					{ fight::Name("jet", 0) },
					{ fight::Name("uav", 0) },
					{ fight::Name("sniffer", 0) },
					{ fight::Name("supersoldier", 0) },
					{ fight::Name("gunTurret", 0) },
					{ fight::Name("militaryBase", 0) },
					{ fight::Name("militaryBaseHighPriority", 0) },
					{ fight::Name("militarySpawner", 0) },
					{ fight::Name("bloodtoxBlower", 0) },
					{ fight::Name("infectedWaterTowerDormant", 0) },
					{ fight::Name("infectedWaterTowerActive", 0) },
					{ fight::Name("brawler", 0) },
					{ fight::Name("leader", 0) },
					{ fight::Name("infected1", 0) },
					{ fight::Name("infected2", 0) },
					{ fight::Name("hydra", 0) },
					{ fight::Name("hive", 0) },
					{ fight::Name("hiveHighPriority", 0) },
					{ fight::Name("infectedSpawner", 0) },
					{ fight::Name("boss", 0) },
					{ fight::Name("diversion", 0) },
					{ fight::Name("markerDestroy", 0) },
					{ fight::Name("markerConsume", 0) },
					{ fight::Name("markerWOI", 0) },
					{ fight::Name("markerRadio", 0) },
					{ fight::Name("markerConsumeNow", 0) },
					{ fight::Name("autoMin", 0) },
					{ fight::Name("autoMax", 0) },
					{ fight::Name("autoGrabMin", 0) },
					{ fight::Name("autoGrabMax", 0) },
					{ fight::Name("autoGroundRanged", 0) },
					{ fight::Name("autoAirRanged", 0) },
					{ fight::Name("autoAirRangedMax", 0) }
				};
			fight::EnumEntry gTendrilDevastatorTrackAttackTypeTable[34] =
				{
					{ fight::Name("None", 0) },
					{ fight::Name("Bare", 0) },
					{ fight::Name("Claws", 0) },
					{ fight::Name("Blades", 0) },
					{ fight::Name("Hammerfist", 0) },
					{ fight::Name("Whipfist", 0) },
					{ fight::Name("Weapon", 0) },
					{ fight::Name("Shield", 0) },
					{ fight::Name("Throw", 0) },
					{ fight::Name("Bullet", 0) },
					{ fight::Name("Sniper", 0) },
					{ fight::Name("Missile", 0) },
					{ fight::Name("MissileExplosion", 0) },
					{ fight::Name("PropExplosion", 0) },
					{ fight::Name("DevastatorGroundSpike", 0) },
					{ fight::Name("GroundSpike", 0) },
					{ fight::Name("TankCrush", 0) },
					{ fight::Name("Script", 0) },
					{ fight::Name("Momentum", 0) },
					{ fight::Name("BloodtoxPoison", 0) },
					{ fight::Name("LeaderHunterPoison", 0) },
					{ fight::Name("DevastatorExplosion", 0) },
					{ fight::Name("DevastatorTendril", 0) },
					{ fight::Name("Hunter", 0) },
					{ fight::Name("HelicopterRotor", 0) },
					{ fight::Name("Infected1", 0) },
					{ fight::Name("Infected2", 0) },
					{ fight::Name("Hydra", 0) },
					{ fight::Name("Thermobaric", 0) },
					{ fight::Name("HiveKill", 0) },
					{ fight::Name("SoldierPush", 0) },
					{ fight::Name("AmbientVehicle", 0) },
					{ fight::Name("SupremeHunter", 0) },
					{ fight::Name("ObstacleBash", 0) }
				};
			fight::EnumEntry gDevastatorTargetHitTrackDamageTypeTable[37] =
				{
					{ fight::Name("None", 0) },
					{ fight::Name("Fire", 0) },
					{ fight::Name("Bullet", 0) },
					{ fight::Name("Crush", 0) },
					{ fight::Name("Crack", 0) },
					{ fight::Name("Treadmark", 0) },
					{ fight::Name("Footprint", 0) },
					{ fight::Name("Blood", 0) },
					{ fight::Name("Slash", 0) },
					{ fight::Name("Tear", 0) },
					{ fight::Name("MortarShell", 0) },
					{ fight::Name("Missile", 0) },
					{ fight::Name("Rain", 0) },
					{ fight::Name("Debris", 0) },
					{ fight::Name("Paper", 0) },
					{ fight::Name("Rocks", 0) },
					{ fight::Name("RotorWash", 0) },
					{ fight::Name("TankCrush", 0) },
					{ fight::Name("Script", 0) },
					{ fight::Name("Momentum", 0) },
					{ fight::Name("SmallRotorWash", 0) },
					{ fight::Name("25mm", 0) },
					{ fight::Name("30mm", 0) },
					{ fight::Name("40mm", 0) },
					{ fight::Name("40mm_Specialist", 0) },
					{ fight::Name("70mm", 0) },
					{ fight::Name("127mm", 0) },
					{ fight::Name("50cal", 0) },
					{ fight::Name("RotorBlades", 0) },
					{ fight::Name("BloodtoxWash", 0) },
					{ fight::Name("gunTurretBullet", 0) },
					{ fight::Name("500mm", 0) },
					{ fight::Name("Thermobaric1", 0) },
					{ fight::Name("Thermobaric2", 0) },
					{ fight::Name("Throw", 0) },
					{ fight::Name("MotherVomit", 0) },
					{ fight::Name("RocketLauncherShell", 0) }
				};
		}
	}
}

// The dynamic initialisers and atexit stubs of the unit's globals:
// FUNCTION: ENGINE 0x10D50040
// FUNCTION: ENGINE 0x10D50070
// FUNCTION: ENGINE 0x10D500A0
// FUNCTION: ENGINE 0x10D500D0
// FUNCTION: ENGINE 0x10D50150
// FUNCTION: ENGINE 0x10D50180
// FUNCTION: ENGINE 0x10D501B0
// FUNCTION: ENGINE 0x10D501E0
// FUNCTION: ENGINE 0x10D50210
// FUNCTION: ENGINE 0x10D50240
// FUNCTION: ENGINE 0x10D50270
// FUNCTION: ENGINE 0x10D502A0
// FUNCTION: ENGINE 0x10D502D0
// FUNCTION: ENGINE 0x10D50300
// FUNCTION: ENGINE 0x10D50370
// FUNCTION: ENGINE 0x10D503C0
// FUNCTION: ENGINE 0x10D50490
// FUNCTION: ENGINE 0x10D50550
// FUNCTION: ENGINE 0x10D505C0
// FUNCTION: ENGINE 0x10D50650
// FUNCTION: ENGINE 0x10D50680
// FUNCTION: ENGINE 0x10D50720
// FUNCTION: ENGINE 0x10D50A70
// FUNCTION: ENGINE 0x10D50C80
// FUNCTION: ENGINE 0x10D50CF0
// FUNCTION: ENGINE 0x10D50DC0
// FUNCTION: ENGINE 0x10D50F00
// FUNCTION: ENGINE 0x10D50F30
// FUNCTION: ENGINE 0x10D50F60
// FUNCTION: ENGINE 0x10D50FD0
// FUNCTION: ENGINE 0x10D51000
// FUNCTION: ENGINE 0x10D51030
// FUNCTION: ENGINE 0x10D51060
// FUNCTION: ENGINE 0x10D51120
// FUNCTION: ENGINE 0x10D51150
// FUNCTION: ENGINE 0x10D51180
// FUNCTION: ENGINE 0x10D511B0
// FUNCTION: ENGINE 0x10D511E0
// FUNCTION: ENGINE 0x10D51210
// FUNCTION: ENGINE 0x10D51240
// FUNCTION: ENGINE 0x10D51270
// FUNCTION: ENGINE 0x10D512A0
// FUNCTION: ENGINE 0x10D512D0
// FUNCTION: ENGINE 0x10D51300
// FUNCTION: ENGINE 0x10D51330
// FUNCTION: ENGINE 0x10D51360
// FUNCTION: ENGINE 0x10D51390
// FUNCTION: ENGINE 0x10D514D0
// FUNCTION: ENGINE 0x10D51500
// FUNCTION: ENGINE 0x10D515C0
// FUNCTION: ENGINE 0x10D515F0
// FUNCTION: ENGINE 0x10D51620
// FUNCTION: ENGINE 0x10D51750
// FUNCTION: ENGINE 0x10D51780
// FUNCTION: ENGINE 0x10D517B0
// FUNCTION: ENGINE 0x10D517E0
// FUNCTION: ENGINE 0x10D51810
// FUNCTION: ENGINE 0x10D518B0
// FUNCTION: ENGINE 0x10D518E0
// FUNCTION: ENGINE 0x10D51910
// FUNCTION: ENGINE 0x10D51940
// FUNCTION: ENGINE 0x10D51A40
// FUNCTION: ENGINE 0x10D51A70
// FUNCTION: ENGINE 0x10D51AA0
// FUNCTION: ENGINE 0x10D51AD0
// FUNCTION: ENGINE 0x10D51E20
// FUNCTION: ENGINE 0x10D51E50
// FUNCTION: ENGINE 0x10D51E80
// FUNCTION: ENGINE 0x10D51EB0
// FUNCTION: ENGINE 0x10D51F30
// FUNCTION: ENGINE 0x10D51F60
// FUNCTION: ENGINE 0x10D51F90
// FUNCTION: ENGINE 0x10D51FC0
// FUNCTION: ENGINE 0x10D51FF0
// FUNCTION: ENGINE 0x10D52120
// FUNCTION: ENGINE 0x10D52150
// FUNCTION: ENGINE 0x10D521D0
// FUNCTION: ENGINE 0x10D52200
// FUNCTION: ENGINE 0x10D52230
// FUNCTION: ENGINE 0x10D52260
// FUNCTION: ENGINE 0x10D52290
// FUNCTION: ENGINE 0x10D522C0
// FUNCTION: ENGINE 0x10D52700
// FUNCTION: ENGINE 0x10D52730
// FUNCTION: ENGINE 0x10D52760
// FUNCTION: ENGINE 0x10D52790
// FUNCTION: ENGINE 0x10D527C0
// FUNCTION: ENGINE 0x10D527F0
// FUNCTION: ENGINE 0x10D52830
// FUNCTION: ENGINE 0x10D52860
// FUNCTION: ENGINE 0x10D528E0
// FUNCTION: ENGINE 0x10D52910
// FUNCTION: ENGINE 0x10D52940
// FUNCTION: ENGINE 0x10D52970
// FUNCTION: ENGINE 0x10D529F0
// FUNCTION: ENGINE 0x10D52A20
// FUNCTION: ENGINE 0x10D52A50
// FUNCTION: ENGINE 0x10D52A80
// FUNCTION: ENGINE 0x10D52AE0
// FUNCTION: ENGINE 0x10D52B10
// FUNCTION: ENGINE 0x10D52B40
// FUNCTION: ENGINE 0x10D52B70
// FUNCTION: ENGINE 0x10D52BA0
// FUNCTION: ENGINE 0x10D52C00
// FUNCTION: ENGINE 0x10D52C30
// FUNCTION: ENGINE 0x10D52C60
// FUNCTION: ENGINE 0x10D52C90
// FUNCTION: ENGINE 0x10D52CC0
// FUNCTION: ENGINE 0x10D52CF0
// FUNCTION: ENGINE 0x10D52D20
// FUNCTION: ENGINE 0x10D52D50
// FUNCTION: ENGINE 0x10D52D80
// FUNCTION: ENGINE 0x10D52DB0
// FUNCTION: ENGINE 0x10D52DE0
// FUNCTION: ENGINE 0x10D52E10
// FUNCTION: ENGINE 0x10D52E40
// FUNCTION: ENGINE 0x10D52E70
// FUNCTION: ENGINE 0x10D52EA0
// FUNCTION: ENGINE 0x10D52ED0
// FUNCTION: ENGINE 0x10D52F20
// FUNCTION: ENGINE 0x10D52F80
// FUNCTION: ENGINE 0x10D52FE0
// FUNCTION: ENGINE 0x10D53010
// FUNCTION: ENGINE 0x10D53040
// FUNCTION: ENGINE 0x10D53070
// FUNCTION: ENGINE 0x10D530A0
// FUNCTION: ENGINE 0x10D530D0
// FUNCTION: ENGINE 0x10D53100
// FUNCTION: ENGINE 0x10D53130
// FUNCTION: ENGINE 0x10D53240
// FUNCTION: ENGINE 0x10D53270
// FUNCTION: ENGINE 0x10D532C0
// FUNCTION: ENGINE 0x10D53320
// FUNCTION: ENGINE 0x10D53380
// FUNCTION: ENGINE 0x10D533B0
// FUNCTION: ENGINE 0x10D533E0
// FUNCTION: ENGINE 0x10D53410
// FUNCTION: ENGINE 0x10D53440
// FUNCTION: ENGINE 0x10D53470
// FUNCTION: ENGINE 0x10D534A0
// FUNCTION: ENGINE 0x10D534D0
// FUNCTION: ENGINE 0x10D53500
// FUNCTION: ENGINE 0x10D53550
// FUNCTION: ENGINE 0x10D53A70
// FUNCTION: ENGINE 0x10D53D60
// FUNCTION: ENGINE 0x10D81CA0
// FUNCTION: ENGINE 0x10D81CB0
// FUNCTION: ENGINE 0x10D81CC0
// FUNCTION: ENGINE 0x10D81CD0
// FUNCTION: ENGINE 0x10D81CF0
// FUNCTION: ENGINE 0x10D81D00
// FUNCTION: ENGINE 0x10D81D10
// FUNCTION: ENGINE 0x10D81D20
// FUNCTION: ENGINE 0x10D81D30
// FUNCTION: ENGINE 0x10D81D40
// FUNCTION: ENGINE 0x10D81D50
// FUNCTION: ENGINE 0x10D81D60
// FUNCTION: ENGINE 0x10D81D70
// FUNCTION: ENGINE 0x10D81D80
// FUNCTION: ENGINE 0x10D81D90
// FUNCTION: ENGINE 0x10D81DA0
// FUNCTION: ENGINE 0x10D81DD0
// FUNCTION: ENGINE 0x10D81DE0
// FUNCTION: ENGINE 0x10D81DF0
// FUNCTION: ENGINE 0x10D81E10
// FUNCTION: ENGINE 0x10D81E20
// FUNCTION: ENGINE 0x10D81E40
// FUNCTION: ENGINE 0x10D81E50
// FUNCTION: ENGINE 0x10D81E60
// FUNCTION: ENGINE 0x10D81E70
// FUNCTION: ENGINE 0x10D81E90
// FUNCTION: ENGINE 0x10D81EB0
// FUNCTION: ENGINE 0x10D81EC0
// FUNCTION: ENGINE 0x10D81ED0
// FUNCTION: ENGINE 0x10D81EF0
// FUNCTION: ENGINE 0x10D81F00
// FUNCTION: ENGINE 0x10D81F10
// FUNCTION: ENGINE 0x10D81F20
// FUNCTION: ENGINE 0x10D81F30
// FUNCTION: ENGINE 0x10D81F40
// FUNCTION: ENGINE 0x10D81F50
// FUNCTION: ENGINE 0x10D81F60
// FUNCTION: ENGINE 0x10D81F70
// FUNCTION: ENGINE 0x10D81F80
// FUNCTION: ENGINE 0x10D81F90
// FUNCTION: ENGINE 0x10D81FA0
// FUNCTION: ENGINE 0x10D81FB0
// FUNCTION: ENGINE 0x10D81FC0
// FUNCTION: ENGINE 0x10D81FD0
// FUNCTION: ENGINE 0x10D81FE0
// FUNCTION: ENGINE 0x10D81FF0
// FUNCTION: ENGINE 0x10D82000
// FUNCTION: ENGINE 0x10D82040
// FUNCTION: ENGINE 0x10D82050
// FUNCTION: ENGINE 0x10D82070
// FUNCTION: ENGINE 0x10D82080
// FUNCTION: ENGINE 0x10D82090
// FUNCTION: ENGINE 0x10D820B0
// FUNCTION: ENGINE 0x10D820C0
// FUNCTION: ENGINE 0x10D820D0
// FUNCTION: ENGINE 0x10D820E0
// FUNCTION: ENGINE 0x10D820F0
// FUNCTION: ENGINE 0x10D82110
// FUNCTION: ENGINE 0x10D82120
// FUNCTION: ENGINE 0x10D82130
// FUNCTION: ENGINE 0x10D82140
// FUNCTION: ENGINE 0x10D82170
// FUNCTION: ENGINE 0x10D82180
// FUNCTION: ENGINE 0x10D82190
// FUNCTION: ENGINE 0x10D821A0
// FUNCTION: ENGINE 0x10D82200
// FUNCTION: ENGINE 0x10D82210
// FUNCTION: ENGINE 0x10D82280
// FUNCTION: ENGINE 0x10D82290
// FUNCTION: ENGINE 0x10D822A0
// FUNCTION: ENGINE 0x10D822B0
// FUNCTION: ENGINE 0x10D822C0
// FUNCTION: ENGINE 0x10D822D0
// FUNCTION: ENGINE 0x10D822E0
// FUNCTION: ENGINE 0x10D82340
// FUNCTION: ENGINE 0x10D82350
// FUNCTION: ENGINE 0x10D82370
// FUNCTION: ENGINE 0x10D82380
// FUNCTION: ENGINE 0x10D82390
// FUNCTION: ENGINE 0x10D823E0
// FUNCTION: ENGINE 0x10D823F0
// FUNCTION: ENGINE 0x10D82400
// FUNCTION: ENGINE 0x10D82440
// FUNCTION: ENGINE 0x10D82450
// FUNCTION: ENGINE 0x10D82460
// FUNCTION: ENGINE 0x10D82470
// FUNCTION: ENGINE 0x10D82480
// FUNCTION: ENGINE 0x10D82490
// FUNCTION: ENGINE 0x10D824A0
// FUNCTION: ENGINE 0x10D824B0
// FUNCTION: ENGINE 0x10D824D0
// FUNCTION: ENGINE 0x10D824E0
// FUNCTION: ENGINE 0x10D824F0
// FUNCTION: ENGINE 0x10D82500
// FUNCTION: ENGINE 0x10D82520
// FUNCTION: ENGINE 0x10D82530
// FUNCTION: ENGINE 0x10D82540
// FUNCTION: ENGINE 0x10D82550
// FUNCTION: ENGINE 0x10D82570
// FUNCTION: ENGINE 0x10D82580
// FUNCTION: ENGINE 0x10D82590
// FUNCTION: ENGINE 0x10D825A0
// FUNCTION: ENGINE 0x10D825B0
// FUNCTION: ENGINE 0x10D825D0
// FUNCTION: ENGINE 0x10D825E0
// FUNCTION: ENGINE 0x10D825F0
// FUNCTION: ENGINE 0x10D82600
// FUNCTION: ENGINE 0x10D82610
// FUNCTION: ENGINE 0x10D82620
// FUNCTION: ENGINE 0x10D82630
// FUNCTION: ENGINE 0x10D82640
// FUNCTION: ENGINE 0x10D82650
// FUNCTION: ENGINE 0x10D82660
// FUNCTION: ENGINE 0x10D82670
// FUNCTION: ENGINE 0x10D82680
// FUNCTION: ENGINE 0x10D826A0
// FUNCTION: ENGINE 0x10D826B0
// FUNCTION: ENGINE 0x10D826C0
// FUNCTION: ENGINE 0x10D826D0
// FUNCTION: ENGINE 0x10D826E0
// FUNCTION: ENGINE 0x10D826F0
// FUNCTION: ENGINE 0x10D82700
// FUNCTION: ENGINE 0x10D82710
// FUNCTION: ENGINE 0x10D82720
// FUNCTION: ENGINE 0x10D82730
// FUNCTION: ENGINE 0x10D82740
// FUNCTION: ENGINE 0x10D82750
// FUNCTION: ENGINE 0x10D82760
// FUNCTION: ENGINE 0x10D82770
// FUNCTION: ENGINE 0x10D82780
// FUNCTION: ENGINE 0x10D82790
// FUNCTION: ENGINE 0x10D827A0
// FUNCTION: ENGINE 0x10D827B0
// FUNCTION: ENGINE 0x10D827C0
// FUNCTION: ENGINE 0x10D827D0
// FUNCTION: ENGINE 0x10D827E0
// FUNCTION: ENGINE 0x10D827F0
// FUNCTION: ENGINE 0x10D82800
// FUNCTION: ENGINE 0x10D82860
// FUNCTION: ENGINE 0x10D82880
// FUNCTION: ENGINE 0x10D82890
