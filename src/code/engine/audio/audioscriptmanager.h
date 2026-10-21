// engine::AudioScriptManager (RTTI name of the script method wrappers; the class has no data and no virtual functions):
// the scripts' access to the audio system. Its constructor registers the snd_* functions of the script context as
// closures over this object; the member names follow the script names. Unit 0x108D1140 - 0x108D35E0 (no assert path;
// the file name is a guess).
#ifndef ENGINE_AUDIO_AUDIOSCRIPTMANAGER_H
#define ENGINE_AUDIO_AUDIOSCRIPTMANAGER_H

#include "code/engine/gameobject/gameobjectsystem.h"

namespace engine
{
	class AudioScriptManager
	{
	public:
		// 0x108D2E90: registers the functions
		AudioScriptManager();

		// snd_EnableDebugOutput / snd_EnableDebugRendering
		void EnableDebugOutput(bool enable);
		void EnableDebugRendering(bool enable);
		// snd_PlayPatch / snd_PlayPatch3D / snd_PlayPatchOverlapped
		void PlayPatch(const char* patch, const char* group);
		void PlayPatch3D(const char* patch, const char* group, LuaGOH object);
		void PlayPatchOverlapped(const char* patch);
		// snd_SetVolume
		void SetVolume(float volume);
		// snd_CreateGroup / snd_SetGroupInterrupts / snd_SetGroupVisibility / snd_SetGroupIsEnabled /
		// snd_DisableAllGroups
		void CreateGroup(const char* group, unsigned int first, unsigned int second);
		void SetGroupInterrupts(const char* group, const char* other);
		void SetGroupVisibility(const char* group, bool visible);
		void SetGroupIsEnabled(const char* group, bool enabled);
		void DisableAllGroups();
		// snd_EnableSpew / snd_DisableSpew
		void EnableSpew();
		void DisableSpew();
		// snd_PlayMusic / snd_PlayMusicPrioritized / snd_StopMusic
		void PlayMusic(const char* music, const char* group);
		void PlayMusicPrioritized(const char* music, const char* group, int priority, bool loop);
		void StopMusic();
		// snd_SetCollisionInstance / snd_SetCollisionValues (empty in this build)
		void SetCollisionInstance(const char* instance);
		void SetCollisionValues(float first, float second, float third);
		// snd_PlayDialogue / snd_DialogueEvent / snd_DialogueEventOnObject
		void PlayDialogue(LuaGOH object, char* first, char* second, char* third);
		void DialogueEvent(char* first, char* second, char* third, float fourth, float fifth, char* sixth, char* seventh);
		void DialogueEventOnObject(LuaGOH object, char* first, char* second, char* third, float fourth, float fifth,
			char* sixth, char* seventh);
		// snd_MixEvent
		void MixEvent(const char* first, const char* second, bool flag, float value);
		// snd_SetListenerOffset / snd_GetListenerOffset
		void SetListenerOffset(float offset);
		float GetListenerOffset();
	};

	// The one instance (0x11318928)
	extern AudioScriptManager* gAudioScriptManager;
}

#endif
