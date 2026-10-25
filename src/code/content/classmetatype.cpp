// content::ClassMetaType, the meta type of a reflected class (code/content/src/meta/classmetatype.cpp, path from the
// assert; the unit runs from 0x105FA740 to 0x105FB5E0). A value is an object of the class or a MetaObject the meta
// system made: the value of the base class and one value per member, found by IsDirect.
#include "code/content/metatype.h"
#include "code/core/debug.h"
#include "code/core/heap.h"
#include <new>
#include <string.h>

namespace content
{
	// The heap the meta system makes its values in (0x11276928, name guess)
	extern int gMetaHeap;

	// The delimiters of a class in its text form: the engine keeps them as three data words (names guessed)
	char gClassOpen[] = "{";
	char gClassClose[] = "}";
	char gClassSeparator[] = ",";

	// What Create makes: the value of the base class and the values of the members
	struct MetaObject
	{
		void* base;
		void** items;
	};

	// The vftable of a meta type with every slot a virtual function that takes its arguments: the engine's code calls the
	// members' types this way (the compiler reads the vftable pointer, then the slot, then the arguments)
	struct MetaTypeView
	{
		virtual bool ReadText(TextReadStream* reader, void* object, int a, int b);
		virtual void ReadBinary(ReadContext* context, void* object, int a, int b);
		virtual void WriteText(TextWriter* writer, const void* object, int a);
		virtual void WriteBinary(WriteContext* context, const void* object, int a);
		virtual bool Compare(ReadContext* first, const char* firstName, ReadContext* second, const char* secondName,
			int flags, TextWriter* log);
		virtual bool Matches(unsigned int flags, void* object);
		virtual void* Create();
		virtual void Destroy(void* object);
		virtual void Copy(void* destination, const void* source, int a);
		virtual int Count(void* object, int a);
		virtual void Describe(MemberEntry** cursor, void* object, int a);
		virtual void WriteBinaryShort(WriteContext* context, const void* object);
	};

	static inline MetaTypeView* View(MetaType* type)
	{
		return (MetaTypeView*)type;
	}

	// FUNCTION: ENGINE 0x105FA740
	const char* GetClassTypeName()
	{
		return "class";
	}

	// FUNCTION: ENGINE 0x105FA750
	ClassMetaType::ClassMetaType(const ClassInfo* info)
		: NamedMetaType(info->name, info->version, info->code)
	{
		members = 0;
		count = 0;
		baseType = 0;
		firstDerived = 0;
		nextSibling = 0;
		baseCaster = 0;
	}

	// FUNCTION: ENGINE 0x105FA790
	void ClassMetaType::SetMembers(const MemberList* list)
	{
		members = list->members;
		count = list->count;
		baseType = (ClassMetaType*)list->baseType;
		baseCaster = list->baseCaster;
		ClassMetaType* base = baseType;
		if (base != 0)
		{
			nextSibling = base->firstDerived;
			base->firstDerived = this;
		}
	}

	// FUNCTION: ENGINE 0x105FA7C0
	unsigned int ClassMetaType::GetTotalCount()
	{
		if (baseType != 0)
		{
			return baseType->GetTotalCount() + count;
		}
		return count;
	}

	// FUNCTION: ENGINE 0x105FA7E0
	MetaType* ClassMetaType::GetMemberType(unsigned int index)
	{
		ClassMetaType* type = this;
		while (index >= type->count)
		{
			index -= type->count;
			type = type->baseType;
		}
		return type->members[index].type;
	}

	// FUNCTION: ENGINE 0x105FA810
	void* ClassMetaType::GetMember(void* object, unsigned int index)
	{
		ClassMetaType* type = this;
		for (;;)
		{
			if (!IsDirect(object))
			{
				unsigned int own = type->count;
				if (index < own)
				{
					return (char*)object + type->members[index].offset;
				}
				type = type->baseType;
				index -= own;
			}
			else
			{
				unsigned int own = type->count;
				if (index < own)
				{
					return ((MetaObject*)object)->items[index];
				}
				object = ((MetaObject*)object)->base;
				type = type->baseType;
				index -= own;
			}
		}
	}

	// FUNCTION: ENGINE 0x105FA870
	void* ClassMetaType::GetMemberOf(void* object, unsigned int index)
	{
		ClassMetaType* type = this;
		if (!IsDirect(object))
		{
			do
			{
				unsigned int own = type->count;
				if (index < own)
				{
					return (char*)object + type->members[index].offset;
				}
				type = type->baseType;
				index -= own;
			}
			while (!IsDirect(object));
		}
		unsigned int own = type->count;
		if (index >= own)
		{
			return type->baseType->GetMember(((MetaObject*)object)->base, index - own);
		}
		return ((MetaObject*)object)->items[index];
	}

	// FUNCTION: ENGINE 0x105FA8F0
	void* ClassMetaType::GetBaseObject(void* object)
	{
		if (!IsDirect(object))
		{
			return object;
		}
		return ((MetaObject*)object)->base;
	}

	// FUNCTION: ENGINE 0x105FA910
	const void* ClassMetaType::GetBaseObject(const void* object)
	{
		if (!IsDirect(object))
		{
			return object;
		}
		return ((const MetaObject*)object)->base;
	}

	// FUNCTION: ENGINE 0x105FA930
	const char* ClassMetaType::GetMemberName(unsigned int index)
	{
		ClassMetaType* type = this;
		while (index >= type->count)
		{
			index -= type->count;
			type = type->baseType;
		}
		return type->members[index].name;
	}

	// FUNCTION: ENGINE 0x105FA960
	// EQUIVALENT: the engine calls itself for the derived class, ours turns that last call into a jump back to the loop (65 against 58 bytes, 90.8 %)
	ClassMetaType* ClassMetaType::FindDerived(void* object)
	{
		ClassMetaType* derived = firstDerived;
		if (derived != 0)
		{
			do
			{
				if (derived->baseCaster != 0 && derived->baseCaster->IsDerived(object))
				{
					ClassMetaType* result = derived->FindDerived(object);
					return result;
				}
				derived = derived->nextSibling;
			}
			while (derived != 0);
		}
		return this;
	}

	// FUNCTION: ENGINE 0x105FA9B0
	void* ClassMetaType::Create()
	{
		core::HeapScope scope(gMetaHeap);
		MetaObject* object = new MetaObject;
		if (baseType != 0)
		{
			object->base = ((MetaTypeView*)baseType)->Create();
		}
		else
		{
			object->base = 0;
		}
		if (count == 0)
		{
			object->items = 0;
		}
		else
		{
			object->items = new void*[count];
			for (unsigned int i = 0; i < count; i++)
			{
				object->items[i] = ((MetaTypeView*)members[i].type)->Create();
			}
		}
		return object;
	}

	// FUNCTION: ENGINE 0x105FAA60
	void ClassMetaType::Destroy(void* object)
	{
		MetaObject* value = (MetaObject*)object;
		for (unsigned int i = 0; i < count; i++)
		{
			((MetaTypeView*)members[i].type)->Destroy(value->items[i]);
		}
		if (baseType != 0)
		{
			((MetaTypeView*)baseType)->Destroy(value->base);
		}
		delete[] value->items;
		delete value;
	}

	// FUNCTION: ENGINE 0x105FAAD0
	void ClassMetaType::Copy(void* destination, const void* source, int a)
	{
		if (baseType != 0)
		{
			((MetaTypeView*)baseType)->Copy(GetBaseObject(destination), GetBaseObject(source), a);
		}
		for (unsigned int i = 0; i < count; i++)
		{
			if (members[i].type->HasKey(a))
			{
				((MetaTypeView*)members[i].type)->Copy(GetMember(destination, i), GetMemberOf((void*)source, i), a);
			}
		}
	}

	// FUNCTION: ENGINE 0x105FAB70
	int ClassMetaType::CountMembers(const void* object, int a)
	{
		int total = 0;
		if (baseType != 0)
		{
			total = baseType->CountMembers(GetBaseObject(object), a);
		}
		for (unsigned int i = 0; i < count; i++)
		{
			void* member = GetMember((void*)object, i);
			if (((MetaTypeView*)members[i].type)->Matches(a, member))
			{
				total += ((MetaTypeView*)members[i].type)->Count(member, a);
			}
		}
		return total;
	}

	// FUNCTION: ENGINE 0x105FAC10
	void ClassMetaType::DescribeMembers(MemberEntry** cursor, const void* object, int a)
	{
		if (baseType != 0)
		{
			baseType->DescribeMembers(cursor, GetBaseObject(object), a);
		}
		for (unsigned int i = 0; i < count; i++)
		{
			void* member = GetMember((void*)object, i);
			if (((MetaTypeView*)members[i].type)->Matches(a, member))
			{
				((MetaTypeView*)members[i].type)->Describe(cursor, member, a);
			}
		}
	}

	// FUNCTION: ENGINE 0x105FACA0
	void ClassMetaType::WriteBinaryShort(WriteContext* context, const void* object)
	{
		OLD_ASSERT_TEXT_AT("..\\..\\..\\code\\content\\src\\meta\\classmetatype.cpp", 0x60B, false, "false");
	}

	// FUNCTION: ENGINE 0x105FACE0
	void ClassMetaType::ReadBinaryMembers(ReadContext* context, void* object, int a, int b)
	{
		if (baseType != 0)
		{
			baseType->ReadBinaryMembers(context, GetBaseObject(object), a, b);
		}
		for (unsigned int i = 0; i < count; i++)
		{
			if (members[i].type->HasKey(b))
			{
				((MetaTypeView*)members[i].type)->ReadBinary(context, GetMember(object, i), a, b);
			}
		}
	}

	// FUNCTION: ENGINE 0x105FAD80
	void ClassMetaType::WriteBinaryMembers(WriteContext* context, const void* object, int a)
	{
		if (baseType != 0)
		{
			baseType->WriteBinaryMembers(context, GetBaseObject(object), a);
		}
		for (unsigned int i = 0; i < count; i++)
		{
			void* member = GetMember((void*)object, i);
			if (((MetaTypeView*)members[i].type)->Matches(a, member))
			{
				((MetaTypeView*)members[i].type)->WriteBinary(context, member, a);
			}
		}
	}

	// FUNCTION: ENGINE 0x105FAE10
	bool ClassMetaType::WriteTextMembers(TextWriter* writer, const void* object, int a)
	{
		bool wrote = false;
		if (baseType != 0)
		{
			wrote = baseType->WriteTextMembers(writer, GetBaseObject(object), a);
		}
		for (unsigned int i = 0; i < count; i++)
		{
			if (((MetaTypeView*)members[i].type)->Matches(a, GetMember((void*)object, i)))
			{
				if (wrote)
				{
					writer->Write(gClassSeparator, false);
					writer->NewLine();
				}
				writer->Write(members[i].name, false);
				((MetaTypeView*)members[i].type)->WriteText(writer, GetMember((void*)object, i), a);
				wrote = true;
			}
		}
		return wrote;
	}

	// FUNCTION: ENGINE 0x105FAF00
	bool ClassMetaType::HasMemberWith(unsigned int first, unsigned int second, const void* object)
	{
		if (baseType != 0)
		{
			if (baseType->HasMemberWith(first, second, GetBaseObject(object)))
			{
				return true;
			}
		}
		for (unsigned int i = 0; i < count; i++)
		{
			if (!((MetaTypeView*)members[i].type)->Matches(first, GetMember((void*)object, i)))
			{
				if (((MetaTypeView*)members[i].type)->Matches(second, GetMember((void*)object, i)))
				{
					return true;
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105FAFC0
	bool ClassMetaType::MatchesClass(unsigned int flags, void* object)
	{
		if (!HasMemberWith(0, 8, object))
		{
			return HasKey(flags);
		}
		return HasMemberWith(8, flags, object) ? true : false;
	}

	// FUNCTION: ENGINE 0x105FB000
	bool ClassMetaType::Matches(unsigned int flags, void* object)
	{
		return MatchesClass(flags, object);
	}

	// FUNCTION: ENGINE 0x105FB010
	// EQUIVALENT: the same operations in the same order; the two address computations of a member's name and type put base and index registers the other way round (99.2 %)
	bool ClassMetaType::CompareMembers(ReadContext* first, const char* firstName, ReadContext* second,
		const char* secondName, int flags, TextWriter* log)
	{
		bool same = true;
		if (baseType != 0)
		{
			same = baseType->CompareMembers(first, firstName, second, secondName, flags, log) ? true : false;
			if (baseType->GetTotalCount() != 0)
			{
				log->NewLine();
			}
		}
		for (unsigned int i = 0; i < count; i++)
		{
			const char* memberName = members[i].name;
			log->Write(memberName, false);
			if (members[i].type->HasKey(flags))
			{
				bool equal = ((MetaTypeView*)members[i].type)->Compare(first, firstName, second, secondName, flags, log);
				same = equal && same;
			}
			if (count - i > 1)
			{
				log->NewLine();
			}
		}
		return same;
	}

	// FUNCTION: ENGINE 0x105FB110
	bool ClassMetaType::FindMember(const char* name, unsigned int* index)
	{
		bool found = false;
		unsigned int total = GetTotalCount();
		for (unsigned int i = 0; i < total; i++)
		{
			if (strcmp(GetMemberName(i), name) == 0)
			{
				*index = i;
				found = true;
				break;
			}
		}
		return found;
	}

	// FUNCTION: ENGINE 0x105FB190
	int ClassMetaType::CountItems(void* object, int a)
	{
		if (!MatchesClass(a, object))
		{
			return 0;
		}
		return CountMembers(object, a);
	}

	// FUNCTION: ENGINE 0x105FB1C0
	void ClassMetaType::Describe(MemberEntry** cursor, void* object, int a)
	{
		if (MatchesClass(a, object))
		{
			DescribeMembers(cursor, object, a);
		}
	}

	// FUNCTION: ENGINE 0x105FB1F0
	void ClassMetaType::ReadBinary(ReadContext* context, void* object, int a, int b)
	{
		ReadBinaryMembers(context, object, a, b);
	}

	// FUNCTION: ENGINE 0x105FB200
	void ClassMetaType::WriteBinary(WriteContext* context, const void* object, int a)
	{
		if (MatchesClass(a, (void*)object))
		{
			WriteBinaryMembers(context, object, a);
		}
	}

	// FUNCTION: ENGINE 0x105FB230
	// EQUIVALENT: the same reads, comparisons, calls and branches; the three locals (the saved this, the line and the index) lie in other stack slots and the error paths share their code differently (89.5 %)
	bool ClassMetaType::ReadText(TextReadStream* reader, void* object, int a, int b)
	{
		char open[2];
		char token[0x800];
		if (!reader->ReadToken(open, 2, false) || strcmp(open, gClassOpen) != 0)
		{
			reader->Error("Expecting class openning delimiter \"{\" near line %d", reader->GetLine());
			return false;
		}
		int line = reader->GetLine();
		if (reader->ReadToken(token, 0x800, false))
		{
			do
			{
				unsigned int index;
				if (FindMember(token, &index))
				{
					MetaType* type = GetMemberType(index);
					if (!((MetaTypeView*)type)->ReadText(reader, GetMember(object, index), a, b))
					{
						return false;
					}
					if (!reader->ReadToken(token, 0x800, false))
					{
						break;
					}
					if (strcmp(token, gClassClose) == 0)
					{
						return true;
					}
					if (strcmp(token, gClassSeparator) != 0)
					{
						reader->Error("Unknown token \"%s\" near line %d", token, reader->GetLine());
						return false;
					}
				}
				else
				{
					if (strcmp(token, gClassClose) == 0)
					{
						return true;
					}
					int depth = 0;
					for (;;)
					{
						if (depth == 0 && strcmp(token, gClassSeparator) == 0)
						{
							break;
						}
						if (strcmp(token, gClassOpen) == 0)
						{
							depth++;
						}
						else if (strcmp(token, gClassClose) == 0)
						{
							if (depth == 0)
							{
								return true;
							}
							depth--;
						}
						if (!reader->ReadToken(token, 0x800, false))
						{
							goto missing;
						}
					}
				}
			}
			while (reader->ReadToken(token, 0x800, false));
		}
	missing:
		reader->Error("Missing class delimiter \"}\" for \"{\" near line %d", line);
		return false;
	}

	// FUNCTION: ENGINE 0x105FB560
	void ClassMetaType::WriteText(TextWriter* writer, const void* object, int a)
	{
		if (MatchesClass(a, (void*)object))
		{
			writer->Write(gClassOpen, false);
			writer->NewLine();
			writer->Indent();
			if (WriteTextMembers(writer, object, a))
			{
				writer->NewLine();
			}
			writer->Unindent();
			writer->Write(gClassClose, false);
		}
	}

	// FUNCTION: ENGINE 0x105FB5D0
	bool ClassMetaType::Compare(ReadContext* first, const char* firstName, ReadContext* second,
		const char* secondName, int flags, TextWriter* log)
	{
		return CompareMembers(first, firstName, second, secondName, flags, log);
	}
}
