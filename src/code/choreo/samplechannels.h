// The channels that animate the joints of a pose, arranged by kind (an array of channel pointers per kind, one entry
// per joint; the same kinds and order as pure3d::JointChannels, which arranges them by joint). Names are guesses.
#ifndef CHOREO_SAMPLECHANNELS_H
#define CHOREO_SAMPLECHANNELS_H

#include "code/pure3d/channel.h"
#include "code/pure3d/posedata.h"

namespace choreo
{
	class SampleChannels
	{
	public:
		static const unsigned int MAX_JOINTS = 96;

		// 0x10952120: whether the root has both channels for a part
		bool HasRootChannels(int part) const;
		// 0x109521B0 / 0x109521C0 / 0x109521D0
		pure3d::QuaternionChannel* GetRootRotation(int part) const;
		pure3d::VectorChannel* GetRootTranslation(int part) const;
		pure3d::VectorChannel* GetUnknown920() const;

		// 0x10952150 - 0x109521A0: the channel of a joint, by kind
		pure3d::QuaternionChannel* GetRotation(int joint);
		pure3d::VectorChannel* GetTranslation(int joint);
		pure3d::VectorChannel* GetUnknown10(int joint);
		pure3d::VectorChannel* GetScale(int joint);
		pure3d::VectorChannel* GetUnknown14(int joint);
		pure3d::VectorChannel* GetUnknown1C(int joint);

		// 0x10953E40: lays the values of the channels at time over the joints first to last of the arrays, each moving
		// from the pose towards the value by weight (the rotations by the shortest arc). Only the joints of the mask
		// take part (all without one); a joint without a channel takes the rest pose's value; the kinds of value
		// beyond the rotation and translation are only done when full is set.
		void Blend(pure3d::JointArrays* arrays, unsigned int first, unsigned int last, const pure3d::JointMask* mask,
			const pure3d::SkeletonData* rest, pure3d::FrameTime time, bool full, float weight);

		// 0x10952ED0 / 0x10952F90 / 0x109530F0: what the channels give for the root: the rotation and the
		// translation that carry it from one frame to the other (the second frame first when not forward), and the
		// root's scale at a time. They answer whether there were channels to read.
		int GetRootRotation(pure3d::FrameTime to, pure3d::FrameTime from, bool forward, math::Quaternion* out);
		bool GetRootTranslation(pure3d::FrameTime to, pure3d::FrameTime from, bool forward, math::Vector* out);
		bool GetRootScale(pure3d::FrameTime time, math::Vector* out);

		// 0x10954E00 / 0x10954C20: lay the channels at time over a two-component value / over the local matrices of a
		// pose (only the joints of the mask when there is one) by weight
		void BlendValue(pure3d::FrameTime time, float* value, float weight);
		void BlendMatrices(math::Matrix* matrices, const pure3d::JointMask* mask, const pure3d::SkeletonData* skeleton,
			pure3d::FrameTime time, float weight);

		pure3d::QuaternionChannel* mRotations[MAX_JOINTS];
		pure3d::VectorChannel* mTranslations[MAX_JOINTS];
		pure3d::VectorChannel* mUnknown10[MAX_JOINTS];
		pure3d::VectorChannel* mScales[MAX_JOINTS];
		pure3d::VectorChannel* mUnknown14[MAX_JOINTS];
		pure3d::VectorChannel* mUnknown1C[MAX_JOINTS];
		// 0x900 - 0x91C: the root's rotation and translation channels of the animation, per skeleton part
		pure3d::QuaternionChannel* mRootRotations[4];
		pure3d::VectorChannel* mRootTranslations[4];
		pure3d::VectorChannel* mUnknown920;
		unsigned char unknown924[0xC];
	};
}

#endif
