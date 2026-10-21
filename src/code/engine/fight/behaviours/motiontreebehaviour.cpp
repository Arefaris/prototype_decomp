#include "code/engine/fight/behaviours/motiontreebehaviour.h"
#include "code/core/heap.h"

namespace engine
{
	// The context name of the motion tree (another unit)
	extern const char* gMotionContextName;

	// The messages the motion tree reads: a word of flags behind the base (types 0xb / 0xf)
	struct MotionTreeMessage : public Message
	{
		MotionTreeMessage(int newType, short newId) : Message(newType, newId)
		{
		}

		unsigned int value;  // +0xC
	};

	// FUNCTION: ENGINE 0x1091F380
	content::ClassInfo* MotionTreeBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "MotionTreeBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1091F3C0
	bool MotionTreeBehaviour::GetAutoResequence() const
	{
		return autoResequence;
	}

	// FUNCTION: ENGINE 0x1091F3D0
	// NONMATCHING: the engine keeps the sequencer test's result in a stack slot across the branch, 41.2 %
#ifdef NONMATCHING
	void MotionTreeBehaviour::UpdateListening()
	{
		bool listen = autoResequence || sequencer.Unknown105A45A0(true);
		Listen2(4, listen);
	}
#endif

	// FUNCTION: ENGINE 0x1091F400
	void MotionTreeBehaviour::OnMessage(Message* message)
	{
		MotionTreeMessage* motionMessage = static_cast<MotionTreeMessage*>(message);
		if (motionMessage->type != 0xb)
		{
			if (motionMessage->type == 0xf && motionMessage->id == 4)
			{
				pendingFlags |= 8;
				return;
			}
		}
		else
		{
			switch ((unsigned short)motionMessage->id)
			{
				case 0xd:
					pendingFlags |= motionMessage->value;
					break;
				case 0xf:
					sequencer.Reset();
					break;
			}
		}
		FightTreeBehaviour::OnMessage(message);
		UpdateListening();
	}

	// FUNCTION: ENGINE 0x1091F470
	void MotionTreeBehaviour::OnActiveChanged(bool active)
	{
		FightTreeBehaviour::OnActiveChanged(active);
	}

	// FUNCTION: ENGINE 0x1091F480
	MotionTreeBehaviour::MotionTreeBehaviour(GameObject* newOwner) : FightTreeBehaviour(newOwner, 0)
	{
		pendingFlags = 0;
		autoResequence = true;
		Listen2(4, true);
		const char* contextName = gMotionContextName;
		core::Name<core::CaseSensitiveKey>* contextNameMember = (core::Name<core::CaseSensitiveKey>*)GetSequencer();
		contextNameMember->SetText(contextName);
		Listen(0x17, true);
		Listen(0xf, true);
	}

	// FUNCTION: ENGINE 0x1091F550
	void MotionTreeBehaviour::SetAutoResequence(bool value)
	{
		autoResequence = value;
		UpdateListening();
	}

	// FUNCTION: ENGINE 0x1091F5B0
	void MotionTreeBehaviour::Update(float dt, unsigned short mask)
	{
		if (mask == 4)
		{
			core::HeapScope scope(0x75);
			GameObjectParams* currentParams = GetParams();
			if (pendingFlags != 0)
			{
				sequencer.Unknown105A4270(pendingFlags, GetParams());
				pendingFlags = 0;
			}
			sequencer.Update(1);
			sequencer.Unknown105A4910(true);
			if (IsActive())
			{
				if (autoResequence)
				{
					fight::Branch* current = branch;
					if (current != 0 && !sequencer.Unknown105A45A0(false))
					{
						fight::Branch* started = current->Slot10(GetSequencer(), currentParams, 0, 0);
						if (started != 0)
						{
							started->Slot11(GetSequencer(), currentParams, 0);
						}
					}
				}
				sequencer.Advance(2, dt);
				sequencer.Update(0);
				UpdateListening();
			}
		}
	}

	// FUNCTION: ENGINE 0x1091F6B0
	void MotionTreeBehaviour::OnPostedMessage(Message* message)
	{
		FightTreeMessage* fightMessage = static_cast<FightTreeMessage*>(message);
		if (fightMessage->type == 0xb && fightMessage->id == 0)
		{
			fightMessage->track = branch;
			return;
		}
		FightTreeBehaviour::OnPostedMessage(message);
	}

	// FUNCTION: ENGINE 0x1091F750
	content::MemberList* MotionTreeBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<FightTreeBehaviour>();
		static content::BaseClassCasterImpl<FightTreeBehaviour, MotionTreeBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberMetaType(&MotionTreeBehaviour::GetAutoResequence,
				&MotionTreeBehaviour::SetAutoResequence, "p"), 0, "autoResequence" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1091F4F0
// FUNCTION: ENGINE 0x1091F500
// FUNCTION: ENGINE 0x1091F560
// FUNCTION: ENGINE 0x1091F580
// FUNCTION: ENGINE 0x1091F590
// FUNCTION: ENGINE 0x1091F6E0
