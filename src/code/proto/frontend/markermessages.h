// The messages the marker manager and the front end display exchange with the objects that carry a marker (RTTI:
// proto::SetIsMarkedMessage and proto::GetMarkerCallerTypeMessage, messages to the front end display, type 0x33). The
// constructors are inline in the engine; the argument lists and the member names are guesses from the users.
#ifndef PROTO_FRONTEND_MARKERMESSAGES_H
#define PROTO_FRONTEND_MARKERMESSAGES_H

#include "code/proto/fightitems/motion/motionmessages5.h"

namespace proto
{
	// The other messages to the front end display that a behaviour answers (the classes are declared where the engine
	// has no inline constructor of its own in this unit; members as the front end display's behaviour writes them)
	struct ShowTargetHealthMessage : public FEDisplayMessage
	{
	public:
		ShowTargetHealthMessage() : FEDisplayMessage(0), show(false)
		{
		}

		bool show;  // +0xC
	};

	struct GetReticuleTypeMessage : public FEDisplayMessage
	{
	public:
		GetReticuleTypeMessage() : FEDisplayMessage(1), reticuleType(0)
		{
		}

		int reticuleType;  // +0xC
	};

	struct GetAmmoTypeMessage : public FEDisplayMessage
	{
	public:
		GetAmmoTypeMessage() : FEDisplayMessage(2), ammoType(0)
		{
		}

		int ammoType;  // +0xC
	};

	struct GetAimingDirection : public FEDisplayMessage
	{
	public:
		GetAimingDirection() : FEDisplayMessage(5), direction(0.0f), valid(false)
		{
		}

		float direction;  // +0xC
		bool valid;  // +0x10
	};

	// Tells the object whether it is marked
	struct SetIsMarkedMessage : public FEDisplayMessage
	{
	public:
		SetIsMarkedMessage(int newMarker, int newMarked) : FEDisplayMessage(6), marker(newMarker), marked(newMarked)
		{
		}
		virtual ~SetIsMarkedMessage()
		{
		}

		int marker;  // +0xC
		int marked;  // +0x10
	};

	// The object answers the type of the marker's caller
	struct GetMarkerCallerTypeMessage : public FEDisplayMessage
	{
	public:
		GetMarkerCallerTypeMessage() : FEDisplayMessage(8), callerType(7)
		{
		}
		virtual ~GetMarkerCallerTypeMessage()
		{
		}

		int callerType;  // +0xC
	};
}

#endif
