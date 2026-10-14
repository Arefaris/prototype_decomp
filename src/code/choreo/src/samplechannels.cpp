// choreo::SampleChannels (unit around 0x10952120 - 0x10955600, which samples animations into poses; file name
// guessed from the class). Names are guesses.
#include "code/choreo/samplechannels.h"

namespace choreo
{
	// FUNCTION: ENGINE 0x10952150
	pure3d::QuaternionChannel* SampleChannels::GetRotation(int joint)
	{
		return mRotations[joint];
	}

	// FUNCTION: ENGINE 0x10952160
	pure3d::VectorChannel* SampleChannels::GetTranslation(int joint)
	{
		return mTranslations[joint];
	}

	// FUNCTION: ENGINE 0x10952170
	pure3d::VectorChannel* SampleChannels::GetUnknown10(int joint)
	{
		return mUnknown10[joint];
	}

	// FUNCTION: ENGINE 0x10952180
	pure3d::VectorChannel* SampleChannels::GetScale(int joint)
	{
		return mScales[joint];
	}

	// FUNCTION: ENGINE 0x10952190
	pure3d::VectorChannel* SampleChannels::GetUnknown14(int joint)
	{
		return mUnknown14[joint];
	}

	// FUNCTION: ENGINE 0x109521A0
	pure3d::VectorChannel* SampleChannels::GetUnknown1C(int joint)
	{
		return mUnknown1C[joint];
	}
}
