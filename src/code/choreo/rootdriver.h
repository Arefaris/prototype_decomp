// choreo::PartitionDriver, choreo::RootDriver and choreo::AnimationDriver (RTTI names; RootDriver : Driver,
// AnimationDriver : PartitionDriver : Driver). The original's vftables are not reconstructed yet, so the classes
// carry no overrides and only what the reconstructed functions read is declared. Names are guesses.
#ifndef CHOREO_ROOTDRIVER_H
#define CHOREO_ROOTDRIVER_H

#include "code/choreo/deltatransform.h"
#include "code/choreo/puppet.h"

namespace choreo
{
	// The driver that partitions the pose (the unit before deltatransform.cpp); 0x38 bytes
	class PartitionDriver : public Driver
	{
	public:
		unsigned char unknown1C[0x1C];
	};

	// The driver that moves the root of the character over the step: a delta transform the tracks feed and the mask
	// saying which of its two deltas goes to the pose
	class RootDriver : public Driver
	{
	public:
		// 0x1094F000: which of the two deltas (bit 0 the translation, bit 1 the rotation) the driver hands over
		void SetMask(unsigned int mask);
		// 0x1094F020: steps the delta transform by dt
		void Update(float dt);
		// 0x1094EFE0 / 0x1094EFF0
		int Unknown1094EFE0();
		int Unknown1094EFF0();

		unsigned char unknown1C[4];
		// 3 (both) until a track narrows it
		unsigned int mMask;            // 0x20
		DeltaTransform mDelta;         // 0x24
	};

	// 0x1094EFA0 / 0x1094EFC0: the driver as a root driver, when it is one (type 9)
	RootDriver* GetRootDriver(Driver* driver);
	RootDriver* Unknown1094EFC0(Driver* driver);

	// The clip a driver plays: a channel of an animation with the range the driver shows (the object at the animation
	// driver's +0x3C). The class has no name in the binary yet; its methods are the ones at 0x10952310 - 0x10952380.
	struct AnimationClip
	{
		void* mSource;            // 0x00
		// The length of the clip in frames
		float mDuration;          // 0x04
		// The rate of the clip in frames per second
		float mFrameRate;         // 0x08
		float mUnknownC;          // 0x0C
		unsigned char mFlags;     // 0x10
		unsigned char unknown11[3];
		void* mAnimation;         // 0x14

		bool IsSet() const;
		float GetDuration() const;
		float GetFrameRate() const;
		bool Unknown10952380() const;
	};

	// 0x1094F550: keeps a frame inside [minimum, maximum], wrapping it around that range when asked to
	float ClampFrame(float frame, float minimum, float maximum, bool wrap);

	// The driver that plays one clip (the frame setters at 0x1094F300 and the root-motion test at 0x1094F530)
	class AnimationDriver : public PartitionDriver
	{
	public:
		// 0x1094F1C0 / 0x1094F1D0: whether the driver moves the root translation / the root rotation
		bool GetUnknown54() const;
		bool GetUnknown55() const;
		// 0x1094F1E0 / 0x1094F1F0
		bool GetUnknown66() const;
		bool GetUnknown67() const;
		// 0x1094F300 / 0x1094F350: the first and the last frame of the range the driver shows
		void SetStartFrame(float frame);
		void SetEndFrame(float frame);
		// 0x1094F5C0: keeps a frame inside that range
		float ClampFrame(float frame) const;
		// 0x1094F5F0: the frames one step of dt advances the clip
		float GetFrameAdvance(float dt) const;
		// 0x1094F610: the range to show, clamped
		void SetUnknownE4(float frame);

		void* mSource;            // 0x38
		AnimationClip mClip;      // 0x3C
		bool mUnknown54;          // 0x54
		bool mUnknown55;          // 0x55
		unsigned char unknown56[2];
		float mUnknown58;         // 0x58
		float mStartFrame;        // 0x5C
		float mEndFrame;          // 0x60
		unsigned char unknown64[2];
		bool mUnknown66;          // 0x66
		bool mUnknown67;          // 0x67
		unsigned char unknown68[0x7C];
		float mUnknownE4;         // 0xE4
	};

	// 0x1094F230: the driver as the type 0 driver, when it is one
	Driver* Unknown1094F230(Driver* driver);
}

#endif
