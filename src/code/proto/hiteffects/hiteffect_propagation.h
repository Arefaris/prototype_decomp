// Fight items of the hit effects: PropagationTrack (unit 0x10510430 - 0x10511200; no assert path, the file name is a guess).
#ifndef PROTO_HITEFFECTMANAGER_HITEFFECT_PROPAGATION_H
#define PROTO_HITEFFECTMANAGER_HITEFFECT_PROPAGATION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/hiteffects/hiteffectdata.h"

namespace proto
{
	namespace HitEffectManager
	{
		// RTTI: proto::HitEffectManager::PropagationTrack (16 vftable slots, 0x48 bytes)
		class PropagationTrack : public fight::Track
		{
		public:
			// 0x10510AA0
			PropagationTrack();
			virtual ~PropagationTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x10503C20, another unit)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float newValue);
			bool SetMaxDeflection(float newValue);
			bool SetEnableDirection(bool newValue);
			bool SetDirection(const math::Vector& newValue);
			bool SetDistance(float newValue);
			bool SetDamagePercentage(float newValue);
			bool SetDamageType(int newValue);
			bool SetAttackType(int newValue);
			bool SetHitType(const fight::Name& newValue);
			bool SetEffectType(const fight::Name& newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			fight::Name effectType;  // +0x10
			fight::Name hitType;  // +0x18
			math::Vector direction;  // +0x20
			float damagePercentage;  // +0x2C
			float distance;  // +0x30
			float maxDeflection;  // +0x34
			float timeBegin;  // +0x38
			int attackType;  // +0x3C
			int damageType;  // +0x40
			bool enableDirection;  // +0x44
			unsigned char unknown45[0x3];
		};

		extern fight::Property** gPropagationTrackProperties;
		fight::TrackFactory* CreatePropagationTrackFactory(const char* name);
		void RegisterPropagationTrackFactory(fight::TrackRegistry* registry, const char* name);

	}
}

#endif
