// proto::FightVariablesBehaviour (RTTI and reflection names; base engine::Behaviour): named values for the fight
// system of a game object: integers, names and timers that the fight messages (type 0x23) read and set, and the
// timers' countdown or count-up in the update. Unit 0x10065D60 - 0x10069010 (no assert path; the file name is a
// guess). The reflected names are original, the rest is guessed; only the reflection is reconstructed.
#ifndef PROTO_BEHAVIOURS_FIGHTVARIABLESBEHAVIOUR_H
#define PROTO_BEHAVIOURS_FIGHTVARIABLESBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"

namespace proto
{
	// An integer of the behaviour, found by its name (RTTI proto::FightVariableInt; reflected: name, value)
	struct FightVariableInt
	{
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		FightVariableInt() : name((const char*)0, 1), value(0), unknownC(false)
		{
		}

		core::Name<core::CaseSensitiveKey> name;  // +0
		int value;  // +8
		bool unknownC;
	};

	// A name of the behaviour (RTTI proto::FightVariableName; reflected: name, value)
	struct __declspec(align(8)) FightVariableName
	{
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		FightVariableName() : name((const char*)0, 1), value((const char*)0, 1), unknown10(false)
		{
		}

		core::Name<core::CaseSensitiveKey> name;  // +0
		core::Name<core::CaseSensitiveKey> value;  // +8
		bool unknown10;
	};

	// A timer of the behaviour (RTTI proto::FightTimer; reflected: name, time, incrementing)
	struct FightTimer
	{
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		FightTimer() : name((const char*)0, 1), time(0.0f), incrementing(false)
		{
		}

		core::Name<core::CaseSensitiveKey> name;  // +0
		float time;  // +8
		bool incrementing;  // +0xC
	};

}

namespace container
{
	// The engine moves the elements down in Erase with a call of AssignRange
	template<> struct ArrayEraseInline<proto::FightVariableInt>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::FightVariableName>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::FightTimer>
	{
		enum
		{
			value = 0
		};
	};
}

namespace proto
{
	class FightVariablesBehaviour : public engine::Behaviour
	{
	public:
		typedef container::ArrayDynamic<FightVariableInt, container::AllocatorNew> IntArray;
		typedef container::ArrayDynamic<FightVariableName, container::AllocatorNew> NameArray;
		typedef container::ArrayDynamic<FightTimer, container::AllocatorNew> TimerArray;

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		IntArray varInts;  // +0xC
		int unknown18;
		NameArray varNames;  // +0x1C
		int unknown28;
		TimerArray timers;  // +0x2C
		int unknown38;
		float outOfCombatTimer;  // +0x3C
	};
}

namespace content
{
	// The element access of the behaviour's name array: the engine's insertion makes room with the count version of
	// Insert (the other two arrays' copies insert the single element)
	template<> class ArrayDynamicHelper<proto::FightVariablesBehaviour::NameArray> : public ArrayDynamicHelperBase
	{
	public:
		typedef proto::FightVariablesBehaviour::NameArray A;
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

#endif
