#include "code/proto/behaviours/javelinmissilebehaviour.h"

namespace proto
{
	// 0x10DA4224: 0.8f (name guess)
	extern const float gEightTenths;
	// 0x10DCA8EC: 18.0f (name guess)
	extern const float gEighteen;

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10466E50
	content::ClassInfo* JavelinMissileBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::JavelinMissileBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10466E90
	JavelinMissileBehaviour::~JavelinMissileBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10466EB0
	void JavelinMissileBehaviour::Slot16()
	{
		if (unknown110 <= unknown108)
		{
			MissileBehaviour::Slot16();
			return;
		}
		unknown8C.x = unknown80.x;
		unknown8C.y = unknown80.y;
		unknown8C.z = unknown80.z;
	}

	// FUNCTION: ENGINE 0x10466F00
	// EQUIVALENT: scheduling; the engine loads the constants and zeroes xmm0 first and stores the vftable after the first stores, ours stores it first (47 %)
	JavelinMissileBehaviour::JavelinMissileBehaviour(engine::GameObject* newOwner) : MissileBehaviour(newOwner)
	{
		float coast = gEightTenths;
		ignitionTime = coast;
		dragForce = coast;
		float fall = gEighteen;
		unknown108 = 0.0f;
		unknown110 = 0.0f;
		verticalDragForce = 0.0f;
		gravity = fall;
		unknown120.x = 0.0f;
		unknown120.y = 0.0f;
		unknown120.z = 0.0f;
		Listen(0x20, true);
	}

	// FUNCTION: ENGINE 0x10467500
	void JavelinMissileBehaviour::Slot1()
	{
		MissileBehaviour::Slot1();
	}

	// FUNCTION: ENGINE 0x10467370
	content::MemberList* JavelinMissileBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<MissileBehaviour>();
		static content::BaseClassCasterImpl<MissileBehaviour, JavelinMissileBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<JavelinMissileBehaviour, float, 0>("p"),
				PROTO_OFFSET(JavelinMissileBehaviour, ignitionTime), "ignitionTime" },
			{ content::GetMemberPrimitiveMetaType<JavelinMissileBehaviour, float, 1>("p"),
				PROTO_OFFSET(JavelinMissileBehaviour, dragForce), "dragForce" },
			{ content::GetMemberPrimitiveMetaType<JavelinMissileBehaviour, float, 2>("p"),
				PROTO_OFFSET(JavelinMissileBehaviour, verticalDragForce), "verticalDragForce" },
			{ content::GetMemberPrimitiveMetaType<JavelinMissileBehaviour, float, 3>("p"),
				PROTO_OFFSET(JavelinMissileBehaviour, gravity), "gravity" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10466FA0
// FUNCTION: ENGINE 0x10466FB0
// FUNCTION: ENGINE 0x10466FE0
// FUNCTION: ENGINE 0x10467270
// FUNCTION: ENGINE 0x104672B0
// FUNCTION: ENGINE 0x104672F0
// FUNCTION: ENGINE 0x10467330
