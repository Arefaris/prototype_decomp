// The reflected attribute classes of the driving code (namespace engine::driving; the code sits in 0x109340E0 -
// 0x10937640 and 0x1093CE40 - 0x1093D9D0, no assert path; directory and file names guessed). The classes are plain
// data the vehicle behaviours read; the member names are the reflected ones.
#ifndef ENGINE_DRIVING_VEHICLEATTRIBUTES_H
#define ENGINE_DRIVING_VEHICLEATTRIBUTES_H

#include "code/content/metatype.h"

namespace engine
{
	namespace driving
	{
		// The mass of a vehicle and how its inertia tensor is scaled (no vftable; 0x1C bytes)
		struct VehicleMassAttributes
		{
			// 0x10934120
			VehicleMassAttributes();

			// 0x109340E0 / 0x109343D0
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float mass;  // +0x0
			float inertiaScaleXX;  // +0x4
			float inertiaScaleYY;  // +0x8
			float inertiaScaleZZ;  // +0xC
			float inertiaScaleXY;  // +0x10
			float inertiaScaleXZ;  // +0x14
			float inertiaScaleYZ;  // +0x18
		};
	}
}

#endif
