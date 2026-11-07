#include "code/proto/timeofday/timeofdayvars.h"
#include "code/content/colourmetatype.h"
#include "code/content/vectormetatype.h"
#include "code/math/colour128.h"
#include "code/math/vector.h"
#include "code/math/vector2.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// The reflection of the keys of the plain value channels
	// FUNCTION: ENGINE 0x105203E0
	template<> content::MemberList* TimeOfDayVarChannel<float>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetMemberPrimitiveMetaType<Key, float, 1>("p"), PROTO_OFFSET(Key, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10520310
	template<> content::MemberList* TimeOfDayVarChannel<math::Vector>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetMemberVectorMetaType<Key, 1>("p"), 4, "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10520240
	template<> content::MemberList* TimeOfDayVarChannel<math::Colour128>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetMemberColourMetaType<Key, 1>("p"), PROTO_OFFSET(Key, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10520DC0
	template<> content::MemberList* TimeOfDayVarChannel<float>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<TimeOfDayVarChannel<float>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(TimeOfDayVarChannel<float>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10520D10
	template<> content::MemberList* TimeOfDayVarChannel<math::Vector>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<TimeOfDayVarChannel<math::Vector>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(TimeOfDayVarChannel<math::Vector>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10520C60
	template<> content::MemberList* TimeOfDayVarChannel<math::Colour128>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<TimeOfDayVarChannel<math::Colour128>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(TimeOfDayVarChannel<math::Colour128>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1051F370
	template<> content::ClassInfo* TimeOfDayVarChannel<math::Colour128>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<math::Colour>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1051F3B0
	template<> content::ClassInfo* TimeOfDayVarChannel<math::Colour128>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<math::Colour>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1051F3F0
	template<> content::ClassInfo* TimeOfDayVarChannel<math::Vector>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<math::Vector>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1051F430
	template<> content::ClassInfo* TimeOfDayVarChannel<math::Vector>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<math::Vector>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1051F470
	template<> content::ClassInfo* TimeOfDayVarChannel<float>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<float>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1051F4B0
	template<> content::ClassInfo* TimeOfDayVarChannel<float>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<float>";
		sInfo.code = "p";
		return &sInfo;
	}


	// The class infos of the fog values, their keys and channel, and of the objects of the time of day
	// FUNCTION: ENGINE 0x10521530
	content::ClassInfo* FogAreaValues::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FogAreaValues";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10521570
	content::ClassInfo* TimeOfDayVarChannel<FogAreaValues>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<proto::FogAreaValues>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x105215B0
	content::ClassInfo* TimeOfDayVarChannel<FogAreaValues>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarChannel<proto::FogAreaValues>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x105215F0
	content::ClassInfo* TimeOfDayLightInfo::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayLightInfo";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10521630
	content::ClassInfo* TimeOfDayVariation::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVariation";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10521670
	content::ClassInfo* TimeOfDayVarGroup::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVarGroup";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x105216B0
	content::ClassInfo* TimeOfDayVars::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TimeOfDayVars";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10521DA0
	content::MemberList* TimeOfDayLightInfo::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<TimeOfDayLightInfo, 0>(true, true, "p"), PROTO_OFFSET(TimeOfDayLightInfo, name), "name" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10523820
	content::MemberList* FogAreaValues::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberColourMetaType<FogAreaValues, 0>("p"), PROTO_OFFSET(FogAreaValues, darkTint), "darkTint" },
			{ content::GetMemberColourMetaType<FogAreaValues, 1>("p"), PROTO_OFFSET(FogAreaValues, lightTint), "lightTint" },
			{ content::GetMemberPrimitiveMetaType<FogAreaValues, float, 0>("p"), PROTO_OFFSET(FogAreaValues, fogTilingX), "fogTiling_x" },
			{ content::GetMemberPrimitiveMetaType<FogAreaValues, float, 1>("p"), PROTO_OFFSET(FogAreaValues, fogTilingY), "fogTiling_y" },
			{ content::GetMemberPrimitiveMetaType<FogAreaValues, float, 2>("p"), PROTO_OFFSET(FogAreaValues, speed), "speed" },
			{ content::GetMemberPrimitiveMetaType<FogAreaValues, float, 3>("p"), PROTO_OFFSET(FogAreaValues, fogFalloff), "fogFalloff" },
			{ content::GetMemberPrimitiveMetaType<FogAreaValues, float, 4>("p"), PROTO_OFFSET(FogAreaValues, falloffModifier), "falloffModifier" },
			{ content::GetMemberPrimitiveMetaType<FogAreaValues, float, 5>("p"), PROTO_OFFSET(FogAreaValues, fogVariation), "fogVariation" },
			{ content::GetMemberPrimitiveMetaType<FogAreaValues, float, 6>("p"), PROTO_OFFSET(FogAreaValues, noiseStrength), "noiseStrength" }
		};
		sList.members = sMembers;
		sList.count = 9;
		return &sList;
	}

	// FUNCTION: ENGINE 0x105248E0
	content::MemberList* TimeOfDayVarChannel<FogAreaValues>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetClassMetaType<FogAreaValues>(), PROTO_OFFSET(Key, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x105249B0
	content::MemberList* TimeOfDayVars::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<TimeOfDayVars, float, 0>("p"), PROTO_OFFSET(TimeOfDayVars, dayLength), "dayLength" },
			{ content::GetMemberPrimitiveMetaType<TimeOfDayVars, float, 1>("p"), PROTO_OFFSET(TimeOfDayVars, dawnTime), "dawnTime" },
			{ content::GetMemberPrimitiveMetaType<TimeOfDayVars, float, 2>("p"), PROTO_OFFSET(TimeOfDayVars, duskTime), "duskTime" },
			{ content::GetMemberPrimitiveMetaType<TimeOfDayVars, float, 3>("p"), PROTO_OFFSET(TimeOfDayVars, renderDawnTime), "renderDawnTime" },
			{ content::GetMemberPrimitiveMetaType<TimeOfDayVars, float, 4>("p"), PROTO_OFFSET(TimeOfDayVars, renderDuskTime), "renderDuskTime" },
			{ content::GetMemberReferenceMetaType<TimeOfDayVars, pure3d::Texture, 0>("p"), PROTO_OFFSET(TimeOfDayVars, cloudCover), "cloudCover" },
			{ content::GetArrayDynamicMetaType<TimeOfDayVars, NameArray>(content::GetMemberNameMetaType<TimeOfDayVars, 0>(true, true, "p"), "p"),
				PROTO_OFFSET(TimeOfDayVars, dayGroups), "dayGroups" },
			{ content::GetArrayDynamicMetaType<TimeOfDayVars, LightInfoArray>(content::GetClassMetaType<TimeOfDayLightInfo>(), "p"),
				PROTO_OFFSET(TimeOfDayVars, lights), "lights" }
		};
		sList.members = sMembers;
		sList.count = 8;
		return &sList;
	}

	// FUNCTION: ENGINE 0x105292C0
	content::MemberList* TimeOfDayVarChannel<FogAreaValues>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<TimeOfDayVarChannel<FogAreaValues>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(TimeOfDayVarChannel<FogAreaValues>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1052B8B0
	content::MemberList* TimeOfDayVariation::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<TimeOfDayVariation, 0>(true, true, "p"), PROTO_OFFSET(TimeOfDayVariation, name), "name" },
			{ content::GetClassMetaType<GlobalLightingRig>(), PROTO_OFFSET(TimeOfDayVariation, globalLights), "globalLights" },
			{ content::GetClassMetaType<GlobalFBEffectsRig>(), PROTO_OFFSET(TimeOfDayVariation, globalFBEffects), "globalFBEffects" },
			{ content::GetClassMetaType<GlobalShaderRig>(), PROTO_OFFSET(TimeOfDayVariation, globalShaderParams), "globalShaderParams" },
			{ content::GetClassMetaType<FogChannel>(), PROTO_OFFSET(TimeOfDayVariation, globalFogValues), "globalFogValues" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1052BFC0
	content::MemberList* TimeOfDayVarGroup::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<TimeOfDayVarGroup, 0>(true, true, "p"), PROTO_OFFSET(TimeOfDayVarGroup, name), "name" },
			{ content::GetArrayDynamicMetaType<TimeOfDayVarGroup, VariationArray>(content::GetClassMetaType<TimeOfDayVariation>(), "pn"),
				PROTO_OFFSET(TimeOfDayVarGroup, dayVariations), "dayVariations" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	template class TimeOfDayVarChannel<float>;
	template class TimeOfDayVarChannel<math::Vector>;
	template class TimeOfDayVarChannel<math::Colour128>;
	template class TimeOfDayVarChannel<math::Vector2>;
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1051F4F0
// FUNCTION: ENGINE 0x1051F530
// FUNCTION: ENGINE 0x1051F540
// FUNCTION: ENGINE 0x1051F580
// FUNCTION: ENGINE 0x1051F590
// FUNCTION: ENGINE 0x1051F5A0
// FUNCTION: ENGINE 0x1051F5E0
// FUNCTION: ENGINE 0x1051F620
// FUNCTION: ENGINE 0x1051F660
// FUNCTION: ENGINE 0x1051F6A0
// FUNCTION: ENGINE 0x1051F710
// FUNCTION: ENGINE 0x1051F740
// FUNCTION: ENGINE 0x1051F760
// FUNCTION: ENGINE 0x1051F7C0
// FUNCTION: ENGINE 0x1051F7F0
// FUNCTION: ENGINE 0x1051F810
// FUNCTION: ENGINE 0x1051F830
// FUNCTION: ENGINE 0x1051F860
// FUNCTION: ENGINE 0x1051F950
// FUNCTION: ENGINE 0x1051F9B0
// FUNCTION: ENGINE 0x1051F9E0
// FUNCTION: ENGINE 0x1051FA00
// FUNCTION: ENGINE 0x1051FA10
// FUNCTION: ENGINE 0x1051FA30
// FUNCTION: ENGINE 0x1051FA50
// FUNCTION: ENGINE 0x1051FA70
// FUNCTION: ENGINE 0x1051FA90
// FUNCTION: ENGINE 0x1051FBE0
// FUNCTION: ENGINE 0x1051FC10
// FUNCTION: ENGINE 0x1051FC30
// FUNCTION: ENGINE 0x1051FC40
// FUNCTION: ENGINE 0x1051FC50
// FUNCTION: ENGINE 0x1051FC70
// FUNCTION: ENGINE 0x1051FC90
// FUNCTION: ENGINE 0x1051FCB0
// FUNCTION: ENGINE 0x1051FD70
// FUNCTION: ENGINE 0x1051FD90
// FUNCTION: ENGINE 0x1051FDC0
// FUNCTION: ENGINE 0x1051FE10
// FUNCTION: ENGINE 0x1051FE40
// FUNCTION: ENGINE 0x1051FE80
// FUNCTION: ENGINE 0x1051FF10
// FUNCTION: ENGINE 0x1051FFB0
// FUNCTION: ENGINE 0x10520050
// FUNCTION: ENGINE 0x10520130
// FUNCTION: ENGINE 0x10520210
// FUNCTION: ENGINE 0x105204B0
// FUNCTION: ENGINE 0x10520510
// FUNCTION: ENGINE 0x10520570
// FUNCTION: ENGINE 0x105205D0
// FUNCTION: ENGINE 0x10520630
// FUNCTION: ENGINE 0x10520690
// FUNCTION: ENGINE 0x10520930
// FUNCTION: ENGINE 0x10520960
// FUNCTION: ENGINE 0x10520A20
// FUNCTION: ENGINE 0x10520A50
// FUNCTION: ENGINE 0x10520AA0
// FUNCTION: ENGINE 0x10520B50
// FUNCTION: ENGINE 0x10520BC0
// FUNCTION: ENGINE 0x10520C00
// FUNCTION: ENGINE 0x10521100
// FUNCTION: ENGINE 0x105211E0
// FUNCTION: ENGINE 0x10521250
// FUNCTION: ENGINE 0x105212D0
// FUNCTION: ENGINE 0x10521320
// FUNCTION: ENGINE 0x10521370
// FUNCTION: ENGINE 0x10521490
// FUNCTION: ENGINE 0x10522A30
// FUNCTION: ENGINE 0x10522C70
// FUNCTION: ENGINE 0x10522C90
// FUNCTION: ENGINE 0x10522F60
// FUNCTION: ENGINE 0x10523390
// FUNCTION: ENGINE 0x10523650
// FUNCTION: ENGINE 0x105237C0
// FUNCTION: ENGINE 0x10523FE0
// FUNCTION: ENGINE 0x10524790
// FUNCTION: ENGINE 0x10525B30
// FUNCTION: ENGINE 0x10525B60
// FUNCTION: ENGINE 0x10525C10
// FUNCTION: ENGINE 0x10525CA0
// FUNCTION: ENGINE 0x10525CE0
// FUNCTION: ENGINE 0x10525D30
// FUNCTION: ENGINE 0x10525D90
// FUNCTION: ENGINE 0x10525E00
// FUNCTION: ENGINE 0x10525E80
// FUNCTION: ENGINE 0x10525F10
// FUNCTION: ENGINE 0x10526000
// FUNCTION: ENGINE 0x10526040
// FUNCTION: ENGINE 0x10526060
// FUNCTION: ENGINE 0x10526100
// FUNCTION: ENGINE 0x10526110
// FUNCTION: ENGINE 0x10526180
// FUNCTION: ENGINE 0x10526240
// FUNCTION: ENGINE 0x105262F0
// FUNCTION: ENGINE 0x10526340
// FUNCTION: ENGINE 0x10526370
// FUNCTION: ENGINE 0x10526460
// FUNCTION: ENGINE 0x10526510
// FUNCTION: ENGINE 0x10526550
// FUNCTION: ENGINE 0x10526660
// FUNCTION: ENGINE 0x10526780
// FUNCTION: ENGINE 0x10526860
// FUNCTION: ENGINE 0x10526950
// FUNCTION: ENGINE 0x105269D0
// FUNCTION: ENGINE 0x10526A50
// FUNCTION: ENGINE 0x10526A70
// FUNCTION: ENGINE 0x10526A80
// FUNCTION: ENGINE 0x10526AF0
// FUNCTION: ENGINE 0x10526B80
// FUNCTION: ENGINE 0x10527010
// FUNCTION: ENGINE 0x10527090
// FUNCTION: ENGINE 0x105270D0
// FUNCTION: ENGINE 0x10527230
// FUNCTION: ENGINE 0x10527260
// FUNCTION: ENGINE 0x10527470
// FUNCTION: ENGINE 0x10527530
// FUNCTION: ENGINE 0x10527920
// FUNCTION: ENGINE 0x10527940
// FUNCTION: ENGINE 0x10527950
// FUNCTION: ENGINE 0x105279C0
// FUNCTION: ENGINE 0x10527A10
// FUNCTION: ENGINE 0x10527AD0
// FUNCTION: ENGINE 0x10527C30
// FUNCTION: ENGINE 0x10527D70
// FUNCTION: ENGINE 0x105281D0
// FUNCTION: ENGINE 0x10528750
// FUNCTION: ENGINE 0x10528DC0
// FUNCTION: ENGINE 0x10528EB0
// FUNCTION: ENGINE 0x10529130
// FUNCTION: ENGINE 0x10529190
// FUNCTION: ENGINE 0x10529580
// FUNCTION: ENGINE 0x105295B0
// FUNCTION: ENGINE 0x105295E0
// FUNCTION: ENGINE 0x10529610
// FUNCTION: ENGINE 0x10529640
// FUNCTION: ENGINE 0x105297E0
// FUNCTION: ENGINE 0x10529860
// FUNCTION: ENGINE 0x10529900
// FUNCTION: ENGINE 0x10529CF0
// FUNCTION: ENGINE 0x10529D10
// FUNCTION: ENGINE 0x10529DD0
// FUNCTION: ENGINE 0x10529DE0
// FUNCTION: ENGINE 0x1052A460
// FUNCTION: ENGINE 0x1052A4B0
// FUNCTION: ENGINE 0x1052A500
// FUNCTION: ENGINE 0x1052A550
// FUNCTION: ENGINE 0x1052AAE0
// FUNCTION: ENGINE 0x1052AB30
// FUNCTION: ENGINE 0x1052B530
// FUNCTION: ENGINE 0x1052B5A0
// FUNCTION: ENGINE 0x1052BF00
// FUNCTION: ENGINE 0x1052BF10
// FUNCTION: ENGINE 0x1052BF20
// FUNCTION: ENGINE 0x1052C7E0
// FUNCTION: ENGINE 0x1052C8E0
// FUNCTION: ENGINE 0x1052CA50
// FUNCTION: ENGINE 0x1052D740
// FUNCTION: ENGINE 0x1052D770
// FUNCTION: ENGINE 0x1052D7B0
// FUNCTION: ENGINE 0x1052D9D0
// FUNCTION: ENGINE 0x1052DAB0
// FUNCTION: ENGINE 0x1052DBE0
// FUNCTION: ENGINE 0x10521AE0
// FUNCTION: ENGINE 0x10521B20
// FUNCTION: ENGINE 0x10521B80
// FUNCTION: ENGINE 0x10521BC0
// FUNCTION: ENGINE 0x10521C40
// FUNCTION: ENGINE 0x10521C90
// FUNCTION: ENGINE 0x10522590
// FUNCTION: ENGINE 0x105225D0
// FUNCTION: ENGINE 0x10522610
// FUNCTION: ENGINE 0x10522650
// FUNCTION: ENGINE 0x10522690
// FUNCTION: ENGINE 0x105226D0
// FUNCTION: ENGINE 0x10522710
// FUNCTION: ENGINE 0x10522750
// FUNCTION: ENGINE 0x10522790
// FUNCTION: ENGINE 0x105227D0
// FUNCTION: ENGINE 0x10522810
// FUNCTION: ENGINE 0x10522850
// FUNCTION: ENGINE 0x10522890
// FUNCTION: ENGINE 0x1052EA30
// FUNCTION: ENGINE 0x1052F1D0
