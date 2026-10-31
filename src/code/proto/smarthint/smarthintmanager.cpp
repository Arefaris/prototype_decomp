#include "code/proto/smarthint/smarthintmanager.h"

#include "code/core/strings.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/scenariomessage.h"

namespace proto
{
	// The names in the game database (0x11275A78: the timers, 0x1126E4C0: the player's setting)
	core::Name<core::CaseSensitiveKey> gSmartHintTimersName("Proto_Save_SmartHint_Timers", 0);
	core::Name<core::CaseSensitiveKey> gSmartHintSettingName("Proto_Save_EvolutionPoints", 0);

	// The listeners of the smart hint scenario messages (0x11275A70)
	extern engine::MessageListeners gSmartHintListeners;

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
	core::Name<core::CaseSensitiveKey> gProtoSaveSmartHintStateBits("Proto_Save_SmartHint_StateBits", 0);
	core::Name<core::CaseSensitiveKey> gProtoSaveSmartHintStateInts("Proto_Save_SmartHint_StateInts", 0);
}

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
