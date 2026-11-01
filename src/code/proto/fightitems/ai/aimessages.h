// The messages of the ai fight items' conditions and actions that no other header declares. Like aicodemessages.h: the RTTI names
// are the engine's, the constructors are inline there (expanded in every user), member names and argument lists are guesses.
#ifndef PROTO_FIGHTITEMS_AI_AIMESSAGES_H
#define PROTO_FIGHTITEMS_AI_AIMESSAGES_H

#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/ai/aicodecommon.h"
#include "code/math/vector.h"

namespace proto
{
	// RTTI: proto::GetFixedDestinationMessage: the object answers whether it has a fixed destination
	struct GetFixedDestinationMessage : public MovementMessage
	{
		GetFixedDestinationMessage() : MovementMessage(0x16), destination(0)
		{
		}
		virtual ~GetFixedDestinationMessage()
		{
		}

		int destination;  // +0xC
	};

	// RTTI: proto::GetFixedAreaDestinationMessage: the object answers whether it has a fixed area destination
	struct GetFixedAreaDestinationMessage : public MovementMessage
	{
		GetFixedAreaDestinationMessage() : MovementMessage(0x19), destination(0)
		{
		}
		virtual ~GetFixedAreaDestinationMessage()
		{
		}

		int destination;  // +0xC
	};

	// RTTI: proto::GetEnabledAIMsg: the object answers whether its ai is enabled
	struct GetEnabledAIMsg : public AIMessage
	{
		GetEnabledAIMsg() : AIMessage(3), enabled(false)
		{
		}
		virtual ~GetEnabledAIMsg()
		{
		}

		bool enabled;  // +0xC
	};

	// RTTI: proto::GetTaskAIMsg: the object answers the name of its task
	struct GetTaskAIMsg : public AIMessage
	{
		GetTaskAIMsg() : AIMessage(5), task()
		{
		}
		virtual ~GetTaskAIMsg()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> task;  // +0x10
	};

	// RTTI: proto::GetGoalAIMsg: the object answers the name of its goal
	struct GetGoalAIMsg : public AIMessage
	{
		GetGoalAIMsg() : AIMessage(7), goal()
		{
		}
		virtual ~GetGoalAIMsg()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> goal;  // +0x10
	};

	// RTTI: proto::DisguiseMessage: the base of the messages about the disguise of an object (message type 0x2A)
	struct DisguiseMessage : public engine::IntrusiveMessage
	{
		explicit DisguiseMessage(short newId) : engine::IntrusiveMessage(0x2a, newId)
		{
		}
		virtual ~DisguiseMessage()
		{
		}
	};

	// RTTI: proto::GetAlertedDisguiseMsg: the object answers how alerted its disguise is
	struct GetAlertedDisguiseMsg : public DisguiseMessage
	{
		GetAlertedDisguiseMsg() : DisguiseMessage(0xd), unknownC(false), alert(0.0f)
		{
		}
		virtual ~GetAlertedDisguiseMsg()
		{
		}

		bool unknownC;
		float alert;  // +0x10
	};

	// RTTI: proto::GetTargetMessage: the object answers its target
	class GetTargetMessage : public TargetMessage
	{
	public:
		GetTargetMessage() : TargetMessage(0), target(), unknown10(0.0f)
		{
		}
		virtual ~GetTargetMessage()
		{
		}

		engine::GameObjectHandle target;  // +0xC
		float unknown10;
	};

	// RTTI: proto::GetTargetSuspicionStateTargetMessage: the object answers how suspicious it is of its target
	struct GetTargetSuspicionStateTargetMessage : public TargetMessage
	{
		GetTargetSuspicionStateTargetMessage() : TargetMessage(0xe), unknownC(0), state(0), target()
		{
		}
		virtual ~GetTargetSuspicionStateTargetMessage()
		{
		}

		int unknownC;
		int state;  // +0x10
		engine::GameObjectHandle target;  // +0x14
	};

	// One event of the list an object keeps (0x10 bytes; member names are guesses)
	struct AIEvent
	{
		core::Name<core::CaseSensitiveKey> name;  // +0x0
		int kind;  // +0x8
		int value;  // +0xC
	};

	// The events of an object: six slots inline, then the end of the used ones (0x64 bytes)
	struct AIEventList
	{
		AIEvent events[6];  // +0x0
		AIEvent* end;  // +0x60
	};

	// RTTI: proto::GetEventsAIMsg: the object answers the list of its events
	struct GetEventsAIMsg : public AIMessage
	{
		GetEventsAIMsg() : AIMessage(8), events(0)
		{
		}
		virtual ~GetEventsAIMsg()
		{
		}

		AIEventList* events;  // +0xC
	};

	// RTTI: proto::ClearFixedAreaDestinationMessage: the object forgets its fixed area destination
	struct ClearFixedAreaDestinationMessage : public MovementMessage
	{
		ClearFixedAreaDestinationMessage() : MovementMessage(0x1b)
		{
		}
		virtual ~ClearFixedAreaDestinationMessage()
		{
		}
	};

	// RTTI: proto::ForceRecalculatePathMovementMessage: the object plans its path again
	struct ForceRecalculatePathMovementMessage : public MovementMessage
	{
		ForceRecalculatePathMovementMessage() : MovementMessage(0x2e)
		{
		}
		virtual ~ForceRecalculatePathMovementMessage()
		{
		}
	};

	// RTTI: proto::DisableStayOnMeshMovementMessage: the object stays on the navigation mesh or leaves it
	struct DisableStayOnMeshMovementMessage : public MovementMessage
	{
		explicit DisableStayOnMeshMovementMessage(bool newDisable) : MovementMessage(0x59), disable(newDisable)
		{
		}
		virtual ~DisableStayOnMeshMovementMessage()
		{
		}

		bool disable;  // +0xC
	};

	// RTTI: proto::GetBrakingDistanceMovementMessage: the object answers how far ahead it brakes
	struct GetBrakingDistanceMovementMessage : public MovementMessage
	{
		GetBrakingDistanceMovementMessage() : MovementMessage(0x1d), distance(0.0f)
		{
		}
		virtual ~GetBrakingDistanceMovementMessage()
		{
		}

		float distance;  // +0xC
	};

	// RTTI: proto::SetBrakingDistanceMovementMessage: how far ahead the object brakes
	struct SetBrakingDistanceMovementMessage : public MovementMessage
	{
		explicit SetBrakingDistanceMovementMessage(float newDistance) : MovementMessage(0x1c), distance(newDistance)
		{
		}
		virtual ~SetBrakingDistanceMovementMessage()
		{
		}

		float distance;  // +0xC
	};

	// RTTI: proto::GetAvoidanceGapAnywhereMovementMessage: the object answers whether it keeps a gap to others anywhere
	struct GetAvoidanceGapAnywhereMovementMessage : public MovementMessage
	{
		GetAvoidanceGapAnywhereMovementMessage() : MovementMessage(0x31), enabled(false)
		{
		}
		virtual ~GetAvoidanceGapAnywhereMovementMessage()
		{
		}

		bool enabled;  // +0xC
	};

	// RTTI: proto::SetAvoidanceGapAnywhereMovementMessage: whether the object keeps a gap to others anywhere
	struct SetAvoidanceGapAnywhereMovementMessage : public MovementMessage
	{
		explicit SetAvoidanceGapAnywhereMovementMessage(bool newEnabled) : MovementMessage(0x32), enabled(newEnabled)
		{
		}
		virtual ~SetAvoidanceGapAnywhereMovementMessage()
		{
		}

		bool enabled;  // +0xC
	};

	// RTTI: proto::GetSpeedMovementMessage: the object answers its speed
	struct GetSpeedMovementMessage : public MovementMessage
	{
		GetSpeedMovementMessage() : MovementMessage(0x24), speed(0.0f)
		{
		}
		virtual ~GetSpeedMovementMessage()
		{
		}

		float speed;  // +0xC
	};

	// RTTI: proto::SetSpeedMovementMessage: the speed of the object
	struct SetSpeedMovementMessage : public MovementMessage
	{
		explicit SetSpeedMovementMessage(float newSpeed) : MovementMessage(0x23), speed(newSpeed)
		{
		}
		virtual ~SetSpeedMovementMessage()
		{
		}

		float speed;  // +0xC
	};

	// RTTI: proto::TriggerEventAIMsg: an event happens on the object (name, then whether it ends)
	struct TriggerEventAIMsg : public AIMessage
	{
		TriggerEventAIMsg(core::Name<core::CaseSensitiveKey> newEvent, int newEnds) : AIMessage(9), event(newEvent), ends(newEnds)
		{
		}
		virtual ~TriggerEventAIMsg()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> event;  // +0x10
		int ends;  // +0x18
		int unknown1C;
	};

	// RTTI: proto::ClearVehicleAccelerationsMessage: the vehicle forgets its accelerations
	struct ClearVehicleAccelerationsMessage : public VehicleMessage
	{
		ClearVehicleAccelerationsMessage() : VehicleMessage(7)
		{
		}
		virtual ~ClearVehicleAccelerationsMessage()
		{
		}
	};

	// What the object answers for its aim: filled in by the sender through the pointer (0x18 bytes, member names are guesses)
	struct AimParameters
	{
		int active;  // +0x0
		int where;  // +0x4
		math::Vector offset;  // +0x8
		bool forceWorldAngles;  // +0x14
		unsigned char unknown15[0x3];
	};

	// RTTI: proto::GetAimParametersMovementMessage: the object answers the block of its aim parameters
	struct GetAimParametersMovementMessage : public MovementMessage
	{
		explicit GetAimParametersMovementMessage(bool newFlag) : MovementMessage(0x57), parameters(0), flag(newFlag)
		{
		}
		virtual ~GetAimParametersMovementMessage()
		{
		}

		AimParameters* parameters;  // +0xC
		bool flag;  // +0x10
	};

	// RTTI: proto::SquadMessage: the base of the messages about the squad of an object (message type 0x27)
	struct SquadMessage : public engine::IntrusiveMessage
	{
		explicit SquadMessage(short newId) : engine::IntrusiveMessage(0x27, newId)
		{
		}
		virtual ~SquadMessage()
		{
		}
	};

	// RTTI: proto::GetCommanderSquadMessage: the object answers the commander of its squad
	struct GetCommanderSquadMessage : public SquadMessage
	{
		GetCommanderSquadMessage() : SquadMessage(1), commander()
		{
		}
		virtual ~GetCommanderSquadMessage()
		{
		}

		engine::GameObjectHandle commander;  // +0xC
	};

	// RTTI: proto::IsFormationSquadMessage: the squad answers whether it is in a formation
	struct IsFormationSquadMessage : public SquadMessage
	{
		IsFormationSquadMessage() : SquadMessage(0x12), inFormation(false)
		{
		}
		virtual ~IsFormationSquadMessage()
		{
		}

		bool inFormation;  // +0xC
	};

	// RTTI: proto::FormationReformingSquadMessage: the squad answers whether it reforms its formation
	struct FormationReformingSquadMessage : public SquadMessage
	{
		FormationReformingSquadMessage() : SquadMessage(0x13), reforming(false)
		{
		}
		virtual ~FormationReformingSquadMessage()
		{
		}

		bool reforming;  // +0xC
	};

	// RTTI: proto::LODAIMessage: the base of the messages about the level of detail of the ai of an object (message type 0x3A)
	struct LODAIMessage : public engine::IntrusiveMessage
	{
		explicit LODAIMessage(short newId) : engine::IntrusiveMessage(0x3a, newId)
		{
		}
		virtual ~LODAIMessage()
		{
		}
	};

	// RTTI: proto::SetUnDowngradableMsg: whether the object may lose detail
	struct SetUnDowngradableMsg : public LODAIMessage
	{
		explicit SetUnDowngradableMsg(bool newUnDowngradable) : LODAIMessage(7), unDowngradable(newUnDowngradable)
		{
		}
		virtual ~SetUnDowngradableMsg()
		{
		}

		bool unDowngradable;  // +0xC
	};

	// RTTI: proto::GetDestinationMessage: the object answers whether it has a destination, and where
	struct GetDestinationMessage : public MovementMessage
	{
		GetDestinationMessage() : MovementMessage(1), hasDestination(false), unknownD(false), destination(math::kZeroVector)
		{
		}
		virtual ~GetDestinationMessage()
		{
		}

		bool hasDestination;  // +0xC
		bool unknownD;
		math::Vector destination;  // +0x10
	};

	// RTTI: proto::GetStuckMovementMessage: the object answers whether it is stuck
	struct GetStuckMovementMessage : public MovementMessage
	{
		GetStuckMovementMessage() : MovementMessage(0x25), stuck(false), unknown10(0.0f)
		{
		}
		virtual ~GetStuckMovementMessage()
		{
		}

		bool stuck;  // +0xC
		float unknown10;
	};

	// RTTI: proto::GetInHotZoneMovementMessage: the object answers whether it is in a hot zone, and whether it stands on the ground
	struct GetInHotZoneMovementMessage : public MovementMessage
	{
		GetInHotZoneMovementMessage() : MovementMessage(0x4d), inHotZone(false), onGround(false)
		{
		}
		virtual ~GetInHotZoneMovementMessage()
		{
		}

		bool inHotZone;  // +0xC
		bool onGround;  // +0xD
	};

	// RTTI: proto::ThreatBallsGetMessage: the object answers the handles of the threat balls around it
	struct ThreatBallsGetMessage : public ThreatMessage
	{
		ThreatBallsGetMessage() : ThreatMessage(1), balls(0), count(0)
		{
		}
		virtual ~ThreatBallsGetMessage()
		{
		}

		engine::GameObjectHandle* balls;  // +0xC
		int count;  // +0x10
	};

	// RTTI: proto::ThreatGetInfoMessage: the threat answers what it is called and who it belongs to
	struct ThreatGetInfoMessage : public engine::IntrusiveMessage
	{
		ThreatGetInfoMessage() : engine::IntrusiveMessage(0x28, 4), owner(), target(), name(), unknown20(0), unknown24(-1)
		{
		}
		virtual ~ThreatGetInfoMessage()
		{
		}

		engine::GameObjectHandle owner;  // +0xC
		engine::GameObjectHandle target;  // +0x10
		int unknown14;
		core::Name<core::CaseSensitiveKey> name;  // +0x18
		int unknown20;
		int unknown24;
	};

	// RTTI: proto::DumpAlertCharactersDisguiseMsg: the characters that are alerted are dumped
	struct DumpAlertCharactersDisguiseMsg : public DisguiseMessage
	{
		DumpAlertCharactersDisguiseMsg() : DisguiseMessage(0x40)
		{
		}
		virtual ~DumpAlertCharactersDisguiseMsg()
		{
		}
	};

	// RTTI: proto::ReportAirStrikeUsedMsg: an air strike was used
	struct ReportAirStrikeUsedMsg : public DisguiseMessage
	{
		ReportAirStrikeUsedMsg() : DisguiseMessage(0x45)
		{
		}
		virtual ~ReportAirStrikeUsedMsg()
		{
		}
	};

	// RTTI: proto::ReportCallStrikeTeamUsedMsg: a strike team was called
	struct ReportCallStrikeTeamUsedMsg : public DisguiseMessage
	{
		ReportCallStrikeTeamUsedMsg() : DisguiseMessage(0x46)
		{
		}
		virtual ~ReportCallStrikeTeamUsedMsg()
		{
		}
	};

	// RTTI: proto::ForcePositionOutsideStateChangeMessage: the object is put outside
	struct ForcePositionOutsideStateChangeMessage : public StateChangeMessage
	{
		ForcePositionOutsideStateChangeMessage() : StateChangeMessage(0xc)
		{
		}
		virtual ~ForcePositionOutsideStateChangeMessage()
		{
		}

		int unknownC;
	};

	// RTTI: proto::ForcePositionUndergroundStateChangeMessage: the object is put underground
	struct ForcePositionUndergroundStateChangeMessage : public StateChangeMessage
	{
		ForcePositionUndergroundStateChangeMessage() : StateChangeMessage(0xd)
		{
		}
		virtual ~ForcePositionUndergroundStateChangeMessage()
		{
		}

		int unknownC;
	};
}

#endif
