// Fight items of the motion group: HunterOnWallCondition, HunterCanHopAroundCornerCondition, HunterShortRangeLocoTrack, HunterShortRangeHopCornerTrack, HunterShortRangeCorner2Track, HunterLandedTrack (unit 0x1017D680 - 0x10180090; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_hunter.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gHunterOnWallConditionProperties;  // 0x11254720

			// FUNCTION: ENGINE 0x1017D680
			bool HunterOnWallCondition::SetAngleThreshold(float newValue)
			{
				angleThreshold = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DBE0
			fight::Property* HunterOnWallCondition::GetProperty(int index)
			{
				return gHunterOnWallConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1017DC00
			void HunterOnWallCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHunterOnWallConditionProperties);
			}

			// FUNCTION: ENGINE 0x1017DC10
			HunterOnWallCondition::HunterOnWallCondition() : fight::Condition(0), angleThreshold(1.0471976f)
			{
			}

			// FUNCTION: ENGINE 0x1017DC40
			HunterOnWallCondition::~HunterOnWallCondition()
			{
			}

			// FUNCTION: ENGINE 0x1017EBF0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HunterOnWallCondition::RegisterProperties()
			{
				if (gHunterOnWallConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<HunterOnWallCondition>("angleThreshold", &HunterOnWallCondition::SetAngleThreshold);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gHunterOnWallConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1017EAD0
			fight::ConditionFactory* CreateHunterOnWallConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HunterOnWallCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1017ED70
			void RegisterHunterOnWallConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HunterOnWallCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHunterCanHopAroundCornerConditionProperties;  // 0x11254724

			// FUNCTION: ENGINE 0x1017DCB0
			fight::Property* HunterCanHopAroundCornerCondition::GetProperty(int index)
			{
				return gHunterCanHopAroundCornerConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1017DCD0
			void HunterCanHopAroundCornerCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHunterCanHopAroundCornerConditionProperties);
			}

			// FUNCTION: ENGINE 0x1017DCE0
			HunterCanHopAroundCornerCondition::HunterCanHopAroundCornerCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1017DD00
			HunterCanHopAroundCornerCondition::~HunterCanHopAroundCornerCondition()
			{
			}

			// FUNCTION: ENGINE 0x1017DC50
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HunterCanHopAroundCornerCondition::RegisterProperties()
			{
				if (gHunterCanHopAroundCornerConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gHunterCanHopAroundCornerConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1017EB00
			fight::ConditionFactory* CreateHunterCanHopAroundCornerConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HunterCanHopAroundCornerCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1017EDA0
			void RegisterHunterCanHopAroundCornerConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HunterCanHopAroundCornerCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHunterShortRangeLocoTrackProperties;  // 0x11254728

			// FUNCTION: ENGINE 0x1017D6A0
			bool HunterShortRangeLocoTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D6C0
			bool HunterShortRangeLocoTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D6E0
			bool HunterShortRangeLocoTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D700
			bool HunterShortRangeLocoTrack::SetTurningVelocity(float newValue)
			{
				turningVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D730
			bool HunterShortRangeLocoTrack::SetCorneringTime(float newValue)
			{
				corneringTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D750
			bool HunterShortRangeLocoTrack::SetVelocityWalk(float newValue)
			{
				velocityWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D770
			bool HunterShortRangeLocoTrack::SetVelocityRun(float newValue)
			{
				velocityRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D790
			bool HunterShortRangeLocoTrack::SetPhase(float newValue)
			{
				phase = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DE40
			bool HunterShortRangeLocoTrack::SetLocomotion(const fight::Name& newValue)
			{
				locomotion = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DE60
			bool HunterShortRangeLocoTrack::SetAnimIdle(const fight::Name& newValue)
			{
				animIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DE80
			bool HunterShortRangeLocoTrack::SetAnimWalk(const fight::Name& newValue)
			{
				animWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DEA0
			bool HunterShortRangeLocoTrack::SetAnimRun(const fight::Name& newValue)
			{
				animRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D7B0
			bool HunterShortRangeLocoTrack::SetSyncFrameIdle(float newValue)
			{
				syncFrameIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D7D0
			bool HunterShortRangeLocoTrack::SetSyncFrameWalk(float newValue)
			{
				syncFrameWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D7F0
			bool HunterShortRangeLocoTrack::SetSyncFrameRun(float newValue)
			{
				syncFrameRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DEC0
			bool HunterShortRangeLocoTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D810
			bool HunterShortRangeLocoTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D830
			bool HunterShortRangeLocoTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D850
			bool HunterShortRangeLocoTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D870
			bool HunterShortRangeLocoTrack::SetDebugDraw(bool newValue)
			{
				debugDraw = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D890
			fight::BranchHolder* HunterShortRangeLocoTrack::SetOnCorner()
			{
				return &onCorner;
			}

			// FUNCTION: ENGINE 0x1017D8A0
			bool HunterShortRangeLocoTrack::SetOnCornerPriority(int newValue)
			{
				onCornerPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D8C0
			fight::ConditionList* HunterShortRangeLocoTrack::SetOnCornerConditions()
			{
				return &onCornerConditions;
			}

			// FUNCTION: ENGINE 0x1017DD10
			fight::Property* HunterShortRangeLocoTrack::GetProperty(int index)
			{
				return gHunterShortRangeLocoTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1017DD30
			void HunterShortRangeLocoTrack::ClearProperties()
			{
				fight::FreePropertyList(&gHunterShortRangeLocoTrackProperties);
			}

			// FUNCTION: ENGINE 0x1017E000
			HunterShortRangeLocoTrack::HunterShortRangeLocoTrack() : onCorner(0), acceleration(5e+01f), blendInTime(0.0f), blendOutTime(0.0f), corneringTime(0.2f), phase(-1.0f), syncFrameIdle(-1.0f), syncFrameRun(-1.0f), syncFrameWalk(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(6.2831855f), velocityRun(-1.0f), velocityWalk(-1.0f), onCornerPriority(0), priority(0), debugDraw(false)
			{
			}

			// FUNCTION: ENGINE 0x1017E120
			float HunterShortRangeLocoTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1017E130
			float HunterShortRangeLocoTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1017E140
			HunterShortRangeLocoTrack::~HunterShortRangeLocoTrack()
			{
			}

			// FUNCTION: ENGINE 0x1017F030
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HunterShortRangeLocoTrack::RegisterProperties()
			{
				if (gHunterShortRangeLocoTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<HunterShortRangeLocoTrack>("timeBegin", &HunterShortRangeLocoTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeLocoTrack>("timeEnd", &HunterShortRangeLocoTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeLocoTrack>("acceleration", &HunterShortRangeLocoTrack::SetAcceleration);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeLocoTrack>("turningVelocity", &HunterShortRangeLocoTrack::SetTurningVelocity);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeLocoTrack>("corneringTime", &HunterShortRangeLocoTrack::SetCorneringTime);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeLocoTrack>("velocityWalk", &HunterShortRangeLocoTrack::SetVelocityWalk);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeLocoTrack>("velocityRun", &HunterShortRangeLocoTrack::SetVelocityRun);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeLocoTrack>("phase", &HunterShortRangeLocoTrack::SetPhase);
					properties[7] = property;
					property = new fight::PropertyName<HunterShortRangeLocoTrack>("locomotion", &HunterShortRangeLocoTrack::SetLocomotion);
					properties[8] = property;
					property = new fight::PropertyName<HunterShortRangeLocoTrack>("animIdle", &HunterShortRangeLocoTrack::SetAnimIdle);
					properties[9] = property;
					property = new fight::PropertyName<HunterShortRangeLocoTrack>("animWalk", &HunterShortRangeLocoTrack::SetAnimWalk);
					properties[10] = property;
					property = new fight::PropertyName<HunterShortRangeLocoTrack>("animRun", &HunterShortRangeLocoTrack::SetAnimRun);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeLocoTrack>("syncFrameIdle", &HunterShortRangeLocoTrack::SetSyncFrameIdle);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeLocoTrack>("syncFrameWalk", &HunterShortRangeLocoTrack::SetSyncFrameWalk);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeLocoTrack>("syncFrameRun", &HunterShortRangeLocoTrack::SetSyncFrameRun);
					properties[14] = property;
					property = new fight::PropertyName<HunterShortRangeLocoTrack>("partition", &HunterShortRangeLocoTrack::SetPartition);
					properties[15] = property;
					property = new fight::PropertyIntConstRange<HunterShortRangeLocoTrack>("priority", &HunterShortRangeLocoTrack::SetPriority);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeLocoTrack>("blendInTime", &HunterShortRangeLocoTrack::SetBlendInTime);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeLocoTrack>("blendOutTime", &HunterShortRangeLocoTrack::SetBlendOutTime);
					properties[18] = property;
					property = new fight::PropertyBool<HunterShortRangeLocoTrack>("debugDraw", &HunterShortRangeLocoTrack::SetDebugDraw);
					properties[19] = property;
					property = new fight::PropertyBranch<HunterShortRangeLocoTrack>("onCorner", &HunterShortRangeLocoTrack::SetOnCorner);
					properties[20] = property;
					property = new fight::PropertyIntConstRange<HunterShortRangeLocoTrack>("onCornerPriority", &HunterShortRangeLocoTrack::SetOnCornerPriority);
					properties[21] = property;
					property = new fight::PropertyConditionGroup<HunterShortRangeLocoTrack>("onCornerConditions", &HunterShortRangeLocoTrack::SetOnCornerConditions);
					properties[22] = property;
					fight::RegisterPropertyList(properties, &gHunterShortRangeLocoTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1017EB30
			fight::TrackFactory* CreateHunterShortRangeLocoTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<HunterShortRangeLocoTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1017EDD0
			void RegisterHunterShortRangeLocoTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<HunterShortRangeLocoTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gHunterShortRangeHopCornerTrackProperties;  // 0x1125472C

			// FUNCTION: ENGINE 0x1017D8D0
			bool HunterShortRangeHopCornerTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D8F0
			bool HunterShortRangeHopCornerTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D910
			bool HunterShortRangeHopCornerTrack::SetVelocityRunUp(float newValue)
			{
				velocityRunUp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D930
			bool HunterShortRangeHopCornerTrack::SetVelocityHorizontal(float newValue)
			{
				velocityHorizontal = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D950
			bool HunterShortRangeHopCornerTrack::SetGravity(float newValue)
			{
				gravity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D970
			bool HunterShortRangeHopCornerTrack::SetOrientationBlendTime(float newValue)
			{
				orientationBlendTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D990
			bool HunterShortRangeHopCornerTrack::SetMaxFallSpeed(float newValue)
			{
				maxFallSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DEE0
			bool HunterShortRangeHopCornerTrack::SetNewSupportingLimb(const fight::Name& newValue)
			{
				newSupportingLimb = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D9B0
			bool HunterShortRangeHopCornerTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D9C0
			bool HunterShortRangeHopCornerTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017D9E0
			bool HunterShortRangeHopCornerTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DD40
			fight::Property* HunterShortRangeHopCornerTrack::GetProperty(int index)
			{
				return gHunterShortRangeHopCornerTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1017DD60
			void HunterShortRangeHopCornerTrack::ClearProperties()
			{
				fight::FreePropertyList(&gHunterShortRangeHopCornerTrackProperties);
			}

			// FUNCTION: ENGINE 0x1017E170
			HunterShortRangeHopCornerTrack::HunterShortRangeHopCornerTrack() : blendInTime(0.0f), blendOutTime(0.0f), gravity(2e+01f), maxFallSpeed(5e+01f), orientationBlendTime(0.2f), timeBegin(0.0f), timeEnd(-1.0f), velocityHorizontal(5.0f), velocityRunUp(15.0f), priority(-1)
			{
			}

			// FUNCTION: ENGINE 0x1017E220
			float HunterShortRangeHopCornerTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1017E230
			float HunterShortRangeHopCornerTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1017E240
			HunterShortRangeHopCornerTrack::~HunterShortRangeHopCornerTrack()
			{
			}

			// FUNCTION: ENGINE 0x1017F610
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HunterShortRangeHopCornerTrack::RegisterProperties()
			{
				if (gHunterShortRangeHopCornerTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<HunterShortRangeHopCornerTrack>("timeBegin", &HunterShortRangeHopCornerTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeHopCornerTrack>("timeEnd", &HunterShortRangeHopCornerTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeHopCornerTrack>("velocityRunUp", &HunterShortRangeHopCornerTrack::SetVelocityRunUp);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeHopCornerTrack>("velocityHorizontal", &HunterShortRangeHopCornerTrack::SetVelocityHorizontal);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeHopCornerTrack>("gravity", &HunterShortRangeHopCornerTrack::SetGravity);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeHopCornerTrack>("orientationBlendTime", &HunterShortRangeHopCornerTrack::SetOrientationBlendTime);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeHopCornerTrack>("maxFallSpeed", &HunterShortRangeHopCornerTrack::SetMaxFallSpeed);
					properties[6] = property;
					property = new fight::PropertyNameList<HunterShortRangeHopCornerTrack>("newSupportingLimb", &HunterShortRangeHopCornerTrack::SetNewSupportingLimb);
					properties[7] = property;
					property = new fight::PropertyIntConstRange<HunterShortRangeHopCornerTrack>("priority", &HunterShortRangeHopCornerTrack::SetPriority);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeHopCornerTrack>("blendInTime", &HunterShortRangeHopCornerTrack::SetBlendInTime);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeHopCornerTrack>("blendOutTime", &HunterShortRangeHopCornerTrack::SetBlendOutTime);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gHunterShortRangeHopCornerTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1017EB60
			fight::TrackFactory* CreateHunterShortRangeHopCornerTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<HunterShortRangeHopCornerTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1017EE00
			void RegisterHunterShortRangeHopCornerTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<HunterShortRangeHopCornerTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gHunterShortRangeCorner2TrackProperties;  // 0x11254730

			// FUNCTION: ENGINE 0x1017DA00
			bool HunterShortRangeCorner2Track::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DA20
			bool HunterShortRangeCorner2Track::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DA40
			bool HunterShortRangeCorner2Track::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DA60
			bool HunterShortRangeCorner2Track::SetCorneringTime(float newValue)
			{
				corneringTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DA80
			bool HunterShortRangeCorner2Track::SetVelocityWalk(float newValue)
			{
				velocityWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DAA0
			bool HunterShortRangeCorner2Track::SetVelocityRun(float newValue)
			{
				velocityRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DAC0
			bool HunterShortRangeCorner2Track::SetPhase(float newValue)
			{
				phase = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DF00
			bool HunterShortRangeCorner2Track::SetLocomotion(const fight::Name& newValue)
			{
				locomotion = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DF20
			bool HunterShortRangeCorner2Track::SetAnimIdle(const fight::Name& newValue)
			{
				animIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DF40
			bool HunterShortRangeCorner2Track::SetAnimWalk(const fight::Name& newValue)
			{
				animWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DF60
			bool HunterShortRangeCorner2Track::SetAnimRun(const fight::Name& newValue)
			{
				animRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DAE0
			bool HunterShortRangeCorner2Track::SetSyncFrameIdle(float newValue)
			{
				syncFrameIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DB00
			bool HunterShortRangeCorner2Track::SetSyncFrameWalk(float newValue)
			{
				syncFrameWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DB20
			bool HunterShortRangeCorner2Track::SetSyncFrameRun(float newValue)
			{
				syncFrameRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DF80
			bool HunterShortRangeCorner2Track::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DB40
			bool HunterShortRangeCorner2Track::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DB50
			bool HunterShortRangeCorner2Track::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DB70
			bool HunterShortRangeCorner2Track::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DB90
			bool HunterShortRangeCorner2Track::SetDebugDraw(bool newValue)
			{
				debugDraw = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DD70
			fight::Property* HunterShortRangeCorner2Track::GetProperty(int index)
			{
				return gHunterShortRangeCorner2TrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1017DD90
			void HunterShortRangeCorner2Track::ClearProperties()
			{
				fight::FreePropertyList(&gHunterShortRangeCorner2TrackProperties);
			}

			// FUNCTION: ENGINE 0x1017E250
			HunterShortRangeCorner2Track::HunterShortRangeCorner2Track() : acceleration(5e+01f), blendInTime(0.0f), blendOutTime(0.0f), corneringTime(0.2f), phase(-1.0f), syncFrameIdle(-1.0f), syncFrameRun(-1.0f), syncFrameWalk(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), velocityRun(-1.0f), velocityWalk(-1.0f), priority(0), debugDraw(false)
			{
			}

			// FUNCTION: ENGINE 0x1017E310
			float HunterShortRangeCorner2Track::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1017E320
			float HunterShortRangeCorner2Track::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1017E330
			HunterShortRangeCorner2Track::~HunterShortRangeCorner2Track()
			{
			}

			// FUNCTION: ENGINE 0x1017F910
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HunterShortRangeCorner2Track::RegisterProperties()
			{
				if (gHunterShortRangeCorner2TrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<HunterShortRangeCorner2Track>("timeBegin", &HunterShortRangeCorner2Track::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeCorner2Track>("timeEnd", &HunterShortRangeCorner2Track::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeCorner2Track>("acceleration", &HunterShortRangeCorner2Track::SetAcceleration);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeCorner2Track>("corneringTime", &HunterShortRangeCorner2Track::SetCorneringTime);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeCorner2Track>("velocityWalk", &HunterShortRangeCorner2Track::SetVelocityWalk);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeCorner2Track>("velocityRun", &HunterShortRangeCorner2Track::SetVelocityRun);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeCorner2Track>("phase", &HunterShortRangeCorner2Track::SetPhase);
					properties[6] = property;
					property = new fight::PropertyName<HunterShortRangeCorner2Track>("locomotion", &HunterShortRangeCorner2Track::SetLocomotion);
					properties[7] = property;
					property = new fight::PropertyName<HunterShortRangeCorner2Track>("animIdle", &HunterShortRangeCorner2Track::SetAnimIdle);
					properties[8] = property;
					property = new fight::PropertyName<HunterShortRangeCorner2Track>("animWalk", &HunterShortRangeCorner2Track::SetAnimWalk);
					properties[9] = property;
					property = new fight::PropertyName<HunterShortRangeCorner2Track>("animRun", &HunterShortRangeCorner2Track::SetAnimRun);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeCorner2Track>("syncFrameIdle", &HunterShortRangeCorner2Track::SetSyncFrameIdle);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeCorner2Track>("syncFrameWalk", &HunterShortRangeCorner2Track::SetSyncFrameWalk);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeCorner2Track>("syncFrameRun", &HunterShortRangeCorner2Track::SetSyncFrameRun);
					properties[13] = property;
					property = new fight::PropertyName<HunterShortRangeCorner2Track>("partition", &HunterShortRangeCorner2Track::SetPartition);
					properties[14] = property;
					property = new fight::PropertyIntConstRange<HunterShortRangeCorner2Track>("priority", &HunterShortRangeCorner2Track::SetPriority);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeCorner2Track>("blendInTime", &HunterShortRangeCorner2Track::SetBlendInTime);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<HunterShortRangeCorner2Track>("blendOutTime", &HunterShortRangeCorner2Track::SetBlendOutTime);
					properties[17] = property;
					property = new fight::PropertyBool<HunterShortRangeCorner2Track>("debugDraw", &HunterShortRangeCorner2Track::SetDebugDraw);
					properties[18] = property;
					fight::RegisterPropertyList(properties, &gHunterShortRangeCorner2TrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1017EB90
			fight::TrackFactory* CreateHunterShortRangeCorner2TrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<HunterShortRangeCorner2Track> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1017EE30
			void RegisterHunterShortRangeCorner2TrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<HunterShortRangeCorner2Track> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gHunterLandedTrackProperties;  // 0x11254734

			// FUNCTION: ENGINE 0x1017DBA0
			bool HunterLandedTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DBC0
			bool HunterLandedTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017DDA0
			fight::Property* HunterLandedTrack::GetProperty(int index)
			{
				return gHunterLandedTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1017DDC0
			void HunterLandedTrack::ClearProperties()
			{
				fight::FreePropertyList(&gHunterLandedTrackProperties);
			}

			// FUNCTION: ENGINE 0x1017DDD0
			HunterLandedTrack::HunterLandedTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1017DE10
			float HunterLandedTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1017DE20
			float HunterLandedTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1017DE30
			HunterLandedTrack::~HunterLandedTrack()
			{
			}

			// FUNCTION: ENGINE 0x1017EC90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HunterLandedTrack::RegisterProperties()
			{
				if (gHunterLandedTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<HunterLandedTrack>("timeBegin", &HunterLandedTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HunterLandedTrack>("timeEnd", &HunterLandedTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gHunterLandedTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1017EBC0
			fight::TrackFactory* CreateHunterLandedTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<HunterLandedTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1017EE60
			void RegisterHunterLandedTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<HunterLandedTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<HunterOnWallCondition>;
			template class fight::ConditionFactoryTemplate<HunterOnWallCondition>;
			template class fight::ConditionFactoryCasterTemplate<HunterOnWallCondition>;
			template class fight::ConditionFactoryTemplate<HunterCanHopAroundCornerCondition>;
			template class fight::ConditionFactoryCasterTemplate<HunterCanHopAroundCornerCondition>;
			template class fight::PropertyFloatConstRange<HunterShortRangeLocoTrack>;
			template class fight::PropertyName<HunterShortRangeLocoTrack>;
			template class fight::PropertyIntConstRange<HunterShortRangeLocoTrack>;
			template class fight::PropertyBool<HunterShortRangeLocoTrack>;
			template class fight::PropertyBranch<HunterShortRangeLocoTrack>;
			template class fight::PropertyConditionGroup<HunterShortRangeLocoTrack>;
			template class fight::TrackFactoryTemplate<HunterShortRangeLocoTrack>;
			template class fight::TrackFactoryCasterTemplate<HunterShortRangeLocoTrack>;
			template class fight::PropertyFloatConstRange<HunterShortRangeHopCornerTrack>;
			template class fight::PropertyNameList<HunterShortRangeHopCornerTrack>;
			template class fight::PropertyIntConstRange<HunterShortRangeHopCornerTrack>;
			template class fight::TrackFactoryTemplate<HunterShortRangeHopCornerTrack>;
			template class fight::TrackFactoryCasterTemplate<HunterShortRangeHopCornerTrack>;
			template class fight::PropertyFloatConstRange<HunterShortRangeCorner2Track>;
			template class fight::PropertyName<HunterShortRangeCorner2Track>;
			template class fight::PropertyIntConstRange<HunterShortRangeCorner2Track>;
			template class fight::PropertyBool<HunterShortRangeCorner2Track>;
			template class fight::TrackFactoryTemplate<HunterShortRangeCorner2Track>;
			template class fight::TrackFactoryCasterTemplate<HunterShortRangeCorner2Track>;
			template class fight::PropertyFloatConstRange<HunterLandedTrack>;
			template class fight::TrackFactoryTemplate<HunterLandedTrack>;
			template class fight::TrackFactoryCasterTemplate<HunterLandedTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1017DFA0
// FUNCTION: ENGINE 0x1017DFD0
// FUNCTION: ENGINE 0x1017E340
// FUNCTION: ENGINE 0x1017E370
// FUNCTION: ENGINE 0x1017E380
// FUNCTION: ENGINE 0x1017E3B0
// FUNCTION: ENGINE 0x1017E3C0
// FUNCTION: ENGINE 0x1017E3F0
// FUNCTION: ENGINE 0x1017E420
// FUNCTION: ENGINE 0x1017E440
// FUNCTION: ENGINE 0x1017E490
// FUNCTION: ENGINE 0x1017E4A0
// FUNCTION: ENGINE 0x1017E4D0
// FUNCTION: ENGINE 0x1017E4E0
// FUNCTION: ENGINE 0x1017E510
// FUNCTION: ENGINE 0x1017E520
// FUNCTION: ENGINE 0x1017E550
// FUNCTION: ENGINE 0x1017E560
// FUNCTION: ENGINE 0x1017E590
// FUNCTION: ENGINE 0x1017E5C0
// FUNCTION: ENGINE 0x1017E5F0
// FUNCTION: ENGINE 0x1017E620
// FUNCTION: ENGINE 0x1017E650
// FUNCTION: ENGINE 0x1017E680
// FUNCTION: ENGINE 0x1017E690
// FUNCTION: ENGINE 0x1017E6C0
// FUNCTION: ENGINE 0x1017E6F0
// FUNCTION: ENGINE 0x1017E700
// FUNCTION: ENGINE 0x1017E730
// FUNCTION: ENGINE 0x1017E750
// FUNCTION: ENGINE 0x1017E760
// FUNCTION: ENGINE 0x1017E790
// FUNCTION: ENGINE 0x1017E7B0
// FUNCTION: ENGINE 0x1017E7C0
// FUNCTION: ENGINE 0x1017E7F0
// FUNCTION: ENGINE 0x1017E810
// FUNCTION: ENGINE 0x1017E840
// FUNCTION: ENGINE 0x1017E860
// FUNCTION: ENGINE 0x1017E890
// FUNCTION: ENGINE 0x1017E8C0
// FUNCTION: ENGINE 0x1017E8D0
// FUNCTION: ENGINE 0x1017E900
// FUNCTION: ENGINE 0x1017E920
// FUNCTION: ENGINE 0x1017E930
// FUNCTION: ENGINE 0x1017E960
// FUNCTION: ENGINE 0x1017E990
// FUNCTION: ENGINE 0x1017E9A0
// FUNCTION: ENGINE 0x1017E9D0
// FUNCTION: ENGINE 0x1017E9F0
// FUNCTION: ENGINE 0x1017EA00
// FUNCTION: ENGINE 0x1017EA30
// FUNCTION: ENGINE 0x1017EA50
// FUNCTION: ENGINE 0x1017EA60
// FUNCTION: ENGINE 0x1017EA90
// FUNCTION: ENGINE 0x1017EAC0
// FUNCTION: ENGINE 0x1017EE90
// FUNCTION: ENGINE 0x1017EEC0
// FUNCTION: ENGINE 0x1017EEE0
// FUNCTION: ENGINE 0x1017EF10
// FUNCTION: ENGINE 0x1017EF30
// FUNCTION: ENGINE 0x1017EF40
// FUNCTION: ENGINE 0x1017EF70
// FUNCTION: ENGINE 0x1017EF90
// FUNCTION: ENGINE 0x1017EFC0
// FUNCTION: ENGINE 0x1017EFE0
// FUNCTION: ENGINE 0x1017F010
// FUNCTION: ENGINE 0x1017FE00
// FUNCTION: ENGINE 0x1017FE50
// FUNCTION: ENGINE 0x1017FEA0
// FUNCTION: ENGINE 0x1017FED0
// FUNCTION: ENGINE 0x1017FF00
// FUNCTION: ENGINE 0x1017FF30
// FUNCTION: ENGINE 0x1017FF50
// FUNCTION: ENGINE 0x1017FF80
// FUNCTION: ENGINE 0x1017FFA0
// FUNCTION: ENGINE 0x1017FFF0
// FUNCTION: ENGINE 0x10180040
