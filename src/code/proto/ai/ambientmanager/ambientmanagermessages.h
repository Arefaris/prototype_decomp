// The messages of the ambient population and the ai that the spawners, the intersections and the pedestrian
// behaviours send or answer (RTTI names; the member names are guesses from the senders). Their constructors and
// destructors are defined in ambientmanagermessages.cpp, where the engine keeps its out-of-line copies (0x10420680 -
// 0x10432E60, scattered).
#ifndef PROTO_AI_AMBIENTMANAGER_AMBIENTMANAGERMESSAGES_H
#define PROTO_AI_AMBIENTMANAGER_AMBIENTMANAGERMESSAGES_H

#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/vector.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/ai/aimessages.h"
#include "code/proto/messages/airequestmessages.h"
#include "code/proto/messages/ambientmessages.h"

namespace proto
{
	class NPCType;

	// The ambient manager's spawners ask an object made of their template to become a vehicle
	struct CreateVehicleMessage : public AmbientMessage
	{
	public:
		// 0x10420680
		explicit CreateVehicleMessage(void* newArgument);
		// 0x104206B0 (the deleting destructor is 0x104208E0)
		virtual ~CreateVehicleMessage()
		{
		}

		void* argument;  // +0xC
	};

	// ... or a pedestrian of the spawner's kind
	struct CreatePedMessage : public AmbientMessage
	{
	public:
		// 0x104206C0
		CreatePedMessage(void* newArgument, NPCType* newType);
		// 0x10420700 (the deleting destructor is 0x10420910)
		virtual ~CreatePedMessage()
		{
		}

		void* argument;  // +0xC
		NPCType* type;  // +0x10
	};

	// RTTI proto::VehicleMovementBehaviourActiveMessage (message type 0x26, id 0x3B)
	struct VehicleMovementBehaviourActiveMessage : public MovementMessage
	{
	public:
		// 0x104289C0
		VehicleMovementBehaviourActiveMessage();
		// 0x104289F0
		virtual ~VehicleMovementBehaviourActiveMessage()
		{
		}

		bool active;  // +0xC
	};

	// RTTI proto::SetVehiclePatrolHeightOffsetMessage (id 0x3C)
	struct SetVehiclePatrolHeightOffsetMessage : public MovementMessage
	{
	public:
		// 0x10428A00
		SetVehiclePatrolHeightOffsetMessage(float newOffset, bool newFlag);
		// 0x10428A40
		virtual ~SetVehiclePatrolHeightOffsetMessage()
		{
		}

		float offset;  // +0xC
		bool flag;  // +0x10
	};

	// RTTI proto::SetLODDestinationAIMsg (message type 0x3A, id 0x15): where an object of a lower level of detail
	// drives to
	struct SetLODDestinationAIMsg : public LODAIMessage
	{
	public:
		// 0x1042D320
		explicit SetLODDestinationAIMsg(const math::Vector& newDestination);
		// 0x1042D360
		virtual ~SetLODDestinationAIMsg()
		{
		}

		math::Vector destination;  // +0xC
	};

	// RTTI proto::HasLODArrivedAIMsg (id 0x16): answered true when the object has arrived
	struct HasLODArrivedAIMsg : public LODAIMessage
	{
	public:
		// 0x1042D370
		HasLODArrivedAIMsg();
		// 0x1042D3A0
		virtual ~HasLODArrivedAIMsg()
		{
		}

		bool arrived;  // +0xC
	};

	// RTTI proto::ForceUpDatePerceptionMessage (message type 0x25, id 0x11)
	struct ForceUpDatePerceptionMessage : public PerceptionMessage
	{
	public:
		// 0x1042EE20
		ForceUpDatePerceptionMessage();
		// 0x1042EE50
		virtual ~ForceUpDatePerceptionMessage()
		{
		}
	};

	// RTTI proto::SetAmbientControlledAIMsg (message type 0x2B, id 0x11)
	struct SetAmbientControlledAIMsg : public AIMessage
	{
	public:
		// 0x1042EE60
		explicit SetAmbientControlledAIMsg(bool newControlled);
		// 0x1042EE90
		virtual ~SetAmbientControlledAIMsg()
		{
		}

		bool controlled;  // +0xC
	};

	// RTTI proto::SetTurnedOffMovementMessage (message type 0x26, id 0x46)
	struct SetTurnedOffMovementMessage : public MovementMessage
	{
	public:
		// 0x1042EEA0
		explicit SetTurnedOffMovementMessage(bool newTurnedOff);
		// 0x1042EED0
		virtual ~SetTurnedOffMovementMessage()
		{
		}

		bool turnedOff;  // +0xC
	};

	// RTTI proto::GetIntersectionStateMessage (ambient id 0): the state of the light for one direction
	struct GetIntersectionStateMessage : public AmbientMessage
	{
	public:
		// 0x104305D0
		explicit GetIntersectionStateMessage(int newDirection);
		// 0x10430620
		virtual ~GetIntersectionStateMessage()
		{
		}

		int state;  // +0xC
		int direction;  // +0x10
		int unknown14;
		float unknown18;
		float unknown1C;
	};

	// RTTI proto::GetIntersectionBehaviourMessage (id 1)
	struct GetIntersectionBehaviourMessage : public AmbientMessage
	{
	public:
		// 0x10432D40
		GetIntersectionBehaviourMessage();
		// 0x10432D70
		virtual ~GetIntersectionBehaviourMessage()
		{
		}

		void* behaviour;  // +0xC
	};

	// RTTI proto::GetAlertInfoMessage (id 0x14): the objects an alert is about
	struct GetAlertInfoMessage : public AmbientMessage
	{
	public:
		// 0x10432D80
		GetAlertInfoMessage();
		// 0x10432DC0
		virtual ~GetAlertInfoMessage()
		{
		}

		engine::HandleBase giver;  // +0xC
		engine::HandleBase taker;  // +0x10
	};
}

#endif
