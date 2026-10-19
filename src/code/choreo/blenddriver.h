// choreo::AnimationBlendDriver (RTTI name; : PartitionDriver, vftable 0x10E8BB64, driver type 1): the driver that
// plays up to fifteen clips at once and blends them into one phase running from 0 to 1. Its methods are the unit
// before deltatransform.cpp (partitiondriver.cpp). Names are guesses.
#ifndef CHOREO_BLENDDRIVER_H
#define CHOREO_BLENDDRIVER_H

#include "code/choreo/rootdriver.h"

namespace choreo
{
	// One clip of the blend driver (0x2C bytes): the animation and its clip, the range of frames shown, how fast the
	// clip runs and how much it weighs in the blend
	struct BlendEntry
	{
		// 0x1094C7D0: no animation, the whole clip, rate and weight 1
		BlendEntry();
		// 0x1094C820: whether the entry takes no part in the blend (no clip, or a weight of nothing)
		bool IsIdle() const;
		// 0x1094C850: the number of frames of the range shown (the range kept inside the clip)
		float GetLength() const;
		// 0x1094C8F0: the frame of the clip at a phase of the range (kept inside the range, or wrapped around it)
		float GetFrame(float phase, bool wrap) const;
		// 0x1094CA80: the frames the range takes for a step of the phase
		float GetFrameStep(float phaseStep) const;
		// 0x1094CA90: the step of the phase that takes that many frames
		float GetPhaseStep(float frames) const;

		AnimationBinding mBinding;     // 0x00
		float mStartFrame;             // 0x1C
		// Negative counts back from the last frame of the clip
		float mEndFrame;               // 0x20
		float mRate;                   // 0x24
		float mWeight;                 // 0x28
	};

	class AnimationBlendDriver;

	// 0x1094CAE0 / 0x1094CB00: the driver as a blend driver, when it is one (type 1)
	AnimationBlendDriver* GetAnimationBlendDriver(Driver* driver);
	AnimationBlendDriver* Unknown1094CB00(Driver* driver);

	class AnimationBlendDriver : public PartitionDriver
	{
	public:
		static const int MAX_ENTRIES = 15;

		// 0x1094D1F0
		AnimationBlendDriver(pure3d::Skeleton* skeleton);
		// 0x1094D290
		virtual ~AnimationBlendDriver();
		// slot 0 (0x1094CB50): binds the clips of the entries to the skeleton
		virtual void Bind(const DriverInfo& info);
		// slot 1 (0x1094CB20): releases the animations of the entries
		virtual void Unbind();

		// 0x1094C790 / 0x1094C7A0: the two flags at +0x2D0 and +0x2D1
		bool IsLooping() const;
		bool GetUnknown2D1() const;
		// 0x1094C7B0 / 0x1094C7C0: the scale of the phase step and the phase
		float GetScale() const;
		float GetPhase() const;
		// 0x1094CBC0: how many entries take part in the blend
		int GetActiveCount() const;
		// 0x1094CBD0: the animation of an entry
		pure3d::Animation* GetAnimation(int index) const;
		// 0x1094CBE0: whether the clips of all the entries are at rest against the skeleton
		bool AllAtRest() const;
		// 0x1094CC30 / 0x1094CC50: the word at +0xC of the clip of an entry
		float GetEntryUnknownC(int index) const;
		void SetEntryUnknownC(int index, float value);
		// 0x1094CC70 / 0x1094CC80 / 0x1094CCA0 / 0x1094CCB0 / 0x1094CCD0 / 0x1094CCE0: the range and the rate of an entry
		float GetStartFrame(int index) const;
		void SetStartFrame(int index, float frame);
		float GetEndFrame(int index) const;
		void SetEndFrame(int index, float frame);
		float GetRate(int index) const;
		void SetRate(int index, float rate);
		// 0x1094CD00 / 0x1094CD10: the weight of an entry (an entry without weight leaves the active count)
		float GetWeight(int index) const;
		void SetWeight(int index, float weight);
		// 0x1094CD60: how long the blend takes to play once at the speed of its clips, before the scale
		float GetNaturalDuration() const;
		// 0x1094CEA0: scales the phase so that the blend takes that long
		void SetDuration(float duration);
		// 0x1094CEF0: how far the phase moves in dt seconds
		float GetPhaseStep(float dt) const;
		// 0x1094CF90: sets the phase (wrapped around when the driver loops, kept in [0, 1] otherwise)
		void SetPhase(float phase);
		// 0x1094CFF0: moves the phase on by its step
		void Advance();
		// 0x1094D020: writes the blend node and the samples of the entries that take part
		void FillNode(PoseBlendNode* node, PoseBlendSample* samples);
		// 0x1094D160: whether the owner stops the driver (it has played out)
		void UpdateFinished();
		// 0x1094D2C0: puts an animation into an entry
		void SetAnimation(int index, pure3d::Animation* animation);
		// 0x1094D390: steps the phase by dt
		void Step(float dt);

		int mActiveCount;              // 0x38
		BlendEntry mEntries[MAX_ENTRIES];  // 0x3C
		bool mLooping;                 // 0x2D0
		bool mUnknown2D1;              // 0x2D1
		float mScale;                  // 0x2D4
		float mPreviousPhase;          // 0x2D8
		float mPhase;                  // 0x2DC
		float mPhaseStep;              // 0x2E0
	};
}

#endif
