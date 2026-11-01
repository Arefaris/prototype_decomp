// The slot table the InputSystem builds on (code/engine/controller/slotmanager.cpp; the file name is a guess, the unit
// starts at 0x108A1A00). Names are guesses.
#include "code/engine/controller/inputsystem.h"

namespace engine
{
	namespace controller
	{
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
