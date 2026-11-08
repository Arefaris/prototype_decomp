#include "code/proto/gamedatabasehelper.h"

#include "code/core/name.h"
#include "code/core/strings.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/frontend/frontend.h"
#include "code/engine/world/zoneset.h"

namespace engine
{
	// 0x10848EE0: the value of a command line option, null when it has none
	const char* GetCommandLineValue(const char* option);
}

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
		// 0x104AE150
		void Unknown104AE150();
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
	// The keys of the profile and the saved game (profilekeys.cpp)
	extern core::Name<core::CaseSensitiveKey> gProtoSaveProtoVersion;
	extern core::Name<core::CaseSensitiveKey> gProtoSaveSpawnFacing;
	extern core::Name<core::CaseSensitiveKey> gProtoSaveSpawnPosition;
	extern core::Name<core::CaseSensitiveKey> gProtoSaveMissionsCompleted;
	extern core::Name<core::CaseSensitiveKey> gProtoSaveNextStoryMission;
	extern core::Name<core::CaseSensitiveKey> gProtoSaveDifficulty;
	extern core::Name<core::CaseSensitiveKey> gProtoVolatileStartType;
	extern core::Name<core::CaseSensitiveKey> gProtoVolatileIsInVehicle;
	extern core::Name<core::CaseSensitiveKey> gProtoTutorial;
	extern core::Name<core::CaseSensitiveKey> gProtoTutorialImageName;
	extern core::Name<core::CaseSensitiveKey> gProtoTutorialImageCaption;
	extern core::Name<core::CaseSensitiveKey> gProtoTutorialNum;

	// 0x104DF950: whether the level is in the list
	bool HasDevSelectLevel(const char* name);

	// The save manager (another unit)
	class SaveManager
	{
	public:
		// 0x1047FD10
		void Unknown1047FD10();
	};
	// 0x1047FD10's owner: the save manager singleton
	SaveManager* GetSaveManager();

	// 0x1126E46C: whether the dev select start is finished
	static bool sDevSelectStarted;

	// FUNCTION: ENGINE 0x104DEFC0
	void FinishDevSelectStart()
	{
		sDevSelectStarted = true;
	}

	// FUNCTION: ENGINE 0x104DEFD0
	void ClearDevSelectStart()
	{
		sDevSelectStarted = false;
	}

	// FUNCTION: ENGINE 0x104DEFE0
	bool IsDevSelectStarted()
	{
		return sDevSelectStarted;
	}

	// FUNCTION: ENGINE 0x104DEDA0
	GameDatabaseHelper::GameDatabaseHelper(const Config& config) : engine::GameDBHelper(config)
	{
	}

	// FUNCTION: ENGINE 0x104DEDE0
	void GameDatabaseHelper::OnMessage(engine::OLSMessage* message)
	{
		if (message->type == 0xB && message->id == 4)
		{
			GetFrontEndHud()->Unknown104B0CB0()->Unknown104AE150();
		}
		engine::GameDBHelper::OnMessage(message);
	}

	// FUNCTION: ENGINE 0x104DEDD0
	void GameDatabaseHelper::Start()
	{
		engine::GameDBHelper::Start();
	}

	// FUNCTION: ENGINE 0x104DEE30
	void GameDatabaseHelper::Stop()
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		database->ReleaseSubject(gProtoSaveProtoVersion);
		database->ReleaseSubject(gProtoSaveSpawnFacing);
		database->ReleaseSubject(gProtoSaveSpawnPosition);
		database->ReleaseSubject(gProtoSaveMissionsCompleted);
		database->ReleaseSubject(gProtoSaveNextStoryMission);
		database->ReleaseSubject(gProtoVolatileStartType);
		database->ReleaseSubject(gLevelNameKey);
		database->ReleaseSubject(gProtoVolatileIsInVehicle);
		engine::GameDBHelper::Stop();
	}

	// FUNCTION: ENGINE 0x104DF040
	void GameDatabaseHelper::AddSubjects()
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		engine::DBSubjectInfo info(false, 1, -1);
		database->AddStringSubject(gLevelNameKey, 0, "", 0x20, info);
		database->AddObserver(gLevelNameKey, this, 0, 0);
		database->AddStringSubject(gProtoVolatileStartType, 0, "", 0x10, info);
		database->AddIntSubject(gProtoVolatileIsInVehicle, 0, 0, info);
		engine::DBSubjectInfo tutorialInfo(true, 1, -1);
		tutorialInfo.b = 0;
		tutorialInfo.a = 0x10;
		tutorialInfo.flag = false;
		engine::DBSubjectInfo tutorialNumberInfo(true, 1, -1);
		tutorialNumberInfo.b = 0;
		tutorialNumberInfo.a = 1;
		tutorialNumberInfo.flag = false;
		database->AddStringSubject(gProtoTutorial, 0, "", 0x100, tutorialInfo);
		database->AddStringSubject(gProtoTutorialImageName, 0, "", 0x100, tutorialInfo);
		database->AddStringSubject(gProtoTutorialImageCaption, 0, "", 0x100, tutorialInfo);
		database->AddIntSubject(gProtoTutorialNum, 0, 0, tutorialNumberInfo);
	}

	// FUNCTION: ENGINE 0x104DF210
	void GameDatabaseHelper::ReleaseSubjects()
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		database->RemoveObserver(gLevelNameKey, static_cast<engine::DBObserver*>(this));
		database->ReleaseSubject(gProtoTutorial);
		database->ReleaseSubject(gProtoTutorialImageName);
		database->ReleaseSubject(gProtoTutorialImageCaption);
		database->ReleaseSubject(gProtoTutorialNum);
		database->ReleaseSubject(gLevelNameKey);
		database->ReleaseSubject(gProtoVolatileStartType);
		database->ReleaseSubject(gProtoVolatileIsInVehicle);
	}

	// FUNCTION: ENGINE 0x104DF2B0
	void GameDatabaseHelper::OnDBSlot1(int a, int b)
	{
	}

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

namespace proto
{
	// FUNCTION: ENGINE 0x104DEFF0
	// NONMATCHING: the engine keeps the constant 1 in ecx for the comparisons and the stored flag, 48 %
#ifdef NONMATCHING
	void SetGameDatabaseMode(int mode)
	{
		switch (mode)
		{
		case 0:
			engine::gGameDatabase->inputMode = false;
			engine::gGameDatabase->onlineHelper.Unknown10893CD0();
			break;
		case 1:
			engine::gGameDatabase->inputMode = true;
			engine::gGameDatabase->onlineHelper.Unknown108939A0();
			break;
		case 2:
			engine::gGameDatabase->inputMode = true;
			engine::gGameDatabase->onlineHelper.Unknown108939A0();
			break;
		}
	}
#endif

	// FUNCTION: ENGINE 0x104DEEC0
	void StartDevSelectLevel(const char* name, int difficulty, const char* group)
	{
		engine::gGameDatabase->SetString(gLevelNameKey, 0, name, 0);
		engine::gGameDatabase->SetString(gProtoSaveNextStoryMission, 0, name, 0);
		if (engine::HasCommandLineOption("Difficulty"))
		{
			const char* value = engine::GetCommandLineValue("Difficulty");
			if (value != 0)
			{
				for (int i = 0; i < 6; i++)
				{
					if (core::StrICmp(value, gDifficultyNames[2 + i]) == 0)
					{
						difficulty = i % 3;
						break;
					}
				}
			}
		}
		engine::gGameDatabase->SetInt(gProtoSaveDifficulty, 0, difficulty, 0);
		engine::gGameDatabase->SetString(gProtoVolatileStartType, 0, group, 0);
		GetSaveManager()->Unknown1047FD10();
	}
}
