#include "code/proto/behaviours/aimbehaviour.h"
#include "code/proto/messages/movementrestrictionsmessage.h"

namespace engine
{
	namespace driving
	{
		extern const float gZero;
	}
}

namespace proto
{
	// Functions of the movement units that set the aim of an object (0x103B86E0 / 0x103B87F0 / 0x103BDE30 / 0x103BE0E0:
	// hand a point to the movement; 0x103BCB00 / 0x103BCC10: the point the object aims at now)
	void Unknown103B86E0(engine::GameObject* object, const math::Vector* point);
	void Unknown103B87F0(engine::GameObject* object, const math::Vector* point);
	void Unknown103BDE30(engine::GameObject* object, const math::Vector* point, bool flag);
	void Unknown103BE0E0(engine::GameObject* object, const math::Vector* point);
	void Unknown103BCB00(math::Vector* result, engine::GameObject* object);
	void Unknown103BCC10(math::Vector* result, engine::GameObject* object);
	// FUNCTION: ENGINE 0x103C65A0
	content::ClassInfo* AimBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "AimBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103C65E0
	content::ClassInfo* TankAimBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "TankAimBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103C6630
	content::ClassInfo* HelicopterAimBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "HelicopterAimBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103C6670
	AimBehaviour::AimBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), unknownC(false)
	{
		Listen(0x26, true);
		Listen(0x2f, true);
	}

	// FUNCTION: ENGINE 0x103C67A0
	AimBehaviour::~AimBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x103C67B0
	void AimBehaviour::Slot1()
	{
		Listen2(0x40, true);
	}

	// FUNCTION: ENGINE 0x103C67C0
	void AimBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 0x26:
			switch ((unsigned short)message->id)
			{
			case 0x57:
				if (static_cast<AimSlotMessage*>(message)->secondary)
				{
					static_cast<AimSlotMessage*>(message)->slot = &primary;
				}
				else
				{
					static_cast<AimSlotMessage*>(message)->slot = &secondary;
				}
				break;
			case 0x58:
				primary.unknown0 = 0;
				secondary.unknown0 = 0;
				break;
			}
			break;
		case 0x2f:
			switch ((unsigned short)message->id)
			{
			case 2:
				unknownC = static_cast<AimEnableMessage*>(message)->enabled;
				break;
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x103C6960
	void AimBehaviour::Slot9(AimInfo* info, int flags)
	{
		math::Vector point;
		Unknown103BCB00(&point, owner);
		Unknown103B86E0(owner, &point);
	}

	// FUNCTION: ENGINE 0x103C69A0
	void AimBehaviour::Slot12(AimInfo* info, int flags)
	{
		math::Vector point;
		Unknown103BCC10(&point, owner);
		Unknown103B86E0(owner, &point);
	}

	// FUNCTION: ENGINE 0x103C69E0
	void AimBehaviour::Slot13(AimInfo* info, int flags)
	{
		GetMovementRestrictionsMessage message;
		owner->SendMessage(&message);
		MovementRestrictions* restrictions = message.restrictions;
		if (!restrictions)
		{
			Slot9(info, flags);
			return;
		}
		math::Vector point(restrictions->point);
		Unknown103B86E0(owner, &point);
	}

	// FUNCTION: ENGINE 0x103C6AB0
	void AimBehaviour::Slot14(AimInfo* info, int flags)
	{
		Unknown103B86E0(owner, &info->unknown18);
	}

	// FUNCTION: ENGINE 0x103C6AD0
	void AimBehaviour::Slot15(AimInfo* info, int flags, math::Vector* point)
	{
		Unknown103B86E0(owner, point);
	}

	// FUNCTION: ENGINE 0x103C7850
	void AimBehaviour::Update(float dt, unsigned short mask)
	{
		if (dt != engine::driving::gZero)
		{
			if (unknownC)
			{
				Slot9(&primary, 1);
			}
			else
			{
				Unknown103C76C0(dt);
			}
		}
	}

	// FUNCTION: ENGINE 0x103C6AF0
	TankAimBehaviour::TankAimBehaviour(engine::GameObject* newOwner) : AimBehaviour(newOwner)
	{
	}

	// FUNCTION: ENGINE 0x103C6B10
	TankAimBehaviour::~TankAimBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x103C6B20
	void TankAimBehaviour::Slot1()
	{
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x103C6B30
	void TankAimBehaviour::Slot9(AimInfo* info, int flags)
	{
		math::Vector point;
		Unknown103BCB00(&point, owner);
		if (flags & 1)
		{
			Unknown103BDE30(owner, &point, info->flag);
		}
		if (flags)
		{
			Unknown103B87F0(owner, &point);
		}
	}

	// FUNCTION: ENGINE 0x103C6BA0
	void TankAimBehaviour::Slot13(AimInfo* info, int flags)
	{
		GetMovementRestrictionsMessage message;
		owner->SendMessage(&message);
		MovementRestrictions* restrictions = message.restrictions;
		if (!restrictions)
		{
			Slot9(info, flags);
			return;
		}
		math::Vector point(restrictions->point);
		Unknown103BDE30(owner, &point, info->flag);
		Unknown103B87F0(owner, &message.restrictions->point);
	}

	// FUNCTION: ENGINE 0x103C6C90
	void TankAimBehaviour::Slot14(AimInfo* info, int flags)
	{
		if (flags & 1)
		{
			Unknown103BDE30(owner, &info->unknown18, info->flag);
		}
		if (flags)
		{
			Unknown103B87F0(owner, &info->unknown18);
		}
	}

	// FUNCTION: ENGINE 0x103C6CF0
	void TankAimBehaviour::Slot15(AimInfo* info, int flags, math::Vector* point)
	{
		if (flags & 1)
		{
			Unknown103BDE30(owner, point, info->flag);
		}
		if (flags)
		{
			Unknown103B87F0(owner, point);
		}
	}

	// FUNCTION: ENGINE 0x103C6D40
	HelicopterAimBehaviour::HelicopterAimBehaviour(engine::GameObject* newOwner) : AimBehaviour(newOwner)
	{
	}

	// FUNCTION: ENGINE 0x103C6D60
	HelicopterAimBehaviour::~HelicopterAimBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x103C6D70
	void HelicopterAimBehaviour::Slot1()
	{
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x103C6E40
	void HelicopterAimBehaviour::Slot9(AimInfo* info, int flags)
	{
	}

	// FUNCTION: ENGINE 0x103C6F50
	void HelicopterAimBehaviour::Slot14(AimInfo* info, int flags)
	{
		Unknown103BE0E0(owner, &info->unknown18);
	}

	// FUNCTION: ENGINE 0x103C6F70
	void HelicopterAimBehaviour::Slot15(AimInfo* info, int flags, math::Vector* point)
	{
		Unknown103BE0E0(owner, point);
	}

	// FUNCTION: ENGINE 0x103C7060
	// NONMATCHING: the engine adds the x of the point first, ours loads the offset into the register of the first sum
	// (the three loads then sit in other registers; 90 % of the instructions)
#ifdef NONMATCHING
	void AimBehaviour::Slot10(AimInfo* info, engine::GameObject* target, int unused)
	{
		math::Matrix* matrix = target->transform->GetPointer();
		math::Vector point;
		matrix->GetTranslation(point);
		math::Vector position;
		position.x = point.x + info->unknown8.x;
		position.y = info->unknown8.y + point.y;
		position.z = info->unknown8.z + point.z;
		AimTarget aimTarget;
		aimTarget.position.x = position.x;
		aimTarget.position.y = position.y;
		aimTarget.position.z = position.z;
		Unknown103BAE00(owner, &aimTarget);
	}
#endif

	// FUNCTION: ENGINE 0x103C7120
	// NONMATCHING: the engine adds the x of the point first, ours loads the offset into the register of the first sum
	// (the three loads then sit in other registers; 90 % of the instructions)
#ifdef NONMATCHING
	void AimBehaviour::Slot11(AimInfo* info, engine::GameObject* target, int unused)
	{
		math::Matrix* matrix = target->transform->GetPointer();
		math::Vector point;
		matrix->GetTranslation(point);
		math::Vector position;
		position.x = point.x + info->unknown8.x;
		position.y = info->unknown8.y + point.y;
		position.z = info->unknown8.z + point.z;
		AimTarget aimTarget;
		aimTarget.position.x = position.x;
		aimTarget.position.y = position.y;
		aimTarget.position.z = position.z;
		Unknown103BAE00(owner, &aimTarget);
	}
#endif

	// FUNCTION: ENGINE 0x103C73A0
	content::MemberList* AimBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, AimBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103C7750
	content::MemberList* TankAimBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<AimBehaviour>();
		static content::BaseClassCasterImpl<AimBehaviour, TankAimBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103C77D0
	content::MemberList* HelicopterAimBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<AimBehaviour>();
		static content::BaseClassCasterImpl<AimBehaviour, HelicopterAimBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103C6620
// FUNCTION: ENGINE 0x103C6790
// FUNCTION: ENGINE 0x103C6F90
// FUNCTION: ENGINE 0x103C6FC0
// FUNCTION: ENGINE 0x103C6FF0
// FUNCTION: ENGINE 0x103C7000
// FUNCTION: ENGINE 0x103C7030
// FUNCTION: ENGINE 0x103C71E0
// FUNCTION: ENGINE 0x103C7370
