#include "code/proto/powers/whipfistpower.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace proto
{
	// FUNCTION: ENGINE 0x1008C9B0
	WhipFistSegment::WhipFistSegment() : unknown0(0.0f), unknown4(0.0f), unknown8(0.0f), unknownC(0.0f), unknown10(0.0f), unknown14(0.0f), unknown18(0.0f), drawable()
	{
	}

	// FUNCTION: ENGINE 0x1008C9F0
	WhipFistSegment::~WhipFistSegment()
	{
		if (drawable.IsValid())
		{
			engine::render::Drawable::Destroy(&drawable, 0);
		}
	}

	// FUNCTION: ENGINE 0x1008CA70
	WhipFistChain::WhipFistChain() : unknown0(0.0f), unknown4(0.0f), unknown8(0.0f), unknownC(0.0f), unknown10(0.0f), unknown14(0.0f), unknown18(0.0f), unknown1C(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x1008CFD0
	// NONMATCHING: scheduling, the engine zeroes the floats behind the handle with a second register (best 87.7 %)
#ifdef NONMATCHING
	WhipFistPower::WhipFistPower() : segments(0), segmentCount(100), unknown14(0), unknown18(0), unknown1C(0), unknown20(0), fixedSegmentCount(0), unknown28(-1), unknown2C(0.0f), segmentLength(engine::driving::gOne), unknown4C(0.0f), unknown50(0.0f), unknown54(0.0f), unknown58(0.0f), unknown5C(0.0f), unknown60(0.0f), unknown68(0.0f), unknown6C(0.0f), unknown70(0.0f), unknown74(false), unknown78(0.0f), unknown7C(0.0f), unknown80(0.0f), unknown84(0.0f), unknown88(0.0f), unknown8C(false), unknown90(0.0f), unknown94(0.0f), unknown98(0.0f), unknown9C(0.0f), unknownA0(0.0f), moveEndJoint(1), endJointRotationOffset(math::kZeroVector), unknown114(0xffff), unknown118(0xffff), unknown11C(0xffff), unknown120(0xffff), segmentDrawable(0), unknown128(0.0f)
	{
	}
#endif

	// FUNCTION: ENGINE 0x1008D190
	// NONMATCHING: scheduling, the engine loads the address of the handle member after the first float stores (best 95.4 %)
#ifdef NONMATCHING
	WhipFistPower::WhipFistPower(const WhipFistPower& other) : Power(other), segments(0), segmentCount(other.segmentCount), unknown14(0), unknown18(0), unknown1C(0), unknown20(0), fixedSegmentCount(other.fixedSegmentCount), unknown28(-1), unknown2C(0.0f), preStartJoint(other.preStartJoint), startJoint(other.startJoint), endJoint(other.endJoint), segmentLength(other.segmentLength), unknown4C(0.0f), unknown50(0.0f), unknown54(0.0f), unknown58(0.0f), unknown5C(0.0f), unknown60(0.0f), unknown68(0.0f), unknown6C(0.0f), unknown70(0.0f), unknown74(false), unknown78(0.0f), unknown7C(0.0f), unknown80(0.0f), unknown84(0.0f), unknown88(0.0f), unknown8C(false), unknown90(0.0f), unknown94(0.0f), unknown98(0.0f), unknown9C(0.0f), unknownA0(0.0f), moveEndJoint(1), endJointRotationOffset(other.endJointRotationOffset), unknown114(0xffff), unknown118(0xffff), unknown11C(0xffff), unknown120(0xffff), segmentDrawable(0), unknown128(other.unknown128)
	{
		unknownA4.Identity();
		core::RefAssign<core::IRefCount>((core::IRefCount*&)segmentDrawable, (core::IRefCount*)other.segmentDrawable);
	}
#endif

	// FUNCTION: ENGINE 0x1008D380
	WhipFistPower::~WhipFistPower()
	{
		if (segments != 0)
		{
			delete[] segments;
			segments = 0;
		}
		if (unknown20 != 0)
		{
			delete[] (char*)unknown20;
			unknown20 = 0;
		}
		core::SafeRelease<core::IRefCount>((core::IRefCount*&)segmentDrawable);
	}

	// FUNCTION: ENGINE 0x1008D420
	Power* WhipFistPower::Clone()
	{
		return new WhipFistPower(*this);
	}

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1008C970
	content::ClassInfo* WhipFistPower::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WhipFistPower";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1008CB30
	bool WhipFistPower::GetMessageMask(unsigned int* mask)
	{
		*mask = 0x1e;
		return true;
	}

	// FUNCTION: ENGINE 0x1008EB80
	content::MemberList* WhipFistPower::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Power>();
		static content::BaseClassCasterImpl<Power, WhipFistPower> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<WhipFistPower, int, 0>("p"),
				PROTO_OFFSET(WhipFistPower, segmentCount), "segmentCount" },
			{ content::GetMemberPrimitiveMetaType<WhipFistPower, float, 0>("p"),
				PROTO_OFFSET(WhipFistPower, segmentLength), "segmentLength" },
			{ content::GetReferenceMetaType<WhipFistPower, engine::render::DrawableArchetype>("p"),
				PROTO_OFFSET(WhipFistPower, segmentDrawable), "segmentDrawable" },
			{ content::GetNameMetaType<WhipFistPower>(true, true, "p"),
				PROTO_NAME_OFFSET(WhipFistPower, preStartJoint), "preStartJoint" },
			{ content::GetNameMetaTypeCopy<WhipFistPower>(true, true, "p"),
				PROTO_NAME_OFFSET(WhipFistPower, startJoint), "startJoint" },
			{ content::GetMemberNameMetaType<WhipFistPower, 1>(true, true, "p"),
				PROTO_NAME_OFFSET(WhipFistPower, endJoint), "endJoint" },
			{ content::GetMemberVectorMetaType<WhipFistPower, 0>("p"), 0xe8, "endJointRotationOffset" },
			{ content::GetMemberPrimitiveMetaType<WhipFistPower, int, 1>("p"),
				PROTO_OFFSET(WhipFistPower, fixedSegmentCount), "fixedSegmentCount" },
			{ content::GetMemberPrimitiveMetaType<WhipFistPower, int, 2>("p"),
				PROTO_OFFSET(WhipFistPower, moveEndJoint), "moveEndJoint" }
		};
		sList.members = sMembers;
		sList.count = 9;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1008CC50
// FUNCTION: ENGINE 0x1008CC60
// FUNCTION: ENGINE 0x1008CCA0
// FUNCTION: ENGINE 0x1008CCE0
// FUNCTION: ENGINE 0x1008CD20
// FUNCTION: ENGINE 0x1008CF90
// FUNCTION: ENGINE 0x1008CFA0
// FUNCTION: ENGINE 0x1008DEE0
// FUNCTION: ENGINE 0x1008DF20
// FUNCTION: ENGINE 0x1008DF60
// FUNCTION: ENGINE 0x1008DFA0
// FUNCTION: ENGINE 0x1008EB20

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1008CAB0
// FUNCTION: ENGINE 0x1008CDA0
// FUNCTION: ENGINE 0x1008E010
