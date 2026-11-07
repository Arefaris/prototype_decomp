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

namespace proto
{
	namespace HitEffectManager
	{
		// RTTI: proto::HitEffectManager::HitEffectParams (3 vftable slots, 0xB0 bytes); made by the manager (constructor 0x104F51A0, destructor 0x104F5270)
		class HitEffectParams : public fight::Params
		{
		public:
			// 0x104F51A0
			HitEffectParams();
			// 0x104F5270 (the deleting destructor is 0x104F5280)
			virtual ~HitEffectParams();

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
			unsigned char unknown40[0x4C - 0x40];
			math::Vector impactDirection;  // +0x4C
			math::Vector surfaceNormal;  // +0x58
			unsigned char unknown64[0x84 - 0x64];
			float unknown84;  // +0x84
			unsigned int unknown88;  // +0x88
			unsigned int unknown8C;  // +0x8C
			float unknown90;  // +0x90
			float unknown94;  // +0x94
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
