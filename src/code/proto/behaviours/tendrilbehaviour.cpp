#include "code/proto/behaviours/tendrilbehaviour.h"
#include "code/core/refptr.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x100784C0
	TendrilBehaviour::TendrilBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), firstAction(0)
	{
		Listen(0x1e, true);
		Listen(0x17, true);
		Listen(2, true);
		Listen2(0x100, true);
	}

	// FUNCTION: ENGINE 0x10078540
	void TendrilBehaviour::Update(float dt, unsigned short mask)
	{
		for (fightitems::motion::AbstractTendrilAction* action = firstAction; action != 0; action = action->nextTendril)
		{
			if (!action->Update(dt))
			{
				action->End(true);
			}
		}
	}

	// FUNCTION: ENGINE 0x10078680
	// NONMATCHING: the registers of the message and of the old head are swapped (91.4 %)
#ifdef NONMATCHING
	void TendrilBehaviour::OnRegister(RegisterTendrilActionMessage* message)
	{
		fightitems::motion::AbstractTendrilAction* action = message->action;
		if (action != 0 && action->nextTendril == 0 && action->previousTendril == 0)
		{
			if (firstAction == 0)
			{
				core::RefAssign(firstAction, action);
				message->registered = true;
				return;
			}
			fightitems::motion::AbstractTendrilAction* old = 0;
			core::RefAssign(old, firstAction);
			core::RefAssign(firstAction, message->action);
			core::RefAssign(old->previousTendril, firstAction);
			core::RefAssign(firstAction->nextTendril, old);
			core::SafeRelease(old);
			message->registered = true;
		}
	}
#endif

	// FUNCTION: ENGINE 0x10078740
	void TendrilBehaviour::OnDeregister(DeregisterTendrilActionMessage* message)
	{
		fightitems::motion::AbstractTendrilAction* action = message->action;
		if (action != 0)
		{
			if (firstAction == action)
			{
				if (action->nextTendril != 0)
				{
					core::RefAssign(firstAction, action->nextTendril);
					core::SafeRelease(message->action->nextTendril->previousTendril);
					core::SafeRelease(message->action->nextTendril);
					return;
				}
				core::SafeRelease(firstAction);
				return;
			}
			if (message->action->nextTendril == 0)
			{
				core::SafeRelease(action->previousTendril->nextTendril);
				core::SafeRelease(message->action->previousTendril);
				return;
			}
			core::RefAssign(action->previousTendril->nextTendril, action->nextTendril);
			core::RefAssign(message->action->nextTendril->previousTendril, message->action->previousTendril);
			core::SafeRelease(message->action->nextTendril);
			core::SafeRelease(message->action->previousTendril);
		}
	}

	// FUNCTION: ENGINE 0x10078870
	void TendrilBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 2:
			return;
		case 0x1e:
			switch ((unsigned short)message->id)
			{
			case 0x22:
				OnRegister(static_cast<RegisterTendrilActionMessage*>(message));
				break;
			case 0x23:
				OnDeregister(static_cast<DeregisterTendrilActionMessage*>(message));
				break;
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x10078940
	TendrilBehaviour::~TendrilBehaviour()
	{
		while (firstAction != 0)
		{
			DeregisterTendrilActionMessage message(firstAction);
			OnDeregister(&message);
		}
	}

	// FUNCTION: ENGINE 0x10078480
	content::ClassInfo* TendrilBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TendrilBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x100788C0
	content::MemberList* TendrilBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, TendrilBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10078640
// FUNCTION: ENGINE 0x10078650

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100789C0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10078400
// FUNCTION: ENGINE 0x10078430
// FUNCTION: ENGINE 0x10078440
// FUNCTION: ENGINE 0x10078580
// FUNCTION: ENGINE 0x100785C0
// FUNCTION: ENGINE 0x100785E0
// FUNCTION: ENGINE 0x10078610
