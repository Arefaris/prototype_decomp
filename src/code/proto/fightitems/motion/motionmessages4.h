// The messages the action halves of the motion fight items (0x100C0000 - 0x100E0000) send, whose classes no other unit of this source tree declares (RTTI names;
// the constructors are inline in the engine and expanded in every user, so the argument lists and member names are guesses from the users).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES4_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES4_H

#include "code/engine/message.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/core/name.h"
#include "code/proto/fightitems/motion/motionmessages2.h"

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
}

#endif
