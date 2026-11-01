// engine::PlaybackTreeBehaviour (RTTI name, vftable 0x10E77F18, 8 slots, base engine::FightTreeBehaviour) and the
// parameters it runs its tree with (engine::PlaybackParams, base engine::GameObjectParams): the fight tree behaviour of
// the playbacks. It listens to the NIS (7), fight (0xB), health (0x14), 0x16 and NIS (0x17) messages, names its
// sequencer after the "Playback" fight context and tells its object when a playback is over. Unit 0x1089AA30 -
// 0x1089B3B0 (no assert path; the file name is a guess); member names are guesses except the reflected ones.
#ifndef ENGINE_FIGHT_BEHAVIOURS_PLAYBACKTREEBEHAVIOUR_H
#define ENGINE_FIGHT_BEHAVIOURS_PLAYBACKTREEBEHAVIOUR_H

#include "code/engine/fight/behaviours/fighttreebehaviour.h"

namespace engine
{
	// RTTI: engine::PlaybackParams (3 vftable slots, 0x1C bytes)
	class PlaybackParams : public GameObjectParams
	{
	public:
		// 0x108B0C30
		explicit PlaybackParams(int value);

		bool unknown18;  // +0x18
	};

	// RTTI: engine::PlaybackFinishedMessage (type 0xB, id 9; base engine::IntrusiveMessage): a playback ended
	struct PlaybackFinishedMessage : public IntrusiveMessage
	{
		explicit PlaybackFinishedMessage(bool newForced) : IntrusiveMessage(0xb, 9), forced(newForced)
		{
		}
		virtual ~PlaybackFinishedMessage()
		{
		}

		bool forced;  // +0xC
	};

	class PlaybackTreeBehaviour : public FightTreeBehaviour
	{
	public:
		// 0x1089AC70
		explicit PlaybackTreeBehaviour(GameObject* newOwner);
		// vftable slot 7 (0x1089AF90 is the deleting destructor, 0x1089AD30 the body)
		virtual ~PlaybackTreeBehaviour();

		// 0x1089AA30 / 0x1089AE60
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x1089AA70): the base's, then the parameters learn the owner's handle
		virtual void Slot1();
		// vftable slot 4 (0x1089AFB0): advances the sequencer, tells the object when the branch it runs changes and when the
		// playback is over
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 5 (0x1089B0D0): answers the playback state queries
		virtual void OnPostedMessage(Message* message);
		// vftable slot 6 (0x1089B1E0): not reconstructed yet
		virtual void OnMessage(Message* message);

		bool isBroadcastingStateChanges;  // +0x68
		bool noDestroyedMessage;  // +0x69
		PlaybackParams* playbackParams;  // +0x6C
		fight::BranchWatch watch;  // +0x70: the branch the sequencer ran when the object was last told
		bool finishedPending;  // +0x7C
		bool overrideTimeSlicing;  // +0x7D
		bool forcePlaybackFinishedNotificationRequested;  // +0x7E
		bool listening;  // +0x7F
		bool unknown80;
		unsigned char unknown81[7];
	};
}

#endif
