// content::ArrayCMetaType (RTTI): the meta type of a fixed number of items of one element type. A value is either
// a heap array the meta system made (the item pointers: begin, end, one more word) or an array of the engine's,
// which the helper walks. Slot names as in ColourMetaType.
#ifndef CONTENT_ARRAYCMETATYPE_H
#define CONTENT_ARRAYCMETATYPE_H

#include "code/content/metatype.h"

namespace content
{
	// The element access of a fixed array for its meta type (RTTI content::VirtualArrayCHelper, two slots)
	struct ArrayCHelperBase
	{
	public:
		virtual void* Get(void* array, int index) = 0;
		virtual void* GetConst(void* array, int index) = 0;
	};

	class ArrayCMetaType : public MetaType
	{
	public:
		// 0x106061F0
		ArrayCMetaType(int newCount, MetaType* newElement, ArrayCHelperBase* newHelper, const char* code);

		virtual void Slot0();
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot6();
		virtual void Slot7();
		virtual void Slot8();
		virtual void Slot9();
		virtual void Slot10();
		virtual void Slot11();

		// 0x10606600 (slot 0)
		bool ReadText(TextReadStream* reader, void* object, int a, int b);
		// 0x10606560 (slot 1)
		void ReadBinary(ReadContext* context, void* object, int a, int b);
		// 0x106067A0 (slot 2) / 0x106065B0 (slot 3)
		void WriteText(TextWriter* writer, const void* object, int a);
		void WriteBinary(WriteContext* context, const void* object, int a);
		// 0x10606220 (slot 4)
		bool Compare(ReadContext* first, const char* firstName, ReadContext* second, const char* secondName,
			int unused, TextWriter* log);
		// 0x106068B0 (slot 6) / 0x10606980 (slot 7) / 0x10606460 (slot 8)
		void* Create();
		void Destroy(void* object);
		void Copy(void* destination, const void* source, int a);
		// 0x106064B0 (slot 9): what the element type counts for each item
		int CountItems(void* object, int a);
		// 0x10606500 (slot 10)
		void Describe(MemberEntry** cursor, void* object, int a);
		// 0x106062F0 (slot 11): not used (the engine asserts)
		void WriteBinaryShort(WriteContext* context, void* object);

		// 0x106062E0
		MetaType* GetElementType();
		// 0x106063E0 / 0x10606420: the item at index, through the helper unless the array is the meta system's
		void* GetItemConst(void* array, int index);
		void* GetItem(void* array, int index);

		MetaType* element;
		int count;
		ArrayCHelperBase* helper;
	};

	// 0x106061E0
	const char* GetArrayCTypeName();

	// The element access of a container::ArrayC<T, N> (RTTI content::ArrayCHelper<A>)
	template<class A> class ArrayCHelper : public ArrayCHelperBase
	{
	public:
		virtual void* Get(void* array, int index)
		{
			return &(*(A*)array)[index];
		}
		virtual void* GetConst(void* array, int index)
		{
			return &(*(A*)array)[index];
		}
	};

	// The meta type of a container::ArrayC member of count elements. Owner only keeps the instantiations of different
	// classes apart; the engine's call passes the element size as the second argument, which is not used
	template<class Owner, class A> ArrayCMetaType* GetArrayCMetaType(int count, int unused, MetaType* element,
		const char* code)
	{
		static ArrayCHelper<A> sHelper;
		static ArrayCMetaType sType(count, element, &sHelper, code);
		return &sType;
	}
}

#endif
