// The reflection of a fight branch: a fight::Branch* member reached through a getter and a setter of its class
// (RTTI: engine::FightBranchRefMetaTypeGetSetter, 2 vftable slots, and the template
// engine::FightBranchRefMemberGetSetter<class C> derived from it). Every behaviour that runs a fight tree
// instantiates the template for itself; engine::FightBranchRefMetaType / ...GetSet are its meta types in the load
// inventory. Only what the behaviours use is reconstructed here.
#ifndef ENGINE_FIGHT_FIGHTBRANCHREF_H
#define ENGINE_FIGHT_FIGHTBRANCHREF_H

#include "code/content/metatype.h"
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

	// The meta type of a branch reference member (RTTI names engine::FightBranchRefMetaType and
	// engine::FightBranchRefMetaTypeGetSet, its 14-slot derivation)
	class FightBranchRefMetaType : public content::MetaType
	{
	public:
		virtual void Slot0();
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot6();
		virtual void Slot7();
		virtual void Slot8();
		virtual void Slot9();
		virtual void Slot10();
		virtual void Slot11();
	};

	class FightBranchRefMetaTypeGetSet : public FightBranchRefMetaType
	{
	public:
		// 0x107FC2A0 (another unit): the code is the base meta type's
		FightBranchRefMetaTypeGetSet(FightBranchRefMetaTypeGetSetter* newGetSetter, const char* code);

		virtual void Slot12();
		virtual void Slot13();

		FightBranchRefMetaTypeGetSetter* getSetter;
	};

	// The meta type of the branch member of class C (the unit's own copy, 0x10864180 for the fight tree). The first
	// parameter is the class name the original passes and does not read.
	template<class C> content::MetaType* GetFightBranchRefMetaType(const char* unused,
		fight::Branch* (C::*getter)() const, void (C::*setter)(fight::Branch*), const char* code)
	{
		static FightBranchRefMemberGetSetter<C> sGetSetter(getter, setter);
		static FightBranchRefMetaTypeGetSet sType(&sGetSetter, code);
		return &sType;
	}
}

#endif
