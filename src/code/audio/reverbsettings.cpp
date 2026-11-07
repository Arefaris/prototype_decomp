// The audio library's reverb settings (0x105BCDF0; the class is another unit's, see engine/audio/audioglobalsettings.h).
#include "code/audio/effect.h"
#include "code/engine/audio/audioglobalsettings.h"

namespace engine
{
	// FUNCTION: ENGINE 0x105BCDF0
	void ReverbSettings::SetDistanceFactor(float factor)
	{
		float lowest = 1.0f;
		float highest = 1.5f;
		float value = factor + 1.0f;
		distanceFactor = audio::Clamp(value, lowest, highest);
	}
}
