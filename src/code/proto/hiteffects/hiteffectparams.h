// proto::HitEffectManager::HitEffectParams (RTTI; base fight::Params): what one hit passes to the fight tree of the hit effects. The
// conditions of the hit effects read it; the manager fills it in (0x104F4190 and the two functions after it). The member names are guesses.
#ifndef PROTO_HITEFFECTMANAGER_HITEFFECTPARAMS_H
#define PROTO_HITEFFECTMANAGER_HITEFFECTPARAMS_H

#include "code/engine/fight/params.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"
#include "code/engine/fight/fightcommon.h"
#include "code/math/vector.h"
#include "code/math/vector2.h"

namespace proto
{
	namespace HitEffectManager
	{
		// The five words at +0x84 of the parameters (name unknown): a scale, two counters and two more scales
		struct HitEffectUnknown84
		{
			HitEffectUnknown84() : unknown0(engine::driving::gOne), unknown4(0), unknown8(0), unknownC(engine::driving::gOne), unknown10(engine::driving::gOne)
			{
			}

			float unknown0;
			unsigned int unknown4;
			unsigned int unknown8;
			float unknownC;
			float unknown10;
		};

		// RTTI: proto::HitEffectManager::HitEffectParams (3 vftable slots, 0xB0 bytes); made by the manager (constructor 0x104F51A0, destructor 0x104F5270)
		class HitEffectParams : public fight::Params
		{
		public:
			// 0x104F51A0
			HitEffectParams();
			// 0x104F5270 (the deleting destructor is 0x104F5280)
			virtual ~HitEffectParams();

			// The setters the manager's hit functions use (the engine inlines them; its out-of-line copies are 0x104F3630 -
			// 0x104F38B0, 0x104F3A00 and 0x104F3A10; the names are guesses)
			void SetDamageType(int newValue);
			void SetDamageGiven(float newValue);
			void SetDamageTaken(float newValue);
			void SetAttackType(int newValue);
			// The getters (0x104F5300 - 0x104F53B0)
			int GetDamageType() const;
			unsigned char GetMaterialType() const;
			float GetDamageGiven() const;
			float GetDamageTaken() const;
			int GetAttackType() const;
			const fight::Name& GetHitType() const;
			const fight::Name& GetEffectType() const;
			const math::Vector& GetSurfaceNormal() const;
			float GetChargeValue() const;
			float GetObjectVolume() const;
			float GetObjectSpeed() const;
			bool GetFromMuscleMass() const;
			// 0x104FB870 / 0x104FB890
			const math::Vector2& GetUnknown7C() const;
			const math::Vector& GetUnknown70() const;
			void SetUnknown7C(const math::Vector2& newValue);
			void SetUnknown84(const HitEffectUnknown84* newValue);
			void SetUnknown40(const math::Vector& newValue);
			void SetSurfaceNormal(const math::Vector& newValue);
			void SetUnknown64(const math::Vector& newValue);
			void SetUnknown70(const math::Vector& newValue);
			void SetGiver(engine::GameObjectHandle newValue);
			void SetReceiver(engine::GameObjectHandle newValue);
			void SetImpactDirection(const math::Vector& newValue);
			void SetMaterialType(unsigned char newValue);
			void SetChargeValue(float newValue);
			void SetObjectVolume(float newValue);
			void SetObjectSpeed(float newValue);
			void SetFromMuscleMass(bool newValue);
			void SetHitType(const fight::Name& newValue);
			void SetEffectType(const fight::Name& newValue);

			unsigned int kind;  // +0xC: 10
			engine::GameObjectHandle giver;  // +0x10
			engine::GameObjectHandle receiver;  // +0x14
			int damageType;  // +0x18
			unsigned char materialType;  // +0x1C
			float damageGiven;  // +0x20
			float damageTaken;  // +0x24
			float chargeValue;  // +0x28
			int attackType;  // +0x2C
			fight::Name hitType;  // +0x30
			fight::Name effectType;  // +0x38
			math::Vector unknown40;  // +0x40
			math::Vector impactDirection;  // +0x4C
			math::Vector surfaceNormal;  // +0x58
			math::Vector unknown64;  // +0x64
			math::Vector unknown70;  // +0x70
			math::Vector2 unknown7C;  // +0x7C
			HitEffectUnknown84 unknown84;  // +0x84
			int physicsObject;  // +0x98
			unsigned short physicsObjectSerial;  // +0x9C
			unsigned char unknown9E[2];
			float objectVolume;  // +0xA0
			float objectSpeed;  // +0xA4
			bool fromMuscleMass;  // +0xA8
			unsigned char unknownA9[0xB0 - 0xA9];
		};
	}
}

namespace proto
{
	// The message that asks an object how much damage of an attack type it takes (RTTI proto::GetDamageScaleByAttackTypeMessage;
	// type 0x14, id 0x28): the scale starts at one and comes back in it
	struct GetDamageScaleByAttackTypeMessage : public engine::IntrusiveMessage
	{
		explicit GetDamageScaleByAttackTypeMessage(int newAttackType) : engine::IntrusiveMessage(0x14, 0x28), attackType(newAttackType), scale(engine::driving::gOne)
		{
		}

		int attackType;  // +0xC
		float scale;  // +0x10
	};
}

#endif
