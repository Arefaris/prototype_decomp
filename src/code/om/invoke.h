// The typed call of a reflected method (slot 1 of om::MetaMethod1 and om::MetaMethod0Const): the call gets the
// arguments in binary form in one block of memory and leaves the result in binary form in another. Only the units
// that instantiate the Invoke slots include this (the other users of the method classes call the engine's copies).
#ifndef OM_INVOKE_H
#define OM_INVOKE_H

#include "code/om/delegate.h"
#include "code/om/memorystream.h"
#include "code/om/metamethod.h"

namespace om
{
	// The stream a result is written to, with the word that follows it in the frame (meaning unknown)
	struct BinaryOutput
	{
		BinaryOutput(StreamBuffer* buffer, StreamContext* context) : stream(buffer, context), unknown(0)
		{
		}

		BinaryStream stream;
		int unknown;
	};

	// A result in binary form: a name goes out as its 64-bit key followed by a zero byte (the engine's copy of the name's
	// writer is part of the method's Invoke); the other types by their own writer
	inline void WriteResult(BinaryStream* stream, const ClassName& name)
	{
		ClassName value = name;
		if (stream->buffer->Write(&value, 8))
		{
			char terminator = 0;
			stream->buffer->Write(&terminator, 1);
		}
	}

	template<class T> inline void WriteResult(BinaryStream* stream, const T& value)
	{
		WriteBinary(stream, value);
	}

	// An argument read from the stream into a value that the list deletes afterwards
	template<class V> V* ReadArgument(BinaryStream* stream, GarbageList* list)
	{
		V* value = new V();
		list->Add(new Garbage<V>(value));
		ReadBinary(stream, value);
		return value;
	}

	// What the call is given for an argument: a value read in place, or the object a reference refers to
	template<class A> struct ArgumentReader
	{
		static A Read(BinaryStream* stream, GarbageList* list)
		{
			A value;
			ReadBinary(stream, &value);
			return value;
		}
	};

	template<class T> struct ArgumentReader<const T&>
	{
		static const T& Read(BinaryStream* stream, GarbageList* list)
		{
			return *ReadArgument<T>(stream, list);
		}
	};

	template<class C, class B, class R, class A> void MetaMethod1<C, B, R, A>::Invoke(void* object, unsigned int a,
		unsigned int b, unsigned int c, unsigned int d)
	{
		MemoryStream input((void*)a, b, false);
		MemoryStream output((void*)c, d, true);
		StreamBuffer inputBuffer(&input, 1);
		StreamBuffer outputBuffer(&output, 1);
		StreamContext context;
		context.Set(GetStreamContextObject(), GetStreamContextObject(), GetStreamContextObject(),
			GetStreamContextObject());
		BinaryStream stream(&inputBuffer, &context);
		GarbageList list;
		(static_cast<C*>(object)->*function)(ArgumentReader<A>::Read(&stream, &list));
		list.DeleteAll();
	}

	template<class C, class B, class R> void MetaMethod0Const<C, B, R>::Invoke(void* object, unsigned int a,
		unsigned int b, unsigned int c, unsigned int d)
	{
		MemoryStream outputStream((void*)c, d, true);
		StreamBuffer outputBuffer(&outputStream, 1);
		StreamContext context;
		context.Set(GetStreamContextObject(), GetStreamContextObject(), GetStreamContextObject(),
			GetStreamContextObject());
		BinaryOutput output2(&outputBuffer, &context);
		WriteResult(&output2.stream, (static_cast<C*>(object)->*function)());
	}
}

#endif
