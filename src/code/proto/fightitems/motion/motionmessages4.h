// The messages the action halves of the motion fight items (0x100C0000 - 0x100E0000) send, whose classes no other unit of this source tree declares (RTTI names;
// the constructors are inline in the engine and expanded in every user, so the argument lists and member names are guesses from the users).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES4_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES4_H

#include "code/engine/message.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/core/name.h"
#include "code/proto/fightitems/motion/motionmessages2.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/ai/aimessages.h"

namespace proto
{
	// RTTI: proto::FEDisplayMessage: the base of the messages to the front end display (message type 0x33)
	struct FEDisplayMessage : public engine::IntrusiveMessage
	{
	public:
		explicit FEDisplayMessage(short newId) : engine::IntrusiveMessage(0x33, newId)
		{
		}
		virtual ~FEDisplayMessage()
		{
		}
	};

	// RTTI: proto::GetMarkerIconTypeMessage: the object answers the type of its marker icon
	struct GetMarkerIconTypeMessage : public FEDisplayMessage
	{
	public:
		GetMarkerIconTypeMessage() : FEDisplayMessage(7), iconType(0x26)
		{
		}
		virtual ~GetMarkerIconTypeMessage()
		{
		}

		int iconType;  // +0xC
	};

	// RTTI: proto::GetGrabbableClassMessage: the object answers the class of its grabs
	class GetGrabbableClassMessage : public GrabbableMessage
	{
	public:
		GetGrabbableClassMessage() : GrabbableMessage(1), className(), unknown18(false)
		{
		}
		virtual ~GetGrabbableClassMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> className;  // +0x10
		bool unknown18;  // +0x18
		int unknown1C;
	};

	// RTTI: proto::SetGrabbedObjectMessage: gives the object an object to hold in a named grab slot
	class SetGrabbedObjectMessage : public GrabMessage
	{
	public:
		SetGrabbedObjectMessage(const core::Name<core::CaseSensitiveKey>* newSlot, engine::GameObjectHandle newObject, int v14) : GrabMessage(1), slot(newSlot), object(newObject), unknown14(v14)
		{
		}
		virtual ~SetGrabbedObjectMessage()
		{
		}

		const core::Name<core::CaseSensitiveKey>* slot;  // +0xC
		engine::GameObjectHandle object;  // +0x10
		int unknown14;
	};

	// RTTI: proto::SwapGrabSlotsMessage: swaps what two grab slots hold
	class SwapGrabSlotsMessage : public GrabMessage
	{
	public:
		SwapGrabSlotsMessage(const core::Name<core::CaseSensitiveKey>* newSlotA, const core::Name<core::CaseSensitiveKey>* newSlotB) : GrabMessage(6), slotA(newSlotA), slotB(newSlotB)
		{
		}
		virtual ~SwapGrabSlotsMessage()
		{
		}

		const core::Name<core::CaseSensitiveKey>* slotA;  // +0xC
		const core::Name<core::CaseSensitiveKey>* slotB;  // +0x10
	};

	// RTTI: proto::SetAllowGrabbingMessage: allows grabs of the object or not
	class SetAllowGrabbingMessage : public GrabbableMessage
	{
	public:
		explicit SetAllowGrabbingMessage(bool newAllow) : GrabbableMessage(2), allow(newAllow)
		{
		}
		virtual ~SetAllowGrabbingMessage()
		{
		}

		bool allow;  // +0xC
	};

	// RTTI: proto::GetAllowGrabbingMessage: the object answers whether grabs are allowed
	class GetAllowGrabbingMessage : public GrabbableMessage
	{
	public:
		GetAllowGrabbingMessage() : GrabbableMessage(3), allow(true)
		{
		}
		virtual ~GetAllowGrabbingMessage()
		{
		}

		bool allow;  // +0xC
	};

	// RTTI: proto::SetAccumDamageDamageMessage: sets the accumulated damage of the object
	struct SetAccumDamageDamageMessage : public engine::IntrusiveMessage
	{
		explicit SetAccumDamageDamageMessage(float newDamage) : engine::IntrusiveMessage(0x14, 0xF), damage(newDamage)
		{
		}
		virtual ~SetAccumDamageDamageMessage()
		{
		}

		float damage;  // +0xC
	};

	// RTTI: proto::GetAccumDamageDamageMessage: the object answers its accumulated damage
	struct GetAccumDamageDamageMessage : public engine::IntrusiveMessage
	{
		GetAccumDamageDamageMessage() : engine::IntrusiveMessage(0x14, 0x10), damage(0.0f)
		{
		}
		virtual ~GetAccumDamageDamageMessage()
		{
		}

		float damage;  // +0xC
	};

	// RTTI: proto::HunterCanHopAroundCornerMovementMessage: the object answers whether it may hop around a corner
	struct HunterCanHopAroundCornerMovementMessage : public MovementMessage
	{
		HunterCanHopAroundCornerMovementMessage() : MovementMessage(0x53), canHop(false)
		{
		}
		virtual ~HunterCanHopAroundCornerMovementMessage()
		{
		}

		bool canHop;  // +0xC
	};

	// RTTI: proto::AttemptGrabMessage: asks the object whether a grab by the given object would take
	class AttemptGrabMessage : public GrabbableMessage
	{
	public:
		explicit AttemptGrabMessage(engine::GameObjectHandle newGrabber) : GrabbableMessage(0), grabber(newGrabber), grabbed(), allowed(true), canGrab(false), unknown16(false)
		{
		}
		virtual ~AttemptGrabMessage()
		{
		}

		engine::GameObjectHandle grabber;  // +0xC
		engine::GameObjectHandle grabbed;  // +0x10
		bool allowed;  // +0x14
		bool canGrab;  // +0x15
		bool unknown16;
	};

	// RTTI: proto::GetGrabTargetGrabMessage: the object answers the object it means to grab
	struct GetGrabTargetGrabMessage : public GrabMessage
	{
		GetGrabTargetGrabMessage() : GrabMessage(9), target()
		{
		}
		virtual ~GetGrabTargetGrabMessage()
		{
		}

		engine::GameObjectHandle target;  // +0xC
	};

	// RTTI: proto::FindGrabTargetGrabMessage: the object answers the object it would grab (the engine's constructor is out of line, 0x100C2370)
	struct FindGrabTargetGrabMessage : public GrabMessage
	{
		FindGrabTargetGrabMessage(bool vC, int v14, core::Name<core::CaseSensitiveKey> newClassName, bool vD, int v10, float v18);
		virtual ~FindGrabTargetGrabMessage()
		{
		}

		bool unknownC;  // +0xC
		bool unknownD;  // +0xD
		int unknown10;
		int unknown14;
		float unknown18;
		int unknown1C;
		core::Name<core::CaseSensitiveKey> className;  // +0x20
		engine::GameObjectHandle target;  // +0x28
	};
}

#endif
