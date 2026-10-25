// engine::AudioMessage, AudioEmitterMessage and AudioEmitterTriggerMessage (RTTI names; classes): messages to an
// audio emitter. The emitter messages name a sound of the emitter and apply themselves to the emitter (slot 1);
// AudioEmitterTriggerMessage plays or stops the sound and sets its parameters. Unit 0x107FE2B0 - 0x107FE508 (no
// assert path; directory and file name are guesses). The audio emitter, its sounds and the audio system live in
// other units (0x1086xxxx - 0x1087xxxx) and are only declared; their names and the members' names are guesses.
#ifndef ENGINE_AUDIO_AUDIOMESSAGE_H
#define ENGINE_AUDIO_AUDIOMESSAGE_H

#include "code/core/name.h"
#include "code/engine/audio/audiomanager.h"
#include "code/engine/message.h"

namespace engine
{
	typedef core::Name<core::CaseSensitiveKey> AudioName;

	// A string of the audio library (4 bytes; another unit, 0x105B3xxx)
	struct AudioString
	{
		int handle;
	};

	// A value an audio parameter can be driven by (another unit)
	class AudioParameterSource
	{
	public:
		// 0x102FB570
		float GetValue();
	};

	// A name hash passed by value
	struct AudioHash
	{
		AudioHash(const AudioName& name)
		{
			const unsigned __int64& hash = name.GetHash();
			low = ((const unsigned int*)&hash)[0];
			high = ((const unsigned int*)&hash)[1];
		}

		unsigned int low;
		unsigned int high;
	};

	// The parameter sources of a sound bank by name hash (another unit)
	class AudioParameterTable
	{
	public:
		// 0x102F6470
		AudioParameterSource* Find(AudioHash hash);
	};

	struct AudioBank
	{
		struct Data
		{
			int unknown0[8];
			AudioParameterTable parameters;
		};

		AudioParameterTable* GetParameters() const
		{
			return &data->parameters;
		}

		int unknown0[2];
		Data* data;
	};

	// A sound an emitter plays
	class AudioSound
	{
	public:
		// 0x108703A0: starts the event of the sound (name guessed)
		void Trigger(const AudioName& event);
		// 0x108714D0
		void Release(bool unknown);
		// 0x10306300: sets a parameter of the sound
		void SetParameter(const AudioName& name, const float* value);

		void SetUnknown21(bool value)
		{
			unknown21 = value;
		}
		void UpdateUnknown24()
		{
			unknown24 = AudioSystem::Get()->GetUnknown28();
		}

		int unknown0[0x14 / 4];
		AudioBank* bank;
		int unknown18[2];
		bool unknown20;
		bool unknown21;
		int unknown24;
	};

	// The sounds of an emitter by name
	__declspec(align(8)) class AudioSoundList
	{
	public:
		// 0x10870AF0: an empty list of the name
		AudioSoundList(const AudioName& newName);
		// 0x10871620: takes every sound out
		~AudioSoundList();
		// 0x1086F2D0
		AudioSound* Find(const AudioName& name);
		// 0x10870D40: a new sound of name (radius unknown, category the sound's)
		AudioSound* Create(const AudioName& name, float radius, const AudioString& category);
		// 0x10871500
		void Remove(AudioSound* sound, bool unknown);

		AudioName name;  // 0
		char unknown8[0x1C];  // the tree of the sounds (+8) and the array of their slots (+0x1C)
	};

	class AudioEmitter
	{
	public:
		virtual void Slot0();
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot5();
		virtual void Slot6();
		virtual void Slot7();
		virtual void Update(float dt);

		int unknown4[3];
		AudioSoundList sounds;
	};

	class AudioMessage : public IntrusiveMessage
	{
	public:
		AudioMessage(int newType, short newId) : IntrusiveMessage(newType, newId)
		{
		}
		virtual ~AudioMessage();

		int unknownC;
	};

	class AudioEmitterMessage : public AudioMessage
	{
	public:
		AudioEmitterMessage(int newType, short newId, const AudioName& newSound) : AudioMessage(newType, newId), sound(newSound)
		{
		}
		virtual void Apply(AudioEmitter* emitter) = 0;

		AudioName sound;
	};

	class AudioEmitterTriggerMessage : public AudioEmitterMessage
	{
	public:
		enum
		{
			MODE_KEEP = 1,
			MODE_RESTART = 2,
			MODE_ONCE = 3
		};

		// The sound and the event named, the volume, the distances and the pitches, the flag at +0x34 and the mode
		// (the engine keeps an out-of-line copy at 0x1008CEE0)
		AudioEmitterTriggerMessage(const AudioName& newSound, const AudioName& newEvent, float newVolume,
			float newMinDistance, float newMaxDistance, float newMinPitch, float newMaxPitch, bool newFlag, int newMode) :
			AudioEmitterMessage(0x15, 0, newSound),
			event(newEvent),
			minDistance(newMinDistance),
			maxDistance(newMaxDistance),
			minPitch(newMinPitch),
			maxPitch(newMaxPitch),
			volume(newVolume),
			unknown34(newFlag),
			mode(newMode)
		{
		}
		virtual void Apply(AudioEmitter* emitter);

		AudioName event;
		float minDistance;
		float maxDistance;
		float minPitch;
		float maxPitch;
		float volume;
		bool unknown34;
		int mode;
	};

	// The event and parameter names (0x11284130 - 0x11284240) and the default sound category ("!NONE!")
	extern AudioName gAudioPlay;
	extern AudioName gAudioStop;
	extern AudioName gAudioMin;
	extern AudioName gAudioMax;
	extern AudioName gAudioMinPitch;
	extern AudioName gAudioMaxPitch;
	extern AudioName gAudioVolume;
	extern AudioString gAudioNoCategory;
}

#endif
