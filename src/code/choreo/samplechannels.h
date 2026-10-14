// The channels that animate the joints of a pose, arranged by kind (an array of channel pointers per kind, one entry
// per joint; the same kinds and order as pure3d::JointChannels, which arranges them by joint). Names are guesses.
#ifndef CHOREO_SAMPLECHANNELS_H
#define CHOREO_SAMPLECHANNELS_H

#include "code/pure3d/channel.h"

namespace choreo
{
	class SampleChannels
	{
	public:
		static const unsigned int MAX_JOINTS = 96;

		// 0x10952150 - 0x109521A0: the channel of a joint, by kind
		pure3d::QuaternionChannel* GetRotation(int joint);
		pure3d::VectorChannel* GetTranslation(int joint);
		pure3d::VectorChannel* GetUnknown10(int joint);
		pure3d::VectorChannel* GetScale(int joint);
		pure3d::VectorChannel* GetUnknown14(int joint);
		pure3d::VectorChannel* GetUnknown1C(int joint);

		pure3d::QuaternionChannel* mRotations[MAX_JOINTS];
		pure3d::VectorChannel* mTranslations[MAX_JOINTS];
		pure3d::VectorChannel* mUnknown10[MAX_JOINTS];
		pure3d::VectorChannel* mScales[MAX_JOINTS];
		pure3d::VectorChannel* mUnknown14[MAX_JOINTS];
		pure3d::VectorChannel* mUnknown1C[MAX_JOINTS];
	};
}

#endif
