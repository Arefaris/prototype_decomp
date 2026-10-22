#include "code/engine/system/exceptionmanager.h"
#include "code/core/interlocked.h"
#include "code/engine/system/engineflags.h"
#include "code/engine/system/enginememory.h"
#include "code/engine/system/gamestatetable.h"

namespace engine
{
	// The front end's other game state calls (another unit, game state machine); the states are picked by index
	void RemoveGameState(int id);
	void SetGameStateScreen(int index, int state, const char* name);
	void RequestGameStateByIndex(int index, int mode);
	void RequestGameState(int state, int mode, SyncCommands::SyncCallback* callback);

	// The network console manager object (0x11318530; another unit): its callback list sits at +0x4C of the object
	// at +0x74 (names guessed)
	struct ConsoleManagerView
	{
		unsigned char unknown0[0x4C];
		container::SListLite<ConsoleManager::Callback> callbacks;
	};
	struct OnlineManagerView
	{
		unsigned char unknown0[0x74];
		ConsoleManagerView* console;
	};
	extern OnlineManagerView* gOnlineManager;

	// The pop-up dialog texts: one button with no text (0x111D2BB4)
	const char* gExceptionButtons[1] = { "" };

	ExceptionManager::IExceptionHandler* ExceptionManager::handlers[4];
	ExceptionManager* gExceptionManager;
	// The watches the pause logic sets (names guessed); the third tells whether the controller watch has anything to
	// wait for
	bool gPauseFlagA;
	bool gPauseFlagB;
	bool (*gControllerWatchCallback)();
	// Written by other units
	extern volatile long gMediaChanged;

	// The flags the drive thread and the media watch keep are read with an interlocked and
	inline bool ReadFlag(volatile long* flag)
	{
		return _InterlockedAnd(flag, -1) != 0;
	}

	// FUNCTION: ENGINE 0x10882770
	ExceptionManager* GetExceptionManager()
	{
		return gExceptionManager;
	}

	// FUNCTION: ENGINE 0x108827B0
	void ExceptionManager::AddHandler(IExceptionHandler* handler)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			if (handlers[i] == 0)
			{
				handlers[i] = handler;
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x108827E0
	void ExceptionManager::RemoveHandler(IExceptionHandler* handler)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			if (handlers[i] == handler)
			{
				handlers[i] = 0;
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x10882810
	void ExceptionManager::Notify(int condition, bool raised)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			if (handlers[i] != 0)
			{
				if (raised)
				{
					handlers[i]->OnRaised(condition);
				}
				else
				{
					handlers[i]->OnCleared(condition);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10882850
	void ExceptionManager::OnFlags(unsigned int id, int local, unsigned int flags, bool set)
	{
		if (local == 1 && flags == 1)
		{
			if (!set)
			{
				if (controller::InputSystem::Get()->FindSlot(id) >= 0)
				{
					for (unsigned int i = 0; i < 8; i++)
					{
						if (pulledControllers[i] == -1)
						{
							pulledControllers[i] = id;
							return;
						}
					}
				}
			}
			else
			{
				for (unsigned int i = 0; i < 8; i++)
				{
					if ((unsigned int)pulledControllers[i] == id)
					{
						pulledControllers[i] = -1;
						return;
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x108828D0
	// EQUIVALENT: the engine makes the minus one in a register (or) and stores it from there, ours stores the constant,
	// 37.8 %
	void ExceptionManager::Slot3(int a, int b)
	{
		if (b != 1 && b != 2)
		{
			return;
		}
		peerLost = true;
		dialogs[1]->Unknown10883D50(-1, true);
	}

	// FUNCTION: ENGINE 0x10882900
	void SetPauseFlagA(bool value)
	{
		gPauseFlagA = value;
	}

	// FUNCTION: ENGINE 0x10882910
	void SetPauseFlagB(bool value)
	{
		gPauseFlagB = value;
	}

	// FUNCTION: ENGINE 0x10882920
	void SetControllerWatchCallback(bool (*callback)())
	{
		gControllerWatchCallback = callback;
	}

	// FUNCTION: ENGINE 0x10882930
	bool IsControllerWatchActive()
	{
		if (!gPauseFlagB)
		{
			return false;
		}
		if (gControllerWatchCallback != 0)
		{
			return gControllerWatchCallback();
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10882950
	bool IsMediaRemoved()
	{
		return gExceptionManager->mediaRemoved;
	}

	// FUNCTION: ENGINE 0x10882960
	ExceptionManager::ExceptionFEPopUpDialogState::ExceptionFEPopUpDialogState(const char* newTitle,
		const char* newMessage, const char** newButtons, int newButtonCount, int a, int b, const char* name,
		int newReason) : FEPopUpDialogState(newTitle, newMessage, newButtons, newButtonCount, a, b, (int)name,
		"EXCEPTIONPOPUP_OVERLAY")
	{
		reason = newReason;
	}

	// FUNCTION: ENGINE 0x10882A00
	void ExceptionManager::ExceptionFEPopUpDialogState::Slot1()
	{
		Notify(reason, true);
		controller::InputSystem::Get()->StopVibration();
	}

	// FUNCTION: ENGINE 0x10882A20
	// EQUIVALENT: ours aligns the head of the first wait loop (the engine does not) and loads the session into eax before
	// it moves it to ecx for the virtual call (the engine loads it into ecx), 45.3 %
	void ExceptionManager::ExceptionFEPopUpDialogState::Slot6()
	{
		int count = 10;
		do
		{
			count--;
			controller::InputSystem::Get()->ClearRemotePlayers();
			Unknown10883DB0();
		}
		while (count != 0);
		if (reason == 1 || reason == 2)
		{
			if (HasEngineFlags(0x80))
			{
				while (true)
				{
					OLS* ols = OLS::Get();
					OLSLocalUser* user = ols->localUsers != 0 ? ols->localUsers[ols->selectedLocalUser] : 0;
					if (user->Unknown108882C0())
					{
						break;
					}
					Unknown10883DB0();
				}
			}
			if (HasEngineFlags(8))
			{
				while (!OLS::Get()->session->IsConnected())
				{
					Unknown10883DB0();
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10882C20
	ExceptionManager::~ExceptionManager()
	{
		controller::InputSystem::Get()->RemoveCallback(this);
		OLS::Get()->RemoveCallback(this);
		if (gOnlineManager != 0)
		{
			ConsoleManagerView* console = gOnlineManager->console;
			if (console != 0)
			{
				console->callbacks.Remove(this);
			}
		}
		RemoveGameState(1);
		RemoveGameState(2);
		RemoveGameState(3);
		RemoveGameState(4);
		delete dialogs[0];
		delete dialogs[1];
		delete dialogs[2];
		delete dialogs[3];
	}

	// FUNCTION: ENGINE 0x10882CF0
	// EQUIVALENT: the engine jumps from the failed test of the first message id to the test of the second (ours skips
	// to the end, knowing the second must fail) and makes the minus one of the dialog call in a register, 33.8 %
	void ExceptionManager::OnMessage(OLSMessage* message)
	{
		if (message->type == 0)
		{
			short id = message->id;
			if (id != 8)
			{
				bool watch = gPauseFlagA;
				if (id == 0 && watch)
				{
					if (message->user != OLS::Get()->profile->currentProfile)
					{
						return;
					}
				}
				else
				{
					if (id != 1 || !watch)
					{
						return;
					}
					if (message->user != OLS::Get()->profile->currentProfile)
					{
						return;
					}
				}
				SetPauseFlagB(false);
				RequestGameStateByIndex(4, 0);
				return;
			}
		}
		else if (message->type == 2 && message->id == 4 && message->unknown10 != 0)
		{
			OLSUserTable* table = OLS::Get()->userTable;
			if (table->count <= 1 ||
				table->items + table->current * 0x40 == table->items + message->user * 0x40)
			{
				peerLost = true;
				dialogs[1]->Unknown10883D50(-1, true);
			}
		}
	}

	// FUNCTION: ENGINE 0x10882E60
	// EQUIVALENT: the engine makes the minus one for the array (or) after the base classes' vftable stores, ours
	// before them, 97.5 %
	ExceptionManager::ExceptionManager(const Config& config) : ConsoleManager::Callback(true)
	{
		lobbyLost = false;
		peerLost = false;
		controllerLost = false;
		unknown37 = false;
		mediaRemoved = false;
		for (int i = 0; i < 8; i++)
		{
			pulledControllers[i] = -1;
		}
		pulledController = -1;
		heap = config.heap;
		dialogs[0] = new (heap) ExceptionFEPopUpDialogState("$Exception", "$LobbyDisconnect", gExceptionButtons, 1, 6,
			0x19, "LobbyDisconnect", 1);
		dialogs[1] = new (heap) ExceptionFEPopUpDialogState("$Exception", "$PeerLost", gExceptionButtons, 1, 7, 0x19,
			"PeerLost", 2);
		dialogs[2] = new (heap) ExceptionFEPopUpDialogState("$Exception", "$ControllerDisconnect", gExceptionButtons, 1,
			8, 0x1A, "ControllerDisconnect", 0);
		dialogs[3] = new (heap) ExceptionFEPopUpDialogState("$Exception", "$MediaRemoved", gExceptionButtons, 1, 9, 0x1B,
			"MediaRemoved", 3);
		SetGameStateScreen(1, config.unknown4, config.screens[0]);
		SetGameStateScreen(2, config.unknown4, config.screens[1]);
		SetGameStateScreen(3, config.unknown4, config.screens[2]);
		SetGameStateScreen(4, config.unknown4, config.screens[3]);
		OLS::Get()->AddCallback(this);
		controller::InputSystem::Get()->AddCallback(this);
		for (int i = 0; i < 4; i++)
		{
			handlers[i] = 0;
		}
	}

	// FUNCTION: ENGINE 0x10883040
	// EQUIVALENT: the engine keeps the minus one in edi for the compares, the stores and the masks of the interlocked
	// reads, ours uses the constant for all but the masks, 66.8 %
	void ExceptionManager::Update(core::Time frameTime)
	{
		if (lobbyLost && !dialogs[0]->Unknown10883D80())
		{
			lobbyLost = false;
			Notify(1, false);
			if (HasEngineFlags(0x80))
			{
				RequestGameState(1, 2, 0);
			}
			else if (HasEngineFlags(0x10))
			{
				RequestGameStateByIndex(1, 0);
			}
		}
		if (peerLost && !dialogs[1]->Unknown10883D80())
		{
			peerLost = false;
			Notify(2, false);
			if (HasEngineFlags(0x80))
			{
				RequestGameState(1, 2, 0);
			}
			else if (HasEngineFlags(0x10))
			{
				RequestGameStateByIndex(2, 2);
			}
		}
		if (controllerLost)
		{
			if (!IsControllerWatchActive() && dialogs[2]->Unknown10883D70())
			{
				dialogs[2]->Unknown10883D60();
			}
			if (!dialogs[2]->Unknown10883D80())
			{
				controllerLost = false;
				Notify(0, false);
			}
		}
		if (!controllerLost)
		{
			for (unsigned int i = 0; i < 8; i++)
			{
				if (pulledControllers[i] != -1)
				{
					pulledController = pulledControllers[i];
					break;
				}
			}
			if (IsControllerWatchActive() && pulledController != -1)
			{
				controllerLost = true;
				dialogs[2]->Unknown10883D50(pulledController, false);
				pulledController = -1;
			}
		}
		bool removed = ReadFlag(&gMediaChanged);
		if (mediaRemoved != removed)
		{
			mediaRemoved = ReadFlag(&gMediaChanged);
			Notify(4, mediaRemoved);
		}
	}

	// FUNCTION: ENGINE 0x108832D0
	void CreateExceptionManager(const ExceptionManager::Config* config)
	{
		gExceptionManager = new (config->heap) ExceptionManager(*config);
	}

	// FUNCTION: ENGINE 0x10883310
	void DestroyExceptionManager()
	{
		delete gExceptionManager;
		gExceptionManager = 0;
	}

	// FUNCTION: ENGINE 0x10883340
	void UpdateExceptionManager(core::Time frameTime)
	{
		if (gExceptionManager != 0)
		{
			gExceptionManager->Update(frameTime);
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108829B0
// FUNCTION: ENGINE 0x108829C0
// FUNCTION: ENGINE 0x108829D0
// FUNCTION: ENGINE 0x108829E0
// FUNCTION: ENGINE 0x108829F0
// FUNCTION: ENGINE 0x10882AE0
// FUNCTION: ENGINE 0x10882B00
// FUNCTION: ENGINE 0x10882B20
// FUNCTION: ENGINE 0x10882E40
