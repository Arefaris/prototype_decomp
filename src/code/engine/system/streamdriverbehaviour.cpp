// engine::StreamDriverBehaviour: see the header. The file name is a guess.
#include "code/engine/system/streamdriverbehaviour.h"

#include "code/engine/gameobject/gameobject.h"
#include "code/engine/system/streampackage.h"
#include "code/engine/system/streamtrigger.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10899830
	// EQUIVALENT: scheduling and block layout (33.1 %): the engine lays the search of the trigger out in another order
	// and loads the position through other registers; every call, test and store is the same
	void StreamDriverBehaviour::Update(float dt, unsigned short mask)
	{
		if (unknown4D)
		{
			if (transitioning)
			{
				transitioning = false;
				Unknown1082BF40();
			}
			return;
		}
		math::Vector position;
		owner->transform->value.GetTranslation(position);
		StreamTrigger* found = 0;
		if (last != 0)
		{
			if (last->Contains(position, 0.0f))
			{
				unknown4C = false;
				found = last;
			}
			else
			{
				StreamTriggerArray* neighbours = last->neighbourTriggers;
				if (neighbours != 0)
				{
					for (unsigned int i = neighbours->end - neighbours->begin; i != 0; i--)
					{
						StreamTrigger* trigger = neighbours->begin[i - 1];
						if (trigger->Contains(position, 0.0f))
						{
							found = trigger;
							break;
						}
					}
				}
			}
		}
		if (found == 0)
		{
			for (unsigned int i = triggers->end - triggers->begin; i != 0; i--)
			{
				StreamTrigger* trigger = triggers->begin[i - 1];
				if (trigger->Contains(position, 0.0f))
				{
					found = trigger;
					break;
				}
			}
		}
		if (found == 0)
		{
			wanted->end = wanted->begin;
		}
		else
		{
			AddTriggerPackages(wanted, found, tags, 0, 1);
		}
		StreamPackage* package = 0;
		if (found != 0)
		{
			package = found->FindPackage(tags);
			if (unknown50)
			{
				if (!package->IsLoaded() && !unknown51)
				{
					Unknown104B1860(true);
					unknown51 = true;
				}
				else if (package->IsLoaded() && unknown51)
				{
					Unknown104B1860(false);
					unknown51 = false;
				}
			}
		}
		Unknown10899770(current, &position, package);
		Unknown10899770(wanted, &position, package);
		UpdateStreamTransition(&wanted, &current, &transitioning, restricted);
		last = found;
	}
}
