#include "code/proto/behaviours/musictreebehaviour.h"
#include "code/core/heap.h"

namespace engine
{
	namespace driving
	{
		extern const float gZero;
	}
}

namespace proto
{
	// The messages the music tree reads: a word of flags behind the base (type 0xb, id 0xD)
	struct MusicTreeMessage : public engine::Message
	{
		MusicTreeMessage(int newType, short newId) : engine::Message(newType, newId)
		{
		}

		unsigned int value;  // +0xC
	};

	// FUNCTION: ENGINE 0x1049ACB0
	content::ClassInfo* MusicTreeBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::MusicTreeBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1049ACF0
	MusicTreeBehaviour::~MusicTreeBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x1049AD00
	void MusicTreeBehaviour::OnMessage(engine::Message* message)
	{
		MusicTreeMessage* musicMessage = static_cast<MusicTreeMessage*>(message);
		if (musicMessage->type == 0xb)
		{
			switch ((unsigned short)musicMessage->id)
			{
				case 0xd:
					pendingFlags |= musicMessage->value;
					break;
				case 2:
					if (musicMessage->value != 0)
					{
						FightTreeBehaviour::OnMessage(message);
					}
					break;
			}
		}
	}

	// FUNCTION: ENGINE 0x1049AD40
	void MusicTreeBehaviour::OnPostedMessage(engine::Message* message)
	{
	}

	// FUNCTION: ENGINE 0x1049AD50
	MusicTreeBehaviour::MusicTreeBehaviour(engine::GameObject* newOwner) : FightTreeBehaviour(newOwner, 0)
	{
		pendingFlags = 0;
		Listen2(4, true);
		core::Name<core::CaseSensitiveKey>* contextNameMember = (core::Name<core::CaseSensitiveKey>*)GetSequencer();
		contextNameMember->SetText("Music");
	}

	// FUNCTION: ENGINE 0x1049AE10
	content::MemberList* MusicTreeBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<FightTreeBehaviour>();
		static content::BaseClassCasterImpl<FightTreeBehaviour, MusicTreeBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1049AE90
	// NONMATCHING: the registers of the branch, its vftable slot and the parameters differ (ebx / edi / ebp), 53.7 %
#ifdef NONMATCHING
	void MusicTreeBehaviour::Update(float dt, unsigned short mask)
	{
		if (dt != engine::driving::gZero)
		{
			core::HeapScope scope(0x75);
			if (branch != 0 && !sequencer.Unknown105A45A0(true))
			{
				engine::GameObjectParams* currentParams = GetParams();
				fight::Branch* current = branch;
				fight::Branch* started = current->Slot10(GetSequencer(), currentParams, 0, 0);
				if (started != 0)
				{
					started->Slot11(&sequencer, currentParams, 0);
				}
			}
			if (pendingFlags != 0)
			{
				sequencer.Unknown105A4270(pendingFlags, GetParams());
				pendingFlags = 0;
			}
			sequencer.Advance(1, dt);
			sequencer.Update(0);
			sequencer.Unknown105A4910(true);
		}
	}
#endif
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1049ADA0
// FUNCTION: ENGINE 0x103C7B40
// FUNCTION: ENGINE 0x1049ADB0
// FUNCTION: ENGINE 0x1049ADE0
