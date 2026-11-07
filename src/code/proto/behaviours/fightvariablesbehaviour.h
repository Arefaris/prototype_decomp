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
#include "code/proto/fightitems/motion/motionmessages2.h"

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

		bool IsFree() const
		{
			return name == core::Name<core::CaseSensitiveKey>((const char*)0, 1) || value == 0;
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

		bool IsFree() const
		{
			return name == core::Name<core::CaseSensitiveKey>((const char*)0, 1) || value == core::Name<core::CaseSensitiveKey>((const char*)0, 1);
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

		bool IsFree() const
		{
			return name == core::Name<core::CaseSensitiveKey>((const char*)0, 1) || (!(0.0f < time) && !incrementing);
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
	// The stream the checkpoint messages carry (a buffer with a cursor at +4; the class is not reconstructed, the name is a guess)
	struct CheckpointStream;

	// RTTI: proto::CheckpointMessage: the base of the messages that save and load the state of an object in a
	// checkpoint (message type 0x39; ids 0 and 1 are the serialize and unserialize messages)
	struct CheckpointMessage : public engine::IntrusiveMessage
	{
	public:
		explicit CheckpointMessage(short newId) : engine::IntrusiveMessage(0x39, newId)
		{
		}
		virtual ~CheckpointMessage()
		{
		}

		CheckpointStream* stream;  // +0xC
	};

	// The layout of the fight variables messages 8 and 9: a variable name and a flag (names guessed)
	struct VariableFlagMessage : public FightVariablesMessage
	{
	public:
		VariableFlagMessage(short newId, const core::Name<core::CaseSensitiveKey>& newVariable, bool newFlag) : FightVariablesMessage(newId), variable(newVariable), flag(newFlag)
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> variable;  // +0x10
		bool flag;  // +0x18
	};

	class FightVariablesBehaviour : public engine::Behaviour
	{
	public:
		typedef container::ArrayDynamic<FightVariableInt, container::AllocatorNew> IntArray;
		typedef container::ArrayDynamic<FightVariableName, container::AllocatorNew> NameArray;
		typedef container::ArrayDynamic<FightTimer, container::AllocatorNew> TimerArray;

		// 0x10068C20
		explicit FightVariablesBehaviour(engine::GameObject* newOwner);
		// 0x10068CB0 (deleting destructor 0x10068FC0)
		virtual ~FightVariablesBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 4 (0x10066C90) and 6 (0x10067C70)
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		IntArray varInts;  // +0xC
		int unknown18;
		NameArray varNames;  // +0x1C
		int unknown28;
		TimerArray timers;  // +0x2C
		int unknown38;
		float outOfCombatTimer;  // +0x3C

		typedef core::Name<core::CaseSensitiveKey> VarName;

		// The find functions leave the index of the entry with the name, or else of the first free entry, in index
		// (the size when there is none); true when the name is present (names guessed)
		bool FindInt(const VarName& name, unsigned int& index);
		bool FindName(const VarName& name, unsigned int& index);
		bool FindTimer(const VarName& name, unsigned int& index);
		void GetInt(VariableIntMessage* message);
		void SetInt(const VarName& name, int value, bool flag);
		void GetName(VariableNameMessage* message);
		void SetName(const VarName& name, const VarName& value, bool flag);
		void GetTimer(TimerMessage* message);
		void SetTimer(TimerMessage* message);
		void Reset();
		void SetIntFlag(const VarName& name, bool flag);
		void SetNameFlag(const VarName& name, bool flag);
		void GetOutOfCombatTimer(OutOfCombatTimerMessage* message);
		void SetOutOfCombatTimer(OutOfCombatTimerMessage* message);
		void ResetOutOfCombatTimer();
		// The checkpoint handlers (the messages 0x39, ids 0 and 1); not reconstructed
		void Save(CheckpointStream* stream);
		void Load(CheckpointStream* stream);
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
