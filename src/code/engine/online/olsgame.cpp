// engine::OLSGame: see olsgame.h.
#include "code/engine/online/olsgame.h"
#include "code/engine/online/olsfriend.h"
#include "code/engine/system/engineflags.h"

namespace engine
{
	class StateCallback;
	// 0x10838B40 (the game state table, another unit; the callback is its SyncCommands::SyncCallback)
	void RequestGameState(int id, int mode, GameFlowManager::StateRequestCallback* callback);
	// 0x10836C30 / 0x108382B0 (the game state table, another unit)
	void RequestTransition(unsigned int id, StateCallback* callback);
	void CancelStateRequest(int state);

	// FUNCTION: ENGINE 0x10887DA0
	void OLSGame::TryRequestState()
	{
		if ((flags & 1) != 0 && OLS::Get()->userTable->Unknown108E7F60())
		{
			int mode = unknown1C == 0;
			RequestGameState(state, mode, this);
			flags = 0;
		}
	}

	// FUNCTION: ENGINE 0x10887DE0
	void OLSGame::CancelState()
	{
		CancelStateRequest(state);
	}

	// FUNCTION: ENGINE 0x10887DF0
	void OLSGame::RequestTransitionState()
	{
		RequestTransition(state, 0);
	}

	// FUNCTION: ENGINE 0x10888080
	void OLSGame::SetSetting(int key, int value)
	{
		for (int i = 0; i < settingCount; i++)
		{
			if (settings[i].key == key)
			{
				settings[i].value = value;
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x10887F60
	void OLSGame::Slot9()
	{
		flags = 2;
		for (int i = 0; i < settingCount; i++)
		{
			if (settings[i].unknownC != -1 && settings[i].value == 0)
			{
				settings[i].value = 3;
			}
		}
		OLS::Get()->userTable->unknown38 = true;
	}

	// FUNCTION: ENGINE 0x10888280
	void OLSGame::Update()
	{
		if ((flags & 1) != 0)
		{
			TryRequestState();
		}
	}

	// FUNCTION: ENGINE 0x10888290
	void OLSGame::RequestState(bool flag)
	{
		flags = 1;
		unknown1C = flag;
		OLS::Get()->userTable->unknown38 = false;
		TryRequestState();
	}

	// FUNCTION: ENGINE 0x10887EF0
	bool OLSGame::Unknown10887EF0()
	{
		if (flags == 0)
		{
			ClearEngineFlags(0x80);
			flags = 2;
			Slot9();
			return false;
		}
		if (flags == 0xE)
		{
			OLSGameMessage message(2);
			message.unknownC = 0;
			OLS::Get()->SendMessage(&message);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108882C0
	bool OLSGame::Unknown108882C0()
	{
		if (Unknown10887EF0())
		{
			OLSUserList* list = OLS::Get()->userList;
			for (int i = 0; i < settingCount; i++)
			{
				int user = settings[i].key;
				if (user != -1)
				{
					list->SetFlag(user, 8, false);
					settings[i].key = -1;
					settings[i].unknownC = -1;
				}
			}
			return true;
		}
		return false;
	}
}
