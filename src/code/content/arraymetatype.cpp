// content::ArrayMetaType: the meta type of a resizable array of items of one element type (unit 0x1060CF80 -
// 0x1060DB90).
#include "code/content/arraymetatype.h"
#include "code/core/heap.h"
#include <new>

namespace content
{
	// The heap the meta system makes its values in (0x11276928, name guessed)
	extern int gMetaHeap;

	// The array of item pointers the meta system makes (12 bytes; begin, end, one more word)
	struct ItemList
	{
		void** begin;
		void** end;
		int unknown8;

		// 0x1060D250 (the argument is an empty allocator object)
		ItemList(const char& allocator);
		// 0x1060D270
		unsigned int Count() const;
		// 0x1060D600: allocates the pointers and fills them with value (false when there are none or they are
		// already there)
		bool Reserve(unsigned int count, void* const& value);
	};

	// RTTI content::VirtualArrayHelper: the helper for an ItemList (the object at 0x110BB180 is the one the meta
	// types use for their own arrays)
	class VirtualArrayHelper : public ArrayHelperBase
	{
	public:
		virtual int Size(void* array);
		virtual void Resize(void* array, unsigned int count, MetaType* element);
		virtual void* GetConst(void* array, int index);
		virtual void* Get(void* array, int index);
	};

	extern VirtualArrayHelper gItemListHelper;

	// The engine's copy of the container fill (0x105FD7C0, kept in the content library)
	void FillPointers(void** first, unsigned int count, void* const& value);

	// FUNCTION: ENGINE 0x1060CF80
	const char* GetArrayTypeName()
	{
		return "array";
	}

	// FUNCTION: ENGINE 0x1060CFA0
	ArrayMetaType::ArrayMetaType(MetaType* newElement, ArrayHelperBase* newHelper, const char* code)
		: MetaType(code)
	{
		element = newElement;
		helper = newHelper;
	}

	// FUNCTION: ENGINE 0x1060D240
	MetaType* ArrayMetaType::GetElementType()
	{
		return element;
	}

	// FUNCTION: ENGINE 0x1060D250
	ItemList::ItemList(const char& allocator)
	{
		begin = 0;
		end = 0;
	}

	// FUNCTION: ENGINE 0x1060D270
	unsigned int ItemList::Count() const
	{
		return end - begin;
	}

	// FUNCTION: ENGINE 0x1060D280
	int VirtualArrayHelper::Size(void* array)
	{
		ItemList* list = (ItemList*)array;
		return list->end - list->begin;
	}

	// FUNCTION: ENGINE 0x1060D290
	void* VirtualArrayHelper::Get(void* array, int index)
	{
		return ((ItemList*)array)->begin[index];
	}

	// FUNCTION: ENGINE 0x1060D2A0
	void* VirtualArrayHelper::GetConst(void* array, int index)
	{
		return ((ItemList*)array)->begin[index];
	}

	// FUNCTION: ENGINE 0x1060D2C0
	void* ArrayMetaType::GetItem(void* array, int index)
	{
		if (!IsDirect(array))
		{
			return helper->Get(array, index);
		}
		return ((ItemList*)array)->begin[index];
	}

	// FUNCTION: ENGINE 0x1060D300
	void* ArrayMetaType::GetItemConst(void* array, int index)
	{
		if (!IsDirect(array))
		{
			return helper->GetConst(array, index);
		}
		return ((ItemList*)array)->begin[index];
	}

	// FUNCTION: ENGINE 0x1060D340
	unsigned int ArrayMetaType::GetCount(void* array)
	{
		if (!IsDirect(array))
		{
			return helper->Size(array);
		}
		ItemList* list = (ItemList*)array;
		return list->end - list->begin;
	}

	// FUNCTION: ENGINE 0x1060D380
	void* ArrayMetaType::Create()
	{
		core::HeapScope scope(gMetaHeap);
		ItemList* list = (ItemList*)operator new(0xC);
		void* result = 0;
		if (list != 0)
		{
			list->begin = 0;
			list->end = 0;
			result = list;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x1060D3C0
	int ArrayMetaType::CountItems(void* object, int a)
	{
		int result = 1;
		unsigned int count = GetCount(object);
		for (unsigned int i = 0; i < count; i++)
		{
			void** slot = element->SlotAddress(9);
			result += ((MetaType::CountFunction)*slot)(element, GetItemConst(object, i), a);
		}
		return result;
	}

	// FUNCTION: ENGINE 0x1060D430
	void ArrayMetaType::Describe(MemberEntry** cursor, void* object, int a)
	{
		(*cursor)->type = this;
		(*cursor)->object = object;
		*cursor += 1;
		unsigned int count = GetCount(object);
		for (unsigned int i = 0; i < count; i++)
		{
			void** slot = element->SlotAddress(10);
			((MetaType::DescribeFunction)*slot)(element, cursor, GetItemConst(object, i), a);
		}
	}

	// FUNCTION: ENGINE 0x1060D4A0
	void ArrayMetaType::WriteBinaryShort(WriteContext* context, void* object)
	{
		unsigned int count = GetCount(object);
		context->writer->Write(&count, 1, 4);
	}

	// FUNCTION: ENGINE 0x1060D4D0
	void ArrayMetaType::WriteBinary(WriteContext* context, const void* object, int a)
	{
		unsigned int count = GetCount((void*)object);
		context->writer->Write(&count, 1, 4);
		for (unsigned int i = 0; i < count; i++)
		{
			void** slot = element->SlotAddress(3);
			((MetaType::WriteBinaryFunction)*slot)(element, context, GetItemConst((void*)object, i), a);
		}
	}

	// FUNCTION: ENGINE 0x1060D540
	void ArrayMetaType::WriteText(TextWriter* writer, const void* object, int a)
	{
		writer->NewLine();
		writer->Write("{", false);
		writer->NewLine();
		writer->Indent();
		unsigned int count = GetCount((void*)object);
		for (unsigned int i = 0; i < count; i++)
		{
			void** slot = element->SlotAddress(2);
			((MetaType::WriteTextFunction)*slot)(element, writer, GetItemConst((void*)object, i), a);
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

	// FUNCTION: ENGINE 0x1060D600
	// EQUIVALENT: the end of the storage is added the other way round, 59.4%
	bool ItemList::Reserve(unsigned int count, void* const& value)
	{
		if (begin != 0)
		{
			return false;
		}
		if (count > 0)
		{
			unsigned int bytes = count * 4;
			begin = (void**)operator new[](bytes);
			if (begin != 0)
			{
				bytes += (unsigned int)begin;
				end = (void**)bytes;
				FillPointers(begin, count, value);
				return true;
			}
		}
		begin = 0;
		end = 0;
		return false;
	}

	// FUNCTION: ENGINE 0x1060D660
	void VirtualArrayHelper::Resize(void* array, unsigned int count, MetaType* type)
	{
		void* zero = 0;
		unsigned int i = 0;
		((ItemList*)array)->Reserve(count, zero);
		if (count > 0)
		{
			do
			{
				void** item = ((ItemList*)array)->begin + i;
				*item = type->InvokeCreate();
				i++;
			}
			while (i < count);
		}
	}

	// FUNCTION: ENGINE 0x1060D6B0
	void ArrayMetaType::Resize(void* array, unsigned int count)
	{
		if (!IsDirect(array))
		{
			helper->Resize(array, count, element);
			return;
		}
		core::HeapScope scope(gMetaHeap);
		gItemListHelper.Resize(array, count, element);
	}

	// FUNCTION: ENGINE 0x1060D710
	void ArrayMetaType::Copy(void* destination, const void* source, int a)
	{
		unsigned int destinationCount = GetCount(destination);
		unsigned int sourceCount = GetCount((void*)source);
		if (sourceCount != destinationCount)
		{
			Resize(destination, sourceCount);
		}
		for (unsigned int i = 0; i < sourceCount; i++)
		{
			void** slot = element->SlotAddress(8);
			((MetaType::CopyFunction)*slot)(element, GetItem(destination, i), GetItemConst((void*)source, i), a);
		}
	}

	// FUNCTION: ENGINE 0x1060D790
	void ArrayMetaType::ReadBinary(ReadContext* context, void* object, int a, int b)
	{
		unsigned int count;
		context->reader->Read(&count, 1, 4);
		Resize(object, count);
		for (unsigned int i = 0; i < GetCount(object); i++)
		{
			void** slot = element->SlotAddress(1);
			((MetaType::ReadBinaryFunction)*slot)(element, context, GetItem(object, i), a, b);
		}
	}

	// FUNCTION: ENGINE 0x1060DB30
	void ArrayMetaType::Destroy(void* object)
	{
		ItemList* list = (ItemList*)object;
		for (unsigned int i = 0; i < (unsigned int)(list->end - list->begin); i++)
		{
			element->InvokeDestroy(list->begin[i]);
		}
		if (list->begin != 0)
		{
			delete[] list->begin;
		}
		operator delete(list);
	}
}
