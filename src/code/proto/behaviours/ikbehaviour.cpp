#include "code/proto/behaviours/ikbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10071830
	IKLimbInfo::IKLimbInfo()
	{
		velocity = engine::driving::gTwo;
		enabled = true;
		positionOffsetMin = -0.375f;
		surfaceFixup = true;
		positionOffsetMax = 0.375f;
		endEffectorRotation = true;
		endEffectorFollowSurfaceNormal = true;
		surfaceNormalAngularVelocity = 1.5707964f;
		surfaceNormalMaxAngle = 0.3926991f;
	}

	// FUNCTION: ENGINE 0x10074B60
	// EQUIVALENT: the constants are loaded once and the stores of the array's words come first (33 %)
	IKSupportingLimbInfo::IKSupportingLimbInfo()
	{
		float one = engine::driving::gOne;
		enabled = true;
		surfaceFixup = true;
		balanceRootPositionOffsetMin = -0.5f;
		float half = engine::driving::gHalf;
		balanceRootVelocity = one;
		balanceRootCorrectionFraction = one;
		balanceRootPositionOffsetMax = half;
		balanceRootDistanceToMinLimb = one;
		balanceRootDistanceToMaxLimb = one;
	}

	// FUNCTION: ENGINE 0x10071000
	content::ClassInfo* IKLimbInfo::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::IKLimbInfo";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10071040
	content::ClassInfo* IKSupportingLimbInfo::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::IKSupportingLimbInfo";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10071080
	content::ClassInfo* IKBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::IKBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10073AC0
	content::MemberList* IKLimbInfo::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<IKLimbInfo>(true, true, "pn"), PROTO_NAME_OFFSET(IKLimbInfo, limbName),
				"limbName" },
			{ content::GetMemberPrimitiveMetaType<IKLimbInfo, bool, 0>("pn"), PROTO_OFFSET(IKLimbInfo, enabled),
				"enabled" },
			{ content::GetMemberPrimitiveMetaType<IKLimbInfo, bool, 1>("pn"), PROTO_OFFSET(IKLimbInfo, surfaceFixup),
				"surfaceFixup" },
			{ content::GetMemberPrimitiveMetaType<IKLimbInfo, bool, 2>("pn"),
				PROTO_OFFSET(IKLimbInfo, endEffectorRotation), "endEffectorRotation" },
			{ content::GetMemberPrimitiveMetaType<IKLimbInfo, bool, 3>("pn"),
				PROTO_OFFSET(IKLimbInfo, endEffectorFollowSurfaceNormal), "endEffectorFollowSurfaceNormal" },
			{ content::GetMemberPrimitiveMetaType<IKLimbInfo, float, 0>("pn"), PROTO_OFFSET(IKLimbInfo, velocity),
				"velocity" },
			{ content::GetMemberPrimitiveMetaType<IKLimbInfo, float, 1>("pn"),
				PROTO_OFFSET(IKLimbInfo, positionOffsetMin), "positionOffsetMin" },
			{ content::GetMemberPrimitiveMetaType<IKLimbInfo, float, 2>("pn"),
				PROTO_OFFSET(IKLimbInfo, positionOffsetMax), "positionOffsetMax" },
			{ content::GetMemberPrimitiveMetaType<IKLimbInfo, float, 3>("pn"),
				PROTO_OFFSET(IKLimbInfo, surfaceNormalAngularVelocity), "surfaceNormalAngularVelocity" },
			{ content::GetMemberPrimitiveMetaType<IKLimbInfo, float, 4>("pn"),
				PROTO_OFFSET(IKLimbInfo, surfaceNormalMaxAngle), "surfaceNormalMaxAngle" }
		};
		sList.members = sMembers;
		sList.count = 10;
		return &sList;
	}

	// FUNCTION: ENGINE 0x100741E0
	content::MemberList* IKSupportingLimbInfo::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<IKSupportingLimbInfo>(true, true, "pn"),
				PROTO_NAME_OFFSET(IKSupportingLimbInfo, supportingLimbName), "supportingLimbName" },
			{ content::GetMemberPrimitiveMetaType<IKSupportingLimbInfo, bool, 0>("pn"),
				PROTO_OFFSET(IKSupportingLimbInfo, enabled), "enabled" },
			{ content::GetMemberPrimitiveMetaType<IKSupportingLimbInfo, bool, 1>("pn"),
				PROTO_OFFSET(IKSupportingLimbInfo, surfaceFixup), "surfaceFixup" },
			{ content::GetMemberPrimitiveMetaType<IKSupportingLimbInfo, float, 0>("pn"),
				PROTO_OFFSET(IKSupportingLimbInfo, balanceRootVelocity), "balanceRootVelocity" },
			{ content::GetMemberPrimitiveMetaType<IKSupportingLimbInfo, float, 1>("pn"),
				PROTO_OFFSET(IKSupportingLimbInfo, balanceRootCorrectionFraction), "balanceRootCorrectionFraction" },
			{ content::GetMemberPrimitiveMetaType<IKSupportingLimbInfo, float, 2>("pn"),
				PROTO_OFFSET(IKSupportingLimbInfo, balanceRootPositionOffsetMin), "balanceRootPositionOffsetMin" },
			{ content::GetMemberPrimitiveMetaType<IKSupportingLimbInfo, float, 3>("pn"),
				PROTO_OFFSET(IKSupportingLimbInfo, balanceRootPositionOffsetMax), "balanceRootPositionOffsetMax" },
			{ content::GetMemberPrimitiveMetaType<IKSupportingLimbInfo, float, 4>("pn"),
				PROTO_OFFSET(IKSupportingLimbInfo, balanceRootDistanceToMinLimb), "balanceRootDistanceToMinLimb" },
			{ content::GetMemberPrimitiveMetaType<IKSupportingLimbInfo, float, 5>("pn"),
				PROTO_OFFSET(IKSupportingLimbInfo, balanceRootDistanceToMaxLimb), "balanceRootDistanceToMaxLimb" },
			{ content::GetArrayDynamicMetaType<IKSupportingLimbInfo, LimbArray>(
				content::GetClassMetaType<IKLimbInfo>(), "pn"),
				PROTO_OFFSET(IKSupportingLimbInfo, ikLimbInfoList), "ikLimbInfoList" }
		};
		sList.members = sMembers;
		sList.count = 10;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10071150
	void IKBehaviour::OnPostedMessage(engine::Message* message)
	{
		if (message->type == 0xf && message->id == 0xb)
		{
			((unsigned char*)message)[0xc] = 1;
		}
	}

	// FUNCTION: ENGINE 0x100747C0
	content::MemberList* IKBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, IKBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<IKBehaviour, int, 0>("pn"),
				PROTO_OFFSET(IKBehaviour, surfaceFixup), "surfaceFixup" },
			{ content::GetMemberPrimitiveMetaType<IKBehaviour, unsigned int, 0>("pn"),
				PROTO_OFFSET(IKBehaviour, balanceRootJointIndex), "balanceRootJointIndex" },
			{ content::GetArrayDynamicMetaType<IKBehaviour, SupportingLimbArray>(
				content::GetClassMetaType<IKSupportingLimbInfo>(), "pn"),
				PROTO_OFFSET(IKBehaviour, ikSupportingLimbInfoList), "ikSupportingLimbInfoList" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10071170
// FUNCTION: ENGINE 0x10071190
// FUNCTION: ENGINE 0x100711F0
// FUNCTION: ENGINE 0x10071250
// FUNCTION: ENGINE 0x10071260
// FUNCTION: ENGINE 0x100712F0
// FUNCTION: ENGINE 0x10071330
// FUNCTION: ENGINE 0x10071370
// FUNCTION: ENGINE 0x100713B0
// FUNCTION: ENGINE 0x100713C0
// FUNCTION: ENGINE 0x100713D0
// FUNCTION: ENGINE 0x100713E0
// FUNCTION: ENGINE 0x10071780
// FUNCTION: ENGINE 0x10071790
// FUNCTION: ENGINE 0x100718B0
// FUNCTION: ENGINE 0x100718C0
// FUNCTION: ENGINE 0x10073050
// FUNCTION: ENGINE 0x10073070
// FUNCTION: ENGINE 0x100730B0
// FUNCTION: ENGINE 0x100730F0
// FUNCTION: ENGINE 0x10073130
// FUNCTION: ENGINE 0x10073170
// FUNCTION: ENGINE 0x100731B0
// FUNCTION: ENGINE 0x100731F0
// FUNCTION: ENGINE 0x10073230
// FUNCTION: ENGINE 0x10073270
// FUNCTION: ENGINE 0x100732B0
// FUNCTION: ENGINE 0x100732F0
// FUNCTION: ENGINE 0x10073330
// FUNCTION: ENGINE 0x10073370
// FUNCTION: ENGINE 0x100733B0
// FUNCTION: ENGINE 0x100733F0
// FUNCTION: ENGINE 0x10073430
// FUNCTION: ENGINE 0x10073470
// FUNCTION: ENGINE 0x100734B0
// FUNCTION: ENGINE 0x100734F0
// FUNCTION: ENGINE 0x10073530
// FUNCTION: ENGINE 0x10073540
// FUNCTION: ENGINE 0x10073560
// FUNCTION: ENGINE 0x10073580
// FUNCTION: ENGINE 0x100735E0
// FUNCTION: ENGINE 0x10073610
// FUNCTION: ENGINE 0x10073670
// FUNCTION: ENGINE 0x10073680
// FUNCTION: ENGINE 0x100736B0
// FUNCTION: ENGINE 0x100736E0
// FUNCTION: ENGINE 0x10073760
// FUNCTION: ENGINE 0x10073780
// FUNCTION: ENGINE 0x100737E0
// FUNCTION: ENGINE 0x10073800
// FUNCTION: ENGINE 0x10073840
// FUNCTION: ENGINE 0x10073860
// FUNCTION: ENGINE 0x100738F0
// FUNCTION: ENGINE 0x100739A0
// FUNCTION: ENGINE 0x10073A30
// FUNCTION: ENGINE 0x10073D20
// FUNCTION: ENGINE 0x10073D80
// FUNCTION: ENGINE 0x10073DE0
// FUNCTION: ENGINE 0x10073F60
// FUNCTION: ENGINE 0x10073FF0
// FUNCTION: ENGINE 0x10074080
// FUNCTION: ENGINE 0x10074450
// FUNCTION: ENGINE 0x100744C0
// FUNCTION: ENGINE 0x10074590
// FUNCTION: ENGINE 0x100745C0
// FUNCTION: ENGINE 0x10074750
// FUNCTION: ENGINE 0x10074910
// FUNCTION: ENGINE 0x10074940
// FUNCTION: ENGINE 0x10074970
// FUNCTION: ENGINE 0x10074A00
// FUNCTION: ENGINE 0x10074A20
// FUNCTION: ENGINE 0x10074AB0
// FUNCTION: ENGINE 0x10074AF0
// FUNCTION: ENGINE 0x10074BD0
// FUNCTION: ENGINE 0x10074C80
// FUNCTION: ENGINE 0x10074CA0
// FUNCTION: ENGINE 0x10074CC0
// FUNCTION: ENGINE 0x10074D50
// FUNCTION: ENGINE 0x10074D90
// FUNCTION: ENGINE 0x10074E70
// FUNCTION: ENGINE 0x10074F40
// FUNCTION: ENGINE 0x10074FA0
// FUNCTION: ENGINE 0x100750E0
// FUNCTION: ENGINE 0x10075160
// FUNCTION: ENGINE 0x10075340

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10073ED0
