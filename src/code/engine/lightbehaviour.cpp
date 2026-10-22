#include "code/engine/lightbehaviour.h"
#include "code/content/arraycmetatype.h"
#include "code/content/colourmetatype.h"

namespace content
{
	static const EnumValue sLightTypeValues[] =
	{
		{ "Ambient", 1 },
		{ "Directional", 2 },
		{ "Point", 3 },
		{ "Spot", 4 },
		{ "Line", 5 },
		{ "Area", 6 },
		{ "SH_Ambient", 7 }
	};

	static const EnumValue sLightMovementValues[] =
	{
		{ "Dynamic_Mobile", 0 },
		{ "Dynamic_Immobile", 1 },
		{ "Static", 2 }
	};

	static const EnumValue sDecayShapeValues[] =
	{
		{ "None", 0 },
		{ "Spherical", 1 }
	};

	static const EnumValue sShadowTypeValues[] =
	{
		{ "Automatic", 7 },
		{ "SpotSimple", 0 },
		{ "SpotTSM", 1 },
		{ "DirectionalBBox", 2 },
		{ "DirectionalTSM", 3 },
		{ "SunlightBBox", 5 },
		{ "SunlightTSM", 6 },
		{ "DirectionalCSM", 4 }
	};

	// FUNCTION: ENGINE 0x1089B8B0
	template<> void EnumInfo<pure3d::Light::LightType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "pure3d::Light::LightType";
		*code = "p";
		*values = sLightTypeValues;
		*count = 7;
	}

	// FUNCTION: ENGINE 0x1089B8E0
	template<> void EnumInfo<engine::LightMovementType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "engine::LightMovementType";
		*code = "p";
		*values = sLightMovementValues;
		*count = 3;
	}

	// FUNCTION: ENGINE 0x1089B910
	template<> void EnumInfo<pure3d::DecayRange::DecayShape>::Get(const char** name, const EnumValue** values,
		int* count, const char** code)
	{
		*name = "pure3d::DecayRange::DecayShape";
		*code = "p";
		*values = sDecayShapeValues;
		*count = 2;
	}

	// FUNCTION: ENGINE 0x1089B940
	template<> void EnumInfo<engine::LightShadowType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "pure3d::Shadow::ShadowType";
		*code = "p";
		*values = sShadowTypeValues;
		*count = 8;
	}
}

namespace engine
{
#define ENGINE_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	typedef container::ArrayDynamic<core::Name<core::CaseSensitiveKey>, container::AllocatorNew> NameArray;

	// FUNCTION: ENGINE 0x1089B9B0
	content::ClassInfo* EnableLightMessage::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::EnableLightMessage";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1089B9F0
	content::ClassInfo* ChangeLightColourMessage::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::ChangeLightColourMessage";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1089DBA0
	content::MemberList* EnableLightMessage::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<IntrusiveMessage>();
		static content::BaseClassCasterImpl<IntrusiveMessage, EnableLightMessage> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<EnableLightMessage, bool, 0>("p"),
				ENGINE_OFFSET(EnableLightMessage, on), "on" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1089DC50
	content::MemberList* ChangeLightColourMessage::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<IntrusiveMessage>();
		static content::BaseClassCasterImpl<IntrusiveMessage, ChangeLightColourMessage> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberColourMetaType<ChangeLightColourMessage, 0>("p"),
				ENGINE_OFFSET(ChangeLightColourMessage, colour), "colour" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1089B970
	content::ClassInfo* LightBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::LightBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1089E7A0
	content::MemberList* LightBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, LightBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<pure3d::Light::LightType>(),
				0x60, "type" },
			{ content::GetEnumMetaType<LightMovementType>(),
				0x64, "movement" },
			{ content::GetMemberColourMetaType<LightBehaviour, 2>("p"),
				ENGINE_OFFSET(LightBehaviour, colour), "colour" },
			{ content::GetMemberColourMetaType<LightBehaviour, 3>("p"),
				ENGINE_OFFSET(LightBehaviour, sphericalHarmonicColour[0]), "sphericalHarmonicColour0" },
			{ content::GetMemberColourMetaType<LightBehaviour, 4>("p"),
				ENGINE_OFFSET(LightBehaviour, sphericalHarmonicColour[1]), "sphericalHarmonicColour1" },
			{ content::GetMemberColourMetaType<LightBehaviour, 5>("p"),
				ENGINE_OFFSET(LightBehaviour, sphericalHarmonicColour[2]), "sphericalHarmonicColour2" },
			{ content::GetMemberColourMetaType<LightBehaviour, 6>("p"),
				ENGINE_OFFSET(LightBehaviour, sphericalHarmonicColour[3]), "sphericalHarmonicColour3" },
			{ content::GetMemberColourMetaType<LightBehaviour, 7>("p"),
				ENGINE_OFFSET(LightBehaviour, sphericalHarmonicColour[4]), "sphericalHarmonicColour4" },
			{ content::GetMemberColourMetaType<LightBehaviour, 8>("p"),
				ENGINE_OFFSET(LightBehaviour, sphericalHarmonicColour[5]), "sphericalHarmonicColour5" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 9>("p"),
				ENGINE_OFFSET(LightBehaviour, intensity), "intensity" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 10>("p"),
				ENGINE_OFFSET(LightBehaviour, ambientContribution), "ambientContribution" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 11>("p"),
				ENGINE_OFFSET(LightBehaviour, umbra), "umbra" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 12>("p"),
				ENGINE_OFFSET(LightBehaviour, penumbra), "penumbra" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, bool, 13>("p"),
				ENGINE_OFFSET(LightBehaviour, castShadow), "castShadow" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, int, 14>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowResolution), "shadowResolution" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 15>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowSoftness), "shadowSoftness" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 16>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowOffset), "shadowOffset" },
			{ content::GetEnumMetaType<pure3d::DecayRange::DecayShape>(),
				0xfc, "decayShape" },
			{ content::GetEnumMetaType<LightShadowType>(),
				0xe8, "shadowType" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 19>("p"),
				ENGINE_OFFSET(LightBehaviour, decayInner), "decayInner" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 20>("p"),
				ENGINE_OFFSET(LightBehaviour, decayOuter), "decayOuter" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 21>("p"),
				ENGINE_OFFSET(LightBehaviour, attenConstant), "attenConstant" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 22>("p"),
				ENGINE_OFFSET(LightBehaviour, attenLinear), "attenLinear" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 23>("p"),
				ENGINE_OFFSET(LightBehaviour, attenQuadratic), "attenQuadratic" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, bool, 24>("p"),
				ENGINE_OFFSET(LightBehaviour, isDynamic), "isDynamic" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, bool, 25>("p"),
				ENGINE_OFFSET(LightBehaviour, isCheap), "isCheap" },
			{ content::GetMatrixMetaType<LightBehaviour>(false, false, "p"),
				ENGINE_OFFSET(LightBehaviour, offsetTransform), "offsetTransform" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 27>("p"),
				ENGINE_OFFSET(LightBehaviour, length), "length" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 28>("p"),
				ENGINE_OFFSET(LightBehaviour, width), "width" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 29>("p"),
				ENGINE_OFFSET(LightBehaviour, height), "height" },
			{ content::GetArrayCMetaType<LightBehaviour, container::ArrayC<float, 27> >(27, 4,
					content::GetMemberPrimitiveMetaType<LightBehaviour, float, 30>("p"), "p"),
				ENGINE_OFFSET(LightBehaviour, sphericalHarmonicValues), "sphericalHarmonicValues" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, bool, 31>("p"),
				ENGINE_OFFSET(LightBehaviour, useSphericalHarmonicValues), "useSphericalHarmonicValues" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 32>("p"),
				ENGINE_OFFSET(LightBehaviour, scale), "scale" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, bool, 33>("p"),
				ENGINE_OFFSET(LightBehaviour, renderingEnabled), "renderingEnabled" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, bool, 34>("p"),
				ENGINE_OFFSET(LightBehaviour, emitSpecular), "emitSpecular" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, unsigned int, 35>("p"),
				ENGINE_OFFSET(LightBehaviour, affectsFlags), "affectsFlags" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 36>("p"),
				ENGINE_OFFSET(LightBehaviour, eulerAngleX), "eulerAngleX" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 37>("p"),
				ENGINE_OFFSET(LightBehaviour, eulerAngleY), "eulerAngleY" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 38>("p"),
				ENGINE_OFFSET(LightBehaviour, eulerAngleZ), "eulerAngleZ" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, unsigned int, 39>("p"),
				ENGINE_OFFSET(LightBehaviour, numShadowCascades), "numShadowCascades" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 40>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtent[0]), "shadowCascadeExtent1" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 41>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtent[1]), "shadowCascadeExtent2" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 42>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtent[2]), "shadowCascadeExtent3" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 43>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtent[3]), "shadowCascadeExtent4" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 44>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtent[4]), "shadowCascadeExtent5" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, unsigned int, 45>("p"),
				ENGINE_OFFSET(LightBehaviour, numShadowCascadesPS3), "numShadowCascadesPS3" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 46>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtentPS3[0]), "shadowCascadeExtentPS3_1" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 47>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtentPS3[1]), "shadowCascadeExtentPS3_2" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 48>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtentPS3[2]), "shadowCascadeExtentPS3_3" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 49>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtentPS3[3]), "shadowCascadeExtentPS3_4" },
			{ content::GetMemberPrimitiveMetaType<LightBehaviour, float, 50>("p"),
				ENGINE_OFFSET(LightBehaviour, shadowCascadeExtentPS3[4]), "shadowCascadeExtentPS3_5" },
			{ content::GetArrayDynamicMetaType<LightBehaviour, NameArray>(
					content::GetNameMetaType<LightBehaviour>(true, true, "p"), "p"),
				ENGINE_OFFSET(LightBehaviour, lightGroups), "lightGroups" }
		};
		sList.members = sMembers;
		sList.count = 52;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1089BE00
// FUNCTION: ENGINE 0x1089BE20
// FUNCTION: ENGINE 0x1089BE80
// FUNCTION: ENGINE 0x1089BEE0
// FUNCTION: ENGINE 0x1089BFA0
// FUNCTION: ENGINE 0x1089BFD0
// FUNCTION: ENGINE 0x1089C000
// FUNCTION: ENGINE 0x1089C030
// FUNCTION: ENGINE 0x1089C060
// FUNCTION: ENGINE 0x1089C090
// FUNCTION: ENGINE 0x1089C0C0
// FUNCTION: ENGINE 0x1089C0F0
// FUNCTION: ENGINE 0x1089C130
// FUNCTION: ENGINE 0x1089C140
// FUNCTION: ENGINE 0x1089C180
// FUNCTION: ENGINE 0x1089C440
// FUNCTION: ENGINE 0x1089C450
// FUNCTION: ENGINE 0x1089C480
// FUNCTION: ENGINE 0x1089C490
// FUNCTION: ENGINE 0x1089C4C0
// FUNCTION: ENGINE 0x1089C4D0
// FUNCTION: ENGINE 0x1089D0C0
// FUNCTION: ENGINE 0x1089D100
// FUNCTION: ENGINE 0x1089D140
// FUNCTION: ENGINE 0x1089D180
// FUNCTION: ENGINE 0x1089D1C0
// FUNCTION: ENGINE 0x1089D200
// FUNCTION: ENGINE 0x1089D240
// FUNCTION: ENGINE 0x1089D280
// FUNCTION: ENGINE 0x1089D2C0
// FUNCTION: ENGINE 0x1089D300
// FUNCTION: ENGINE 0x1089D340
// FUNCTION: ENGINE 0x1089D380
// FUNCTION: ENGINE 0x1089D3C0
// FUNCTION: ENGINE 0x1089D400
// FUNCTION: ENGINE 0x1089D440
// FUNCTION: ENGINE 0x1089D480
// FUNCTION: ENGINE 0x1089D4C0
// FUNCTION: ENGINE 0x1089D500
// FUNCTION: ENGINE 0x1089D540
// FUNCTION: ENGINE 0x1089D580
// FUNCTION: ENGINE 0x1089D5C0
// FUNCTION: ENGINE 0x1089D600
// FUNCTION: ENGINE 0x1089D640
// FUNCTION: ENGINE 0x1089D680
// FUNCTION: ENGINE 0x1089D6C0
// FUNCTION: ENGINE 0x1089D700
// FUNCTION: ENGINE 0x1089D740
// FUNCTION: ENGINE 0x1089D780
// FUNCTION: ENGINE 0x1089D7C0
// FUNCTION: ENGINE 0x1089D800
// FUNCTION: ENGINE 0x1089D840
// FUNCTION: ENGINE 0x1089D880
// FUNCTION: ENGINE 0x1089D8C0
// FUNCTION: ENGINE 0x1089D900
// FUNCTION: ENGINE 0x1089D940
// FUNCTION: ENGINE 0x1089D980
// FUNCTION: ENGINE 0x1089D9C0
// FUNCTION: ENGINE 0x1089DA00
// FUNCTION: ENGINE 0x1089DA40
// FUNCTION: ENGINE 0x1089DA80
// FUNCTION: ENGINE 0x1089DB00
// FUNCTION: ENGINE 0x1089DB10
// FUNCTION: ENGINE 0x1089DB20
// FUNCTION: ENGINE 0x1089E6C0
// FUNCTION: ENGINE 0x1089E710
