// pure3d animation channels (RTTI names pure3d::Channel, Float1Channel and the other channel types) and the key
// readers they evaluate through (no names survive for those; their copies sit in the animation unit,
// 0x106E2FE0 - 0x106E4300). Layouts partial; names are guesses.
#ifndef PURE3D_CHANNEL_H
#define PURE3D_CHANNEL_H

namespace pure3d
{
	// A time in an animation: the frame number and the exact time (8 bytes, passed by value)
	struct FrameTime
	{
		// 0x106E3010
		FrameTime& Set(float time);

		short frame;
		float time;
	};

	// The keys of a channel: their frame numbers, count and values
	class ChannelKeysBase
	{
	public:
		// 0x106E3070 / 0x106E3080
		void SetFrames(const unsigned short* frames);
		void Set(const unsigned short* frames, unsigned int count, const void* values);

		const unsigned short* frames;
		unsigned int count;
		const void* values;
	};

	// Typed keys with their interpolation mode (0x106E30A0, 0x106E30C0 and 0x106E30E0 are three instances of Set;
	// 0x106E41C0 is the float instance of Evaluate)
	template<class T> class ChannelKeys : public ChannelKeysBase
	{
	public:
		void Set(const unsigned short* frames, unsigned int count, const T* values, unsigned int mode);
		void Evaluate(FrameTime time, T* out);

		unsigned int mode;
	};

	class Float1Channel
	{
	public:
		virtual void Unknown0();

		// 0x107350B0: the value at frame
		void GetValue(float frame, float* out);

		const unsigned short* frames;
		unsigned char unknown8[0xC];
		unsigned int count;
		const float* values;
		unsigned char unknown1C[4];
		unsigned int mode;
	};
}

#endif
