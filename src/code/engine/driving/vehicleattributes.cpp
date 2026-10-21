// The reflected attribute classes of the driving code: see the header.
#include "code/engine/driving/vehicleattributes.h"

namespace engine
{
	namespace driving
	{
		// FUNCTION: ENGINE 0x109340E0
		content::ClassInfo* VehicleMassAttributes::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::driving::VehicleMassAttributes";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10934120
		VehicleMassAttributes::VehicleMassAttributes()
		{
			mass = 1.0f;
			inertiaScaleXX = inertiaScaleYY = inertiaScaleZZ = 1.0f;
			inertiaScaleXY = inertiaScaleXZ = inertiaScaleYZ = 0.0f;
		}

#define ENGINE_DRIVING_FLOAT(Class, index, member) \
	{ content::GetMemberPrimitiveMetaType<Class, float, index>("p"), \
		content::MemberOffset(&((Class*)0)->member, (int)&((Class*)0)->member), #member }

		// FUNCTION: ENGINE 0x109343D0
		content::MemberList* VehicleMassAttributes::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				ENGINE_DRIVING_FLOAT(VehicleMassAttributes, 0, mass),
				ENGINE_DRIVING_FLOAT(VehicleMassAttributes, 1, inertiaScaleXX),
				ENGINE_DRIVING_FLOAT(VehicleMassAttributes, 2, inertiaScaleYY),
				ENGINE_DRIVING_FLOAT(VehicleMassAttributes, 3, inertiaScaleZZ),
				ENGINE_DRIVING_FLOAT(VehicleMassAttributes, 4, inertiaScaleXY),
				ENGINE_DRIVING_FLOAT(VehicleMassAttributes, 5, inertiaScaleXZ),
				ENGINE_DRIVING_FLOAT(VehicleMassAttributes, 6, inertiaScaleYZ)
			};
			sList.members = sMembers;
			sList.count = 7;
			return &sList;
		}
	}
}
