// pure3d::SkeletonData (unit around 0x1072D570 - 0x1072D9A0; file name guessed from the struct): the arrays a skeleton
// keeps for its rest pose and its limbs. Names are guesses.
#include <new>

#include "code/core/heap.h"
#include "code/engine/driving/carattributes.h"
#include "code/math/matrix.h"
#include "code/math/plane.h"
#include "code/engine/nis/nis.h"
#include "code/math/worldbounds.h"
#include "code/pure3d/posedata.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1072D590
	unsigned int SkeletonData::GetMemorySize()
	{
		return mLimbCount * 0x40 + mJointCount * 0x12F;
	}

	// FUNCTION: ENGINE 0x1072D620
	void SkeletonData::GetLimbInfo(SkeletonLimbInfo* out) const
	{
		out->mLimbCount = mLimbCount;
		out->mUnknown = (unsigned int)mMemory;
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

	// FUNCTION: ENGINE 0x1072D810
	// The matrix of a limb: its centre moved to the origin, scaled, sheared and moved back, then its offset (name guess)
	void BuildLimbMatrix(math::Matrix* matrix, const math::Vector* centre, const math::Vector* shear,
		const math::Vector* scale, const math::Vector* offset)
	{
		matrix->Identity();
		float origin = math::WORLD_MIN;
		matrix->m[3][0] = origin - centre->x;
		matrix->m[3][1] = origin - centre->y;
		matrix->m[3][2] = origin - centre->z;
		math::Matrix factor;
		factor.Identity();
		factor.m[0][0] = scale->x;
		factor.m[1][1] = scale->y;
		factor.m[2][2] = scale->z;
		matrix->Multiply(*matrix, factor);
		factor.Identity();
		factor.m[1][0] = shear->x;
		factor.m[2][0] = shear->y;
		factor.m[2][1] = shear->z;
		matrix->Multiply(*matrix, factor);
		factor.Identity();
		factor.m[3][0] = centre->x;
		factor.m[3][1] = centre->y;
		factor.m[3][2] = centre->z;
		matrix->Multiply(*matrix, factor);
		factor.m[3][0] = offset->x;
		factor.m[3][1] = offset->y;
		factor.m[3][2] = offset->z;
		matrix->Multiply(*matrix, factor);
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

	// FUNCTION: ENGINE 0x1072DB80
	// NONMATCHING: the engine keeps the joint index and both offsets in registers and spills the parent (50 %)
#ifdef NONMATCHING
	void SkeletonData::BuildBindPose()
	{
		math::Matrix product;
		math::Matrix limb;
		BuildLimbMatrix(&limb, mUnknown10, mUnknown18, mScales, mUnknown1C);
		limb.Invert();
		product.Multiply(mFileMatrices[0], limb);
		mRotations[0].FromMatrix(product);
		math::Vector4* translation = &mTranslations[0];
		translation->x = product.m[3][0];
		translation->y = product.m[3][1];
		translation->z = product.m[3][2];
		*(engine::NISTransform*)&mJoints[0] = *(const engine::NISTransform*)&mFileMatrices[0];
		math::Matrix* inverse = mInverseJoints;
		*(engine::NISTransform*)inverse = *(const engine::NISTransform*)&mFileMatrices[0];
		inverse->Invert();
		for (unsigned int joint = 1; joint < mJointCount; joint++)
		{
			BuildLimbMatrix(&limb, &mUnknown10[joint], &mUnknown18[joint], &mScales[joint], &mUnknown1C[joint]);
			limb.Invert();
			product.Multiply(mFileMatrices[joint], limb);
			mRotations[joint].FromMatrix(product);
			translation = &mTranslations[joint];
			translation->x = product.m[3][0];
			translation->y = product.m[3][1];
			translation->z = product.m[3][2];
			unsigned int parent = mParents[joint];
			mJoints[joint].Multiply(mFileMatrices[joint], mJoints[parent]);
			mInverseJoints[joint] = mJoints[joint];
			mInverseJoints[joint].Invert();
		}
		if (mLimbCount != 0)
		{
			BuildLimbRotations();
		}
	}
#endif

	// FUNCTION: ENGINE 0x1072D940
	// NONMATCHING: the engine takes the base of the joint matrices in ecx and the index in eax (49 %)
#ifdef NONMATCHING
	void SkeletonData::BuildLimbRotations()
	{
		math::Matrix rotation = math::Matrix::IDENTITY;
		math::Quaternion* quaternion = mLimbRotations;
		math::Vector4* translation = mLimbTranslations;
		for (unsigned int limb = 0; limb < mLimbCount; limb++)
		{
			SkeletonLimb* current = &mLimbs[limb];
			math::Vector third(mJoints[current->joints[2]].m[3][0], mJoints[current->joints[2]].m[3][1],
				mJoints[current->joints[2]].m[3][2]);
			math::Vector second(mJoints[current->joints[1]].m[3][0], mJoints[current->joints[1]].m[3][1],
				mJoints[current->joints[1]].m[3][2]);
			math::Vector first(mJoints[current->joints[0]].m[3][0], mJoints[current->joints[0]].m[3][1],
				mJoints[current->joints[0]].m[3][2]);
			math::Plane plane;
			plane.Set(first, second, third);
			math::Vector up(0.0f, 0.0f, engine::driving::gOne);
			rotation.RotationFromTo(up, plane.normal);
			quaternion->FromMatrix(rotation);
			translation->x = mJoints[current->joints[2]].m[3][0];
			translation->y = mJoints[current->joints[2]].m[3][1];
			translation->z = mJoints[current->joints[2]].m[3][2];
			quaternion++;
			translation++;
		}
	}
#endif
}
