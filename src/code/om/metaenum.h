// The enumeration reflection of the om library (RTTI: om::MetaEnumBase, MetaEnum<E>): the description of an
// enumeration with the names of its values. The base keeps the names; an instance reads and writes a value of E as
// an int.
#ifndef OM_METAENUM_H
#define OM_METAENUM_H

#include "code/om/allocation.h"
#include "code/om/metaproperty.h"

namespace om
{
	// A name of the enumeration and its value (the value is at +0x20 of the node)
	struct EnumValue
	{
		char node[0x20];
		int value;
	};

	class MetaEnumBase : public MetaTypeBase
	{
	public:
		// 0x105EB8C0 / 0x105EBC70 (the deleting destructor is 0x105EBCD0)
		MetaEnumBase(const ClassName& newName, const type_info* newType);
		virtual ~MetaEnumBase();
		// 0x105EBCB0: the entry of a name, null when there is none
		const EnumValue* FindValue(const ClassName& valueName);
		// 0x105EB9D0: the name of a value, passed on to the text writer of the library
		void WriteValueName(int value);

		TreeHead names;  // 0x38
		TreeHead values;  // 0x4C
	};

	// The value of a stream as an int (0x105B7EB0 / 0x105B7ED0, names guessed)
	bool ReadInt(BinaryStream* stream, int* value);
	void WriteInt(BinaryStream* stream, int value);

	template<class E> class MetaEnum : public MetaEnumBase
	{
	public:
		MetaEnum(const ClassName& newName) :
			MetaEnumBase(newName, &typeid(E))
		{
		}
		virtual ~MetaEnum()
		{
		}
		virtual bool ReadText(const TextValue* text, void* value);
		virtual void WriteText(TextValue* text, const void* value);
		virtual bool ReadBinary(BinaryStream* stream, void* value);
		virtual void WriteBinary(BinaryStream* stream, const void* value);
		virtual int Slot5()
		{
			return 0;
		}
		virtual void Slot6(void* unknown)
		{
		}
		virtual const type_info* GetType()
		{
			return &typeid(E);
		}
		OM_ALLOCATION(MetaEnum);
	};

	template<class E> const char* MetaEnum<E>::AllocationTag()
	{
		return "";
	}

	template<class E> bool MetaEnum<E>::ReadText(const TextValue* text, void* value)
	{
		ClassName valueName;
		bool ok = om::ReadText(text, &valueName);
		const EnumValue* entry = FindValue(valueName);
		if (entry != 0)
		{
			*static_cast<int*>(value) = entry->value;
		}
		return ok && entry != 0;
	}

	template<class E> void MetaEnum<E>::WriteText(TextValue* text, const void* value)
	{
		WriteValueName(*static_cast<const int*>(value));
	}

	template<class E> bool MetaEnum<E>::ReadBinary(BinaryStream* stream, void* value)
	{
		int number;
		bool ok = ReadInt(stream, &number);
		*static_cast<int*>(value) = number;
		return ok;
	}

	template<class E> void MetaEnum<E>::WriteBinary(BinaryStream* stream, const void* value)
	{
		int number = *static_cast<const int*>(value);
		WriteInt(stream, number);
	}
}

#endif
