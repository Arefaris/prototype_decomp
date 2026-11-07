#include "code/proto/behaviours/fightvariablesbehaviour.h"
#include "code/engine/fight/fighteventmessage.h"
#include "code/engine/gameobject/gameobject.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10068C20
	FightVariablesBehaviour::FightVariablesBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		outOfCombatTimer(0.0f)
	{
		Listen(0x23, true);
		Listen(2, true);
		Listen(0x39, true);
		Listen2(8, true);
	}

	// FUNCTION: ENGINE 0x10068CB0
	FightVariablesBehaviour::~FightVariablesBehaviour()
	{
	}

	// A free entry has no name or no value
	// FUNCTION: ENGINE 0x100663E0
	// NONMATCHING: the engine keeps the element pointer of the free test in edi across the calls and passes the temporary by address; the registers of this and index are swapped (14 %)
#ifdef NONMATCHING
	bool FightVariablesBehaviour::FindInt(const VarName& name, unsigned int& index)
	{
		index = varInts.Size();
		for (unsigned int i = 0; i < (unsigned int)varInts.Size(); i++)
		{
			if (varInts.begin[i].name == name)
			{
				index = i;
				return true;
			}
			bool isFree = false;
			if (i < index)
			{
				isFree = varInts.begin[i].IsFree();
			}
			if (isFree)
			{
				index = i;
			}
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x100664E0
	void FightVariablesBehaviour::GetInt(VariableIntMessage* message)
	{
		unsigned int index;
		if (FindInt(message->variable, index))
		{
			message->value = varInts.begin[index].value;
			return;
		}
		message->value = 0;
	}

	// FUNCTION: ENGINE 0x10066530
	void FightVariablesBehaviour::SetInt(const VarName& name, int value, bool persistent)
	{
		unsigned int found;
		bool exists = FindInt(name, found);
		unsigned int index = found;
		if (exists || index < (unsigned int)varInts.Size())
		{
			varInts.begin[index].name = name;
			varInts.begin[index].value = value;
			if (persistent)
			{
				varInts.begin[index].unknownC = true;
			}
			engine::FightEventMessage message(0x400);
			owner->SendMessage(&message);
		}
	}

	// FUNCTION: ENGINE 0x100665F0
	// NONMATCHING: see FindInt (name array)
#ifdef NONMATCHING
	bool FightVariablesBehaviour::FindName(const VarName& name, unsigned int& index)
	{
		index = varNames.Size();
		for (unsigned int i = 0; i < (unsigned int)varNames.Size(); i++)
		{
			if (varNames.begin[i].name == name)
			{
				index = i;
				return true;
			}
			bool isFree = false;
			if (i < index)
			{
				isFree = varNames.begin[i].IsFree();
			}
			if (isFree)
			{
				index = i;
			}
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x10066750
	void FightVariablesBehaviour::GetName(VariableNameMessage* message)
	{
		unsigned int index;
		if (FindName(message->variable, index))
		{
			message->value = varNames.begin[index].value;
			return;
		}
		VarName empty((const char*)0, 1);
		message->value = empty;
	}

	// FUNCTION: ENGINE 0x100667D0
	void FightVariablesBehaviour::SetName(const VarName& name, const VarName& value, bool persistent)
	{
		unsigned int found;
		bool exists = FindName(name, found);
		unsigned int index = found;
		if (exists || index < (unsigned int)varNames.Size())
		{
			varNames.begin[index].name = name;
			varNames.begin[index].value = value;
			if (persistent)
			{
				varNames.begin[index].unknown10 = true;
			}
			engine::FightEventMessage message(0x400);
			owner->SendMessage(&message);
		}
	}

	// FUNCTION: ENGINE 0x100668B0
	// NONMATCHING: see FindInt (timer array)
#ifdef NONMATCHING
	bool FightVariablesBehaviour::FindTimer(const VarName& name, unsigned int& index)
	{
		index = timers.Size();
		for (unsigned int i = 0; i < (unsigned int)timers.Size(); i++)
		{
			if (timers.begin[i].name == name)
			{
				index = i;
				return true;
			}
			bool isFree = false;
			if (i < index)
			{
				isFree = timers.begin[i].IsFree();
			}
			if (isFree)
			{
				index = i;
			}
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x100669B0
	void FightVariablesBehaviour::GetTimer(TimerMessage* message)
	{
		unsigned int index;
		if (FindTimer(message->timer, index))
		{
			message->time = timers.begin[index].time;
			message->incrementing = timers.begin[index].incrementing;
			return;
		}
		message->time = 0.0f;
		message->incrementing = false;
	}

	// FUNCTION: ENGINE 0x10066A10
	// NONMATCHING: the engine's two sends share one tail with the flags stored as an immediate; ours keeps a zero in ecx (54 %)
#ifdef NONMATCHING
	void FightVariablesBehaviour::SetTimer(TimerMessage* message)
	{
		unsigned int found;
		bool exists = FindTimer(message->timer, found);
		unsigned int index = found;
		if (exists || index < (unsigned int)timers.Size())
		{
			float oldTime = timers.begin[index].time;
			if (oldTime != 0.0f && message->time == 0.0f)
			{
				engine::FightEventMessage event(0x400);
				owner->SendMessage(&event);
			}
			else if (oldTime <= 0.0f && 0.0f < message->time)
			{
				engine::FightEventMessage event(0x400);
				owner->SendMessage(&event);
			}
			timers.begin[index].name = message->timer;
			timers.begin[index].time = message->time;
			timers.begin[index].incrementing = message->incrementing;
		}
	}
#endif

	// FUNCTION: ENGINE 0x10066E30
	void FightVariablesBehaviour::SetIntFlag(const VarName& name, bool flag)
	{
		unsigned int index;
		if (FindInt(name, index))
		{
			varInts.begin[index].unknownC = flag;
		}
	}

	// FUNCTION: ENGINE 0x10066E70
	void FightVariablesBehaviour::SetNameFlag(const VarName& name, bool flag)
	{
		unsigned int index;
		if (FindName(name, index))
		{
			varNames.begin[index].unknown10 = flag;
		}
	}

	// FUNCTION: ENGINE 0x10065E60
	void FightVariablesBehaviour::GetOutOfCombatTimer(OutOfCombatTimerMessage* message)
	{
		message->time = outOfCombatTimer;
	}

	// FUNCTION: ENGINE 0x10065E70
	void FightVariablesBehaviour::SetOutOfCombatTimer(OutOfCombatTimerMessage* message)
	{
		outOfCombatTimer = message->time;
	}

	// FUNCTION: ENGINE 0x10065E80
	void FightVariablesBehaviour::ResetOutOfCombatTimer()
	{
		outOfCombatTimer = 0.0f;
	}

	// FUNCTION: ENGINE 0x10066B10
	void FightVariablesBehaviour::Reset()
	{
		for (unsigned int i = 0; i < (unsigned int)varInts.Size(); i++)
		{
			VarName empty((const char*)0, 1);
			varInts.begin[i].name = empty;
			varInts.begin[i].value = 0;
		}
		for (unsigned int i = 0; i < (unsigned int)varNames.Size(); i++)
		{
			VarName empty((const char*)0, 1);
			varNames.begin[i].name = empty;
			VarName emptyValue((const char*)0, 1);
			varNames.begin[i].value = emptyValue;
		}
		for (unsigned int i = 0; i < (unsigned int)timers.Size(); i++)
		{
			VarName empty((const char*)0, 1);
			timers.begin[i].name = empty;
			timers.begin[i].time = 0.0f;
			timers.begin[i].incrementing = false;
		}
		ResetOutOfCombatTimer();
	}

	// FUNCTION: ENGINE 0x10066C90
	// NONMATCHING: the zero and the old time swap xmm0 and xmm1 (96.6 %)
#ifdef NONMATCHING
	void FightVariablesBehaviour::Update(float dt, unsigned short mask)
	{
		for (unsigned int i = 0; i < (unsigned int)timers.Size(); i++)
		{
			float oldTime = timers.begin[i].time;
			if (timers.begin[i].incrementing)
			{
				timers.begin[i].time = oldTime + dt;
			}
			else
			{
				timers.begin[i].time = oldTime - dt;
				if (0.0f > timers.begin[i].time)
				{
					timers.begin[i].time = 0.0f;
				}
			}
			if (oldTime != 0.0f && timers.begin[i].time == 0.0f)
			{
				engine::FightEventMessage event(0x400);
				owner->SendMessage(&event);
			}
			else if (oldTime <= 0.0f && 0.0f < timers.begin[i].time)
			{
				engine::FightEventMessage event(0x400);
				owner->SendMessage(&event);
			}
		}
		outOfCombatTimer += dt;
	}
#endif

	// FUNCTION: ENGINE 0x10067C70
	void FightVariablesBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 2:
			Reset();
			break;
		case 0x23:
			switch ((unsigned short)message->id)
			{
			case 0:
				GetInt(static_cast<VariableIntMessage*>(message));
				break;
			case 1:
				SetInt(static_cast<VariableIntSetMessage*>(message)->variable, static_cast<VariableIntSetMessage*>(message)->value, static_cast<VariableIntSetMessage*>(message)->flag);
				break;
			case 2:
				GetName(static_cast<VariableNameMessage*>(message));
				break;
			case 3:
				SetName(static_cast<VariableNameSetMessage*>(message)->variable, static_cast<VariableNameSetMessage*>(message)->value, static_cast<VariableNameSetMessage*>(message)->persistent);
				break;
			case 4:
				GetTimer(static_cast<TimerMessage*>(message));
				break;
			case 5:
				SetTimer(static_cast<TimerMessage*>(message));
				break;
			case 6:
				GetOutOfCombatTimer(static_cast<OutOfCombatTimerMessage*>(message));
				break;
			case 7:
				SetOutOfCombatTimer(static_cast<OutOfCombatTimerMessage*>(message));
				break;
			case 8:
				SetIntFlag(static_cast<VariableFlagMessage*>(message)->variable, static_cast<VariableFlagMessage*>(message)->flag);
				break;
			case 9:
				SetNameFlag(static_cast<VariableFlagMessage*>(message)->variable, static_cast<VariableFlagMessage*>(message)->flag);
				break;
			}
			break;
		case 0x39:
			switch ((unsigned short)message->id)
			{
			case 0:
				Save(static_cast<CheckpointMessage*>(message)->stream);
				break;
			case 1:
				Load(static_cast<CheckpointMessage*>(message)->stream);
				break;
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x10065D60
	content::ClassInfo* FightVariableInt::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FightVariableInt";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10065DA0
	content::ClassInfo* FightVariableName::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FightVariableName";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10065DE0
	content::ClassInfo* FightTimer::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FightTimer";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10065E20
	content::ClassInfo* FightVariablesBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FightVariablesBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x100662C0
	content::MemberList* FightVariableName::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<FightVariableName>(true, true, "p"), PROTO_NAME_OFFSET(FightVariableName, name),
				"name" },
			{ content::GetNameMetaTypeCopy<FightVariableName>(true, true, "p"),
				PROTO_NAME_OFFSET(FightVariableName, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10067A90
	content::MemberList* FightVariableInt::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<FightVariableInt>(true, true, "p"), PROTO_NAME_OFFSET(FightVariableInt, name),
				"name" },
			{ content::GetMemberPrimitiveMetaType<FightVariableInt, int, 0>("p"),
				PROTO_OFFSET(FightVariableInt, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10067B60
	content::MemberList* FightTimer::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<FightTimer>(true, true, "p"), PROTO_NAME_OFFSET(FightTimer, name), "name" },
			{ content::GetMemberPrimitiveMetaType<FightTimer, float, 0>("p"), PROTO_OFFSET(FightTimer, time),
				"time" },
			{ content::GetMemberPrimitiveMetaType<FightTimer, bool, 0>("p"),
				PROTO_OFFSET(FightTimer, incrementing), "incrementing" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10068370
	content::MemberList* FightVariablesBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, FightVariablesBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<FightVariablesBehaviour, IntArray>(
				content::GetClassMetaType<FightVariableInt>(), "p"),
				PROTO_OFFSET(FightVariablesBehaviour, varInts), "varInts" },
			{ content::GetArrayDynamicMetaType<FightVariablesBehaviour, NameArray>(
				content::GetClassMetaType<FightVariableName>(), "p"),
				PROTO_OFFSET(FightVariablesBehaviour, varNames), "varNames" },
			{ content::GetArrayDynamicMetaType<FightVariablesBehaviour, TimerArray>(
				content::GetClassMetaType<FightTimer>(), "p"),
				PROTO_OFFSET(FightVariablesBehaviour, timers), "timers" },
			{ content::GetMemberPrimitiveMetaType<FightVariablesBehaviour, float, 0>("p"),
				PROTO_OFFSET(FightVariablesBehaviour, outOfCombatTimer), "outOfCombatTimer" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10065E90
// FUNCTION: ENGINE 0x10065EC0
// FUNCTION: ENGINE 0x10065F20
// FUNCTION: ENGINE 0x10065FC0
// FUNCTION: ENGINE 0x10066050
// FUNCTION: ENGINE 0x100660D0
// FUNCTION: ENGINE 0x100660E0
// FUNCTION: ENGINE 0x10066120
// FUNCTION: ENGINE 0x10066130
// FUNCTION: ENGINE 0x10066170
// FUNCTION: ENGINE 0x100661B0
// FUNCTION: ENGINE 0x100661F0
// FUNCTION: ENGINE 0x10066200
// FUNCTION: ENGINE 0x10066210
// FUNCTION: ENGINE 0x10066220
// FUNCTION: ENGINE 0x10066230
// FUNCTION: ENGINE 0x10066240
// FUNCTION: ENGINE 0x10066250
// FUNCTION: ENGINE 0x10066260
// FUNCTION: ENGINE 0x10066280
// FUNCTION: ENGINE 0x100662A0
// FUNCTION: ENGINE 0x100663A0
// FUNCTION: ENGINE 0x100663B0
// FUNCTION: ENGINE 0x10067130
// FUNCTION: ENGINE 0x10067190
// FUNCTION: ENGINE 0x100671D0
// FUNCTION: ENGINE 0x10067210
// FUNCTION: ENGINE 0x10067250
// FUNCTION: ENGINE 0x10067290
// FUNCTION: ENGINE 0x100672A0
// FUNCTION: ENGINE 0x100672C0
// FUNCTION: ENGINE 0x100672E0
// FUNCTION: ENGINE 0x10067300
// FUNCTION: ENGINE 0x10067360
// FUNCTION: ENGINE 0x10067380
// FUNCTION: ENGINE 0x100673B0
// FUNCTION: ENGINE 0x100673E0
// FUNCTION: ENGINE 0x10067410
// FUNCTION: ENGINE 0x10067420
// FUNCTION: ENGINE 0x10067450
// FUNCTION: ENGINE 0x10067470
// FUNCTION: ENGINE 0x10067490
// FUNCTION: ENGINE 0x100674F0
// FUNCTION: ENGINE 0x10067520
// FUNCTION: ENGINE 0x10067550
// FUNCTION: ENGINE 0x10067580
// FUNCTION: ENGINE 0x100675B0
// FUNCTION: ENGINE 0x100675C0
// FUNCTION: ENGINE 0x100675E0
// FUNCTION: ENGINE 0x10067600
// FUNCTION: ENGINE 0x10067620
// FUNCTION: ENGINE 0x10067680
// FUNCTION: ENGINE 0x100676A0
// FUNCTION: ENGINE 0x100676D0
// FUNCTION: ENGINE 0x10067700
// FUNCTION: ENGINE 0x10067730
// FUNCTION: ENGINE 0x10067750
// FUNCTION: ENGINE 0x10067780
// FUNCTION: ENGINE 0x100677A0
// FUNCTION: ENGINE 0x100677B0
// FUNCTION: ENGINE 0x100677C0
// FUNCTION: ENGINE 0x100677D0
// FUNCTION: ENGINE 0x10067800
// FUNCTION: ENGINE 0x10067850
// FUNCTION: ENGINE 0x10067890
// FUNCTION: ENGINE 0x100678F0
// FUNCTION: ENGINE 0x10067920
// FUNCTION: ENGINE 0x100679D0
// FUNCTION: ENGINE 0x10067DD0
// FUNCTION: ENGINE 0x10067E30
// FUNCTION: ENGINE 0x10067E90
// FUNCTION: ENGINE 0x10067EF0
// FUNCTION: ENGINE 0x10067F50
// FUNCTION: ENGINE 0x10067FE0
// FUNCTION: ENGINE 0x10068010
// FUNCTION: ENGINE 0x10068040
// FUNCTION: ENGINE 0x10068530
// FUNCTION: ENGINE 0x10068560
// FUNCTION: ENGINE 0x100685A0
// FUNCTION: ENGINE 0x100685D0
// FUNCTION: ENGINE 0x100686D0
// FUNCTION: ENGINE 0x10068800
// FUNCTION: ENGINE 0x10068950
// FUNCTION: ENGINE 0x10068A50
// FUNCTION: ENGINE 0x10068AA0
// FUNCTION: ENGINE 0x10068B10
// FUNCTION: ENGINE 0x10068D10
// FUNCTION: ENGINE 0x10068DF0
// FUNCTION: ENGINE 0x10068EE0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10067100
// FUNCTION: ENGINE 0x10067110
// FUNCTION: ENGINE 0x10067120
// FUNCTION: ENGINE 0x10068250
// FUNCTION: ENGINE 0x100682B0
// FUNCTION: ENGINE 0x10068310
// FUNCTION: ENGINE 0x100689F0
// FUNCTION: ENGINE 0x10068A10
// FUNCTION: ENGINE 0x10068A30
// FUNCTION: ENGINE 0x10068FC0
