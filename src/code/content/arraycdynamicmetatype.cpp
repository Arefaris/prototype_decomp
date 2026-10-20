// content::ArrayCDynamicMetaType: the meta type of an array of items of one element type, and the helper that
// edits the meta system's own arrays (unit 0x10600270 - 0x10600FB0).
#include "code/content/metatype.h"
#include "code/core/heap.h"
#include <new>
#include <string.h>

namespace content
{
	// The heap the meta system makes its values in (0x11276928, name guessed)
	extern int gMetaHeap;

	// An array of item pointers the meta system makes (16 bytes; begin, end, end of storage)
	struct PointerArray
	{
		void** begin;
		void** end;
		void** capacityEnd;
		int unknownC;

		// 0x106007E0 (the second argument is an empty allocator object)
		PointerArray(unsigned int capacity, const char& allocator);
	};

	// RTTI content::VirtualArrayCDynamicHelper: the helper for a PointerArray (the object at 0x110BAD58 is the one
	// the meta types use for their own arrays)
	class VirtualArrayCDynamicHelper : public ArrayCDynamicHelperBase
	{
	public:
		virtual int Size(void* array);
		virtual void* Get(void* array, int index);
		virtual void* GetConst(void* array, int index);
		virtual void Insert(void* array, int index, int type);
		virtual void Erase(void* array, int index, int type);
	};

	extern VirtualArrayCDynamicHelper gPointerArrayHelper;

	// Copies [first, last) down to dest, answering the end of the copy
	inline void** CopyPointers(void** first, void** last, void** dest)
	{
		for (; first != last; first++, dest++)
		{
			*dest = *first;
		}
		return dest;
	}

	// FUNCTION: ENGINE 0x10600270
	const char* GetArrayCDynamicTypeName()
	{
		return "arraycdynamic";
	}

	// FUNCTION: ENGINE 0x10600280
	ArrayCDynamicMetaType::ArrayCDynamicMetaType(int newCapacity, MetaType* newElement,
		ArrayCDynamicHelperBase* newHelper, const char* code)
		: MetaType(code)
	{
		element = newElement;
		capacity = newCapacity;
		helper = newHelper;
	}

	// FUNCTION: ENGINE 0x10600520
	MetaType* ArrayCDynamicMetaType::GetElementType()
	{
		return element;
	}

	// FUNCTION: ENGINE 0x10600530
	void ArrayCDynamicMetaType::WriteBinaryShort(WriteContext* context, void* object)
	{
		void* value = object;
		context->writer->Write(&value, 1, 4);
	}

	// FUNCTION: ENGINE 0x10600550
	int VirtualArrayCDynamicHelper::Size(void* array)
	{
		PointerArray* pointers = (PointerArray*)array;
		return pointers->end - pointers->begin;
	}

	// FUNCTION: ENGINE 0x10600560
	void* VirtualArrayCDynamicHelper::Get(void* array, int index)
	{
		return ((PointerArray*)array)->begin[index];
	}

	// FUNCTION: ENGINE 0x10600570
	void* VirtualArrayCDynamicHelper::GetConst(void* array, int index)
	{
		return ((PointerArray*)array)->begin[index];
	}

	// FUNCTION: ENGINE 0x10600590
	void* ArrayCDynamicMetaType::GetItemConst(void* array, int index)
	{
		if (!IsDirect(array))
		{
			return helper->GetConst(array, index);
		}
		return ((PointerArray*)array)->begin[index];
	}

	// FUNCTION: ENGINE 0x106005D0
	void* ArrayCDynamicMetaType::GetItem(void* array, int index)
	{
		if (!IsDirect(array))
		{
			return helper->Get(array, index);
		}
		return ((PointerArray*)array)->begin[index];
	}

	// FUNCTION: ENGINE 0x10600610
	unsigned int ArrayCDynamicMetaType::GetCount(void* array)
	{
		if (!IsDirect(array))
		{
			return helper->Size(array);
		}
		PointerArray* pointers = (PointerArray*)array;
		return pointers->end - pointers->begin;
	}

	// FUNCTION: ENGINE 0x106007E0
	// EQUIVALENT: the end of the storage is made with a lea, 53%
	PointerArray::PointerArray(unsigned int capacity, const char& allocator)
	{
		if (capacity != 0)
		{
			unsigned int bytes = capacity * 4;
			begin = (void**)operator new[](bytes);
			if (begin != 0)
			{
				capacityEnd = (void**)(bytes + (unsigned int)begin);
				end = begin;
				return;
			}
		}
		else
		{
			begin = 0;
		}
		end = 0;
		capacityEnd = 0;
	}

	// FUNCTION: ENGINE 0x10600830
	void VirtualArrayCDynamicHelper::Erase(void* array, int index, int type)
	{
		PointerArray* pointers = (PointerArray*)array;
		((MetaType*)type)->InvokeDestroy(pointers->begin[index]);
		void** to = pointers->begin + index;
		CopyPointers(to + 1, pointers->end, to);
		pointers->end--;
	}

	// FUNCTION: ENGINE 0x10600A80
	void ArrayCDynamicMetaType::EraseItem(void* array, int index)
	{
		if (!IsDirect(array))
		{
			helper->Erase(array, index, (int)element);
			return;
		}
		gPointerArrayHelper.Erase(array, index, (int)element);
	}

	// FUNCTION: ENGINE 0x10600B30
	// EQUIVALENT: register allocation, 88%
	void VirtualArrayCDynamicHelper::Insert(void* array, int index, int type)
	{
		PointerArray* pointers = (PointerArray*)array;
		void** last = pointers->end;
		void** position = pointers->begin + index;
		void** newEnd = last + 1;
		if (newEnd <= pointers->capacityEnd)
		{
			pointers->end = newEnd;
			while (last != position)
			{
				last--;
				newEnd--;
				if (newEnd != 0)
				{
					*newEnd = *last;
				}
			}
			if (position != 0)
			{
				*position = 0;
			}
		}
		void** item = pointers->begin + index;
		*item = ((MetaType*)type)->InvokeCreate();
	}

	// FUNCTION: ENGINE 0x10600B90
	void ArrayCDynamicMetaType::InsertItem(void* array, int index)
	{
		if (!IsDirect(array))
		{
			helper->Insert(array, index, (int)element);
			return;
		}
		core::HeapScope scope(gMetaHeap);
		gPointerArrayHelper.Insert(array, index, (int)element);
	}

	// FUNCTION: ENGINE 0x10600650
	// EQUIVALENT: register allocation of the counters, 46%
	int ArrayCDynamicMetaType::CountItems(void* object, int a)
	{
		int result = 1;
		unsigned int count = GetCount(object);
		unsigned int kept = 0;
		void** items = new void*[count];
		unsigned int i;
		for (i = 0; i < count; i++)
		{
			items[kept] = GetItem(object, i);
			if (element->InvokeMatches(a, items[kept]))
			{
				kept++;
			}
			else
			{
				items[kept] = 0;
			}
		}
		for (i = 0; i < kept; i++)
		{
			result += element->InvokeCount(items[i], a);
		}
		delete[] items;
		return result;
	}

	// FUNCTION: ENGINE 0x10600710
	void ArrayCDynamicMetaType::Describe(MemberEntry** cursor, void* object, int a)
	{
		unsigned int count = GetCount(object);
		unsigned int kept = 0;
		void** items = new void*[count];
		unsigned int i;
		for (i = 0; i < count; i++)
		{
			items[kept] = GetItem(object, i);
			if (element->InvokeMatches(a, items[kept]))
			{
				kept++;
			}
			else
			{
				items[kept] = 0;
			}
		}
		(*cursor)->type = this;
		(*cursor)->object = (void*)kept;
		*cursor += 1;
		for (i = 0; i < kept; i++)
		{
			element->InvokeDescribe(cursor, items[i], a);
		}
		delete[] items;
	}

	// FUNCTION: ENGINE 0x10600880
	// EQUIVALENT: register allocation of the counters, 90%
	void ArrayCDynamicMetaType::WriteBinary(WriteContext* context, const void* object, int a)
	{
		unsigned int count = GetCount((void*)object);
		unsigned int kept = 0;
		void** items = new void*[count];
		unsigned int i;
		for (i = 0; i < count; i++)
		{
			items[kept] = GetItem((void*)object, i);
			if (element->InvokeMatches(a, items[kept]))
			{
				kept++;
			}
			else
			{
				items[kept] = 0;
			}
		}
		context->writer->Write(&kept, 1, 4);
		for (i = 0; i < kept; i++)
		{
			element->InvokeWriteBinary(context, items[i], a);
		}
		delete[] items;
	}

	// FUNCTION: ENGINE 0x10600950
	void ArrayCDynamicMetaType::WriteText(TextWriter* writer, const void* object, int a)
	{
		unsigned int count = GetCount((void*)object);
		unsigned int kept = 0;
		void** items = new void*[count];
		unsigned int i;
		for (i = 0; i < count; i++)
		{
			items[kept] = GetItem((void*)object, i);
			if (element->InvokeMatches(a, items[kept]))
			{
				kept++;
			}
			else
			{
				items[kept] = 0;
			}
		}
		writer->NewLine();
		writer->Write("{", false);
		writer->NewLine();
		writer->Indent();
		for (i = 0; i < kept; i++)
		{
			element->InvokeWriteText(writer, items[i], a);
			if (kept - i != 0)
			{
				writer->Write(",", false);
				writer->NewLine();
			}
		}
		writer->Unindent();
		writer->NewLine();
		writer->Write("}", false);
		delete[] items;
	}

	// FUNCTION: ENGINE 0x10600AD0
	void* ArrayCDynamicMetaType::Create()
	{
		core::HeapScope scope(gMetaHeap);
		PointerArray* array = (PointerArray*)operator new(0x10);
		void* result;
		if (array != 0)
		{
			char allocator;
			result = new (array) PointerArray(capacity, allocator);
		}
		else
		{
			result = 0;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10600BF0
	// EQUIVALENT: register allocation, 25%
	void ArrayCDynamicMetaType::Destroy(void* object)
	{
		PointerArray* array = (PointerArray*)object;
		for (unsigned int i = 0; i < (unsigned int)(array->end - array->begin); i++)
		{
			element->InvokeDestroy(array->begin[i]);
		}
		array->end = array->begin;
		if (array->begin != 0)
		{
			delete[] array->begin;
		}
		operator delete(array);
	}

	// FUNCTION: ENGINE 0x10600C50
	// EQUIVALENT: register allocation and the element type's vftable is read after the items are fetched, 17%
	void ArrayCDynamicMetaType::Copy(void* destination, const void* source, int a)
	{
		unsigned int destinationCount = GetCount(destination);
		unsigned int sourceCount = GetCount((void*)source);
		if (sourceCount < destinationCount)
		{
			for (int i = destinationCount; (int)sourceCount < i; i--)
			{
				EraseItem(destination, i - 1);
			}
		}
		if (destinationCount < sourceCount)
		{
			for (unsigned int i = destinationCount; i < sourceCount; i++)
			{
				InsertItem(destination, i);
			}
		}
		for (unsigned int i = 0; i < sourceCount; i++)
		{
			void** slot = element->SlotAddress(8);
			((MetaType::CopyFunction)*slot)(element, GetItemConst(destination, i), GetItem((void*)source, i), a);
		}
	}

	// FUNCTION: ENGINE 0x10600D00
	void ArrayCDynamicMetaType::ReadBinary(ReadContext* context, void* object, int a, int b)
	{
		unsigned int count;
		context->reader->Read(&count, 1, 4);
		for (unsigned int i = 0; i < count; i++)
		{
			InsertItem(object, i);
			void** slot = element->SlotAddress(1);
			((MetaType::ReadBinaryFunction)*slot)(element, context, GetItemConst(object, i), a, b);
		}
	}

	// FUNCTION: ENGINE 0x10600D70
	// NONMATCHING: the delimiter tests come out in another shape, best 24%
#ifdef NONMATCHING
	bool ArrayCDynamicMetaType::ReadText(TextReadStream* reader, void* object, int a, int b)
	{
		char opener[2];
		if (!reader->ReadToken(opener, 2, false))
		{
			goto missingOpener;
		}
		int different;
		different = strcmp(opener, "{");
		if (different != 0)
		{
			goto missingOpener;
		}
		unsigned int start;
		start = reader->GetPosition();
		int line;
		line = reader->GetLine();
		char buffer[0x800];
		if (!reader->ReadToken(buffer, 0x800, false))
		{
			reader->Error("Missing closing array delimiter \"}\" for \"{\" near line %d", line);
			return false;
		}
		different = strcmp(buffer, "}");
		if (different != 0)
		{
			reader->SetLine(line);
			reader->SetPosition(start);
			int index = 0;
			char delimiter[2];
			int notClose;
			do
			{
				InsertItem(object, index);
				void** slot = element->SlotAddress(0);
				if (!((MetaType::ReadTextFunction)*slot)(element, reader, GetItemConst(object, index), a, b))
				{
					return false;
				}
				index++;
				if (!reader->ReadToken(delimiter, 2, false))
				{
					goto missingDelimiter;
				}
				int notComma;
				notComma = strcmp(delimiter, ",");
				bool comma;
				comma = notComma == 0;
				notClose = strcmp(delimiter, "}");
				if (notClose == 0 ? comma : !comma)
				{
					if (!comma)
					{
						goto missingDelimiter;
					}
					unsigned int position;
					position = reader->GetPosition();
					int commaLine;
					commaLine = reader->GetLine();
					if (!reader->ReadToken(delimiter, 2, false))
					{
						goto missingDelimiter;
					}
					notClose = strcmp(delimiter, "}");
					if (notClose != 0)
					{
						reader->SetLine(commaLine);
						reader->SetPosition(position);
					}
				}
				notClose = strcmp(delimiter, "}");
			}
			while (notClose != 0);
		}
		return true;
	missingOpener:
		reader->Error("Expecting array delimiter \"{\" at line %d", reader->GetLine());
		return false;
	missingDelimiter:
		reader->Error("Missing array delimiter near line %d", reader->GetLine());
		return false;
	}
#endif
}
