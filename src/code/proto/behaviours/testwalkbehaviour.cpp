#include "code/proto/behaviours/testwalkbehaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/message.h"
#include "code/math/matrix.h"
#include <math.h>

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace proto
{
	// The messages of type 0x26
	struct TestWalkTargetMessage : public engine::Message
	{
		float x;  // +0xC
		float y;
		float z;
	};

	struct TestWalkSettingsMessage : public engine::Message
	{
		TestWalkBehaviour::WalkSettings* settings;  // +0xC
	};

	// 0x103BA610 (another unit): sends the object a request to move along the vector (name guess)
	void SendWalkIntention(engine::GameObject* object, const math::Vector* direction, int flags);

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10402BB0
	content::ClassInfo* TestWalkBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TestWalkBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10402BF0
	// NONMATCHING: the engine loads the speed constant before it zeroes the register for the flags (94.0 %)
#ifdef NONMATCHING
	TestWalkBehaviour::TestWalkBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), targetX(0.0f),
		targetY(0.0f), targetZ(0.0f), speed(engine::driving::gOne)
	{
		walking = false;
		settingsStored = false;
		settings.end.x = math::kZeroVector.x;
		settings.end.y = math::kZeroVector.y;
		settings.end.z = math::kZeroVector.z;
		settings.mode = 0;
		Listen(0x26, true);
	}
#endif

	// FUNCTION: ENGINE 0x10402C90
	TestWalkBehaviour::~TestWalkBehaviour()
	{
		OnActiveChanged(false);
	}

	// FUNCTION: ENGINE 0x10402CB0
	void TestWalkBehaviour::Slot1()
	{
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x10402D30
	// NONMATCHING: the engine stores the walking flag after the last coordinate (94.4 %)
#ifdef NONMATCHING
	void TestWalkBehaviour::OnMessage(engine::Message* message)
	{
		if (message->type != 0x26)
		{
			return;
		}
		switch ((unsigned short)message->id)
		{
		case 0:
			{
				TestWalkTargetMessage* target = (TestWalkTargetMessage*)message;
				targetX = target->x;
				targetY = target->y;
				targetZ = target->z;
				walking = true;
			}
			break;
		case 0x16:
			if (settingsStored)
			{
				((TestWalkSettingsMessage*)message)->settings = &settings;
				settingsStored = false;
			}
			break;
		case 0x17:
			{
				const WalkSettings* source = ((TestWalkSettingsMessage*)message)->settings;
				settings.start.x = source->start.x;
				settings.start.y = source->start.y;
				settings.start.z = source->start.z;
				settings.end.x = source->end.x;
				settings.end.y = source->end.y;
				settings.end.z = source->end.z;
				settings.mode = source->mode;
				settingsStored = true;
			}
			break;
		}
	}
#endif

	// FUNCTION: ENGINE 0x10402DD0
	// NONMATCHING: the engine takes the squares in the order z, x, y and keeps the differences in SSE registers (14 %)
#ifdef NONMATCHING
	void TestWalkBehaviour::Update(float dt, unsigned short mask)
	{
		if (walking)
		{
			const math::Matrix& matrix = owner->transform->value;
			float dx = targetX - matrix.m[3][0];
			float dy = targetY - matrix.m[3][1];
			float dz = targetZ - matrix.m[3][2];
			float distance = sqrtf(dx * dx + dy * dy + dz * dz);
			if (distance < 5.0f)
			{
				walking = false;
				return;
			}
			float scale = speed / distance;
			math::Vector direction(dx * scale, dy * scale, dz * scale);
			SendWalkIntention(owner, &direction, 0);
		}
	}
#endif

	// FUNCTION: ENGINE 0x10402F10
	content::MemberList* TestWalkBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, TestWalkBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<TestWalkBehaviour, float, 0>("pn"),
				PROTO_OFFSET(TestWalkBehaviour, speed), "speed" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}
