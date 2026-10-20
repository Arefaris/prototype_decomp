// content::StringMetaType: the string meta type's slots (unit 0x10600FB0 - 0x10601450).
#include "code/content/stringmetatype.h"
#include "code/core/heap.h"
#include "code/core/textconvert.h"
#include <new>
#include <string.h>

namespace content
{
	// The heap the meta system makes its values in (0x11276928, name guessed)
	extern int gMetaHeap;

	// FUNCTION: ENGINE 0x10600FB0
	const char* GetStringTypeName()
	{
		return "string";
	}

	// FUNCTION: ENGINE 0x10600FC0
	StringMetaType::StringMetaType(int newCapacity, const char* code)
		: MetaType(code)
	{
		capacity = newCapacity;
	}

	// FUNCTION: ENGINE 0x10600FE0
	void StringMetaType::ReadBinary(ReadContext* context, void* object, int a, int b)
	{
		char buffer[0x400];
		int length;
		context->reader->Read(&length, 1, 4);
		context->reader->Read(buffer, length, 1);
		buffer[length] = 0;
		SetResolved(object, buffer, a);
	}

	// FUNCTION: ENGINE 0x10601050
	void StringMetaType::WriteBinary(WriteContext* context, const void* object, int a)
	{
		const char* text = Get(object);
		int length = strlen(text);
		context->writer->Write(&length, 1, 4);
		if (length != 0)
		{
			context->writer->Write(text, length, 1);
		}
	}

	// FUNCTION: ENGINE 0x106010A0
	bool StringMetaType::ReadText(TextReadStream* reader, void* object, int a, int b)
	{
		char buffer[0x400];
		if (!reader->ReadToken(buffer, capacity, true))
		{
			reader->Error("Expecting a quoted \"\" string at line %d", reader->GetLine());
			return false;
		}
		SetResolved(object, buffer, a);
		return true;
	}

	// FUNCTION: ENGINE 0x10601120
	void StringMetaType::WriteText(TextWriter* writer, const void* object, int a)
	{
		const char* text = Get(object);
		writer->Write(text, true);
	}

	// FUNCTION: ENGINE 0x10601140
	bool StringMetaType::Compare(ReadContext* first, const char* firstName, ReadContext* second,
		const char* secondName, int unused, TextWriter* log)
	{
		char a[0x100] = { 0 };
		char b[0x100] = { 0 };
		if (first != 0)
		{
			int length;
			first->reader->Read(&length, 1, 4);
			first->reader->Read(a, length, 1);
			a[length] = 0;
		}
		if (second != 0)
		{
			int length;
			second->reader->Read(&length, 1, 4);
			second->reader->Read(b, length, 1);
			b[length] = 0;
		}
		if (strcmp(a, b) == 0)
		{
			log->Write(a, true);
			return true;
		}
		if (first != 0)
		{
			log->NewLine();
			log->Write("*******************", false);
			log->Write(firstName, false);
			log->NewLine();
			log->Write(a, true);
		}
		if (second != 0)
		{
			log->NewLine();
			log->Write("*******************", false);
			log->Write(secondName, false);
			log->NewLine();
			log->Write(b, true);
		}
		log->NewLine();
		log->Write("*******************", false);
		log->NewLine();
		return false;
	}

	// FUNCTION: ENGINE 0x10601300
	const char* StringMetaType::Get(const void* object)
	{
		return (const char*)object;
	}

	// FUNCTION: ENGINE 0x10601310
	void StringMetaType::Set(void* object, const char* value)
	{
		core::AsciiCopy((char*)object, value, capacity);
	}

	// FUNCTION: ENGINE 0x10601330
	void StringMetaType::SetResolved(void* object, const char* value, int unused)
	{
		Set(object, value);
	}

	// FUNCTION: ENGINE 0x10601350
	void* StringMetaType::Create()
	{
		core::HeapScope scope(gMetaHeap);
		char* text = new char[capacity];
		*text = 0;
		return text;
	}

	// FUNCTION: ENGINE 0x10601390
	void StringMetaType::Destroy(void* object)
	{
		delete[] (char*)object;
	}

	// FUNCTION: ENGINE 0x106013A0
	void StringMetaType::Copy(void* destination, const void* source, int a)
	{
		Set(destination, Get(source));
	}

	// FUNCTION: ENGINE 0x106013D0
	int StringMetaType::Unknown9(int a, int b)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x106013E0
	void StringMetaType::Describe(MemberEntry** cursor, void* object, int unused)
	{
		(*cursor)->type = this;
		(*cursor)->object = object;
		*cursor += 1;
	}

	// FUNCTION: ENGINE 0x10601400
	void StringMetaType::WriteBinaryShort(WriteContext* context, const void* object)
	{
		const char* text = Get(object);
		int length = strlen(text);
		context->writer->Write(&length, 1, 4);
		if (length != 0)
		{
			context->writer->Write(text, length, 1);
		}
	}
}
