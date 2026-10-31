// The reflection of the values the engine's property nodes carry (RTTI: om::MetaSimpleType<T>): the description of a type
// that is read and written as one value, in text and in binary form, through the library's functions for the type. The
// packets of the mgraph library and the arrays of their values are described this way.
#ifndef OM_METASIMPLETYPE_H
#define OM_METASIMPLETYPE_H

#include "code/om/allocation.h"
#include "code/om/metaproperty.h"
#include "code/om/metatype.h"
#include "code/om/textvalue.h"

namespace om
{
	// The forms of a value, called without a qualifier so that the friend functions of the arrays are found as well
	template<class V> inline bool ReadTextOf(const TextValue* text, V* value)
	{
		return ReadText(text, value);
	}
	template<class V> inline void WriteTextOf(TextValue* text, const V& value)
	{
		WriteText(text, value);
	}
	template<class V> inline bool ReadBinaryOf(BinaryStream* stream, V* value)
	{
		return ReadBinary(stream, value);
	}
	template<class V> inline bool WriteBinaryOf(BinaryStream* stream, const V& value)
	{
		return WriteBinary(stream, value);
	}

	template<class T> class MetaSimpleType : public MetaTypeBase
	{
	public:
		MetaSimpleType(const ClassName& newName) :
			MetaTypeBase(newName, &typeid(T))
		{
		}
		virtual ~MetaSimpleType()
		{
		}
		virtual bool ReadText(const TextValue* text, void* value);
		virtual void WriteText(TextValue* text, const void* value);
		virtual bool ReadBinary(BinaryStream* stream, void* value);
		virtual bool WriteBinary(BinaryStream* stream, const void* value);
		virtual int Slot5()
		{
			return 0;
		}
		virtual void Slot6(void* unknown)
		{
		}
		virtual const type_info* GetType()
		{
			return &typeid(T);
		}
		OM_ALLOCATION(MetaSimpleType);
	};

	template<class T> const char* MetaSimpleType<T>::AllocationTag()
	{
		return "";
	}

	template<class T> bool MetaSimpleType<T>::ReadText(const TextValue* text, void* value)
	{
		return ReadTextOf(text, static_cast<T*>(value));
	}

	template<class T> void MetaSimpleType<T>::WriteText(TextValue* text, const void* value)
	{
		WriteTextOf(text, *static_cast<const T*>(value));
	}

	template<class T> bool MetaSimpleType<T>::ReadBinary(BinaryStream* stream, void* value)
	{
		return ReadBinaryOf(stream, static_cast<T*>(value));
	}

	template<class T> bool MetaSimpleType<T>::WriteBinary(BinaryStream* stream, const void* value)
	{
		return WriteBinaryOf(stream, *static_cast<const T*>(value));
	}
}

#endif
