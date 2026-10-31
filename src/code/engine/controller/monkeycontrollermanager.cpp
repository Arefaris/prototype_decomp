#include "code/engine/controller/monkeycontrollermanager.h"

namespace engine
{
	namespace controller
	{
		// FUNCTION: ENGINE 0x10890950
		MonkeyControllerManager::~MonkeyControllerManager()
		{
			InputSystem::Get()->SetManager(inner, false);
		}

		// FUNCTION: ENGINE 0x10890980
		void MonkeyControllerManager::SetFlags(unsigned int id, unsigned int flags, bool set)
		{
			inner->SetFlags(id, flags, set);
		}

		// FUNCTION: ENGINE 0x10890990
		void MonkeyControllerManager::SetValue(unsigned int id, int value)
		{
			inner->SetValue(id, value);
		}

		// FUNCTION: ENGINE 0x108909A0
		// EQUIVALENT: register allocation (the engine jumps through eax, ours through edx; 80 %)
		void MonkeyControllerManager::Refresh()
		{
			inner->Refresh();
		}

		// FUNCTION: ENGINE 0x10890970
		void MonkeyControllerManager::Collect(container::SListBase* players)
		{
			inner->Collect(players);
		}

		// FUNCTION: ENGINE 0x108909B0
		void MonkeyControllerManager::OnFlags(unsigned int id, unsigned int flags, bool set, int which)
		{
			callback->OnFlags(id, flags, set, which);
		}

		// FUNCTION: ENGINE 0x108909C0
		void MonkeyControllerManager::OnValue(unsigned int id, int value)
		{
			callback->OnValue(id, value);
		}

		// FUNCTION: ENGINE 0x108909D0
		void MonkeyControllerManager::OnRelease(unsigned int id, int value)
		{
			callback->OnRelease(id, value);
		}
	}
}
