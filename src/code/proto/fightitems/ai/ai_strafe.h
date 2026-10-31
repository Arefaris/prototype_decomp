// Fight items of the ai group: CanStrafeRunCondition, StrafeRunTrack, SimpleOpenStrafeRunTrack, PrepareTightStrafeRunTrack, TryOpenStrafeRunTrack, TightStrafeRunTrack, PredefinedPatrolTrack, TryStrafeRunTrack (unit 0x1024A810 - 0x1024F860; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_STRAFE_H
#define PROTO_FIGHTITEMS_AI_AI_STRAFE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::CanStrafeRunCondition (10 vftable slots, 0x20 bytes)
			class CanStrafeRunCondition : public fight::Condition
			{
			public:
				// 0x1024B690
				CanStrafeRunCondition();
				virtual ~CanStrafeRunCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1020D9F0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetTimeTolerance(float newValue);
				bool SetDistanceTolerance(float newValue);
				bool SetMinDelta(int newValue);
				bool SetMaxDelta(int newValue);
				bool SetFarthestPossible(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distanceTolerance;  // +0xC
					float timeTolerance;  // +0x10
					int maxDelta;  // +0x14
					int minDelta;  // +0x18
					bool farthestPossible;  // +0x1C
					unsigned char unknown1D[0x3];
			};

			extern fight::Property** gCanStrafeRunConditionProperties;
			fight::ConditionFactory* CreateCanStrafeRunConditionFactory(const char* name);
			void RegisterCanStrafeRunConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::StrafeRunTrack (16 vftable slots, 0x80 bytes)
			class StrafeRunTrack : public fight::Track
			{
			public:
				// 0x1024B720
				StrafeRunTrack();
				virtual ~StrafeRunTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1020ED90, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMinDistance(float newValue);
				bool SetMaxDistance(float newValue);
				bool SetMinAngle(float newValue);
				bool SetFreeRadiusEnd(float newValue);
				bool SetFreeRadiusTarget(float newValue);
				bool SetMinHeightAtTarget(float newValue);
				bool SetMaxHeightAtEnds(float newValue);
				bool SetMinHeightAtEnds(float newValue);
				bool SetSafeHeightAtEnds(float newValue);
				bool SetMaxHeightDiffTargetAndEnds(float newValue);
				bool SetMaxPathHeightFromTarget(float newValue);
				bool SetMaxPathYaw(float newValue);
				bool SetMaxPathPitch(float newValue);
				bool SetFreeRadiusPath(float newValue);
				bool SetTurningFactorA(int newValue);
				bool SetTurningFactorB(int newValue);
				bool SetHeuristic(int newValue);
				bool SetSameHeightPath(bool newValue);
				bool SetOrientAtEnd(bool newValue);
				bool SetGoBack(bool newValue);
				bool SetBrake(bool newValue);
				bool SetMinSpeed(float newValue);
				bool SetMaxSpeed(float newValue);
				bool SetSpeedFactor(const math::Vector& newValue);
				bool SetPassMidPointSpeedFactor(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector passMidPointSpeedFactor;  // +0x10
					math::Vector speedFactor;  // +0x1C
					float freeRadiusEnd;  // +0x28
					float freeRadiusPath;  // +0x2C
					float freeRadiusTarget;  // +0x30
					float maxDistance;  // +0x34
					float maxHeightAtEnds;  // +0x38
					float maxHeightDiffTargetAndEnds;  // +0x3C
					float maxPathHeightFromTarget;  // +0x40
					float maxPathPitch;  // +0x44
					float maxPathYaw;  // +0x48
					float maxSpeed;  // +0x4C
					float minAngle;  // +0x50
					float minDistance;  // +0x54
					float minHeightAtEnds;  // +0x58
					float minHeightAtTarget;  // +0x5C
					float minSpeed;  // +0x60
					float safeHeightAtEnds;  // +0x64
					float timeBegin;  // +0x68
					float timeEnd;  // +0x6C
					int heuristic;  // +0x70
					int turningFactorA;  // +0x74
					int turningFactorB;  // +0x78
					bool brake;  // +0x7C
					bool goBack;  // +0x7D
					bool orientAtEnd;  // +0x7E
					bool sameHeightPath;  // +0x7F
			};

			extern fight::Property** gStrafeRunTrackProperties;
			fight::TrackFactory* CreateStrafeRunTrackFactory(const char* name);
			void RegisterStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::SimpleOpenStrafeRunTrack (16 vftable slots, 0x44 bytes)
			class SimpleOpenStrafeRunTrack : public fight::Track
			{
			public:
				// 0x1024B8C0
				SimpleOpenStrafeRunTrack();
				virtual ~SimpleOpenStrafeRunTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x102101C0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetFreeRadiusPath(float newValue);
				bool SetFreeRadiusPathToStart(float newValue);
				bool SetMinHeightStartFromTarget(float newValue);
				bool SetMinHeightGoUpStart(float newValue);
				bool SetReserveVolumeMargin(float newValue);
				bool SetReserveVolumeSideRadius(float newValue);
				bool SetToleranceToStart(float newValue);
				bool SetOrientAtEnd(bool newValue);
				bool SetSpeedFactor(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector speedFactor;  // +0x10
					float freeRadiusPath;  // +0x1C
					float freeRadiusPathToStart;  // +0x20
					float minHeightGoUpStart;  // +0x24
					float minHeightStartFromTarget;  // +0x28
					float reserveVolumeMargin;  // +0x2C
					float reserveVolumeSideRadius;  // +0x30
					float timeBegin;  // +0x34
					float timeEnd;  // +0x38
					float toleranceToStart;  // +0x3C
					bool orientAtEnd;  // +0x40
					unsigned char unknown41[0x3];
			};

			extern fight::Property** gSimpleOpenStrafeRunTrackProperties;
			fight::TrackFactory* CreateSimpleOpenStrafeRunTrackFactory(const char* name);
			void RegisterSimpleOpenStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::PrepareTightStrafeRunTrack (16 vftable slots, 0x44 bytes)
			class PrepareTightStrafeRunTrack : public fight::Track
			{
			public:
				// 0x1024B9B0
				PrepareTightStrafeRunTrack();
				virtual ~PrepareTightStrafeRunTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1020F220, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMinSpeed(float newValue);
				bool SetMaxSpeed(float newValue);
				bool SetDistanceTolerance(float newValue);
				bool SetHeightTolerance(float newValue);
				bool SetExtraHeightStart(float newValue);
				bool SetLengthPostStart(float newValue);
				bool SetWaitTimeAtStart(float newValue);
				bool SetHeightAtTarget(float newValue);
				bool SetSpeedFactor(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector speedFactor;  // +0x10
					float distanceTolerance;  // +0x1C
					float extraHeightStart;  // +0x20
					float heightAtTarget;  // +0x24
					float heightTolerance;  // +0x28
					float lengthPostStart;  // +0x2C
					float maxSpeed;  // +0x30
					float minSpeed;  // +0x34
					float timeBegin;  // +0x38
					float timeEnd;  // +0x3C
					float waitTimeAtStart;  // +0x40
			};

			extern fight::Property** gPrepareTightStrafeRunTrackProperties;
			fight::TrackFactory* CreatePrepareTightStrafeRunTrackFactory(const char* name);
			void RegisterPrepareTightStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TryOpenStrafeRunTrack (16 vftable slots, 0x7C bytes)
			class TryOpenStrafeRunTrack : public fight::Track
			{
			public:
				// 0x1024BAC0
				TryOpenStrafeRunTrack();
				virtual ~TryOpenStrafeRunTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1020F960, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMaxHeightPath(float newValue);
				bool SetMaxHeightEnd(float newValue);
				bool SetMinHeightWithTarget(float newValue);
				bool SetEndHigherThanTarget(float newValue);
				bool SetMaxHeightStartWithTarget(float newValue);
				bool SetMinHeightStartWithTarget(float newValue);
				bool SetMaxLength(int newValue);
				bool SetMinLength(int newValue);
				bool SetMinLengthAfterTarget(int newValue);
				bool SetMinLengthBeforeTarget(float newValue);
				bool SetMaxHeightToIgnoreStartLength(float newValue);
				bool SetFreeRadiusStart(float newValue);
				bool SetFreeRadiusPath(float newValue);
				bool SetFreeRadiusEnd(float newValue);
				fight::BranchHolder* SetIfFound();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder ifFound;  // +0x10
					fight::ConditionList conditions;  // +0x34
					float endHigherThanTarget;  // +0x38
					float freeRadiusEnd;  // +0x3C
					float freeRadiusPath;  // +0x40
					float freeRadiusStart;  // +0x44
					float maxHeightEnd;  // +0x48
					float maxHeightPath;  // +0x4C
					float maxHeightStartWithTarget;  // +0x50
					float maxHeightToIgnoreStartLength;  // +0x54
					float minHeightStartWithTarget;  // +0x58
					float minHeightWithTarget;  // +0x5C
					float minLengthBeforeTarget;  // +0x60
					float timeBegin;  // +0x64
					float timeEnd;  // +0x68
					int maxLength;  // +0x6C
					int minLength;  // +0x70
					int minLengthAfterTarget;  // +0x74
					int priority;  // +0x78
			};

			extern fight::Property** gTryOpenStrafeRunTrackProperties;
			fight::TrackFactory* CreateTryOpenStrafeRunTrackFactory(const char* name);
			void RegisterTryOpenStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TightStrafeRunTrack (16 vftable slots, 0x54 bytes)
			class TightStrafeRunTrack : public fight::Track
			{
			public:
				// 0x1024BC10
				TightStrafeRunTrack();
				virtual ~TightStrafeRunTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1020F1D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetDistance(float newValue);
				bool SetTurnRate(float newValue);
				bool SetMinSpeed(float newValue);
				bool SetMaxSpeed(float newValue);
				bool SetDistanceTolerance(float newValue);
				bool SetHeightTolerance(float newValue);
				bool SetExtraHeightStart(float newValue);
				bool SetLengthPostStart(float newValue);
				bool SetFreeRadiusEnd(float newValue);
				bool SetGoBack(bool newValue);
				bool SetUseTargetIntermediate(bool newValue);
				bool SetGoUpSoon(bool newValue);
				bool SetHeightAtTarget(float newValue);
				bool SetTemporaryTarget(int newValue);
				bool SetSpeedFactor(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector speedFactor;  // +0x10
					float distance;  // +0x1C
					float distanceTolerance;  // +0x20
					float extraHeightStart;  // +0x24
					float freeRadiusEnd;  // +0x28
					float heightAtTarget;  // +0x2C
					float heightTolerance;  // +0x30
					float lengthPostStart;  // +0x34
					float maxSpeed;  // +0x38
					float minSpeed;  // +0x3C
					float timeBegin;  // +0x40
					float timeEnd;  // +0x44
					float turnRate;  // +0x48
					int temporaryTarget;  // +0x4C
					bool goBack;  // +0x50
					bool goUpSoon;  // +0x51
					bool useTargetIntermediate;  // +0x52
					unsigned char unknown53[0x1];
			};

			extern fight::Property** gTightStrafeRunTrackProperties;
			fight::TrackFactory* CreateTightStrafeRunTrackFactory(const char* name);
			void RegisterTightStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::PredefinedPatrolTrack (16 vftable slots, 0x34 bytes)
			class PredefinedPatrolTrack : public fight::Track
			{
			public:
				// 0x1024BD50
				PredefinedPatrolTrack();
				virtual ~PredefinedPatrolTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x102109E0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetFreeRadius(float newValue);
				bool SetPrimaryLength(float newValue);
				bool SetSecondaryLength(float newValue);
				bool SetFreeRadiusPath(float newValue);
				bool SetDistanceToStartTolerance(float newValue);
				bool SetDistanceTolerance(float newValue);
				bool SetMaxPitch(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distanceToStartTolerance;  // +0x10
					float distanceTolerance;  // +0x14
					float freeRadius;  // +0x18
					float freeRadiusPath;  // +0x1C
					float maxPitch;  // +0x20
					float primaryLength;  // +0x24
					float secondaryLength;  // +0x28
					float timeBegin;  // +0x2C
					float timeEnd;  // +0x30
			};

			extern fight::Property** gPredefinedPatrolTrackProperties;
			fight::TrackFactory* CreatePredefinedPatrolTrackFactory(const char* name);
			void RegisterPredefinedPatrolTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TryStrafeRunTrack (16 vftable slots, 0x98 bytes)
			class TryStrafeRunTrack : public fight::Track
			{
			public:
				// 0x1024BE20
				TryStrafeRunTrack();
				virtual ~TryStrafeRunTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1020F270, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMinDistance(float newValue);
				bool SetMaxDistance(float newValue);
				bool SetMinAngle(float newValue);
				bool SetFreeRadiusEnd(float newValue);
				bool SetFreeRadiusTarget(float newValue);
				bool SetNumTries(int newValue);
				bool SetMinHeightAtTarget(float newValue);
				bool SetMaxHeightAtEnds(float newValue);
				bool SetMinHeightAtEnds(float newValue);
				bool SetSafeHeightAtEnds(float newValue);
				bool SetMaxHeightDiffTargetAndEnds(float newValue);
				bool SetMaxHeightDiffTargetAndWaypoint(float newValue);
				bool SetMaxPathHeightFromTarget(float newValue);
				bool SetMaxPathYaw(float newValue);
				bool SetMaxPathPitch(float newValue);
				bool SetFreeRadiusPath(float newValue);
				bool SetTurningFactorA(int newValue);
				bool SetTurningFactorB(int newValue);
				bool SetHeuristic(int newValue);
				bool SetSameHeightPath(bool newValue);
				bool SetBrake(bool newValue);
				bool SetTimeBetweenTries(float newValue);
				fight::BranchHolder* SetIfFound();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder ifFound;  // +0x10
					fight::ConditionList conditions;  // +0x34
					float freeRadiusEnd;  // +0x38
					float freeRadiusPath;  // +0x3C
					float freeRadiusTarget;  // +0x40
					float maxDistance;  // +0x44
					float maxHeightAtEnds;  // +0x48
					float maxHeightDiffTargetAndEnds;  // +0x4C
					float maxHeightDiffTargetAndWaypoint;  // +0x50
					float maxPathHeightFromTarget;  // +0x54
					float maxPathPitch;  // +0x58
					float maxPathYaw;  // +0x5C
					float minAngle;  // +0x60
					float minDistance;  // +0x64
					float minHeightAtEnds;  // +0x68
					float minHeightAtTarget;  // +0x6C
					float safeHeightAtEnds;  // +0x70
					float timeBegin;  // +0x74
					float timeBetweenTries;  // +0x78
					float timeEnd;  // +0x7C
					int heuristic;  // +0x80
					int numTries;  // +0x84
					int priority;  // +0x88
					int turningFactorA;  // +0x8C
					int turningFactorB;  // +0x90
					bool brake;  // +0x94
					bool sameHeightPath;  // +0x95
					unsigned char unknown96[0x2];
			};

			extern fight::Property** gTryStrafeRunTrackProperties;
			fight::TrackFactory* CreateTryStrafeRunTrackFactory(const char* name);
			void RegisterTryStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
