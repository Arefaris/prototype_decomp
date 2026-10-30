// proto::CollectibleBehaviour (RTTI and reflection names; base engine::Behaviour): a pickup of the open world that
// lives for a while, fades out and tells the scenario when it is collected or expires. Reflected: the collectible
// type, the lifetime, the part of it left when the fade starts and the delay before it can be collected. Unit
// 0x10581620 - 0x10582170 (no assert path; the file name is a guess). The reflected names are original, the rest is
// guessed.
#ifndef PROTO_COLLECTIBLEBEHAVIOUR_H
#define PROTO_COLLECTIBLEBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/engine/scenariomessage.h"

namespace proto
{
	// The sizes and kinds of collectible (reflected as proto::CollectibleType)
	enum CollectibleType
	{
		COLLECTIBLE_NOT_SET = -1,
		COLLECTIBLE_SMALL = 0,
		COLLECTIBLE_MEDIUM = 1,
		COLLECTIBLE_LARGE = 2,
		COLLECTIBLE_OTHER = 3,
		COLLECTIBLE_LOCATION = 4,
		COLLECTIBLE_HINT = 5,
		COLLECTIBLE_WAYPOINT = 6
	};

	// The messages that configure a collectible (type 0x38; RTTI proto::CollectibleMessage and its three derived
	// messages; the field names and the ids are guesses)
	struct CollectibleMessage : public engine::IntrusiveMessage
	{
		CollectibleMessage(short newId) : engine::IntrusiveMessage(0x38, newId)
		{
		}
	};

	// Gives the collectible its type, its lifetime and its name (id 0)
	struct ConfigureMappedCollectibleMessage : public CollectibleMessage
	{
		ConfigureMappedCollectibleMessage() : CollectibleMessage(0)
		{
		}

		CollectibleType collectibleType;  // +0xC
		core::Name<core::CaseSensitiveKey> name;  // +0x10
		float maxLifetime;  // +0x18
		bool flag;  // +0x1C
	};

	// Gives the collectible its type and its name, without a lifetime (id 1)
	struct SetCollectibleTypeMessage : public CollectibleMessage
	{
		SetCollectibleTypeMessage() : CollectibleMessage(1)
		{
		}

		CollectibleType collectibleType;  // +0xC
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	// Switches the collectible on or off (id 2)
	struct SetCollectibleStateMessage : public CollectibleMessage
	{
		SetCollectibleStateMessage() : CollectibleMessage(2)
		{
		}

		bool enabled;  // +0xC
	};

	// The scenario messages a collectible sends when it is picked up (event 0x41) and when it is removed without
	// having been (event 0x42): the type of the collectible, its name and the object that took it. Their other
	// members are in another unit (0x10491890 - 0x10493220).
	struct CollectibleCollectedScenarioMessage : public engine::ScenarioMessage
	{
		CollectibleCollectedScenarioMessage(engine::GameObjectHandle collector, int newType,
			const core::Name<core::CaseSensitiveKey>& newName) : engine::ScenarioMessage(0x41),
			name((unknown1C = newType, newName))
		{
			handles[0] = collector;
		}
		virtual ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		core::Name<core::CaseSensitiveKey> name;  // +0x20
	};

	struct CollectibleEndOfLifeScenarioMessage : public engine::ScenarioMessage
	{
		CollectibleEndOfLifeScenarioMessage(int newType, const core::Name<core::CaseSensitiveKey>& newName) :
			engine::ScenarioMessage(0x42), name((unknown1C = newType, newName))
		{
		}
		virtual ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		core::Name<core::CaseSensitiveKey> name;  // +0x20
	};

	class CollectibleBehaviour : public engine::Behaviour
	{
	public:
		explicit CollectibleBehaviour(engine::GameObject* newOwner);
		virtual ~CollectibleBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// Starts the countdown to the fade-out when there is a lifetime (0x105816C0)
		void RestartFade();
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// 0x105816A0: takes the "enabled" flag from the message
		void SetEnabled(const SetCollectibleStateMessage* message);
		// 0x10581FC0 / 0x10582010: the two ways a collectible is configured
		void Configure(const ConfigureMappedCollectibleMessage* message);
		void SetType(const SetCollectibleTypeMessage* message);
		// 0x105816B0: restarts the age
		void ResetAge();
		// 0x10582060: the player (or another object) entering / leaving the collectible's trigger
		void OnTrigger(engine::GameObjectHandle handle, bool entering);
		// 0x105819A0: the collectible is picked up (tells the scenario and plays the pickup)
		void Collect();
		// 0x10581B40: sends the playback message of the collectible's current type
		void SendPlayback();
		// The pickup test shared by Update and OnTrigger
		void TryCollect();

		float maxLifetime;  // +0xC
		float age;  // +0x10
		float fadeStart;  // +0x14
		float percentOfLifetimeLeftToFadeAt;  // +0x18
		float timeDelayToCollect;  // +0x1C
		CollectibleType collectibleType;  // +0x20
		unsigned char unknown24[4];
		core::Name<core::CaseSensitiveKey> unknownName28;  // +0x28
		core::Name<core::CaseSensitiveKey> unknownName30;  // +0x30
		bool collected;  // +0x38
		bool unknown39;
		bool unknown3A;
		bool unknown3B;
	};
}

#endif
