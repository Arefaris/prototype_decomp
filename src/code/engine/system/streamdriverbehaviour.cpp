// engine::StreamDriverBehaviour: see the header. The file name is a guess.
#include "code/engine/system/streamdriverbehaviour.h"

#include "code/engine/gameobject/gameobject.h"
#include "code/engine/system/streampackage.h"
#include "code/engine/system/streamtrigger.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10899830
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
		const math::Matrix& m = owner->transform->value;
		math::Vector position;
		position.Set(m.m[3][0], m.m[3][1], m.m[3][2]);
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
					for (unsigned int i = neighbours->end - neighbours->begin; i != 0;)
					{
						i--;
						StreamTrigger* trigger = neighbours->begin[i];
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
			for (unsigned int i = triggers->end - triggers->begin; i != 0;)
			{
				i--;
				StreamTrigger* trigger = triggers->begin[i];
				if (trigger->Contains(position, 0.0f))
				{
					found = trigger;
					break;
				}
			}
		}
		if (found != 0)
		{
			AddTriggerPackages(wanted, found, tags, 0, 1);
		}
		else
		{
			wanted->end = wanted->begin;
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
