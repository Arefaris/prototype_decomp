#include "code/proto/behaviours/fedisplaybehaviour.h"

namespace content
{
	static const EnumValue sHUDReticuleTypeValues[] =
	{
		{ "RETICULE_ALEX_DEFAULT", 0 },
		{ "RETICULE_WEAPON", 1 },
		{ "RETICULE_HELI_APACHE", 2 },
		{ "RETICULE_HELI_TRANSPORT", 3 },
		{ "RETICULE_TANK", 4 }
	};

	// FUNCTION: ENGINE 0x104BFAD0
	template<> void EnumInfo<proto::HUDReticuleType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::HUDReticuleType";
		*code = "p";
		*values = sHUDReticuleTypeValues;
		*count = 5;
	}

	static const EnumValue sHUDAmmoTypeValues[] =
	{
		{ "AMMOTYPE_HELLFIRE", 0 },
		{ "AMMOTYPE_ROCKET", 1 },
		{ "AMMOTYPE_GUN", 2 },
		{ "AMMOTYPE_CANNON", 3 },
		{ "AMMOTYPE_THERMABOLIC", 4 },
		{ "AMMOTYPE_GRENADE", 5 },
		{ "AMMOTYPE_NOTHING", 6 }
	};

	// FUNCTION: ENGINE 0x104BFB10
	template<> void EnumInfo<proto::HUDAmmoType>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::HUDAmmoType";
		*code = "p";
		*values = sHUDAmmoTypeValues;
		*count = 7;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x104BFB50
	content::ClassInfo* FEDisplayBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FEDisplayBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104BFB90
	FEDisplayBehaviour::FEDisplayBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
		retType = RETICULE_ALEX_DEFAULT;
		ammoType = AMMOTYPE_NOTHING;
		showTargetHealth = false;
		unknown1C = 0x26;
		unknown20 = 7;
		Listen(0x33, true);
		Listen(0x14, true);
	}

	// FUNCTION: ENGINE 0x104BFBF0
	FEDisplayBehaviour::~FEDisplayBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x104BFC00
	void FEDisplayBehaviour::Slot1()
	{
	}

	// FUNCTION: ENGINE 0x104BFD50
	void FEDisplayBehaviour::Update(float dt, unsigned short mask)
	{
	}

	// FUNCTION: ENGINE 0x104BFF70
	content::MemberList* FEDisplayBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, FEDisplayBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<FEDisplayBehaviour, float, 0>("pn"),
				PROTO_OFFSET(FEDisplayBehaviour, vehicleReticulePosY), "vehicleReticulePosY" },
			{ content::GetMemberPrimitiveMetaType<FEDisplayBehaviour, bool, 0>("pn"),
				PROTO_OFFSET(FEDisplayBehaviour, showTargetHealth), "showTargetHealth" },
			{ content::GetEnumMetaType<HUDReticuleType>(), 0xc, "retType" },
			{ content::GetEnumMetaType<HUDAmmoType>(), 0x10, "ammoType" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104BFD60
// FUNCTION: ENGINE 0x104BFDE0
// FUNCTION: ENGINE 0x104BFE80
// FUNCTION: ENGINE 0x104BFE90
// FUNCTION: ENGINE 0x104BFEC0
// FUNCTION: ENGINE 0x104BFEF0
// FUNCTION: ENGINE 0x104BFF30
