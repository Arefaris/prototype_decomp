#include "code/engine/database/gamedbhelper.h"
#include "code/core/language.h"
#include "code/engine/database/gamedatabase.h"

namespace engine
{
	GameDBHelper* GameDBHelper::current;

	// FUNCTION: ENGINE 0x10894450
	GameDBHelper::Config::Config()
	{
		unknown0 = 0x12;
	}

	// FUNCTION: ENGINE 0x10894460
	GameDBHelper* GameDBHelper::Get()
	{
		return current;
	}

	// FUNCTION: ENGINE 0x10894470
	GameDBHelper::~GameDBHelper()
	{
		current = 0;
	}

	// FUNCTION: ENGINE 0x10894490
	bool GameDBHelper::Slot2()
	{
		return false;
	}

	// FUNCTION: ENGINE 0x108944A0
	void GameDBHelper::OnMessage(OLSMessage* message)
	{
		if (message->type == 0 && (message->id == 1 || message->id == 0))
		{
			Slot2();
		}
	}

	// FUNCTION: ENGINE 0x108944D0
	GameDBHelper::GameDBHelper(const Config& config)
	{
		unknown8 = config.unknown0;
		current = this;
	}

	// FUNCTION: ENGINE 0x10894510
	void GameDBHelper::Start()
	{
		GameDatabase* database = gGameDatabase;
		database->AddIntSubject(core::Name<core::CaseSensitiveKey>("LoginAccountNum", 0), 0, 0,
			DBSubjectInfo(false, 1, -1));
		database->AddStringSubject(core::Name<core::CaseSensitiveKey>("LoginAccountName", 0), 0, "", 0x20,
			DBSubjectInfo(false, 10, -1));
		database->AddIntSubject(core::Name<core::CaseSensitiveKey>("PlatformMultiSessionAllowed", 0), 0, 1,
			DBSubjectInfo(false, 1, -1));
		database->AddIntSubject(core::Name<core::CaseSensitiveKey>("PlatformCommunicationAllowed", 0), 0, 2,
			DBSubjectInfo(false, 1, -1));
		int language = core::LanguageGet();
		unsigned int subtitles = language != 0x45;
		database->AddIntSubject(core::Name<core::CaseSensitiveKey>("SettingAudioSubtitlesEnabled", 0), 1,
			subtitles, DBSubjectInfo(true, 1, -1));
		const char* languageName = core::GetLanguageName(language);
		database->AddStringSubject(core::Name<core::CaseSensitiveKey>("SettingAudioLanguage", 0), 0,
			languageName, 0x40, DBSubjectInfo(false, 1, -1));
		database->AddIntSubject(core::Name<core::CaseSensitiveKey>("SettingVideoGammaCorrection", 0), 1, 5,
			DBSubjectInfo(true, 1, -1));
		database->AddIntSubject(core::Name<core::CaseSensitiveKey>("SettingsMouseSensitivity", 0), 1, 8,
			DBSubjectInfo(true, 1, -1));
	}

	// FUNCTION: ENGINE 0x108946A0
	void GameDBHelper::Stop()
	{
		GameDatabase* database = gGameDatabase;
		database->ReleaseSubject(core::Name<core::CaseSensitiveKey>("SettingAudioSubtitlesEnabled", 0));
		database->ReleaseSubject(core::Name<core::CaseSensitiveKey>("SettingAudioLanguage", 0));
		database->ReleaseSubject(core::Name<core::CaseSensitiveKey>("SettingVideoGammaCorrection", 0));
		database->ReleaseSubject(core::Name<core::CaseSensitiveKey>("SettingVideoAALevel", 0));
		database->ReleaseSubject(core::Name<core::CaseSensitiveKey>("SettingVideoVSyncEnabled", 0));
		database->ReleaseSubject(core::Name<core::CaseSensitiveKey>("SettingVideoShadowDetail", 0));
		database->ReleaseSubject(core::Name<core::CaseSensitiveKey>("SettingVideoGraphicQuality", 0));
		database->ReleaseSubject(core::Name<core::CaseSensitiveKey>("SettingsMouseSensitivity", 0));
		database->ReleaseSubject(core::Name<core::CaseSensitiveKey>("PlatformMultiSessionAllowed", 0));
		database->ReleaseSubject(core::Name<core::CaseSensitiveKey>("PlatformCommunicationAllowed", 0));
		database->ReleaseSubject(core::Name<core::CaseSensitiveKey>("LoginAccountName", 0));
		database->ReleaseSubject(core::Name<core::CaseSensitiveKey>("LoginAccountNum", 0));
	}

	// FUNCTION: ENGINE 0x108947D0
	bool GameDBHelper::Enable()
	{
		OLS::Get()->AddCallback(this);
		return Slot2();
	}

	// FUNCTION: ENGINE 0x10894800
	void GameDBHelper::Disable()
	{
		OLS::Get()->RemoveCallback(this);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108944F0
