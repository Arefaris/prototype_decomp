// What pure3d::PoseAnimationController (primitive.h) reads of its animation: the joints it drives. Names are
// guesses.
#ifndef PURE3D_POSECONTROLLER_H
#define PURE3D_POSECONTROLLER_H

#include "code/pure3d/channel.h"
#include "code/pure3d/pose.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// The joints an animation drives: bit n of the words after the first is set for joint n
	struct JointMask
	{
		unsigned int unknown0;
		unsigned int words[1];
	};

	// What the controller keeps at +0x160 (the joint mask is at +0x10)
	struct PoseAnimationInfo
	{
		unsigned char unknown0[0x10];
		JointMask* mJointMask;
	};
}

#endif
