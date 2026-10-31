// Fight items of the motion group: ReactionEventConditionGroupCondition, ReactionHitCollisionPositionCondition, ReactionHitDamageCondition, ReactionHitChargeCondition, ReactionHitOriginatorDistanceCondition, ReactionReceiverIsTargetCondition, ReactionGiverIsBeingGrabbedCondition, ReactionEventCondition, ReactionHitCollisionNormalCondition, ReactionScriptedSubTypeCondition, ReactionHitOriginatorIsPlayerCondition, ReactionGrabTypeCondition, ReactionHitSliceAngleCondition, ReactionHitFromMuscleMassCondition, ReactionHitCollisionFlagCondition, ReactionThrowHitTypeCondition, ReactionHitImpulseCondition, ReactionHitDamageTypeCondition, ReactionHitImpulseDirectionCondition, ReactionTargetCondition, ReactionHitAttackTypeCondition, ReactionHitHeightCondition, ReactionHitHitTypeCondition, ReactionHitImpulseYAngleCondition (unit 0x101A1160 - 0x101A69E0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_reactioncondition.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gReactionEventConditionGroupConditionProperties;  // 0x11254968

			// FUNCTION: ENGINE 0x101A1160
			bool ReactionEventConditionGroupCondition::SetObject(int newValue)
			{
				object = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1170
			fight::ConditionList* ReactionEventConditionGroupCondition::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x101A14B0
			fight::Property* ReactionEventConditionGroupCondition::GetProperty(int index)
			{
				return gReactionEventConditionGroupConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A14D0
			void ReactionEventConditionGroupCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionEventConditionGroupConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A14E0
			ReactionEventConditionGroupCondition::ReactionEventConditionGroupCondition() : fight::Condition(0), object(0)
			{
			}

			// FUNCTION: ENGINE 0x101A1510
			ReactionEventConditionGroupCondition::~ReactionEventConditionGroupCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A4100
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionEventConditionGroupCondition::RegisterProperties()
			{
				if (gReactionEventConditionGroupConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ReactionEventConditionGroupCondition>("object", gReactionHitGrabTrackObjectTable, gReactionHitGrabTrackObjectCount, &ReactionEventConditionGroupCondition::SetObject);
					properties[0] = property;
					property = new fight::PropertyConditionGroup<ReactionEventConditionGroupCondition>("conditions", &ReactionEventConditionGroupCondition::SetConditions);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionEventConditionGroupConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3C80
			fight::ConditionFactory* CreateReactionEventConditionGroupConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionEventConditionGroupCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A5260
			void RegisterReactionEventConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionEventConditionGroupCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitCollisionPositionConditionProperties;  // 0x1125496C

			// FUNCTION: ENGINE 0x101A1180
			bool ReactionHitCollisionPositionCondition::SetComponent(int newValue)
			{
				component = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1190
			bool ReactionHitCollisionPositionCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A11A0
			bool ReactionHitCollisionPositionCondition::SetPosition(float newValue)
			{
				position = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1530
			fight::Property* ReactionHitCollisionPositionCondition::GetProperty(int index)
			{
				return gReactionHitCollisionPositionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1550
			void ReactionHitCollisionPositionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitCollisionPositionConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A1560
			ReactionHitCollisionPositionCondition::ReactionHitCollisionPositionCondition() : fight::Condition(0), position(0.0f), compare(0), component(0)
			{
			}

			// FUNCTION: ENGINE 0x101A15A0
			ReactionHitCollisionPositionCondition::~ReactionHitCollisionPositionCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A41F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitCollisionPositionCondition::RegisterProperties()
			{
				if (gReactionHitCollisionPositionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ReactionHitCollisionPositionCondition>("component", gReactionHitCollisionPositionConditionComponentTable, 3, &ReactionHitCollisionPositionCondition::SetComponent);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<ReactionHitCollisionPositionCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ReactionHitCollisionPositionCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitCollisionPositionCondition>("position", &ReactionHitCollisionPositionCondition::SetPosition);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gReactionHitCollisionPositionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3CB0
			fight::ConditionFactory* CreateReactionHitCollisionPositionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitCollisionPositionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A5290
			void RegisterReactionHitCollisionPositionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitCollisionPositionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitDamageConditionProperties;  // 0x11254970

			// FUNCTION: ENGINE 0x101A11C0
			bool ReactionHitDamageCondition::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A11D0
			bool ReactionHitDamageCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A11E0
			bool ReactionHitDamageCondition::SetDamage(float newValue)
			{
				damage = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A15B0
			fight::Property* ReactionHitDamageCondition::GetProperty(int index)
			{
				return gReactionHitDamageConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A15D0
			void ReactionHitDamageCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitDamageConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A15E0
			ReactionHitDamageCondition::ReactionHitDamageCondition() : fight::Condition(0), damage(0.0f), compare(0), type(0)
			{
			}

			// FUNCTION: ENGINE 0x101A1620
			ReactionHitDamageCondition::~ReactionHitDamageCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A4330
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitDamageCondition::RegisterProperties()
			{
				if (gReactionHitDamageConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ReactionHitDamageCondition>("type", gReactionHitDamageConditionTypeTable, gReactionHitDamageConditionTypeCount, &ReactionHitDamageCondition::SetType);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<ReactionHitDamageCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ReactionHitDamageCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitDamageCondition>("damage", &ReactionHitDamageCondition::SetDamage);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gReactionHitDamageConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3CE0
			fight::ConditionFactory* CreateReactionHitDamageConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitDamageCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A52C0
			void RegisterReactionHitDamageConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitDamageCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitChargeConditionProperties;  // 0x11254974

			// FUNCTION: ENGINE 0x101A1200
			bool ReactionHitChargeCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1210
			bool ReactionHitChargeCondition::SetCharge(float newValue)
			{
				charge = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1630
			fight::Property* ReactionHitChargeCondition::GetProperty(int index)
			{
				return gReactionHitChargeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1650
			void ReactionHitChargeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitChargeConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A1660
			ReactionHitChargeCondition::ReactionHitChargeCondition() : fight::Condition(0), charge(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101A1690
			ReactionHitChargeCondition::~ReactionHitChargeCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A4470
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitChargeCondition::RegisterProperties()
			{
				if (gReactionHitChargeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ReactionHitChargeCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ReactionHitChargeCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitChargeCondition>("charge", &ReactionHitChargeCondition::SetCharge);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionHitChargeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3D10
			fight::ConditionFactory* CreateReactionHitChargeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitChargeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A52F0
			void RegisterReactionHitChargeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitChargeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitOriginatorDistanceConditionProperties;  // 0x11254978

			// FUNCTION: ENGINE 0x101A1230
			bool ReactionHitOriginatorDistanceCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1240
			bool ReactionHitOriginatorDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1250
			bool ReactionHitOriginatorDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A16A0
			fight::Property* ReactionHitOriginatorDistanceCondition::GetProperty(int index)
			{
				return gReactionHitOriginatorDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A16C0
			void ReactionHitOriginatorDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitOriginatorDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A16D0
			ReactionHitOriginatorDistanceCondition::ReactionHitOriginatorDistanceCondition() : fight::Condition(0), distance(2e+01f), compare(4), direction(0)
			{
			}

			// FUNCTION: ENGINE 0x101A1710
			ReactionHitOriginatorDistanceCondition::~ReactionHitOriginatorDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A4560
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitOriginatorDistanceCondition::RegisterProperties()
			{
				if (gReactionHitOriginatorDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ReactionHitOriginatorDistanceCondition>("direction", gCrowdPositionConditionDirectionTable, gCrowdPositionConditionDirectionCount, &ReactionHitOriginatorDistanceCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<ReactionHitOriginatorDistanceCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ReactionHitOriginatorDistanceCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitOriginatorDistanceCondition>("distance", &ReactionHitOriginatorDistanceCondition::SetDistance);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gReactionHitOriginatorDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3D40
			fight::ConditionFactory* CreateReactionHitOriginatorDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitOriginatorDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A5320
			void RegisterReactionHitOriginatorDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitOriginatorDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionReceiverIsTargetConditionProperties;  // 0x1125497C

			// FUNCTION: ENGINE 0x101A1270
			bool ReactionReceiverIsTargetCondition::SetIsTarget(bool newValue)
			{
				isTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1720
			fight::Property* ReactionReceiverIsTargetCondition::GetProperty(int index)
			{
				return gReactionReceiverIsTargetConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1740
			void ReactionReceiverIsTargetCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionReceiverIsTargetConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A1750
			ReactionReceiverIsTargetCondition::ReactionReceiverIsTargetCondition() : fight::Condition(0), isTarget(true)
			{
			}

			// FUNCTION: ENGINE 0x101A1770
			ReactionReceiverIsTargetCondition::~ReactionReceiverIsTargetCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A46A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionReceiverIsTargetCondition::RegisterProperties()
			{
				if (gReactionReceiverIsTargetConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ReactionReceiverIsTargetCondition>("isTarget", &ReactionReceiverIsTargetCondition::SetIsTarget);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gReactionReceiverIsTargetConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3D70
			fight::ConditionFactory* CreateReactionReceiverIsTargetConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionReceiverIsTargetCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A5350
			void RegisterReactionReceiverIsTargetConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionReceiverIsTargetCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionGiverIsBeingGrabbedConditionProperties;  // 0x11254980

			// FUNCTION: ENGINE 0x101A1280
			bool ReactionGiverIsBeingGrabbedCondition::SetGrabType(int newValue)
			{
				grabType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1780
			fight::Property* ReactionGiverIsBeingGrabbedCondition::GetProperty(int index)
			{
				return gReactionGiverIsBeingGrabbedConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A17A0
			void ReactionGiverIsBeingGrabbedCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionGiverIsBeingGrabbedConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A17B0
			ReactionGiverIsBeingGrabbedCondition::ReactionGiverIsBeingGrabbedCondition() : fight::Condition(0), grabType(0)
			{
			}

			// FUNCTION: ENGINE 0x101A17E0
			ReactionGiverIsBeingGrabbedCondition::~ReactionGiverIsBeingGrabbedCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A4740
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionGiverIsBeingGrabbedCondition::RegisterProperties()
			{
				if (gReactionGiverIsBeingGrabbedConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ReactionGiverIsBeingGrabbedCondition>("grabType", gReactionGiverIsBeingGrabbedConditionGrabTypeTable, gReactionGiverIsBeingGrabbedConditionGrabTypeCount, &ReactionGiverIsBeingGrabbedCondition::SetGrabType);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gReactionGiverIsBeingGrabbedConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3DA0
			fight::ConditionFactory* CreateReactionGiverIsBeingGrabbedConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionGiverIsBeingGrabbedCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A5380
			void RegisterReactionGiverIsBeingGrabbedConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionGiverIsBeingGrabbedCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionEventConditionProperties;  // 0x11254984

			// FUNCTION: ENGINE 0x101A1290
			bool ReactionEventCondition::SetIsReactionEvent(bool newValue)
			{
				isReactionEvent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A12A0
			bool ReactionEventCondition::SetReactionType(int newValue)
			{
				reactionType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A17F0
			fight::Property* ReactionEventCondition::GetProperty(int index)
			{
				return gReactionEventConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1810
			void ReactionEventCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionEventConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A1820
			ReactionEventCondition::ReactionEventCondition() : fight::Condition(0), reactionType(0), isReactionEvent(true)
			{
			}

			// FUNCTION: ENGINE 0x101A1850
			ReactionEventCondition::~ReactionEventCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A47F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionEventCondition::RegisterProperties()
			{
				if (gReactionEventConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ReactionEventCondition>("isReactionEvent", &ReactionEventCondition::SetIsReactionEvent);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<ReactionEventCondition>("reactionType", gReactionEventConditionReactionTypeTable, gReactionEventConditionReactionTypeCount, &ReactionEventCondition::SetReactionType);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionEventConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3DD0
			fight::ConditionFactory* CreateReactionEventConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionEventCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A53B0
			void RegisterReactionEventConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionEventCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitCollisionNormalConditionProperties;  // 0x11254988

			// FUNCTION: ENGINE 0x101A12B0
			bool ReactionHitCollisionNormalCondition::SetNormal(const math::Vector& newValue)
			{
				normal.x = newValue.x;
				normal.y = newValue.y;
				normal.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101A12D0
			bool ReactionHitCollisionNormalCondition::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1860
			fight::Property* ReactionHitCollisionNormalCondition::GetProperty(int index)
			{
				return gReactionHitCollisionNormalConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1880
			void ReactionHitCollisionNormalCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitCollisionNormalConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A1890
			ReactionHitCollisionNormalCondition::ReactionHitCollisionNormalCondition() : fight::Condition(0), normal(0.0f, 1.0f, 0.0f), arc(1.5707964f)
			{
			}

			// FUNCTION: ENGINE 0x101A18E0
			ReactionHitCollisionNormalCondition::~ReactionHitCollisionNormalCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A48E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitCollisionNormalCondition::RegisterProperties()
			{
				if (gReactionHitCollisionNormalConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyVector<ReactionHitCollisionNormalCondition>("normal", &ReactionHitCollisionNormalCondition::SetNormal);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitCollisionNormalCondition>("arc", &ReactionHitCollisionNormalCondition::SetArc);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionHitCollisionNormalConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3E00
			fight::ConditionFactory* CreateReactionHitCollisionNormalConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitCollisionNormalCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A53E0
			void RegisterReactionHitCollisionNormalConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitCollisionNormalCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionScriptedSubTypeConditionProperties;  // 0x1125498C

			// FUNCTION: ENGINE 0x101A1ED0
			bool ReactionScriptedSubTypeCondition::SetSubType(const fight::Name& newValue)
			{
				subType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A18F0
			fight::Property* ReactionScriptedSubTypeCondition::GetProperty(int index)
			{
				return gReactionScriptedSubTypeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1910
			void ReactionScriptedSubTypeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionScriptedSubTypeConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A2100
			ReactionScriptedSubTypeCondition::ReactionScriptedSubTypeCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x101A2130
			ReactionScriptedSubTypeCondition::~ReactionScriptedSubTypeCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A5E30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionScriptedSubTypeCondition::RegisterProperties()
			{
				if (gReactionScriptedSubTypeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<ReactionScriptedSubTypeCondition>("subType", &ReactionScriptedSubTypeCondition::SetSubType);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gReactionScriptedSubTypeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3E30
			fight::ConditionFactory* CreateReactionScriptedSubTypeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionScriptedSubTypeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A5410
			void RegisterReactionScriptedSubTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionScriptedSubTypeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitOriginatorIsPlayerConditionProperties;  // 0x11254990

			// FUNCTION: ENGINE 0x101A1980
			fight::Property* ReactionHitOriginatorIsPlayerCondition::GetProperty(int index)
			{
				return gReactionHitOriginatorIsPlayerConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A19A0
			void ReactionHitOriginatorIsPlayerCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitOriginatorIsPlayerConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A19B0
			ReactionHitOriginatorIsPlayerCondition::ReactionHitOriginatorIsPlayerCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x101A19D0
			ReactionHitOriginatorIsPlayerCondition::~ReactionHitOriginatorIsPlayerCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A1920
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitOriginatorIsPlayerCondition::RegisterProperties()
			{
				if (gReactionHitOriginatorIsPlayerConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gReactionHitOriginatorIsPlayerConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3E60
			fight::ConditionFactory* CreateReactionHitOriginatorIsPlayerConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitOriginatorIsPlayerCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A5440
			void RegisterReactionHitOriginatorIsPlayerConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitOriginatorIsPlayerCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionGrabTypeConditionProperties;  // 0x11254994

			// FUNCTION: ENGINE 0x101A12F0
			bool ReactionGrabTypeCondition::SetIsGrabbed(bool newValue)
			{
				isGrabbed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A19E0
			fight::Property* ReactionGrabTypeCondition::GetProperty(int index)
			{
				return gReactionGrabTypeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1A00
			void ReactionGrabTypeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionGrabTypeConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A1A10
			ReactionGrabTypeCondition::ReactionGrabTypeCondition() : fight::Condition(0), isGrabbed(false)
			{
			}

			// FUNCTION: ENGINE 0x101A1A30
			ReactionGrabTypeCondition::~ReactionGrabTypeCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A49C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionGrabTypeCondition::RegisterProperties()
			{
				if (gReactionGrabTypeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ReactionGrabTypeCondition>("isGrabbed", &ReactionGrabTypeCondition::SetIsGrabbed);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gReactionGrabTypeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3E90
			fight::ConditionFactory* CreateReactionGrabTypeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionGrabTypeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A5470
			void RegisterReactionGrabTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionGrabTypeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitSliceAngleConditionProperties;  // 0x11254998

			// FUNCTION: ENGINE 0x101A1300
			bool ReactionHitSliceAngleCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1320
			bool ReactionHitSliceAngleCondition::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1A40
			fight::Property* ReactionHitSliceAngleCondition::GetProperty(int index)
			{
				return gReactionHitSliceAngleConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1A60
			void ReactionHitSliceAngleCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitSliceAngleConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A1A70
			ReactionHitSliceAngleCondition::ReactionHitSliceAngleCondition() : fight::Condition(0), angle(0.0f), arc(0.5235988f)
			{
			}

			// FUNCTION: ENGINE 0x101A1AB0
			ReactionHitSliceAngleCondition::~ReactionHitSliceAngleCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A4A60
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitSliceAngleCondition::RegisterProperties()
			{
				if (gReactionHitSliceAngleConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReactionHitSliceAngleCondition>("angle", &ReactionHitSliceAngleCondition::SetAngle);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitSliceAngleCondition>("arc", &ReactionHitSliceAngleCondition::SetArc);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionHitSliceAngleConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3EC0
			fight::ConditionFactory* CreateReactionHitSliceAngleConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitSliceAngleCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A54A0
			void RegisterReactionHitSliceAngleConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitSliceAngleCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitFromMuscleMassConditionProperties;  // 0x1125499C

			// FUNCTION: ENGINE 0x101A1340
			bool ReactionHitFromMuscleMassCondition::SetMuscleMassActive(bool newValue)
			{
				muscleMassActive = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1AC0
			fight::Property* ReactionHitFromMuscleMassCondition::GetProperty(int index)
			{
				return gReactionHitFromMuscleMassConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1AE0
			void ReactionHitFromMuscleMassCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitFromMuscleMassConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A1AF0
			ReactionHitFromMuscleMassCondition::ReactionHitFromMuscleMassCondition() : fight::Condition(0), muscleMassActive(true)
			{
			}

			// FUNCTION: ENGINE 0x101A1B10
			ReactionHitFromMuscleMassCondition::~ReactionHitFromMuscleMassCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A4B40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitFromMuscleMassCondition::RegisterProperties()
			{
				if (gReactionHitFromMuscleMassConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ReactionHitFromMuscleMassCondition>("muscleMassActive", &ReactionHitFromMuscleMassCondition::SetMuscleMassActive);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gReactionHitFromMuscleMassConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3EF0
			fight::ConditionFactory* CreateReactionHitFromMuscleMassConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitFromMuscleMassCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A54D0
			void RegisterReactionHitFromMuscleMassConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitFromMuscleMassCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitCollisionFlagConditionProperties;  // 0x112549A0

			// FUNCTION: ENGINE 0x101A1EF0
			bool ReactionHitCollisionFlagCondition::SetCollisionFlag(const fight::Name& newValue)
			{
				collisionFlag = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1350
			bool ReactionHitCollisionFlagCondition::SetDoesMatch(bool newValue)
			{
				doesMatch = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1B20
			fight::Property* ReactionHitCollisionFlagCondition::GetProperty(int index)
			{
				return gReactionHitCollisionFlagConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1B40
			void ReactionHitCollisionFlagCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitCollisionFlagConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A2200
			ReactionHitCollisionFlagCondition::ReactionHitCollisionFlagCondition() : fight::Condition(0), doesMatch(true)
			{
			}

			// FUNCTION: ENGINE 0x101A2230
			ReactionHitCollisionFlagCondition::~ReactionHitCollisionFlagCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A5ED0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitCollisionFlagCondition::RegisterProperties()
			{
				if (gReactionHitCollisionFlagConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<ReactionHitCollisionFlagCondition>("collisionFlag", &ReactionHitCollisionFlagCondition::SetCollisionFlag);
					properties[0] = property;
					property = new fight::PropertyBool<ReactionHitCollisionFlagCondition>("doesMatch", &ReactionHitCollisionFlagCondition::SetDoesMatch);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionHitCollisionFlagConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3F20
			fight::ConditionFactory* CreateReactionHitCollisionFlagConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitCollisionFlagCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A5500
			void RegisterReactionHitCollisionFlagConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitCollisionFlagCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionThrowHitTypeConditionProperties;  // 0x112549A4

			// FUNCTION: ENGINE 0x101A1360
			bool ReactionThrowHitTypeCondition::SetDoesMatch(bool newValue)
			{
				doesMatch = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1F10
			bool ReactionThrowHitTypeCondition::SetHitType(const fight::Name& newValue)
			{
				hitType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1B50
			fight::Property* ReactionThrowHitTypeCondition::GetProperty(int index)
			{
				return gReactionThrowHitTypeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1B70
			void ReactionThrowHitTypeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionThrowHitTypeConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A2240
			ReactionThrowHitTypeCondition::ReactionThrowHitTypeCondition() : fight::Condition(0), doesMatch(true)
			{
			}

			// FUNCTION: ENGINE 0x101A2270
			ReactionThrowHitTypeCondition::~ReactionThrowHitTypeCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A5FB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionThrowHitTypeCondition::RegisterProperties()
			{
				if (gReactionThrowHitTypeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ReactionThrowHitTypeCondition>("doesMatch", &ReactionThrowHitTypeCondition::SetDoesMatch);
					properties[0] = property;
					property = new fight::PropertyNameList<ReactionThrowHitTypeCondition>("hitType", &ReactionThrowHitTypeCondition::SetHitType);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionThrowHitTypeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3F50
			fight::ConditionFactory* CreateReactionThrowHitTypeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionThrowHitTypeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A5530
			void RegisterReactionThrowHitTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionThrowHitTypeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitImpulseConditionProperties;  // 0x112549A8

			// FUNCTION: ENGINE 0x101A1370
			bool ReactionHitImpulseCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1380
			bool ReactionHitImpulseCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1390
			bool ReactionHitImpulseCondition::SetImpulse(float newValue)
			{
				impulse = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1B80
			fight::Property* ReactionHitImpulseCondition::GetProperty(int index)
			{
				return gReactionHitImpulseConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1BA0
			void ReactionHitImpulseCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitImpulseConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A1BB0
			ReactionHitImpulseCondition::ReactionHitImpulseCondition() : fight::Condition(0), impulse(0.0f), compare(0), direction(0)
			{
			}

			// FUNCTION: ENGINE 0x101A1BF0
			ReactionHitImpulseCondition::~ReactionHitImpulseCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A4BE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitImpulseCondition::RegisterProperties()
			{
				if (gReactionHitImpulseConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ReactionHitImpulseCondition>("direction", gCrowdPositionConditionDirectionTable, gCrowdPositionConditionDirectionCount, &ReactionHitImpulseCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<ReactionHitImpulseCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ReactionHitImpulseCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitImpulseCondition>("impulse", &ReactionHitImpulseCondition::SetImpulse);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gReactionHitImpulseConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3F80
			fight::ConditionFactory* CreateReactionHitImpulseConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitImpulseCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A5560
			void RegisterReactionHitImpulseConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitImpulseCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitDamageTypeConditionProperties;  // 0x112549AC

			// FUNCTION: ENGINE 0x101A13B0
			bool ReactionHitDamageTypeCondition::SetDoesMatch(bool newValue)
			{
				doesMatch = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A13C0
			bool ReactionHitDamageTypeCondition::SetDamageType(int newValue)
			{
				damageType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1C00
			fight::Property* ReactionHitDamageTypeCondition::GetProperty(int index)
			{
				return gReactionHitDamageTypeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1C20
			void ReactionHitDamageTypeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitDamageTypeConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A1C30
			ReactionHitDamageTypeCondition::ReactionHitDamageTypeCondition() : fight::Condition(0), damageType(0), doesMatch(true)
			{
			}

			// FUNCTION: ENGINE 0x101A1C60
			ReactionHitDamageTypeCondition::~ReactionHitDamageTypeCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A4D20
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitDamageTypeCondition::RegisterProperties()
			{
				if (gReactionHitDamageTypeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ReactionHitDamageTypeCondition>("doesMatch", &ReactionHitDamageTypeCondition::SetDoesMatch);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<ReactionHitDamageTypeCondition>("damageType", gDevastatorTargetHitTrackDamageTypeTable, gDevastatorTargetHitTrackDamageTypeCount, &ReactionHitDamageTypeCondition::SetDamageType);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionHitDamageTypeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3FB0
			fight::ConditionFactory* CreateReactionHitDamageTypeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitDamageTypeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A5590
			void RegisterReactionHitDamageTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitDamageTypeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitImpulseDirectionConditionProperties;  // 0x112549B0

			// FUNCTION: ENGINE 0x101A13D0
			bool ReactionHitImpulseDirectionCondition::SetDirection(float newValue)
			{
				direction = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101A13F0
			bool ReactionHitImpulseDirectionCondition::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1C70
			fight::Property* ReactionHitImpulseDirectionCondition::GetProperty(int index)
			{
				return gReactionHitImpulseDirectionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1C90
			void ReactionHitImpulseDirectionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitImpulseDirectionConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A1CA0
			ReactionHitImpulseDirectionCondition::ReactionHitImpulseDirectionCondition() : fight::Condition(0), arc(1.5707964f), direction(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x101A1CE0
			ReactionHitImpulseDirectionCondition::~ReactionHitImpulseDirectionCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A4E10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitImpulseDirectionCondition::RegisterProperties()
			{
				if (gReactionHitImpulseDirectionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReactionHitImpulseDirectionCondition>("direction", &ReactionHitImpulseDirectionCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitImpulseDirectionCondition>("arc", &ReactionHitImpulseDirectionCondition::SetArc);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionHitImpulseDirectionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A3FE0
			fight::ConditionFactory* CreateReactionHitImpulseDirectionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitImpulseDirectionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A55C0
			void RegisterReactionHitImpulseDirectionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitImpulseDirectionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionTargetConditionProperties;  // 0x112549B4

			// FUNCTION: ENGINE 0x101A1410
			bool ReactionTargetCondition::SetDoesMatch(bool newValue)
			{
				doesMatch = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1CF0
			fight::Property* ReactionTargetCondition::GetProperty(int index)
			{
				return gReactionTargetConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1D10
			void ReactionTargetCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionTargetConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A1D20
			ReactionTargetCondition::ReactionTargetCondition() : fight::Condition(0), doesMatch(true)
			{
			}

			// FUNCTION: ENGINE 0x101A1D40
			ReactionTargetCondition::~ReactionTargetCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A4EF0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionTargetCondition::RegisterProperties()
			{
				if (gReactionTargetConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ReactionTargetCondition>("doesMatch", &ReactionTargetCondition::SetDoesMatch);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gReactionTargetConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A4010
			fight::ConditionFactory* CreateReactionTargetConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionTargetCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A55F0
			void RegisterReactionTargetConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionTargetCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitAttackTypeConditionProperties;  // 0x112549B8

			// FUNCTION: ENGINE 0x101A1420
			bool ReactionHitAttackTypeCondition::SetDoesMatch(bool newValue)
			{
				doesMatch = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1430
			bool ReactionHitAttackTypeCondition::SetAttackType(int newValue)
			{
				attackType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1D50
			fight::Property* ReactionHitAttackTypeCondition::GetProperty(int index)
			{
				return gReactionHitAttackTypeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1D70
			void ReactionHitAttackTypeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitAttackTypeConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A1D80
			ReactionHitAttackTypeCondition::ReactionHitAttackTypeCondition() : fight::Condition(0), attackType(0), doesMatch(true)
			{
			}

			// FUNCTION: ENGINE 0x101A1DB0
			ReactionHitAttackTypeCondition::~ReactionHitAttackTypeCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A4F90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitAttackTypeCondition::RegisterProperties()
			{
				if (gReactionHitAttackTypeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ReactionHitAttackTypeCondition>("doesMatch", &ReactionHitAttackTypeCondition::SetDoesMatch);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<ReactionHitAttackTypeCondition>("attackType", gTendrilDevastatorTrackAttackTypeTable, gTendrilDevastatorTrackAttackTypeCount, &ReactionHitAttackTypeCondition::SetAttackType);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionHitAttackTypeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A4040
			fight::ConditionFactory* CreateReactionHitAttackTypeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitAttackTypeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A5620
			void RegisterReactionHitAttackTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitAttackTypeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitHeightConditionProperties;  // 0x112549BC

			// FUNCTION: ENGINE 0x101A1440
			bool ReactionHitHeightCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1450
			bool ReactionHitHeightCondition::SetHeight(float newValue)
			{
				height = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1DC0
			fight::Property* ReactionHitHeightCondition::GetProperty(int index)
			{
				return gReactionHitHeightConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1DE0
			void ReactionHitHeightCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitHeightConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A1DF0
			ReactionHitHeightCondition::ReactionHitHeightCondition() : fight::Condition(0), height(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101A1E20
			ReactionHitHeightCondition::~ReactionHitHeightCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A5080
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitHeightCondition::RegisterProperties()
			{
				if (gReactionHitHeightConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ReactionHitHeightCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ReactionHitHeightCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitHeightCondition>("height", &ReactionHitHeightCondition::SetHeight);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionHitHeightConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A4070
			fight::ConditionFactory* CreateReactionHitHeightConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitHeightCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A5650
			void RegisterReactionHitHeightConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitHeightCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitHitTypeConditionProperties;  // 0x112549C0

			// FUNCTION: ENGINE 0x101A1470
			bool ReactionHitHitTypeCondition::SetDoesMatch(bool newValue)
			{
				doesMatch = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1F30
			bool ReactionHitHitTypeCondition::SetHitType(const fight::Name& newValue)
			{
				hitType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1E30
			fight::Property* ReactionHitHitTypeCondition::GetProperty(int index)
			{
				return gReactionHitHitTypeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1E50
			void ReactionHitHitTypeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitHitTypeConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A23A0
			ReactionHitHitTypeCondition::ReactionHitHitTypeCondition() : fight::Condition(0), doesMatch(true)
			{
			}

			// FUNCTION: ENGINE 0x101A23D0
			ReactionHitHitTypeCondition::~ReactionHitHitTypeCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A6090
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitHitTypeCondition::RegisterProperties()
			{
				if (gReactionHitHitTypeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ReactionHitHitTypeCondition>("doesMatch", &ReactionHitHitTypeCondition::SetDoesMatch);
					properties[0] = property;
					property = new fight::PropertyNameList<ReactionHitHitTypeCondition>("hitType", &ReactionHitHitTypeCondition::SetHitType);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionHitHitTypeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A40A0
			fight::ConditionFactory* CreateReactionHitHitTypeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitHitTypeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A5680
			void RegisterReactionHitHitTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitHitTypeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionHitImpulseYAngleConditionProperties;  // 0x112549C4

			// FUNCTION: ENGINE 0x101A1480
			bool ReactionHitImpulseYAngleCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1490
			bool ReactionHitImpulseYAngleCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101A1E60
			fight::Property* ReactionHitImpulseYAngleCondition::GetProperty(int index)
			{
				return gReactionHitImpulseYAngleConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A1E80
			void ReactionHitImpulseYAngleCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitImpulseYAngleConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A1E90
			ReactionHitImpulseYAngleCondition::ReactionHitImpulseYAngleCondition() : fight::Condition(0), angle(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101A1EC0
			ReactionHitImpulseYAngleCondition::~ReactionHitImpulseYAngleCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A5170
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitImpulseYAngleCondition::RegisterProperties()
			{
				if (gReactionHitImpulseYAngleConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ReactionHitImpulseYAngleCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ReactionHitImpulseYAngleCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitImpulseYAngleCondition>("angle", &ReactionHitImpulseYAngleCondition::SetAngle);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionHitImpulseYAngleConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A40D0
			fight::ConditionFactory* CreateReactionHitImpulseYAngleConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitImpulseYAngleCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A56B0
			void RegisterReactionHitImpulseYAngleConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionHitImpulseYAngleCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<ReactionEventConditionGroupCondition>;
			template class fight::PropertyConditionGroup<ReactionEventConditionGroupCondition>;
			template class fight::ConditionFactoryTemplate<ReactionEventConditionGroupCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionEventConditionGroupCondition>;
			template class fight::PropertyEnumConstList<ReactionHitCollisionPositionCondition>;
			template class fight::PropertyFloatConstRange<ReactionHitCollisionPositionCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitCollisionPositionCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitCollisionPositionCondition>;
			template class fight::PropertyEnumConstList<ReactionHitDamageCondition>;
			template class fight::PropertyFloatConstRange<ReactionHitDamageCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitDamageCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitDamageCondition>;
			template class fight::PropertyEnumConstList<ReactionHitChargeCondition>;
			template class fight::PropertyFloatConstRange<ReactionHitChargeCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitChargeCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitChargeCondition>;
			template class fight::PropertyEnumConstList<ReactionHitOriginatorDistanceCondition>;
			template class fight::PropertyFloatConstRange<ReactionHitOriginatorDistanceCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitOriginatorDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitOriginatorDistanceCondition>;
			template class fight::PropertyBool<ReactionReceiverIsTargetCondition>;
			template class fight::ConditionFactoryTemplate<ReactionReceiverIsTargetCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionReceiverIsTargetCondition>;
			template class fight::PropertyEnumConstList<ReactionGiverIsBeingGrabbedCondition>;
			template class fight::ConditionFactoryTemplate<ReactionGiverIsBeingGrabbedCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionGiverIsBeingGrabbedCondition>;
			template class fight::PropertyBool<ReactionEventCondition>;
			template class fight::PropertyEnumConstList<ReactionEventCondition>;
			template class fight::ConditionFactoryTemplate<ReactionEventCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionEventCondition>;
			template class fight::PropertyVector<ReactionHitCollisionNormalCondition>;
			template class fight::PropertyFloatConstRange<ReactionHitCollisionNormalCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitCollisionNormalCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitCollisionNormalCondition>;
			template class fight::PropertyName<ReactionScriptedSubTypeCondition>;
			template class fight::ConditionFactoryTemplate<ReactionScriptedSubTypeCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionScriptedSubTypeCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitOriginatorIsPlayerCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitOriginatorIsPlayerCondition>;
			template class fight::PropertyBool<ReactionGrabTypeCondition>;
			template class fight::ConditionFactoryTemplate<ReactionGrabTypeCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionGrabTypeCondition>;
			template class fight::PropertyFloatConstRange<ReactionHitSliceAngleCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitSliceAngleCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitSliceAngleCondition>;
			template class fight::PropertyBool<ReactionHitFromMuscleMassCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitFromMuscleMassCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitFromMuscleMassCondition>;
			template class fight::PropertyName<ReactionHitCollisionFlagCondition>;
			template class fight::PropertyBool<ReactionHitCollisionFlagCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitCollisionFlagCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitCollisionFlagCondition>;
			template class fight::PropertyBool<ReactionThrowHitTypeCondition>;
			template class fight::PropertyNameList<ReactionThrowHitTypeCondition>;
			template class fight::ConditionFactoryTemplate<ReactionThrowHitTypeCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionThrowHitTypeCondition>;
			template class fight::PropertyEnumConstList<ReactionHitImpulseCondition>;
			template class fight::PropertyFloatConstRange<ReactionHitImpulseCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitImpulseCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitImpulseCondition>;
			template class fight::PropertyBool<ReactionHitDamageTypeCondition>;
			template class fight::PropertyEnumConstList<ReactionHitDamageTypeCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitDamageTypeCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitDamageTypeCondition>;
			template class fight::PropertyFloatConstRange<ReactionHitImpulseDirectionCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitImpulseDirectionCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitImpulseDirectionCondition>;
			template class fight::PropertyBool<ReactionTargetCondition>;
			template class fight::ConditionFactoryTemplate<ReactionTargetCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionTargetCondition>;
			template class fight::PropertyBool<ReactionHitAttackTypeCondition>;
			template class fight::PropertyEnumConstList<ReactionHitAttackTypeCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitAttackTypeCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitAttackTypeCondition>;
			template class fight::PropertyEnumConstList<ReactionHitHeightCondition>;
			template class fight::PropertyFloatConstRange<ReactionHitHeightCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitHeightCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitHeightCondition>;
			template class fight::PropertyBool<ReactionHitHitTypeCondition>;
			template class fight::PropertyNameList<ReactionHitHitTypeCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitHitTypeCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitHitTypeCondition>;
			template class fight::PropertyEnumConstList<ReactionHitImpulseYAngleCondition>;
			template class fight::PropertyFloatConstRange<ReactionHitImpulseYAngleCondition>;
			template class fight::ConditionFactoryTemplate<ReactionHitImpulseYAngleCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionHitImpulseYAngleCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101A1F50
// FUNCTION: ENGINE 0x101A1F80
// FUNCTION: ENGINE 0x101A1FB0
// FUNCTION: ENGINE 0x101A1FE0
// FUNCTION: ENGINE 0x101A2010
// FUNCTION: ENGINE 0x101A2040
// FUNCTION: ENGINE 0x101A2070
// FUNCTION: ENGINE 0x101A20A0
// FUNCTION: ENGINE 0x101A20D0
// FUNCTION: ENGINE 0x101A2140
// FUNCTION: ENGINE 0x101A2170
// FUNCTION: ENGINE 0x101A21A0
// FUNCTION: ENGINE 0x101A21D0
// FUNCTION: ENGINE 0x101A2280
// FUNCTION: ENGINE 0x101A22B0
// FUNCTION: ENGINE 0x101A22E0
// FUNCTION: ENGINE 0x101A2310
// FUNCTION: ENGINE 0x101A2340
// FUNCTION: ENGINE 0x101A2370
// FUNCTION: ENGINE 0x101A23E0
// FUNCTION: ENGINE 0x101A2410
// FUNCTION: ENGINE 0x101A2420
// FUNCTION: ENGINE 0x101A2450
// FUNCTION: ENGINE 0x101A2460
// FUNCTION: ENGINE 0x101A2490
// FUNCTION: ENGINE 0x101A24A0
// FUNCTION: ENGINE 0x101A24D0
// FUNCTION: ENGINE 0x101A24E0
// FUNCTION: ENGINE 0x101A2510
// FUNCTION: ENGINE 0x101A2520
// FUNCTION: ENGINE 0x101A2550
// FUNCTION: ENGINE 0x101A2560
// FUNCTION: ENGINE 0x101A2590
// FUNCTION: ENGINE 0x101A25A0
// FUNCTION: ENGINE 0x101A25D0
// FUNCTION: ENGINE 0x101A25E0
// FUNCTION: ENGINE 0x101A2610
// FUNCTION: ENGINE 0x101A2620
// FUNCTION: ENGINE 0x101A2650
// FUNCTION: ENGINE 0x101A2660
// FUNCTION: ENGINE 0x101A2690
// FUNCTION: ENGINE 0x101A26A0
// FUNCTION: ENGINE 0x101A26D0
// FUNCTION: ENGINE 0x101A2700
// FUNCTION: ENGINE 0x101A2720
// FUNCTION: ENGINE 0x101A2770
// FUNCTION: ENGINE 0x101A2780
// FUNCTION: ENGINE 0x101A27B0
// FUNCTION: ENGINE 0x101A27C0
// FUNCTION: ENGINE 0x101A27F0
// FUNCTION: ENGINE 0x101A2800
// FUNCTION: ENGINE 0x101A2830
// FUNCTION: ENGINE 0x101A2840
// FUNCTION: ENGINE 0x101A2870
// FUNCTION: ENGINE 0x101A2880
// FUNCTION: ENGINE 0x101A28B0
// FUNCTION: ENGINE 0x101A28C0
// FUNCTION: ENGINE 0x101A28F0
// FUNCTION: ENGINE 0x101A2900
// FUNCTION: ENGINE 0x101A2930
// FUNCTION: ENGINE 0x101A2940
// FUNCTION: ENGINE 0x101A2970
// FUNCTION: ENGINE 0x101A2980
// FUNCTION: ENGINE 0x101A29B0
// FUNCTION: ENGINE 0x101A29C0
// FUNCTION: ENGINE 0x101A29F0
// FUNCTION: ENGINE 0x101A2A00
// FUNCTION: ENGINE 0x101A2A30
// FUNCTION: ENGINE 0x101A2A40
// FUNCTION: ENGINE 0x101A2A70
// FUNCTION: ENGINE 0x101A2A80
// FUNCTION: ENGINE 0x101A2AB0
// FUNCTION: ENGINE 0x101A2AE0
// FUNCTION: ENGINE 0x101A2B10
// FUNCTION: ENGINE 0x101A2B40
// FUNCTION: ENGINE 0x101A2B70
// FUNCTION: ENGINE 0x101A2BB0
// FUNCTION: ENGINE 0x101A2BC0
// FUNCTION: ENGINE 0x101A2BF0
// FUNCTION: ENGINE 0x101A2C10
// FUNCTION: ENGINE 0x101A2C20
// FUNCTION: ENGINE 0x101A2C50
// FUNCTION: ENGINE 0x101A2C70
// FUNCTION: ENGINE 0x101A2CB0
// FUNCTION: ENGINE 0x101A2CC0
// FUNCTION: ENGINE 0x101A2CF0
// FUNCTION: ENGINE 0x101A2D10
// FUNCTION: ENGINE 0x101A2D20
// FUNCTION: ENGINE 0x101A2D50
// FUNCTION: ENGINE 0x101A2D80
// FUNCTION: ENGINE 0x101A2D90
// FUNCTION: ENGINE 0x101A2DD0
// FUNCTION: ENGINE 0x101A2DE0
// FUNCTION: ENGINE 0x101A2E10
// FUNCTION: ENGINE 0x101A2E30
// FUNCTION: ENGINE 0x101A2E40
// FUNCTION: ENGINE 0x101A2E70
// FUNCTION: ENGINE 0x101A2EA0
// FUNCTION: ENGINE 0x101A2EB0
// FUNCTION: ENGINE 0x101A2EF0
// FUNCTION: ENGINE 0x101A2F00
// FUNCTION: ENGINE 0x101A2F30
// FUNCTION: ENGINE 0x101A2F50
// FUNCTION: ENGINE 0x101A2F60
// FUNCTION: ENGINE 0x101A2F90
// FUNCTION: ENGINE 0x101A2FC0
// FUNCTION: ENGINE 0x101A2FD0
// FUNCTION: ENGINE 0x101A3010
// FUNCTION: ENGINE 0x101A3020
// FUNCTION: ENGINE 0x101A3050
// FUNCTION: ENGINE 0x101A3070
// FUNCTION: ENGINE 0x101A3080
// FUNCTION: ENGINE 0x101A30B0
// FUNCTION: ENGINE 0x101A30E0
// FUNCTION: ENGINE 0x101A30F0
// FUNCTION: ENGINE 0x101A3120
// FUNCTION: ENGINE 0x101A3140
// FUNCTION: ENGINE 0x101A3150
// FUNCTION: ENGINE 0x101A3190
// FUNCTION: ENGINE 0x101A31A0
// FUNCTION: ENGINE 0x101A31D0
// FUNCTION: ENGINE 0x101A31F0
// FUNCTION: ENGINE 0x101A3200
// FUNCTION: ENGINE 0x101A3230
// FUNCTION: ENGINE 0x101A3250
// FUNCTION: ENGINE 0x101A3260
// FUNCTION: ENGINE 0x101A32A0
// FUNCTION: ENGINE 0x101A32B0
// FUNCTION: ENGINE 0x101A32E0
// FUNCTION: ENGINE 0x101A3300
// FUNCTION: ENGINE 0x101A3310
// FUNCTION: ENGINE 0x101A3340
// FUNCTION: ENGINE 0x101A3360
// FUNCTION: ENGINE 0x101A3370
// FUNCTION: ENGINE 0x101A33A0
// FUNCTION: ENGINE 0x101A33D0
// FUNCTION: ENGINE 0x101A33E0
// FUNCTION: ENGINE 0x101A3410
// FUNCTION: ENGINE 0x101A3430
// FUNCTION: ENGINE 0x101A3440
// FUNCTION: ENGINE 0x101A3470
// FUNCTION: ENGINE 0x101A34A0
// FUNCTION: ENGINE 0x101A34B0
// FUNCTION: ENGINE 0x101A34E0
// FUNCTION: ENGINE 0x101A3500
// FUNCTION: ENGINE 0x101A3510
// FUNCTION: ENGINE 0x101A3540
// FUNCTION: ENGINE 0x101A3560
// FUNCTION: ENGINE 0x101A3570
// FUNCTION: ENGINE 0x101A35A0
// FUNCTION: ENGINE 0x101A35C0
// FUNCTION: ENGINE 0x101A35D0
// FUNCTION: ENGINE 0x101A3610
// FUNCTION: ENGINE 0x101A3620
// FUNCTION: ENGINE 0x101A3650
// FUNCTION: ENGINE 0x101A3670
// FUNCTION: ENGINE 0x101A3680
// FUNCTION: ENGINE 0x101A36B0
// FUNCTION: ENGINE 0x101A36E0
// FUNCTION: ENGINE 0x101A36F0
// FUNCTION: ENGINE 0x101A3720
// FUNCTION: ENGINE 0x101A3740
// FUNCTION: ENGINE 0x101A3750
// FUNCTION: ENGINE 0x101A3790
// FUNCTION: ENGINE 0x101A37A0
// FUNCTION: ENGINE 0x101A37D0
// FUNCTION: ENGINE 0x101A37F0
// FUNCTION: ENGINE 0x101A3800
// FUNCTION: ENGINE 0x101A3830
// FUNCTION: ENGINE 0x101A3860
// FUNCTION: ENGINE 0x101A3870
// FUNCTION: ENGINE 0x101A38A0
// FUNCTION: ENGINE 0x101A38C0
// FUNCTION: ENGINE 0x101A38D0
// FUNCTION: ENGINE 0x101A3900
// FUNCTION: ENGINE 0x101A3920
// FUNCTION: ENGINE 0x101A3930
// FUNCTION: ENGINE 0x101A3970
// FUNCTION: ENGINE 0x101A3980
// FUNCTION: ENGINE 0x101A39B0
// FUNCTION: ENGINE 0x101A39D0
// FUNCTION: ENGINE 0x101A39E0
// FUNCTION: ENGINE 0x101A3A20
// FUNCTION: ENGINE 0x101A3A30
// FUNCTION: ENGINE 0x101A3A60
// FUNCTION: ENGINE 0x101A3A80
// FUNCTION: ENGINE 0x101A3A90
// FUNCTION: ENGINE 0x101A3AC0
// FUNCTION: ENGINE 0x101A3AF0
// FUNCTION: ENGINE 0x101A3B00
// FUNCTION: ENGINE 0x101A3B30
// FUNCTION: ENGINE 0x101A3B50
// FUNCTION: ENGINE 0x101A3B60
// FUNCTION: ENGINE 0x101A3BA0
// FUNCTION: ENGINE 0x101A3BB0
// FUNCTION: ENGINE 0x101A3BE0
// FUNCTION: ENGINE 0x101A3C00
// FUNCTION: ENGINE 0x101A3C10
// FUNCTION: ENGINE 0x101A3C40
// FUNCTION: ENGINE 0x101A3C70
// FUNCTION: ENGINE 0x101A56E0
// FUNCTION: ENGINE 0x101A5710
// FUNCTION: ENGINE 0x101A5730
// FUNCTION: ENGINE 0x101A5760
// FUNCTION: ENGINE 0x101A5780
// FUNCTION: ENGINE 0x101A57B0
// FUNCTION: ENGINE 0x101A57D0
// FUNCTION: ENGINE 0x101A57E0
// FUNCTION: ENGINE 0x101A5810
// FUNCTION: ENGINE 0x101A5830
// FUNCTION: ENGINE 0x101A5840
// FUNCTION: ENGINE 0x101A5870
// FUNCTION: ENGINE 0x101A5890
// FUNCTION: ENGINE 0x101A58C0
// FUNCTION: ENGINE 0x101A58E0
// FUNCTION: ENGINE 0x101A5910
// FUNCTION: ENGINE 0x101A5930
// FUNCTION: ENGINE 0x101A5960
// FUNCTION: ENGINE 0x101A5980
// FUNCTION: ENGINE 0x101A59B0
// FUNCTION: ENGINE 0x101A59D0
// FUNCTION: ENGINE 0x101A5A00
// FUNCTION: ENGINE 0x101A5A20
// FUNCTION: ENGINE 0x101A5A50
// FUNCTION: ENGINE 0x101A5A70
// FUNCTION: ENGINE 0x101A5AA0
// FUNCTION: ENGINE 0x101A5AC0
// FUNCTION: ENGINE 0x101A5AF0
// FUNCTION: ENGINE 0x101A5B10
// FUNCTION: ENGINE 0x101A5B40
// FUNCTION: ENGINE 0x101A5B60
// FUNCTION: ENGINE 0x101A5B90
// FUNCTION: ENGINE 0x101A5BB0
// FUNCTION: ENGINE 0x101A5BE0
// FUNCTION: ENGINE 0x101A5C00
// FUNCTION: ENGINE 0x101A5C30
// FUNCTION: ENGINE 0x101A5C50
// FUNCTION: ENGINE 0x101A5C80
// FUNCTION: ENGINE 0x101A5CA0
// FUNCTION: ENGINE 0x101A5CD0
// FUNCTION: ENGINE 0x101A5CF0
// FUNCTION: ENGINE 0x101A5D20
// FUNCTION: ENGINE 0x101A5D40
// FUNCTION: ENGINE 0x101A5D70
// FUNCTION: ENGINE 0x101A5D90
// FUNCTION: ENGINE 0x101A5DC0
// FUNCTION: ENGINE 0x101A5DE0
// FUNCTION: ENGINE 0x101A5E10
// FUNCTION: ENGINE 0x101A6170
// FUNCTION: ENGINE 0x101A61C0
// FUNCTION: ENGINE 0x101A6210
// FUNCTION: ENGINE 0x101A6260
// FUNCTION: ENGINE 0x101A62B0
// FUNCTION: ENGINE 0x101A6300
// FUNCTION: ENGINE 0x101A6350
// FUNCTION: ENGINE 0x101A63A0
// FUNCTION: ENGINE 0x101A63F0
// FUNCTION: ENGINE 0x101A6440
// FUNCTION: ENGINE 0x101A6490
// FUNCTION: ENGINE 0x101A64E0
// FUNCTION: ENGINE 0x101A6530
// FUNCTION: ENGINE 0x101A6580
// FUNCTION: ENGINE 0x101A65D0
// FUNCTION: ENGINE 0x101A6620
// FUNCTION: ENGINE 0x101A6670
// FUNCTION: ENGINE 0x101A66C0
// FUNCTION: ENGINE 0x101A6710
// FUNCTION: ENGINE 0x101A6760
// FUNCTION: ENGINE 0x101A6790
// FUNCTION: ENGINE 0x101A67B0
// FUNCTION: ENGINE 0x101A67E0
// FUNCTION: ENGINE 0x101A6800
// FUNCTION: ENGINE 0x101A6830
// FUNCTION: ENGINE 0x101A6850
// FUNCTION: ENGINE 0x101A6880
// FUNCTION: ENGINE 0x101A68A0
// FUNCTION: ENGINE 0x101A68F0
// FUNCTION: ENGINE 0x101A6940
// FUNCTION: ENGINE 0x101A6990
