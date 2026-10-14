#include <algorithm>

#include "code/ravenphysics/broadphase/broadphasedetector.h"

// The sorts of the detector's lists are the toolchain's <algorithm> for SortEntry; the unit keeps the instances it
// needs as COMDAT functions of its own, and the compiler reproduces every one of them
// FUNCTION: ENGINE 0x106B6CE0
template void std::_Med3<ravenphysics::SortEntry*>(ravenphysics::SortEntry*, ravenphysics::SortEntry*, ravenphysics::SortEntry*);

// FUNCTION: ENGINE 0x106B6D50
template void std::_Adjust_heap<ravenphysics::SortEntry*, int, ravenphysics::SortEntry>(ravenphysics::SortEntry*, int, int, ravenphysics::SortEntry);

// FUNCTION: ENGINE 0x106B76B0
template void std::_Median<ravenphysics::SortEntry*>(ravenphysics::SortEntry*, ravenphysics::SortEntry*, ravenphysics::SortEntry*);

// FUNCTION: ENGINE 0x106B7740
template void std::_Make_heap<ravenphysics::SortEntry*, int, ravenphysics::SortEntry>(ravenphysics::SortEntry*, ravenphysics::SortEntry*, int*, ravenphysics::SortEntry*);

// FUNCTION: ENGINE 0x106B8120
template std::pair<ravenphysics::SortEntry*, ravenphysics::SortEntry*> std::_Unguarded_partition<ravenphysics::SortEntry*>(ravenphysics::SortEntry*, ravenphysics::SortEntry*);

// FUNCTION: ENGINE 0x106B86C0
template void std::_Insertion_sort1<ravenphysics::SortEntry*, ravenphysics::SortEntry>(ravenphysics::SortEntry*, ravenphysics::SortEntry*, ravenphysics::SortEntry*);

// FUNCTION: ENGINE 0x106B91C0
template void std::_Sort_heap<ravenphysics::SortEntry*>(ravenphysics::SortEntry*, ravenphysics::SortEntry*);

// FUNCTION: ENGINE 0x106BA260
template void std::_Sort<ravenphysics::SortEntry*, int>(ravenphysics::SortEntry*, ravenphysics::SortEntry*, int);

// FUNCTION: ENGINE 0x106BA4A0
template void std::sort<ravenphysics::SortEntry*>(ravenphysics::SortEntry*, ravenphysics::SortEntry*);
