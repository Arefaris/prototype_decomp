// pure3d::Pose (RTTI name; bases pure3d::LockableRefCounted, core::IRefCount): the joint transforms of a skeleton
// instance, 0x50 bytes (the skeleton at +0xC, the joint data from +0x10). pure3d::Skeleton is a content::LoadObject.
// Only what the engine's render units call; all of it is in other units (pure3d).
#ifndef PURE3D_POSE_H
#define PURE3D_POSE_H

#include "code/core/memory/imemoryallocator.h"

namespace pure3d
{
	class Pose;

	class Skeleton
	{
	public:
		// 0x106DDA70: a new pose of the skeleton
		Pose* CreatePose(int kind);

		unsigned char unknown0[0x38];
		// The bind pose's joint matrices (0x40 bytes each)
		void* mJoints;
	};

	class LockableRefCounted : public core::IRefCount
	{
	public:
		// 0x106E2A70 / 0x106E2A80
		virtual void AddRef();
		virtual void Release();

		int mLock;
		int mRefCount;
	};

	class Pose : public LockableRefCounted
	{
	public:
		// 0x106DD670
		Pose(Skeleton* skeleton, int a, int b, int c);
		// 0x106DD7C0: takes over the joint data of another pose
		void CopyStateFrom(Pose* other);
		// 0x106DD760, 0x106DD730
		void Unknown106DD760();
		void Unknown106DD730();
		// 0x106DD780
		void CopyFrom(Pose* other);
		// 0x106DD830: a new pose of the same skeleton with this one's joints
		Pose* CreateInstance(int kind);
		// 0x106DD6E0: recomputes the joints and counts the update
		void Update();

		Skeleton* mSkeleton;
		unsigned char unknown10[4];
		unsigned int mJointCount;
		unsigned char unknown18[0x1C];
		// The joint matrices (0x40 bytes each)
		void* mJoints;
		unsigned char unknown38[8];
		// Bit 1: the joints need Update
		unsigned char mFlags;
		unsigned char unknown41[0xF];
	};
}

#endif
