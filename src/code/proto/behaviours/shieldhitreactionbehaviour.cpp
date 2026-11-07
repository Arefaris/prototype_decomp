#include "code/proto/behaviours/shieldhitreactionbehaviour.h"
#include "code/core/refptr.h"
#include "code/engine/physics/physicsmessages.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/ravenphysics/context.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102C48D0
	ShieldHitReactionBehaviour::ShieldHitReactionBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		hitsA(0), hitsB(0), reflecting(false), reflectingIntersectionProperties(0)
	{
		Listen(0x14, true);
		Listen(0x1e, true);
	}

	// The hit messages (type 0x1E, ids 0x20 and 0x21): which of the two sources hit (name guesses)
	struct ShieldHitMessage : public engine::Message
	{
		bool fromA;  // +0xC
		bool fromB;  // +0xD
	};

	// FUNCTION: ENGINE 0x102C4930
	void ShieldHitReactionBehaviour::OnHitsBegin(engine::Message* message)
	{
		ShieldHitMessage* hit = static_cast<ShieldHitMessage*>(message);
		if (hit->fromA)
		{
			hitsA++;
		}
		if (hit->fromB)
		{
			hitsB++;
		}
		if (!reflecting && (hitsA > 0 || hitsB > 0))
		{
			engine::SetIntersectionPropertiesMessage properties(reflectingIntersectionProperties->unknown40, true, 1, false);
			owner->SendMessage(&properties);
			reflecting = true;
		}
	}

	// FUNCTION: ENGINE 0x102C49D0
	void ShieldHitReactionBehaviour::OnHitsEnd(engine::Message* message)
	{
		ShieldHitMessage* hit = static_cast<ShieldHitMessage*>(message);
		if (hit->fromA)
		{
			hitsA--;
		}
		if (hit->fromB)
		{
			hitsB--;
		}
		if (reflecting && hitsA <= 0 && hitsB <= 0)
		{
			engine::SetIntersectionPropertiesMessage properties(reflectingIntersectionProperties->unknown40, false, 1, false);
			owner->SendMessage(&properties);
			reflecting = false;
		}
	}

	// FUNCTION: ENGINE 0x102C4C70
	void ShieldHitReactionBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 0x14:
			if (message->id == 0xA)
			{
				OnAttachmentMessage(message);
			}
			break;
		case 0x1E:
			switch ((unsigned short)message->id)
			{
			case 0x20:
				OnHitsBegin(message);
				break;
			case 0x21:
				OnHitsEnd(message);
				break;
			}
			break;
		}
	}

	// Asks the object which one it is attached to (type 0xF, id 6; the answer is a pointer to a handle; name guesses)
	struct GetAttachmentStateMessage : public engine::Message
	{
		GetAttachmentStateMessage() : engine::Message(0xF, 6)
		{
			state = 0;
		}
		virtual ~GetAttachmentStateMessage()
		{
		}

		engine::HandleBase* state;  // +0xC
	};

	// The hit the attachment is told about (type 0x14, id 0xA): the kind of attack at +0x48, the object that took it at +0x7C
	struct ShieldAttackMessage : public engine::Message
	{
		unsigned char unknownC[0x48 - 0xC];
		int attackType;  // +0x48
		unsigned char unknown4C[0x7C - 0x4C];
		engine::HandleBase target;  // +0x7C
	};

	// FUNCTION: ENGINE 0x102C4B10
	// NONMATCHING: the checks and the calls are the engine's; the engine tests the attached object's handle three times
	// from the table where ours merges the last two (about 53 %)
#ifdef NONMATCHING
	void ShieldHitReactionBehaviour::OnAttachmentMessage(engine::Message* message)
	{
		engine::GameObjectHandle& attached = static_cast<engine::GameObjectHandle&>(attachedTo);
		if (!attached.IsValid())
		{
			GetAttachmentStateMessage query;
			owner->PostMessage(&query);
			if (query.state != 0)
			{
				attachedTo = *query.state;
			}
		}
		if (attached.IsValid())
		{
			ShieldAttackMessage* attack = static_cast<ShieldAttackMessage*>(message);
			bool bullet = attack->attackType == 9 || attack->attackType == 10;
			bool missile = attack->attackType == 11;
			if (bullet || missile)
			{
				attached.Get()->SendMessage(message);
				if ((bullet && hitsA > 0) || (missile && hitsB > 0))
				{
					attack->target = attachedTo;
				}
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x102C4AB0
	ShieldHitReactionBehaviour::~ShieldHitReactionBehaviour()
	{
		core::SafeRelease(reflectingIntersectionProperties);
	}

	// FUNCTION: ENGINE 0x102C4890
	content::ClassInfo* ShieldHitReactionBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ShieldHitReactionBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102C4D30
	content::MemberList* ShieldHitReactionBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, ShieldHitReactionBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<ShieldHitReactionBehaviour, ravenphysics::IntersectionPropertiesLoader>("p"),
				PROTO_OFFSET(ShieldHitReactionBehaviour, reflectingIntersectionProperties),
				"reflectingIntersectionProperties" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102C4A70
// FUNCTION: ENGINE 0x102C4A80
// FUNCTION: ENGINE 0x102C4AE0
// FUNCTION: ENGINE 0x102C4CD0
