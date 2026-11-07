#include "code/proto/behaviours/shoulderconfixupbehaviour.h"
#include "code/core/refptr.h"
#include "code/engine/attributemessage.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/nis/nis.h"
#include "code/engine/physics/ragdollmessages.h"
#include "code/proto/fightitems/motion/motionmessages3.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10076370
	content::ClassInfo* ShoulderConFixupPropertiesJointPair::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ShoulderConFixupPropertiesJointPair";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x100763B0
	content::ClassInfo* ShoulderConFixupProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ShoulderConFixupProperties";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x100763F0
	content::ClassInfo* ShoulderConFixupBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ShoulderConFixupBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x100767D0
	ShoulderConFixupPropertiesJointPair::ShoulderConFixupPropertiesJointPair()
	{
	}

	// FUNCTION: ENGINE 0x10076440
	ShoulderConFixupPartIndices::ShoulderConFixupPartIndices() : shoulderJoint(0xffff), shoulderConJoint(0xffff)
	{
	}

	// FUNCTION: ENGINE 0x10076460
	void ShoulderConFixupBehaviour::UpdateListening()
	{
		bool listen;
		if (enableCount > 0 || enabled || ragdollEnabled)
		{
			listen = true;
		}
		else
		{
			listen = false;
		}
		Listen2(0x40, listen);
	}

	// FUNCTION: ENGINE 0x100766B0
	content::MemberList* ShoulderConFixupPropertiesJointPair::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<ShoulderConFixupPropertiesJointPair>(true, true, "p"),
				PROTO_NAME_OFFSET(ShoulderConFixupPropertiesJointPair, shoulderJointName), "shoulderJointName" },
			{ content::GetNameMetaTypeCopy<ShoulderConFixupPropertiesJointPair>(true, true, "p"),
				PROTO_NAME_OFFSET(ShoulderConFixupPropertiesJointPair, shoulderConJointName), "shoulderConJointName" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10076870
	ShoulderConFixupBehaviour::ShoulderConFixupBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		drawable(0), properties(0), enableCount(0), enabled(false), ragdollEnabled(false)
	{
		Listen(1, true);
		Listen(0x12, true);
		Listen(2, true);
		Listen(0x2c, true);
	}

	// FUNCTION: ENGINE 0x10076900
	ShoulderConFixupBehaviour::~ShoulderConFixupBehaviour()
	{
		core::SafeRelease(properties);
	}

	// FUNCTION: ENGINE 0x10076930
	void ShoulderConFixupBehaviour::SetEnabled(bool newEnabled)
	{
		enabled = newEnabled;
		UpdateListening();
	}

	// FUNCTION: ENGINE 0x10076950
	void ShoulderConFixupBehaviour::Reset()
	{
		enableCount = 0;
		ragdollEnabled = false;
		UpdateListening();
	}

	// FUNCTION: ENGINE 0x10076960
	void ShoulderConFixupBehaviour::AddEnabled(bool add)
	{
		if (add)
		{
			enableCount++;
		}
		else
		{
			enableCount--;
		}
		UpdateListening();
	}

	// FUNCTION: ENGINE 0x10076990
	void ShoulderConFixupBehaviour::Update(float dt, unsigned short mask)
	{
		if (drawable != 0)
		{
			proto::PartLookup* lookup = ((engine::Attribute<proto::PartLookup*>*)drawable)->value;
			if (lookup != 0)
			{
				for (int i = 0; i < 2; i++)
				{
					int from = parts[i].shoulderJoint;
					int to = parts[i].shoulderConJoint;
					math::Vector4& source = lookup->positions[from];
					math::Vector4& destination = lookup->positions[to];
					destination.x = source.x;
					destination.y = source.y;
					destination.z = source.z;
					lookup->rotations[to] = lookup->rotations[from];
					engine::NISTransform* transforms = lookup->transforms30;
					transforms[to] = transforms[from];
					lookup->transforms34[to] = lookup->transforms34[from];
					lookup->transforms38[to] = lookup->transforms38[from];
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10076EC0
	void ShoulderConFixupBehaviour::FindParts()
	{
		engine::Attribute<proto::PartLookup*>* attribute =
			(engine::Attribute<proto::PartLookup*>*)owner->FindAttribute(proto::gDrawableAttributeName);
		drawable = attribute;
		if (attribute != 0 && attribute->value != 0 && properties != 0)
		{
			proto::PartLookup* lookup = attribute->value;
			for (unsigned int i = 0; i < 2; i++)
			{
				const core::Name<core::CaseSensitiveKey>& first = properties->jointPairs.begin[i].shoulderJointName;
				parts[i].shoulderJoint = lookup->FindPart(first);
				const core::Name<core::CaseSensitiveKey>& second = properties->jointPairs.begin[i].shoulderConJointName;
				parts[i].shoulderConJoint = lookup->FindPart(second);
			}
		}
	}

	// FUNCTION: ENGINE 0x10076F40
	void ShoulderConFixupBehaviour::Slot1()
	{
		FindParts();
	}

	// FUNCTION: ENGINE 0x10076F50
	void ShoulderConFixupBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 1:
			if (static_cast<engine::AttributeUpdatedMessage*>(message)->name == proto::gDrawableAttributeName)
			{
				FindParts();
			}
			break;
		case 0x12:
			switch ((unsigned short)message->id)
			{
			case 1:
				ragdollEnabled = static_cast<engine::RagdollSetEnabledMessage*>(message)->enabled;
				UpdateListening();
				break;
			}
			break;
		case 2:
			Reset();
			break;
		case 0x2c:
			switch ((unsigned short)message->id)
			{
			case 2:
				AddEnabled(static_cast<SetShoulderConFixupEnabledMessage*>(message)->unknownC);
				break;
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x10077220
	content::MemberList* ShoulderConFixupProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<ShoulderConFixupProperties, JointPairArray>(
				content::GetClassMetaType<ShoulderConFixupPropertiesJointPair>(), "p"),
				PROTO_OFFSET(ShoulderConFixupProperties, jointPairs), "jointPairs" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x100772D0
	content::MemberList* ShoulderConFixupBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, ShoulderConFixupBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<ShoulderConFixupBehaviour, ShoulderConFixupProperties>("p"),
				PROTO_OFFSET(ShoulderConFixupBehaviour, properties), "shoulderConFixupProperties" },
			{ content::GetMemberMetaType<ShoulderConFixupBehaviour, bool>(&ShoulderConFixupBehaviour::GetEnabled,
				&ShoulderConFixupBehaviour::SetEnabled, "p"), 0, "fixupEnabledByDefault" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10077700
	ShoulderConFixupProperties::ShoulderConFixupProperties()
	{
	}

	// FUNCTION: ENGINE 0x10077730
	ShoulderConFixupProperties::~ShoulderConFixupProperties()
	{
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10076230
// FUNCTION: ENGINE 0x10076240
// FUNCTION: ENGINE 0x10076560
// FUNCTION: ENGINE 0x10076570
// FUNCTION: ENGINE 0x100765B0
// FUNCTION: ENGINE 0x100765F0
// FUNCTION: ENGINE 0x10076600
// FUNCTION: ENGINE 0x10076610
// FUNCTION: ENGINE 0x10076630
// FUNCTION: ENGINE 0x10076640
// FUNCTION: ENGINE 0x10076680
// FUNCTION: ENGINE 0x10076790
// FUNCTION: ENGINE 0x100767A0
// FUNCTION: ENGINE 0x100767F0
// FUNCTION: ENGINE 0x10076800
// FUNCTION: ENGINE 0x10076840
// FUNCTION: ENGINE 0x10076A80
// FUNCTION: ENGINE 0x10076A90
// FUNCTION: ENGINE 0x10076AF0
// FUNCTION: ENGINE 0x10076B00
// FUNCTION: ENGINE 0x10076B20
// FUNCTION: ENGINE 0x10076B80
// FUNCTION: ENGINE 0x10076BA0
// FUNCTION: ENGINE 0x10076BC0
// FUNCTION: ENGINE 0x10076BF0
// FUNCTION: ENGINE 0x10076C00
// FUNCTION: ENGINE 0x10076C30
// FUNCTION: ENGINE 0x10076C50
// FUNCTION: ENGINE 0x10076C70
// FUNCTION: ENGINE 0x10076C90
// FUNCTION: ENGINE 0x10076CB0
// FUNCTION: ENGINE 0x10076CD0
// FUNCTION: ENGINE 0x10076CF0
// FUNCTION: ENGINE 0x10076D20
// FUNCTION: ENGINE 0x10076D60
// FUNCTION: ENGINE 0x10076DB0
// FUNCTION: ENGINE 0x10076DE0
// FUNCTION: ENGINE 0x10076E40
// FUNCTION: ENGINE 0x10076E60
// FUNCTION: ENGINE 0x10076E90
// FUNCTION: ENGINE 0x10077040
// FUNCTION: ENGINE 0x100770A0
// FUNCTION: ENGINE 0x10077100
// FUNCTION: ENGINE 0x100771C0
// FUNCTION: ENGINE 0x100771D0
// FUNCTION: ENGINE 0x10D810F0
// FUNCTION: ENGINE 0x100773F0
// FUNCTION: ENGINE 0x10077460
// FUNCTION: ENGINE 0x100774D0
// FUNCTION: ENGINE 0x10077500
// FUNCTION: ENGINE 0x10077600
// FUNCTION: ENGINE 0x10077650
// FUNCTION: ENGINE 0x10077670
// FUNCTION: ENGINE 0x10077760
// FUNCTION: ENGINE 0x10077810
