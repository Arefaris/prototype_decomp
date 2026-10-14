// proto::VehicleBehaviourAmbient (path from the unit's own assert string: code\proto\ai\ambientmanager\behaviours\
// vehiclebehaviourambient.cpp). Only the two functions below are reconstructed; the rest of the unit (the reflected
// members, the update 0x1044F060, the message dispatch 0x1044F710 and the state machine) is not.
#include "code/proto/ai/ambientmanager/behaviours/vehiclebehaviourambient.h"

#include "code/engine/gameobject/gameobject.h"
#include "code/math/matrix.h"

namespace proto
{
	// The navigation mesh the ambient managers share (the global 0x112730C0): the array of area records at +0x38. Each
	// record is 0x40 bytes and keeps the list of the vehicles standing in it at +0x28 (the 16-bit index at +0x36 is
	// another of its fields, read by the pedestrian code).
	class NavArea
	{
	public:
		unsigned char unknown0[0x28];
		container::ListBase::Node* vehicles;
		unsigned char unknown2C[0x40 - 0x2c];
	};

	class NavMesh
	{
	public:
		unsigned char unknown0[0x38];
		NavArea* areas;
	};

	extern NavMesh* gNavMesh;

	// The area a path node lies in, or null when the node names none
	static NavArea* GetArea(PathNode* node)
	{
		unsigned short index = node->areaLink->area;
		if (index == 0xffff)
		{
			return 0;
		}
		return &gNavMesh->areas[index];
	}

	// A vehicle behaviour of the ambient manager is the object its list node at 0x68 sits in
	static VehicleBehaviourAmbient* BehaviourOf(container::ListBase::Node* node)
	{
		return (VehicleBehaviourAmbient*)((char*)node - 0x68);
	}

	// FUNCTION: ENGINE 0x104421F0
	bool VehicleBehaviourAmbient::GetUnknown84()
	{
		return halted;
	}

	// FUNCTION: ENGINE 0x104438C0
	// NONMATCHING: the shape is the original's (the list of ambient vehicles is walked per run of path nodes that
	// share an area, and the car ahead is picked by the distance between the two owners' transforms), but the loop
	// and index forms were not brought to byte identity.
#ifdef NONMATCHING
	bool VehicleBehaviourAmbient::IsVehicleAhead(float maxDistanceSquared)
	{
		container::ListBase::Node* node = node68.next;
		int count = path88.Count();
		for (int i = 0; i < count; i++)
		{
			PathNode* here = path88.At(i);
			for (; node != 0; node = node->next)
			{
				VehicleBehaviourAmbient* vehicle = BehaviourOf(node);
				if (!vehicle->halted)
				{
					continue;
				}
				if (vehicle->IsBlocking())
				{
					continue;
				}
				if (vehicle->path88.Count() <= 0)
				{
					continue;
				}
				if (here->link->key != vehicle->path88.At(0)->link->key)
				{
					continue;
				}
				const math::Matrix& mine = owner->transform->Get();
				const math::Matrix& theirs = vehicle->owner->transform->Get();
				float dx = mine.m[3][0] - theirs.m[3][0];
				float dy = mine.m[3][1] - theirs.m[3][1];
				float dz = mine.m[3][2] - theirs.m[3][2];
				return dz * dz + dy * dy + dx * dx < maxDistanceSquared;
			}
			NavArea* area = GetArea(here);
			// the next run of nodes belongs to the next area (the run is skipped, the next round walks it)
			if (i < count - 1)
			{
				int last = i;
				for (;;)
				{
					last++;
					if (last >= count - 1 || area != GetArea(path88.At(last)))
					{
						break;
					}
				}
				i = last - 1;
			}
			node = area != 0 ? area->vehicles : 0;
		}
		return false;
	}
#endif
}
