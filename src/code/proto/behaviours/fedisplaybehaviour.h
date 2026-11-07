// proto::FEDisplayBehaviour (RTTI and reflection names; base engine::Behaviour): tells the interface what to show for its
// object: the reticule and ammunition of a vehicle, whether the target's health is shown, and (messages of type 0x33) the
// transformation slot. Unit 0x104BFAD0 - 0x104C00D0 (no assert path; the file name is a guess). The reflected member
// names and the enumerations' values are original, the rest is guessed.
#ifndef PROTO_BEHAVIOURS_FEDISPLAYBEHAVIOUR_H
#define PROTO_BEHAVIOURS_FEDISPLAYBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"

namespace proto
{
	// The reticule the interface draws (RTTI-less enumeration, reflection name proto::HUDReticuleType)
	enum HUDReticuleType
	{
		RETICULE_ALEX_DEFAULT = 0,
		RETICULE_WEAPON = 1,
		RETICULE_HELI_APACHE = 2,
		RETICULE_HELI_TRANSPORT = 3,
		RETICULE_TANK = 4
	};

	// The ammunition the interface shows (proto::HUDAmmoType)
	enum HUDAmmoType
	{
		AMMOTYPE_HELLFIRE = 0,
		AMMOTYPE_ROCKET = 1,
		AMMOTYPE_GUN = 2,
		AMMOTYPE_CANNON = 3,
		AMMOTYPE_THERMABOLIC = 4,
		AMMOTYPE_GRENADE = 5,
		AMMOTYPE_NOTHING = 6
	};

	class FEDisplayBehaviour : public engine::Behaviour
	{
	public:
		// 0x104BFB90
		explicit FEDisplayBehaviour(engine::GameObject* newOwner);
		// 0x104BFBF0 (deleting destructor 0x104BFEC0)
		virtual ~FEDisplayBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1, 4 and 6 (0x104BFC00, 0x104BFD50, 0x104BFC10)
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		HUDReticuleType retType;  // +0xC
		HUDAmmoType ammoType;  // +0x10
		float vehicleReticulePosY;  // +0x14
		bool showTargetHealth;  // +0x18
		int unknown1C;
		int unknown20;
	};
}

#endif
