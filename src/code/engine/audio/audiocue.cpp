// engine::AudioCue: see the header.
#include "code/engine/audio/audiocue.h"
#include "code/om/metatype.h"

namespace engine
{
	// FUNCTION: ENGINE 0x1087EA50
	AudioCue::AudioCue(om::Entity* newEntity)
	{
		reference.entity = newEntity;
		if (newEntity != 0)
		{
			om::ThreadSafeRefCount::AddRef(&newEntity->count);
		}
	}

	// FUNCTION: ENGINE 0x1087E650
	void AudioCue::Slot3(int unused)
	{
		om::StreamContext context;
		context.Set(om::GetStreamContextObject(), om::GetStreamContextObject(), om::GetStreamContextObject(),
			om::GetStreamContextObject());
		om::StreamContext* pointer = &context;
		reference.entity->Slot8(&pointer);
	}

	// FUNCTION: ENGINE 0x1087E6B0
	bool AudioCue::IsReady()
	{
		return reference.entity->Slot1() ? true : false;
	}

	// FUNCTION: ENGINE 0x1087EAB0
	// The compiler's destructor of AudioCue (the class declares none)

	// FUNCTION: ENGINE 0x1087E540
	const char* AudioCue::AllocationTag()
	{
		return "";
	}
}
