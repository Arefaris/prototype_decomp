// pure3d animation channels (unit around 0x10734F00 - 0x10736900 with the channel loader; file name guessed from the
// classes). Names are guesses.
#include "code/pure3d/channel.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x107350B0
	void Float1Channel::GetValue(float frame, float* out)
	{
		ChannelKeys<float> keys;
		keys.Set(mode, count, frames, values);
		keys.Evaluate(FrameTime(frame), out);
	}
}
