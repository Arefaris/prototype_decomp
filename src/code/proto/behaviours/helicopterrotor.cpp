#include "code/proto/behaviours/helicopterrotor.h"
#include "code/core/refptr.h"
#include "code/engine/driving/carattributes.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/proto/reflectedstubs.h"

namespace engine
{
	extern content::ObjectName gPoseAwakeName;
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_RAW_OFFSET(type, member) \
	((int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10311600
	HelicopterRotorAnimationBehaviour::HelicopterRotorAnimationBehaviour(engine::GameObject* newOwner) :
		engine::Behaviour(newOwner), rotorPowerChangeTime(0.0f), rotorsOn(false), genericProperties(0)
	{
		Listen(0x2b, true);
		Listen(0x31, true);
		bool awake = true;
		owner->SetAttribute<bool>(engine::gPoseAwakeName, awake, false);
	}

	// FUNCTION: ENGINE 0x10311680
	HelicopterRotorAnimationBehaviour::~HelicopterRotorAnimationBehaviour()
	{
		core::SafeRelease(genericProperties);
	}

	// FUNCTION: ENGINE 0x10310000
	void HelicopterRotorAnimationBehaviour::OnMessage(engine::Message* message)
	{
		if (message->type == 0x31)
		{
			switch ((unsigned short)message->id)
			{
			case 0x17:
				rotorsOn = ((SetTurnOnRotorStateMessage*)message)->turnOn;
				break;
			case 0x18:
				rotorPowerChangeTime = ((SetRotorPowerChangeTimeMessage*)message)->time;
				break;
			}
		}
	}

	// FUNCTION: ENGINE 0x1030FFC0
	content::ClassInfo* HelicopterRotorAnimationBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HelicopterRotorAnimationBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103117D0
	content::ClassInfo* RotorParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::RotorParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10311810
	content::ClassInfo* Rotor::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::Rotor";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10312150
	RotorParams::RotorParams() : fadeStart(0.8f)
	{
		float one = engine::driving::gOne;
		fadeEnd = one;
		speed = one;
		axisOfRotation.x = one;
		axisOfRotation.y = one;
		axisOfRotation.z = one;
	}

	// FUNCTION: ENGINE 0x103121C0
	Rotor::Rotor()
	{
	}

	// FUNCTION: ENGINE 0x103109A0
	// NONMATCHING: the array helper of the rotors needs the copy of the engine's int array (its constructor allocates
	// in another register order) and the copies of the rotor, so it is left to the engine
#ifdef NONMATCHING
	content::MemberList* HelicopterRotorAnimationBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, HelicopterRotorAnimationBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<HelicopterRotorAnimationBehaviour, RotorArray>(
				content::GetClassMetaType<Rotor>(), "p"), PROTO_OFFSET(HelicopterRotorAnimationBehaviour, rotors),
				"rotors" },
			{ content::GetReferenceMetaType<HelicopterRotorAnimationBehaviour, HelicopterSolverGenericProperties>("p"),
				PROTO_OFFSET(HelicopterRotorAnimationBehaviour, genericProperties), "genericProperties" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
#endif

	// FUNCTION: ENGINE 0x10311E60
	content::MemberList* RotorParams::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<RotorParams, JointNameArray>(
				content::GetNameMetaType<RotorParams>(true, true, "p"), "p"),
				PROTO_OFFSET(RotorParams, jointNames), "jointNames" },
			{ content::GetMemberNameMetaType<RotorParams, 1>(true, true, "p"),
				PROTO_NAME_OFFSET(RotorParams, geoPrimGroup), "geoPrimGroup" },
			{ content::GetMemberNameMetaType<RotorParams, 2>(true, true, "p"),
				PROTO_NAME_OFFSET(RotorParams, shaderPrimGroup), "shaderPrimGroup" },
			{ content::GetMemberPrimitiveMetaType<RotorParams, float, 3>("p"),
				PROTO_OFFSET(RotorParams, fadeStart), "fadeStart" },
			{ content::GetMemberPrimitiveMetaType<RotorParams, float, 4>("p"),
				PROTO_OFFSET(RotorParams, fadeEnd), "fadeEnd" },
			{ content::GetMemberPrimitiveMetaType<RotorParams, float, 5>("p"),
				PROTO_OFFSET(RotorParams, speed), "speed" },
			{ content::GetMemberVectorMetaType<RotorParams, 6>("p"),
				PROTO_RAW_OFFSET(RotorParams, axisOfRotation), "axisOfRotation" }
		};
		sList.members = sMembers;
		sList.count = 7;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103120B0
	content::MemberList* Rotor::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetClassMetaType<RotorParams>(), PROTO_OFFSET(Rotor, rotorParams), "rotorParams" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103118F0
// FUNCTION: ENGINE 0x10311930
// FUNCTION: ENGINE 0x10311970
// FUNCTION: ENGINE 0x103119B0
// FUNCTION: ENGINE 0x103119F0
// FUNCTION: ENGINE 0x10311CA0
// FUNCTION: ENGINE 0x10311CE0
// FUNCTION: ENGINE 0x10311D20
// FUNCTION: ENGINE 0x10311E00
// FUNCTION: ENGINE 0x10312050
// FUNCTION: ENGINE 0x10310140
// FUNCTION: ENGINE 0x10310280
// FUNCTION: ENGINE 0x10310CA0

// The engine's copies of every member of the array of rotors
template class container::ArrayDynamic<proto::Rotor, container::AllocatorNew>;
// FUNCTION: ENGINE 0x10310040
// FUNCTION: ENGINE 0x10310060
// FUNCTION: ENGINE 0x103100D0
// FUNCTION: ENGINE 0x103102F0
// FUNCTION: ENGINE 0x10310350
// FUNCTION: ENGINE 0x10310370
// FUNCTION: ENGINE 0x10310380
// FUNCTION: ENGINE 0x10310390
// FUNCTION: ENGINE 0x103103B0
// FUNCTION: ENGINE 0x103103C0
// FUNCTION: ENGINE 0x103103D0
// FUNCTION: ENGINE 0x103104E0
// FUNCTION: ENGINE 0x10310520
// FUNCTION: ENGINE 0x10310C20
// FUNCTION: ENGINE 0x10310CC0
// FUNCTION: ENGINE 0x10310D00
// FUNCTION: ENGINE 0x10310D70
// FUNCTION: ENGINE 0x10310E80
// FUNCTION: ENGINE 0x10310ED0
// FUNCTION: ENGINE 0x10310F10
// FUNCTION: ENGINE 0x10310F50
// FUNCTION: ENGINE 0x10311070
// FUNCTION: ENGINE 0x10311160
// FUNCTION: ENGINE 0x103112B0
// FUNCTION: ENGINE 0x10311330
// FUNCTION: ENGINE 0x10311490
// FUNCTION: ENGINE 0x103114E0
// FUNCTION: ENGINE 0x103117A0
// FUNCTION: ENGINE 0x10310170
