// engine::ConsoleManager::Callback (RTTI name; a list node of container::SListLite<Callback>): what the network
// console manager tells the classes that listen to it (the sync commands, the online game database helper, the
// exception manager, the peers ...). Six virtual slots: the defaults of five do nothing, slot 4 asks the manager.
// Unit 0x10882BC0 - 0x10882C20 (no assert path; the directory and file name are guesses). Slot names and the
// parameters are guesses; the engine kept the constructor and the defaults as functions of their own.
#ifndef ENGINE_ONLINE_CONSOLEMANAGERCALLBACK_H
#define ENGINE_ONLINE_CONSOLEMANAGERCALLBACK_H

#include "code/container/slist.h"
#include "code/engine/online/onlinemanager.h"

namespace engine
{
	class ConsoleManager::Callback : public container::SListLite<ConsoleManager::Callback>::Node
	{
	public:
		// 0x10882BC0
		Callback();

		// 0x10882BD0, 0x10882BE0, 0x10882BF0, 0x10882C00: do nothing
		virtual void Slot0(int a, int b);
		virtual void Slot1(int a, int b);
		virtual void Slot2(int a);
		virtual void Slot3(int a, int b);
		// 0x108C4900 (another unit): asks the manager
		virtual void Slot4();
		// 0x10882C10: does nothing
		virtual void Slot5(int a);

		int unknown8;
		int unknownC;
	};
}

#endif
