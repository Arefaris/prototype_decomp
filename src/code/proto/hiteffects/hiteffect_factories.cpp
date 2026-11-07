// The registration groups of the hit effects' fight items: the conditions (RegisterAt104F54B0Factories), the effect
// tracks (RegisterAt104FF140Factories) and the group of factories the engine registers together
// (RegisterAt104F3900Factories). The groups are functions of the units whose factories they register (0x104F3900,
// 0x104F54B0, 0x104FF140); no assert path names them, so the names are guesses.
#include "code/proto/fightitems/motion/motion_intersectionproperties.h"
#include "code/proto/hiteffects/hiteffect_conditions.h"
#include "code/proto/hiteffects/hiteffect_fxlight.h"

namespace engine
{
	// 0x1080A9E0 (conditions.cpp), 0x1080D4C0 (effecttracksetup.cpp)
	void RegisterHealthConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAbortEffectTrackFactory(fight::TrackRegistry* registry, const char* name);
}

namespace proto
{
	namespace HitEffectManager
	{
		// 0x1050BE00 (the hit effects' effect track)
		void RegisterEffectTrackFactory(fight::TrackRegistry* registry, const char* name);
	}

	namespace fightitems
	{
		// 0x104FB8A0, 0x10503730
		bool RegisterAt104FB8A0Factories(fight::TrackRegistry* registry);
		bool RegisterAt10503730Factories(fight::TrackRegistry* registry);
		// 0x104F54B0, 0x104FF140
		bool RegisterAt104F54B0Factories(fight::TrackRegistry* registry);
		bool RegisterAt104FF140Factories(fight::TrackRegistry* registry);

		// FUNCTION: ENGINE 0x104F3900
		void RegisterAt104F3900Factories(fight::TrackRegistry* registry)
		{
			RegisterAt104F54B0Factories(registry);
			RegisterAt104FB8A0Factories(registry);
			RegisterAt104FF140Factories(registry);
			RegisterAt10503730Factories(registry);
		}

		// FUNCTION: ENGINE 0x104F54B0
		bool RegisterAt104F54B0Factories(fight::TrackRegistry* registry)
		{
			engine::RegisterHealthConditionFactory(registry, "health");
			motion::RegisterIntersectionPropertiesConditionFactory(registry, "intersectionProperties");
			HitEffectManager::RegisterAttackTypeConditionFactory(registry, "attackType");
			HitEffectManager::RegisterChargeValueConditionFactory(registry, "chargeValue");
			HitEffectManager::RegisterDamageGivenConditionFactory(registry, "damageGiven");
			HitEffectManager::RegisterDamageScaleConditionFactory(registry, "damageScale");
			HitEffectManager::RegisterDamageTakenConditionFactory(registry, "damageTaken");
			HitEffectManager::RegisterDamageTypeConditionFactory(registry, "damageType");
			HitEffectManager::RegisterEffectTypeConditionFactory(registry, "effectType");
			HitEffectManager::RegisterGiverConditionGroupConditionFactory(registry, "giverConditionGroup");
			HitEffectManager::RegisterGiverMaterialTypeConditionFactory(registry, "giverMaterialType");
			HitEffectManager::RegisterHitTypeConditionFactory(registry, "hitType");
			HitEffectManager::RegisterImpactVsSurfaceAngleConditionFactory(registry, "impactVsSurfaceAngle");
			HitEffectManager::RegisterMaterialTypeConditionFactory(registry, "materialType");
			HitEffectManager::RegisterObjectSpeedConditionFactory(registry, "objectSpeed");
			HitEffectManager::RegisterObjectVolumeConditionFactory(registry, "objectVolume");
			HitEffectManager::RegisterReceiverClassNameConditionFactory(registry, "receiverClassName");
			HitEffectManager::RegisterReceiverConditionGroupConditionFactory(registry, "receiverConditionGroup");
			HitEffectManager::RegisterReceiverGrabbableClassConditionFactory(registry, "receiverGrabbableClass");
			HitEffectManager::RegisterSurfaceAngleConditionFactory(registry, "surfaceAngle");
			HitEffectManager::RegisterDamageOriginatorIsPlayerConditionFactory(registry, "damageOriginatorIsPlayer");
			HitEffectManager::RegisterFromMuscleMassConditionFactory(registry, "fromMuscleMass");
			return true;
		}

		// FUNCTION: ENGINE 0x104FF140
		bool RegisterAt104FF140Factories(fight::TrackRegistry* registry)
		{
			HitEffectManager::RegisterEffectTrackFactory(registry, "effect");
			HitEffectManager::RegisterFXLight_PointTrackFactory(registry, "fxlight_point");
			engine::RegisterAbortEffectTrackFactory(registry, "abortEffect");
			return true;
		}
	}
}
