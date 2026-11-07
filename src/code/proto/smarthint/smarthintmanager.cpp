#include "code/proto/smarthint/smarthintmanager.h"

#include "code/core/strings.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/scenariomessage.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/engine/fmv/fmvplayer.h"
#include "code/core/heap.h"
#include "code/engine/frontend/frontend.h"
#include "code/engine/luascriptmanager.h"

namespace proto
{
	// The names in the game database (0x11275A78: the timers, 0x1126E4C0: the player's setting)
	core::Name<core::CaseSensitiveKey> gSmartHintTimersName("Proto_Save_SmartHint_Timers", 0);
	core::Name<core::CaseSensitiveKey> gSmartHintSettingName("Proto_Save_EvolutionPoints", 0);

	// The listeners of the smart hint scenario messages (0x11275A70)
	engine::MessageListeners gSmartHintListeners("scenario", 0);

	// 0x10575B30: the game mode word
	int* GetGameMode();

	extern core::Name<core::CaseSensitiveKey> gProtoSaveSmartHintStateBits;
	extern core::Name<core::CaseSensitiveKey> gProtoSaveSmartHintStateInts;
	extern core::Name<core::CaseSensitiveKey> gProtoSaveSmartHintTimersEnabled;

	// FUNCTION: ENGINE 0x1059ABE0
	void SmartHintManager::ResetDatabaseEntries()
	{
		log->ClearAll();
		engine::GameDatabase* database = engine::gGameDatabase;
		for (unsigned int i = 0; i < 0x10; i++)
		{
			database->SetInt(gProtoSaveSmartHintStateInts, 0, 0, i);
		}
		for (unsigned int i = 0; i < 0x20; i++)
		{
			database->SetFloat(gSmartHintTimersName, 0, 0.0f, i);
		}
		timerLog->SetAll();
	}

	// FUNCTION: ENGINE 0x1059D250
	void SmartHintManager::Initialise()
	{
		ResetDatabaseEntries();
		enabled = true;
		active = true;
		if (engine::HasCommandLineOption("NoSmartHints"))
		{
			enabled = false;
		}
		mode = 0;
		flag2C = false;
		setting = -1;
		queues.Clear();
		unknownA6BC = true;
		ResetState();
	}

	// FUNCTION: ENGINE 0x1059E870
	void CreateSmartHintManager()
	{
		core::HeapScope scope(0);
		gSmartHintManager = new SmartHintManager;
	}

	// FUNCTION: ENGINE 0x1059ABC0
	void SmartHintManager::UnregisterNatives()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->Unregister(this);
	}

	// FUNCTION: ENGINE 0x1059AC50
	bool SmartHintManager::GetHintFlag(int index)
	{
		return log->Test(index);
	}

	// FUNCTION: ENGINE 0x1059ACE0
	void SmartHintManager::SetTimerEnabled(int index, bool enabled)
	{
		if (enabled)
		{
			timerLog->Set(index);
			return;
		}
		timerLog->Clear(index);
	}

	// FUNCTION: ENGINE 0x1059B1E0
	bool SmartHintManager::Unknown1059B1E0()
	{
		if (shown.state != 2 || shown.kind != 1)
		{
			return false;
		}
		if (*GetGameMode() == 0 && !engine::IsMoviePlaying())
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x1059B4D0
	void SmartHintManager::ResetState()
	{
		shown.Reset();
		unknown1C = 0.0f;
		unknown20 = 5.0f;
		flags.Reset();
	}

	// FUNCTION: ENGINE 0x1059B5A0
	void SmartHintManager::CreateLogs()
	{
		log = new GameDatabaseBitRecord(gProtoSaveSmartHintStateBits, 0x12c);
		engine::GameDatabase* database = engine::gGameDatabase;
		engine::DBSubjectInfo info(true, 1, -1);
		info.a = 0x10;
		database->AddIntSubject(gProtoSaveSmartHintStateInts, 0, 0, info);
		info.a = 0x20;
		database->AddFloatSubject(gSmartHintTimersName, 0, 0.0f, info);
		timerLog = new GameDatabaseBitRecord(gProtoSaveSmartHintTimersEnabled, 0x20);
	}

	// FUNCTION: ENGINE 0x1059B6C0
	void SmartHintManager::DestroyLogs()
	{
		delete log;
		log = 0;
		engine::GameDatabase* database = engine::gGameDatabase;
		database->ReleaseSubject(gProtoSaveSmartHintStateInts);
		database->ReleaseSubject(gSmartHintTimersName);
		delete timerLog;
		timerLog = 0;
	}

	// FUNCTION: ENGINE 0x1059B2D0
	void SmartHintEntry::CopyText(const char* source, char* destination)
	{
		core::StrNCpy(destination, source, 0x3fu);
	}

	// FUNCTION: ENGINE 0x1059B890
	void SmartHintEntry::Clear()
	{
		lineCount = 0;
		CopyText("", title);
		for (int i = 0; i < 6; i++)
		{
			CopyText("", lines[i]);
			CopyText("", images[i]);
			CopyText("", captions[i]);
		}
	}

	// FUNCTION: ENGINE 0x1059B340
	void SmartHintShown::Reset()
	{
		kind = 3;
		state = 0;
		id = -1;
		unknownC = -1;
		flag = false;
	}

	// FUNCTION: ENGINE 0x1059B360
	void SmartHintFlags::Reset()
	{
		unknown0 = false;
		unknown1 = false;
		unknown2 = false;
	}

	// FUNCTION: ENGINE 0x1059AB30
	void SmartHintManager::SetEnabledFlag(bool value)
	{
		enabled = value;
	}

	// FUNCTION: ENGINE 0x1059AB40
	bool SmartHintManager::IsModeOne()
	{
		return mode == 1;
	}

	// FUNCTION: ENGINE 0x1059AB50
	void SmartHintManager::SetModeTwo(bool on)
	{
		mode = on ? 2 : 0;
	}

	// FUNCTION: ENGINE 0x1059AB70
	bool SmartHintManager::IsModeTwo()
	{
		return mode == 2;
	}

	// FUNCTION: ENGINE 0x1059AB80
	void SmartHintManager::SetModeThree(bool on)
	{
		mode = on ? 3 : 0;
	}

	// FUNCTION: ENGINE 0x1059ABA0
	bool SmartHintManager::IsModeThree()
	{
		return mode == 3;
	}

	// FUNCTION: ENGINE 0x1059ABB0
	void SmartHintManager::SetFlags0(bool value)
	{
		flags.unknown0 = value;
	}

	// FUNCTION: ENGINE 0x1059AC60
	void SmartHintManager::SetHintFlag(int index, bool set)
	{
		if (set)
		{
			log->Set(index);
			return;
		}
		log->Clear(index);
	}

	// FUNCTION: ENGINE 0x1059AC90
	float SmartHintManager::GetTimer(int index)
	{
		return engine::gGameDatabase->GetFloat(gSmartHintTimersName, 0, index);
	}

	// FUNCTION: ENGINE 0x1059ACB0
	void SmartHintManager::SetTimer(int index, float value)
	{
		engine::gGameDatabase->SetFloat(gSmartHintTimersName, 0, value, index);
	}

	// FUNCTION: ENGINE 0x1059AED0
	bool SmartHintManager::IsShowing()
	{
		return shown.state != 0;
	}

	// FUNCTION: ENGINE 0x1059B0F0
	void SmartHintManager::AdvanceShown()
	{
		switch (shown.state)
		{
		case 1:
			shown.state = 2;
			break;
		case 2:
			shown.state = 0;
			break;
		}
	}

	// FUNCTION: ENGINE 0x1059B110
	void SmartHintManager::StartShowing(int newId)
	{
		shown.kind = 2;
		shown.state = 3;
		shown.id = newId;
		shown.unknownC = -1;
		shown.flag = false;
	}

	// FUNCTION: ENGINE 0x1059B140
	void SmartHintManager::StopShowing(bool unused)
	{
		shown.state = 0;
		SetHintFlag(shown.id, true);
	}

	// FUNCTION: ENGINE 0x1059B160
	void SmartHintManager::ReadSetting()
	{
		setting = engine::gGameDatabase->GetInt(gSmartHintSettingName, 0, 0);
	}

	// FUNCTION: ENGINE 0x1059B190
	void SmartHintManager::SetFlag2C()
	{
		flag2C = true;
	}

	// FUNCTION: ENGINE 0x1059B210
	void SmartHintManager::SetUnknown20(float value)
	{
		unknown20 = value;
	}

	// FUNCTION: ENGINE 0x1059B510
	void SmartHintManager::SetActive(bool newActive)
	{
		active = newActive;
		if (!newActive)
		{
			HideShown();
		}
	}

	// FUNCTION: ENGINE 0x1059B530
	void SmartHintManager::SetFreeRoam(bool on)
	{
		if (on)
		{
			mode = 1;
			if (flag2C)
			{
				flag2C = false;
				core::Name<core::CaseSensitiveKey> name("smarthint_in_free_roam", 1);
				engine::StringMessage message(name);
				engine::SendMessage(&message, &gSmartHintListeners);
			}
		}
		else
		{
			mode = 0;
		}
	}

	// helper
	static inline void NotifyHint(const char* text)
	{
		core::Name<core::CaseSensitiveKey> name(text, 1);
		engine::StringMessage message(name);
		engine::SendMessage(&message, &gSmartHintListeners);
	}

	// FUNCTION: ENGINE 0x1059B7F0
	// EQUIVALENT: the same name constructions, messages and calls in the same order; the engine keeps the two messages
	// in separate stack slots (a 0x58 byte frame), ours shares the slot of the first for the second (0x30 bytes), 97 %
	void SmartHintManager::SendExitPause()
	{
		if (engine::gGameDatabase->GetInt(gSmartHintSettingName, 0, 0) < setting)
		{
			NotifyHint("smarthint_exit_pause_purchase");
		}
		NotifyHint("smarthint_exit_pause");
	}
}

namespace proto
{
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup("Undefined_SlotGroup", 0);
	core::Name<core::CaseSensitiveKey> gEmpty("", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveSmartHintStateBits("Proto_Save_SmartHint_StateBits", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveSmartHintStateInts("Proto_Save_SmartHint_StateInts", 0);
}

namespace proto
{
	core::Name<core::CaseSensitiveKey> gStatTimePlayed("Stat: Time Played", 0);
	core::Name<core::CaseSensitiveKey> gStatCurrentEvolutionPoints("Stat: Current Evolution points", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveSmartHintTimersEnabled("Proto_Save_SmartHint_TimersEnabled", 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D65D30
// FUNCTION: ENGINE 0x10D864B0


// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D65CD0
// FUNCTION: ENGINE 0x10D65D00
// FUNCTION: ENGINE 0x10D65E50
// FUNCTION: ENGINE 0x10D86430
// FUNCTION: ENGINE 0x10D86440
// FUNCTION: ENGINE 0x10D86510


// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D60550
// FUNCTION: ENGINE 0x10D65D60
// FUNCTION: ENGINE 0x10D65DC0
// FUNCTION: ENGINE 0x10D65DF0
// FUNCTION: ENGINE 0x10D65E20
// FUNCTION: ENGINE 0x10D856B0
// FUNCTION: ENGINE 0x10D864C0
// FUNCTION: ENGINE 0x10D864E0
// FUNCTION: ENGINE 0x10D864F0
// FUNCTION: ENGINE 0x10D86500

// The dynamic initialisers and atexit stubs of the unit's globals:
// FUNCTION: ENGINE 0x10D65D90
// FUNCTION: ENGINE 0x10D864D0
