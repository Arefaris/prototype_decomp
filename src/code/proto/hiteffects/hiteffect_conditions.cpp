// Fight items of the hit effects: AttackTypeCondition, GiverConditionGroupCondition, FromMuscleMassCondition, DamageTakenCondition, MaterialTypeCondition, DamageScaleCondition, EffectTypeCondition, ImpactVsSurfaceAngleCondition, ObjectVolumeCondition, DamageGivenCondition, DamageOriginatorIsPlayerCondition, SurfaceAngleCondition, ReceiverConditionGroupCondition, ChargeValueCondition, ReceiverGrabbableClassCondition, GiverMaterialTypeCondition, ReceiverClassNameCondition, ObjectSpeedCondition, DamageTypeCondition, HitTypeCondition (unit 0x104F5600 - 0x104FB000; no assert path, the file name is a guess).
#include "code/proto/hiteffects/hiteffect_conditions.h"
#include "code/engine/fight/fightcommon.h"
#include "code/proto/fightitems/motion/motioncommon.h"
#include <math.h>
#include "code/engine/gameobject/gameobject.h"
#include "code/proto/hiteffects/hiteffectparams.h"
#include "code/ravenphysics/material.h"

namespace proto
{
	namespace HitEffectManager
	{
		fight::Property** gAttackTypeConditionProperties;  // 0x1126F494

		// FUNCTION: ENGINE 0x104F6450
		bool AttackTypeCondition::SetAttackType(int newValue)
		{
			attackType = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6660
		fight::Property* AttackTypeCondition::GetProperty(int index)
		{
			return gAttackTypeConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6680
		void AttackTypeCondition::ClearProperties()
		{
			fight::FreePropertyList(&gAttackTypeConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F6690
		AttackTypeCondition::AttackTypeCondition() : fight::Condition(0), attackType(0)
		{
		}

		// FUNCTION: ENGINE 0x104F66C0
		AttackTypeCondition::~AttackTypeCondition()
		{
		}

		// FUNCTION: ENGINE 0x104F8AB0
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void AttackTypeCondition::RegisterProperties()
		{
			if (gAttackTypeConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumConstList<AttackTypeCondition>("attackType", gAttackTypeConditionAttackTypeTable, gAttackTypeConditionAttackTypeCount, &AttackTypeCondition::SetAttackType);
				properties[0] = property;
				fight::RegisterPropertyList(properties, &gAttackTypeConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F86F0
		fight::ConditionFactory* CreateAttackTypeConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<AttackTypeCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F95B0
		void RegisterAttackTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<AttackTypeCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gGiverConditionGroupConditionProperties;  // 0x1126F498

		// FUNCTION: ENGINE 0x104F6460
		fight::ConditionList* GiverConditionGroupCondition::SetConditions()
		{
			return &conditions;
		}

		// FUNCTION: ENGINE 0x104F66D0
		fight::Property* GiverConditionGroupCondition::GetProperty(int index)
		{
			return gGiverConditionGroupConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F66F0
		void GiverConditionGroupCondition::ClearProperties()
		{
			fight::FreePropertyList(&gGiverConditionGroupConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F6700
		GiverConditionGroupCondition::GiverConditionGroupCondition() : fight::Condition(0)
		{
		}

		// FUNCTION: ENGINE 0x104F6730
		GiverConditionGroupCondition::~GiverConditionGroupCondition()
		{
		}

		// FUNCTION: ENGINE 0x104F8B60
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void GiverConditionGroupCondition::RegisterProperties()
		{
			if (gGiverConditionGroupConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyConditionGroup<GiverConditionGroupCondition>("conditions", &GiverConditionGroupCondition::SetConditions);
				properties[0] = property;
				fight::RegisterPropertyList(properties, &gGiverConditionGroupConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F8720
		fight::ConditionFactory* CreateGiverConditionGroupConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<GiverConditionGroupCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F95E0
		void RegisterGiverConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<GiverConditionGroupCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gFromMuscleMassConditionProperties;  // 0x1126F49C

		// FUNCTION: ENGINE 0x104F6470
		bool FromMuscleMassCondition::SetMuscleMassActive(bool newValue)
		{
			muscleMassActive = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6750
		fight::Property* FromMuscleMassCondition::GetProperty(int index)
		{
			return gFromMuscleMassConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6770
		void FromMuscleMassCondition::ClearProperties()
		{
			fight::FreePropertyList(&gFromMuscleMassConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F6780
		FromMuscleMassCondition::FromMuscleMassCondition() : fight::Condition(0), muscleMassActive(true)
		{
		}

		// FUNCTION: ENGINE 0x104F67A0
		FromMuscleMassCondition::~FromMuscleMassCondition()
		{
		}

		// FUNCTION: ENGINE 0x104F8C00
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void FromMuscleMassCondition::RegisterProperties()
		{
			if (gFromMuscleMassConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyBool<FromMuscleMassCondition>("muscleMassActive", &FromMuscleMassCondition::SetMuscleMassActive);
				properties[0] = property;
				fight::RegisterPropertyList(properties, &gFromMuscleMassConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F8750
		fight::ConditionFactory* CreateFromMuscleMassConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<FromMuscleMassCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F9610
		void RegisterFromMuscleMassConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<FromMuscleMassCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gDamageTakenConditionProperties;  // 0x1126F4A0

		// FUNCTION: ENGINE 0x104F6480
		bool DamageTakenCondition::SetCompare(int newValue)
		{
			compare = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6490
		bool DamageTakenCondition::SetDamageTaken(float newValue)
		{
			damageTaken = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F67B0
		fight::Property* DamageTakenCondition::GetProperty(int index)
		{
			return gDamageTakenConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F67D0
		void DamageTakenCondition::ClearProperties()
		{
			fight::FreePropertyList(&gDamageTakenConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F67E0
		DamageTakenCondition::DamageTakenCondition() : fight::Condition(0), damageTaken(0.0f), compare(0)
		{
		}

		// FUNCTION: ENGINE 0x104F6810
		DamageTakenCondition::~DamageTakenCondition()
		{
		}

		// FUNCTION: ENGINE 0x104F8CA0
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void DamageTakenCondition::RegisterProperties()
		{
			if (gDamageTakenConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumConstList<DamageTakenCondition>("compare", gDamageTakenConditionCompareTable, gDamageTakenConditionCompareCount, &DamageTakenCondition::SetCompare);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<DamageTakenCondition>("damageTaken", &DamageTakenCondition::SetDamageTaken);
				properties[1] = property;
				fight::RegisterPropertyList(properties, &gDamageTakenConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F8780
		fight::ConditionFactory* CreateDamageTakenConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<DamageTakenCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F9640
		void RegisterDamageTakenConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<DamageTakenCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gMaterialTypeConditionProperties;  // 0x1126F4A4

		// FUNCTION: ENGINE 0x104F6E30
		bool MaterialTypeCondition::SetMaterialType(const fight::Name& newValue)
		{
			materialType = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6820
		fight::Property* MaterialTypeCondition::GetProperty(int index)
		{
			return gMaterialTypeConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6840
		void MaterialTypeCondition::ClearProperties()
		{
			fight::FreePropertyList(&gMaterialTypeConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F6FB0
		MaterialTypeCondition::MaterialTypeCondition() : fight::Condition(0)
		{
		}

		// FUNCTION: ENGINE 0x104F6FE0
		MaterialTypeCondition::~MaterialTypeCondition()
		{
		}

		// FUNCTION: ENGINE 0x104F9FA0
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void MaterialTypeCondition::RegisterProperties()
		{
			if (gMaterialTypeConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyNameList<MaterialTypeCondition>("materialType", &MaterialTypeCondition::SetMaterialType);
				properties[0] = property;
				fight::RegisterPropertyList(properties, &gMaterialTypeConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F87B0
		fight::ConditionFactory* CreateMaterialTypeConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<MaterialTypeCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F9670
		void RegisterMaterialTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<MaterialTypeCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gDamageScaleConditionProperties;  // 0x1126F4A8

		// FUNCTION: ENGINE 0x104F64B0
		bool DamageScaleCondition::SetCompare(int newValue)
		{
			compare = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F64C0
		bool DamageScaleCondition::SetDamageScale(float newValue)
		{
			damageScale = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6850
		fight::Property* DamageScaleCondition::GetProperty(int index)
		{
			return gDamageScaleConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6870
		void DamageScaleCondition::ClearProperties()
		{
			fight::FreePropertyList(&gDamageScaleConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F6880
		DamageScaleCondition::DamageScaleCondition() : fight::Condition(0), damageScale(1.0f), compare(0)
		{
		}

		// FUNCTION: ENGINE 0x104F68C0
		DamageScaleCondition::~DamageScaleCondition()
		{
		}

		// FUNCTION: ENGINE 0x104F8D90
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void DamageScaleCondition::RegisterProperties()
		{
			if (gDamageScaleConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumConstList<DamageScaleCondition>("compare", gDamageTakenConditionCompareTable, gDamageTakenConditionCompareCount, &DamageScaleCondition::SetCompare);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<DamageScaleCondition>("damageScale", &DamageScaleCondition::SetDamageScale);
				properties[1] = property;
				fight::RegisterPropertyList(properties, &gDamageScaleConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F87E0
		fight::ConditionFactory* CreateDamageScaleConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<DamageScaleCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F96A0
		void RegisterDamageScaleConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<DamageScaleCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gEffectTypeConditionProperties;  // 0x1126F4AC

		// FUNCTION: ENGINE 0x104F6E50
		bool EffectTypeCondition::SetEffectType(const fight::Name& newValue)
		{
			effectType = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F68D0
		fight::Property* EffectTypeCondition::GetProperty(int index)
		{
			return gEffectTypeConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F68F0
		void EffectTypeCondition::ClearProperties()
		{
			fight::FreePropertyList(&gEffectTypeConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F7020
		EffectTypeCondition::EffectTypeCondition() : fight::Condition(0)
		{
		}

		// FUNCTION: ENGINE 0x104F7050
		EffectTypeCondition::~EffectTypeCondition()
		{
		}

		// FUNCTION: ENGINE 0x104FA040
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void EffectTypeCondition::RegisterProperties()
		{
			if (gEffectTypeConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyNameList<EffectTypeCondition>("effectType", &EffectTypeCondition::SetEffectType);
				properties[0] = property;
				fight::RegisterPropertyList(properties, &gEffectTypeConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F8810
		fight::ConditionFactory* CreateEffectTypeConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<EffectTypeCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F96D0
		void RegisterEffectTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<EffectTypeCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gImpactVsSurfaceAngleConditionProperties;  // 0x1126F4B0

		// FUNCTION: ENGINE 0x104F64E0
		bool ImpactVsSurfaceAngleCondition::SetCompare(int newValue)
		{
			compare = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F64F0
		bool ImpactVsSurfaceAngleCondition::SetTolerance(float newValue)
		{
			tolerance = newValue * 0.017453292f;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6900
		fight::Property* ImpactVsSurfaceAngleCondition::GetProperty(int index)
		{
			return gImpactVsSurfaceAngleConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6920
		void ImpactVsSurfaceAngleCondition::ClearProperties()
		{
			fight::FreePropertyList(&gImpactVsSurfaceAngleConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F6930
		ImpactVsSurfaceAngleCondition::ImpactVsSurfaceAngleCondition() : fight::Condition(0), tolerance(0.0f), compare(0)
		{
		}

		// FUNCTION: ENGINE 0x104F6960
		ImpactVsSurfaceAngleCondition::~ImpactVsSurfaceAngleCondition()
		{
		}

		// FUNCTION: ENGINE 0x104F8E80
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void ImpactVsSurfaceAngleCondition::RegisterProperties()
		{
			if (gImpactVsSurfaceAngleConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumConstList<ImpactVsSurfaceAngleCondition>("compare", gDamageTakenConditionCompareTable, gDamageTakenConditionCompareCount, &ImpactVsSurfaceAngleCondition::SetCompare);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<ImpactVsSurfaceAngleCondition>("tolerance", &ImpactVsSurfaceAngleCondition::SetTolerance);
				properties[1] = property;
				fight::RegisterPropertyList(properties, &gImpactVsSurfaceAngleConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F8840
		fight::ConditionFactory* CreateImpactVsSurfaceAngleConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ImpactVsSurfaceAngleCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F9700
		void RegisterImpactVsSurfaceAngleConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ImpactVsSurfaceAngleCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gObjectVolumeConditionProperties;  // 0x1126F4B4

		// FUNCTION: ENGINE 0x104F6510
		bool ObjectVolumeCondition::SetCompare(int newValue)
		{
			compare = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6520
		bool ObjectVolumeCondition::SetVolume(float newValue)
		{
			volume = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6970
		fight::Property* ObjectVolumeCondition::GetProperty(int index)
		{
			return gObjectVolumeConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6990
		void ObjectVolumeCondition::ClearProperties()
		{
			fight::FreePropertyList(&gObjectVolumeConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F69A0
		ObjectVolumeCondition::ObjectVolumeCondition() : fight::Condition(0), volume(0.0f), compare(0)
		{
		}

		// FUNCTION: ENGINE 0x104F69D0
		ObjectVolumeCondition::~ObjectVolumeCondition()
		{
		}

		// FUNCTION: ENGINE 0x104F8F70
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void ObjectVolumeCondition::RegisterProperties()
		{
			if (gObjectVolumeConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumConstList<ObjectVolumeCondition>("compare", gDamageTakenConditionCompareTable, gDamageTakenConditionCompareCount, &ObjectVolumeCondition::SetCompare);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<ObjectVolumeCondition>("volume", &ObjectVolumeCondition::SetVolume);
				properties[1] = property;
				fight::RegisterPropertyList(properties, &gObjectVolumeConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F8870
		fight::ConditionFactory* CreateObjectVolumeConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ObjectVolumeCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F9730
		void RegisterObjectVolumeConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ObjectVolumeCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gDamageGivenConditionProperties;  // 0x1126F4B8

		// FUNCTION: ENGINE 0x104F6540
		bool DamageGivenCondition::SetCompare(int newValue)
		{
			compare = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6550
		bool DamageGivenCondition::SetDamageGiven(float newValue)
		{
			damageGiven = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F69E0
		fight::Property* DamageGivenCondition::GetProperty(int index)
		{
			return gDamageGivenConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6A00
		void DamageGivenCondition::ClearProperties()
		{
			fight::FreePropertyList(&gDamageGivenConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F6A10
		DamageGivenCondition::DamageGivenCondition() : fight::Condition(0), damageGiven(0.0f), compare(0)
		{
		}

		// FUNCTION: ENGINE 0x104F6A40
		DamageGivenCondition::~DamageGivenCondition()
		{
		}

		// FUNCTION: ENGINE 0x104F9060
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void DamageGivenCondition::RegisterProperties()
		{
			if (gDamageGivenConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumConstList<DamageGivenCondition>("compare", gDamageTakenConditionCompareTable, gDamageTakenConditionCompareCount, &DamageGivenCondition::SetCompare);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<DamageGivenCondition>("damageGiven", &DamageGivenCondition::SetDamageGiven);
				properties[1] = property;
				fight::RegisterPropertyList(properties, &gDamageGivenConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F88A0
		fight::ConditionFactory* CreateDamageGivenConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<DamageGivenCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F9760
		void RegisterDamageGivenConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<DamageGivenCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gDamageOriginatorIsPlayerConditionProperties;  // 0x1126F4BC

		// FUNCTION: ENGINE 0x104F6AB0
		fight::Property* DamageOriginatorIsPlayerCondition::GetProperty(int index)
		{
			return gDamageOriginatorIsPlayerConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6AD0
		void DamageOriginatorIsPlayerCondition::ClearProperties()
		{
			fight::FreePropertyList(&gDamageOriginatorIsPlayerConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F6AE0
		DamageOriginatorIsPlayerCondition::DamageOriginatorIsPlayerCondition() : fight::Condition(0)
		{
		}

		// FUNCTION: ENGINE 0x104F6B00
		DamageOriginatorIsPlayerCondition::~DamageOriginatorIsPlayerCondition()
		{
		}

		// FUNCTION: ENGINE 0x104F6A50
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void DamageOriginatorIsPlayerCondition::RegisterProperties()
		{
			if (gDamageOriginatorIsPlayerConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				fight::RegisterPropertyList(properties, &gDamageOriginatorIsPlayerConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F88D0
		fight::ConditionFactory* CreateDamageOriginatorIsPlayerConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<DamageOriginatorIsPlayerCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F9790
		void RegisterDamageOriginatorIsPlayerConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<DamageOriginatorIsPlayerCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gSurfaceAngleConditionProperties;  // 0x1126F4C0

		// FUNCTION: ENGINE 0x104F6570
		bool SurfaceAngleCondition::SetCompare(int newValue)
		{
			compare = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6580
		bool SurfaceAngleCondition::SetDirection(const math::Vector& newValue)
		{
			direction.x = newValue.x;
			direction.y = newValue.y;
			direction.z = newValue.z;
			return true;
		}

		// FUNCTION: ENGINE 0x104F65A0
		bool SurfaceAngleCondition::SetTolerance(float newValue)
		{
			tolerance = newValue * 0.017453292f;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6B10
		fight::Property* SurfaceAngleCondition::GetProperty(int index)
		{
			return gSurfaceAngleConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6B30
		void SurfaceAngleCondition::ClearProperties()
		{
			fight::FreePropertyList(&gSurfaceAngleConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F6B40
		SurfaceAngleCondition::SurfaceAngleCondition() : fight::Condition(0), direction(0.0f, 1.0f, 0.0f), tolerance(0.0f), compare(0)
		{
		}

		// FUNCTION: ENGINE 0x104F6B90
		SurfaceAngleCondition::~SurfaceAngleCondition()
		{
		}

		// FUNCTION: ENGINE 0x104F9150
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void SurfaceAngleCondition::RegisterProperties()
		{
			if (gSurfaceAngleConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumConstList<SurfaceAngleCondition>("compare", gDamageTakenConditionCompareTable, gDamageTakenConditionCompareCount, &SurfaceAngleCondition::SetCompare);
				properties[0] = property;
				property = new fight::PropertyVector<SurfaceAngleCondition>("direction", &SurfaceAngleCondition::SetDirection);
				properties[1] = property;
				property = new fight::PropertyFloatConstRange<SurfaceAngleCondition>("tolerance", &SurfaceAngleCondition::SetTolerance);
				properties[2] = property;
				fight::RegisterPropertyList(properties, &gSurfaceAngleConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F8900
		fight::ConditionFactory* CreateSurfaceAngleConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<SurfaceAngleCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F97C0
		void RegisterSurfaceAngleConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<SurfaceAngleCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gReceiverConditionGroupConditionProperties;  // 0x1126F4C4

		// FUNCTION: ENGINE 0x104F65C0
		fight::ConditionList* ReceiverConditionGroupCondition::SetConditions()
		{
			return &conditions;
		}

		// FUNCTION: ENGINE 0x104F6BA0
		fight::Property* ReceiverConditionGroupCondition::GetProperty(int index)
		{
			return gReceiverConditionGroupConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6BC0
		void ReceiverConditionGroupCondition::ClearProperties()
		{
			fight::FreePropertyList(&gReceiverConditionGroupConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F6BD0
		ReceiverConditionGroupCondition::ReceiverConditionGroupCondition() : fight::Condition(0)
		{
		}

		// FUNCTION: ENGINE 0x104F6C00
		ReceiverConditionGroupCondition::~ReceiverConditionGroupCondition()
		{
		}

		// FUNCTION: ENGINE 0x104F9280
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void ReceiverConditionGroupCondition::RegisterProperties()
		{
			if (gReceiverConditionGroupConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyConditionGroup<ReceiverConditionGroupCondition>("conditions", &ReceiverConditionGroupCondition::SetConditions);
				properties[0] = property;
				fight::RegisterPropertyList(properties, &gReceiverConditionGroupConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F8930
		fight::ConditionFactory* CreateReceiverConditionGroupConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ReceiverConditionGroupCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F97F0
		void RegisterReceiverConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ReceiverConditionGroupCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gChargeValueConditionProperties;  // 0x1126F4C8

		// FUNCTION: ENGINE 0x104F65D0
		bool ChargeValueCondition::SetCompare(int newValue)
		{
			compare = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F65E0
		bool ChargeValueCondition::SetCharge(float newValue)
		{
			charge = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6C20
		fight::Property* ChargeValueCondition::GetProperty(int index)
		{
			return gChargeValueConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6C40
		void ChargeValueCondition::ClearProperties()
		{
			fight::FreePropertyList(&gChargeValueConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F6C50
		ChargeValueCondition::ChargeValueCondition() : fight::Condition(0), charge(0.0f), compare(0)
		{
		}

		// FUNCTION: ENGINE 0x104F6C80
		ChargeValueCondition::~ChargeValueCondition()
		{
		}

		// FUNCTION: ENGINE 0x104F9320
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void ChargeValueCondition::RegisterProperties()
		{
			if (gChargeValueConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumConstList<ChargeValueCondition>("compare", gDamageTakenConditionCompareTable, gDamageTakenConditionCompareCount, &ChargeValueCondition::SetCompare);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<ChargeValueCondition>("charge", &ChargeValueCondition::SetCharge);
				properties[1] = property;
				fight::RegisterPropertyList(properties, &gChargeValueConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F8960
		fight::ConditionFactory* CreateChargeValueConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ChargeValueCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F9820
		void RegisterChargeValueConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ChargeValueCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gReceiverGrabbableClassConditionProperties;  // 0x1126F4CC

		// FUNCTION: ENGINE 0x104F6600
		bool ReceiverGrabbableClassCondition::SetCompare(int newValue)
		{
			compare = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6E70
		bool ReceiverGrabbableClassCondition::SetGrabbableClass(const fight::Name& newValue)
		{
			grabbableClass = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6C90
		fight::Property* ReceiverGrabbableClassCondition::GetProperty(int index)
		{
			return gReceiverGrabbableClassConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6CB0
		void ReceiverGrabbableClassCondition::ClearProperties()
		{
			fight::FreePropertyList(&gReceiverGrabbableClassConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F71B0
		ReceiverGrabbableClassCondition::ReceiverGrabbableClassCondition() : fight::Condition(0), compare(0)
		{
		}

		// FUNCTION: ENGINE 0x104F71E0
		ReceiverGrabbableClassCondition::~ReceiverGrabbableClassCondition()
		{
		}

		// FUNCTION: ENGINE 0x104FA0E0
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void ReceiverGrabbableClassCondition::RegisterProperties()
		{
			if (gReceiverGrabbableClassConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumConstList<ReceiverGrabbableClassCondition>("compare", gReceiverGrabbableClassConditionCompareTable, gReceiverGrabbableClassConditionCompareCount, &ReceiverGrabbableClassCondition::SetCompare);
				properties[0] = property;
				property = new fight::PropertyName<ReceiverGrabbableClassCondition>("grabbableClass", &ReceiverGrabbableClassCondition::SetGrabbableClass);
				properties[1] = property;
				fight::RegisterPropertyList(properties, &gReceiverGrabbableClassConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F8990
		fight::ConditionFactory* CreateReceiverGrabbableClassConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ReceiverGrabbableClassCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F9850
		void RegisterReceiverGrabbableClassConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ReceiverGrabbableClassCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gGiverMaterialTypeConditionProperties;  // 0x1126F4D0

		// FUNCTION: ENGINE 0x104F6E90
		bool GiverMaterialTypeCondition::SetGiverMaterialType(const fight::Name& newValue)
		{
			giverMaterialType = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6CC0
		fight::Property* GiverMaterialTypeCondition::GetProperty(int index)
		{
			return gGiverMaterialTypeConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6CE0
		void GiverMaterialTypeCondition::ClearProperties()
		{
			fight::FreePropertyList(&gGiverMaterialTypeConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F71F0
		GiverMaterialTypeCondition::GiverMaterialTypeCondition() : fight::Condition(0)
		{
		}

		// FUNCTION: ENGINE 0x104F7220
		GiverMaterialTypeCondition::~GiverMaterialTypeCondition()
		{
		}

		// FUNCTION: ENGINE 0x104FA1D0
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void GiverMaterialTypeCondition::RegisterProperties()
		{
			if (gGiverMaterialTypeConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyNameList<GiverMaterialTypeCondition>("giverMaterialType", &GiverMaterialTypeCondition::SetGiverMaterialType);
				properties[0] = property;
				fight::RegisterPropertyList(properties, &gGiverMaterialTypeConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F89C0
		fight::ConditionFactory* CreateGiverMaterialTypeConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<GiverMaterialTypeCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F9880
		void RegisterGiverMaterialTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<GiverMaterialTypeCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gReceiverClassNameConditionProperties;  // 0x1126F4D4

		// FUNCTION: ENGINE 0x104F6610
		bool ReceiverClassNameCondition::SetCompare(int newValue)
		{
			compare = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6EB0
		bool ReceiverClassNameCondition::SetValue(const fight::Name& newValue)
		{
			value = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6CF0
		fight::Property* ReceiverClassNameCondition::GetProperty(int index)
		{
			return gReceiverClassNameConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6D10
		void ReceiverClassNameCondition::ClearProperties()
		{
			fight::FreePropertyList(&gReceiverClassNameConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F7230
		ReceiverClassNameCondition::ReceiverClassNameCondition() : fight::Condition(0), compare(0)
		{
		}

		// FUNCTION: ENGINE 0x104F7260
		ReceiverClassNameCondition::~ReceiverClassNameCondition()
		{
		}

		// FUNCTION: ENGINE 0x104FA270
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void ReceiverClassNameCondition::RegisterProperties()
		{
			if (gReceiverClassNameConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumConstList<ReceiverClassNameCondition>("compare", gReceiverGrabbableClassConditionCompareTable, gReceiverGrabbableClassConditionCompareCount, &ReceiverClassNameCondition::SetCompare);
				properties[0] = property;
				property = new fight::PropertyName<ReceiverClassNameCondition>("value", &ReceiverClassNameCondition::SetValue);
				properties[1] = property;
				fight::RegisterPropertyList(properties, &gReceiverClassNameConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F89F0
		fight::ConditionFactory* CreateReceiverClassNameConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ReceiverClassNameCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F98B0
		void RegisterReceiverClassNameConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ReceiverClassNameCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gObjectSpeedConditionProperties;  // 0x1126F4D8

		// FUNCTION: ENGINE 0x104F6620
		bool ObjectSpeedCondition::SetCompare(int newValue)
		{
			compare = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6630
		bool ObjectSpeedCondition::SetSpeed(float newValue)
		{
			speed = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6D20
		fight::Property* ObjectSpeedCondition::GetProperty(int index)
		{
			return gObjectSpeedConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6D40
		void ObjectSpeedCondition::ClearProperties()
		{
			fight::FreePropertyList(&gObjectSpeedConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F6D50
		ObjectSpeedCondition::ObjectSpeedCondition() : fight::Condition(0), speed(0.0f), compare(0)
		{
		}

		// FUNCTION: ENGINE 0x104F6D80
		ObjectSpeedCondition::~ObjectSpeedCondition()
		{
		}

		// FUNCTION: ENGINE 0x104F9410
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void ObjectSpeedCondition::RegisterProperties()
		{
			if (gObjectSpeedConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumConstList<ObjectSpeedCondition>("compare", gDamageTakenConditionCompareTable, gDamageTakenConditionCompareCount, &ObjectSpeedCondition::SetCompare);
				properties[0] = property;
				property = new fight::PropertyFloatConstRange<ObjectSpeedCondition>("speed", &ObjectSpeedCondition::SetSpeed);
				properties[1] = property;
				fight::RegisterPropertyList(properties, &gObjectSpeedConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F8A20
		fight::ConditionFactory* CreateObjectSpeedConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ObjectSpeedCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F98E0
		void RegisterObjectSpeedConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ObjectSpeedCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gDamageTypeConditionProperties;  // 0x1126F4DC

		// FUNCTION: ENGINE 0x104F6650
		bool DamageTypeCondition::SetDamageType(int newValue)
		{
			damageType = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6D90
		fight::Property* DamageTypeCondition::GetProperty(int index)
		{
			return gDamageTypeConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6DB0
		void DamageTypeCondition::ClearProperties()
		{
			fight::FreePropertyList(&gDamageTypeConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F6DC0
		DamageTypeCondition::DamageTypeCondition() : fight::Condition(0), damageType(0)
		{
		}

		// FUNCTION: ENGINE 0x104F6DF0
		DamageTypeCondition::~DamageTypeCondition()
		{
		}

		// FUNCTION: ENGINE 0x104F9500
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void DamageTypeCondition::RegisterProperties()
		{
			if (gDamageTypeConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumConstList<DamageTypeCondition>("damageType", gDamageTypeConditionDamageTypeTable, gDamageTypeConditionDamageTypeCount, &DamageTypeCondition::SetDamageType);
				properties[0] = property;
				fight::RegisterPropertyList(properties, &gDamageTypeConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F8A50
		fight::ConditionFactory* CreateDamageTypeConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<DamageTypeCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F9910
		void RegisterDamageTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<DamageTypeCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		fight::Property** gHitTypeConditionProperties;  // 0x1126F4E0

		// FUNCTION: ENGINE 0x104F6ED0
		bool HitTypeCondition::SetHitType(const fight::Name& newValue)
		{
			hitType = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x104F6E00
		fight::Property* HitTypeCondition::GetProperty(int index)
		{
			return gHitTypeConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x104F6E20
		void HitTypeCondition::ClearProperties()
		{
			fight::FreePropertyList(&gHitTypeConditionProperties);
		}

		// FUNCTION: ENGINE 0x104F72D0
		HitTypeCondition::HitTypeCondition() : fight::Condition(0)
		{
		}

		// FUNCTION: ENGINE 0x104F7300
		HitTypeCondition::~HitTypeCondition()
		{
		}

		// FUNCTION: ENGINE 0x104FA360
		// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
		void HitTypeCondition::RegisterProperties()
		{
			if (gHitTypeConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyNameList<HitTypeCondition>("hitType", &HitTypeCondition::SetHitType);
				properties[0] = property;
				fight::RegisterPropertyList(properties, &gHitTypeConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x104F8A80
		fight::ConditionFactory* CreateHitTypeConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<HitTypeCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x104F9940
		void RegisterHitTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<HitTypeCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		// ---- evaluate begin

		// The fourth argument of a condition is the hit's parameters
		static inline const HitEffectParams* AsParams(int c)
		{
			return (const HitEffectParams*)c;
		}

		// FUNCTION: ENGINE 0x104F5600
		bool DamageTypeCondition::Evaluate(int a, int b, int c, int d)
		{
			return AsParams(c)->damageType == damageType;
		}

		// FUNCTION: ENGINE 0x104F5620
		bool AttackTypeCondition::Evaluate(int a, int b, int c, int d)
		{
			return AsParams(c)->attackType == attackType;
		}

		// FUNCTION: ENGINE 0x104F5640
		bool MaterialTypeCondition::Evaluate(int a, int b, int c, int d)
		{
			unsigned char material = AsParams(c)->materialType;
			return material == ravenphysics::FindMaterialIndex(materialType);
		}

		// FUNCTION: ENGINE 0x104F5670
		bool DamageGivenCondition::Evaluate(int a, int b, int c, int d)
		{
			float value = AsParams(c)->damageGiven;
			switch (compare)
			{
			case 0:
				return value < damageGiven;
			case 1:
				return value <= damageGiven;
			case 2:
				return value == damageGiven;
			case 3:
				return value != damageGiven;
			case 4:
				return value >= damageGiven;
			case 5:
				return value > damageGiven;
			}
			return false;
		}

		// FUNCTION: ENGINE 0x104F5730
		bool DamageTakenCondition::Evaluate(int a, int b, int c, int d)
		{
			float value = AsParams(c)->damageTaken;
			switch (compare)
			{
			case 0:
				return value < damageTaken;
			case 1:
				return value <= damageTaken;
			case 2:
				return value == damageTaken;
			case 3:
				return value != damageTaken;
			case 4:
				return value >= damageTaken;
			case 5:
				return value > damageTaken;
			}
			return false;
		}

		// FUNCTION: ENGINE 0x104F5C10
		bool FromMuscleMassCondition::Evaluate(int a, int b, int c, int d)
		{
			return AsParams(c)->fromMuscleMass == muscleMassActive;
		}

		// FUNCTION: ENGINE 0x104F5C60
		bool HitTypeCondition::Evaluate(int a, int b, int c, int d)
		{
			return AsParams(c)->hitType == hitType;
		}

		// FUNCTION: ENGINE 0x104F5C80
		bool EffectTypeCondition::Evaluate(int a, int b, int c, int d)
		{
			return AsParams(c)->effectType == effectType;
		}

		// FUNCTION: ENGINE 0x104F5EF0
		bool DamageScaleCondition::Evaluate(int a, int b, int c, int d)
		{
			const HitEffectParams* params = AsParams(c);
			if (params == 0)
			{
				return false;
			}
			int attackType = params->attackType;
			engine::GameObjectHandle receiver = params->receiver;
			engine::GameObject* object = receiver.Get();
			if (object == 0)
			{
				return false;
			}
			GetDamageScaleByAttackTypeMessage message(attackType);
			object->SendMessage(&message);
			int op = compare;
			float rhs = damageScale;
			return fight::CompareFloats(op, &message.scale, &rhs);
		}

		// 0x112562B8: the name of the attribute that holds an object's class name (name guess)
		core::Name<core::CaseSensitiveKey> gClassNameAttributeName("className", 0);

		// FUNCTION: ENGINE 0x104F61E0
		bool ReceiverClassNameCondition::Evaluate(int a, int b, int c, int d)
		{
			const HitEffectParams* params = AsParams(c);
			if (params == 0)
			{
				return false;
			}
			engine::GameObjectHandle receiver = params->receiver;
			engine::GameObject* object = receiver.Get();
			if (object == 0)
			{
				return false;
			}
			engine::BaseAttribute* attribute = object->FindAttribute(gClassNameAttributeName);
			if (attribute == 0)
			{
				return false;
			}
			core::Name<core::CaseSensitiveKey>* attributeValue = &((engine::Attribute<core::Name<core::CaseSensitiveKey> >*)attribute)->value;
			if (attributeValue == 0)
			{
				return false;
			}
			return fight::CompareNames(compare, attributeValue, &value);
		}

		// FUNCTION: ENGINE 0x104F5CA0
		bool ChargeValueCondition::Evaluate(int a, int b, int c, int d)
		{
			const HitEffectParams* params = AsParams(c);
			if (params == 0)
			{
				return false;
			}
			float rhs = charge;
			int op = compare;
			float lhs = params->chargeValue;
			return fight::CompareFloats(op, &lhs, &rhs);
		}

		// FUNCTION: ENGINE 0x104F57F0
		// NONMATCHING: the engine sums the three products of the dot product in the order z, x, y; the compiler orders ours z, y, x whatever the source order, and the clamp loads its constants in other places (46.9 %)
#ifdef NONMATCHING
		bool ImpactVsSurfaceAngleCondition::Evaluate(int a, int b, int c, int d)
		{
			const HitEffectParams* params = AsParams(c);
			math::Vector impact;
			impact.x = params->impactDirection.x;
			impact.y = params->impactDirection.y;
			impact.z = params->impactDirection.z;
			math::Vector surface;
			surface.x = params->surfaceNormal.x;
			surface.y = params->surfaceNormal.y;
			surface.z = params->surfaceNormal.z;
			impact.Normalize();
			surface.Normalize();
			float zz = surface.z * impact.z;
			float xx = surface.x * impact.x;
			float yy = surface.y * impact.y;
			float angle = zz + xx + yy;
			if (!(angle - choreo::gMinusOne >= 0.0f))
			{
				angle = choreo::gMinusOne;
			}
			if (angle - engine::driving::gOne >= 0.0f)
			{
				angle = engine::driving::gOne;
			}
			angle = (float)acos(angle);
			switch (compare)
			{
			case 0:
				return angle < tolerance;
			case 1:
				return angle <= tolerance;
			case 2:
				return angle == tolerance;
			case 3:
				return angle != tolerance;
			case 4:
				return angle >= tolerance;
			case 5:
				return angle > tolerance;
			}
			return false;
		}
#endif

		// FUNCTION: ENGINE 0x104F5A00
		// NONMATCHING: the engine sums the three products of the dot product in the order z, x, y; the compiler orders ours z, y, x whatever the source order, and the clamp loads its constants in other places (46.9 %)
#ifdef NONMATCHING
		bool SurfaceAngleCondition::Evaluate(int a, int b, int c, int d)
		{
			const HitEffectParams* params = AsParams(c);
			math::Vector impact;
			impact.x = params->impactDirection.x;
			impact.y = params->impactDirection.y;
			impact.z = params->impactDirection.z;
			math::Vector surface;
			surface.x = direction.x;
			surface.y = direction.y;
			surface.z = direction.z;
			impact.Normalize();
			surface.Normalize();
			float zz = surface.z * impact.z;
			float xx = surface.x * impact.x;
			float yy = surface.y * impact.y;
			float angle = zz + xx + yy;
			if (!(angle - choreo::gMinusOne >= 0.0f))
			{
				angle = choreo::gMinusOne;
			}
			if (angle - engine::driving::gOne >= 0.0f)
			{
				angle = engine::driving::gOne;
			}
			angle = (float)acos(angle);
			switch (compare)
			{
			case 0:
				return angle < tolerance;
			case 1:
				return angle <= tolerance;
			case 2:
				return angle == tolerance;
			case 3:
				return angle != tolerance;
			case 4:
				return angle >= tolerance;
			case 5:
				return angle > tolerance;
			}
			return false;
		}
#endif

		// FUNCTION: ENGINE 0x104F5CF0
		bool ObjectVolumeCondition::Evaluate(int a, int b, int c, int d)
		{
			const HitEffectParams* params = AsParams(c);
			if (params == 0)
			{
				return false;
			}
			float rhs = volume;
			int op = compare;
			float lhs = params->objectVolume;
			return fight::CompareFloats(op, &lhs, &rhs);
		}

		// FUNCTION: ENGINE 0x104F5D50
		bool ObjectSpeedCondition::Evaluate(int a, int b, int c, int d)
		{
			const HitEffectParams* params = AsParams(c);
			if (params == 0)
			{
				return false;
			}
			float rhs = speed * speed;
			int op = compare;
			float lhs = params->objectSpeed;
			return fight::CompareFloats(op, &lhs, &rhs);
		}

		// ---- evaluate end

		template class fight::PropertyEnumConstList<AttackTypeCondition>;
		template class fight::ConditionFactoryTemplate<AttackTypeCondition>;
		template class fight::ConditionFactoryCasterTemplate<AttackTypeCondition>;
		template class fight::PropertyConditionGroup<GiverConditionGroupCondition>;
		template class fight::ConditionFactoryTemplate<GiverConditionGroupCondition>;
		template class fight::ConditionFactoryCasterTemplate<GiverConditionGroupCondition>;
		template class fight::PropertyBool<FromMuscleMassCondition>;
		template class fight::ConditionFactoryTemplate<FromMuscleMassCondition>;
		template class fight::ConditionFactoryCasterTemplate<FromMuscleMassCondition>;
		template class fight::PropertyEnumConstList<DamageTakenCondition>;
		template class fight::PropertyFloatConstRange<DamageTakenCondition>;
		template class fight::ConditionFactoryTemplate<DamageTakenCondition>;
		template class fight::ConditionFactoryCasterTemplate<DamageTakenCondition>;
		template class fight::PropertyNameList<MaterialTypeCondition>;
		template class fight::ConditionFactoryTemplate<MaterialTypeCondition>;
		template class fight::ConditionFactoryCasterTemplate<MaterialTypeCondition>;
		template class fight::PropertyEnumConstList<DamageScaleCondition>;
		template class fight::PropertyFloatConstRange<DamageScaleCondition>;
		template class fight::ConditionFactoryTemplate<DamageScaleCondition>;
		template class fight::ConditionFactoryCasterTemplate<DamageScaleCondition>;
		template class fight::PropertyNameList<EffectTypeCondition>;
		template class fight::ConditionFactoryTemplate<EffectTypeCondition>;
		template class fight::ConditionFactoryCasterTemplate<EffectTypeCondition>;
		template class fight::PropertyEnumConstList<ImpactVsSurfaceAngleCondition>;
		template class fight::PropertyFloatConstRange<ImpactVsSurfaceAngleCondition>;
		template class fight::ConditionFactoryTemplate<ImpactVsSurfaceAngleCondition>;
		template class fight::ConditionFactoryCasterTemplate<ImpactVsSurfaceAngleCondition>;
		template class fight::PropertyEnumConstList<ObjectVolumeCondition>;
		template class fight::PropertyFloatConstRange<ObjectVolumeCondition>;
		template class fight::ConditionFactoryTemplate<ObjectVolumeCondition>;
		template class fight::ConditionFactoryCasterTemplate<ObjectVolumeCondition>;
		template class fight::PropertyEnumConstList<DamageGivenCondition>;
		template class fight::PropertyFloatConstRange<DamageGivenCondition>;
		template class fight::ConditionFactoryTemplate<DamageGivenCondition>;
		template class fight::ConditionFactoryCasterTemplate<DamageGivenCondition>;
		template class fight::ConditionFactoryTemplate<DamageOriginatorIsPlayerCondition>;
		template class fight::ConditionFactoryCasterTemplate<DamageOriginatorIsPlayerCondition>;
		template class fight::PropertyEnumConstList<SurfaceAngleCondition>;
		template class fight::PropertyVector<SurfaceAngleCondition>;
		template class fight::PropertyFloatConstRange<SurfaceAngleCondition>;
		template class fight::ConditionFactoryTemplate<SurfaceAngleCondition>;
		template class fight::ConditionFactoryCasterTemplate<SurfaceAngleCondition>;
		template class fight::PropertyConditionGroup<ReceiverConditionGroupCondition>;
		template class fight::ConditionFactoryTemplate<ReceiverConditionGroupCondition>;
		template class fight::ConditionFactoryCasterTemplate<ReceiverConditionGroupCondition>;
		template class fight::PropertyEnumConstList<ChargeValueCondition>;
		template class fight::PropertyFloatConstRange<ChargeValueCondition>;
		template class fight::ConditionFactoryTemplate<ChargeValueCondition>;
		template class fight::ConditionFactoryCasterTemplate<ChargeValueCondition>;
		template class fight::PropertyEnumConstList<ReceiverGrabbableClassCondition>;
		template class fight::PropertyName<ReceiverGrabbableClassCondition>;
		template class fight::ConditionFactoryTemplate<ReceiverGrabbableClassCondition>;
		template class fight::ConditionFactoryCasterTemplate<ReceiverGrabbableClassCondition>;
		template class fight::PropertyNameList<GiverMaterialTypeCondition>;
		template class fight::ConditionFactoryTemplate<GiverMaterialTypeCondition>;
		template class fight::ConditionFactoryCasterTemplate<GiverMaterialTypeCondition>;
		template class fight::PropertyEnumConstList<ReceiverClassNameCondition>;
		template class fight::PropertyName<ReceiverClassNameCondition>;
		template class fight::ConditionFactoryTemplate<ReceiverClassNameCondition>;
		template class fight::ConditionFactoryCasterTemplate<ReceiverClassNameCondition>;
		template class fight::PropertyEnumConstList<ObjectSpeedCondition>;
		template class fight::PropertyFloatConstRange<ObjectSpeedCondition>;
		template class fight::ConditionFactoryTemplate<ObjectSpeedCondition>;
		template class fight::ConditionFactoryCasterTemplate<ObjectSpeedCondition>;
		template class fight::PropertyEnumConstList<DamageTypeCondition>;
		template class fight::ConditionFactoryTemplate<DamageTypeCondition>;
		template class fight::ConditionFactoryCasterTemplate<DamageTypeCondition>;
		template class fight::PropertyNameList<HitTypeCondition>;
		template class fight::ConditionFactoryTemplate<HitTypeCondition>;
		template class fight::ConditionFactoryCasterTemplate<HitTypeCondition>;
	}
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D52BD0
// FUNCTION: ENGINE 0x10D825C0


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104F6EF0
// FUNCTION: ENGINE 0x104F6F20
// FUNCTION: ENGINE 0x104F6F50
// FUNCTION: ENGINE 0x104F6F80
// FUNCTION: ENGINE 0x104F6FF0
// FUNCTION: ENGINE 0x104F7060
// FUNCTION: ENGINE 0x104F7090
// FUNCTION: ENGINE 0x104F70C0
// FUNCTION: ENGINE 0x104F70F0
// FUNCTION: ENGINE 0x104F7120
// FUNCTION: ENGINE 0x104F7150
// FUNCTION: ENGINE 0x104F7180
// FUNCTION: ENGINE 0x104F7270
// FUNCTION: ENGINE 0x104F72A0
// FUNCTION: ENGINE 0x104F7310
// FUNCTION: ENGINE 0x104F7320
// FUNCTION: ENGINE 0x104F7350
// FUNCTION: ENGINE 0x104F7360
// FUNCTION: ENGINE 0x104F7390
// FUNCTION: ENGINE 0x104F73A0
// FUNCTION: ENGINE 0x104F73D0
// FUNCTION: ENGINE 0x104F73E0
// FUNCTION: ENGINE 0x104F7410
// FUNCTION: ENGINE 0x104F7420
// FUNCTION: ENGINE 0x104F7450
// FUNCTION: ENGINE 0x104F7460
// FUNCTION: ENGINE 0x104F7490
// FUNCTION: ENGINE 0x104F74A0
// FUNCTION: ENGINE 0x104F74D0
// FUNCTION: ENGINE 0x104F74E0
// FUNCTION: ENGINE 0x104F7510
// FUNCTION: ENGINE 0x104F7520
// FUNCTION: ENGINE 0x104F7550
// FUNCTION: ENGINE 0x104F7560
// FUNCTION: ENGINE 0x104F7590
// FUNCTION: ENGINE 0x104F75A0
// FUNCTION: ENGINE 0x104F75D0
// FUNCTION: ENGINE 0x104F7600
// FUNCTION: ENGINE 0x104F7620
// FUNCTION: ENGINE 0x104F7670
// FUNCTION: ENGINE 0x104F7680
// FUNCTION: ENGINE 0x104F76B0
// FUNCTION: ENGINE 0x104F76C0
// FUNCTION: ENGINE 0x104F76F0
// FUNCTION: ENGINE 0x104F7700
// FUNCTION: ENGINE 0x104F7730
// FUNCTION: ENGINE 0x104F7740
// FUNCTION: ENGINE 0x104F7770
// FUNCTION: ENGINE 0x104F7780
// FUNCTION: ENGINE 0x104F77B0
// FUNCTION: ENGINE 0x104F77C0
// FUNCTION: ENGINE 0x104F77F0
// FUNCTION: ENGINE 0x104F7800
// FUNCTION: ENGINE 0x104F7830
// FUNCTION: ENGINE 0x104F7840
// FUNCTION: ENGINE 0x104F7870
// FUNCTION: ENGINE 0x104F7880
// FUNCTION: ENGINE 0x104F78B0
// FUNCTION: ENGINE 0x104F78E0
// FUNCTION: ENGINE 0x104F7910
// FUNCTION: ENGINE 0x104F7940
// FUNCTION: ENGINE 0x104F7970
// FUNCTION: ENGINE 0x104F79A0
// FUNCTION: ENGINE 0x104F79D0
// FUNCTION: ENGINE 0x104F7A10
// FUNCTION: ENGINE 0x104F7A20
// FUNCTION: ENGINE 0x104F7A50
// FUNCTION: ENGINE 0x104F7A70
// FUNCTION: ENGINE 0x104F7A80
// FUNCTION: ENGINE 0x104F7AB0
// FUNCTION: ENGINE 0x104F7AD0
// FUNCTION: ENGINE 0x104F7B00
// FUNCTION: ENGINE 0x104F7B20
// FUNCTION: ENGINE 0x104F7B30
// FUNCTION: ENGINE 0x104F7B70
// FUNCTION: ENGINE 0x104F7B80
// FUNCTION: ENGINE 0x104F7BB0
// FUNCTION: ENGINE 0x104F7BD0
// FUNCTION: ENGINE 0x104F7BE0
// FUNCTION: ENGINE 0x104F7C10
// FUNCTION: ENGINE 0x104F7C40
// FUNCTION: ENGINE 0x104F7C50
// FUNCTION: ENGINE 0x104F7C90
// FUNCTION: ENGINE 0x104F7CA0
// FUNCTION: ENGINE 0x104F7CD0
// FUNCTION: ENGINE 0x104F7CF0
// FUNCTION: ENGINE 0x104F7D00
// FUNCTION: ENGINE 0x104F7D30
// FUNCTION: ENGINE 0x104F7D60
// FUNCTION: ENGINE 0x104F7D70
// FUNCTION: ENGINE 0x104F7DB0
// FUNCTION: ENGINE 0x104F7DC0
// FUNCTION: ENGINE 0x104F7DF0
// FUNCTION: ENGINE 0x104F7E10
// FUNCTION: ENGINE 0x104F7E20
// FUNCTION: ENGINE 0x104F7E50
// FUNCTION: ENGINE 0x104F7E80
// FUNCTION: ENGINE 0x104F7E90
// FUNCTION: ENGINE 0x104F7ED0
// FUNCTION: ENGINE 0x104F7EE0
// FUNCTION: ENGINE 0x104F7F10
// FUNCTION: ENGINE 0x104F7F30
// FUNCTION: ENGINE 0x104F7F40
// FUNCTION: ENGINE 0x104F7F70
// FUNCTION: ENGINE 0x104F7FA0
// FUNCTION: ENGINE 0x104F7FB0
// FUNCTION: ENGINE 0x104F7FF0
// FUNCTION: ENGINE 0x104F8000
// FUNCTION: ENGINE 0x104F8030
// FUNCTION: ENGINE 0x104F8050
// FUNCTION: ENGINE 0x104F8060
// FUNCTION: ENGINE 0x104F8090
// FUNCTION: ENGINE 0x104F80C0
// FUNCTION: ENGINE 0x104F80D0
// FUNCTION: ENGINE 0x104F8110
// FUNCTION: ENGINE 0x104F8120
// FUNCTION: ENGINE 0x104F8150
// FUNCTION: ENGINE 0x104F8170
// FUNCTION: ENGINE 0x104F8180
// FUNCTION: ENGINE 0x104F81B0
// FUNCTION: ENGINE 0x104F81D0
// FUNCTION: ENGINE 0x104F81E0
// FUNCTION: ENGINE 0x104F8210
// FUNCTION: ENGINE 0x104F8240
// FUNCTION: ENGINE 0x104F8250
// FUNCTION: ENGINE 0x104F8280
// FUNCTION: ENGINE 0x104F82A0
// FUNCTION: ENGINE 0x104F82E0
// FUNCTION: ENGINE 0x104F82F0
// FUNCTION: ENGINE 0x104F8320
// FUNCTION: ENGINE 0x104F8340
// FUNCTION: ENGINE 0x104F8350
// FUNCTION: ENGINE 0x104F8380
// FUNCTION: ENGINE 0x104F83B0
// FUNCTION: ENGINE 0x104F83C0
// FUNCTION: ENGINE 0x104F8400
// FUNCTION: ENGINE 0x104F8410
// FUNCTION: ENGINE 0x104F8440
// FUNCTION: ENGINE 0x104F8460
// FUNCTION: ENGINE 0x104F8470
// FUNCTION: ENGINE 0x104F84B0
// FUNCTION: ENGINE 0x104F84C0
// FUNCTION: ENGINE 0x104F84F0
// FUNCTION: ENGINE 0x104F8510
// FUNCTION: ENGINE 0x104F8520
// FUNCTION: ENGINE 0x104F8560
// FUNCTION: ENGINE 0x104F8570
// FUNCTION: ENGINE 0x104F85A0
// FUNCTION: ENGINE 0x104F85C0
// FUNCTION: ENGINE 0x104F85D0
// FUNCTION: ENGINE 0x104F8600
// FUNCTION: ENGINE 0x104F8630
// FUNCTION: ENGINE 0x104F8640
// FUNCTION: ENGINE 0x104F8680
// FUNCTION: ENGINE 0x104F8690
// FUNCTION: ENGINE 0x104F86C0
// FUNCTION: ENGINE 0x104F86E0
// FUNCTION: ENGINE 0x104F9970
// FUNCTION: ENGINE 0x104F99A0
// FUNCTION: ENGINE 0x104F99C0
// FUNCTION: ENGINE 0x104F99D0
// FUNCTION: ENGINE 0x104F9A00
// FUNCTION: ENGINE 0x104F9A20
// FUNCTION: ENGINE 0x104F9A30
// FUNCTION: ENGINE 0x104F9A60
// FUNCTION: ENGINE 0x104F9A80
// FUNCTION: ENGINE 0x104F9AB0
// FUNCTION: ENGINE 0x104F9AD0
// FUNCTION: ENGINE 0x104F9AE0
// FUNCTION: ENGINE 0x104F9B10
// FUNCTION: ENGINE 0x104F9B30
// FUNCTION: ENGINE 0x104F9B60
// FUNCTION: ENGINE 0x104F9B80
// FUNCTION: ENGINE 0x104F9B90
// FUNCTION: ENGINE 0x104F9BC0
// FUNCTION: ENGINE 0x104F9BE0
// FUNCTION: ENGINE 0x104F9C10
// FUNCTION: ENGINE 0x104F9C30
// FUNCTION: ENGINE 0x104F9C60
// FUNCTION: ENGINE 0x104F9C80
// FUNCTION: ENGINE 0x104F9CB0
// FUNCTION: ENGINE 0x104F9CD0
// FUNCTION: ENGINE 0x104F9D00
// FUNCTION: ENGINE 0x104F9D20
// FUNCTION: ENGINE 0x104F9D50
// FUNCTION: ENGINE 0x104F9D70
// FUNCTION: ENGINE 0x104F9DA0
// FUNCTION: ENGINE 0x104F9DC0
// FUNCTION: ENGINE 0x104F9DF0
// FUNCTION: ENGINE 0x104F9E10
// FUNCTION: ENGINE 0x104F9E40
// FUNCTION: ENGINE 0x104F9E60
// FUNCTION: ENGINE 0x104F9E90
// FUNCTION: ENGINE 0x104F9EB0
// FUNCTION: ENGINE 0x104F9EE0
// FUNCTION: ENGINE 0x104F9F00
// FUNCTION: ENGINE 0x104F9F30
// FUNCTION: ENGINE 0x104F9F50
// FUNCTION: ENGINE 0x104F9F80
// FUNCTION: ENGINE 0x104FA400
// FUNCTION: ENGINE 0x104FA450
// FUNCTION: ENGINE 0x104FA4A0
// FUNCTION: ENGINE 0x104FA4F0
// FUNCTION: ENGINE 0x104FA540
// FUNCTION: ENGINE 0x104FA590
// FUNCTION: ENGINE 0x104FA5E0
// FUNCTION: ENGINE 0x104FA630
// FUNCTION: ENGINE 0x104FA680
// FUNCTION: ENGINE 0x104FA6D0
// FUNCTION: ENGINE 0x104FA720
// FUNCTION: ENGINE 0x104FA770
// FUNCTION: ENGINE 0x104FA7C0
// FUNCTION: ENGINE 0x104FA810
// FUNCTION: ENGINE 0x104FA840
// FUNCTION: ENGINE 0x104FA860
// FUNCTION: ENGINE 0x104FA890
// FUNCTION: ENGINE 0x104FA8B0
// FUNCTION: ENGINE 0x104FA8E0
// FUNCTION: ENGINE 0x104FA900
// FUNCTION: ENGINE 0x104FA930
// FUNCTION: ENGINE 0x104FA950
// FUNCTION: ENGINE 0x104FA980
// FUNCTION: ENGINE 0x104FA9A0
// FUNCTION: ENGINE 0x104FA9D0
// FUNCTION: ENGINE 0x104FA9F0
// FUNCTION: ENGINE 0x104FAA40
// FUNCTION: ENGINE 0x104FAA90
// FUNCTION: ENGINE 0x104FAAE0
// FUNCTION: ENGINE 0x104FAB30
// FUNCTION: ENGINE 0x104FAB80
