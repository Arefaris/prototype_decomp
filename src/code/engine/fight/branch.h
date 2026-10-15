// fight::Branch (RTTI name, 18 vftable slots, vtable 0x10E2C294; bases fight::Entity, content::LoadObject,
// core::IRefCount and fight::Param): the branch of a fight tree a behaviour runs. Its unit is not this one, so only
// the slots and the members the behaviours touch are named. A behaviour keeps the branch as the node of the branch's
// listener list (the node's payload at +0, its links behind), which is why Register / Unregister take its address.
#ifndef ENGINE_FIGHT_BRANCH_H
#define ENGINE_FIGHT_BRANCH_H

#include "code/core/name.h"

namespace core
{
	struct IRefCount;
	struct CaseSensitiveKey;
}

namespace engine
{
	class GameObject;
}

namespace fight
{
	class Sequencer;

	class Branch
	{
	public:
		virtual void Slot0();
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot5();
		// 0x10863B00 / 0x10863FB0 read it: the track the branch runs (its own kind, so the two can be compared and
		// its own name asked for)
		virtual Branch* Slot6();
		virtual void Slot7();
		virtual void Slot8();
		virtual void Slot9();
		// 0x10863FB0: runs the branch on a sequencer with parameters, answering the track it started (or null)
		virtual Branch* Slot10(Sequencer* sequencer, void* params, int a, int b);
		// 0x10863FB0: starts that track, answering whether it began
		virtual bool Slot11(Sequencer* sequencer, void* params, int a);
		// 0x105A4780 (the sequencer's unit) starts a pending track through it
		virtual void Slot12(int a, core::IRefCount* b, Sequencer* sequencer);
		virtual void Slot13();
		virtual void Slot14();
		virtual void Slot15();
		virtual void Slot16();
		virtual void Slot17();

		// 0x105A3A40 / 0x105A3A90 (the sequencer's unit): enters the branch's listener list / leaves it
		void Register(void* entry);
		void Unregister(void* entry);

		// The reference count of the load object the branch derives from
		int unknown4;
		// 0x10863FB0 compares it with the running track's name
		core::Name<core::CaseSensitiveKey> name;
		int unknown10;
		int unknown14;
		// 0x10863B00 walks the chain through it
		Branch* unknown18;
	};
}

#endif
