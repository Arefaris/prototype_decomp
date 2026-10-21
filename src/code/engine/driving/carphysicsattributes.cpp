#include "code/engine/driving/physicsattributes.h"

namespace engine
{
	namespace driving
	{
		// FUNCTION: ENGINE 0x10906C40
		content::ClassInfo* CarPhysicsAttributes::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "CarPhysicsAttributes";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10906D80
		content::MemberList* CarPhysicsAttributes::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetClassMetaType<CarSuspensionAttributes>(),
					content::MemberOffset(&((CarPhysicsAttributes*)0)->suspension,
					(int)&((CarPhysicsAttributes*)0)->suspension), "suspension" },
				{ content::GetClassMetaType<CarControlAttributes>(),
					content::MemberOffset(&((CarPhysicsAttributes*)0)->control,
					(int)&((CarPhysicsAttributes*)0)->control), "control" }
			};
			sList.members = sMembers;
			sList.count = 2;
			return &sList;
		}

		// FUNCTION: ENGINE 0x10906E20
		// EQUIVALENT: the engine's lea of the first member sits behind the reference count store, ours before it, 85.9 %
		CarPhysicsAttributes::CarPhysicsAttributes()
		{
		}
	}
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10906CC0
// FUNCTION: ENGINE 0x10906D10
// FUNCTION: ENGINE 0x10906D60
// FUNCTION: ENGINE 0x10906D70
