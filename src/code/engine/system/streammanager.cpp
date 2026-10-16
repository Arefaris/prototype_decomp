// The stream manager's unit: see the header. The file name and the names are guesses.
#include "code/engine/system/streammanager.h"

#include "code/engine/system/streampackage.h"
#include "code/engine/system/streamtrigger.h"
#include "code/engine/system/tagset.h"
#include "code/math/vector.h"

namespace engine
{
	// FUNCTION: ENGINE 0x1082DB20
	// NONMATCHING: the engine's centre is fully scalarised (the three sums, one 0.5f and the three products live in
	// xmm0 - xmm3 and go straight into the package) and its three statements evaluate in x, y, z order; ours rotates
	// the three register assignments and sinks each store behind its product, 85.3 %
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
				float x = trigger->boundingBox.min.x + trigger->boundingBox.max.x;
				float y = trigger->boundingBox.min.y + trigger->boundingBox.max.y;
				float z = trigger->boundingBox.min.z + trigger->boundingBox.max.z;
				package->unknown4C.x = x * 0.5f;
				package->unknown4C.y = y * 0.5f;
				package->unknown4C.z = z * 0.5f;
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
