// Fight items of the ai group: TargetHasLoFCondition, HaveTokenCondition, DestinationTargetDistanceCondition, InfectedAlertedCondition, TargetHasLoFDistanceCondition, FloatShotAllowedCondition, InTargetsCameraCondition, ShouldRadioHQCondition, TargetIsHumanCondition, AnyPlayerDistanceCondition, AimingAtCondition, FacingAngleTargetCondition, HaveStrafeRunTokenCondition, AimingAtTargetCondition, TargetBeingHeldCondition, RefreshStrafeRunTokenTrack, ActionTrack, RequestTokenTrack, CombatDestinationFindTrack, CombatDestinationTransmitTrack, DrawDebugTrack, TargetTokenBoostTrack (unit 0x1021E550 - 0x10225F80; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_token.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			extern const int gCombatDestinationFindTrackInitialHeuristicMembers[];  // 0x110469B4

			fight::Property** gTargetHasLoFConditionProperties;  // 0x11255840

			// FUNCTION: ENGINE 0x1021E550
			bool TargetHasLoFCondition::SetTimeTolerance(float newValue)
			{
				timeTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E570
			bool TargetHasLoFCondition::SetDistanceTolerance(float newValue)
			{
				distanceTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E590
			bool TargetHasLoFCondition::SetCollisionFlags(int newValue)
			{
				collisionFlags = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E5A0
			bool TargetHasLoFCondition::SetCollideWithType(int newValue)
			{
				collideWithType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E5B0
			bool TargetHasLoFCondition::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E5D0
			bool TargetHasLoFCondition::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F060
			fight::Property* TargetHasLoFCondition::GetProperty(int index)
			{
				return gTargetHasLoFConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F080
			void TargetHasLoFCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetHasLoFConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021F090
			TargetHasLoFCondition::TargetHasLoFCondition() : fight::Condition(0), offset(0.0f, 0.0f, 0.0f), distanceTolerance(2.0f), radius(0.2f), timeTolerance(0.5f), collisionFlags(0), collideWithType(motion::gCollisionHitTrackCollideWithDefault)
			{
			}

			// FUNCTION: ENGINE 0x1021F110
			TargetHasLoFCondition::~TargetHasLoFCondition()
			{
			}

			// FUNCTION: ENGINE 0x10222880
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetHasLoFCondition::RegisterProperties()
			{
				if (gTargetHasLoFConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TargetHasLoFCondition>("timeTolerance", &TargetHasLoFCondition::SetTimeTolerance);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TargetHasLoFCondition>("distanceTolerance", &TargetHasLoFCondition::SetDistanceTolerance);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<TargetHasLoFCondition>("collisionFlags", gTargetHasLoFConditionCollisionFlagsTable, gTargetHasLoFConditionCollisionFlagsCount, &TargetHasLoFCondition::SetCollisionFlags);
					properties[2] = property;
					property = new fight::PropertyBitfieldConstList<TargetHasLoFCondition>("collideWithType", motion::gDetectObbCollisionConditionCollideWithTable, motion::gDetectObbCollisionConditionCollideWithCount, &TargetHasLoFCondition::SetCollideWithType);
					properties[3] = property;
					property = new fight::PropertyVector<TargetHasLoFCondition>("offset", &TargetHasLoFCondition::SetOffset);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<TargetHasLoFCondition>("radius", &TargetHasLoFCondition::SetRadius);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gTargetHasLoFConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10222460
			fight::ConditionFactory* CreateTargetHasLoFConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetHasLoFCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10223DA0
			void RegisterTargetHasLoFConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetHasLoFCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHaveTokenConditionProperties;  // 0x11255844

			// FUNCTION: ENGINE 0x1021E5F0
			bool HaveTokenCondition::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E600
			bool HaveTokenCondition::SetOwner(int newValue)
			{
				owner = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F120
			fight::Property* HaveTokenCondition::GetProperty(int index)
			{
				return gHaveTokenConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F140
			void HaveTokenCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHaveTokenConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021F150
			HaveTokenCondition::HaveTokenCondition() : fight::Condition(0), owner(0), type(0)
			{
			}

			// FUNCTION: ENGINE 0x1021F180
			HaveTokenCondition::~HaveTokenCondition()
			{
			}

			// FUNCTION: ENGINE 0x10222A80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HaveTokenCondition::RegisterProperties()
			{
				if (gHaveTokenConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<HaveTokenCondition>("type", gHaveTokenConditionTypeTable, gHaveTokenConditionTypeCount, &HaveTokenCondition::SetType);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<HaveTokenCondition>("owner", gHaveTokenConditionOwnerTable, gHaveTokenConditionOwnerCount, &HaveTokenCondition::SetOwner);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gHaveTokenConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10222490
			fight::ConditionFactory* CreateHaveTokenConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HaveTokenCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10223DD0
			void RegisterHaveTokenConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HaveTokenCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDestinationTargetDistanceConditionProperties;  // 0x11255848

			// FUNCTION: ENGINE 0x1021E610
			bool DestinationTargetDistanceCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E620
			bool DestinationTargetDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E630
			bool DestinationTargetDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E650
			bool DestinationTargetDistanceCondition::SetUseParams(bool newValue)
			{
				useParams = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F190
			fight::Property* DestinationTargetDistanceCondition::GetProperty(int index)
			{
				return gDestinationTargetDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F1B0
			void DestinationTargetDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDestinationTargetDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021F1C0
			DestinationTargetDistanceCondition::DestinationTargetDistanceCondition() : fight::Condition(0), distance(2e+01f), compare(4), direction(0), useParams(false)
			{
			}

			// FUNCTION: ENGINE 0x1021F200
			DestinationTargetDistanceCondition::~DestinationTargetDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x10222B80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DestinationTargetDistanceCondition::RegisterProperties()
			{
				if (gDestinationTargetDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<DestinationTargetDistanceCondition>("direction", motion::gCrowdPositionConditionDirectionTable, motion::gCrowdPositionConditionDirectionCount, &DestinationTargetDistanceCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<DestinationTargetDistanceCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &DestinationTargetDistanceCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DestinationTargetDistanceCondition>("distance", &DestinationTargetDistanceCondition::SetDistance);
					properties[2] = property;
					property = new fight::PropertyBool<DestinationTargetDistanceCondition>("useParams", &DestinationTargetDistanceCondition::SetUseParams);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gDestinationTargetDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102224C0
			fight::ConditionFactory* CreateDestinationTargetDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DestinationTargetDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10223E00
			void RegisterDestinationTargetDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DestinationTargetDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gInfectedAlertedConditionProperties;  // 0x1125584C

			// FUNCTION: ENGINE 0x1021E660
			bool InfectedAlertedCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E670
			bool InfectedAlertedCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E680
			bool InfectedAlertedCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E6A0
			bool InfectedAlertedCondition::SetTargetingMe(bool newValue)
			{
				targetingMe = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E6B0
			bool InfectedAlertedCondition::SetRequireToughGuy(bool newValue)
			{
				requireToughGuy = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F210
			fight::Property* InfectedAlertedCondition::GetProperty(int index)
			{
				return gInfectedAlertedConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F230
			void InfectedAlertedCondition::ClearProperties()
			{
				fight::FreePropertyList(&gInfectedAlertedConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021F240
			InfectedAlertedCondition::InfectedAlertedCondition() : fight::Condition(0), distance(5e+01f), compare(4), direction(0), requireToughGuy(false), targetingMe(false)
			{
			}

			// FUNCTION: ENGINE 0x1021F290
			InfectedAlertedCondition::~InfectedAlertedCondition()
			{
			}

			// FUNCTION: ENGINE 0x10222D00
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void InfectedAlertedCondition::RegisterProperties()
			{
				if (gInfectedAlertedConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<InfectedAlertedCondition>("direction", motion::gCrowdPositionConditionDirectionTable, motion::gCrowdPositionConditionDirectionCount, &InfectedAlertedCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<InfectedAlertedCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &InfectedAlertedCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<InfectedAlertedCondition>("distance", &InfectedAlertedCondition::SetDistance);
					properties[2] = property;
					property = new fight::PropertyBool<InfectedAlertedCondition>("targetingMe", &InfectedAlertedCondition::SetTargetingMe);
					properties[3] = property;
					property = new fight::PropertyBool<InfectedAlertedCondition>("requireToughGuy", &InfectedAlertedCondition::SetRequireToughGuy);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gInfectedAlertedConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102224F0
			fight::ConditionFactory* CreateInfectedAlertedConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InfectedAlertedCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10223E30
			void RegisterInfectedAlertedConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InfectedAlertedCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetHasLoFDistanceConditionProperties;  // 0x11255850

			// FUNCTION: ENGINE 0x1021E6C0
			bool TargetHasLoFDistanceCondition::SetTimeTolerance(float newValue)
			{
				timeTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E6E0
			bool TargetHasLoFDistanceCondition::SetDistanceTolerance(float newValue)
			{
				distanceTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E700
			bool TargetHasLoFDistanceCondition::SetCollisionFlags(int newValue)
			{
				collisionFlags = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E710
			bool TargetHasLoFDistanceCondition::SetCollideWithTypeLessThanDist(int newValue)
			{
				collideWithTypeLessThanDist = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E720
			bool TargetHasLoFDistanceCondition::SetCollideWithTypeAnyDist(int newValue)
			{
				collideWithTypeAnyDist = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E730
			bool TargetHasLoFDistanceCondition::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E750
			bool TargetHasLoFDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E760
			bool TargetHasLoFDistanceCondition::SetDistanceFromTargetSqr(float newValue)
			{
				distanceFromTargetSqr = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F2A0
			fight::Property* TargetHasLoFDistanceCondition::GetProperty(int index)
			{
				return gTargetHasLoFDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F2C0
			void TargetHasLoFDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetHasLoFDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021F2D0
			TargetHasLoFDistanceCondition::TargetHasLoFDistanceCondition() : fight::Condition(0), offset(0.0f, 0.0f, 0.0f), distanceFromTargetSqr(0.2f), distanceTolerance(2.0f), timeTolerance(0.5f), collisionFlags(0), compare(4), collideWithTypeAnyDist(motion::gCollisionHitTrackCollideWithDefault), collideWithTypeLessThanDist(motion::gCollisionHitTrackCollideWithDefault)
			{
			}

			// FUNCTION: ENGINE 0x1021F360
			TargetHasLoFDistanceCondition::~TargetHasLoFDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x10222EC0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetHasLoFDistanceCondition::RegisterProperties()
			{
				if (gTargetHasLoFDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TargetHasLoFDistanceCondition>("timeTolerance", &TargetHasLoFDistanceCondition::SetTimeTolerance);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TargetHasLoFDistanceCondition>("distanceTolerance", &TargetHasLoFDistanceCondition::SetDistanceTolerance);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<TargetHasLoFDistanceCondition>("collisionFlags", gTargetHasLoFConditionCollisionFlagsTable, gTargetHasLoFConditionCollisionFlagsCount, &TargetHasLoFDistanceCondition::SetCollisionFlags);
					properties[2] = property;
					property = new fight::PropertyBitfieldConstList<TargetHasLoFDistanceCondition>("collideWithTypeLessThanDist", motion::gDetectObbCollisionConditionCollideWithTable, motion::gDetectObbCollisionConditionCollideWithCount, &TargetHasLoFDistanceCondition::SetCollideWithTypeLessThanDist);
					properties[3] = property;
					property = new fight::PropertyBitfieldConstList<TargetHasLoFDistanceCondition>("collideWithTypeAnyDist", motion::gDetectObbCollisionConditionCollideWithTable, motion::gDetectObbCollisionConditionCollideWithCount, &TargetHasLoFDistanceCondition::SetCollideWithTypeAnyDist);
					properties[4] = property;
					property = new fight::PropertyVector<TargetHasLoFDistanceCondition>("offset", &TargetHasLoFDistanceCondition::SetOffset);
					properties[5] = property;
					property = new fight::PropertyEnumConstList<TargetHasLoFDistanceCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &TargetHasLoFDistanceCondition::SetCompare);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<TargetHasLoFDistanceCondition>("distanceFromTargetSqr", &TargetHasLoFDistanceCondition::SetDistanceFromTargetSqr);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gTargetHasLoFDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10222520
			fight::ConditionFactory* CreateTargetHasLoFDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetHasLoFDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10223E60
			void RegisterTargetHasLoFDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetHasLoFDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gFloatShotAllowedConditionProperties;  // 0x11255854

			// FUNCTION: ENGINE 0x1021F3D0
			fight::Property* FloatShotAllowedCondition::GetProperty(int index)
			{
				return gFloatShotAllowedConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F3F0
			void FloatShotAllowedCondition::ClearProperties()
			{
				fight::FreePropertyList(&gFloatShotAllowedConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021F400
			FloatShotAllowedCondition::FloatShotAllowedCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1021F420
			FloatShotAllowedCondition::~FloatShotAllowedCondition()
			{
			}

			// FUNCTION: ENGINE 0x1021F370
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FloatShotAllowedCondition::RegisterProperties()
			{
				if (gFloatShotAllowedConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gFloatShotAllowedConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10222550
			fight::ConditionFactory* CreateFloatShotAllowedConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FloatShotAllowedCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10223E90
			void RegisterFloatShotAllowedConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FloatShotAllowedCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gInTargetsCameraConditionProperties;  // 0x11255858

			// FUNCTION: ENGINE 0x1021E780
			bool InTargetsCameraCondition::SetSize(float newValue)
			{
				size = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F430
			fight::Property* InTargetsCameraCondition::GetProperty(int index)
			{
				return gInTargetsCameraConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F450
			void InTargetsCameraCondition::ClearProperties()
			{
				fight::FreePropertyList(&gInTargetsCameraConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021F460
			InTargetsCameraCondition::InTargetsCameraCondition() : fight::Condition(0), size(2.0f)
			{
			}

			// FUNCTION: ENGINE 0x1021F490
			InTargetsCameraCondition::~InTargetsCameraCondition()
			{
			}

			// FUNCTION: ENGINE 0x10223160
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void InTargetsCameraCondition::RegisterProperties()
			{
				if (gInTargetsCameraConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<InTargetsCameraCondition>("size", &InTargetsCameraCondition::SetSize);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gInTargetsCameraConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10222580
			fight::ConditionFactory* CreateInTargetsCameraConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InTargetsCameraCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10223EC0
			void RegisterInTargetsCameraConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InTargetsCameraCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gShouldRadioHQConditionProperties;  // 0x1125585C

			// FUNCTION: ENGINE 0x1021E7A0
			bool ShouldRadioHQCondition::SetRadio(bool newValue)
			{
				radio = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F4A0
			fight::Property* ShouldRadioHQCondition::GetProperty(int index)
			{
				return gShouldRadioHQConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F4C0
			void ShouldRadioHQCondition::ClearProperties()
			{
				fight::FreePropertyList(&gShouldRadioHQConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021F4D0
			ShouldRadioHQCondition::ShouldRadioHQCondition() : fight::Condition(0), radio(true)
			{
			}

			// FUNCTION: ENGINE 0x1021F4F0
			ShouldRadioHQCondition::~ShouldRadioHQCondition()
			{
			}

			// FUNCTION: ENGINE 0x10223200
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShouldRadioHQCondition::RegisterProperties()
			{
				if (gShouldRadioHQConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ShouldRadioHQCondition>("radio", &ShouldRadioHQCondition::SetRadio);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gShouldRadioHQConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102225B0
			fight::ConditionFactory* CreateShouldRadioHQConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShouldRadioHQCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10223EF0
			void RegisterShouldRadioHQConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShouldRadioHQCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetIsHumanConditionProperties;  // 0x11255860

			// FUNCTION: ENGINE 0x1021E7B0
			bool TargetIsHumanCondition::SetHuman(bool newValue)
			{
				human = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E7C0
			bool TargetIsHumanCondition::SetCheckPointPeds(bool newValue)
			{
				checkPointPeds = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F500
			fight::Property* TargetIsHumanCondition::GetProperty(int index)
			{
				return gTargetIsHumanConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F520
			void TargetIsHumanCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetIsHumanConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021F530
			TargetIsHumanCondition::TargetIsHumanCondition() : fight::Condition(0), checkPointPeds(false), human(true)
			{
			}

			// FUNCTION: ENGINE 0x1021F560
			TargetIsHumanCondition::~TargetIsHumanCondition()
			{
			}

			// FUNCTION: ENGINE 0x102232A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetIsHumanCondition::RegisterProperties()
			{
				if (gTargetIsHumanConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<TargetIsHumanCondition>("human", &TargetIsHumanCondition::SetHuman);
					properties[0] = property;
					property = new fight::PropertyBool<TargetIsHumanCondition>("checkPointPeds", &TargetIsHumanCondition::SetCheckPointPeds);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gTargetIsHumanConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102225E0
			fight::ConditionFactory* CreateTargetIsHumanConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetIsHumanCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10223F20
			void RegisterTargetIsHumanConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetIsHumanCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gAnyPlayerDistanceConditionProperties;  // 0x11255864

			// FUNCTION: ENGINE 0x1021E7D0
			bool AnyPlayerDistanceCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E7E0
			bool AnyPlayerDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E7F0
			bool AnyPlayerDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E810
			bool AnyPlayerDistanceCondition::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F570
			fight::Property* AnyPlayerDistanceCondition::GetProperty(int index)
			{
				return gAnyPlayerDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F590
			void AnyPlayerDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAnyPlayerDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021F5A0
			AnyPlayerDistanceCondition::AnyPlayerDistanceCondition() : fight::Condition(0), offset(0.0f, 0.0f, 0.0f), distance(2e+01f), compare(4), direction(0)
			{
			}

			// FUNCTION: ENGINE 0x1021F600
			AnyPlayerDistanceCondition::~AnyPlayerDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x10223380
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AnyPlayerDistanceCondition::RegisterProperties()
			{
				if (gAnyPlayerDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<AnyPlayerDistanceCondition>("direction", motion::gCrowdPositionConditionDirectionTable, motion::gCrowdPositionConditionDirectionCount, &AnyPlayerDistanceCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<AnyPlayerDistanceCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &AnyPlayerDistanceCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<AnyPlayerDistanceCondition>("distance", &AnyPlayerDistanceCondition::SetDistance);
					properties[2] = property;
					property = new fight::PropertyVector<AnyPlayerDistanceCondition>("offset", &AnyPlayerDistanceCondition::SetOffset);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gAnyPlayerDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10222610
			fight::ConditionFactory* CreateAnyPlayerDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AnyPlayerDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10223F50
			void RegisterAnyPlayerDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AnyPlayerDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gAimingAtConditionProperties;  // 0x11255868

			// FUNCTION: ENGINE 0x1021FC10
			bool AimingAtCondition::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E830
			bool AimingAtCondition::SetTolerance(float newValue)
			{
				tolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E850
			bool AimingAtCondition::Set3D(bool newValue)
			{
				flag3D = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E860
			bool AimingAtCondition::SetHeading(const math::Vector& newValue)
			{
				heading.x = newValue.x;
				heading.y = newValue.y;
				heading.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E880
			bool AimingAtCondition::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E8A0
			bool AimingAtCondition::SetWhere(int newValue)
			{
				where = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F610
			fight::Property* AimingAtCondition::GetProperty(int index)
			{
				return gAimingAtConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F630
			void AimingAtCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAimingAtConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021FE70
			AimingAtCondition::AimingAtCondition() : fight::Condition(0), heading(0.0f, 0.0f, -1.0f), offset(0.0f, 0.0f, 0.0f), tolerance(0.1f), where(0), flag3D(false)
			{
			}

			// FUNCTION: ENGINE 0x1021FEF0
			AimingAtCondition::~AimingAtCondition()
			{
			}

			// FUNCTION: ENGINE 0x10224870
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AimingAtCondition::RegisterProperties()
			{
				if (gAimingAtConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyNameList<AimingAtCondition>("joint", &AimingAtCondition::SetJoint);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AimingAtCondition>("tolerance", &AimingAtCondition::SetTolerance);
					properties[1] = property;
					property = new fight::PropertyBool<AimingAtCondition>("3D", &AimingAtCondition::Set3D);
					properties[2] = property;
					property = new fight::PropertyVector<AimingAtCondition>("heading", &AimingAtCondition::SetHeading);
					properties[3] = property;
					property = new fight::PropertyVector<AimingAtCondition>("offset", &AimingAtCondition::SetOffset);
					properties[4] = property;
					property = new fight::PropertyEnumConstList<AimingAtCondition>("where", gAimTrackWhereTable, gAimTrackWhereCount, &AimingAtCondition::SetWhere);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gAimingAtConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10222640
			fight::ConditionFactory* CreateAimingAtConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AimingAtCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10223F80
			void RegisterAimingAtConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AimingAtCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gFacingAngleTargetConditionProperties;  // 0x1125586C

			// FUNCTION: ENGINE 0x1021E8B0
			bool FacingAngleTargetCondition::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E8C0
			bool FacingAngleTargetCondition::SetCompareTime(int newValue)
			{
				compareTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E8D0
			bool FacingAngleTargetCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E8F0
			bool FacingAngleTargetCondition::SetSigned(bool newValue)
			{
				signedValue = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F640
			fight::Property* FacingAngleTargetCondition::GetProperty(int index)
			{
				return gFacingAngleTargetConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F660
			void FacingAngleTargetCondition::ClearProperties()
			{
				fight::FreePropertyList(&gFacingAngleTargetConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021F670
			FacingAngleTargetCondition::FacingAngleTargetCondition() : fight::Condition(0), angle(0.0f), compareTime(4), type(0), signedValue(false)
			{
			}

			// FUNCTION: ENGINE 0x1021F6B0
			FacingAngleTargetCondition::~FacingAngleTargetCondition()
			{
			}

			// FUNCTION: ENGINE 0x10223500
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FacingAngleTargetCondition::RegisterProperties()
			{
				if (gFacingAngleTargetConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<FacingAngleTargetCondition>("type", gFacingAngleTargetConditionTypeTable, gFacingAngleTargetConditionTypeCount, &FacingAngleTargetCondition::SetType);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<FacingAngleTargetCondition>("compareTime", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &FacingAngleTargetCondition::SetCompareTime);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FacingAngleTargetCondition>("angle", &FacingAngleTargetCondition::SetAngle);
					properties[2] = property;
					property = new fight::PropertyBool<FacingAngleTargetCondition>("signed", &FacingAngleTargetCondition::SetSigned);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gFacingAngleTargetConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10222670
			fight::ConditionFactory* CreateFacingAngleTargetConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FacingAngleTargetCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10223FB0
			void RegisterFacingAngleTargetConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FacingAngleTargetCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHaveStrafeRunTokenConditionProperties;  // 0x11255870

			// FUNCTION: ENGINE 0x1021E900
			bool HaveStrafeRunTokenCondition::SetRequestIt(bool newValue)
			{
				requestIt = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F6C0
			fight::Property* HaveStrafeRunTokenCondition::GetProperty(int index)
			{
				return gHaveStrafeRunTokenConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F6E0
			void HaveStrafeRunTokenCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHaveStrafeRunTokenConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021F6F0
			HaveStrafeRunTokenCondition::HaveStrafeRunTokenCondition() : fight::Condition(0), requestIt(true)
			{
			}

			// FUNCTION: ENGINE 0x1021F710
			HaveStrafeRunTokenCondition::~HaveStrafeRunTokenCondition()
			{
			}

			// FUNCTION: ENGINE 0x10223680
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HaveStrafeRunTokenCondition::RegisterProperties()
			{
				if (gHaveStrafeRunTokenConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<HaveStrafeRunTokenCondition>("requestIt", &HaveStrafeRunTokenCondition::SetRequestIt);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gHaveStrafeRunTokenConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102226A0
			fight::ConditionFactory* CreateHaveStrafeRunTokenConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HaveStrafeRunTokenCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10223FE0
			void RegisterHaveStrafeRunTokenConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HaveStrafeRunTokenCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gAimingAtTargetConditionProperties;  // 0x11255874

			// FUNCTION: ENGINE 0x1021FC30
			bool AimingAtTargetCondition::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E910
			bool AimingAtTargetCondition::SetTolerance(float newValue)
			{
				tolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E930
			bool AimingAtTargetCondition::Set3D(bool newValue)
			{
				flag3D = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E940
			bool AimingAtTargetCondition::SetHeading(const math::Vector& newValue)
			{
				heading.x = newValue.x;
				heading.y = newValue.y;
				heading.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E960
			bool AimingAtTargetCondition::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F720
			fight::Property* AimingAtTargetCondition::GetProperty(int index)
			{
				return gAimingAtTargetConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F740
			void AimingAtTargetCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAimingAtTargetConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021FF60
			AimingAtTargetCondition::AimingAtTargetCondition() : fight::Condition(0), heading(0.0f, 0.0f, -1.0f), offset(0.0f, 0.0f, 0.0f), tolerance(0.1f), flag3D(false)
			{
			}

			// FUNCTION: ENGINE 0x1021FFD0
			AimingAtTargetCondition::~AimingAtTargetCondition()
			{
			}

			// FUNCTION: ENGINE 0x10224A50
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AimingAtTargetCondition::RegisterProperties()
			{
				if (gAimingAtTargetConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyNameList<AimingAtTargetCondition>("joint", &AimingAtTargetCondition::SetJoint);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AimingAtTargetCondition>("tolerance", &AimingAtTargetCondition::SetTolerance);
					properties[1] = property;
					property = new fight::PropertyBool<AimingAtTargetCondition>("3D", &AimingAtTargetCondition::Set3D);
					properties[2] = property;
					property = new fight::PropertyVector<AimingAtTargetCondition>("heading", &AimingAtTargetCondition::SetHeading);
					properties[3] = property;
					property = new fight::PropertyVector<AimingAtTargetCondition>("offset", &AimingAtTargetCondition::SetOffset);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gAimingAtTargetConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102226D0
			fight::ConditionFactory* CreateAimingAtTargetConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AimingAtTargetCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10224010
			void RegisterAimingAtTargetConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AimingAtTargetCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetBeingHeldConditionProperties;  // 0x11255878

			// FUNCTION: ENGINE 0x1021E980
			bool TargetBeingHeldCondition::SetHeld(bool newValue)
			{
				held = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E990
			bool TargetBeingHeldCondition::SetDontCountIfHeldByMe(bool newValue)
			{
				dontCountIfHeldByMe = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F750
			fight::Property* TargetBeingHeldCondition::GetProperty(int index)
			{
				return gTargetBeingHeldConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F770
			void TargetBeingHeldCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetBeingHeldConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021F780
			TargetBeingHeldCondition::TargetBeingHeldCondition() : fight::Condition(0), dontCountIfHeldByMe(true), held(false)
			{
			}

			// FUNCTION: ENGINE 0x1021F7B0
			TargetBeingHeldCondition::~TargetBeingHeldCondition()
			{
			}

			// FUNCTION: ENGINE 0x10223720
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetBeingHeldCondition::RegisterProperties()
			{
				if (gTargetBeingHeldConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<TargetBeingHeldCondition>("held", &TargetBeingHeldCondition::SetHeld);
					properties[0] = property;
					property = new fight::PropertyBool<TargetBeingHeldCondition>("dontCountIfHeldByMe", &TargetBeingHeldCondition::SetDontCountIfHeldByMe);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gTargetBeingHeldConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10222700
			fight::ConditionFactory* CreateTargetBeingHeldConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetBeingHeldCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10224040
			void RegisterTargetBeingHeldConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetBeingHeldCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gRefreshStrafeRunTokenTrackProperties;  // 0x1125587C

			// FUNCTION: ENGINE 0x1021E9A0
			bool RefreshStrafeRunTokenTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021E9C0
			bool RefreshStrafeRunTokenTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F7C0
			fight::Property* RefreshStrafeRunTokenTrack::GetProperty(int index)
			{
				return gRefreshStrafeRunTokenTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F7E0
			void RefreshStrafeRunTokenTrack::ClearProperties()
			{
				fight::FreePropertyList(&gRefreshStrafeRunTokenTrackProperties);
			}

			// FUNCTION: ENGINE 0x1021F7F0
			RefreshStrafeRunTokenTrack::RefreshStrafeRunTokenTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1021F820
			float RefreshStrafeRunTokenTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1021F830
			float RefreshStrafeRunTokenTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1021F840
			RefreshStrafeRunTokenTrack::~RefreshStrafeRunTokenTrack()
			{
			}

			// FUNCTION: ENGINE 0x10223800
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RefreshStrafeRunTokenTrack::RegisterProperties()
			{
				if (gRefreshStrafeRunTokenTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<RefreshStrafeRunTokenTrack>("timeBegin", &RefreshStrafeRunTokenTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<RefreshStrafeRunTokenTrack>("timeEnd", &RefreshStrafeRunTokenTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gRefreshStrafeRunTokenTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10222730
			fight::TrackFactory* CreateRefreshStrafeRunTokenTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<RefreshStrafeRunTokenTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10224070
			void RegisterRefreshStrafeRunTokenTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<RefreshStrafeRunTokenTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gActionTrackProperties;  // 0x11255880

			// FUNCTION: ENGINE 0x1021E9E0
			bool ActionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EA00
			bool ActionTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EA20
			bool ActionTrack::SetButton(int newValue)
			{
				button = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F850
			fight::Property* ActionTrack::GetProperty(int index)
			{
				return gActionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F870
			void ActionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gActionTrackProperties);
			}

			// FUNCTION: ENGINE 0x1021F880
			ActionTrack::ActionTrack() : timeBegin(0.0f), timeEnd(-1.0f), button(0)
			{
			}

			// FUNCTION: ENGINE 0x1021F8C0
			float ActionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1021F8D0
			float ActionTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1021F8E0
			ActionTrack::~ActionTrack()
			{
			}

			// FUNCTION: ENGINE 0x102238E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ActionTrack::RegisterProperties()
			{
				if (gActionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ActionTrack>("timeBegin", &ActionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ActionTrack>("timeEnd", &ActionTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnum<ActionTrack>("button", &ActionTrack::GetButtonEntry, &ActionTrack::GetButtonCount, &ActionTrack::SetButton);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gActionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10222760
			fight::TrackFactory* CreateActionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ActionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102240A0
			void RegisterActionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ActionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gRequestTokenTrackProperties;  // 0x11255884

			// FUNCTION: ENGINE 0x1021EA30
			bool RequestTokenTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EA50
			bool RequestTokenTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EA70
			bool RequestTokenTrack::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F8F0
			fight::Property* RequestTokenTrack::GetProperty(int index)
			{
				return gRequestTokenTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F910
			void RequestTokenTrack::ClearProperties()
			{
				fight::FreePropertyList(&gRequestTokenTrackProperties);
			}

			// FUNCTION: ENGINE 0x1021F920
			RequestTokenTrack::RequestTokenTrack() : timeBegin(0.0f), timeEnd(-1.0f), type(0)
			{
			}

			// FUNCTION: ENGINE 0x1021F960
			float RequestTokenTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1021F970
			float RequestTokenTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1021F980
			RequestTokenTrack::~RequestTokenTrack()
			{
			}

			// FUNCTION: ENGINE 0x10223A10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RequestTokenTrack::RegisterProperties()
			{
				if (gRequestTokenTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<RequestTokenTrack>("timeBegin", &RequestTokenTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<RequestTokenTrack>("timeEnd", &RequestTokenTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<RequestTokenTrack>("type", gHaveTokenConditionTypeTable, gHaveTokenConditionTypeCount, &RequestTokenTrack::SetType);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gRequestTokenTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10222790
			fight::TrackFactory* CreateRequestTokenTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<RequestTokenTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102240D0
			void RegisterRequestTokenTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<RequestTokenTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gCombatDestinationFindTrackProperties;  // 0x11255888

			// FUNCTION: ENGINE 0x1021EA80
			bool CombatDestinationFindTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EAA0
			bool CombatDestinationFindTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EAC0
			bool CombatDestinationFindTrack::SetMinDistance(float newValue)
			{
				minDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EAE0
			bool CombatDestinationFindTrack::SetMaxDistance(float newValue)
			{
				maxDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EB00
			bool CombatDestinationFindTrack::SetMinAngle(float newValue)
			{
				minAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EB30
			bool CombatDestinationFindTrack::SetMaxAngle(float newValue)
			{
				maxAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EB60
			bool CombatDestinationFindTrack::SetNumTries(int newValue)
			{
				numTries = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EB80
			bool CombatDestinationFindTrack::SetIgnoreRestrictions(bool newValue)
			{
				ignoreRestrictions = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EBA0
			bool CombatDestinationFindTrack::SetCheckNotReserved(bool newValue)
			{
				checkNotReserved = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EBC0
			bool CombatDestinationFindTrack::SetCheckCanGo(bool newValue)
			{
				checkCanGo = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EBE0
			bool CombatDestinationFindTrack::SetUseNavMeshHeight(bool newValue)
			{
				useNavMeshHeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EC00
			bool CombatDestinationFindTrack::SetHeightDifferenceCheck(int newValue)
			{
				heightDifferenceCheck = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EC20
			bool CombatDestinationFindTrack::SetMaxHeightDifference(float newValue)
			{
				maxHeightDifference = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EC40
			bool CombatDestinationFindTrack::SetMinHeightDifference(float newValue)
			{
				minHeightDifference = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EC60
			bool CombatDestinationFindTrack::SetLookJustCloser(float newValue)
			{
				lookJustCloser = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EC80
			bool CombatDestinationFindTrack::SetMinDistanceFromCurrent(float newValue)
			{
				minDistanceFromCurrent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021ECA0
			bool CombatDestinationFindTrack::SetFreeRadiusAround(float newValue)
			{
				freeRadiusAround = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021ECC0
			bool CombatDestinationFindTrack::SetAllowedAreas(int newValue)
			{
				allowedAreas = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021ECE0
			bool CombatDestinationFindTrack::SetIgnoreAreasWhenAgentOutside(bool newValue)
			{
				ignoreAreasWhenAgentOutside = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021ED00
			bool CombatDestinationFindTrack::SetMaxDistanceToGround(float newValue)
			{
				maxDistanceToGround = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021ED20
			bool CombatDestinationFindTrack::SetMaxAbsoluteHeight(float newValue)
			{
				maxAbsoluteHeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021ED40
			bool CombatDestinationFindTrack::SetReferenceOffset(const math::Vector& newValue)
			{
				referenceOffset.x = newValue.x;
				referenceOffset.y = newValue.y;
				referenceOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1021ED60
			bool CombatDestinationFindTrack::SetAirDestination(bool newValue)
			{
				airDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021ED80
			bool CombatDestinationFindTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EDA0
			bool CombatDestinationFindTrack::SetCameraVisibility(int newValue)
			{
				cameraVisibility = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EDC0
			bool CombatDestinationFindTrack::SetCollisionFlagsLOF(int newValue)
			{
				collisionFlagsLOF = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EDE0
			bool CombatDestinationFindTrack::SetCollideWithTypeLOF(int newValue)
			{
				collideWithTypeLOF = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EE00
			bool CombatDestinationFindTrack::SetOffsetLOF(const math::Vector& newValue)
			{
				offsetLOF.x = newValue.x;
				offsetLOF.y = newValue.y;
				offsetLOF.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EE20
			bool CombatDestinationFindTrack::SetHeuristic(int newValue)
			{
				heuristic = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021FC50
			bool CombatDestinationFindTrack::SetInitialHeuristicTimer(const fight::Name& newValue)
			{
				initialHeuristicTimer = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EE40
			bool CombatDestinationFindTrack::SetInitialHeuristicMinTimer(float newValue)
			{
				initialHeuristicMinTimer = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EE60
			bool CombatDestinationFindTrack::SetInitialHeuristicMinTimerFactor(float newValue)
			{
				initialHeuristicMinTimerFactor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EE80
			bool CombatDestinationFindTrack::SetInitialHeuristicMaxTimer(float newValue)
			{
				initialHeuristicMaxTimer = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EEA0
			bool CombatDestinationFindTrack::SetInitialHeuristicMaxTimerFactor(float newValue)
			{
				initialHeuristicMaxTimerFactor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EEC0
			bool CombatDestinationFindTrack::SetReferencePosition(int newValue)
			{
				referencePosition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EEE0
			bool CombatDestinationFindTrack::SetDeadReckoningTime(float newValue)
			{
				deadReckoningTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EF00
			fight::BranchHolder* CombatDestinationFindTrack::SetWhenFound()
			{
				return &whenFound;
			}

			// FUNCTION: ENGINE 0x1021EF10
			bool CombatDestinationFindTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EF30
			fight::ConditionList* CombatDestinationFindTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1021F990
			fight::Property* CombatDestinationFindTrack::GetProperty(int index)
			{
				return gCombatDestinationFindTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021F9B0
			void CombatDestinationFindTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCombatDestinationFindTrackProperties);
			}

			// FUNCTION: ENGINE 0x102200A0
			CombatDestinationFindTrack::CombatDestinationFindTrack() : whenFound(0), offset(0.0f, 0.0f, 0.0f), offsetLOF(0.0f, 0.0f, 0.0f), referenceOffset(0.0f, 0.0f, 0.0f), deadReckoningTime(0.0f), freeRadiusAround(0.0f), initialHeuristicMaxTimer(0.0f), initialHeuristicMaxTimerFactor(0.0f), initialHeuristicMinTimer(0.0f), initialHeuristicMinTimerFactor(0.0f), lookJustCloser(0.0f), maxAbsoluteHeight(3e+04f), maxAngle(1.5707964f), maxDistance(2e+01f), maxDistanceToGround(0.0f), maxHeightDifference(3.0f), minAngle(-1.5707964f), minDistance(1e+01f), minDistanceFromCurrent(0.0f), minHeightDifference(8.0f), timeBegin(0.0f), timeEnd(-1.0f), cameraVisibility(0), collisionFlagsLOF(0), heightDifferenceCheck(0), heuristic(0), numTries(1), priority(0), referencePosition(0), allowedAreas(gCombatDestinationFindTrackAllowedAreasDefault), collideWithTypeLOF(gCombatDestinationFindTrackCollideWithTypeLOFDefault), airDestination(false), checkCanGo(true), checkNotReserved(true), ignoreAreasWhenAgentOutside(false), ignoreRestrictions(false), initialHeuristic(false), useNavMeshHeight(true)
			{
			}

			// FUNCTION: ENGINE 0x102202B0
			bool CombatDestinationFindTrack::Slot16(int index)
			{
				return (overrideMask & (1ui64 << index)) != 0;
			}

			// FUNCTION: ENGINE 0x1021F9C0
			// NONMATCHING: the engine keeps the group flag's result only in the argument slot and pushes a register copy for the recursive call; ours holds it in a register (same function as HideHUDTrack::ApplyGroup)
#ifdef NONMATCHING
			void CombatDestinationFindTrack::ApplyGroup(int group, bool value)
			{
				if (group != 0)
				{
					return;
				}
				if (value && !initialHeuristic)
				{
					value = false;
				}
				for (int i = 0; gCombatDestinationFindTrackInitialHeuristicMembers[i] != -1; i++)
				{
					const int* member = &gCombatDestinationFindTrackInitialHeuristicMembers[i];
					unsigned __int64 bit = 1ui64 << *member;
					if (value)
					{
						overrideMask |= bit;
					}
					else
					{
						overrideMask &= ~bit;
					}
					ApplyGroup(*member, value);
				}
			}
#endif

			// FUNCTION: ENGINE 0x10220330
			bool CombatDestinationFindTrack::SetInitialHeuristic(bool newValue)
			{
				initialHeuristic = newValue;
				ApplyGroup(0, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x102202A0
			float CombatDestinationFindTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x102202F0
			float CombatDestinationFindTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10220300
			CombatDestinationFindTrack::~CombatDestinationFindTrack()
			{
			}

			// FUNCTION: ENGINE 0x10224BE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CombatDestinationFindTrack::RegisterProperties()
			{
				if (gCombatDestinationFindTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("timeBegin", &CombatDestinationFindTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("timeEnd", &CombatDestinationFindTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("minDistance", &CombatDestinationFindTrack::SetMinDistance);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("maxDistance", &CombatDestinationFindTrack::SetMaxDistance);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("minAngle", &CombatDestinationFindTrack::SetMinAngle);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("maxAngle", &CombatDestinationFindTrack::SetMaxAngle);
					properties[5] = property;
					property = new fight::PropertyIntConstRange<CombatDestinationFindTrack>("numTries", &CombatDestinationFindTrack::SetNumTries);
					properties[6] = property;
					property = new fight::PropertyBool<CombatDestinationFindTrack>("ignoreRestrictions", &CombatDestinationFindTrack::SetIgnoreRestrictions);
					properties[7] = property;
					property = new fight::PropertyBool<CombatDestinationFindTrack>("checkNotReserved", &CombatDestinationFindTrack::SetCheckNotReserved);
					properties[8] = property;
					property = new fight::PropertyBool<CombatDestinationFindTrack>("checkCanGo", &CombatDestinationFindTrack::SetCheckCanGo);
					properties[9] = property;
					property = new fight::PropertyBool<CombatDestinationFindTrack>("useNavMeshHeight", &CombatDestinationFindTrack::SetUseNavMeshHeight);
					properties[10] = property;
					property = new fight::PropertyEnumConstList<CombatDestinationFindTrack>("heightDifferenceCheck", gCombatDestinationFindTrackHeightDifferenceCheckTable, gCombatDestinationFindTrackHeightDifferenceCheckCount, &CombatDestinationFindTrack::SetHeightDifferenceCheck);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("maxHeightDifference", &CombatDestinationFindTrack::SetMaxHeightDifference);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("minHeightDifference", &CombatDestinationFindTrack::SetMinHeightDifference);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("lookJustCloser", &CombatDestinationFindTrack::SetLookJustCloser);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("minDistanceFromCurrent", &CombatDestinationFindTrack::SetMinDistanceFromCurrent);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("freeRadiusAround", &CombatDestinationFindTrack::SetFreeRadiusAround);
					properties[16] = property;
					property = new fight::PropertyBitfieldConstList<CombatDestinationFindTrack>("allowedAreas", gCombatDestinationFindTrackAllowedAreasTable, gCombatDestinationFindTrackAllowedAreasCount, &CombatDestinationFindTrack::SetAllowedAreas);
					properties[17] = property;
					property = new fight::PropertyBool<CombatDestinationFindTrack>("ignoreAreasWhenAgentOutside", &CombatDestinationFindTrack::SetIgnoreAreasWhenAgentOutside);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("maxDistanceToGround", &CombatDestinationFindTrack::SetMaxDistanceToGround);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("maxAbsoluteHeight", &CombatDestinationFindTrack::SetMaxAbsoluteHeight);
					properties[20] = property;
					property = new fight::PropertyVector<CombatDestinationFindTrack>("referenceOffset", &CombatDestinationFindTrack::SetReferenceOffset);
					properties[21] = property;
					property = new fight::PropertyBool<CombatDestinationFindTrack>("airDestination", &CombatDestinationFindTrack::SetAirDestination);
					properties[22] = property;
					property = new fight::PropertyVector<CombatDestinationFindTrack>("offset", &CombatDestinationFindTrack::SetOffset);
					properties[23] = property;
					property = new fight::PropertyEnumConstList<CombatDestinationFindTrack>("cameraVisibility", gCombatDestinationFindTrackCameraVisibilityTable, gCombatDestinationFindTrackCameraVisibilityCount, &CombatDestinationFindTrack::SetCameraVisibility);
					properties[24] = property;
					property = new fight::PropertyEnumConstList<CombatDestinationFindTrack>("collisionFlagsLOF", gTargetHasLoFConditionCollisionFlagsTable, gTargetHasLoFConditionCollisionFlagsCount, &CombatDestinationFindTrack::SetCollisionFlagsLOF);
					properties[25] = property;
					property = new fight::PropertyBitfieldConstList<CombatDestinationFindTrack>("collideWithTypeLOF", motion::gDetectObbCollisionConditionCollideWithTable, motion::gDetectObbCollisionConditionCollideWithCount, &CombatDestinationFindTrack::SetCollideWithTypeLOF);
					properties[26] = property;
					property = new fight::PropertyVector<CombatDestinationFindTrack>("offsetLOF", &CombatDestinationFindTrack::SetOffsetLOF);
					properties[27] = property;
					property = new fight::PropertyEnumConstList<CombatDestinationFindTrack>("heuristic", gCombatDestinationFindTrackHeuristicTable, gCombatDestinationFindTrackHeuristicCount, &CombatDestinationFindTrack::SetHeuristic);
					properties[28] = property;
					property = new fight::PropertyGroup<CombatDestinationFindTrack>("initialHeuristic", &CombatDestinationFindTrack::SetInitialHeuristic, gCombatDestinationFindTrackInitialHeuristicMembers);
					properties[29] = property;
					property = new fight::PropertyName<CombatDestinationFindTrack>("initialHeuristicTimer", &CombatDestinationFindTrack::SetInitialHeuristicTimer);
					properties[30] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("initialHeuristicMinTimer", &CombatDestinationFindTrack::SetInitialHeuristicMinTimer);
					properties[31] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("initialHeuristicMinTimerFactor", &CombatDestinationFindTrack::SetInitialHeuristicMinTimerFactor);
					properties[32] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("initialHeuristicMaxTimer", &CombatDestinationFindTrack::SetInitialHeuristicMaxTimer);
					properties[33] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("initialHeuristicMaxTimerFactor", &CombatDestinationFindTrack::SetInitialHeuristicMaxTimerFactor);
					properties[34] = property;
					property = new fight::PropertyEnumConstList<CombatDestinationFindTrack>("referencePosition", gCombatDestinationFindTrackReferencePositionTable, gCombatDestinationFindTrackReferencePositionCount, &CombatDestinationFindTrack::SetReferencePosition);
					properties[35] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationFindTrack>("deadReckoningTime", &CombatDestinationFindTrack::SetDeadReckoningTime);
					properties[36] = property;
					property = new fight::PropertyBranch<CombatDestinationFindTrack>("whenFound", &CombatDestinationFindTrack::SetWhenFound);
					properties[37] = property;
					property = new fight::PropertyIntConstRange<CombatDestinationFindTrack>("priority", &CombatDestinationFindTrack::SetPriority);
					properties[38] = property;
					property = new fight::PropertyConditionGroup<CombatDestinationFindTrack>("conditions", &CombatDestinationFindTrack::SetConditions);
					properties[39] = property;
					fight::RegisterPropertyList(properties, &gCombatDestinationFindTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102227C0
			fight::TrackFactory* CreateCombatDestinationFindTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CombatDestinationFindTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10224100
			void RegisterCombatDestinationFindTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CombatDestinationFindTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gCombatDestinationTransmitTrackProperties;  // 0x1125588C

			// FUNCTION: ENGINE 0x1021EF40
			bool CombatDestinationTransmitTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EF60
			bool CombatDestinationTransmitTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021FC70
			bool CombatDestinationTransmitTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021FA70
			fight::Property* CombatDestinationTransmitTrack::GetProperty(int index)
			{
				return gCombatDestinationTransmitTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021FA90
			void CombatDestinationTransmitTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCombatDestinationTransmitTrackProperties);
			}

			// FUNCTION: ENGINE 0x10220350
			CombatDestinationTransmitTrack::CombatDestinationTransmitTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10220390
			float CombatDestinationTransmitTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x102203A0
			float CombatDestinationTransmitTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x102203B0
			CombatDestinationTransmitTrack::~CombatDestinationTransmitTrack()
			{
			}

			// FUNCTION: ENGINE 0x10225690
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CombatDestinationTransmitTrack::RegisterProperties()
			{
				if (gCombatDestinationTransmitTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CombatDestinationTransmitTrack>("timeBegin", &CombatDestinationTransmitTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<CombatDestinationTransmitTrack>("timeEnd", &CombatDestinationTransmitTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<CombatDestinationTransmitTrack>("grabSlot", &CombatDestinationTransmitTrack::SetGrabSlot);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gCombatDestinationTransmitTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102227F0
			fight::TrackFactory* CreateCombatDestinationTransmitTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CombatDestinationTransmitTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10224130
			void RegisterCombatDestinationTransmitTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CombatDestinationTransmitTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDrawDebugTrackProperties;  // 0x11255890

			// FUNCTION: ENGINE 0x1021EF80
			bool DrawDebugTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EFA0
			bool DrawDebugTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EFC0
			bool DrawDebugTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021EFE0
			bool DrawDebugTrack::SetColour(const math::Colour128& newValue)
			{
				colour = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021FAA0
			fight::Property* DrawDebugTrack::GetProperty(int index)
			{
				return gDrawDebugTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021FAC0
			void DrawDebugTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDrawDebugTrackProperties);
			}

			// FUNCTION: ENGINE 0x1021FAD0
			DrawDebugTrack::DrawDebugTrack() : colour(1.0f, 0.0f, 0.0f, 1.0f), radius(1.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1021FB40
			float DrawDebugTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1021FB50
			float DrawDebugTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1021FB60
			DrawDebugTrack::~DrawDebugTrack()
			{
			}

			// FUNCTION: ENGINE 0x10223B40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DrawDebugTrack::RegisterProperties()
			{
				if (gDrawDebugTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DrawDebugTrack>("timeBegin", &DrawDebugTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DrawDebugTrack>("timeEnd", &DrawDebugTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DrawDebugTrack>("radius", &DrawDebugTrack::SetRadius);
					properties[2] = property;
					property = new fight::PropertyColour<DrawDebugTrack>("colour", &DrawDebugTrack::SetColour);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gDrawDebugTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10222820
			fight::TrackFactory* CreateDrawDebugTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DrawDebugTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10224160
			void RegisterDrawDebugTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DrawDebugTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTargetTokenBoostTrackProperties;  // 0x11255894

			// FUNCTION: ENGINE 0x1021F010
			bool TargetTokenBoostTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F030
			bool TargetTokenBoostTrack::SetExtraTokens(int newValue)
			{
				extraTokens = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021F040
			bool TargetTokenBoostTrack::SetBoostTime(float newValue)
			{
				boostTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021FB70
			fight::Property* TargetTokenBoostTrack::GetProperty(int index)
			{
				return gTargetTokenBoostTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021FB90
			void TargetTokenBoostTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTargetTokenBoostTrackProperties);
			}

			// FUNCTION: ENGINE 0x1021FBA0
			TargetTokenBoostTrack::TargetTokenBoostTrack() : boostTime(15.0f), timeBegin(0.0f), extraTokens(4)
			{
			}

			// FUNCTION: ENGINE 0x1021FBE0
			float TargetTokenBoostTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1021FBF0
			float TargetTokenBoostTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1021FC00
			TargetTokenBoostTrack::~TargetTokenBoostTrack()
			{
			}

			// FUNCTION: ENGINE 0x10223C90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetTokenBoostTrack::RegisterProperties()
			{
				if (gTargetTokenBoostTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TargetTokenBoostTrack>("timeBegin", &TargetTokenBoostTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyIntConstRange<TargetTokenBoostTrack>("extraTokens", &TargetTokenBoostTrack::SetExtraTokens);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TargetTokenBoostTrack>("boostTime", &TargetTokenBoostTrack::SetBoostTime);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gTargetTokenBoostTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10222850
			fight::TrackFactory* CreateTargetTokenBoostTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TargetTokenBoostTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10224190
			void RegisterTargetTokenBoostTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TargetTokenBoostTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}


			// FUNCTION: ENGINE 0x101E44E0
			// EQUIVALENT: register allocation and scheduling (the engine loads the manager pointer before the handle, ours the other way round); the same call with the same arguments (best 58.6 %)
			bool HaveStrafeRunTokenCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(AsOwner(c));
				proto::ByteFlag flag = { requestIt };
				return proto::gAISystem->strafeRunTokens->Unknown10384090(handle, flag);
			}

			// FUNCTION: ENGINE 0x101E63B0
			// EQUIVALENT: instruction selection (the engine compares into al, ours through cl); the same calls in the same order (best 86.0 %)
			bool ShouldRadioHQCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object == 0)
				{
					return false;
				}
				return proto::gAISystem->baseAlert->Unknown1037E0F0(object) == radio;
			}


			// FUNCTION: ENGINE 0x101E44B0
			// EQUIVALENT: scheduling and register choice (the engine loads the float constant and the manager first, ours the handle first); the same call with the same arguments (best 38.7 %)
			bool RefreshStrafeRunTokenAction::Slot5(int arg, float value)
			{
				return proto::gAISystem->strafeRunTokens->Unknown10383FF0(target, 2.0f);
			}

			// FUNCTION: ENGINE 0x101E7A30
			bool RefreshStrafeRunTokenAction::Slot7(int arg, float value)
			{
				if (link.object == 0)
				{
					return false;
				}
				proto::gAISystem->strafeRunTokens->Unknown10383FF0(target, 2.0f);
				return true;
			}

			// FUNCTION: ENGINE 0x101E7740
			// EQUIVALENT: block order (the engine puts the failure exit first and jumps back to it, ours puts it last); the same tests, the same store (best 21.7 %)
			bool DrawDebugAction::Slot5(int arg, float value)
			{
				if (link.object != 0 && target.IsValid())
				{
					unknown2C = 0;
					return true;
				}
				return false;
			}

			// FUNCTION: ENGINE 0x101E77A0
			void DrawDebugAction::Slot6()
			{
				unknown2C = 0;
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x101E7980
			RefreshStrafeRunTokenAction::RefreshStrafeRunTokenAction(RefreshStrafeRunTokenTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101E4D20
			RefreshStrafeRunTokenAction::~RefreshStrafeRunTokenAction()
			{
			}

			// FUNCTION: ENGINE 0x101E7A70
			void RefreshStrafeRunTokenAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101E7FC0
			fight::Action* RefreshStrafeRunTokenTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new RefreshStrafeRunTokenAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101E7530
			ActionAction::ActionAction(ActionTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101E4C20
			ActionAction::~ActionAction()
			{
			}

			// FUNCTION: ENGINE 0x101E4460
			bool ActionAction::Slot5(int arg, float value)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x101E4470
			void ActionAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101E7D20
			fight::Action* ActionTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ActionAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101E77B0
			RequestTokenAction::RequestTokenAction(RequestTokenTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101E4CD0
			RequestTokenAction::~RequestTokenAction()
			{
			}

			// FUNCTION: ENGINE 0x101E7DC0
			fight::Action* RequestTokenTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new RequestTokenAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101E76A0
			DrawDebugAction::DrawDebugAction(DrawDebugTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), unknown2C(0)
			{
			}

			// FUNCTION: ENGINE 0x101E4C70
			DrawDebugAction::~DrawDebugAction()
			{
			}

			// FUNCTION: ENGINE 0x101E7790
			bool DrawDebugAction::Slot7(int arg, float value)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x101E7D70
			fight::Action* DrawDebugTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new DrawDebugAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101E7A80
			TargetTokenBoostAction::TargetTokenBoostAction(TargetTokenBoostTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101E4D70
			TargetTokenBoostAction::~TargetTokenBoostAction()
			{
			}

			// FUNCTION: ENGINE 0x101E8010
			fight::Action* TargetTokenBoostTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new TargetTokenBoostAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<TargetHasLoFCondition>;
			template class fight::PropertyEnumConstList<TargetHasLoFCondition>;
			template class fight::PropertyBitfieldConstList<TargetHasLoFCondition>;
			template class fight::PropertyVector<TargetHasLoFCondition>;
			template class fight::ConditionFactoryTemplate<TargetHasLoFCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetHasLoFCondition>;
			template class fight::PropertyEnumConstList<HaveTokenCondition>;
			template class fight::ConditionFactoryTemplate<HaveTokenCondition>;
			template class fight::ConditionFactoryCasterTemplate<HaveTokenCondition>;
			template class fight::PropertyEnumConstList<DestinationTargetDistanceCondition>;
			template class fight::PropertyFloatConstRange<DestinationTargetDistanceCondition>;
			template class fight::PropertyBool<DestinationTargetDistanceCondition>;
			template class fight::ConditionFactoryTemplate<DestinationTargetDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<DestinationTargetDistanceCondition>;
			template class fight::PropertyEnumConstList<InfectedAlertedCondition>;
			template class fight::PropertyFloatConstRange<InfectedAlertedCondition>;
			template class fight::PropertyBool<InfectedAlertedCondition>;
			template class fight::ConditionFactoryTemplate<InfectedAlertedCondition>;
			template class fight::ConditionFactoryCasterTemplate<InfectedAlertedCondition>;
			template class fight::PropertyFloatConstRange<TargetHasLoFDistanceCondition>;
			template class fight::PropertyEnumConstList<TargetHasLoFDistanceCondition>;
			template class fight::PropertyBitfieldConstList<TargetHasLoFDistanceCondition>;
			template class fight::PropertyVector<TargetHasLoFDistanceCondition>;
			template class fight::ConditionFactoryTemplate<TargetHasLoFDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetHasLoFDistanceCondition>;
			template class fight::ConditionFactoryTemplate<FloatShotAllowedCondition>;
			template class fight::ConditionFactoryCasterTemplate<FloatShotAllowedCondition>;
			template class fight::PropertyFloatConstRange<InTargetsCameraCondition>;
			template class fight::ConditionFactoryTemplate<InTargetsCameraCondition>;
			template class fight::ConditionFactoryCasterTemplate<InTargetsCameraCondition>;
			template class fight::PropertyBool<ShouldRadioHQCondition>;
			template class fight::ConditionFactoryTemplate<ShouldRadioHQCondition>;
			template class fight::ConditionFactoryCasterTemplate<ShouldRadioHQCondition>;
			template class fight::PropertyBool<TargetIsHumanCondition>;
			template class fight::ConditionFactoryTemplate<TargetIsHumanCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetIsHumanCondition>;
			template class fight::PropertyEnumConstList<AnyPlayerDistanceCondition>;
			template class fight::PropertyFloatConstRange<AnyPlayerDistanceCondition>;
			template class fight::PropertyVector<AnyPlayerDistanceCondition>;
			template class fight::ConditionFactoryTemplate<AnyPlayerDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<AnyPlayerDistanceCondition>;
			template class fight::PropertyNameList<AimingAtCondition>;
			template class fight::PropertyFloatConstRange<AimingAtCondition>;
			template class fight::PropertyBool<AimingAtCondition>;
			template class fight::PropertyVector<AimingAtCondition>;
			template class fight::PropertyEnumConstList<AimingAtCondition>;
			template class fight::ConditionFactoryTemplate<AimingAtCondition>;
			template class fight::ConditionFactoryCasterTemplate<AimingAtCondition>;
			template class fight::PropertyEnumConstList<FacingAngleTargetCondition>;
			template class fight::PropertyFloatConstRange<FacingAngleTargetCondition>;
			template class fight::PropertyBool<FacingAngleTargetCondition>;
			template class fight::ConditionFactoryTemplate<FacingAngleTargetCondition>;
			template class fight::ConditionFactoryCasterTemplate<FacingAngleTargetCondition>;
			template class fight::PropertyBool<HaveStrafeRunTokenCondition>;
			template class fight::ConditionFactoryTemplate<HaveStrafeRunTokenCondition>;
			template class fight::ConditionFactoryCasterTemplate<HaveStrafeRunTokenCondition>;
			template class fight::PropertyNameList<AimingAtTargetCondition>;
			template class fight::PropertyFloatConstRange<AimingAtTargetCondition>;
			template class fight::PropertyBool<AimingAtTargetCondition>;
			template class fight::PropertyVector<AimingAtTargetCondition>;
			template class fight::ConditionFactoryTemplate<AimingAtTargetCondition>;
			template class fight::ConditionFactoryCasterTemplate<AimingAtTargetCondition>;
			template class fight::PropertyBool<TargetBeingHeldCondition>;
			template class fight::ConditionFactoryTemplate<TargetBeingHeldCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetBeingHeldCondition>;
			template class fight::PropertyFloatConstRange<RefreshStrafeRunTokenTrack>;
			template class fight::TrackFactoryTemplate<RefreshStrafeRunTokenTrack>;
			template class fight::TrackFactoryCasterTemplate<RefreshStrafeRunTokenTrack>;
			template class fight::PropertyFloatConstRange<ActionTrack>;
			template class fight::PropertyEnum<ActionTrack>;
			template class fight::TrackFactoryTemplate<ActionTrack>;
			template class fight::TrackFactoryCasterTemplate<ActionTrack>;
			template class fight::PropertyFloatConstRange<RequestTokenTrack>;
			template class fight::PropertyEnumConstList<RequestTokenTrack>;
			template class fight::TrackFactoryTemplate<RequestTokenTrack>;
			template class fight::TrackFactoryCasterTemplate<RequestTokenTrack>;
			template class fight::PropertyFloatConstRange<CombatDestinationFindTrack>;
			template class fight::PropertyIntConstRange<CombatDestinationFindTrack>;
			template class fight::PropertyBool<CombatDestinationFindTrack>;
			template class fight::PropertyEnumConstList<CombatDestinationFindTrack>;
			template class fight::PropertyBitfieldConstList<CombatDestinationFindTrack>;
			template class fight::PropertyVector<CombatDestinationFindTrack>;
			template class fight::PropertyGroup<CombatDestinationFindTrack>;
			template class fight::PropertyName<CombatDestinationFindTrack>;
			template class fight::PropertyBranch<CombatDestinationFindTrack>;
			template class fight::PropertyConditionGroup<CombatDestinationFindTrack>;
			template class fight::TrackFactoryTemplate<CombatDestinationFindTrack>;
			template class fight::TrackFactoryCasterTemplate<CombatDestinationFindTrack>;
			template class fight::PropertyFloatConstRange<CombatDestinationTransmitTrack>;
			template class fight::PropertyName<CombatDestinationTransmitTrack>;
			template class fight::TrackFactoryTemplate<CombatDestinationTransmitTrack>;
			template class fight::TrackFactoryCasterTemplate<CombatDestinationTransmitTrack>;
			template class fight::PropertyFloatConstRange<DrawDebugTrack>;
			template class fight::PropertyColour<DrawDebugTrack>;
			template class fight::TrackFactoryTemplate<DrawDebugTrack>;
			template class fight::TrackFactoryCasterTemplate<DrawDebugTrack>;
			template class fight::PropertyFloatConstRange<TargetTokenBoostTrack>;
			template class fight::PropertyIntConstRange<TargetTokenBoostTrack>;
			template class fight::TrackFactoryTemplate<TargetTokenBoostTrack>;
			template class fight::TrackFactoryCasterTemplate<TargetTokenBoostTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101E75B0
// FUNCTION: ENGINE 0x101E7710
// FUNCTION: ENGINE 0x101E7830
// FUNCTION: ENGINE 0x101E7A00
// FUNCTION: ENGINE 0x101E7B00
// FUNCTION: ENGINE 0x1021FC90
// FUNCTION: ENGINE 0x1021FCC0
// FUNCTION: ENGINE 0x1021FCF0
// FUNCTION: ENGINE 0x1021FD20
// FUNCTION: ENGINE 0x1021FD50
// FUNCTION: ENGINE 0x1021FD80
// FUNCTION: ENGINE 0x1021FDB0
// FUNCTION: ENGINE 0x1021FDE0
// FUNCTION: ENGINE 0x1021FE10
// FUNCTION: ENGINE 0x1021FE40
// FUNCTION: ENGINE 0x1021FF00
// FUNCTION: ENGINE 0x1021FF30
// FUNCTION: ENGINE 0x1021FFE0
// FUNCTION: ENGINE 0x10220010
// FUNCTION: ENGINE 0x10220040
// FUNCTION: ENGINE 0x10220070
// FUNCTION: ENGINE 0x102203C0
// FUNCTION: ENGINE 0x102203F0
// FUNCTION: ENGINE 0x10220420
// FUNCTION: ENGINE 0x10220430
// FUNCTION: ENGINE 0x10220460
// FUNCTION: ENGINE 0x10220470
// FUNCTION: ENGINE 0x102204A0
// FUNCTION: ENGINE 0x102204B0
// FUNCTION: ENGINE 0x102204E0
// FUNCTION: ENGINE 0x102204F0
// FUNCTION: ENGINE 0x10220520
// FUNCTION: ENGINE 0x10220530
// FUNCTION: ENGINE 0x10220560
// FUNCTION: ENGINE 0x10220570
// FUNCTION: ENGINE 0x102205A0
// FUNCTION: ENGINE 0x102205D0
// FUNCTION: ENGINE 0x102205F0
// FUNCTION: ENGINE 0x10220640
// FUNCTION: ENGINE 0x10220650
// FUNCTION: ENGINE 0x10220680
// FUNCTION: ENGINE 0x10220690
// FUNCTION: ENGINE 0x102206C0
// FUNCTION: ENGINE 0x102206D0
// FUNCTION: ENGINE 0x10220700
// FUNCTION: ENGINE 0x10220710
// FUNCTION: ENGINE 0x10220740
// FUNCTION: ENGINE 0x10220750
// FUNCTION: ENGINE 0x10220780
// FUNCTION: ENGINE 0x10220790
// FUNCTION: ENGINE 0x102207C0
// FUNCTION: ENGINE 0x102207D0
// FUNCTION: ENGINE 0x10220800
// FUNCTION: ENGINE 0x10220810
// FUNCTION: ENGINE 0x10220840
// FUNCTION: ENGINE 0x10220850
// FUNCTION: ENGINE 0x10220880
// FUNCTION: ENGINE 0x10220890
// FUNCTION: ENGINE 0x102208C0
// FUNCTION: ENGINE 0x102208D0
// FUNCTION: ENGINE 0x10220900
// FUNCTION: ENGINE 0x10220910
// FUNCTION: ENGINE 0x10220940
// FUNCTION: ENGINE 0x10220950
// FUNCTION: ENGINE 0x10220980
// FUNCTION: ENGINE 0x10220990
// FUNCTION: ENGINE 0x102209C0
// FUNCTION: ENGINE 0x102209D0
// FUNCTION: ENGINE 0x10220A00
// FUNCTION: ENGINE 0x10220A10
// FUNCTION: ENGINE 0x10220A40
// FUNCTION: ENGINE 0x10220A70
// FUNCTION: ENGINE 0x10220AA0
// FUNCTION: ENGINE 0x10220AD0
// FUNCTION: ENGINE 0x10220B00
// FUNCTION: ENGINE 0x10220B30
// FUNCTION: ENGINE 0x10220B60
// FUNCTION: ENGINE 0x10220B70
// FUNCTION: ENGINE 0x10220BB0
// FUNCTION: ENGINE 0x10220BC0
// FUNCTION: ENGINE 0x10220BF0
// FUNCTION: ENGINE 0x10220C10
// FUNCTION: ENGINE 0x10220C20
// FUNCTION: ENGINE 0x10220C60
// FUNCTION: ENGINE 0x10220C70
// FUNCTION: ENGINE 0x10220C90
// FUNCTION: ENGINE 0x10220CA0
// FUNCTION: ENGINE 0x10220D00
// FUNCTION: ENGINE 0x10220D30
// FUNCTION: ENGINE 0x10220D50
// FUNCTION: ENGINE 0x10220D60
// FUNCTION: ENGINE 0x10220DA0
// FUNCTION: ENGINE 0x10220DB0
// FUNCTION: ENGINE 0x10220DE0
// FUNCTION: ENGINE 0x10220E00
// FUNCTION: ENGINE 0x10220E10
// FUNCTION: ENGINE 0x10220E50
// FUNCTION: ENGINE 0x10220E60
// FUNCTION: ENGINE 0x10220E90
// FUNCTION: ENGINE 0x10220EB0
// FUNCTION: ENGINE 0x10220EC0
// FUNCTION: ENGINE 0x10220EF0
// FUNCTION: ENGINE 0x10220F20
// FUNCTION: ENGINE 0x10220F30
// FUNCTION: ENGINE 0x10220F60
// FUNCTION: ENGINE 0x10220F80
// FUNCTION: ENGINE 0x10220F90
// FUNCTION: ENGINE 0x10220FD0
// FUNCTION: ENGINE 0x10220FE0
// FUNCTION: ENGINE 0x10221010
// FUNCTION: ENGINE 0x10221030
// FUNCTION: ENGINE 0x10221040
// FUNCTION: ENGINE 0x10221070
// FUNCTION: ENGINE 0x102210A0
// FUNCTION: ENGINE 0x102210B0
// FUNCTION: ENGINE 0x102210E0
// FUNCTION: ENGINE 0x10221100
// FUNCTION: ENGINE 0x10221110
// FUNCTION: ENGINE 0x10221140
// FUNCTION: ENGINE 0x10221170
// FUNCTION: ENGINE 0x10221180
// FUNCTION: ENGINE 0x102211C0
// FUNCTION: ENGINE 0x102211D0
// FUNCTION: ENGINE 0x10221200
// FUNCTION: ENGINE 0x10221220
// FUNCTION: ENGINE 0x10221230
// FUNCTION: ENGINE 0x10221270
// FUNCTION: ENGINE 0x10221280
// FUNCTION: ENGINE 0x102212A0
// FUNCTION: ENGINE 0x102212B0
// FUNCTION: ENGINE 0x10221310
// FUNCTION: ENGINE 0x10221340
// FUNCTION: ENGINE 0x10221360
// FUNCTION: ENGINE 0x10221370
// FUNCTION: ENGINE 0x102213A0
// FUNCTION: ENGINE 0x102213D0
// FUNCTION: ENGINE 0x102213E0
// FUNCTION: ENGINE 0x10221410
// FUNCTION: ENGINE 0x10221430
// FUNCTION: ENGINE 0x10221440
// FUNCTION: ENGINE 0x10221470
// FUNCTION: ENGINE 0x10221490
// FUNCTION: ENGINE 0x102214A0
// FUNCTION: ENGINE 0x102214E0
// FUNCTION: ENGINE 0x102214F0
// FUNCTION: ENGINE 0x10221520
// FUNCTION: ENGINE 0x10221540
// FUNCTION: ENGINE 0x10221550
// FUNCTION: ENGINE 0x10221580
// FUNCTION: ENGINE 0x102215B0
// FUNCTION: ENGINE 0x102215C0
// FUNCTION: ENGINE 0x102215F0
// FUNCTION: ENGINE 0x10221610
// FUNCTION: ENGINE 0x10221620
// FUNCTION: ENGINE 0x10221650
// FUNCTION: ENGINE 0x10221680
// FUNCTION: ENGINE 0x10221690
// FUNCTION: ENGINE 0x102216C0
// FUNCTION: ENGINE 0x102216E0
// FUNCTION: ENGINE 0x102216F0
// FUNCTION: ENGINE 0x10221720
// FUNCTION: ENGINE 0x10221740
// FUNCTION: ENGINE 0x10221750
// FUNCTION: ENGINE 0x10221790
// FUNCTION: ENGINE 0x102217A0
// FUNCTION: ENGINE 0x102217D0
// FUNCTION: ENGINE 0x102217F0
// FUNCTION: ENGINE 0x10221800
// FUNCTION: ENGINE 0x10221840
// FUNCTION: ENGINE 0x10221850
// FUNCTION: ENGINE 0x10221880
// FUNCTION: ENGINE 0x102218A0
// FUNCTION: ENGINE 0x102218B0
// FUNCTION: ENGINE 0x102218E0
// FUNCTION: ENGINE 0x10221910
// FUNCTION: ENGINE 0x10221920
// FUNCTION: ENGINE 0x10221950
// FUNCTION: ENGINE 0x10221970
// FUNCTION: ENGINE 0x10221980
// FUNCTION: ENGINE 0x102219B0
// FUNCTION: ENGINE 0x102219D0
// FUNCTION: ENGINE 0x102219E0
// FUNCTION: ENGINE 0x10221A10
// FUNCTION: ENGINE 0x10221A40
// FUNCTION: ENGINE 0x10221A50
// FUNCTION: ENGINE 0x10221A80
// FUNCTION: ENGINE 0x10221AA0
// FUNCTION: ENGINE 0x10221AB0
// FUNCTION: ENGINE 0x10221AE0
// FUNCTION: ENGINE 0x10221B00
// FUNCTION: ENGINE 0x10221B10
// FUNCTION: ENGINE 0x10221B40
// FUNCTION: ENGINE 0x10221B60
// FUNCTION: ENGINE 0x10221B70
// FUNCTION: ENGINE 0x10221BA0
// FUNCTION: ENGINE 0x10221BD0
// FUNCTION: ENGINE 0x10221BE0
// FUNCTION: ENGINE 0x10221C10
// FUNCTION: ENGINE 0x10221C40
// FUNCTION: ENGINE 0x10221C50
// FUNCTION: ENGINE 0x10221C90
// FUNCTION: ENGINE 0x10221CB0
// FUNCTION: ENGINE 0x10221CD0
// FUNCTION: ENGINE 0x10221CF0
// FUNCTION: ENGINE 0x10221D00
// FUNCTION: ENGINE 0x10221D30
// FUNCTION: ENGINE 0x10221D60
// FUNCTION: ENGINE 0x10221D70
// FUNCTION: ENGINE 0x10221DB0
// FUNCTION: ENGINE 0x10221DC0
// FUNCTION: ENGINE 0x10221DF0
// FUNCTION: ENGINE 0x10221E10
// FUNCTION: ENGINE 0x10221E20
// FUNCTION: ENGINE 0x10221E50
// FUNCTION: ENGINE 0x10221E80
// FUNCTION: ENGINE 0x10221E90
// FUNCTION: ENGINE 0x10221EC0
// FUNCTION: ENGINE 0x10221EE0
// FUNCTION: ENGINE 0x10221EF0
// FUNCTION: ENGINE 0x10221F20
// FUNCTION: ENGINE 0x10221F40
// FUNCTION: ENGINE 0x10221F50
// FUNCTION: ENGINE 0x10221F90
// FUNCTION: ENGINE 0x10221FA0
// FUNCTION: ENGINE 0x10221FD0
// FUNCTION: ENGINE 0x10221FF0
// FUNCTION: ENGINE 0x10222000
// FUNCTION: ENGINE 0x10222040
// FUNCTION: ENGINE 0x10222050
// FUNCTION: ENGINE 0x10222070
// FUNCTION: ENGINE 0x10222080
// FUNCTION: ENGINE 0x102220E0
// FUNCTION: ENGINE 0x10222110
// FUNCTION: ENGINE 0x10222130
// FUNCTION: ENGINE 0x10222140
// FUNCTION: ENGINE 0x10222170
// FUNCTION: ENGINE 0x10222190
// FUNCTION: ENGINE 0x102221A0
// FUNCTION: ENGINE 0x102221B0
// FUNCTION: ENGINE 0x102221E0
// FUNCTION: ENGINE 0x10222200
// FUNCTION: ENGINE 0x10222230
// FUNCTION: ENGINE 0x10222250
// FUNCTION: ENGINE 0x10222280
// FUNCTION: ENGINE 0x102222B0
// FUNCTION: ENGINE 0x102222C0
// FUNCTION: ENGINE 0x102222F0
// FUNCTION: ENGINE 0x10222320
// FUNCTION: ENGINE 0x10222330
// FUNCTION: ENGINE 0x10222360
// FUNCTION: ENGINE 0x10222380
// FUNCTION: ENGINE 0x10222390
// FUNCTION: ENGINE 0x102223C0
// FUNCTION: ENGINE 0x102223F0
// FUNCTION: ENGINE 0x10222400
// FUNCTION: ENGINE 0x10222430
// FUNCTION: ENGINE 0x10222450
// FUNCTION: ENGINE 0x102241C0
// FUNCTION: ENGINE 0x102241F0
// FUNCTION: ENGINE 0x10224210
// FUNCTION: ENGINE 0x10224220
// FUNCTION: ENGINE 0x10224250
// FUNCTION: ENGINE 0x10224270
// FUNCTION: ENGINE 0x10224280
// FUNCTION: ENGINE 0x102242B0
// FUNCTION: ENGINE 0x102242D0
// FUNCTION: ENGINE 0x10224300
// FUNCTION: ENGINE 0x10224320
// FUNCTION: ENGINE 0x10224350
// FUNCTION: ENGINE 0x10224370
// FUNCTION: ENGINE 0x102243A0
// FUNCTION: ENGINE 0x102243C0
// FUNCTION: ENGINE 0x102243F0
// FUNCTION: ENGINE 0x10224410
// FUNCTION: ENGINE 0x10224440
// FUNCTION: ENGINE 0x10224460
// FUNCTION: ENGINE 0x10224490
// FUNCTION: ENGINE 0x102244B0
// FUNCTION: ENGINE 0x102244E0
// FUNCTION: ENGINE 0x10224500
// FUNCTION: ENGINE 0x10224530
// FUNCTION: ENGINE 0x10224550
// FUNCTION: ENGINE 0x10224580
// FUNCTION: ENGINE 0x102245A0
// FUNCTION: ENGINE 0x102245D0
// FUNCTION: ENGINE 0x102245F0
// FUNCTION: ENGINE 0x10224620
// FUNCTION: ENGINE 0x10224640
// FUNCTION: ENGINE 0x10224670
// FUNCTION: ENGINE 0x10224690
// FUNCTION: ENGINE 0x102246C0
// FUNCTION: ENGINE 0x102246E0
// FUNCTION: ENGINE 0x10224710
// FUNCTION: ENGINE 0x10224730
// FUNCTION: ENGINE 0x10224760
// FUNCTION: ENGINE 0x10224780
// FUNCTION: ENGINE 0x102247B0
// FUNCTION: ENGINE 0x102247D0
// FUNCTION: ENGINE 0x10224800
// FUNCTION: ENGINE 0x10224820
// FUNCTION: ENGINE 0x10224850
// FUNCTION: ENGINE 0x102257A0
// FUNCTION: ENGINE 0x102257F0
// FUNCTION: ENGINE 0x10225840
// FUNCTION: ENGINE 0x10225890
// FUNCTION: ENGINE 0x102258E0
// FUNCTION: ENGINE 0x10225930
// FUNCTION: ENGINE 0x10225980
// FUNCTION: ENGINE 0x102259D0
// FUNCTION: ENGINE 0x10225A20
// FUNCTION: ENGINE 0x10225A70
// FUNCTION: ENGINE 0x10225AC0
// FUNCTION: ENGINE 0x10225B10
// FUNCTION: ENGINE 0x10225B60
// FUNCTION: ENGINE 0x10225BB0
// FUNCTION: ENGINE 0x10225C00
// FUNCTION: ENGINE 0x10225C50
// FUNCTION: ENGINE 0x10225CA0
// FUNCTION: ENGINE 0x10225CF0
// FUNCTION: ENGINE 0x10225D20
// FUNCTION: ENGINE 0x10225D40
// FUNCTION: ENGINE 0x10225D70
// FUNCTION: ENGINE 0x10225D90
// FUNCTION: ENGINE 0x10225DC0
// FUNCTION: ENGINE 0x10225DF0
// FUNCTION: ENGINE 0x10225E20
// FUNCTION: ENGINE 0x10225E40
// FUNCTION: ENGINE 0x10225E90
// FUNCTION: ENGINE 0x10225EE0
// FUNCTION: ENGINE 0x10225F30
