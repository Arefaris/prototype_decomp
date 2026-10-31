// Fight items of the motion group: MagneticBootsNextSurfaceNormalCondition, UsingHunterShortRangeCondition, OrientationNormalAngleCondition, MagneticBootsTestDetachTrack, MagneticBootsResetInfoTrack, MagneticBootsJumpTrack, MagneticBootsDetachTrack, MagneticBootsTestCornerTrack, MagneticBootsStickToWallTrack, MagneticBootsTurnCornerTrack, MagneticBootsTrack, MagneticBootsTestJumpStuckTrack, MagneticBootsTestWallTrack (unit 0x1018D500 - 0x10192C50; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_magneticboots.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gMagneticBootsNextSurfaceNormalConditionProperties;  // 0x112547D0

			// FUNCTION: ENGINE 0x1018D500
			bool MagneticBootsNextSurfaceNormalCondition::SetNormal(const math::Vector& newValue)
			{
				normal.x = newValue.x;
				normal.y = newValue.y;
				normal.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D520
			bool MagneticBootsNextSurfaceNormalCondition::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DEF0
			fight::Property* MagneticBootsNextSurfaceNormalCondition::GetProperty(int index)
			{
				return gMagneticBootsNextSurfaceNormalConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1018DF10
			void MagneticBootsNextSurfaceNormalCondition::ClearProperties()
			{
				fight::FreePropertyList(&gMagneticBootsNextSurfaceNormalConditionProperties);
			}

			// FUNCTION: ENGINE 0x1018DF20
			MagneticBootsNextSurfaceNormalCondition::MagneticBootsNextSurfaceNormalCondition() : fight::Condition(0), normal(0.0f, 0.0f, 0.0f), arc(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x1018DF60
			MagneticBootsNextSurfaceNormalCondition::~MagneticBootsNextSurfaceNormalCondition()
			{
			}

			// FUNCTION: ENGINE 0x10190450
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MagneticBootsNextSurfaceNormalCondition::RegisterProperties()
			{
				if (gMagneticBootsNextSurfaceNormalConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyVector<MagneticBootsNextSurfaceNormalCondition>("normal", &MagneticBootsNextSurfaceNormalCondition::SetNormal);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsNextSurfaceNormalCondition>("arc", &MagneticBootsNextSurfaceNormalCondition::SetArc);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gMagneticBootsNextSurfaceNormalConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101901E0
			fight::ConditionFactory* CreateMagneticBootsNextSurfaceNormalConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<MagneticBootsNextSurfaceNormalCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10191C80
			void RegisterMagneticBootsNextSurfaceNormalConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<MagneticBootsNextSurfaceNormalCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gUsingHunterShortRangeConditionProperties;  // 0x112547D4

			// FUNCTION: ENGINE 0x1018D540
			bool UsingHunterShortRangeCondition::SetUsing(bool newValue)
			{
				usingValue = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DF70
			fight::Property* UsingHunterShortRangeCondition::GetProperty(int index)
			{
				return gUsingHunterShortRangeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1018DF90
			void UsingHunterShortRangeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gUsingHunterShortRangeConditionProperties);
			}

			// FUNCTION: ENGINE 0x1018DFA0
			UsingHunterShortRangeCondition::UsingHunterShortRangeCondition() : fight::Condition(0), usingValue(true)
			{
			}

			// FUNCTION: ENGINE 0x1018DFC0
			UsingHunterShortRangeCondition::~UsingHunterShortRangeCondition()
			{
			}

			// FUNCTION: ENGINE 0x10190530
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void UsingHunterShortRangeCondition::RegisterProperties()
			{
				if (gUsingHunterShortRangeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<UsingHunterShortRangeCondition>("using", &UsingHunterShortRangeCondition::SetUsing);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gUsingHunterShortRangeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10190210
			fight::ConditionFactory* CreateUsingHunterShortRangeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<UsingHunterShortRangeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10191CB0
			void RegisterUsingHunterShortRangeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<UsingHunterShortRangeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gOrientationNormalAngleConditionProperties;  // 0x112547D8

			// FUNCTION: ENGINE 0x1018D550
			bool OrientationNormalAngleCondition::SetNormal(const math::Vector& newValue)
			{
				normal.x = newValue.x;
				normal.y = newValue.y;
				normal.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D570
			bool OrientationNormalAngleCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D580
			bool OrientationNormalAngleCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DFD0
			fight::Property* OrientationNormalAngleCondition::GetProperty(int index)
			{
				return gOrientationNormalAngleConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1018DFF0
			void OrientationNormalAngleCondition::ClearProperties()
			{
				fight::FreePropertyList(&gOrientationNormalAngleConditionProperties);
			}

			// FUNCTION: ENGINE 0x1018E000
			OrientationNormalAngleCondition::OrientationNormalAngleCondition() : fight::Condition(0), normal(0.0f, 1.0f, 0.0f), angle(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x1018E050
			OrientationNormalAngleCondition::~OrientationNormalAngleCondition()
			{
			}

			// FUNCTION: ENGINE 0x101905D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void OrientationNormalAngleCondition::RegisterProperties()
			{
				if (gOrientationNormalAngleConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyVector<OrientationNormalAngleCondition>("normal", &OrientationNormalAngleCondition::SetNormal);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<OrientationNormalAngleCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &OrientationNormalAngleCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<OrientationNormalAngleCondition>("angle", &OrientationNormalAngleCondition::SetAngle);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gOrientationNormalAngleConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10190240
			fight::ConditionFactory* CreateOrientationNormalAngleConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<OrientationNormalAngleCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10191CE0
			void RegisterOrientationNormalAngleConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<OrientationNormalAngleCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gMagneticBootsTestDetachTrackProperties;  // 0x112547DC

			// FUNCTION: ENGINE 0x1018D5A0
			bool MagneticBootsTestDetachTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D5C0
			bool MagneticBootsTestDetachTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D5E0
			bool MagneticBootsTestDetachTrack::SetThresoldAngle(float newValue)
			{
				thresoldAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D600
			bool MagneticBootsTestDetachTrack::SetDebugDraw(bool newValue)
			{
				debugDraw = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D610
			fight::BranchHolder* MagneticBootsTestDetachTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x1018D620
			bool MagneticBootsTestDetachTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D630
			fight::ConditionList* MagneticBootsTestDetachTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1018E060
			fight::Property* MagneticBootsTestDetachTrack::GetProperty(int index)
			{
				return gMagneticBootsTestDetachTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1018E080
			void MagneticBootsTestDetachTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMagneticBootsTestDetachTrackProperties);
			}

			// FUNCTION: ENGINE 0x1018E090
			MagneticBootsTestDetachTrack::MagneticBootsTestDetachTrack() : branch(0), thresoldAngle(0.08726647f), timeBegin(0.0f), timeEnd(-1.0f), priority(0), debugDraw(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1018E100
			float MagneticBootsTestDetachTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E110
			float MagneticBootsTestDetachTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E120
			MagneticBootsTestDetachTrack::~MagneticBootsTestDetachTrack()
			{
			}

			// FUNCTION: ENGINE 0x10190700
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MagneticBootsTestDetachTrack::RegisterProperties()
			{
				if (gMagneticBootsTestDetachTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MagneticBootsTestDetachTrack>("timeBegin", &MagneticBootsTestDetachTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTestDetachTrack>("timeEnd", &MagneticBootsTestDetachTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTestDetachTrack>("thresoldAngle", &MagneticBootsTestDetachTrack::SetThresoldAngle);
					properties[2] = property;
					property = new fight::PropertyBool<MagneticBootsTestDetachTrack>("debugDraw", &MagneticBootsTestDetachTrack::SetDebugDraw);
					properties[3] = property;
					property = new fight::PropertyBranch<MagneticBootsTestDetachTrack>("branch", &MagneticBootsTestDetachTrack::SetBranch);
					properties[4] = property;
					property = new fight::PropertyIntConstRange<MagneticBootsTestDetachTrack>("priority", &MagneticBootsTestDetachTrack::SetPriority);
					properties[5] = property;
					property = new fight::PropertyConditionGroup<MagneticBootsTestDetachTrack>("conditions", &MagneticBootsTestDetachTrack::SetConditions);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gMagneticBootsTestDetachTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10190270
			fight::TrackFactory* CreateMagneticBootsTestDetachTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsTestDetachTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10191D10
			void RegisterMagneticBootsTestDetachTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsTestDetachTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gMagneticBootsResetInfoTrackProperties;  // 0x112547E0

			// FUNCTION: ENGINE 0x1018D640
			bool MagneticBootsResetInfoTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D660
			bool MagneticBootsResetInfoTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018E150
			fight::Property* MagneticBootsResetInfoTrack::GetProperty(int index)
			{
				return gMagneticBootsResetInfoTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1018E170
			void MagneticBootsResetInfoTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMagneticBootsResetInfoTrackProperties);
			}

			// FUNCTION: ENGINE 0x1018E180
			MagneticBootsResetInfoTrack::MagneticBootsResetInfoTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1018E1C0
			float MagneticBootsResetInfoTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E1D0
			float MagneticBootsResetInfoTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E1E0
			MagneticBootsResetInfoTrack::~MagneticBootsResetInfoTrack()
			{
			}

			// FUNCTION: ENGINE 0x10190910
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MagneticBootsResetInfoTrack::RegisterProperties()
			{
				if (gMagneticBootsResetInfoTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MagneticBootsResetInfoTrack>("timeBegin", &MagneticBootsResetInfoTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsResetInfoTrack>("timeEnd", &MagneticBootsResetInfoTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gMagneticBootsResetInfoTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101902A0
			fight::TrackFactory* CreateMagneticBootsResetInfoTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsResetInfoTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10191D40
			void RegisterMagneticBootsResetInfoTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsResetInfoTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gMagneticBootsJumpTrackProperties;  // 0x112547E4

			// FUNCTION: ENGINE 0x1018D680
			bool MagneticBootsJumpTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D6A0
			bool MagneticBootsJumpTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D6C0
			bool MagneticBootsJumpTrack::SetFlightTime(float newValue)
			{
				flightTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D6E0
			bool MagneticBootsJumpTrack::SetUpDistance(float newValue)
			{
				upDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D700
			bool MagneticBootsJumpTrack::SetForwardDistance(float newValue)
			{
				forwardDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D720
			bool MagneticBootsJumpTrack::SetMaxFallSpeed(float newValue)
			{
				maxFallSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D740
			bool MagneticBootsJumpTrack::SetChoreoPriority(int newValue)
			{
				choreoPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D750
			bool MagneticBootsJumpTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D770
			bool MagneticBootsJumpTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018E1F0
			fight::Property* MagneticBootsJumpTrack::GetProperty(int index)
			{
				return gMagneticBootsJumpTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1018E210
			void MagneticBootsJumpTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMagneticBootsJumpTrackProperties);
			}

			// FUNCTION: ENGINE 0x1018E220
			MagneticBootsJumpTrack::MagneticBootsJumpTrack() : blendInTime(0.0f), blendOutTime(0.0f), flightTime(2.0f), forwardDistance(4.0f), maxFallSpeed(5e+01f), timeBegin(0.0f), timeEnd(-1.0f), upDistance(4.0f), choreoPriority(-5)
			{
			}

			// FUNCTION: ENGINE 0x1018E2A0
			float MagneticBootsJumpTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E2B0
			float MagneticBootsJumpTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E2C0
			MagneticBootsJumpTrack::~MagneticBootsJumpTrack()
			{
			}

			// FUNCTION: ENGINE 0x101909F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MagneticBootsJumpTrack::RegisterProperties()
			{
				if (gMagneticBootsJumpTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MagneticBootsJumpTrack>("timeBegin", &MagneticBootsJumpTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsJumpTrack>("timeEnd", &MagneticBootsJumpTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsJumpTrack>("flightTime", &MagneticBootsJumpTrack::SetFlightTime);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsJumpTrack>("upDistance", &MagneticBootsJumpTrack::SetUpDistance);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsJumpTrack>("forwardDistance", &MagneticBootsJumpTrack::SetForwardDistance);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsJumpTrack>("maxFallSpeed", &MagneticBootsJumpTrack::SetMaxFallSpeed);
					properties[5] = property;
					property = new fight::PropertyIntConstRange<MagneticBootsJumpTrack>("choreoPriority", &MagneticBootsJumpTrack::SetChoreoPriority);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsJumpTrack>("blendInTime", &MagneticBootsJumpTrack::SetBlendInTime);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsJumpTrack>("blendOutTime", &MagneticBootsJumpTrack::SetBlendOutTime);
					properties[8] = property;
					fight::RegisterPropertyList(properties, &gMagneticBootsJumpTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101902D0
			fight::TrackFactory* CreateMagneticBootsJumpTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsJumpTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10191D70
			void RegisterMagneticBootsJumpTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsJumpTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gMagneticBootsDetachTrackProperties;  // 0x112547E8

			// FUNCTION: ENGINE 0x1018D790
			bool MagneticBootsDetachTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D7B0
			bool MagneticBootsDetachTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D7D0
			bool MagneticBootsDetachTrack::SetTime(float newValue)
			{
				time = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D7F0
			bool MagneticBootsDetachTrack::SetSeparation(float newValue)
			{
				separation = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D810
			bool MagneticBootsDetachTrack::SetChoreoPriority(int newValue)
			{
				choreoPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D820
			bool MagneticBootsDetachTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D840
			bool MagneticBootsDetachTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D860
			bool MagneticBootsDetachTrack::SetDebugDraw(bool newValue)
			{
				debugDraw = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018E2D0
			fight::Property* MagneticBootsDetachTrack::GetProperty(int index)
			{
				return gMagneticBootsDetachTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1018E2F0
			void MagneticBootsDetachTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMagneticBootsDetachTrackProperties);
			}

			// FUNCTION: ENGINE 0x1018E300
			MagneticBootsDetachTrack::MagneticBootsDetachTrack() : blendInTime(0.0f), blendOutTime(0.0f), separation(2.0f), time(0.1f), timeBegin(0.0f), timeEnd(-1.0f), choreoPriority(-5), debugDraw(false)
			{
			}

			// FUNCTION: ENGINE 0x1018E370
			float MagneticBootsDetachTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E380
			float MagneticBootsDetachTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E390
			MagneticBootsDetachTrack::~MagneticBootsDetachTrack()
			{
			}

			// FUNCTION: ENGINE 0x10190C70
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MagneticBootsDetachTrack::RegisterProperties()
			{
				if (gMagneticBootsDetachTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MagneticBootsDetachTrack>("timeBegin", &MagneticBootsDetachTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsDetachTrack>("timeEnd", &MagneticBootsDetachTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsDetachTrack>("time", &MagneticBootsDetachTrack::SetTime);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsDetachTrack>("separation", &MagneticBootsDetachTrack::SetSeparation);
					properties[3] = property;
					property = new fight::PropertyIntConstRange<MagneticBootsDetachTrack>("choreoPriority", &MagneticBootsDetachTrack::SetChoreoPriority);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsDetachTrack>("blendInTime", &MagneticBootsDetachTrack::SetBlendInTime);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsDetachTrack>("blendOutTime", &MagneticBootsDetachTrack::SetBlendOutTime);
					properties[6] = property;
					property = new fight::PropertyBool<MagneticBootsDetachTrack>("debugDraw", &MagneticBootsDetachTrack::SetDebugDraw);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gMagneticBootsDetachTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10190300
			fight::TrackFactory* CreateMagneticBootsDetachTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsDetachTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10191DA0
			void RegisterMagneticBootsDetachTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsDetachTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gMagneticBootsTestCornerTrackProperties;  // 0x112547EC

			// FUNCTION: ENGINE 0x1018D870
			bool MagneticBootsTestCornerTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D890
			bool MagneticBootsTestCornerTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D8B0
			bool MagneticBootsTestCornerTrack::SetLookAhead(float newValue)
			{
				lookAhead = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D8D0
			bool MagneticBootsTestCornerTrack::SetCornerDepth(float newValue)
			{
				cornerDepth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D8F0
			bool MagneticBootsTestCornerTrack::SetCornerLookBack(float newValue)
			{
				cornerLookBack = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D910
			bool MagneticBootsTestCornerTrack::SetCollideWith(int newValue)
			{
				collideWith = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D920
			bool MagneticBootsTestCornerTrack::SetDebugDraw(bool newValue)
			{
				debugDraw = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D930
			fight::BranchHolder* MagneticBootsTestCornerTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x1018D940
			bool MagneticBootsTestCornerTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D950
			fight::ConditionList* MagneticBootsTestCornerTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1018E3A0
			fight::Property* MagneticBootsTestCornerTrack::GetProperty(int index)
			{
				return gMagneticBootsTestCornerTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1018E3C0
			void MagneticBootsTestCornerTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMagneticBootsTestCornerTrackProperties);
			}

			// FUNCTION: ENGINE 0x1018E3D0
			MagneticBootsTestCornerTrack::MagneticBootsTestCornerTrack() : branch(0), cornerDepth(2.0f), cornerLookBack(3.0f), lookAhead(2.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(0), collideWith(gMagneticBootsTestCornerTrackCollideWithDefault), debugDraw(false)
			{
			}

			// FUNCTION: ENGINE 0x1018E460
			float MagneticBootsTestCornerTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E470
			float MagneticBootsTestCornerTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E480
			MagneticBootsTestCornerTrack::~MagneticBootsTestCornerTrack()
			{
			}

			// FUNCTION: ENGINE 0x10190EC0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MagneticBootsTestCornerTrack::RegisterProperties()
			{
				if (gMagneticBootsTestCornerTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MagneticBootsTestCornerTrack>("timeBegin", &MagneticBootsTestCornerTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTestCornerTrack>("timeEnd", &MagneticBootsTestCornerTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTestCornerTrack>("lookAhead", &MagneticBootsTestCornerTrack::SetLookAhead);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTestCornerTrack>("cornerDepth", &MagneticBootsTestCornerTrack::SetCornerDepth);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTestCornerTrack>("cornerLookBack", &MagneticBootsTestCornerTrack::SetCornerLookBack);
					properties[4] = property;
					property = new fight::PropertyBitfieldConstList<MagneticBootsTestCornerTrack>("collideWith", gDetectObbCollisionConditionCollideWithTable, gDetectObbCollisionConditionCollideWithCount, &MagneticBootsTestCornerTrack::SetCollideWith);
					properties[5] = property;
					property = new fight::PropertyBool<MagneticBootsTestCornerTrack>("debugDraw", &MagneticBootsTestCornerTrack::SetDebugDraw);
					properties[6] = property;
					property = new fight::PropertyBranch<MagneticBootsTestCornerTrack>("branch", &MagneticBootsTestCornerTrack::SetBranch);
					properties[7] = property;
					property = new fight::PropertyIntConstRange<MagneticBootsTestCornerTrack>("priority", &MagneticBootsTestCornerTrack::SetPriority);
					properties[8] = property;
					property = new fight::PropertyConditionGroup<MagneticBootsTestCornerTrack>("conditions", &MagneticBootsTestCornerTrack::SetConditions);
					properties[9] = property;
					fight::RegisterPropertyList(properties, &gMagneticBootsTestCornerTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10190330
			fight::TrackFactory* CreateMagneticBootsTestCornerTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsTestCornerTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10191DD0
			void RegisterMagneticBootsTestCornerTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsTestCornerTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gMagneticBootsStickToWallTrackProperties;  // 0x112547F0

			// FUNCTION: ENGINE 0x1018D960
			bool MagneticBootsStickToWallTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D980
			bool MagneticBootsStickToWallTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D9A0
			bool MagneticBootsStickToWallTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D9C0
			bool MagneticBootsStickToWallTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018D9E0
			bool MagneticBootsStickToWallTrack::SetBeginTurn(float newValue)
			{
				beginTurn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DA00
			bool MagneticBootsStickToWallTrack::SetEndTurn(float newValue)
			{
				endTurn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DA20
			bool MagneticBootsStickToWallTrack::SetVerticalOffset(float newValue)
			{
				verticalOffset = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DA40
			bool MagneticBootsStickToWallTrack::SetChoreoPriority(int newValue)
			{
				choreoPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DA50
			bool MagneticBootsStickToWallTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DA70
			bool MagneticBootsStickToWallTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DA90
			bool MagneticBootsStickToWallTrack::SetDebugDraw(bool newValue)
			{
				debugDraw = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018E4B0
			fight::Property* MagneticBootsStickToWallTrack::GetProperty(int index)
			{
				return gMagneticBootsStickToWallTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1018E4D0
			void MagneticBootsStickToWallTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMagneticBootsStickToWallTrackProperties);
			}

			// FUNCTION: ENGINE 0x1018E4E0
			MagneticBootsStickToWallTrack::MagneticBootsStickToWallTrack() : acceleration(0.0f), beginTurn(0.0f), blendInTime(0.0f), blendOutTime(0.0f), endTurn(0.0f), speed(1e+01f), timeBegin(0.0f), timeEnd(-1.0f), verticalOffset(0.0f), choreoPriority(-5), debugDraw(false)
			{
			}

			// FUNCTION: ENGINE 0x1018E560
			float MagneticBootsStickToWallTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E570
			float MagneticBootsStickToWallTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E580
			MagneticBootsStickToWallTrack::~MagneticBootsStickToWallTrack()
			{
			}

			// FUNCTION: ENGINE 0x101911A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MagneticBootsStickToWallTrack::RegisterProperties()
			{
				if (gMagneticBootsStickToWallTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MagneticBootsStickToWallTrack>("timeBegin", &MagneticBootsStickToWallTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsStickToWallTrack>("timeEnd", &MagneticBootsStickToWallTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsStickToWallTrack>("speed", &MagneticBootsStickToWallTrack::SetSpeed);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsStickToWallTrack>("acceleration", &MagneticBootsStickToWallTrack::SetAcceleration);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsStickToWallTrack>("beginTurn", &MagneticBootsStickToWallTrack::SetBeginTurn);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsStickToWallTrack>("endTurn", &MagneticBootsStickToWallTrack::SetEndTurn);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsStickToWallTrack>("verticalOffset", &MagneticBootsStickToWallTrack::SetVerticalOffset);
					properties[6] = property;
					property = new fight::PropertyIntConstRange<MagneticBootsStickToWallTrack>("choreoPriority", &MagneticBootsStickToWallTrack::SetChoreoPriority);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsStickToWallTrack>("blendInTime", &MagneticBootsStickToWallTrack::SetBlendInTime);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsStickToWallTrack>("blendOutTime", &MagneticBootsStickToWallTrack::SetBlendOutTime);
					properties[9] = property;
					property = new fight::PropertyBool<MagneticBootsStickToWallTrack>("debugDraw", &MagneticBootsStickToWallTrack::SetDebugDraw);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gMagneticBootsStickToWallTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10190360
			fight::TrackFactory* CreateMagneticBootsStickToWallTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsStickToWallTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10191E00
			void RegisterMagneticBootsStickToWallTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsStickToWallTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gMagneticBootsTurnCornerTrackProperties;  // 0x112547F4

			// FUNCTION: ENGINE 0x1018DAA0
			bool MagneticBootsTurnCornerTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DAC0
			bool MagneticBootsTurnCornerTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DAE0
			bool MagneticBootsTurnCornerTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DB00
			bool MagneticBootsTurnCornerTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DB20
			bool MagneticBootsTurnCornerTrack::SetBeginTurn(float newValue)
			{
				beginTurn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DB40
			bool MagneticBootsTurnCornerTrack::SetEndTurn(float newValue)
			{
				endTurn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DB60
			bool MagneticBootsTurnCornerTrack::SetChoreoPriority(int newValue)
			{
				choreoPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DB70
			bool MagneticBootsTurnCornerTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DB90
			bool MagneticBootsTurnCornerTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DBB0
			bool MagneticBootsTurnCornerTrack::SetDebugDraw(bool newValue)
			{
				debugDraw = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018E590
			fight::Property* MagneticBootsTurnCornerTrack::GetProperty(int index)
			{
				return gMagneticBootsTurnCornerTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1018E5B0
			void MagneticBootsTurnCornerTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMagneticBootsTurnCornerTrackProperties);
			}

			// FUNCTION: ENGINE 0x1018E5C0
			MagneticBootsTurnCornerTrack::MagneticBootsTurnCornerTrack() : acceleration(0.0f), beginTurn(0.0f), blendInTime(0.0f), blendOutTime(0.0f), endTurn(0.0f), speed(1e+01f), timeBegin(0.0f), timeEnd(-1.0f), choreoPriority(-5), debugDraw(false)
			{
			}

			// FUNCTION: ENGINE 0x1018E630
			float MagneticBootsTurnCornerTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E640
			float MagneticBootsTurnCornerTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E650
			MagneticBootsTurnCornerTrack::~MagneticBootsTurnCornerTrack()
			{
			}

			// FUNCTION: ENGINE 0x101914A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MagneticBootsTurnCornerTrack::RegisterProperties()
			{
				if (gMagneticBootsTurnCornerTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MagneticBootsTurnCornerTrack>("timeBegin", &MagneticBootsTurnCornerTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTurnCornerTrack>("timeEnd", &MagneticBootsTurnCornerTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTurnCornerTrack>("speed", &MagneticBootsTurnCornerTrack::SetSpeed);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTurnCornerTrack>("acceleration", &MagneticBootsTurnCornerTrack::SetAcceleration);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTurnCornerTrack>("beginTurn", &MagneticBootsTurnCornerTrack::SetBeginTurn);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTurnCornerTrack>("endTurn", &MagneticBootsTurnCornerTrack::SetEndTurn);
					properties[5] = property;
					property = new fight::PropertyIntConstRange<MagneticBootsTurnCornerTrack>("choreoPriority", &MagneticBootsTurnCornerTrack::SetChoreoPriority);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTurnCornerTrack>("blendInTime", &MagneticBootsTurnCornerTrack::SetBlendInTime);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTurnCornerTrack>("blendOutTime", &MagneticBootsTurnCornerTrack::SetBlendOutTime);
					properties[8] = property;
					property = new fight::PropertyBool<MagneticBootsTurnCornerTrack>("debugDraw", &MagneticBootsTurnCornerTrack::SetDebugDraw);
					properties[9] = property;
					fight::RegisterPropertyList(properties, &gMagneticBootsTurnCornerTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10190390
			fight::TrackFactory* CreateMagneticBootsTurnCornerTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsTurnCornerTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10191E30
			void RegisterMagneticBootsTurnCornerTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsTurnCornerTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gMagneticBootsTrackProperties;  // 0x112547F8

			// FUNCTION: ENGINE 0x1018DBC0
			bool MagneticBootsTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DBE0
			bool MagneticBootsTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DC00
			bool MagneticBootsTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DC20
			bool MagneticBootsTrack::SetTurningVelocity(float newValue)
			{
				turningVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DC40
			bool MagneticBootsTrack::SetVelocityWalk(float newValue)
			{
				velocityWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DC60
			bool MagneticBootsTrack::SetVelocityRun(float newValue)
			{
				velocityRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DC80
			bool MagneticBootsTrack::SetPhase(float newValue)
			{
				phase = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018E890
			bool MagneticBootsTrack::SetLocomotion(const fight::Name& newValue)
			{
				locomotion = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018E8B0
			bool MagneticBootsTrack::SetAnimIdle(const fight::Name& newValue)
			{
				animIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018E8D0
			bool MagneticBootsTrack::SetAnimWalk(const fight::Name& newValue)
			{
				animWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018E8F0
			bool MagneticBootsTrack::SetAnimRun(const fight::Name& newValue)
			{
				animRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DCA0
			bool MagneticBootsTrack::SetSyncFrameIdle(float newValue)
			{
				syncFrameIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DCC0
			bool MagneticBootsTrack::SetSyncFrameWalk(float newValue)
			{
				syncFrameWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DCE0
			bool MagneticBootsTrack::SetSyncFrameRun(float newValue)
			{
				syncFrameRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018E910
			bool MagneticBootsTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DD00
			bool MagneticBootsTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DD10
			bool MagneticBootsTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DD30
			bool MagneticBootsTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DD50
			bool MagneticBootsTrack::SetDebugDraw(bool newValue)
			{
				debugDraw = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018E660
			fight::Property* MagneticBootsTrack::GetProperty(int index)
			{
				return gMagneticBootsTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1018E680
			void MagneticBootsTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMagneticBootsTrackProperties);
			}

			// FUNCTION: ENGINE 0x1018EB10
			MagneticBootsTrack::MagneticBootsTrack() : acceleration(5e+01f), blendInTime(0.0f), blendOutTime(0.0f), phase(-1.0f), syncFrameIdle(-1.0f), syncFrameRun(-1.0f), syncFrameWalk(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(6.2831855f), velocityRun(-1.0f), velocityWalk(-1.0f), priority(0), debugDraw(false)
			{
			}

			// FUNCTION: ENGINE 0x1018EBD0
			float MagneticBootsTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1018EBE0
			float MagneticBootsTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1018EBF0
			MagneticBootsTrack::~MagneticBootsTrack()
			{
			}

			// FUNCTION: ENGINE 0x10192300
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MagneticBootsTrack::RegisterProperties()
			{
				if (gMagneticBootsTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MagneticBootsTrack>("timeBegin", &MagneticBootsTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTrack>("timeEnd", &MagneticBootsTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTrack>("acceleration", &MagneticBootsTrack::SetAcceleration);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTrack>("turningVelocity", &MagneticBootsTrack::SetTurningVelocity);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTrack>("velocityWalk", &MagneticBootsTrack::SetVelocityWalk);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTrack>("velocityRun", &MagneticBootsTrack::SetVelocityRun);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTrack>("phase", &MagneticBootsTrack::SetPhase);
					properties[6] = property;
					property = new fight::PropertyName<MagneticBootsTrack>("locomotion", &MagneticBootsTrack::SetLocomotion);
					properties[7] = property;
					property = new fight::PropertyName<MagneticBootsTrack>("animIdle", &MagneticBootsTrack::SetAnimIdle);
					properties[8] = property;
					property = new fight::PropertyName<MagneticBootsTrack>("animWalk", &MagneticBootsTrack::SetAnimWalk);
					properties[9] = property;
					property = new fight::PropertyName<MagneticBootsTrack>("animRun", &MagneticBootsTrack::SetAnimRun);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTrack>("syncFrameIdle", &MagneticBootsTrack::SetSyncFrameIdle);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTrack>("syncFrameWalk", &MagneticBootsTrack::SetSyncFrameWalk);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTrack>("syncFrameRun", &MagneticBootsTrack::SetSyncFrameRun);
					properties[13] = property;
					property = new fight::PropertyName<MagneticBootsTrack>("partition", &MagneticBootsTrack::SetPartition);
					properties[14] = property;
					property = new fight::PropertyIntConstRange<MagneticBootsTrack>("priority", &MagneticBootsTrack::SetPriority);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTrack>("blendInTime", &MagneticBootsTrack::SetBlendInTime);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTrack>("blendOutTime", &MagneticBootsTrack::SetBlendOutTime);
					properties[17] = property;
					property = new fight::PropertyBool<MagneticBootsTrack>("debugDraw", &MagneticBootsTrack::SetDebugDraw);
					properties[18] = property;
					fight::RegisterPropertyList(properties, &gMagneticBootsTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101903C0
			fight::TrackFactory* CreateMagneticBootsTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10191E60
			void RegisterMagneticBootsTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gMagneticBootsTestJumpStuckTrackProperties;  // 0x112547FC

			// FUNCTION: ENGINE 0x1018DD60
			bool MagneticBootsTestJumpStuckTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DD80
			bool MagneticBootsTestJumpStuckTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DDA0
			bool MagneticBootsTestJumpStuckTrack::SetUseFacing(bool newValue)
			{
				useFacing = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DDB0
			fight::BranchHolder* MagneticBootsTestJumpStuckTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x1018DDC0
			bool MagneticBootsTestJumpStuckTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DDD0
			fight::ConditionList* MagneticBootsTestJumpStuckTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1018E690
			fight::Property* MagneticBootsTestJumpStuckTrack::GetProperty(int index)
			{
				return gMagneticBootsTestJumpStuckTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1018E6B0
			void MagneticBootsTestJumpStuckTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMagneticBootsTestJumpStuckTrackProperties);
			}

			// FUNCTION: ENGINE 0x1018E6C0
			MagneticBootsTestJumpStuckTrack::MagneticBootsTestJumpStuckTrack() : branch(0), timeBegin(0.0f), timeEnd(-1.0f), priority(0), useFacing(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1018E720
			float MagneticBootsTestJumpStuckTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E730
			float MagneticBootsTestJumpStuckTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E740
			MagneticBootsTestJumpStuckTrack::~MagneticBootsTestJumpStuckTrack()
			{
			}

			// FUNCTION: ENGINE 0x10191760
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MagneticBootsTestJumpStuckTrack::RegisterProperties()
			{
				if (gMagneticBootsTestJumpStuckTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MagneticBootsTestJumpStuckTrack>("timeBegin", &MagneticBootsTestJumpStuckTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTestJumpStuckTrack>("timeEnd", &MagneticBootsTestJumpStuckTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<MagneticBootsTestJumpStuckTrack>("useFacing", &MagneticBootsTestJumpStuckTrack::SetUseFacing);
					properties[2] = property;
					property = new fight::PropertyBranch<MagneticBootsTestJumpStuckTrack>("branch", &MagneticBootsTestJumpStuckTrack::SetBranch);
					properties[3] = property;
					property = new fight::PropertyIntConstRange<MagneticBootsTestJumpStuckTrack>("priority", &MagneticBootsTestJumpStuckTrack::SetPriority);
					properties[4] = property;
					property = new fight::PropertyConditionGroup<MagneticBootsTestJumpStuckTrack>("conditions", &MagneticBootsTestJumpStuckTrack::SetConditions);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gMagneticBootsTestJumpStuckTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101903F0
			fight::TrackFactory* CreateMagneticBootsTestJumpStuckTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsTestJumpStuckTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10191E90
			void RegisterMagneticBootsTestJumpStuckTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsTestJumpStuckTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gMagneticBootsTestWallTrackProperties;  // 0x11254800

			// FUNCTION: ENGINE 0x1018DDE0
			bool MagneticBootsTestWallTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DE00
			bool MagneticBootsTestWallTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DE20
			bool MagneticBootsTestWallTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DE40
			bool MagneticBootsTestWallTrack::SetYawOffset(float newValue)
			{
				yawOffset = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DE60
			bool MagneticBootsTestWallTrack::SetLength(float newValue)
			{
				length = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DE80
			bool MagneticBootsTestWallTrack::SetCollideWith(int newValue)
			{
				collideWith = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DE90
			bool MagneticBootsTestWallTrack::SetUseFacing(bool newValue)
			{
				useFacing = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DEA0
			bool MagneticBootsTestWallTrack::SetUseBackwardsFacing(bool newValue)
			{
				useBackwardsFacing = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DEB0
			bool MagneticBootsTestWallTrack::SetDebugDraw(bool newValue)
			{
				debugDraw = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DEC0
			fight::BranchHolder* MagneticBootsTestWallTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x1018DED0
			bool MagneticBootsTestWallTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018DEE0
			fight::ConditionList* MagneticBootsTestWallTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1018E770
			fight::Property* MagneticBootsTestWallTrack::GetProperty(int index)
			{
				return gMagneticBootsTestWallTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1018E790
			void MagneticBootsTestWallTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMagneticBootsTestWallTrackProperties);
			}

			// FUNCTION: ENGINE 0x1018E7A0
			MagneticBootsTestWallTrack::MagneticBootsTestWallTrack() : branch(0), offset(0.0f, 0.0f, 0.0f), length(2.0f), timeBegin(0.0f), timeEnd(-1.0f), yawOffset(0.0f), priority(0), collideWith(gMagneticBootsTestWallTrackCollideWithDefault), debugDraw(false), useBackwardsFacing(false), useFacing(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1018E840
			float MagneticBootsTestWallTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E850
			float MagneticBootsTestWallTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1018E860
			MagneticBootsTestWallTrack::~MagneticBootsTestWallTrack()
			{
			}

			// FUNCTION: ENGINE 0x10191930
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MagneticBootsTestWallTrack::RegisterProperties()
			{
				if (gMagneticBootsTestWallTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MagneticBootsTestWallTrack>("timeBegin", &MagneticBootsTestWallTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTestWallTrack>("timeEnd", &MagneticBootsTestWallTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyVector<MagneticBootsTestWallTrack>("offset", &MagneticBootsTestWallTrack::SetOffset);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTestWallTrack>("yawOffset", &MagneticBootsTestWallTrack::SetYawOffset);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<MagneticBootsTestWallTrack>("length", &MagneticBootsTestWallTrack::SetLength);
					properties[4] = property;
					property = new fight::PropertyBitfieldConstList<MagneticBootsTestWallTrack>("collideWith", gDetectObbCollisionConditionCollideWithTable, gDetectObbCollisionConditionCollideWithCount, &MagneticBootsTestWallTrack::SetCollideWith);
					properties[5] = property;
					property = new fight::PropertyBool<MagneticBootsTestWallTrack>("useFacing", &MagneticBootsTestWallTrack::SetUseFacing);
					properties[6] = property;
					property = new fight::PropertyBool<MagneticBootsTestWallTrack>("useBackwardsFacing", &MagneticBootsTestWallTrack::SetUseBackwardsFacing);
					properties[7] = property;
					property = new fight::PropertyBool<MagneticBootsTestWallTrack>("debugDraw", &MagneticBootsTestWallTrack::SetDebugDraw);
					properties[8] = property;
					property = new fight::PropertyBranch<MagneticBootsTestWallTrack>("branch", &MagneticBootsTestWallTrack::SetBranch);
					properties[9] = property;
					property = new fight::PropertyIntConstRange<MagneticBootsTestWallTrack>("priority", &MagneticBootsTestWallTrack::SetPriority);
					properties[10] = property;
					property = new fight::PropertyConditionGroup<MagneticBootsTestWallTrack>("conditions", &MagneticBootsTestWallTrack::SetConditions);
					properties[11] = property;
					fight::RegisterPropertyList(properties, &gMagneticBootsTestWallTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10190420
			fight::TrackFactory* CreateMagneticBootsTestWallTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsTestWallTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10191EC0
			void RegisterMagneticBootsTestWallTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MagneticBootsTestWallTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyVector<MagneticBootsNextSurfaceNormalCondition>;
			template class fight::PropertyFloatConstRange<MagneticBootsNextSurfaceNormalCondition>;
			template class fight::ConditionFactoryTemplate<MagneticBootsNextSurfaceNormalCondition>;
			template class fight::ConditionFactoryCasterTemplate<MagneticBootsNextSurfaceNormalCondition>;
			template class fight::PropertyBool<UsingHunterShortRangeCondition>;
			template class fight::ConditionFactoryTemplate<UsingHunterShortRangeCondition>;
			template class fight::ConditionFactoryCasterTemplate<UsingHunterShortRangeCondition>;
			template class fight::PropertyVector<OrientationNormalAngleCondition>;
			template class fight::PropertyEnumConstList<OrientationNormalAngleCondition>;
			template class fight::PropertyFloatConstRange<OrientationNormalAngleCondition>;
			template class fight::ConditionFactoryTemplate<OrientationNormalAngleCondition>;
			template class fight::ConditionFactoryCasterTemplate<OrientationNormalAngleCondition>;
			template class fight::PropertyFloatConstRange<MagneticBootsTestDetachTrack>;
			template class fight::PropertyBool<MagneticBootsTestDetachTrack>;
			template class fight::PropertyBranch<MagneticBootsTestDetachTrack>;
			template class fight::PropertyIntConstRange<MagneticBootsTestDetachTrack>;
			template class fight::PropertyConditionGroup<MagneticBootsTestDetachTrack>;
			template class fight::TrackFactoryTemplate<MagneticBootsTestDetachTrack>;
			template class fight::TrackFactoryCasterTemplate<MagneticBootsTestDetachTrack>;
			template class fight::PropertyFloatConstRange<MagneticBootsResetInfoTrack>;
			template class fight::TrackFactoryTemplate<MagneticBootsResetInfoTrack>;
			template class fight::TrackFactoryCasterTemplate<MagneticBootsResetInfoTrack>;
			template class fight::PropertyFloatConstRange<MagneticBootsJumpTrack>;
			template class fight::PropertyIntConstRange<MagneticBootsJumpTrack>;
			template class fight::TrackFactoryTemplate<MagneticBootsJumpTrack>;
			template class fight::TrackFactoryCasterTemplate<MagneticBootsJumpTrack>;
			template class fight::PropertyFloatConstRange<MagneticBootsDetachTrack>;
			template class fight::PropertyIntConstRange<MagneticBootsDetachTrack>;
			template class fight::PropertyBool<MagneticBootsDetachTrack>;
			template class fight::TrackFactoryTemplate<MagneticBootsDetachTrack>;
			template class fight::TrackFactoryCasterTemplate<MagneticBootsDetachTrack>;
			template class fight::PropertyFloatConstRange<MagneticBootsTestCornerTrack>;
			template class fight::PropertyBitfieldConstList<MagneticBootsTestCornerTrack>;
			template class fight::PropertyBool<MagneticBootsTestCornerTrack>;
			template class fight::PropertyBranch<MagneticBootsTestCornerTrack>;
			template class fight::PropertyIntConstRange<MagneticBootsTestCornerTrack>;
			template class fight::PropertyConditionGroup<MagneticBootsTestCornerTrack>;
			template class fight::TrackFactoryTemplate<MagneticBootsTestCornerTrack>;
			template class fight::TrackFactoryCasterTemplate<MagneticBootsTestCornerTrack>;
			template class fight::PropertyFloatConstRange<MagneticBootsStickToWallTrack>;
			template class fight::PropertyIntConstRange<MagneticBootsStickToWallTrack>;
			template class fight::PropertyBool<MagneticBootsStickToWallTrack>;
			template class fight::TrackFactoryTemplate<MagneticBootsStickToWallTrack>;
			template class fight::TrackFactoryCasterTemplate<MagneticBootsStickToWallTrack>;
			template class fight::PropertyFloatConstRange<MagneticBootsTurnCornerTrack>;
			template class fight::PropertyIntConstRange<MagneticBootsTurnCornerTrack>;
			template class fight::PropertyBool<MagneticBootsTurnCornerTrack>;
			template class fight::TrackFactoryTemplate<MagneticBootsTurnCornerTrack>;
			template class fight::TrackFactoryCasterTemplate<MagneticBootsTurnCornerTrack>;
			template class fight::PropertyFloatConstRange<MagneticBootsTrack>;
			template class fight::PropertyName<MagneticBootsTrack>;
			template class fight::PropertyIntConstRange<MagneticBootsTrack>;
			template class fight::PropertyBool<MagneticBootsTrack>;
			template class fight::TrackFactoryTemplate<MagneticBootsTrack>;
			template class fight::TrackFactoryCasterTemplate<MagneticBootsTrack>;
			template class fight::PropertyFloatConstRange<MagneticBootsTestJumpStuckTrack>;
			template class fight::PropertyBool<MagneticBootsTestJumpStuckTrack>;
			template class fight::PropertyBranch<MagneticBootsTestJumpStuckTrack>;
			template class fight::PropertyIntConstRange<MagneticBootsTestJumpStuckTrack>;
			template class fight::PropertyConditionGroup<MagneticBootsTestJumpStuckTrack>;
			template class fight::TrackFactoryTemplate<MagneticBootsTestJumpStuckTrack>;
			template class fight::TrackFactoryCasterTemplate<MagneticBootsTestJumpStuckTrack>;
			template class fight::PropertyFloatConstRange<MagneticBootsTestWallTrack>;
			template class fight::PropertyVector<MagneticBootsTestWallTrack>;
			template class fight::PropertyBitfieldConstList<MagneticBootsTestWallTrack>;
			template class fight::PropertyBool<MagneticBootsTestWallTrack>;
			template class fight::PropertyBranch<MagneticBootsTestWallTrack>;
			template class fight::PropertyIntConstRange<MagneticBootsTestWallTrack>;
			template class fight::PropertyConditionGroup<MagneticBootsTestWallTrack>;
			template class fight::TrackFactoryTemplate<MagneticBootsTestWallTrack>;
			template class fight::TrackFactoryCasterTemplate<MagneticBootsTestWallTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1018E930
// FUNCTION: ENGINE 0x1018E960
// FUNCTION: ENGINE 0x1018E990
// FUNCTION: ENGINE 0x1018E9C0
// FUNCTION: ENGINE 0x1018E9F0
// FUNCTION: ENGINE 0x1018EA20
// FUNCTION: ENGINE 0x1018EA50
// FUNCTION: ENGINE 0x1018EA80
// FUNCTION: ENGINE 0x1018EAB0
// FUNCTION: ENGINE 0x1018EAE0
// FUNCTION: ENGINE 0x1018EC00
// FUNCTION: ENGINE 0x1018EC30
// FUNCTION: ENGINE 0x1018EC60
// FUNCTION: ENGINE 0x1018EC70
// FUNCTION: ENGINE 0x1018ECA0
// FUNCTION: ENGINE 0x1018ECB0
// FUNCTION: ENGINE 0x1018ECE0
// FUNCTION: ENGINE 0x1018ECF0
// FUNCTION: ENGINE 0x1018ED20
// FUNCTION: ENGINE 0x1018ED30
// FUNCTION: ENGINE 0x1018ED60
// FUNCTION: ENGINE 0x1018ED70
// FUNCTION: ENGINE 0x1018EDA0
// FUNCTION: ENGINE 0x1018EDB0
// FUNCTION: ENGINE 0x1018EDE0
// FUNCTION: ENGINE 0x1018EDF0
// FUNCTION: ENGINE 0x1018EE20
// FUNCTION: ENGINE 0x1018EE30
// FUNCTION: ENGINE 0x1018EE60
// FUNCTION: ENGINE 0x1018EE70
// FUNCTION: ENGINE 0x1018EEA0
// FUNCTION: ENGINE 0x1018EEB0
// FUNCTION: ENGINE 0x1018EEE0
// FUNCTION: ENGINE 0x1018EEF0
// FUNCTION: ENGINE 0x1018EF20
// FUNCTION: ENGINE 0x1018EF30
// FUNCTION: ENGINE 0x1018EF60
// FUNCTION: ENGINE 0x1018EF70
// FUNCTION: ENGINE 0x1018EFA0
// FUNCTION: ENGINE 0x1018EFD0
// FUNCTION: ENGINE 0x1018F000
// FUNCTION: ENGINE 0x1018F020
// FUNCTION: ENGINE 0x1018F030
// FUNCTION: ENGINE 0x1018F060
// FUNCTION: ENGINE 0x1018F090
// FUNCTION: ENGINE 0x1018F0A0
// FUNCTION: ENGINE 0x1018F0D0
// FUNCTION: ENGINE 0x1018F0F0
// FUNCTION: ENGINE 0x1018F100
// FUNCTION: ENGINE 0x1018F130
// FUNCTION: ENGINE 0x1018F150
// FUNCTION: ENGINE 0x1018F160
// FUNCTION: ENGINE 0x1018F1A0
// FUNCTION: ENGINE 0x1018F1B0
// FUNCTION: ENGINE 0x1018F1E0
// FUNCTION: ENGINE 0x1018F200
// FUNCTION: ENGINE 0x1018F210
// FUNCTION: ENGINE 0x1018F240
// FUNCTION: ENGINE 0x1018F270
// FUNCTION: ENGINE 0x1018F280
// FUNCTION: ENGINE 0x1018F2B0
// FUNCTION: ENGINE 0x1018F2E0
// FUNCTION: ENGINE 0x1018F2F0
// FUNCTION: ENGINE 0x1018F320
// FUNCTION: ENGINE 0x1018F340
// FUNCTION: ENGINE 0x1018F350
// FUNCTION: ENGINE 0x1018F380
// FUNCTION: ENGINE 0x1018F3A0
// FUNCTION: ENGINE 0x1018F3D0
// FUNCTION: ENGINE 0x1018F3F0
// FUNCTION: ENGINE 0x1018F400
// FUNCTION: ENGINE 0x1018F430
// FUNCTION: ENGINE 0x1018F450
// FUNCTION: ENGINE 0x1018F480
// FUNCTION: ENGINE 0x1018F4B0
// FUNCTION: ENGINE 0x1018F4C0
// FUNCTION: ENGINE 0x1018F4F0
// FUNCTION: ENGINE 0x1018F520
// FUNCTION: ENGINE 0x1018F530
// FUNCTION: ENGINE 0x1018F560
// FUNCTION: ENGINE 0x1018F580
// FUNCTION: ENGINE 0x1018F590
// FUNCTION: ENGINE 0x1018F5C0
// FUNCTION: ENGINE 0x1018F5F0
// FUNCTION: ENGINE 0x1018F600
// FUNCTION: ENGINE 0x1018F630
// FUNCTION: ENGINE 0x1018F650
// FUNCTION: ENGINE 0x1018F660
// FUNCTION: ENGINE 0x1018F690
// FUNCTION: ENGINE 0x1018F6B0
// FUNCTION: ENGINE 0x1018F6C0
// FUNCTION: ENGINE 0x1018F6F0
// FUNCTION: ENGINE 0x1018F720
// FUNCTION: ENGINE 0x1018F730
// FUNCTION: ENGINE 0x1018F770
// FUNCTION: ENGINE 0x1018F780
// FUNCTION: ENGINE 0x1018F7A0
// FUNCTION: ENGINE 0x1018F7B0
// FUNCTION: ENGINE 0x1018F810
// FUNCTION: ENGINE 0x1018F840
// FUNCTION: ENGINE 0x1018F860
// FUNCTION: ENGINE 0x1018F870
// FUNCTION: ENGINE 0x1018F8A0
// FUNCTION: ENGINE 0x1018F8C0
// FUNCTION: ENGINE 0x1018F8F0
// FUNCTION: ENGINE 0x1018F910
// FUNCTION: ENGINE 0x1018F920
// FUNCTION: ENGINE 0x1018F950
// FUNCTION: ENGINE 0x1018F970
// FUNCTION: ENGINE 0x1018F9A0
// FUNCTION: ENGINE 0x1018F9D0
// FUNCTION: ENGINE 0x1018F9E0
// FUNCTION: ENGINE 0x1018FA10
// FUNCTION: ENGINE 0x1018FA30
// FUNCTION: ENGINE 0x1018FA40
// FUNCTION: ENGINE 0x1018FA70
// FUNCTION: ENGINE 0x1018FA90
// FUNCTION: ENGINE 0x1018FAA0
// FUNCTION: ENGINE 0x1018FAD0
// FUNCTION: ENGINE 0x1018FB00
// FUNCTION: ENGINE 0x1018FB10
// FUNCTION: ENGINE 0x1018FB40
// FUNCTION: ENGINE 0x1018FB60
// FUNCTION: ENGINE 0x1018FB70
// FUNCTION: ENGINE 0x1018FBA0
// FUNCTION: ENGINE 0x1018FBC0
// FUNCTION: ENGINE 0x1018FBD0
// FUNCTION: ENGINE 0x1018FC00
// FUNCTION: ENGINE 0x1018FC30
// FUNCTION: ENGINE 0x1018FC40
// FUNCTION: ENGINE 0x1018FC70
// FUNCTION: ENGINE 0x1018FC90
// FUNCTION: ENGINE 0x1018FCA0
// FUNCTION: ENGINE 0x1018FCD0
// FUNCTION: ENGINE 0x1018FCF0
// FUNCTION: ENGINE 0x1018FD00
// FUNCTION: ENGINE 0x1018FD30
// FUNCTION: ENGINE 0x1018FD60
// FUNCTION: ENGINE 0x1018FD70
// FUNCTION: ENGINE 0x1018FDA0
// FUNCTION: ENGINE 0x1018FDC0
// FUNCTION: ENGINE 0x1018FDD0
// FUNCTION: ENGINE 0x1018FE00
// FUNCTION: ENGINE 0x1018FE20
// FUNCTION: ENGINE 0x1018FE50
// FUNCTION: ENGINE 0x1018FE70
// FUNCTION: ENGINE 0x1018FE80
// FUNCTION: ENGINE 0x1018FEB0
// FUNCTION: ENGINE 0x1018FED0
// FUNCTION: ENGINE 0x1018FF00
// FUNCTION: ENGINE 0x1018FF30
// FUNCTION: ENGINE 0x1018FF40
// FUNCTION: ENGINE 0x1018FF70
// FUNCTION: ENGINE 0x1018FF90
// FUNCTION: ENGINE 0x1018FFA0
// FUNCTION: ENGINE 0x1018FFE0
// FUNCTION: ENGINE 0x1018FFF0
// FUNCTION: ENGINE 0x10190010
// FUNCTION: ENGINE 0x10190020
// FUNCTION: ENGINE 0x10190080
// FUNCTION: ENGINE 0x101900B0
// FUNCTION: ENGINE 0x101900D0
// FUNCTION: ENGINE 0x101900E0
// FUNCTION: ENGINE 0x10190110
// FUNCTION: ENGINE 0x10190130
// FUNCTION: ENGINE 0x10190160
// FUNCTION: ENGINE 0x10190180
// FUNCTION: ENGINE 0x10190190
// FUNCTION: ENGINE 0x101901C0
// FUNCTION: ENGINE 0x10191EF0
// FUNCTION: ENGINE 0x10191F20
// FUNCTION: ENGINE 0x10191F40
// FUNCTION: ENGINE 0x10191F70
// FUNCTION: ENGINE 0x10191F90
// FUNCTION: ENGINE 0x10191FC0
// FUNCTION: ENGINE 0x10191FE0
// FUNCTION: ENGINE 0x10192010
// FUNCTION: ENGINE 0x10192030
// FUNCTION: ENGINE 0x10192060
// FUNCTION: ENGINE 0x10192080
// FUNCTION: ENGINE 0x101920B0
// FUNCTION: ENGINE 0x101920D0
// FUNCTION: ENGINE 0x10192100
// FUNCTION: ENGINE 0x10192120
// FUNCTION: ENGINE 0x10192150
// FUNCTION: ENGINE 0x10192170
// FUNCTION: ENGINE 0x101921A0
// FUNCTION: ENGINE 0x101921C0
// FUNCTION: ENGINE 0x101921F0
// FUNCTION: ENGINE 0x10192210
// FUNCTION: ENGINE 0x10192240
// FUNCTION: ENGINE 0x10192260
// FUNCTION: ENGINE 0x10192290
// FUNCTION: ENGINE 0x101922B0
// FUNCTION: ENGINE 0x101922E0
// FUNCTION: ENGINE 0x101927F0
// FUNCTION: ENGINE 0x10192840
// FUNCTION: ENGINE 0x10192890
// FUNCTION: ENGINE 0x101928E0
// FUNCTION: ENGINE 0x10192930
// FUNCTION: ENGINE 0x10192980
// FUNCTION: ENGINE 0x101929D0
// FUNCTION: ENGINE 0x10192A20
// FUNCTION: ENGINE 0x10192A70
// FUNCTION: ENGINE 0x10192AC0
// FUNCTION: ENGINE 0x10192B10
// FUNCTION: ENGINE 0x10192B60
// FUNCTION: ENGINE 0x10192BB0
// FUNCTION: ENGINE 0x10192BE0
// FUNCTION: ENGINE 0x10192C00
