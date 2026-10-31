// Fight items of the motion group: HitWeaponTrack (unit 0x1017C270 - 0x1017CA90; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_HITWEAPON_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_HITWEAPON_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::HitWeaponTrack (16 vftable slots, 0x60 bytes)
			class HitWeaponTrack : public fight::Track
			{
			public:
				// 0x1017C370
				HitWeaponTrack();
				virtual ~HitWeaponTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D6090, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetCollisionCountMax(int newValue);
				bool SetDamage(float newValue);
				bool SetDamageType(int newValue);
				bool SetImpulse(const math::Vector& newValue);
				fight::BranchHolder* SetReceiverBranch();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder receiverBranch;  // +0x10
					unsigned char unknown34[0x4];
					fight::Name grabSlot;  // +0x38
					math::Vector impulse;  // +0x40
					float damage;  // +0x4C
					float timeBegin;  // +0x50
					float timeEnd;  // +0x54
					int collisionCountMax;  // +0x58
					int damageType;  // +0x5C
			};

			extern fight::Property** gHitWeaponTrackProperties;
			fight::TrackFactory* CreateHitWeaponTrackFactory(const char* name);
			void RegisterHitWeaponTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
