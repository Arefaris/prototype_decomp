// The messages the action halves of the motion fight items (0x100C0000 - 0x100E0000) send, whose classes no other unit of this source tree declares (RTTI names;
// the constructors are inline in the engine and expanded in every user, so the argument lists and member names are guesses from the users).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES4_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES4_H

#include "code/engine/message.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/core/name.h"
#include "code/proto/fightitems/motion/motionmessages2.h"
#include "code/proto/fightitems/ai/aicodemessages.h"

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
}

#endif
