#include "code/proto/timeofday/globalfbeffectsrig.h"
#include "code/content/colourmetatype.h"
#include "code/content/vectormetatype.h"

namespace proto
{
#define PROTO_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1052E0F0
	content::ClassInfo* GlobalFBEffectsRig::ColourMatrixParameters::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalFBEffectsRig::ColourMatrixParameters";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1052E130
	template<> content::ClassInfo* TimeOfDayVarChannel<GlobalFBEffectsRig::ColourMatrixParameters>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalFBEffectsRigChannel<proto::GlobalFBEffectsRig::ColourMatrixParameters>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1052E170
	template<> content::ClassInfo* GlobalFBEffectsRigChannel<GlobalFBEffectsRig::ColourMatrixParameters>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalFBEffectsRigChannel<proto::GlobalFBEffectsRig::ColourMatrixParameters>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10531220
	content::MemberList* GlobalFBEffectsRig::ColourMatrixParameters::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::ColourMatrixParameters, float, 0>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::ColourMatrixParameters, brightness), "brightness" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::ColourMatrixParameters, float, 1>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::ColourMatrixParameters, contrast), "contrast" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::ColourMatrixParameters, float, 2>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::ColourMatrixParameters, midpoint), "midpoint" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::ColourMatrixParameters, float, 3>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::ColourMatrixParameters, saturation), "saturation" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::ColourMatrixParameters, float, 4>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::ColourMatrixParameters, hue), "hue" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::ColourMatrixParameters, float, 5>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::ColourMatrixParameters, cmykScale), "cmykScale" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::ColourMatrixParameters, float, 6>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::ColourMatrixParameters, cmykBias), "cmykBias" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::ColourMatrixParameters, float, 7>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::ColourMatrixParameters, grainSpeed), "grainSpeed" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::ColourMatrixParameters, float, 8>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::ColourMatrixParameters, grainIntensity), "grainIntensity" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::ColourMatrixParameters, float, 9>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::ColourMatrixParameters, overlayOpacity), "overlayOpacity" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::ColourMatrixParameters, float, 10>("pn"),
				PROTO_OFFSET(GlobalFBEffectsRig::ColourMatrixParameters, overlaySaturation), "overlaySaturation" },
			{ content::GetMemberColourMetaType<GlobalFBEffectsRig::ColourMatrixParameters, 0>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::ColourMatrixParameters, tint), "tint" },
			{ content::GetMemberVectorMetaType<GlobalFBEffectsRig::ColourMatrixParameters, 0>("p"),
				(int)&(((GlobalFBEffectsRig::ColourMatrixParameters*)0)->cmyk), "cmyk" }
		};
		sList.members = sMembers;
		sList.count = 13;
		return &sList;
	}

	// FUNCTION: ENGINE 0x105328E0
	template<> content::MemberList* TimeOfDayVarChannel<GlobalFBEffectsRig::ColourMatrixParameters>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetClassMetaType<GlobalFBEffectsRig::ColourMatrixParameters>(), PROTO_OFFSET(Key, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10533F50
	template<> content::MemberList* GlobalFBEffectsRigChannel<GlobalFBEffectsRig::ColourMatrixParameters>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRigChannel<GlobalFBEffectsRig::ColourMatrixParameters>, bool, 0>("p"),
				PROTO_OFFSET(GlobalFBEffectsRigChannel<GlobalFBEffectsRig::ColourMatrixParameters>, enable), "enable" },
			{ content::GetArrayDynamicMetaType<GlobalFBEffectsRigChannel<GlobalFBEffectsRig::ColourMatrixParameters>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(GlobalFBEffectsRigChannel<GlobalFBEffectsRig::ColourMatrixParameters>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1052E1B0
	content::ClassInfo* GlobalFBEffectsRig::TonemapParameters::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalFBEffectsRig::TonemapParameters";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1052E1F0
	template<> content::ClassInfo* TimeOfDayVarChannel<GlobalFBEffectsRig::TonemapParameters>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalFBEffectsRigChannel<proto::GlobalFBEffectsRig::TonemapParameters>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1052E230
	template<> content::ClassInfo* GlobalFBEffectsRigChannel<GlobalFBEffectsRig::TonemapParameters>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalFBEffectsRigChannel<proto::GlobalFBEffectsRig::TonemapParameters>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10531510
	content::MemberList* GlobalFBEffectsRig::TonemapParameters::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::TonemapParameters, float, 0>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::TonemapParameters, avgLum), "avgLum" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::TonemapParameters, float, 1>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::TonemapParameters, adaptRate), "adaptRate" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::TonemapParameters, float, 2>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::TonemapParameters, rangeLower), "rangeLower" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::TonemapParameters, float, 3>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::TonemapParameters, rangeUpper), "rangeUpper" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::TonemapParameters, float, 4>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::TonemapParameters, exposurePower), "exposurePower" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x105329B0
	template<> content::MemberList* TimeOfDayVarChannel<GlobalFBEffectsRig::TonemapParameters>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetClassMetaType<GlobalFBEffectsRig::TonemapParameters>(), PROTO_OFFSET(Key, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10534030
	template<> content::MemberList* GlobalFBEffectsRigChannel<GlobalFBEffectsRig::TonemapParameters>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRigChannel<GlobalFBEffectsRig::TonemapParameters>, bool, 0>("p"),
				PROTO_OFFSET(GlobalFBEffectsRigChannel<GlobalFBEffectsRig::TonemapParameters>, enable), "enable" },
			{ content::GetArrayDynamicMetaType<GlobalFBEffectsRigChannel<GlobalFBEffectsRig::TonemapParameters>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(GlobalFBEffectsRigChannel<GlobalFBEffectsRig::TonemapParameters>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1052E270
	content::ClassInfo* GlobalFBEffectsRig::BloomParameters::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalFBEffectsRig::BloomParameters";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1052E2B0
	template<> content::ClassInfo* TimeOfDayVarChannel<GlobalFBEffectsRig::BloomParameters>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalFBEffectsRigChannel<proto::GlobalFBEffectsRig::BloomParameters>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1052E2F0
	template<> content::ClassInfo* GlobalFBEffectsRigChannel<GlobalFBEffectsRig::BloomParameters>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalFBEffectsRigChannel<proto::GlobalFBEffectsRig::BloomParameters>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10531680
	content::MemberList* GlobalFBEffectsRig::BloomParameters::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::BloomParameters, float, 0>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::BloomParameters, bloom), "bloom" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::BloomParameters, float, 1>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::BloomParameters, backbuffer), "backbuffer" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::BloomParameters, float, 2>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::BloomParameters, radiusX), "radiusX" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::BloomParameters, float, 3>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::BloomParameters, radiusY), "radiusY" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::BloomParameters, float, 4>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::BloomParameters, cutoff), "cutoff" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::BloomParameters, float, 5>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::BloomParameters, falloff), "falloff" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::BloomParameters, float, 6>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::BloomParameters, contrast), "contrast" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::BloomParameters, float, 7>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::BloomParameters, brightness), "brightness" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::BloomParameters, float, 8>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::BloomParameters, hue), "hue" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::BloomParameters, float, 9>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::BloomParameters, midpoint), "midpoint" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::BloomParameters, float, 10>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::BloomParameters, saturation), "saturation" },
			{ content::GetMemberColourMetaType<GlobalFBEffectsRig::BloomParameters, 0>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::BloomParameters, tint), "tint" }
		};
		sList.members = sMembers;
		sList.count = 12;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10532A80
	template<> content::MemberList* TimeOfDayVarChannel<GlobalFBEffectsRig::BloomParameters>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetClassMetaType<GlobalFBEffectsRig::BloomParameters>(), PROTO_OFFSET(Key, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10534110
	template<> content::MemberList* GlobalFBEffectsRigChannel<GlobalFBEffectsRig::BloomParameters>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRigChannel<GlobalFBEffectsRig::BloomParameters>, bool, 0>("p"),
				PROTO_OFFSET(GlobalFBEffectsRigChannel<GlobalFBEffectsRig::BloomParameters>, enable), "enable" },
			{ content::GetArrayDynamicMetaType<GlobalFBEffectsRigChannel<GlobalFBEffectsRig::BloomParameters>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(GlobalFBEffectsRigChannel<GlobalFBEffectsRig::BloomParameters>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1052E330
	content::ClassInfo* GlobalFBEffectsRig::DOFParameters::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalFBEffectsRig::DOFParameters";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1052E370
	template<> content::ClassInfo* TimeOfDayVarChannel<GlobalFBEffectsRig::DOFParameters>::Key::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalFBEffectsRigChannel<proto::GlobalFBEffectsRig::DOFParameters>::Key";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1052E3B0
	template<> content::ClassInfo* GlobalFBEffectsRigChannel<GlobalFBEffectsRig::DOFParameters>::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalFBEffectsRigChannel<proto::GlobalFBEffectsRig::DOFParameters>";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10531940
	content::MemberList* GlobalFBEffectsRig::DOFParameters::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::DOFParameters, float, 0>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::DOFParameters, nearDepth), "nearDepth" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::DOFParameters, float, 1>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::DOFParameters, farDepth), "farDepth" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::DOFParameters, float, 2>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::DOFParameters, range), "range" },
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRig::DOFParameters, float, 3>("p"),
				PROTO_OFFSET(GlobalFBEffectsRig::DOFParameters, aperture), "aperture" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10532B50
	template<> content::MemberList* TimeOfDayVarChannel<GlobalFBEffectsRig::DOFParameters>::Key::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Key, float, 0>("p"), PROTO_OFFSET(Key, time), "time" },
			{ content::GetClassMetaType<GlobalFBEffectsRig::DOFParameters>(), PROTO_OFFSET(Key, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x105341F0
	template<> content::MemberList* GlobalFBEffectsRigChannel<GlobalFBEffectsRig::DOFParameters>::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<GlobalFBEffectsRigChannel<GlobalFBEffectsRig::DOFParameters>, bool, 0>("p"),
				PROTO_OFFSET(GlobalFBEffectsRigChannel<GlobalFBEffectsRig::DOFParameters>, enable), "enable" },
			{ content::GetArrayDynamicMetaType<GlobalFBEffectsRigChannel<GlobalFBEffectsRig::DOFParameters>, KeyArray>(content::GetClassMetaType<Key>(), "p"),
				PROTO_OFFSET(GlobalFBEffectsRigChannel<GlobalFBEffectsRig::DOFParameters>, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1052E3F0
	content::ClassInfo* GlobalFBEffectsRig::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GlobalFBEffectsRig";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1053BDA0
	content::MemberList* GlobalFBEffectsRig::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetClassMetaType<GlobalFBEffectsRigChannel<BloomParameters> >(),
				PROTO_OFFSET(GlobalFBEffectsRig, bloomKeys), "bloomKeys" },
			{ content::GetClassMetaType<GlobalFBEffectsRigChannel<TonemapParameters> >(),
				PROTO_OFFSET(GlobalFBEffectsRig, tonemapKeys), "tonemapKeys" },
			{ content::GetClassMetaType<GlobalFBEffectsRigChannel<ColourMatrixParameters> >(),
				PROTO_OFFSET(GlobalFBEffectsRig, colourMatrixKeys), "colourMatrixKeys" },
			{ content::GetClassMetaType<GlobalFBEffectsRigChannel<DOFParameters> >(),
				PROTO_OFFSET(GlobalFBEffectsRig, dofKeys), "dofKeys" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1052E430
	GlobalFBEffectsRigChannel<GlobalFBEffectsRig::BloomParameters>* GlobalFBEffectsRig::GetBloomKeys()
	{
		return &bloomKeys;
	}

	// FUNCTION: ENGINE 0x1052E440
	GlobalFBEffectsRigChannel<GlobalFBEffectsRig::TonemapParameters>* GlobalFBEffectsRig::GetTonemapKeys()
	{
		return &tonemapKeys;
	}

	// FUNCTION: ENGINE 0x1052E450
	GlobalFBEffectsRigChannel<GlobalFBEffectsRig::ColourMatrixParameters>* GlobalFBEffectsRig::GetColourMatrixKeys()
	{
		return &colourMatrixKeys;
	}

	// FUNCTION: ENGINE 0x1052E460
	GlobalFBEffectsRigChannel<GlobalFBEffectsRig::DOFParameters>* GlobalFBEffectsRig::GetDofKeys()
	{
		return &dofKeys;
	}

	// FUNCTION: ENGINE 0x1052E470
	const GlobalFBEffectsRigChannel<GlobalFBEffectsRig::BloomParameters>* GlobalFBEffectsRig::GetBloomKeys() const
	{
		return &bloomKeys;
	}

	// FUNCTION: ENGINE 0x1052E480
	const GlobalFBEffectsRigChannel<GlobalFBEffectsRig::TonemapParameters>* GlobalFBEffectsRig::GetTonemapKeys() const
	{
		return &tonemapKeys;
	}

	// FUNCTION: ENGINE 0x1052E490
	const GlobalFBEffectsRigChannel<GlobalFBEffectsRig::ColourMatrixParameters>* GlobalFBEffectsRig::GetColourMatrixKeys() const
	{
		return &colourMatrixKeys;
	}

	// FUNCTION: ENGINE 0x1052E4A0
	const GlobalFBEffectsRigChannel<GlobalFBEffectsRig::DOFParameters>* GlobalFBEffectsRig::GetDofKeys() const
	{
		return &dofKeys;
	}

	template class GlobalFBEffectsRigChannel<GlobalFBEffectsRig::BloomParameters>;
	template class GlobalFBEffectsRigChannel<GlobalFBEffectsRig::TonemapParameters>;
	template class GlobalFBEffectsRigChannel<GlobalFBEffectsRig::ColourMatrixParameters>;
	template class GlobalFBEffectsRigChannel<GlobalFBEffectsRig::DOFParameters>;
	// FUNCTION: ENGINE 0x1052EA90
	// NONMATCHING: 65 %: the engine computes the last index twice and branches on it differently
#ifdef NONMATCHING
	template int TimeOfDayVarChannel<GlobalFBEffectsRig::BloomParameters>::FindPreviousKey(float time);
#endif
	// FUNCTION: ENGINE 0x1052EB20
	// NONMATCHING: 88 %: the engine tests the emptiness with a shift, ours masks the size
#ifdef NONMATCHING
	template int TimeOfDayVarChannel<GlobalFBEffectsRig::BloomParameters>::FindNextKey(float time);
#endif
	template int TimeOfDayVarChannel<GlobalFBEffectsRig::TonemapParameters>::FindPreviousKey(float time);
	template int TimeOfDayVarChannel<GlobalFBEffectsRig::TonemapParameters>::FindNextKey(float time);
	template int TimeOfDayVarChannel<GlobalFBEffectsRig::ColourMatrixParameters>::FindPreviousKey(float time);
	template int TimeOfDayVarChannel<GlobalFBEffectsRig::ColourMatrixParameters>::FindNextKey(float time);
	template int TimeOfDayVarChannel<GlobalFBEffectsRig::DOFParameters>::FindPreviousKey(float time);
	template int TimeOfDayVarChannel<GlobalFBEffectsRig::DOFParameters>::FindNextKey(float time);
}

namespace container
{
	template class ArrayDynamic<proto::TimeOfDayVarChannel<proto::GlobalFBEffectsRig::BloomParameters>::Key, AllocatorNew>;
	template class ArrayDynamic<proto::TimeOfDayVarChannel<proto::GlobalFBEffectsRig::TonemapParameters>::Key, AllocatorNew>;
	template class ArrayDynamic<proto::TimeOfDayVarChannel<proto::GlobalFBEffectsRig::ColourMatrixParameters>::Key, AllocatorNew>;
	template class ArrayDynamic<proto::TimeOfDayVarChannel<proto::GlobalFBEffectsRig::DOFParameters>::Key, AllocatorNew>;
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1052E580
// FUNCTION: ENGINE 0x1052E630
// FUNCTION: ENGINE 0x1052E6E0
// FUNCTION: ENGINE 0x1052E790
// FUNCTION: ENGINE 0x1052E7E0
// FUNCTION: ENGINE 0x1052E820
// FUNCTION: ENGINE 0x1052E860
// FUNCTION: ENGINE 0x1052E870
// FUNCTION: ENGINE 0x1052E880
// FUNCTION: ENGINE 0x1052E890
// FUNCTION: ENGINE 0x1052E8A0
// FUNCTION: ENGINE 0x1052E8E0
// FUNCTION: ENGINE 0x1052E8F0
// FUNCTION: ENGINE 0x1052E900
// FUNCTION: ENGINE 0x1052E910
// FUNCTION: ENGINE 0x1052E920
// FUNCTION: ENGINE 0x1052E930
// FUNCTION: ENGINE 0x1052E940
// FUNCTION: ENGINE 0x1052E950
// FUNCTION: ENGINE 0x1052E960
// FUNCTION: ENGINE 0x1052E990
// FUNCTION: ENGINE 0x1052E9F0
// FUNCTION: ENGINE 0x1052EFE0
// FUNCTION: ENGINE 0x1052F040
// FUNCTION: ENGINE 0x1052F130
// FUNCTION: ENGINE 0x1052F680
// FUNCTION: ENGINE 0x1052F6C0
// FUNCTION: ENGINE 0x1052F700
// FUNCTION: ENGINE 0x1052F740
// FUNCTION: ENGINE 0x1052F780
// FUNCTION: ENGINE 0x1052F7C0
// FUNCTION: ENGINE 0x1052F800
// FUNCTION: ENGINE 0x1052F840
// FUNCTION: ENGINE 0x1052F880
// FUNCTION: ENGINE 0x1052F8C0
// FUNCTION: ENGINE 0x1052F900
// FUNCTION: ENGINE 0x1052F940
// FUNCTION: ENGINE 0x1052F980
// FUNCTION: ENGINE 0x1052F9C0
// FUNCTION: ENGINE 0x1052FA00
// FUNCTION: ENGINE 0x1052FA40
// FUNCTION: ENGINE 0x1052FA80
// FUNCTION: ENGINE 0x1052FAC0
// FUNCTION: ENGINE 0x1052FB00
// FUNCTION: ENGINE 0x1052FB40
// FUNCTION: ENGINE 0x1052FB80
// FUNCTION: ENGINE 0x1052FBC0
// FUNCTION: ENGINE 0x1052FC00
// FUNCTION: ENGINE 0x1052FC40
// FUNCTION: ENGINE 0x1052FC80
// FUNCTION: ENGINE 0x1052FCC0
// FUNCTION: ENGINE 0x1052FD00
// FUNCTION: ENGINE 0x1052FD40
// FUNCTION: ENGINE 0x1052FD80
// FUNCTION: ENGINE 0x1052FDC0
// FUNCTION: ENGINE 0x1052FE00
// FUNCTION: ENGINE 0x1052FE40
// FUNCTION: ENGINE 0x1052FE80
// FUNCTION: ENGINE 0x1052FEC0
// FUNCTION: ENGINE 0x1052FF00
// FUNCTION: ENGINE 0x1052FF40
// FUNCTION: ENGINE 0x1052FF80
// FUNCTION: ENGINE 0x1052FFC0
// FUNCTION: ENGINE 0x10530000
// FUNCTION: ENGINE 0x10530130
// FUNCTION: ENGINE 0x10530160
// FUNCTION: ENGINE 0x10530190
// FUNCTION: ENGINE 0x105301B0
// FUNCTION: ENGINE 0x105301D0
// FUNCTION: ENGINE 0x10530200
// FUNCTION: ENGINE 0x10530260
// FUNCTION: ENGINE 0x10530290
// FUNCTION: ENGINE 0x105302C0
// FUNCTION: ENGINE 0x105302E0
// FUNCTION: ENGINE 0x10530300
// FUNCTION: ENGINE 0x10530330
// FUNCTION: ENGINE 0x105303F0
// FUNCTION: ENGINE 0x10530420
// FUNCTION: ENGINE 0x10530440
// FUNCTION: ENGINE 0x10530460
// FUNCTION: ENGINE 0x10530480
// FUNCTION: ENGINE 0x105304A0
// FUNCTION: ENGINE 0x10530530
// FUNCTION: ENGINE 0x10530560
// FUNCTION: ENGINE 0x10530580
// FUNCTION: ENGINE 0x105305A0
// FUNCTION: ENGINE 0x105305D0
// FUNCTION: ENGINE 0x10530850
// FUNCTION: ENGINE 0x105309F0
// FUNCTION: ENGINE 0x10530BC0
// FUNCTION: ENGINE 0x10530C20
// FUNCTION: ENGINE 0x10530ED0
// FUNCTION: ENGINE 0x10531020
// FUNCTION: ENGINE 0x10531090
// FUNCTION: ENGINE 0x10531AE0
// FUNCTION: ENGINE 0x10531B40
// FUNCTION: ENGINE 0x10531BA0
// FUNCTION: ENGINE 0x10531C00
// FUNCTION: ENGINE 0x105320C0
// FUNCTION: ENGINE 0x10532120
// FUNCTION: ENGINE 0x10532180
// FUNCTION: ENGINE 0x105321E0
// FUNCTION: ENGINE 0x10532240
// FUNCTION: ENGINE 0x10532370
// FUNCTION: ENGINE 0x105323A0
// FUNCTION: ENGINE 0x105324C0
// FUNCTION: ENGINE 0x105324F0
// FUNCTION: ENGINE 0x10532560
// FUNCTION: ENGINE 0x105327E0
// FUNCTION: ENGINE 0x10533440
// FUNCTION: ENGINE 0x105334A0
// FUNCTION: ENGINE 0x10533500
// FUNCTION: ENGINE 0x10533560
// FUNCTION: ENGINE 0x105338F0
// FUNCTION: ENGINE 0x10533C70
// FUNCTION: ENGINE 0x10533D20
// FUNCTION: ENGINE 0x10533D70
// FUNCTION: ENGINE 0x10533DD0
// FUNCTION: ENGINE 0x10533E30
// FUNCTION: ENGINE 0x10534360
// FUNCTION: ENGINE 0x105344C0
// FUNCTION: ENGINE 0x10534510
// FUNCTION: ENGINE 0x10534950
// FUNCTION: ENGINE 0x105349F0
// FUNCTION: ENGINE 0x10534A00
// FUNCTION: ENGINE 0x105350B0
// FUNCTION: ENGINE 0x10535300
// FUNCTION: ENGINE 0x10535380
// FUNCTION: ENGINE 0x10535430
// FUNCTION: ENGINE 0x105358D0
// FUNCTION: ENGINE 0x105358F0
// FUNCTION: ENGINE 0x105359B0
// FUNCTION: ENGINE 0x10536900
// FUNCTION: ENGINE 0x10536BE0
// FUNCTION: ENGINE 0x10537220
// FUNCTION: ENGINE 0x10537240
// FUNCTION: ENGINE 0x10537250
// FUNCTION: ENGINE 0x10537650
// FUNCTION: ENGINE 0x10537B40
// FUNCTION: ENGINE 0x10537D50
// FUNCTION: ENGINE 0x10537DD0
// FUNCTION: ENGINE 0x10537E70
// FUNCTION: ENGINE 0x105382A0
// FUNCTION: ENGINE 0x105382C0
// FUNCTION: ENGINE 0x10538380
// FUNCTION: ENGINE 0x10538390
// FUNCTION: ENGINE 0x10539150
// FUNCTION: ENGINE 0x105391B0
// FUNCTION: ENGINE 0x10539210
// FUNCTION: ENGINE 0x10539270
// FUNCTION: ENGINE 0x105392D0
// FUNCTION: ENGINE 0x10539320
// FUNCTION: ENGINE 0x10539370
// FUNCTION: ENGINE 0x105393C0
// FUNCTION: ENGINE 0x10539410
// FUNCTION: ENGINE 0x10539430
// FUNCTION: ENGINE 0x10539480
// FUNCTION: ENGINE 0x105394A0
// FUNCTION: ENGINE 0x105396C0
// FUNCTION: ENGINE 0x10539800
// FUNCTION: ENGINE 0x10539910
// FUNCTION: ENGINE 0x1053C0E0
// FUNCTION: ENGINE 0x1053C130
// FUNCTION: ENGINE 0x1053C180
// FUNCTION: ENGINE 0x1053C1D0
// FUNCTION: ENGINE 0x1053C620
// FUNCTION: ENGINE 0x10534330
// FUNCTION: ENGINE 0x10535080
// FUNCTION: ENGINE 0x105368D0
// FUNCTION: ENGINE 0x10537B10
// FUNCTION: ENGINE 0x1053BF40
// FUNCTION: ENGINE 0x1053BFD0
// FUNCTION: ENGINE 0x1053C020
// FUNCTION: ENGINE 0x1053C0B0
// FUNCTION: ENGINE 0x1052EBB0
// FUNCTION: ENGINE 0x1052EC50
// FUNCTION: ENGINE 0x1052ED10
// FUNCTION: ENGINE 0x1052EDB0
// FUNCTION: ENGINE 0x1052EE70
// FUNCTION: ENGINE 0x1052EF10
// FUNCTION: ENGINE 0x1052e980
// FUNCTION: ENGINE 0x1052e9d0
// FUNCTION: ENGINE 0x1052ea20
// FUNCTION: ENGINE 0x1052ea70
// FUNCTION: ENGINE 0x10530390
// FUNCTION: ENGINE 0x10530630
// FUNCTION: ENGINE 0x105325d0
// FUNCTION: ENGINE 0x10532620
// FUNCTION: ENGINE 0x1053c2c0
// FUNCTION: ENGINE 0x1052E590
// FUNCTION: ENGINE 0x1052E650
// FUNCTION: ENGINE 0x1052E700
// FUNCTION: ENGINE 0x1052E7B0
// FUNCTION: ENGINE 0x1052E5A0
// FUNCTION: ENGINE 0x1052E660
// FUNCTION: ENGINE 0x1052E710
// FUNCTION: ENGINE 0x1052E7C0
// FUNCTION: ENGINE 0x10530C60
// FUNCTION: ENGINE 0x10530CA0
// FUNCTION: ENGINE 0x10530CE0
// FUNCTION: ENGINE 0x10530D20
// FUNCTION: ENGINE 0x1052F250
// FUNCTION: ENGINE 0x1052F260
// FUNCTION: ENGINE 0x1052F270
// FUNCTION: ENGINE 0x1052F280
