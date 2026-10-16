// proto::LODRenderBehaviour: see the header. The file name and the member names are guesses.
#include "code/math/mathutils.h"
#include "code/proto/render/lodrenderbehaviour.h"

namespace proto
{
	// FUNCTION: ENGINE 0x102DA700
	void LODRenderBehaviour::UpdateLevel()
	{
		unsigned int wanted = 0;
		if ((flags & 1) != 0 && readyBegin != readyEnd)
		{
			unsigned int size = (levelsEnd - levelsBegin) >> 3;
			float t = math::Clamp(fade, 0.0f, 1.0f);
			wanted = (unsigned int)((1.0f - t) * (float)(unsigned int)(size - 1));
		}
		unsigned int previous = level;
		if (wanted != previous)
		{
			level = wanted;
			unsigned int last = wanted >= minimumLevels ? wanted : minimumLevels;
			ChangeDrawableLevels(previous, levelsBegin + wanted * 8, levelsBegin + last * 8);
		}
	}
}
