// content::EnumMetaType: the slots of the enumeration meta type (unit 0x105FE7C0 - 0x105FEBB0; the file name is
// guessed).
#include "code/content/metatype.h"
#include "code/content/enummetatype.h"
#include "code/core/heap.h"
#include "code/core/strings.h"

namespace content
{
	// The heap the meta system makes its values in (0x11276928, name guessed)
	extern int gMetaHeap;

	// FUNCTION: ENGINE 0x105FE7B0
	const char* GetEnumTypeName()
	{
		return "enum";
	}

	// FUNCTION: ENGINE 0x105FE7C0
	EnumMetaType::EnumMetaType(const char* name, int version, const char* code, const EnumValue* newValues,
		int newCount)
		: NamedMetaType(name, (unsigned short)version, code)
	{
		values = newValues;
		count = newCount;
	}

	// FUNCTION: ENGINE 0x105FE800
	void EnumMetaType::ReadBinary(ReadContext* context, void* object, int a, int b)
	{
		int value;
		context->reader->Read(&value, 1, 4);
		Set(object, value);
	}

	// FUNCTION: ENGINE 0x105FE830
	void EnumMetaType::WriteBinary(WriteContext* context, const void* object, int a)
	{
		int value = Get(object);
		context->writer->Write(&value, 1, 4);
	}

	// FUNCTION: ENGINE 0x105FE860
	bool EnumMetaType::ReadText(TextReadStream* reader, void* object, int a, int b)
	{
		char text[0x100];
		if (!reader->ReadToken(text, 0x100, false))
		{
			reader->Error("Expecting enumeration token at line %d", reader->GetLine());
			return false;
		}
		for (unsigned int i = 0; i < count; i++)
		{
			if (core::StrCmp(values[i].name, text) == 0)
			{
				Set(object, values[i].value);
				return true;
			}
		}
		reader->Error("Invalid enumeration token \"%s\" at line %d", text, reader->GetLine());
		return false;
	}

	// FUNCTION: ENGINE 0x105FE930
	void EnumMetaType::WriteText(TextWriter* writer, const void* object, int a)
	{
		int value = Get(object);
		for (unsigned int i = 0; i < count; i++)
		{
			if (values[i].value == value)
			{
				writer->Write(values[i].name, false);
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x105FE980
	bool EnumMetaType::Compare(ReadContext* first, const char* firstName, ReadContext* second,
		const char* secondName, int unused, TextWriter* log)
	{
		int firstValue = 0;
		int secondValue = 1;
		if (first != 0)
		{
			first->reader->Read(&firstValue, 1, 4);
		}
		if (second != 0)
		{
			second->reader->Read(&secondValue, 1, 4);
		}
		if (firstValue == secondValue)
		{
			log->WriteInt(&firstValue);
			return true;
		}
		if (first != 0)
		{
			log->NewLine();
			log->Write("*******************", false);
			log->Write(firstName, false);
			log->NewLine();
			log->WriteInt(&firstValue);
		}
		if (second != 0)
		{
			log->NewLine();
			log->Write("*******************", false);
			log->Write(secondName, false);
			log->NewLine();
			log->WriteInt(&secondValue);
		}
		log->NewLine();
		log->Write("*******************", false);
		log->NewLine();
		return false;
	}

	// FUNCTION: ENGINE 0x105FEA90
	int EnumMetaType::Get(const void* object)
	{
		return *(const int*)object;
	}

	// FUNCTION: ENGINE 0x105FEAA0
	void EnumMetaType::Set(void* object, int value)
	{
		*(int*)object = value;
	}

	// FUNCTION: ENGINE 0x105FEAB0
	int EnumMetaType::GetDefault()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x105FEAC0
	void* EnumMetaType::Create()
	{
		core::HeapScope scope(gMetaHeap);
		return new int(GetDefault());
	}

	// FUNCTION: ENGINE 0x105FEB10
	void EnumMetaType::Destroy(void* object)
	{
		operator delete(object);
	}

	// FUNCTION: ENGINE 0x105FEB20
	void EnumMetaType::Copy(void* destination, const void* source, int a)
	{
		Set(destination, Get(source));
	}

	// FUNCTION: ENGINE 0x105FEB50
	int EnumMetaType::Unknown9(int a, int b)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x105FEB60
	void EnumMetaType::Describe(MemberEntry** cursor, void* object, int unused)
	{
		(*cursor)->type = this;
		(*cursor)->object = object;
		*cursor += 1;
	}

	// FUNCTION: ENGINE 0x105FEB80
	void EnumMetaType::WriteBinaryShort(WriteContext* context, const void* object)
	{
		int value = Get(object);
		context->writer->Write(&value, 1, 4);
	}
}
