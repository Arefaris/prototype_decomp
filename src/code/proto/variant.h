// proto::Variant<T0 ... T14>: a tagged union of up to fifteen types (the RTTI names the instances with the unused
// parameters filled with proto::NilVariant). The value sits at the start of the object, behind it an int with the index
// of the held type in the table of the type discriminators. Each type has a TypeDiscriminatorImpl<T> with one object per
// type (a function-local static); the table lists the discriminators in the order of the parameters. Member names are
// guesses.
#ifndef PROTO_VARIANT_H
#define PROTO_VARIANT_H

#include <new>
#include <typeinfo>

namespace proto
{
	// The unused type parameters
	struct NilVariant
	{
	};

	template<unsigned int A, unsigned int B> struct VariantMax
	{
		enum
		{
			value = A > B ? A : B
		};
	};

	template<class T0, class T1 = NilVariant, class T2 = NilVariant, class T3 = NilVariant, class T4 = NilVariant,
		class T5 = NilVariant, class T6 = NilVariant, class T7 = NilVariant, class T8 = NilVariant,
		class T9 = NilVariant, class T10 = NilVariant, class T11 = NilVariant, class T12 = NilVariant,
		class T13 = NilVariant, class T14 = NilVariant> class Variant
	{
	public:
		// What the table keeps for a type: its type_info and how to destroy and copy a value of it
		class TypeDiscriminator
		{
		public:
			virtual const type_info* GetType() = 0;
			virtual void Destroy(void* value) = 0;
			virtual void Copy(void* destination, const void* source) = 0;
		};

		template<class T> class TypeDiscriminatorImpl : public TypeDiscriminator
		{
		public:
			virtual const type_info* GetType()
			{
				return &typeid(T);
			}
			virtual void Destroy(void* value)
			{
				((T*)value)->~T();
			}
			virtual void Copy(void* destination, const void* source)
			{
				new (destination) T(*(const T*)source);
			}
		};

		// The one discriminator of T
		template<class T> static TypeDiscriminator* GetDiscriminator()
		{
			static TypeDiscriminatorImpl<T> discriminator;
			return &discriminator;
		}

		// The discriminators in the order of the type parameters
		static TypeDiscriminator** GetTable()
		{
			static TypeDiscriminator* table[15] = {GetDiscriminator<T0>(), GetDiscriminator<T1>(),
				GetDiscriminator<T2>(), GetDiscriminator<T3>(), GetDiscriminator<T4>(), GetDiscriminator<T5>(),
				GetDiscriminator<T6>(), GetDiscriminator<T7>(), GetDiscriminator<T8>(), GetDiscriminator<T9>(),
				GetDiscriminator<T10>(), GetDiscriminator<T11>(), GetDiscriminator<T12>(), GetDiscriminator<T13>(),
				GetDiscriminator<T14>()};
			return table;
		}

		// The index of discriminator in the table, -1 when it is not there
		static int FindIndex(TypeDiscriminator* discriminator)
		{
			TypeDiscriminator** table = GetTable();
			for (int i = 0; i < 15; i++)
			{
				if (discriminator == table[i])
				{
					return i;
				}
			}
			return -1;
		}

		// An empty variant
		Variant()
		{
			index = -1;
		}
		~Variant()
		{
			if (index != -1)
			{
				GetTable()[index]->Destroy(storage);
			}
		}
		// Replaces the held value
		template<class T> Variant& operator=(const T& value)
		{
			if (index != -1)
			{
				GetTable()[index]->Destroy(storage);
			}
			Construct(value);
			return *this;
		}

		// Makes the variant hold value (the previous value is not destroyed)
		template<class T> void Construct(const T& value)
		{
			index = FindIndex(GetDiscriminator<T>());
			new (storage) T(value);
		}

		enum
		{
			size = VariantMax<VariantMax<VariantMax<VariantMax<sizeof(T0), sizeof(T1)>::value,
				VariantMax<sizeof(T2), sizeof(T3)>::value>::value, VariantMax<VariantMax<sizeof(T4), sizeof(T5)>::value,
				VariantMax<sizeof(T6), sizeof(T7)>::value>::value>::value, VariantMax<VariantMax<VariantMax<sizeof(T8),
				sizeof(T9)>::value, VariantMax<sizeof(T10), sizeof(T11)>::value>::value, VariantMax<VariantMax<sizeof(T12),
				sizeof(T13)>::value, sizeof(T14)>::value>::value>::value
		};

		unsigned char storage[size];
		int index;
	};
}

#endif
