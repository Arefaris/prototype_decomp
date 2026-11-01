// The messages of the physics behaviours of a game object (RTTI names, namespace proto; message type 3, the type of the
// engine's physics messages). The constructors are inline: the fields are stored one by one and the object's own
// vftable (a single slot, the deleting destructor) last. The member names are guesses.
#ifndef PROTO_MESSAGES_PHYSICSMESSAGES_H
#define PROTO_MESSAGES_PHYSICSMESSAGES_H

#include "code/core/name.h"
#include "code/engine/message.h"

namespace proto
{
	// RTTI proto::PhysicsMessage: the base of the messages below (base IntrusiveMessage)
	struct PhysicsMessage : public engine::IntrusiveMessage
	{
		explicit PhysicsMessage(short newId) : engine::IntrusiveMessage(3, newId)
		{
		}
		virtual ~PhysicsMessage()
		{
		}
	};

	// Switches the physics object to a named level of detail (id 0x22)
	struct SetPhysicsLODMessage : public PhysicsMessage
	{
		explicit SetPhysicsLODMessage(const core::Name<core::CaseSensitiveKey>* newLod) : PhysicsMessage(0x22)
		{
			lod = newLod;
		}
		virtual ~SetPhysicsLODMessage()
		{
		}

		const core::Name<core::CaseSensitiveKey>* lod;  // +0xC
	};

	// Asks for the name of the level of detail the physics is on (RTTI proto::GetPhysicsLODMessage, id 0x1F); the name
	// comes back in the message
	struct GetPhysicsLODMessage : public PhysicsMessage
	{
		GetPhysicsLODMessage() : PhysicsMessage(0x1f)
		{
		}
		virtual ~GetPhysicsLODMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> lod;  // +0x10
	};

	// Latches or unlatches the doors of a vehicle (id 0x23)
	struct SetVehicleDoorsLatchedMessage : public PhysicsMessage
	{
		explicit SetVehicleDoorsLatchedMessage(bool newLatched) : PhysicsMessage(0x23)
		{
			latched = newLatched;
		}
		virtual ~SetVehicleDoorsLatchedMessage()
		{
		}

		bool latched;  // +0xC
	};
}

#endif
