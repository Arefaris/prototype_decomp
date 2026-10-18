// pure3d::Pose (RTTI name; bases pure3d::LockableRefCounted, core::IRefCount): the joint transforms of a skeleton
// instance, 0x50 bytes (the skeleton at +0xC, the joint data from +0x10). pure3d::Skeleton is a content::LoadObject.
// Only what the engine's render units call; all of it is in other units (pure3d).
#ifndef PURE3D_POSE_H
#define PURE3D_POSE_H

#include "code/content/loadinventory.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/pure3d/posedata.h"

namespace pure3d
{
	class Pose;

	// (RTTI: bases content::LoadObject, core::IRefCount; 5 vftable slots)
	class Skeleton : public content::LoadObject
	{
	public:
		// 0x106DDA70: a new pose of the skeleton
		Pose* CreatePose(int kind);

		SkeletonData mData;
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
