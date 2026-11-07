// The messages of proto::IntersectionBehaviour (a unit of intersectionbehaviour.cpp, apart from it because the messages
// clash with the declarations that file includes): the state of the lights for a direction and the behaviour itself.
#include "code/proto/ai/ambientmanager/ambientmanagermessages.h"
#include "code/proto/ai/ambientmanager/intersectionbehaviour.h"

namespace proto
{
	// FUNCTION: ENGINE 0x104307C0
	void IntersectionBehaviour::AnswerBehaviour(GetIntersectionBehaviourMessage* message)
	{
		message->behaviour = this;
	}

	// FUNCTION: ENGINE 0x10430AA0
	void IntersectionBehaviour::AnswerState(GetIntersectionStateMessage* message)
	{
		int direction = message->direction;
		IntersectionData::Phase* current = &data->phases.begin[phase];
		if (direction >= 0 && direction < (int)current->states.Size())
		{
			message->state = phase;
			message->lightState = current->states.begin[direction];
			message->timeLeft = timeLeft;
			message->phaseDuration = current->duration;
		}
	}

	// FUNCTION: ENGINE 0x10430B00
	void IntersectionBehaviour::OnMessage(engine::Message* message)
	{
		if (message->type == 0x24)
		{
			switch ((unsigned short)message->id)
			{
			case 0:
				AnswerState((GetIntersectionStateMessage*)message);
				break;
			case 1:
				AnswerBehaviour((GetIntersectionBehaviourMessage*)message);
				break;
			}
		}
	}

	// FUNCTION: ENGINE 0x10430B40
	int IntersectionBehaviour::GetLightState(int direction)
	{
		return data->phases.begin[phase].states.begin[direction];
	}
}
