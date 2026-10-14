// Sorted lists of range endpoints of the sweep (unit around 0x106D8610 - 0x106DB000; file name and function names
// are guesses).
#include <math.h>

#include "code/math/vector.h"
#include "code/ravenphysics/broadphase/broadphasedetector.h"
#include "code/ravenphysics/common/stackallocator.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x106D9260
	// NONMATCHING: the original keeps the index in ebp, the loop pointers in esi / edi and works through copies in
	// eax / ecx; ours picks other registers (about 30 % of the instructions line up)
#ifdef NONMATCHING
	int BuildEndpoints(const BroadPhaseBox* boxes, unsigned int boxCount, const unsigned char* flags,
		unsigned int flagCount, Endpoint* second, unsigned int secondCount, Endpoint* first,
		unsigned int firstCount, unsigned int total, unsigned int firstBoxes)
	{
		unsigned int i = 0;
		Endpoint* begin = first;
		Endpoint* end = first + 1;
		int count = 0;
		for (; i < firstBoxes; i++)
		{
			Endpoint& b = *begin;
			Endpoint& e = *end;
			b.position = boxes[i].boundsMin.x;
			e.position = boxes[i].boundsMax.x;
			b.box = i;
			b.kind = 2;
			e.box = i;
			e.kind = 0;
			begin += 2;
			end += 2;
			if (e.position <= b.position)
			{
				begin -= 2;
				end -= 2;
			}
			if (!(fabs((double)b.position) < 1e12f) || !(fabs((double)e.position) < 1e12f))
			{
				begin -= 2;
				end -= 2;
			}
		}
		begin = second;
		end = second + 1;
		for (i = firstBoxes; i < total; i++)
		{
			Endpoint& b = *begin;
			Endpoint& e = *end;
			b.position = boxes[i].boundsMin.x;
			e.position = boxes[i].boundsMax.x;
			b.box = i;
			b.kind = 2 - ((flags[i >> 3] & (1 << (i & 7))) != 0);
			e.box = i;
			e.kind = 0;
			begin += 2;
			end += 2;
			count += 2;
			if (e.position <= b.position)
			{
				begin -= 2;
				end -= 2;
				count -= 2;
			}
			if (!(fabs((double)b.position) < 1e12f) || !(fabs((double)e.position) < 1e12f))
			{
				begin -= 2;
				end -= 2;
				count -= 2;
			}
		}
		return count;
	}
#endif
}

// The unit's instances of StackAllocator::AllocArray
// FUNCTION: ENGINE 0x106D8790
template float* ravenphysics::StackAllocator::AllocArray<float>(int, int);

// FUNCTION: ENGINE 0x106D87C0
template math::Vector* ravenphysics::StackAllocator::AllocArray<math::Vector>(int, int);
