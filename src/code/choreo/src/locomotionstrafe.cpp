// choreo::LocomotionStrafeDriver (driver type 6; the unit 0x1094A610 - 0x1094C790, file name guessed from the class): a
// grid of clips by heading and speed, blended by the heading and the speed of the character. Names are guesses.
#include "code/choreo/drivers.h"
#include "code/choreo/poseblendjob.h"
#include "code/math/mathutils.h"
#include <algorithm>
#include <math.h>

// The sort of the samples is the toolchain's <algorithm> for StrafeSample*; the unit keeps every instance of it as a COMDAT
// function of its own, and the compiler reproduces each one
// FUNCTION: ENGINE 0x1094AED0
template choreo::StrafeSample* std::_Checked_base<choreo::StrafeSample*>(choreo::StrafeSample*&, std::_Unchanged_checked_iterator_base_type_tag);

// FUNCTION: ENGINE 0x1094AEE0
template std::pair<choreo::StrafeSample*, choreo::StrafeSample*>::pair(choreo::StrafeSample* const&, choreo::StrafeSample* const&);

// FUNCTION: ENGINE 0x1094AF00
template int* std::_Dist_type<choreo::StrafeSample*>(choreo::StrafeSample*);

// FUNCTION: ENGINE 0x1094AF10
template choreo::StrafeSample* std::_Val_type<choreo::StrafeSample*>(choreo::StrafeSample*);

// FUNCTION: ENGINE 0x1094AF20
template void std::swap<choreo::StrafeSample>(choreo::StrafeSample&, choreo::StrafeSample&);

// FUNCTION: ENGINE 0x1094AF50
template void std::_Push_heap<choreo::StrafeSample*, int, choreo::StrafeSample>(choreo::StrafeSample*, int, int, choreo::StrafeSample);

// FUNCTION: ENGINE 0x1094AFD0
template std::random_access_iterator_tag std::_Iter_random<choreo::StrafeSample*, choreo::StrafeSample*>(choreo::StrafeSample* const&, choreo::StrafeSample* const&);

// FUNCTION: ENGINE 0x1094AFE0
template std::_Nonscalar_ptr_iterator_tag std::_Ptr_cat<choreo::StrafeSample*, choreo::StrafeSample*>(choreo::StrafeSample*&, choreo::StrafeSample*&);

// FUNCTION: ENGINE 0x1094AFF0
template choreo::StrafeSample* std::_Copy_backward_opt<choreo::StrafeSample*, choreo::StrafeSample*, std::forward_iterator_tag>(choreo::StrafeSample*, choreo::StrafeSample*, choreo::StrafeSample*, std::forward_iterator_tag, std::_Nonscalar_ptr_iterator_tag, std::_Range_checked_iterator_tag);

// FUNCTION: ENGINE 0x1094B4C0
template choreo::StrafeSample* std::_Checked_base<choreo::StrafeSample*>(choreo::StrafeSample*&);

// FUNCTION: ENGINE 0x1094B4D0
template void std::iter_swap<choreo::StrafeSample*, choreo::StrafeSample*>(choreo::StrafeSample*, choreo::StrafeSample*);

// FUNCTION: ENGINE 0x1094B500
template void std::_Med3<choreo::StrafeSample*>(choreo::StrafeSample*, choreo::StrafeSample*, choreo::StrafeSample*);

// FUNCTION: ENGINE 0x1094B5A0
template void std::_Adjust_heap<choreo::StrafeSample*, int, choreo::StrafeSample>(choreo::StrafeSample*, int, int, choreo::StrafeSample);

// FUNCTION: ENGINE 0x1094B650
template choreo::StrafeSample* std::_Copy_backward_opt<choreo::StrafeSample*, choreo::StrafeSample*>(choreo::StrafeSample*, choreo::StrafeSample*, choreo::StrafeSample*, std::random_access_iterator_tag, std::_Nonscalar_ptr_iterator_tag, std::_Range_checked_iterator_tag);

// FUNCTION: ENGINE 0x1094B6B0
template void std::_Pop_heap<choreo::StrafeSample*, int, choreo::StrafeSample>(choreo::StrafeSample*, choreo::StrafeSample*, choreo::StrafeSample*, choreo::StrafeSample, int*);

// FUNCTION: ENGINE 0x1094B940
template void std::_Median<choreo::StrafeSample*>(choreo::StrafeSample*, choreo::StrafeSample*, choreo::StrafeSample*);

// FUNCTION: ENGINE 0x1094B9F0
template void std::_Make_heap<choreo::StrafeSample*, int, choreo::StrafeSample>(choreo::StrafeSample*, choreo::StrafeSample*, int*, choreo::StrafeSample*);

// FUNCTION: ENGINE 0x1094BA60
template choreo::StrafeSample* stdext::unchecked_copy_backward<choreo::StrafeSample*, choreo::StrafeSample*>(choreo::StrafeSample*, choreo::StrafeSample*, choreo::StrafeSample*);

// FUNCTION: ENGINE 0x1094BA90
template void std::_Pop_heap_0<choreo::StrafeSample*, choreo::StrafeSample>(choreo::StrafeSample*, choreo::StrafeSample*, choreo::StrafeSample*);

// FUNCTION: ENGINE 0x1094BAF0
template std::pair<choreo::StrafeSample*, choreo::StrafeSample*> std::_Unguarded_partition<choreo::StrafeSample*>(choreo::StrafeSample*, choreo::StrafeSample*);

// FUNCTION: ENGINE 0x1094BF70
template void std::make_heap<choreo::StrafeSample*>(choreo::StrafeSample*, choreo::StrafeSample*);

// FUNCTION: ENGINE 0x1094BFB0
template void std::_Insertion_sort1<choreo::StrafeSample*, choreo::StrafeSample>(choreo::StrafeSample*, choreo::StrafeSample*, choreo::StrafeSample*);

// FUNCTION: ENGINE 0x1094C060
template void std::pop_heap<choreo::StrafeSample*>(choreo::StrafeSample*, choreo::StrafeSample*);

// FUNCTION: ENGINE 0x1094C0A0
template void std::_Insertion_sort<choreo::StrafeSample*>(choreo::StrafeSample*, choreo::StrafeSample*);

// FUNCTION: ENGINE 0x1094C0C0
template void std::_Sort_heap<choreo::StrafeSample*>(choreo::StrafeSample*, choreo::StrafeSample*);

// FUNCTION: ENGINE 0x1094C150
template void std::sort_heap<choreo::StrafeSample*>(choreo::StrafeSample*, choreo::StrafeSample*);

// FUNCTION: ENGINE 0x1094C160
template void std::_Sort<choreo::StrafeSample*, int>(choreo::StrafeSample*, choreo::StrafeSample*, int);

// FUNCTION: ENGINE 0x1094C2C0
template void std::sort<choreo::StrafeSample*>(choreo::StrafeSample*, choreo::StrafeSample*);

namespace choreo
{
	// 0x111EBCB0 (symbols.txt): the direction a transform faces without a rotation
	extern const math::Vector gForward;

	// 0x109516E0: the rate of a clip of the locomotion from a table of speeds (unit of the locomotion driver)
	float GetClipRate(const void* speeds, pure3d::Animation* animation);

	// FUNCTION: ENGINE 0x1094A8C0
	float HeadingDifference(float from, float to)
	{
		return AngleDifference(from, to);
	}

	// The order of the samples, as a function of its own
	// FUNCTION: ENGINE 0x1094A6C0 ; choreo::StrafeSample::operator<
	bool (StrafeSample::*gKeepStrafeSampleLess)(const StrafeSample&) const = &StrafeSample::operator<;

	// FUNCTION: ENGINE 0x1094A690
	pure3d::Skeleton* LocomotionStrafeDriver::GetSkeletonCopy() const
	{
		return mSkeleton;
	}

	// FUNCTION: ENGINE 0x1094A6A0
	const pure3d::JointMask* LocomotionStrafeDriver::GetJointMaskCopy() const
	{
		return mJointMask;
	}

	// FUNCTION: ENGINE 0x1094A6B0
	unsigned int LocomotionStrafeDriver::GetCellCount() const
	{
		return mRows * mColumns;
	}

	// FUNCTION: ENGINE 0x1094A6E0
	LocomotionStrafeDriver* GetStrafeDriver(Driver* driver)
	{
		return driver->mType == 6 ? static_cast<LocomotionStrafeDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x1094A700
	LocomotionStrafeDriver* Unknown1094A700(Driver* driver)
	{
		return driver->mType == 6 ? static_cast<LocomotionStrafeDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x1094A720
	void LocomotionStrafeDriver::Unbind()
	{
		for (unsigned int i = 0; i < mBindingCount; i++)
		{
			if (mBindings[i].mSource)
			{
				mBindings[i].mSource->Unknown106E7B50();
			}
		}
	}

	// FUNCTION: ENGINE 0x1094A750
	void LocomotionStrafeDriver::SetClipRates(const void* speeds)
	{
		for (unsigned int i = 0; i < mBindingCount; i++)
		{
			mBindings[i].mClip.Unknown10952360(GetClipRate(speeds, mBindings[i].mSource));
		}
	}

	// FUNCTION: ENGINE 0x1094A790
	void LocomotionStrafeDriver::Bind(const DriverInfo& info)
	{
		PartitionDriver::Bind(info);
		bool any = false;
		for (unsigned int i = 0; i < mBindingCount; i++)
		{
			if (mBindings[i].mSource)
			{
				mBindings[i].mClip.Set(mBindings[i].mSource, mSkeleton, false);
				if (any || mBindings[i].mClip.Unknown10952380())
				{
					any = true;
				}
			}
		}
		Unknown1094A4A0(any);
	}

	// FUNCTION: ENGINE 0x1094A800
	unsigned int LocomotionStrafeDriver::GetUnknown1C0() const
	{
		return mSampleCount;
	}

	// FUNCTION: ENGINE 0x1094A810
	bool LocomotionStrafeDriver::AllAtRest() const
	{
		bool all = true;
		for (unsigned int i = 0; i < mBindingCount; i++)
		{
			if (mBindings[i].mSource)
			{
				if (Unknown1094D4C0(mBindings[i]) && all)
				{
					all = true;
				}
				else
				{
					all = false;
				}
			}
		}
		return all;
	}

	// FUNCTION: ENGINE 0x1094A8A0
	void LocomotionStrafeDriver::SetFirstHeading(const math::Vector& direction)
	{
		mFirstHeading = Heading(direction);
	}

	// FUNCTION: ENGINE 0x1094A8E0
	math::Vector* LocomotionStrafeDriver::GetDirection(math::Vector* out) const
	{
		out->x = gForward.x;
		out->y = gForward.y;
		out->z = gForward.z;
		RotateY(mHeading, *out);
		return out;
	}

	// FUNCTION: ENGINE 0x1094A930
	void LocomotionStrafeDriver::SetHeading(const math::Vector& direction)
	{
		mHeading = Heading(direction);
	}

	// FUNCTION: ENGINE 0x1094A950
	math::Vector* LocomotionStrafeDriver::GetVelocity(math::Vector* out) const
	{
		out->x = gForward.x;
		out->y = gForward.y;
		out->z = gForward.z;
		RotateY(mHeading, *out);
		float speed = mSpeed;
		out->x = out->x * speed;
		out->y = out->y * speed;
		out->z = out->z * speed;
		return out;
	}

	// FUNCTION: ENGINE 0x1094A9D0
	// NONMATCHING: the engine computes the step in x87, stores it and takes its reciprocal in SSE; ours keeps everything in x87 (26.7 %)
#ifdef NONMATCHING
	float LocomotionStrafeDriver::GetRowSpeed(unsigned int row, float heading) const
	{
		float angle = WrapFrame(0.0f, 6.2831855f, heading);
		float step = 6.2831855f / (float)mColumns;
		float scale = 1.0f / step;
		unsigned int column = (unsigned int)(angle * scale) % mColumns;
		float t = (angle - (float)column * step) * scale;
		unsigned int next = (column + 1) % mColumns;
		return mCells[mColumns * row + column].mSpeed * (1.0f - t) + mCells[mColumns * row + next].mSpeed * t;
	}
#endif

	// FUNCTION: ENGINE 0x1094B020
	float LocomotionStrafeDriver::GetRowSpeedAt(unsigned int row, float from, float to) const
	{
		return GetRowSpeed(row, HeadingDifference(from, to));
	}

	// FUNCTION: ENGINE 0x1094B060
	float LocomotionStrafeDriver::GetLastRowSpeedAt(float from, float to) const
	{
		unsigned int last = mRows - 1;
		return GetRowSpeed(last, HeadingDifference(from, to));
	}

	// FUNCTION: ENGINE 0x1094B0A0
	float LocomotionStrafeDriver::GetSpeedAtDifference(float position, float from, float to) const
	{
		return GetSpeedAt(position, HeadingDifference(from, to));
	}

	// FUNCTION: ENGINE 0x1094B3A0
	// EQUIVALENT: the squares are summed in another order (the compiler reorders the sum); the vertical part is zero (97.6 %)
	void LocomotionStrafeDriver::SetVelocity(const math::Vector* velocity)
	{
		math::Vector flat;
		flat.x = velocity->x;
		flat.z = velocity->z;
		flat.y = 0.0f;
		mHeading = Heading(flat);
		mSpeed = sqrtf(flat.x * flat.x + flat.z * flat.z + flat.y * flat.y);
	}

	// FUNCTION: ENGINE 0x1094B400
	float LocomotionStrafeDriver::DivideByLastRowSpeedAt(float value, float from, float to) const
	{
		unsigned int last = mRows - 1;
		return value / GetRowSpeed(last, HeadingDifference(from, to));
	}

	// FUNCTION: ENGINE 0x1094B440
	float LocomotionStrafeDriver::DivideByLastRowSpeed(float value, float heading) const
	{
		return value / GetRowSpeed(mRows - 1, heading);
	}

	// FUNCTION: ENGINE 0x1094B460
	float LocomotionStrafeDriver::MultiplyByLastRowSpeedAt(float value, float from, float to) const
	{
		unsigned int last = mRows - 1;
		return GetRowSpeed(last, HeadingDifference(from, to)) * value;
	}

	// FUNCTION: ENGINE 0x1094B4A0
	float LocomotionStrafeDriver::MultiplyByLastRowSpeed(float value, float heading) const
	{
		return GetRowSpeed(mRows - 1, heading) * value;
	}

	// FUNCTION: ENGINE 0x1094B710
	float LocomotionStrafeDriver::ScaleByHeadingSpeed(float value) const
	{
		return MultiplyByLastRowSpeedAt(value, mHeading, mFirstHeading);
	}

	// FUNCTION: ENGINE 0x1094B740
	float LocomotionStrafeDriver::GetSpeedAtHeading(float position) const
	{
		float heading = mHeading;
		float first = mFirstHeading;
		return GetSpeedAt(position, HeadingDifference(heading, first));
	}

	// FUNCTION: ENGINE 0x1094B8D0
	void LocomotionStrafeDriver::SetSpeedByHeading(float value)
	{
		mSpeed = MultiplyByLastRowSpeedAt(value, mHeading, mFirstHeading);
	}

	// FUNCTION: ENGINE 0x1094B900
	void LocomotionStrafeDriver::SetSpeedAtHeading(float position)
	{
		float heading = mHeading;
		float first = mFirstHeading;
		mSpeed = GetSpeedAt(position, HeadingDifference(heading, first));
	}

	// FUNCTION: ENGINE 0x1094AC60
	// EQUIVALENT: the same operations; the count and the pointer into the samples swap registers, and the blend is
	// computed in other xmm registers (71.6 %)
	void LocomotionStrafeDriver::AddSample(unsigned int cell, float weight, float value)
	{
		if (weight <= 0.0f || cell >= mBindingCount)
		{
			return;
		}
		unsigned int count = mSampleCount;
		for (unsigned int i = 0; i < count; i++)
		{
			if (mSamples[i].mCell == cell)
			{
				float total = mSamples[i].mWeight + weight;
				float blend = weight / total;
				mSamples[i].mWeight = total;
				mSamples[i].mValue = (1.0f - blend) * mSamples[i].mValue + blend * value;
				return;
			}
		}
		mSamples[count].mCell = cell;
		mSamples[mSampleCount].mWeight = weight;
		mSamples[mSampleCount].mValue = value;
		mSampleCount++;
	}

	// FUNCTION: ENGINE 0x1094B0D0
	LocomotionStrafeDriver::~LocomotionStrafeDriver()
	{
	}

	// FUNCTION: ENGINE 0x1094B100
	unsigned int PartitionDriver::GetFirstJoint() const
	{
		return mFirstJoint;
	}

	// FUNCTION: ENGINE 0x1094B110
	unsigned int PartitionDriver::GetLastJoint() const
	{
		return mLastJoint;
	}

	// FUNCTION: ENGINE 0x1094AD30
	// NONMATCHING: the frame of the engine's function is 0x18 bytes, ours 0x20, and it loads the node first (25.9 %)
#ifdef NONMATCHING
	void LocomotionStrafeDriver::FillNode(PoseBlendNode* node, PoseBlendSample* samples)
	{
		unsigned int first = mFirstJoint;
		bool none = true;
		if (first == 0)
		{
			none = false;
			node->SetRotation(mDelta.GetQuaternion());
			node->SetTranslation(mDelta.GetPosition());
			mDelta.Transform::Reset();
			first = 1;
		}
		if (mSampleCount > 0)
		{
			node->SetJoints(first, mLastJoint, const_cast<pure3d::JointMask*>(mJointMask));
			node->Set(samples, samples + GetUnknown1C0(), false, false, false);
			float total = 0.0f;
			for (unsigned int i = 0; i < mSampleCount; i++)
			{
				float weight = mSamples[i].mWeight;
				total += weight;
				AnimationBinding& binding = mBindings[mSamples[i].mCell];
				float last = binding.mClip.GetDuration() - 1.0f;
				float frame = WrapFrame(0.0f, last, binding.mClip.Unknown10952350() + mUnknown40 * last);
				binding.mClip.Unknown10952480(&samples[i]);
				samples[i].Set(weight, total, frame, frame, true);
				binding.mSource->Touch();
			}
		}
		node->SetNone(none, none);
	}
#endif
}
