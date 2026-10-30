#include "code/proto/zonebehaviour.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace content
{
	static const EnumValue sZoneTypeValues[] =
	{
		{ "Military", 0 },
		{ "Outbreak", 1 },
		{ "War", 2 }
	};

	// FUNCTION: ENGINE 0x10572670
	template<> void EnumInfo<proto::ZoneBehaviour::ZoneType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::ZoneBehaviour::ZoneType";
		*code = "p";
		*values = sZoneTypeValues;
		*count = 3;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x105726B0
	content::ClassInfo* ZoneBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ZoneBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10565930
	float ZoneBehaviour::GetZoneStrength() const
	{
		return targetStrength;
	}

	// FUNCTION: ENGINE 0x10572A70
	float ZoneBehaviour::GetStrength() const
	{
		return strength;
	}

	// FUNCTION: ENGINE 0x10572C90
	void ZoneBehaviour::SetZoneStrength(float value)
	{
		if (targetStrength != value)
		{
			if (!(value >= 0.0f))
			{
				value = 0.0f;
			}
			if (0.0f <= value - engine::driving::gOne)
			{
				value = engine::driving::gOne;
			}
			targetStrength = value;
			if (initialised)
			{
				UpdateEffects();
			}
		}
	}

	// FUNCTION: ENGINE 0x10573190
	content::MemberList* ZoneBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, ZoneBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ZoneBehaviour, float, 0>("pn"), PROTO_OFFSET(ZoneBehaviour, radius),
				"radius" },
			{ content::GetEnumMetaType<ZoneType>(), 0x24, "zoneType" },
			{ content::GetMemberMetaType<ZoneBehaviour, float, 0>(&ZoneBehaviour::GetZoneStrength,
				&ZoneBehaviour::SetZoneStrength, "pn"), 0, "zoneStrength" },
			{ content::GetMemberPrimitiveMetaType<ZoneBehaviour, bool, 0>("pn"),
				PROTO_OFFSET(ZoneBehaviour, renderEffectsState), "renderEffectsState" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}
}

template class PrimitiveMemberGetSetter<proto::ZoneBehaviour, float>;

// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x10572A80
// FUNCTION: ENGINE 0x10572B10
// FUNCTION: ENGINE 0x10572B20
// FUNCTION: ENGINE 0x10572CF0
// FUNCTION: ENGINE 0x10572D30
// FUNCTION: ENGINE 0x10572D70
// FUNCTION: ENGINE 0x10572D90
// FUNCTION: ENGINE 0x10572DB0
// FUNCTION: ENGINE 0x10573110
