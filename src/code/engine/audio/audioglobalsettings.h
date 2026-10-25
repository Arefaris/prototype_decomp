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

	// The audio system and its parts that the settings put into effect (other units, names guessed)
	class AudioListener
	{
	public:
		char unknown0[0x54];
		float listenerOffset;  // 0x54
	};
	extern AudioListener* gAudioListener;

	class ReverbSettings
	{
	public:
		// 0x105BCDF0: keeps the factor within its limits
		void SetDistanceFactor(float factor);
	};
	extern ReverbSettings gReverbSettings;

	class AudioSystem
	{
	public:
		static AudioSystem* Get();
		// 0x10871140: makes the group
		void AddSoundGroup(const om::String& name, unsigned int maxSounds, unsigned int maxSoundsPerInstance);
		// 0x10871240: lets the group interrupt another
		void AddInterrupt(const om::String& group, const om::String& other);
	};

	// The settings entity (0x30 bytes)
	class AudioGlobalSettings : public om::Entity
	{
	public:
		explicit AudioGlobalSettings(const om::ClassName& newName) :
			Entity(newName),
			listenerOffset(0.0f),
			reverbDistanceFactor(0.0f),
			soundGroups()
		{
		}
		virtual ~AudioGlobalSettings();
		// Slot 5 (0x108CC520): reads the settings, then puts them into effect
		virtual bool Slot5(void* argument);
		virtual om::EntityTypeBase* GetEntityType();
		OM_ENTITY_ALLOCATION(AudioGlobalSettings);

		// 0x108CAE10: gives the listener its offset and the reverb its factor, and tells the system about every
		// sound group and its interruptions
		void Apply();
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
