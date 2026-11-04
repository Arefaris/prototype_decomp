#include "code/proto/behaviours/discardedfirearmbehaviour.h"
#include "code/core/refptr.h"

namespace content
{
	static const EnumValue sAmmoActionValues[] =
	{
		{ "None", 0 },
		{ "Reload", 1 },
		{ "Fade", 2 }
	};

	// FUNCTION: ENGINE 0x10464F30
	void EnumInfo<proto::DiscardedFirearmBehaviour::AmmoActionOnAttachmentChange>::Get(const char** name,
		const EnumValue** values, int* count, const char** code)
	{
		*name = "proto::DiscardedFirearmBehaviour::AmmoActionOnAttachmentChange";
		*code = "pn";
		*values = sAmmoActionValues;
		*count = 3;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10464F70
	content::ClassInfo* DiscardedFirearmBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DiscardedFirearmBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10464FB0
	DiscardedFirearmBehaviour::DiscardedFirearmBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		ammoActionOnAttach(0), ammoProfileOnAttach(0), timeBeforeFade(0.0f), timeToFade(0.0f), timeElapsed(0.0f)
	{
		Listen(0xf, true);
		Listen(1, true);
	}

	// FUNCTION: ENGINE 0x104652A0
	DiscardedFirearmBehaviour::~DiscardedFirearmBehaviour()
	{
		core::SafeRelease(ammoProfileOnAttach);
	}

	// FUNCTION: ENGINE 0x104657C0
	content::MemberList* DiscardedFirearmBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, DiscardedFirearmBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<AmmoActionOnAttachmentChange>(), 0xc, "ammoActionOnAttach" },
			{ content::GetReferenceMetaType<DiscardedFirearmBehaviour, AmmoProfileBase>("p"),
				PROTO_OFFSET(DiscardedFirearmBehaviour, ammoProfileOnAttach), "ammoProfileOnAttach" },
			{ content::GetMemberPrimitiveMetaType<DiscardedFirearmBehaviour, float, 0>("p"),
				PROTO_OFFSET(DiscardedFirearmBehaviour, timeBeforeFade), "timeBeforeFade" },
			{ content::GetMemberPrimitiveMetaType<DiscardedFirearmBehaviour, float, 1>("p"),
				PROTO_OFFSET(DiscardedFirearmBehaviour, timeToFade), "timeToFade" },
			{ content::GetMemberPrimitiveMetaType<DiscardedFirearmBehaviour, float, 2>("n"),
				PROTO_OFFSET(DiscardedFirearmBehaviour, timeElapsed), "timeElapsed" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10465170
// FUNCTION: ENGINE 0x10465200
// FUNCTION: ENGINE 0x10465260
// FUNCTION: ENGINE 0x10465270
// FUNCTION: ENGINE 0x104652D0
// FUNCTION: ENGINE 0x10465310
// FUNCTION: ENGINE 0x10465350
// FUNCTION: ENGINE 0x104653A0
// FUNCTION: ENGINE 0x10465760
