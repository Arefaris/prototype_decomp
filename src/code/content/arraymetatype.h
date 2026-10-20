// content::ArrayMetaType (RTTI): the meta type of an array of items of one element type whose size can change. A
// value is either a heap array the meta system made (item pointers: begin, end) or an array of the engine's, which
// the helper walks. Slot names as in ColourMetaType.
#ifndef CONTENT_ARRAYMETATYPE_H
#define CONTENT_ARRAYMETATYPE_H

#include "code/content/metatype.h"

namespace content
{
	// The edit access of an array for its meta type (RTTI content::ArrayHelperBase / VirtualArrayHelper)
	struct ArrayHelperBase
	{
	public:
		virtual int Size(void* array) = 0;
		virtual void Resize(void* array, unsigned int count, MetaType* element) = 0;
		virtual void* GetConst(void* array, int index) = 0;
		virtual void* Get(void* array, int index) = 0;
	};

	class ArrayMetaType : public MetaType
	{
	public:
		// 0x1060CFA0
		ArrayMetaType(MetaType* newElement, ArrayHelperBase* newHelper, const char* code);

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

		// 0x1060D810 (slot 0)
		bool ReadText(TextReadStream* reader, void* object, int a, int b);
		// 0x1060D790 (slot 1)
		void ReadBinary(ReadContext* context, void* object, int a, int b);
		// 0x1060D540 (slot 2) / 0x1060D4D0 (slot 3)
		void WriteText(TextWriter* writer, const void* object, int a);
		void WriteBinary(WriteContext* context, const void* object, int a);
		// 0x1060CFD0 (slot 4)
		bool Compare(ReadContext* first, const char* firstName, ReadContext* second, const char* secondName,
			int unused, TextWriter* log);
		// 0x1060D380 (slot 6) / 0x1060DB30 (slot 7) / 0x1060D710 (slot 8)
		void* Create();
		void Destroy(void* object);
		void Copy(void* destination, const void* source, int a);
		// 0x1060D3C0 (slot 9) / 0x1060D430 (slot 10) / 0x1060D4A0 (slot 11)
		int CountItems(void* object, int a);
		void Describe(MemberEntry** cursor, void* object, int a);
		void WriteBinaryShort(WriteContext* context, void* object);

		// 0x1060D240
		MetaType* GetElementType();
		// 0x1060D2C0 / 0x1060D300 / 0x1060D340: the item at index and the number of items, through the helper
		// unless the array is the meta system's
		void* GetItem(void* array, int index);
		void* GetItemConst(void* array, int index);
		unsigned int GetCount(void* array);
		// 0x1060D6B0: gives the array that many items (new ones are made by the element type)
		void Resize(void* array, unsigned int count);

		MetaType* element;
		ArrayHelperBase* helper;
	};

	// 0x1060CF80
	const char* GetArrayTypeName();
}

#endif
