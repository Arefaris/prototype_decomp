#include "code/proto/behaviours/anchortogroundbehaviour.h"

namespace engine
{
	extern content::ObjectName gPhysicsObjectAttributeName;
}

namespace proto
{
	extern content::ObjectName gDrawableAttributeName;

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10061490
	AnchorToGroundBehaviour::AnchorToGroundBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		physicsObjectAttribute(0), drawableAttribute(0), offset(math::kZeroVector), unknown20(math::kZeroVector),
		unknown2C(math::kZeroVector), stayAnchored(false), anchorToJointOrientationOffset(0.0f)
	{
		Listen(0x2f, true);
		Listen(2, true);
		Listen(0x1a, true);
	}

	// FUNCTION: ENGINE 0x100610C0
	AnchorToGroundBehaviour::~AnchorToGroundBehaviour()
	{
		ReleaseConstraints();
	}

	// FUNCTION: ENGINE 0x10061A30
	void AnchorToGroundBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 0x2f:
			switch ((unsigned short)message->id)
			{
			case 0xe:
				ApplyAnchor(static_cast<AnchorToGroundStateChangeMessage*>(message)->anchor,
					static_cast<AnchorToGroundStateChangeMessage*>(message)->zeroHeight);
				break;
			case 0xf:
				static_cast<IsAnchoredStateChangeMessage*>(message)->anchored = ballInSocketHandle.IsValid();
				break;
			}
			break;
		case 0x1a:
			if (stayAnchored)
			{
				ApplyAnchor(true, false);
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x100615D0
	void AnchorToGroundBehaviour::Slot1()
	{
		physicsObjectAttribute = owner->FindAttribute(engine::gPhysicsObjectAttributeName);
		drawableAttribute = owner->FindAttribute(gDrawableAttributeName);
	}

	// FUNCTION: ENGINE 0x10060430
	void AnchorToGroundBehaviour::OnActiveChanged(bool active)
	{
		engine::Behaviour::OnActiveChanged(active);
	}

	// FUNCTION: ENGINE 0x10060440
	void AnchorToGroundBehaviour::Update(float dt, unsigned short mask)
	{
	}

	// FUNCTION: ENGINE 0x100603D0
	content::ClassInfo* AnchorToGroundBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AnchorToGroundBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10061360
	content::MemberList* AnchorToGroundBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, AnchorToGroundBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<AnchorToGroundBehaviour, 0>("p"),
				0x14, "offset" },
			{ content::GetMemberPrimitiveMetaType<AnchorToGroundBehaviour, bool, 0>("p"),
				PROTO_OFFSET(AnchorToGroundBehaviour, stayAnchored), "stayAnchored" },
			{ content::GetMemberPrimitiveMetaType<AnchorToGroundBehaviour, float, 0>("p"),
				PROTO_OFFSET(AnchorToGroundBehaviour, anchorToJointOrientationOffset), "anchorToJointOrientationOffset" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10060180
// FUNCTION: ENGINE 0x10060410
// FUNCTION: ENGINE 0x10060610
// FUNCTION: ENGINE 0x10060670
// FUNCTION: ENGINE 0x100606C0
// FUNCTION: ENGINE 0x100606D0
// FUNCTION: ENGINE 0x100606E0
// FUNCTION: ENGINE 0x10060AC0
// FUNCTION: ENGINE 0x10061060
// FUNCTION: ENGINE 0x10061070
// FUNCTION: ENGINE 0x10061240
// FUNCTION: ENGINE 0x10061280

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10060420
// FUNCTION: ENGINE 0x100610F0
// FUNCTION: ENGINE 0x100615A0
