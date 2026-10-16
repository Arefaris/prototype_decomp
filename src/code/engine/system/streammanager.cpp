// The stream manager's unit: see the header. The file name and the names are guesses.
#include "code/engine/system/streammanager.h"

#include "code/engine/system/streampackage.h"
#include "code/engine/system/streamtrigger.h"
#include "code/engine/system/tagset.h"
#include "code/math/vector.h"

namespace engine
{
	// FUNCTION: ENGINE 0x1082DB20
	// EQUIVALENT: operand order of the x sum: the engine loads min.x and adds max.x, this compiler loads max.x and adds
	// min.x (98.9 %)
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
				centre.x = trigger->boundingBox.max.x + trigger->boundingBox.min.x;
				centre.y = trigger->boundingBox.max.y + trigger->boundingBox.min.y;
				centre.z = trigger->boundingBox.max.z + trigger->boundingBox.min.z;
				centre.Scale(0.5f);
				package->unknown4C.x = centre.x;
				package->unknown4C.y = centre.y;
				package->unknown4C.z = centre.z;
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
}
