#include "code/proto/ai/ambientmanager/intersectionbehaviour.h"
#include "code/proto/reflectedstubs.h"

namespace engine
{
	namespace driving
	{
		// 0x10D94F78: 0.0f in the pooled constants (name guess)
		extern const float gZero;
	}
}

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
			int count = data->phases.end - data->phases.begin;
			phase = (phase + 1) % count;
			timeLeft = data->phases.begin[phase].duration + timeLeft;
		}
	}

	// FUNCTION: ENGINE 0x10430B60
	bool IntersectionBehaviour::GetGreenTimeLeft(int direction, float* time)
	{
		*time = timeLeft;
		IntersectionData::PhaseArray& phases = data->phases;
		IntersectionData::Phase* begin = phases.begin;
		int current = phase;
		int state = begin[current].states.begin[direction];
		if (state != IntersectionData::STATE_YELLOW && state != IntersectionData::STATE_RED)
		{
			int count = phases.end - begin;
			int next = (current + 1) % count;
			if (next != current)
			{
				do
				{
					IntersectionData::Phase* other = &data->phases.begin[next];
					if (other->states.begin[direction] != IntersectionData::STATE_GREEN)
					{
						break;
					}
					*time = other->duration + *time;
					next = (next + 1) % count;
				}
				while (next != phase);
			}
			float left = *time - PedBehaviourTunables::sInstance->unknown518;
			if (left > engine::driving::gZero)
			{
				*time = left;
				return true;
			}
		}
		return false;
	}
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104307B0
// FUNCTION: ENGINE 0x10430A00
