// Fight items of the ai group: CanStrafeRunCondition, StrafeRunTrack, SimpleOpenStrafeRunTrack, PrepareTightStrafeRunTrack, TryOpenStrafeRunTrack, TightStrafeRunTrack, PredefinedPatrolTrack, TryStrafeRunTrack (unit 0x1024A810 - 0x1024F860; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_strafe.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gCanStrafeRunConditionProperties;  // 0x11255BA4

			// FUNCTION: ENGINE 0x1024A810
			bool CanStrafeRunCondition::SetTimeTolerance(float newValue)
			{
				timeTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024A830
			bool CanStrafeRunCondition::SetDistanceTolerance(float newValue)
			{
				distanceTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024A850
			bool CanStrafeRunCondition::SetMinDelta(int newValue)
			{
				minDelta = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024A860
			bool CanStrafeRunCondition::SetMaxDelta(int newValue)
			{
				maxDelta = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024A870
			bool CanStrafeRunCondition::SetFarthestPossible(bool newValue)
			{
				farthestPossible = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B660
			fight::Property* CanStrafeRunCondition::GetProperty(int index)
			{
				return gCanStrafeRunConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1024B680
			void CanStrafeRunCondition::ClearProperties()
			{
				fight::FreePropertyList(&gCanStrafeRunConditionProperties);
			}

			// FUNCTION: ENGINE 0x1024B690
			CanStrafeRunCondition::CanStrafeRunCondition() : fight::Condition(0), distanceTolerance(2.0f), timeTolerance(0.5f), maxDelta(40), minDelta(5), farthestPossible(true)
			{
			}

			// FUNCTION: ENGINE 0x1024B6E0
			CanStrafeRunCondition::~CanStrafeRunCondition()
			{
			}

			// FUNCTION: ENGINE 0x1024D060
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CanStrafeRunCondition::RegisterProperties()
			{
				if (gCanStrafeRunConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CanStrafeRunCondition>("timeTolerance", &CanStrafeRunCondition::SetTimeTolerance);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<CanStrafeRunCondition>("distanceTolerance", &CanStrafeRunCondition::SetDistanceTolerance);
					properties[1] = property;
					property = new fight::PropertyIntConstRange<CanStrafeRunCondition>("minDelta", &CanStrafeRunCondition::SetMinDelta);
					properties[2] = property;
					property = new fight::PropertyIntConstRange<CanStrafeRunCondition>("maxDelta", &CanStrafeRunCondition::SetMaxDelta);
					properties[3] = property;
					property = new fight::PropertyBool<CanStrafeRunCondition>("farthestPossible", &CanStrafeRunCondition::SetFarthestPossible);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gCanStrafeRunConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1024CEE0
			fight::ConditionFactory* CreateCanStrafeRunConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CanStrafeRunCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1024F1C0
			void RegisterCanStrafeRunConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CanStrafeRunCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gStrafeRunTrackProperties;  // 0x11255BA8

			// FUNCTION: ENGINE 0x1024A880
			bool StrafeRunTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024A8A0
			bool StrafeRunTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024A8C0
			bool StrafeRunTrack::SetMinDistance(float newValue)
			{
				minDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024A8E0
			bool StrafeRunTrack::SetMaxDistance(float newValue)
			{
				maxDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024A900
			bool StrafeRunTrack::SetMinAngle(float newValue)
			{
				minAngle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024A920
			bool StrafeRunTrack::SetFreeRadiusEnd(float newValue)
			{
				freeRadiusEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024A940
			bool StrafeRunTrack::SetFreeRadiusTarget(float newValue)
			{
				freeRadiusTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024A960
			bool StrafeRunTrack::SetMinHeightAtTarget(float newValue)
			{
				minHeightAtTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024A980
			bool StrafeRunTrack::SetMaxHeightAtEnds(float newValue)
			{
				maxHeightAtEnds = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024A9A0
			bool StrafeRunTrack::SetMinHeightAtEnds(float newValue)
			{
				minHeightAtEnds = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024A9C0
			bool StrafeRunTrack::SetSafeHeightAtEnds(float newValue)
			{
				safeHeightAtEnds = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024A9E0
			bool StrafeRunTrack::SetMaxHeightDiffTargetAndEnds(float newValue)
			{
				maxHeightDiffTargetAndEnds = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AA00
			bool StrafeRunTrack::SetMaxPathHeightFromTarget(float newValue)
			{
				maxPathHeightFromTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AA20
			bool StrafeRunTrack::SetMaxPathYaw(float newValue)
			{
				maxPathYaw = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AA40
			bool StrafeRunTrack::SetMaxPathPitch(float newValue)
			{
				maxPathPitch = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AA60
			bool StrafeRunTrack::SetFreeRadiusPath(float newValue)
			{
				freeRadiusPath = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AA80
			bool StrafeRunTrack::SetTurningFactorA(int newValue)
			{
				turningFactorA = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AA90
			bool StrafeRunTrack::SetTurningFactorB(int newValue)
			{
				turningFactorB = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AAA0
			bool StrafeRunTrack::SetHeuristic(int newValue)
			{
				heuristic = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AAB0
			bool StrafeRunTrack::SetSameHeightPath(bool newValue)
			{
				sameHeightPath = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AAC0
			bool StrafeRunTrack::SetOrientAtEnd(bool newValue)
			{
				orientAtEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AAD0
			bool StrafeRunTrack::SetGoBack(bool newValue)
			{
				goBack = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AAE0
			bool StrafeRunTrack::SetBrake(bool newValue)
			{
				brake = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AAF0
			bool StrafeRunTrack::SetMinSpeed(float newValue)
			{
				minSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AB10
			bool StrafeRunTrack::SetMaxSpeed(float newValue)
			{
				maxSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AB30
			bool StrafeRunTrack::SetSpeedFactor(const math::Vector& newValue)
			{
				speedFactor.x = newValue.x;
				speedFactor.y = newValue.y;
				speedFactor.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AB50
			bool StrafeRunTrack::SetPassMidPointSpeedFactor(const math::Vector& newValue)
			{
				passMidPointSpeedFactor.x = newValue.x;
				passMidPointSpeedFactor.y = newValue.y;
				passMidPointSpeedFactor.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B6F0
			fight::Property* StrafeRunTrack::GetProperty(int index)
			{
				return gStrafeRunTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1024B710
			void StrafeRunTrack::ClearProperties()
			{
				fight::FreePropertyList(&gStrafeRunTrackProperties);
			}

			// FUNCTION: ENGINE 0x1024B720
			StrafeRunTrack::StrafeRunTrack() : passMidPointSpeedFactor(-1.0f, -1.0f, -1.0f), speedFactor(-1.0f, -1.0f, -1.0f), freeRadiusEnd(3e+01f), freeRadiusPath(2e+01f), freeRadiusTarget(18.0f), maxDistance(3e+01f), maxHeightAtEnds(2e+01f), maxHeightDiffTargetAndEnds(2e+01f), maxPathHeightFromTarget(2e+02f), maxPathPitch(6.2831855f), maxPathYaw(6.2831855f), maxSpeed(1.0f), minAngle(2.8f), minDistance(3e+01f), minHeightAtEnds(1e+01f), minHeightAtTarget(1e+01f), minSpeed(0.8f), safeHeightAtEnds(1e+01f), timeBegin(0.0f), timeEnd(-1.0f), heuristic(0), turningFactorA(2), turningFactorB(0), brake(true), goBack(true), orientAtEnd(true), sameHeightPath(false)
			{
			}

			// FUNCTION: ENGINE 0x1024B860
			float StrafeRunTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1024B870
			float StrafeRunTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1024B880
			StrafeRunTrack::~StrafeRunTrack()
			{
			}

			// FUNCTION: ENGINE 0x1024D1F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void StrafeRunTrack::RegisterProperties()
			{
				if (gStrafeRunTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("timeBegin", &StrafeRunTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("timeEnd", &StrafeRunTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("minDistance", &StrafeRunTrack::SetMinDistance);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("maxDistance", &StrafeRunTrack::SetMaxDistance);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("minAngle", &StrafeRunTrack::SetMinAngle);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("freeRadiusEnd", &StrafeRunTrack::SetFreeRadiusEnd);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("freeRadiusTarget", &StrafeRunTrack::SetFreeRadiusTarget);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("minHeightAtTarget", &StrafeRunTrack::SetMinHeightAtTarget);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("maxHeightAtEnds", &StrafeRunTrack::SetMaxHeightAtEnds);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("minHeightAtEnds", &StrafeRunTrack::SetMinHeightAtEnds);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("safeHeightAtEnds", &StrafeRunTrack::SetSafeHeightAtEnds);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("maxHeightDiffTargetAndEnds", &StrafeRunTrack::SetMaxHeightDiffTargetAndEnds);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("maxPathHeightFromTarget", &StrafeRunTrack::SetMaxPathHeightFromTarget);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("maxPathYaw", &StrafeRunTrack::SetMaxPathYaw);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("maxPathPitch", &StrafeRunTrack::SetMaxPathPitch);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("freeRadiusPath", &StrafeRunTrack::SetFreeRadiusPath);
					properties[15] = property;
					property = new fight::PropertyIntConstRange<StrafeRunTrack>("turningFactorA", &StrafeRunTrack::SetTurningFactorA);
					properties[16] = property;
					property = new fight::PropertyIntConstRange<StrafeRunTrack>("turningFactorB", &StrafeRunTrack::SetTurningFactorB);
					properties[17] = property;
					property = new fight::PropertyEnumConstList<StrafeRunTrack>("heuristic", gStrafeRunTrackHeuristicTable, gStrafeRunTrackHeuristicCount, &StrafeRunTrack::SetHeuristic);
					properties[18] = property;
					property = new fight::PropertyBool<StrafeRunTrack>("sameHeightPath", &StrafeRunTrack::SetSameHeightPath);
					properties[19] = property;
					property = new fight::PropertyBool<StrafeRunTrack>("orientAtEnd", &StrafeRunTrack::SetOrientAtEnd);
					properties[20] = property;
					property = new fight::PropertyBool<StrafeRunTrack>("goBack", &StrafeRunTrack::SetGoBack);
					properties[21] = property;
					property = new fight::PropertyBool<StrafeRunTrack>("brake", &StrafeRunTrack::SetBrake);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("minSpeed", &StrafeRunTrack::SetMinSpeed);
					properties[23] = property;
					property = new fight::PropertyFloatConstRange<StrafeRunTrack>("maxSpeed", &StrafeRunTrack::SetMaxSpeed);
					properties[24] = property;
					property = new fight::PropertyVector<StrafeRunTrack>("speedFactor", &StrafeRunTrack::SetSpeedFactor);
					properties[25] = property;
					property = new fight::PropertyVector<StrafeRunTrack>("passMidPointSpeedFactor", &StrafeRunTrack::SetPassMidPointSpeedFactor);
					properties[26] = property;
					fight::RegisterPropertyList(properties, &gStrafeRunTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1024CF10
			fight::TrackFactory* CreateStrafeRunTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<StrafeRunTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1024F1F0
			void RegisterStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<StrafeRunTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSimpleOpenStrafeRunTrackProperties;  // 0x11255BAC

			// FUNCTION: ENGINE 0x1024AB70
			bool SimpleOpenStrafeRunTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AB90
			bool SimpleOpenStrafeRunTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024ABB0
			bool SimpleOpenStrafeRunTrack::SetFreeRadiusPath(float newValue)
			{
				freeRadiusPath = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024ABD0
			bool SimpleOpenStrafeRunTrack::SetFreeRadiusPathToStart(float newValue)
			{
				freeRadiusPathToStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024ABF0
			bool SimpleOpenStrafeRunTrack::SetMinHeightStartFromTarget(float newValue)
			{
				minHeightStartFromTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AC10
			bool SimpleOpenStrafeRunTrack::SetMinHeightGoUpStart(float newValue)
			{
				minHeightGoUpStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AC30
			bool SimpleOpenStrafeRunTrack::SetReserveVolumeMargin(float newValue)
			{
				reserveVolumeMargin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AC50
			bool SimpleOpenStrafeRunTrack::SetReserveVolumeSideRadius(float newValue)
			{
				reserveVolumeSideRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AC70
			bool SimpleOpenStrafeRunTrack::SetToleranceToStart(float newValue)
			{
				toleranceToStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AC90
			bool SimpleOpenStrafeRunTrack::SetOrientAtEnd(bool newValue)
			{
				orientAtEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024ACA0
			bool SimpleOpenStrafeRunTrack::SetSpeedFactor(const math::Vector& newValue)
			{
				speedFactor.x = newValue.x;
				speedFactor.y = newValue.y;
				speedFactor.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B890
			fight::Property* SimpleOpenStrafeRunTrack::GetProperty(int index)
			{
				return gSimpleOpenStrafeRunTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1024B8B0
			void SimpleOpenStrafeRunTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSimpleOpenStrafeRunTrackProperties);
			}

			// FUNCTION: ENGINE 0x1024B8C0
			SimpleOpenStrafeRunTrack::SimpleOpenStrafeRunTrack() : speedFactor(-1.0f, -1.0f, -1.0f), freeRadiusPath(2e+01f), freeRadiusPathToStart(2e+01f), minHeightGoUpStart(2e+01f), minHeightStartFromTarget(2e+01f), reserveVolumeMargin(2e+01f), reserveVolumeSideRadius(2e+01f), timeBegin(0.0f), timeEnd(-1.0f), toleranceToStart(3.0f), orientAtEnd(true)
			{
			}

			// FUNCTION: ENGINE 0x1024B950
			float SimpleOpenStrafeRunTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1024B960
			float SimpleOpenStrafeRunTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1024B970
			SimpleOpenStrafeRunTrack::~SimpleOpenStrafeRunTrack()
			{
			}

			// FUNCTION: ENGINE 0x1024D8E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SimpleOpenStrafeRunTrack::RegisterProperties()
			{
				if (gSimpleOpenStrafeRunTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SimpleOpenStrafeRunTrack>("timeBegin", &SimpleOpenStrafeRunTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SimpleOpenStrafeRunTrack>("timeEnd", &SimpleOpenStrafeRunTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<SimpleOpenStrafeRunTrack>("freeRadiusPath", &SimpleOpenStrafeRunTrack::SetFreeRadiusPath);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<SimpleOpenStrafeRunTrack>("freeRadiusPathToStart", &SimpleOpenStrafeRunTrack::SetFreeRadiusPathToStart);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<SimpleOpenStrafeRunTrack>("minHeightStartFromTarget", &SimpleOpenStrafeRunTrack::SetMinHeightStartFromTarget);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<SimpleOpenStrafeRunTrack>("minHeightGoUpStart", &SimpleOpenStrafeRunTrack::SetMinHeightGoUpStart);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<SimpleOpenStrafeRunTrack>("reserveVolumeMargin", &SimpleOpenStrafeRunTrack::SetReserveVolumeMargin);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<SimpleOpenStrafeRunTrack>("reserveVolumeSideRadius", &SimpleOpenStrafeRunTrack::SetReserveVolumeSideRadius);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<SimpleOpenStrafeRunTrack>("toleranceToStart", &SimpleOpenStrafeRunTrack::SetToleranceToStart);
					properties[8] = property;
					property = new fight::PropertyBool<SimpleOpenStrafeRunTrack>("orientAtEnd", &SimpleOpenStrafeRunTrack::SetOrientAtEnd);
					properties[9] = property;
					property = new fight::PropertyVector<SimpleOpenStrafeRunTrack>("speedFactor", &SimpleOpenStrafeRunTrack::SetSpeedFactor);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gSimpleOpenStrafeRunTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1024CF40
			fight::TrackFactory* CreateSimpleOpenStrafeRunTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SimpleOpenStrafeRunTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1024F220
			void RegisterSimpleOpenStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SimpleOpenStrafeRunTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gPrepareTightStrafeRunTrackProperties;  // 0x11255BB0

			// FUNCTION: ENGINE 0x1024ACC0
			bool PrepareTightStrafeRunTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024ACE0
			bool PrepareTightStrafeRunTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AD00
			bool PrepareTightStrafeRunTrack::SetMinSpeed(float newValue)
			{
				minSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AD20
			bool PrepareTightStrafeRunTrack::SetMaxSpeed(float newValue)
			{
				maxSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AD40
			bool PrepareTightStrafeRunTrack::SetDistanceTolerance(float newValue)
			{
				distanceTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AD60
			bool PrepareTightStrafeRunTrack::SetHeightTolerance(float newValue)
			{
				heightTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AD80
			bool PrepareTightStrafeRunTrack::SetExtraHeightStart(float newValue)
			{
				extraHeightStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024ADA0
			bool PrepareTightStrafeRunTrack::SetLengthPostStart(float newValue)
			{
				lengthPostStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024ADC0
			bool PrepareTightStrafeRunTrack::SetWaitTimeAtStart(float newValue)
			{
				waitTimeAtStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024ADE0
			bool PrepareTightStrafeRunTrack::SetHeightAtTarget(float newValue)
			{
				heightAtTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AE00
			bool PrepareTightStrafeRunTrack::SetSpeedFactor(const math::Vector& newValue)
			{
				speedFactor.x = newValue.x;
				speedFactor.y = newValue.y;
				speedFactor.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B980
			fight::Property* PrepareTightStrafeRunTrack::GetProperty(int index)
			{
				return gPrepareTightStrafeRunTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1024B9A0
			void PrepareTightStrafeRunTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPrepareTightStrafeRunTrackProperties);
			}

			// FUNCTION: ENGINE 0x1024B9B0
			PrepareTightStrafeRunTrack::PrepareTightStrafeRunTrack() : speedFactor(-1.0f, -1.0f, -1.0f), distanceTolerance(2.0f), extraHeightStart(2.0f), heightAtTarget(1e+01f), heightTolerance(2.0f), lengthPostStart(2.0f), maxSpeed(1.0f), minSpeed(0.8f), timeBegin(0.0f), timeEnd(-1.0f), waitTimeAtStart(0.5f)
			{
			}

			// FUNCTION: ENGINE 0x1024BA60
			float PrepareTightStrafeRunTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1024BA70
			float PrepareTightStrafeRunTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1024BA80
			PrepareTightStrafeRunTrack::~PrepareTightStrafeRunTrack()
			{
			}

			// FUNCTION: ENGINE 0x1024DBE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PrepareTightStrafeRunTrack::RegisterProperties()
			{
				if (gPrepareTightStrafeRunTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PrepareTightStrafeRunTrack>("timeBegin", &PrepareTightStrafeRunTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PrepareTightStrafeRunTrack>("timeEnd", &PrepareTightStrafeRunTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<PrepareTightStrafeRunTrack>("minSpeed", &PrepareTightStrafeRunTrack::SetMinSpeed);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<PrepareTightStrafeRunTrack>("maxSpeed", &PrepareTightStrafeRunTrack::SetMaxSpeed);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<PrepareTightStrafeRunTrack>("distanceTolerance", &PrepareTightStrafeRunTrack::SetDistanceTolerance);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<PrepareTightStrafeRunTrack>("heightTolerance", &PrepareTightStrafeRunTrack::SetHeightTolerance);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<PrepareTightStrafeRunTrack>("extraHeightStart", &PrepareTightStrafeRunTrack::SetExtraHeightStart);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<PrepareTightStrafeRunTrack>("lengthPostStart", &PrepareTightStrafeRunTrack::SetLengthPostStart);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<PrepareTightStrafeRunTrack>("waitTimeAtStart", &PrepareTightStrafeRunTrack::SetWaitTimeAtStart);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<PrepareTightStrafeRunTrack>("heightAtTarget", &PrepareTightStrafeRunTrack::SetHeightAtTarget);
					properties[9] = property;
					property = new fight::PropertyVector<PrepareTightStrafeRunTrack>("speedFactor", &PrepareTightStrafeRunTrack::SetSpeedFactor);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gPrepareTightStrafeRunTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1024CF70
			fight::TrackFactory* CreatePrepareTightStrafeRunTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PrepareTightStrafeRunTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1024F250
			void RegisterPrepareTightStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PrepareTightStrafeRunTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTryOpenStrafeRunTrackProperties;  // 0x11255BB4

			// FUNCTION: ENGINE 0x1024AE20
			bool TryOpenStrafeRunTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AE40
			bool TryOpenStrafeRunTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AE60
			bool TryOpenStrafeRunTrack::SetMaxHeightPath(float newValue)
			{
				maxHeightPath = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AE80
			bool TryOpenStrafeRunTrack::SetMaxHeightEnd(float newValue)
			{
				maxHeightEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AEA0
			bool TryOpenStrafeRunTrack::SetMinHeightWithTarget(float newValue)
			{
				minHeightWithTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AEC0
			bool TryOpenStrafeRunTrack::SetEndHigherThanTarget(float newValue)
			{
				endHigherThanTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AEE0
			bool TryOpenStrafeRunTrack::SetMaxHeightStartWithTarget(float newValue)
			{
				maxHeightStartWithTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AF00
			bool TryOpenStrafeRunTrack::SetMinHeightStartWithTarget(float newValue)
			{
				minHeightStartWithTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AF20
			bool TryOpenStrafeRunTrack::SetMaxLength(int newValue)
			{
				maxLength = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AF30
			bool TryOpenStrafeRunTrack::SetMinLength(int newValue)
			{
				minLength = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AF40
			bool TryOpenStrafeRunTrack::SetMinLengthAfterTarget(int newValue)
			{
				minLengthAfterTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AF50
			bool TryOpenStrafeRunTrack::SetMinLengthBeforeTarget(float newValue)
			{
				minLengthBeforeTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AF70
			bool TryOpenStrafeRunTrack::SetMaxHeightToIgnoreStartLength(float newValue)
			{
				maxHeightToIgnoreStartLength = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AF90
			bool TryOpenStrafeRunTrack::SetFreeRadiusStart(float newValue)
			{
				freeRadiusStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AFB0
			bool TryOpenStrafeRunTrack::SetFreeRadiusPath(float newValue)
			{
				freeRadiusPath = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AFD0
			bool TryOpenStrafeRunTrack::SetFreeRadiusEnd(float newValue)
			{
				freeRadiusEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024AFF0
			fight::BranchHolder* TryOpenStrafeRunTrack::SetIfFound()
			{
				return &ifFound;
			}

			// FUNCTION: ENGINE 0x1024B000
			bool TryOpenStrafeRunTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B010
			fight::ConditionList* TryOpenStrafeRunTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1024BA90
			fight::Property* TryOpenStrafeRunTrack::GetProperty(int index)
			{
				return gTryOpenStrafeRunTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1024BAB0
			void TryOpenStrafeRunTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTryOpenStrafeRunTrackProperties);
			}

			// FUNCTION: ENGINE 0x1024BAC0
			TryOpenStrafeRunTrack::TryOpenStrafeRunTrack() : ifFound(0), endHigherThanTarget(3e+01f), freeRadiusEnd(2e+01f), freeRadiusPath(2e+01f), freeRadiusStart(2e+01f), maxHeightEnd(3e+01f), maxHeightPath(3e+01f), maxHeightStartWithTarget(3e+01f), maxHeightToIgnoreStartLength(2.0f), minHeightStartWithTarget(5.0f), minHeightWithTarget(3e+01f), minLengthBeforeTarget(2.0f), timeBegin(0.0f), timeEnd(-1.0f), maxLength(2), minLength(2), minLengthAfterTarget(2), priority(0)
			{
			}

			// FUNCTION: ENGINE 0x1024BB90
			float TryOpenStrafeRunTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1024BBA0
			float TryOpenStrafeRunTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1024BBB0
			TryOpenStrafeRunTrack::~TryOpenStrafeRunTrack()
			{
			}

			// FUNCTION: ENGINE 0x1024DEE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TryOpenStrafeRunTrack::RegisterProperties()
			{
				if (gTryOpenStrafeRunTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TryOpenStrafeRunTrack>("timeBegin", &TryOpenStrafeRunTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TryOpenStrafeRunTrack>("timeEnd", &TryOpenStrafeRunTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TryOpenStrafeRunTrack>("maxHeightPath", &TryOpenStrafeRunTrack::SetMaxHeightPath);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<TryOpenStrafeRunTrack>("maxHeightEnd", &TryOpenStrafeRunTrack::SetMaxHeightEnd);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<TryOpenStrafeRunTrack>("minHeightWithTarget", &TryOpenStrafeRunTrack::SetMinHeightWithTarget);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<TryOpenStrafeRunTrack>("endHigherThanTarget", &TryOpenStrafeRunTrack::SetEndHigherThanTarget);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<TryOpenStrafeRunTrack>("maxHeightStartWithTarget", &TryOpenStrafeRunTrack::SetMaxHeightStartWithTarget);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<TryOpenStrafeRunTrack>("minHeightStartWithTarget", &TryOpenStrafeRunTrack::SetMinHeightStartWithTarget);
					properties[7] = property;
					property = new fight::PropertyIntConstRange<TryOpenStrafeRunTrack>("maxLength", &TryOpenStrafeRunTrack::SetMaxLength);
					properties[8] = property;
					property = new fight::PropertyIntConstRange<TryOpenStrafeRunTrack>("minLength", &TryOpenStrafeRunTrack::SetMinLength);
					properties[9] = property;
					property = new fight::PropertyIntConstRange<TryOpenStrafeRunTrack>("minLengthAfterTarget", &TryOpenStrafeRunTrack::SetMinLengthAfterTarget);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<TryOpenStrafeRunTrack>("minLengthBeforeTarget", &TryOpenStrafeRunTrack::SetMinLengthBeforeTarget);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<TryOpenStrafeRunTrack>("maxHeightToIgnoreStartLength", &TryOpenStrafeRunTrack::SetMaxHeightToIgnoreStartLength);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<TryOpenStrafeRunTrack>("freeRadiusStart", &TryOpenStrafeRunTrack::SetFreeRadiusStart);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<TryOpenStrafeRunTrack>("freeRadiusPath", &TryOpenStrafeRunTrack::SetFreeRadiusPath);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<TryOpenStrafeRunTrack>("freeRadiusEnd", &TryOpenStrafeRunTrack::SetFreeRadiusEnd);
					properties[15] = property;
					property = new fight::PropertyBranch<TryOpenStrafeRunTrack>("ifFound", &TryOpenStrafeRunTrack::SetIfFound);
					properties[16] = property;
					property = new fight::PropertyIntConstRange<TryOpenStrafeRunTrack>("priority", &TryOpenStrafeRunTrack::SetPriority);
					properties[17] = property;
					property = new fight::PropertyConditionGroup<TryOpenStrafeRunTrack>("conditions", &TryOpenStrafeRunTrack::SetConditions);
					properties[18] = property;
					fight::RegisterPropertyList(properties, &gTryOpenStrafeRunTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1024CFA0
			fight::TrackFactory* CreateTryOpenStrafeRunTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TryOpenStrafeRunTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1024F280
			void RegisterTryOpenStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TryOpenStrafeRunTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTightStrafeRunTrackProperties;  // 0x11255BB8

			// FUNCTION: ENGINE 0x1024B020
			bool TightStrafeRunTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B040
			bool TightStrafeRunTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B060
			bool TightStrafeRunTrack::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B080
			bool TightStrafeRunTrack::SetTurnRate(float newValue)
			{
				turnRate = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B0A0
			bool TightStrafeRunTrack::SetMinSpeed(float newValue)
			{
				minSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B0C0
			bool TightStrafeRunTrack::SetMaxSpeed(float newValue)
			{
				maxSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B0E0
			bool TightStrafeRunTrack::SetDistanceTolerance(float newValue)
			{
				distanceTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B100
			bool TightStrafeRunTrack::SetHeightTolerance(float newValue)
			{
				heightTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B120
			bool TightStrafeRunTrack::SetExtraHeightStart(float newValue)
			{
				extraHeightStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B140
			bool TightStrafeRunTrack::SetLengthPostStart(float newValue)
			{
				lengthPostStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B160
			bool TightStrafeRunTrack::SetFreeRadiusEnd(float newValue)
			{
				freeRadiusEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B180
			bool TightStrafeRunTrack::SetGoBack(bool newValue)
			{
				goBack = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B190
			bool TightStrafeRunTrack::SetUseTargetIntermediate(bool newValue)
			{
				useTargetIntermediate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B1A0
			bool TightStrafeRunTrack::SetGoUpSoon(bool newValue)
			{
				goUpSoon = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B1B0
			bool TightStrafeRunTrack::SetHeightAtTarget(float newValue)
			{
				heightAtTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B1D0
			bool TightStrafeRunTrack::SetTemporaryTarget(int newValue)
			{
				temporaryTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B1E0
			bool TightStrafeRunTrack::SetSpeedFactor(const math::Vector& newValue)
			{
				speedFactor.x = newValue.x;
				speedFactor.y = newValue.y;
				speedFactor.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1024BBE0
			fight::Property* TightStrafeRunTrack::GetProperty(int index)
			{
				return gTightStrafeRunTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1024BC00
			void TightStrafeRunTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTightStrafeRunTrackProperties);
			}

			// FUNCTION: ENGINE 0x1024BC10
			TightStrafeRunTrack::TightStrafeRunTrack() : speedFactor(-1.0f, -1.0f, -1.0f), distance(3e+01f), distanceTolerance(2.0f), extraHeightStart(2.0f), freeRadiusEnd(2.0f), heightAtTarget(1e+01f), heightTolerance(2.0f), lengthPostStart(2.0f), maxSpeed(1.0f), minSpeed(0.8f), timeBegin(0.0f), timeEnd(-1.0f), turnRate(5.2359877f), temporaryTarget(0), goBack(true), goUpSoon(true), useTargetIntermediate(false)
			{
			}

			// FUNCTION: ENGINE 0x1024BCF0
			float TightStrafeRunTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1024BD00
			float TightStrafeRunTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1024BD10
			TightStrafeRunTrack::~TightStrafeRunTrack()
			{
			}

			// FUNCTION: ENGINE 0x1024E3D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TightStrafeRunTrack::RegisterProperties()
			{
				if (gTightStrafeRunTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TightStrafeRunTrack>("timeBegin", &TightStrafeRunTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TightStrafeRunTrack>("timeEnd", &TightStrafeRunTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TightStrafeRunTrack>("distance", &TightStrafeRunTrack::SetDistance);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<TightStrafeRunTrack>("turnRate", &TightStrafeRunTrack::SetTurnRate);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<TightStrafeRunTrack>("minSpeed", &TightStrafeRunTrack::SetMinSpeed);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<TightStrafeRunTrack>("maxSpeed", &TightStrafeRunTrack::SetMaxSpeed);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<TightStrafeRunTrack>("distanceTolerance", &TightStrafeRunTrack::SetDistanceTolerance);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<TightStrafeRunTrack>("heightTolerance", &TightStrafeRunTrack::SetHeightTolerance);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<TightStrafeRunTrack>("extraHeightStart", &TightStrafeRunTrack::SetExtraHeightStart);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<TightStrafeRunTrack>("lengthPostStart", &TightStrafeRunTrack::SetLengthPostStart);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<TightStrafeRunTrack>("freeRadiusEnd", &TightStrafeRunTrack::SetFreeRadiusEnd);
					properties[10] = property;
					property = new fight::PropertyBool<TightStrafeRunTrack>("goBack", &TightStrafeRunTrack::SetGoBack);
					properties[11] = property;
					property = new fight::PropertyBool<TightStrafeRunTrack>("useTargetIntermediate", &TightStrafeRunTrack::SetUseTargetIntermediate);
					properties[12] = property;
					property = new fight::PropertyBool<TightStrafeRunTrack>("goUpSoon", &TightStrafeRunTrack::SetGoUpSoon);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<TightStrafeRunTrack>("heightAtTarget", &TightStrafeRunTrack::SetHeightAtTarget);
					properties[14] = property;
					property = new fight::PropertyEnumConstList<TightStrafeRunTrack>("temporaryTarget", motion::gJointLookAtTrackWhereTable, motion::gJointLookAtTrackWhereCount, &TightStrafeRunTrack::SetTemporaryTarget);
					properties[15] = property;
					property = new fight::PropertyVector<TightStrafeRunTrack>("speedFactor", &TightStrafeRunTrack::SetSpeedFactor);
					properties[16] = property;
					fight::RegisterPropertyList(properties, &gTightStrafeRunTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1024CFD0
			fight::TrackFactory* CreateTightStrafeRunTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TightStrafeRunTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1024F2B0
			void RegisterTightStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TightStrafeRunTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gPredefinedPatrolTrackProperties;  // 0x11255BBC

			// FUNCTION: ENGINE 0x1024B200
			bool PredefinedPatrolTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B220
			bool PredefinedPatrolTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B240
			bool PredefinedPatrolTrack::SetFreeRadius(float newValue)
			{
				freeRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B260
			bool PredefinedPatrolTrack::SetPrimaryLength(float newValue)
			{
				primaryLength = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B280
			bool PredefinedPatrolTrack::SetSecondaryLength(float newValue)
			{
				secondaryLength = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B2A0
			bool PredefinedPatrolTrack::SetFreeRadiusPath(float newValue)
			{
				freeRadiusPath = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B2C0
			bool PredefinedPatrolTrack::SetDistanceToStartTolerance(float newValue)
			{
				distanceToStartTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B2E0
			bool PredefinedPatrolTrack::SetDistanceTolerance(float newValue)
			{
				distanceTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B300
			bool PredefinedPatrolTrack::SetMaxPitch(float newValue)
			{
				maxPitch = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1024BD20
			fight::Property* PredefinedPatrolTrack::GetProperty(int index)
			{
				return gPredefinedPatrolTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1024BD40
			void PredefinedPatrolTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPredefinedPatrolTrackProperties);
			}

			// FUNCTION: ENGINE 0x1024BD50
			PredefinedPatrolTrack::PredefinedPatrolTrack() : distanceToStartTolerance(2e+01f), distanceTolerance(2e+01f), freeRadius(2e+01f), freeRadiusPath(2e+01f), maxPitch(6.2831855f), primaryLength(2e+01f), secondaryLength(2e+01f), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1024BDC0
			float PredefinedPatrolTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1024BDD0
			float PredefinedPatrolTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1024BDE0
			PredefinedPatrolTrack::~PredefinedPatrolTrack()
			{
			}

			// FUNCTION: ENGINE 0x1024E850
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PredefinedPatrolTrack::RegisterProperties()
			{
				if (gPredefinedPatrolTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PredefinedPatrolTrack>("timeBegin", &PredefinedPatrolTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PredefinedPatrolTrack>("timeEnd", &PredefinedPatrolTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<PredefinedPatrolTrack>("freeRadius", &PredefinedPatrolTrack::SetFreeRadius);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<PredefinedPatrolTrack>("primaryLength", &PredefinedPatrolTrack::SetPrimaryLength);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<PredefinedPatrolTrack>("secondaryLength", &PredefinedPatrolTrack::SetSecondaryLength);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<PredefinedPatrolTrack>("freeRadiusPath", &PredefinedPatrolTrack::SetFreeRadiusPath);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<PredefinedPatrolTrack>("distanceToStartTolerance", &PredefinedPatrolTrack::SetDistanceToStartTolerance);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<PredefinedPatrolTrack>("distanceTolerance", &PredefinedPatrolTrack::SetDistanceTolerance);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<PredefinedPatrolTrack>("maxPitch", &PredefinedPatrolTrack::SetMaxPitch);
					properties[8] = property;
					fight::RegisterPropertyList(properties, &gPredefinedPatrolTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1024D000
			fight::TrackFactory* CreatePredefinedPatrolTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PredefinedPatrolTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1024F2E0
			void RegisterPredefinedPatrolTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PredefinedPatrolTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTryStrafeRunTrackProperties;  // 0x11255BC0

			// FUNCTION: ENGINE 0x1024B320
			bool TryStrafeRunTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B340
			bool TryStrafeRunTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B360
			bool TryStrafeRunTrack::SetMinDistance(float newValue)
			{
				minDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B380
			bool TryStrafeRunTrack::SetMaxDistance(float newValue)
			{
				maxDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B3A0
			bool TryStrafeRunTrack::SetMinAngle(float newValue)
			{
				minAngle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B3C0
			bool TryStrafeRunTrack::SetFreeRadiusEnd(float newValue)
			{
				freeRadiusEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B3E0
			bool TryStrafeRunTrack::SetFreeRadiusTarget(float newValue)
			{
				freeRadiusTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B400
			bool TryStrafeRunTrack::SetNumTries(int newValue)
			{
				numTries = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B420
			bool TryStrafeRunTrack::SetMinHeightAtTarget(float newValue)
			{
				minHeightAtTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B440
			bool TryStrafeRunTrack::SetMaxHeightAtEnds(float newValue)
			{
				maxHeightAtEnds = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B460
			bool TryStrafeRunTrack::SetMinHeightAtEnds(float newValue)
			{
				minHeightAtEnds = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B480
			bool TryStrafeRunTrack::SetSafeHeightAtEnds(float newValue)
			{
				safeHeightAtEnds = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B4A0
			bool TryStrafeRunTrack::SetMaxHeightDiffTargetAndEnds(float newValue)
			{
				maxHeightDiffTargetAndEnds = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B4C0
			bool TryStrafeRunTrack::SetMaxHeightDiffTargetAndWaypoint(float newValue)
			{
				maxHeightDiffTargetAndWaypoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B4E0
			bool TryStrafeRunTrack::SetMaxPathHeightFromTarget(float newValue)
			{
				maxPathHeightFromTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B500
			bool TryStrafeRunTrack::SetMaxPathYaw(float newValue)
			{
				maxPathYaw = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B520
			bool TryStrafeRunTrack::SetMaxPathPitch(float newValue)
			{
				maxPathPitch = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B540
			bool TryStrafeRunTrack::SetFreeRadiusPath(float newValue)
			{
				freeRadiusPath = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B560
			bool TryStrafeRunTrack::SetTurningFactorA(int newValue)
			{
				turningFactorA = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B580
			bool TryStrafeRunTrack::SetTurningFactorB(int newValue)
			{
				turningFactorB = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B5A0
			bool TryStrafeRunTrack::SetHeuristic(int newValue)
			{
				heuristic = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B5C0
			bool TryStrafeRunTrack::SetSameHeightPath(bool newValue)
			{
				sameHeightPath = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B5E0
			bool TryStrafeRunTrack::SetBrake(bool newValue)
			{
				brake = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B600
			bool TryStrafeRunTrack::SetTimeBetweenTries(float newValue)
			{
				timeBetweenTries = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B620
			fight::BranchHolder* TryStrafeRunTrack::SetIfFound()
			{
				return &ifFound;
			}

			// FUNCTION: ENGINE 0x1024B630
			bool TryStrafeRunTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024B650
			fight::ConditionList* TryStrafeRunTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1024BDF0
			fight::Property* TryStrafeRunTrack::GetProperty(int index)
			{
				return gTryStrafeRunTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1024BE10
			void TryStrafeRunTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTryStrafeRunTrackProperties);
			}

			// FUNCTION: ENGINE 0x1024BE20
			TryStrafeRunTrack::TryStrafeRunTrack() : ifFound(0), freeRadiusEnd(3e+01f), freeRadiusPath(2e+01f), freeRadiusTarget(18.0f), maxDistance(3e+01f), maxHeightAtEnds(2e+01f), maxHeightDiffTargetAndEnds(2e+01f), maxHeightDiffTargetAndWaypoint(2e+01f), maxPathHeightFromTarget(2e+02f), maxPathPitch(6.2831855f), maxPathYaw(6.2831855f), minAngle(2.8f), minDistance(3e+01f), minHeightAtEnds(1e+01f), minHeightAtTarget(1e+01f), safeHeightAtEnds(1e+01f), timeBegin(0.0f), timeBetweenTries(0.0f), timeEnd(-1.0f), heuristic(0), numTries(1), priority(0), turningFactorA(2), turningFactorB(0), brake(true), sameHeightPath(false)
			{
			}

			// FUNCTION: ENGINE 0x1024BF60
			float TryStrafeRunTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1024BF70
			float TryStrafeRunTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1024BF80
			TryStrafeRunTrack::~TryStrafeRunTrack()
			{
			}

			// FUNCTION: ENGINE 0x1024EAD0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TryStrafeRunTrack::RegisterProperties()
			{
				if (gTryStrafeRunTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("timeBegin", &TryStrafeRunTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("timeEnd", &TryStrafeRunTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("minDistance", &TryStrafeRunTrack::SetMinDistance);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("maxDistance", &TryStrafeRunTrack::SetMaxDistance);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("minAngle", &TryStrafeRunTrack::SetMinAngle);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("freeRadiusEnd", &TryStrafeRunTrack::SetFreeRadiusEnd);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("freeRadiusTarget", &TryStrafeRunTrack::SetFreeRadiusTarget);
					properties[6] = property;
					property = new fight::PropertyIntConstRange<TryStrafeRunTrack>("numTries", &TryStrafeRunTrack::SetNumTries);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("minHeightAtTarget", &TryStrafeRunTrack::SetMinHeightAtTarget);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("maxHeightAtEnds", &TryStrafeRunTrack::SetMaxHeightAtEnds);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("minHeightAtEnds", &TryStrafeRunTrack::SetMinHeightAtEnds);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("safeHeightAtEnds", &TryStrafeRunTrack::SetSafeHeightAtEnds);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("maxHeightDiffTargetAndEnds", &TryStrafeRunTrack::SetMaxHeightDiffTargetAndEnds);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("maxHeightDiffTargetAndWaypoint", &TryStrafeRunTrack::SetMaxHeightDiffTargetAndWaypoint);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("maxPathHeightFromTarget", &TryStrafeRunTrack::SetMaxPathHeightFromTarget);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("maxPathYaw", &TryStrafeRunTrack::SetMaxPathYaw);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("maxPathPitch", &TryStrafeRunTrack::SetMaxPathPitch);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("freeRadiusPath", &TryStrafeRunTrack::SetFreeRadiusPath);
					properties[17] = property;
					property = new fight::PropertyIntConstRange<TryStrafeRunTrack>("turningFactorA", &TryStrafeRunTrack::SetTurningFactorA);
					properties[18] = property;
					property = new fight::PropertyIntConstRange<TryStrafeRunTrack>("turningFactorB", &TryStrafeRunTrack::SetTurningFactorB);
					properties[19] = property;
					property = new fight::PropertyEnumConstList<TryStrafeRunTrack>("heuristic", gStrafeRunTrackHeuristicTable, gStrafeRunTrackHeuristicCount, &TryStrafeRunTrack::SetHeuristic);
					properties[20] = property;
					property = new fight::PropertyBool<TryStrafeRunTrack>("sameHeightPath", &TryStrafeRunTrack::SetSameHeightPath);
					properties[21] = property;
					property = new fight::PropertyBool<TryStrafeRunTrack>("brake", &TryStrafeRunTrack::SetBrake);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<TryStrafeRunTrack>("timeBetweenTries", &TryStrafeRunTrack::SetTimeBetweenTries);
					properties[23] = property;
					property = new fight::PropertyBranch<TryStrafeRunTrack>("ifFound", &TryStrafeRunTrack::SetIfFound);
					properties[24] = property;
					property = new fight::PropertyIntConstRange<TryStrafeRunTrack>("priority", &TryStrafeRunTrack::SetPriority);
					properties[25] = property;
					property = new fight::PropertyConditionGroup<TryStrafeRunTrack>("conditions", &TryStrafeRunTrack::SetConditions);
					properties[26] = property;
					fight::RegisterPropertyList(properties, &gTryStrafeRunTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1024D030
			fight::TrackFactory* CreateTryStrafeRunTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TryStrafeRunTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1024F310
			void RegisterTryStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TryStrafeRunTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<CanStrafeRunCondition>;
			template class fight::PropertyIntConstRange<CanStrafeRunCondition>;
			template class fight::PropertyBool<CanStrafeRunCondition>;
			template class fight::ConditionFactoryTemplate<CanStrafeRunCondition>;
			template class fight::ConditionFactoryCasterTemplate<CanStrafeRunCondition>;
			template class fight::PropertyFloatConstRange<StrafeRunTrack>;
			template class fight::PropertyIntConstRange<StrafeRunTrack>;
			template class fight::PropertyEnumConstList<StrafeRunTrack>;
			template class fight::PropertyBool<StrafeRunTrack>;
			template class fight::PropertyVector<StrafeRunTrack>;
			template class fight::TrackFactoryTemplate<StrafeRunTrack>;
			template class fight::TrackFactoryCasterTemplate<StrafeRunTrack>;
			template class fight::PropertyFloatConstRange<SimpleOpenStrafeRunTrack>;
			template class fight::PropertyBool<SimpleOpenStrafeRunTrack>;
			template class fight::PropertyVector<SimpleOpenStrafeRunTrack>;
			template class fight::TrackFactoryTemplate<SimpleOpenStrafeRunTrack>;
			template class fight::TrackFactoryCasterTemplate<SimpleOpenStrafeRunTrack>;
			template class fight::PropertyFloatConstRange<PrepareTightStrafeRunTrack>;
			template class fight::PropertyVector<PrepareTightStrafeRunTrack>;
			template class fight::TrackFactoryTemplate<PrepareTightStrafeRunTrack>;
			template class fight::TrackFactoryCasterTemplate<PrepareTightStrafeRunTrack>;
			template class fight::PropertyFloatConstRange<TryOpenStrafeRunTrack>;
			template class fight::PropertyIntConstRange<TryOpenStrafeRunTrack>;
			template class fight::PropertyBranch<TryOpenStrafeRunTrack>;
			template class fight::PropertyConditionGroup<TryOpenStrafeRunTrack>;
			template class fight::TrackFactoryTemplate<TryOpenStrafeRunTrack>;
			template class fight::TrackFactoryCasterTemplate<TryOpenStrafeRunTrack>;
			template class fight::PropertyFloatConstRange<TightStrafeRunTrack>;
			template class fight::PropertyBool<TightStrafeRunTrack>;
			template class fight::PropertyEnumConstList<TightStrafeRunTrack>;
			template class fight::PropertyVector<TightStrafeRunTrack>;
			template class fight::TrackFactoryTemplate<TightStrafeRunTrack>;
			template class fight::TrackFactoryCasterTemplate<TightStrafeRunTrack>;
			template class fight::PropertyFloatConstRange<PredefinedPatrolTrack>;
			template class fight::TrackFactoryTemplate<PredefinedPatrolTrack>;
			template class fight::TrackFactoryCasterTemplate<PredefinedPatrolTrack>;
			template class fight::PropertyFloatConstRange<TryStrafeRunTrack>;
			template class fight::PropertyIntConstRange<TryStrafeRunTrack>;
			template class fight::PropertyEnumConstList<TryStrafeRunTrack>;
			template class fight::PropertyBool<TryStrafeRunTrack>;
			template class fight::PropertyBranch<TryStrafeRunTrack>;
			template class fight::PropertyConditionGroup<TryStrafeRunTrack>;
			template class fight::TrackFactoryTemplate<TryStrafeRunTrack>;
			template class fight::TrackFactoryCasterTemplate<TryStrafeRunTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1024BFB0
// FUNCTION: ENGINE 0x1024BFE0
// FUNCTION: ENGINE 0x1024C010
// FUNCTION: ENGINE 0x1024C040
// FUNCTION: ENGINE 0x1024C070
// FUNCTION: ENGINE 0x1024C0A0
// FUNCTION: ENGINE 0x1024C0D0
// FUNCTION: ENGINE 0x1024C100
// FUNCTION: ENGINE 0x1024C130
// FUNCTION: ENGINE 0x1024C140
// FUNCTION: ENGINE 0x1024C170
// FUNCTION: ENGINE 0x1024C180
// FUNCTION: ENGINE 0x1024C1B0
// FUNCTION: ENGINE 0x1024C1C0
// FUNCTION: ENGINE 0x1024C1F0
// FUNCTION: ENGINE 0x1024C200
// FUNCTION: ENGINE 0x1024C230
// FUNCTION: ENGINE 0x1024C240
// FUNCTION: ENGINE 0x1024C270
// FUNCTION: ENGINE 0x1024C280
// FUNCTION: ENGINE 0x1024C2B0
// FUNCTION: ENGINE 0x1024C2C0
// FUNCTION: ENGINE 0x1024C2F0
// FUNCTION: ENGINE 0x1024C300
// FUNCTION: ENGINE 0x1024C330
// FUNCTION: ENGINE 0x1024C360
// FUNCTION: ENGINE 0x1024C390
// FUNCTION: ENGINE 0x1024C3A0
// FUNCTION: ENGINE 0x1024C3D0
// FUNCTION: ENGINE 0x1024C3F0
// FUNCTION: ENGINE 0x1024C400
// FUNCTION: ENGINE 0x1024C430
// FUNCTION: ENGINE 0x1024C450
// FUNCTION: ENGINE 0x1024C460
// FUNCTION: ENGINE 0x1024C490
// FUNCTION: ENGINE 0x1024C4C0
// FUNCTION: ENGINE 0x1024C4D0
// FUNCTION: ENGINE 0x1024C500
// FUNCTION: ENGINE 0x1024C520
// FUNCTION: ENGINE 0x1024C530
// FUNCTION: ENGINE 0x1024C570
// FUNCTION: ENGINE 0x1024C580
// FUNCTION: ENGINE 0x1024C5B0
// FUNCTION: ENGINE 0x1024C5D0
// FUNCTION: ENGINE 0x1024C5E0
// FUNCTION: ENGINE 0x1024C610
// FUNCTION: ENGINE 0x1024C630
// FUNCTION: ENGINE 0x1024C640
// FUNCTION: ENGINE 0x1024C670
// FUNCTION: ENGINE 0x1024C690
// FUNCTION: ENGINE 0x1024C6A0
// FUNCTION: ENGINE 0x1024C6D0
// FUNCTION: ENGINE 0x1024C700
// FUNCTION: ENGINE 0x1024C710
// FUNCTION: ENGINE 0x1024C740
// FUNCTION: ENGINE 0x1024C760
// FUNCTION: ENGINE 0x1024C770
// FUNCTION: ENGINE 0x1024C7A0
// FUNCTION: ENGINE 0x1024C7C0
// FUNCTION: ENGINE 0x1024C7D0
// FUNCTION: ENGINE 0x1024C800
// FUNCTION: ENGINE 0x1024C830
// FUNCTION: ENGINE 0x1024C840
// FUNCTION: ENGINE 0x1024C870
// FUNCTION: ENGINE 0x1024C890
// FUNCTION: ENGINE 0x1024C8A0
// FUNCTION: ENGINE 0x1024C8D0
// FUNCTION: ENGINE 0x1024C900
// FUNCTION: ENGINE 0x1024C910
// FUNCTION: ENGINE 0x1024C940
// FUNCTION: ENGINE 0x1024C960
// FUNCTION: ENGINE 0x1024C970
// FUNCTION: ENGINE 0x1024C9A0
// FUNCTION: ENGINE 0x1024C9C0
// FUNCTION: ENGINE 0x1024C9F0
// FUNCTION: ENGINE 0x1024CA10
// FUNCTION: ENGINE 0x1024CA40
// FUNCTION: ENGINE 0x1024CA70
// FUNCTION: ENGINE 0x1024CA80
// FUNCTION: ENGINE 0x1024CAB0
// FUNCTION: ENGINE 0x1024CAD0
// FUNCTION: ENGINE 0x1024CAE0
// FUNCTION: ENGINE 0x1024CB20
// FUNCTION: ENGINE 0x1024CB30
// FUNCTION: ENGINE 0x1024CB60
// FUNCTION: ENGINE 0x1024CB80
// FUNCTION: ENGINE 0x1024CB90
// FUNCTION: ENGINE 0x1024CBC0
// FUNCTION: ENGINE 0x1024CBE0
// FUNCTION: ENGINE 0x1024CBF0
// FUNCTION: ENGINE 0x1024CC20
// FUNCTION: ENGINE 0x1024CC50
// FUNCTION: ENGINE 0x1024CC60
// FUNCTION: ENGINE 0x1024CC90
// FUNCTION: ENGINE 0x1024CCC0
// FUNCTION: ENGINE 0x1024CCD0
// FUNCTION: ENGINE 0x1024CD00
// FUNCTION: ENGINE 0x1024CD20
// FUNCTION: ENGINE 0x1024CD30
// FUNCTION: ENGINE 0x1024CD70
// FUNCTION: ENGINE 0x1024CD80
// FUNCTION: ENGINE 0x1024CDB0
// FUNCTION: ENGINE 0x1024CDD0
// FUNCTION: ENGINE 0x1024CDE0
// FUNCTION: ENGINE 0x1024CE10
// FUNCTION: ENGINE 0x1024CE30
// FUNCTION: ENGINE 0x1024CE40
// FUNCTION: ENGINE 0x1024CE70
// FUNCTION: ENGINE 0x1024CE90
// FUNCTION: ENGINE 0x1024CEC0
// FUNCTION: ENGINE 0x1024F340
// FUNCTION: ENGINE 0x1024F370
// FUNCTION: ENGINE 0x1024F390
// FUNCTION: ENGINE 0x1024F3C0
// FUNCTION: ENGINE 0x1024F3F0
// FUNCTION: ENGINE 0x1024F420
// FUNCTION: ENGINE 0x1024F440
// FUNCTION: ENGINE 0x1024F470
// FUNCTION: ENGINE 0x1024F490
// FUNCTION: ENGINE 0x1024F4C0
// FUNCTION: ENGINE 0x1024F4E0
// FUNCTION: ENGINE 0x1024F510
// FUNCTION: ENGINE 0x1024F530
// FUNCTION: ENGINE 0x1024F560
// FUNCTION: ENGINE 0x1024F580
// FUNCTION: ENGINE 0x1024F5B0
// FUNCTION: ENGINE 0x1024F5E0
// FUNCTION: ENGINE 0x1024F630
// FUNCTION: ENGINE 0x1024F680
// FUNCTION: ENGINE 0x1024F6D0
// FUNCTION: ENGINE 0x1024F720
// FUNCTION: ENGINE 0x1024F770
// FUNCTION: ENGINE 0x1024F7C0
// FUNCTION: ENGINE 0x1024F810
