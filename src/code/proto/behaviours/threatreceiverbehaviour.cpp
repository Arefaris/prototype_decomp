#include "code/proto/behaviours/threatreceiverbehaviour.h"
#include "code/engine/message.h"

namespace proto
{
	// The messages of type 0x35 the behaviour answers (the members are guesses from the handlers)
	struct ThreatReportMessage : public engine::IntrusiveMessage
	{
		engine::GameObjectHandle handle;  // +0xC
	};

	struct ThreatenedListMessage : public engine::IntrusiveMessage
	{
		engine::GameObjectHandle* list;  // +0xC
		int count;  // +0x10
	};

	struct ThreatQueryMessage : public engine::IntrusiveMessage
	{
		engine::GameObjectHandle handle;  // +0xC
		int other;  // +0x10
		bool found;  // +0x14
	};

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10403000
	content::ClassInfo* ThreatReceiverBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ThreatReceiverBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10403690
	ThreatReceiverBehaviour::ThreatReceiverBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
		Listen(0x35, true);
		Listen(2, true);
		ClearThreatenedBy();
	}

	// FUNCTION: ENGINE 0x10403580
	void ThreatReceiverBehaviour::ClearThreatenedBy()
	{
		threatenedBy.Reset();
	}

	// FUNCTION: ENGINE 0x10403190
	bool ThreatReceiverBehaviour::HasThreat(unsigned int handle, int other)
	{
		bool found = false;
		for (ThreatEntry* entry = threats.Begin(); entry != threats.End(); entry++)
		{
			if (*(unsigned int*)&entry->handle == handle && entry->amount != other)
			{
				found = true;
				break;
			}
		}
		return found;
	}

	// FUNCTION: ENGINE 0x10403590
	void ThreatReceiverBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 2:
			ClearThreatenedBy();
			break;
		case 0x35:
			switch ((unsigned short)message->id)
			{
			case 0:
				OnThreatReported(((ThreatReportMessage*)message)->handle);
				return;
			case 1:
				{
					ThreatenedListMessage* list = (ThreatenedListMessage*)message;
					int count = threatenedBy.Size();
					list->count = count;
					list->list = count > 0 ? threatenedBy.Data() : 0;
				}
				return;
			case 2:
				{
					ThreatQueryMessage* query = (ThreatQueryMessage*)message;
					query->found = HasThreat(*(unsigned int*)&query->handle, query->other);
				}
				return;
			case 3:
				threats.Reset();
				return;
			case 4:
				threatenedBy.Reset();
				return;
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x104036F0
	ThreatReceiverBehaviour::~ThreatReceiverBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10403650
	void ThreatReceiverBehaviour::Update(float dt, unsigned short mask)
	{
		if (automaticallyClearThreats)
		{
			threatenedBy.Reset();
		}
		Listen2(8, false);
	}

	// FUNCTION: ENGINE 0x10403300
	content::MemberList* ThreatReceiverBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, ThreatReceiverBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ThreatReceiverBehaviour, bool, 0>("pn"),
				PROTO_OFFSET(ThreatReceiverBehaviour, automaticallyClearThreats), "automaticallyClearThreats" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10403040
// FUNCTION: ENGINE 0x10403050
// FUNCTION: ENGINE 0x10403060
// FUNCTION: ENGINE 0x104030A0
// FUNCTION: ENGINE 0x104030B0
// FUNCTION: ENGINE 0x10403130
// FUNCTION: ENGINE 0x10403140
// FUNCTION: ENGINE 0x10403150
// FUNCTION: ENGINE 0x10403160
// FUNCTION: ENGINE 0x104032B0
// FUNCTION: ENGINE 0x104032C0
// FUNCTION: ENGINE 0x10403560
// FUNCTION: ENGINE 0x10403570
// FUNCTION: ENGINE 0x10403680
// FUNCTION: ENGINE 0x10403710
// FUNCTION: ENGINE 0x10403950
// FUNCTION: ENGINE 0x10403A40
