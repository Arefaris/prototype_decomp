// choreo::LocomotionSteerDriver (driver type 5; the unit 0x1094FB00 - 0x10951F00, file name guessed from the class): the
// locomotion that blends its clips by how the character steers. Names are guesses.
#include "code/choreo/drivers.h"
#include "code/choreo/poseblendjob.h"

namespace choreo
{
	// 0x109516E0: the rate of a clip of the locomotion from a table of speeds (unit of the locomotion driver)
	float GetClipRate(const void* speeds, pure3d::Animation* animation);

	// FUNCTION: ENGINE 0x1094FB20
	unsigned int LocomotionSteerDriver::GetUnknown48() const
	{
		return mUnknown48;
	}

	// FUNCTION: ENGINE 0x1094FB30
	unsigned int LocomotionSteerDriver::GetUnknown48Plus1() const
	{
		return mUnknown48 + 1;
	}

	// FUNCTION: ENGINE 0x1094FB40
	unsigned int LocomotionSteerDriver::GetSampleCount() const
	{
		return mSampleCount;
	}

	// FUNCTION: ENGINE 0x1094FB70
	LocomotionSteerDriver* GetSteerDriver(Driver* driver)
	{
		return driver->mType == 5 ? static_cast<LocomotionSteerDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x1094FB90
	LocomotionSteerDriver* Unknown1094FB90(Driver* driver)
	{
		return driver->mType == 5 ? static_cast<LocomotionSteerDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x1094FBB0
	void LocomotionSteerDriver::Unbind()
	{
		for (unsigned int i = 0; i < mBindingCount; i++)
		{
			if (mBindings[i].mSource)
			{
				mBindings[i].mSource->Unknown106E7B50();
			}
		}
	}

	// FUNCTION: ENGINE 0x1094FBE0
	void LocomotionSteerDriver::SetClipRates(const void* speeds)
	{
		for (unsigned int i = 0; i < mBindingCount; i++)
		{
			mBindings[i].mClip.Unknown10952360(GetClipRate(speeds, mBindings[i].mSource));
		}
	}

	// FUNCTION: ENGINE 0x1094FC20
	void LocomotionSteerDriver::Bind(const DriverInfo& info)
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

	// FUNCTION: ENGINE 0x1094FCB0
	bool LocomotionSteerDriver::AllAtRest() const
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

	// FUNCTION: ENGINE 0x1094FCF0
	float LocomotionSteerDriver::GetUnknown1A4(int index) const
	{
		return mUnknown1A4[index];
	}

	// FUNCTION: ENGINE 0x1094FD00
	// EQUIVALENT: the same operations; the count and the pointer into the samples swap registers, and the blend is
	// computed in other xmm registers
	void LocomotionSteerDriver::AddSample(unsigned int binding, float weight, float value)
	{
		if (weight <= 0.0f || binding >= mBindingCount)
		{
			return;
		}
		unsigned int count = mSampleCount;
		for (unsigned int i = 0; i < count; i++)
		{
			if (mSamples[i].mCell == binding)
			{
				float total = mSamples[i].mWeight + weight;
				float blend = weight / total;
				mSamples[i].mWeight = total;
				mSamples[i].mValue = (1.0f - blend) * mSamples[i].mValue + blend * value;
				return;
			}
		}
		mSamples[count].mCell = binding;
		mSamples[mSampleCount].mWeight = weight;
		mSamples[mSampleCount].mValue = value;
		mSampleCount++;
	}

	// FUNCTION: ENGINE 0x109500C0
	LocomotionSteerDriver::~LocomotionSteerDriver()
	{
	}
}
