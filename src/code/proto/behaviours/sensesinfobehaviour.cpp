#include "code/proto/behaviours/sensesinfobehaviour.h"

namespace content
{
	static const EnumValue sSensesTypeValues[] =
	{
		{ "None", 0 },
		{ "Prototype", 1 },
		{ "Infected0", 2 },
		{ "Infected1", 3 },
		{ "Infected2", 4 },
		{ "Brawler", 5 },
		{ "Stealth", 6 },
		{ "Leader", 7 },
		{ "Hydra", 8 },
		{ "Soldier", 9 },
		{ "Tank", 10 },
		{ "Helicopter", 11 },
		{ "UAV", 12 },
		{ "GenericMilitary", 13 },
		{ "HiveProp", 14 },
		{ "InfectedBoss", 15 },
		{ "Pedestrian", 16 }
	};

	// FUNCTION: ENGINE 0x10075A80
	template<> void EnumInfo<proto::SensesType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::SensesType";
		*code = "p";
		*values = sSensesTypeValues;
		*count = 0x11;
	}
}

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace proto
{
	// FUNCTION: ENGINE 0x10075B00
	// EQUIVALENT: the vftable store and the load of the constant are scheduled differently (78.9 %)
	SensesInfoBehaviour::SensesInfoBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), unknownC(0.0f),
		unknown10(0.0f), unknown14(engine::driving::gOne), sensesType(SENSES_NONE), unknown1C(false), unknown1D(false)
	{
		Listen(7, true);
		Listen(0x3d, true);
		Listen2(8, true);
	}

	SensesInfoBehaviour::~SensesInfoBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10075AC0
	content::ClassInfo* SensesInfoBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::SensesInfoBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10075DA0
	content::MemberList* SensesInfoBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, SensesInfoBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<SensesType>(), 0x18, "sensesType" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10075BD0
// FUNCTION: ENGINE 0x10075CA0
// FUNCTION: ENGINE 0x10075CB0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10075B80
// FUNCTION: ENGINE 0x10075CE0
