#include "code/proto/worldtriggers.h"
#include "code/math/aabb.h"
#include "code/ravenphysics/collision/collisionobject.h"

namespace math
{
	// FUNCTION: ENGINE 0x103B4130
	// NONMATCHING: the engine loads the three extents before it multiplies them (27.3 %)
#ifdef NONMATCHING
	float AABB::GetVolume() const
	{
		return (max.x - min.x) * ((max.y - min.y) * (max.z - min.z));
	}
#endif
}

namespace proto
{
	// FUNCTION: ENGINE 0x103B42D0
	void Unknown103B42D0(math::AABB* box)
	{
		box->min.x = -6000.0f;
		box->min.y = -6000.0f;
		box->min.z = -6000.0f;
		box->max.x = 6000.0f;
		box->max.y = 6000.0f;
		box->max.z = 6000.0f;
	}
}

namespace content
{
	static const EnumValue sWorldTriggerTypeValues[] =
	{
		{ "water", 0 },
		{ "exclusion", 1 },
		{ "kill", 2 }
	};

	// FUNCTION: ENGINE 0x103B5AA0
	template<> void EnumInfo<proto::WorldTriggerType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::WorldTriggerType";
		*code = "p";
		*values = sWorldTriggerTypeValues;
		*count = 3;
	}
}

namespace content
{
	// The engine's copy (0x103B62C0) runs: its element helper is not recovered
	template<> ArrayDynamicMetaType* GetArrayDynamicMetaType<proto::WorldTriggers, proto::WorldTriggers::TriggerArray>(
		MetaType* element, const char* code);
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x103B5A60
	content::ClassInfo* WorldTriggers::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WorldTriggers";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103B5AE0
	content::ClassInfo* WorldTrigger::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WorldTrigger";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103B5CF0
	content::MemberList* WorldTrigger::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<WorldTrigger, 0>("p"), 0, "aabbLow" },
			{ content::GetMemberVectorMetaType<WorldTrigger, 1>("p"), 0xC, "aabbHigh" },
			{ content::GetEnumMetaType<WorldTriggerType>(), 0x18, "type" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103B6410
	content::MemberList* WorldTriggers::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<WorldTriggers, TriggerArray>(content::GetClassMetaType<WorldTrigger>(), "p"),
				PROTO_OFFSET(WorldTriggers, triggerList), "triggerList" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103B6040
	// NONMATCHING: the engine stores the type, then the minus one, and only then tests the static's guard (88.6 %)
#ifdef NONMATCHING
	WorldTrigger::WorldTrigger()
	{
		physicsObject.value = 0xFFFFFFFF;
		type = WORLD_TRIGGER_WATER;
		static const math::Vector sZero(0.0f, 0.0f, 0.0f);
		aabbLow.x = sZero.x;
		aabbLow.y = sZero.y;
		aabbLow.z = sZero.z;
		aabbHigh.x = sZero.x;
		aabbHigh.y = sZero.y;
		aabbHigh.z = sZero.z;
	}
#endif

	// FUNCTION: ENGINE 0x103B68A0
	WorldTriggers::~WorldTriggers()
	{
		for (WorldTrigger* trigger = triggerList.begin; trigger != triggerList.end; trigger++)
		{
			if (trigger->physicsObject.IsValid())
			{
				ravenphysics::gContext->SleepObject(trigger->physicsObject);
				trigger->physicsObject.DestroyObject();
			}
		}
	}

	// FUNCTION: ENGINE 0x103B6870
	WorldTriggers::WorldTriggers()
	{
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103B5A30
// FUNCTION: ENGINE 0x103B5B40
// FUNCTION: ENGINE 0x103B5C30
// FUNCTION: ENGINE 0x103B5C40
// FUNCTION: ENGINE 0x103B5C50
// FUNCTION: ENGINE 0x103B5C90
// FUNCTION: ENGINE 0x103B5CE0
// FUNCTION: ENGINE 0x103B5EC0
// FUNCTION: ENGINE 0x103B5ED0
// FUNCTION: ENGINE 0x103B64C0
// FUNCTION: ENGINE 0x103B6A00
