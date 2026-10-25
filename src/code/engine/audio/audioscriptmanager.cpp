// The scripts' access to the audio system (see the header). The unit instantiates the script method wrappers
// (engine::Function's Method and Closure templates) for the signatures of the snd_* functions.
#include "code/engine/audio/audioscriptmanager.h"

#include "code/engine/audio/audioglobalsettings.h"
#include "code/engine/audio/audiomanager.h"
#include "code/engine/audio/audiomessage.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"

namespace engine
{
	AudioScriptManager* gAudioScriptManager;  // 0x11318928

	// The parts of the audio system the script functions reach (other units; names guessed)
	// 0x10895720
	void SetAudioDebugOutput(bool enable);
	// 0x10895730
	void SetAudioDebugRendering(bool enable);
	class AudioDebug
	{
	public:
		// 0x10895650
		void SetVolume(float volume);

		int spewMode;
	};
	extern AudioDebug* gAudioDebug;  // 0x11317810
	// 0x10895740
	void SetAudioGroupVisible(const om::String& group, bool visible);
	extern core::Name<core::CaseSensitiveKey> gAudioPlay;  // 0x11284138

	// FUNCTION: ENGINE 0x108D1140
	void AudioScriptManager::EnableDebugOutput(bool enable)
	{
		SetAudioDebugOutput(enable);
	}

	// FUNCTION: ENGINE 0x108D1200
	void AudioScriptManager::EnableDebugRendering(bool enable)
	{
		SetAudioDebugRendering(enable);
	}

	// FUNCTION: ENGINE 0x108D1150
	void AudioScriptManager::SetVolume(float volume)
	{
		gAudioDebug->SetVolume(volume);
	}

	// FUNCTION: ENGINE 0x108D1170
	void AudioScriptManager::CreateGroup(const char* group, unsigned int first, unsigned int second)
	{
		om::String name(group, true);
		AudioSystem::Get()->AddSoundGroup(name, first, second);
	}

	// FUNCTION: ENGINE 0x108D11B0
	void AudioScriptManager::SetGroupInterrupts(const char* group, const char* other)
	{
		om::String otherName(other, true);
		om::String groupName(group, true);
		AudioSystem::Get()->AddInterrupt(groupName, otherName);
	}

	// FUNCTION: ENGINE 0x108D1210
	void AudioScriptManager::SetGroupVisibility(const char* group, bool visible)
	{
		om::String name(group, true);
		SetAudioGroupVisible(name, visible);
	}

	// FUNCTION: ENGINE 0x108D1250
	void AudioScriptManager::SetGroupIsEnabled(const char* group, bool enabled)
	{
		om::String name(group, true);
		AudioSystem::Get()->SetGroupEnabled(name, enabled);
	}

	// FUNCTION: ENGINE 0x108D1290
	void AudioScriptManager::DisableAllGroups()
	{
		AudioSystem::Get()->DisableAllGroups();
	}

	// FUNCTION: ENGINE 0x108D12A0
	void AudioScriptManager::EnableSpew()
	{
		gAudioDebug->spewMode = 2;
	}

	// FUNCTION: ENGINE 0x108D12B0
	void AudioScriptManager::DisableSpew()
	{
		gAudioDebug->spewMode = 1;
	}

	// FUNCTION: ENGINE 0x108D12C0
	void AudioScriptManager::SetCollisionInstance(const char* instance)
	{
	}

	// FUNCTION: ENGINE 0x108D12D0
	void AudioScriptManager::SetCollisionValues(float first, float second, float third)
	{
	}

	// FUNCTION: ENGINE 0x108D12E0
	void AudioScriptManager::SetListenerOffset(float offset)
	{
		gAudioListener->listenerOffset = offset;
	}

	// FUNCTION: ENGINE 0x108D1300
	float AudioScriptManager::GetListenerOffset()
	{
		return gAudioListener->listenerOffset;
	}

	// FUNCTION: ENGINE 0x108D13B0
	void AudioScriptManager::PlayPatch(const char* patch, const char* group)
	{
		AudioManager::Get()->PlayPatch(core::Name<core::CaseSensitiveKey>(patch, 1),
			core::Name<core::CaseSensitiveKey>(group, 1), 0, 0);
	}

	// FUNCTION: ENGINE 0x108D13F0
	void AudioScriptManager::PlayPatchOverlapped(const char* patch)
	{
		AudioManager::Get()->PlayPatch(core::Name<core::CaseSensitiveKey>(patch, 1), gAudioPlay, 1, 0);
	}

	// FUNCTION: ENGINE 0x108D1420
	void AudioScriptManager::PlayMusic(const char* music, const char* group)
	{
		MusicChannel::Get(core::Name<core::CaseSensitiveKey>("", 1))->Play(core::Name<core::CaseSensitiveKey>(music, 1),
			core::Name<core::CaseSensitiveKey>(group, 1), 0, false);
	}

	// FUNCTION: ENGINE 0x108D1470
	void AudioScriptManager::PlayMusicPrioritized(const char* music, const char* group, int priority, bool loop)
	{
		MusicChannel::Get(core::Name<core::CaseSensitiveKey>("", 1))->Play(core::Name<core::CaseSensitiveKey>(music, 1),
			core::Name<core::CaseSensitiveKey>(group, 1), priority, loop);
	}

	// FUNCTION: ENGINE 0x108D14D0
	void AudioScriptManager::StopMusic()
	{
		MusicChannel::Get(core::Name<core::CaseSensitiveKey>("", 1))->Stop();
	}

	// FUNCTION: ENGINE 0x108D1500
	void AudioScriptManager::PlayDialogue(LuaGOH object, char* first, char* second, char* third)
	{
		core::Name<core::CaseSensitiveKey> thirdName(third, 1);
		core::Name<core::CaseSensitiveKey> secondName(second, 1);
		core::Name<core::CaseSensitiveKey> firstName(first, 1);
		om::String text("", false);
		AudioMixer::Get()->PlayDialogue(0, 0, firstName, secondName, thirdName, DeserializeHandle(object), 500, 2000,
			1.0f, 1.0f, core::Name<core::CaseSensitiveKey>(), text);
	}

	// FUNCTION: ENGINE 0x108D15B0
	void AudioScriptManager::DialogueEvent(char* first, char* second, char* third, float fourth, float fifth,
		char* sixth, char* seventh)
	{
		core::Name<core::CaseSensitiveKey> sixthName(sixth, 1);
		core::Name<core::CaseSensitiveKey> thirdName(third, 1);
		core::Name<core::CaseSensitiveKey> secondName(second, 1);
		core::Name<core::CaseSensitiveKey> firstName(first, 1);
		om::String text(seventh, true);
		GameObjectHandle none;
		AudioMixer::Get()->PlayDialogue(0, 0, firstName, secondName, thirdName, none, 0, 0, fourth, fifth, sixthName,
			text);
	}

	// FUNCTION: ENGINE 0x108D1660
	void AudioScriptManager::DialogueEventOnObject(LuaGOH object, char* first, char* second, char* third, float fourth,
		float fifth, char* sixth, char* seventh)
	{
		core::Name<core::CaseSensitiveKey> sixthName(sixth, 1);
		core::Name<core::CaseSensitiveKey> thirdName(third, 1);
		core::Name<core::CaseSensitiveKey> secondName(second, 1);
		core::Name<core::CaseSensitiveKey> firstName(first, 1);
		om::String text(seventh, true);
		AudioMixer::Get()->PlayDialogue(0, 0, firstName, secondName, thirdName, DeserializeHandle(object), 0, 0,
			fourth, fifth, sixthName, text);
	}

	// FUNCTION: ENGINE 0x108D1720
	void AudioScriptManager::MixEvent(const char* first, const char* second, bool flag, float value)
	{
		AudioEmitterSystem* system = gAudioEmitterSystem;
		system->MixEvent(core::Name<core::CaseSensitiveKey>(first, 1), core::Name<core::CaseSensitiveKey>(second, 1), flag,
			1, value, -1.0f);
	}

	// FUNCTION: ENGINE 0x108D22C0
	// NONMATCHING: the two name temporaries land in the other stack slots and the message is built from them, the
	// same calls otherwise (68.9 %)
#ifdef NONMATCHING
	void AudioScriptManager::PlayPatch3D(const char* patch, const char* group, LuaGOH object)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		core::Name<core::CaseSensitiveKey> groupName(group, 1);
		core::Name<core::CaseSensitiveKey> patchName(patch, 1);
		AudioEmitterTriggerMessage message(patchName, groupName, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, false, 0);
		gameObject->SendMessage(&message);
	}
#endif

	// FUNCTION: ENGINE 0x108D2E90
	AudioScriptManager::AudioScriptManager()
	{
		LuaScriptManager* manager = GetScriptManager();
		manager->SetOwner(gAudioScriptManager);
		manager->RegisterMethod("snd_EnableDebugOutput", gAudioScriptManager, &AudioScriptManager::EnableDebugOutput);
		manager->RegisterMethod("snd_EnableDebugRendering", gAudioScriptManager, &AudioScriptManager::EnableDebugRendering);
		manager->RegisterMethod("snd_PlayPatch", gAudioScriptManager, &AudioScriptManager::PlayPatch);
		manager->RegisterMethod("snd_PlayPatch3D", gAudioScriptManager, &AudioScriptManager::PlayPatch3D);
		manager->RegisterMethod("snd_PlayPatchOverlapped", gAudioScriptManager, &AudioScriptManager::PlayPatchOverlapped);
		manager->RegisterMethod("snd_SetVolume", gAudioScriptManager, &AudioScriptManager::SetVolume);
		manager->RegisterMethod("snd_CreateGroup", gAudioScriptManager, &AudioScriptManager::CreateGroup);
		manager->RegisterMethod("snd_SetGroupInterrupts", gAudioScriptManager, &AudioScriptManager::SetGroupInterrupts);
		manager->RegisterMethod("snd_SetGroupVisibility", gAudioScriptManager, &AudioScriptManager::SetGroupVisibility);
		manager->RegisterMethod("snd_EnableSpew", gAudioScriptManager, &AudioScriptManager::EnableSpew);
		manager->RegisterMethod("snd_DisableSpew", gAudioScriptManager, &AudioScriptManager::DisableSpew);
		manager->RegisterMethod("snd_PlayMusic", gAudioScriptManager, &AudioScriptManager::PlayMusic);
		manager->RegisterMethod("snd_PlayMusicPrioritized", gAudioScriptManager, &AudioScriptManager::PlayMusicPrioritized);
		manager->RegisterMethod("snd_StopMusic", gAudioScriptManager, &AudioScriptManager::StopMusic);
		manager->RegisterMethod("snd_SetCollisionInstance", gAudioScriptManager, &AudioScriptManager::SetCollisionInstance);
		manager->RegisterMethod("snd_SetCollisionValues", gAudioScriptManager, &AudioScriptManager::SetCollisionValues);
		manager->RegisterMethod("snd_DisableAllGroups", gAudioScriptManager, &AudioScriptManager::DisableAllGroups);
		manager->RegisterMethod("snd_SetGroupIsEnabled", gAudioScriptManager, &AudioScriptManager::SetGroupIsEnabled);
		manager->RegisterMethod("snd_PlayDialogue", gAudioScriptManager, &AudioScriptManager::PlayDialogue);
		manager->RegisterMethod("snd_DialogueEvent", gAudioScriptManager, &AudioScriptManager::DialogueEvent);
		manager->RegisterMethod("snd_DialogueEventOnObject", gAudioScriptManager, &AudioScriptManager::DialogueEventOnObject);
		manager->RegisterMethod("snd_MixEvent", gAudioScriptManager, &AudioScriptManager::MixEvent);
		manager->RegisterMethod("snd_SetListenerOffset", gAudioScriptManager, &AudioScriptManager::SetListenerOffset);
		manager->RegisterMethod("snd_GetListenerOffset", gAudioScriptManager, &AudioScriptManager::GetListenerOffset);
		manager->ClearOwner();
	}

	// FUNCTION: ENGINE 0x108D1310
	const char* AudioScriptManager::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x108D2290
	void DestroyAudioScriptManager()
	{
		delete gAudioScriptManager;
		gAudioScriptManager = 0;
	}

	// FUNCTION: ENGINE 0x108D35B0
	void CreateAudioScriptManager()
	{
		gAudioScriptManager = new AudioScriptManager;
	}
}

template class Method0<engine::AudioScriptManager, void>;
template class Closure0<engine::AudioScriptManager, void>;
template class Method1<engine::AudioScriptManager, void, bool>;
template class Method2<engine::AudioScriptManager, void, const char*, const char*>;
template class Method3<engine::AudioScriptManager, void, const char*, const char*, engine::LuaGOH>;
template class Method1<engine::AudioScriptManager, void, const char*>;
template class Method1<engine::AudioScriptManager, void, float>;
template class Method3<engine::AudioScriptManager, void, const char*, unsigned int, unsigned int>;
template class Method2<engine::AudioScriptManager, void, const char*, bool>;
template class Method4<engine::AudioScriptManager, void, const char*, const char*, int, bool>;
template class Method3<engine::AudioScriptManager, void, float, float, float>;
template class Method4<engine::AudioScriptManager, void, engine::LuaGOH, char*, char*, char*>;
template class Method7<engine::AudioScriptManager, void, char*, char*, char*, float, float, char*, char*>;
template class Method8<engine::AudioScriptManager, void, engine::LuaGOH, char*, char*, char*, float, float, char*, char*>;
template class Method4<engine::AudioScriptManager, void, const char*, const char*, bool, float>;
template class Method0<engine::AudioScriptManager, float>;
template class Closure1<engine::AudioScriptManager, void, bool>;
template class Closure2<engine::AudioScriptManager, void, const char*, const char*>;
template class Closure3<engine::AudioScriptManager, void, const char*, const char*, engine::LuaGOH>;
template class Closure1<engine::AudioScriptManager, void, const char*>;
template class Closure1<engine::AudioScriptManager, void, float>;
template class Closure3<engine::AudioScriptManager, void, const char*, unsigned int, unsigned int>;
template class Closure2<engine::AudioScriptManager, void, const char*, bool>;
template class Closure4<engine::AudioScriptManager, void, const char*, const char*, int, bool>;
template class Closure3<engine::AudioScriptManager, void, float, float, float>;
template class Closure4<engine::AudioScriptManager, void, engine::LuaGOH, char*, char*, char*>;
template class Closure7<engine::AudioScriptManager, void, char*, char*, char*, float, float, char*, char*>;
template class Closure8<engine::AudioScriptManager, void, engine::LuaGOH, char*, char*, char*, float, float, char*, char*>;
template class Closure4<engine::AudioScriptManager, void, const char*, const char*, bool, float>;
template class Closure0<engine::AudioScriptManager, float>;

template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void>(const char*,
	engine::AudioScriptManager*, void (engine::AudioScriptManager::*)());
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, bool>(const char*,
	engine::AudioScriptManager*, void (engine::AudioScriptManager::*)(bool));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, const char*, const char*>(
	const char*, engine::AudioScriptManager*, void (engine::AudioScriptManager::*)(const char*, const char*));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, const char*, const char*,
	engine::LuaGOH>(const char*, engine::AudioScriptManager*,
	void (engine::AudioScriptManager::*)(const char*, const char*, engine::LuaGOH));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, const char*>(const char*,
	engine::AudioScriptManager*, void (engine::AudioScriptManager::*)(const char*));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, float>(const char*,
	engine::AudioScriptManager*, void (engine::AudioScriptManager::*)(float));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, const char*, unsigned int,
	unsigned int>(const char*, engine::AudioScriptManager*,
	void (engine::AudioScriptManager::*)(const char*, unsigned int, unsigned int));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, const char*, bool>(
	const char*, engine::AudioScriptManager*, void (engine::AudioScriptManager::*)(const char*, bool));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, const char*, const char*,
	int, bool>(const char*, engine::AudioScriptManager*,
	void (engine::AudioScriptManager::*)(const char*, const char*, int, bool));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, float, float, float>(
	const char*, engine::AudioScriptManager*, void (engine::AudioScriptManager::*)(float, float, float));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, engine::LuaGOH, char*,
	char*, char*>(const char*, engine::AudioScriptManager*,
	void (engine::AudioScriptManager::*)(engine::LuaGOH, char*, char*, char*));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, char*, char*, char*, float,
	float, char*, char*>(const char*, engine::AudioScriptManager*,
	void (engine::AudioScriptManager::*)(char*, char*, char*, float, float, char*, char*));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, engine::LuaGOH, char*,
	char*, char*, float, float, char*, char*>(const char*, engine::AudioScriptManager*,
	void (engine::AudioScriptManager::*)(engine::LuaGOH, char*, char*, char*, float, float, char*, char*));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, void, const char*, const char*,
	bool, float>(const char*, engine::AudioScriptManager*,
	void (engine::AudioScriptManager::*)(const char*, const char*, bool, float));
template void engine::LuaScriptManager::RegisterMethod<engine::AudioScriptManager, float>(const char*,
	engine::AudioScriptManager*, float (engine::AudioScriptManager::*)());

// The wrappers and registrations this unit instantiates, in address order:
// FUNCTION: ENGINE 0x108D1320
// FUNCTION: ENGINE 0x108D1360
// FUNCTION: ENGINE 0x108D1780
// FUNCTION: ENGINE 0x108D17D0
// FUNCTION: ENGINE 0x108D17E0
// FUNCTION: ENGINE 0x108D1830
// FUNCTION: ENGINE 0x108D1850
// FUNCTION: ENGINE 0x108D1870
// FUNCTION: ENGINE 0x108D18D0
// FUNCTION: ENGINE 0x108D18F0
// FUNCTION: ENGINE 0x108D1910
// FUNCTION: ENGINE 0x108D1980
// FUNCTION: ENGINE 0x108D19A0
// FUNCTION: ENGINE 0x108D19C0
// FUNCTION: ENGINE 0x108D1A10
// FUNCTION: ENGINE 0x108D1A20
// FUNCTION: ENGINE 0x108D1A40
// FUNCTION: ENGINE 0x108D1A90
// FUNCTION: ENGINE 0x108D1AB0
// FUNCTION: ENGINE 0x108D1AD0
// FUNCTION: ENGINE 0x108D1B40
// FUNCTION: ENGINE 0x108D1B60
// FUNCTION: ENGINE 0x108D1B80
// FUNCTION: ENGINE 0x108D1BE0
// FUNCTION: ENGINE 0x108D1C00
// FUNCTION: ENGINE 0x108D1C20
// FUNCTION: ENGINE 0x108D1CC0
// FUNCTION: ENGINE 0x108D1CF0
// FUNCTION: ENGINE 0x108D1D60
// FUNCTION: ENGINE 0x108D1D90
// FUNCTION: ENGINE 0x108D1DC0
// FUNCTION: ENGINE 0x108D1E60
// FUNCTION: ENGINE 0x108D1E90
// FUNCTION: ENGINE 0x108D1F30
// FUNCTION: ENGINE 0x108D1F80
// FUNCTION: ENGINE 0x108D1FD0
// FUNCTION: ENGINE 0x108D2080
// FUNCTION: ENGINE 0x108D20D0
// FUNCTION: ENGINE 0x108D2130
// FUNCTION: ENGINE 0x108D21D0
// FUNCTION: ENGINE 0x108D2200
// FUNCTION: ENGINE 0x108D2240
// FUNCTION: ENGINE 0x108D2260
// FUNCTION: ENGINE 0x108D23A0
// FUNCTION: ENGINE 0x108D2410
// FUNCTION: ENGINE 0x108D2460
// FUNCTION: ENGINE 0x108D2480
// FUNCTION: ENGINE 0x108D24B0
// FUNCTION: ENGINE 0x108D24D0
// FUNCTION: ENGINE 0x108D2500
// FUNCTION: ENGINE 0x108D2520
// FUNCTION: ENGINE 0x108D2570
// FUNCTION: ENGINE 0x108D2590
// FUNCTION: ENGINE 0x108D25E0
// FUNCTION: ENGINE 0x108D2600
// FUNCTION: ENGINE 0x108D2630
// FUNCTION: ENGINE 0x108D2650
// FUNCTION: ENGINE 0x108D2680
// FUNCTION: ENGINE 0x108D26A0
// FUNCTION: ENGINE 0x108D26B0
// FUNCTION: ENGINE 0x108D26E0
// FUNCTION: ENGINE 0x108D2710
// FUNCTION: ENGINE 0x108D2740
// FUNCTION: ENGINE 0x108D2770
// FUNCTION: ENGINE 0x108D27A0
// FUNCTION: ENGINE 0x108D27D0
// FUNCTION: ENGINE 0x108D2800
// FUNCTION: ENGINE 0x108D2850
// FUNCTION: ENGINE 0x108D2880
// FUNCTION: ENGINE 0x108D2890
// FUNCTION: ENGINE 0x108D28C0
// FUNCTION: ENGINE 0x108D28F0
// FUNCTION: ENGINE 0x108D2940
// FUNCTION: ENGINE 0x108D2970
// FUNCTION: ENGINE 0x108D29C0
// FUNCTION: ENGINE 0x108D2A20
// FUNCTION: ENGINE 0x108D2A80
// FUNCTION: ENGINE 0x108D2AD0
// FUNCTION: ENGINE 0x108D2B20
// FUNCTION: ENGINE 0x108D2B80
// FUNCTION: ENGINE 0x108D2BE0
// FUNCTION: ENGINE 0x108D2C40
// FUNCTION: ENGINE 0x108D2CA0
// FUNCTION: ENGINE 0x108D2D00
// FUNCTION: ENGINE 0x108D2D60
// FUNCTION: ENGINE 0x108D2DC0
// FUNCTION: ENGINE 0x108D2E20
// FUNCTION: ENGINE 0x108D1370 @ AudioScriptManager::operator new
