// fight::Branch (RTTI name, 18 vftable slots, vtable 0x10E2C294; bases fight::Entity, content::LoadObject,
// core::IRefCount and fight::Param): the branch of a fight tree a behaviour runs. Its unit is not this one, so only
// the slots and the members the behaviours touch are named. A behaviour keeps the branch as the node of the branch's
// listener list (the node's payload at +0, its links behind), which is why Register / Unregister take its address.
#ifndef ENGINE_FIGHT_BRANCH_H
#define ENGINE_FIGHT_BRANCH_H

namespace engine
{
	class GameObject;
}

namespace fight
{
	class Branch
	{
	public:
		virtual void Slot0();
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot5();
		// 0x10863B00 / 0x10863FB0 read it: the track the branch runs
		virtual void* Slot6();
		virtual void Slot7();
		virtual void Slot8();
		virtual void Slot9();
		virtual void Slot10();
		virtual void Slot11();
		virtual void Slot12();
		virtual void Slot13();
		virtual void Slot14();
		virtual void Slot15();
		virtual void Slot16();
		virtual void Slot17();

		// 0x105A3A40 / 0x105A3A90 (the sequencer's unit): enters the branch's listener list / leaves it
		void Register(void* entry);
		void Unregister(void* entry);
	};
}

#endif
