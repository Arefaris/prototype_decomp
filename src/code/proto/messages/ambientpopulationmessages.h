// The messages of the ambient population (RTTI names): the vehicle spawn and level of detail messages of the ambient
// message family (type 0x24), the render message that resets what a pedestrian senses, the world query for the ambient
// packages and the two messages that start up the threat behaviours (type 0x28). The members behind the ids are guesses
// from the constructors and the handlers.
#ifndef PROTO_MESSAGES_AMBIENTPOPULATIONMESSAGES_H
#define PROTO_MESSAGES_AMBIENTPOPULATIONMESSAGES_H

#include "code/core/name.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"
#include "code/math/sphere.h"
#include "code/math/vector.h"
#include "code/proto/messages/airequestmessages.h"
#include "code/proto/messages/ambientmessages.h"

namespace fight
{
	class Branch;
}

namespace proto
{
	// Id 7: makes an ambient vehicle (0x3C bytes)
	struct SpawnVehicleMessage : public AmbientMessage
	{
		SpawnVehicleMessage(const math::Vector& newPosition, const math::Vector& newDirection,
			const math::Vector& newVelocity, int newType, int newFlags, bool newFlag) : AmbientMessage(7),
			position(newPosition), direction(newDirection), velocity(newVelocity), type(newType), flags(newFlags),
			flag(newFlag)
		{
		}
		virtual ~SpawnVehicleMessage()
		{
		}

		math::Vector position;  // +0xC
		math::Vector direction;  // +0x18
		math::Vector velocity;  // +0x24
		int type;  // +0x30
		int flags;  // +0x34
		bool flag;  // +0x38
	};

	// Id 0x18: asks whether the physics of a vehicle runs in the high level of detail
	struct GetVehiclePhysicsLODMessage : public AmbientMessage
	{
		GetVehiclePhysicsLODMessage() : AmbientMessage(0x18), high(false)
		{
		}
		virtual ~GetVehiclePhysicsLODMessage()
		{
		}

		bool high;  // +0xC
	};

	// Id 0x19
	struct SetPhysicsLODHighMessage : public AmbientMessage
	{
		explicit SetPhysicsLODHighMessage(bool newHigh) : AmbientMessage(0x19), high(newHigh)
		{
		}
		virtual ~SetPhysicsLODHighMessage()
		{
		}

		bool high;  // +0xC
	};

	// Id 0x1A: the answer starts true
	struct IsPhysicsDownGradeAbleMessage : public AmbientMessage
	{
		IsPhysicsDownGradeAbleMessage() : AmbientMessage(0x1a), downgradeable(true)
		{
		}
		virtual ~IsPhysicsDownGradeAbleMessage()
		{
		}

		bool downgradeable;  // +0xC
	};

	// Id 0x12: marks a vehicle as parked under a name
	struct SetAsParkedCarMessage : public AmbientMessage
	{
		SetAsParkedCarMessage() : AmbientMessage(0x12), name("", 1)
		{
		}
		virtual ~SetAsParkedCarMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	// Render message 0x10
	struct ResetSensesInfoMessage : public ProtoRenderMsg
	{
		ResetSensesInfoMessage() : ProtoRenderMsg(0x10)
		{
		}
		virtual ~ResetSensesInfoMessage()
		{
		}
	};

	// World message 1: the names of the ambient packages
	struct WorldGetAmbientPackagesMessage : public WorldMsg
	{
		WorldGetAmbientPackagesMessage() : WorldMsg(1)
		{
		}
		virtual ~WorldGetAmbientPackagesMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	// Type 0x28, id 2: sets a threat ball up
	struct ThreatBallInitializeMessage : public engine::IntrusiveMessage
	{
		ThreatBallInitializeMessage(const math::Sphere& newSphere, const math::Vector& newPosition, float newTime,
			core::Name<core::CaseSensitiveKey> newName, engine::GameObjectHandle newOwner, fight::Branch* newBranch,
			int newValue) : engine::IntrusiveMessage(0x28, 2), sphere(newSphere), position(newPosition),
			time(newTime), name(newName), owner(newOwner), branch(newBranch), value(newValue)
		{
		}
		virtual ~ThreatBallInitializeMessage()
		{
		}

		math::Sphere sphere;  // +0xC
		math::Vector position;  // +0x1C
		float time;  // +0x28
		int unknown2C;
		core::Name<core::CaseSensitiveKey> name;  // +0x30
		engine::GameObjectHandle owner;  // +0x38
		fight::Branch* branch;  // +0x3C
		int value;  // +0x40
	};

	// Type 0x28, id 3: sets a threat up
	struct ThreatInitializeMessage : public engine::IntrusiveMessage
	{
		ThreatInitializeMessage(float newTime, core::Name<core::CaseSensitiveKey> newName, int newValue, int newOther,
			fight::Branch* newBranch, int newLast) : engine::IntrusiveMessage(0x28, 3), time(newTime), name(newName),
			value(newValue), other(newOther), branch(newBranch), last(newLast)
		{
		}
		virtual ~ThreatInitializeMessage()
		{
		}

		float time;  // +0xC
		core::Name<core::CaseSensitiveKey> name;  // +0x10
		int value;  // +0x18
		int other;  // +0x1C
		fight::Branch* branch;  // +0x20
		int last;  // +0x24
	};
}

#endif
