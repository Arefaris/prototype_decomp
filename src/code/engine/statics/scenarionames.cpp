// Globals that the engine's static initialisers 0x10D62710 - 0x10D72CE0 construct in translation units whose code is not
// reconstructed: the scenario, unlockable, free roam event, comparison and lit shader names, and the names and strings every such unit repeats through its headers (the
// slot group names, the audio file and listener names). Unit name guess; one file holds the runs of several units.
#include "code/core/name.h"
#include "code/core/namecopy.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/om/string.h"
#include "code/om/tree.h"
#include "code/math/matrix.h"
#include "code/pure3d/pddi/vertexdeclaration.h"

namespace engine
{
	core::Name<core::CaseSensitiveKey> gEmpty25("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup30("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty26("", 0);
	MessageListeners gScenario10("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUnlockables("Unlockables", 0);
	core::Name<core::CaseSensitiveKey> gUnlockablesPurchaseTypeCount("UnlockablesPurchaseTypeCount", 0);
	core::Name<core::CaseSensitiveKey> gCanPilotAllVehicles("Can Pilot all Vehicles", 0);
	core::Name<core::CaseSensitiveKey> gAcquiredAnUpgrade("Acquired an Upgrade", 0);
	core::Name<core::CaseSensitiveKey> gAcquiredAllUpgrades("Acquired all Upgrades", 0);
	core::Name<core::CaseSensitiveKey> gGoldAwardEvents("Gold Award Events", 0);
	MessageListeners gScenario11("scenario", 0);
	core::Name<core::CaseSensitiveKey> gFreLoco("freLoco", 0);
	core::Name<core::CaseSensitiveKey> gFreGlide("freGlide", 0);
	core::Name<core::CaseSensitiveKey> gFreKill("freKill", 0);
	core::Name<core::CaseSensitiveKey> gFre3WW("fre3WW", 0);
	core::Name<core::CaseSensitiveKey> gFreOpp("freOpp", 0);
	core::Name<core::CaseSensitiveKey> gFreSci("freSci", 0);
	core::Name<core::CaseSensitiveKey> gFreColl("freColl", 0);
	core::Name<core::CaseSensitiveKey> gDynamicPackageSlotGroup("DynamicPackageSlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup31("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty27("", 0);
	MessageListeners gScenario12("scenario", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup32("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty28("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup33("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty29("", 0);
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup34("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty30("", 0);
	fight::EnumEntry gCompareOperatorTable[6] =
	{
		{ fight::Name("<", 0) },
		{ fight::Name("<=", 0) },
		{ fight::Name("==", 0) },
		{ fight::Name("!=", 0) },
		{ fight::Name(">=", 0) },
		{ fight::Name(">", 0) }
	};
	fight::EnumEntry gEqualityOperatorTable[2] =
	{
		{ fight::Name("==", 0) },
		{ fight::Name("!=", 0) }
	};
	om::String gEmpty31("", 0);
	om::TreeHead gTreeHeadObject;
	om::TreeHead gTreeHeadObject2;
	om::TreeHead gTreeHeadObject3;
	om::TreeHead gTreeHeadObject4;
	om::String gName("?Name?", 0);
	core::Name<core::CaseSensitiveKey> gUnknownName11276940("?", 0);
	core::Name<core::CaseInsensitiveKey32> gCheapLit0Names[8] =
	{
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("cheapLit0", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("cheapLit1", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("cheapLit2", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("cheapLit3", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("cheapLit4", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("cheapLit5", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("cheapLit6", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("cheapLit7", 0)))
	};
	core::Name<core::CaseInsensitiveKey32> gShadowDepthMap0Names[8] =
	{
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("shadowDepthMap[0]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("shadowDepthMap[1]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("shadowDepthMap[2]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("shadowDepthMap[3]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("shadowDepthMap[4]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("shadowDepthMap[5]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("shadowDepthMap[6]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("shadowDepthMap[7]", 0)))
	};
	core::Name<core::CaseInsensitiveKey32> gTexCoordRange0Names[8] =
	{
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("texCoordRange[0]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("texCoordRange[1]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("texCoordRange[2]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("texCoordRange[3]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("texCoordRange[4]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("texCoordRange[5]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("texCoordRange[6]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("texCoordRange[7]", 0)))
	};
	core::Name<core::CaseInsensitiveKey32> gColourChannel0Names[8] =
	{
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel0", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel1", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel2", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel3", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel4", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel5", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel6", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourChannel7", 0)))
	};
	core::Name<core::CaseInsensitiveKey32> gTextureMatrix0Names[8] =
	{
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("textureMatrix[0]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("textureMatrix[1]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("textureMatrix[2]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("textureMatrix[3]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("textureMatrix[4]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("textureMatrix[5]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("textureMatrix[6]", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("textureMatrix[7]", 0)))
	};
	core::Name<core::CaseInsensitiveKey32> gP3dSHParam0Names[9] =
	{
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param0", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param1", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param2", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param3", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param4", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param5", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param6", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param7", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dSH_Param8", 0)))
	};
	core::Name<core::CaseInsensitiveKey32> gP3dParticleDebugParam1Names[3] =
	{
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dParticle_debugParam1", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dParticle_debugParam2", 0))),
		core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("p3dParticle_debugParam3", 0)))
	};
	core::Name<core::CaseInsensitiveKey32> gLitBasic = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("lit_basic", 0)));
	core::Name<core::CaseInsensitiveKey32> gProtoLitNight = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("proto_lit_night", 0)));
	core::Name<core::CaseInsensitiveKey32> gProtoLitInterior = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("proto_lit_interior", 0)));
	core::Name<core::CaseInsensitiveKey32> gProtoLitLOD = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("proto_lit_LOD", 0)));
	core::Name<core::CaseInsensitiveKey32> gProtoLitGlow = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("proto_lit_glow", 0)));
	core::Name<core::CaseInsensitiveKey32> gProtoGymLit = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("proto_gym_lit", 0)));
	core::Name<core::CaseInsensitiveKey32> gProtoLitThermal = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("proto_lit_thermal", 0)));
	core::Name<core::CaseInsensitiveKey32> gProtoLitChameleon = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("proto_lit_chameleon", 0)));
	core::Name<core::CaseInsensitiveKey32> gCaseInsensitiveKey32Object;
	core::Name<core::CaseInsensitiveKey32> gCharHair("char_hair", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvSkyDynamic("env_sky_dynamic", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvRoad("env_road", 0);
	core::Name<core::CaseInsensitiveKey32> gZCBV2EnvRoad("zCBV2_env_road", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvSidewalk("env_sidewalk", 0);
	core::Name<core::CaseInsensitiveKey32> gZCBV2EnvSidewalk("zCBV2_env_sidewalk", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvDecalBiasNm("env_decal_bias_nm", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvWater("env_water", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvMidgroundTraffic("env_midground_traffic", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvMidgroundTree("env_midground_tree", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvVehicleColorvar("env_vehicle_colorvar", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvVehicleGlassFade("env_vehicle_glass_fade", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvCarTire("env_car_tire", 0);
	core::Name<core::CaseInsensitiveKey32> gPpObjDistortion("pp_obj_distortion", 0);
	core::Name<core::CaseInsensitiveKey32> gPfxObjDistortion("pfx_obj_distortion", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvDecal("env_decal", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvDecalNm("env_decal_nm", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvLightDecalSpot("env_light_decal_spot", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvMidgroundLights("env_midground_lights", 0);
	core::Name<core::CaseInsensitiveKey32> gPpFogBuffer("pp_fog_buffer", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvHaze("env_haze", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvMidground("env_midground", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvHiveExterior("env_hive_exterior", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvHiveDecal("env_hive_decal", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvHiveInterior("env_hive_interior", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvMidgroundRoad("env_midground_road", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvMidgroundShoreline("env_midground_shoreline", 0);
	core::Name<core::CaseInsensitiveKey32> gEnvMidgroundShorelinebuildings("env_midground_shorelinebuildings", 0);
	core::Name<core::CaseInsensitiveKey32> gFxCbvcolorAlpha("fx_cbvcolor_alpha", 0);
	core::Name<core::CaseInsensitiveKey32> gHudIcon("hud_icon", 0);
	math::Matrix gIdentityMatrix = math::Matrix::IDENTITY;
	math::Matrix gIdentityMatrix2 = math::Matrix::IDENTITY;
	pure3d::dxVertexDeclaration gdxVertexDeclarationObject;
}

// The dynamic initialisers and atexit stubs of the unit's globals:
// FUNCTION: ENGINE 0x10D62710
// FUNCTION: ENGINE 0x10D62740
// FUNCTION: ENGINE 0x10D62770
// FUNCTION: ENGINE 0x10D627A0
// FUNCTION: ENGINE 0x10D65010
// FUNCTION: ENGINE 0x10D65040
// FUNCTION: ENGINE 0x10D65070
// FUNCTION: ENGINE 0x10D650A0
// FUNCTION: ENGINE 0x10D650D0
// FUNCTION: ENGINE 0x10D65100
// FUNCTION: ENGINE 0x10D65310
// FUNCTION: ENGINE 0x10D65340
// FUNCTION: ENGINE 0x10D65370
// FUNCTION: ENGINE 0x10D653A0
// FUNCTION: ENGINE 0x10D653D0
// FUNCTION: ENGINE 0x10D65400
// FUNCTION: ENGINE 0x10D65430
// FUNCTION: ENGINE 0x10D65460
// FUNCTION: ENGINE 0x10D65530
// FUNCTION: ENGINE 0x10D65560
// FUNCTION: ENGINE 0x10D65590
// FUNCTION: ENGINE 0x10D655C0
// FUNCTION: ENGINE 0x10D655F0
// FUNCTION: ENGINE 0x10D65620
// FUNCTION: ENGINE 0x10D65C10
// FUNCTION: ENGINE 0x10D65C40
// FUNCTION: ENGINE 0x10D65C70
// FUNCTION: ENGINE 0x10D65CA0
// FUNCTION: ENGINE 0x10D66290
// FUNCTION: ENGINE 0x10D66310
// FUNCTION: ENGINE 0x10D66460
// FUNCTION: ENGINE 0x10D664E0
// FUNCTION: ENGINE 0x10D66500
// FUNCTION: ENGINE 0x10D66550
// FUNCTION: ENGINE 0x10D66570
// FUNCTION: ENGINE 0x10D665B0
// FUNCTION: ENGINE 0x10D665D0
// FUNCTION: ENGINE 0x10D672A0
// FUNCTION: ENGINE 0x10D67BE0
// FUNCTION: ENGINE 0x10D67D60
// FUNCTION: ENGINE 0x10D67EE0
// FUNCTION: ENGINE 0x10D68060
// FUNCTION: ENGINE 0x10D681E0
// FUNCTION: ENGINE 0x10D69740
// FUNCTION: ENGINE 0x10D72290
// FUNCTION: ENGINE 0x10D72310
// FUNCTION: ENGINE 0x10D72350
// FUNCTION: ENGINE 0x10D72390
// FUNCTION: ENGINE 0x10D723D0
// FUNCTION: ENGINE 0x10D72410
// FUNCTION: ENGINE 0x10D72450
// FUNCTION: ENGINE 0x10D72490
// FUNCTION: ENGINE 0x10D727A0
// FUNCTION: ENGINE 0x10D72940
// FUNCTION: ENGINE 0x10D72960
// FUNCTION: ENGINE 0x10D72980
// FUNCTION: ENGINE 0x10D729A0
// FUNCTION: ENGINE 0x10D729C0
// FUNCTION: ENGINE 0x10D729E0
// FUNCTION: ENGINE 0x10D72A00
// FUNCTION: ENGINE 0x10D72A20
// FUNCTION: ENGINE 0x10D72A40
// FUNCTION: ENGINE 0x10D72A60
// FUNCTION: ENGINE 0x10D72A80
// FUNCTION: ENGINE 0x10D72AA0
// FUNCTION: ENGINE 0x10D72AC0
// FUNCTION: ENGINE 0x10D72AE0
// FUNCTION: ENGINE 0x10D72B00
// FUNCTION: ENGINE 0x10D72B20
// FUNCTION: ENGINE 0x10D72B40
// FUNCTION: ENGINE 0x10D72B60
// FUNCTION: ENGINE 0x10D72B80
// FUNCTION: ENGINE 0x10D72BA0
// FUNCTION: ENGINE 0x10D72BC0
// FUNCTION: ENGINE 0x10D72BE0
// FUNCTION: ENGINE 0x10D72C00
// FUNCTION: ENGINE 0x10D72C20
// FUNCTION: ENGINE 0x10D72C40
// FUNCTION: ENGINE 0x10D72C60
// FUNCTION: ENGINE 0x10D72C80
// FUNCTION: ENGINE 0x10D72CA0
// FUNCTION: ENGINE 0x10D72CC0
// FUNCTION: ENGINE 0x10D72CE0
// FUNCTION: ENGINE 0x10D86140
// FUNCTION: ENGINE 0x10D86150
// FUNCTION: ENGINE 0x10D86160
// FUNCTION: ENGINE 0x10D86170
// FUNCTION: ENGINE 0x10D86190
// FUNCTION: ENGINE 0x10D861A0
// FUNCTION: ENGINE 0x10D861B0
// FUNCTION: ENGINE 0x10D861C0
// FUNCTION: ENGINE 0x10D861D0
// FUNCTION: ENGINE 0x10D861E0
// FUNCTION: ENGINE 0x10D862A0
// FUNCTION: ENGINE 0x10D862B0
// FUNCTION: ENGINE 0x10D862C0
// FUNCTION: ENGINE 0x10D862D0
// FUNCTION: ENGINE 0x10D862E0
// FUNCTION: ENGINE 0x10D862F0
// FUNCTION: ENGINE 0x10D86300
// FUNCTION: ENGINE 0x10D86310
// FUNCTION: ENGINE 0x10D86330
// FUNCTION: ENGINE 0x10D86350
// FUNCTION: ENGINE 0x10D86360
// FUNCTION: ENGINE 0x10D86370
// FUNCTION: ENGINE 0x10D86380
// FUNCTION: ENGINE 0x10D86390
// FUNCTION: ENGINE 0x10D863C0
// FUNCTION: ENGINE 0x10D863D0
// FUNCTION: ENGINE 0x10D86410
// FUNCTION: ENGINE 0x10D86420
// FUNCTION: ENGINE 0x10D86620
// FUNCTION: ENGINE 0x10D86630
// FUNCTION: ENGINE 0x10D866C0
// FUNCTION: ENGINE 0x10D86700
// FUNCTION: ENGINE 0x10D86710
// FUNCTION: ENGINE 0x10D86740
// FUNCTION: ENGINE 0x10D86750
// FUNCTION: ENGINE 0x10D86790
// FUNCTION: ENGINE 0x10D867A0
// FUNCTION: ENGINE 0x10D86D90
// FUNCTION: ENGINE 0x10D86F10
// FUNCTION: ENGINE 0x10D86F20
// FUNCTION: ENGINE 0x10D86F30
// FUNCTION: ENGINE 0x10D86F40
// FUNCTION: ENGINE 0x10D86F50
// FUNCTION: ENGINE 0x10D87450
// FUNCTION: ENGINE 0x10D893C0
// FUNCTION: ENGINE 0x10D893E0
// FUNCTION: ENGINE 0x10D893F0
// FUNCTION: ENGINE 0x10D89400
// FUNCTION: ENGINE 0x10D89410
// FUNCTION: ENGINE 0x10D89420
// FUNCTION: ENGINE 0x10D89430
// FUNCTION: ENGINE 0x10D89440
// FUNCTION: ENGINE 0x10D894D0
// FUNCTION: ENGINE 0x10D89510
// FUNCTION: ENGINE 0x10D89520
// FUNCTION: ENGINE 0x10D89530
// FUNCTION: ENGINE 0x10D89540
// FUNCTION: ENGINE 0x10D89550
// FUNCTION: ENGINE 0x10D89560
// FUNCTION: ENGINE 0x10D89570
// FUNCTION: ENGINE 0x10D89580
// FUNCTION: ENGINE 0x10D89590
// FUNCTION: ENGINE 0x10D895A0
// FUNCTION: ENGINE 0x10D895B0
// FUNCTION: ENGINE 0x10D895C0
// FUNCTION: ENGINE 0x10D895D0
// FUNCTION: ENGINE 0x10D895E0
// FUNCTION: ENGINE 0x10D895F0
// FUNCTION: ENGINE 0x10D89600
// FUNCTION: ENGINE 0x10D89610
// FUNCTION: ENGINE 0x10D89620
// FUNCTION: ENGINE 0x10D89630
// FUNCTION: ENGINE 0x10D89640
// FUNCTION: ENGINE 0x10D89650
// FUNCTION: ENGINE 0x10D89660
// FUNCTION: ENGINE 0x10D89670
// FUNCTION: ENGINE 0x10D89680
// FUNCTION: ENGINE 0x10D89690
// FUNCTION: ENGINE 0x10D896A0
// FUNCTION: ENGINE 0x10D896B0
// FUNCTION: ENGINE 0x10D896C0
// FUNCTION: ENGINE 0x10D896D0
// FUNCTION: ENGINE 0x10D896E0
// FUNCTION: ENGINE 0x10D66740
// FUNCTION: ENGINE 0x10D727C0
// FUNCTION: ENGINE 0x10D67140
// FUNCTION: ENGINE 0x10D86D20
