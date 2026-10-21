// engine::PropLogicTreeBehaviour: see the header.
#include "code/engine/fight/behaviours/proplogictreebehaviour.h"
#include "code/core/heap.h"

namespace engine
{
	extern const char* gPropLogicContextName;

	// 0x10921560 (constructor, kept copy) and 0x10921570 (IsDerived): the caster the class meta type of
	// engine::FightTreeBehaviour carries for engine::PropLogicTreeBehaviour, kept out of line by an explicit instantiation.
	template struct content::BaseClassCasterImpl<FightTreeBehaviour, PropLogicTreeBehaviour>;

	// FUNCTION: ENGINE 0x10921440
	content::ClassInfo* PropLogicTreeBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::PropLogicTreeBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x109214F0
	PropLogicTreeBehaviour::PropLogicTreeBehaviour(GameObject* newOwner) : FightTreeBehaviour(newOwner, 0)
	{
		Listen(0xb, true);
		Listen(0x14, true);
		Listen(0x17, true);
		const char* contextName = gPropLogicContextName;
		fight::Sequencer* sequencer = GetSequencer();
		sequencer->SetContextName(contextName);
	}

	// FUNCTION: ENGINE 0x10921480
	void PropLogicTreeBehaviour::Update(float dt, unsigned short mask)
	{
		if (sequencer.Unknown105A45A0(true))
		{
			core::HeapScope scope(0x75);
			sequencer.Advance(1, dt);
			sequencer.Update(0);
			sequencer.Unknown105A4910(true);
		}
		else
		{
			Listen2(4, false);
		}
	}

	// FUNCTION: ENGINE 0x109215C0
	content::MemberList* PropLogicTreeBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<FightTreeBehaviour>();
		static content::BaseClassCasterImpl<FightTreeBehaviour, PropLogicTreeBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}
