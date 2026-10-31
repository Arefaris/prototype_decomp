// Fight items of the motion group: HitReactionThrowTrack, ThrowTrack (unit 0x101BE030 - 0x101BF880; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_THROW_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_THROW_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::HitReactionThrowTrack (16 vftable slots, 0x68 bytes)
			class HitReactionThrowTrack : public fight::Track
			{
			public:
				// 0x101BE5C0
				HitReactionThrowTrack();
				virtual ~HitReactionThrowTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101211D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAutoTargetArc(float newValue);
				bool SetMaxTargetArc(float newValue);
				bool SetDistanceMin(float newValue);
				bool SetDistanceMax(float newValue);
				bool SetVelocityMin(float newValue);
				bool SetVelocityMax(float newValue);
				bool SetTrackingMin(float newValue);
				bool SetTrackingMax(float newValue);
				bool SetSpinMin(float newValue);
				bool SetSpinMax(float newValue);
				bool SetArcRange(float newValue);
				bool SetArcMax(float newValue);
				bool SetDamageMin(float newValue);
				bool SetDamageMax(float newValue);
				bool SetImpulseMin(float newValue);
				bool SetImpulseMax(float newValue);
				bool SetFriendlyFire(float newValue);
				bool SetHitType(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name hitType;  // +0x10
					float arcMax;  // +0x18
					float arcRange;  // +0x1C
					float autoTargetArc;  // +0x20
					float damageMax;  // +0x24
					float damageMin;  // +0x28
					float distanceMax;  // +0x2C
					float distanceMin;  // +0x30
					float friendlyFire;  // +0x34
					float impulseMax;  // +0x38
					float impulseMin;  // +0x3C
					float maxTargetArc;  // +0x40
					float spinMax;  // +0x44
					float spinMin;  // +0x48
					float timeBegin;  // +0x4C
					float timeEnd;  // +0x50
					float trackingMax;  // +0x54
					float trackingMin;  // +0x58
					float velocityMax;  // +0x5C
					float velocityMin;  // +0x60
					unsigned char unknown64[0x4];
			};

			extern fight::Property** gHitReactionThrowTrackProperties;
			fight::TrackFactory* CreateHitReactionThrowTrackFactory(const char* name);
			void RegisterHitReactionThrowTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ThrowTrack (16 vftable slots, 0x78 bytes)
			class ThrowTrack : public fight::Track
			{
			public:
				// 0x101BE6C0
				ThrowTrack();
				virtual ~ThrowTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10121180, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetDirection(const math::Vector& newValue);
				bool SetDistanceMin(float newValue);
				bool SetDistanceMax(float newValue);
				bool SetVelocityMin(float newValue);
				bool SetVelocityMax(float newValue);
				bool SetTrackingMin(float newValue);
				bool SetTrackingMax(float newValue);
				bool SetSpinMin(float newValue);
				bool SetSpinMax(float newValue);
				bool SetArcRange(float newValue);
				bool SetArcMax(float newValue);
				bool SetDamageMin(float newValue);
				bool SetDamageMax(float newValue);
				bool SetImpulseMin(float newValue);
				bool SetImpulseMax(float newValue);
				bool SetFriendlyFire(float newValue);
				bool SetUseTarget(bool newValue);
				bool SetUseTargetVehicle(bool newValue);
				bool SetRandomOffset(float newValue);
				bool SetInterruptPriority(int newValue);
				bool SetHitType(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					fight::Name hitType;  // +0x18
					math::Vector direction;  // +0x20
					float arcMax;  // +0x2C
					float arcRange;  // +0x30
					float damageMax;  // +0x34
					float damageMin;  // +0x38
					float distanceMax;  // +0x3C
					float distanceMin;  // +0x40
					float friendlyFire;  // +0x44
					float impulseMax;  // +0x48
					float impulseMin;  // +0x4C
					float randomOffset;  // +0x50
					float spinMax;  // +0x54
					float spinMin;  // +0x58
					float timeBegin;  // +0x5C
					float trackingMax;  // +0x60
					float trackingMin;  // +0x64
					float velocityMax;  // +0x68
					float velocityMin;  // +0x6C
					int interruptPriority;  // +0x70
					bool useTarget;  // +0x74
					bool useTargetVehicle;  // +0x75
					unsigned char unknown76[0x2];
			};

			extern fight::Property** gThrowTrackProperties;
			fight::TrackFactory* CreateThrowTrackFactory(const char* name);
			void RegisterThrowTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
