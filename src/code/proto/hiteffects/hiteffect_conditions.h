// Fight items of the hit effects: AttackTypeCondition, GiverConditionGroupCondition, FromMuscleMassCondition, DamageTakenCondition, MaterialTypeCondition, DamageScaleCondition, EffectTypeCondition, ImpactVsSurfaceAngleCondition, ObjectVolumeCondition, DamageGivenCondition, DamageOriginatorIsPlayerCondition, SurfaceAngleCondition, ReceiverConditionGroupCondition, ChargeValueCondition, ReceiverGrabbableClassCondition, GiverMaterialTypeCondition, ReceiverClassNameCondition, ObjectSpeedCondition, DamageTypeCondition, HitTypeCondition (unit 0x104F5600 - 0x104FB000; no assert path, the file name is a guess).
#ifndef PROTO_HITEFFECTMANAGER_HITEFFECT_CONDITIONS_H
#define PROTO_HITEFFECTMANAGER_HITEFFECT_CONDITIONS_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/hiteffects/hiteffectdata.h"

namespace proto
{
	namespace HitEffectManager
	{
		// RTTI: proto::HitEffectManager::AttackTypeCondition (10 vftable slots, 0x10 bytes)
		class AttackTypeCondition : public fight::Condition
		{
		public:
			// 0x104F6690
			AttackTypeCondition();
			virtual ~AttackTypeCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F5620, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetAttackType(int newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				int attackType;  // +0xC
		};

		extern fight::Property** gAttackTypeConditionProperties;
		fight::ConditionFactory* CreateAttackTypeConditionFactory(const char* name);
		void RegisterAttackTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::GiverConditionGroupCondition (10 vftable slots, 0x10 bytes)
		class GiverConditionGroupCondition : public fight::Condition
		{
		public:
			// 0x104F6700
			GiverConditionGroupCondition();
			virtual ~GiverConditionGroupCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F5FC0, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			fight::ConditionList* SetConditions();

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				fight::ConditionList conditions;  // +0xC
		};

		extern fight::Property** gGiverConditionGroupConditionProperties;
		fight::ConditionFactory* CreateGiverConditionGroupConditionFactory(const char* name);
		void RegisterGiverConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::FromMuscleMassCondition (10 vftable slots, 0x10 bytes)
		class FromMuscleMassCondition : public fight::Condition
		{
		public:
			// 0x104F6780
			FromMuscleMassCondition();
			virtual ~FromMuscleMassCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F5C10, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetMuscleMassActive(bool newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				bool muscleMassActive;  // +0xC
				unsigned char unknownD[0x3];
		};

		extern fight::Property** gFromMuscleMassConditionProperties;
		fight::ConditionFactory* CreateFromMuscleMassConditionFactory(const char* name);
		void RegisterFromMuscleMassConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::DamageTakenCondition (10 vftable slots, 0x14 bytes)
		class DamageTakenCondition : public fight::Condition
		{
		public:
			// 0x104F67E0
			DamageTakenCondition();
			virtual ~DamageTakenCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F5730, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetCompare(int newValue);
			bool SetDamageTaken(float newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				float damageTaken;  // +0xC
				int compare;  // +0x10
		};

		extern fight::Property** gDamageTakenConditionProperties;
		fight::ConditionFactory* CreateDamageTakenConditionFactory(const char* name);
		void RegisterDamageTakenConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::MaterialTypeCondition (10 vftable slots, 0x18 bytes)
		class MaterialTypeCondition : public fight::Condition
		{
		public:
			// 0x104F6FB0
			MaterialTypeCondition();
			virtual ~MaterialTypeCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F5640, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetMaterialType(const fight::Name& newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				unsigned char unknownC[0x4];
				fight::Name materialType;  // +0x10
		};

		extern fight::Property** gMaterialTypeConditionProperties;
		fight::ConditionFactory* CreateMaterialTypeConditionFactory(const char* name);
		void RegisterMaterialTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::DamageScaleCondition (10 vftable slots, 0x14 bytes)
		class DamageScaleCondition : public fight::Condition
		{
		public:
			// 0x104F6880
			DamageScaleCondition();
			virtual ~DamageScaleCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F5EF0, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetCompare(int newValue);
			bool SetDamageScale(float newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				float damageScale;  // +0xC
				int compare;  // +0x10
		};

		extern fight::Property** gDamageScaleConditionProperties;
		fight::ConditionFactory* CreateDamageScaleConditionFactory(const char* name);
		void RegisterDamageScaleConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::EffectTypeCondition (10 vftable slots, 0x18 bytes)
		class EffectTypeCondition : public fight::Condition
		{
		public:
			// 0x104F7020
			EffectTypeCondition();
			virtual ~EffectTypeCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F5C80, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetEffectType(const fight::Name& newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				unsigned char unknownC[0x4];
				fight::Name effectType;  // +0x10
		};

		extern fight::Property** gEffectTypeConditionProperties;
		fight::ConditionFactory* CreateEffectTypeConditionFactory(const char* name);
		void RegisterEffectTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::ImpactVsSurfaceAngleCondition (10 vftable slots, 0x14 bytes)
		class ImpactVsSurfaceAngleCondition : public fight::Condition
		{
		public:
			// 0x104F6930
			ImpactVsSurfaceAngleCondition();
			virtual ~ImpactVsSurfaceAngleCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F57F0, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetCompare(int newValue);
			bool SetTolerance(float newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				float tolerance;  // +0xC
				int compare;  // +0x10
		};

		extern fight::Property** gImpactVsSurfaceAngleConditionProperties;
		fight::ConditionFactory* CreateImpactVsSurfaceAngleConditionFactory(const char* name);
		void RegisterImpactVsSurfaceAngleConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::ObjectVolumeCondition (10 vftable slots, 0x14 bytes)
		class ObjectVolumeCondition : public fight::Condition
		{
		public:
			// 0x104F69A0
			ObjectVolumeCondition();
			virtual ~ObjectVolumeCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F5CF0, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetCompare(int newValue);
			bool SetVolume(float newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				float volume;  // +0xC
				int compare;  // +0x10
		};

		extern fight::Property** gObjectVolumeConditionProperties;
		fight::ConditionFactory* CreateObjectVolumeConditionFactory(const char* name);
		void RegisterObjectVolumeConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::DamageGivenCondition (10 vftable slots, 0x14 bytes)
		class DamageGivenCondition : public fight::Condition
		{
		public:
			// 0x104F6A10
			DamageGivenCondition();
			virtual ~DamageGivenCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F5670, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetCompare(int newValue);
			bool SetDamageGiven(float newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				float damageGiven;  // +0xC
				int compare;  // +0x10
		};

		extern fight::Property** gDamageGivenConditionProperties;
		fight::ConditionFactory* CreateDamageGivenConditionFactory(const char* name);
		void RegisterDamageGivenConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::DamageOriginatorIsPlayerCondition (10 vftable slots, 0xC bytes)
		class DamageOriginatorIsPlayerCondition : public fight::Condition
		{
		public:
			// 0x104F6AE0
			DamageOriginatorIsPlayerCondition();
			virtual ~DamageOriginatorIsPlayerCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F6330, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

		};

		extern fight::Property** gDamageOriginatorIsPlayerConditionProperties;
		fight::ConditionFactory* CreateDamageOriginatorIsPlayerConditionFactory(const char* name);
		void RegisterDamageOriginatorIsPlayerConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::SurfaceAngleCondition (10 vftable slots, 0x20 bytes)
		class SurfaceAngleCondition : public fight::Condition
		{
		public:
			// 0x104F6B40
			SurfaceAngleCondition();
			virtual ~SurfaceAngleCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F5A00, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetCompare(int newValue);
			bool SetDirection(const math::Vector& newValue);
			bool SetTolerance(float newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				math::Vector direction;  // +0xC
				float tolerance;  // +0x18
				int compare;  // +0x1C
		};

		extern fight::Property** gSurfaceAngleConditionProperties;
		fight::ConditionFactory* CreateSurfaceAngleConditionFactory(const char* name);
		void RegisterSurfaceAngleConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::ReceiverConditionGroupCondition (10 vftable slots, 0x10 bytes)
		class ReceiverConditionGroupCondition : public fight::Condition
		{
		public:
			// 0x104F6BD0
			ReceiverConditionGroupCondition();
			virtual ~ReceiverConditionGroupCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F60D0, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			fight::ConditionList* SetConditions();

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				fight::ConditionList conditions;  // +0xC
		};

		extern fight::Property** gReceiverConditionGroupConditionProperties;
		fight::ConditionFactory* CreateReceiverConditionGroupConditionFactory(const char* name);
		void RegisterReceiverConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::ChargeValueCondition (10 vftable slots, 0x14 bytes)
		class ChargeValueCondition : public fight::Condition
		{
		public:
			// 0x104F6C50
			ChargeValueCondition();
			virtual ~ChargeValueCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F5CA0, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetCompare(int newValue);
			bool SetCharge(float newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				float charge;  // +0xC
				int compare;  // +0x10
		};

		extern fight::Property** gChargeValueConditionProperties;
		fight::ConditionFactory* CreateChargeValueConditionFactory(const char* name);
		void RegisterChargeValueConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::ReceiverGrabbableClassCondition (10 vftable slots, 0x20 bytes)
		class ReceiverGrabbableClassCondition : public fight::Condition
		{
		public:
			// 0x104F71B0
			ReceiverGrabbableClassCondition();
			virtual ~ReceiverGrabbableClassCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F6260, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetCompare(int newValue);
			bool SetGrabbableClass(const fight::Name& newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				unsigned char unknownC[0x4];
				fight::Name grabbableClass;  // +0x10
				int compare;  // +0x18
				unsigned char unknown1C[0x4];
		};

		extern fight::Property** gReceiverGrabbableClassConditionProperties;
		fight::ConditionFactory* CreateReceiverGrabbableClassConditionFactory(const char* name);
		void RegisterReceiverGrabbableClassConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::GiverMaterialTypeCondition (10 vftable slots, 0x18 bytes)
		class GiverMaterialTypeCondition : public fight::Condition
		{
		public:
			// 0x104F71F0
			GiverMaterialTypeCondition();
			virtual ~GiverMaterialTypeCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F5DB0, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetGiverMaterialType(const fight::Name& newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				unsigned char unknownC[0x4];
				fight::Name giverMaterialType;  // +0x10
		};

		extern fight::Property** gGiverMaterialTypeConditionProperties;
		fight::ConditionFactory* CreateGiverMaterialTypeConditionFactory(const char* name);
		void RegisterGiverMaterialTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::ReceiverClassNameCondition (10 vftable slots, 0x20 bytes)
		class ReceiverClassNameCondition : public fight::Condition
		{
		public:
			// 0x104F7230
			ReceiverClassNameCondition();
			virtual ~ReceiverClassNameCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F61E0, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetCompare(int newValue);
			bool SetValue(const fight::Name& newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				unsigned char unknownC[0x4];
				fight::Name value;  // +0x10
				int compare;  // +0x18
				unsigned char unknown1C[0x4];
		};

		extern fight::Property** gReceiverClassNameConditionProperties;
		fight::ConditionFactory* CreateReceiverClassNameConditionFactory(const char* name);
		void RegisterReceiverClassNameConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::ObjectSpeedCondition (10 vftable slots, 0x14 bytes)
		class ObjectSpeedCondition : public fight::Condition
		{
		public:
			// 0x104F6D50
			ObjectSpeedCondition();
			virtual ~ObjectSpeedCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F5D50, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetCompare(int newValue);
			bool SetSpeed(float newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				float speed;  // +0xC
				int compare;  // +0x10
		};

		extern fight::Property** gObjectSpeedConditionProperties;
		fight::ConditionFactory* CreateObjectSpeedConditionFactory(const char* name);
		void RegisterObjectSpeedConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::DamageTypeCondition (10 vftable slots, 0x10 bytes)
		class DamageTypeCondition : public fight::Condition
		{
		public:
			// 0x104F6DC0
			DamageTypeCondition();
			virtual ~DamageTypeCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F5600, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetDamageType(int newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				int damageType;  // +0xC
		};

		extern fight::Property** gDamageTypeConditionProperties;
		fight::ConditionFactory* CreateDamageTypeConditionFactory(const char* name);
		void RegisterDamageTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: proto::HitEffectManager::HitTypeCondition (10 vftable slots, 0x18 bytes)
		class HitTypeCondition : public fight::Condition
		{
		public:
			// 0x104F72D0
			HitTypeCondition();
			virtual ~HitTypeCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x104F5C60, another unit)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetHitType(const fight::Name& newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				unsigned char unknownC[0x4];
				fight::Name hitType;  // +0x10
		};

		extern fight::Property** gHitTypeConditionProperties;
		fight::ConditionFactory* CreateHitTypeConditionFactory(const char* name);
		void RegisterHitTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

	}
}

#endif
