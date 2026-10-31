// Fight items of the motion group: InsideJumpInBoundaryCondition, DistanceFromWaterSurfaceCondition, HeliBoundaryStatusCondition, FromWaterSetJumpToTrack, IgnoreWaterReactionTrack, JumpFromWaterTrack, OrientTowardsJumpInPositionTrack (unit 0x10144950 - 0x10146A60; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/boundary.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gInsideJumpInBoundaryConditionProperties;  // 0x112542EC

			// FUNCTION: ENGINE 0x10144950
			bool InsideJumpInBoundaryCondition::SetInsideJumpInBoundary(bool newValue)
			{
				insideJumpInBoundary = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144CD0
			fight::Property* InsideJumpInBoundaryCondition::GetProperty(int index)
			{
				return gInsideJumpInBoundaryConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10144CF0
			void InsideJumpInBoundaryCondition::ClearProperties()
			{
				fight::FreePropertyList(&gInsideJumpInBoundaryConditionProperties);
			}

			// FUNCTION: ENGINE 0x10144D00
			InsideJumpInBoundaryCondition::InsideJumpInBoundaryCondition() : fight::Condition(0), insideJumpInBoundary(true)
			{
			}

			// FUNCTION: ENGINE 0x10144D20
			InsideJumpInBoundaryCondition::~InsideJumpInBoundaryCondition()
			{
			}

			// FUNCTION: ENGINE 0x10145A70
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void InsideJumpInBoundaryCondition::RegisterProperties()
			{
				if (gInsideJumpInBoundaryConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<InsideJumpInBoundaryCondition>("insideJumpInBoundary", &InsideJumpInBoundaryCondition::SetInsideJumpInBoundary);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gInsideJumpInBoundaryConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10145920
			fight::ConditionFactory* CreateInsideJumpInBoundaryConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InsideJumpInBoundaryCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101464B0
			void RegisterInsideJumpInBoundaryConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InsideJumpInBoundaryCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDistanceFromWaterSurfaceConditionProperties;  // 0x112542F0

			// FUNCTION: ENGINE 0x10144960
			bool DistanceFromWaterSurfaceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144970
			bool DistanceFromWaterSurfaceCondition::SetDistanceFromSurface(float newValue)
			{
				distanceFromSurface = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144D30
			fight::Property* DistanceFromWaterSurfaceCondition::GetProperty(int index)
			{
				return gDistanceFromWaterSurfaceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10144D50
			void DistanceFromWaterSurfaceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDistanceFromWaterSurfaceConditionProperties);
			}

			// FUNCTION: ENGINE 0x10144D60
			DistanceFromWaterSurfaceCondition::DistanceFromWaterSurfaceCondition() : fight::Condition(0), distanceFromSurface(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10144D90
			DistanceFromWaterSurfaceCondition::~DistanceFromWaterSurfaceCondition()
			{
			}

			// FUNCTION: ENGINE 0x10145B10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DistanceFromWaterSurfaceCondition::RegisterProperties()
			{
				if (gDistanceFromWaterSurfaceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<DistanceFromWaterSurfaceCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &DistanceFromWaterSurfaceCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DistanceFromWaterSurfaceCondition>("distanceFromSurface", &DistanceFromWaterSurfaceCondition::SetDistanceFromSurface);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gDistanceFromWaterSurfaceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10145950
			fight::ConditionFactory* CreateDistanceFromWaterSurfaceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DistanceFromWaterSurfaceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101464E0
			void RegisterDistanceFromWaterSurfaceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DistanceFromWaterSurfaceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHeliBoundaryStatusConditionProperties;  // 0x112542F4

			// FUNCTION: ENGINE 0x10144990
			bool HeliBoundaryStatusCondition::SetHeliBoundaryStatus(int newValue)
			{
				heliBoundaryStatus = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144DA0
			fight::Property* HeliBoundaryStatusCondition::GetProperty(int index)
			{
				return gHeliBoundaryStatusConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10144DC0
			void HeliBoundaryStatusCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHeliBoundaryStatusConditionProperties);
			}

			// FUNCTION: ENGINE 0x10144DD0
			HeliBoundaryStatusCondition::HeliBoundaryStatusCondition() : fight::Condition(0), heliBoundaryStatus(0)
			{
			}

			// FUNCTION: ENGINE 0x10144E00
			HeliBoundaryStatusCondition::~HeliBoundaryStatusCondition()
			{
			}

			// FUNCTION: ENGINE 0x10145C00
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HeliBoundaryStatusCondition::RegisterProperties()
			{
				if (gHeliBoundaryStatusConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<HeliBoundaryStatusCondition>("heliBoundaryStatus", gHeliBoundaryStatusConditionHeliBoundaryStatusTable, gHeliBoundaryStatusConditionHeliBoundaryStatusCount, &HeliBoundaryStatusCondition::SetHeliBoundaryStatus);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gHeliBoundaryStatusConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10145980
			fight::ConditionFactory* CreateHeliBoundaryStatusConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HeliBoundaryStatusCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10146510
			void RegisterHeliBoundaryStatusConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HeliBoundaryStatusCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gFromWaterSetJumpToTrackProperties;  // 0x112542F8

			// FUNCTION: ENGINE 0x101449A0
			bool FromWaterSetJumpToTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144E10
			fight::Property* FromWaterSetJumpToTrack::GetProperty(int index)
			{
				return gFromWaterSetJumpToTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10144E30
			void FromWaterSetJumpToTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFromWaterSetJumpToTrackProperties);
			}

			// FUNCTION: ENGINE 0x10144E40
			FromWaterSetJumpToTrack::FromWaterSetJumpToTrack() : timeBegin(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x10144E60
			float FromWaterSetJumpToTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10144E70
			float FromWaterSetJumpToTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10144E80
			FromWaterSetJumpToTrack::~FromWaterSetJumpToTrack()
			{
			}

			// FUNCTION: ENGINE 0x10145CB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FromWaterSetJumpToTrack::RegisterProperties()
			{
				if (gFromWaterSetJumpToTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FromWaterSetJumpToTrack>("timeBegin", &FromWaterSetJumpToTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gFromWaterSetJumpToTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101459B0
			fight::TrackFactory* CreateFromWaterSetJumpToTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FromWaterSetJumpToTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10146540
			void RegisterFromWaterSetJumpToTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FromWaterSetJumpToTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gIgnoreWaterReactionTrackProperties;  // 0x112542FC

			// FUNCTION: ENGINE 0x101449C0
			bool IgnoreWaterReactionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101449E0
			bool IgnoreWaterReactionTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144E90
			fight::Property* IgnoreWaterReactionTrack::GetProperty(int index)
			{
				return gIgnoreWaterReactionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10144EB0
			void IgnoreWaterReactionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gIgnoreWaterReactionTrackProperties);
			}

			// FUNCTION: ENGINE 0x10144EC0
			IgnoreWaterReactionTrack::IgnoreWaterReactionTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10144F00
			float IgnoreWaterReactionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10144F10
			float IgnoreWaterReactionTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10144F20
			IgnoreWaterReactionTrack::~IgnoreWaterReactionTrack()
			{
			}

			// FUNCTION: ENGINE 0x10145D50
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IgnoreWaterReactionTrack::RegisterProperties()
			{
				if (gIgnoreWaterReactionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<IgnoreWaterReactionTrack>("timeBegin", &IgnoreWaterReactionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<IgnoreWaterReactionTrack>("timeEnd", &IgnoreWaterReactionTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gIgnoreWaterReactionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101459E0
			fight::TrackFactory* CreateIgnoreWaterReactionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<IgnoreWaterReactionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10146570
			void RegisterIgnoreWaterReactionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<IgnoreWaterReactionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gJumpFromWaterTrackProperties;  // 0x11254300

			// FUNCTION: ENGINE 0x10144A00
			bool JumpFromWaterTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144A20
			bool JumpFromWaterTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144A40
			bool JumpFromWaterTrack::SetFlightTimeMin(float newValue)
			{
				flightTimeMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144A60
			bool JumpFromWaterTrack::SetFlightTimeMax(float newValue)
			{
				flightTimeMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144A80
			bool JumpFromWaterTrack::SetUpOvershootDistance(float newValue)
			{
				upOvershootDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144AA0
			bool JumpFromWaterTrack::SetForwardDistanceMin(float newValue)
			{
				forwardDistanceMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144AC0
			bool JumpFromWaterTrack::SetForwardDistanceMax(float newValue)
			{
				forwardDistanceMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144AE0
			bool JumpFromWaterTrack::SetTurningVelocityMin(float newValue)
			{
				turningVelocityMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10144B00
			bool JumpFromWaterTrack::SetTurningVelocityMinForwardSpeedCap(float newValue)
			{
				turningVelocityMinForwardSpeedCap = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144B20
			bool JumpFromWaterTrack::SetTurningVelocityMax(float newValue)
			{
				turningVelocityMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10144B40
			bool JumpFromWaterTrack::SetTurningVelocityMaxForwardSpeedCap(float newValue)
			{
				turningVelocityMaxForwardSpeedCap = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144B60
			bool JumpFromWaterTrack::SetMaxFallSpeed(float newValue)
			{
				maxFallSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144B80
			bool JumpFromWaterTrack::SetForwardVelocityScale(float newValue)
			{
				forwardVelocityScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144BA0
			bool JumpFromWaterTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144BB0
			bool JumpFromWaterTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144BD0
			bool JumpFromWaterTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144F30
			fight::Property* JumpFromWaterTrack::GetProperty(int index)
			{
				return gJumpFromWaterTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10144F50
			void JumpFromWaterTrack::ClearProperties()
			{
				fight::FreePropertyList(&gJumpFromWaterTrackProperties);
			}

			// FUNCTION: ENGINE 0x10144F60
			JumpFromWaterTrack::JumpFromWaterTrack() : blendInTime(0.0f), blendOutTime(0.0f), flightTimeMax(-1.0f), flightTimeMin(-1.0f), forwardDistanceMax(1.0f), forwardDistanceMin(1.0f), forwardVelocityScale(1.0f), maxFallSpeed(5e+01f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocityMax(0.0f), turningVelocityMaxForwardSpeedCap(0.0f), turningVelocityMin(0.0f), turningVelocityMinForwardSpeedCap(0.0f), upOvershootDistance(0.0f), priority(-5)
			{
			}

			// FUNCTION: ENGINE 0x10145000
			float JumpFromWaterTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10145010
			float JumpFromWaterTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10145020
			JumpFromWaterTrack::~JumpFromWaterTrack()
			{
			}

			// FUNCTION: ENGINE 0x10145E30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void JumpFromWaterTrack::RegisterProperties()
			{
				if (gJumpFromWaterTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<JumpFromWaterTrack>("timeBegin", &JumpFromWaterTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<JumpFromWaterTrack>("timeEnd", &JumpFromWaterTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<JumpFromWaterTrack>("flightTimeMin", &JumpFromWaterTrack::SetFlightTimeMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<JumpFromWaterTrack>("flightTimeMax", &JumpFromWaterTrack::SetFlightTimeMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<JumpFromWaterTrack>("upOvershootDistance", &JumpFromWaterTrack::SetUpOvershootDistance);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<JumpFromWaterTrack>("forwardDistanceMin", &JumpFromWaterTrack::SetForwardDistanceMin);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<JumpFromWaterTrack>("forwardDistanceMax", &JumpFromWaterTrack::SetForwardDistanceMax);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<JumpFromWaterTrack>("turningVelocityMin", &JumpFromWaterTrack::SetTurningVelocityMin);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<JumpFromWaterTrack>("turningVelocityMinForwardSpeedCap", &JumpFromWaterTrack::SetTurningVelocityMinForwardSpeedCap);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<JumpFromWaterTrack>("turningVelocityMax", &JumpFromWaterTrack::SetTurningVelocityMax);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<JumpFromWaterTrack>("turningVelocityMaxForwardSpeedCap", &JumpFromWaterTrack::SetTurningVelocityMaxForwardSpeedCap);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<JumpFromWaterTrack>("maxFallSpeed", &JumpFromWaterTrack::SetMaxFallSpeed);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<JumpFromWaterTrack>("forwardVelocityScale", &JumpFromWaterTrack::SetForwardVelocityScale);
					properties[12] = property;
					property = new fight::PropertyIntConstRange<JumpFromWaterTrack>("priority", &JumpFromWaterTrack::SetPriority);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<JumpFromWaterTrack>("blendInTime", &JumpFromWaterTrack::SetBlendInTime);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<JumpFromWaterTrack>("blendOutTime", &JumpFromWaterTrack::SetBlendOutTime);
					properties[15] = property;
					fight::RegisterPropertyList(properties, &gJumpFromWaterTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10145A10
			fight::TrackFactory* CreateJumpFromWaterTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<JumpFromWaterTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101465A0
			void RegisterJumpFromWaterTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<JumpFromWaterTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gOrientTowardsJumpInPositionTrackProperties;  // 0x11254304

			// FUNCTION: ENGINE 0x10144BF0
			bool OrientTowardsJumpInPositionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144C10
			bool OrientTowardsJumpInPositionTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144C30
			bool OrientTowardsJumpInPositionTrack::SetTurningVelocity(float newValue)
			{
				turningVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10144C50
			bool OrientTowardsJumpInPositionTrack::SetOrientationCutOffDistance(float newValue)
			{
				orientationCutOffDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144C70
			bool OrientTowardsJumpInPositionTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144C80
			bool OrientTowardsJumpInPositionTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144CA0
			bool OrientTowardsJumpInPositionTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10144CC0
			bool OrientTowardsJumpInPositionTrack::SetUseJumpDestination(bool newValue)
			{
				useJumpDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10145030
			fight::Property* OrientTowardsJumpInPositionTrack::GetProperty(int index)
			{
				return gOrientTowardsJumpInPositionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10145050
			void OrientTowardsJumpInPositionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gOrientTowardsJumpInPositionTrackProperties);
			}

			// FUNCTION: ENGINE 0x10145060
			OrientTowardsJumpInPositionTrack::OrientTowardsJumpInPositionTrack() : blendInTime(0.0f), blendOutTime(0.0f), orientationCutOffDistance(5.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(0.0f), priority(-5), useJumpDestination(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101450D0
			float OrientTowardsJumpInPositionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101450E0
			float OrientTowardsJumpInPositionTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101450F0
			OrientTowardsJumpInPositionTrack::~OrientTowardsJumpInPositionTrack()
			{
			}

			// FUNCTION: ENGINE 0x10146260
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void OrientTowardsJumpInPositionTrack::RegisterProperties()
			{
				if (gOrientTowardsJumpInPositionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<OrientTowardsJumpInPositionTrack>("timeBegin", &OrientTowardsJumpInPositionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<OrientTowardsJumpInPositionTrack>("timeEnd", &OrientTowardsJumpInPositionTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<OrientTowardsJumpInPositionTrack>("turningVelocity", &OrientTowardsJumpInPositionTrack::SetTurningVelocity);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<OrientTowardsJumpInPositionTrack>("orientationCutOffDistance", &OrientTowardsJumpInPositionTrack::SetOrientationCutOffDistance);
					properties[3] = property;
					property = new fight::PropertyIntConstRange<OrientTowardsJumpInPositionTrack>("priority", &OrientTowardsJumpInPositionTrack::SetPriority);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<OrientTowardsJumpInPositionTrack>("blendInTime", &OrientTowardsJumpInPositionTrack::SetBlendInTime);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<OrientTowardsJumpInPositionTrack>("blendOutTime", &OrientTowardsJumpInPositionTrack::SetBlendOutTime);
					properties[6] = property;
					property = new fight::PropertyBool<OrientTowardsJumpInPositionTrack>("useJumpDestination", &OrientTowardsJumpInPositionTrack::SetUseJumpDestination);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gOrientTowardsJumpInPositionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10145A40
			fight::TrackFactory* CreateOrientTowardsJumpInPositionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<OrientTowardsJumpInPositionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101465D0
			void RegisterOrientTowardsJumpInPositionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<OrientTowardsJumpInPositionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyBool<InsideJumpInBoundaryCondition>;
			template class fight::ConditionFactoryTemplate<InsideJumpInBoundaryCondition>;
			template class fight::ConditionFactoryCasterTemplate<InsideJumpInBoundaryCondition>;
			template class fight::PropertyEnumConstList<DistanceFromWaterSurfaceCondition>;
			template class fight::PropertyFloatConstRange<DistanceFromWaterSurfaceCondition>;
			template class fight::ConditionFactoryTemplate<DistanceFromWaterSurfaceCondition>;
			template class fight::ConditionFactoryCasterTemplate<DistanceFromWaterSurfaceCondition>;
			template class fight::PropertyEnumConstList<HeliBoundaryStatusCondition>;
			template class fight::ConditionFactoryTemplate<HeliBoundaryStatusCondition>;
			template class fight::ConditionFactoryCasterTemplate<HeliBoundaryStatusCondition>;
			template class fight::PropertyFloatConstRange<FromWaterSetJumpToTrack>;
			template class fight::TrackFactoryTemplate<FromWaterSetJumpToTrack>;
			template class fight::TrackFactoryCasterTemplate<FromWaterSetJumpToTrack>;
			template class fight::PropertyFloatConstRange<IgnoreWaterReactionTrack>;
			template class fight::TrackFactoryTemplate<IgnoreWaterReactionTrack>;
			template class fight::TrackFactoryCasterTemplate<IgnoreWaterReactionTrack>;
			template class fight::PropertyFloatConstRange<JumpFromWaterTrack>;
			template class fight::PropertyIntConstRange<JumpFromWaterTrack>;
			template class fight::TrackFactoryTemplate<JumpFromWaterTrack>;
			template class fight::TrackFactoryCasterTemplate<JumpFromWaterTrack>;
			template class fight::PropertyFloatConstRange<OrientTowardsJumpInPositionTrack>;
			template class fight::PropertyIntConstRange<OrientTowardsJumpInPositionTrack>;
			template class fight::PropertyBool<OrientTowardsJumpInPositionTrack>;
			template class fight::TrackFactoryTemplate<OrientTowardsJumpInPositionTrack>;
			template class fight::TrackFactoryCasterTemplate<OrientTowardsJumpInPositionTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10145100
// FUNCTION: ENGINE 0x10145130
// FUNCTION: ENGINE 0x10145160
// FUNCTION: ENGINE 0x10145190
// FUNCTION: ENGINE 0x101451C0
// FUNCTION: ENGINE 0x101451F0
// FUNCTION: ENGINE 0x10145220
// FUNCTION: ENGINE 0x10145250
// FUNCTION: ENGINE 0x10145260
// FUNCTION: ENGINE 0x10145290
// FUNCTION: ENGINE 0x101452A0
// FUNCTION: ENGINE 0x101452D0
// FUNCTION: ENGINE 0x101452E0
// FUNCTION: ENGINE 0x10145310
// FUNCTION: ENGINE 0x10145320
// FUNCTION: ENGINE 0x10145350
// FUNCTION: ENGINE 0x10145360
// FUNCTION: ENGINE 0x10145390
// FUNCTION: ENGINE 0x101453A0
// FUNCTION: ENGINE 0x101453D0
// FUNCTION: ENGINE 0x101453E0
// FUNCTION: ENGINE 0x10145410
// FUNCTION: ENGINE 0x10145440
// FUNCTION: ENGINE 0x10145460
// FUNCTION: ENGINE 0x10145470
// FUNCTION: ENGINE 0x101454B0
// FUNCTION: ENGINE 0x101454C0
// FUNCTION: ENGINE 0x101454F0
// FUNCTION: ENGINE 0x10145510
// FUNCTION: ENGINE 0x10145520
// FUNCTION: ENGINE 0x10145550
// FUNCTION: ENGINE 0x10145580
// FUNCTION: ENGINE 0x10145590
// FUNCTION: ENGINE 0x101455D0
// FUNCTION: ENGINE 0x101455E0
// FUNCTION: ENGINE 0x10145610
// FUNCTION: ENGINE 0x10145630
// FUNCTION: ENGINE 0x10145640
// FUNCTION: ENGINE 0x10145670
// FUNCTION: ENGINE 0x101456A0
// FUNCTION: ENGINE 0x101456B0
// FUNCTION: ENGINE 0x101456E0
// FUNCTION: ENGINE 0x10145710
// FUNCTION: ENGINE 0x10145720
// FUNCTION: ENGINE 0x10145750
// FUNCTION: ENGINE 0x10145780
// FUNCTION: ENGINE 0x10145790
// FUNCTION: ENGINE 0x101457C0
// FUNCTION: ENGINE 0x101457E0
// FUNCTION: ENGINE 0x101457F0
// FUNCTION: ENGINE 0x10145820
// FUNCTION: ENGINE 0x10145850
// FUNCTION: ENGINE 0x10145860
// FUNCTION: ENGINE 0x10145890
// FUNCTION: ENGINE 0x101458B0
// FUNCTION: ENGINE 0x101458C0
// FUNCTION: ENGINE 0x101458F0
// FUNCTION: ENGINE 0x10145910
// FUNCTION: ENGINE 0x10146600
// FUNCTION: ENGINE 0x10146630
// FUNCTION: ENGINE 0x10146650
// FUNCTION: ENGINE 0x10146680
// FUNCTION: ENGINE 0x101466A0
// FUNCTION: ENGINE 0x101466D0
// FUNCTION: ENGINE 0x101466F0
// FUNCTION: ENGINE 0x10146720
// FUNCTION: ENGINE 0x10146740
// FUNCTION: ENGINE 0x10146770
// FUNCTION: ENGINE 0x10146790
// FUNCTION: ENGINE 0x101467C0
// FUNCTION: ENGINE 0x101467E0
// FUNCTION: ENGINE 0x10146810
// FUNCTION: ENGINE 0x10146830
// FUNCTION: ENGINE 0x10146880
// FUNCTION: ENGINE 0x101468D0
// FUNCTION: ENGINE 0x10146920
// FUNCTION: ENGINE 0x10146970
// FUNCTION: ENGINE 0x101469C0
// FUNCTION: ENGINE 0x10146A10
