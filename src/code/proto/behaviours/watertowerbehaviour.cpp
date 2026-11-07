#include "code/proto/behaviours/watertowerbehaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/proto/fightitems/motion/motionmessages2.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10406A70
	content::ClassInfo* WaterTowerBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WaterTowerBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10406AB0
	WaterTowerBehaviour::WaterTowerBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
		forceInfected = false;
		unknown10 = 0.0f;
		unknown14 = false;
		Listen(0x16, true);
		Listen(0x2b, true);
	}

	// FUNCTION: ENGINE 0x10406B00
	WaterTowerBehaviour::~WaterTowerBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10406B80
	// NONMATCHING: the engine keeps the vftable store behind the name copy and before the send (70 %)
#ifdef NONMATCHING
	int WaterTowerBehaviour::GetInfected()
	{
		core::Name<core::CaseSensitiveKey> name("infected", 1);
		VariableIntGetMessage message(name);
		owner->SendMessage(&message);
		return message.value;
	}
#endif

	// FUNCTION: ENGINE 0x10406C00
	// NONMATCHING: the engine keeps the vftable store behind the name copy and before the send (70 %)
#ifdef NONMATCHING
	void WaterTowerBehaviour::SetInfected(int value)
	{
		core::Name<core::CaseSensitiveKey> name("infected", 1);
		VariableIntSetMessage message(name, value, true);
		owner->SendMessage(&message);
	}
#endif

	// FUNCTION: ENGINE 0x10406C80
	// NONMATCHING: the engine keeps the vftable store behind the name copy and before the send (70 %)
#ifdef NONMATCHING
	int WaterTowerBehaviour::GetScanState()
	{
		core::Name<core::CaseSensitiveKey> name("scanState", 1);
		VariableIntGetMessage message(name);
		owner->SendMessage(&message);
		return message.value;
	}
#endif

	// FUNCTION: ENGINE 0x10406D00
	// NONMATCHING: the engine keeps the vftable store behind the name copy and before the send (70 %)
#ifdef NONMATCHING
	void WaterTowerBehaviour::SetScanState(int value)
	{
		core::Name<core::CaseSensitiveKey> name("scanState", 1);
		VariableIntSetMessage message(name, value, true);
		owner->SendMessage(&message);
	}
#endif

	// FUNCTION: ENGINE 0x10406DC0
	content::MemberList* WaterTowerBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, WaterTowerBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<WaterTowerBehaviour, bool, 0>("p"),
				PROTO_OFFSET(WaterTowerBehaviour, forceInfected), "forceInfected" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10406B10
// FUNCTION: ENGINE 0x10406B20
// FUNCTION: ENGINE 0x10406B50
// FUNCTION: ENGINE 0x10406D80
