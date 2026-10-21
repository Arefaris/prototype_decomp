#include "code/engine/firstpersoncontrolbehaviour.h"
#include "code/engine/camera/camera.h"
#include "code/engine/camera/director.h"
#include "code/engine/gameobject/gameobjectsystem.h"

namespace engine
{
	// 0x107F2800 (another unit)
	int GetControllingPlayer(GameObject* object);

#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1091DF60
	content::ClassInfo* FirstPersonControlBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::FirstPersonControlBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1091DFB0
	void FirstPersonControlBehaviour::Slot1()
	{
		camera::Director* director = camera::Director::Get();
		int player = GetControllingPlayer(controlled);
		director->StartTransition(4, 0.0f, player, 0);
		GameObjectHandle handle = GetHandle(controlled);
		director->NotifyControllers(*(int*)&handle, player);
	}

	// FUNCTION: ENGINE 0x1091EBD0
	FirstPersonControlBehaviour::FirstPersonControlBehaviour(GameObject* newOwner) : Behaviour(newOwner)
	{
		horizSensitivity = 2.5f;
		vertSensitivity = 1.5f;
		vertDeadZone = 0.2f;
		speed = 4.0f;
		invert = false;
		unknown20 = 0.0f;
		unknown24 = 0.0f;
		eyeTransform = 0;
		controlled = 0;
		unknown30 = 0.0f;
		Listen2(4, true);
		Attribute<math::Matrix>* attribute = owner->SetAttributeAndGet<math::Matrix>(gEyePointName,
			math::Matrix::IDENTITY, false);
		controlled = newOwner;
		eyeTransform = attribute;
	}

	// FUNCTION: ENGINE 0x1091E210
	content::MemberList* FirstPersonControlBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, FirstPersonControlBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<FirstPersonControlBehaviour, bool, 0>("p"),
				ENGINE_OFFSET(FirstPersonControlBehaviour, invert), "invert" },
			{ content::GetMemberPrimitiveMetaType<FirstPersonControlBehaviour, float, 0>("p"),
				ENGINE_OFFSET(FirstPersonControlBehaviour, horizSensitivity), "horizSensitivity" },
			{ content::GetMemberPrimitiveMetaType<FirstPersonControlBehaviour, float, 1>("p"),
				ENGINE_OFFSET(FirstPersonControlBehaviour, vertSensitivity), "vertSensitivity" },
			{ content::GetMemberPrimitiveMetaType<FirstPersonControlBehaviour, float, 2>("p"),
				ENGINE_OFFSET(FirstPersonControlBehaviour, vertDeadZone), "vertDeadZone" },
			{ content::GetMemberPrimitiveMetaType<FirstPersonControlBehaviour, float, 3>("p"),
				ENGINE_OFFSET(FirstPersonControlBehaviour, speed), "speed" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1091DFA0
// FUNCTION: ENGINE 0x1091E010
// FUNCTION: ENGINE 0x1091E020
// FUNCTION: ENGINE 0x1091E070
// FUNCTION: ENGINE 0x1091E0B0
// FUNCTION: ENGINE 0x1091E0F0
// FUNCTION: ENGINE 0x1091E130
// FUNCTION: ENGINE 0x1091E170
