// More messages the actions of the ai fight items send (RTTI names from the engine; type, id and members from the engine's
// constructors, member names are guesses). The constructors are inline, expanded in every user.
#ifndef PROTO_FIGHTITEMS_AI_AIACTIONMESSAGES_H
#define PROTO_FIGHTITEMS_AI_AIACTIONMESSAGES_H

#include "code/proto/fightitems/ai/aimessages.h"
#include "code/proto/messages/airequestmessages.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/gameobjectparams.h"

namespace fight
{
	class Action;
}

namespace choreo
{
	// 0x10D94FF8
	extern const float gMinusOne;
}

namespace engine
{
	// 0x11255368: the names of the goto tasks (aifightitemnames.cpp)
	extern fight::EnumEntry gGotoTable[8];
	// 0x11265840 / 0x11265858: the names "DriverAI" and "DriverAITakingOff" (charactertypenames.cpp)
	extern core::Name<core::CaseSensitiveKey> gDriverAI3;
	extern core::Name<core::CaseSensitiveKey> gDriverAITakingOff;
	// 0x11255360: the listeners of the scenario messages ("scenario"; aifightitemnames.cpp)
	extern MessageListeners gScenario38;
}

namespace engine
{
	// RTTI: engine::FightGetGameObjectParamsMessage: the object answers the parameters its fight is created with (null when it has none)
	struct FightGetGameObjectParamsMessage : public NonintrusiveMessage
	{
		FightGetGameObjectParamsMessage() : NonintrusiveMessage(0xb, 0x10), params(0)
		{
		}
		virtual ~FightGetGameObjectParamsMessage()
		{
		}

		GameObjectParams* params;  // +0xC
	};
}

namespace proto
{
	// RTTI: proto::ClearFixedDestinationMessage: the object forgets the fixed destination an action gave it
	struct ClearFixedDestinationMessage : public MovementMessage
	{
		explicit ClearFixedDestinationMessage(fight::Action* newSource) : MovementMessage(0x18), source(newSource)
		{
		}
		virtual ~ClearFixedDestinationMessage()
		{
		}

		fight::Action* source;  // +0xC
	};

	// RTTI: proto::SetStateStateChangeMessage: the object takes the state of that name
	struct SetStateStateChangeMessage : public StateChangeMessage
	{
		explicit SetStateStateChangeMessage(const core::Name<core::CaseSensitiveKey>& newState) : StateChangeMessage(1), state(newState)
		{
		}
		virtual ~SetStateStateChangeMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> state;  // +0x10
	};

	// RTTI: proto::SetVehicleAccelerationsMessage: the vehicle takes a factor for its accelerations (the others stay at minus one)
	struct SetVehicleAccelerationsMessage : public VehicleMessage
	{
		SetVehicleAccelerationsMessage() : VehicleMessage(6), unknownC(choreo::gMinusOne), unknown10(choreo::gMinusOne), factor(choreo::gMinusOne), unknown18(choreo::gMinusOne)
		{
		}
		virtual ~SetVehicleAccelerationsMessage()
		{
		}

		float unknownC;
		float unknown10;
		float factor;  // +0x14
		float unknown18;
	};

	// RTTI: proto::GetIntersectionPropertiesMovementMessage: the object answers the name of its intersection properties
	struct GetIntersectionPropertiesMovementMessage : public MovementMessage
	{
		GetIntersectionPropertiesMovementMessage() : MovementMessage(0x4c), name()
		{
		}
		virtual ~GetIntersectionPropertiesMovementMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	// RTTI: proto::SetIntersectionPropertiesMovementMessage: the object takes the intersection properties of that name
	struct SetIntersectionPropertiesMovementMessage : public MovementMessage
	{
		explicit SetIntersectionPropertiesMovementMessage(const core::Name<core::CaseSensitiveKey>& newName) : MovementMessage(0x4b), name(newName)
		{
		}
		virtual ~SetIntersectionPropertiesMovementMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	// What the perception of an object knows about one other object (the part the conditions read; 0x30 bytes)
	struct PerceptionStatusEntry
	{
		engine::HandleBase object;  // +0x0
		unsigned char unknown4[0x10];
		float time;  // +0x14: how long ago the object was seen
		unsigned char unknown18[0x18];
	};

	// The entries of a perception (begin and end of an array)
	struct PerceptionStatusList
	{
		PerceptionStatusEntry* begin;  // +0x0
		PerceptionStatusEntry* end;  // +0x4
	};

	// RTTI: proto::GetStatusPerceptionMsg: the object answers what its perception knows about other objects
	struct GetStatusPerceptionMsg : public PerceptionMessage
	{
		GetStatusPerceptionMsg() : PerceptionMessage(0), list(0)
		{
		}
		virtual ~GetStatusPerceptionMsg()
		{
		}

		PerceptionStatusList* list;  // +0xC
	};

	// RTTI: proto::ThreatInMemoryMessage: the object answers whether a threat is in its memory
	struct ThreatInMemoryMessage : public ThreatMessage
	{
		ThreatInMemoryMessage(int newThreat, int newValue) : ThreatMessage(2), threat(newThreat), value(newValue), found(false)
		{
		}
		virtual ~ThreatInMemoryMessage()
		{
		}

		int threat;  // +0xC
		int value;  // +0x10
		bool found;  // +0x14
	};

	// RTTI: proto::GetLastThreatMessage: the object answers the last threat that hit it
	struct GetLastThreatMessage : public engine::IntrusiveMessage
	{
		GetLastThreatMessage() : engine::IntrusiveMessage(0x28, 7), threat()
		{
		}
		virtual ~GetLastThreatMessage()
		{
		}

		engine::GameObjectHandle threat;  // +0xC
	};

	// A patrol path an object follows (name guess): the handle of the object that holds the path; the methods ask that object
	class PatrolPath
	{
	public:
		// 0x10205260: whether the object of the path exists
		bool IsValid();

		engine::GameObjectHandle object;  // +0x0
	};

	// RTTI: proto::GetPatrolMovementMessage: the object answers the handle of the patrol path it follows (null when it follows none)
	struct GetPatrolMovementMessage : public MovementMessage
	{
		GetPatrolMovementMessage() : MovementMessage(10), path(0)
		{
		}
		virtual ~GetPatrolMovementMessage()
		{
		}

		PatrolPath* path;  // +0xC
	};

	// RTTI: proto::SetBrakingInMotionMovementMessage: the object does or does not brake while it moves
	struct SetBrakingInMotionMovementMessage : public MovementMessage
	{
		explicit SetBrakingInMotionMovementMessage(bool newBraking) : MovementMessage(0x20), braking(newBraking)
		{
		}
		virtual ~SetBrakingInMotionMovementMessage()
		{
		}

		bool braking;  // +0xC
	};

	// RTTI: proto::SetReverseGearMovementMessage: the object drives in reverse gear or not
	struct SetReverseGearMovementMessage : public MovementMessage
	{
		explicit SetReverseGearMovementMessage(bool newReverse) : MovementMessage(0x21), reverse(newReverse)
		{
		}
		virtual ~SetReverseGearMovementMessage()
		{
		}

		bool reverse;  // +0xC
	};

	// What an object follows (the part the follow target action reads)
	struct FollowInformation
	{
		math::Vector position;  // +0x0
		engine::GameObjectHandle target;  // +0xC
	};

	// RTTI: proto::GetFollowInformationMessage: the object answers what it follows
	struct GetFollowInformationMessage : public MovementMessage
	{
		GetFollowInformationMessage() : MovementMessage(0x37), information(0)
		{
		}
		virtual ~GetFollowInformationMessage()
		{
		}

		FollowInformation* information;  // +0xC
	};

	// RTTI: proto::SetNPCLODStateAIMsg: the object takes a level of detail state
	struct SetNPCLODStateAIMsg : public LODAIMessage
	{
		explicit SetNPCLODStateAIMsg(int newState) : LODAIMessage(0x13), state(newState)
		{
		}
		virtual ~SetNPCLODStateAIMsg()
		{
		}

		int state;  // +0xC
	};
}

#endif
