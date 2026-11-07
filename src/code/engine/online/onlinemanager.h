// engine::OnlineManager (code/engine/online/onlinemanager.cpp; the name is the one its own operator new passes to
// the allocator) and its peer, engine::ConsoleManagerPeer. Only the allocations the unit defines are reconstructed
// here: the classes' members, their bases and their vftables belong to the rest of the unit.
#ifndef ENGINE_ONLINE_ONLINEMANAGER_H
#define ENGINE_ONLINE_ONLINEMANAGER_H

#include "code/core/time.h"
#include "code/engine/system/simulationdriver.h"

namespace engine
{
	// 0x108EC860: what the manager classes' operator new forwards to. The second argument picks the heap the block
	// comes from (0 is heap 0x81, 2 is heap 0x82, 1 is the heap the global at 0x111E2060 holds) and the third is
	// the class name, which the release build does not use.
	void* AllocateManagerObject(unsigned int size, int heap, const char* name);
	// 0x108EC840: gives such an object back
	void FreeManagerObject(void* object);

	class ChannelManager;
	class ConsoleManagerPeer;

	// RTTI: engine::OnlineManager (0x9C bytes; bases ISimulationDriver and SimulationDriverTimeData): the simulation
	// driver of an online session. It wraps the driver the game ran before (inner) and steps it through the net
	// layer. The members are guesses.
	class OnlineManager : public ISimulationDriver
	{
	public:
		// 0x108BEF80 / 0x108EC840
		static void* operator new(unsigned int size);
		static void operator delete(void* block)
		{
			FreeManagerObject(block);
		}

		// 0x108BF160
		OnlineManager();
		// 0x108BF880 (deleting destructor 0x108BF8A0)
		virtual ~OnlineManager();

		// The driver's slots: the ones the manager does not step itself go to the inner driver
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual bool Slot4();
		virtual void Slot5();
		virtual void Slot9();

		// 0x108BF690: takes the session down
		void Shutdown();
		// 0x108BF520: keeps the clock in step with the real one
		void UpdateClock();

		ChannelManager* channels;  // +0x70
		ConsoleManagerPeer* console;  // +0x74
		SimulationDriver* inner;  // +0x78
		void* unknown7C;
		int stepsThisFrame;  // +0x80
		core::Time clock;  // +0x84
		int rate;  // +0x90
		void* unknown94;
		void* unknown98;
	};

	class ConsoleManager
	{
	public:
		class Callback;
	};

	class ConsoleManagerPeer : public ConsoleManager
	{
	public:
		// 0x108BEFA0
		static void* operator new(unsigned int size);
	};
}

#endif
