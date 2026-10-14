// Sorted lists of range endpoints of the sweep (unit around 0x106D8610 - 0x106DB000; file name and function names
// are guesses).
#include <math.h>

#include "code/math/vector.h"
#include "code/ravenphysics/broadphase/broadphasedetector.h"
#include "code/ravenphysics/common/stackallocator.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x106D9260
	// NONMATCHING: the original keeps its loop pointers in esi / edi and works through copies in eax / ecx; ours
	// folds the copies and orders the stores differently
#ifdef NONMATCHING
	int BuildEndpoints(const BroadPhaseBox* boxes, unsigned int boxCount, const unsigned char* flags,
		unsigned int flagCount, Endpoint* second, unsigned int secondCount, Endpoint* first,
		unsigned int firstCount, unsigned int total, unsigned int firstBoxes)
	{
		Endpoint* nextBegin = first;
		Endpoint* nextEnd = first + 1;
		unsigned int i = 0;
		for (; i < firstBoxes; i++)
		{
			Endpoint* begin = nextBegin;
			Endpoint* end = nextEnd;
			begin->position = boxes[i].boundsMin.x;
			end->position = boxes[i].boundsMax.x;
			begin->box = i;
			begin->kind = 2;
			float endPosition = end->position;
			end->box = i;
			end->kind = 0;
			float beginPosition = begin->position;
			nextBegin = begin + 2;
			nextEnd = end + 2;
			if (endPosition <= beginPosition)
			{
				nextBegin = begin;
				nextEnd = end;
			}
			if (1e12f <= fabs(beginPosition) || 1e12f <= fabs(endPosition))
			{
				nextBegin -= 2;
				nextEnd -= 2;
			}
		}
		int count = 0;
		nextBegin = second;
		nextEnd = second + 1;
		for (i = firstBoxes; i < total; i++)
		{
			Endpoint* begin = nextBegin;
			Endpoint* end = nextEnd;
			begin->position = boxes[i].boundsMin.x;
			end->position = boxes[i].boundsMax.x;
			begin->box = i;
			begin->kind = 2 - ((flags[i >> 3] & (1 << (i & 7))) != 0);
			float endPosition = end->position;
			end->box = i;
			end->kind = 0;
			float beginPosition = begin->position;
			nextBegin = begin + 2;
			nextEnd = end + 2;
			int nextCount = count + 2;
			if (endPosition <= beginPosition)
			{
				nextBegin = begin;
				nextEnd = end;
				nextCount = count;
			}
			count = nextCount;
			if (1e12f <= fabs(beginPosition) || 1e12f <= fabs(endPosition))
			{
				nextBegin -= 2;
				nextEnd -= 2;
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
