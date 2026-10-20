// choreo::PartitionDriver, choreo::RootDriver and choreo::AnimationDriver (RTTI names; RootDriver : Driver,
// AnimationDriver : PartitionDriver : Driver). The virtuals are in the order of the engine's vftables (RootDriver
// 0x10E8C1D4, five slots; AnimationDriver 0x10E8C2F4, six). Names are guesses.
#ifndef CHOREO_ROOTDRIVER_H
#define CHOREO_ROOTDRIVER_H

#include "code/choreo/deltatransform.h"
#include "code/choreo/puppet.h"
#include "code/choreo/samplechannels.h"
#include "code/pure3d/animation.h"
#include "code/pure3d/pose.h"

namespace choreo
{
	// The clip of an animation a driver shows: the range of frames of one animation that the driver keeps to. Its
	// methods sit in the unit of the sample channels (0x10952290 - 0x10952390) and are only declared here.
	struct AnimationClip
	{
		// 0x109521E0: an empty clip with its channel block
		AnimationClip();
		// 0x10952220: a copy with a block of channels of its own
		AnimationClip(const AnimationClip& other);
		// 0x10952290
		~AnimationClip();
		// 0x109522A0: binds the clip to an animation (nothing is copied while reset is clear)
		void Set(pure3d::Animation* animation, void* pose, bool reset);
		// 0x10952340: the rate of the clip in frames per second
		void SetFrameRate(float rate);
		// 0x10952370: bit 0 of the clip's flags
		bool Unknown10952370() const;
		// 0x10952310: whether the clip is bound to an animation
		bool IsSet() const;
		// 0x10952320 / 0x10952330: the length of the clip in frames and its rate in frames per second
		float GetDuration() const;
		float GetFrameRate() const;
		// 0x10952350 / 0x10952360: the word at +0xC
		float Unknown10952350() const;
		void Unknown10952360(float value);
		// 0x10952380: bit 1 of the clip's flags
		bool Unknown10952380() const;
		// 0x10952390: whether the animation drives any joint of the mask
		bool Unknown10952390(const void* mask) const;
		// 0x10952480: the animation the clip shows
		void Unknown10952480(PoseBlendSample* sample) const;
		// 0x10955260 / 0x109552C0 / 0x10955360: samples the clip over the two frames (in another unit, declared here)
		void Unknown10955260(float from, float to, bool forward, int mode);
		void Unknown109552C0(float from, float to, bool forward, int mode);
		void Unknown10955360(float frame, float weight, void* owner);

		SampleChannels* mChannels;      // 0x00
		float mDuration;                // 0x04
		float mFrameRate;               // 0x08
		float mUnknownC;                // 0x0C
		bool mFlag0 : 1;                // 0x10
		bool mFlag1 : 1;
		unsigned char unknown10Bits : 6;
		unsigned char unknown11[3];
		pure3d::Animation* mAnimation;  // 0x14
	};

	// The animation a driver plays and the clip of it that it shows (the pair at the animation driver's +0x38)
	struct AnimationBinding
	{
		// 0x10952490: no animation and an empty clip
		AnimationBinding();
		// 0x10955530: another binding's clip and animation
		AnimationBinding(const AnimationBinding& other);
		// 0x10955560: releases the animation and the clip
		~AnimationBinding();

		pure3d::Animation* mSource;     // 0x00
		AnimationClip mClip;            // 0x04
	};

	class RootDriver;
	class PoseBlendNode;
	class PoseBlendSample;

	// 0x1131E6D4 / 0x1131E6D8: how many root drivers exist and how many ever did
	extern int gRootDriverCount;
	extern int gRootDriverPeak;
	// 0x1131E6DC / 0x1131E6E0: the same for the animation drivers
	extern int gAnimationDriverCount;
	extern int gAnimationDriverPeak;

	// 0x1094EFA0 / 0x1094EFC0: the driver as a root driver, when it is one (type 9)
	RootDriver* GetRootDriver(Driver* driver);
	RootDriver* Unknown1094EFC0(Driver* driver);
	// 0x1094F230: the driver as the type 0 driver, when it is one
	Driver* Unknown1094F230(Driver* driver);

	// 0x1094F550: keeps a frame inside [minimum, maximum], or wraps it around that range
	float ClampFrame(float frame, float minimum, float maximum, bool wrap);

	// The driver that moves the root of the character over the step: a delta transform the tracks feed and the mask
	// saying which of its two deltas goes to the pose
	class RootDriver : public Driver
	{
	public:
		RootDriver();
		virtual ~RootDriver();
		// The root driver drives no joint of the pose (the engine returns 0 for both)
		virtual unsigned int GetFirstJoint() const;
		virtual unsigned int GetLastJoint() const;

		// 0x1094F000: which of the two deltas (bit 0 the translation, bit 1 the rotation) the driver hands over
		void SetMask(unsigned int mask);
		// 0x1094F020: steps the delta transform by dt
		void Update(float dt);
		// 0x1094F040: hands the deltas of the step to the pose of the puppet
		void FillPose(PoseBlendNode* node, PoseBlendSample* sample);
		// 0x1094F0A0: blends the deltas of the step into a matrix
		void BlendIntoMatrix(math::Matrix& matrix, const void* a, const void* b, float weight);

		// 3 (both) until a track narrows it
		unsigned int mMask;            // 0x20
		DeltaTransform mDelta;         // 0x24
	};

	// The driver that partitions the pose of the puppet over a range of joints (0x38 bytes). Its methods are the unit
	// before deltatransform.cpp (partitiondriver.cpp).
	class PartitionDriver : public Driver
	{
	public:
		// 0x1094D520: a driver of the given type over the joints of the skeleton (all of them until a partition is set)
		PartitionDriver(pure3d::Skeleton* skeleton, int type);
		// 0x1094D3E0
		PartitionDriver(const PartitionDriver& other);
		// 0x1094D430
		virtual ~PartitionDriver();
		// slot 0 (0x1094D690): binds the driver to the skeleton and to the partition it drives
		virtual void Bind(const DriverInfo& info);
		// slots 2/3 (0x1094B100 / 0x1094B110): the first and the last joint of the range the driver drives
		virtual unsigned int GetFirstJoint() const;
		virtual unsigned int GetLastJoint() const;
		// slot 5 (0x1094D4B0): whether the range of joints starts at the root
		virtual bool CoversRoot() const;
		// 0x1094D4C0: whether the driver's clip is at rest against the pose
		bool Unknown1094D4C0(const AnimationBinding& binding) const;
		// 0x1094D450 / 0x1094D470: the first and the last joint of the range
		void SetFirstJoint(unsigned int joint);
		void SetLastJoint(unsigned int joint);
		// 0x1094D490: the range covers the whole skeleton
		void ResetRange();
		// 0x1094D570: the range is the one the partition covers (the whole skeleton for none)
		void SetPartition(pure3d::Skeleton::Partition* partition);
		// 0x1094D610: the same for the partition of the skeleton with that index
		void SetPartitionIndex(int index);
		// 0x1094D630: the same for the partition with that name (the empty name means none)
		void SetPartitionByName(const core::Name<core::CaseSensitiveKey>& name);

		// The first and the last joint of the pose the driver drives
		unsigned int mFirstJoint;      // 0x20
		unsigned int mLastJoint;       // 0x24
		pure3d::Skeleton* mSkeleton;   // 0x28
		pure3d::Skeleton::Partition* mPartition;  // 0x2C
		const pure3d::JointMask* mJointMask;    // 0x30
		unsigned char unknown34[4];    // 0x34
	};

	// The driver that plays one clip: the frames it shows, the root motion the clip carries and the range of the pose
	// it is blended into
	class AnimationDriver : public PartitionDriver
	{
	public:
		// slot 0 (0x1094F290): binds the clip to an animation
		virtual void Bind(const DriverInfo& info);
		// slot 1 (0x1094F2D0): releases the animation
		virtual void Unbind();
		// slot 5 (0x1094F530): whether the driver moves the root of the pose
		virtual bool CoversRoot() const;

		// 0x1094F200
		~AnimationDriver();

		// 0x1094F1C0 / 0x1094F1D0: whether the driver moves the root translation / the root rotation
		bool GetUnknown54() const;
		bool GetUnknown55() const;
		// 0x1094F1E0 / 0x1094F1F0
		bool GetUnknown66() const;
		bool GetUnknown67() const;
		// 0x1094F2E0: whether the driver plays a clip
		bool IsSet() const;
		// 0x1094F2F0: whether the clip is at rest against the pose
		bool UpdateRest();
		// 0x1094FA70: steps the clip by dt
		void Update(float dt);
		// 0x1094F240: plays the animation
		void SetAnimation(pure3d::Animation* animation);
		// 0x1094F300 / 0x1094F350: the first and the last frame of the range the driver shows
		void SetStartFrame(float frame);
		void SetEndFrame(float frame);
		// 0x1094F3A0: how long the range the driver shows takes to play
		float GetRangeTime() const;
		// 0x1094F420: whether the driver has root motion at all
		float Unknown1094F420() const;
		// 0x1094F440: the time left before the range is played out
		float GetTimeLeft() const;
		// 0x1094F4F0 / 0x1094F510: whether the clip carries the root translation / rotation
		void SetUnknown64(bool value);
		void SetUnknown65(bool value);
		// 0x1094F5C0: keeps a frame inside that range
		float ClampFrame(float frame) const;
		// 0x1094F5F0: the frames one step of dt advances the clip
		float GetFrameAdvance(float dt) const;
		// 0x1094F610: the range to show, clamped
		void SetUnknownE4(float frame);
		// 0x1094F630 / 0x1094F670 / 0x1094F6B0: the clip's frame samplers
		void Unknown1094F630(float a, float b, float frame, int mode);
		void Unknown1094F670(float a, float b, float frame, int mode);
		void Unknown1094F6B0(float a, float b, void* c);
		// 0x1094F6D0: hands the clip to the pose blend node and to the sample of the node
		void Unknown1094F6D0(PoseBlendNode* node, PoseBlendSample* sample);

		AnimationBinding mBinding;     // 0x38
		bool mUnknown54;               // 0x54
		bool mUnknown55;               // 0x55
		float mUnknown58;              // 0x58
		float mStartFrame;             // 0x5C
		float mEndFrame;               // 0x60
		bool mUnknown64;               // 0x64
		bool mUnknown65;               // 0x65
		bool mUnknown66;               // 0x66
		bool mUnknown67;               // 0x67
		DeltaTransform mDelta;         // 0x68
		float mUnknownE4;              // 0xE4
		float mUnknownE8;              // 0xE8
		float mUnknownEC;              // 0xEC
		bool mUnknownF0;               // 0xF0
		float mUnknownF4;              // 0xF4
	};
}

#endif
