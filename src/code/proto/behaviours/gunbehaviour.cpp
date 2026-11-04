#include "code/proto/behaviours/gunbehaviour.h"
#include "code/core/refptr.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace choreo
{
	extern const float gMinusOne;
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10465A20
	content::ClassInfo* GunAmmoProfile::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GunAmmoProfile";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10465A60
	content::ClassInfo* GunBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GunBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10465AA0
	// EQUIVALENT: scheduling; the engine loads the 1.0 before it stores the vftable, ours after it (83 %)
	GunAmmoProfile::GunAmmoProfile() : effectScale(engine::driving::gOne), explosive(false)
	{
	}

	// FUNCTION: ENGINE 0x10465AD0
	GunAmmoProfile::~GunAmmoProfile()
	{
	}

	// FUNCTION: ENGINE 0x10465AE0
	// EQUIVALENT: scheduling; the engine loads the -1.0 of the direction after the stores of the zeros, ours before them (85 %)
	GunBehaviour::GunBehaviour(engine::GameObject* newOwner) : WeaponBehaviour(newOwner),
		bulletSpawnOffset(0.0f, 0.0f, 0.0f), bulletSpawnDirection(0.0f, 0.0f, choreo::gMinusOne), ammoProfile(0)
	{
		Listen(0x22, true);
	}

	// FUNCTION: ENGINE 0x10465B50
	void GunBehaviour::Slot1()
	{
		WeaponBehaviour::Slot1();
		Slot9(0);
	}

	// FUNCTION: ENGINE 0x10465B70
	void GunBehaviour::OnMessage(engine::Message* message)
	{
		WeaponBehaviour::OnMessage(message);
	}

	// FUNCTION: ENGINE 0x10465B80
	AmmoProfileBase* GunBehaviour::GetAmmoProfile()
	{
		return ammoProfile;
	}

	// FUNCTION: ENGINE 0x10465DF0
	GunBehaviour::~GunBehaviour()
	{
		core::SafeRelease(ammoProfile);
	}

	// FUNCTION: ENGINE 0x10465E20
	void GunBehaviour::SetAmmoProfile(AmmoProfileBase* profile)
	{
		core::RefAssign(ammoProfile, static_cast<GunAmmoProfile*>(profile));
	}

	// FUNCTION: ENGINE 0x10465F00
	content::MemberList* GunAmmoProfile::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<AmmoProfileBase>();
		static content::BaseClassCasterImpl<AmmoProfileBase, GunAmmoProfile> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<GunAmmoProfile, float, 0>("p"),
				PROTO_OFFSET(GunAmmoProfile, effectScale), "effectScale" },
			{ content::GetMemberPrimitiveMetaType<GunAmmoProfile, bool, 0>("p"),
				PROTO_OFFSET(GunAmmoProfile, explosive), "explosive" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10466D10
	content::MemberList* GunBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<WeaponBehaviour>();
		static content::BaseClassCasterImpl<WeaponBehaviour, GunBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<GunBehaviour, GunAmmoProfile>("p"),
				PROTO_OFFSET(GunBehaviour, ammoProfile), "ammoProfile" },
			{ content::GetMemberVectorMetaType<GunBehaviour, 0>("p"), 0x68, "bulletSpawnOffset" },
			{ content::GetMemberVectorMetaType<GunBehaviour, 1>("p"), 0x74, "bulletSpawnDirection" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10465B90
// FUNCTION: ENGINE 0x10465BF0
// FUNCTION: ENGINE 0x10465C50
// FUNCTION: ENGINE 0x10465C60
// FUNCTION: ENGINE 0x10465CA0
// FUNCTION: ENGINE 0x10465CE0
// FUNCTION: ENGINE 0x10465D00
// FUNCTION: ENGINE 0x10465D40
// FUNCTION: ENGINE 0x10465D50
// FUNCTION: ENGINE 0x10465D80
// FUNCTION: ENGINE 0x10465D90
// FUNCTION: ENGINE 0x10465DC0
// FUNCTION: ENGINE 0x10465E40
// FUNCTION: ENGINE 0x10465E80
// FUNCTION: ENGINE 0x10465EC0
// FUNCTION: ENGINE 0x10465ED0
// FUNCTION: ENGINE 0x10466010
// FUNCTION: ENGINE 0x10466CB0
