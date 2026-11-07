#include "code/proto/observerhelper.h"

#include "code/engine/database/gamedatabase.h"

namespace proto
{
	// The keys of the profile and the settings (profilekeys.cpp)
	extern core::Name<core::CaseSensitiveKey> gProtoProfileGamepadRumbleEnabled;
	extern core::Name<core::CaseSensitiveKey> gOLSProfileYAxisInversion;
	extern core::Name<core::CaseSensitiveKey> gOLSProfileControllerVibration;
	extern core::Name<core::CaseSensitiveKey> gProtoProfileCameraVerticalInv;
	extern core::Name<core::CaseSensitiveKey> gProtoProfileCameraVerticalInvTank;
	extern core::Name<core::CaseSensitiveKey> gProtoProfileCameraVerticalInvHeli;
	extern core::Name<core::CaseSensitiveKey> gProtoProfileMouseWheelInvHeli;

	// 0x104DED00: switches the rumble of the first controller (name guess)
	void SetGamepadRumble(bool enabled, unsigned char player);
	// 0x104DDBB0: the language of the game by name
	void SetLanguage(const char* name, int round);
	// 0x108732E0 (name unknown)
	void Unknown108732E0(bool flag);

	// FUNCTION: ENGINE 0x104DF580
	ObserverHelper::ObserverHelper() : languageKey("SettingAudioLanguage", 0)
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		database->AddObserver(gProtoProfileGamepadRumbleEnabled, this, 0, 0);
		database->AddObserver(languageKey, this, 0, 0);
		if (database->Exists(gOLSProfileYAxisInversion, 0, 0))
		{
			database->AddObserver(gOLSProfileYAxisInversion, this, 0, 0);
		}
		if (database->Exists(gOLSProfileControllerVibration, 0, 0))
		{
			database->AddObserver(gOLSProfileControllerVibration, this, 0, 0);
		}
		database->AddObserver(core::Name<core::CaseSensitiveKey>("SettingsDefaultController", 0), this, 0, 0);
	}

	// FUNCTION: ENGINE 0x104DF660
	ObserverHelper::~ObserverHelper()
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		database->RemoveObserver(gProtoProfileGamepadRumbleEnabled, this);
		database->RemoveObserver(languageKey, this);
		if (database->Exists(gOLSProfileYAxisInversion, 0, 0))
		{
			database->RemoveObserver(gOLSProfileYAxisInversion, this);
		}
		if (database->Exists(gOLSProfileControllerVibration, 0, 0))
		{
			database->RemoveObserver(gOLSProfileControllerVibration, this);
		}
		database->RemoveObserver(core::Name<core::CaseSensitiveKey>("SettingsDefaultController", 0), this);
	}

	// FUNCTION: ENGINE 0x104DED90
	void ObserverHelper::OnDBSlot1(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x104DF710
	void ObserverHelper::OnDBSlot0(int key, int change)
	{
		const core::Name<core::CaseSensitiveKey>& name = *(const core::Name<core::CaseSensitiveKey>*)key;
		const DBChange* record = (const DBChange*)change;
		if (name == gProtoProfileGamepadRumbleEnabled)
		{
			SetGamepadRumble(record->value != 0, record->player);
			return;
		}
		if (name == languageKey)
		{
			SetLanguage((const char*)record->value, record->player);
			return;
		}
		if (name == gOLSProfileYAxisInversion)
		{
			engine::GameDatabase* database = engine::gGameDatabase;
			database->SetInt(gProtoProfileCameraVerticalInv, record->player, record->value, record->index);
			database->SetInt(gProtoProfileCameraVerticalInvTank, record->player, record->value, record->index);
			database->SetInt(gProtoProfileCameraVerticalInvHeli, record->player, record->value, record->index);
			database->SetInt(gProtoProfileMouseWheelInvHeli, record->player, record->value, record->index);
			return;
		}
		if (name == gOLSProfileControllerVibration)
		{
			engine::gGameDatabase->SetInt(gProtoProfileGamepadRumbleEnabled, record->player, record->value, record->index);
			return;
		}
		if (name == core::Name<core::CaseSensitiveKey>("SettingsDefaultController", 0))
		{
			Unknown108732E0(record->value < 2);
		}
	}
}
