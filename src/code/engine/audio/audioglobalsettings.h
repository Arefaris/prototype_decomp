// The audio library's global settings (RTTI: engine::AudioGlobalSettings, an om entity named "GlobalSettings", and
// engine::SoundGroup, a plain value) and their om reflection (audioglobalsettings.cpp). The settings are loaded
// from the game's audio data; the reflected names (ListenerOffset, ReverbDistanceFactor, SoundGroups, and the
// groups' Name, MaxSounds, MaxSoundsPerInstance, InterruptList) are the original's.
#ifndef ENGINE_AUDIOGLOBALSETTINGS_H
#define ENGINE_AUDIOGLOBALSETTINGS_H

#include "code/om/dynamicarray.h"
#include "code/om/entity.h"
#include "code/om/string.h"

namespace engine
{
	// A limit on how many sounds of a kind play at once and which kinds it interrupts (0x1C bytes)
	class SoundGroup
	{
	public:
		SoundGroup();
		SoundGroup(const SoundGroup& other);
		~SoundGroup();

		const om::String& GetName() const;
		void SetName(const om::String& newName);
		const unsigned int& GetMaxSounds() const;
		void SetMaxSounds(const unsigned int& newMaxSounds);
		const unsigned int& GetMaxSoundsPerInstance() const;
		void SetMaxSoundsPerInstance(const unsigned int& newMaxSoundsPerInstance);
		const om::DynamicArray<om::String, unsigned short>& GetInterruptList() const;
		void SetInterruptList(const om::DynamicArray<om::String, unsigned short>& newInterruptList);

		unsigned int maxSounds;  // 0
		unsigned int maxSoundsPerInstance;  // 4
		om::DynamicArray<om::String, unsigned short> interruptList;  // 8
		om::String name;  // 0x10
	};

	// The settings entity (0x30 bytes)
	class AudioGlobalSettings : public om::Entity
	{
	public:
		const float& GetListenerOffset() const;
		void SetListenerOffset(const float& newListenerOffset);
		const float& GetReverbDistanceFactor() const;
		void SetReverbDistanceFactor(const float& newReverbDistanceFactor);
		const om::DynamicArray<SoundGroup, unsigned short>& GetSoundGroups() const;
		void SetSoundGroups(const om::DynamicArray<SoundGroup, unsigned short>& newSoundGroups);

		char unknown10[0x10];
		float listenerOffset;  // 0x20
		float reverbDistanceFactor;  // 0x24
		om::DynamicArray<SoundGroup, unsigned short> soundGroups;  // 0x28
	};
}

#endif
