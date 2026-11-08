// engine::PlaybackTreeBehaviour: see the header.
#include "code/engine/fight/behaviours/playbacktreebehaviour.h"
#include "code/core/heap.h"
#include "code/core/refptr.h"
#include "code/engine/fight/fighteventmessage.h"
#include "code/engine/playbackmessage.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"

namespace engine
{
	extern const char* gPlaybackContextName;

	// 0x1089AAC0 (kept copy in this unit): the helper the destructor releases the parameters with; the explicit
	// instantiation keeps it out of line
	template void core::SafeRelease<PlaybackParams>(PlaybackParams*&);

	// 0x10E77F10 / 0x1089AC40: the caster the class meta type of engine::FightTreeBehaviour carries for this class
	template struct content::BaseClassCasterImpl<FightTreeBehaviour, PlaybackTreeBehaviour>;

#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x108B0C30
	PlaybackParams::PlaybackParams(int value) : GameObjectParams(value)
	{
		unknown18 = false;
	}

	// FUNCTION: ENGINE 0x1089AA30
	content::ClassInfo* PlaybackTreeBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::PlaybackTreeBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1089AC70
	PlaybackTreeBehaviour::PlaybackTreeBehaviour(GameObject* newOwner)
		: FightTreeBehaviour(newOwner, 0), isBroadcastingStateChanges(false), noDestroyedMessage(false), watch(0)
	{
		finishedPending = false;
		overrideTimeSlicing = false;
		listening = true;
		unknown80 = true;
		Listen(7, true);
		Listen(0xb, true);
		Listen(0x14, true);
		Listen(0x16, true);
		Listen(0x17, true);
		const char* contextName = gPlaybackContextName;
		fight::Sequencer* sequencer = GetSequencer();
		sequencer->SetContextName(contextName);
		playbackParams = new PlaybackParams(0x10003);
		playbackParams->AddRef();
		playbackParams->unknown18 = true;
	}

	// FUNCTION: ENGINE 0x1089AD30
	PlaybackTreeBehaviour::~PlaybackTreeBehaviour()
	{
		core::SafeRelease(playbackParams);
	}

	// FUNCTION: ENGINE 0x1089AA70
	void PlaybackTreeBehaviour::Slot1()
	{
		FightTreeBehaviour::Slot1();
		playbackParams->handle = GetHandle(owner);
	}

	// FUNCTION: ENGINE 0x1089AE60
	content::MemberList* PlaybackTreeBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<FightTreeBehaviour>();
		static content::BaseClassCasterImpl<FightTreeBehaviour, PlaybackTreeBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<PlaybackTreeBehaviour, bool, 0>("pn"),
				ENGINE_OFFSET(PlaybackTreeBehaviour, isBroadcastingStateChanges), "isBroadcastingStateChanges" },
			{ content::GetMemberPrimitiveMetaType<PlaybackTreeBehaviour, bool, 1>("pn"),
				ENGINE_OFFSET(PlaybackTreeBehaviour, noDestroyedMessage), "noDestroyedMessage" },
			{ content::GetMemberPrimitiveMetaType<PlaybackTreeBehaviour, bool, 2>("pn"),
				ENGINE_OFFSET(PlaybackTreeBehaviour, forcePlaybackFinishedNotificationRequested), "forcePlaybackFinishedNotificationRequested" },
			{ content::GetMemberPrimitiveMetaType<PlaybackTreeBehaviour, bool, 3>("pn"),
				ENGINE_OFFSET(PlaybackTreeBehaviour, overrideTimeSlicing), "overrideTimeSlicing" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1089AFB0
	void PlaybackTreeBehaviour::Update(float dt, unsigned short mask)
	{
		if (listening && !overrideTimeSlicing)
		{
			Remove(2);
			listening = false;
		}
		unknown80 = false;
		if (sequencer.Unknown105A45A0(true))
		{
			core::HeapScope scope(0x75);
			sequencer.Advance(1, dt);
			fight::Branch* track = sequencer.track;
			sequencer.Update(0);
			sequencer.Unknown105A4910(false);
			if (watch.branch != track)
			{
				FightEventMessage message(0x10);
				owner->SendMessage(&message);
			}
			if (track != watch.branch)
			{
				if (watch.branch != 0)
				{
					watch.branch->Unregister(&watch);
				}
				watch.branch = track;
				if (track != 0)
				{
					track->Register(&watch);
				}
			}
			return;
		}
		Listen2(4, false);
		if (finishedPending || forcePlaybackFinishedNotificationRequested)
		{
			PlaybackFinishedMessage message(true);
			owner->SendMessage(&message);
			finishedPending = false;
		}
	}

	// FUNCTION: ENGINE 0x1089B0D0
	// EQUIVALENT: register allocation: the engine keeps the branch in ebp and the watched one in ebx (ours the other way round) and loads the
	// name's this pointer before the test of the empty state instead of behind it (85.5 %)
	void PlaybackTreeBehaviour::OnPostedMessage(Message* message)
	{
		GetPlaybackStateMessage* query = static_cast<GetPlaybackStateMessage*>(message);
		if (query->type == 0xb && query->id == 4)
		{
			fight::Branch* current = branch;
			if (current != 0)
			{
				fight::Branch* watched = watch.branch;
				if (watched != 0)
				{
					if (query->playbackSet.IsEmpty())
					{
						if (!query->state.IsEmpty())
						{
							if (!(query->state != query->requestedState))
							{
								return;
							}
							if (!query->requestedState.IsEmpty() && watched->name == query->requestedState)
							{
								query->state = query->requestedState;
								return;
							}
							core::Name<core::CaseSensitiveKey> multiple("__MULTIPLE__", 1);
							query->state = multiple;
							return;
						}
					}
					else if (!(query->playbackSet == current->name))
					{
						return;
					}
					query->state = watched->name;
				}
			}
		}
	}
}

// Kept copies (template instances of this unit's reflection):
// FUNCTION: ENGINE 0x1089AD60
// FUNCTION: ENGINE 0x1089ADA0
// FUNCTION: ENGINE 0x1089ADE0
// FUNCTION: ENGINE 0x1089AE20
