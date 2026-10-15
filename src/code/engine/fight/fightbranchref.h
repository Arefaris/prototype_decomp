// The reflection of a fight branch: a fight::Branch* member reached through a getter and a setter of its class
// (RTTI: engine::FightBranchRefMetaTypeGetSetter, 2 vftable slots, and the template
// engine::FightBranchRefMemberGetSetter<class C> derived from it). Every behaviour that runs a fight tree
// instantiates the template for itself; engine::FightBranchRefMetaType / ...GetSet are its meta types in the load
// inventory. Only what the behaviours use is reconstructed here.
#ifndef ENGINE_FIGHT_FIGHTBRANCHREF_H
#define ENGINE_FIGHT_FIGHTBRANCHREF_H

#include "code/engine/fight/branch.h"

namespace engine
{
	// Reads and writes a branch reference through the accessors of its class (RTTI: a struct)
	struct FightBranchRefMetaTypeGetSetter
	{
	public:
		virtual fight::Branch* Get(const void* object) = 0;
		virtual void Set(void* object, fight::Branch* value) = 0;
	};

	// A branch member of class C reached through a getter and a setter (RTTI: engine::FightBranchRefMemberGetSetter)
	template<class C> class FightBranchRefMemberGetSetter : public FightBranchRefMetaTypeGetSetter
	{
	public:
		typedef fight::Branch* (C::*Getter)() const;
		typedef void (C::*Setter)(fight::Branch*);

		FightBranchRefMemberGetSetter(Getter newGetter, Setter newSetter)
		{
			getter = newGetter;
			setter = newSetter;
		}

		virtual fight::Branch* Get(const void* object)
		{
			return (((const C*)object)->*getter)();
		}
		virtual void Set(void* object, fight::Branch* value)
		{
			(((C*)object)->*setter)(value);
		}

		Getter getter;
		Setter setter;
	};
}

#endif
