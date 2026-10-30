#include "code/proto/smarthint/smarthintmanager.h"

#include "code/engine/database/gamedatabase.h"

namespace proto
{
	// The names in the game database (0x11275A78: the timers, 0x1126E4C0: the player's setting)
	extern core::Name<core::CaseSensitiveKey> gSmartHintTimersName;
	extern core::Name<core::CaseSensitiveKey> gSmartHintSettingName;

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
}
