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

		core::Name<core::CaseSensitiveKey> name;  // +0
		int value;  // +8
		bool unknownC;
	};

	// A name of the behaviour (RTTI proto::FightVariableName; reflected: name, value)
	struct FightVariableName
	{
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> name;  // +0
		core::Name<core::CaseSensitiveKey> value;  // +8
		bool unknown10;
	};

	// A timer of the behaviour (RTTI proto::FightTimer; reflected: name, time, incrementing)
	struct FightTimer
	{
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> name;  // +0
		float time;  // +8
		bool incrementing;  // +0xC
	};

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

#endif
