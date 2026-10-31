// Fight items of the motion group: CrowdMinDistanceCondition, CrowdPositionCondition, LocoCrowdTrack, CrowdTestTrack (unit 0x1014F4D0 - 0x10151930; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_crowd.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gCrowdMinDistanceConditionProperties;  // 0x112543AC

			// FUNCTION: ENGINE 0x1014F4D0
			bool CrowdMinDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F4E0
			bool CrowdMinDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F9B0
			fight::Property* CrowdMinDistanceCondition::GetProperty(int index)
			{
				return gCrowdMinDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1014F9D0
			void CrowdMinDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gCrowdMinDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x1014F9E0
			CrowdMinDistanceCondition::CrowdMinDistanceCondition() : fight::Condition(0), distance(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x1014FA10
			CrowdMinDistanceCondition::~CrowdMinDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x10150710
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CrowdMinDistanceCondition::RegisterProperties()
			{
				if (gCrowdMinDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<CrowdMinDistanceCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &CrowdMinDistanceCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<CrowdMinDistanceCondition>("distance", &CrowdMinDistanceCondition::SetDistance);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gCrowdMinDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10150650
			fight::ConditionFactory* CreateCrowdMinDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CrowdMinDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10150BC0
			void RegisterCrowdMinDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CrowdMinDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gCrowdPositionConditionProperties;  // 0x112543B0

			// FUNCTION: ENGINE 0x1014F500
			bool CrowdPositionCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F510
			bool CrowdPositionCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F520
			bool CrowdPositionCondition::SetPosition(float newValue)
			{
				position = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014FA20
			fight::Property* CrowdPositionCondition::GetProperty(int index)
			{
				return gCrowdPositionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1014FA40
			void CrowdPositionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gCrowdPositionConditionProperties);
			}

			// FUNCTION: ENGINE 0x1014FA50
			CrowdPositionCondition::CrowdPositionCondition() : fight::Condition(0), position(0.0f), compare(0), direction(0)
			{
			}

			// FUNCTION: ENGINE 0x1014FA90
			CrowdPositionCondition::~CrowdPositionCondition()
			{
			}

			// FUNCTION: ENGINE 0x10150800
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CrowdPositionCondition::RegisterProperties()
			{
				if (gCrowdPositionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<CrowdPositionCondition>("direction", gCrowdPositionConditionDirectionTable, gCrowdPositionConditionDirectionCount, &CrowdPositionCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<CrowdPositionCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &CrowdPositionCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<CrowdPositionCondition>("position", &CrowdPositionCondition::SetPosition);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gCrowdPositionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10150680
			fight::ConditionFactory* CreateCrowdPositionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CrowdPositionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10150BF0
			void RegisterCrowdPositionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CrowdPositionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gLocoCrowdTrackProperties;  // 0x112543B4

			// FUNCTION: ENGINE 0x1014F540
			bool LocoCrowdTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F560
			bool LocoCrowdTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F580
			bool LocoCrowdTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F5A0
			bool LocoCrowdTrack::SetTurningVelocity(float newValue)
			{
				turningVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F5D0
			bool LocoCrowdTrack::SetTwistRateOn(float newValue)
			{
				twistRateOn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F5F0
			bool LocoCrowdTrack::SetTwistRateOff(float newValue)
			{
				twistRateOff = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F610
			bool LocoCrowdTrack::SetVelocityWalk(float newValue)
			{
				velocityWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F630
			bool LocoCrowdTrack::SetVelocityRun(float newValue)
			{
				velocityRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F650
			bool LocoCrowdTrack::SetSmoothSteeringAngle(float newValue)
			{
				smoothSteeringAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F680
			bool LocoCrowdTrack::SetPhase(float newValue)
			{
				phase = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014FBC0
			bool LocoCrowdTrack::SetLocomotion(const fight::Name& newValue)
			{
				locomotion = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014FBE0
			bool LocoCrowdTrack::SetAnimIdle(const fight::Name& newValue)
			{
				animIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014FC00
			bool LocoCrowdTrack::SetAnimIdleTwistLeft(const fight::Name& newValue)
			{
				animIdleTwistLeft = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014FC20
			bool LocoCrowdTrack::SetAnimIdleTwistRight(const fight::Name& newValue)
			{
				animIdleTwistRight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014FC40
			bool LocoCrowdTrack::SetAnimWalk(const fight::Name& newValue)
			{
				animWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014FC60
			bool LocoCrowdTrack::SetAnimWalkTwistLeft(const fight::Name& newValue)
			{
				animWalkTwistLeft = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014FC80
			bool LocoCrowdTrack::SetAnimWalkTwistRight(const fight::Name& newValue)
			{
				animWalkTwistRight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014FCA0
			bool LocoCrowdTrack::SetAnimRun(const fight::Name& newValue)
			{
				animRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014FCC0
			bool LocoCrowdTrack::SetAnimRunTwistLeft(const fight::Name& newValue)
			{
				animRunTwistLeft = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014FCE0
			bool LocoCrowdTrack::SetAnimRunTwistRight(const fight::Name& newValue)
			{
				animRunTwistRight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F6A0
			bool LocoCrowdTrack::SetSyncFrameIdle(float newValue)
			{
				syncFrameIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F6C0
			bool LocoCrowdTrack::SetSyncFrameIdleTwistLeft(float newValue)
			{
				syncFrameIdleTwistLeft = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F6E0
			bool LocoCrowdTrack::SetSyncFrameIdleTwistRight(float newValue)
			{
				syncFrameIdleTwistRight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F700
			bool LocoCrowdTrack::SetSyncFrameWalk(float newValue)
			{
				syncFrameWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F720
			bool LocoCrowdTrack::SetSyncFrameWalkTwistLeft(float newValue)
			{
				syncFrameWalkTwistLeft = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F740
			bool LocoCrowdTrack::SetSyncFrameWalkTwistRight(float newValue)
			{
				syncFrameWalkTwistRight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F760
			bool LocoCrowdTrack::SetSyncFrameRun(float newValue)
			{
				syncFrameRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F780
			bool LocoCrowdTrack::SetSyncFrameRunTwistLeft(float newValue)
			{
				syncFrameRunTwistLeft = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F7A0
			bool LocoCrowdTrack::SetSyncFrameRunTwistRight(float newValue)
			{
				syncFrameRunTwistRight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014FD00
			bool LocoCrowdTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F7C0
			bool LocoCrowdTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F7E0
			bool LocoCrowdTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F800
			bool LocoCrowdTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F820
			bool LocoCrowdTrack::SetRadiusMin(float newValue)
			{
				radiusMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F840
			bool LocoCrowdTrack::SetRadiusMax(float newValue)
			{
				radiusMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F860
			bool LocoCrowdTrack::SetOffsetMax(float newValue)
			{
				offsetMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F880
			fight::BranchHolder* LocoCrowdTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x1014F890
			bool LocoCrowdTrack::SetInterruptPriority(int newValue)
			{
				interruptPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F8B0
			fight::ConditionList* LocoCrowdTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1014FAA0
			fight::Property* LocoCrowdTrack::GetProperty(int index)
			{
				return gLocoCrowdTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1014FAC0
			void LocoCrowdTrack::ClearProperties()
			{
				fight::FreePropertyList(&gLocoCrowdTrackProperties);
			}

			// FUNCTION: ENGINE 0x1014FD80
			LocoCrowdTrack::LocoCrowdTrack() : branch(0), acceleration(5e+01f), blendInTime(0.0f), blendOutTime(0.0f), offsetMax(0.0f), phase(-1.0f), radiusMax(0.0f), radiusMin(0.0f), smoothSteeringAngle(0.0f), syncFrameIdle(-1.0f), syncFrameIdleTwistLeft(-1.0f), syncFrameIdleTwistRight(-1.0f), syncFrameRun(-1.0f), syncFrameRunTwistLeft(-1.0f), syncFrameRunTwistRight(-1.0f), syncFrameWalk(-1.0f), syncFrameWalkTwistLeft(-1.0f), syncFrameWalkTwistRight(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(6.2831855f), twistRateOff(1.0f), twistRateOn(1.0f), velocityRun(-1.0f), velocityWalk(-1.0f), interruptPriority(0), priority(0)
			{
			}

			// FUNCTION: ENGINE 0x1014FF60
			float LocoCrowdTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1014FF70
			float LocoCrowdTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1014FF80
			LocoCrowdTrack::~LocoCrowdTrack()
			{
			}

			// FUNCTION: ENGINE 0x10150DC0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void LocoCrowdTrack::RegisterProperties()
			{
				if (gLocoCrowdTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("timeBegin", &LocoCrowdTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("timeEnd", &LocoCrowdTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("acceleration", &LocoCrowdTrack::SetAcceleration);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("turningVelocity", &LocoCrowdTrack::SetTurningVelocity);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("twistRateOn", &LocoCrowdTrack::SetTwistRateOn);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("twistRateOff", &LocoCrowdTrack::SetTwistRateOff);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("velocityWalk", &LocoCrowdTrack::SetVelocityWalk);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("velocityRun", &LocoCrowdTrack::SetVelocityRun);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("smoothSteeringAngle", &LocoCrowdTrack::SetSmoothSteeringAngle);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("phase", &LocoCrowdTrack::SetPhase);
					properties[9] = property;
					property = new fight::PropertyName<LocoCrowdTrack>("locomotion", &LocoCrowdTrack::SetLocomotion);
					properties[10] = property;
					property = new fight::PropertyName<LocoCrowdTrack>("animIdle", &LocoCrowdTrack::SetAnimIdle);
					properties[11] = property;
					property = new fight::PropertyName<LocoCrowdTrack>("animIdleTwistLeft", &LocoCrowdTrack::SetAnimIdleTwistLeft);
					properties[12] = property;
					property = new fight::PropertyName<LocoCrowdTrack>("animIdleTwistRight", &LocoCrowdTrack::SetAnimIdleTwistRight);
					properties[13] = property;
					property = new fight::PropertyName<LocoCrowdTrack>("animWalk", &LocoCrowdTrack::SetAnimWalk);
					properties[14] = property;
					property = new fight::PropertyName<LocoCrowdTrack>("animWalkTwistLeft", &LocoCrowdTrack::SetAnimWalkTwistLeft);
					properties[15] = property;
					property = new fight::PropertyName<LocoCrowdTrack>("animWalkTwistRight", &LocoCrowdTrack::SetAnimWalkTwistRight);
					properties[16] = property;
					property = new fight::PropertyName<LocoCrowdTrack>("animRun", &LocoCrowdTrack::SetAnimRun);
					properties[17] = property;
					property = new fight::PropertyName<LocoCrowdTrack>("animRunTwistLeft", &LocoCrowdTrack::SetAnimRunTwistLeft);
					properties[18] = property;
					property = new fight::PropertyName<LocoCrowdTrack>("animRunTwistRight", &LocoCrowdTrack::SetAnimRunTwistRight);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("syncFrameIdle", &LocoCrowdTrack::SetSyncFrameIdle);
					properties[20] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("syncFrameIdleTwistLeft", &LocoCrowdTrack::SetSyncFrameIdleTwistLeft);
					properties[21] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("syncFrameIdleTwistRight", &LocoCrowdTrack::SetSyncFrameIdleTwistRight);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("syncFrameWalk", &LocoCrowdTrack::SetSyncFrameWalk);
					properties[23] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("syncFrameWalkTwistLeft", &LocoCrowdTrack::SetSyncFrameWalkTwistLeft);
					properties[24] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("syncFrameWalkTwistRight", &LocoCrowdTrack::SetSyncFrameWalkTwistRight);
					properties[25] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("syncFrameRun", &LocoCrowdTrack::SetSyncFrameRun);
					properties[26] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("syncFrameRunTwistLeft", &LocoCrowdTrack::SetSyncFrameRunTwistLeft);
					properties[27] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("syncFrameRunTwistRight", &LocoCrowdTrack::SetSyncFrameRunTwistRight);
					properties[28] = property;
					property = new fight::PropertyName<LocoCrowdTrack>("partition", &LocoCrowdTrack::SetPartition);
					properties[29] = property;
					property = new fight::PropertyIntConstRange<LocoCrowdTrack>("priority", &LocoCrowdTrack::SetPriority);
					properties[30] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("blendInTime", &LocoCrowdTrack::SetBlendInTime);
					properties[31] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("blendOutTime", &LocoCrowdTrack::SetBlendOutTime);
					properties[32] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("radiusMin", &LocoCrowdTrack::SetRadiusMin);
					properties[33] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("radiusMax", &LocoCrowdTrack::SetRadiusMax);
					properties[34] = property;
					property = new fight::PropertyFloatConstRange<LocoCrowdTrack>("offsetMax", &LocoCrowdTrack::SetOffsetMax);
					properties[35] = property;
					property = new fight::PropertyBranch<LocoCrowdTrack>("branch", &LocoCrowdTrack::SetBranch);
					properties[36] = property;
					property = new fight::PropertyIntConstRange<LocoCrowdTrack>("interruptPriority", &LocoCrowdTrack::SetInterruptPriority);
					properties[37] = property;
					property = new fight::PropertyConditionGroup<LocoCrowdTrack>("conditions", &LocoCrowdTrack::SetConditions);
					properties[38] = property;
					fight::RegisterPropertyList(properties, &gLocoCrowdTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101506B0
			fight::TrackFactory* CreateLocoCrowdTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<LocoCrowdTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10150C20
			void RegisterLocoCrowdTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<LocoCrowdTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gCrowdTestTrackProperties;  // 0x112543B8

			// FUNCTION: ENGINE 0x1014F8C0
			bool CrowdTestTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F8E0
			bool CrowdTestTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F900
			bool CrowdTestTrack::SetVelocityCap(float newValue)
			{
				velocityCap = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F920
			bool CrowdTestTrack::SetRadiusMin(float newValue)
			{
				radiusMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F940
			bool CrowdTestTrack::SetRadiusMax(float newValue)
			{
				radiusMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F960
			bool CrowdTestTrack::SetOffsetMax(float newValue)
			{
				offsetMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F980
			fight::BranchHolder* CrowdTestTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x1014F990
			bool CrowdTestTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1014F9A0
			fight::ConditionList* CrowdTestTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1014FAD0
			fight::Property* CrowdTestTrack::GetProperty(int index)
			{
				return gCrowdTestTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1014FAF0
			void CrowdTestTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCrowdTestTrackProperties);
			}

			// FUNCTION: ENGINE 0x1014FB00
			CrowdTestTrack::CrowdTestTrack() : branch(0), offsetMax(0.0f), radiusMax(0.0f), radiusMin(0.0f), timeBegin(0.0f), timeEnd(-1.0f), velocityCap(0.0f), priority(0)
			{
			}

			// FUNCTION: ENGINE 0x1014FB70
			float CrowdTestTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1014FB80
			float CrowdTestTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1014FB90
			CrowdTestTrack::~CrowdTestTrack()
			{
			}

			// FUNCTION: ENGINE 0x10150940
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CrowdTestTrack::RegisterProperties()
			{
				if (gCrowdTestTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CrowdTestTrack>("timeBegin", &CrowdTestTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<CrowdTestTrack>("timeEnd", &CrowdTestTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<CrowdTestTrack>("velocityCap", &CrowdTestTrack::SetVelocityCap);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<CrowdTestTrack>("radiusMin", &CrowdTestTrack::SetRadiusMin);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<CrowdTestTrack>("radiusMax", &CrowdTestTrack::SetRadiusMax);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<CrowdTestTrack>("offsetMax", &CrowdTestTrack::SetOffsetMax);
					properties[5] = property;
					property = new fight::PropertyBranch<CrowdTestTrack>("branch", &CrowdTestTrack::SetBranch);
					properties[6] = property;
					property = new fight::PropertyIntConstRange<CrowdTestTrack>("priority", &CrowdTestTrack::SetPriority);
					properties[7] = property;
					property = new fight::PropertyConditionGroup<CrowdTestTrack>("conditions", &CrowdTestTrack::SetConditions);
					properties[8] = property;
					fight::RegisterPropertyList(properties, &gCrowdTestTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101506E0
			fight::TrackFactory* CreateCrowdTestTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CrowdTestTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10150C50
			void RegisterCrowdTestTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CrowdTestTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<CrowdMinDistanceCondition>;
			template class fight::PropertyFloatConstRange<CrowdMinDistanceCondition>;
			template class fight::ConditionFactoryTemplate<CrowdMinDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<CrowdMinDistanceCondition>;
			template class fight::PropertyEnumConstList<CrowdPositionCondition>;
			template class fight::PropertyFloatConstRange<CrowdPositionCondition>;
			template class fight::ConditionFactoryTemplate<CrowdPositionCondition>;
			template class fight::ConditionFactoryCasterTemplate<CrowdPositionCondition>;
			template class fight::PropertyFloatConstRange<LocoCrowdTrack>;
			template class fight::PropertyName<LocoCrowdTrack>;
			template class fight::PropertyIntConstRange<LocoCrowdTrack>;
			template class fight::PropertyBranch<LocoCrowdTrack>;
			template class fight::PropertyConditionGroup<LocoCrowdTrack>;
			template class fight::TrackFactoryTemplate<LocoCrowdTrack>;
			template class fight::TrackFactoryCasterTemplate<LocoCrowdTrack>;
			template class fight::PropertyFloatConstRange<CrowdTestTrack>;
			template class fight::PropertyBranch<CrowdTestTrack>;
			template class fight::PropertyIntConstRange<CrowdTestTrack>;
			template class fight::PropertyConditionGroup<CrowdTestTrack>;
			template class fight::TrackFactoryTemplate<CrowdTestTrack>;
			template class fight::TrackFactoryCasterTemplate<CrowdTestTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1014FD20
// FUNCTION: ENGINE 0x1014FD50
// FUNCTION: ENGINE 0x1014FFB0
// FUNCTION: ENGINE 0x1014FFF0
// FUNCTION: ENGINE 0x10150000
// FUNCTION: ENGINE 0x10150030
// FUNCTION: ENGINE 0x10150040
// FUNCTION: ENGINE 0x10150070
// FUNCTION: ENGINE 0x10150080
// FUNCTION: ENGINE 0x101500B0
// FUNCTION: ENGINE 0x101500C0
// FUNCTION: ENGINE 0x101500F0
// FUNCTION: ENGINE 0x10150120
// FUNCTION: ENGINE 0x10150160
// FUNCTION: ENGINE 0x10150170
// FUNCTION: ENGINE 0x101501A0
// FUNCTION: ENGINE 0x101501C0
// FUNCTION: ENGINE 0x101501D0
// FUNCTION: ENGINE 0x10150200
// FUNCTION: ENGINE 0x10150230
// FUNCTION: ENGINE 0x10150240
// FUNCTION: ENGINE 0x10150280
// FUNCTION: ENGINE 0x10150290
// FUNCTION: ENGINE 0x101502C0
// FUNCTION: ENGINE 0x101502E0
// FUNCTION: ENGINE 0x101502F0
// FUNCTION: ENGINE 0x10150320
// FUNCTION: ENGINE 0x10150350
// FUNCTION: ENGINE 0x10150360
// FUNCTION: ENGINE 0x10150390
// FUNCTION: ENGINE 0x101503C0
// FUNCTION: ENGINE 0x101503D0
// FUNCTION: ENGINE 0x10150400
// FUNCTION: ENGINE 0x10150420
// FUNCTION: ENGINE 0x10150430
// FUNCTION: ENGINE 0x10150460
// FUNCTION: ENGINE 0x10150480
// FUNCTION: ENGINE 0x101504C0
// FUNCTION: ENGINE 0x101504E0
// FUNCTION: ENGINE 0x10150510
// FUNCTION: ENGINE 0x10150540
// FUNCTION: ENGINE 0x10150550
// FUNCTION: ENGINE 0x10150580
// FUNCTION: ENGINE 0x101505A0
// FUNCTION: ENGINE 0x101505D0
// FUNCTION: ENGINE 0x101505F0
// FUNCTION: ENGINE 0x10150600
// FUNCTION: ENGINE 0x10150630
// FUNCTION: ENGINE 0x10150C80
// FUNCTION: ENGINE 0x10150CB0
// FUNCTION: ENGINE 0x10150CD0
// FUNCTION: ENGINE 0x10150D00
// FUNCTION: ENGINE 0x10150D20
// FUNCTION: ENGINE 0x10150D50
// FUNCTION: ENGINE 0x10150D70
// FUNCTION: ENGINE 0x10150DA0
// FUNCTION: ENGINE 0x10151790
// FUNCTION: ENGINE 0x101517E0
// FUNCTION: ENGINE 0x10151830
// FUNCTION: ENGINE 0x10151880
// FUNCTION: ENGINE 0x101518B0
// FUNCTION: ENGINE 0x101518E0
