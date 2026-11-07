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
		explicit CreateVehicleMessage(void* newArgument) : AmbientMessage(5), argument(newArgument)
		{
		}
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
		CreatePedMessage(void* newArgument, NPCType* newType) :
			AmbientMessage(6), argument(newArgument), type(newType)
		{
		}
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
		VehicleMovementBehaviourActiveMessage() :
			MovementMessage(0x3b), active(false)
		{
		}
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
		SetVehiclePatrolHeightOffsetMessage(float newOffset, bool newFlag) :
			MovementMessage(0x3c), offset(newOffset), flag(newFlag)
		{
		}
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
		explicit SetLODDestinationAIMsg(const math::Vector& newDestination) : LODAIMessage(0x15)
		{
			destination.x = newDestination.x;
		destination.y = newDestination.y;
		destination.z = newDestination.z;
		}
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
		HasLODArrivedAIMsg() : LODAIMessage(0x16), arrived(true)
		{
		}
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
		ForceUpDatePerceptionMessage() : PerceptionMessage(0x11)
		{
		}
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
		explicit SetAmbientControlledAIMsg(bool newControlled) : AIMessage(0x11), controlled(newControlled)
		{
		}
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
		explicit SetTurnedOffMovementMessage(bool newTurnedOff) :
			MovementMessage(0x46), turnedOff(newTurnedOff)
		{
		}
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
		explicit GetIntersectionStateMessage(int newDirection) :
			AmbientMessage(0), state(-1), direction(newDirection), lightState(0), timeLeft(0.0f), phaseDuration(0.0f)
		{
		}
		// 0x10430620
		virtual ~GetIntersectionStateMessage()
		{
		}

		int state;  // +0xC: the index of the phase the intersection is in
		int direction;  // +0x10
		int lightState;  // +0x14: the state of the light for the direction in that phase
		float timeLeft;  // +0x18
		float phaseDuration;  // +0x1C
	};

	// RTTI proto::GetIntersectionBehaviourMessage (id 1)
	struct GetIntersectionBehaviourMessage : public AmbientMessage
	{
	public:
		// 0x10432D40
		GetIntersectionBehaviourMessage() : AmbientMessage(1), behaviour(0)
		{
		}
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
		GetAlertInfoMessage() : AmbientMessage(0x14)
		{
		}
		// 0x10432DC0
		virtual ~GetAlertInfoMessage()
		{
		}

		engine::HandleBase giver;  // +0xC
		engine::HandleBase taker;  // +0x10
	};
	// RTTI proto::GetSensesInfoMessage (message type 0x3D, id 0xF)
	struct GetSensesInfoMessage : public ProtoRenderMsg
	{
	public:
		// 0x10432E30
		explicit GetSensesInfoMessage(bool newFlag) : ProtoRenderMsg(0xf)
		{
			flag = newFlag;
		}
		// 0x10432E60
		virtual ~GetSensesInfoMessage()
		{
		}

		unsigned char unknownC[8];
		bool flag;  // +0x14
	};
}

#endif
