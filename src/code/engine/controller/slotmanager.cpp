// The slot table the InputSystem builds on (code/engine/controller/slotmanager.cpp; the file name is a guess, the unit
// starts at 0x108A1A00). Names are guesses.
#include "code/engine/controller/inputsystem.h"
#include <new>

namespace engine
{
	namespace controller
	{
		// FUNCTION: ENGINE 0x108A1A20
		SlotManager::~SlotManager()
		{
			delete[] slots;
		}

		// FUNCTION: ENGINE 0x108A1CA0
		SlotManager::SlotManager(int count)
			: capacity(count)
		{
			slots = new Slot[count];
		}

		// FUNCTION: ENGINE 0x108A1C40
		void SlotManager::AssignSlot(int index, unsigned int id)
		{
			slots[index].id = id;
		}

		// FUNCTION: ENGINE 0x108A1AF0
		// NONMATCHING: the engine places the block that takes the free slot right behind the search loop and tests the slot for -1 behind it (30 %)
#ifdef NONMATCHING
		void SlotManager::ReleaseSlot(unsigned int id, int slot)
		{
			if (slot < -2 || slot >= capacity)
			{
				return;
			}
			if (id != 0xffffffff)
			{
				int found = FindSlot(id);
				if (found == slot)
				{
					return;
				}
				int target = slot;
				if (found >= 0)
				{
					if (slot == -2)
					{
						return;
					}
				}
				else if (slot == -2)
				{
					int index = 0;
					for (; index < capacity; index++)
					{
						if (slots[index].id == 0xffffffff)
						{
							target = index;
							goto check;
						}
					}
					goto assign;
				}
			check:
				if (target != -1)
				{
				assign:
					if (slots[target].id == 0xffffffff)
					{
						if (found >= 0)
						{
							AssignSlot(found, 0xffffffff);
							CountSlots();
							Notify(slots[found].id, found);
						}
						AssignSlot(target, id);
						CountSlots();
						Notify(slots[target].id, target);
						return;
					}
					Notify(slots[target].id, target);
					return;
				}
				if (found >= 0)
				{
					AssignSlot(found, 0xffffffff);
					CountSlots();
					Notify(slots[found].id, found);
				}
				return;
			}
			if (slot < 0)
			{
				return;
			}
			AssignSlot(slot, 0xffffffff);
			CountSlots();
			Notify(slots[slot].id, slot);
		}
#endif

		// FUNCTION: ENGINE 0x108A1A10
		SlotManager::Slot::Slot()
			: id(0xffffffff)
		{
		}

		// FUNCTION: ENGINE 0x108A1A50
		int SlotManager::FindSlot(unsigned int id)
		{
			int index = 0;
			if (0 < capacity)
			{
				Slot* slot = slots;
				do
				{
					if (slot->id == id)
					{
						return index;
					}
					index++;
					slot++;
				}
				while (index < capacity);
			}
			return -1;
		}

		// FUNCTION: ENGINE 0x108A1A80
		void SlotManager::CountSlots()
		{
			slotCount = 0;
			for (int index = 0; index < capacity; index++)
			{
				if (slots[index].id != 0xffffffff)
				{
					slotCount++;
				}
			}
		}

		// FUNCTION: ENGINE 0x108A1AB0
		// NONMATCHING: the engine passes the empty id from a register it fills before the loop (61.5 %)
#ifdef NONMATCHING
		void SlotManager::ResetSlots()
		{
			unsigned int none = 0xffffffff;
			for (int index = 0; index < capacity; index++)
			{
				AssignSlot(index, none);
			}
			slotCount = 0;
		}

#endif
		// FUNCTION: ENGINE 0x108A1C60
		// NONMATCHING: the engine loads the slot's id as a word and shifts it where ours reads the byte, and keeps the empty id in a register (33.3 %)
#ifdef NONMATCHING
		void SlotManager::ReleaseSlotsOfKind(unsigned int kind)
		{
			for (int index = 0; index < capacity; index++)
			{
				unsigned int id = slots[index].id;
				if (((id >> 8) & 0xff) == kind)
				{
					AssignSlot(index, 0xffffffff);
				}
			}
		}
#endif
	}
}
