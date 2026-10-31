// Fight items of the motion group: SupportingLimbTestSurfaceNormalVelocityArcCondition, SupportingLimbTestSurfaceNormalAngleCondition, SupportingLimbSurfaceIntersectionPropertiesCondition, SupportingLimbTestSurfaceVelocityAngleCondition, SupportingLimbTestTimeToImpactCondition, SupportingSurfaceNormalVelocityArcCondition, SupportingSurfaceConditionGroupCondition, SupportingLimbTestSurfaceDistanceCondition, SupportingLimbTestSwitchSurfacesCondition, SupportingLimbTestSurfaceConditionGroupCondition, SupportingLimbSetActiveTrack, SupportingLimbTestTrack, SupportingLimbSetActiveRangeTrack, SurfaceMoveAtVelocityTrack, SupportingLimbSetDirectionTrack (unit 0x101B7170 - 0x101BBA40; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_supportinglimb.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gSupportingLimbTestSurfaceNormalVelocityArcConditionProperties;  // 0x11254B10

			// FUNCTION: ENGINE 0x101B7170
			bool SupportingLimbTestSurfaceNormalVelocityArcCondition::SetVelocityType(int newValue)
			{
				velocityType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7180
			bool SupportingLimbTestSurfaceNormalVelocityArcCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7190
			bool SupportingLimbTestSurfaceNormalVelocityArcCondition::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7660
			fight::Property* SupportingLimbTestSurfaceNormalVelocityArcCondition::GetProperty(int index)
			{
				return gSupportingLimbTestSurfaceNormalVelocityArcConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101B7680
			void SupportingLimbTestSurfaceNormalVelocityArcCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSupportingLimbTestSurfaceNormalVelocityArcConditionProperties);
			}

			// FUNCTION: ENGINE 0x101B7690
			SupportingLimbTestSurfaceNormalVelocityArcCondition::SupportingLimbTestSurfaceNormalVelocityArcCondition() : fight::Condition(0), arc(0.0f), compare(0), velocityType(0)
			{
			}

			// FUNCTION: ENGINE 0x101B76D0
			SupportingLimbTestSurfaceNormalVelocityArcCondition::~SupportingLimbTestSurfaceNormalVelocityArcCondition()
			{
			}

			// FUNCTION: ENGINE 0x101B9930
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SupportingLimbTestSurfaceNormalVelocityArcCondition::RegisterProperties()
			{
				if (gSupportingLimbTestSurfaceNormalVelocityArcConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<SupportingLimbTestSurfaceNormalVelocityArcCondition>("velocityType", gSupportingLimbTestSurfaceNormalVelocityArcConditionVelocityTypeTable, gSupportingLimbTestSurfaceNormalVelocityArcConditionVelocityTypeCount, &SupportingLimbTestSurfaceNormalVelocityArcCondition::SetVelocityType);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<SupportingLimbTestSurfaceNormalVelocityArcCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &SupportingLimbTestSurfaceNormalVelocityArcCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<SupportingLimbTestSurfaceNormalVelocityArcCondition>("arc", &SupportingLimbTestSurfaceNormalVelocityArcCondition::SetArc);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gSupportingLimbTestSurfaceNormalVelocityArcConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B9660
			fight::ConditionFactory* CreateSupportingLimbTestSurfaceNormalVelocityArcConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbTestSurfaceNormalVelocityArcCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BA680
			void RegisterSupportingLimbTestSurfaceNormalVelocityArcConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbTestSurfaceNormalVelocityArcCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSupportingLimbTestSurfaceNormalAngleConditionProperties;  // 0x11254B14

			// FUNCTION: ENGINE 0x101B71B0
			bool SupportingLimbTestSurfaceNormalAngleCondition::SetNormal(const math::Vector& newValue)
			{
				normal.x = newValue.x;
				normal.y = newValue.y;
				normal.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101B71D0
			bool SupportingLimbTestSurfaceNormalAngleCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B71E0
			bool SupportingLimbTestSurfaceNormalAngleCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101B76E0
			fight::Property* SupportingLimbTestSurfaceNormalAngleCondition::GetProperty(int index)
			{
				return gSupportingLimbTestSurfaceNormalAngleConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101B7700
			void SupportingLimbTestSurfaceNormalAngleCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSupportingLimbTestSurfaceNormalAngleConditionProperties);
			}

			// FUNCTION: ENGINE 0x101B7710
			SupportingLimbTestSurfaceNormalAngleCondition::SupportingLimbTestSurfaceNormalAngleCondition() : fight::Condition(0), normal(0.0f, 1.0f, 0.0f), angle(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101B7760
			SupportingLimbTestSurfaceNormalAngleCondition::~SupportingLimbTestSurfaceNormalAngleCondition()
			{
			}

			// FUNCTION: ENGINE 0x101B9A70
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SupportingLimbTestSurfaceNormalAngleCondition::RegisterProperties()
			{
				if (gSupportingLimbTestSurfaceNormalAngleConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyVector<SupportingLimbTestSurfaceNormalAngleCondition>("normal", &SupportingLimbTestSurfaceNormalAngleCondition::SetNormal);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<SupportingLimbTestSurfaceNormalAngleCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &SupportingLimbTestSurfaceNormalAngleCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<SupportingLimbTestSurfaceNormalAngleCondition>("angle", &SupportingLimbTestSurfaceNormalAngleCondition::SetAngle);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gSupportingLimbTestSurfaceNormalAngleConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B9690
			fight::ConditionFactory* CreateSupportingLimbTestSurfaceNormalAngleConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbTestSurfaceNormalAngleCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BA6B0
			void RegisterSupportingLimbTestSurfaceNormalAngleConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbTestSurfaceNormalAngleCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSupportingLimbSurfaceIntersectionPropertiesConditionProperties;  // 0x11254B18

			// FUNCTION: ENGINE 0x101B7200
			bool SupportingLimbSurfaceIntersectionPropertiesCondition::SetTestBits(int newValue)
			{
				testBits = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7210
			bool SupportingLimbSurfaceIntersectionPropertiesCondition::SetMatchAgainst(int newValue)
			{
				matchAgainst = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7770
			fight::Property* SupportingLimbSurfaceIntersectionPropertiesCondition::GetProperty(int index)
			{
				return gSupportingLimbSurfaceIntersectionPropertiesConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101B7790
			void SupportingLimbSurfaceIntersectionPropertiesCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSupportingLimbSurfaceIntersectionPropertiesConditionProperties);
			}

			// FUNCTION: ENGINE 0x101B77A0
			SupportingLimbSurfaceIntersectionPropertiesCondition::SupportingLimbSurfaceIntersectionPropertiesCondition() : fight::Condition(0), matchAgainst(0), testBits(0)
			{
			}

			// FUNCTION: ENGINE 0x101B77D0
			SupportingLimbSurfaceIntersectionPropertiesCondition::~SupportingLimbSurfaceIntersectionPropertiesCondition()
			{
			}

			// FUNCTION: ENGINE 0x101B9BA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SupportingLimbSurfaceIntersectionPropertiesCondition::RegisterProperties()
			{
				if (gSupportingLimbSurfaceIntersectionPropertiesConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBitfieldConstList<SupportingLimbSurfaceIntersectionPropertiesCondition>("testBits", gDetectObbCollisionConditionCollideWithTable, gDetectObbCollisionConditionCollideWithCount, &SupportingLimbSurfaceIntersectionPropertiesCondition::SetTestBits);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<SupportingLimbSurfaceIntersectionPropertiesCondition>("matchAgainst", gSupportingLimbSurfaceIntersectionPropertiesConditionMatchAgainstTable, 2, &SupportingLimbSurfaceIntersectionPropertiesCondition::SetMatchAgainst);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gSupportingLimbSurfaceIntersectionPropertiesConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B96C0
			fight::ConditionFactory* CreateSupportingLimbSurfaceIntersectionPropertiesConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbSurfaceIntersectionPropertiesCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BA6E0
			void RegisterSupportingLimbSurfaceIntersectionPropertiesConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbSurfaceIntersectionPropertiesCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSupportingLimbTestSurfaceVelocityAngleConditionProperties;  // 0x11254B1C

			// FUNCTION: ENGINE 0x101B7220
			bool SupportingLimbTestSurfaceVelocityAngleCondition::SetVelocityType(int newValue)
			{
				velocityType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7230
			bool SupportingLimbTestSurfaceVelocityAngleCondition::SetZeroVector(const math::Vector& newValue)
			{
				zeroVector.x = newValue.x;
				zeroVector.y = newValue.y;
				zeroVector.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7250
			bool SupportingLimbTestSurfaceVelocityAngleCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7270
			bool SupportingLimbTestSurfaceVelocityAngleCondition::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7290
			bool SupportingLimbTestSurfaceVelocityAngleCondition::SetUseExcessVelocity(bool newValue)
			{
				useExcessVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B77E0
			fight::Property* SupportingLimbTestSurfaceVelocityAngleCondition::GetProperty(int index)
			{
				return gSupportingLimbTestSurfaceVelocityAngleConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101B7800
			void SupportingLimbTestSurfaceVelocityAngleCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSupportingLimbTestSurfaceVelocityAngleConditionProperties);
			}

			// FUNCTION: ENGINE 0x101B7810
			SupportingLimbTestSurfaceVelocityAngleCondition::SupportingLimbTestSurfaceVelocityAngleCondition() : fight::Condition(0), zeroVector(0.0f, 1.0f, 0.0f), angle(0.0f), arc(0.0f), velocityType(0), useExcessVelocity(false)
			{
			}

			// FUNCTION: ENGINE 0x101B7870
			SupportingLimbTestSurfaceVelocityAngleCondition::~SupportingLimbTestSurfaceVelocityAngleCondition()
			{
			}

			// FUNCTION: ENGINE 0x101B9CA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SupportingLimbTestSurfaceVelocityAngleCondition::RegisterProperties()
			{
				if (gSupportingLimbTestSurfaceVelocityAngleConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<SupportingLimbTestSurfaceVelocityAngleCondition>("velocityType", gSupportingLimbTestSurfaceNormalVelocityArcConditionVelocityTypeTable, gSupportingLimbTestSurfaceNormalVelocityArcConditionVelocityTypeCount, &SupportingLimbTestSurfaceVelocityAngleCondition::SetVelocityType);
					properties[0] = property;
					property = new fight::PropertyVector<SupportingLimbTestSurfaceVelocityAngleCondition>("zeroVector", &SupportingLimbTestSurfaceVelocityAngleCondition::SetZeroVector);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<SupportingLimbTestSurfaceVelocityAngleCondition>("angle", &SupportingLimbTestSurfaceVelocityAngleCondition::SetAngle);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<SupportingLimbTestSurfaceVelocityAngleCondition>("arc", &SupportingLimbTestSurfaceVelocityAngleCondition::SetArc);
					properties[3] = property;
					property = new fight::PropertyBool<SupportingLimbTestSurfaceVelocityAngleCondition>("useExcessVelocity", &SupportingLimbTestSurfaceVelocityAngleCondition::SetUseExcessVelocity);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gSupportingLimbTestSurfaceVelocityAngleConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B96F0
			fight::ConditionFactory* CreateSupportingLimbTestSurfaceVelocityAngleConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbTestSurfaceVelocityAngleCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BA710
			void RegisterSupportingLimbTestSurfaceVelocityAngleConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbTestSurfaceVelocityAngleCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSupportingLimbTestTimeToImpactConditionProperties;  // 0x11254B20

			// FUNCTION: ENGINE 0x101B72A0
			bool SupportingLimbTestTimeToImpactCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B72B0
			bool SupportingLimbTestTimeToImpactCondition::SetTimeToImpact(float newValue)
			{
				timeToImpact = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7880
			fight::Property* SupportingLimbTestTimeToImpactCondition::GetProperty(int index)
			{
				return gSupportingLimbTestTimeToImpactConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101B78A0
			void SupportingLimbTestTimeToImpactCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSupportingLimbTestTimeToImpactConditionProperties);
			}

			// FUNCTION: ENGINE 0x101B78B0
			SupportingLimbTestTimeToImpactCondition::SupportingLimbTestTimeToImpactCondition() : fight::Condition(0), timeToImpact(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101B78E0
			SupportingLimbTestTimeToImpactCondition::~SupportingLimbTestTimeToImpactCondition()
			{
			}

			// FUNCTION: ENGINE 0x101B9E50
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SupportingLimbTestTimeToImpactCondition::RegisterProperties()
			{
				if (gSupportingLimbTestTimeToImpactConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<SupportingLimbTestTimeToImpactCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &SupportingLimbTestTimeToImpactCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SupportingLimbTestTimeToImpactCondition>("timeToImpact", &SupportingLimbTestTimeToImpactCondition::SetTimeToImpact);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gSupportingLimbTestTimeToImpactConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B9720
			fight::ConditionFactory* CreateSupportingLimbTestTimeToImpactConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbTestTimeToImpactCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BA740
			void RegisterSupportingLimbTestTimeToImpactConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbTestTimeToImpactCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSupportingSurfaceNormalVelocityArcConditionProperties;  // 0x11254B24

			// FUNCTION: ENGINE 0x101B72D0
			bool SupportingSurfaceNormalVelocityArcCondition::SetVelocityType(int newValue)
			{
				velocityType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B72E0
			bool SupportingSurfaceNormalVelocityArcCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B72F0
			bool SupportingSurfaceNormalVelocityArcCondition::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101B78F0
			fight::Property* SupportingSurfaceNormalVelocityArcCondition::GetProperty(int index)
			{
				return gSupportingSurfaceNormalVelocityArcConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101B7910
			void SupportingSurfaceNormalVelocityArcCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSupportingSurfaceNormalVelocityArcConditionProperties);
			}

			// FUNCTION: ENGINE 0x101B7920
			SupportingSurfaceNormalVelocityArcCondition::SupportingSurfaceNormalVelocityArcCondition() : fight::Condition(0), arc(0.0f), compare(0), velocityType(0)
			{
			}

			// FUNCTION: ENGINE 0x101B7960
			SupportingSurfaceNormalVelocityArcCondition::~SupportingSurfaceNormalVelocityArcCondition()
			{
			}

			// FUNCTION: ENGINE 0x101B9F40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SupportingSurfaceNormalVelocityArcCondition::RegisterProperties()
			{
				if (gSupportingSurfaceNormalVelocityArcConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<SupportingSurfaceNormalVelocityArcCondition>("velocityType", gSupportingLimbTestSurfaceNormalVelocityArcConditionVelocityTypeTable, gSupportingLimbTestSurfaceNormalVelocityArcConditionVelocityTypeCount, &SupportingSurfaceNormalVelocityArcCondition::SetVelocityType);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<SupportingSurfaceNormalVelocityArcCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &SupportingSurfaceNormalVelocityArcCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<SupportingSurfaceNormalVelocityArcCondition>("arc", &SupportingSurfaceNormalVelocityArcCondition::SetArc);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gSupportingSurfaceNormalVelocityArcConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B9750
			fight::ConditionFactory* CreateSupportingSurfaceNormalVelocityArcConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingSurfaceNormalVelocityArcCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BA770
			void RegisterSupportingSurfaceNormalVelocityArcConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingSurfaceNormalVelocityArcCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSupportingSurfaceConditionGroupConditionProperties;  // 0x11254B28

			// FUNCTION: ENGINE 0x101B7310
			fight::ConditionList* SupportingSurfaceConditionGroupCondition::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x101B7970
			fight::Property* SupportingSurfaceConditionGroupCondition::GetProperty(int index)
			{
				return gSupportingSurfaceConditionGroupConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101B7990
			void SupportingSurfaceConditionGroupCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSupportingSurfaceConditionGroupConditionProperties);
			}

			// FUNCTION: ENGINE 0x101B79A0
			SupportingSurfaceConditionGroupCondition::SupportingSurfaceConditionGroupCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x101B79D0
			SupportingSurfaceConditionGroupCondition::~SupportingSurfaceConditionGroupCondition()
			{
			}

			// FUNCTION: ENGINE 0x101BA080
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SupportingSurfaceConditionGroupCondition::RegisterProperties()
			{
				if (gSupportingSurfaceConditionGroupConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyConditionGroup<SupportingSurfaceConditionGroupCondition>("conditions", &SupportingSurfaceConditionGroupCondition::SetConditions);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gSupportingSurfaceConditionGroupConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B9780
			fight::ConditionFactory* CreateSupportingSurfaceConditionGroupConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingSurfaceConditionGroupCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BA7A0
			void RegisterSupportingSurfaceConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingSurfaceConditionGroupCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSupportingLimbTestSurfaceDistanceConditionProperties;  // 0x11254B2C

			// FUNCTION: ENGINE 0x101B7320
			bool SupportingLimbTestSurfaceDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7330
			bool SupportingLimbTestSurfaceDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B79F0
			fight::Property* SupportingLimbTestSurfaceDistanceCondition::GetProperty(int index)
			{
				return gSupportingLimbTestSurfaceDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101B7A10
			void SupportingLimbTestSurfaceDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSupportingLimbTestSurfaceDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x101B7A20
			SupportingLimbTestSurfaceDistanceCondition::SupportingLimbTestSurfaceDistanceCondition() : fight::Condition(0), distance(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101B7A50
			SupportingLimbTestSurfaceDistanceCondition::~SupportingLimbTestSurfaceDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x101BA120
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SupportingLimbTestSurfaceDistanceCondition::RegisterProperties()
			{
				if (gSupportingLimbTestSurfaceDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<SupportingLimbTestSurfaceDistanceCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &SupportingLimbTestSurfaceDistanceCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SupportingLimbTestSurfaceDistanceCondition>("distance", &SupportingLimbTestSurfaceDistanceCondition::SetDistance);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gSupportingLimbTestSurfaceDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B97B0
			fight::ConditionFactory* CreateSupportingLimbTestSurfaceDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbTestSurfaceDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BA7D0
			void RegisterSupportingLimbTestSurfaceDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbTestSurfaceDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSupportingLimbTestSwitchSurfacesConditionProperties;  // 0x11254B30

			// FUNCTION: ENGINE 0x101B7350
			bool SupportingLimbTestSwitchSurfacesCondition::SetSwitchSurfaces(bool newValue)
			{
				switchSurfaces = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7A60
			fight::Property* SupportingLimbTestSwitchSurfacesCondition::GetProperty(int index)
			{
				return gSupportingLimbTestSwitchSurfacesConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101B7A80
			void SupportingLimbTestSwitchSurfacesCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSupportingLimbTestSwitchSurfacesConditionProperties);
			}

			// FUNCTION: ENGINE 0x101B7A90
			SupportingLimbTestSwitchSurfacesCondition::SupportingLimbTestSwitchSurfacesCondition() : fight::Condition(0), switchSurfaces(true)
			{
			}

			// FUNCTION: ENGINE 0x101B7AB0
			SupportingLimbTestSwitchSurfacesCondition::~SupportingLimbTestSwitchSurfacesCondition()
			{
			}

			// FUNCTION: ENGINE 0x101BA210
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SupportingLimbTestSwitchSurfacesCondition::RegisterProperties()
			{
				if (gSupportingLimbTestSwitchSurfacesConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<SupportingLimbTestSwitchSurfacesCondition>("switchSurfaces", &SupportingLimbTestSwitchSurfacesCondition::SetSwitchSurfaces);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gSupportingLimbTestSwitchSurfacesConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B97E0
			fight::ConditionFactory* CreateSupportingLimbTestSwitchSurfacesConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbTestSwitchSurfacesCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BA800
			void RegisterSupportingLimbTestSwitchSurfacesConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbTestSwitchSurfacesCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSupportingLimbTestSurfaceConditionGroupConditionProperties;  // 0x11254B34

			// FUNCTION: ENGINE 0x101B7360
			fight::ConditionList* SupportingLimbTestSurfaceConditionGroupCondition::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x101B7AC0
			fight::Property* SupportingLimbTestSurfaceConditionGroupCondition::GetProperty(int index)
			{
				return gSupportingLimbTestSurfaceConditionGroupConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101B7AE0
			void SupportingLimbTestSurfaceConditionGroupCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSupportingLimbTestSurfaceConditionGroupConditionProperties);
			}

			// FUNCTION: ENGINE 0x101B7AF0
			SupportingLimbTestSurfaceConditionGroupCondition::SupportingLimbTestSurfaceConditionGroupCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x101B7B20
			SupportingLimbTestSurfaceConditionGroupCondition::~SupportingLimbTestSurfaceConditionGroupCondition()
			{
			}

			// FUNCTION: ENGINE 0x101BA2B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SupportingLimbTestSurfaceConditionGroupCondition::RegisterProperties()
			{
				if (gSupportingLimbTestSurfaceConditionGroupConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyConditionGroup<SupportingLimbTestSurfaceConditionGroupCondition>("conditions", &SupportingLimbTestSurfaceConditionGroupCondition::SetConditions);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gSupportingLimbTestSurfaceConditionGroupConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B9810
			fight::ConditionFactory* CreateSupportingLimbTestSurfaceConditionGroupConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbTestSurfaceConditionGroupCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BA830
			void RegisterSupportingLimbTestSurfaceConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SupportingLimbTestSurfaceConditionGroupCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSupportingLimbSetActiveTrackProperties;  // 0x11254B38

			// FUNCTION: ENGINE 0x101B7370
			bool SupportingLimbSetActiveTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7D50
			bool SupportingLimbSetActiveTrack::SetSupportingLimb(const fight::Name& newValue)
			{
				supportingLimb = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7B40
			fight::Property* SupportingLimbSetActiveTrack::GetProperty(int index)
			{
				return gSupportingLimbSetActiveTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101B7B60
			void SupportingLimbSetActiveTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSupportingLimbSetActiveTrackProperties);
			}

			// FUNCTION: ENGINE 0x101B7FB0
			SupportingLimbSetActiveTrack::SupportingLimbSetActiveTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101B7FF0
			float SupportingLimbSetActiveTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101B8000
			float SupportingLimbSetActiveTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101B8010
			SupportingLimbSetActiveTrack::~SupportingLimbSetActiveTrack()
			{
			}

			// FUNCTION: ENGINE 0x101BAE30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SupportingLimbSetActiveTrack::RegisterProperties()
			{
				if (gSupportingLimbSetActiveTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SupportingLimbSetActiveTrack>("timeBegin", &SupportingLimbSetActiveTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<SupportingLimbSetActiveTrack>("supportingLimb", &SupportingLimbSetActiveTrack::SetSupportingLimb);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gSupportingLimbSetActiveTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B9840
			fight::TrackFactory* CreateSupportingLimbSetActiveTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SupportingLimbSetActiveTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BA860
			void RegisterSupportingLimbSetActiveTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SupportingLimbSetActiveTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSupportingLimbTestTrackProperties;  // 0x11254B3C

			// FUNCTION: ENGINE 0x101B7390
			bool SupportingLimbTestTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B73B0
			bool SupportingLimbTestTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7D70
			bool SupportingLimbTestTrack::SetSupportingLimb(const fight::Name& newValue)
			{
				supportingLimb = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B73D0
			bool SupportingLimbTestTrack::SetDirection(const math::Vector& newValue)
			{
				direction.x = newValue.x;
				direction.y = newValue.y;
				direction.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101B73F0
			bool SupportingLimbTestTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7410
			bool SupportingLimbTestTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7430
			bool SupportingLimbTestTrack::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7450
			bool SupportingLimbTestTrack::SetExtraDistance(float newValue)
			{
				extraDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7470
			bool SupportingLimbTestTrack::SetUseInput(bool newValue)
			{
				useInput = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7480
			bool SupportingLimbTestTrack::SetMaxInputArc(float newValue)
			{
				maxInputArc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101B74A0
			bool SupportingLimbTestTrack::SetUsePreviousSurface(bool newValue)
			{
				usePreviousSurface = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B74B0
			bool SupportingLimbTestTrack::SetUseMotion(bool newValue)
			{
				useMotion = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B74C0
			bool SupportingLimbTestTrack::SetSwitchSurfaces(bool newValue)
			{
				switchSurfaces = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B74D0
			fight::BranchHolder* SupportingLimbTestTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x101B74E0
			bool SupportingLimbTestTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B74F0
			fight::ConditionList* SupportingLimbTestTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x101B7B70
			fight::Property* SupportingLimbTestTrack::GetProperty(int index)
			{
				return gSupportingLimbTestTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101B7B90
			void SupportingLimbTestTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSupportingLimbTestTrackProperties);
			}

			// FUNCTION: ENGINE 0x101B8020
			SupportingLimbTestTrack::SupportingLimbTestTrack() : branch(0), direction(0.0f, 0.0f, -1.0f), offset(0.0f, 0.0f, 0.0f), arc(1.5707964f), extraDistance(0.0f), maxInputArc(3.1415927f), radius(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(0), switchSurfaces(false), useInput(true), useMotion(false), usePreviousSurface(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101B8100
			float SupportingLimbTestTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101B8110
			float SupportingLimbTestTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101B8120
			SupportingLimbTestTrack::~SupportingLimbTestTrack()
			{
			}

			// FUNCTION: ENGINE 0x101BAF10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SupportingLimbTestTrack::RegisterProperties()
			{
				if (gSupportingLimbTestTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SupportingLimbTestTrack>("timeBegin", &SupportingLimbTestTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SupportingLimbTestTrack>("timeEnd", &SupportingLimbTestTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<SupportingLimbTestTrack>("supportingLimb", &SupportingLimbTestTrack::SetSupportingLimb);
					properties[2] = property;
					property = new fight::PropertyVector<SupportingLimbTestTrack>("direction", &SupportingLimbTestTrack::SetDirection);
					properties[3] = property;
					property = new fight::PropertyVector<SupportingLimbTestTrack>("offset", &SupportingLimbTestTrack::SetOffset);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<SupportingLimbTestTrack>("radius", &SupportingLimbTestTrack::SetRadius);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<SupportingLimbTestTrack>("arc", &SupportingLimbTestTrack::SetArc);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<SupportingLimbTestTrack>("extraDistance", &SupportingLimbTestTrack::SetExtraDistance);
					properties[7] = property;
					property = new fight::PropertyBool<SupportingLimbTestTrack>("useInput", &SupportingLimbTestTrack::SetUseInput);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<SupportingLimbTestTrack>("maxInputArc", &SupportingLimbTestTrack::SetMaxInputArc);
					properties[9] = property;
					property = new fight::PropertyBool<SupportingLimbTestTrack>("usePreviousSurface", &SupportingLimbTestTrack::SetUsePreviousSurface);
					properties[10] = property;
					property = new fight::PropertyBool<SupportingLimbTestTrack>("useMotion", &SupportingLimbTestTrack::SetUseMotion);
					properties[11] = property;
					property = new fight::PropertyBool<SupportingLimbTestTrack>("switchSurfaces", &SupportingLimbTestTrack::SetSwitchSurfaces);
					properties[12] = property;
					property = new fight::PropertyBranch<SupportingLimbTestTrack>("branch", &SupportingLimbTestTrack::SetBranch);
					properties[13] = property;
					property = new fight::PropertyIntConstRange<SupportingLimbTestTrack>("priority", &SupportingLimbTestTrack::SetPriority);
					properties[14] = property;
					property = new fight::PropertyConditionGroup<SupportingLimbTestTrack>("conditions", &SupportingLimbTestTrack::SetConditions);
					properties[15] = property;
					fight::RegisterPropertyList(properties, &gSupportingLimbTestTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B9870
			fight::TrackFactory* CreateSupportingLimbTestTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SupportingLimbTestTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BA890
			void RegisterSupportingLimbTestTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SupportingLimbTestTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSupportingLimbSetActiveRangeTrackProperties;  // 0x11254B40

			// FUNCTION: ENGINE 0x101B7500
			bool SupportingLimbSetActiveRangeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7520
			bool SupportingLimbSetActiveRangeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7D90
			bool SupportingLimbSetActiveRangeTrack::SetOnBegin(const fight::Name& newValue)
			{
				onBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7DB0
			bool SupportingLimbSetActiveRangeTrack::SetOnEnd(const fight::Name& newValue)
			{
				onEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7BA0
			fight::Property* SupportingLimbSetActiveRangeTrack::GetProperty(int index)
			{
				return gSupportingLimbSetActiveRangeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101B7BC0
			void SupportingLimbSetActiveRangeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSupportingLimbSetActiveRangeTrackProperties);
			}

			// FUNCTION: ENGINE 0x101B8150
			SupportingLimbSetActiveRangeTrack::SupportingLimbSetActiveRangeTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101B81A0
			float SupportingLimbSetActiveRangeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101B81B0
			float SupportingLimbSetActiveRangeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101B81C0
			SupportingLimbSetActiveRangeTrack::~SupportingLimbSetActiveRangeTrack()
			{
			}

			// FUNCTION: ENGINE 0x101BB340
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SupportingLimbSetActiveRangeTrack::RegisterProperties()
			{
				if (gSupportingLimbSetActiveRangeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SupportingLimbSetActiveRangeTrack>("timeBegin", &SupportingLimbSetActiveRangeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SupportingLimbSetActiveRangeTrack>("timeEnd", &SupportingLimbSetActiveRangeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<SupportingLimbSetActiveRangeTrack>("onBegin", &SupportingLimbSetActiveRangeTrack::SetOnBegin);
					properties[2] = property;
					property = new fight::PropertyNameList<SupportingLimbSetActiveRangeTrack>("onEnd", &SupportingLimbSetActiveRangeTrack::SetOnEnd);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gSupportingLimbSetActiveRangeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B98A0
			fight::TrackFactory* CreateSupportingLimbSetActiveRangeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SupportingLimbSetActiveRangeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BA8C0
			void RegisterSupportingLimbSetActiveRangeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SupportingLimbSetActiveRangeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSurfaceMoveAtVelocityTrackProperties;  // 0x11254B44

			// FUNCTION: ENGINE 0x101B7540
			bool SurfaceMoveAtVelocityTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7560
			bool SurfaceMoveAtVelocityTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7580
			bool SurfaceMoveAtVelocityTrack::SetVelocity(const math::Vector& newValue)
			{
				velocity.x = newValue.x;
				velocity.y = newValue.y;
				velocity.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101B75A0
			bool SurfaceMoveAtVelocityTrack::SetOrientation(float newValue)
			{
				orientation = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101B75C0
			bool SurfaceMoveAtVelocityTrack::SetPreserveMomentum(bool newValue)
			{
				preserveMomentum = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B75D0
			bool SurfaceMoveAtVelocityTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B75E0
			bool SurfaceMoveAtVelocityTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7600
			bool SurfaceMoveAtVelocityTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7BD0
			fight::Property* SurfaceMoveAtVelocityTrack::GetProperty(int index)
			{
				return gSurfaceMoveAtVelocityTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101B7BF0
			void SurfaceMoveAtVelocityTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSurfaceMoveAtVelocityTrackProperties);
			}

			// FUNCTION: ENGINE 0x101B7C00
			SurfaceMoveAtVelocityTrack::SurfaceMoveAtVelocityTrack() : velocity(0.0f, 0.0f, 0.0f), blendInTime(0.0f), blendOutTime(0.0f), orientation(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(-5), preserveMomentum(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101B7C70
			float SurfaceMoveAtVelocityTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101B7C80
			float SurfaceMoveAtVelocityTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101B7C90
			SurfaceMoveAtVelocityTrack::~SurfaceMoveAtVelocityTrack()
			{
			}

			// FUNCTION: ENGINE 0x101BA350
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SurfaceMoveAtVelocityTrack::RegisterProperties()
			{
				if (gSurfaceMoveAtVelocityTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SurfaceMoveAtVelocityTrack>("timeBegin", &SurfaceMoveAtVelocityTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SurfaceMoveAtVelocityTrack>("timeEnd", &SurfaceMoveAtVelocityTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyVector<SurfaceMoveAtVelocityTrack>("velocity", &SurfaceMoveAtVelocityTrack::SetVelocity);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<SurfaceMoveAtVelocityTrack>("orientation", &SurfaceMoveAtVelocityTrack::SetOrientation);
					properties[3] = property;
					property = new fight::PropertyBool<SurfaceMoveAtVelocityTrack>("preserveMomentum", &SurfaceMoveAtVelocityTrack::SetPreserveMomentum);
					properties[4] = property;
					property = new fight::PropertyIntConstRange<SurfaceMoveAtVelocityTrack>("priority", &SurfaceMoveAtVelocityTrack::SetPriority);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<SurfaceMoveAtVelocityTrack>("blendInTime", &SurfaceMoveAtVelocityTrack::SetBlendInTime);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<SurfaceMoveAtVelocityTrack>("blendOutTime", &SurfaceMoveAtVelocityTrack::SetBlendOutTime);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gSurfaceMoveAtVelocityTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B98D0
			fight::TrackFactory* CreateSurfaceMoveAtVelocityTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SurfaceMoveAtVelocityTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BA8F0
			void RegisterSurfaceMoveAtVelocityTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SurfaceMoveAtVelocityTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSupportingLimbSetDirectionTrackProperties;  // 0x11254B48

			// FUNCTION: ENGINE 0x101B7620
			bool SupportingLimbSetDirectionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7640
			bool SupportingLimbSetDirectionTrack::SetDirection(const math::Vector& newValue)
			{
				direction.x = newValue.x;
				direction.y = newValue.y;
				direction.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101B7CA0
			fight::Property* SupportingLimbSetDirectionTrack::GetProperty(int index)
			{
				return gSupportingLimbSetDirectionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101B7CC0
			void SupportingLimbSetDirectionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSupportingLimbSetDirectionTrackProperties);
			}

			// FUNCTION: ENGINE 0x101B7CD0
			SupportingLimbSetDirectionTrack::SupportingLimbSetDirectionTrack() : direction(0.0f, -1.0f, 0.0f), timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101B7D20
			float SupportingLimbSetDirectionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101B7D30
			float SupportingLimbSetDirectionTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101B7D40
			SupportingLimbSetDirectionTrack::~SupportingLimbSetDirectionTrack()
			{
			}

			// FUNCTION: ENGINE 0x101BA5A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SupportingLimbSetDirectionTrack::RegisterProperties()
			{
				if (gSupportingLimbSetDirectionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SupportingLimbSetDirectionTrack>("timeBegin", &SupportingLimbSetDirectionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyVector<SupportingLimbSetDirectionTrack>("direction", &SupportingLimbSetDirectionTrack::SetDirection);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gSupportingLimbSetDirectionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B9900
			fight::TrackFactory* CreateSupportingLimbSetDirectionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SupportingLimbSetDirectionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BA920
			void RegisterSupportingLimbSetDirectionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SupportingLimbSetDirectionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<SupportingLimbTestSurfaceNormalVelocityArcCondition>;
			template class fight::PropertyFloatConstRange<SupportingLimbTestSurfaceNormalVelocityArcCondition>;
			template class fight::ConditionFactoryTemplate<SupportingLimbTestSurfaceNormalVelocityArcCondition>;
			template class fight::ConditionFactoryCasterTemplate<SupportingLimbTestSurfaceNormalVelocityArcCondition>;
			template class fight::PropertyVector<SupportingLimbTestSurfaceNormalAngleCondition>;
			template class fight::PropertyEnumConstList<SupportingLimbTestSurfaceNormalAngleCondition>;
			template class fight::PropertyFloatConstRange<SupportingLimbTestSurfaceNormalAngleCondition>;
			template class fight::ConditionFactoryTemplate<SupportingLimbTestSurfaceNormalAngleCondition>;
			template class fight::ConditionFactoryCasterTemplate<SupportingLimbTestSurfaceNormalAngleCondition>;
			template class fight::PropertyBitfieldConstList<SupportingLimbSurfaceIntersectionPropertiesCondition>;
			template class fight::PropertyEnumConstList<SupportingLimbSurfaceIntersectionPropertiesCondition>;
			template class fight::ConditionFactoryTemplate<SupportingLimbSurfaceIntersectionPropertiesCondition>;
			template class fight::ConditionFactoryCasterTemplate<SupportingLimbSurfaceIntersectionPropertiesCondition>;
			template class fight::PropertyEnumConstList<SupportingLimbTestSurfaceVelocityAngleCondition>;
			template class fight::PropertyVector<SupportingLimbTestSurfaceVelocityAngleCondition>;
			template class fight::PropertyFloatConstRange<SupportingLimbTestSurfaceVelocityAngleCondition>;
			template class fight::PropertyBool<SupportingLimbTestSurfaceVelocityAngleCondition>;
			template class fight::ConditionFactoryTemplate<SupportingLimbTestSurfaceVelocityAngleCondition>;
			template class fight::ConditionFactoryCasterTemplate<SupportingLimbTestSurfaceVelocityAngleCondition>;
			template class fight::PropertyEnumConstList<SupportingLimbTestTimeToImpactCondition>;
			template class fight::PropertyFloatConstRange<SupportingLimbTestTimeToImpactCondition>;
			template class fight::ConditionFactoryTemplate<SupportingLimbTestTimeToImpactCondition>;
			template class fight::ConditionFactoryCasterTemplate<SupportingLimbTestTimeToImpactCondition>;
			template class fight::PropertyEnumConstList<SupportingSurfaceNormalVelocityArcCondition>;
			template class fight::PropertyFloatConstRange<SupportingSurfaceNormalVelocityArcCondition>;
			template class fight::ConditionFactoryTemplate<SupportingSurfaceNormalVelocityArcCondition>;
			template class fight::ConditionFactoryCasterTemplate<SupportingSurfaceNormalVelocityArcCondition>;
			template class fight::PropertyConditionGroup<SupportingSurfaceConditionGroupCondition>;
			template class fight::ConditionFactoryTemplate<SupportingSurfaceConditionGroupCondition>;
			template class fight::ConditionFactoryCasterTemplate<SupportingSurfaceConditionGroupCondition>;
			template class fight::PropertyEnumConstList<SupportingLimbTestSurfaceDistanceCondition>;
			template class fight::PropertyFloatConstRange<SupportingLimbTestSurfaceDistanceCondition>;
			template class fight::ConditionFactoryTemplate<SupportingLimbTestSurfaceDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<SupportingLimbTestSurfaceDistanceCondition>;
			template class fight::PropertyBool<SupportingLimbTestSwitchSurfacesCondition>;
			template class fight::ConditionFactoryTemplate<SupportingLimbTestSwitchSurfacesCondition>;
			template class fight::ConditionFactoryCasterTemplate<SupportingLimbTestSwitchSurfacesCondition>;
			template class fight::PropertyConditionGroup<SupportingLimbTestSurfaceConditionGroupCondition>;
			template class fight::ConditionFactoryTemplate<SupportingLimbTestSurfaceConditionGroupCondition>;
			template class fight::ConditionFactoryCasterTemplate<SupportingLimbTestSurfaceConditionGroupCondition>;
			template class fight::PropertyFloatConstRange<SupportingLimbSetActiveTrack>;
			template class fight::PropertyNameList<SupportingLimbSetActiveTrack>;
			template class fight::TrackFactoryTemplate<SupportingLimbSetActiveTrack>;
			template class fight::TrackFactoryCasterTemplate<SupportingLimbSetActiveTrack>;
			template class fight::PropertyFloatConstRange<SupportingLimbTestTrack>;
			template class fight::PropertyNameList<SupportingLimbTestTrack>;
			template class fight::PropertyVector<SupportingLimbTestTrack>;
			template class fight::PropertyBool<SupportingLimbTestTrack>;
			template class fight::PropertyBranch<SupportingLimbTestTrack>;
			template class fight::PropertyIntConstRange<SupportingLimbTestTrack>;
			template class fight::PropertyConditionGroup<SupportingLimbTestTrack>;
			template class fight::TrackFactoryTemplate<SupportingLimbTestTrack>;
			template class fight::TrackFactoryCasterTemplate<SupportingLimbTestTrack>;
			template class fight::PropertyFloatConstRange<SupportingLimbSetActiveRangeTrack>;
			template class fight::PropertyNameList<SupportingLimbSetActiveRangeTrack>;
			template class fight::TrackFactoryTemplate<SupportingLimbSetActiveRangeTrack>;
			template class fight::TrackFactoryCasterTemplate<SupportingLimbSetActiveRangeTrack>;
			template class fight::PropertyFloatConstRange<SurfaceMoveAtVelocityTrack>;
			template class fight::PropertyVector<SurfaceMoveAtVelocityTrack>;
			template class fight::PropertyBool<SurfaceMoveAtVelocityTrack>;
			template class fight::PropertyIntConstRange<SurfaceMoveAtVelocityTrack>;
			template class fight::TrackFactoryTemplate<SurfaceMoveAtVelocityTrack>;
			template class fight::TrackFactoryCasterTemplate<SurfaceMoveAtVelocityTrack>;
			template class fight::PropertyFloatConstRange<SupportingLimbSetDirectionTrack>;
			template class fight::PropertyVector<SupportingLimbSetDirectionTrack>;
			template class fight::TrackFactoryTemplate<SupportingLimbSetDirectionTrack>;
			template class fight::TrackFactoryCasterTemplate<SupportingLimbSetDirectionTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101B7DD0
// FUNCTION: ENGINE 0x101B7E00
// FUNCTION: ENGINE 0x101B7E30
// FUNCTION: ENGINE 0x101B7E60
// FUNCTION: ENGINE 0x101B7E90
// FUNCTION: ENGINE 0x101B7EC0
// FUNCTION: ENGINE 0x101B7EF0
// FUNCTION: ENGINE 0x101B7F20
// FUNCTION: ENGINE 0x101B7F50
// FUNCTION: ENGINE 0x101B7F80
// FUNCTION: ENGINE 0x101B81D0
// FUNCTION: ENGINE 0x101B8200
// FUNCTION: ENGINE 0x101B8230
// FUNCTION: ENGINE 0x101B8240
// FUNCTION: ENGINE 0x101B8270
// FUNCTION: ENGINE 0x101B8280
// FUNCTION: ENGINE 0x101B82B0
// FUNCTION: ENGINE 0x101B82C0
// FUNCTION: ENGINE 0x101B82F0
// FUNCTION: ENGINE 0x101B8300
// FUNCTION: ENGINE 0x101B8330
// FUNCTION: ENGINE 0x101B8340
// FUNCTION: ENGINE 0x101B8370
// FUNCTION: ENGINE 0x101B8380
// FUNCTION: ENGINE 0x101B83B0
// FUNCTION: ENGINE 0x101B83C0
// FUNCTION: ENGINE 0x101B83F0
// FUNCTION: ENGINE 0x101B8400
// FUNCTION: ENGINE 0x101B8430
// FUNCTION: ENGINE 0x101B8440
// FUNCTION: ENGINE 0x101B8470
// FUNCTION: ENGINE 0x101B8480
// FUNCTION: ENGINE 0x101B84B0
// FUNCTION: ENGINE 0x101B84C0
// FUNCTION: ENGINE 0x101B84F0
// FUNCTION: ENGINE 0x101B8500
// FUNCTION: ENGINE 0x101B8530
// FUNCTION: ENGINE 0x101B8540
// FUNCTION: ENGINE 0x101B8570
// FUNCTION: ENGINE 0x101B8580
// FUNCTION: ENGINE 0x101B85B0
// FUNCTION: ENGINE 0x101B85C0
// FUNCTION: ENGINE 0x101B85F0
// FUNCTION: ENGINE 0x101B8620
// FUNCTION: ENGINE 0x101B8650
// FUNCTION: ENGINE 0x101B8680
// FUNCTION: ENGINE 0x101B86C0
// FUNCTION: ENGINE 0x101B86D0
// FUNCTION: ENGINE 0x101B8700
// FUNCTION: ENGINE 0x101B8720
// FUNCTION: ENGINE 0x101B8730
// FUNCTION: ENGINE 0x101B8760
// FUNCTION: ENGINE 0x101B8790
// FUNCTION: ENGINE 0x101B87A0
// FUNCTION: ENGINE 0x101B87D0
// FUNCTION: ENGINE 0x101B87F0
// FUNCTION: ENGINE 0x101B8800
// FUNCTION: ENGINE 0x101B8840
// FUNCTION: ENGINE 0x101B8850
// FUNCTION: ENGINE 0x101B8880
// FUNCTION: ENGINE 0x101B88A0
// FUNCTION: ENGINE 0x101B88B0
// FUNCTION: ENGINE 0x101B88E0
// FUNCTION: ENGINE 0x101B8910
// FUNCTION: ENGINE 0x101B8920
// FUNCTION: ENGINE 0x101B8960
// FUNCTION: ENGINE 0x101B8970
// FUNCTION: ENGINE 0x101B8990
// FUNCTION: ENGINE 0x101B89A0
// FUNCTION: ENGINE 0x101B8A00
// FUNCTION: ENGINE 0x101B8A40
// FUNCTION: ENGINE 0x101B8A50
// FUNCTION: ENGINE 0x101B8A80
// FUNCTION: ENGINE 0x101B8AA0
// FUNCTION: ENGINE 0x101B8AB0
// FUNCTION: ENGINE 0x101B8AF0
// FUNCTION: ENGINE 0x101B8B00
// FUNCTION: ENGINE 0x101B8B30
// FUNCTION: ENGINE 0x101B8B50
// FUNCTION: ENGINE 0x101B8B60
// FUNCTION: ENGINE 0x101B8B90
// FUNCTION: ENGINE 0x101B8BB0
// FUNCTION: ENGINE 0x101B8BC0
// FUNCTION: ENGINE 0x101B8BF0
// FUNCTION: ENGINE 0x101B8C20
// FUNCTION: ENGINE 0x101B8C30
// FUNCTION: ENGINE 0x101B8C60
// FUNCTION: ENGINE 0x101B8C80
// FUNCTION: ENGINE 0x101B8C90
// FUNCTION: ENGINE 0x101B8CD0
// FUNCTION: ENGINE 0x101B8CE0
// FUNCTION: ENGINE 0x101B8D10
// FUNCTION: ENGINE 0x101B8D30
// FUNCTION: ENGINE 0x101B8D40
// FUNCTION: ENGINE 0x101B8D70
// FUNCTION: ENGINE 0x101B8DA0
// FUNCTION: ENGINE 0x101B8DB0
// FUNCTION: ENGINE 0x101B8DF0
// FUNCTION: ENGINE 0x101B8E00
// FUNCTION: ENGINE 0x101B8E30
// FUNCTION: ENGINE 0x101B8E50
// FUNCTION: ENGINE 0x101B8E60
// FUNCTION: ENGINE 0x101B8E90
// FUNCTION: ENGINE 0x101B8EC0
// FUNCTION: ENGINE 0x101B8ED0
// FUNCTION: ENGINE 0x101B8F00
// FUNCTION: ENGINE 0x101B8F20
// FUNCTION: ENGINE 0x101B8F60
// FUNCTION: ENGINE 0x101B8F70
// FUNCTION: ENGINE 0x101B8FA0
// FUNCTION: ENGINE 0x101B8FC0
// FUNCTION: ENGINE 0x101B8FD0
// FUNCTION: ENGINE 0x101B9000
// FUNCTION: ENGINE 0x101B9030
// FUNCTION: ENGINE 0x101B9040
// FUNCTION: ENGINE 0x101B9070
// FUNCTION: ENGINE 0x101B9090
// FUNCTION: ENGINE 0x101B90A0
// FUNCTION: ENGINE 0x101B90D0
// FUNCTION: ENGINE 0x101B90F0
// FUNCTION: ENGINE 0x101B9120
// FUNCTION: ENGINE 0x101B9150
// FUNCTION: ENGINE 0x101B9160
// FUNCTION: ENGINE 0x101B9190
// FUNCTION: ENGINE 0x101B91C0
// FUNCTION: ENGINE 0x101B91D0
// FUNCTION: ENGINE 0x101B9200
// FUNCTION: ENGINE 0x101B9220
// FUNCTION: ENGINE 0x101B9230
// FUNCTION: ENGINE 0x101B9260
// FUNCTION: ENGINE 0x101B9280
// FUNCTION: ENGINE 0x101B9290
// FUNCTION: ENGINE 0x101B92C0
// FUNCTION: ENGINE 0x101B92E0
// FUNCTION: ENGINE 0x101B9310
// FUNCTION: ENGINE 0x101B9330
// FUNCTION: ENGINE 0x101B9340
// FUNCTION: ENGINE 0x101B9370
// FUNCTION: ENGINE 0x101B9390
// FUNCTION: ENGINE 0x101B93C0
// FUNCTION: ENGINE 0x101B93F0
// FUNCTION: ENGINE 0x101B9400
// FUNCTION: ENGINE 0x101B9430
// FUNCTION: ENGINE 0x101B9460
// FUNCTION: ENGINE 0x101B9470
// FUNCTION: ENGINE 0x101B94A0
// FUNCTION: ENGINE 0x101B94C0
// FUNCTION: ENGINE 0x101B94D0
// FUNCTION: ENGINE 0x101B9500
// FUNCTION: ENGINE 0x101B9520
// FUNCTION: ENGINE 0x101B9530
// FUNCTION: ENGINE 0x101B9560
// FUNCTION: ENGINE 0x101B9580
// FUNCTION: ENGINE 0x101B9590
// FUNCTION: ENGINE 0x101B95C0
// FUNCTION: ENGINE 0x101B95F0
// FUNCTION: ENGINE 0x101B9600
// FUNCTION: ENGINE 0x101B9630
// FUNCTION: ENGINE 0x101B9650
// FUNCTION: ENGINE 0x101BA950
// FUNCTION: ENGINE 0x101BA980
// FUNCTION: ENGINE 0x101BA9A0
// FUNCTION: ENGINE 0x101BA9B0
// FUNCTION: ENGINE 0x101BA9E0
// FUNCTION: ENGINE 0x101BAA00
// FUNCTION: ENGINE 0x101BAA10
// FUNCTION: ENGINE 0x101BAA40
// FUNCTION: ENGINE 0x101BAA60
// FUNCTION: ENGINE 0x101BAA70
// FUNCTION: ENGINE 0x101BAAA0
// FUNCTION: ENGINE 0x101BAAC0
// FUNCTION: ENGINE 0x101BAAF0
// FUNCTION: ENGINE 0x101BAB10
// FUNCTION: ENGINE 0x101BAB40
// FUNCTION: ENGINE 0x101BAB60
// FUNCTION: ENGINE 0x101BAB90
// FUNCTION: ENGINE 0x101BABB0
// FUNCTION: ENGINE 0x101BABE0
// FUNCTION: ENGINE 0x101BAC00
// FUNCTION: ENGINE 0x101BAC30
// FUNCTION: ENGINE 0x101BAC50
// FUNCTION: ENGINE 0x101BAC80
// FUNCTION: ENGINE 0x101BACA0
// FUNCTION: ENGINE 0x101BACD0
// FUNCTION: ENGINE 0x101BACF0
// FUNCTION: ENGINE 0x101BAD20
// FUNCTION: ENGINE 0x101BAD40
// FUNCTION: ENGINE 0x101BAD70
// FUNCTION: ENGINE 0x101BAD90
// FUNCTION: ENGINE 0x101BADC0
// FUNCTION: ENGINE 0x101BADE0
// FUNCTION: ENGINE 0x101BAE10
// FUNCTION: ENGINE 0x101BB490
// FUNCTION: ENGINE 0x101BB4E0
// FUNCTION: ENGINE 0x101BB530
// FUNCTION: ENGINE 0x101BB580
// FUNCTION: ENGINE 0x101BB5D0
// FUNCTION: ENGINE 0x101BB620
// FUNCTION: ENGINE 0x101BB670
// FUNCTION: ENGINE 0x101BB6C0
// FUNCTION: ENGINE 0x101BB710
// FUNCTION: ENGINE 0x101BB760
// FUNCTION: ENGINE 0x101BB7B0
// FUNCTION: ENGINE 0x101BB800
// FUNCTION: ENGINE 0x101BB850
// FUNCTION: ENGINE 0x101BB880
// FUNCTION: ENGINE 0x101BB8A0
// FUNCTION: ENGINE 0x101BB8D0
// FUNCTION: ENGINE 0x101BB900
// FUNCTION: ENGINE 0x101BB930
// FUNCTION: ENGINE 0x101BB950
// FUNCTION: ENGINE 0x101BB9A0
// FUNCTION: ENGINE 0x101BB9F0
