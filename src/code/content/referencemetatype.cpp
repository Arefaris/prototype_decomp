// content::ReferenceMetaType, ReferenceMetaTypeGetSet and NamedReferenceMetaTypeGetSet: the meta types of members that
// refer to inventory objects (unit 0x105FEC40 - 0x105FF560; assert path content\src\meta\referencemetatype.cpp).
#include "code/content/loadinventory.h"
#include "code/content/metastream.h"
#include "code/core/debug.h"
#include "code/core/heap.h"
#include "code/core/strings.h"
#include <new>
#include <string.h>

namespace content
{
	// The heap the meta system makes its values in (0x11276928, name guessed)
	extern int gMetaHeap;

	// FUNCTION: ENGINE 0x105FEBB0
	void ReadContext::ReadShortString(char* destination, int size)
	{
		unsigned char length;
		reader->Read(&length, 1, 1);
		reader->Read(destination, length, 1);
		destination[length] = 0;
	}

	// FUNCTION: ENGINE 0x105FEBF0
	void WriteContext::WriteShortString(const char* text)
	{
		unsigned char length = (unsigned char)strlen(text);
		writer->Write(&length, 1, 1);
		if (length != 0)
		{
			writer->Write(text, length, 1);
		}
	}

	// FUNCTION: ENGINE 0x105FEC40
	const char* GetReferenceTypeName()
	{
		return "reference";
	}

	// FUNCTION: ENGINE 0x105FEC50
	ReferenceMetaType::ReferenceMetaType(LoadInventory::DynamicCasterBase* newCaster, const char* code)
		: MetaType(code)
	{
		caster = newCaster;
	}

	// FUNCTION: ENGINE 0x105FEC70
	bool ReferenceMetaType::Compare(ReadContext* first, const char* firstName, ReadContext* second,
		const char* secondName, int unused, TextWriter* log)
	{
		unsigned char length;
		char firstText[0x40] = { 0 };
		char secondText[0x40] = { 0 };
		if (first != 0)
		{
			first->reader->Read(&length, 1, 1);
			first->reader->Read(firstText, length, 1);
			firstText[length] = 0;
		}
		if (second != 0)
		{
			second->reader->Read(&length, 1, 1);
			second->reader->Read(secondText, length, 1);
			secondText[length] = 0;
		}
		int different = strcmp(firstText, secondText);
		if (different == 0)
		{
			log->Write(firstText, true);
			return true;
		}
		if (first != 0)
		{
			log->NewLine();
			log->Write("*******************", false);
			log->Write(firstName, false);
			log->NewLine();
			log->Write(firstText, true);
		}
		if (second != 0)
		{
			log->NewLine();
			log->Write("*******************", false);
			log->Write(secondName, false);
			log->NewLine();
			log->Write(secondText, true);
		}
		log->NewLine();
		log->Write("*******************", false);
		log->NewLine();
		return false;
	}

	// FUNCTION: ENGINE 0x105FEE10
	const char* ReferenceMetaType::GetObjectName(const void* object)
	{
		OLD_ASSERT_TEXT_AT("..\\..\\..\\code\\content\\src\\meta\\referencemetatype.cpp", 0x116, false, "false");
		return 0;
	}

	// FUNCTION: ENGINE 0x105FEE50
	void* ReferenceMetaType::Create()
	{
		core::HeapScope scope(gMetaHeap);
		LoadObject** value = (LoadObject**)operator new(4);
		*value = 0;
		return value;
	}

	// FUNCTION: ENGINE 0x105FEE90
	void ReferenceMetaType::Set(void* object, LoadObject* value, const ObjectName* name)
	{
		if (value != 0)
		{
			value->AddRef();
		}
		LoadObject** slot = (LoadObject**)object;
		if (*slot != 0)
		{
			(*slot)->Release();
		}
		*slot = value;
	}

	// FUNCTION: ENGINE 0x105FEEC0
	LoadObject* ReferenceMetaType::Get(const void* object)
	{
		return *(LoadObject* const*)object;
	}

	// FUNCTION: ENGINE 0x105FEED0
	int ReferenceMetaType::Unknown9(int a, int b)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x105FEEE0
	void ReferenceMetaType::Describe(MemberEntry** cursor, void* object, int unused)
	{
		(*cursor)->type = this;
		(*cursor)->object = object;
		*cursor += 1;
	}

	// FUNCTION: ENGINE 0x105FEF00
	void ReferenceMetaType::WriteBinaryShort(WriteContext* context, const void* object)
	{
		char text[0x40];
		const char* name = GetObjectName(object);
		if (name != 0)
		{
			core::StrCpy(text, name);
		}
		else
		{
			core::StrCpy(text, "");
		}
		unsigned char length = (unsigned char)strlen(text);
		context->writer->Write(&length, 1, 1);
		if (length != 0)
		{
			context->writer->Write(text, length, 1);
		}
	}

	// FUNCTION: ENGINE 0x105FEF80
	ReferenceMetaTypeGetSet::ReferenceMetaTypeGetSet(LoadInventory::DynamicCasterBase* newCaster,
		ReferenceMetaTypeGetSetter* newGetSetter, const char* code)
		: ReferenceMetaType(newCaster, code)
	{
		getSetter = newGetSetter;
	}

	// FUNCTION: ENGINE 0x105FEFB0
	LoadObject* ReferenceMetaTypeGetSet::Get(const void* object)
	{
		if (MetaType::IsDirect(object))
		{
			return ReferenceMetaType::Get(object);
		}
		return getSetter->Get(object);
	}

	// FUNCTION: ENGINE 0x105FEFE0
	void ReferenceMetaTypeGetSet::Set(void* object, LoadObject* value, const ObjectName* name)
	{
		if (MetaType::IsDirect(object))
		{
			ReferenceMetaType::Set(object, value, name);
			return;
		}
		getSetter->Set(object, value);
	}

	// FUNCTION: ENGINE 0x105FF030
	NamedReferenceMetaTypeGetSet::NamedReferenceMetaTypeGetSet(LoadInventory::DynamicCasterBase* newCaster,
		NamedReferenceMetaTypeGetSetter* newGetSetter, const char* code)
		: ReferenceMetaType(newCaster, code)
	{
		getSetter = newGetSetter;
	}

	// FUNCTION: ENGINE 0x105FF060
	void NamedReferenceMetaTypeGetSet::Copy(void* destination, const void* source, int a)
	{
		Set(destination, Get(source), GetName(source));
	}

	// FUNCTION: ENGINE 0x105FF090
	const ObjectName* NamedReferenceMetaTypeGetSet::GetName(const void* object)
	{
		if (MetaType::IsDirect(object))
		{
			return &((const NamedReferenceValue*)object)->name;
		}
		return getSetter->GetName(object);
	}

	// FUNCTION: ENGINE 0x105FF0C0
	LoadObject* NamedReferenceMetaTypeGetSet::Get(const void* object)
	{
		if (MetaType::IsDirect(object))
		{
			return ReferenceMetaType::Get(object);
		}
		return getSetter->GetObject(object);
	}

	// FUNCTION: ENGINE 0x105FF100
	void ReferenceMetaType::ReadBinary(ReadContext* context, void* object, int a, int b)
	{
		unsigned char length;
		char text[0x40];
		context->reader->Read(&length, 1, 1);
		context->reader->Read(text, length, 1);
		text[length] = 0;
		ObjectName name(text, 1);
		LoadObject* found = (LoadObject*)((LoadInventory*)a)->FindObject(caster, name, true);
		Set(object, found, &name);
	}

	// FUNCTION: ENGINE 0x105FF180
	void ReferenceMetaType::WriteBinary(WriteContext* context, const void* object, int a)
	{
		char text[0x40];
		const char* name = GetObjectName(object);
		if (name != 0)
		{
			core::StrCpy(text, name);
		}
		else
		{
			core::StrCpy(text, "");
		}
		unsigned char length = (unsigned char)strlen(text);
		context->writer->Write(&length, 1, 1);
		if (length != 0)
		{
			context->writer->Write(text, length, 1);
		}
	}

	// FUNCTION: ENGINE 0x105FF200
	bool ReferenceMetaType::ReadText(TextReadStream* reader, void* object, int a, int b)
	{
		char text[0x40];
		if (!reader->ReadToken(text, 0x40, true))
		{
			reader->Error("Expecting a quoted \"\" reference name at line %d", reader->GetLine());
			return false;
		}
		ObjectName name(text, 1);
		LoadObject* found = (LoadObject*)((LoadInventory*)a)->FindObject(caster, name, true);
		Set(object, found, &name);
		return true;
	}

	// FUNCTION: ENGINE 0x105FF290
	void ReferenceMetaType::WriteText(TextWriter* writer, const void* object, int a)
	{
		const char* name = GetObjectName(object);
		if (name != 0)
		{
			writer->Write(name, true);
			return;
		}
		writer->Write("", true);
	}

	// FUNCTION: ENGINE 0x105FF2D0
	void ReferenceMetaType::Destroy(void* object)
	{
		LoadObject* none = 0;
		Set(object, none, &ObjectName());
		operator delete(object);
	}

	// FUNCTION: ENGINE 0x105FF310
	// EQUIVALENT: scheduling: the engine reads the vftable pointer before the name's constructor call, ours after it (86.5 %)
	void ReferenceMetaType::Copy(void* destination, const void* source, int a)
	{
		const ObjectName* name = &ObjectName();
		Set(destination, Get(source), name);
	}

	// FUNCTION: ENGINE 0x105FF370
	void NamedReferenceMetaTypeGetSet::Set(void* object, LoadObject* value, const ObjectName* name)
	{
		if (MetaType::IsDirect(object))
		{
			((NamedReferenceValue*)object)->name = *name;
			ReferenceMetaType::Set(object, value, name);
			return;
		}
		getSetter->Set(object, value, name);
	}

	// FUNCTION: ENGINE 0x105FF3D0
	void NamedReferenceMetaTypeGetSet::WriteBinary(WriteContext* context, const void* object, int a)
	{
		char text[0x40];
		const char* name = GetName(object)->GetText();
		if (name != 0)
		{
			core::StrCpy(text, name);
		}
		else
		{
			core::StrCpy(text, "");
		}
		unsigned char length = (unsigned char)strlen(text);
		context->writer->Write(&length, 1, 1);
		if (length != 0)
		{
			context->writer->Write(text, length, 1);
		}
	}

	// FUNCTION: ENGINE 0x105FF460
	void NamedReferenceMetaTypeGetSet::WriteText(TextWriter* writer, const void* object, int a)
	{
		const char* name = GetName(object)->GetText();
		if (name != 0)
		{
			writer->Write(name, true);
			return;
		}
		writer->Write("", true);
	}

	// FUNCTION: ENGINE 0x105FF4A0
	void* NamedReferenceMetaTypeGetSet::Create()
	{
		core::HeapScope scope(gMetaHeap);
		NamedReferenceValue* value = new (core::HeapAllocAligned(core::GetCurrentHeap(), 0x10, 8)) NamedReferenceValue();
		value->object = 0;
		return value;
	}

	// FUNCTION: ENGINE 0x105FF520
	void NamedReferenceMetaTypeGetSet::Destroy(void* object)
	{
		LoadObject* none = 0;
		Set(object, none, &ObjectName());
		core::FreeAligned(object);
	}
}
