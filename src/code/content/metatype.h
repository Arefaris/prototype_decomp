// The content library's reflection types (names from the RTTI: content::MetaType, PrimitiveMetaType<T>,
// PrimitiveMetaTypeGetSet<T>, PrimitiveMetaTypeGetSetter<T> and the global PrimitiveMemberGetSetter<C, T>). Only
// the parts the engine's reflected classes instantiate are reconstructed. MetaType has 12 virtual slots of unknown
// meaning (all pure but slot 5); PrimitiveMetaType<T> implements them in the content library (their copies are
// mapped in symbols.txt) and adds Get / Set. Each reflected class builds its meta types in function-local statics.
#ifndef CONTENT_METATYPE_H
#define CONTENT_METATYPE_H

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

	template<class T> class PrimitiveMetaTypeGetSetter
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

	// A meta type with a name and a member list (another unit, 0x105FA750 / 0x105FA790; 0x2C bytes)
	class NamedMetaType : public MetaType
	{
	public:
		explicit NamedMetaType(const char* code) : MetaType(code)
		{
		}
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

		int unknown8[(0x2c - 8) / 4];
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

		bool flag8;
		bool flag9;
	};

	// Creates and deletes the instances an object member points to
	class MetaInstanceHelperBase
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
	class ArrayDynamicHelperBase
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

	// Owner only keeps the instantiations of different classes apart
	template<class Owner, class A> ArrayDynamicMetaType* GetArrayDynamicMetaType(MetaType* element, const char* code)
	{
		static ArrayDynamicHelper<A> sHelper;
		static ArrayDynamicMetaType sType(element, &sHelper, code);
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
}

#endif
