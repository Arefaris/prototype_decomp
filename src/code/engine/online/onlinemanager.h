// engine::OnlineManager (code/engine/online/onlinemanager.cpp; the name is the one its own operator new passes to
// the allocator) and its peer, engine::ConsoleManagerPeer. Only the allocations the unit defines are reconstructed
// here: the classes' members, their bases and their vftables belong to the rest of the unit.
#ifndef ENGINE_ONLINE_ONLINEMANAGER_H
#define ENGINE_ONLINE_ONLINEMANAGER_H

namespace engine
{
	// 0x108EC860: what the manager classes' operator new forwards to. The second argument picks the heap the block
	// comes from (0 is heap 0x81, 2 is heap 0x82, 1 is the heap the global at 0x111E2060 holds) and the third is
	// the class name, which the release build does not use.
	void* AllocateManagerObject(unsigned int size, int heap, const char* name);

	class OnlineManager
	{
	public:
		// 0x108BEF80
		static void* operator new(unsigned int size);
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
