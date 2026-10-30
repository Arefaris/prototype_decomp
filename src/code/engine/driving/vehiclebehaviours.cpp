#include "code/engine/driving/vehiclebehaviours.h"

namespace engine
{
	namespace driving
	{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

		// FUNCTION: ENGINE 0x1091CD30
		content::ClassInfo* CarIntentionBehaviour::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "CarIntentionBehaviour";
			sInfo.code = "pn";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x1091CF50
		content::MemberList* CarIntentionBehaviour::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<VehicleIntentionBehaviour>();
			static content::BaseClassCasterImpl<VehicleIntentionBehaviour, CarIntentionBehaviour> sCaster;
			sList.baseCaster = &sCaster;
			return &sList;
		}

		// FUNCTION: ENGINE 0x1091D020
		content::ClassInfo* CarPhysicsBehaviour::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "CarPhysicsBehaviour";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x1091D7B0
		content::MemberList* CarPhysicsBehaviour::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<VehiclePhysicsBehaviour>();
			static content::BaseClassCasterImpl<VehiclePhysicsBehaviour, CarPhysicsBehaviour> sCaster;
			sList.baseCaster = &sCaster;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetReferenceMetaType<CarPhysicsBehaviour, WheelCollectionData>("p"),
					ENGINE_OFFSET(CarPhysicsBehaviour, wheelsData), "wheelsData" },
				{ content::GetReferenceMetaType<CarPhysicsBehaviour, CarPhysicsAttributes>("p"),
					ENGINE_OFFSET(CarPhysicsBehaviour, carPhysics), "carPhysics" }
			};
			sList.members = sMembers;
			sList.count = 2;
			return &sList;
		}

		// FUNCTION: ENGINE 0x1091D980
		content::ClassInfo* HelicopterIntentionBehaviour::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "HelicopterIntentionBehaviour";
			sInfo.code = "pn";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x1091DB70
		content::MemberList* HelicopterIntentionBehaviour::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<VehicleIntentionBehaviour>();
			static content::BaseClassCasterImpl<VehicleIntentionBehaviour, HelicopterIntentionBehaviour> sCaster;
			sList.baseCaster = &sCaster;
			return &sList;
		}

		// FUNCTION: ENGINE 0x1091DC00
		content::ClassInfo* HelicopterPhysicsBehaviour::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "HelicopterPhysicsBehaviour";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x1091DEA0
		content::MemberList* HelicopterPhysicsBehaviour::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<VehiclePhysicsBehaviour>();
			static content::BaseClassCasterImpl<VehiclePhysicsBehaviour, HelicopterPhysicsBehaviour> sCaster;
			sList.baseCaster = &sCaster;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetReferenceMetaType<HelicopterPhysicsBehaviour, HelicopterPhysicsAttributes>("p"),
					ENGINE_OFFSET(HelicopterPhysicsBehaviour, helicopterPhysics), "helicopterPhysics" }
			};
			sList.members = sMembers;
			sList.count = 1;
			return &sList;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1091CEF0
// FUNCTION: ENGINE 0x1091CF00
// FUNCTION: ENGINE 0x1091CE50
// FUNCTION: ENGINE 0x1091D090
// FUNCTION: ENGINE 0x1091D0F0
// FUNCTION: ENGINE 0x1091D100
// FUNCTION: ENGINE 0x1091D1A0
// FUNCTION: ENGINE 0x1091D1B0
// FUNCTION: ENGINE 0x1091D6A0
// FUNCTION: ENGINE 0x1091D6C0
// FUNCTION: ENGINE 0x1091D6D0
// FUNCTION: ENGINE 0x1091D710
// FUNCTION: ENGINE 0x1091D760
// FUNCTION: ENGINE 0x1091DB10
// FUNCTION: ENGINE 0x1091DB20
// FUNCTION: ENGINE 0x1091DC80
// FUNCTION: ENGINE 0x1091DCD0
// FUNCTION: ENGINE 0x1091DCE0
// FUNCTION: ENGINE 0x1091DE00
// FUNCTION: ENGINE 0x1091DE10
// FUNCTION: ENGINE 0x1091DE50
