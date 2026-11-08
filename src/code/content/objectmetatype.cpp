// content::ObjectMetaType: the meta type of a pointer to a reflected object (unit 0x10603820 - 0x10604310).
#include <string.h>

#include "code/content/metafactory.h"
#include "code/content/metatype.h"
#include "code/core/heap.h"

namespace content
{
	// The heap the meta system makes its values in (0x11276928, name guessed)
	extern int gMetaHeap;

	// The name a null object is written under (0x10E33054; the text writers of the unit use a literal of their own)
	extern const char gNullName[];
	const char gNullName[] = "NULL";

	// FUNCTION: ENGINE 0x10603820
	const char* GetObjectTypeName()
	{
		return "object";
	}

	// FUNCTION: ENGINE 0x10603830
	ObjectValue::ObjectValue()
	{
		type = 0;
		instance = 0;
	}

	// FUNCTION: ENGINE 0x10603840
	ObjectValue::~ObjectValue()
	{
		if (instance != 0 && type != 0)
		{
			((MetaTypeView*)type)->Destroy(instance);
		}
	}

	// FUNCTION: ENGINE 0x10603860
	ObjectMetaType::ObjectMetaType(MetaType* newType, MetaInstanceHelperBase* newHelper, const char* code)
		: MetaType(code)
	{
		type = static_cast<ClassMetaType*>(newType);
		helper = newHelper;
	}

	// FUNCTION: ENGINE 0x10603B00
	void ObjectMetaType::Clear(void* object)
	{
		if (!IsDirect(object))
		{
			void** pointer = (void**)object;
			if (*pointer != 0)
			{
				helper->Delete(*pointer);
				*pointer = 0;
			}
			return;
		}
		ObjectValue* value = (ObjectValue*)object;
		if (value->instance != 0 && value->type != 0)
		{
			((MetaTypeView*)value->type)->Destroy(value->instance);
			value->instance = 0;
			value->type = 0;
		}
	}

	// FUNCTION: ENGINE 0x10603B60
	ClassMetaType* ObjectMetaType::MakeInstance(void* object, const char* name, unsigned short version)
	{
		if (!IsDirect(object))
		{
			MetaInstanceCreator* creator = FindInstanceCreator(name, version);
			if (creator == 0)
			{
				return 0;
			}
			ClassMetaType* result = creator->GetType();
			*(void**)object = creator->Create();
			return result;
		}
		ObjectValue* value = (ObjectValue*)object;
		value->type = dynamic_cast<ClassMetaType*>(NamedMetaType::Find(name, version));
		if (value->type != 0)
		{
			core::HeapScope scope(gMetaHeap);
			value->instance = ((MetaTypeView*)value->type)->Create();
		}
		return value->type;
	}

	// FUNCTION: ENGINE 0x10603C10
	ClassMetaType* ObjectMetaType::GetValueType(void* object)
	{
		if (IsDirect(object))
		{
			return *(ClassMetaType**)object;
		}
		ClassMetaType* result = *(ClassMetaType**)object;
		if (result == 0)
		{
			return result;
		}
		return type->FindDerived(result);
	}

	// FUNCTION: ENGINE 0x10603C40
	const char* ObjectMetaType::GetValueName(void* object, unsigned short* version)
	{
		ClassMetaType* valueType = GetValueType(object);
		if (valueType == 0)
		{
			*version = 0;
			return gNullName;
		}
		*version = valueType->GetVersion();
		return valueType->GetName();
	}

	// FUNCTION: ENGINE 0x10603C80
	void ObjectMetaType::Set(void* object, const char* name, unsigned short version)
	{
		Clear(object);
		if (strcmp(gNullName, name) != 0)
		{
			MakeInstance(object, name, version);
		}
	}

	// FUNCTION: ENGINE 0x10603CE0
	void* ObjectMetaType::GetInstance(const void* object)
	{
		if (!IsDirect(object))
		{
			return *(void**)object;
		}
		return ((ObjectValue*)object)->instance;
	}

	// FUNCTION: ENGINE 0x10603D00
	void* ObjectMetaType::GetInstance(void* object)
	{
		if (!IsDirect(object))
		{
			return *(void**)object;
		}
		return ((ObjectValue*)object)->instance;
	}

	// FUNCTION: ENGINE 0x10603D20
	bool ObjectMetaType::Matches(unsigned int flags, void* object)
	{
		ClassMetaType* valueType = GetValueType(object);
		if (valueType == 0)
		{
			return type->HasKey(flags);
		}
		return valueType->HasKey(flags);
	}

	// FUNCTION: ENGINE 0x10603D60
	void* ObjectMetaType::Create()
	{
		core::HeapScope scope(gMetaHeap);
		return new ObjectValue;
	}

	// FUNCTION: ENGINE 0x10604250
	void ObjectMetaType::Destroy(void* object)
	{
		ObjectValue* value = (ObjectValue*)object;
		if (value != 0)
		{
			delete value;
		}
	}

	// FUNCTION: ENGINE 0x10603DD0
	void ObjectMetaType::Copy(void* destination, const void* source, int a)
	{
		ClassMetaType* sourceType = GetValueType((void*)source);
		ClassMetaType* destinationType = GetValueType(destination);
		if (sourceType != destinationType)
		{
			if (destinationType != 0)
			{
				Clear(destination);
			}
			if (sourceType == 0)
			{
				return;
			}
			MakeInstance(destination, sourceType->GetName(), sourceType->GetVersion());
		}
		if (sourceType != 0)
		{
			((MetaTypeView*)sourceType)->Copy(GetInstance(destination), GetInstance(source), a);
		}
	}

	// FUNCTION: ENGINE 0x10603E50
	int ObjectMetaType::Count(void* object, int a)
	{
		void* instance = GetInstance((const void*)object);
		int result = 1;
		if (instance != 0)
		{
			result += ((MetaTypeView*)GetValueType(object))->Count(instance, a);
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10603E90
	void ObjectMetaType::Describe(MemberEntry** cursor, void* object, int a)
	{
		void* instance = GetInstance((const void*)object);
		if (instance == 0)
		{
			(*cursor)->type = this;
			(*cursor)->object = (void*)-1;
			*cursor += 1;
			return;
		}
		ClassMetaType* valueType = GetValueType(object);
		unsigned short index = (unsigned short)valueType->GetIndex();
		(*cursor)->type = this;
		(*cursor)->object = (void*)index;
		*cursor += 1;
		((MetaTypeView*)valueType)->Describe(cursor, instance, a);
	}

	// FUNCTION: ENGINE 0x10603F00
	void ObjectMetaType::WriteBinaryShort(WriteContext* context, unsigned short index)
	{
		int value = index;
		context->writer->Write(&value, 1, 2);
	}

	// FUNCTION: ENGINE 0x106041D0
	void ObjectMetaType::WriteText(TextWriter* writer, const void* object, int a)
	{
		void* instance = GetInstance(object);
		if (instance == 0)
		{
			writer->Write(gNullName, false);
			return;
		}
		ClassMetaType* valueType = GetValueType((void*)object);
		writer->Write(valueType->GetName(), false);
		unsigned short version = valueType->GetVersion();
		writer->WriteUShort(&version);
		writer->NewLine();
		((MetaTypeView*)valueType)->WriteText(writer, instance, a);
	}

	// FUNCTION: ENGINE 0x10603FF0
	void ObjectMetaType::WriteBinary(WriteContext* context, const void* object, int a)
	{
		void* instance = GetInstance(object);
		if (instance == 0)
		{
			int length = 4;
			context->writer->Write(&length, 1, 4);
			if (length != 0)
			{
				context->writer->Write(gNullName, length, 1);
			}
			return;
		}
		ClassMetaType* valueType = GetValueType((void*)object);
		context->WriteString(valueType->GetName());
		int version = valueType->GetVersion();
		context->writer->Write(&version, 1, 2);
		((MetaTypeView*)valueType)->WriteBinary(context, instance, a);
	}

	// FUNCTION: ENGINE 0x10603F20
	void ObjectMetaType::ReadBinary(ReadContext* context, void* object, int a, int b)
	{
		unsigned short version;
		char name[0x40];
		int length;
		context->reader->Read(&length, 1, 4);
		context->reader->Read(name, length, 1);
		name[length] = 0;
		Clear(object);
		if (strcmp(name, gNullName) != 0)
		{
			context->reader->Read(&version, 1, 2);
			ClassMetaType* valueType = MakeInstance(object, name, version);
			((MetaTypeView*)valueType)->ReadBinary(context, GetInstance(object), a, b);
		}
	}

	// FUNCTION: ENGINE 0x106040A0
	bool ObjectMetaType::ReadText(TextReadStream* reader, void* object, int a, int b)
	{
		char name[0x40];
		if (!reader->ReadToken(name, 0x40, false))
		{
			reader->Error("Expecting class name at line %d", reader->GetLine());
			return false;
		}
		Clear(object);
		if (strcmp(name, gNullName) == 0)
		{
			return true;
		}
		unsigned short version;
		if (!reader->ReadUShort(&version))
		{
			reader->Error("Expecting version at line %d", reader->GetLine());
			return false;
		}
		ClassMetaType* valueType = MakeInstance(object, name, version);
		if (valueType == 0)
		{
			reader->Error("Class %s(v:%d) at line %d was not found", name, version, reader->GetLine());
			return false;
		}
		return ((MetaTypeView*)valueType)->ReadText(reader, GetInstance(object), a, b);
	}

	// FUNCTION: ENGINE 0x10603890
	bool ObjectMetaType::Compare(ReadContext* first, const char* firstName, ReadContext* second,
		const char* secondName, int unused, TextWriter* log)
	{
		int version;
		int firstIndex = 0;
		int secondIndex = 0;
		if (first != 0)
		{
			first->reader->Read(&firstIndex, 1, 2);
		}
		if (second != 0)
		{
			second->reader->Read(&secondIndex, 1, 2);
		}
		if ((unsigned short)firstIndex != (unsigned short)secondIndex && first != 0 && second != 0)
		{
			ClassMetaType* firstType = dynamic_cast<ClassMetaType*>(NamedMetaType::GetByIndex((unsigned short)firstIndex));
			if (firstType != 0)
			{
				const char* name = firstType->GetName();
				version = firstType->GetVersion();
				log->Write(name, false);
				log->WriteUShort((unsigned short*)&version);
				log->NewLine();
				log->Indent();
				((MetaTypeView*)firstType)->Compare(first, firstName, second, secondName, unused, log);
				log->Unindent();
			}
			else
			{
				log->Write("NULL", false);
			}
			ClassMetaType* secondType = dynamic_cast<ClassMetaType*>(NamedMetaType::GetByIndex((unsigned short)secondIndex));
			if (secondType != 0)
			{
				const char* name = secondType->GetName();
				version = secondType->GetVersion();
				log->Write(name, false);
				log->WriteUShort((unsigned short*)&version);
				log->NewLine();
				log->Indent();
				((MetaTypeView*)secondType)->Compare(first, firstName, second, secondName, unused, log);
				log->Unindent();
			}
			else
			{
				log->Write("NULL", false);
			}
			return false;
		}
		unsigned short index = first != 0 ? (unsigned short)firstIndex : (unsigned short)secondIndex;
		ClassMetaType* valueType = dynamic_cast<ClassMetaType*>(NamedMetaType::GetByIndex(index));
		if (valueType != 0)
		{
			const char* name = valueType->GetName();
			version = valueType->GetVersion();
			log->Write(name, false);
			log->WriteUShort((unsigned short*)&version);
			log->NewLine();
			log->Indent();
			bool result = ((MetaTypeView*)valueType)->Compare(first, firstName, second, secondName, unused, log);
			log->Unindent();
			return result;
		}
		log->Write("NULL", false);
		return true;
	}
}
