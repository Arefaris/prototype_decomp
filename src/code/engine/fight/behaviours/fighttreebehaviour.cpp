// engine::FightTreeBehaviour: see the header. The unit has no name of its own in the binary; the debug dump of the
// tree carries the file path code/engine/fight/behaviours/fighttreebehaviour.cpp.
#include "code/engine/fight/behaviours/fighttreebehaviour.h"

#include "code/core/refptr.h"
#include "code/engine/fight/fightbranchref.h"
#include "code/engine/fight/playbackset.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/math/random.h"

namespace engine
{
	// 0x10863A80 (constructor, kept copy) and 0x10863A90 (IsDerived): the caster the class meta type of
	// engine::FightTreeBehaviour carries. The unit kept them out of line, which is what an explicit instantiation
	// makes the compiler do.
	template struct content::BaseClassCasterImpl<Behaviour, FightTreeBehaviour>;

	// FUNCTION: ENGINE 0x10863F40
	// FUNCTION: ENGINE 0x10863F60
	// FUNCTION: ENGINE 0x10863F70
	// The object the "fightBranch" member of the class meta type reads and writes the branch through, kept out of
	// line by its own instantiation.
	template class FightBranchRefMemberGetSetter<FightTreeBehaviour>;

	// FUNCTION: ENGINE 0x10864180
	// FUNCTION: ENGINE 0x108641E0
	content::MemberList* FightTreeBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, FightTreeBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ GetFightBranchRefMetaType<FightTreeBehaviour>("GameObject", &FightTreeBehaviour::GetBranch,
				&FightTreeBehaviour::SetBranch, "p"), 0, "fightBranch" },
			{ content::GetClassMetaType<fight::Sequencer>(),
				content::MemberOffset(&((FightTreeBehaviour*)0)->sequencer,
				(int)&((FightTreeBehaviour*)0)->sequencer), "sequencer" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x108638C0
	content::ClassInfo* FightTreeBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::FightTreeBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10863900
	// NONMATCHING: the parameters load and the generator step's registers, 54 %
#ifdef NONMATCHING
	void FightTreeBehaviour::Slot1()
	{
		params->handle = GetHandle(owner);
		math::gRandom->Next();
	}
#endif

	// FUNCTION: ENGINE 0x108639A0
	// NONMATCHING: the parameters load and the handle copy swap places, 89 %
#ifdef NONMATCHING
	GameObjectParams* FightTreeBehaviour::GetParams()
	{
		params->handle = GetHandle(owner);
		return params;
	}
#endif

	// FUNCTION: ENGINE 0x10863950
	void FightTreeBehaviour::OnActiveChanged(bool active)
	{
		Behaviour::OnActiveChanged(active);
		if (!active)
		{
			sequencer.EndPending();
		}
	}

	// FUNCTION: ENGINE 0x10863970
	fight::Sequencer* FightTreeBehaviour::GetSequencer()
	{
		return &sequencer;
	}

	// FUNCTION: ENGINE 0x10863980
	const fight::Sequencer* FightTreeBehaviour::GetSequencer() const
	{
		return &sequencer;
	}

	// FUNCTION: ENGINE 0x108639E0
	// NONMATCHING: the vtable store and the sequencer's `this` swap places, 97 %
#ifdef NONMATCHING
	FightTreeBehaviour::FightTreeBehaviour(GameObject* newOwner, GameObjectParams* newParams) :
		Behaviour(newOwner),
		branch(0),
		unknown10(0),
		unknown14(0)
	{
		params = 0;
		Listen(0xb, true);
		Listen(2, true);
		if (newParams == 0)
		{
			newParams = new GameObjectParams(0x10001);
		}
		core::RefAssign(params, newParams);
	}
#endif

	// FUNCTION: ENGINE 0x10863AC0
	FightTreeBehaviour::~FightTreeBehaviour()
	{
		core::SafeRelease(params);
		sequencer.End();
		if (branch != 0)
		{
			branch->Unregister(&branch);
		}
	}

	// FUNCTION: ENGINE 0x10863B90
	fight::Branch* FightTreeBehaviour::GetBranch() const
	{
		return branch;
	}

	// FUNCTION: ENGINE 0x10863BA0
	void FightTreeBehaviour::SetBranch(fight::Branch* newBranch)
	{
		if (newBranch != branch)
		{
			if (branch != 0)
			{
				branch->Unregister(&branch);
			}
			branch = newBranch;
			if (newBranch != 0)
			{
				newBranch->Register(&branch);
			}
		}
		PlaybackSet* set = dynamic_cast<PlaybackSet*>(newBranch);
		if (set != 0)
		{
			set->SetOwner(owner);
		}
	}
}
