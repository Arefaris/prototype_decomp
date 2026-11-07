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

	// A handle on what the content keeps of a file (a pointer that starts empty)
	struct FileHandle
	{
		FileHandle() :
			pointer(0)
		{
		}

		void* pointer;
	};

	// An audio file of the content (RTTI: audio::AudioFile, an entity)
	class AudioFile : public om::Entity
	{
	public:
		// 0x10AB67F0
		explicit AudioFile(const om::ClassName& newName);
		// Slot 0 (0x10AB6860 is the body, the deleting destructor 0x10AB6C70)
		virtual ~AudioFile();
		// Slots 3, 4, 5 and 7 (0x10AB64C0 / 0x10AB64D0 / 0x10AB64E0 / 0x10AB64F0): nothing is done and nothing answered
		virtual bool Slot3(void* argument);
		virtual void Slot4(void* argument);
		virtual bool Slot5(void* argument);
		// Slot 6 (0x10AB7000): reads the file's description from a stream
		virtual bool Slot6(void* argument);
		virtual bool Slot7(void* argument);
		// Slot 9 (0x10AB6850)
		virtual om::EntityTypeBase* GetEntityType();
		OM_ENTITY_ALLOCATION(AudioFile);

		AudioFileType fileType;  // 0x20
		FileHandle file;  // 0x24: what the content keeps of the file (a counted handle; meaning not recovered)
		om::String unknown28;  // 0x28
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

	// The driver of the XAudio2 device (RTTI: audio::XAudio2RendererDriver, also a voice callback of the device library;
	// described by its name so far)
	class XAudio2RendererDriver : public RendererDriver
	{
	public:
	};
}

#endif
