#include "code/engine/controller/defaultcontrollerhandler.h"
#include "code/engine/function.h"

// The Windows calls the constructor makes (the single-instance check)
extern "C"
{
	extern void* (__stdcall* _imp__CreateMutexA)(void* attributes, int initialOwner, const char* name);
	extern unsigned long (__stdcall* _imp__GetLastError)();
	extern int (__stdcall* _imp__CloseHandle)(void* handle);
}

namespace engine
{
	// 0x10848E70 (another unit)
	bool HasCommandLineOption(const char* option);
	// 0x10882900 / 0x10882910 (the pause state's unit): flags the front end keeps (names guessed)
	void SetPauseFlagA(bool value);
	void SetPauseFlagB(bool value);

	namespace controller
	{
		// 0x111D3FD4: the controller the game falls back to (the first one, 0xFE00 | 2 at the start; name guess)
		extern unsigned int gDefaultController;
		// 0x11317840: set while a controller is locked (name guess)
		extern bool gControllerLocked;

		// 0x108A0B40 (another unit): enables the controller (or all of them with -1) of the physical controller
		// manager, locked to the second argument (names guessed)
		class PhysicalControllerManagerView
		{
		public:
			void Unknown108A0B40(int a, unsigned int b);
		};

		// The input system's virtual functions as the handler calls them: slot 1 takes a controller id and a slot (-1:
		// none), although the declared slot 1 takes none (the object may be another class on the same slots)
		class InputSystemView
		{
		public:
			virtual void Slot0();
			virtual void ReleaseSlot(unsigned int id, int slot);
		};

		// FUNCTION: ENGINE 0x10895BD0
		DefaultControllerHandler::~DefaultControllerHandler()
		{
			GetScriptManager()->Unregister(this);
		}

		// FUNCTION: ENGINE 0x10895BF0
		void DefaultControllerHandler::LockController(unsigned int unused)
		{
			gDefaultController = 0xFE02;
			Slot3();
			OLS* ols = OLS::Get();
			ols->profile->SelectProfile(0);
			gControllerLocked = true;
		}

		// FUNCTION: ENGINE 0x10895C20
		// EQUIVALENT: the engine loads the locked controller into ecx and pushes it before it loads the physical manager
		// and the minus one (which it makes with or), ours loads the controller into eax and pushes it after the other
		// two, 80.3 %
		void DefaultControllerHandler::UnlockAllControllers()
		{
			InputSystem* input = InputSystem::Get();
			for (int i = 0; i < input->controllerCount; i++)
			{
				unsigned int id = (i & 0xFF) | 0xFE00;
				input->ClearPlayerFlags(id, 2);
				input->ClearPlayerFlags(id, 8);
				input->ClearPlayerFlags(id, 4);
				((InputSystemView*)input)->ReleaseSlot(id, -1);
			}
			if (!secondInstance && !HasCommandLineOption("EnableAllControllers"))
			{
				((PhysicalControllerManagerView*)input->physical)->Unknown108A0B40(-1, controller);
			}
			controller = 0xFFFFFFFF;
			SetPauseFlagA(false);
			SetPauseFlagB(false);
			gControllerLocked = false;
		}

		// FUNCTION: ENGINE 0x10895CC0
		void DefaultControllerHandler::OnFlags(unsigned int id, int local, unsigned int flags, bool set)
		{
			if (local == 1 && (flags & 1) != 0)
			{
				Slot3();
			}
		}
		// FUNCTION: ENGINE 0x10895CE0
		// EQUIVALENT: as in UnlockAllControllers, the engine pushes the locked controller before it loads the physical
		// manager and makes the minus one with or, 77.6 %
		void DefaultControllerHandler::Slot3()
		{
			Slot5();
			InputSystem* input = InputSystem::Get();
			if (!secondInstance && !HasCommandLineOption("EnableAllControllers"))
			{
				((PhysicalControllerManagerView*)input->physical)->Unknown108A0B40(-1, controller);
			}
		}

		// FUNCTION: ENGINE 0x10895D20
		// EQUIVALENT: scheduling of the virtual call's table load and of the loads after the command line test, 75 %
		void DefaultControllerHandler::Slot4()
		{
			int index = OLS::Get()->profile->currentProfile;
			if (index < 0)
			{
				return;
			}
			OLSProfile* profile = OLS::Get()->profile;
			OLSUser* user = profile->GetUser(index);
			SetController(user->controller);
			if (HasCommandLineOption("EnableAllControllers"))
			{
				Slot8();
				return;
			}
			Slot7();
		}

		// FUNCTION: ENGINE 0x10895F90
		void DefaultControllerHandler::OnMessage(OLSMessage* message)
		{
			if (message->type == 0 && message->id == 6)
			{
				Slot3();
			}
		}
		// FUNCTION: ENGINE 0x10896000
		void DefaultControllerHandler::Slot5()
		{
			InputSystem* input = InputSystem::Get();
			bool debugCamera = HasCommandLineOption("DebugCam2Controller");
			for (int i = 0; i < input->controllerCount; i++)
			{
				unsigned int id = (i & 0xFF) | 0xFE00;
				if (id != controller)
				{
					if (debugCamera)
					{
						input->SetPlayerFlags(id, 2);
					}
					input->ClearPlayerFlags(id, 8);
				}
			}
			unsigned int chosen = 0xFFFFFFFF;
			for (PlayerInfo* player = (PlayerInfo*)input->active.head; player != 0;
				player = player->GetNext())
			{
				unsigned int id = player->id;
				if ((id & 0xFFFFFF00) == 0xFE00 && (chosen == 0xFFFFFFFF || id == gDefaultController) &&
					(player->flags & 1) != 0)
				{
					chosen = id;
				}
			}
			if (chosen == 0xFFFFFFFF)
			{
				chosen = gDefaultController;
			}
			SetController(chosen);
			if (HasCommandLineOption("EnableAllControllers"))
			{
				Slot8();
				return;
			}
			Slot7();
		}

		// FUNCTION: ENGINE 0x10895D80
		// EQUIVALENT: the engine makes the minus one of the first release call in a register (or) and pushes it, ours
		// pushes the constant, and the registers after it differ, 55 %
		void DefaultControllerHandler::SetController(unsigned int newController)
		{
			unsigned int old = controller;
			InputSystem* input = InputSystem::Get();
			controller = newController;
			if (old != newController)
			{
				int slot = 0;
				if (old != 0xFFFFFFFF)
				{
					input->ClearPlayerFlags(old, 2);
					input->ClearPlayerFlags(old, 4);
					slot = input->FindSlot(old);
					((InputSystemView*)input)->ReleaseSlot(-1, slot);
				}
				input->ClearPlayerFlags(controller, 8);
				input->SetPlayerFlags(controller, 2);
				input->SetPlayerFlags(controller, 4);
				((InputSystemView*)input)->ReleaseSlot(controller, slot);
			}
		}

		// FUNCTION: ENGINE 0x10895E10
		// EQUIVALENT: the engine makes the minus one of the release call in a register (or) and pushes it, ours pushes
		// the constant, 72 %
		void DefaultControllerHandler::Slot7()
		{
			InputSystem* input = InputSystem::Get();
			for (int i = 0; i < input->playerCount; i++)
			{
				unsigned int id = input->slots[i].id;
				if ((id & 0xFFFFFF00) == 0xFE00 && id != controller)
				{
					((InputSystemView*)input)->ReleaseSlot(-1, i);
				}
			}
			bool debugCamera = HasCommandLineOption("DebugCam2Controller");
			for (int i = 0; i < input->controllerCount; i++)
			{
				unsigned int id = (i & 0xFF) | 0xFE00;
				if (debugCamera)
				{
					input->SetPlayerFlags(id, 2);
				}
				else if (id != controller)
				{
					input->SetPlayerFlags(id, 8);
				}
			}
		}

		// FUNCTION: ENGINE 0x10895EA0
		// EQUIVALENT: the engine loads the list address into ecx and the id into eax for the two pushes in the other
		// order, and keeps the controller number 0xFE00 of the last search in a register, 59 %
		void DefaultControllerHandler::Slot8()
		{
			InputSystem* input = InputSystem::Get();
			int count = input->controllerCount;
			for (unsigned int i = 3; (int)i < count; i++)
			{
				PlayerInfo* player = input->FindPlayer((i & 0xFF) | 0xFE00, &input->active);
				if (player != 0 && input->connected.count < playerCount && input->FindSlot(player->id) < 0)
				{
					input->ClearPlayerFlags(player->id, 4);
					input->SetPlayerFlags(player->id, 2);
					((InputSystemView*)input)->ReleaseSlot(player->id, -2);
				}
			}
			PlayerInfo* player = input->FindPlayer(0xFE00, &input->active);
			if (player != 0 && input->connected.count < playerCount && input->FindSlot(player->id) < 0)
			{
				input->ClearPlayerFlags(player->id, 4);
				input->SetPlayerFlags(player->id, 2);
				((InputSystemView*)input)->ReleaseSlot(player->id, -2);
			}
		}

		// FUNCTION: ENGINE 0x10896340
		// EQUIVALENT: the engine saves edi after loading this, schedules the pushes of the mutex call's arguments
		// between the vftable stores and leaves out the dead store of the input callback base's vftable, 90 %
		DefaultControllerHandler::DefaultControllerHandler(int newPlayerCount)
		{
			controller = 0xFFFFFFFF;
			unknown18 = false;
			secondInstance = false;
			void* mutex = _imp__CreateMutexA(0, 0, "GymMutex");
			if (_imp__GetLastError() != 0xB7)
			{
				secondInstance = false;
				_imp__CloseHandle(mutex);
			}
			else
			{
				secondInstance = true;
			}
			if (newPlayerCount < 0)
			{
				newPlayerCount = InputSystem::Get()->playerCount;
			}
			playerCount = newPlayerCount;
			LuaScriptManager* script = GetScriptManager();
			script->RegisterMethod("fe_LockController", this, &DefaultControllerHandler::LockController);
			script->RegisterMethod("fe_UnlockAllControllers", this, &DefaultControllerHandler::UnlockAllControllers);
			UnlockAllControllers();
		}
	}
}
