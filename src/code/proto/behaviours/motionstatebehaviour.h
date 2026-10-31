// proto::MotionStateBehaviour (RTTI and reflection names; base engine::Behaviour): the motion state of a character
// (idling, walking, running, ...) which it tells the scenario about (proto::MotionStateScenarioMessage). Reflected: the
// state (proto::MotionState::State) and a name. Unit 0x10075450 - 0x10076370 (no assert path; the file name is a
// guess). The reflected names are original, the rest is guessed; only the reflection is reconstructed.
#ifndef PROTO_BEHAVIOURS_MOTIONSTATEBEHAVIOUR_H
#define PROTO_BEHAVIOURS_MOTIONSTATEBEHAVIOUR_H

#include "code/content/enummetatype.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/proto/fightitems/motion/motionmessages.h"

namespace proto
{
	// RTTI proto::MotionState: only the enumeration is known
	struct MotionState
	{
		enum State
		{
			STATE_NOT_SET = -1,
			STATE_IDLING = 0,
			STATE_WALKING = 1,
			STATE_RUNNING = 2,
			STATE_FALLING = 3,
			STATE_JUMPING = 4,
			STATE_WALLRUNNING = 5,
			STATE_GETTING_HIT = 6,
			STATE_ATTACK_WINDUP = 7,
			STATE_ATTACK_RELEASE = 8,
			STATE_FLYING = 9,
			STATE_CLIMBING = 10,
			STATE_BEING_GRABBED = 11,
			STATE_DRIVING = 12,
			STATE_BLOCKING = 13,
			STATE_STUNNED = 14,
			STATE_GLIDING = 15,
			STATE_JUMPING_OUT_OF_WATER = 16,
			STATE_CONSUMING = 17,
			STATE_DEVASTATOR = 18,
			STATE_SLIDING = 19,
			STATE_OTHER = 20
		};
	};

	// Turns the broadcast of the state to the scenario on or off (id 0xC)
	struct SetBroadcastMotionStateMsg : public CharacterMotionMessage
	{
		explicit SetBroadcastMotionStateMsg(bool newBroadcast) : CharacterMotionMessage(0xc), broadcast(newBroadcast)
		{
		}
		virtual ~SetBroadcastMotionStateMsg()
		{
		}

		bool broadcast;  // +0xC
	};

	class MotionStateBehaviour : public engine::Behaviour
	{
	public:
		// 0x10075710
		explicit MotionStateBehaviour(engine::GameObject* newOwner);
		// 0x100759C0 (deleting destructor)
		virtual ~MotionStateBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 6 (0x100759F0)
		virtual void OnMessage(engine::Message* message);

		// 0x10075880: forgets the state
		void Reset();
		// 0x10075590: turns the broadcast on or off
		void SetBroadcast(bool broadcast);
		// 0x10075780: takes a new state and tells the scenario and the fight system of it
		void SetState(int newState, const core::Name<core::CaseSensitiveKey>& newName);

		unsigned char unknownC[4];
		core::Name<core::CaseSensitiveKey> name;  // +0x10
		MotionState::State motionState;  // +0x18
		bool unknown1C;
	};
}

#endif
