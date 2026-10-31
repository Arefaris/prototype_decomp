// Fight items of the motion group: TargetDistanceCondition, TargetCanJumpToCondition, TargetDistanceWithOffsetCondition, AutoTargetDistanceCondition (unit 0x101BBFD0 - 0x101BD3C0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_targetdistance.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gTargetDistanceConditionProperties;  // 0x11254B84

			// FUNCTION: ENGINE 0x101BBFD0
			bool TargetDistanceCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BBFE0
			bool TargetDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BBFF0
			bool TargetDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BC160
			fight::Property* TargetDistanceCondition::GetProperty(int index)
			{
				return gTargetDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101BC180
			void TargetDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x101BC190
			TargetDistanceCondition::TargetDistanceCondition() : fight::Condition(0), distance(2e+01f), compare(4), direction(0)
			{
			}

			// FUNCTION: ENGINE 0x101BC1D0
			TargetDistanceCondition::~TargetDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x101BCAB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetDistanceCondition::RegisterProperties()
			{
				if (gTargetDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<TargetDistanceCondition>("direction", gCrowdPositionConditionDirectionTable, gCrowdPositionConditionDirectionCount, &TargetDistanceCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<TargetDistanceCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &TargetDistanceCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TargetDistanceCondition>("distance", &TargetDistanceCondition::SetDistance);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gTargetDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101BC9F0
			fight::ConditionFactory* CreateTargetDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BD080
			void RegisterTargetDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetCanJumpToConditionProperties;  // 0x11254B88

			// FUNCTION: ENGINE 0x101BC010
			bool TargetCanJumpToCondition::SetLaunchAngle(float newValue)
			{
				launchAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BC030
			bool TargetCanJumpToCondition::SetMinLaunchAngle(float newValue)
			{
				minLaunchAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BC050
			bool TargetCanJumpToCondition::SetGravity(float newValue)
			{
				gravity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BC070
			bool TargetCanJumpToCondition::SetMaxInitialVelocity(float newValue)
			{
				maxInitialVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BC090
			bool TargetCanJumpToCondition::SetUseStoredValues(bool newValue)
			{
				useStoredValues = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BC0A0
			bool TargetCanJumpToCondition::SetMargin(float newValue)
			{
				margin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BC1E0
			fight::Property* TargetCanJumpToCondition::GetProperty(int index)
			{
				return gTargetCanJumpToConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101BC200
			void TargetCanJumpToCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetCanJumpToConditionProperties);
			}

			// FUNCTION: ENGINE 0x101BC210
			TargetCanJumpToCondition::TargetCanJumpToCondition() : fight::Condition(0), gravity(9.8f), launchAngle(0.7853982f), margin(0.0f), maxInitialVelocity(5e+01f), minLaunchAngle(0.0f), useStoredValues(false)
			{
			}

			// FUNCTION: ENGINE 0x101BC270
			TargetCanJumpToCondition::~TargetCanJumpToCondition()
			{
			}

			// FUNCTION: ENGINE 0x101BCBF0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetCanJumpToCondition::RegisterProperties()
			{
				if (gTargetCanJumpToConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TargetCanJumpToCondition>("launchAngle", &TargetCanJumpToCondition::SetLaunchAngle);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TargetCanJumpToCondition>("minLaunchAngle", &TargetCanJumpToCondition::SetMinLaunchAngle);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TargetCanJumpToCondition>("gravity", &TargetCanJumpToCondition::SetGravity);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<TargetCanJumpToCondition>("maxInitialVelocity", &TargetCanJumpToCondition::SetMaxInitialVelocity);
					properties[3] = property;
					property = new fight::PropertyBool<TargetCanJumpToCondition>("useStoredValues", &TargetCanJumpToCondition::SetUseStoredValues);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<TargetCanJumpToCondition>("margin", &TargetCanJumpToCondition::SetMargin);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gTargetCanJumpToConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101BCA20
			fight::ConditionFactory* CreateTargetCanJumpToConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetCanJumpToCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BD0B0
			void RegisterTargetCanJumpToConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetCanJumpToCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetDistanceWithOffsetConditionProperties;  // 0x11254B8C

			// FUNCTION: ENGINE 0x101BC0C0
			bool TargetDistanceWithOffsetCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BC0D0
			bool TargetDistanceWithOffsetCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BC0E0
			bool TargetDistanceWithOffsetCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BC100
			bool TargetDistanceWithOffsetCondition::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101BC280
			fight::Property* TargetDistanceWithOffsetCondition::GetProperty(int index)
			{
				return gTargetDistanceWithOffsetConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101BC2A0
			void TargetDistanceWithOffsetCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetDistanceWithOffsetConditionProperties);
			}

			// FUNCTION: ENGINE 0x101BC2B0
			TargetDistanceWithOffsetCondition::TargetDistanceWithOffsetCondition() : fight::Condition(0), offset(0.0f, 0.0f, 0.0f), distance(2e+01f), compare(4), direction(0)
			{
			}

			// FUNCTION: ENGINE 0x101BC310
			TargetDistanceWithOffsetCondition::~TargetDistanceWithOffsetCondition()
			{
			}

			// FUNCTION: ENGINE 0x101BCDC0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetDistanceWithOffsetCondition::RegisterProperties()
			{
				if (gTargetDistanceWithOffsetConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<TargetDistanceWithOffsetCondition>("direction", gCrowdPositionConditionDirectionTable, gCrowdPositionConditionDirectionCount, &TargetDistanceWithOffsetCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<TargetDistanceWithOffsetCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &TargetDistanceWithOffsetCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TargetDistanceWithOffsetCondition>("distance", &TargetDistanceWithOffsetCondition::SetDistance);
					properties[2] = property;
					property = new fight::PropertyVector<TargetDistanceWithOffsetCondition>("offset", &TargetDistanceWithOffsetCondition::SetOffset);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gTargetDistanceWithOffsetConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101BCA50
			fight::ConditionFactory* CreateTargetDistanceWithOffsetConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetDistanceWithOffsetCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BD0E0
			void RegisterTargetDistanceWithOffsetConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetDistanceWithOffsetCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gAutoTargetDistanceConditionProperties;  // 0x11254B90

			// FUNCTION: ENGINE 0x101BC120
			bool AutoTargetDistanceCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BC130
			bool AutoTargetDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BC140
			bool AutoTargetDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BC320
			fight::Property* AutoTargetDistanceCondition::GetProperty(int index)
			{
				return gAutoTargetDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101BC340
			void AutoTargetDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAutoTargetDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x101BC350
			AutoTargetDistanceCondition::AutoTargetDistanceCondition() : fight::Condition(0), distance(2e+01f), compare(4), direction(0)
			{
			}

			// FUNCTION: ENGINE 0x101BC390
			AutoTargetDistanceCondition::~AutoTargetDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x101BCF40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AutoTargetDistanceCondition::RegisterProperties()
			{
				if (gAutoTargetDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<AutoTargetDistanceCondition>("direction", gCrowdPositionConditionDirectionTable, gCrowdPositionConditionDirectionCount, &AutoTargetDistanceCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<AutoTargetDistanceCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &AutoTargetDistanceCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<AutoTargetDistanceCondition>("distance", &AutoTargetDistanceCondition::SetDistance);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gAutoTargetDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101BCA80
			fight::ConditionFactory* CreateAutoTargetDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AutoTargetDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BD110
			void RegisterAutoTargetDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AutoTargetDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<TargetDistanceCondition>;
			template class fight::PropertyFloatConstRange<TargetDistanceCondition>;
			template class fight::ConditionFactoryTemplate<TargetDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetDistanceCondition>;
			template class fight::PropertyFloatConstRange<TargetCanJumpToCondition>;
			template class fight::PropertyBool<TargetCanJumpToCondition>;
			template class fight::ConditionFactoryTemplate<TargetCanJumpToCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetCanJumpToCondition>;
			template class fight::PropertyEnumConstList<TargetDistanceWithOffsetCondition>;
			template class fight::PropertyFloatConstRange<TargetDistanceWithOffsetCondition>;
			template class fight::PropertyVector<TargetDistanceWithOffsetCondition>;
			template class fight::ConditionFactoryTemplate<TargetDistanceWithOffsetCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetDistanceWithOffsetCondition>;
			template class fight::PropertyEnumConstList<AutoTargetDistanceCondition>;
			template class fight::PropertyFloatConstRange<AutoTargetDistanceCondition>;
			template class fight::ConditionFactoryTemplate<AutoTargetDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<AutoTargetDistanceCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101BC3A0
// FUNCTION: ENGINE 0x101BC3D0
// FUNCTION: ENGINE 0x101BC400
// FUNCTION: ENGINE 0x101BC430
// FUNCTION: ENGINE 0x101BC460
// FUNCTION: ENGINE 0x101BC470
// FUNCTION: ENGINE 0x101BC4A0
// FUNCTION: ENGINE 0x101BC4B0
// FUNCTION: ENGINE 0x101BC4E0
// FUNCTION: ENGINE 0x101BC4F0
// FUNCTION: ENGINE 0x101BC520
// FUNCTION: ENGINE 0x101BC530
// FUNCTION: ENGINE 0x101BC560
// FUNCTION: ENGINE 0x101BC5A0
// FUNCTION: ENGINE 0x101BC5B0
// FUNCTION: ENGINE 0x101BC5E0
// FUNCTION: ENGINE 0x101BC600
// FUNCTION: ENGINE 0x101BC610
// FUNCTION: ENGINE 0x101BC640
// FUNCTION: ENGINE 0x101BC670
// FUNCTION: ENGINE 0x101BC680
// FUNCTION: ENGINE 0x101BC6B0
// FUNCTION: ENGINE 0x101BC6E0
// FUNCTION: ENGINE 0x101BC6F0
// FUNCTION: ENGINE 0x101BC720
// FUNCTION: ENGINE 0x101BC740
// FUNCTION: ENGINE 0x101BC750
// FUNCTION: ENGINE 0x101BC790
// FUNCTION: ENGINE 0x101BC7A0
// FUNCTION: ENGINE 0x101BC7D0
// FUNCTION: ENGINE 0x101BC7F0
// FUNCTION: ENGINE 0x101BC800
// FUNCTION: ENGINE 0x101BC830
// FUNCTION: ENGINE 0x101BC860
// FUNCTION: ENGINE 0x101BC870
// FUNCTION: ENGINE 0x101BC8A0
// FUNCTION: ENGINE 0x101BC8C0
// FUNCTION: ENGINE 0x101BC8D0
// FUNCTION: ENGINE 0x101BC910
// FUNCTION: ENGINE 0x101BC920
// FUNCTION: ENGINE 0x101BC950
// FUNCTION: ENGINE 0x101BC970
// FUNCTION: ENGINE 0x101BC980
// FUNCTION: ENGINE 0x101BC9B0
// FUNCTION: ENGINE 0x101BC9E0
// FUNCTION: ENGINE 0x101BD140
// FUNCTION: ENGINE 0x101BD170
// FUNCTION: ENGINE 0x101BD190
// FUNCTION: ENGINE 0x101BD1C0
// FUNCTION: ENGINE 0x101BD1E0
// FUNCTION: ENGINE 0x101BD210
// FUNCTION: ENGINE 0x101BD230
// FUNCTION: ENGINE 0x101BD260
// FUNCTION: ENGINE 0x101BD280
// FUNCTION: ENGINE 0x101BD2D0
// FUNCTION: ENGINE 0x101BD320
// FUNCTION: ENGINE 0x101BD370
