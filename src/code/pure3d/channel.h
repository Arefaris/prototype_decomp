// pure3d animation channels (RTTI names pure3d::Channel, Float1Channel and the other channel types) and the key
// readers they evaluate through (no names survive for those; their copies sit in the animation unit,
// 0x106E2FE0 - 0x106E7BE0). Layouts partial; names are guesses.
#ifndef PURE3D_CHANNEL_H
#define PURE3D_CHANNEL_H

#include "code/math/compressedquaternion.h"
#include "code/math/quaternion.h"
#include "code/math/vector.h"

namespace pure3d
{
	// A time in an animation: the frame number and the exact time (8 bytes, passed by value)
	struct FrameTime
	{
		// 0x106E2FE0
		FrameTime();
		// 0x106E3010
		FrameTime(float time);
		// 0x106E3030: sets the frame and the time that goes with it
		void SetFrame(short frame);
		// 0x106E3050: sets the time and the frame that goes with it
		void SetTime(float newTime);
		// The exact time (inline in the engine)
		float GetFloat() const
		{
			return time;
		}

		short frame;
		float time;
	};

	// The keys of a channel: whether to interpolate, the number of keys and their frame numbers
	class ChannelKeysBase
	{
	public:
		// 0x106E3070 / 0x106E3080
		void SetMode(unsigned int mode);
		void Set(unsigned int mode, unsigned int count, const short* frames);
		// 0x106E34E0: finds the keys around a time (a binary search); false when the time is before the first or
		// after the last key, where both keys are that one
		bool FindKeys(FrameTime time, unsigned int* index0, unsigned int* index1, short* frame0, short* frame1);

		unsigned int mode;
		unsigned int count;
		const short* frames;
	};

	// What a key type evaluates to (the compressed quaternions evaluate to a Quaternion)
	template<class T> struct KeyValue
	{
		typedef T Type;
	};
	template<> struct KeyValue<math::CompressedQuaternion6>
	{
		typedef math::Quaternion Type;
	};
	template<> struct KeyValue<math::CompressedQuaternion8>
	{
		typedef math::Quaternion Type;
	};

	// Typed keys (0x106E30A0, 0x106E30C0 and 0x106E30E0 are three instances of Set; 0x106E41C0 is the float
	// instance of Evaluate, 0x106E6350 and 0x106E69B0 those of the two compressed quaternions)
	template<class T> class ChannelKeys : public ChannelKeysBase
	{
	public:
		void Set(unsigned int mode, unsigned int count, const short* frames, const T* values);
		void Evaluate(FrameTime time, typename KeyValue<T>::Type* out);

		const T* values;
	};

	// The rotation keys of a channel in one of its stored forms: a tag, then the keys of that form (the compressed
	// ones among them); the evaluation dispatches on the tag
	class RotationKeys
	{
	public:
		// 0x106E6D70
		void Evaluate(FrameTime time, math::Quaternion* out);

		int type;
	};

	// The same for three-component values (translations, scales)
	class VectorKeys
	{
	public:
		// 0x106E5CC0
		void Evaluate(FrameTime time, math::Vector* out);

		int type;
	};

	// pure3d::QuaternionChannel (RTTI: bases RotationChannel, SimpleChannel, Channel)
	class QuaternionChannel
	{
	public:
		virtual void Unknown0();

		// 0x107354B0: the rotation that takes the value at previousTime to the one at time
		void GetDelta(float previousTime, float time, math::Quaternion* out);

		unsigned char unknown4[0x1C];
		RotationKeys mKeys;
	};

	// pure3d::VectorChannel (RTTI: bases SimpleChannel, Channel)
	class VectorChannel
	{
	public:
		virtual void Unknown0();
		virtual void Unknown1();
		virtual void Unknown2();
		virtual void Unknown3();
		// The change of the value from previousTime to time
		virtual void GetDelta(float previousTime, float time, math::Vector* out);

		unsigned char unknown4[0x1C];
		VectorKeys mKeys;
	};

	// The channels that animate one joint, in the order of the pose's arrays; a channel is null when the animation
	// does not animate that kind of value of the joint
	struct JointChannels
	{
		QuaternionChannel* rotation;
		VectorChannel* translation;
		VectorChannel* unknown10;
		VectorChannel* scale;
		VectorChannel* unknown14;
		VectorChannel* unknown1C;
	};

	class Float1Channel
	{
	public:
		virtual void Unknown0();

		// 0x107350B0: the value at frame
		void GetValue(float frame, float* out);

		unsigned int mode;
		unsigned char unknown8[0xC];
		unsigned int count;
		const short* frames;
		unsigned char unknown1C[4];
		const float* values;
	};
}

#endif
