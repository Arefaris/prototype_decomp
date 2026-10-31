// The messages the code half of the ai fight items (conditions' Evaluate and the actions) sends to game objects. The messages are
// declared by other units of the engine (RTTI names; the constructors are inline there and expanded in every user), the member
// names and the argument lists are guesses from the users.
#ifndef PROTO_FIGHTITEMS_AI_AICODEMESSAGES_H
#define PROTO_FIGHTITEMS_AI_AICODEMESSAGES_H

#include "code/engine/message.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/core/name.h"

namespace proto
{
	// RTTI: proto::EnterPoisonExDamageMessage: a poison starts on the object
	struct EnterPoisonExDamageMessage : public engine::IntrusiveMessage
	{
		EnterPoisonExDamageMessage(int newPoisonType, float newDamageRate, float newDamageSpikes, float newTimeToHit, float newExtraRandomTime, int unused = 0)
			: engine::IntrusiveMessage(0x14, 0x14), poisonType(newPoisonType), damageRate(newDamageRate), damageSpikes(newDamageSpikes),
			timeToHit(newTimeToHit), extraRandomTime(newExtraRandomTime)
		{
		}
		virtual ~EnterPoisonExDamageMessage()
		{
		}

		int poisonType;  // +0xC
		float damageRate;  // +0x10
		float damageSpikes;  // +0x14
		float timeToHit;  // +0x18
		float extraRandomTime;  // +0x1C
	};

	// RTTI: proto::ExitPoisonDamageMessage: a poison ends
	struct ExitPoisonDamageMessage : public engine::IntrusiveMessage
	{
		ExitPoisonDamageMessage() : engine::IntrusiveMessage(0x14, 0x15), poisonType(0x13), source(), unknown14(0.0f)
		{
		}
		virtual ~ExitPoisonDamageMessage()
		{
		}

		int poisonType;  // +0xC
		engine::HandleBase source;  // +0x10
		float unknown14;
	};

	// RTTI: proto::GetPoisonedTimeDamageMessage: the object answers how long its poison of a type still lasts
	struct GetPoisonedTimeDamageMessage : public engine::IntrusiveMessage
	{
		explicit GetPoisonedTimeDamageMessage(int newPoisonType) : engine::IntrusiveMessage(0x14, 0x16), poisonType(newPoisonType)
		{
		}
		virtual ~GetPoisonedTimeDamageMessage()
		{
		}

		int poisonType;  // +0xC
		float time;  // +0x10
	};

	// RTTI: proto::SetPoisonCloudParametersDamageMessage: how the poison cloud of the object behaves
	struct SetPoisonCloudParametersDamageMessage : public engine::IntrusiveMessage
	{
		SetPoisonCloudParametersDamageMessage() : engine::IntrusiveMessage(0x14, 0x17), growFacingDir(false), growDownDir(false), inheritFacingDir(false),
			fallToGroundSpeed(-1.0f), unknown14(-1.0f), unknown18(-1.0f), unknown1C(-1.0f), unknown20(-1.0f), unknown24(-1.0f)
		{
		}
		virtual ~SetPoisonCloudParametersDamageMessage()
		{
		}

		bool growFacingDir;  // +0xC
		bool growDownDir;  // +0xD
		bool inheritFacingDir;  // +0xE
		float fallToGroundSpeed;  // +0x10
		float unknown14;
		float unknown18;
		float unknown1C;
		float unknown20;
		float unknown24;
	};

	// RTTI: proto::StateChangeMessage: the base of the messages about a character's state (message type 0x2F)
	struct StateChangeMessage : public engine::IntrusiveMessage
	{
		explicit StateChangeMessage(short newId) : engine::IntrusiveMessage(0x2f, newId)
		{
		}
		virtual ~StateChangeMessage()
		{
		}
	};

	// RTTI: proto::GetStateStateChangeMessage: the object answers the name of its state
	struct GetStateStateChangeMessage : public StateChangeMessage
	{
		GetStateStateChangeMessage() : StateChangeMessage(0), state()
		{
		}
		virtual ~GetStateStateChangeMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> state;  // +0x10
	};

	// RTTI: proto::VehicleMessage: the base of the messages about a vehicle (message type 0x31)
	struct VehicleMessage : public engine::IntrusiveMessage
	{
		explicit VehicleMessage(short newId) : engine::IntrusiveMessage(0x31, newId)
		{
		}
		virtual ~VehicleMessage()
		{
		}
	};

	// RTTI: proto::SetVehicleStateVehicleMessage: the vehicle goes into a named state
	struct SetVehicleStateVehicleMessage : public VehicleMessage
	{
		explicit SetVehicleStateVehicleMessage(core::Name<core::CaseSensitiveKey> newState) : VehicleMessage(3), state(newState)
		{
		}
		virtual ~SetVehicleStateVehicleMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> state;  // +0x10
	};

	// RTTI: proto::GetVehicleStateVehicleMessage: the vehicle answers the name of its state
	struct GetVehicleStateVehicleMessage : public VehicleMessage
	{
		GetVehicleStateVehicleMessage() : VehicleMessage(4), state()
		{
		}
		virtual ~GetVehicleStateVehicleMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> state;  // +0x10
	};
	// RTTI: proto::AIMessage: the base of the messages to the ai of an object (message type 0x2B)
	struct AIMessage : public engine::IntrusiveMessage
	{
		explicit AIMessage(short newId) : engine::IntrusiveMessage(0x2b, newId)
		{
		}
		virtual ~AIMessage()
		{
		}
	};

	// RTTI: proto::AtRoofsEdgeAIMsg: the object answers how long it has stood at the edge of its roof and whether it does
	struct AtRoofsEdgeAIMsg : public AIMessage
	{
		AtRoofsEdgeAIMsg() : AIMessage(0xe), time(0.0f), atEdge(false)
		{
		}
		virtual ~AtRoofsEdgeAIMsg()
		{
		}

		float time;  // +0xC
		bool atEdge;  // +0x10
	};

	// RTTI: proto::ActivateStayOnRooftopBehaviourMsg
	struct ActivateStayOnRooftopBehaviourMsg : public AIMessage
	{
		explicit ActivateStayOnRooftopBehaviourMsg(bool newActive) : AIMessage(0xf), active(newActive)
		{
		}
		virtual ~ActivateStayOnRooftopBehaviourMsg()
		{
		}

		bool active;  // +0xC
	};
	// RTTI: proto::GrabMessage: the base of the messages about grabbing (message type 0x1F)
	class GrabMessage : public engine::IntrusiveMessage
	{
	public:
		explicit GrabMessage(short newId) : engine::IntrusiveMessage(0x1f, newId)
		{
		}
		virtual ~GrabMessage()
		{
		}
	};

	// RTTI: proto::GetGrabbedObjectMessage: the object answers what it holds in a named grab slot (0x1006F9E0 is the engine's copy of the constructor)
	class GetGrabbedObjectMessage : public GrabMessage
	{
	public:
		explicit GetGrabbedObjectMessage(const core::Name<core::CaseSensitiveKey>* newSlot) : GrabMessage(0), slot(newSlot), grabbed()
		{
		}
		virtual ~GetGrabbedObjectMessage()
		{
		}

		const core::Name<core::CaseSensitiveKey>* slot;  // +0xC
		engine::GameObjectHandle grabbed;  // +0x10
	};

	// RTTI: proto::SpawnMessage: the base of the messages about spawning (message type 0x29)
	struct SpawnMessage : public engine::IntrusiveMessage
	{
		explicit SpawnMessage(short newId) : engine::IntrusiveMessage(0x29, newId)
		{
		}
		virtual ~SpawnMessage()
		{
		}
	};

	// RTTI: proto::IsReadySpawnMessage: the object answers whether it is ready to spawn
	struct IsReadySpawnMessage : public SpawnMessage
	{
		IsReadySpawnMessage() : SpawnMessage(10), ready(false)
		{
		}
		virtual ~IsReadySpawnMessage()
		{
		}

		bool ready;  // +0xC
	};

	// RTTI: proto::GetSpawnTemplateSpawnMessage: the object answers the name of the template it spawns
	struct GetSpawnTemplateSpawnMessage : public SpawnMessage
	{
		GetSpawnTemplateSpawnMessage() : SpawnMessage(0xc), templateName()
		{
		}
		virtual ~GetSpawnTemplateSpawnMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> templateName;  // +0x10
	};

	// RTTI: proto::ObjectSpawnedSpawnMessage: an object was spawned
	struct ObjectSpawnedSpawnMessage : public SpawnMessage
	{
		ObjectSpawnedSpawnMessage(engine::GameObjectHandle newSpawned, bool newLastGuy) : SpawnMessage(9), spawned(newSpawned), lastGuy(newLastGuy)
		{
		}
		virtual ~ObjectSpawnedSpawnMessage()
		{
		}

		engine::GameObjectHandle spawned;  // +0xC
		bool lastGuy;  // +0x10
	};
}

#endif
