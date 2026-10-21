// The knots of the vehicle graphs: see carattributes.h.
#include "code/engine/driving/carattributes.h"
#include "code/math/mathutils.h"

namespace engine
{
	namespace driving
	{
		// FUNCTION: ENGINE 0x10934910
		// EQUIVALENT: register allocation; the engine keeps the knot gap in xmm2 and the knot being compared in xmm1, ours the other way round, and the unrolled copies of the compare branch on the opposite condition; the loads, arithmetic and stores are the engine's
		void GraphKnots::SetKnot(unsigned int index, float value)
		{
			const float gap = 0.00001f;
			if (index < 5)
			{
				knots[index] = value;
				for (unsigned int step = 1; step <= index; step++)
				{
					unsigned int at = index - step;
					float limit = knots[at + 1] - gap;
					knots[at] = math::Min(knots[at], limit);
				}
				for (unsigned int at = index + 1; at < 5; at++)
				{
					float limit = knots[at - 1] + gap;
					knots[at] = math::Max(limit, knots[at]);
				}
			}
		}
	}
}
