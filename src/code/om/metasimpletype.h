// The reflection of the values the engine's property nodes carry (RTTI: om::MetaSimpleType<T>): the description of a type
// that is read and written as one value, in text and in binary form, through the library's functions for the type. The
// packets of the mgraph library and the arrays of their values are described this way.
#ifndef OM_METASIMPLETYPE_H
#define OM_METASIMPLETYPE_H

#include "code/om/allocation.h"
#include "code/om/metatype.h"
#include "code/om/textvalue.h"

namespace om
{
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
		return om::ReadText(text, static_cast<T*>(value));
	}

	template<class T> void MetaSimpleType<T>::WriteText(TextValue* text, const void* value)
	{
		om::WriteText(text, *static_cast<const T*>(value));
	}

	template<class T> bool MetaSimpleType<T>::ReadBinary(BinaryStream* stream, void* value)
	{
		return om::ReadBinary(stream, static_cast<T*>(value));
	}

	template<class T> bool MetaSimpleType<T>::WriteBinary(BinaryStream* stream, const void* value)
	{
		return om::WriteBinary(stream, *static_cast<const T*>(value));
	}
}

#endif
