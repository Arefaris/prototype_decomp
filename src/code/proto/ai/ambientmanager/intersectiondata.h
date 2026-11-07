// proto::IntersectionData (RTTI and reflection names; a plain struct, 0x18 bytes) and proto::IntersectionSpawner (a
// load object): the traffic light cycle of one road intersection. An intersection holds a name and an array of phases
// (proto::IntersectionData::Phase, 0x14 bytes): the states of its lights in that phase (proto::IntersectionData::State)
// and how long the phase lasts; the spawner holds the array of intersections. Unit 0x10430630 - 0x10432C00 (no assert
// path; the file name is a guess). The reflected names are original, the rest is guessed.
#ifndef PROTO_AI_AMBIENTMANAGER_INTERSECTIONDATA_H
#define PROTO_AI_AMBIENTMANAGER_INTERSECTIONDATA_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"

namespace proto
{
	struct IntersectionData
	{
	public:
		// The state of one traffic light
		enum State
		{
			STATE_NONE = 0,
			STATE_GREEN = 1,
			STATE_YELLOW = 2,
			STATE_RED = 3
		};

		struct Phase
		{
		public:
			typedef container::ArrayDynamic<State, container::AllocatorNew> StateArray;

			Phase()
			{
			}
			Phase(const Phase& other) : states(other.states)
			{
				duration = other.duration;
			}
			Phase& operator=(const Phase& other)
			{
				states = other.states;
				duration = other.duration;
				return *this;
			}

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			StateArray states;  // +0
			int unknownC;  // behind the array: its allocator word
			float duration;  // +0x10
		};

		typedef container::ArrayDynamic<Phase, container::AllocatorNew> PhaseArray;

		IntersectionData()
		{
		}
		IntersectionData(const IntersectionData& other) : phases(other.phases), name(other.name)
		{
		}
		IntersectionData& operator=(const IntersectionData& other)
		{
			phases = other.phases;
			name = other.name;
			return *this;
		}

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		PhaseArray phases;  // +0
		int unknownC;  // behind the array: its allocator word
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	class IntersectionSpawner : public content::MetaLoadObject
	{
	public:
		typedef container::ArrayDynamic<IntersectionData, container::AllocatorNew> DataArray;

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		DataArray intersectionData;  // +8
		int unknown14;  // behind the array: its allocator word
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::IntersectionData::State>
	{
		enum
		{
			value = 3
		};
	};

	template<> struct ArrayEraseInline<proto::IntersectionData::Phase>
	{
		enum
		{
			value = 0
		};
	};

	template<> struct ArrayEraseInline<proto::IntersectionData>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	// The state array inserts the element its helper keeps in a static (Default); the insertion is the engine's code
	template<> class ArrayDynamicHelper<container::ArrayDynamic<proto::IntersectionData::State, container::AllocatorNew> >
		: public ArrayDynamicHelperBase
	{
	public:
		typedef container::ArrayDynamic<proto::IntersectionData::State, container::AllocatorNew> A;
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
		virtual void Insert(void* array, int index, int unused);
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

	// The intersection array: the removal is the engine's code
	template<> class ArrayDynamicHelper<container::ArrayDynamic<proto::IntersectionData, container::AllocatorNew> >
		: public ArrayDynamicHelperBase
	{
	public:
		typedef container::ArrayDynamic<proto::IntersectionData, container::AllocatorNew> A;
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
		virtual void Erase(void* array, int index, int unused);
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

#endif
