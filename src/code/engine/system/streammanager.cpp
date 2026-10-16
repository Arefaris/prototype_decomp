// The stream manager's unit: see the header. The file name and the names are guesses.
#include "code/engine/system/streammanager.h"

#include "code/engine/system/streampackage.h"
#include "code/engine/system/streamtrigger.h"
#include "code/engine/system/tagset.h"
#include "code/math/vector.h"

namespace engine
{
	// FUNCTION: ENGINE 0x1082DB20
	// NONMATCHING: register allocation of the box centre, 92 %. Every call and store is the engine's and in its order;
	// the engine's three components come out in xmm0 / xmm1 / xmm2 with one `movss` store each, ours land in other
	// registers of the same file and its loads of the box corners commute the other way (the sums are written
	// `min + max` in both). Tried: a Vector temporary built with Add/Scale and then assigned (spills the temporary),
	// a Set of the three sums (arguments evaluate right to left, so the components come out in the other order) and
	// three float locals with a Set.
#ifdef NONMATCHING
	void AddTriggerPackages(StreamPackageArray* packages, StreamTrigger* trigger, const TagSet& tags, int count,
		int base)
	{
		packages->end = packages->begin;
		if (count == 0)
		{
			StreamPackage* package = trigger->FindPackage(tags);
			if (package != 0)
			{
				math::Vector centre;
				centre.Add(trigger->boundingBox.min, trigger->boundingBox.max);
				centre.Scale(0.5f);
				package->unknown4C = centre;
				packages->PushBack(package);
			}
		}
		StreamTriggerArray* neighbours = trigger->neighbourTriggers;
		if (neighbours != 0)
		{
			int budget = base + count;
			StreamCollect collect;
			collect.packages = packages;
			collect.tags = &tags;
			collect.count = count;
			collect.budget = budget;
			if (budget != 0)
			{
				CollectPackages(&collect, neighbours, 1);
			}
		}
	}
#endif
}
