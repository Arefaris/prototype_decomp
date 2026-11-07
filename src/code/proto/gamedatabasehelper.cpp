#include "code/proto/gamedatabasehelper.h"

#include "code/core/name.h"
#include "code/core/strings.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/world/zoneset.h"

namespace proto
{
	// 0x1126E518 .. (profilekeys.cpp)
	extern core::Name<core::CaseSensitiveKey> gProtoProfileCameraVerticalInv;
	extern core::Name<core::CaseSensitiveKey> gProtoProfileCameraVerticalInvTank;
	extern core::Name<core::CaseSensitiveKey> gProtoProfileCameraVerticalInvHeli;
	extern core::Name<core::CaseSensitiveKey> gProtoProfileMouseWheelInvHeli;
	extern core::Name<core::CaseSensitiveKey> gProtoProfileGamepadRumbleEnabled;
	extern core::Name<core::CaseSensitiveKey> gOLSProfileYAxisInversion;
	extern core::Name<core::CaseSensitiveKey> gOLSProfileControllerVibration;

	// The head-up display's elements (names unknown)
	class HudSettings
	{
	public:
		// 0x104AE020
		void Unknown104AE020();
	};
	class FrontEndHud
	{
	public:
		// 0x104B0CB0
		HudSettings* Unknown104B0CB0();
	};
	// 0x104B0A00
	FrontEndHud* GetFrontEndHud();

	// 0x1126E538 (midgroundmanager.cpp)
	extern core::Name<core::CaseSensitiveKey> gLevelNameKey;

	// 0x104DF950 / 0x104DEEC0: whether the level is in the list, and starts it
	bool HasDevSelectLevel(const char* name);
	void StartDevSelectLevel(const char* name, int flag, const char* group);

	// FUNCTION: ENGINE 0x104E0790
	void GameDatabaseHelper::OnDBSlot0(int a, int b)
	{
		if (*(core::Name<core::CaseSensitiveKey>*)a == gLevelNameKey)
		{
			engine::GetZoneSet()->Unknown108951B0();
		}
	}

	// FUNCTION: ENGINE 0x104E04C0
	void PrepareGameDevSelect(unsigned int index)
	{
		if (index < gDevSelectList.Size())
		{
			StartDevSelectLevel(gDevSelectList.entries[index].name, 1, "DevSelect");
		}
	}

	// FUNCTION: ENGINE 0x104E02F0
	void GameDatabaseHelper::ReleaseSettingSubjects()
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		database->ReleaseSubject(core::Name<core::CaseSensitiveKey>("SettingVideoResolution", 0));
		database->ReleaseSubject(core::Name<core::CaseSensitiveKey>("SettingsDefaultController", 0));
		GetFrontEndHud()->Unknown104B0CB0()->Unknown104AE020();
	}

	// FUNCTION: ENGINE 0x104E0520
	void GameDatabaseHelper::AddValidMission(const char* name, const char* location)
	{
		if (!HasDevSelectLevel(name))
		{
			DevSelectEntry* entry = gDevSelectList.Push();
			core::StrCpy(entry->name, name);
			core::StrCpy(entry->location, location);
		}
	}

	// FUNCTION: ENGINE 0x104E05A0
	unsigned int GameDatabaseHelper::GetNumMissions()
	{
		return gDevSelectList.Size();
	}

	// FUNCTION: ENGINE 0x104E05D0
	const char* GameDatabaseHelper::GetMissionName(unsigned int index)
	{
		return gDevSelectList.entries[index].name;
	}

	// FUNCTION: ENGINE 0x104E05F0
	const char* GameDatabaseHelper::GetLocationName(unsigned int index)
	{
		return gDevSelectList.entries[index].location;
	}

	// FUNCTION: ENGINE 0x104E0610
	void GameDatabaseHelper::RestoreGameDBDefault(const char* key, unsigned int player)
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		core::Name<core::CaseSensitiveKey> name(key, 1);
		if (name == gProtoProfileCameraVerticalInv || name == gProtoProfileCameraVerticalInvTank || name == gProtoProfileCameraVerticalInvHeli || name == gProtoProfileMouseWheelInvHeli)
		{
			if (database->Exists(gOLSProfileYAxisInversion, 0, 0))
			{
				int value = database->GetInt(gOLSProfileYAxisInversion, player, 0);
				database->SetInt(name, player, value, 0);
				return;
			}
		}
		if (name == gProtoProfileGamepadRumbleEnabled)
		{
			if (database->Exists(gOLSProfileControllerVibration, 0, 0))
			{
				int value = database->GetInt(gOLSProfileControllerVibration, player, 0);
				database->SetInt(name, player, value, 0);
				return;
			}
		}
		if (!(name == core::Name<core::CaseSensitiveKey>("SettingsDefaultController", 0)))
		{
			database->ResetSubject(name, player);
		}
	}
}
