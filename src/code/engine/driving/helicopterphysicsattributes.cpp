#include "code/engine/driving/physicsattributes.h"

namespace engine
{
	namespace driving
	{
		// FUNCTION: ENGINE 0x10906E90
		content::ClassInfo* HelicopterPhysicsAttributes::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "HelicopterPhysicsAttributes";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10906F40
		content::MemberList* HelicopterPhysicsAttributes::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetClassMetaType<HelicopterControlAttributes>(),
					content::MemberOffset(&((HelicopterPhysicsAttributes*)0)->control,
					(int)&((HelicopterPhysicsAttributes*)0)->control), "control" }
			};
			sList.members = sMembers;
			sList.count = 1;
			return &sList;
		}

		// FUNCTION: ENGINE 0x10906FC0
		// EQUIVALENT: the engine's lea of the first member sits behind the reference count store, ours before it, 73.5 %
		HelicopterPhysicsAttributes::HelicopterPhysicsAttributes()
		{
		}
	}
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10906EE0
// FUNCTION: ENGINE 0x10906F30
// FUNCTION: ENGINE 0x10906FF0
