#include "code/proto/collectiblebehaviour.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/playbackmessage.h"
#include "code/proto/freeroamevents/freventmanager.h"

namespace content
{
	static const EnumValue sCollectibleTypeValues[] =
	{
		{ "Small", 0 },
		{ "Medium", 1 },
		{ "Large", 2 },
		{ "Other", 3 },
		{ "Location", 4 },
		{ "Hint", 5 },
		{ "Waypoint", 6 },
		{ "notSet", -1 }
	};

	// FUNCTION: ENGINE 0x10581620
	template<> void EnumInfo<proto::CollectibleType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::CollectibleType";
		*code = "p";
		*values = sCollectibleTypeValues;
		*count = 8;
	}
}

namespace engine
{
	class GameObject;
}

namespace proto
{
	// 0x10099560: the game object of the player with the index, null when there is none
	engine::GameObject* GetPlayerObject(int index);
	// 0x103C01F0: asks an object for the object it is linked to and answers it when it is the given one (name guess)
	engine::GameObject* GetLinkedObject(engine::GameObject* object);
	// Names of the unit's sounds and animations (0x11274E60 - 0x11274EA0; what they hold is unknown)
	core::Name<core::CaseSensitiveKey> gPlaybackSmall("small", 0);
	core::Name<core::CaseSensitiveKey> gPlaybackStandard("large", 0);
	core::Name<core::CaseSensitiveKey> gPlaybackLocation("location", 0);
	core::Name<core::CaseSensitiveKey> gPlaybackHint("hint", 0);
	core::Name<core::CaseSensitiveKey> gPlaybackWaypoint("initial", 0);
	core::Name<core::CaseSensitiveKey> gPlaybackExpire("final", 0);
	core::Name<core::CaseSensitiveKey> gPickupStandard("largeCollected", 0);
	core::Name<core::CaseSensitiveKey> gPickupSmall("smallCollected", 0);
	core::Name<core::CaseSensitiveKey> gPickupLocation("collected", 0);
	// The listeners of the collectible scenario messages (0x11274E58)
	extern engine::MessageListeners gCollectibleListeners;
	// 0x10078F70: whether the object is the first player's
	bool IsPlayerObject(engine::GameObject* object);

#define PROTO_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10581660
	content::ClassInfo* CollectibleBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CollectibleBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x105816A0
	void CollectibleBehaviour::SetEnabled(const SetCollectibleStateMessage* message)
	{
		unknown3B = message->enabled;
	}

	// FUNCTION: ENGINE 0x105816B0
	void CollectibleBehaviour::ResetAge()
	{
		age = 0.0f;
	}

	// FUNCTION: ENGINE 0x105816C0
	void CollectibleBehaviour::RestartFade()
	{
		if (maxLifetime > 0.0f)
		{
			fadeStart = maxLifetime - percentOfLifetimeLeftToFadeAt * maxLifetime;
			Listen2(4, true);
			return;
		}
		Listen2(4, false);
	}

	// FUNCTION: ENGINE 0x10581860
	CollectibleBehaviour::CollectibleBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		maxLifetime(-1.0f), age(0.0f), fadeStart(0.0f), percentOfLifetimeLeftToFadeAt(0.25f), timeDelayToCollect(0.0f),
		collectibleType(COLLECTIBLE_NOT_SET), unknownName28((const char*)0, 1), unknownName30(), collected(false),
		unknown39(false), unknown3A(false), unknown3B(true)
	{
		Listen(0x38, true);
		Listen(0xd, true);
		Listen(2, true);
	}

	// FUNCTION: ENGINE 0x10581FC0
	void CollectibleBehaviour::Configure(const ConfigureMappedCollectibleMessage* message)
	{
		collectibleType = message->collectibleType;
		maxLifetime = message->maxLifetime;
		unknownName30 = message->name;
		unknown3A = message->flag;
		ResetAge();
		SendPlayback();
		RestartFade();
	}

	// FUNCTION: ENGINE 0x10582010
	void CollectibleBehaviour::SetType(const SetCollectibleTypeMessage* message)
	{
		collectibleType = message->collectibleType;
		unknownName28 = message->name;
		maxLifetime = -1.0f;
		ResetAge();
		SendPlayback();
		RestartFade();
	}

	// FUNCTION: ENGINE 0x10581D10
	content::MemberList* CollectibleBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, CollectibleBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<CollectibleType>(),
				0x20, "collectibleType" },
			{ content::GetMemberPrimitiveMetaType<CollectibleBehaviour, float, 0>("p"),
				PROTO_OFFSET(CollectibleBehaviour, maxLifetime), "maxLifetime" },
			{ content::GetMemberPrimitiveMetaType<CollectibleBehaviour, float, 1>("p"),
				PROTO_OFFSET(CollectibleBehaviour, percentOfLifetimeLeftToFadeAt), "percentOfLifetimeLeftToFadeAt" },
			{ content::GetMemberPrimitiveMetaType<CollectibleBehaviour, float, 2>("p"),
				PROTO_OFFSET(CollectibleBehaviour, timeDelayToCollect), "timeDelayToCollect" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}
}

namespace proto
{
	__forceinline void CollectibleBehaviour::TryCollect()
	{
		switch (collectibleType)
		{
		case COLLECTIBLE_LOCATION:
		case COLLECTIBLE_HINT:
			Collect();
			return;
		}
		if (GetLinkedObject(GetPlayerObject(0)) != 0)
		{
			return;
		}
		Collect();
	}

	// FUNCTION: ENGINE 0x10582060
	void CollectibleBehaviour::OnTrigger(engine::GameObjectHandle handle, bool entering)
	{
		if (entering)
		{
			if (!collected && handle.IsValid() && IsPlayerObject(handle.Get()))
			{
				unknown39 = true;
				if (unknown3B && age >= timeDelayToCollect)
				{
					TryCollect();
				}
			}
		}
		else
		{
			engine::GameObject* object = handle.Get();
			if (object != 0 && IsPlayerObject(object))
			{
				unknown39 = false;
			}
		}
	}

	// FUNCTION: ENGINE 0x10582170
	void CollectibleBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 2:
			ResetAge();
			break;
		case 0xd:
			switch ((unsigned short)message->id)
			{
			case 3:
				OnTrigger(static_cast<engine::ScenarioMessage*>(message)->handles[1], true);
				break;
			case 4:
				OnTrigger(static_cast<engine::ScenarioMessage*>(message)->handles[1], false);
				break;
			}
			break;
		case 0x38:
			switch ((unsigned short)message->id)
			{
			case 0:
				Configure(static_cast<ConfigureMappedCollectibleMessage*>(message));
				break;
			case 1:
				SetType(static_cast<SetCollectibleTypeMessage*>(message));
				break;
			case 2:
				SetEnabled(static_cast<SetCollectibleStateMessage*>(message));
				break;
			}
			break;
		}
	}
}

namespace proto
{
	// FUNCTION: ENGINE 0x10581920
	CollectibleBehaviour::~CollectibleBehaviour()
	{
		if (unknown3A)
		{
			CollectibleEndOfLifeScenarioMessage message(collectibleType, unknownName30);
			engine::SendMessage(&message, &gCollectibleListeners);
		}
	}
}

namespace proto
{
	// FUNCTION: ENGINE 0x10581B40
	void CollectibleBehaviour::SendPlayback()
	{
		core::Name<core::CaseSensitiveKey> playback = gPlaybackWaypoint;
		switch (collectibleType)
		{
		case COLLECTIBLE_SMALL:
		case COLLECTIBLE_MEDIUM:
		case COLLECTIBLE_LARGE:
		case COLLECTIBLE_OTHER:
			playback = gPlaybackStandard;
			break;
		case COLLECTIBLE_LOCATION:
			playback = gPlaybackLocation;
			break;
		case COLLECTIBLE_HINT:
			playback = gPlaybackHint;
			break;
		case COLLECTIBLE_WAYPOINT:
			playback = gPlaybackWaypoint;
			break;
		}
		core::Name<core::CaseSensitiveKey> empty("", 1);
		engine::PlaybackMessage message(playback, empty, false, false, 1.0f);
		owner->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x10581EA0
	void CollectibleBehaviour::Update(float dt, unsigned short mask)
	{
		age += dt;
		if (unknown3B && !collected && unknown39 && age >= timeDelayToCollect)
		{
			TryCollect();
		}
		if (age > maxLifetime && !collected)
		{
			core::Name<core::CaseSensitiveKey> empty("", 1);
			engine::PlaybackMessage message(gPlaybackExpire, empty, false, false, 0.0f);
			owner->SendMessage(&message);
			Listen2(4, false);
		}
	}

	// FUNCTION: ENGINE 0x10581990
	void CollectibleBehaviour::Slot1()
	{
		RestartFade();
	}

	// FUNCTION: ENGINE 0x105819A0
	void CollectibleBehaviour::Collect()
	{
		if (collectibleType != COLLECTIBLE_NOT_SET)
		{
			CollectibleCollectedScenarioMessage message(engine::GetHandle(owner), collectibleType, unknownName30);
			engine::SendMessage(&message, &gCollectibleListeners);
		}
		switch (collectibleType)
		{
		case COLLECTIBLE_SMALL:
		case COLLECTIBLE_MEDIUM:
		case COLLECTIBLE_LARGE:
		case COLLECTIBLE_OTHER:
			{
				core::Name<core::CaseSensitiveKey> empty("", 1);
				engine::PlaybackMessage message(gPickupStandard, empty, false, false, 0.0f);
				owner->SendMessage(&message);
			}
			break;
		case COLLECTIBLE_LOCATION:
		case COLLECTIBLE_HINT:
		case COLLECTIBLE_WAYPOINT:
			{
				core::Name<core::CaseSensitiveKey> empty("", 1);
				engine::PlaybackMessage message(gPickupLocation, empty, false, false, 0.0f);
				owner->SendMessage(&message);
			}
			break;
		}
		collected = true;
		if (!unknownName28.IsEmpty())
		{
			switch (collectibleType)
			{
			case COLLECTIBLE_LOCATION:
				gFREventManager->locationLog.Add(&unknownName28);
				break;
			case COLLECTIBLE_HINT:
				gFREventManager->hintLog.Add(&unknownName28);
				break;
			}
		}
	}
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D65160
// FUNCTION: ENGINE 0x10D65190
// FUNCTION: ENGINE 0x10D651C0
// FUNCTION: ENGINE 0x10D651F0
// FUNCTION: ENGINE 0x10D65220
// FUNCTION: ENGINE 0x10D65250
// FUNCTION: ENGINE 0x10D65280
// FUNCTION: ENGINE 0x10D652B0
// FUNCTION: ENGINE 0x10D652E0
// FUNCTION: ENGINE 0x10D86210
// FUNCTION: ENGINE 0x10D86220
// FUNCTION: ENGINE 0x10D86230
// FUNCTION: ENGINE 0x10D86240
// FUNCTION: ENGINE 0x10D86250
// FUNCTION: ENGINE 0x10D86260
// FUNCTION: ENGINE 0x10D86270
// FUNCTION: ENGINE 0x10D86280
// FUNCTION: ENGINE 0x10D86290
