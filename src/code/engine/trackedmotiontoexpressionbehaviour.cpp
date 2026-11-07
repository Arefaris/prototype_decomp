// engine::TrackedMotionToExpressionBehaviour (RTTI name; base engine::Behaviour): unit 0x1092A440 - 0x1092B520. Only the
// reflection's class description is reconstructed so far; the class is still described by reflectedclasses.h.
#include "code/engine/reflectedclasses.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1092A440
	content::ClassInfo* TrackedMotionToExpressionBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::TrackedMotionToExpressionBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1092AA40
	content::MemberList* TrackedMotionToExpressionBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, TrackedMotionToExpressionBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<TrackedMotionToExpressionBehaviour, TrackedMotionToExpressionMap>("pn"),
				ENGINE_OFFSET(TrackedMotionToExpressionBehaviour, map), "map" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1092A570
// FUNCTION: ENGINE 0x1092A620
// FUNCTION: ENGINE 0x1092A630
// FUNCTION: ENGINE 0x1092A740
// FUNCTION: ENGINE 0x1092A750
// FUNCTION: ENGINE 0x1092A920
