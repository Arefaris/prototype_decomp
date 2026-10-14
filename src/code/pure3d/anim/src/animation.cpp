// pure3d animations (code/pure3d/anim/src/animation.cpp, path from the asserts; the unit starts around 0x106E2A30):
// the key readers of the channels among others. Names are guesses.
#include "code/pure3d/channel.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x106E3070
	void ChannelKeysBase::SetFrames(const unsigned short* frames)
	{
		this->frames = frames;
	}

	// FUNCTION: ENGINE 0x106E3080
	void ChannelKeysBase::Set(const unsigned short* frames, unsigned int count, const void* values)
	{
		SetFrames(frames);
		this->count = count;
		this->values = values;
	}

	template<class T> void ChannelKeys<T>::Set(const unsigned short* frames, unsigned int count, const T* values,
		unsigned int mode)
	{
		ChannelKeysBase::Set(frames, count, values);
		this->mode = mode;
	}
}

// FUNCTION: ENGINE 0x106E30C0
template void pure3d::ChannelKeys<float>::Set(const unsigned short* frames, unsigned int count, const float* values,
	unsigned int mode);
