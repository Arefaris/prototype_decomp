// The property of a bit mask member of a fight node: a value picked from a table of named bits (RTTI:
// fight::PropertyTypeBitfield, 10 vftable slots, and the template fight::PropertyBitfield<T>). The table is not the
// property's own: the class gives two member functions that answer an entry and the count.
#ifndef ENGINE_FIGHT_BITFIELDPROPERTY_H
#define ENGINE_FIGHT_BITFIELDPROPERTY_H

#include "code/engine/fight/trackfactory.h"

namespace fight
{
	class PropertyTypeBitfield : public Property
	{
	public:
		// 0x105A92B0
		PropertyTypeBitfield(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		// vftable slot 6 (0x105A92D0)
		virtual bool Slot6(int a, int b, void* object);
		// vftable slot 7: the entry of a bit
		virtual const EnumEntry* GetEntry(void* object, int index) = 0;
		// vftable slot 8
		virtual int GetCount(void* object) const = 0;
		// vftable slot 9
		virtual bool Set(void* object, int value) = 0;
	};

	template<class T> class PropertyBitfield : public PropertyTypeBitfield
	{
	public:
		typedef bool (T::*Setter)(int);
		typedef const EnumEntry* (T::*EntryFunction)(int);
		typedef int (T::*CountFunction)();

		PropertyBitfield(const char* name, EntryFunction entry, CountFunction count, Setter setter)
			: PropertyTypeBitfield(name), m_setter(setter), m_entry(entry), m_count(count)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return m_setter == 0;
		}

		// vftable slot 7
		virtual const EnumEntry* GetEntry(void* object, int index)
		{
			return (static_cast<T*>(object)->*m_entry)(index);
		}

		// vftable slot 8
		virtual int GetCount(void* object) const
		{
			return (static_cast<T*>(object)->*m_count)();
		}

		// vftable slot 9
		virtual bool Set(void* object, int value)
		{
			if (m_setter == 0)
			{
				return false;
			}
			return (static_cast<T*>(object)->*m_setter)(value);
		}

		Setter m_setter;
		EntryFunction m_entry;
		CountFunction m_count;
	};
}

#endif
