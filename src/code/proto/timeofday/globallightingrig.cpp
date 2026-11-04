#include "code/proto/timeofday/globallightingrig.h"
#include "code/content/colourmetatype.h"
#include "code/content/vectormetatype.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1053D870
	content::ClassInfo* GlobalLightingRig::SkyParameters::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalLightingRig::SkyParameters";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1053D8B0
	template<> content::ClassInfo* TimeOfDayVarChannel<GlobalLightingRig::SkyParameters>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<proto::GlobalLightingRig::SkyParameters>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1053D8F0
	template<> content::ClassInfo* TimeOfDayVarChannel<GlobalLightingRig::SkyParameters>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<proto::GlobalLightingRig::SkyParameters>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10541040
	content::MemberList* GlobalLightingRig::SkyParameters::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberColourMetaType<GlobalLightingRig::SkyParameters, 0>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, sunColour), "sunColour" },
			{ content::GetMemberColourMetaType<GlobalLightingRig::SkyParameters, 1>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, skyColour), "skyColour" },
			{ content::GetMemberColourMetaType<GlobalLightingRig::SkyParameters, 2>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, fogColour), "fogColour" },
			{ content::GetMemberColourMetaType<GlobalLightingRig::SkyParameters, 3>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, decayColour), "decayColour" },
			{ content::GetMemberColourMetaType<GlobalLightingRig::SkyParameters, 4>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, horizonColour), "horizonColour" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::SkyParameters, float, 0>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, sunSize), "sunSize" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::SkyParameters, float, 1>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, sunStrength), "sunStrength" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::SkyParameters, float, 2>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, glowSize), "glowSize" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::SkyParameters, float, 3>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, glowStrength), "glowStrength" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::SkyParameters, float, 4>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, fogDensity), "fogDensity" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::SkyParameters, float, 5>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, fogMaxDensity), "fogMaxDensity" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::SkyParameters, float, 6>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, skyHalfHeight), "skyHalfHeight" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::SkyParameters, float, 7>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, decayDensity), "decayDensity" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::SkyParameters, float, 8>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, decayHalfHeight), "decayHalfHeight" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::SkyParameters, float, 9>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, fogHalfHeight), "fogHalfHeight" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::SkyParameters, float, 10>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, horizonSize), "horizonSize" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::SkyParameters, float, 11>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, starStrength), "starStrength" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::SkyParameters, float, 12>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, scatterDensity), "scatterDensity" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::SkyParameters, float, 13>("p"),
				PROTO_OFFSET(GlobalLightingRig::SkyParameters, scatterDistance), "scatterDistance" }
		};
		sList.members = sMembers;
		sList.count = 19;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10542CE0
	template<> content::MemberList* TimeOfDayVarChannel<GlobalLightingRig::SkyParameters>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetClassMetaType<GlobalLightingRig::SkyParameters>(), PROTO_OFFSET(Key, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x105453E0
	template<> content::MemberList* TimeOfDayVarChannel<GlobalLightingRig::SkyParameters>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<TimeOfDayVarChannel<GlobalLightingRig::SkyParameters>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(TimeOfDayVarChannel<GlobalLightingRig::SkyParameters>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1053D930
	content::ClassInfo* GlobalLightingRig::GlobalLightParameters::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalLightingRig::GlobalLightParameters";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1053D970
	template<> content::ClassInfo* TimeOfDayVarChannel<GlobalLightingRig::GlobalLightParameters>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<proto::GlobalLightingRig::GlobalLightParameters>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1053D9B0
	template<> content::ClassInfo* TimeOfDayVarChannel<GlobalLightingRig::GlobalLightParameters>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<proto::GlobalLightingRig::GlobalLightParameters>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10541470
	content::MemberList* GlobalLightingRig::GlobalLightParameters::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberColourMetaType<GlobalLightingRig::GlobalLightParameters, 0>("p"),
				PROTO_OFFSET(GlobalLightingRig::GlobalLightParameters, hemiLightUpper), "hemiLightUpper" },
			{ content::GetMemberColourMetaType<GlobalLightingRig::GlobalLightParameters, 1>("p"),
				PROTO_OFFSET(GlobalLightingRig::GlobalLightParameters, hemiLightLower), "hemiLightLower" },
			{ content::GetMemberColourMetaType<GlobalLightingRig::GlobalLightParameters, 2>("p"),
				PROTO_OFFSET(GlobalLightingRig::GlobalLightParameters, clearColour), "clearColour" },
			{ content::GetMemberColourMetaType<GlobalLightingRig::GlobalLightParameters, 3>("p"),
				PROTO_OFFSET(GlobalLightingRig::GlobalLightParameters, midgroundColour), "midgroundColour" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::GlobalLightParameters, float, 0>("p"),
				PROTO_OFFSET(GlobalLightingRig::GlobalLightParameters, desatStartDist), "desatStartDist" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::GlobalLightParameters, float, 1>("p"),
				PROTO_OFFSET(GlobalLightingRig::GlobalLightParameters, desatRange), "desatRange" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::GlobalLightParameters, float, 2>("p"),
				PROTO_OFFSET(GlobalLightingRig::GlobalLightParameters, desatMin), "desatMin" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::GlobalLightParameters, float, 3>("p"),
				PROTO_OFFSET(GlobalLightingRig::GlobalLightParameters, nearYScale), "nearYScale" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::GlobalLightParameters, float, 4>("p"),
				PROTO_OFFSET(GlobalLightingRig::GlobalLightParameters, farYScale), "farYScale" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::GlobalLightParameters, float, 5>("p"),
				PROTO_OFFSET(GlobalLightingRig::GlobalLightParameters, camDistBias), "camDistBias" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::GlobalLightParameters, float, 6>("p"),
				PROTO_OFFSET(GlobalLightingRig::GlobalLightParameters, yFalloff), "yFalloff" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::GlobalLightParameters, float, 7>("p"),
				PROTO_OFFSET(GlobalLightingRig::GlobalLightParameters, streetLevel), "streetLevel" }
		};
		sList.members = sMembers;
		sList.count = 12;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10542DB0
	template<> content::MemberList* TimeOfDayVarChannel<GlobalLightingRig::GlobalLightParameters>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetClassMetaType<GlobalLightingRig::GlobalLightParameters>(), PROTO_OFFSET(Key, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10545490
	template<> content::MemberList* TimeOfDayVarChannel<GlobalLightingRig::GlobalLightParameters>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<TimeOfDayVarChannel<GlobalLightingRig::GlobalLightParameters>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(TimeOfDayVarChannel<GlobalLightingRig::GlobalLightParameters>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1053D9F0
	content::ClassInfo* GlobalLightingRig::CloudParameters::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalLightingRig::CloudParameters";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1053DA30
	template<> content::ClassInfo* TimeOfDayVarChannel<GlobalLightingRig::CloudParameters>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<proto::GlobalLightingRig::CloudParameters>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1053DA70
	template<> content::ClassInfo* TimeOfDayVarChannel<GlobalLightingRig::CloudParameters>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<proto::GlobalLightingRig::CloudParameters>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10541730
	content::MemberList* GlobalLightingRig::CloudParameters::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberColourMetaType<GlobalLightingRig::CloudParameters, 0>("p"),
				PROTO_OFFSET(GlobalLightingRig::CloudParameters, lowScaleDir), "lowScaleDir" },
			{ content::GetMemberColourMetaType<GlobalLightingRig::CloudParameters, 1>("p"),
				PROTO_OFFSET(GlobalLightingRig::CloudParameters, highScaleDir), "highScaleDir" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::CloudParameters, float, 0>("p"),
				PROTO_OFFSET(GlobalLightingRig::CloudParameters, lowOpacity), "lowOpacity" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::CloudParameters, float, 1>("p"),
				PROTO_OFFSET(GlobalLightingRig::CloudParameters, highOpacity), "highOpacity" },
			{ content::GetMemberColourMetaType<GlobalLightingRig::CloudParameters, 2>("p"),
				PROTO_OFFSET(GlobalLightingRig::CloudParameters, lowColour), "lowColour" },
			{ content::GetMemberColourMetaType<GlobalLightingRig::CloudParameters, 3>("p"),
				PROTO_OFFSET(GlobalLightingRig::CloudParameters, highColour), "highColour" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::CloudParameters, float, 2>("p"),
				PROTO_OFFSET(GlobalLightingRig::CloudParameters, softness), "softness" },
			{ content::GetMemberColourMetaType<GlobalLightingRig::CloudParameters, 4>("p"),
				PROTO_OFFSET(GlobalLightingRig::CloudParameters, sunColour), "sunColour" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::CloudParameters, float, 3>("p"),
				PROTO_OFFSET(GlobalLightingRig::CloudParameters, sunLightRadius), "sunLightRadius" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::CloudParameters, float, 4>("p"),
				PROTO_OFFSET(GlobalLightingRig::CloudParameters, terrainScale), "terrainScale" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::CloudParameters, float, 5>("p"),
				PROTO_OFFSET(GlobalLightingRig::CloudParameters, terrainDarkness), "terrainDarkness" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::CloudParameters, float, 6>("p"),
				PROTO_OFFSET(GlobalLightingRig::CloudParameters, terrainOpacity), "terrainOpacity" }
		};
		sList.members = sMembers;
		sList.count = 12;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10542E80
	template<> content::MemberList* TimeOfDayVarChannel<GlobalLightingRig::CloudParameters>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetClassMetaType<GlobalLightingRig::CloudParameters>(), PROTO_OFFSET(Key, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10545540
	template<> content::MemberList* TimeOfDayVarChannel<GlobalLightingRig::CloudParameters>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<TimeOfDayVarChannel<GlobalLightingRig::CloudParameters>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(TimeOfDayVarChannel<GlobalLightingRig::CloudParameters>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1053DAB0
	content::ClassInfo* GlobalLightingRig::Light::LightData::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalLightingRig::Light::LightData";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1053DAF0
	template<> content::ClassInfo* TimeOfDayVarChannel<GlobalLightingRig::Light::LightData>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<proto::GlobalLightingRig::Light::LightData>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1053DB30
	template<> content::ClassInfo* TimeOfDayVarChannel<GlobalLightingRig::Light::LightData>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<proto::GlobalLightingRig::Light::LightData>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x105419F0
	content::MemberList* GlobalLightingRig::Light::LightData::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberColourMetaType<GlobalLightingRig::Light::LightData, 0>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, colour), "colour" },
			{ content::GetMemberVectorMetaType<GlobalLightingRig::Light::LightData, 0>("p"),
				(int)&(((GlobalLightingRig::Light::LightData*)0)->euler), "euler" },
			{ content::GetMemberVectorMetaType<GlobalLightingRig::Light::LightData, 1>("p"),
				(int)&(((GlobalLightingRig::Light::LightData*)0)->position), "position" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 0>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, propIntensity), "propIntensity" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 1>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, specIntensity), "specIntensity" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 2>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, shadowIntensity), "shadowIntensity" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 3>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, innerDecay), "innerDecay" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 4>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, outerDecay), "outerDecay" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 5>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, ambientShade), "ambientShade" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 6>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, umbra), "umbra" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 7>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, penumbra), "penumbra" },
			{ content::GetEnumMetaType<engine::LightShadowType>(),
				(int)&(((GlobalLightingRig::Light::LightData*)0)->shadowType), "shadowType" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 8>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, shadowOffset), "shadowOffset" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, unsigned int, 0>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, numShadowCascades), "numShadowCascades" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 9>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, shadowCascadeExtent1), "shadowCascadeExtent1" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 10>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, shadowCascadeExtent2), "shadowCascadeExtent2" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 11>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, shadowCascadeExtent3), "shadowCascadeExtent3" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 12>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, shadowCascadeExtent4), "shadowCascadeExtent4" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 13>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, shadowCascadeExtent5), "shadowCascadeExtent5" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, unsigned int, 1>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, numShadowCascadesPS3), "numShadowCascadesPS3" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 14>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, shadowCascadeExtentPS3_1), "shadowCascadeExtentPS3_1" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 15>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, shadowCascadeExtentPS3_2), "shadowCascadeExtentPS3_2" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 16>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, shadowCascadeExtentPS3_3), "shadowCascadeExtentPS3_3" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 17>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, shadowCascadeExtentPS3_4), "shadowCascadeExtentPS3_4" },
			{ content::GetMemberPrimitiveMetaType<GlobalLightingRig::Light::LightData, float, 18>("p"),
				PROTO_OFFSET(GlobalLightingRig::Light::LightData, shadowCascadeExtentPS3_5), "shadowCascadeExtentPS3_5" }
		};
		sList.members = sMembers;
		sList.count = 25;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10542F50
	template<> content::MemberList* TimeOfDayVarChannel<GlobalLightingRig::Light::LightData>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetClassMetaType<GlobalLightingRig::Light::LightData>(), PROTO_OFFSET(Key, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x105455F0
	template<> content::MemberList* TimeOfDayVarChannel<GlobalLightingRig::Light::LightData>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<TimeOfDayVarChannel<GlobalLightingRig::Light::LightData>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(TimeOfDayVarChannel<GlobalLightingRig::Light::LightData>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1053DB70
	content::ClassInfo* GlobalLightingRig::Light::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalLightingRig::Light";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1054ADF0
	content::MemberList* GlobalLightingRig::Light::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<Light>(true, true, "p"), PROTO_NAME_OFFSET(Light, name), "name" },
			{ content::GetMemberPrimitiveMetaType<Light, bool, 0>("p"), PROTO_OFFSET(Light, shadowEnabled), "shadowEnabled" },
			{ content::GetClassMetaType<TimeOfDayVarChannel<LightData> >(), PROTO_OFFSET(Light, lightKeys), "lightKeys" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1053DBB0
	content::ClassInfo* GlobalLightingRig::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalLightingRig";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1054B2B0
	content::MemberList* GlobalLightingRig::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<GlobalLightingRig, container::ArrayDynamic<Light, container::AllocatorNew> >(
				content::GetClassMetaType<Light>(), "p"), PROTO_OFFSET(GlobalLightingRig, lights), "lights" },
			{ content::GetClassMetaType<TimeOfDayVarChannel<SkyParameters> >(), PROTO_OFFSET(GlobalLightingRig, skyKeys), "skyKeys" },
			{ content::GetClassMetaType<TimeOfDayVarChannel<GlobalLightParameters> >(), PROTO_OFFSET(GlobalLightingRig, globalKeys), "globalKeys" },
			{ content::GetClassMetaType<TimeOfDayVarChannel<CloudParameters> >(), PROTO_OFFSET(GlobalLightingRig, cloudKeys), "cloudKeys" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	template class TimeOfDayVarChannel<GlobalLightingRig::SkyParameters>;
	template class TimeOfDayVarChannel<GlobalLightingRig::GlobalLightParameters>;
	template class TimeOfDayVarChannel<GlobalLightingRig::CloudParameters>;
	template class TimeOfDayVarChannel<GlobalLightingRig::Light::LightData>;
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1053DCB0
// FUNCTION: ENGINE 0x1053DD90
// FUNCTION: ENGINE 0x1053DDE0
// FUNCTION: ENGINE 0x1053DE40
// FUNCTION: ENGINE 0x1053DF00
// FUNCTION: ENGINE 0x1053DFD0
// FUNCTION: ENGINE 0x1053E090
// FUNCTION: ENGINE 0x1053E100
// FUNCTION: ENGINE 0x1053E140
// FUNCTION: ENGINE 0x1053E180
// FUNCTION: ENGINE 0x1053E1C0
// FUNCTION: ENGINE 0x1053E200
// FUNCTION: ENGINE 0x1053E240
// FUNCTION: ENGINE 0x1053E250
// FUNCTION: ENGINE 0x1053E260
// FUNCTION: ENGINE 0x1053E2A0
// FUNCTION: ENGINE 0x1053E2E0
// FUNCTION: ENGINE 0x1053E320
// FUNCTION: ENGINE 0x1053E360
// FUNCTION: ENGINE 0x1053E370
// FUNCTION: ENGINE 0x1053E380
// FUNCTION: ENGINE 0x1053E3C0
// FUNCTION: ENGINE 0x1053E400
// FUNCTION: ENGINE 0x1053E440
// FUNCTION: ENGINE 0x1053E480
// FUNCTION: ENGINE 0x1053E4C0
// FUNCTION: ENGINE 0x1053E4D0
// FUNCTION: ENGINE 0x1053E4E0
// FUNCTION: ENGINE 0x1053E520
// FUNCTION: ENGINE 0x1053E560
// FUNCTION: ENGINE 0x1053E5B0
// FUNCTION: ENGINE 0x1053E5C0
// FUNCTION: ENGINE 0x1053E5D0
// FUNCTION: ENGINE 0x1053E610
// FUNCTION: ENGINE 0x1053E620
// FUNCTION: ENGINE 0x1053E630
// FUNCTION: ENGINE 0x1053E640
// FUNCTION: ENGINE 0x1053E650
// FUNCTION: ENGINE 0x1053E660
// FUNCTION: ENGINE 0x1053E6C0
// FUNCTION: ENGINE 0x1053E730
// FUNCTION: ENGINE 0x1053E7B0
// FUNCTION: ENGINE 0x1053E800
// FUNCTION: ENGINE 0x1053EE50
// FUNCTION: ENGINE 0x1053EE90
// FUNCTION: ENGINE 0x1053EED0
// FUNCTION: ENGINE 0x1053F2E0
// FUNCTION: ENGINE 0x1053F320
// FUNCTION: ENGINE 0x1053F360
// FUNCTION: ENGINE 0x1053F3A0
// FUNCTION: ENGINE 0x1053F3E0
// FUNCTION: ENGINE 0x1053F420
// FUNCTION: ENGINE 0x1053F460
// FUNCTION: ENGINE 0x1053F4A0
// FUNCTION: ENGINE 0x1053F4E0
// FUNCTION: ENGINE 0x1053F520
// FUNCTION: ENGINE 0x1053F560
// FUNCTION: ENGINE 0x1053F5A0
// FUNCTION: ENGINE 0x1053F5E0
// FUNCTION: ENGINE 0x1053F620
// FUNCTION: ENGINE 0x1053F660
// FUNCTION: ENGINE 0x1053F6A0
// FUNCTION: ENGINE 0x1053F6E0
// FUNCTION: ENGINE 0x1053F720
// FUNCTION: ENGINE 0x1053F760
// FUNCTION: ENGINE 0x1053F7A0
// FUNCTION: ENGINE 0x1053F7E0
// FUNCTION: ENGINE 0x1053F820
// FUNCTION: ENGINE 0x1053F860
// FUNCTION: ENGINE 0x1053F8A0
// FUNCTION: ENGINE 0x1053F8E0
// FUNCTION: ENGINE 0x1053F920
// FUNCTION: ENGINE 0x1053F960
// FUNCTION: ENGINE 0x1053F9A0
// FUNCTION: ENGINE 0x1053F9E0
// FUNCTION: ENGINE 0x1053FA20
// FUNCTION: ENGINE 0x1053FA60
// FUNCTION: ENGINE 0x1053FAA0
// FUNCTION: ENGINE 0x1053FAE0
// FUNCTION: ENGINE 0x1053FB20
// FUNCTION: ENGINE 0x1053FB60
// FUNCTION: ENGINE 0x1053FBA0
// FUNCTION: ENGINE 0x1053FBE0
// FUNCTION: ENGINE 0x1053FC20
// FUNCTION: ENGINE 0x1053FC60
// FUNCTION: ENGINE 0x1053FCA0
// FUNCTION: ENGINE 0x1053FCE0
// FUNCTION: ENGINE 0x1053FD20
// FUNCTION: ENGINE 0x1053FD60
// FUNCTION: ENGINE 0x1053FDA0
// FUNCTION: ENGINE 0x1053FDE0
// FUNCTION: ENGINE 0x1053FE20
// FUNCTION: ENGINE 0x1053FE60
// FUNCTION: ENGINE 0x1053FEA0
// FUNCTION: ENGINE 0x1053FEE0
// FUNCTION: ENGINE 0x1053FF20
// FUNCTION: ENGINE 0x1053FF60
// FUNCTION: ENGINE 0x1053FFA0
// FUNCTION: ENGINE 0x1053FFE0
// FUNCTION: ENGINE 0x10540020
// FUNCTION: ENGINE 0x10540060
// FUNCTION: ENGINE 0x105400E0
// FUNCTION: ENGINE 0x10540110
// FUNCTION: ENGINE 0x10540140
// FUNCTION: ENGINE 0x10540160
// FUNCTION: ENGINE 0x10540180
// FUNCTION: ENGINE 0x105401B0
// FUNCTION: ENGINE 0x10540210
// FUNCTION: ENGINE 0x10540240
// FUNCTION: ENGINE 0x10540270
// FUNCTION: ENGINE 0x10540290
// FUNCTION: ENGINE 0x105402B0
// FUNCTION: ENGINE 0x105402E0
// FUNCTION: ENGINE 0x10540340
// FUNCTION: ENGINE 0x10540370
// FUNCTION: ENGINE 0x105403A0
// FUNCTION: ENGINE 0x105403C0
// FUNCTION: ENGINE 0x105403E0
// FUNCTION: ENGINE 0x10540410
// FUNCTION: ENGINE 0x10540470
// FUNCTION: ENGINE 0x105404A0
// FUNCTION: ENGINE 0x105404D0
// FUNCTION: ENGINE 0x105404F0
// FUNCTION: ENGINE 0x10540510
// FUNCTION: ENGINE 0x10540540
// FUNCTION: ENGINE 0x10540550
// FUNCTION: ENGINE 0x10540570
// FUNCTION: ENGINE 0x10540590
// FUNCTION: ENGINE 0x105405B0
// FUNCTION: ENGINE 0x105405D0
// FUNCTION: ENGINE 0x10540AA0
// EQUIVALENT: scheduling and inlining; the same loads, stores, copies and calls of the key operations, in the order and with the helpers the engine's compile chose (19.1 %)
// FUNCTION: ENGINE 0x10540AC0
// EQUIVALENT: scheduling and inlining; the same loads, stores, copies and calls of the key operations, in the order and with the helpers the engine's compile chose (20.5 %)
// FUNCTION: ENGINE 0x10540AE0
// EQUIVALENT: scheduling and inlining; the same loads, stores, copies and calls of the key operations, in the order and with the helpers the engine's compile chose (20.5 %)
// FUNCTION: ENGINE 0x10541F60
// FUNCTION: ENGINE 0x10541FC0
// FUNCTION: ENGINE 0x10542020
// FUNCTION: ENGINE 0x10542080
// FUNCTION: ENGINE 0x10542720
// FUNCTION: ENGINE 0x10542780
// FUNCTION: ENGINE 0x105427E0
// FUNCTION: ENGINE 0x10542840
// FUNCTION: ENGINE 0x105428A0
// FUNCTION: ENGINE 0x10542900
// FUNCTION: ENGINE 0x10542940
// FUNCTION: ENGINE 0x10542A40
// FUNCTION: ENGINE 0x10542C40
// FUNCTION: ENGINE 0x10542C90
// FUNCTION: ENGINE 0x10544230
// FUNCTION: ENGINE 0x10544290
// FUNCTION: ENGINE 0x105442F0
// FUNCTION: ENGINE 0x10544350
// FUNCTION: ENGINE 0x10544430
// FUNCTION: ENGINE 0x10544590
// FUNCTION: ENGINE 0x10545010
// FUNCTION: ENGINE 0x10545090
// FUNCTION: ENGINE 0x10545140
// FUNCTION: ENGINE 0x105451F0
// FUNCTION: ENGINE 0x10545260
// FUNCTION: ENGINE 0x105452C0
// FUNCTION: ENGINE 0x10545320
// FUNCTION: ENGINE 0x10545380
// FUNCTION: ENGINE 0x105456A0
// FUNCTION: ENGINE 0x105456C0
// FUNCTION: ENGINE 0x10545870
// FUNCTION: ENGINE 0x105458F0
// EQUIVALENT: scheduling and inlining; the same loads, stores, copies and calls of the key operations, in the order and with the helpers the engine's compile chose (70.2 %)
// FUNCTION: ENGINE 0x10545DB0
// FUNCTION: ENGINE 0x10545DD0
// FUNCTION: ENGINE 0x10545DE0
// FUNCTION: ENGINE 0x10545FE0
// FUNCTION: ENGINE 0x10546020
// FUNCTION: ENGINE 0x10546070
// FUNCTION: ENGINE 0x10546140
// FUNCTION: ENGINE 0x10546180
// FUNCTION: ENGINE 0x10546510
// FUNCTION: ENGINE 0x10546580
// FUNCTION: ENGINE 0x105465B0
// FUNCTION: ENGINE 0x105465D0
// FUNCTION: ENGINE 0x10546650
// FUNCTION: ENGINE 0x10546700
// FUNCTION: ENGINE 0x10546740
// FUNCTION: ENGINE 0x105467D0
// FUNCTION: ENGINE 0x10546880
// FUNCTION: ENGINE 0x10546B20
// FUNCTION: ENGINE 0x10546C10
// FUNCTION: ENGINE 0x10546C90
// FUNCTION: ENGINE 0x10546D10
// FUNCTION: ENGINE 0x10546D30
// EQUIVALENT: scheduling and inlining; the same loads, stores, copies and calls of the key operations, in the order and with the helpers the engine's compile chose (15.9 %)
// FUNCTION: ENGINE 0x10546DE0
// FUNCTION: ENGINE 0x10546DF0
// FUNCTION: ENGINE 0x10546F70
// FUNCTION: ENGINE 0x10547080
// FUNCTION: ENGINE 0x105470C0
// FUNCTION: ENGINE 0x10547110
// FUNCTION: ENGINE 0x10547150
// FUNCTION: ENGINE 0x105471A0
// FUNCTION: ENGINE 0x10547270
// FUNCTION: ENGINE 0x10547360
// FUNCTION: ENGINE 0x105473E0
// FUNCTION: ENGINE 0x10547410
// FUNCTION: ENGINE 0x10547430
// FUNCTION: ENGINE 0x105474B0
// FUNCTION: ENGINE 0x10547550
// FUNCTION: ENGINE 0x10547590
// FUNCTION: ENGINE 0x105476B0
// FUNCTION: ENGINE 0x105478A0
// FUNCTION: ENGINE 0x10547970
// FUNCTION: ENGINE 0x105479E0
// FUNCTION: ENGINE 0x10547A50
// FUNCTION: ENGINE 0x10547A70
// EQUIVALENT: scheduling and inlining; the same loads, stores, copies and calls of the key operations, in the order and with the helpers the engine's compile chose (38.6 %)
// FUNCTION: ENGINE 0x10547B10
// FUNCTION: ENGINE 0x10547B20
// FUNCTION: ENGINE 0x10547BE0
// FUNCTION: ENGINE 0x10547C60
// FUNCTION: ENGINE 0x10547D60
// FUNCTION: ENGINE 0x10547DA0
// FUNCTION: ENGINE 0x10547E40
// FUNCTION: ENGINE 0x10547E80
// FUNCTION: ENGINE 0x10547ED0
// FUNCTION: ENGINE 0x10547FA0
// FUNCTION: ENGINE 0x10548080
// FUNCTION: ENGINE 0x105480C0
// FUNCTION: ENGINE 0x105480F0
// FUNCTION: ENGINE 0x10548110
// FUNCTION: ENGINE 0x10548190
// FUNCTION: ENGINE 0x10548230
// FUNCTION: ENGINE 0x10548270
// FUNCTION: ENGINE 0x10548300
// FUNCTION: ENGINE 0x105483A0
// FUNCTION: ENGINE 0x105485C0
// FUNCTION: ENGINE 0x10548690
// FUNCTION: ENGINE 0x10548700
// FUNCTION: ENGINE 0x10548780
// FUNCTION: ENGINE 0x105487A0
// EQUIVALENT: scheduling and inlining; the same loads, stores, copies and calls of the key operations, in the order and with the helpers the engine's compile chose (18.2 %)
// FUNCTION: ENGINE 0x10548850
// FUNCTION: ENGINE 0x10548860
// FUNCTION: ENGINE 0x10548930
// FUNCTION: ENGINE 0x105489B0
// FUNCTION: ENGINE 0x10548AB0
// FUNCTION: ENGINE 0x10548AF0
// FUNCTION: ENGINE 0x10548B40
// FUNCTION: ENGINE 0x10548B80
// FUNCTION: ENGINE 0x10548BD0
// FUNCTION: ENGINE 0x10548CA0
// FUNCTION: ENGINE 0x10548D80
// FUNCTION: ENGINE 0x10548DF0
// FUNCTION: ENGINE 0x10548E20
// FUNCTION: ENGINE 0x10548E80
// FUNCTION: ENGINE 0x10548EE0
// FUNCTION: ENGINE 0x10548F40
// FUNCTION: ENGINE 0x10548FA0
// FUNCTION: ENGINE 0x10548FF0
// FUNCTION: ENGINE 0x10549040
// FUNCTION: ENGINE 0x10549090
// FUNCTION: ENGINE 0x10549590
// FUNCTION: ENGINE 0x105495E0
// FUNCTION: ENGINE 0x10549BB0
// FUNCTION: ENGINE 0x1054A0D0
// FUNCTION: ENGINE 0x1054A0F0
// FUNCTION: ENGINE 0x1054A560
// FUNCTION: ENGINE 0x1054A580
// FUNCTION: ENGINE 0x1054A9F0
// FUNCTION: ENGINE 0x1054AB30
// FUNCTION: ENGINE 0x1054AC60
// FUNCTION: ENGINE 0x1054ACD0
// FUNCTION: ENGINE 0x1054AF90
// FUNCTION: ENGINE 0x1054AFC0
// FUNCTION: ENGINE 0x1054AFF0
// FUNCTION: ENGINE 0x1054B020
// FUNCTION: ENGINE 0x1054B050
// FUNCTION: ENGINE 0x1054B080
// FUNCTION: ENGINE 0x1054B270
// FUNCTION: ENGINE 0x1054B280
// FUNCTION: ENGINE 0x1054B290
// FUNCTION: ENGINE 0x1054B2A0
// FUNCTION: ENGINE 0x1054B3E0
// FUNCTION: ENGINE 0x1054B450
// FUNCTION: ENGINE 0x1054B530
// EQUIVALENT: scheduling and inlining; the same loads, stores, copies and calls of the key operations, in the order and with the helpers the engine's compile chose (22.9 %)
// FUNCTION: ENGINE 0x1054B5E0
// EQUIVALENT: scheduling and inlining; the same loads, stores, copies and calls of the key operations, in the order and with the helpers the engine's compile chose (72.2 %)
// FUNCTION: ENGINE 0x1054B690
// FUNCTION: ENGINE 0x1054B850
// FUNCTION: ENGINE 0x1054B9D0
// FUNCTION: ENGINE 0x1054BB50
// FUNCTION: ENGINE 0x1054BCD0
// FUNCTION: ENGINE 0x1054BFA0
// EQUIVALENT: scheduling and inlining; the same loads, stores, copies and calls of the key operations, in the order and with the helpers the engine's compile chose (61.3 %)
// FUNCTION: ENGINE 0x1054C470
// FUNCTION: ENGINE 0x1054C4F0
// FUNCTION: ENGINE 0x1054C780
// EQUIVALENT: scheduling and inlining; the same loads, stores, copies and calls of the key operations, in the order and with the helpers the engine's compile chose (68.0 %)
// FUNCTION: ENGINE 0x1054C830
// FUNCTION: ENGINE 0x1054CE60
// EQUIVALENT: scheduling and inlining; the same loads, stores, copies and calls of the key operations, in the order and with the helpers the engine's compile chose (30.9 %)
// FUNCTION: ENGINE 0x1054CFB0
// EQUIVALENT: scheduling and inlining; the same loads, stores, copies and calls of the key operations, in the order and with the helpers the engine's compile chose (99.2 %)
// FUNCTION: ENGINE 0x1054D100
// EQUIVALENT: scheduling and inlining; the same loads, stores, copies and calls of the key operations, in the order and with the helpers the engine's compile chose (23.8 %)
// FUNCTION: ENGINE 0x1054D330
// EQUIVALENT: scheduling and inlining; the same loads, stores, copies and calls of the key operations, in the order and with the helpers the engine's compile chose (22.7 %)
