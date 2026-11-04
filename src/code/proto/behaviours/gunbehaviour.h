// proto::GunBehaviour (RTTI and reflection names; base proto::WeaponBehaviour) and its ammunition proto::GunAmmoProfile
// (base proto::AmmoProfileBase): a weapon that shoots bullets from a point and direction of its object. Unit
// 0x10465AA0 - 0x10466EB0 (no assert path; the file name is a guess). The reflected names are original, the rest is
// guessed; the reflection, the construction and the destruction are reconstructed, the shooting is left to the engine.
#ifndef PROTO_BEHAVIOURS_GUNBEHAVIOUR_H
#define PROTO_BEHAVIOURS_GUNBEHAVIOUR_H

#include "code/proto/behaviours/weaponbehaviour.h"

namespace proto
{
	// The ammunition of a gun (RTTI proto::GunAmmoProfile; 0x70 bytes)
	struct GunAmmoProfile : public AmmoProfileBase
	{
		// 0x10465AA0
		GunAmmoProfile();
		// 0x10465AD0 (the deleting destructor is 0x10465DC0)
		virtual ~GunAmmoProfile();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		float effectScale;  // +0x68
		bool explosive;  // +0x6C
	};

	class GunBehaviour : public WeaponBehaviour
	{
	public:
		// 0x10465AE0
		explicit GunBehaviour(engine::GameObject* newOwner);
		// 0x10465DF0 (the deleting destructor is 0x10466010)
		virtual ~GunBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10465B50): the clip starts full
		virtual void Slot1();
		// vftable slot 6 (0x10465B70)
		virtual void OnMessage(engine::Message* message);
		// vftable slot 8 (0x104665A0) / 11 (0x10466040), left to the engine
		virtual void Slot8(int a, int b, float c);
		virtual void Slot11(int a);
		// vftable slot 12 (0x10465B80) / 13 (0x10465E20)
		virtual AmmoProfileBase* GetAmmoProfile();
		virtual void SetAmmoProfile(AmmoProfileBase* profile);

		math::Vector bulletSpawnOffset;  // +0x68
		math::Vector bulletSpawnDirection;  // +0x74
		GunAmmoProfile* ammoProfile;  // +0x80
	};
}

#endif
