// pure3d::PoseAnimationController (unit around 0x10732100 - 0x10733300; file name guessed from the class). Names are
// guesses.
#include "code/pure3d/posecontroller.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10732320
	// EQUIVALENT: the same operations in the same order; the engine keeps the joint index, the channel pointers and
	// the lerped vector in other registers (its frame is the same size) and interleaves the three components of the
	// lerps
	void PoseAnimationController::Apply(int unknown, float time, float weight, JointChannels* channels,
		float* previousTime)
	{
		float alpha = 1.0f - weight;
		Skeleton* skeleton = mPose->mSkeleton;
		unsigned int jointCount = mPose->mData.mArrays.mJointCount;
		JointMask* mask = mInfo->mJointMask;
		unsigned int joint = 0;
		math::Vector vector;
		if (mAnimatesRoot)
		{
			joint = 1;
			if (mask->words[0] & 1)
			{
				if (mUseFrameTimes)
				{
					time = mFrameTimes[0];
				}
				math::Quaternion rotation;
				if (channels->rotation)
				{
					channels->rotation->GetDelta(*previousTime, time, &rotation);
				}
				else
				{
					rotation = skeleton->mData.mRotations[0];
				}
				rotation.Slerp(rotation, mPose->mData.mArrays.mRotations[0], alpha);
				mPose->mData.mArrays.mRotations[0] = rotation;
				if (channels->translation)
				{
					channels->translation->GetDelta(*previousTime, time, &vector);
				}
				else
				{
					math::Vector4* rest = skeleton->mData.mTranslations;
					vector.x = rest->x;
					vector.y = rest->y;
					vector.z = rest->z;
				}
				math::Matrix* local = mPose->mData.mLocalMatrices;
				vector.x = (local->m[3][0] - vector.x) * alpha + vector.x;
				vector.y = (local->m[3][1] - vector.y) * alpha + vector.y;
				vector.z = (local->m[3][2] - vector.z) * alpha + vector.z;
				math::Vector4* target = mPose->mData.mArrays.mTranslations;
				target->x = vector.x;
				target->y = vector.y;
				target->z = vector.z;
				*previousTime = time;
			}
		}
		for (; joint < jointCount; joint++)
		{
			if (mask->words[joint >> 5] & (1 << (joint & 0x1F)))
			{
				if (mUseFrameTimes)
				{
					time = mFrameTimes[joint];
				}
				JointChannels* jointChannels = &channels[joint];
				math::Quaternion rotation;
				QuaternionChannel* rotationChannel = jointChannels->rotation;
				if (rotationChannel)
				{
					rotationChannel->mKeys.Evaluate(FrameTime(time), &rotation);
				}
				else
				{
					rotation = skeleton->mData.mRotations[joint];
				}
				rotation.Slerp(rotation, mPose->mData.mArrays.mRotations[joint], alpha);
				mPose->mData.mArrays.mRotations[joint] = rotation;
				{
					VectorChannel* channel = jointChannels->translation;
					if (channel)
					{
						channel->mKeys.Evaluate(FrameTime(time), &vector);
					}
					else
					{
						math::Vector4* rest = &skeleton->mData.mTranslations[joint];
						vector.x = rest->x;
						vector.y = rest->y;
						vector.z = rest->z;
					}
					math::Matrix* local = &mPose->mData.mLocalMatrices[joint];
					vector.x = (local->m[3][0] - vector.x) * alpha + vector.x;
					vector.y = (local->m[3][1] - vector.y) * alpha + vector.y;
					vector.z = (local->m[3][2] - vector.z) * alpha + vector.z;
					math::Vector4* target = &mPose->mData.mArrays.mTranslations[joint];
					target->x = vector.x;
					target->y = vector.y;
					target->z = vector.z;
				}
				{
					VectorChannel* channel = jointChannels->unknown10;
					if (channel)
					{
						channel->mKeys.Evaluate(FrameTime(time), &vector);
					}
					else
					{
						math::Vector4* rest = &skeleton->mData.mUnknown10[joint];
						vector.x = rest->x;
						vector.y = rest->y;
						vector.z = rest->z;
					}
					math::Vector4* current = &mPose->mData.mArrays.mUnknown10[joint];
					vector.x = (current->x - vector.x) * alpha + vector.x;
					vector.y = (current->y - vector.y) * alpha + vector.y;
					vector.z = (current->z - vector.z) * alpha + vector.z;
					math::Vector4* target = &mPose->mData.mArrays.mUnknown10[joint];
					target->x = vector.x;
					target->y = vector.y;
					target->z = vector.z;
				}
				{
					VectorChannel* channel = jointChannels->scale;
					if (channel)
					{
						channel->mKeys.Evaluate(FrameTime(time), &vector);
					}
					else
					{
						math::Vector4* rest = &skeleton->mData.mScales[joint];
						vector.x = rest->x;
						vector.y = rest->y;
						vector.z = rest->z;
					}
					math::Vector4* current = &mPose->mData.mArrays.mScales[joint];
					vector.x = (current->x - vector.x) * alpha + vector.x;
					vector.y = (current->y - vector.y) * alpha + vector.y;
					vector.z = (current->z - vector.z) * alpha + vector.z;
					math::Vector4* target = &mPose->mData.mArrays.mScales[joint];
					target->x = vector.x;
					target->y = vector.y;
					target->z = vector.z;
				}
				{
					VectorChannel* channel = jointChannels->unknown14;
					if (channel)
					{
						channel->mKeys.Evaluate(FrameTime(time), &vector);
					}
					else
					{
						math::Vector4* rest = &skeleton->mData.mUnknown18[joint];
						vector.x = rest->x;
						vector.y = rest->y;
						vector.z = rest->z;
					}
					math::Vector4* current = &mPose->mData.mArrays.mUnknown14[joint];
					vector.x = (current->x - vector.x) * alpha + vector.x;
					vector.y = (current->y - vector.y) * alpha + vector.y;
					vector.z = (current->z - vector.z) * alpha + vector.z;
					math::Vector4* target = &mPose->mData.mArrays.mUnknown14[joint];
					target->x = vector.x;
					target->y = vector.y;
					target->z = vector.z;
				}
				{
					VectorChannel* channel = jointChannels->unknown1C;
					if (channel)
					{
						channel->mKeys.Evaluate(FrameTime(time), &vector);
					}
					else
					{
						math::Vector4* rest = &skeleton->mData.mUnknown1C[joint];
						vector.x = rest->x;
						vector.y = rest->y;
						vector.z = rest->z;
					}
					math::Vector4* current = &mPose->mData.mArrays.mUnknown1C[joint];
					vector.x = (current->x - vector.x) * alpha + vector.x;
					vector.y = (current->y - vector.y) * alpha + vector.y;
					vector.z = (current->z - vector.z) * alpha + vector.z;
					math::Vector4* target = &mPose->mData.mArrays.mUnknown1C[joint];
					target->x = vector.x;
					target->y = vector.y;
					target->z = vector.z;
				}
			}
		}
		mPose->mData.mFlags |= 3;
	}
}
