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

	// The online manager as the other units see it (the type the global is mapped with); the manager's clock update
	// is another unit's function of the same object
	struct OnlineManagerView
	{
		// 0x108BF430
		void Unknown108BF430();
	};

	// FUNCTION: ENGINE 0x108BF160
	OnlineManager::OnlineManager() : channels(0), console(0), inner(0), clock(0, 0), unknown94(0)
	{
	}

	// FUNCTION: ENGINE 0x108BF880
	OnlineManager::~OnlineManager()
	{
		Shutdown();
	}

	// FUNCTION: ENGINE 0x108BF460
	void OnlineManager::Slot1()
	{
		inner->Slot1();
		time6 = inner->time6;
		time5 = inner->time5;
		((OnlineManagerView*)this)->Unknown108BF430();
	}

	// FUNCTION: ENGINE 0x108BF4A0
	void OnlineManager::Slot2()
	{
		inner->Slot2();
	}

	// FUNCTION: ENGINE 0x108BF4B0
	void OnlineManager::Slot3()
	{
		stepsThisFrame = 0;
		clock.Clear();
	}

	// FUNCTION: ENGINE 0x108BF870
	void OnlineManager::Slot5()
	{
		UpdateClock();
	}

	// FUNCTION: ENGINE 0x108BF5B0
	void OnlineManager::Slot9()
	{
		ISimulationDriver::Slot9();
		inner->Slot9();
	}

	// FUNCTION: ENGINE 0x108BEFC0
	void* ChannelManager::operator new(unsigned int size)
	{
		return AllocateManagerObject(size, 0, "ChannelManager");
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
