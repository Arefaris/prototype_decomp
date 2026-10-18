// The pose blend job (code/choreo/src/poseblendjob.cpp, path from the asserts; the unit runs from about 0x10957600 to
// 0x10959200). Names are guesses.
#include "code/choreo/poseblendjob.h"
#include "code/choreo/puppet.h"
#include "code/choreo/samplechannels.h"
#include "code/core/criticalsection.h"
#include "code/core/debug.h"
#include "code/core/report.h"
#include "code/ravenphysics/common/stackallocator.h"
#include "code/math/worldbounds.h"
#include <math.h>

namespace choreo
{
	// The file and the system name the unit's reports carry
	#define POSEBLENDJOB_FILE "..\\..\\..\\code\\choreo\\src\\poseblendjob.cpp"
	#define POSEBLENDJOB_SYSTEM "Choreo  Pre "

	// FUNCTION: ENGINE 0x10957690
	static void ReportBadJobVector(const math::Vector& value)
	{
		static bool sReportValues = true;
		static bool sReportHeader = true;
		if (sReportHeader)
		{
			if (core::Report(0, POSEBLENDJOB_SYSTEM, POSEBLENDJOB_FILE, 0x22, 0, "Bad vector: ", 0) == 3)
			{
				sReportHeader = false;
			}
		}
		if (sReportValues)
		{
			if (core::Report(0, POSEBLENDJOB_SYSTEM, POSEBLENDJOB_FILE, 0x23, 0, "[ %f | %f | %f ]", value.x, value.y,
				value.z, 0) == 3)
			{
				sReportValues = false;
			}
		}
	}

	// FUNCTION: ENGINE 0x10957710
	static void ReportBadJobQuaternion(const math::Quaternion& value)
	{
		static bool sReportValues = true;
		static bool sReportHeader = true;
		if (sReportHeader)
		{
			if (core::Report(0, POSEBLENDJOB_SYSTEM, POSEBLENDJOB_FILE, 0x27, 0, "Bad quaternion: ", 0) == 3)
			{
				sReportHeader = false;
			}
		}
		if (sReportValues)
		{
			if (core::Report(0, POSEBLENDJOB_SYSTEM, POSEBLENDJOB_FILE, 0x28, 0, "[ %f | %f | %f | %f ]", value.x,
				value.y, value.z, value.w, 0) == 3)
			{
				sReportValues = false;
			}
		}
	}

	// What the asserts on a delta of the root say
	#define POSEBLENDJOB_BAD_DELTA "Invalid root delta obtained from animation. Please obtain the Crash Handler report (or if you are not at Radical, please note down the callstack and output log) and continue - the assert occurring soon after this should provide more info."

	// The largest magnitude any number of a delta may have
	static const float POSEBLENDJOB_LIMIT = 1e12f;

	// FUNCTION: ENGINE 0x10958640
	static bool ValidateDeltaInputJob(const math::Quaternion& value, float frame, float previousFrame, float rootWeight)
	{
		if (POSEBLENDJOB_LIMIT > fabsf(value.x) && POSEBLENDJOB_LIMIT > fabsf(value.y)
			&& POSEBLENDJOB_LIMIT > fabsf(value.z) && POSEBLENDJOB_LIMIT > fabsf(value.w))
		{
			return true;
		}
		ReportBadJobQuaternion(value);
		static bool sReport = true;
		if (sReport)
		{
			if (core::Report(0, POSEBLENDJOB_SYSTEM, POSEBLENDJOB_FILE, 0x32, 0,
				"frame=%f, prevFrame=%f, rootWeight=%f", frame, previousFrame, rootWeight, 0) == 3)
			{
				sReport = false;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x109586E0
	static bool ValidateDeltaInputJob(const math::Vector& value, float frame, float previousFrame, float rootWeight)
	{
		if (POSEBLENDJOB_LIMIT > fabsf(value.x) && POSEBLENDJOB_LIMIT > fabsf(value.y)
			&& POSEBLENDJOB_LIMIT > fabsf(value.z))
		{
			return true;
		}
		ReportBadJobVector(value);
		static bool sReport = true;
		if (sReport)
		{
			if (core::Report(0, POSEBLENDJOB_SYSTEM, POSEBLENDJOB_FILE, 0x32, 0,
				"frame=%f, prevFrame=%f, rootWeight=%f", frame, previousFrame, rootWeight, 0) == 3)
			{
				sReport = false;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x109577A0
	void PoseBlendSample::Set(float scale, float bias, float frame, float previousFrame, bool forward)
	{
		mScale = scale;
		mBias = bias;
		mFrame.SetTime(frame);
		mPreviousFrame.SetTime(previousFrame);
		mForward = forward;
	}

	// FUNCTION: ENGINE 0x109577F0
	int PoseBlendSample::GetRootRotation(math::Quaternion* out)
	{
		return mChannels->GetRootRotation(mPreviousFrame, mFrame, mForward, out);
	}

	// FUNCTION: ENGINE 0x10957820
	bool PoseBlendSample::GetRootTranslation(math::Vector* out)
	{
		return mChannels->GetRootTranslation(mPreviousFrame, mFrame, mForward, out);
	}

	// FUNCTION: ENGINE 0x10957850
	bool PoseBlendSample::GetRootScale(math::Vector* out)
	{
		return mChannels->GetRootScale(mFrame, out);
	}

	// How far the channels move the pose at elapsed time t: nothing while scale * t is not positive, else the scale over
	// the reciprocal of t (at most 1) with the bias added
	static inline float BlendWeight(float scale, float t, float bias)
	{
		float limited = t < 1.0f ? t : 1.0f;
		float weight;
		if (math::WORLD_MIN - scale * t >= 0.0f)
		{
			weight = 0.0f;
		}
		else
		{
			weight = scale / ((1.0f / limited - 1.0f) + bias);
		}
		return weight;
	}

	// FUNCTION: ENGINE 0x109582E0
	void PoseBlendSample::BlendValue(float* value, float t)
	{
		mChannels->BlendValue(mFrame, value, BlendWeight(mScale, t, mBias));
	}

	// FUNCTION: ENGINE 0x10958360
	void PoseBlendSample::BlendJoints(pure3d::JointArrays* arrays, unsigned int first, unsigned int last,
		const pure3d::JointMask* mask, const pure3d::SkeletonData* rest, bool full, float t)
	{
		mChannels->Blend(arrays, first, last, mask, rest, mFrame, full, BlendWeight(mScale, t, mBias));
	}

	// FUNCTION: ENGINE 0x10958400
	void PoseBlendSample::BlendMatrices(math::Matrix* matrices, const pure3d::JointMask* mask,
		const pure3d::SkeletonData* skeleton, float t)
	{
		mChannels->BlendMatrices(matrices, mask, skeleton, mFrame, BlendWeight(mScale, t, mBias));
	}

	// The value a fraction of the way from one number to another
	static inline float Interpolate(float from, float to, float fraction)
	{
		return to * fraction + from * (1.0f - fraction);
	}

	// FUNCTION: ENGINE 0x10958770
	// EQUIVALENT: the same operations in the same order; the engine multiplies the scales' y and z by the remainder before
	// x and allocates the scale block's registers differently, 94 %
	void PoseBlendSample::BlendRoot(math::Matrix* root, pure3d::JointArrays* arrays, bool rotation, bool translation,
		bool scale, float weight, float scaleWeight)
	{
		weight = BlendWeight(mScale, weight, mBias);
		scaleWeight = BlendWeight(mScale, scaleWeight, mBias);
		if (rotation)
		{
			math::Quaternion delta;
			GetRootRotation(&delta);
			OLD_ASSERT_AT(POSEBLENDJOB_FILE, 0x9C, ValidateDeltaInputJob(delta, mFrame.GetFloat(), mPreviousFrame.GetFloat(), weight),
				"ValidateDeltaInputJob( qDelta, mFrame.GetFloat(), mPreviousFrame.GetFloat(), rootWeight )",
				POSEBLENDJOB_BAD_DELTA);
			math::Quaternion current;
			current.FromMatrix(*root);
			current.Slerp(current, delta, weight);
			root->FromQuaternion(current);
		}
		if (translation)
		{
			math::Vector delta;
			GetRootTranslation(&delta);
			OLD_ASSERT_AT(POSEBLENDJOB_FILE, 0xAA, ValidateDeltaInputJob(delta, mFrame.GetFloat(), mPreviousFrame.GetFloat(), weight),
				"ValidateDeltaInputJob( newDeltaV, mFrame.GetFloat(), mPreviousFrame.GetFloat(), rootWeight )",
				POSEBLENDJOB_BAD_DELTA);
			const math::Vector& step = delta;
			math::Vector current(root->m[3][0], root->m[3][1], root->m[3][2]);
			float rest = 1.0f - weight;
			math::Vector scaled(current.x * rest, current.y * rest, current.z * rest);
			math::Vector position(step.x * weight + scaled.x, step.y * weight + scaled.y, step.z * weight + scaled.z);
			root->SetTranslation(position);
		}
		if (scale)
		{
			math::Vector delta(1.0f, 1.0f, 1.0f);
			if (GetRootScale(&delta))
			{
				const math::Vector& step = delta;
				math::Vector4* scales = arrays->mScales;
				math::Vector current(scales->x, scales->y, scales->z);
				float rest = 1.0f - scaleWeight;
				math::Vector scaled(current.x * rest, current.y * rest, current.z * rest);
				math::Vector result(step.x * scaleWeight + scaled.x, step.y * scaleWeight + scaled.y,
					step.z * scaleWeight + scaled.z);
				scales->x = result.x;
				scales->y = result.y;
				scales->z = result.z;
			}
		}
	}

	// FUNCTION: ENGINE 0x10957870
	void PoseBlendNode::SetWeights(float a, float b, float c, float d)
	{
		mWeights[0] = a;
		mWeights[1] = b;
		mWeights[2] = c;
		mWeights[3] = d;
	}

	// FUNCTION: ENGINE 0x109578A0
	void PoseBlendNode::SetRootParts(unsigned int parts)
	{
		mRootParts = parts;
	}

	// FUNCTION: ENGINE 0x109578B0
	void PoseBlendNode::SetNone(bool rotation, bool translation)
	{
		mMode = 4;
		if (rotation)
		{
			mRotationState = 2;
		}
		if (translation)
		{
			mTranslationState = 2;
		}
		mFull = false;
	}

	// FUNCTION: ENGINE 0x109578E0
	void PoseBlendNode::Set(PoseBlendSample* sample, void* arrays, bool rotation, bool translation, bool full)
	{
		mMode = 0;
		mSource.sampled.sample = sample;
		mSource.sampled.arrays = (pure3d::JointArrays*)arrays;
		if (rotation)
		{
			mRotationState = 0;
		}
		if (translation)
		{
			mTranslationState = 0;
		}
		mFull = full;
	}

	// FUNCTION: ENGINE 0x10957920
	void PoseBlendNode::SetJoint(unsigned int joint, const math::Quaternion& rotation, const math::Vector& translation)
	{
		mFirstJoint = joint;
		mLastJoint = joint;
		mMask.jointCount = 0;
		mMode = 1;
		mRotation = rotation;
		mTranslation.x = translation.x;
		mTranslation.y = translation.y;
		mTranslation.z = translation.z;
	}

	// FUNCTION: ENGINE 0x10957970
	void PoseBlendNode::SetPose(pure3d::PoseData* pose, unsigned int channels)
	{
		mMode = 2;
		pose->GetLayout(&mSource.pose);
		mChannels = channels;
	}

	// FUNCTION: ENGINE 0x10957990
	void PoseBlendNode::SetMode3()
	{
		mMode = 3;
	}

	// FUNCTION: ENGINE 0x109579A0
	void PoseBlendNode::SetNoRotation()
	{
		mRotationState = 2;
	}

	// FUNCTION: ENGINE 0x109579B0
	void PoseBlendNode::SetRotation(const math::Quaternion& rotation)
	{
		mRotationState = 1;
		mRotation = rotation;
	}

	// FUNCTION: ENGINE 0x109579E0
	void PoseBlendNode::SetNoTranslation()
	{
		mTranslationState = 2;
	}

	// FUNCTION: ENGINE 0x109579F0
	void PoseBlendNode::SetTranslation(const math::Vector& translation)
	{
		mTranslationState = 1;
		mTranslation.x = translation.x;
		mTranslation.y = translation.y;
		mTranslation.z = translation.z;
	}

	// FUNCTION: ENGINE 0x10957A10
	void PoseBlendNode::SetNoRoot()
	{
		mRotationState = 2;
		mTranslationState = 2;
		mFull = false;
	}

	// FUNCTION: ENGINE 0x10957A20
	void PoseBlendNode::SetEmpty()
	{
		mMode = 4;
		mRotationState = 2;
		mTranslationState = 2;
		mFull = false;
	}

	// Moves a vector of the arrays a fraction of the way to a source value
	static inline void BlendVector(math::Vector4* array, unsigned int joint, const math::Vector& source, float weight)
	{
		math::Vector current(array[joint].x, array[joint].y, array[joint].z);
		math::Vector result((source.x - current.x) * weight + current.x, (source.y - current.y) * weight + current.y,
			(source.z - current.z) * weight + current.z);
		array[joint].x = result.x;
		array[joint].y = result.y;
		array[joint].z = result.z;
	}

	static inline void BlendVectorFrom(math::Vector4* array, unsigned int joint, const math::Vector& from, float weight)
	{
		math::Vector current(array[joint].x, array[joint].y, array[joint].z);
		math::Vector difference;
		difference.Sub(from, current);
		difference.Scale(weight);
		math::Vector result;
		result.Add(difference, current);
		math::Vector4* element = &array[joint];
		element->x = result.x;
		element->y = result.y;
		element->z = result.z;
	}

	// Whether the joint is one of the node's (all joints are when it has no mask)
	static inline bool InMask(const PoseJointMask& mask, unsigned int joint)
	{
		return mask.jointCount <= 0 || (mask.words[joint >> 5] & (1 << (joint & 0x1F))) != 0;
	}

	// FUNCTION: ENGINE 0x10957A40
	// EQUIVALENT: the same loads, operations and stores; the engine keeps the array's base in esi and the scaled joint
	// index in eax, ours the other way round, 98.6 %
	void PoseBlendNode::BlendRootJoint(pure3d::JointArrays* arrays, unsigned int joint)
	{
		if (mRootParts & 1)
		{
			BlendVector(arrays->mTranslations, joint, mTranslation, mWeights[0]);
		}
		if (mRootParts & 2)
		{
			math::Quaternion rotation = arrays->mRotations[joint];
			rotation.Slerp(rotation, mRotation, mWeights[0]);
			arrays->mRotations[joint] = rotation;
		}
	}

	// FUNCTION: ENGINE 0x10957B20
	// EQUIVALENT: the same loads, operations and stores in the same order; the engine addresses the stores of each
	// vector array through one element pointer (lea) and keeps the arrays' bases in other registers, 43.7 %
	void PoseBlendNode::BlendJoints(pure3d::JointArrays* arrays)
	{
		pure3d::JointArrays source;
		source.Set(&mSource.pose);
		float weight = mWeights[0];
		for (unsigned int joint = mFirstJoint; joint <= mLastJoint; joint++)
		{
			if (InMask(mMask, joint))
			{
				if (mChannels & 2)
				{
					math::Quaternion from = source.mRotations[joint];
					math::Quaternion rotation = arrays->mRotations[joint];
					rotation.Slerp(rotation, from, weight);
					arrays->mRotations[joint] = rotation;
				}
				if (mChannels & 4)
				{
					BlendVectorFrom(arrays->mTranslations, joint, math::Vector(source.mTranslations[joint].x, source.mTranslations[joint].y, source.mTranslations[joint].z), weight);
				}
				if (mChannels & 8)
				{
					BlendVectorFrom(arrays->mUnknown10, joint, math::Vector(source.mUnknown10[joint].x, source.mUnknown10[joint].y, source.mUnknown10[joint].z), weight);
				}
				if (mChannels & 0x10)
				{
					BlendVectorFrom(arrays->mScales, joint, math::Vector(source.mScales[joint].x, source.mScales[joint].y, source.mScales[joint].z), weight);
				}
				if (mChannels & 0x20)
				{
					BlendVectorFrom(arrays->mUnknown14, joint, math::Vector(source.mUnknown14[joint].x, source.mUnknown14[joint].y, source.mUnknown14[joint].z), weight);
				}
				if (mChannels & 0x40)
				{
					BlendVectorFrom(arrays->mUnknown1C, joint, math::Vector(source.mUnknown1C[joint].x, source.mUnknown1C[joint].y, source.mUnknown1C[joint].z), weight);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10957E10
	// EQUIVALENT: the same loads, operations and stores; the engine reloads the pose after the rotation's stores and
	// forms the translation pointer with add, ours with lea and other registers, 72 %
	void PoseBlendNode::BlendPose(pure3d::JointArrays* arrays, pure3d::PoseData* pose)
	{
		unsigned int last = mLastJoint;
		for (unsigned int joint = mFirstJoint; joint <= last; joint++)
		{
			if (InMask(mMask, joint))
			{
				math::Quaternion rotation = arrays->mRotations[joint];
				math::Quaternion target = pose->mArrays.mRotations[joint];
				rotation.Slerp(rotation, target, mWeights[0]);
				arrays->mRotations[joint] = rotation;
				math::Vector current(arrays->mTranslations[joint].x, arrays->mTranslations[joint].y,
					arrays->mTranslations[joint].z);
				math::Vector from(pose->mArrays.mTranslations[joint].x, pose->mArrays.mTranslations[joint].y,
					pose->mArrays.mTranslations[joint].z);
				math::Vector difference;
				difference.Sub(from, current);
				difference.Scale(mWeights[0]);
				math::Vector result;
				result.Add(difference, current);
				math::Vector4* element = &arrays->mTranslations[joint];
				element->x = result.x;
				element->y = result.y;
				element->z = result.z;
			}
		}
	}

	// FUNCTION: ENGINE 0x10957F60
	void PoseBlendRootTask::SetWeights(float first, float second)
	{
		mFirst = first;
		mSecond = second;
	}

	// FUNCTION: ENGINE 0x10957F80
	void PoseBlendRootTask::SetDriver(StrafeAdjustRootDriver* driver)
	{
		mKind = 0;
		mDriver = driver;
	}

	// FUNCTION: ENGINE 0x10957F90
	void PoseBlendRootTask::Apply(Puppet* puppet, pure3d::PoseData* pose)
	{
		mDriver->Unknown109571C0(puppet, pose, mFirst, mSecond);
	}

	// FUNCTION: ENGINE 0x10957FC0
	void PoseBlendRootRange::Apply()
	{
		for (PoseBlendRootTask* task = mBegin; task < mEnd; task++)
		{
			task->Apply(mPuppet, mPose);
		}
	}

	// FUNCTION: ENGINE 0x10957FF0
	void PoseBlendLimbTask::SetWeights(float first, float second)
	{
		mFirst = first;
		mSecond = second;
	}

	// FUNCTION: ENGINE 0x10958010
	void PoseBlendLimbTask::SetIK(IKDriver* driver)
	{
		mKind = 0;
		mDriver = driver;
	}

	// FUNCTION: ENGINE 0x10958020
	void PoseBlendLimbTask::SetJointLock(JointLockDriver* driver)
	{
		mKind = 1;
		mDriver = driver;
	}

	// FUNCTION: ENGINE 0x10958030
	void PoseBlendLimbTask::Apply(Puppet* puppet, pure3d::PoseData* pose)
	{
		switch (mKind)
		{
		case 0:
			((IKDriver*)mDriver)->Unknown1094A2D0(puppet, pose, mFirst, mSecond);
			break;
		case 1:
			((JointLockDriver*)mDriver)->Unknown10955E70(puppet, pose, mFirst, mSecond);
			break;
		}
	}

	// FUNCTION: ENGINE 0x10958090
	void PoseBlendLimbRange::Apply()
	{
		for (PoseBlendLimbTask* task = mBegin; task < mEnd; task++)
		{
			task->Apply(mPuppet, mPose);
		}
	}

	// FUNCTION: ENGINE 0x109581F0
	bool PoseBlendBuffers::HasRootNodes()
	{
		return 0 < mRootNodeCount;
	}

	// FUNCTION: ENGINE 0x10958200
	bool PoseBlendBuffers::HasRootTasks()
	{
		return 0 < mRootRangeCount;
	}

	// FUNCTION: ENGINE 0x10958220
	void PoseBlendBuffers::Apply10958220()
	{
		PoseBlendRootRange* range = (PoseBlendRootRange*)mBlock[2];
		for (unsigned int i = 0; i < mRootRangeCount; i++)
		{
			range->Apply();
			range++;
		}
	}

	// FUNCTION: ENGINE 0x10958250
	// NONMATCHING: compiling it makes the compiler see that RunPoseBlendJob's buffers never escape and turn its last call into a tail call (RunPoseBlendJob drops to 92.9%)
#ifdef NONMATCHING
	void PoseBlendBuffers::Apply10958250()
	{
		PoseBlendLimbRange* range = (PoseBlendLimbRange*)mBlock[4];
		for (unsigned int i = 0; i < mLimbRangeCount; i++)
		{
			range->Apply();
			range++;
		}
	}
#endif

	// FUNCTION: ENGINE 0x10958490
	void PoseBlendBuffers::Count(Puppet** begin, Puppet** end)
	{
		ravenphysics::ScratchStack stack;
		mPuppetCount = end - begin;
		mCounts = (PuppetCounts*)stack.Alloc(mPuppetCount * sizeof(PuppetCounts), 0x10);
		mRootNodeCount = 0;
		mNodeCount = 0;
		mSampleCount = 0;
		mRootRangeCount = 0;
		mRootTaskCount = 0;
		mLimbRangeCount = 0;
		mLimbTaskCount = 0;
		PuppetCounts* counts = mCounts;
		for (Puppet** puppet = begin; puppet < end; puppet++)
		{
			(*puppet)->CountNodes(counts);
			mRootNodeCount += 0 < counts->count[0];
			mNodeCount += counts->count[0];
			mSampleCount += counts->count[1];
			mRootRangeCount += 0 < counts->count[2];
			mRootTaskCount += counts->count[2];
			mLimbRangeCount += 0 < counts->count[3];
			mLimbTaskCount += counts->count[3];
			counts++;
		}
		mRootNodes = 0;
		mBlock[0] = 0;
		mBlock[1] = 0;
		mBlock[2] = 0;
		mBlock[3] = 0;
		mBlock[4] = 0;
		mBlock[5] = 0;
		unsigned int total = (mRootNodeCount * 3 + mSampleCount * 2 + mNodeCount * 7 + mLimbTaskCount + mRootTaskCount
			+ mRootRangeCount + mLimbRangeCount) * 0x10;
		unsigned char* memory = (unsigned char*)stack.Alloc(total, 0x10);
		if (0 < mRootNodeCount)
		{
			mRootNodes = (BlendRootNode*)memory;
			memory += mRootNodeCount * 0x30;
			if (0 < mNodeCount)
			{
				mBlock[0] = memory;
				memory += mNodeCount * 0x70;
				if (0 < mSampleCount)
				{
					mBlock[1] = memory;
					memory += mSampleCount * 0x20;
				}
			}
		}
		if (0 < mRootRangeCount)
		{
			mBlock[2] = memory;
			memory += mRootRangeCount * 0x10;
			if (0 < mRootTaskCount)
			{
				mBlock[3] = memory;
				memory += mRootTaskCount * 0x10;
			}
		}
		if (0 < mLimbRangeCount)
		{
			mBlock[4] = memory;
			if (0 < mLimbTaskCount)
			{
				mBlock[5] = memory + mLimbRangeCount * 0x10;
			}
		}
	}

	// FUNCTION: ENGINE 0x109585F0
	void PoseJointMask::Assign(const pure3d::JointMask* mask)
	{
		unsigned int copyWords = (mask->jointCount + 0x1F) >> 5;
		jointCount = mask->jointCount;
		unsigned int clearWords = (jointCount + 0x1F) >> 5;
		for (unsigned int i = 0; i < clearWords; i++)
		{
			words[i] = 0;
		}
		for (unsigned int i = 0; i < copyWords; i++)
		{
			words[i] = mask->words[i];
		}
	}

	// FUNCTION: ENGINE 0x109580C0
	PoseBlendCursors::PoseBlendCursors()
	{
		cursor[0] = 0;
		cursor[1] = 0;
		cursor[2] = 0;
		cursor[3] = 0;
		cursor[4] = 0;
		cursor[5] = 0;
		cursor[6] = 0;
	}

	// FUNCTION: ENGINE 0x109580E0
	PoseBlendBuffers::PoseBlendBuffers()
	{
		mRootNodes = 0;
		mBlock[0] = 0;
		mBlock[1] = 0;
		mBlock[2] = 0;
		mBlock[3] = 0;
		mBlock[4] = 0;
		mBlock[5] = 0;
		mPuppetCount = 0;
		mRootNodeCount = 0;
		mNodeCount = 0;
		mSampleCount = 0;
		mRootRangeCount = 0;
		mRootTaskCount = 0;
		mLimbRangeCount = 0;
		mLimbTaskCount = 0;
	}

	// FUNCTION: ENGINE 0x10958210
	bool PoseBlendBuffers::HasLastNodes()
	{
		return 0 < mLimbRangeCount;
	}

	// FUNCTION: ENGINE 0x10958120
	void PoseBlendBuffers::Fill(Puppet** begin, Puppet** end)
	{
		PoseBlendCursors cursors;
		cursors.cursor[0] = (unsigned char*)mRootNodes;
		cursors.cursor[1] = mBlock[2];
		cursors.cursor[2] = mBlock[4];
		cursors.cursor[3] = mBlock[0];
		cursors.cursor[4] = mBlock[1];
		cursors.cursor[5] = mBlock[3];
		cursors.cursor[6] = mBlock[5];
		PuppetCounts* counts = mCounts;
		for (; begin < end; begin++, counts++)
		{
			(*begin)->BuildNodes(counts, &cursors);
			cursors.cursor[0] += (0 < counts->count[0]) * 0x30;
			cursors.cursor[1] += (0 < counts->count[2]) * 0x10;
			cursors.cursor[2] += (0 < counts->count[3]) * 0x10;
			cursors.cursor[3] += counts->count[0] * 0x70;
			cursors.cursor[4] += counts->count[1] * 0x20;
			cursors.cursor[5] += counts->count[2] * 0x10;
			cursors.cursor[6] += counts->count[3] * 0x10;
		}
	}

	// FUNCTION: ENGINE 0x10958D50
	void PoseBlendBuffers::ApplyRootNodes()
	{
		BlendRootNode* node = mRootNodes;
		for (unsigned int i = 0; i < mRootNodeCount; i++)
		{
			node->Apply();
			node++;
		}
	}

	// FUNCTION: ENGINE 0x10959150
	void UpdatePuppets(float dt, Puppet** begin, Puppet** end)
	{
		for (; begin < end; begin++)
		{
			(*begin)->Update(dt);
		}
	}

	// FUNCTION: ENGINE 0x10958DA0
	void RunPoseBlendJob(PoseBlendJob* job)
	{
		Puppet** begin = job->mBegin;
		Puppet** end = job->mEnd;
		UpdatePuppets(job->mDt, begin, end);
		PoseBlendBuffers buffers;
		core::CriticalSectionEnter(job->mBufferLock);
		buffers.Count(begin, end);
		core::CriticalSectionLeave(job->mBufferLock);
		buffers.Fill(begin, end);
		buffers.ApplyRootNodes();
		buffers.Apply10958220();
		if (buffers.HasLastNodes())
		{
			Unknown10959180(begin, end);
			buffers.Apply10958250();
		}
		for (Puppet** it = begin; it < end; it++)
		{
			Puppet* puppet = *it;
			puppet->BuildRootDelta();
			puppet->UpdatePose();
		}
		core::CriticalSectionEnter(job->mResultLock);
		Unknown109591B0(begin, end);
		core::CriticalSectionLeave(job->mResultLock);
	}
}
