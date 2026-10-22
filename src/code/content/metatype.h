// The content library's reflection types (names from the RTTI: content::MetaType, PrimitiveMetaType<T>,
// PrimitiveMetaTypeGetSet<T>, PrimitiveMetaTypeGetSetter<T> and the global PrimitiveMemberGetSetter<C, T>). Only
// the parts the engine's reflected classes instantiate are reconstructed. MetaType has 12 virtual slots of unknown
// meaning (all pure but slot 5); PrimitiveMetaType<T> implements them in the content library (their copies are
// mapped in symbols.txt) and adds Get / Set. Each reflected class builds its meta types in function-local statics.
#ifndef CONTENT_METATYPE_H
#define CONTENT_METATYPE_H

#include "code/content/metastream.h"

namespace content
{
	class MetaType
	{
	public:
		// 0x105FBF40: code is a short type code string ("p", "pn", ...); the constructor stores what 0x105FBB50 derives
		// from it
		explicit MetaType(const char* code);

		// 0x105FBE10: true when the object lies in the directly addressable range (meaning guessed)
		static bool IsDirect(const void* object);

		virtual void Slot0() = 0;
		virtual void Slot1() = 0;
		virtual void Slot2() = 0;
		virtual void Slot3() = 0;
		virtual void Slot4() = 0;
		virtual void Slot5();
		virtual void Slot6() = 0;
		virtual void Slot7() = 0;
		virtual void Slot8() = 0;
		virtual void Slot9() = 0;
		virtual void Slot10() = 0;
		virtual void Slot11() = 0;

		int key;

		// The slots with the arguments the engine's code gives them (the virtual functions above are declared
		// without; these call the slot by its place in the vftable). The slots, with the meaning of what is
		// known: 0 / 1 read a value from its text / binary form, 2 / 3 write it, 4 compares the binary forms of
		// two values and reports the difference as text, 5 asks whether the value has the flags (the base
		// answers by the type's own), 6 makes a value, 7 deletes it, 8 copies it, 9 counts the items the value
		// takes in a table, 10 enters the value in a table of them and 11 writes it in binary through that table
		// The types of the slots, for calls that must read the vftable before the arguments are worked out (the
		// compiler does that for a real virtual call): fetch the address with SlotAddress first, call it after
		typedef bool (__thiscall *ReadTextFunction)(MetaType*, TextReadStream*, void*, int, int);
		typedef void (__thiscall *ReadBinaryFunction)(MetaType*, ReadContext*, void*, int, int);
		typedef void (__thiscall *WriteTextFunction)(MetaType*, TextWriter*, const void*, int);
		typedef void (__thiscall *WriteBinaryFunction)(MetaType*, WriteContext*, const void*, int);
		typedef bool (__thiscall *MatchesFunction)(MetaType*, unsigned int, void*);
		typedef void (__thiscall *CopyFunction)(MetaType*, void*, const void*, int);
		typedef int (__thiscall *CountFunction)(MetaType*, void*, int);
		typedef void (__thiscall *DescribeFunction)(MetaType*, MemberEntry**, void*, int);
		void** SlotAddress(int slot)
		{
			return *(void***)this + slot;
		}
		bool InvokeReadText(TextReadStream* reader, void* object, int a, int b)
		{
			typedef bool (__thiscall *Function)(MetaType*, TextReadStream*, void*, int, int);
			return ((Function)(*(void***)this)[0])(this, reader, object, a, b);
		}
		void InvokeReadBinary(ReadContext* context, void* object, int a, int b)
		{
			typedef void (__thiscall *Function)(MetaType*, ReadContext*, void*, int, int);
			((Function)(*(void***)this)[1])(this, context, object, a, b);
		}
		void InvokeWriteText(TextWriter* writer, const void* object, int a)
		{
			typedef void (__thiscall *Function)(MetaType*, TextWriter*, const void*, int);
			((Function)(*(void***)this)[2])(this, writer, object, a);
		}
		void InvokeWriteBinary(WriteContext* context, const void* object, int a)
		{
			typedef void (__thiscall *Function)(MetaType*, WriteContext*, const void*, int);
			((Function)(*(void***)this)[3])(this, context, object, a);
		}
		bool InvokeCompare(ReadContext* first, const char* firstName, ReadContext* second, const char* secondName,
			int unused, TextWriter* log)
		{
			typedef bool (__thiscall *Function)(MetaType*, ReadContext*, const char*, ReadContext*, const char*, int,
				TextWriter*);
			return ((Function)(*(void***)this)[4])(this, first, firstName, second, secondName, unused, log);
		}
		bool InvokeMatches(unsigned int flags, void* object)
		{
			typedef bool (__thiscall *Function)(MetaType*, unsigned int, void*);
			return ((Function)(*(void***)this)[5])(this, flags, object);
		}
		void* InvokeCreate()
		{
			typedef void* (__thiscall *Function)(MetaType*);
			return ((Function)(*(void***)this)[6])(this);
		}
		void InvokeDestroy(void* object)
		{
			typedef void (__thiscall *Function)(MetaType*, void*);
			((Function)(*(void***)this)[7])(this, object);
		}
		void InvokeCopy(void* destination, const void* source, int a)
		{
			typedef void (__thiscall *Function)(MetaType*, void*, const void*, int);
			((Function)(*(void***)this)[8])(this, destination, source, a);
		}
		int InvokeCount(void* object, int a)
		{
			typedef int (__thiscall *Function)(MetaType*, void*, int);
			return ((Function)(*(void***)this)[9])(this, object, a);
		}
		void InvokeDescribe(MemberEntry** cursor, void* object, int a)
		{
			typedef void (__thiscall *Function)(MetaType*, MemberEntry**, void*, int);
			((Function)(*(void***)this)[10])(this, cursor, object, a);
		}
		void InvokeWriteBinaryShort(WriteContext* context, const void* object)
		{
			typedef void (__thiscall *Function)(MetaType*, WriteContext*, const void*);
			((Function)(*(void***)this)[11])(this, context, object);
		}
	};

	template<class T> class PrimitiveMetaType : public MetaType
	{
	public:
		explicit PrimitiveMetaType(const char* code) : MetaType(code)
		{
		}

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
		virtual T Get(const void* object);
		virtual void Set(void* object, T value);
	};

	template<class T> struct PrimitiveMetaTypeGetSetter
	{
	public:
		PrimitiveMetaTypeGetSetter()
		{
		}
		virtual T Get(const void* object) = 0;
		virtual void Set(void* object, T value) = 0;
	};

	template<class T> class PrimitiveMetaTypeGetSet : public PrimitiveMetaType<T>
	{
	public:
		PrimitiveMetaTypeGetSet(PrimitiveMetaTypeGetSetter<T>* newGetSetter, const char* code)
			: PrimitiveMetaType<T>(code)
		{
			getSetter = newGetSetter;
		}

		virtual T Get(const void* object)
		{
			if (IsDirect(object))
			{
				return *(const T*)object;
			}
			return getSetter->Get(object);
		}
		virtual void Set(void* object, T value)
		{
			if (IsDirect(object))
			{
				*(T*)object = value;
				return;
			}
			getSetter->Set(object, value);
		}

		PrimitiveMetaTypeGetSetter<T>* getSetter;
	};

	// One reflected member: its meta type, an offset (0 for members reached through accessors) and its name
	struct MemberInfo
	{
		MetaType* type;
		int offset;
		const char* name;
	};

	class MetaType;

	// Tests whether an object of a base class is of the derived class (content::IBaseClassCaster)
	struct IBaseClassCaster
	{
		virtual bool IsDerived(void* object) = 0;
	};

	template<class B, class D> struct BaseClassCasterImpl : IBaseClassCaster
	{
		virtual bool IsDerived(void* object)
		{
			return dynamic_cast<D*>((B*)object) != 0;
		}
	};

	// A reflected class's members, and its base class (meta type and caster) when it has one
	struct MemberList
	{
		MemberList()
		{
			members = 0;
			count = 0;
			baseType = 0;
			baseCaster = 0;
		}

		MemberInfo* members;
		int count;
		MetaType* baseType;
		IBaseClassCaster* baseCaster;
	};

	// A reflected class: its name, a version and a type code
	struct ClassInfo
	{
		ClassInfo()
		{
		}

		const char* name;
		unsigned short version;
		const char* code;
	};

	// The offset of a member: the first argument (the member's address in a null object) only selects the template;
	// each member type gets its own copy (MemberOffset<unsigned char> is 0x10568950, <core::Name> 0x10066120)
	template<class T> int MemberOffset(T* member, int offset);

	template<class T> int MemberOffset(T* member, int offset)
	{
		return offset;
	}

	// A meta type with a name and a version: the base of the reflected classes' meta types (RTTI NamedMetaType), kept
	// in a list of all of them, newest first (head 0x1127694C); names other than the class's are guesses
	class NamedMetaType : public MetaType
	{
	public:
		// 0x10600130: makes the type known by name and version
		NamedMetaType(const char* newName, unsigned short newVersion, const char* code);

		// 0x10600170: the newest type, also stored at iterator
		static NamedMetaType* GetFirst(NamedMetaType** iterator);
		// 0x10600190: steps the iterator to the next older type
		static void Next(NamedMetaType** iterator);
		// 0x106001A0: the type that many places down the list (the last one when the list is shorter)
		static NamedMetaType* GetByIndex(unsigned short index);
		// 0x106001D0: the type of that name and version, null for none
		static NamedMetaType* Find(const char* name, unsigned short version);
		// 0x10600230 / 0x10600240 / 0x10600250: the name, the version and the place in the list
		const char* GetName();
		unsigned short GetVersion();
		int GetIndex();

		NamedMetaType* next;
		unsigned short version;
		const char* name;
	};

	class ClassMetaType : public NamedMetaType
	{
	public:
		explicit ClassMetaType(const ClassInfo* info);
		void SetMembers(const MemberList* list);

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

		int unknown14[(0x2c - 0x14) / 4];
	};

	// The meta type of a core::Name member (0x105FCC70; the two flags are unknown)
	class NameMetaType : public MetaType
	{
	public:
		NameMetaType(bool unknown8, bool unknown9, const char* code);

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

		bool flag8;
		bool flag9;
	};

	// 0x10604360
	const char* GetMatrixTypeName();

	// The meta type of a math::Matrix member (0x10604370; the two flags are unknown)
	class MatrixMetaType : public MetaType
	{
	public:
		MatrixMetaType(bool unknown8, bool unknown9, const char* code);

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

		// The slots as the engine's code takes them (see ColourMetaType). A value is a math::Matrix (the 16
		// floats) unless flag9 is set: then it is a rotation, a position and, with flag8, a scale, in binary
		// form three, four and three floats
		// 0x106044A0 (slot 7)
		void Destroy(void* object);
		// 0x10604520 (slot 9): always 1
		int Unknown9(int a, int b);
		// 0x10604530 (slot 10)
		void Describe(MemberEntry** cursor, void* object, int unused);
		// 0x10604550 (slot 11)
		void WriteBinaryShort(WriteContext* context, const void* object);

		bool flag8;
		bool flag9;
	};

	// Creates and deletes the instances an object member points to
	struct MetaInstanceHelperBase
	{
	public:
		virtual void Delete(void* object) = 0;
	};

	template<class T, int N> class MetaInstanceHelper : public MetaInstanceHelperBase
	{
	public:
		virtual void Delete(void* object)
		{
			delete (T*)object;
		}
	};

	// The meta type of a pointer to a reflected object (0x10603860)
	class ObjectMetaType : public MetaType
	{
	public:
		ObjectMetaType(MetaType* type, MetaInstanceHelperBase* helper, const char* code);

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

		MetaType* type;
		MetaInstanceHelperBase* helper;
	};

	// The element access of a container::ArrayDynamic for its meta type
	struct ArrayDynamicHelperBase
	{
	public:
		virtual int Size(void* array) = 0;
		virtual void* Get(void* array, int index) = 0;
		virtual void* GetConst(void* array, int index) = 0;
		virtual void Insert(void* array, int index, int unused) = 0;
		virtual void Erase(void* array, int index, int unused) = 0;
		virtual int Capacity(void* array) = 0;
		virtual void Expand(void* array, unsigned int count) = 0;
	};

	template<class A> class ArrayDynamicHelper : public ArrayDynamicHelperBase
	{
	public:
		typedef typename A::Element T;

		virtual int Size(void* array)
		{
			return ((A*)array)->Size();
		}
		virtual void* Get(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		virtual void* GetConst(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		virtual void Insert(void* array, int index, int unused)
		{
			A* a = (A*)array;
			if (a->Size() >= a->Capacity())
			{
				a->Reserve(a->Size() + 1);
			}
			T* position = a->begin + index;
			static T sDefault;
			a->Insert(position, sDefault);
		}
		virtual void Erase(void* array, int index, int unused)
		{
			A* a = (A*)array;
			a->Erase(a->begin + index);
		}
		virtual int Capacity(void* array)
		{
			return ((A*)array)->Capacity();
		}
		virtual void Expand(void* array, unsigned int count)
		{
			A* a = (A*)array;
			if (a->Capacity() == 0)
			{
				a->Allocate(count);
			}
			else if (count + a->Size() > a->Capacity())
			{
				a->Reserve(count + a->Size());
			}
		}
	};

	// The meta type of a container::ArrayDynamic member (0x105FD3C0)
	class ArrayDynamicMetaType : public MetaType
	{
	public:
		ArrayDynamicMetaType(MetaType* element, ArrayDynamicHelperBase* helper, const char* code);

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

		MetaType* element;
		ArrayDynamicHelperBase* helper;
	};

	// The element access of a container::ArrayCDynamic for its meta type
	struct ArrayCDynamicHelperBase
	{
	public:
		virtual int Size(void* array) = 0;
		virtual void* Get(void* array, int index) = 0;
		virtual void* GetConst(void* array, int index) = 0;
		virtual void Insert(void* array, int index, int unused) = 0;
		virtual void Erase(void* array, int index, int unused) = 0;
	};

	template<class A> class ArrayCDynamicHelper : public ArrayCDynamicHelperBase
	{
	public:
		typedef typename A::Element T;

		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}

		virtual int Size(void* array)
		{
			return ((A*)array)->Size();
		}
		virtual void* Get(void* array, int index)
		{
			return &(*(A*)array)[index];
		}
		virtual void* GetConst(void* array, int index)
		{
			return &(*(A*)array)[index];
		}
		virtual void Insert(void* array, int index, int unused);
		virtual void Erase(void* array, int index, int unused)
		{
			A* a = (A*)array;
			a->Erase(a->Begin() + index);
		}
	};

	// The meta type of a container::ArrayCDynamic member of capacity elements (0x10600280). A value is either one of
	// the arrays the meta system made itself (a heap array of element pointers: begin, end, end of storage) or
	// an array of the engine's, which the helper walks
	class ArrayCDynamicMetaType : public MetaType
	{
	public:
		ArrayCDynamicMetaType(int capacity, MetaType* element, ArrayCDynamicHelperBase* helper, const char* code);

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

		// The slots as the engine's code takes them (see ColourMetaType), and the item access they share (names guessed)
		// 0x10600D70 (slot 0)
		bool ReadText(TextReadStream* reader, void* object, int a, int b);
		// 0x10600D00 (slot 1)
		void ReadBinary(ReadContext* context, void* object, int a, int b);
		// 0x10600950 (slot 2) / 0x10600880 (slot 3): only the items the element type matches, counted first
		void WriteText(TextWriter* writer, const void* object, int a);
		void WriteBinary(WriteContext* context, const void* object, int a);
		// 0x106002B0 (slot 4)
		bool Compare(ReadContext* first, const char* firstName, ReadContext* second, const char* secondName,
			int unused, TextWriter* log);
		// 0x10600AD0 (slot 6) / 0x10600BF0 (slot 7) / 0x10600C50 (slot 8)
		void* Create();
		void Destroy(void* object);
		void Copy(void* destination, const void* source, int a);
		// 0x10600650 (slot 9): 1 and what the element type counts for each matching item
		int CountItems(void* object, int a);
		// 0x10600710 (slot 10): enters the number of matching items and then each of them
		void Describe(MemberEntry** cursor, void* object, int a);
		// 0x10600530 (slot 11): writes the value (the item count) as it stands
		void WriteBinaryShort(WriteContext* context, void* object);

		// 0x10600520
		MetaType* GetElementType();
		// 0x10600590 / 0x106005D0: the item at index, through the helper unless the array is the meta system's
		void* GetItemConst(void* array, int index);
		void* GetItem(void* array, int index);
		// 0x10600610
		unsigned int GetCount(void* array);
		// 0x10600A80 / 0x10600B90: takes the item at index out (deleting it) / makes a new one there
		void EraseItem(void* array, int index);
		void InsertItem(void* array, int index);

		MetaType* element;
		int capacity;
		ArrayCDynamicHelperBase* helper;
	};

	// 0x10600270
	const char* GetArrayCDynamicTypeName();

	// One value of a reflected enumeration
	struct EnumValue
	{
		const char* name;
		int value;
	};

	// The values of enumeration E (a specialisation per enumeration, defined out of line in its unit)
	template<class E> struct EnumInfo
	{
		static void Get(const char** name, const EnumValue** values, int* count, const char** code);
	};

	// The meta type of an enumeration (0x105FE7C0; the second argument is passed as 1, meaning unknown)
	class EnumMetaType : public MetaType
	{
	public:
		EnumMetaType(const char* name, int unknown, const char* code, const EnumValue* values, int count);

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

		int unknown8[(0x1c - 8) / 4];
	};

	// The meta type of a math::Vector member (0x105FB5F0)
	class VectorMetaType : public MetaType
	{
	public:
		explicit VectorMetaType(const char* code);

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
	};

	// The class meta type of T, built on first use from T::GetClassInfo and T::GetMembers
	template<class T> ClassMetaType* GetClassMetaType()
	{
		static ClassMetaType* sType;
		if (sType == 0)
		{
			static ClassMetaType sStorage(T::GetClassInfo());
			sType = &sStorage;
			sStorage.SetMembers(T::GetMembers());
		}
		return sType;
	}

	// The meta type of a core::Name member of class C
	template<class C> NameMetaType* GetNameMetaType(bool unknown8, bool unknown9, const char* code)
	{
		static NameMetaType sType(unknown8, unknown9, code);
		return &sType;
	}

	// The meta type of a math::Matrix member of class C
	template<class C> MatrixMetaType* GetMatrixMetaType(bool unknown8, bool unknown9, const char* code)
	{
		static MatrixMetaType sType(unknown8, unknown9, code);
		return &sType;
	}

	template<class T> ObjectMetaType* GetObjectMetaType(const char* code)
	{
		static MetaInstanceHelper<T, 1> sHelper;
		static ObjectMetaType sType(GetClassMetaType<T>(), &sHelper, code);
		return &sType;
	}

	// The same in a second unit that reflects an object of that class: the engine kept a copy in each of them (at
	// different addresses), and the name tells them apart in symbols.txt
	template<class T> ObjectMetaType* GetObjectMetaTypeCopy(const char* code)
	{
		static MetaInstanceHelper<T, 1> sHelper;
		static ObjectMetaType sType(GetClassMetaType<T>(), &sHelper, code);
		return &sType;
	}

	// Owner only keeps the instantiations of different classes apart
	template<class Owner, class A> ArrayDynamicMetaType* GetArrayDynamicMetaType(MetaType* element, const char* code)
	{
		static ArrayDynamicHelper<A> sHelper;
		static ArrayDynamicMetaType sType(element, &sHelper, code);
		return &sType;
	}

	template<class E> EnumMetaType* GetEnumMetaType()
	{
		static const char* sName;
		static const EnumValue* sValues;
		static int sCount;
		static const char* sCode;
		EnumInfo<E>::Get(&sName, &sValues, &sCount, &sCode);
		static EnumMetaType sType(sName, 1, sCode, sValues, sCount);
		return &sType;
	}

	// Owner only keeps the instantiations of different classes apart
	template<class Owner, class A> ArrayCDynamicMetaType* GetArrayCDynamicMetaType(int capacity, MetaType* element,
		const char* code)
	{
		static ArrayCDynamicHelper<A> sHelper;
		static ArrayCDynamicMetaType sType(capacity, element, &sHelper, code);
		return &sType;
	}

	// The meta types of the primitive and vector members a class reflects member by member: one instance per member
	// (Id tells them apart; the reconstruction uses the source line), so each gets its own copy in the class's unit
	template<class C, class T, int Id> PrimitiveMetaType<T>* GetMemberPrimitiveMetaType(const char* code)
	{
		static PrimitiveMetaType<T> sType(code);
		return &sType;
	}

	template<class C, int Id> VectorMetaType* GetMemberVectorMetaType(const char* code)
	{
		static VectorMetaType sType(code);
		return &sType;
	}

	template<class T> PrimitiveMetaType<T>* GetPrimitiveMetaType(const char* code)
	{
		static PrimitiveMetaType<T> sType(code);
		return &sType;
	}
}

// A member reached through a getter and a setter of class C (RTTI: global namespace)
template<class C, class T> class PrimitiveMemberGetSetter : public content::PrimitiveMetaTypeGetSetter<T>
{
public:
	typedef T (C::*Getter)() const;
	typedef void (C::*Setter)(T);

	PrimitiveMemberGetSetter(Getter newGetter, Setter newSetter)
	{
		getter = newGetter;
		setter = newSetter;
	}

	virtual T Get(const void* object)
	{
		return (((const C*)object)->*getter)();
	}
	virtual void Set(void* object, T value)
	{
		(((C*)object)->*setter)(value);
	}

	Getter getter;
	Setter setter;
};

namespace content
{
	template<class C, class T> MetaType* GetMemberMetaType(T (C::*getter)() const, void (C::*setter)(T),
		const char* code)
	{
		static PrimitiveMemberGetSetter<C, T> sGetSetter(getter, setter);
		static PrimitiveMetaTypeGetSet<T> sType(&sGetSetter, code);
		return &sType;
	}

	// The same for a class that reflects several members of one type through getters and setters: one instance per
	// member (Id tells them apart; the reconstruction uses the source line), so each gets its own copy
	template<class C, class T, int Id> MetaType* GetMemberMetaType(T (C::*getter)() const, void (C::*setter)(T),
		const char* code)
	{
		static PrimitiveMemberGetSetter<C, T> sGetSetter(getter, setter);
		static PrimitiveMetaTypeGetSet<T> sType(&sGetSetter, code);
		return &sType;
	}
}

#endif
