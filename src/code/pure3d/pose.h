// pure3d::Pose (RTTI name; bases pure3d::LockableRefCounted, core::IRefCount): the joint transforms of a skeleton
// instance, 0x50 bytes (the skeleton at +0xC, the joint data from +0x10). pure3d::Skeleton is a content::LoadObject.
// Only what the engine's render units call; all of it is in other units (pure3d).
#ifndef PURE3D_POSE_H
#define PURE3D_POSE_H

#include "code/core/memory/imemoryallocator.h"
#include "code/core/name.h"
#include "code/pure3d/posedata.h"

namespace pure3d
{
	class Pose;

	// A named group of the joints of a skeleton (0x18 bytes): the joints it covers are the bits of its mask
	struct SkeletonPartition
	{
		unsigned char unknown0[8];
		core::Name<core::CaseSensitiveKey> mName;  // 0x08
		JointMask* mMask;                          // 0x10
		unsigned char unknown14[4];
	};

	class Skeleton
	{
	public:
		// Reference counting through the vftable (slots 0 and 1)
		virtual void AddRef();
		virtual void Release();
		// 0x106DDA70: a new pose of the skeleton
		Pose* CreatePose(int kind);
		// 0x106DDC80: the partition of that name (null when there is none; the empty names get a static empty one)
		SkeletonPartition* FindPartition(const core::Name<core::CaseSensitiveKey>& name);

		unsigned char unknown4[4];
		SkeletonData mData;
		unsigned char unknown4C[0xC];
		unsigned int mPartitionCount;              // 0x58
		SkeletonPartition* mPartitions;            // 0x5C
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
		// 0x106DD6E0: recomputes the joint matrices and counts the update
		void Update();

		Skeleton* mSkeleton;
		PoseData mData;
		unsigned int mUpdateCount;
	};

	// What a pose keeps past the data above, which this partial view does not lay out: the word the skinning code
	// stamps when it draws the pose (+0x138)
	struct PoseSkinView
	{
		unsigned char unknown0[0x138];
		int unknown138;
	};;
}

#endif
