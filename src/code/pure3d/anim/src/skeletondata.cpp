// pure3d::SkeletonData (unit around 0x1072D570 - 0x1072D9A0; file name guessed from the struct): the arrays a skeleton
// keeps for its rest pose and its limbs. Names are guesses.
#include <new>

#include "code/core/heap.h"
#include "code/pure3d/posedata.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1072D590
	unsigned int SkeletonData::GetMemorySize()
	{
		return mLimbCount * 0x40 + mJointCount * 0x12F;
	}

	// FUNCTION: ENGINE 0x1072D5F0
	unsigned int SkeletonData::SetJointArrays(unsigned int memory)
	{
		unsigned int count = mJointCount;
		unsigned int at = count * 0x40 + memory;
		mUnknown3C = (int*)at;
		at += count * 4;
		mParents = (unsigned short*)at;
		at += count * 2;
		mInverseJoints = (math::Matrix*)memory;
		mUnknown40 = (signed char*)at;
		return at + count;
	}

	// FUNCTION: ENGINE 0x1072D6C0
	void SkeletonData::SetMemory(void* memory)
	{
		unsigned int jointBytes = mJointCount * 0x10;
		char* at = (char*)memory + jointBytes;
		mTranslations = (math::Vector4*)at;
		at += jointBytes;
		mUnknown10 = (math::Vector4*)at;
		at += jointBytes;
		mScales = (math::Vector4*)at;
		at += jointBytes;
		mUnknown18 = (math::Vector4*)at;
		at += jointBytes;
		mMemory = memory;
		mRotations = (math::Quaternion*)memory;
		unsigned int limbs = mLimbCount;
		mUnknown1C = (math::Vector4*)at;
		unsigned int i = 0;
		at += jointBytes;
		if (limbs > 0)
		{
			mLimbRotations = (math::Quaternion*)at;
			at += limbs * 0x10;
			mLimbTranslations = (math::Vector4*)at;
			at += limbs * 0x10;
			mLimbs = (SkeletonLimb*)at;
			at += limbs * 0x20;
			if (limbs > 0)
			{
				for (; i < mLimbCount; i++)
				{
					new (&mLimbs[i].name) core::Name<core::CaseSensitiveKey>;
				}
			}
		}
		else
		{
			mLimbRotations = 0;
			mLimbTranslations = 0;
			mLimbs = 0;
		}
		mFileMatrices = (math::Matrix*)at;
		at += mJointCount * 0x40;
		mJoints = (math::Matrix*)at;
		at += mJointCount * 0x40;
		mNames = (core::Name<core::CaseSensitiveKey>*)SetJointArrays((unsigned int)at);
	}

	// FUNCTION: ENGINE 0x1072D770
	SkeletonData::SkeletonData(unsigned int jointCount, unsigned int limbCount)
	{
		mJointCount = jointCount;
		mLimbCount = limbCount;
		unsigned int size = GetMemorySize();
		SetMemory(core::HeapAllocAligned(core::GetCurrentHeap(), size, 0x10));
	}

	// FUNCTION: ENGINE 0x1072D7D0
	unsigned int SkeletonData::FindJoint(const core::Name<core::CaseSensitiveKey>& name)
	{
		unsigned int count = mJointCount;
		unsigned int joint = 0;
		if (count > 0)
		{
			core::Name<core::CaseSensitiveKey>* at = mNames;
			do
			{
				if (*at == name)
				{
					return joint;
				}
				joint++;
				at++;
			} while (joint < count);
		}
		return 0xFFFF;
	}

	// FUNCTION: ENGINE 0x1072D930
	void SkeletonData::Free()
	{
		core::FreeAligned(mMemory);
	}
}
