// Fight items of the motion group: ObstacleDistanceCondition, ObstacleTimeToObstacleCondition, ObstacleSlopeCondition, ObstacleFaceHeightSlopeCondition, ObstacleFaceHeightCondition, ObstacleColliderTypeCondition, ObstacleVelocityCondition, ObstacleLengthCondition, ObstacleWidthCondition, ObstacleHeightCondition, ObstacleAvoidExitTrack, ObstacleAvoidTrack, PushFromObstacleTrack, ObstacleTestTrack (unit 0x10193D60 - 0x10198800; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_obstacle.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gObstacleDistanceConditionProperties;  // 0x11254840

			// FUNCTION: ENGINE 0x10193D60
			bool ObstacleDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193D70
			bool ObstacleDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194470
			fight::Property* ObstacleDistanceCondition::GetProperty(int index)
			{
				return gObstacleDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10194490
			void ObstacleDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gObstacleDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x101944A0
			ObstacleDistanceCondition::ObstacleDistanceCondition() : fight::Condition(0), distance(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101944D0
			ObstacleDistanceCondition::~ObstacleDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x10196640
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ObstacleDistanceCondition::RegisterProperties()
			{
				if (gObstacleDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ObstacleDistanceCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ObstacleDistanceCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ObstacleDistanceCondition>("distance", &ObstacleDistanceCondition::SetDistance);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gObstacleDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101963A0
			fight::ConditionFactory* CreateObstacleDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10197A20
			void RegisterObstacleDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gObstacleTimeToObstacleConditionProperties;  // 0x11254844

			// FUNCTION: ENGINE 0x10193D90
			bool ObstacleTimeToObstacleCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193DA0
			bool ObstacleTimeToObstacleCondition::SetTime(float newValue)
			{
				time = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101944E0
			fight::Property* ObstacleTimeToObstacleCondition::GetProperty(int index)
			{
				return gObstacleTimeToObstacleConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10194500
			void ObstacleTimeToObstacleCondition::ClearProperties()
			{
				fight::FreePropertyList(&gObstacleTimeToObstacleConditionProperties);
			}

			// FUNCTION: ENGINE 0x10194510
			ObstacleTimeToObstacleCondition::ObstacleTimeToObstacleCondition() : fight::Condition(0), time(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10194540
			ObstacleTimeToObstacleCondition::~ObstacleTimeToObstacleCondition()
			{
			}

			// FUNCTION: ENGINE 0x10196730
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ObstacleTimeToObstacleCondition::RegisterProperties()
			{
				if (gObstacleTimeToObstacleConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ObstacleTimeToObstacleCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ObstacleTimeToObstacleCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ObstacleTimeToObstacleCondition>("time", &ObstacleTimeToObstacleCondition::SetTime);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gObstacleTimeToObstacleConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101963D0
			fight::ConditionFactory* CreateObstacleTimeToObstacleConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleTimeToObstacleCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10197A50
			void RegisterObstacleTimeToObstacleConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleTimeToObstacleCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gObstacleSlopeConditionProperties;  // 0x11254848

			// FUNCTION: ENGINE 0x10193DC0
			bool ObstacleSlopeCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193DD0
			bool ObstacleSlopeCondition::SetSlope(float newValue)
			{
				slope = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10194550
			fight::Property* ObstacleSlopeCondition::GetProperty(int index)
			{
				return gObstacleSlopeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10194570
			void ObstacleSlopeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gObstacleSlopeConditionProperties);
			}

			// FUNCTION: ENGINE 0x10194580
			ObstacleSlopeCondition::ObstacleSlopeCondition() : fight::Condition(0), slope(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101945B0
			ObstacleSlopeCondition::~ObstacleSlopeCondition()
			{
			}

			// FUNCTION: ENGINE 0x10196820
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ObstacleSlopeCondition::RegisterProperties()
			{
				if (gObstacleSlopeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ObstacleSlopeCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ObstacleSlopeCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ObstacleSlopeCondition>("slope", &ObstacleSlopeCondition::SetSlope);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gObstacleSlopeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10196400
			fight::ConditionFactory* CreateObstacleSlopeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleSlopeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10197A80
			void RegisterObstacleSlopeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleSlopeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gObstacleFaceHeightSlopeConditionProperties;  // 0x1125484C

			// FUNCTION: ENGINE 0x10193DF0
			bool ObstacleFaceHeightSlopeCondition::SetFaceHeightMin(float newValue)
			{
				faceHeightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193E10
			bool ObstacleFaceHeightSlopeCondition::SetHeightMax(float newValue)
			{
				heightMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193E30
			bool ObstacleFaceHeightSlopeCondition::SetSlopeMax(float newValue)
			{
				slopeMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101945C0
			fight::Property* ObstacleFaceHeightSlopeCondition::GetProperty(int index)
			{
				return gObstacleFaceHeightSlopeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101945E0
			void ObstacleFaceHeightSlopeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gObstacleFaceHeightSlopeConditionProperties);
			}

			// FUNCTION: ENGINE 0x101945F0
			ObstacleFaceHeightSlopeCondition::ObstacleFaceHeightSlopeCondition() : fight::Condition(0), faceHeightMin(0.5f), heightMax(2.0f), slopeMax(1.0471976f)
			{
			}

			// FUNCTION: ENGINE 0x10194640
			ObstacleFaceHeightSlopeCondition::~ObstacleFaceHeightSlopeCondition()
			{
			}

			// FUNCTION: ENGINE 0x10196910
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ObstacleFaceHeightSlopeCondition::RegisterProperties()
			{
				if (gObstacleFaceHeightSlopeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ObstacleFaceHeightSlopeCondition>("faceHeightMin", &ObstacleFaceHeightSlopeCondition::SetFaceHeightMin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ObstacleFaceHeightSlopeCondition>("heightMax", &ObstacleFaceHeightSlopeCondition::SetHeightMax);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ObstacleFaceHeightSlopeCondition>("slopeMax", &ObstacleFaceHeightSlopeCondition::SetSlopeMax);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gObstacleFaceHeightSlopeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10196430
			fight::ConditionFactory* CreateObstacleFaceHeightSlopeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleFaceHeightSlopeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10197AB0
			void RegisterObstacleFaceHeightSlopeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleFaceHeightSlopeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gObstacleFaceHeightConditionProperties;  // 0x11254850

			// FUNCTION: ENGINE 0x10193E50
			bool ObstacleFaceHeightCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193E60
			bool ObstacleFaceHeightCondition::SetHeight(float newValue)
			{
				height = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194650
			fight::Property* ObstacleFaceHeightCondition::GetProperty(int index)
			{
				return gObstacleFaceHeightConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10194670
			void ObstacleFaceHeightCondition::ClearProperties()
			{
				fight::FreePropertyList(&gObstacleFaceHeightConditionProperties);
			}

			// FUNCTION: ENGINE 0x10194680
			ObstacleFaceHeightCondition::ObstacleFaceHeightCondition() : fight::Condition(0), height(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101946B0
			ObstacleFaceHeightCondition::~ObstacleFaceHeightCondition()
			{
			}

			// FUNCTION: ENGINE 0x10196A20
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ObstacleFaceHeightCondition::RegisterProperties()
			{
				if (gObstacleFaceHeightConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ObstacleFaceHeightCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ObstacleFaceHeightCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ObstacleFaceHeightCondition>("height", &ObstacleFaceHeightCondition::SetHeight);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gObstacleFaceHeightConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10196460
			fight::ConditionFactory* CreateObstacleFaceHeightConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleFaceHeightCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10197AE0
			void RegisterObstacleFaceHeightConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleFaceHeightCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gObstacleColliderTypeConditionProperties;  // 0x11254854

			// FUNCTION: ENGINE 0x10193E80
			bool ObstacleColliderTypeCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193E90
			bool ObstacleColliderTypeCondition::SetColliderType(int newValue)
			{
				colliderType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101946C0
			fight::Property* ObstacleColliderTypeCondition::GetProperty(int index)
			{
				return gObstacleColliderTypeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101946E0
			void ObstacleColliderTypeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gObstacleColliderTypeConditionProperties);
			}

			// FUNCTION: ENGINE 0x101946F0
			ObstacleColliderTypeCondition::ObstacleColliderTypeCondition() : fight::Condition(0), compare(0), colliderType(0)
			{
			}

			// FUNCTION: ENGINE 0x10194720
			ObstacleColliderTypeCondition::~ObstacleColliderTypeCondition()
			{
			}

			// FUNCTION: ENGINE 0x10196B10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ObstacleColliderTypeCondition::RegisterProperties()
			{
				if (gObstacleColliderTypeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ObstacleColliderTypeCondition>("compare", gObstacleColliderTypeConditionCompareTable, 2, &ObstacleColliderTypeCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyBitfieldConstList<ObstacleColliderTypeCondition>("colliderType", gDetectObbCollisionConditionCollideWithTable, gDetectObbCollisionConditionCollideWithCount, &ObstacleColliderTypeCondition::SetColliderType);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gObstacleColliderTypeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10196490
			fight::ConditionFactory* CreateObstacleColliderTypeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleColliderTypeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10197B10
			void RegisterObstacleColliderTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleColliderTypeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gObstacleVelocityConditionProperties;  // 0x11254858

			// FUNCTION: ENGINE 0x10193EA0
			bool ObstacleVelocityCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193EB0
			bool ObstacleVelocityCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193EC0
			bool ObstacleVelocityCondition::SetVelocity(float newValue)
			{
				velocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194730
			fight::Property* ObstacleVelocityCondition::GetProperty(int index)
			{
				return gObstacleVelocityConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10194750
			void ObstacleVelocityCondition::ClearProperties()
			{
				fight::FreePropertyList(&gObstacleVelocityConditionProperties);
			}

			// FUNCTION: ENGINE 0x10194760
			ObstacleVelocityCondition::ObstacleVelocityCondition() : fight::Condition(0), velocity(0.0f), compare(0), direction(0)
			{
			}

			// FUNCTION: ENGINE 0x101947A0
			ObstacleVelocityCondition::~ObstacleVelocityCondition()
			{
			}

			// FUNCTION: ENGINE 0x10196C10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ObstacleVelocityCondition::RegisterProperties()
			{
				if (gObstacleVelocityConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ObstacleVelocityCondition>("direction", gCrowdPositionConditionDirectionTable, gCrowdPositionConditionDirectionCount, &ObstacleVelocityCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<ObstacleVelocityCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ObstacleVelocityCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ObstacleVelocityCondition>("velocity", &ObstacleVelocityCondition::SetVelocity);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gObstacleVelocityConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101964C0
			fight::ConditionFactory* CreateObstacleVelocityConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleVelocityCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10197B40
			void RegisterObstacleVelocityConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleVelocityCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gObstacleLengthConditionProperties;  // 0x1125485C

			// FUNCTION: ENGINE 0x10193EE0
			bool ObstacleLengthCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193EF0
			bool ObstacleLengthCondition::SetLength(float newValue)
			{
				length = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101947B0
			fight::Property* ObstacleLengthCondition::GetProperty(int index)
			{
				return gObstacleLengthConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101947D0
			void ObstacleLengthCondition::ClearProperties()
			{
				fight::FreePropertyList(&gObstacleLengthConditionProperties);
			}

			// FUNCTION: ENGINE 0x101947E0
			ObstacleLengthCondition::ObstacleLengthCondition() : fight::Condition(0), length(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10194810
			ObstacleLengthCondition::~ObstacleLengthCondition()
			{
			}

			// FUNCTION: ENGINE 0x10196D50
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ObstacleLengthCondition::RegisterProperties()
			{
				if (gObstacleLengthConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ObstacleLengthCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ObstacleLengthCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ObstacleLengthCondition>("length", &ObstacleLengthCondition::SetLength);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gObstacleLengthConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101964F0
			fight::ConditionFactory* CreateObstacleLengthConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleLengthCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10197B70
			void RegisterObstacleLengthConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleLengthCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gObstacleWidthConditionProperties;  // 0x11254860

			// FUNCTION: ENGINE 0x10193F10
			bool ObstacleWidthCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193F20
			bool ObstacleWidthCondition::SetWidth(float newValue)
			{
				width = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194820
			fight::Property* ObstacleWidthCondition::GetProperty(int index)
			{
				return gObstacleWidthConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10194840
			void ObstacleWidthCondition::ClearProperties()
			{
				fight::FreePropertyList(&gObstacleWidthConditionProperties);
			}

			// FUNCTION: ENGINE 0x10194850
			ObstacleWidthCondition::ObstacleWidthCondition() : fight::Condition(0), width(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10194880
			ObstacleWidthCondition::~ObstacleWidthCondition()
			{
			}

			// FUNCTION: ENGINE 0x10196E40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ObstacleWidthCondition::RegisterProperties()
			{
				if (gObstacleWidthConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ObstacleWidthCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ObstacleWidthCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ObstacleWidthCondition>("width", &ObstacleWidthCondition::SetWidth);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gObstacleWidthConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10196520
			fight::ConditionFactory* CreateObstacleWidthConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleWidthCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10197BA0
			void RegisterObstacleWidthConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleWidthCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gObstacleHeightConditionProperties;  // 0x11254864

			// FUNCTION: ENGINE 0x10193F40
			bool ObstacleHeightCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193F50
			bool ObstacleHeightCondition::SetHeight(float newValue)
			{
				height = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194890
			fight::Property* ObstacleHeightCondition::GetProperty(int index)
			{
				return gObstacleHeightConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101948B0
			void ObstacleHeightCondition::ClearProperties()
			{
				fight::FreePropertyList(&gObstacleHeightConditionProperties);
			}

			// FUNCTION: ENGINE 0x101948C0
			ObstacleHeightCondition::ObstacleHeightCondition() : fight::Condition(0), height(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101948F0
			ObstacleHeightCondition::~ObstacleHeightCondition()
			{
			}

			// FUNCTION: ENGINE 0x10196F30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ObstacleHeightCondition::RegisterProperties()
			{
				if (gObstacleHeightConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ObstacleHeightCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ObstacleHeightCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ObstacleHeightCondition>("height", &ObstacleHeightCondition::SetHeight);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gObstacleHeightConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10196550
			fight::ConditionFactory* CreateObstacleHeightConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleHeightCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10197BD0
			void RegisterObstacleHeightConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ObstacleHeightCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gObstacleAvoidExitTrackProperties;  // 0x11254868

			// FUNCTION: ENGINE 0x10193F70
			bool ObstacleAvoidExitTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193F90
			bool ObstacleAvoidExitTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193FB0
			bool ObstacleAvoidExitTrack::SetTangentDistance(float newValue)
			{
				tangentDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193FD0
			bool ObstacleAvoidExitTrack::SetNormalDistance(float newValue)
			{
				normalDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193FF0
			bool ObstacleAvoidExitTrack::SetTurningRate(float newValue)
			{
				turningRate = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10194010
			bool ObstacleAvoidExitTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194020
			bool ObstacleAvoidExitTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194040
			bool ObstacleAvoidExitTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194900
			fight::Property* ObstacleAvoidExitTrack::GetProperty(int index)
			{
				return gObstacleAvoidExitTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10194920
			void ObstacleAvoidExitTrack::ClearProperties()
			{
				fight::FreePropertyList(&gObstacleAvoidExitTrackProperties);
			}

			// FUNCTION: ENGINE 0x10194930
			ObstacleAvoidExitTrack::ObstacleAvoidExitTrack() : blendInTime(0.0f), blendOutTime(0.0f), normalDistance(0.0f), tangentDistance(0.0f), timeBegin(0.0f), timeEnd(-1.0f), turningRate(1.5707964f), priority(-5)
			{
			}

			// FUNCTION: ENGINE 0x101949A0
			float ObstacleAvoidExitTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101949B0
			float ObstacleAvoidExitTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101949C0
			ObstacleAvoidExitTrack::~ObstacleAvoidExitTrack()
			{
			}

			// FUNCTION: ENGINE 0x10197020
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ObstacleAvoidExitTrack::RegisterProperties()
			{
				if (gObstacleAvoidExitTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidExitTrack>("timeBegin", &ObstacleAvoidExitTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidExitTrack>("timeEnd", &ObstacleAvoidExitTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidExitTrack>("tangentDistance", &ObstacleAvoidExitTrack::SetTangentDistance);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidExitTrack>("normalDistance", &ObstacleAvoidExitTrack::SetNormalDistance);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidExitTrack>("turningRate", &ObstacleAvoidExitTrack::SetTurningRate);
					properties[4] = property;
					property = new fight::PropertyIntConstRange<ObstacleAvoidExitTrack>("priority", &ObstacleAvoidExitTrack::SetPriority);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidExitTrack>("blendInTime", &ObstacleAvoidExitTrack::SetBlendInTime);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidExitTrack>("blendOutTime", &ObstacleAvoidExitTrack::SetBlendOutTime);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gObstacleAvoidExitTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10196580
			fight::TrackFactory* CreateObstacleAvoidExitTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ObstacleAvoidExitTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10197C00
			void RegisterObstacleAvoidExitTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ObstacleAvoidExitTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gObstacleAvoidTrackProperties;  // 0x1125486C

			// FUNCTION: ENGINE 0x10194060
			bool ObstacleAvoidTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194080
			bool ObstacleAvoidTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101940A0
			bool ObstacleAvoidTrack::SetHeightMin(float newValue)
			{
				heightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101940C0
			bool ObstacleAvoidTrack::SetUpVelocityMax(float newValue)
			{
				upVelocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101940E0
			bool ObstacleAvoidTrack::SetForwardVelocityMin(float newValue)
			{
				forwardVelocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194100
			bool ObstacleAvoidTrack::SetForwardVelocityMax(float newValue)
			{
				forwardVelocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194120
			bool ObstacleAvoidTrack::SetTurnVelocityMin(float newValue)
			{
				turnVelocityMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10194140
			bool ObstacleAvoidTrack::SetTurnVelocityMax(float newValue)
			{
				turnVelocityMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10194160
			bool ObstacleAvoidTrack::SetTurnAccelerationMin(float newValue)
			{
				turnAccelerationMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10194180
			bool ObstacleAvoidTrack::SetTurnAccelerationMax(float newValue)
			{
				turnAccelerationMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101941A0
			bool ObstacleAvoidTrack::SetPoleAvoidVelocity(float newValue)
			{
				poleAvoidVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101941C0
			bool ObstacleAvoidTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101941D0
			bool ObstacleAvoidTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101941F0
			bool ObstacleAvoidTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101949D0
			fight::Property* ObstacleAvoidTrack::GetProperty(int index)
			{
				return gObstacleAvoidTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101949F0
			void ObstacleAvoidTrack::ClearProperties()
			{
				fight::FreePropertyList(&gObstacleAvoidTrackProperties);
			}

			// FUNCTION: ENGINE 0x10194A00
			ObstacleAvoidTrack::ObstacleAvoidTrack() : blendInTime(0.0f), blendOutTime(0.0f), forwardVelocityMax(2e+01f), forwardVelocityMin(1e+01f), heightMin(1.0f), poleAvoidVelocity(1e+01f), timeBegin(0.0f), timeEnd(-1.0f), turnAccelerationMax(0.0f), turnAccelerationMin(0.0f), turnVelocityMax(0.0f), turnVelocityMin(0.0f), upVelocityMax(5.0f), priority(-5)
			{
			}

			// FUNCTION: ENGINE 0x10194AB0
			float ObstacleAvoidTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10194AC0
			float ObstacleAvoidTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10194AD0
			ObstacleAvoidTrack::~ObstacleAvoidTrack()
			{
			}

			// FUNCTION: ENGINE 0x10197270
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ObstacleAvoidTrack::RegisterProperties()
			{
				if (gObstacleAvoidTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidTrack>("timeBegin", &ObstacleAvoidTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidTrack>("timeEnd", &ObstacleAvoidTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidTrack>("heightMin", &ObstacleAvoidTrack::SetHeightMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidTrack>("upVelocityMax", &ObstacleAvoidTrack::SetUpVelocityMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidTrack>("forwardVelocityMin", &ObstacleAvoidTrack::SetForwardVelocityMin);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidTrack>("forwardVelocityMax", &ObstacleAvoidTrack::SetForwardVelocityMax);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidTrack>("turnVelocityMin", &ObstacleAvoidTrack::SetTurnVelocityMin);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidTrack>("turnVelocityMax", &ObstacleAvoidTrack::SetTurnVelocityMax);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidTrack>("turnAccelerationMin", &ObstacleAvoidTrack::SetTurnAccelerationMin);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidTrack>("turnAccelerationMax", &ObstacleAvoidTrack::SetTurnAccelerationMax);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidTrack>("poleAvoidVelocity", &ObstacleAvoidTrack::SetPoleAvoidVelocity);
					properties[10] = property;
					property = new fight::PropertyIntConstRange<ObstacleAvoidTrack>("priority", &ObstacleAvoidTrack::SetPriority);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidTrack>("blendInTime", &ObstacleAvoidTrack::SetBlendInTime);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<ObstacleAvoidTrack>("blendOutTime", &ObstacleAvoidTrack::SetBlendOutTime);
					properties[13] = property;
					fight::RegisterPropertyList(properties, &gObstacleAvoidTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101965B0
			fight::TrackFactory* CreateObstacleAvoidTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ObstacleAvoidTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10197C30
			void RegisterObstacleAvoidTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ObstacleAvoidTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gPushFromObstacleTrackProperties;  // 0x11254870

			// FUNCTION: ENGINE 0x10194210
			bool PushFromObstacleTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194230
			bool PushFromObstacleTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194C80
			bool PushFromObstacleTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194250
			bool PushFromObstacleTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10194270
			bool PushFromObstacleTrack::SetRayVector(const math::Vector& newValue)
			{
				rayVector.x = newValue.x;
				rayVector.y = newValue.y;
				rayVector.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10194290
			bool PushFromObstacleTrack::SetCollideWith(int newValue)
			{
				collideWith = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101942A0
			bool PushFromObstacleTrack::SetVelocity(float newValue)
			{
				velocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194AE0
			fight::Property* PushFromObstacleTrack::GetProperty(int index)
			{
				return gPushFromObstacleTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10194B00
			void PushFromObstacleTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPushFromObstacleTrackProperties);
			}

			// FUNCTION: ENGINE 0x10194EE0
			PushFromObstacleTrack::PushFromObstacleTrack() : offset(0.0f, 0.0f, 0.0f), rayVector(0.0f, 0.0f, 0.0f), timeBegin(0.0f), timeEnd(-1.0f), velocity(1e+01f), collideWith(gPushFromObstacleTrackCollideWithDefault)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10194F70
			float PushFromObstacleTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10194F80
			float PushFromObstacleTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10194F90
			PushFromObstacleTrack::~PushFromObstacleTrack()
			{
			}

			// FUNCTION: ENGINE 0x10198130
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PushFromObstacleTrack::RegisterProperties()
			{
				if (gPushFromObstacleTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PushFromObstacleTrack>("timeBegin", &PushFromObstacleTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PushFromObstacleTrack>("timeEnd", &PushFromObstacleTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<PushFromObstacleTrack>("joint", &PushFromObstacleTrack::SetJoint);
					properties[2] = property;
					property = new fight::PropertyVector<PushFromObstacleTrack>("offset", &PushFromObstacleTrack::SetOffset);
					properties[3] = property;
					property = new fight::PropertyVector<PushFromObstacleTrack>("rayVector", &PushFromObstacleTrack::SetRayVector);
					properties[4] = property;
					property = new fight::PropertyBitfieldConstList<PushFromObstacleTrack>("collideWith", gDetectObbCollisionConditionCollideWithTable, gDetectObbCollisionConditionCollideWithCount, &PushFromObstacleTrack::SetCollideWith);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<PushFromObstacleTrack>("velocity", &PushFromObstacleTrack::SetVelocity);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gPushFromObstacleTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101965E0
			fight::TrackFactory* CreatePushFromObstacleTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PushFromObstacleTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10197C60
			void RegisterPushFromObstacleTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PushFromObstacleTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gObstacleTestTrackProperties;  // 0x11254874

			// FUNCTION: ENGINE 0x101942C0
			bool ObstacleTestTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101942E0
			bool ObstacleTestTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194300
			bool ObstacleTestTrack::SetLookaheadDistance(float newValue)
			{
				lookaheadDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194320
			bool ObstacleTestTrack::SetCharacterHeight(float newValue)
			{
				characterHeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194340
			bool ObstacleTestTrack::SetCharacterWidth(float newValue)
			{
				characterWidth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194360
			bool ObstacleTestTrack::SetCharacterDepth(float newValue)
			{
				characterDepth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194380
			bool ObstacleTestTrack::SetCharacterSurfaceClearance(float newValue)
			{
				characterSurfaceClearance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101943A0
			bool ObstacleTestTrack::SetObstacleHeightMin(float newValue)
			{
				obstacleHeightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101943C0
			bool ObstacleTestTrack::SetObstacleHeightMax(float newValue)
			{
				obstacleHeightMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101943E0
			bool ObstacleTestTrack::SetObstacleLengthMax(float newValue)
			{
				obstacleLengthMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194400
			bool ObstacleTestTrack::SetSurfaceNormalOverride(const math::Vector& newValue)
			{
				surfaceNormalOverride.x = newValue.x;
				surfaceNormalOverride.y = newValue.y;
				surfaceNormalOverride.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10194420
			bool ObstacleTestTrack::SetPoleAvoidVelocity(float newValue)
			{
				poleAvoidVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194440
			fight::BranchHolder* ObstacleTestTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x10194450
			bool ObstacleTestTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10194460
			fight::ConditionList* ObstacleTestTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x10194B10
			fight::Property* ObstacleTestTrack::GetProperty(int index)
			{
				return gObstacleTestTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10194B30
			void ObstacleTestTrack::ClearProperties()
			{
				fight::FreePropertyList(&gObstacleTestTrackProperties);
			}

			// FUNCTION: ENGINE 0x10194B40
			ObstacleTestTrack::ObstacleTestTrack() : branch(0), surfaceNormalOverride(0.0f, 0.0f, 0.0f), characterDepth(1.0f), characterHeight(2.0f), characterSurfaceClearance(0.5f), characterWidth(1.0f), lookaheadDistance(5.0f), obstacleHeightMax(2.0f), obstacleHeightMin(0.25f), obstacleLengthMax(2.0f), poleAvoidVelocity(1e+01f), timeBegin(0.0f), timeEnd(-1.0f), priority(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10194C30
			float ObstacleTestTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10194C40
			float ObstacleTestTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10194C50
			ObstacleTestTrack::~ObstacleTestTrack()
			{
			}

			// FUNCTION: ENGINE 0x10197630
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ObstacleTestTrack::RegisterProperties()
			{
				if (gObstacleTestTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ObstacleTestTrack>("timeBegin", &ObstacleTestTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ObstacleTestTrack>("timeEnd", &ObstacleTestTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ObstacleTestTrack>("lookaheadDistance", &ObstacleTestTrack::SetLookaheadDistance);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ObstacleTestTrack>("characterHeight", &ObstacleTestTrack::SetCharacterHeight);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<ObstacleTestTrack>("characterWidth", &ObstacleTestTrack::SetCharacterWidth);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<ObstacleTestTrack>("characterDepth", &ObstacleTestTrack::SetCharacterDepth);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<ObstacleTestTrack>("characterSurfaceClearance", &ObstacleTestTrack::SetCharacterSurfaceClearance);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<ObstacleTestTrack>("obstacleHeightMin", &ObstacleTestTrack::SetObstacleHeightMin);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<ObstacleTestTrack>("obstacleHeightMax", &ObstacleTestTrack::SetObstacleHeightMax);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<ObstacleTestTrack>("obstacleLengthMax", &ObstacleTestTrack::SetObstacleLengthMax);
					properties[9] = property;
					property = new fight::PropertyVector<ObstacleTestTrack>("surfaceNormalOverride", &ObstacleTestTrack::SetSurfaceNormalOverride);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<ObstacleTestTrack>("poleAvoidVelocity", &ObstacleTestTrack::SetPoleAvoidVelocity);
					properties[11] = property;
					property = new fight::PropertyBranch<ObstacleTestTrack>("branch", &ObstacleTestTrack::SetBranch);
					properties[12] = property;
					property = new fight::PropertyIntConstRange<ObstacleTestTrack>("priority", &ObstacleTestTrack::SetPriority);
					properties[13] = property;
					property = new fight::PropertyConditionGroup<ObstacleTestTrack>("conditions", &ObstacleTestTrack::SetConditions);
					properties[14] = property;
					fight::RegisterPropertyList(properties, &gObstacleTestTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10196610
			fight::TrackFactory* CreateObstacleTestTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ObstacleTestTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10197C90
			void RegisterObstacleTestTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ObstacleTestTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<ObstacleDistanceCondition>;
			template class fight::PropertyFloatConstRange<ObstacleDistanceCondition>;
			template class fight::ConditionFactoryTemplate<ObstacleDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<ObstacleDistanceCondition>;
			template class fight::PropertyEnumConstList<ObstacleTimeToObstacleCondition>;
			template class fight::PropertyFloatConstRange<ObstacleTimeToObstacleCondition>;
			template class fight::ConditionFactoryTemplate<ObstacleTimeToObstacleCondition>;
			template class fight::ConditionFactoryCasterTemplate<ObstacleTimeToObstacleCondition>;
			template class fight::PropertyEnumConstList<ObstacleSlopeCondition>;
			template class fight::PropertyFloatConstRange<ObstacleSlopeCondition>;
			template class fight::ConditionFactoryTemplate<ObstacleSlopeCondition>;
			template class fight::ConditionFactoryCasterTemplate<ObstacleSlopeCondition>;
			template class fight::PropertyFloatConstRange<ObstacleFaceHeightSlopeCondition>;
			template class fight::ConditionFactoryTemplate<ObstacleFaceHeightSlopeCondition>;
			template class fight::ConditionFactoryCasterTemplate<ObstacleFaceHeightSlopeCondition>;
			template class fight::PropertyEnumConstList<ObstacleFaceHeightCondition>;
			template class fight::PropertyFloatConstRange<ObstacleFaceHeightCondition>;
			template class fight::ConditionFactoryTemplate<ObstacleFaceHeightCondition>;
			template class fight::ConditionFactoryCasterTemplate<ObstacleFaceHeightCondition>;
			template class fight::PropertyEnumConstList<ObstacleColliderTypeCondition>;
			template class fight::PropertyBitfieldConstList<ObstacleColliderTypeCondition>;
			template class fight::ConditionFactoryTemplate<ObstacleColliderTypeCondition>;
			template class fight::ConditionFactoryCasterTemplate<ObstacleColliderTypeCondition>;
			template class fight::PropertyEnumConstList<ObstacleVelocityCondition>;
			template class fight::PropertyFloatConstRange<ObstacleVelocityCondition>;
			template class fight::ConditionFactoryTemplate<ObstacleVelocityCondition>;
			template class fight::ConditionFactoryCasterTemplate<ObstacleVelocityCondition>;
			template class fight::PropertyEnumConstList<ObstacleLengthCondition>;
			template class fight::PropertyFloatConstRange<ObstacleLengthCondition>;
			template class fight::ConditionFactoryTemplate<ObstacleLengthCondition>;
			template class fight::ConditionFactoryCasterTemplate<ObstacleLengthCondition>;
			template class fight::PropertyEnumConstList<ObstacleWidthCondition>;
			template class fight::PropertyFloatConstRange<ObstacleWidthCondition>;
			template class fight::ConditionFactoryTemplate<ObstacleWidthCondition>;
			template class fight::ConditionFactoryCasterTemplate<ObstacleWidthCondition>;
			template class fight::PropertyEnumConstList<ObstacleHeightCondition>;
			template class fight::PropertyFloatConstRange<ObstacleHeightCondition>;
			template class fight::ConditionFactoryTemplate<ObstacleHeightCondition>;
			template class fight::ConditionFactoryCasterTemplate<ObstacleHeightCondition>;
			template class fight::PropertyFloatConstRange<ObstacleAvoidExitTrack>;
			template class fight::PropertyIntConstRange<ObstacleAvoidExitTrack>;
			template class fight::TrackFactoryTemplate<ObstacleAvoidExitTrack>;
			template class fight::TrackFactoryCasterTemplate<ObstacleAvoidExitTrack>;
			template class fight::PropertyFloatConstRange<ObstacleAvoidTrack>;
			template class fight::PropertyIntConstRange<ObstacleAvoidTrack>;
			template class fight::TrackFactoryTemplate<ObstacleAvoidTrack>;
			template class fight::TrackFactoryCasterTemplate<ObstacleAvoidTrack>;
			template class fight::PropertyFloatConstRange<PushFromObstacleTrack>;
			template class fight::PropertyNameList<PushFromObstacleTrack>;
			template class fight::PropertyVector<PushFromObstacleTrack>;
			template class fight::PropertyBitfieldConstList<PushFromObstacleTrack>;
			template class fight::TrackFactoryTemplate<PushFromObstacleTrack>;
			template class fight::TrackFactoryCasterTemplate<PushFromObstacleTrack>;
			template class fight::PropertyFloatConstRange<ObstacleTestTrack>;
			template class fight::PropertyVector<ObstacleTestTrack>;
			template class fight::PropertyBranch<ObstacleTestTrack>;
			template class fight::PropertyIntConstRange<ObstacleTestTrack>;
			template class fight::PropertyConditionGroup<ObstacleTestTrack>;
			template class fight::TrackFactoryTemplate<ObstacleTestTrack>;
			template class fight::TrackFactoryCasterTemplate<ObstacleTestTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10194CA0
// FUNCTION: ENGINE 0x10194CD0
// FUNCTION: ENGINE 0x10194D00
// FUNCTION: ENGINE 0x10194D30
// FUNCTION: ENGINE 0x10194D60
// FUNCTION: ENGINE 0x10194D90
// FUNCTION: ENGINE 0x10194DC0
// FUNCTION: ENGINE 0x10194DF0
// FUNCTION: ENGINE 0x10194E20
// FUNCTION: ENGINE 0x10194E50
// FUNCTION: ENGINE 0x10194E80
// FUNCTION: ENGINE 0x10194EB0
// FUNCTION: ENGINE 0x10194FA0
// FUNCTION: ENGINE 0x10194FD0
// FUNCTION: ENGINE 0x10194FE0
// FUNCTION: ENGINE 0x10195010
// FUNCTION: ENGINE 0x10195020
// FUNCTION: ENGINE 0x10195050
// FUNCTION: ENGINE 0x10195060
// FUNCTION: ENGINE 0x10195090
// FUNCTION: ENGINE 0x101950A0
// FUNCTION: ENGINE 0x101950D0
// FUNCTION: ENGINE 0x101950E0
// FUNCTION: ENGINE 0x10195110
// FUNCTION: ENGINE 0x10195120
// FUNCTION: ENGINE 0x10195150
// FUNCTION: ENGINE 0x10195160
// FUNCTION: ENGINE 0x10195190
// FUNCTION: ENGINE 0x101951A0
// FUNCTION: ENGINE 0x101951D0
// FUNCTION: ENGINE 0x101951E0
// FUNCTION: ENGINE 0x10195210
// FUNCTION: ENGINE 0x10195220
// FUNCTION: ENGINE 0x10195250
// FUNCTION: ENGINE 0x10195260
// FUNCTION: ENGINE 0x10195290
// FUNCTION: ENGINE 0x101952A0
// FUNCTION: ENGINE 0x101952D0
// FUNCTION: ENGINE 0x101952E0
// FUNCTION: ENGINE 0x10195310
// FUNCTION: ENGINE 0x10195320
// FUNCTION: ENGINE 0x10195350
// FUNCTION: ENGINE 0x10195380
// FUNCTION: ENGINE 0x101953C0
// FUNCTION: ENGINE 0x101953D0
// FUNCTION: ENGINE 0x10195400
// FUNCTION: ENGINE 0x10195420
// FUNCTION: ENGINE 0x10195430
// FUNCTION: ENGINE 0x10195460
// FUNCTION: ENGINE 0x10195490
// FUNCTION: ENGINE 0x101954A0
// FUNCTION: ENGINE 0x101954E0
// FUNCTION: ENGINE 0x101954F0
// FUNCTION: ENGINE 0x10195520
// FUNCTION: ENGINE 0x10195540
// FUNCTION: ENGINE 0x10195550
// FUNCTION: ENGINE 0x10195580
// FUNCTION: ENGINE 0x101955B0
// FUNCTION: ENGINE 0x101955C0
// FUNCTION: ENGINE 0x10195600
// FUNCTION: ENGINE 0x10195610
// FUNCTION: ENGINE 0x10195640
// FUNCTION: ENGINE 0x10195660
// FUNCTION: ENGINE 0x10195670
// FUNCTION: ENGINE 0x101956A0
// FUNCTION: ENGINE 0x101956D0
// FUNCTION: ENGINE 0x101956E0
// FUNCTION: ENGINE 0x10195710
// FUNCTION: ENGINE 0x10195740
// FUNCTION: ENGINE 0x10195750
// FUNCTION: ENGINE 0x10195790
// FUNCTION: ENGINE 0x101957A0
// FUNCTION: ENGINE 0x101957D0
// FUNCTION: ENGINE 0x101957F0
// FUNCTION: ENGINE 0x10195800
// FUNCTION: ENGINE 0x10195830
// FUNCTION: ENGINE 0x10195860
// FUNCTION: ENGINE 0x10195870
// FUNCTION: ENGINE 0x101958B0
// FUNCTION: ENGINE 0x101958C0
// FUNCTION: ENGINE 0x101958F0
// FUNCTION: ENGINE 0x10195910
// FUNCTION: ENGINE 0x10195920
// FUNCTION: ENGINE 0x10195960
// FUNCTION: ENGINE 0x10195970
// FUNCTION: ENGINE 0x10195990
// FUNCTION: ENGINE 0x101959A0
// FUNCTION: ENGINE 0x10195A00
// FUNCTION: ENGINE 0x10195A40
// FUNCTION: ENGINE 0x10195A50
// FUNCTION: ENGINE 0x10195A80
// FUNCTION: ENGINE 0x10195AA0
// FUNCTION: ENGINE 0x10195AB0
// FUNCTION: ENGINE 0x10195AE0
// FUNCTION: ENGINE 0x10195B10
// FUNCTION: ENGINE 0x10195B20
// FUNCTION: ENGINE 0x10195B60
// FUNCTION: ENGINE 0x10195B70
// FUNCTION: ENGINE 0x10195BA0
// FUNCTION: ENGINE 0x10195BC0
// FUNCTION: ENGINE 0x10195BD0
// FUNCTION: ENGINE 0x10195C00
// FUNCTION: ENGINE 0x10195C30
// FUNCTION: ENGINE 0x10195C40
// FUNCTION: ENGINE 0x10195C80
// FUNCTION: ENGINE 0x10195C90
// FUNCTION: ENGINE 0x10195CC0
// FUNCTION: ENGINE 0x10195CE0
// FUNCTION: ENGINE 0x10195CF0
// FUNCTION: ENGINE 0x10195D20
// FUNCTION: ENGINE 0x10195D50
// FUNCTION: ENGINE 0x10195D60
// FUNCTION: ENGINE 0x10195DA0
// FUNCTION: ENGINE 0x10195DB0
// FUNCTION: ENGINE 0x10195DE0
// FUNCTION: ENGINE 0x10195E00
// FUNCTION: ENGINE 0x10195E10
// FUNCTION: ENGINE 0x10195E40
// FUNCTION: ENGINE 0x10195E70
// FUNCTION: ENGINE 0x10195E80
// FUNCTION: ENGINE 0x10195EB0
// FUNCTION: ENGINE 0x10195EE0
// FUNCTION: ENGINE 0x10195EF0
// FUNCTION: ENGINE 0x10195F20
// FUNCTION: ENGINE 0x10195F40
// FUNCTION: ENGINE 0x10195F50
// FUNCTION: ENGINE 0x10195F80
// FUNCTION: ENGINE 0x10195FB0
// FUNCTION: ENGINE 0x10195FC0
// FUNCTION: ENGINE 0x10195FF0
// FUNCTION: ENGINE 0x10196010
// FUNCTION: ENGINE 0x10196020
// FUNCTION: ENGINE 0x10196050
// FUNCTION: ENGINE 0x10196080
// FUNCTION: ENGINE 0x10196090
// FUNCTION: ENGINE 0x101960C0
// FUNCTION: ENGINE 0x101960E0
// FUNCTION: ENGINE 0x101960F0
// FUNCTION: ENGINE 0x10196130
// FUNCTION: ENGINE 0x10196140
// FUNCTION: ENGINE 0x10196160
// FUNCTION: ENGINE 0x10196170
// FUNCTION: ENGINE 0x101961D0
// FUNCTION: ENGINE 0x10196200
// FUNCTION: ENGINE 0x10196230
// FUNCTION: ENGINE 0x10196240
// FUNCTION: ENGINE 0x10196270
// FUNCTION: ENGINE 0x10196290
// FUNCTION: ENGINE 0x101962A0
// FUNCTION: ENGINE 0x101962D0
// FUNCTION: ENGINE 0x101962F0
// FUNCTION: ENGINE 0x10196320
// FUNCTION: ENGINE 0x10196340
// FUNCTION: ENGINE 0x10196350
// FUNCTION: ENGINE 0x10196380
// FUNCTION: ENGINE 0x10197CC0
// FUNCTION: ENGINE 0x10197CF0
// FUNCTION: ENGINE 0x10197D10
// FUNCTION: ENGINE 0x10197D20
// FUNCTION: ENGINE 0x10197D50
// FUNCTION: ENGINE 0x10197D70
// FUNCTION: ENGINE 0x10197DA0
// FUNCTION: ENGINE 0x10197DC0
// FUNCTION: ENGINE 0x10197DF0
// FUNCTION: ENGINE 0x10197E10
// FUNCTION: ENGINE 0x10197E40
// FUNCTION: ENGINE 0x10197E60
// FUNCTION: ENGINE 0x10197E90
// FUNCTION: ENGINE 0x10197EB0
// FUNCTION: ENGINE 0x10197EE0
// FUNCTION: ENGINE 0x10197F00
// FUNCTION: ENGINE 0x10197F30
// FUNCTION: ENGINE 0x10197F50
// FUNCTION: ENGINE 0x10197F80
// FUNCTION: ENGINE 0x10197FA0
// FUNCTION: ENGINE 0x10197FD0
// FUNCTION: ENGINE 0x10197FF0
// FUNCTION: ENGINE 0x10198020
// FUNCTION: ENGINE 0x10198040
// FUNCTION: ENGINE 0x10198070
// FUNCTION: ENGINE 0x10198090
// FUNCTION: ENGINE 0x101980C0
// FUNCTION: ENGINE 0x101980E0
// FUNCTION: ENGINE 0x10198110
// FUNCTION: ENGINE 0x10198350
// FUNCTION: ENGINE 0x101983A0
// FUNCTION: ENGINE 0x101983F0
// FUNCTION: ENGINE 0x10198440
// FUNCTION: ENGINE 0x10198490
// FUNCTION: ENGINE 0x101984E0
// FUNCTION: ENGINE 0x10198530
// FUNCTION: ENGINE 0x10198580
// FUNCTION: ENGINE 0x101985D0
// FUNCTION: ENGINE 0x10198620
// FUNCTION: ENGINE 0x10198670
// FUNCTION: ENGINE 0x101986C0
// FUNCTION: ENGINE 0x10198710
// FUNCTION: ENGINE 0x10198760
// FUNCTION: ENGINE 0x10198790
// FUNCTION: ENGINE 0x101987B0
