// The game database keys of the profile and the saved game (Proto_Profile_*, Proto_Save_*, Proto_Volatile_*): names
// that the units read and write through the game database (unit name guess: the engine's static initialisers
// 0x10D60280 - 0x10D60940 construct them in one run, in no unit that has code of its own).
#include "code/core/name.h"

namespace proto
{
	core::Name<core::CaseSensitiveKey> gProtoProfileCameraHorizontalInv("Proto_Profile_CameraHorizontalInv", 0);
	core::Name<core::CaseSensitiveKey> gProtoProfileCameraVerticalInv("Proto_Profile_CameraVerticalInv", 0);
	core::Name<core::CaseSensitiveKey> gProtoProfileCameraVerticalInvTank("Proto_Profile_CameraVerticalInv_Tank", 0);
	core::Name<core::CaseSensitiveKey> gProtoProfileCameraVerticalInvHeli("Proto_Profile_CameraVerticalInv_Heli", 0);
	core::Name<core::CaseSensitiveKey> gProtoProfileMouseWheelInvHeli("Proto_Profile_MouseWheelInv_Heli", 0);
	core::Name<core::CaseSensitiveKey> gProtoProfileGamepadRumbleEnabled("Proto_Profile_GamepadRumbleEnabled", 0);
	core::Name<core::CaseSensitiveKey> gProtoProfileTargetToggleEnabled("Proto_Profile_TargetToggleEnabled", 0);
	core::Name<core::CaseSensitiveKey> gProtoProfileBodySurfCheatEnabled("Proto_Profile_BodySurfCheatEnabled", 0);
	core::Name<core::CaseSensitiveKey> gOLSProfileYAxisInversion("OLS_Profile_YAxisInversion", 0);
	core::Name<core::CaseSensitiveKey> gOLSProfileControllerVibration("OLS_Profile_ControllerVibration", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveStoryComplete("Proto_Save_StoryComplete", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveNextStoryMission("Proto_Save_NextStoryMission", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveMissionsCompleted("Proto_Save_MissionsCompleted", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveArtilleryStrikeCount("Proto_Save_ArtilleryStrikeCount", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveDifficulty("Proto_Save_Difficulty", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveQuickPowerSelect("Proto_Save_QuickPowerSelect", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveDisguiseName("Proto_Save_Disguise_Name", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveDisguiseDrawableName("Proto_Save_Disguise_DrawableName", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveDisguiseStreamPackageName("Proto_Save_Disguise_StreamPackageName", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveDisguiseFaction("Proto_Save_Disguise_Faction", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveDisguiseShaderColourEntriesName("Proto_Save_Disguise_ShaderColourEntriesName", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveDisguiseShaderColourEntriesRed("Proto_Save_Disguise_ShaderColourEntriesRed", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveDisguiseShaderColourEntriesGreen("Proto_Save_Disguise_ShaderColourEntriesGreen", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveDisguiseShaderColourEntriesBlue("Proto_Save_Disguise_ShaderColourEntriesBlue", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveDisguiseShaderColourEntriesAlpha("Proto_Save_Disguise_ShaderColourEntriesAlpha", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveSpawnPosition("Proto_Save_SpawnPosition", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveSpawnFacing("Proto_Save_SpawnFacing", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveProtoVersion("Proto_Save_ProtoVersion", 0);
	core::Name<core::CaseSensitiveKey> gProtoVolatileStartType("Proto_Volatile_StartType", 0);
	core::Name<core::CaseSensitiveKey> gProtoVolatileIsInVehicle("Proto_Volatile_IsInVehicle", 0);
	core::Name<core::CaseSensitiveKey> gProtoTutorial("Proto_Tutorial", 0);
	core::Name<core::CaseSensitiveKey> gProtoTutorialImageName("Proto_Tutorial_ImageName", 0);
	core::Name<core::CaseSensitiveKey> gProtoTutorialImageCaption("Proto_Tutorial_ImageCaption", 0);
	core::Name<core::CaseSensitiveKey> gProtoTutorialNum("Proto_Tutorial_Num", 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D60280
// FUNCTION: ENGINE 0x10D602B0
// FUNCTION: ENGINE 0x10D602E0
// FUNCTION: ENGINE 0x10D60310
// FUNCTION: ENGINE 0x10D60340
// FUNCTION: ENGINE 0x10D60370
// FUNCTION: ENGINE 0x10D603A0
// FUNCTION: ENGINE 0x10D603D0
// FUNCTION: ENGINE 0x10D60400
// FUNCTION: ENGINE 0x10D60430
// FUNCTION: ENGINE 0x10D60460
// FUNCTION: ENGINE 0x10D60490
// FUNCTION: ENGINE 0x10D604C0
// FUNCTION: ENGINE 0x10D604F0
// FUNCTION: ENGINE 0x10D60520
// FUNCTION: ENGINE 0x10D60580
// FUNCTION: ENGINE 0x10D605B0
// FUNCTION: ENGINE 0x10D605E0
// FUNCTION: ENGINE 0x10D60610
// FUNCTION: ENGINE 0x10D60640
// FUNCTION: ENGINE 0x10D60670
// FUNCTION: ENGINE 0x10D606A0
// FUNCTION: ENGINE 0x10D606D0
// FUNCTION: ENGINE 0x10D60700
// FUNCTION: ENGINE 0x10D60730
// FUNCTION: ENGINE 0x10D60760
// FUNCTION: ENGINE 0x10D60790
// FUNCTION: ENGINE 0x10D607C0
// FUNCTION: ENGINE 0x10D60820
// FUNCTION: ENGINE 0x10D60880
// FUNCTION: ENGINE 0x10D608B0
// FUNCTION: ENGINE 0x10D608E0
// FUNCTION: ENGINE 0x10D60910
// FUNCTION: ENGINE 0x10D60940
// FUNCTION: ENGINE 0x10D855C0
// FUNCTION: ENGINE 0x10D855D0
// FUNCTION: ENGINE 0x10D855E0
// FUNCTION: ENGINE 0x10D855F0
// FUNCTION: ENGINE 0x10D85600
// FUNCTION: ENGINE 0x10D85610
// FUNCTION: ENGINE 0x10D85620
// FUNCTION: ENGINE 0x10D85630
// FUNCTION: ENGINE 0x10D85640
// FUNCTION: ENGINE 0x10D85650
// FUNCTION: ENGINE 0x10D85660
// FUNCTION: ENGINE 0x10D85670
// FUNCTION: ENGINE 0x10D85680
// FUNCTION: ENGINE 0x10D85690
// FUNCTION: ENGINE 0x10D856A0
// FUNCTION: ENGINE 0x10D856C0
// FUNCTION: ENGINE 0x10D856D0
// FUNCTION: ENGINE 0x10D856E0
// FUNCTION: ENGINE 0x10D856F0
// FUNCTION: ENGINE 0x10D85700
// FUNCTION: ENGINE 0x10D85710
// FUNCTION: ENGINE 0x10D85720
// FUNCTION: ENGINE 0x10D85730
// FUNCTION: ENGINE 0x10D85740
// FUNCTION: ENGINE 0x10D85750
// FUNCTION: ENGINE 0x10D85760
// FUNCTION: ENGINE 0x10D85770
// FUNCTION: ENGINE 0x10D85780
// FUNCTION: ENGINE 0x10D857A0
// FUNCTION: ENGINE 0x10D857C0
// FUNCTION: ENGINE 0x10D857D0
// FUNCTION: ENGINE 0x10D857E0
// FUNCTION: ENGINE 0x10D857F0
// FUNCTION: ENGINE 0x10D85800
