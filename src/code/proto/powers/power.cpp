#include "code/proto/powers/power.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10089F50
	content::ClassInfo* Power::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::Power";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10089F90
	content::MemberList* Power::GetMembers()
	{
		static content::MemberList sList;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10089FD0
	Power::~Power()
	{
	}

	// FUNCTION: ENGINE 0x1008A0E0
	Power::Power() : gameObject(0)
	{
	}

	// FUNCTION: ENGINE 0x10089FE0
	Power::Power(const Power& other) : gameObject(other.gameObject)
	{
	}

	// FUNCTION: ENGINE 0x1008A180
	PowerInstance::PowerInstance() : power(0), instance(0)
	{
	}

	// FUNCTION: ENGINE 0x1008A290
	PowerInstance::~PowerInstance()
	{
		core::SafeRelease(power);
	}

	// FUNCTION: ENGINE 0x1008A0B0
	Power* Power::Clone()
	{
		return new Power(*this);
	}

	// FUNCTION: ENGINE 0x1008A100
	content::ClassInfo* PowerInstance::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PowerInstance";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1008A140
	content::ClassInfo* PowerBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PowerBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1008ACF0
	PowerBehaviour::PowerBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
	}

	// FUNCTION: ENGINE 0x1008AD20
	PowerBehaviour::~PowerBehaviour()
	{
		int count = powerInstances.Size();
		for (int i = 0; i < count; i++)
		{
			core::SafeRelease(powerInstances[i].instance);
		}
		powerInstances.Clear();
	}

	// FUNCTION: ENGINE 0x1008A2A0
	void PowerBehaviour::Slot1()
	{
		Listen2(0x10, true);
		unsigned int mask = 0;
		int count = powerInstances.Size();
		for (int i = 0; i < count; i++)
		{
			core::RefAssign(powerInstances[i].instance, powerInstances[i].power->Clone());
			Power* power = powerInstances[i].instance;
			power->gameObject = owner;
			power->Slot9(0.0f);
			unsigned int bits;
			if (power->GetMessageMask(&bits))
			{
				mask |= bits;
			}
		}
		Listen(mask, true);
	}

	// FUNCTION: ENGINE 0x1008A360
	void PowerBehaviour::Update(float dt, unsigned short mask)
	{
		int count = powerInstances.Size();
		for (int i = 0; i < count; i++)
		{
			powerInstances[i].instance->Slot10(dt);
		}
	}

	// FUNCTION: ENGINE 0x1008A3B0
	void PowerBehaviour::OnMessage(engine::Message* message)
	{
		int count = powerInstances.Size();
		for (int i = 0; i < count; i++)
		{
			Power* power = powerInstances[i].instance;
			unsigned int mask;
			power->GetMessageMask(&mask);
			if ((message->type & mask) != 0)
			{
				power->Slot11(message);
			}
		}
	}

	// FUNCTION: ENGINE 0x1008A720
	content::MemberList* PowerInstance::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<PowerInstance, Power>("p"), PROTO_OFFSET(PowerInstance, power),
				"power" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1008A960
	content::MemberList* PowerBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, PowerBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<PowerBehaviour, InstanceArray>(
				content::GetClassMetaType<PowerInstance>(), "p"),
				PROTO_OFFSET(PowerBehaviour, powerInstances), "powerInstances" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Members of the instance array that the engine's unit holds copies of (the code that uses them is not reconstructed)
namespace container
{
	typedef proto::PowerInstance PowerInstance;
	typedef proto::PowerBehaviour::InstanceArray PowerArray;

	template bool PowerArray::Create(unsigned int);
	template PowerInstance* PowerArray::Begin();
	template PowerInstance& PowerArray::operator[](int);
	template const PowerInstance& PowerArray::operator[](int) const;
	template void PowerArray::Free();
	template PowerInstance* PowerArray::Insert(PowerInstance*, unsigned int, const PowerInstance&);
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1008A010
// FUNCTION: ENGINE 0x1008A020
// FUNCTION: ENGINE 0x1008A030
// FUNCTION: ENGINE 0x1008A040
// FUNCTION: ENGINE 0x1008A050
// FUNCTION: ENGINE 0x1008A060
// FUNCTION: ENGINE 0x1008A070
// FUNCTION: ENGINE 0x1008A080
// FUNCTION: ENGINE 0x1008A1A0
// FUNCTION: ENGINE 0x1008A1B0
// FUNCTION: ENGINE 0x1008A1C0
// FUNCTION: ENGINE 0x1008A240
// FUNCTION: ENGINE 0x1008A250
// FUNCTION: ENGINE 0x1008A260
// FUNCTION: ENGINE 0x1008A420
// FUNCTION: ENGINE 0x1008A430
// FUNCTION: ENGINE 0x1008A440
// FUNCTION: ENGINE 0x1008A460
// FUNCTION: ENGINE 0x1008A480
// FUNCTION: ENGINE 0x1008A4E0
// FUNCTION: ENGINE 0x1008A4F0
// FUNCTION: ENGINE 0x1008A500
// FUNCTION: ENGINE 0x1008A510
// FUNCTION: ENGINE 0x1008A530
// FUNCTION: ENGINE 0x1008A560
// FUNCTION: ENGINE 0x1008A5A0
// FUNCTION: ENGINE 0x1008A5C0
// FUNCTION: ENGINE 0x1008A5E0
// FUNCTION: ENGINE 0x1008A610
// FUNCTION: ENGINE 0x1008A670
// FUNCTION: ENGINE 0x1008A710
// FUNCTION: ENGINE 0x1008A7C0
// FUNCTION: ENGINE 0x1008A820
// FUNCTION: ENGINE 0x1008A850
// FUNCTION: ENGINE 0x1008A8A0
// FUNCTION: ENGINE 0x1008A900
// FUNCTION: ENGINE 0x1008AA40
// FUNCTION: ENGINE 0x1008AA80
// EQUIVALENT: the address of the element behind the erased one is computed with a separate add where ours folds it into the lea (78.3 %)
// FUNCTION: ENGINE 0x1008AAE0
// FUNCTION: ENGINE 0x1008ABE0
// FUNCTION: ENGINE 0x1008AC20
// FUNCTION: ENGINE 0x1008AC60
// FUNCTION: ENGINE 0x1008ACB0
// FUNCTION: ENGINE 0x1008ADD0
// FUNCTION: ENGINE 0x1008AE80
