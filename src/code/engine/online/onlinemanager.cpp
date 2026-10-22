// engine::OnlineManager (code/engine/online/onlinemanager.cpp): the manager the network simulation runs through.
// Every class of the unit allocates itself out of its own heap, through the shared helper 0x108EC860.
#include "code/engine/online/onlinemanager.h"
#include "code/engine/online/consolemanagercallback.h"

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

	// FUNCTION: ENGINE 0x10882BC0
	ConsoleManager::Callback::Callback()
	{
		unknownC = 0;
	}

	// FUNCTION: ENGINE 0x10882BD0
	void ConsoleManager::Callback::Slot0(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x10882BE0
	void ConsoleManager::Callback::Slot1(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x10882BF0
	void ConsoleManager::Callback::Slot2(int a)
	{
	}

	// FUNCTION: ENGINE 0x10882C00
	void ConsoleManager::Callback::Slot3(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x10882C10
	void ConsoleManager::Callback::Slot5(int a)
	{
	}
}
