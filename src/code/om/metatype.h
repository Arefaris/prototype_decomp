// The type descriptions of the om library (RTTI: om::MetaTypeBase): one object per reflected type, found by the
// type_info of the type and cached by the users in a static of their own. Slots 1 to 4 read and write a value as
// text and in binary form (a pointer to the value is the second argument).
#ifndef OM_METATYPE_H
#define OM_METATYPE_H

#include <typeinfo>

namespace om
{
	class TextValue;
	// The buffer a binary stream reads from and writes to (0x105B7BC0 and 0x105B7C00; names guessed)
	class StreamBuffer
	{
	public:
		bool Read(void* data, int size);
		bool Write(const void* data, int size);
	};

	// A stream of values in their binary form
	class BinaryStream
	{
	public:
		StreamBuffer* buffer;
	};

	class MetaTypeBase
	{
	public:
		virtual ~MetaTypeBase();
		virtual bool ReadText(const TextValue* text, void* value) = 0;
		virtual void WriteText(TextValue* text, const void* value) = 0;
		virtual bool ReadBinary(BinaryStream* stream, void* value) = 0;
		virtual void WriteBinary(BinaryStream* stream, const void* value) = 0;
	};

	// 0x105B6FF0: the description registered for the type, null when there is none
	MetaTypeBase* FindMetaType(const type_info& type);

	// The static in which the users of a reflected type keep what FindMetaType answered for it (the engine has one
	// such word per type, shared by all the users)
	template<class T> struct MetaTypeCache
	{
		static MetaTypeBase* type;
	};
}

#endif
