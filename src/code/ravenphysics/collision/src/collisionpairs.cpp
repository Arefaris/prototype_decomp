// The pair tests between collision objects (unit around 0x106A3B40 - 0x106A5400; file name and function names are
// guesses).
#include "code/ravenphysics/common/stackallocator.h"

// The unit's instances of StackAllocator::AllocArray
// FUNCTION: ENGINE 0x106A3EE0
template unsigned short* ravenphysics::StackAllocator::AllocArray<unsigned short>(int, int);
