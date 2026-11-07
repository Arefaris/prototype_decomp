// proto::IntersectionBehaviour (RTTI name; base engine::Behaviour): runs the traffic light cycle of one road
// intersection. It steps through the phases of its proto::IntersectionData, each lasting its duration (the
// message type 0x24 answers the current phase and takes a new intersection). Unit 0x10430750 - 0x10430E00 (the
// behaviour is made by proto::IntersectionSpawner; no assert path names it, the file name is a guess). The members
// are guessed; only the construction and the cycle are reconstructed.
#ifndef PROTO_AI_AMBIENTMANAGER_INTERSECTIONBEHAVIOUR_H
#define PROTO_AI_AMBIENTMANAGER_INTERSECTIONBEHAVIOUR_H

#include "code/engine/gameobject/behaviour.h"
#include "code/proto/ai/ambientmanager/intersectiondata.h"

namespace proto
{

	struct GetIntersectionStateMessage;
	struct GetIntersectionBehaviourMessage;

	class IntersectionBehaviour : public engine::Behaviour
	{
	public:
		// 0x10430750
		IntersectionBehaviour(engine::GameObject* newOwner, IntersectionData* newData);
		// the deleting destructor is 0x10430A00 (the destructor is the compiler's)

		// vftable slot 4 (0x10430A30): steps to the next phase when the time of the current one has run out
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x10430B00): the message type 0x24 answers the current phase and takes a new intersection
		virtual void OnMessage(engine::Message* message);

		// 0x10430AA0 / 0x104307C0: the answers to the two messages
		void AnswerState(GetIntersectionStateMessage* message);
		void AnswerBehaviour(GetIntersectionBehaviourMessage* message);
		// 0x10430B40: the state of the light for a direction in the current phase
		int GetLightState(int direction);

		IntersectionData* data;  // +0xC
		int phase;  // +0x10
		float timeLeft;  // +0x14
	};
}

#endif
