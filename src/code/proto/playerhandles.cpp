// The players' game object handles and the local player (unit 0x104DBBB0 - 0x104DC4A0; no assert path, the file name is a
// guess).
#include "code/engine/gameobject/gameobjecthandle.h"

namespace engine
{
	// 0x107F2850
	bool IsLocalSlot(int slot);
}

namespace proto
{
	// FUNCTION: ENGINE 0x104DBCA0
	int GetLocalPlayerIndex()
	{
		for (int i = 0; i < 1; i++)
		{
			if (engine::IsLocalSlot(i))
			{
				return i;
			}
		}
		return -1;
	}
}
