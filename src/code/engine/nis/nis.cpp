#include "code/engine/nis/nis.h"
#include <new>

namespace content
{
	// The meta types of the name members of a class that has several of them (Id tells them apart)
	template<class C, int Id> NameMetaType* GetMemberNameMetaType(bool unknown8, bool unknown9, const char* code)
	{
		static NameMetaType sType(unknown8, unknown9, code);
		return &sType;
	}
}

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_MATRIX_OFFSET(type, member) \
	content::MemberOffset((math::Matrix*)&((type*)0)->member, (int)&((type*)0)->member)

	// A tag that keeps a second float array of the scene apart from the first
	struct ShotBoundariesTag
	{
	};

	// FUNCTION: ENGINE 0x1088B6E0
	content::ClassInfo* NIS::Insertion::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::NIS::Insertion";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1088B720
	content::ClassInfo* NIS::Placement::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::NIS::Placement";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1088B760
	content::ClassInfo* NIS::Animation::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::NIS::Animation";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1088B7A0
	content::ClassInfo* NIS::Attachment::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::NIS::Attachment";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1088B7E0
	content::ClassInfo* NIS::Visibility::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::NIS::Visibility";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1088B820
	content::ClassInfo* NIS::LightGroup::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::NIS::LightGroup";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1088B860
	content::ClassInfo* NIS::SubTitle::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::NIS::SubTitle";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1088B8E0
	content::ClassInfo* NIS::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::NIS";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1088BD80
	content::MemberList* NIS::Insertion::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<Insertion, 0>(true, true, "p"), ENGINE_NAME_OFFSET(Insertion, object),
				"object" },
			{ content::GetMemberNameMetaType<Insertion, 1>(true, true, "p"),
				ENGINE_NAME_OFFSET(Insertion, objectTemplate), "template" },
			{ content::GetMatrixMetaType<Insertion>(false, false, "p"), ENGINE_MATRIX_OFFSET(Insertion, transform),
				"transform" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1088BE60
	content::MemberList* NIS::Placement::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<Placement, 0>(true, true, "p"), ENGINE_NAME_OFFSET(Placement, object),
				"object" },
			{ content::GetMatrixMetaType<Placement>(false, false, "p"), ENGINE_MATRIX_OFFSET(Placement, transform),
				"transform" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1088BF10
	content::MemberList* NIS::Animation::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<Animation, 0>(true, true, "p"), ENGINE_NAME_OFFSET(Animation, animation),
				"animation" },
			{ content::GetMemberNameMetaType<Animation, 1>(true, true, "p"), ENGINE_NAME_OFFSET(Animation, object),
				"object" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1088BFC0
	content::MemberList* NIS::Attachment::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<Attachment, 0>(true, true, "p"), ENGINE_NAME_OFFSET(Attachment, parent),
				"parent" },
			{ content::GetMemberNameMetaType<Attachment, 1>(true, true, "p"),
				ENGINE_NAME_OFFSET(Attachment, parentJoint), "parentJoint" },
			{ content::GetMemberNameMetaType<Attachment, 2>(true, true, "p"), ENGINE_NAME_OFFSET(Attachment, child),
				"child" },
			{ content::GetMatrixMetaType<Attachment>(false, false, "p"),
				ENGINE_MATRIX_OFFSET(Attachment, childTransform), "childTransform" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1088C0D0
	content::MemberList* NIS::LightGroup::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<LightGroup, 0>(true, true, "p"),
				ENGINE_NAME_OFFSET(LightGroup, lightGroupName), "lightGroupName" },
			{ content::GetMemberNameMetaType<LightGroup, 1>(true, true, "p"), ENGINE_NAME_OFFSET(LightGroup, object),
				"object" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1088E270
	content::MemberList* NIS::SubTitle::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<SubTitle, 0>(true, true, "p"), ENGINE_NAME_OFFSET(SubTitle, subTitleId),
				"subTitleId" },
			{ content::GetMemberPrimitiveMetaType<SubTitle, float, 0>("p"), ENGINE_OFFSET(SubTitle, timeBegin),
				"timeBegin" },
			{ content::GetMemberPrimitiveMetaType<SubTitle, float, 1>("p"), ENGINE_OFFSET(SubTitle, timeEnd),
				"timeEnd" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1088EF60
	content::MemberList* NIS::Visibility::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<Visibility, 0>(true, true, "p"), ENGINE_NAME_OFFSET(Visibility, object),
				"object" },
			{ content::GetMemberPrimitiveMetaType<Visibility, bool, 0>("p"),
				ENGINE_OFFSET(Visibility, startVisibility), "startVisibility" },
			{ content::GetArrayDynamicMetaType<Visibility, FloatArray>(
				content::GetMemberPrimitiveMetaType<Visibility, float, 0>("p"), "p"),
				ENGINE_OFFSET(Visibility, keys), "keys" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1088FAC0
	content::MemberList* NIS::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<NIS, InsertionArray>(content::GetClassMetaType<Insertion>(), "p"),
				ENGINE_OFFSET(NIS, insertions), "insertions" },
			{ content::GetArrayDynamicMetaType<NIS, PlacementArray>(content::GetClassMetaType<Placement>(), "p"),
				ENGINE_OFFSET(NIS, placements), "placements" },
			{ content::GetArrayDynamicMetaType<NIS, AnimationArray>(content::GetClassMetaType<Animation>(), "p"),
				ENGINE_OFFSET(NIS, animations), "animations" },
			{ content::GetArrayDynamicMetaType<NIS, AttachmentArray>(content::GetClassMetaType<Attachment>(), "p"),
				ENGINE_OFFSET(NIS, attachments), "attachments" },
			{ content::GetArrayDynamicMetaType<NIS, VisibilityArray>(content::GetClassMetaType<Visibility>(), "p"),
				ENGINE_OFFSET(NIS, visibilities), "visibilities" },
			{ content::GetArrayDynamicMetaType<NIS, LightGroupArray>(content::GetClassMetaType<LightGroup>(), "p"),
				ENGINE_OFFSET(NIS, lightGroups), "lightGroups" },
			{ content::GetArrayDynamicMetaType<NIS, SubTitleArray>(content::GetClassMetaType<SubTitle>(), "p"),
				ENGINE_OFFSET(NIS, subTitles), "subTitles" },
			{ content::GetArrayDynamicMetaType<NIS, FloatArray>(
				content::GetMemberPrimitiveMetaType<NIS, float, 0>("p"), "p"),
				ENGINE_OFFSET(NIS, timeSlices), "timeSlices" },
			{ content::GetArrayDynamicMetaType<ShotBoundariesTag, FloatArray>(
				content::GetMemberPrimitiveMetaType<NIS, float, 1>("p"), "p"),
				ENGINE_OFFSET(NIS, shotBoundaries), "shotBoundaries" },
			{ content::GetMemberPrimitiveMetaType<NIS, float, 2>("p"), ENGINE_OFFSET(NIS, exclusionRadius),
				"exclusionRadius" }
		};
		sList.members = sMembers;
		sList.count = 10;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1088C940
	NIS::Insertion::Insertion()
	{
		transform.SetIdentity();
	}

	// FUNCTION: ENGINE 0x1088CBE0
	NIS::Placement::Placement()
	{
		transform.SetIdentity();
	}

	// FUNCTION: ENGINE 0x1088D050
	NIS::Attachment::Attachment()
	{
		childTransform.SetIdentity();
	}

}

namespace container
{
	// The insertion of one element of the scene arrays runs the fill
	template<> engine::NIS::Insertion* ArrayDynamic<engine::NIS::Insertion, AllocatorNew>::Insert(engine::NIS::Insertion* position,
		const engine::NIS::Insertion& value)
	{
		return Insert(position, 1, value);
	}
	template<> engine::NIS::Placement* ArrayDynamic<engine::NIS::Placement, AllocatorNew>::Insert(engine::NIS::Placement* position,
		const engine::NIS::Placement& value)
	{
		return Insert(position, 1, value);
	}
	template<> engine::NIS::Animation* ArrayDynamic<engine::NIS::Animation, AllocatorNew>::Insert(engine::NIS::Animation* position,
		const engine::NIS::Animation& value)
	{
		return Insert(position, 1, value);
	}
	template<> engine::NIS::Attachment* ArrayDynamic<engine::NIS::Attachment, AllocatorNew>::Insert(engine::NIS::Attachment* position,
		const engine::NIS::Attachment& value)
	{
		return Insert(position, 1, value);
	}
	template<> engine::NIS::Visibility* ArrayDynamic<engine::NIS::Visibility, AllocatorNew>::Insert(engine::NIS::Visibility* position,
		const engine::NIS::Visibility& value)
	{
		return Insert(position, 1, value);
	}
	template<> engine::NIS::LightGroup* ArrayDynamic<engine::NIS::LightGroup, AllocatorNew>::Insert(engine::NIS::LightGroup* position,
		const engine::NIS::LightGroup& value)
	{
		return Insert(position, 1, value);
	}
}

namespace container
{
	template class ArrayDynamic<float, AllocatorNew>;
	template class ArrayDynamic<engine::NIS::Insertion, AllocatorNew>;
	template class ArrayDynamic<engine::NIS::Placement, AllocatorNew>;
	template class ArrayDynamic<engine::NIS::Animation, AllocatorNew>;
	template class ArrayDynamic<engine::NIS::Attachment, AllocatorNew>;
	template class ArrayDynamic<engine::NIS::Visibility, AllocatorNew>;
	template class ArrayDynamic<engine::NIS::LightGroup, AllocatorNew>;
	template class ArrayDynamic<engine::NIS::SubTitle, AllocatorNew>;
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1088B940
// FUNCTION: ENGINE 0x1088B980
// FUNCTION: ENGINE 0x1088B9C0
// FUNCTION: ENGINE 0x1088BA00
// FUNCTION: ENGINE 0x1088BA40
// FUNCTION: ENGINE 0x1088BA80
// FUNCTION: ENGINE 0x1088BAC0
// FUNCTION: ENGINE 0x1088BB00
// FUNCTION: ENGINE 0x1088BB40
// FUNCTION: ENGINE 0x1088BB80
// FUNCTION: ENGINE 0x1088BBC0
// FUNCTION: ENGINE 0x1088BC00
// FUNCTION: ENGINE 0x1088BC40
// FUNCTION: ENGINE 0x1088BC50
// FUNCTION: ENGINE 0x1088BC90
// FUNCTION: ENGINE 0x1088BCD0
// FUNCTION: ENGINE 0x1088BD10
// FUNCTION: ENGINE 0x1088BD20
// FUNCTION: ENGINE 0x1088BD30
// FUNCTION: ENGINE 0x1088BD40
// FUNCTION: ENGINE 0x1088BD50
// FUNCTION: ENGINE 0x1088BD60
// FUNCTION: ENGINE 0x1088BD70
// FUNCTION: ENGINE 0x1088C3C0
// FUNCTION: ENGINE 0x1088C410
// FUNCTION: ENGINE 0x1088C460
// FUNCTION: ENGINE 0x1088C4B0
// FUNCTION: ENGINE 0x1088C500
// FUNCTION: ENGINE 0x1088C550
// FUNCTION: ENGINE 0x1088C590
// FUNCTION: ENGINE 0x1088C5D0
// FUNCTION: ENGINE 0x1088C610
// FUNCTION: ENGINE 0x1088C650
// FUNCTION: ENGINE 0x1088C690
// FUNCTION: ENGINE 0x1088C6D0
// FUNCTION: ENGINE 0x1088C710
// FUNCTION: ENGINE 0x1088C720
// FUNCTION: ENGINE 0x1088C740
// FUNCTION: ENGINE 0x1088C750
// FUNCTION: ENGINE 0x1088C760
// FUNCTION: ENGINE 0x1088C780
// FUNCTION: ENGINE 0x1088C790
// FUNCTION: ENGINE 0x1088C7E0
// FUNCTION: ENGINE 0x1088C830
// FUNCTION: ENGINE 0x1088C860
// FUNCTION: ENGINE 0x1088C8D0
// FUNCTION: ENGINE 0x1088C910
// FUNCTION: ENGINE 0x1088CA30
// FUNCTION: ENGINE 0x1088CA40
// FUNCTION: ENGINE 0x1088CA90
// FUNCTION: ENGINE 0x1088CAE0
// FUNCTION: ENGINE 0x1088CB10
// FUNCTION: ENGINE 0x1088CB80
// FUNCTION: ENGINE 0x1088CBB0
// FUNCTION: ENGINE 0x1088CCC0
// FUNCTION: ENGINE 0x1088CD20
// FUNCTION: ENGINE 0x1088CE70
// FUNCTION: ENGINE 0x1088CE80
// FUNCTION: ENGINE 0x1088CED0
// FUNCTION: ENGINE 0x1088CF20
// FUNCTION: ENGINE 0x1088CF50
// FUNCTION: ENGINE 0x1088CFC0
// FUNCTION: ENGINE 0x1088D010
// FUNCTION: ENGINE 0x1088D140
// FUNCTION: ENGINE 0x1088D150
// FUNCTION: ENGINE 0x1088D1A0
// FUNCTION: ENGINE 0x1088D1F0
// FUNCTION: ENGINE 0x1088D210
// FUNCTION: ENGINE 0x1088D290
// FUNCTION: ENGINE 0x1088D2C0
// FUNCTION: ENGINE 0x1088D320
// FUNCTION: ENGINE 0x1088D470
// FUNCTION: ENGINE 0x1088D4D0
// FUNCTION: ENGINE 0x1088D570
// FUNCTION: ENGINE 0x1088D5B0
// FUNCTION: ENGINE 0x1088D5E0
// FUNCTION: ENGINE 0x1088D610
// FUNCTION: ENGINE 0x1088D620
// FUNCTION: ENGINE 0x1088D630
// FUNCTION: ENGINE 0x1088D640
// FUNCTION: ENGINE 0x1088D650
// FUNCTION: ENGINE 0x1088D670
// FUNCTION: ENGINE 0x1088D690
// FUNCTION: ENGINE 0x1088D6B0
// FUNCTION: ENGINE 0x1088D6D0
// FUNCTION: ENGINE 0x1088D6F0
// FUNCTION: ENGINE 0x1088D710
// FUNCTION: ENGINE 0x1088D730
// FUNCTION: ENGINE 0x1088D750
// FUNCTION: ENGINE 0x1088D760
// FUNCTION: ENGINE 0x1088D770
// FUNCTION: ENGINE 0x1088D780
// FUNCTION: ENGINE 0x1088D790
// FUNCTION: ENGINE 0x1088D7B0
// FUNCTION: ENGINE 0x1088D7C0
// FUNCTION: ENGINE 0x1088D7D0
// FUNCTION: ENGINE 0x1088D7F0
// FUNCTION: ENGINE 0x1088D800
// FUNCTION: ENGINE 0x1088D810
// FUNCTION: ENGINE 0x1088D820
// FUNCTION: ENGINE 0x1088D830
// FUNCTION: ENGINE 0x1088D840
// FUNCTION: ENGINE 0x1088D850
// FUNCTION: ENGINE 0x1088D860
// FUNCTION: ENGINE 0x1088D870
// FUNCTION: ENGINE 0x1088D880
// FUNCTION: ENGINE 0x1088D890
// FUNCTION: ENGINE 0x1088D8A0
// FUNCTION: ENGINE 0x1088D910
// FUNCTION: ENGINE 0x1088D9A0
// FUNCTION: ENGINE 0x1088D9E0
// FUNCTION: ENGINE 0x1088DAA0
// FUNCTION: ENGINE 0x1088DAD0
// FUNCTION: ENGINE 0x1088DBB0
// FUNCTION: ENGINE 0x1088DBF0
// FUNCTION: ENGINE 0x1088DC40
// FUNCTION: ENGINE 0x1088DD40
// FUNCTION: ENGINE 0x1088DD80
// FUNCTION: ENGINE 0x1088DDB0
// FUNCTION: ENGINE 0x1088DDF0
// FUNCTION: ENGINE 0x1088DEB0
// FUNCTION: ENGINE 0x1088DF60
// FUNCTION: ENGINE 0x1088DFB0
// FUNCTION: ENGINE 0x1088E080
// FUNCTION: ENGINE 0x1088E0D0
// FUNCTION: ENGINE 0x1088E1A0
// FUNCTION: ENGINE 0x1088E350
// FUNCTION: ENGINE 0x1088E3A0
// FUNCTION: ENGINE 0x1088E3F0
// FUNCTION: ENGINE 0x1088E440
// FUNCTION: ENGINE 0x1088E490
// FUNCTION: ENGINE 0x1088E4E0
// FUNCTION: ENGINE 0x1088E530
// FUNCTION: ENGINE 0x1088E580
// FUNCTION: ENGINE 0x1088E5D0
// FUNCTION: ENGINE 0x1088E620
// FUNCTION: ENGINE 0x1088E670
// FUNCTION: ENGINE 0x1088E720
// FUNCTION: ENGINE 0x1088E760
// FUNCTION: ENGINE 0x1088E790
// FUNCTION: ENGINE 0x1088E7F0
// FUNCTION: ENGINE 0x1088E820
// FUNCTION: ENGINE 0x1088E9B0
// FUNCTION: ENGINE 0x1088ECA0
// FUNCTION: ENGINE 0x1088ED30
// FUNCTION: ENGINE 0x1088EDB0
// FUNCTION: ENGINE 0x1088EE00
// FUNCTION: ENGINE 0x1088EE90
// FUNCTION: ENGINE 0x1088EEE0
// FUNCTION: ENGINE 0x1088EF30
// FUNCTION: ENGINE 0x1088F0C0
// FUNCTION: ENGINE 0x1088F110
// FUNCTION: ENGINE 0x1088F150
// FUNCTION: ENGINE 0x1088F180
// FUNCTION: ENGINE 0x1088F1B0
// FUNCTION: ENGINE 0x1088F1E0
// FUNCTION: ENGINE 0x1088F210
// FUNCTION: ENGINE 0x1088F240
// FUNCTION: ENGINE 0x1088F270
// FUNCTION: ENGINE 0x1088F380
// FUNCTION: ENGINE 0x1088F480
// FUNCTION: ENGINE 0x1088F550
// FUNCTION: ENGINE 0x1088F6B0
// FUNCTION: ENGINE 0x1088F780
// FUNCTION: ENGINE 0x1088F850
// FUNCTION: ENGINE 0x1088F870
// FUNCTION: ENGINE 0x1088F890
// FUNCTION: ENGINE 0x1088F8D0
// FUNCTION: ENGINE 0x1088F950
// FUNCTION: ENGINE 0x1088F9D0
// FUNCTION: ENGINE 0x1088FA10
// FUNCTION: ENGINE 0x1088FA60
// FUNCTION: ENGINE 0x1088FA90
// FUNCTION: ENGINE 0x1088FD10
// FUNCTION: ENGINE 0x1088FD80
// FUNCTION: ENGINE 0x1088FDE0
// FUNCTION: ENGINE 0x1088FE40
// FUNCTION: ENGINE 0x1088FE80
// FUNCTION: ENGINE 0x1088FF10
// FUNCTION: ENGINE 0x1088FF50
// FUNCTION: ENGINE 0x1088FF90
// FUNCTION: ENGINE 0x1088FFC0
// FUNCTION: ENGINE 0x10890020
// FUNCTION: ENGINE 0x108900B0
// FUNCTION: ENGINE 0x108900D0
// FUNCTION: ENGINE 0x10890100
// FUNCTION: ENGINE 0x10890150
// FUNCTION: ENGINE 0x10890180
// FUNCTION: ENGINE 0x10890220
// FUNCTION: ENGINE 0x108902C0
// FUNCTION: ENGINE 0x10890350
// FUNCTION: ENGINE 0x108903F0
// FUNCTION: ENGINE 0x10890480
// FUNCTION: ENGINE 0x10890520
// FUNCTION: ENGINE 0x108905B0
// FUNCTION: ENGINE 0x108905F0
// FUNCTION: ENGINE 0x10890650
// FUNCTION: ENGINE 0x10890690
// FUNCTION: ENGINE 0x10890770
// FUNCTION: ENGINE 0x108907B0
// FUNCTION: ENGINE 0x108907F0
// FUNCTION: ENGINE 0x10890820

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1088C730
// FUNCTION: ENGINE 0x1088C850
// FUNCTION: ENGINE 0x1088C880
// FUNCTION: ENGINE 0x1088C890
// FUNCTION: ENGINE 0x1088C8B0
// FUNCTION: ENGINE 0x1088CB00
// FUNCTION: ENGINE 0x1088CB30
// FUNCTION: ENGINE 0x1088CB40
// FUNCTION: ENGINE 0x1088CB60
// FUNCTION: ENGINE 0x1088CCD0
// FUNCTION: ENGINE 0x1088CD70
// FUNCTION: ENGINE 0x1088CD80
// FUNCTION: ENGINE 0x1088CD90
// FUNCTION: ENGINE 0x1088CDA0
// FUNCTION: ENGINE 0x1088CDB0
// FUNCTION: ENGINE 0x1088CDC0
// FUNCTION: ENGINE 0x1088CDF0
// FUNCTION: ENGINE 0x1088CE10
// FUNCTION: ENGINE 0x1088CE40
// FUNCTION: ENGINE 0x1088CF40
// FUNCTION: ENGINE 0x1088CF70
// FUNCTION: ENGINE 0x1088CF80
// FUNCTION: ENGINE 0x1088CFA0
// FUNCTION: ENGINE 0x1088D200
// FUNCTION: ENGINE 0x1088D220
// FUNCTION: ENGINE 0x1088D230
// FUNCTION: ENGINE 0x1088D240
// FUNCTION: ENGINE 0x1088D260
// FUNCTION: ENGINE 0x1088D2D0
// FUNCTION: ENGINE 0x1088D370
// FUNCTION: ENGINE 0x1088D380
// FUNCTION: ENGINE 0x1088D390
// FUNCTION: ENGINE 0x1088D3A0
// FUNCTION: ENGINE 0x1088D3B0
// FUNCTION: ENGINE 0x1088D3C0
// FUNCTION: ENGINE 0x1088D3F0
// FUNCTION: ENGINE 0x1088D410
// FUNCTION: ENGINE 0x1088D440
// FUNCTION: ENGINE 0x1088D480
// FUNCTION: ENGINE 0x1088D520
// FUNCTION: ENGINE 0x1088D540
// FUNCTION: ENGINE 0x1088D550
// FUNCTION: ENGINE 0x1088D560
// FUNCTION: ENGINE 0x1088D590
// FUNCTION: ENGINE 0x1088D8E0
// FUNCTION: ENGINE 0x1088DB80
// FUNCTION: ENGINE 0x1088DD10
// FUNCTION: ENGINE 0x1088E7C0
// FUNCTION: ENGINE 0x1088E980
// FUNCTION: ENGINE 0x1088EB20
// FUNCTION: ENGINE 0x1088EB50
// FUNCTION: ENGINE 0x1088EB80
// FUNCTION: ENGINE 0x1088EBB0
// FUNCTION: ENGINE 0x1088EC40
// FUNCTION: ENGINE 0x1088EC70
// FUNCTION: ENGINE 0x1088F910
// FUNCTION: ENGINE 0x1088F990
// FUNCTION: ENGINE 0x1088FFF0
// FUNCTION: ENGINE 0x10890050
