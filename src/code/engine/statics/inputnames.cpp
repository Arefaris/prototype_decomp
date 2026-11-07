// Globals that the engine's static initialisers 0x10D4C7E0 - 0x10D4FFE0 construct in translation units whose code is not
// reconstructed: the input control and hot key names, the ground spike and scenario names of the motion and fight item units, and the names and strings every such unit repeats through its headers (the
// slot group names, the audio file and listener names). Unit name guess; one file holds the runs of several units.
#include "code/core/name.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/om/staticinit.h"

namespace engine
{
	MessageListeners gScenario26("scenario", 0);
	MessageListeners gScenario27("scenario", 0);
	core::Name<core::CaseSensitiveKey> gEncounterObject6("encounterObject", 0);
	core::Name<core::CaseSensitiveKey> gEncounter6("encounter", 0);
	core::Name<core::CaseSensitiveKey> gSupremeHunter("supreme_hunter", 0);
	core::Name<core::CaseSensitiveKey> gSupremeHunterWeak("supreme_hunter_weak", 0);
	MessageListeners gScenario28("scenario", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour2("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour3("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour4("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup92("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty100("", 0);
	MessageListeners gScenario29("scenario", 0);
	core::Name<core::CaseSensitiveKey> gSenses("Senses", 0);
	core::Name<core::CaseSensitiveKey> gDisguise("disguise", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup93("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty101("", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour5("AlexArmour", 0);
	MessageListeners gScenario30("scenario", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour6("AlexArmour", 0);
	om::String gAudioGlobalP3d31 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener32 = om::NameOfText("Listener");
	om::ClassName gMaster32 = om::NameOfText("Master");
	core::Name<core::CaseInsensitiveKey32> gPoint0("point0", 0);
	core::Name<core::CaseInsensitiveKey32> gPoint1("point1", 0);
	core::Name<core::CaseInsensitiveKey32> gPoint2("point2", 0);
	core::Name<core::CaseInsensitiveKey32> gPoint3("point3", 0);
	core::Name<core::CaseInsensitiveKey32> gUpVector("upVector", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup94("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty102("", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour7("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup95("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty103("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup96("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty104("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup97("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty105("", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour8("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup98("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty106("", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour9("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup99("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty107("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup100("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty108("", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour10("AlexArmour", 0);
	MessageListeners gScenario31("scenario", 0);
	MessageListeners gScenario32("scenario", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour11("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup101("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty109("", 0);
	core::Name<core::CaseSensitiveKey> gHunterLandedMotionEvent("HunterLandedMotionEvent", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour12("AlexArmour", 0);
	om::String gAudioGlobalP3d32 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener33 = om::NameOfText("Listener");
	om::ClassName gMaster33 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup102("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty110("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup103("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty111("", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour13("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour14("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup104("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty112("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup105("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty113("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup106("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty114("", 0);
	fight::EnumEntry gGiverTable[3] =
		{
			{ fight::Name("Giver", 0) },
			{ fight::Name("Taker", 0) },
			{ fight::Name("Alert", 0) }
		};
	MessageListeners gScenario33("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup107("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty115("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup108("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty116("", 0);
	MessageListeners gScenario34("scenario", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour15("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour16("AlexArmour", 0);
	fight::EnumEntry gConstantTable[2] =
		{
			{ fight::Name("Constant", 0) },
			{ fight::Name("TrackTimer", 0) }
		};
	fight::EnumEntry gNoneTable2[5] =
		{
			{ fight::Name("None", 0) },
			{ fight::Name("At target", 0) },
			{ fight::Name("Intention", 0) },
			{ fight::Name("At target feet", 0) },
			{ fight::Name("At temporary target", 0) }
		};
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup109("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty117("", 0);
	om::String gAudioGlobalP3d33 = om::StringOfText("audio\\global.p3d");
	om::ClassName gListener34 = om::NameOfText("Listener");
	om::ClassName gMaster34 = om::NameOfText("Master");
	core::Name<core::CaseSensitiveKey> gAlexArmour17("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup110("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty118("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup111("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty119("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup112("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty120("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup113("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty121("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup114("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty122("", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour18("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup115("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty123("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup116("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty124("", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour19("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour20("AlexArmour", 0);
	core::Name<core::CaseSensitiveKey> gAlexArmour21("AlexArmour", 0);
	core::Name<core::CaseInsensitiveKey32> gPoint02("point0", 0);
	core::Name<core::CaseInsensitiveKey32> gPoint12("point1", 0);
	core::Name<core::CaseInsensitiveKey32> gPoint22("point2", 0);
	core::Name<core::CaseInsensitiveKey32> gPoint32("point3", 0);
	core::Name<core::CaseInsensitiveKey32> gUpVector2("upVector", 0);
	core::Name<core::CaseSensitiveKey> gEmpty125("", 0);
	MessageListeners gScenario35("scenario", 0);
}

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::EnumEntry gChargeConditionTypeTable[4] =
				{
					{ fight::Name("<Invalid>", 0) },
					{ fight::Name("Jump", 0) },
					{ fight::Name("Attack", 0) },
					{ fight::Name("Throw", 0) }
				};
			fight::EnumEntry gRadialBlurTrackAttachSpaceTable[4] =
				{
					{ fight::Name("World Space", 0) },
					{ fight::Name("Game Object Space", 0) },
					{ fight::Name("Joint Space", 0) },
					{ fight::Name("Game Object Pose", 0) }
				};
			fight::EnumEntry gJointLookAtTrackWhereTable[6] =
				{
					{ fight::Name("At target", 0) },
					{ fight::Name("Intention", 0) },
					{ fight::Name("At target feet", 0) },
					{ fight::Name("At temporary target", 0) },
					{ fight::Name("At temporary target feet", 0) },
					{ fight::Name("At FreeAim position", 0) }
				};
			fight::EnumEntry gReactionHitGrabTrackObjectTable[2] =
				{
					{ fight::Name("Giver", 0) },
					{ fight::Name("Receiver", 0) }
				};
			fight::EnumEntry gMotionStateConditionStateTable[21] =
				{
					{ fight::Name("Idling", 0) },
					{ fight::Name("Walking", 0) },
					{ fight::Name("Running", 0) },
					{ fight::Name("Falling", 0) },
					{ fight::Name("Jumping", 0) },
					{ fight::Name("Wallrunning", 0) },
					{ fight::Name("GettingHit", 0) },
					{ fight::Name("AttackWindup", 0) },
					{ fight::Name("AttackRelease", 0) },
					{ fight::Name("Flying", 0) },
					{ fight::Name("Climbing", 0) },
					{ fight::Name("BeingGrabbed", 0) },
					{ fight::Name("Driving", 0) },
					{ fight::Name("Blocking", 0) },
					{ fight::Name("Stunned", 0) },
					{ fight::Name("Gliding", 0) },
					{ fight::Name("JumpingOutOfWater", 0) },
					{ fight::Name("Consuming", 0) },
					{ fight::Name("Devastator", 0) },
					{ fight::Name("Sliding", 0) },
					{ fight::Name("Other", 0) }
				};
			fight::EnumEntry gDetectObbCollisionConditionCollideWithTable[32] =
				{
					{ fight::Name("StaticObject", 0) },
					{ fight::Name("SimulatedObject", 0) },
					{ fight::Name("SupportingSurface", 0) },
					{ fight::Name("Attachable", 0) },
					{ fight::Name("Health", 0) },
					{ fight::Name("HitReaction", 0) },
					{ fight::Name("Prop", 0) },
					{ fight::Name("CharacterSolver", 0) },
					{ fight::Name("CauseDamage", 0) },
					{ fight::Name("CauseHitReaction", 0) },
					{ fight::Name("TriggerVolume", 0) },
					{ fight::Name("Grabbable", 0) },
					{ fight::Name("NavigationSimulatedObstacle", 0) },
					{ fight::Name("AmbientLookaheadVolume", 0) },
					{ fight::Name("PedBehaviour", 0) },
					{ fight::Name("VehicleBehaviour", 0) },
					{ fight::Name("Building", 0) },
					{ fight::Name("Dead", 0) },
					{ fight::Name("Tank", 0) },
					{ fight::Name("Walker", 0) },
					{ fight::Name("Flyer", 0) },
					{ fight::Name("Hunter", 0) },
					{ fight::Name("World", 0) },
					{ fight::Name("CharacterShield", 0) },
					{ fight::Name("District", 0) },
					{ fight::Name("Zone", 0) },
					{ fight::Name("Player", 0) },
					{ fight::Name("CameraPop", 0) },
					{ fight::Name("Shoveable", 0) },
					{ fight::Name("Pole", 0) },
					{ fight::Name("NISExclusionVolume", 0) },
					{ fight::Name("NavigationStaticObstacle", 0) }
				};
			fight::EnumEntry gCollisionGrabTrackPhysicsModeTable[4] =
				{
					{ fight::Name("Disabled", 0) },
					{ fight::Name("Simulated", 0) },
					{ fight::Name("SimulatedChild", 0) },
					{ fight::Name("Keyframed", 0) }
				};
		}
	}
}

// The dynamic initialisers and atexit stubs of the unit's globals:
// FUNCTION: ENGINE 0x10D4CC40
// FUNCTION: ENGINE 0x10D4CC70
// FUNCTION: ENGINE 0x10D4CCA0
// FUNCTION: ENGINE 0x10D4CCD0
// FUNCTION: ENGINE 0x10D4CD00
// FUNCTION: ENGINE 0x10D4CD30
// FUNCTION: ENGINE 0x10D4CEB0
// FUNCTION: ENGINE 0x10D4CEE0
// FUNCTION: ENGINE 0x10D4CF10
// FUNCTION: ENGINE 0x10D4CF40
// FUNCTION: ENGINE 0x10D4CF70
// FUNCTION: ENGINE 0x10D4CFA0
// FUNCTION: ENGINE 0x10D4CFD0
// FUNCTION: ENGINE 0x10D4D000
// FUNCTION: ENGINE 0x10D4D030
// FUNCTION: ENGINE 0x10D4D060
// FUNCTION: ENGINE 0x10D4D090
// FUNCTION: ENGINE 0x10D4D0C0
// FUNCTION: ENGINE 0x10D4D0F0
// FUNCTION: ENGINE 0x10D4D120
// FUNCTION: ENGINE 0x10D4D150
// FUNCTION: ENGINE 0x10D4D1A0
// FUNCTION: ENGINE 0x10D4D200
// FUNCTION: ENGINE 0x10D4D260
// FUNCTION: ENGINE 0x10D4D290
// FUNCTION: ENGINE 0x10D4D2C0
// FUNCTION: ENGINE 0x10D4D2F0
// FUNCTION: ENGINE 0x10D4D320
// FUNCTION: ENGINE 0x10D4D540
// FUNCTION: ENGINE 0x10D4D570
// FUNCTION: ENGINE 0x10D4D680
// FUNCTION: ENGINE 0x10D4D6B0
// FUNCTION: ENGINE 0x10D4D6E0
// FUNCTION: ENGINE 0x10D4D790
// FUNCTION: ENGINE 0x10D4D7C0
// FUNCTION: ENGINE 0x10D4D890
// FUNCTION: ENGINE 0x10D4D900
// FUNCTION: ENGINE 0x10D4D930
// FUNCTION: ENGINE 0x10D4D960
// FUNCTION: ENGINE 0x10D4D9E0
// FUNCTION: ENGINE 0x10D4DA10
// FUNCTION: ENGINE 0x10D4DA40
// FUNCTION: ENGINE 0x10D4DA70
// FUNCTION: ENGINE 0x10D4DAA0
// FUNCTION: ENGINE 0x10D4DB20
// FUNCTION: ENGINE 0x10D4DB50
// FUNCTION: ENGINE 0x10D4DB80
// FUNCTION: ENGINE 0x10D4DBB0
// FUNCTION: ENGINE 0x10D4DBE0
// FUNCTION: ENGINE 0x10D4DCD0
// FUNCTION: ENGINE 0x10D4DDA0
// FUNCTION: ENGINE 0x10D4E100
// FUNCTION: ENGINE 0x10D4E130
// FUNCTION: ENGINE 0x10D4E160
// FUNCTION: ENGINE 0x10D4E200
// FUNCTION: ENGINE 0x10D4E290
// FUNCTION: ENGINE 0x10D4E2C0
// FUNCTION: ENGINE 0x10D4E310
// FUNCTION: ENGINE 0x10D4E370
// FUNCTION: ENGINE 0x10D4E3D0
// FUNCTION: ENGINE 0x10D4E400
// FUNCTION: ENGINE 0x10D4E430
// FUNCTION: ENGINE 0x10D4E460
// FUNCTION: ENGINE 0x10D4E490
// FUNCTION: ENGINE 0x10D4E4C0
// FUNCTION: ENGINE 0x10D4E4F0
// FUNCTION: ENGINE 0x10D4E520
// FUNCTION: ENGINE 0x10D4E550
// FUNCTION: ENGINE 0x10D4E580
// FUNCTION: ENGINE 0x10D4E670
// FUNCTION: ENGINE 0x10D4E6A0
// FUNCTION: ENGINE 0x10D4E750
// FUNCTION: ENGINE 0x10D4E7A0
// FUNCTION: ENGINE 0x10D4E7D0
// FUNCTION: ENGINE 0x10D4E800
// FUNCTION: ENGINE 0x10D4E8B0
// FUNCTION: ENGINE 0x10D4E980
// FUNCTION: ENGINE 0x10D4E9B0
// FUNCTION: ENGINE 0x10D4E9E0
// FUNCTION: ENGINE 0x10D4EA10
// FUNCTION: ENGINE 0x10D4EAD0
// FUNCTION: ENGINE 0x10D4EB90
// FUNCTION: ENGINE 0x10D4EBD0
// FUNCTION: ENGINE 0x10D4EC50
// FUNCTION: ENGINE 0x10D4EC80
// FUNCTION: ENGINE 0x10D4ECB0
// FUNCTION: ENGINE 0x10D4ED00
// FUNCTION: ENGINE 0x10D4ED60
// FUNCTION: ENGINE 0x10D4EDC0
// FUNCTION: ENGINE 0x10D4EDF0
// FUNCTION: ENGINE 0x10D4EE20
// FUNCTION: ENGINE 0x10D4EE50
// FUNCTION: ENGINE 0x10D4EE80
// FUNCTION: ENGINE 0x10D4EEB0
// FUNCTION: ENGINE 0x10D4F080
// FUNCTION: ENGINE 0x10D4F0B0
// FUNCTION: ENGINE 0x10D4F180
// FUNCTION: ENGINE 0x10D4F1B0
// FUNCTION: ENGINE 0x10D4F1E0
// FUNCTION: ENGINE 0x10D4F210
// FUNCTION: ENGINE 0x10D4F2B0
// FUNCTION: ENGINE 0x10D4F2E0
// FUNCTION: ENGINE 0x10D4F310
// FUNCTION: ENGINE 0x10D4F3B0
// FUNCTION: ENGINE 0x10D4F3E0
// FUNCTION: ENGINE 0x10D4F410
// FUNCTION: ENGINE 0x10D4F6D0
// FUNCTION: ENGINE 0x10D4F8C0
// FUNCTION: ENGINE 0x10D4F8F0
// FUNCTION: ENGINE 0x10D4F920
// FUNCTION: ENGINE 0x10D4F950
// FUNCTION: ENGINE 0x10D4F980
// FUNCTION: ENGINE 0x10D4F9B0
// FUNCTION: ENGINE 0x10D4F9E0
// FUNCTION: ENGINE 0x10D4FA10
// FUNCTION: ENGINE 0x10D4FF50
// FUNCTION: ENGINE 0x10D4FFE0
// FUNCTION: ENGINE 0x10D81010
// FUNCTION: ENGINE 0x10D81020
// FUNCTION: ENGINE 0x10D81060
// FUNCTION: ENGINE 0x10D81070
// FUNCTION: ENGINE 0x10D81080
// FUNCTION: ENGINE 0x10D81090
// FUNCTION: ENGINE 0x10D810E0
// FUNCTION: ENGINE 0x10D81100
// FUNCTION: ENGINE 0x10D81110
// FUNCTION: ENGINE 0x10D81120
// FUNCTION: ENGINE 0x10D81130
// FUNCTION: ENGINE 0x10D81140
// FUNCTION: ENGINE 0x10D81150
// FUNCTION: ENGINE 0x10D81160
// FUNCTION: ENGINE 0x10D81170
// FUNCTION: ENGINE 0x10D81190
// FUNCTION: ENGINE 0x10D811A0
// FUNCTION: ENGINE 0x10D811C0
// FUNCTION: ENGINE 0x10D811D0
// FUNCTION: ENGINE 0x10D811F0
// FUNCTION: ENGINE 0x10D81200
// FUNCTION: ENGINE 0x10D81210
// FUNCTION: ENGINE 0x10D81220
// FUNCTION: ENGINE 0x10D81230
// FUNCTION: ENGINE 0x10D81240
// FUNCTION: ENGINE 0x10D81250
// FUNCTION: ENGINE 0x10D81270
// FUNCTION: ENGINE 0x10D81280
// FUNCTION: ENGINE 0x10D812B0
// FUNCTION: ENGINE 0x10D812C0
// FUNCTION: ENGINE 0x10D812D0
// FUNCTION: ENGINE 0x10D812F0
// FUNCTION: ENGINE 0x10D81300
// FUNCTION: ENGINE 0x10D81330
// FUNCTION: ENGINE 0x10D81340
// FUNCTION: ENGINE 0x10D81350
// FUNCTION: ENGINE 0x10D81360
// FUNCTION: ENGINE 0x10D81380
// FUNCTION: ENGINE 0x10D81390
// FUNCTION: ENGINE 0x10D813B0
// FUNCTION: ENGINE 0x10D813C0
// FUNCTION: ENGINE 0x10D813D0
// FUNCTION: ENGINE 0x10D813F0
// FUNCTION: ENGINE 0x10D81400
// FUNCTION: ENGINE 0x10D81410
// FUNCTION: ENGINE 0x10D81420
// FUNCTION: ENGINE 0x10D81430
// FUNCTION: ENGINE 0x10D81470
// FUNCTION: ENGINE 0x10D814A0
// FUNCTION: ENGINE 0x10D81530
// FUNCTION: ENGINE 0x10D81540
// FUNCTION: ENGINE 0x10D81550
// FUNCTION: ENGINE 0x10D81570
// FUNCTION: ENGINE 0x10D81580
// FUNCTION: ENGINE 0x10D81590
// FUNCTION: ENGINE 0x10D815A0
// FUNCTION: ENGINE 0x10D815B0
// FUNCTION: ENGINE 0x10D815C0
// FUNCTION: ENGINE 0x10D815D0
// FUNCTION: ENGINE 0x10D815E0
// FUNCTION: ENGINE 0x10D815F0
// FUNCTION: ENGINE 0x10D81600
// FUNCTION: ENGINE 0x10D81610
// FUNCTION: ENGINE 0x10D81620
// FUNCTION: ENGINE 0x10D81630
// FUNCTION: ENGINE 0x10D81660
// FUNCTION: ENGINE 0x10D81670
// FUNCTION: ENGINE 0x10D81690
// FUNCTION: ENGINE 0x10D816A0
// FUNCTION: ENGINE 0x10D816B0
// FUNCTION: ENGINE 0x10D816C0
// FUNCTION: ENGINE 0x10D816E0
// FUNCTION: ENGINE 0x10D81710
// FUNCTION: ENGINE 0x10D81720
// FUNCTION: ENGINE 0x10D81730
// FUNCTION: ENGINE 0x10D81740
// FUNCTION: ENGINE 0x10D81780
// FUNCTION: ENGINE 0x10D817A0
// FUNCTION: ENGINE 0x10D817B0
// FUNCTION: ENGINE 0x10D817C0
// FUNCTION: ENGINE 0x10D817D0
// FUNCTION: ENGINE 0x10D817E0
// FUNCTION: ENGINE 0x10D817F0
// FUNCTION: ENGINE 0x10D81800
// FUNCTION: ENGINE 0x10D81810
// FUNCTION: ENGINE 0x10D81820
// FUNCTION: ENGINE 0x10D81830
// FUNCTION: ENGINE 0x10D81840
// FUNCTION: ENGINE 0x10D81850
// FUNCTION: ENGINE 0x10D81860
// FUNCTION: ENGINE 0x10D81890
// FUNCTION: ENGINE 0x10D818A0
// FUNCTION: ENGINE 0x10D818B0
// FUNCTION: ENGINE 0x10D818C0
// FUNCTION: ENGINE 0x10D818E0
// FUNCTION: ENGINE 0x10D818F0
// FUNCTION: ENGINE 0x10D81900
// FUNCTION: ENGINE 0x10D81920
// FUNCTION: ENGINE 0x10D81930
// FUNCTION: ENGINE 0x10D81940
// FUNCTION: ENGINE 0x10D81950
// FUNCTION: ENGINE 0x10D81990
// FUNCTION: ENGINE 0x10D819A0
// FUNCTION: ENGINE 0x10D819B0
// FUNCTION: ENGINE 0x10D819C0
// FUNCTION: ENGINE 0x10D819D0
// FUNCTION: ENGINE 0x10D819E0
// FUNCTION: ENGINE 0x10D819F0
// FUNCTION: ENGINE 0x10D81A00
// FUNCTION: ENGINE 0x10D81C50
// FUNCTION: ENGINE 0x10D81C80
