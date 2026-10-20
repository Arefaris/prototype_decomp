// content::ArrayCMetaType: the meta type of a fixed number of items of one element type (unit 0x106061E0 -
// 0x106069D0; the file is content/src/meta/arraycmetatype.cpp).
#include "code/content/arraycmetatype.h"
#include "code/core/debug.h"
#include "code/core/heap.h"
#include <new>
#include <string.h>

namespace content
{
	// The heap the meta system makes its values in (0x11276928, name guessed)
	extern int gMetaHeap;

	// The array of item pointers the meta system makes (12 bytes; the third word is not used)
	struct ItemArray
	{
		void** begin;
		void** end;
		int unknown8;

		ItemArray(unsigned int count)
		{
			if (count > 0)
			{
				unsigned int bytes = count * 4;
				begin = (void**)operator new[](bytes);
				if (begin != 0)
				{
					bytes += (unsigned int)begin;
					end = (void**)bytes;
					return;
				}
			}
			begin = 0;
			end = 0;
		}
	};

	// FUNCTION: ENGINE 0x106061E0
	const char* GetArrayCTypeName()
	{
		return "arrayc";
	}

	// FUNCTION: ENGINE 0x106061F0
	ArrayCMetaType::ArrayCMetaType(int newCount, MetaType* newElement, ArrayCHelperBase* newHelper, const char* code)
		: MetaType(code)
	{
		element = newElement;
		count = newCount;
		helper = newHelper;
	}

	// FUNCTION: ENGINE 0x106062E0
	MetaType* ArrayCMetaType::GetElementType()
	{
		return element;
	}

	// FUNCTION: ENGINE 0x106062F0
	void ArrayCMetaType::WriteBinaryShort(WriteContext* context, void* object)
	{
		OLD_ASSERT_TEXT_AT("..\\..\\..\\code\\content\\src\\meta\\arraycmetatype.cpp", 0x202, false, "false");
	}

	// FUNCTION: ENGINE 0x106063E0
	void* ArrayCMetaType::GetItemConst(void* array, int index)
	{
		if (!IsDirect(array))
		{
			return helper->GetConst(array, index);
		}
		return ((ItemArray*)array)->begin[index];
	}

	// FUNCTION: ENGINE 0x10606420
	void* ArrayCMetaType::GetItem(void* array, int index)
	{
		if (!IsDirect(array))
		{
			return helper->Get(array, index);
		}
		return ((ItemArray*)array)->begin[index];
	}

	// FUNCTION: ENGINE 0x10606460
	void ArrayCMetaType::Copy(void* destination, const void* source, int a)
	{
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			void** slot = element->SlotAddress(8);
			((MetaType::CopyFunction)*slot)(element, GetItemConst(destination, i), GetItem((void*)source, i), a);
		}
	}

	// FUNCTION: ENGINE 0x106064B0
	int ArrayCMetaType::CountItems(void* object, int a)
	{
		int total = 0;
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			void** slot = element->SlotAddress(9);
			total += ((MetaType::CountFunction)*slot)(element, GetItem(object, i), a);
		}
		return total;
	}

	// FUNCTION: ENGINE 0x10606500
	void ArrayCMetaType::Describe(MemberEntry** cursor, void* object, int a)
	{
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			void** slot = *(void***)element + 10;
			((void (__thiscall *)(MetaType*, MemberEntry**, void*, int))*slot)(element, cursor, GetItem(object, i), a);
		}
	}

	// FUNCTION: ENGINE 0x10606560
	void ArrayCMetaType::ReadBinary(ReadContext* context, void* object, int a, int b)
	{
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			void** slot = element->SlotAddress(1);
			((MetaType::ReadBinaryFunction)*slot)(element, context, GetItemConst(object, i), a, b);
		}
	}

	// FUNCTION: ENGINE 0x106065B0
	void ArrayCMetaType::WriteBinary(WriteContext* context, const void* object, int a)
	{
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			void** slot = element->SlotAddress(3);
			((MetaType::WriteBinaryFunction)*slot)(element, context, GetItem((void*)object, i), a);
		}
	}

	// FUNCTION: ENGINE 0x106067A0
	void ArrayCMetaType::WriteText(TextWriter* writer, const void* object, int a)
	{
		writer->NewLine();
		writer->Write("{", false);
		writer->NewLine();
		writer->Indent();
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			void** slot = element->SlotAddress(2);
			((MetaType::WriteTextFunction)*slot)(element, writer, GetItem((void*)object, i), a);
			if (count - i > 1)
			{
				writer->Write(",", false);
				writer->NewLine();
			}
		}
		writer->Unindent();
		writer->NewLine();
		writer->Write("}", false);
	}

	// FUNCTION: ENGINE 0x10606220
	bool ArrayCMetaType::Compare(ReadContext* first, const char* firstName, ReadContext* second,
		const char* secondName, int unused, TextWriter* log)
	{
		log->NewLine();
		log->Write("{", false);
		log->NewLine();
		log->Indent();
		bool result = true;
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			if (element->InvokeCompare(first, firstName, second, secondName, unused, log) && result)
			{
				result = true;
			}
			else
			{
				result = false;
			}
			if (count - i > 1)
			{
				log->Write(",", false);
				log->NewLine();
			}
		}
		log->Unindent();
		log->NewLine();
		log->Write("}", false);
		return result;
	}

	// FUNCTION: ENGINE 0x106068B0
	// EQUIVALENT: the end of the storage is added the other way round, 98.6%
	void* ArrayCMetaType::Create()
	{
		core::HeapScope scope(gMetaHeap);
		ItemArray* array = new ItemArray(count);
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			void** item = array->begin + i;
			*item = element->InvokeCreate();
		}
		return array;
	}

	// FUNCTION: ENGINE 0x10606980
	void ArrayCMetaType::Destroy(void* object)
	{
		ItemArray* array = (ItemArray*)object;
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			element->InvokeDestroy(array->begin[i]);
		}
		if (array != 0)
		{
			if (array->begin != 0)
			{
				delete[] array->begin;
			}
			operator delete(array);
		}
	}

	// FUNCTION: ENGINE 0x10606600
	// NONMATCHING: the error blocks sit in another place, best 31%
#ifdef NONMATCHING
	bool ArrayCMetaType::ReadText(TextReadStream* reader, void* object, int a, int b)
	{
		char token[2];
		if (!reader->ReadToken(token, 2, false))
		{
			goto expectOpen;
		}
		int different;
		different = strcmp(token, "{");
		if (different != 0)
		{
			goto expectOpen;
		}
		unsigned int i;
		i = 0;
		if (count != 0)
		{
			do
			{
				void** slot = element->SlotAddress(0);
				if (!((MetaType::ReadTextFunction)*slot)(element, reader, GetItemConst(object, i), a, b))
				{
					return false;
				}
				if (count - i > 1)
				{
					if (!reader->ReadToken(token, 2, false))
					{
						goto expectComma;
					}
					different = strcmp(token, ",");
					if (different != 0)
					{
						goto expectComma;
					}
				}
				i++;
			}
			while (i < (unsigned int)count);
		}
		if (!reader->ReadToken(token, 2, false))
		{
			goto expectClose;
		}
		different = strcmp(token, ",");
		if (different == 0)
		{
			if (!reader->ReadToken(token, 2, false))
			{
				goto expectClose;
			}
		}
		different = strcmp(token, "}");
		if (different != 0)
		{
			goto expectClose;
		}
		return true;
	expectOpen:
		reader->Error("Expecting array delimiter \"{\" at line %d", reader->GetLine());
		return false;
	expectComma:
		reader->Error("Expecting array member delimiter \",\" at line %d", reader->GetLine());
		return false;
	expectClose:
		reader->Error("Expecting array delimiter at line %d", reader->GetLine());
		return false;
	}
#endif
}
