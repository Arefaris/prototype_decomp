// The game state of a front end dialog (unit 0x108E3E00 - 0x108E44F0; no assert path, file name guessed).
#include "code/engine/frontend/privatedialogstate.h"
#include "code/engine/system/engineflags.h"
#include "code/core/strings.h"
#include "code/engine/controller/inputsystem.h"
#include "code/engine/frontend/dialogstate.h"
#include "code/engine/frontend/frontend.h"

namespace engine
{
	// The real time tasks, the state flags and the mouse (the units that own them declare the same)
	void AddRealTimeTask(IRealTimeTask* task, unsigned int mask, int priority, unsigned int data);
	void RemoveRealTimeTask(IRealTimeTask* task);
	unsigned int* RemoveStateFlags(unsigned int flags);
	void SetMouseVisible(bool visible, bool option);
	bool GetMouseVisible();
	// 0x108366F0: switches to the main fiber
	void YieldFiber();

	// FUNCTION: ENGINE 0x108E42D0
	// EQUIVALENT: scheduling (the engine pushes the destination of the first string copy after the last two stores; 73 %)
	PrivateDialogState::PrivateDialogState(DialogState* newOwner, int newId, int newPriority, const char* newName,
		const char* newOverlay) : GameState(0, 0x10000)
	{
		owner = newOwner;
		stateId = newId;
		priority = newPriority;
		icon = 0;
		iconVisible = false;
		requested = false;
		active = false;
		inputPushed = false;
		mouseVisible = false;
		controller = -1;
		overlay = 0;
		core::StrNCpy(name, newName, 0x20);
		core::StrNCpy(overlayName, newOverlay, 0x20);
	}

	// FUNCTION: ENGINE 0x108E3E10
	PrivateDialogState::~PrivateDialogState()
	{
		if (GetGameState(stateId) != 0)
		{
			FreeGameState(stateId);
		}
	}

	// FUNCTION: ENGINE 0x108E3E50
	bool PrivateDialogState::Request(int newController, int flag)
	{
		if (requested)
		{
			return false;
		}
		icon = 0;
		requested = true;
		controller = newController;
		if (GetGameState(stateId) != 0)
		{
			FreeGameState(stateId);
		}
		if (HasEngineFlags(0x10) && flag == 0)
		{
			covered = false;
			AddGameState(this, stateId, priority, 2, 0, 0);
			RequestGameState(stateId, 2, this);
			return true;
		}
		covered = true;
		if (flag == 1)
		{
			AddGameState(this, stateId, priority, 0, 0, 0);
			RequestGameState(stateId, 0, this);
			return true;
		}
		AddGameState(this, stateId, priority, 0, 0, 0);
		RequestGameState(stateId, 1, this);
		return true;
	}

	// FUNCTION: ENGINE 0x108E3F60
	bool PrivateDialogState::IsActive()
	{
		return active;
	}

	// FUNCTION: ENGINE 0x108E3F70
	bool PrivateDialogState::IsDone()
	{
		return requested || GetGameStateStatus(stateId) != 1;
	}

	// FUNCTION: ENGINE 0x108E3FA0
	void PrivateDialogState::SetIcon(int newIcon, bool visible)
	{
		icon = newIcon;
		iconVisible = visible;
	}

	// FUNCTION: ENGINE 0x108E3FD0
	void PrivateDialogState::Unknown108E3FD0()
	{
		YieldFiber();
	}

	// FUNCTION: ENGINE 0x108E3FE0
	void PrivateDialogState::Enter()
	{
		owner->Slot1();
		if (controller != -1)
		{
			int count = controller::InputSystem::Get()->GetControllerCount();
			for (int i = 0; i < count; i++)
			{
				unsigned int id = controller::InputSystem::LocalId(i);
				if (id == controller)
				{
					controller::InputSystem::Get()->PushContext(id, 2);
				}
				else
				{
					controller::InputSystem::Get()->PushContext(id, 0);
				}
			}
		}
		inputPushed = true;
		overlay = Unknown10864330()->CreateOverlay(name, overlayName, priority);
		overlay->AddCallback("CloseDialog", this, 0);
		overlay->AddCallback("SetCloseGameState", this, 1);
		overlay->AddCallback("ClientMessage", this, 2);
		AddRealTimeTask(this, 1, 1, (unsigned int)"Dialog Realtime Task");
		if (covered)
		{
			RemoveStateFlags(4);
			RemoveStateFlags(8);
		}
		UpdateScreenCentre();
		mouseVisible = GetMouseVisible();
		SetMouseVisible(true, false);
		active = true;
		owner->Slot2();
	}

	// FUNCTION: ENGINE 0x108E4100
	// NONMATCHING: the engine keeps the context id of the loop and the mouse flag in eax and ecx, ours in ecx and edx, 73.9 %
#ifdef NONMATCHING
	void PrivateDialogState::Leave()
	{
		if (active)
		{
			active = false;
			overlay->RemoveCallback("CloseDialog");
			overlay->RemoveCallback("SetCloseGameState");
			overlay->RemoveCallback("ClientMessage");
			delete overlay;
			owner->Slot5();
		}
		RemoveRealTimeTask(this);
		if (controller != -1)
		{
			int count = controller::InputSystem::Get()->GetControllerCount();
			for (int i = 0; i < count; i++)
			{
				unsigned int id = controller::InputSystem::LocalId(i);
				controller::InputSystem::Get()->PopContext(id);
			}
		}
		inputPushed = false;
		requested = false;
		controller = -1;
		SetMouseVisible(mouseVisible, false);
		owner->Slot6();
	}
#endif

	// FUNCTION: ENGINE 0x108E41F0
	void PrivateDialogState::Update(UpdateContext context)
	{
		owner->Slot3(context);
	}

	// FUNCTION: ENGINE 0x108E4220
	void PrivateDialogState::OnFinished(int state, bool aborted)
	{
	}

	// FUNCTION: ENGINE 0x108E4230
	void PrivateDialogState::SetController(int newController)
	{
		if (inputPushed && controller != -1)
		{
			int count = controller::InputSystem::Get()->GetControllerCount();
			for (int i = 0; i < count; i++)
			{
				unsigned int id = controller::InputSystem::LocalId(i);
				controller::InputSystem::Get()->PopContext(id);
			}
		}
		controller = newController;
		if (inputPushed && newController != -1)
		{
			int count = controller::InputSystem::Get()->GetControllerCount();
			for (int i = 0; i < count; i++)
			{
				unsigned int id = controller::InputSystem::LocalId(i);
				if (id == controller)
				{
					controller::InputSystem::Get()->PushContext(id, 2);
				}
				else
				{
					controller::InputSystem::Get()->PushContext(id, 0);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x108E4390
	void PrivateDialogState::Close()
	{
		active = false;
		overlay->RemoveCallback("CloseDialog");
		overlay->RemoveCallback("SetCloseGameState");
		overlay->RemoveCallback("ClientMessage");
		delete overlay;
		owner->Slot4();
		if (icon == 0)
		{
			if (iconVisible)
			{
				RequestGameStateOverlay(stateId, 2, 0);
			}
			else if (covered)
			{
				RequestGameStateOverlay(stateId, 0, 0);
			}
			else
			{
				RequestGameStateOverlay(stateId, 2, 0);
			}
			return;
		}
		if (!iconVisible && covered)
		{
			RequestGameState(icon, 0, 0);
		}
		else
		{
			RequestGameState(icon, 2, 0);
		}
	}

	// FUNCTION: ENGINE 0x108E4470
	// The overlay's script calls: 0 closes the dialog, 1 sets the icon, 2 goes to the dialog's own handler
	void PrivateDialogState::OnCall(int call, int arguments, int unused, int result)
	{
		if (call == 0)
		{
			Close();
		}
		else if (call == 1)
		{
			const FEMovie::Value* values = (const FEMovie::Value*)arguments;
			SetIcon((unsigned int)values[0].number, values[1].flag);
		}
		else if (call == 2)
		{
			owner->OnCall((DialogCall*)arguments, unused, (FEMovie::Value*)result);
		}
	}
}

// Kept copies (inline members and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108E3E00
// FUNCTION: ENGINE 0x108E3F40
