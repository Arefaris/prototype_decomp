// proto::CharacterBudgetPolicy (RTTI and reflection names) and proto::CharacterBudgetPolicyList (a load object): how
// far from the player a kind of ai character lives (its despawn and freeze distances, which the policy keeps squared),
// how important it is to keep it and what it weighs on the character budget at each level of detail. Unit
// 0x10385AE0 - 0x1038A3FF (no assert path; the file name is a guess); the reflected names are original, the rest is
// guessed.
#ifndef PROTO_CHARACTERBUDGETPOLICY_H
#define PROTO_CHARACTERBUDGETPOLICY_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"

namespace proto
{
	// The squares of the distances a new policy starts with (data of the engine, names guessed)
	extern float gDefaultFreezeDistanceSquared;
	extern float gDefaultDespawnDistanceSquared;

	// RTTI class proto::CharacterBudgetPolicy (0x28 bytes)
	class __declspec(align(8)) CharacterBudgetPolicy
	{
	public:
		// 0x10386880
		CharacterBudgetPolicy();
		inline CharacterBudgetPolicy(const CharacterBudgetPolicy& other) : className(other.className)
		{
			despawnDistanceSquared = other.despawnDistanceSquared;
			freezeDistanceSquared = other.freezeDistanceSquared;
			priority = other.priority;
			weight = other.weight;
			weightLOD2 = other.weightLOD2;
			weightLOD3 = other.weightLOD3;
			needsLoadedCell = other.needsLoadedCell;
		}

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x10385E20 / 0x103868F0: the reflected distance (the policy keeps its square)
		float GetDespawnDistance() const;
		void SetDespawnDistance(float distance);
		// 0x10385E40 / 0x10386910
		float GetFreezeDistance() const;
		void SetFreezeDistance(float distance);

		core::Name<core::CaseSensitiveKey> className;  // +0
		float despawnDistanceSquared;  // +8
		float freezeDistanceSquared;  // +0xC
		int priority;  // +0x10
		int weight;  // +0x14
		int weightLOD2;  // +0x18
		int weightLOD3;  // +0x1C
		bool needsLoadedCell;  // +0x20
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::CharacterBudgetPolicy>
	{
		enum
		{
			value = 0
		};
	};

	// Defined out of line in characterbudgetpolicy.cpp: the engine's copy has the copy constructor inlined
	template<> void ConstructCopyAt<proto::CharacterBudgetPolicy>(proto::CharacterBudgetPolicy* p,
		const proto::CharacterBudgetPolicy& value);
}

namespace content
{
	template<> class ArrayDynamicHelper<container::ArrayDynamic<proto::CharacterBudgetPolicy, container::AllocatorNew> >
		: public ArrayDynamicHelperBase
	{
	public:
		typedef container::ArrayDynamic<proto::CharacterBudgetPolicy, container::AllocatorNew> A;
		typedef A::Element T;

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
			a->Insert(position, 1, sDefault);
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
}


namespace proto
{
	class CharacterBudgetPolicyList : public content::MetaLoadObject
	{
	public:
		typedef container::ArrayDynamic<CharacterBudgetPolicy, container::AllocatorNew> PolicyArray;

		// 0x10389680 (the deleting destructor is 0x10389820)
		CharacterBudgetPolicyList();
		// 0x103896B0
		virtual ~CharacterBudgetPolicyList();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		PolicyArray policies;  // +8
		int unknown14;  // behind the array: its allocator word
	};
}

#endif
