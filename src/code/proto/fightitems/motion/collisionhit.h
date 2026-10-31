// Fight items of the motion group: CollisionHitTrack (unit 0x1014B6C0 - 0x1014D220; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_COLLISIONHIT_H
#define PROTO_FIGHTITEMS_MOTION_COLLISIONHIT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::CollisionHitTrack (16 vftable slots, 0x120 bytes)
			class CollisionHitTrack : public fight::Track
			{
			public:
				// 0x1014BD60
				CollisionHitTrack();
				virtual ~CollisionHitTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100AACF0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetUseShapecast(bool newValue);
				bool SetCollisionCountMax(int newValue);
				bool SetTimeBetweenHits(float newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetJointEnd(const fight::Name& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetRadius(float newValue);
				bool SetArcOffset(float newValue);
				bool SetArcRange(float newValue);
				bool SetCollideWith(int newValue);
				bool SetDamageMin(float newValue);
				bool SetDamageMax(float newValue);
				bool SetUseTransformationDamageMultiplier(bool newValue);
				bool SetUseWeaponDamageMultiplier(bool newValue);
				bool SetFriendlyFire(float newValue);
				bool SetAttackType(int newValue);
				bool SetHitType(const fight::Name& newValue);
				bool SetDamageType(int newValue);
				bool SetEffectType(const fight::Name& newValue);
				bool SetScaleX(float newValue);
				bool SetScaleY(float newValue);
				bool SetEffectScale(float newValue);
				bool SetPropAreaEmissionScale(float newValue);
				bool SetPropAreaEmissionScaleFunction(int newValue);
				bool SetPropAreaSizeScale(float newValue);
				bool SetPropAreaSizeScaleFunction(int newValue);
				bool SetImpulseMin(const math::Vector& newValue);
				bool SetImpulseMax(const math::Vector& newValue);
				bool SetImpulseRandomPlusMinus(float newValue);
				bool SetUseMotion(bool newValue);
				bool SetCollisionDirection(const math::Vector& newValue);
				bool SetDeformDirStr(float newValue);
				bool SetDeformStr(float newValue);
				bool SetCollisionFlag(const fight::Name& newValue);
				fight::BranchHolder* SetGiverBranch();
				fight::BranchHolder* SetReceiverBranch();
				bool SetUseDamageOriginator(bool newValue);
				bool SetSendAlert(bool newValue);
				bool SetSendOnlyToAIManager(bool newValue);
				bool SetUseOriginatorToValidate(bool newValue);
				bool SetIsThrown(bool newValue);
				bool SetMomentumDamageVelocity(float newValue);
				bool SetMomentumDamageMax(float newValue);
				bool SetTravelVelocity(float newValue);
				bool SetTravelTowardTarget(int newValue);
				bool SetIgnorePowerTarget(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder giverBranch;  // +0x10
					fight::BranchHolder receiverBranch;  // +0x34
					fight::Name collisionFlag;  // +0x58
					fight::Name effectType;  // +0x60
					fight::Name hitType;  // +0x68
					fight::Name joint;  // +0x70
					fight::Name jointEnd;  // +0x78
					math::Vector collisionDirection;  // +0x80
					math::Vector impulseMax;  // +0x8C
					math::Vector impulseMin;  // +0x98
					math::Vector offset;  // +0xA4
					float arcOffset;  // +0xB0
					float arcRange;  // +0xB4
					float damageMax;  // +0xB8
					float damageMin;  // +0xBC
					float deformDirStr;  // +0xC0
					float deformStr;  // +0xC4
					float effectScale;  // +0xC8
					float friendlyFire;  // +0xCC
					float impulseRandomPlusMinus;  // +0xD0
					float momentumDamageMax;  // +0xD4
					float momentumDamageVelocity;  // +0xD8
					float propAreaEmissionScale;  // +0xDC
					float propAreaSizeScale;  // +0xE0
					float radius;  // +0xE4
					float scaleX;  // +0xE8
					float scaleY;  // +0xEC
					float timeBegin;  // +0xF0
					float timeBetweenHits;  // +0xF4
					float timeEnd;  // +0xF8
					float travelVelocity;  // +0xFC
					int attackType;  // +0x100
					int collisionCountMax;  // +0x104
					int damageType;  // +0x108
					int propAreaEmissionScaleFunction;  // +0x10C
					int propAreaSizeScaleFunction;  // +0x110
					int travelTowardTarget;  // +0x114
					int collideWith;  // +0x118
					bool ignorePowerTarget : 1;  // +0x11C bit 0
					bool isThrown : 1;  // +0x11C bit 1
					bool sendAlert : 1;  // +0x11C bit 2
					bool sendOnlyToAIManager : 1;  // +0x11C bit 3
					bool useDamageOriginator : 1;  // +0x11C bit 4
					bool useMotion : 1;  // +0x11C bit 5
					bool useOriginatorToValidate : 1;  // +0x11C bit 6
					bool useShapecast : 1;  // +0x11C bit 7
					bool useTransformationDamageMultiplier : 1;  // +0x11D bit 0
					bool useWeaponDamageMultiplier : 1;  // +0x11D bit 1
					bool unknownBit11D_2 : 1;  // +0x11D bit 2
					bool unknownBit11D_3 : 1;  // +0x11D bit 3
					bool unknownBit11D_4 : 1;  // +0x11D bit 4
					bool unknownBit11D_5 : 1;  // +0x11D bit 5
					bool unknownBit11D_6 : 1;  // +0x11D bit 6
					bool unknownBit11D_7 : 1;  // +0x11D bit 7
					unsigned char unknown11E[0x2];
			};

			extern fight::Property** gCollisionHitTrackProperties;
			fight::TrackFactory* CreateCollisionHitTrackFactory(const char* name);
			void RegisterCollisionHitTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
