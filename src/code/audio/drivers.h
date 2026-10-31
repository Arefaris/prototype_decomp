// The audio renderer drivers of the platform (RTTI: audio::NullRendererDriver, MmeRendererDriver, AsioRendererDriver,
// WdmKsRendererDriver and DirectSoundRendererDriverImpl) and the enumerations of the mixer and the audio files. Only what
// the reflection of the drivers names is described so far: the accessors of the properties the registration binds.
#ifndef AUDIO_DRIVERS_H
#define AUDIO_DRIVERS_H

#include "code/audio/rendererdriver.h"
#include "code/om/entity.h"

namespace audio
{
	// Where the device's buffer lives (names of the values not recovered)
	enum BufferLocation
	{
		BufferLocationUnknown
	};

	// How the mixer mixes (names of the values not recovered)
	enum MixType
	{
		MixTypeUnknown
	};

	// Which windows' sound plays (names of the values not recovered)
	enum Focus
	{
		FocusUnknown
	};

	// The format of an audio file (names of the values not recovered)
	enum AudioFileType
	{
		AudioFileTypeUnknown
	};

	// An audio file of the content (RTTI: audio::AudioFile, an entity)
	class AudioFile : public om::Entity
	{
	public:
		// 0x10AB67F0
		explicit AudioFile(const om::ClassName& newName);
		OM_ENTITY_ALLOCATION(AudioFile);

		AudioFileType fileType;  // 0x20
		char unknown24[0x10];
		om::String path;  // 0x34
	};

	// The multimedia extension driver (names of the accessors guessed)
	class MmeRendererDriver : public RendererDriver
	{
	public:
		void SetWaveFormat(WAVEFORMAT newWaveFormat);
		WAVEFORMAT GetWaveFormat() const;
	};

	class WdmKsRendererDriver : public RendererDriver
	{
	public:
		void SetWaveFormat(WAVEFORMAT newWaveFormat);
		WAVEFORMAT GetWaveFormat() const;
	};

	// The interface the DirectSound driver implements besides the driver base (at 0x7C of the object; RTTI:
	// audio::DirectSoundRendererDriver, four slots not recovered)
	class DirectSoundRendererDriver
	{
	public:
		virtual void Slot0() = 0;
		virtual void Slot1() = 0;
		virtual void Slot2() = 0;
		virtual void Slot3() = 0;
	};

	class DirectSoundRendererDriverImpl : public RendererDriver, public DirectSoundRendererDriver
	{
	public:
		void SetBufferLocation(BufferLocation newBufferLocation);
		BufferLocation GetBufferLocation() const;
		void SetMixType(MixType newMixType);
		MixType GetMixType() const;
		void SetFocus(Focus newFocus);
		Focus GetFocus() const;
		void SetWaveFormat(WAVEFORMAT newWaveFormat);
		WAVEFORMAT GetWaveFormat() const;
	};
}

#endif
