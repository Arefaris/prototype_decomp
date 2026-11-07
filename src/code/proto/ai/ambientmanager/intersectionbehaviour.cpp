#include "code/proto/ai/ambientmanager/intersectionbehaviour.h"
#include "code/proto/reflectedstubs.h"

namespace proto
{
	// FUNCTION: ENGINE 0x10430750
	IntersectionBehaviour::IntersectionBehaviour(engine::GameObject* newOwner, IntersectionData* newData) :
		engine::Behaviour(newOwner), data(newData), phase(-1), timeLeft(0.0f)
	{
		Listen2(4, true);
		Listen(0x24, true);
	}

	// FUNCTION: ENGINE 0x10430A30
	void IntersectionBehaviour::Update(float dt, unsigned short mask)
	{
		timeLeft -= dt;
		if (timeLeft <= 0.0f)
		{
			int count = data->phasesEnd - data->phasesBegin;
			phase = (phase + 1) % count;
			timeLeft = data->phasesBegin[phase].duration + timeLeft;
		}
	}
}
