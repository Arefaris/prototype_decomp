#include "code/engine/driving/physicsattributes.h"

namespace engine
{
	namespace driving
	{
		// The vehicle vector (0x1131B4B4)
		math::Vector gVehicleVector;

		// FUNCTION: ENGINE 0x10905A00
		content::ClassInfo* VehiclePhysicsAttributes::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "VehiclePhysicsAttributes";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10905A70
		VehicleMassAttributes* VehiclePhysicsAttributes::GetMassAttributes()
		{
			return &massAttributes;
		}

		// FUNCTION: ENGINE 0x10905A40
		const math::Vector* GetVehicleVector()
		{
			return &gVehicleVector;
		}

		// FUNCTION: ENGINE 0x10905A50
		void SetVehicleVector(const math::Vector* value)
		{
			gVehicleVector = *value;
		}

		// FUNCTION: ENGINE 0x10905AE0
		content::MemberList* VehiclePhysicsAttributes::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetClassMetaType<VehicleMassAttributes>(),
					content::MemberOffset(&((VehiclePhysicsAttributes*)0)->massAttributes,
					(int)&((VehiclePhysicsAttributes*)0)->massAttributes), "massAttributes" }
			};
			sList.members = sMembers;
			sList.count = 1;
			return &sList;
		}

		// FUNCTION: ENGINE 0x10905B60
		// EQUIVALENT: the engine's lea of the first member sits behind the reference count store, ours before it, 73.5 %
		VehiclePhysicsAttributes::VehiclePhysicsAttributes()
		{
		}
	}
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10905A80
// FUNCTION: ENGINE 0x10905AD0
// FUNCTION: ENGINE 0x10905B90
