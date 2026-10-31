// The player's audio options (engine::AudioSettings, engine::AudioSettingsDatabaseObserver; 0x108CE7E0 - 0x108CEDB0).
#include "code/engine/audio/audiosettings.h"
#include "code/audio/renderer.h"
#include "code/audio/rendererdriver.h"
#include "code/engine/audio/audiomanager.h"
#include "code/engine/database/gamedatabase.h"

namespace audio
{
	// The DirectSound driver (another unit)
	class DirectSoundRendererDriver : public RendererDriver
	{
	};
}

namespace engine
{
	// The latencies the options offer (0x111DCD20)
	extern const unsigned int gLatencySteps[7];

	AudioSettings* gAudioSettings;  // 0x113188E8
	AudioSettingsDatabaseObserver* gAudioSettingsObserver;  // 0x113188E0

	static inline SettingName MakeName()
	{
		return SettingName("AudioSettings", true);
	}

	AudioSettings::AudioSettings() :
		AudioSoundList(MakeName())
	{
		gAudioSettings = this;
	}

	AudioSettings::~AudioSettings()
	{
		gAudioSettings = 0;
	}

	const char* AudioSettings::AllocationTag()
	{
		return "";
	}

	AudioSettings* GetAudioSettings()
	{
		return gAudioSettings;
	}

	unsigned int AudioSettings::GetLatencyIndex(unsigned int latency)
	{
		for (unsigned int i = 0; i < 7; i++)
		{
			if (latency <= gLatencySteps[i])
			{
				return i;
			}
		}
		return gLatencySteps[6];
	}

	unsigned int AudioSettings::GetLatency(unsigned int index)
	{
		return gLatencySteps[index];
	}

	audio::DirectSoundRendererDriver* AudioSettings::GetDirectSoundDriver()
	{
		audio::RendererDriver* driver = audio::gRenderer->GetDriver();
		return dynamic_cast<audio::DirectSoundRendererDriver*>(driver);
	}

	float AudioSettings::GetVolume(int tenths)
	{
		return tenths * 0.1f;
	}

	int AudioSettings::GetTenths(float volume)
	{
		return (int)(volume * 10.0f);
	}

	void AudioSettings::Apply(const SettingName& setting, int value)
	{
		if (gMusicVolumeSetting == setting)
		{
			gAudioEmitterSystem->Unknown10877E30(&gUserMixName, &gMusicName, GetVolume(value));
		}
		else if (gSfxVolumeSetting == setting)
		{
			gAudioEmitterSystem->Unknown10877E30(&gUserMixName, &gSfxName, GetVolume(value));
		}
		else if (gDialogVolumeSetting == setting)
		{
			gAudioEmitterSystem->Unknown10877E30(&gUserMixName, &gDialogName, GetVolume(value));
		}
		else if (gLatencySetting == setting)
		{
			audio::RendererDriver* driver = audio::gRenderer->GetDriver();
			if (driver != 0)
			{
				driver->SetLatency(GetLatency(value));
				return;
			}
		}
		gAudioEmitterSystem->MixEvent(gUserMixName, gDuckName, true, 1, 5000.0f, -1.0f);
	}

	int AudioSettings::GetValue(const SettingName& setting)
	{
		if (gMusicVolumeSetting == setting)
		{
			return GetTenths(gAudioEmitterSystem->Unknown10877E60(&gUserMixName, &gMusicName));
		}
		if (gSfxVolumeSetting == setting)
		{
			return GetTenths(gAudioEmitterSystem->Unknown10877E60(&gUserMixName, &gSfxName));
		}
		if (gDialogVolumeSetting == setting)
		{
			return GetTenths(gAudioEmitterSystem->Unknown10877E60(&gUserMixName, &gDialogName));
		}
		if (gLatencySetting == setting)
		{
			audio::RendererDriver* driver = audio::gRenderer->GetDriver();
			if (driver != 0)
			{
				return GetLatencyIndex(driver->GetLatency());
			}
			return gLatencySteps[6];
		}
		return 0;
	}

	void CreateAudioSettings()
	{
		new AudioSettings();
	}

	void DestroyAudioSettings()
	{
		delete gAudioSettings;
	}

	void AudioSettingsDatabaseObserver::RemoveSetting(const SettingName& setting)
	{
		GameDatabase* database = gGameDatabase;
		database->RemoveObserver(setting, this);
		database->ReleaseSubject(setting);
	}

	void AudioSettingsDatabaseObserver::AddSetting(const SettingName& setting)
	{
		GameDatabase* database = gGameDatabase;
		database->AddIntSubject(setting, 1, GetAudioSettings()->GetValue(setting), DBSubjectInfo(true, 1, -1));
		database->AddObserver(setting, this, 0, 0);
	}

	AudioSettingsDatabaseObserver::AudioSettingsDatabaseObserver()
	{
		gAudioSettingsObserver = this;
		AddSetting(gDialogVolumeSetting);
		AddSetting(gMusicVolumeSetting);
		AddSetting(gSfxVolumeSetting);
		AddSetting(gLatencySetting);
	}

	AudioSettingsDatabaseObserver::~AudioSettingsDatabaseObserver()
	{
		RemoveSetting(gDialogVolumeSetting);
		RemoveSetting(gMusicVolumeSetting);
		RemoveSetting(gSfxVolumeSetting);
		RemoveSetting(gLatencySetting);
		gAudioSettingsObserver = 0;
	}

	const char* AudioSettingsDatabaseObserver::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x108CEC50
	void AudioSettingsDatabaseObserver::OnDBSlot0(int a, int b)
	{
		GetAudioSettings()->Apply(*(const SettingName*)a, ((const DBChange*)b)->intValue);
	}

	void CreateAudioSettingsObserver()
	{
		new AudioSettingsDatabaseObserver();
	}

	void DestroyAudioSettingsObserver()
	{
		delete gAudioSettingsObserver;
	}
}

namespace engine
{
	core::Name<core::CaseSensitiveKey> gDuckName("duck", 0);
	core::Name<core::CaseSensitiveKey> gMusicName("music", 0);
	core::Name<core::CaseSensitiveKey> gPos("pos", 0);
	core::Name<core::CaseSensitiveKey> gSfxName("sfx", 0);
	core::Name<core::CaseSensitiveKey> gMusicVolumeSetting("SettingAudioMusicVolume", 0);
	core::Name<core::CaseSensitiveKey> gSfxVolumeSetting("SettingAudioSFXVolume", 0);
	core::Name<core::CaseSensitiveKey> gDialogVolumeSetting("SettingAudioDialogVolume", 0);
	core::Name<core::CaseSensitiveKey> gLatencySetting("SettingAudioLatency", 0);
}

namespace engine
{
	core::Name<core::CaseSensitiveKey> gSettingAudioTHXNeutralEnabled("SettingAudioTHXNeutralEnabled", 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D78590
// FUNCTION: ENGINE 0x10D8B000


// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D74250
// FUNCTION: ENGINE 0x10D743D0
// FUNCTION: ENGINE 0x10D74410
// FUNCTION: ENGINE 0x10D74430
// FUNCTION: ENGINE 0x10D78510
// FUNCTION: ENGINE 0x10D78530
// FUNCTION: ENGINE 0x10D78550
// FUNCTION: ENGINE 0x10D78570
// FUNCTION: ENGINE 0x10D89E30
// FUNCTION: ENGINE 0x10D89EF0
// FUNCTION: ENGINE 0x10D89F10
// FUNCTION: ENGINE 0x10D89F20
// FUNCTION: ENGINE 0x10D8AFC0
// FUNCTION: ENGINE 0x10D8AFD0
// FUNCTION: ENGINE 0x10D8AFE0
// FUNCTION: ENGINE 0x10D8AFF0


// ---- annotations of the functions mapped in symbols.txt (generated) ----

// FUNCTION: ENGINE 0x108CE7E0 @ void engine::AudioSettings::operator delete(void *)
// FUNCTION: ENGINE 0x108CE800 @ void engine::AudioSettingsDatabaseObserver::operator delete(void *)
// FUNCTION: ENGINE 0x108CE820 @ engine::AudioSettings * engine::GetAudioSettings(void)
// FUNCTION: ENGINE 0x108CE830 @ engine::AudioSettings::~AudioSettings(void)
// FUNCTION: ENGINE 0x108CE840 @ unsigned int engine::AudioSettings::GetLatencyIndex(unsigned int)
// FUNCTION: ENGINE 0x108CE860 @ unsigned int engine::AudioSettings::GetLatency(unsigned int)
// FUNCTION: ENGINE 0x108CE870 @ audio::DirectSoundRendererDriver * engine::AudioSettings::GetDirectSoundDriver(void)
// FUNCTION: ENGINE 0x108CE8A0 @ float engine::AudioSettings::GetVolume(int)
// FUNCTION: ENGINE 0x108CE8B0 @ int engine::AudioSettings::GetTenths(float)
// FUNCTION: ENGINE 0x108CE8D0 @ void engine::AudioSettingsDatabaseObserver::RemoveSetting(core::Name<core::CaseSensitiveKey> const &)
// FUNCTION: ENGINE 0x108CE900 @ char const * engine::AudioSettings::AllocationTag(void)
// FUNCTION: ENGINE 0x108CE910 @ char const * engine::AudioSettingsDatabaseObserver::AllocationTag(void)
// FUNCTION: ENGINE 0x108CE920 @ void * engine::AudioSettings::operator new(unsigned int)
// FUNCTION: ENGINE 0x108CE940 @ void * engine::AudioSettingsDatabaseObserver::operator new(unsigned int)
// FUNCTION: ENGINE 0x108CE960 @ void * engine::AudioSettings::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CE990 @ engine::AudioSettings::AudioSettings(void)
// FUNCTION: ENGINE 0x108CE9C0 @ void engine::AudioSettings::Apply(core::Name<core::CaseSensitiveKey> const &,int)
// FUNCTION: ENGINE 0x108CEAC0 @ int engine::AudioSettings::GetValue(core::Name<core::CaseSensitiveKey> const &)
// FUNCTION: ENGINE 0x108CEBB0 @ engine::AudioSettingsDatabaseObserver::~AudioSettingsDatabaseObserver(void)
// FUNCTION: ENGINE 0x108CEC00 @ void engine::AudioSettingsDatabaseObserver::AddSetting(core::Name<core::CaseSensitiveKey> const &)
// FUNCTION: ENGINE 0x108CEC70 @ void engine::CreateAudioSettings(void)
// FUNCTION: ENGINE 0x108CEC90 @ void engine::DestroyAudioSettings(void)
// FUNCTION: ENGINE 0x108CECC0 @ void * engine::AudioSettingsDatabaseObserver::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CECF0 @ engine::AudioSettingsDatabaseObserver::AudioSettingsDatabaseObserver(void)
// FUNCTION: ENGINE 0x108CED40 @ void engine::CreateAudioSettingsObserver(void)
// FUNCTION: ENGINE 0x108CED60 @ void engine::DestroyAudioSettingsObserver(void)
