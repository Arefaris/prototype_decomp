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

	struct MemberList
	{
		MemberList()
		{
			members = 0;
			count = 0;
			unknown8 = 0;
			unknownC = 0;
		}

		MemberInfo* members;
		int count;
		int unknown8;
		int unknownC;
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

	// 0x10568950: the offset of a member (the first argument is not used)
	int MemberOffset(int unused, int offset);

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
