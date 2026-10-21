// pure3d::Pose (RTTI name; bases pure3d::LockableRefCounted, core::IRefCount): the joint transforms of a skeleton
// instance, 0x50 bytes (the skeleton at +0xC, the joint data from +0x10). pure3d::Skeleton is a content::LoadObject.
// Only what the engine's render units call; all of it is in other units (pure3d).
#ifndef PURE3D_POSE_H
#define PURE3D_POSE_H

#include "code/content/loadinventory.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/name.h"
#include "code/pure3d/posedata.h"

namespace pure3d
{
	class Pose;

	class Skeleton;

	// The names a skeleton keeps for debugging when the engine is told to (0x18 bytes, name guessed)
	struct SkeletonDebugInfo
	{
		// 0x106DD980
		explicit SkeletonDebugInfo(Skeleton* owner);

		Skeleton* skeleton;
		char* name;
		char** jointNames;
		unsigned int partitionCount;
		char** partitionNames;
		char** limbNames;
	};

	// (RTTI: bases content::LoadObject, core::IRefCount; 5 vftable slots; 0x60 bytes)
	class Skeleton : public content::LoadObject
	{
	public:
		// RTTI pure3d::Skeleton::Partition (1 vftable slot, 0x18 bytes): a named set of joints
		class Partition
		{
		public:
			virtual ~Partition();

			unsigned char unknown4[4];
			core::Name<core::CaseSensitiveKey> name;
			JointMask* joints;
			unsigned char unknown14[4];
		};

		// 0x106DDF20: a skeleton of that many joints, partitions and limbs (the arrays are allocated, the partitions'
		// joint masks cleared)
		Skeleton(unsigned int jointCount, unsigned int partitionCount, unsigned int limbCount);
		virtual ~Skeleton();

		// 0x106DDAA0: builds the bind pose from what a file gave
		void Finish();
		// 0x106DDA70: a new pose of the skeleton
		Pose* CreatePose(int kind);
		// 0x106DDAB0: the matrix of a joint of the rest pose (identity with its rotation and translation)
		void GetRestMatrix(unsigned int joint, math::Matrix* out);
		// 0x106DDC80: the partition of that name (null when there is none; the empty names get a static empty one)
		Partition* FindPartition(const core::Name<core::CaseSensitiveKey>& name);
		// 0x106DDA60: the index of the joint of that name (looked up in the joint data)
		int FindJoint(const core::Name<core::CaseSensitiveKey>& name) const;

		SkeletonData mData;
		unsigned char unknown50[4];
		SkeletonDebugInfo* debugInfo;
		unsigned int partitionCount;
		Partition* partitions;
	};

	class LockableRefCounted : public core::IRefCount
	{
	public:
		// 0x106E2A70 / 0x106E2A80
		virtual void AddRef();
		virtual void Release();
		// 0x106E2A30: takes a reference and a lock (the skinning job holds its pose this way while it runs)
		void Lock();

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
		// 0x10070FC0: stores the rotation of a joint
		void SetJointRotation(int joint, const math::Quaternion* rotation);

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
