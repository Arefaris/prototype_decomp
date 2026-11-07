#include "code/proto/behaviours/alertbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1042E3D0
	content::ClassInfo* AlertBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AlertBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1042E410
	// NONMATCHING: the engine zeroes the three words before it loads the frame skip for Remove (88.5 %)
#ifdef NONMATCHING
	AlertBehaviour::AlertBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), alertRadius(5.0f),
		alertType(0), unknown14(0.0f), broadcastFrequency(3), broadcastForever(true), timeBroadcasting(0.0f)
	{
		unknown2C = 0;
		unknown30 = 0;
		unknown34 = 0;
		Remove((unsigned char)broadcastFrequency);
		Listen2(0x10, true);
		Listen(0x24, true);
		Listen(0x25, true);
	}
#endif

	// FUNCTION: ENGINE 0x1042E900
	content::MemberList* AlertBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, AlertBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<AlertBehaviour, float, 0>("p"),
				PROTO_OFFSET(AlertBehaviour, alertRadius), "alertRadius" },
			{ content::GetEnumMetaType<AiAlert>(), 0xC, "alertType" },
			{ content::GetMemberPrimitiveMetaType<AlertBehaviour, int, 0>("p"),
				PROTO_OFFSET(AlertBehaviour, broadcastFrequency), "broadcastFrequency" },
			{ content::GetMemberPrimitiveMetaType<AlertBehaviour, bool, 0>("p"),
				PROTO_OFFSET(AlertBehaviour, broadcastForever), "broadcastForever" },
			{ content::GetMemberPrimitiveMetaType<AlertBehaviour, float, 1>("p"),
				PROTO_OFFSET(AlertBehaviour, timeBroadcasting), "timeBroadcasting" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}
}

namespace content
{
	// 0x103608E0 (another unit)
	template<> void EnumInfo<proto::AiAlert>::Get(const char** name, const EnumValue** values, int* count,
		const char** code);
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1042E590
// FUNCTION: ENGINE 0x1042E690
// FUNCTION: ENGINE 0x1042E6A0
// FUNCTION: ENGINE 0x1042E800
// FUNCTION: ENGINE 0x1042E840
// FUNCTION: ENGINE 0x1042E880
// FUNCTION: ENGINE 0x1042E8C0
