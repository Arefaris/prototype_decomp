// This unit group's copies of the helpers that release a driver or a reference counted object and clear the pointer (each original
// translation unit has its own, defined next to the first unit that calls it).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONHELPERS_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONHELPERS_H

#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// 0x100C05D0
			void ReleaseDriverFreezescale(choreo::Driver*& driver);
			// 0x100C05F0
			void SafeReleaseRefFreezescale(core::IRefCount*& object);
			// 0x100DBB40
			void ReleaseDriverJoint(choreo::Driver*& driver);
		}
	}
}

#endif
