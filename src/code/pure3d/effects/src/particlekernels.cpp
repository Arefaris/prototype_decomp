// The particle update kernels (unit around 0x107836D0 - 0x10791D00; the file name is a guess, the functions are
// named after what the first of them show, the others by the bit that selects them). Names are guesses.
#include "code/math/mathconstants.h"
#include "code/math/mathutils.h"
#include "code/pure3d/effects/particles.h"

namespace pure3d
{
	// The kernels of the unit keep the math helpers out of line (the unit is too big for the inlining budget)
	#pragma inline_depth(0)

	// FUNCTION: ENGINE 0x107837F0
	// EQUIVALENT: the same instructions; the engine keeps the loop constants in other SSE registers
	void UpdateFrameBlend(float dt, unsigned int count, int unknown2, ParticleFrameBlend* blends,
		const float* newFrames, void* unknown5, float* ages, const float* lifeTime)
	{
		float life = *lifeTime;
		if (count > 0)
		{
			bool noLife = math::IsEqual(life, 0.0f, math::EPSILON_SMALL);
			float* to = &blends->to;
			unsigned int i = 0;
			do
			{
				float age = ages[i] - dt;
				ages[i] = age;
				if (age <= 0.0f)
				{
					float next = *to;
					float from = to[-1];
					ages[i] = life;
					if (from != next)
					{
						to[-1] = next;
					}
					else
					{
						to[-1] = newFrames[i];
					}
					*to = newFrames[i];
				}
				to[1] = noLife ? 0.0f : 1.0f - ages[i] / life;
				i++;
				to += 3;
			}
			while (--count != 0);
		}
	}

	// FUNCTION: ENGINE 0x1078B550
	void UpdateNothing(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d)
	{
	}
}
