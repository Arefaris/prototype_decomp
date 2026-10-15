// engine::OnlineManager (code/engine/online/onlinemanager.cpp): the manager the network simulation runs through.
// Every class of the unit allocates itself out of its own heap, through the shared helper 0x108EC860.
#include "code/engine/online/onlinemanager.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108BEF80
	void* OnlineManager::operator new(unsigned int size)
	{
		return AllocateManagerObject(size, 0, "OnlineManager");
	}

	// FUNCTION: ENGINE 0x108BEFA0
	void* ConsoleManagerPeer::operator new(unsigned int size)
	{
		return AllocateManagerObject(size, 0, "ConsoleManagerPeer");
	}
}
