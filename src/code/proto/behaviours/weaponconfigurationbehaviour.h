// proto::WeaponConfigurationBehaviour (RTTI and reflection names; base engine::Behaviour) and the records around it:
// proto::WeaponConfiguration (a named set of weapons) and proto::WeaponEntry (one weapon of it with the slot it is
// grabbed in). The behaviour keeps the configurations an object can switch between. Unit 0x10474AE0 - 0x10476A40 (no
// assert path; the file name is a guess). The reflected names are original, the rest is guessed; the reflection, the
// construction and the destruction are reconstructed, the handling of the messages is left to the engine.
#ifndef PROTO_BEHAVIOURS_WEAPONCONFIGURATIONBEHAVIOUR_H
#define PROTO_BEHAVIOURS_WEAPONCONFIGURATIONBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"

namespace proto
{
	// One weapon of a configuration (RTTI proto::WeaponEntry; 0x10 bytes): its name and the slot it is grabbed in
	class WeaponEntry
	{
	public:
		// 0x10474F50
		WeaponEntry();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> weapon;  // +0
		core::Name<core::CaseSensitiveKey> grabSlot;  // +8
	};

	// A named set of weapons (RTTI proto::WeaponConfiguration; 0x18 bytes)
	class WeaponConfiguration
	{
	public:
		typedef container::ArrayDynamic<WeaponEntry, container::AllocatorNew> WeaponArray;

		// 0x10476220
		WeaponConfiguration();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> name;  // +0
		WeaponArray weapons;  // +8
		// The word behind the array (never touched here)
		int unknown14;
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::WeaponEntry>
	{
		enum
		{
			value = 4
		};
	};
	template<> struct ArrayEraseInline<proto::WeaponConfiguration>
	{
		enum
		{
			value = 0
		};
	};
}

#define PROTO_ARRAY_DYNAMIC_HELPER(ELEMENT) \
	namespace content \
	{ \
		template<> class ArrayDynamicHelper<container::ArrayDynamic<ELEMENT, container::AllocatorNew> > \
			: public ArrayDynamicHelperBase \
		{ \
		public: \
			typedef container::ArrayDynamic<ELEMENT, container::AllocatorNew> A; \
			typedef A::Element T; \
			\
			virtual int Size(void* array) \
			{ \
				return ((A*)array)->Size(); \
			} \
			virtual void* Get(void* array, int index) \
			{ \
				return ((A*)array)->begin + index; \
			} \
			virtual void* GetConst(void* array, int index) \
			{ \
				return ((A*)array)->begin + index; \
			} \
			virtual void Insert(void* array, int index, int unused) \
			{ \
				A* a = (A*)array; \
				if (a->Size() >= a->Capacity()) \
				{ \
					a->Reserve(a->Size() + 1); \
				} \
				T* position = a->begin + index; \
				static T sDefault; \
				a->Insert(position, 1, sDefault); \
			} \
			virtual void Erase(void* array, int index, int unused) \
			{ \
				A* a = (A*)array; \
				a->Erase(a->begin + index); \
			} \
			virtual int Capacity(void* array) \
			{ \
				return ((A*)array)->Capacity(); \
			} \
			virtual void Expand(void* array, unsigned int count) \
			{ \
				A* a = (A*)array; \
				if (a->Capacity() == 0) \
				{ \
					a->Allocate(count); \
				} \
				else if (count + a->Size() > a->Capacity()) \
				{ \
					a->Reserve(count + a->Size()); \
				} \
			} \
		}; \
	}

PROTO_ARRAY_DYNAMIC_HELPER(proto::WeaponEntry)
PROTO_ARRAY_DYNAMIC_HELPER(proto::WeaponConfiguration)

namespace proto
{
	class WeaponConfigurationBehaviour : public engine::Behaviour
	{
	public:
		typedef container::ArrayDynamic<WeaponConfiguration, container::AllocatorNew> ConfigurationArray;

		// 0x10476800
		explicit WeaponConfigurationBehaviour(engine::GameObject* newOwner);
		// 0x10476850 (the deleting destructor is 0x10476970)
		virtual ~WeaponConfigurationBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10474FB0): starts with the first configuration
		virtual void Slot1();
		// vftable slot 6 (0x104758A0), left to the engine
		virtual void OnMessage(engine::Message* message);

		ConfigurationArray configurations;  // +0xC
		// The word behind the array
		int unknown18;
		int currentConfiguration;  // +0x1C
	};
}

#endif
