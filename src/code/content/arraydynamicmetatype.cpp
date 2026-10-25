// content::ArrayDynamicMetaType: the meta type of a container::ArrayDynamic of items of one element type, and the helper
// that edits the meta system's own arrays (unit 0x105FD3B0 - 0x105FE7C0; the file name is guessed). The unit is the
// counterpart of arraycdynamicmetatype.cpp.
#include "code/content/metatype.h"
#include "code/container/arraydynamic.h"
#include "code/core/heap.h"
#include <new>
#include <string.h>

namespace content
{
	// The heap the meta system makes its values in (0x11276928, name guess)
	extern int gMetaHeap;

	// An array of item pointers (the meta system's own arrays: begin, end, end of storage) and the members of
	// container::ArrayDynamic<void*, AllocatorNew> that the unit instantiates (names guessed). The engine's class is a
	// template instantiated as a whole, so every member is also a function of its own.
	template<class T> struct ArrayOf
	{
		T* begin;
		T* end;
		T* capacityEnd;

		// 0x105FDA90
		ArrayOf()
		{
			begin = 0;
			end = 0;
			capacityEnd = 0;
		}
		// 0x105FDAA0: room for count pointers
		void Init(unsigned int count)
		{
			if (count != 0)
			{
				begin = (T*)operator new[](count * sizeof(T));
				if (begin != 0)
				{
					capacityEnd = begin + count;
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
		// 0x105FD690 / 0x105FD6A0 / 0x105FD6B0
		int Capacity() const
		{
			return capacityEnd - begin;
		}
		T* Begin() const
		{
			return begin;
		}
		int Size() const
		{
			return end - begin;
		}
		// 0x105FD6C0 / 0x105FD6D0
		T* At(int index)
		{
			return begin + index;
		}
		const T* At(int index) const
		{
			return begin + index;
		}
		// 0x105FD6E0: the storage for count pointers, false when there is none
		bool Allocate(unsigned int count)
		{
			if (count != 0)
			{
				begin = (T*)operator new[](count * sizeof(T));
				if (begin != 0)
				{
					capacityEnd = begin + count;
					end = begin;
					return true;
				}
			}
			else
			{
				begin = 0;
			}
			end = 0;
			capacityEnd = 0;
			return false;
		}
		// 0x105FDAF0: takes the pointer at position out, answering the position
		T* Erase(T* position)
		{
			container::Copy(position + 1, end, position);
			end--;
			return position;
		}
		// 0x105FDB20: gives the storage back
		void Release()
		{
			if (begin != 0)
			{
				delete[] begin;
			}
			capacityEnd = 0;
			end = 0;
			begin = 0;
		}
		// 0x105FDB50: empties the array
		void Clear()
		{
			end = begin;
		}
		// 0x105FDB60: moves the pointers from position on up by count and sets the end after them
		void MoveUp(T* position, int count)
		{
			T* last = end;
			T* to = last + count;
			end = to;
			while (last != position)
			{
				last--;
				to--;
				if (to != 0)
				{
					*to = *last;
				}
			}
		}
		// 0x105FDE60: the destructor
		~ArrayOf()
		{
			end = begin;
			if (begin != 0)
			{
				delete[] begin;
			}
		}
		// 0x105FDE80: makes the storage hold count pointers, keeping what fits
		void Reserve(int count);
		// 0x105FDF10: puts count copies of value at position
		static __forceinline void Fill(T* place, unsigned int number, T* const& value)
		{
			T* current = place;
			if (number != 0)
			{
				do
				{
					number--;
					if (current != 0)
					{
						*current = *value;
					}
					current++;
				}
				while (number != 0);
			}
		}
		void InsertCopies(T* position, int count, T* value)
		{
			T* last = end;
			T* to = last + count;
			if (to <= capacityEnd)
			{
				end = to;
				while (last != position)
				{
					last--;
					to--;
					if (to != 0)
					{
						*to = *last;
					}
				}
				Fill(position, count, value);
			}
		}

		// 0x105FE040: the destructor and, when the low bit of flags is set, the array itself
		ArrayOf* Destroy(unsigned char flags)
		{
			end = begin;
			if (begin != 0)
			{
				delete[] begin;
			}
			if (flags & 1)
			{
				operator delete(this);
			}
			return this;
		}
		// 0x105FE070: puts a copy of value at position
		void InsertOne(T* position, T* value)
		{
			T* last = end;
			T* to = last + 1;
			if (to <= capacityEnd)
			{
				T* from = last;
				end = to;
				while (from != position)
				{
					from--;
					to--;
					if (to != 0)
					{
						*to = *from;
					}
				}
				if (position != 0)
				{
					*position = *value;
				}
			}
		}

		// 0x105FD750: copies a pointer to a place that exists
		static void Construct(T* place, T* value)
		{
			if (place != 0)
			{
				*place = *value;
			}
		}
		// 0x105FD770: copies [first, last) to dest, answering the end of the copy
		static T* CopyRange(T* first, T* last, T* dest)
		{
			for (; first != last; first++, dest++)
			{
				*dest = *first;
			}
			return dest;
		}
	};

	typedef ArrayOf<void*> PointerList;

	// RTTI content::VirtualArrayDynamicHelper: the helper for a PointerList (the object at 0x110BABC0 is the one the
	// meta types use for their own arrays)
	class VirtualArrayDynamicHelper : public ArrayDynamicHelperBase
	{
	public:
		virtual int Size(void* array);
		virtual void* Get(void* array, int index);
		virtual void* GetConst(void* array, int index);
		virtual void Insert(void* array, int index, int type);
		virtual void Erase(void* array, int index, int type);
		virtual int Capacity(void* array);
		virtual void Expand(void* array, unsigned int count);
	};

	extern VirtualArrayDynamicHelper gPointerListHelper;

	// FUNCTION: ENGINE 0x105FD3B0
	const char* GetArrayDynamicTypeName()
	{
		return "arraydynamic";
	}

	// FUNCTION: ENGINE 0x105FD3C0
	ArrayDynamicMetaType::ArrayDynamicMetaType(MetaType* newElement, ArrayDynamicHelperBase* newHelper,
		const char* code)
		: MetaType(code)
	{
		element = newElement;
		helper = newHelper;
	}

	// FUNCTION: ENGINE 0x105FD660
	MetaType* ArrayDynamicMetaType::GetElementType()
	{
		return element;
	}

	// FUNCTION: ENGINE 0x105FD670
	void ArrayDynamicMetaType::WriteBinaryShort(WriteContext* context, void* object)
	{
		void* value = object;
		context->writer->Write(&value, 1, 4);
	}

	// FUNCTION: ENGINE 0x105FD690
	template int ArrayOf<void*>::Capacity() const;

	// FUNCTION: ENGINE 0x105FD6A0
	template void** ArrayOf<void*>::Begin() const;

	// FUNCTION: ENGINE 0x105FD6B0
	template int ArrayOf<void*>::Size() const;

	// FUNCTION: ENGINE 0x105FD6C0
	template void** ArrayOf<void*>::At(int);

	// FUNCTION: ENGINE 0x105FD6D0
	template void* const* ArrayOf<void*>::At(int) const;

	// FUNCTION: ENGINE 0x105FD6E0
	template bool ArrayOf<void*>::Allocate(unsigned int);

	// FUNCTION: ENGINE 0x105FD750
	template void ArrayOf<void*>::Construct(void**, void**);

	// FUNCTION: ENGINE 0x105FD770
	template void** ArrayOf<void*>::CopyRange(void**, void**, void**);

	// FUNCTION: ENGINE 0x105FD7C0
	void FillPointers(void** place, unsigned int count, void* const& value)
	{
		void** current = place;
		if (count != 0)
		{
			do
			{
				count--;
				if (current != 0)
				{
					*current = value;
				}
				current++;
			}
			while (count != 0);
		}
	}

	// FUNCTION: ENGINE 0x105FD7F0
	int VirtualArrayDynamicHelper::Size(void* array)
	{
		PointerList* pointers = (PointerList*)array;
		return pointers->end - pointers->begin;
	}

	// FUNCTION: ENGINE 0x105FD800
	void* VirtualArrayDynamicHelper::GetConst(void* array, int index)
	{
		return ((PointerList*)array)->begin[index];
	}

	// FUNCTION: ENGINE 0x105FD810
	void* VirtualArrayDynamicHelper::Get(void* array, int index)
	{
		return ((PointerList*)array)->begin[index];
	}

	// FUNCTION: ENGINE 0x105FD830
	int VirtualArrayDynamicHelper::Capacity(void* array)
	{
		PointerList* pointers = (PointerList*)array;
		return pointers->capacityEnd - pointers->begin;
	}

	// FUNCTION: ENGINE 0x105FD840
	void* ArrayDynamicMetaType::GetItemConst(void* array, int index)
	{
		if (!IsDirect(array))
		{
			return helper->GetConst(array, index);
		}
		return ((PointerList*)array)->begin[index];
	}

	// FUNCTION: ENGINE 0x105FD880
	void* ArrayDynamicMetaType::GetItem(void* array, int index)
	{
		if (!IsDirect(array))
		{
			return helper->Get(array, index);
		}
		return ((PointerList*)array)->begin[index];
	}

	// FUNCTION: ENGINE 0x105FD8C0
	unsigned int ArrayDynamicMetaType::GetCount(void* array)
	{
		if (!IsDirect(array))
		{
			return helper->Size(array);
		}
		PointerList* pointers = (PointerList*)array;
		return pointers->end - pointers->begin;
	}

	// FUNCTION: ENGINE 0x105FD900
	int ArrayDynamicMetaType::CountItems(void* object, int a)
	{
		int result = 1;
		unsigned int count = GetCount(object);
		unsigned int kept = 0;
		void** items = new void*[count];
		unsigned int i;
		for (i = 0; i < count; i++)
		{
			items[kept] = GetItem(object, i);
			if (((MetaTypeView*)element)->Matches(a, items[kept]))
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
			result += ((MetaTypeView*)element)->Count(items[i], a);
		}
		delete[] items;
		return result;
	}

	// FUNCTION: ENGINE 0x105FD9C0
	void ArrayDynamicMetaType::Describe(MemberEntry** cursor, void* object, int a)
	{
		unsigned int count = GetCount(object);
		unsigned int kept = 0;
		void** items = new void*[count];
		unsigned int i;
		for (i = 0; i < count; i++)
		{
			items[kept] = GetItem(object, i);
			if (((MetaTypeView*)element)->Matches(a, items[kept]))
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
			((MetaTypeView*)element)->Describe(cursor, items[i], a);
		}
		delete[] items;
	}

	// FUNCTION: ENGINE 0x105FDA90
	template ArrayOf<void*>::ArrayOf();

	// FUNCTION: ENGINE 0x105FDAA0
	template void ArrayOf<void*>::Init(unsigned int);

	// FUNCTION: ENGINE 0x105FDAF0
	template void** ArrayOf<void*>::Erase(void**);

	// FUNCTION: ENGINE 0x105FDB20
	template void ArrayOf<void*>::Release();

	// FUNCTION: ENGINE 0x105FDB50
	template void ArrayOf<void*>::Clear();

	// FUNCTION: ENGINE 0x105FDB60
	template void ArrayOf<void*>::MoveUp(void**, int);

	// FUNCTION: ENGINE 0x105FDB90
	void VirtualArrayDynamicHelper::Erase(void* array, int index, int type)
	{
		PointerList* pointers = (PointerList*)array;
		((MetaTypeView*)type)->Destroy(pointers->begin[index]);
		pointers->Erase(pointers->begin + index);
	}

	// FUNCTION: ENGINE 0x105FDBE0
	void ArrayDynamicMetaType::WriteBinary(WriteContext* context, const void* object, int a)
	{
		unsigned int count = GetCount((void*)object);
		unsigned int kept = 0;
		void** items = new void*[count];
		unsigned int i;
		for (i = 0; i < count; i++)
		{
			items[kept] = GetItem((void*)object, i);
			if (((MetaTypeView*)element)->Matches(a, items[kept]))
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
			((MetaTypeView*)element)->WriteBinary(context, items[i], a);
		}
		delete[] items;
	}

	// FUNCTION: ENGINE 0x105FDCB0
	void ArrayDynamicMetaType::WriteText(TextWriter* writer, const void* object, int a)
	{
		unsigned int count = GetCount((void*)object);
		unsigned int kept = 0;
		void** items = new void*[count];
		unsigned int i;
		for (i = 0; i < count; i++)
		{
			items[kept] = GetItem((void*)object, i);
			if (((MetaTypeView*)element)->Matches(a, items[kept]))
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
			((MetaTypeView*)element)->WriteText(writer, items[i], a);
			if (kept - i > 1)
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

	// FUNCTION: ENGINE 0x105FDDD0
	void ArrayDynamicMetaType::EraseItem(void* array, int index)
	{
		if (!IsDirect(array))
		{
			helper->Erase(array, index, (int)element);
			return;
		}
		gPointerListHelper.Erase(array, index, (int)element);
	}

	// FUNCTION: ENGINE 0x105FDE20
	void* ArrayDynamicMetaType::Create()
	{
		core::HeapScope scope(gMetaHeap);
		PointerList* array = (PointerList*)operator new(0x10);
		void* result = 0;
		if (array != 0)
		{
			new (array) PointerList();
			result = array;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105FDE60
	template ArrayOf<void*>::~ArrayOf();

	template<class T> void ArrayOf<T>::Reserve(int count)
	{
		int size = end - begin;
		if (count != capacityEnd - begin)
		{
			int keep = count < size ? count : size;
			T* storage = (T*)operator new[](count * sizeof(T));
			if (storage == 0)
			{
				keep = 0;
				count = 0;
			}
			else
			{
				for (int i = 0; i < keep; i++)
				{
					Construct(storage + i, &begin[i]);
				}
			}
			if (begin != 0)
			{
				delete[] begin;
			}
			begin = storage;
			end = storage + keep;
			capacityEnd = storage + count;
		}
	}

	// FUNCTION: ENGINE 0x105FDE80
	template void ArrayOf<void*>::Reserve(int);

	// FUNCTION: ENGINE 0x105FDF10
	// EQUIVALENT: the same loads, stores and branches in the same order; the engine keeps the old end in a second register and puts the count in edi, ours uses other registers for the end, the count and the position (49.4 %)
	template void ArrayOf<void*>::InsertCopies(void**, int, void**);

	// The engine compiles Expand inline into ArrayDynamicMetaType::Reserve as well
	static __forceinline void ExpandPointers(PointerList* pointers, unsigned int count)
	{
		if (pointers->Capacity() == 0)
		{
			pointers->Init(count);
		}
		else if (count + pointers->Size() > (unsigned int)pointers->Capacity())
		{
			pointers->Reserve(count + pointers->Size());
		}
	}

	// FUNCTION: ENGINE 0x105FDF70
	void VirtualArrayDynamicHelper::Expand(void* array, unsigned int count)
	{
		ExpandPointers((PointerList*)array, count);
	}

	// FUNCTION: ENGINE 0x105FDFB0
	void ArrayDynamicMetaType::Reserve(void* array, unsigned int count)
	{
		if (!IsDirect(array))
		{
			helper->Expand(array, count);
			return;
		}
		core::HeapScope scope(gMetaHeap);
		ExpandPointers((PointerList*)array, count);
	}

	// FUNCTION: ENGINE 0x105FE040
	template ArrayOf<void*>* ArrayOf<void*>::Destroy(unsigned char);

	// FUNCTION: ENGINE 0x105FE070
	// EQUIVALENT: the same loads, stores and branches in the same order; the engine keeps the old end in a second register and stores the new end after the comparison, ours uses other registers and stores it before (18.2 %)
	template void ArrayOf<void*>::InsertOne(void**, void**);

	// FUNCTION: ENGINE 0x105FE0B0
	// EQUIVALENT: register allocation: the engine keeps the end in ecx and the position in eax, ours the other way round (91.6 %)
	void VirtualArrayDynamicHelper::Insert(void* array, int index, int type)
	{
		PointerList* pointers = (PointerList*)array;
		if ((unsigned int)(pointers->end - pointers->begin) >= (unsigned int)(pointers->capacityEnd - pointers->begin))
		{
			pointers->Reserve(pointers->end - pointers->begin + 1);
		}
		void** last = pointers->end;
		void** to = last + 1;
		void** position = pointers->begin + index;
		if (to <= pointers->capacityEnd)
		{
			pointers->end = to;
			while (last != position)
			{
				last--;
				to--;
				if (to != 0)
				{
					*to = *last;
				}
			}
			if (position != 0)
			{
				*position = 0;
			}
		}
		void** slot = pointers->begin + index;
		*slot = ((MetaTypeView*)type)->Create();
	}

	// FUNCTION: ENGINE 0x105FE130
	void ArrayDynamicMetaType::InsertItem(void* array, int index)
	{
		if (!IsDirect(array))
		{
			helper->Insert(array, index, (int)element);
			return;
		}
		core::HeapScope scope(gMetaHeap);
		gPointerListHelper.Insert(array, index, (int)element);
	}

	// FUNCTION: ENGINE 0x105FE190
	void ArrayDynamicMetaType::Destroy(void* object)
	{
		PointerList* array = (PointerList*)object;
		unsigned int i = 0;
		for (;;)
		{
			void** items = array->begin;
			if (i >= (unsigned int)(array->end - items))
			{
				break;
			}
			((MetaTypeView*)element)->Destroy(items[i]);
			i++;
		}
		array->end = array->begin;
		if (array->begin != 0)
		{
			delete[] array->begin;
		}
		operator delete(array);
	}

	// FUNCTION: ENGINE 0x105FE1F0
	void ArrayDynamicMetaType::Copy(void* destination, const void* source, int a)
	{
		unsigned int destinationCount = GetCount(destination);
		unsigned int sourceCount = GetCount((void*)source);
		unsigned int i;
		if (destinationCount > sourceCount)
		{
			for (i = destinationCount; (int)i > (int)sourceCount; i--)
			{
				EraseItem(destination, i - 1);
			}
		}
		if (sourceCount > destinationCount)
		{
			Reserve(destination, sourceCount);
		}
		destinationCount = GetCount(destination);
		for (i = 0; i < sourceCount; i++)
		{
			if (i >= destinationCount)
			{
				InsertItem(destination, i);
			}
			((MetaTypeView*)element)->Copy(GetItemConst(destination, i), GetItem((void*)source, i), a);
		}
	}

	// FUNCTION: ENGINE 0x105FE2C0
	void ArrayDynamicMetaType::ReadBinary(ReadContext* context, void* object, int a, int b)
	{
		unsigned int count;
		context->reader->Read(&count, 1, 4);
		Reserve(object, count);
		for (unsigned int i = 0; i < count; i++)
		{
			InsertItem(object, i);
			((MetaTypeView*)element)->ReadBinary(context, GetItemConst(object, i), a, b);
		}
	}

	// FUNCTION: ENGINE 0x105FE340
	// NONMATCHING: the frame holds the saved line and the this pointer the other way round and the error exits are laid out in another order, best 72.2 %
#ifdef NONMATCHING
	bool ArrayDynamicMetaType::ReadText(TextReadStream* reader, void* object, int a, int b)
	{
		char delimiter[2];
		if (reader->ReadToken(delimiter, 2, false))
		{
			int different = strcmp(delimiter, "{");
			if (different == 0)
			{
				unsigned int count = 0;
				int depth = 0;
				unsigned int start = reader->GetPosition();
				int line = reader->GetLine();
				bool trailing = false;
				char buffer[0x800];
				while (reader->ReadToken(buffer, 0x800, false))
				{
					int closer = strcmp(buffer, "}");
					if (closer == 0)
					{
						if (depth == 0)
						{
							if (trailing)
							{
								count--;
							}
							if (count == 0)
							{
								return true;
							}
							reader->SetLine(line);
							reader->SetPosition(start);
							Reserve(object, count);
							for (unsigned int i = 0; i < count; i++)
							{
								InsertItem(object, i);
								if (!((MetaTypeView*)element)->ReadText(reader, GetItemConst(object, i), a, b))
								{
									return false;
								}
								if (count - i > 1)
								{
									if (!reader->ReadToken(delimiter, 2, false))
									{
										goto missingMember;
									}
									int comma = strcmp(delimiter, ",");
									if (comma != 0)
									{
										goto missingMember;
									}
								}
							}
							if (!reader->ReadToken(delimiter, 2, false))
							{
								goto missingEnd;
							}
							int comma = strcmp(delimiter, ",");
							if (comma == 0 && !reader->ReadToken(delimiter, 2, false))
							{
								goto missingEnd;
							}
							int end = strcmp(delimiter, "}");
							if (end == 0)
							{
								return true;
							}
						missingEnd:
							reader->Error("Missing array delimiter near line %d", reader->GetLine());
							return false;
						missingMember:
							reader->Error("Missing array member delimiter \",\" near line %d", reader->GetLine());
							return false;
						}
						depth--;
						if (depth == 0 && count == 0)
						{
							count = 1;
						}
						trailing = false;
					}
					else
					{
						int opener = strcmp(buffer, "{");
						if (opener == 0)
						{
							depth++;
							trailing = false;
						}
						else
						{
							int comma = strcmp(buffer, ",");
							if (comma == 0)
							{
								if (depth == 0)
								{
									count++;
									trailing = true;
								}
								else
								{
									trailing = false;
								}
							}
							else
							{
								if (depth == 0 && count == 0)
								{
									count = 1;
								}
								trailing = false;
							}
						}
					}
				}
				reader->Error("Missing closing array delimiter \"}\" for \"{\" near line %d", line);
				return false;
			}
		}
		reader->Error("Expecting array delimiter \"{\" at line %d", reader->GetLine());
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x105FD3F0
	// EQUIVALENT: register allocation and block layout: the engine keeps the zero in ebp and the common count in edi, ours the other way round, and it lays the loop test blocks out one jump differently (93.6 %)
	bool ArrayDynamicMetaType::Compare(ReadContext* first, const char* firstName, ReadContext* second,
		const char* secondName, int flags, TextWriter* log)
	{
		unsigned int firstCount = 0;
		unsigned int secondCount = 0;
		if (first != 0)
		{
			first->reader->Read(&firstCount, 1, 4);
		}
		if (second != 0)
		{
			second->reader->Read(&secondCount, 1, 4);
		}
		unsigned int common;
		if (firstCount > secondCount)
		{
			common = secondCount;
		}
		else
		{
			common = firstCount;
		}
		log->NewLine();
		log->Write("{", false);
		log->NewLine();
		log->Indent();
		bool same = true;
		if (firstCount != secondCount)
		{
			log->Write("*******************", false);
			log->Write(firstName, false);
			log->WriteUInt(&firstCount);
			log->Write(secondName, false);
			log->WriteUInt(&secondCount);
			log->Write("elements in the array", false);
			log->NewLine();
		}
		for (unsigned int i = 0; i < common; i++)
		{
			bool equal = ((MetaTypeView*)element)->Compare(first, firstName, second, secondName, flags, log);
			same = equal && same;
			if (common - i > 1)
			{
				log->Write(",", false);
				log->NewLine();
			}
		}
		if (firstCount != secondCount)
		{
			log->Write(",", false);
			log->NewLine();
			if (common < firstCount)
			{
				for (; common < firstCount; common++)
				{
					bool equal = ((MetaTypeView*)element)->Compare(first, firstName, 0, secondName, flags, log);
					same = equal && same;
					if (firstCount - common > 1)
					{
						log->Write(",", false);
						log->NewLine();
					}
				}
			}
			else if (common < secondCount)
			{
				for (; common < secondCount; common++)
				{
					bool equal = ((MetaTypeView*)element)->Compare(0, firstName, second, secondName, flags, log);
					same = equal && same;
					if (secondCount - common > 1)
					{
						log->Write(",", false);
						log->NewLine();
					}
				}
			}
			same = false;
		}
		log->Unindent();
		log->NewLine();
		log->Write("}", false);
		return same;
	}


}
