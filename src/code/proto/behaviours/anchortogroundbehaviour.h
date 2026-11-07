// proto::AnchorToGroundBehaviour (RTTI and reflection names; base engine::Behaviour): keeps its object attached to the
// ground (or to a joint of another object) with a ball in socket and two align constraints of the physics. Reflected: the
// offset of the anchor, whether the object stays anchored and the orientation offset of the joint. Unit 0x10060160 -
// 0x10061B00 (no assert path; the file name is a guess). The reflected names are original, the rest is guessed; only the
// reflection is reconstructed.
#ifndef PROTO_ANCHORTOGROUNDBEHAVIOUR_H
#define PROTO_ANCHORTOGROUNDBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/message.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/math/vector.h"
#include "code/ravenphysics/collision/collisionobject.h"

namespace proto
{
	// Anchors the object or lets it go (RTTI proto::AnchorToGroundStateChangeMessage, id 0xE; the member names are guesses)
	struct AnchorToGroundStateChangeMessage : public StateChangeMessage
	{
		AnchorToGroundStateChangeMessage(bool newAnchor, bool newZeroHeight) : StateChangeMessage(0xe),
			anchor(newAnchor), zeroHeight(newZeroHeight)
		{
		}
		virtual ~AnchorToGroundStateChangeMessage()
		{
		}

		bool anchor;  // +0xC
		bool zeroHeight;  // +0xD
	};

	// Asks whether the object is anchored (id 0xF; the name is a guess)
	struct IsAnchoredStateChangeMessage : public StateChangeMessage
	{
		IsAnchoredStateChangeMessage() : StateChangeMessage(0xf), anchored(false)
		{
		}
		virtual ~IsAnchoredStateChangeMessage()
		{
		}

		bool anchored;  // +0xC
	};

	class AnchorToGroundBehaviour : public engine::Behaviour
	{
	public:
		// 0x10061490
		explicit AnchorToGroundBehaviour(engine::GameObject* newOwner);
		// 0x100610C0 (deleting destructor 0x100615A0)
		virtual ~AnchorToGroundBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x100615D0), 3 (0x10060430), 4 (0x10060440) and 6 (0x10061A30)
		virtual void Slot1();
		virtual void OnActiveChanged(bool active);
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// 0x10060450 (name guess): destroys the constraints of the anchor
		void ReleaseConstraints();
		// 0x100605E0 (name guess): moves the anchor point of the ball in socket constraint
		void SetAnchorPoint(const math::Vector* point);
		// 0x10061900: anchors the object to the ground (or to the joint) or lets it go
		void ApplyAnchor(bool anchor, bool zeroHeight);

		engine::BaseAttribute* physicsObjectAttribute;  // +0xC
		engine::BaseAttribute* drawableAttribute;  // +0x10
		math::Vector offset;  // +0x14
		math::Vector unknown20;
		math::Vector unknown2C;
		ravenphysics::CollisionHandle alignHandleA;  // +0x38
		ravenphysics::CollisionHandle alignHandleB;  // +0x3C
		ravenphysics::CollisionHandle ballInSocketHandle;  // +0x40
		bool stayAnchored;  // +0x44
		float anchorToJointOrientationOffset;  // +0x48
	};

}

#endif
