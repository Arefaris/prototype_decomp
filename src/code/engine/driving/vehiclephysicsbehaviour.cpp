#include "code/engine/driving/vehiclebehaviours.h"

namespace engine
{
	namespace driving
	{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

		// FUNCTION: ENGINE 0x10938420
		content::ClassInfo* VehiclePhysicsBehaviour::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "VehiclePhysicsBehaviour";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10938AC0
		content::MemberList* VehiclePhysicsBehaviour::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<Behaviour>();
			static content::BaseClassCasterImpl<Behaviour, VehiclePhysicsBehaviour> sCaster;
			sList.baseCaster = &sCaster;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetReferenceMetaType<VehiclePhysicsBehaviour, VehiclePhysicsAttributes>("p"),
					ENGINE_OFFSET(VehiclePhysicsBehaviour, basePhysics), "basePhysics" }
			};
			sList.members = sMembers;
			sList.count = 1;
			return &sList;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10938490
// FUNCTION: ENGINE 0x109384C0
// FUNCTION: ENGINE 0x109384D0
// FUNCTION: ENGINE 0x10938A10
// FUNCTION: ENGINE 0x10938A20
// FUNCTION: ENGINE 0x10938A70
