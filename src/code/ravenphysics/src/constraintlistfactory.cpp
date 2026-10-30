// The list of constraints a physics object factory makes for its body (unit 0x106A56B0 - 0x106A6E00, no assert path,
// so the file name is a guess): the entries, the pair mask they clear and the set of joints made from them.
#include "code/ravenphysics/constraintlistfactory.h"
#include "code/ravenphysics/constraints/constraint.h"
#include "code/ravenphysics/physicsobject.h"

namespace ravenphysics
{
	// The bit of a pair of objects in a mask (another unit, 0x1065FC30 / 0x1065FB20)
	int GetPairIndex(int count, unsigned int first, unsigned int second);
	void SetBit(unsigned char* bits, unsigned int index, bool value);

	// FUNCTION: ENGINE 0x106A5730
	ConstraintListFactory::ConstraintSpec::ConstraintSpec()
	{
		objectAIndex = 0;
		objectBIndex = 1;
		constraint = 0;
	}

	// FUNCTION: ENGINE 0x106A5750
	ConstraintListFactory::ConstraintSpec::~ConstraintSpec()
	{
		if (constraint != 0)
		{
			delete constraint;
			constraint = 0;
		}
	}

	// FUNCTION: ENGINE 0x106A5770
	void ConstraintListFactory::ConstraintSpec::ClearPair(unsigned char* mask, int count)
	{
		unsigned int index = GetPairIndex(count, objectAIndex, objectBIndex);
		SetBit(mask, index, false);
	}

	// FUNCTION: ENGINE 0x106A5F90
	int JointSet::Count()
	{
		return end - begin;
	}

	// FUNCTION: ENGINE 0x106A5FB0
	// NONMATCHING: 16.7 %: the engine keeps the factory in edi, loads the end of the list again for the count and counts down in ebx; ours allocates other registers and orders the loads differently
#ifdef NONMATCHING
	void ConstraintListFactory::ApplyPairMask(unsigned char* mask, int count)
	{
		if (specsBegin != specsEnd && mask != 0)
		{
			int total = specsEnd - specsBegin;
			if (total != 0)
			{
				for (int i = 0; i != total; i++)
				{
					specsBegin[i].ClearPair(mask, count);
				}
			}
		}
	}
#endif
}
