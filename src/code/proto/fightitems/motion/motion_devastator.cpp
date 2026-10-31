// Fight items of the motion group: DevastatorTargetConditionGroupCondition, DevastatorAvailableCondition, DevastatorTargetDistanceCondition, DevastatorTargetGroundSpikeTrack, DevastatorTrack, DevastatorUsedTrack, DevastatorTargetExecuteTrack, TendrilDevastatorTrack, DevastatorTargetHitTrack (unit 0x101561B0 - 0x101598C0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_devastator.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gDevastatorTargetConditionGroupConditionProperties;  // 0x11254438

			// FUNCTION: ENGINE 0x101561B0
			fight::ConditionList* DevastatorTargetConditionGroupCondition::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x101567E0
			fight::Property* DevastatorTargetConditionGroupCondition::GetProperty(int index)
			{
				return gDevastatorTargetConditionGroupConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10156800
			void DevastatorTargetConditionGroupCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDevastatorTargetConditionGroupConditionProperties);
			}

			// FUNCTION: ENGINE 0x10156810
			DevastatorTargetConditionGroupCondition::DevastatorTargetConditionGroupCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x10156840
			DevastatorTargetConditionGroupCondition::~DevastatorTargetConditionGroupCondition()
			{
			}

			// FUNCTION: ENGINE 0x10157EE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DevastatorTargetConditionGroupCondition::RegisterProperties()
			{
				if (gDevastatorTargetConditionGroupConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyConditionGroup<DevastatorTargetConditionGroupCondition>("conditions", &DevastatorTargetConditionGroupCondition::SetConditions);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gDevastatorTargetConditionGroupConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10157D30
			fight::ConditionFactory* CreateDevastatorTargetConditionGroupConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DevastatorTargetConditionGroupCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10158FC0
			void RegisterDevastatorTargetConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DevastatorTargetConditionGroupCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDevastatorAvailableConditionProperties;  // 0x1125443C

			// FUNCTION: ENGINE 0x101561C0
			bool DevastatorAvailableCondition::SetAvailable(bool newValue)
			{
				available = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156860
			fight::Property* DevastatorAvailableCondition::GetProperty(int index)
			{
				return gDevastatorAvailableConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10156880
			void DevastatorAvailableCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDevastatorAvailableConditionProperties);
			}

			// FUNCTION: ENGINE 0x10156890
			DevastatorAvailableCondition::DevastatorAvailableCondition() : fight::Condition(0), available(true)
			{
			}

			// FUNCTION: ENGINE 0x101568B0
			DevastatorAvailableCondition::~DevastatorAvailableCondition()
			{
			}

			// FUNCTION: ENGINE 0x10157F80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DevastatorAvailableCondition::RegisterProperties()
			{
				if (gDevastatorAvailableConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<DevastatorAvailableCondition>("available", &DevastatorAvailableCondition::SetAvailable);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gDevastatorAvailableConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10157D60
			fight::ConditionFactory* CreateDevastatorAvailableConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DevastatorAvailableCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10158FF0
			void RegisterDevastatorAvailableConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DevastatorAvailableCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDevastatorTargetDistanceConditionProperties;  // 0x11254440

			// FUNCTION: ENGINE 0x101561D0
			bool DevastatorTargetDistanceCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101561E0
			bool DevastatorTargetDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101561F0
			bool DevastatorTargetDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101568C0
			fight::Property* DevastatorTargetDistanceCondition::GetProperty(int index)
			{
				return gDevastatorTargetDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101568E0
			void DevastatorTargetDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDevastatorTargetDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x101568F0
			DevastatorTargetDistanceCondition::DevastatorTargetDistanceCondition() : fight::Condition(0), distance(0.0f), compare(4), direction(0)
			{
			}

			// FUNCTION: ENGINE 0x10156930
			DevastatorTargetDistanceCondition::~DevastatorTargetDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x10158020
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DevastatorTargetDistanceCondition::RegisterProperties()
			{
				if (gDevastatorTargetDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<DevastatorTargetDistanceCondition>("direction", gCrowdPositionConditionDirectionTable, gCrowdPositionConditionDirectionCount, &DevastatorTargetDistanceCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<DevastatorTargetDistanceCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &DevastatorTargetDistanceCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTargetDistanceCondition>("distance", &DevastatorTargetDistanceCondition::SetDistance);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gDevastatorTargetDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10157D90
			fight::ConditionFactory* CreateDevastatorTargetDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DevastatorTargetDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10159020
			void RegisterDevastatorTargetDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DevastatorTargetDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDevastatorTargetGroundSpikeTrackProperties;  // 0x11254444

			// FUNCTION: ENGINE 0x10156210
			bool DevastatorTargetGroundSpikeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156E90
			bool DevastatorTargetGroundSpikeTrack::SetTemplate(const fight::Name& newValue)
			{
				templateValue = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156230
			bool DevastatorTargetGroundSpikeTrack::SetParameter(int newValue)
			{
				parameter = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156240
			bool DevastatorTargetGroundSpikeTrack::SetRandom(bool newValue)
			{
				random = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156940
			fight::Property* DevastatorTargetGroundSpikeTrack::GetProperty(int index)
			{
				return gDevastatorTargetGroundSpikeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10156960
			void DevastatorTargetGroundSpikeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDevastatorTargetGroundSpikeTrackProperties);
			}

			// FUNCTION: ENGINE 0x10156F40
			DevastatorTargetGroundSpikeTrack::DevastatorTargetGroundSpikeTrack() : timeBegin(0.0f), parameter(1), random(false)
			{
			}

			// FUNCTION: ENGINE 0x10156F80
			float DevastatorTargetGroundSpikeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10156F90
			float DevastatorTargetGroundSpikeTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10156FA0
			DevastatorTargetGroundSpikeTrack::~DevastatorTargetGroundSpikeTrack()
			{
			}

			// FUNCTION: ENGINE 0x10159450
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DevastatorTargetGroundSpikeTrack::RegisterProperties()
			{
				if (gDevastatorTargetGroundSpikeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DevastatorTargetGroundSpikeTrack>("timeBegin", &DevastatorTargetGroundSpikeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyName<DevastatorTargetGroundSpikeTrack>("template", &DevastatorTargetGroundSpikeTrack::SetTemplate);
					properties[1] = property;
					property = new fight::PropertyIntConstRange<DevastatorTargetGroundSpikeTrack>("parameter", &DevastatorTargetGroundSpikeTrack::SetParameter);
					properties[2] = property;
					property = new fight::PropertyBool<DevastatorTargetGroundSpikeTrack>("random", &DevastatorTargetGroundSpikeTrack::SetRandom);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gDevastatorTargetGroundSpikeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10157DC0
			fight::TrackFactory* CreateDevastatorTargetGroundSpikeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DevastatorTargetGroundSpikeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10159050
			void RegisterDevastatorTargetGroundSpikeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DevastatorTargetGroundSpikeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDevastatorTrackProperties;  // 0x11254448

			// FUNCTION: ENGINE 0x10156250
			bool DevastatorTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156270
			bool DevastatorTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156290
			bool DevastatorTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101562B0
			bool DevastatorTrack::SetTargetCount(int newValue)
			{
				targetCount = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101562D0
			fight::BranchHolder* DevastatorTrack::SetTargetBranch()
			{
				return &targetBranch;
			}

			// FUNCTION: ENGINE 0x101562E0
			fight::BranchHolder* DevastatorTrack::SetRandomTargetBranch()
			{
				return &randomTargetBranch;
			}

			// FUNCTION: ENGINE 0x101562F0
			bool DevastatorTrack::SetMinTargetCount(int newValue)
			{
				minTargetCount = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156310
			bool DevastatorTrack::SetRandomHeightArc(float newValue)
			{
				randomHeightArc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10156340
			bool DevastatorTrack::SetRandomMinRadius(float newValue)
			{
				randomMinRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156360
			bool DevastatorTrack::SetMinHeightArcOnGround(float newValue)
			{
				minHeightArcOnGround = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10156380
			bool DevastatorTrack::SetMinTargetCategory(int newValue)
			{
				minTargetCategory = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101563A0
			bool DevastatorTrack::SetMinTargetPriority(int newValue)
			{
				minTargetPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101563C0
			bool DevastatorTrack::SetAttackTimeBeginStart(float newValue)
			{
				attackTimeBeginStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101563E0
			bool DevastatorTrack::SetAttackTimeBeginStop(float newValue)
			{
				attackTimeBeginStop = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156400
			bool DevastatorTrack::SetAttackTimeBeginRandom(bool newValue)
			{
				attackTimeBeginRandom = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156420
			bool DevastatorTrack::SetAttackTimeDuration(float newValue)
			{
				attackTimeDuration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156440
			bool DevastatorTrack::SetAttackDamage(float newValue)
			{
				attackDamage = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156460
			bool DevastatorTrack::SetRandomDamage(float newValue)
			{
				randomDamage = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156480
			bool DevastatorTrack::SetCameraMaxArc(float newValue)
			{
				cameraMaxArc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101564A0
			bool DevastatorTrack::SetCameraMaxTargets(int newValue)
			{
				cameraMaxTargets = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101564C0
			bool DevastatorTrack::SetCameraMinTargetCategory(int newValue)
			{
				cameraMinTargetCategory = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101564E0
			bool DevastatorTrack::SetCameraMinTargetPriority(int newValue)
			{
				cameraMinTargetPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156500
			bool DevastatorTrack::SetCameraLookAtTargetArc(float newValue)
			{
				cameraLookAtTargetArc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10156520
			bool DevastatorTrack::SetCameraLookAtTargetTime(float newValue)
			{
				cameraLookAtTargetTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156540
			bool DevastatorTrack::SetCameraSwitchTargetTime(float newValue)
			{
				cameraSwitchTargetTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156560
			bool DevastatorTrack::SetUseCharacterHeap(bool newValue)
			{
				useCharacterHeap = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156970
			fight::Property* DevastatorTrack::GetProperty(int index)
			{
				return gDevastatorTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10156990
			void DevastatorTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDevastatorTrackProperties);
			}

			// FUNCTION: ENGINE 0x101569A0
			DevastatorTrack::DevastatorTrack() : randomTargetBranch(0), targetBranch(0), attackDamage(1e+02f), attackTimeBeginStart(1.0f), attackTimeBeginStop(3.0f), attackTimeDuration(0.5f), cameraLookAtTargetArc(1.5707964f), cameraLookAtTargetTime(0.5f), cameraMaxArc(3.1415927f), cameraSwitchTargetTime(0.5f), minHeightArcOnGround(0.0f), radius(5e+01f), randomDamage(2e+01f), randomHeightArc(0.0f), randomMinRadius(0.0f), timeBegin(0.0f), timeEnd(-1.0f), cameraMaxTargets(5), cameraMinTargetCategory(1), cameraMinTargetPriority(0), minTargetCategory(1), minTargetCount(0), minTargetPriority(0), targetCount(30), attackTimeBeginRandom(true), useCharacterHeap(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10156B00
			float DevastatorTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10156B10
			float DevastatorTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10156B20
			DevastatorTrack::~DevastatorTrack()
			{
			}

			// FUNCTION: ENGINE 0x10158160
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DevastatorTrack::RegisterProperties()
			{
				if (gDevastatorTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DevastatorTrack>("timeBegin", &DevastatorTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTrack>("timeEnd", &DevastatorTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTrack>("radius", &DevastatorTrack::SetRadius);
					properties[2] = property;
					property = new fight::PropertyIntConstRange<DevastatorTrack>("targetCount", &DevastatorTrack::SetTargetCount);
					properties[3] = property;
					property = new fight::PropertyBranch<DevastatorTrack>("targetBranch", &DevastatorTrack::SetTargetBranch);
					properties[4] = property;
					property = new fight::PropertyBranch<DevastatorTrack>("randomTargetBranch", &DevastatorTrack::SetRandomTargetBranch);
					properties[5] = property;
					property = new fight::PropertyIntConstRange<DevastatorTrack>("minTargetCount", &DevastatorTrack::SetMinTargetCount);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTrack>("randomHeightArc", &DevastatorTrack::SetRandomHeightArc);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTrack>("randomMinRadius", &DevastatorTrack::SetRandomMinRadius);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTrack>("minHeightArcOnGround", &DevastatorTrack::SetMinHeightArcOnGround);
					properties[9] = property;
					property = new fight::PropertyIntConstRange<DevastatorTrack>("minTargetCategory", &DevastatorTrack::SetMinTargetCategory);
					properties[10] = property;
					property = new fight::PropertyIntConstRange<DevastatorTrack>("minTargetPriority", &DevastatorTrack::SetMinTargetPriority);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTrack>("attackTimeBeginStart", &DevastatorTrack::SetAttackTimeBeginStart);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTrack>("attackTimeBeginStop", &DevastatorTrack::SetAttackTimeBeginStop);
					properties[13] = property;
					property = new fight::PropertyBool<DevastatorTrack>("attackTimeBeginRandom", &DevastatorTrack::SetAttackTimeBeginRandom);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTrack>("attackTimeDuration", &DevastatorTrack::SetAttackTimeDuration);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTrack>("attackDamage", &DevastatorTrack::SetAttackDamage);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTrack>("randomDamage", &DevastatorTrack::SetRandomDamage);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTrack>("cameraMaxArc", &DevastatorTrack::SetCameraMaxArc);
					properties[18] = property;
					property = new fight::PropertyIntConstRange<DevastatorTrack>("cameraMaxTargets", &DevastatorTrack::SetCameraMaxTargets);
					properties[19] = property;
					property = new fight::PropertyIntConstRange<DevastatorTrack>("cameraMinTargetCategory", &DevastatorTrack::SetCameraMinTargetCategory);
					properties[20] = property;
					property = new fight::PropertyIntConstRange<DevastatorTrack>("cameraMinTargetPriority", &DevastatorTrack::SetCameraMinTargetPriority);
					properties[21] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTrack>("cameraLookAtTargetArc", &DevastatorTrack::SetCameraLookAtTargetArc);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTrack>("cameraLookAtTargetTime", &DevastatorTrack::SetCameraLookAtTargetTime);
					properties[23] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTrack>("cameraSwitchTargetTime", &DevastatorTrack::SetCameraSwitchTargetTime);
					properties[24] = property;
					property = new fight::PropertyBool<DevastatorTrack>("useCharacterHeap", &DevastatorTrack::SetUseCharacterHeap);
					properties[25] = property;
					fight::RegisterPropertyList(properties, &gDevastatorTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10157DF0
			fight::TrackFactory* CreateDevastatorTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DevastatorTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10159080
			void RegisterDevastatorTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DevastatorTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDevastatorUsedTrackProperties;  // 0x1125444C

			// FUNCTION: ENGINE 0x10156580
			bool DevastatorUsedTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156B50
			fight::Property* DevastatorUsedTrack::GetProperty(int index)
			{
				return gDevastatorUsedTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10156B70
			void DevastatorUsedTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDevastatorUsedTrackProperties);
			}

			// FUNCTION: ENGINE 0x10156B80
			DevastatorUsedTrack::DevastatorUsedTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10156BB0
			float DevastatorUsedTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10156BC0
			float DevastatorUsedTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10156BD0
			DevastatorUsedTrack::~DevastatorUsedTrack()
			{
			}

			// FUNCTION: ENGINE 0x10158800
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DevastatorUsedTrack::RegisterProperties()
			{
				if (gDevastatorUsedTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DevastatorUsedTrack>("timeBegin", &DevastatorUsedTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gDevastatorUsedTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10157E20
			fight::TrackFactory* CreateDevastatorUsedTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DevastatorUsedTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101590B0
			void RegisterDevastatorUsedTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DevastatorUsedTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDevastatorTargetExecuteTrackProperties;  // 0x11254450

			// FUNCTION: ENGINE 0x101565A0
			bool DevastatorTargetExecuteTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101565C0
			bool DevastatorTargetExecuteTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101565E0
			bool DevastatorTargetExecuteTrack::SetUseAttackTimeBegin(bool newValue)
			{
				useAttackTimeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101565F0
			bool DevastatorTargetExecuteTrack::SetUseAttackTimeEnd(bool newValue)
			{
				useAttackTimeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156600
			bool DevastatorTargetExecuteTrack::SetSetTarget(bool newValue)
			{
				setTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156610
			fight::BranchHolder* DevastatorTargetExecuteTrack::SetReceiverBranch()
			{
				return &receiverBranch;
			}

			// FUNCTION: ENGINE 0x10156620
			bool DevastatorTargetExecuteTrack::SetInterruptPriority(int newValue)
			{
				interruptPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156BE0
			fight::Property* DevastatorTargetExecuteTrack::GetProperty(int index)
			{
				return gDevastatorTargetExecuteTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10156C00
			void DevastatorTargetExecuteTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDevastatorTargetExecuteTrackProperties);
			}

			// FUNCTION: ENGINE 0x10156C10
			DevastatorTargetExecuteTrack::DevastatorTargetExecuteTrack() : receiverBranch(0), timeBegin(0.0f), timeEnd(-1.0f), interruptPriority(-5), setTarget(false), useAttackTimeBegin(false), useAttackTimeEnd(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10156C70
			float DevastatorTargetExecuteTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10156C80
			float DevastatorTargetExecuteTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10156C90
			DevastatorTargetExecuteTrack::~DevastatorTargetExecuteTrack()
			{
			}

			// FUNCTION: ENGINE 0x101588A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DevastatorTargetExecuteTrack::RegisterProperties()
			{
				if (gDevastatorTargetExecuteTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DevastatorTargetExecuteTrack>("timeBegin", &DevastatorTargetExecuteTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTargetExecuteTrack>("timeEnd", &DevastatorTargetExecuteTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<DevastatorTargetExecuteTrack>("useAttackTimeBegin", &DevastatorTargetExecuteTrack::SetUseAttackTimeBegin);
					properties[2] = property;
					property = new fight::PropertyBool<DevastatorTargetExecuteTrack>("useAttackTimeEnd", &DevastatorTargetExecuteTrack::SetUseAttackTimeEnd);
					properties[3] = property;
					property = new fight::PropertyBool<DevastatorTargetExecuteTrack>("setTarget", &DevastatorTargetExecuteTrack::SetSetTarget);
					properties[4] = property;
					property = new fight::PropertyBranch<DevastatorTargetExecuteTrack>("receiverBranch", &DevastatorTargetExecuteTrack::SetReceiverBranch);
					properties[5] = property;
					property = new fight::PropertyIntConstRange<DevastatorTargetExecuteTrack>("interruptPriority", &DevastatorTargetExecuteTrack::SetInterruptPriority);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gDevastatorTargetExecuteTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10157E50
			fight::TrackFactory* CreateDevastatorTargetExecuteTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DevastatorTargetExecuteTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101590E0
			void RegisterDevastatorTargetExecuteTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DevastatorTargetExecuteTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTendrilDevastatorTrackProperties;  // 0x11254454

			// FUNCTION: ENGINE 0x10156630
			bool TendrilDevastatorTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156650
			bool TendrilDevastatorTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156670
			bool TendrilDevastatorTrack::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156690
			fight::BranchHolder* TendrilDevastatorTrack::SetTargetBranch()
			{
				return &targetBranch;
			}

			// FUNCTION: ENGINE 0x101566A0
			bool TendrilDevastatorTrack::SetTendrilCount(int newValue)
			{
				tendrilCount = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101566B0
			bool TendrilDevastatorTrack::SetAttackTimeBegin(float newValue)
			{
				attackTimeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101566D0
			bool TendrilDevastatorTrack::SetAttackTimeDuration(float newValue)
			{
				attackTimeDuration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101566F0
			bool TendrilDevastatorTrack::SetAttackType(int newValue)
			{
				attackType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156700
			bool TendrilDevastatorTrack::SetAttackDamage(float newValue)
			{
				attackDamage = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156CB0
			fight::Property* TendrilDevastatorTrack::GetProperty(int index)
			{
				return gTendrilDevastatorTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10156CD0
			void TendrilDevastatorTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTendrilDevastatorTrackProperties);
			}

			// FUNCTION: ENGINE 0x10156CE0
			TendrilDevastatorTrack::TendrilDevastatorTrack() : targetBranch(0), attackDamage(1e+02f), attackTimeBegin(1.0f), attackTimeDuration(0.5f), distance(5e+01f), timeBegin(0.0f), timeEnd(-1.0f), attackType(0), tendrilCount(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10156D80
			float TendrilDevastatorTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10156D90
			float TendrilDevastatorTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10156DA0
			TendrilDevastatorTrack::~TendrilDevastatorTrack()
			{
			}

			// FUNCTION: ENGINE 0x10158AB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TendrilDevastatorTrack::RegisterProperties()
			{
				if (gTendrilDevastatorTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TendrilDevastatorTrack>("timeBegin", &TendrilDevastatorTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TendrilDevastatorTrack>("timeEnd", &TendrilDevastatorTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TendrilDevastatorTrack>("distance", &TendrilDevastatorTrack::SetDistance);
					properties[2] = property;
					property = new fight::PropertyBranch<TendrilDevastatorTrack>("targetBranch", &TendrilDevastatorTrack::SetTargetBranch);
					properties[3] = property;
					property = new fight::PropertyIntConstRange<TendrilDevastatorTrack>("tendrilCount", &TendrilDevastatorTrack::SetTendrilCount);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<TendrilDevastatorTrack>("attackTimeBegin", &TendrilDevastatorTrack::SetAttackTimeBegin);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<TendrilDevastatorTrack>("attackTimeDuration", &TendrilDevastatorTrack::SetAttackTimeDuration);
					properties[6] = property;
					property = new fight::PropertyEnumConstList<TendrilDevastatorTrack>("attackType", gTendrilDevastatorTrackAttackTypeTable, gTendrilDevastatorTrackAttackTypeCount, &TendrilDevastatorTrack::SetAttackType);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<TendrilDevastatorTrack>("attackDamage", &TendrilDevastatorTrack::SetAttackDamage);
					properties[8] = property;
					fight::RegisterPropertyList(properties, &gTendrilDevastatorTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10157E80
			fight::TrackFactory* CreateTendrilDevastatorTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TendrilDevastatorTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10159110
			void RegisterTendrilDevastatorTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TendrilDevastatorTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDevastatorTargetHitTrackProperties;  // 0x11254458

			// FUNCTION: ENGINE 0x10156720
			bool DevastatorTargetHitTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156740
			bool DevastatorTargetHitTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156760
			bool DevastatorTargetHitTrack::SetUseAttackTimeBegin(bool newValue)
			{
				useAttackTimeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156770
			bool DevastatorTargetHitTrack::SetUseAttackTimeEnd(bool newValue)
			{
				useAttackTimeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156780
			bool DevastatorTargetHitTrack::SetDamage(float newValue)
			{
				damage = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101567A0
			bool DevastatorTargetHitTrack::SetImpulse(const math::Vector& newValue)
			{
				impulse.x = newValue.x;
				impulse.y = newValue.y;
				impulse.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101567C0
			bool DevastatorTargetHitTrack::SetAttackType(int newValue)
			{
				attackType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101567D0
			bool DevastatorTargetHitTrack::SetDamageType(int newValue)
			{
				damageType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10156DC0
			fight::Property* DevastatorTargetHitTrack::GetProperty(int index)
			{
				return gDevastatorTargetHitTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10156DE0
			void DevastatorTargetHitTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDevastatorTargetHitTrackProperties);
			}

			// FUNCTION: ENGINE 0x10156DF0
			DevastatorTargetHitTrack::DevastatorTargetHitTrack() : impulse(0.0f, 0.0f, 0.0f), damage(0.0f), timeBegin(0.0f), timeEnd(-1.0f), attackType(0), damageType(0), useAttackTimeBegin(false), useAttackTimeEnd(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10156E60
			float DevastatorTargetHitTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10156E70
			float DevastatorTargetHitTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10156E80
			DevastatorTargetHitTrack::~DevastatorTargetHitTrack()
			{
			}

			// FUNCTION: ENGINE 0x10158D50
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DevastatorTargetHitTrack::RegisterProperties()
			{
				if (gDevastatorTargetHitTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DevastatorTargetHitTrack>("timeBegin", &DevastatorTargetHitTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTargetHitTrack>("timeEnd", &DevastatorTargetHitTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<DevastatorTargetHitTrack>("useAttackTimeBegin", &DevastatorTargetHitTrack::SetUseAttackTimeBegin);
					properties[2] = property;
					property = new fight::PropertyBool<DevastatorTargetHitTrack>("useAttackTimeEnd", &DevastatorTargetHitTrack::SetUseAttackTimeEnd);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<DevastatorTargetHitTrack>("damage", &DevastatorTargetHitTrack::SetDamage);
					properties[4] = property;
					property = new fight::PropertyVector<DevastatorTargetHitTrack>("impulse", &DevastatorTargetHitTrack::SetImpulse);
					properties[5] = property;
					property = new fight::PropertyEnumConstList<DevastatorTargetHitTrack>("attackType", gTendrilDevastatorTrackAttackTypeTable, gTendrilDevastatorTrackAttackTypeCount, &DevastatorTargetHitTrack::SetAttackType);
					properties[6] = property;
					property = new fight::PropertyEnumConstList<DevastatorTargetHitTrack>("damageType", gDevastatorTargetHitTrackDamageTypeTable, gDevastatorTargetHitTrackDamageTypeCount, &DevastatorTargetHitTrack::SetDamageType);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gDevastatorTargetHitTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10157EB0
			fight::TrackFactory* CreateDevastatorTargetHitTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DevastatorTargetHitTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10159140
			void RegisterDevastatorTargetHitTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DevastatorTargetHitTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyConditionGroup<DevastatorTargetConditionGroupCondition>;
			template class fight::ConditionFactoryTemplate<DevastatorTargetConditionGroupCondition>;
			template class fight::ConditionFactoryCasterTemplate<DevastatorTargetConditionGroupCondition>;
			template class fight::PropertyBool<DevastatorAvailableCondition>;
			template class fight::ConditionFactoryTemplate<DevastatorAvailableCondition>;
			template class fight::ConditionFactoryCasterTemplate<DevastatorAvailableCondition>;
			template class fight::PropertyEnumConstList<DevastatorTargetDistanceCondition>;
			template class fight::PropertyFloatConstRange<DevastatorTargetDistanceCondition>;
			template class fight::ConditionFactoryTemplate<DevastatorTargetDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<DevastatorTargetDistanceCondition>;
			template class fight::PropertyFloatConstRange<DevastatorTargetGroundSpikeTrack>;
			template class fight::PropertyName<DevastatorTargetGroundSpikeTrack>;
			template class fight::PropertyIntConstRange<DevastatorTargetGroundSpikeTrack>;
			template class fight::PropertyBool<DevastatorTargetGroundSpikeTrack>;
			template class fight::TrackFactoryTemplate<DevastatorTargetGroundSpikeTrack>;
			template class fight::TrackFactoryCasterTemplate<DevastatorTargetGroundSpikeTrack>;
			template class fight::PropertyFloatConstRange<DevastatorTrack>;
			template class fight::PropertyIntConstRange<DevastatorTrack>;
			template class fight::PropertyBranch<DevastatorTrack>;
			template class fight::PropertyBool<DevastatorTrack>;
			template class fight::TrackFactoryTemplate<DevastatorTrack>;
			template class fight::TrackFactoryCasterTemplate<DevastatorTrack>;
			template class fight::PropertyFloatConstRange<DevastatorUsedTrack>;
			template class fight::TrackFactoryTemplate<DevastatorUsedTrack>;
			template class fight::TrackFactoryCasterTemplate<DevastatorUsedTrack>;
			template class fight::PropertyFloatConstRange<DevastatorTargetExecuteTrack>;
			template class fight::PropertyBool<DevastatorTargetExecuteTrack>;
			template class fight::PropertyBranch<DevastatorTargetExecuteTrack>;
			template class fight::PropertyIntConstRange<DevastatorTargetExecuteTrack>;
			template class fight::TrackFactoryTemplate<DevastatorTargetExecuteTrack>;
			template class fight::TrackFactoryCasterTemplate<DevastatorTargetExecuteTrack>;
			template class fight::PropertyFloatConstRange<TendrilDevastatorTrack>;
			template class fight::PropertyBranch<TendrilDevastatorTrack>;
			template class fight::PropertyIntConstRange<TendrilDevastatorTrack>;
			template class fight::PropertyEnumConstList<TendrilDevastatorTrack>;
			template class fight::TrackFactoryTemplate<TendrilDevastatorTrack>;
			template class fight::TrackFactoryCasterTemplate<TendrilDevastatorTrack>;
			template class fight::PropertyFloatConstRange<DevastatorTargetHitTrack>;
			template class fight::PropertyBool<DevastatorTargetHitTrack>;
			template class fight::PropertyVector<DevastatorTargetHitTrack>;
			template class fight::PropertyEnumConstList<DevastatorTargetHitTrack>;
			template class fight::TrackFactoryTemplate<DevastatorTargetHitTrack>;
			template class fight::TrackFactoryCasterTemplate<DevastatorTargetHitTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10156EB0
// FUNCTION: ENGINE 0x10156EE0
// FUNCTION: ENGINE 0x10156F10
// FUNCTION: ENGINE 0x10156FB0
// FUNCTION: ENGINE 0x10156FE0
// FUNCTION: ENGINE 0x10157010
// FUNCTION: ENGINE 0x10157040
// FUNCTION: ENGINE 0x10157070
// FUNCTION: ENGINE 0x101570A0
// FUNCTION: ENGINE 0x101570B0
// FUNCTION: ENGINE 0x101570E0
// FUNCTION: ENGINE 0x101570F0
// FUNCTION: ENGINE 0x10157120
// FUNCTION: ENGINE 0x10157130
// FUNCTION: ENGINE 0x10157160
// FUNCTION: ENGINE 0x10157170
// FUNCTION: ENGINE 0x101571A0
// FUNCTION: ENGINE 0x101571B0
// FUNCTION: ENGINE 0x101571E0
// FUNCTION: ENGINE 0x101571F0
// FUNCTION: ENGINE 0x10157220
// FUNCTION: ENGINE 0x10157230
// FUNCTION: ENGINE 0x10157260
// FUNCTION: ENGINE 0x10157270
// FUNCTION: ENGINE 0x101572A0
// FUNCTION: ENGINE 0x101572B0
// FUNCTION: ENGINE 0x101572E0
// FUNCTION: ENGINE 0x10157310
// FUNCTION: ENGINE 0x10157340
// FUNCTION: ENGINE 0x10157360
// FUNCTION: ENGINE 0x10157390
// FUNCTION: ENGINE 0x101573B0
// FUNCTION: ENGINE 0x101573C0
// FUNCTION: ENGINE 0x10157400
// FUNCTION: ENGINE 0x10157410
// FUNCTION: ENGINE 0x10157440
// FUNCTION: ENGINE 0x10157460
// FUNCTION: ENGINE 0x10157470
// FUNCTION: ENGINE 0x101574A0
// FUNCTION: ENGINE 0x101574D0
// FUNCTION: ENGINE 0x101574E0
// FUNCTION: ENGINE 0x10157510
// FUNCTION: ENGINE 0x10157540
// FUNCTION: ENGINE 0x10157550
// FUNCTION: ENGINE 0x10157580
// FUNCTION: ENGINE 0x101575A0
// FUNCTION: ENGINE 0x101575B0
// FUNCTION: ENGINE 0x101575E0
// FUNCTION: ENGINE 0x10157600
// FUNCTION: ENGINE 0x10157610
// FUNCTION: ENGINE 0x10157640
// FUNCTION: ENGINE 0x10157670
// FUNCTION: ENGINE 0x10157680
// FUNCTION: ENGINE 0x101576B0
// FUNCTION: ENGINE 0x101576D0
// FUNCTION: ENGINE 0x101576E0
// FUNCTION: ENGINE 0x10157710
// FUNCTION: ENGINE 0x10157730
// FUNCTION: ENGINE 0x10157760
// FUNCTION: ENGINE 0x10157780
// FUNCTION: ENGINE 0x10157790
// FUNCTION: ENGINE 0x101577C0
// FUNCTION: ENGINE 0x101577F0
// FUNCTION: ENGINE 0x10157800
// FUNCTION: ENGINE 0x10157830
// FUNCTION: ENGINE 0x10157860
// FUNCTION: ENGINE 0x10157870
// FUNCTION: ENGINE 0x101578A0
// FUNCTION: ENGINE 0x101578C0
// FUNCTION: ENGINE 0x101578D0
// FUNCTION: ENGINE 0x10157900
// FUNCTION: ENGINE 0x10157920
// FUNCTION: ENGINE 0x10157950
// FUNCTION: ENGINE 0x10157970
// FUNCTION: ENGINE 0x10157980
// FUNCTION: ENGINE 0x101579B0
// FUNCTION: ENGINE 0x101579E0
// FUNCTION: ENGINE 0x101579F0
// FUNCTION: ENGINE 0x10157A20
// FUNCTION: ENGINE 0x10157A40
// FUNCTION: ENGINE 0x10157A70
// FUNCTION: ENGINE 0x10157A90
// FUNCTION: ENGINE 0x10157AA0
// FUNCTION: ENGINE 0x10157AE0
// FUNCTION: ENGINE 0x10157AF0
// FUNCTION: ENGINE 0x10157B20
// FUNCTION: ENGINE 0x10157B40
// FUNCTION: ENGINE 0x10157B50
// FUNCTION: ENGINE 0x10157B80
// FUNCTION: ENGINE 0x10157BB0
// FUNCTION: ENGINE 0x10157BC0
// FUNCTION: ENGINE 0x10157BF0
// FUNCTION: ENGINE 0x10157C10
// FUNCTION: ENGINE 0x10157C20
// FUNCTION: ENGINE 0x10157C50
// FUNCTION: ENGINE 0x10157C70
// FUNCTION: ENGINE 0x10157C80
// FUNCTION: ENGINE 0x10157CC0
// FUNCTION: ENGINE 0x10157CD0
// FUNCTION: ENGINE 0x10157D00
// FUNCTION: ENGINE 0x10157D20
// FUNCTION: ENGINE 0x10159170
// FUNCTION: ENGINE 0x101591A0
// FUNCTION: ENGINE 0x101591C0
// FUNCTION: ENGINE 0x101591F0
// FUNCTION: ENGINE 0x10159210
// FUNCTION: ENGINE 0x10159240
// FUNCTION: ENGINE 0x10159260
// FUNCTION: ENGINE 0x10159290
// FUNCTION: ENGINE 0x101592B0
// FUNCTION: ENGINE 0x101592E0
// FUNCTION: ENGINE 0x10159310
// FUNCTION: ENGINE 0x10159340
// FUNCTION: ENGINE 0x10159360
// FUNCTION: ENGINE 0x10159390
// FUNCTION: ENGINE 0x101593B0
// FUNCTION: ENGINE 0x101593E0
// FUNCTION: ENGINE 0x10159400
// FUNCTION: ENGINE 0x10159430
// FUNCTION: ENGINE 0x101595A0
// FUNCTION: ENGINE 0x101595F0
// FUNCTION: ENGINE 0x10159640
// FUNCTION: ENGINE 0x10159690
// FUNCTION: ENGINE 0x101596E0
// FUNCTION: ENGINE 0x10159730
// FUNCTION: ENGINE 0x10159780
// FUNCTION: ENGINE 0x101597D0
// FUNCTION: ENGINE 0x10159820
// FUNCTION: ENGINE 0x10159850
// FUNCTION: ENGINE 0x10159870
