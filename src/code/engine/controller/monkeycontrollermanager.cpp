#include "code/engine/controller/monkeycontrollermanager.h"
#include "code/core/strings.h"
#include "code/engine/frontend/frontend.h"
#include <stdlib.h>

namespace engine
{
	// 0x10848EE0 (another unit): the value of a command line option
	const char* GetCommandLineValue(const char* option);

	namespace controller
	{
		MonkeyControllerManager* gMonkeyControllerManager;

		// FUNCTION: ENGINE 0x10890A20
		MonkeyControllerManager::MonkeyControllerManager()
		{
			random.Seed(0);
			inner = InputSystem::Get()->manager;
			InputSystem::Get()->SetManager(this, false);
			unknownC = 0.0f;
			unknown10 = false;
			unknown20 = 0;
			allowStart = false;
			focused = true;
			stayInFE = false;
			timeout = -999.0f;
			const char* seed = GetCommandLineValue("Monkey");
			if (seed != 0)
			{
				unsigned int value = atoi(seed);
				random.Seed(value, value);
			}
			const char* options = GetCommandLineValue("MonkeyOptions");
			if (options != 0)
			{
				if (core::StrNCmp(options, "AllowStart", 10) == 0)
				{
					allowStart = true;
				}
				else if (core::StrNCmp(options, "StayInFE", 10) == 0)
				{
					stayInFE = true;
				}
			}
			const char* timeoutText = GetCommandLineValue("MonkeyTimeout");
			if (timeoutText != 0)
			{
				timeout = (float)atof(timeoutText);
			}
		}

		// FUNCTION: ENGINE 0x108909E0
		void MonkeyControllerManager::SetFocus(const char* name)
		{
			const char* current = InputSystem::Get()->config.name;
			if (name != 0 && *name != 0 && core::StrNCmp(name, current, 20) != 0)
			{
				focused = false;
				return;
			}
			focused = true;
		}

		// FUNCTION: ENGINE 0x10890930
		MonkeyControllerManager* GetMonkeyControllerManager()
		{
			return gMonkeyControllerManager;
		}

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
		void MonkeyControllerManager::Release(unsigned int id, int slot)
		{
			inner->Release(id, slot);
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

	// FUNCTION: ENGINE 0x10890910
	void ShutdownInputConfig()
	{
		if (controller::gMonkeyControllerManager != 0)
		{
			delete controller::gMonkeyControllerManager;
			controller::gMonkeyControllerManager = 0;
		}
	}

	// FUNCTION: ENGINE 0x108925B0
	void InitInputConfig()
	{
		if (HasCommandLineOption("Monkey") && controller::gMonkeyControllerManager == 0)
		{
			controller::gMonkeyControllerManager = new controller::MonkeyControllerManager();
		}
	}
}
