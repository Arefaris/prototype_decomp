// pure3d::PoseData (code/pure3d/anim/src/posedata.cpp, path from the asserts): the joint data of a Pose, its 0x3C
// bytes embedded in the Pose after the skeleton pointer. Per joint it holds the local rotation / translation / scale
// and further transform arrays (16 bytes per joint each), and the joint matrices built from them. Names are
// guesses; the asserts of the constructor name mJointCount and mSpaces.
#ifndef PURE3D_POSEDATA_H
#define PURE3D_POSEDATA_H

#include "code/math/matrix.h"
#include "code/math/quaternion.h"
#include "code/math/vector4.h"

namespace pure3d
{
	// The skeleton's part that the poses read: the Skeleton's own members from +8. The rest pose of every joint is
	// kept in arrays like the pose's own (16 bytes per joint), the same kinds in a different order
	struct SkeletonData
	{
		unsigned int mJointCount;
		unsigned char unknown4[4];
		math::Quaternion* mRotations;
		math::Vector4* mTranslations;
		math::Vector4* mUnknown10;
		math::Vector4* mScales;
		math::Vector4* mUnknown18;
		math::Vector4* mUnknown1C;
		unsigned char unknown20[0x10];
		// The bind pose's joint matrices
		math::Matrix* mJoints;
		// The inverses of the bind pose matrices
		math::Matrix* mInverseJoints;
		// The parent joint of each joint
		unsigned short* mParents;
		// Per joint: zero for the plain rotation / translation / scale form
		int* mUnknown3C;
		// Per joint: nonzero when the scale of the parent is divided out
		signed char* mUnknown40;
	};

	class PoseData
	{
	public:
		// 0x107098A0: builds the local and then the joint matrices
		void Update();
		// 0x10708E00: the local matrices from the joint transforms (flag 1), leaves flag 2 for UpdateWorld
		void UpdateLocal();
		// 0x10708330: the joint matrices (parents applied) and the skinning matrices (inverse bind pose applied)
		void UpdateWorld();

		SkeletonData* mSkeleton;
		unsigned int mJointCount;
		math::Quaternion* mRotations;
		math::Vector4* mTranslations;
		math::Vector4* mUnknown10;
		math::Vector4* mUnknown14;
		math::Vector4* mScales;
		math::Vector4* mUnknown1C;
		math::Matrix* mLocalMatrices;
		math::Matrix* mWorldMatrices;
		math::Matrix* mSkinMatrices;
		// 3 when the local, joint and skinning matrices exist
		int mSpaces;
		// Bit 0: local matrices out of date, bit 1: joint matrices out of date, bit 2: the further transform arrays
		// are in use
		unsigned char mFlags;
		unsigned char unknown31[3];
		void* mUnknown34;
		void* mUnknown38;
	};
}

#endif
