// pure3d::PoseAnimationController (unit around 0x10732100 - 0x10733300; file name guessed from the class). Names are
// guesses.
#include <new>

#include "code/engine/driving/carattributes.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/posecontroller.h"

namespace pure3d
{
	void AssignCoreRef(core::IRefCount*& pointer, core::IRefCount* object);

	// FUNCTION: ENGINE 0x10732120
	// NONMATCHING: the engine stores the vftable after the member stores (71.8 %)
#ifdef NONMATCHING
	PoseAnimationController::PoseAnimationController()
	{
		float one = engine::driving::gOne;
		mPose = 0;
		mJointCapacity = 0;
		mUseFrameTimes = false;
		mAnimatesRoot = false;
		mInfo = 0;
		mChannels[0] = 0;
		mFrameTimes[0] = 0;
		unknown114 = one;
	}
#endif

	// FUNCTION: ENGINE 0x107321B0
	Pose* PoseAnimationController::GetPose()
	{
		return mPose;
	}

	// FUNCTION: ENGINE 0x107330A0
	void PoseAnimationController::SetPose(Pose* pose)
	{
		if (pose != mPose)
		{
			if (mPose == 0 || mPose->mSkeleton != pose->mSkeleton)
			{
				mAnimationChanged = true;
			}
			AssignCoreRef((core::IRefCount*&)mPose, pose);
			if (mPose->mData.mArrays.mJointCount > mJointCapacity)
			{
				if (mChannels[0] != 0)
				{
					delete[] mChannels[0];
				}
				mJointCapacity = mPose->mData.mArrays.mJointCount;
				mChannels[0] = new JointChannels[mJointCapacity * 5];
				if (mFrameTimes[0] != 0)
				{
					delete[] mFrameTimes[0];
				}
				mFrameTimes[0] = new float[mJointCapacity * 5];
				for (int i = 1; i < 5; i++)
				{
					mChannels[i] = mChannels[i - 1] + mJointCapacity;
					mFrameTimes[i] = mFrameTimes[i - 1] + mJointCapacity;
				}
			}
			if (mInfo != 0)
			{
				Skeleton* skeleton = mPose->mSkeleton;
				mInfo = skeleton->FindPartition(mInfo->name);
			}
			if (mInfo == 0)
			{
				Skeleton* skeleton = mPose->mSkeleton;
				mInfo = skeleton->FindPartition(core::Name<core::CaseSensitiveKey>("root", 1));
			}
		}
	}

	// FUNCTION: ENGINE 0x10732D40
	void PoseAnimationController::UpdateFrameTimes()
	{
		if (mUseFrameTimes)
		{
			for (unsigned int i = 0; i < mCount; i++)
			{
				float frame = mEntries[i].GetFrame();
				for (unsigned int joint = 0; joint < mPose->mSkeleton->mData.mJointCount; joint++)
				{
					mFrameTimes[i][joint] = frame;
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x107343D0
	// NONMATCHING: the engine loads the constant before it stores the vftable (92.2 %)
#ifdef NONMATCHING
	PoseAnimationController::PoseAnimationController(const PoseAnimationController& other) : BlendFrameController(other)
	{
		float one = engine::driving::gOne;
		mPose = 0;
		unknown114 = one;
		mJointCapacity = 0;
		mAnimatesRoot = false;
		mInfo = 0;
		mChannels[0] = 0;
		mFrameTimes[0] = 0;
		if (const_cast<PoseAnimationController&>(other).GetPose() != 0)
		{
			SetPose(const_cast<PoseAnimationController&>(other).GetPose());
		}
		mUseFrameTimes = other.mUseFrameTimes;
		mInfo = other.mInfo;
	}
#endif

	// FUNCTION: ENGINE 0x10732170
	bool PoseAnimationController::Unknown29()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10732FD0
	void PoseAnimationController::SetAnimation(Animation* animation, float a, float b)
	{
		BlendFrameController::SetAnimation(animation, a, b);
		mAnimationChanged = true;
		UpdateFrameTimes();
		if (mAnimatesRoot)
		{
			for (unsigned int i = 0; i < mCount; i++)
			{
				mPreviousTimes[i] = a;
			}
		}
	}

	// FUNCTION: ENGINE 0x10733040
	void PoseAnimationController::Advance(float dt, bool update)
	{
		BlendFrameController::Advance(dt, false);
		UpdateFrameTimes();
		if (mUpdateOnAdvance == true || update == true)
		{
			BlendFrameController::Unknown5();
		}
	}

	// FUNCTION: ENGINE 0x10733080
	void PoseAnimationController::SetFrame(float frame)
	{
		BlendFrameController::SetFrame(frame);
		UpdateFrameTimes();
	}

	// FUNCTION: ENGINE 0x10734460
	PoseAnimationController* PoseAnimationController::Clone()
	{
		return new PoseAnimationController(*this);
	}

	// FUNCTION: ENGINE 0x10734490
	void PoseAnimationController::SetTarget(Entity* target)
	{
		Drawable* drawable = dynamic_cast<Drawable*>(target);
		if (drawable != 0)
		{
			SetPose(drawable->GetPose());
		}
		else
		{
			SetPose(dynamic_cast<Pose*>(target));
		}
	}

	// FUNCTION: ENGINE 0x10732180
	bool PoseAnimationController::IsSupported(Animation* animation)
	{
		if (animation != 0 && animation->mGroupCount > 0)
		{
			return animation->mType == 0x4E525450;
		}
		return false;
	}

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
		JointMask* mask = mInfo->joints;
		unsigned int joint = 0;
		math::Vector vector;
		if (mAnimatesRoot)
		{
			joint = 1;
			if (mask->words[0] & 1)
			{
				if (mUseFrameTimes)
				{
					time = mFrameTimes[0][0];
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
					time = mFrameTimes[0][joint];
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
