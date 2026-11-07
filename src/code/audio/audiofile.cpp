// The audio file entity of the content (0x10AB64C0 - 0x10AB7000).
#include "code/audio/drivers.h"

namespace audio
{
	// FUNCTION: ENGINE 0x10AB67F0
	AudioFile::AudioFile(const om::ClassName& newName) :
		Entity(newName),
		fileType(static_cast<AudioFileType>(3))
	{
	}

	// FUNCTION: ENGINE 0x10AB64C0
	bool AudioFile::Slot3(void* argument)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x10AB64D0
	void AudioFile::Slot4(void* argument)
	{
	}

	// FUNCTION: ENGINE 0x10AB64E0
	bool AudioFile::Slot5(void* argument)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x10AB64F0
	bool AudioFile::Slot7(void* argument)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x10AB6850
	om::EntityTypeBase* AudioFile::GetEntityType()
	{
		return om::FindEntityType(typeid(AudioFile));
	}
}
