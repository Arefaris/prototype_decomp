// Fight items of the ai group: CanStrafeRunCondition, StrafeRunTrack, SimpleOpenStrafeRunTrack, PrepareTightStrafeRunTrack, TryOpenStrafeRunTrack, TightStrafeRunTrack, PredefinedPatrolTrack, TryStrafeRunTrack (unit 0x1024A810 - 0x1024F860; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_STRAFE_H
#define PROTO_FIGHTITEMS_AI_AI_STRAFE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/engine/fight/effecttrack.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"
#include "code/container/arrayfixed.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/engine/gameobject/gameobjectparams.h"
#include "code/math/vector.h"

namespace engine
{
	// 0x1020C120 (the strafe actions' copy): stores a reference counted object in a slot, releasing the previous one
	void AssignRefCountedCopy6(core::IRefCount** slot, core::IRefCount* value);
}

namespace core
{
	// 0x1020C160 (the strafe actions' copy): lets go of the object in a slot
	void SafeReleaseRefCopy7(IRefCount** slot);
}

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

			// RTTI: proto::fightitems::ai::StrafeRunParams (the owner a strafe run is made on, kind 0x2100F; the part the actions copy)
			class StrafeRunParams : public engine::GameObjectParams
			{
			public:
				math::Vector unknown18;  // +0x18
				math::Vector unknown24;  // +0x24
				math::Vector unknown30;  // +0x30
			};

			// The owner as the strafe run actions keep it: null when the owner is none or not strafe run params (0x1020B630 is the engine's out of line copy)
			inline StrafeRunParams* AsStrafeRunParams(core::IRefCount* owner)
			{
				if (owner == 0)
				{
					return 0;
				}
				return ((motion::TrackOwner*)owner)->kind == 0x2100F ? (StrafeRunParams*)owner : 0;
			}

			// RTTI: proto::fightitems::ai::StrafeRunAction (9 vftable slots, 0x7C bytes)
			class StrafeRunAction : public fight::Action
			{
			public:
				// 0x1020DE00
				StrafeRunAction(StrafeRunTrack* newTrack, engine::GameObjectHandle newTarget, StrafeRunParams* newParams);
				// 0x1020D170
				virtual ~StrafeRunAction();

				// vftable slot 5 (0x10210300)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10210A60)
				virtual void Slot6();
				// vftable slot 7 (0x102132F0)
				virtual bool Slot7(int arg, float value);

				core::Link<StrafeRunTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				float unknown2C;  // +0x2C
				float unknown30;  // +0x30
				float unknown34;  // +0x34
				float unknown38;  // +0x38
				bool unknown3C;
				unsigned char unknown3D[0x3];
				int unknown40;
				unsigned char unknown44[0x34];
				StrafeRunParams* params;  // +0x78
			};
			// RTTI: proto::fightitems::ai::SimpleOpenStrafeRunAction (9 vftable slots, 0x54 bytes)
			class SimpleOpenStrafeRunAction : public fight::Action
			{
			public:
				// 0x1020EA60
				SimpleOpenStrafeRunAction(SimpleOpenStrafeRunTrack* newTrack, engine::GameObjectHandle newTarget, StrafeRunParams* newParams);
				// 0x1020D340
				virtual ~SimpleOpenStrafeRunAction();

				// vftable slot 5 (0x102147D0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x102129B0)
				virtual void Slot6();
				// vftable slot 7 (0x10214A10)
				virtual bool Slot7(int arg, float value);

				core::Link<SimpleOpenStrafeRunTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				math::Vector unknown2C;  // +0x2C
				math::Vector unknown38;  // +0x38
				math::Vector unknown44;  // +0x44
				int unknown50;  // +0x50
			};
			// RTTI: proto::fightitems::ai::PredefinedPatrolAction (9 vftable slots, 0xA4 bytes)
			class PredefinedPatrolAction : public fight::Action
			{
			public:
				// 0x10210230
				PredefinedPatrolAction(PredefinedPatrolTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x102102C0
				virtual ~PredefinedPatrolAction();

				// vftable slot 5 (0x10214C10)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x1020C030)
				virtual void Slot6();
				// vftable slot 7 (0x10214D30)
				virtual bool Slot7(int arg, float value);

				core::Link<PredefinedPatrolTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				container::ArrayFixed<math::Vector, 6> points;  // +0x2C
				int unknown78;  // +0x78
				int unknown7C;  // +0x7C
				int unknown80;  // +0x80
				unsigned char unknown84[0x18];
				bool unknown9C;  // +0x9C
				unsigned char unknown9D[0x7];
			};

			// RTTI: proto::fightitems::ai::TightStrafeRunAction (9 vftable slots, 0x90 bytes)
			class TightStrafeRunAction : public fight::Action
			{
			public:
				// 0x1020E080
				TightStrafeRunAction(TightStrafeRunTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x1020D1D0
				virtual ~TightStrafeRunAction();

				// vftable slot 5 (0x10213630)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x102119E0)
				virtual void Slot6();
				// vftable slot 7 (0x10213C20)
				virtual bool Slot7(int arg, float value);

				core::Link<TightStrafeRunTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				bool unknown2C;  // +0x2C
				unsigned char unknown2D[0x3];
				float unknown30;  // +0x30
				unsigned char unknown34[0x4];
				int unknown38;  // +0x38
				float unknown3C;  // +0x3C
				float unknown40;  // +0x40
				float unknown44;  // +0x44
				float unknown48;  // +0x48
				float unknown4C;  // +0x4C
				float unknown50;  // +0x50
				float unknown54;  // +0x54
				float unknown58;  // +0x58
				float unknown5C;  // +0x5C
				float unknown60;  // +0x60
				float unknown64;  // +0x64
				int unknown68;  // +0x68
				int unknown6C;  // +0x6C
				bool unknown70;  // +0x70
				unsigned char unknown71[0x3];
				math::Vector unknown74;  // +0x74
				math::Vector unknown80;  // +0x80
				engine::HandleBase unknown8C;  // +0x8C
			};
			// RTTI: proto::fightitems::ai::PrepareTightStrafeRunAction (9 vftable slots, 0x88 bytes)
			class PrepareTightStrafeRunAction : public fight::Action
			{
			public:
				// 0x1020E5B0
				PrepareTightStrafeRunAction(PrepareTightStrafeRunTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x1020D220
				virtual ~PrepareTightStrafeRunAction();

				// vftable slot 5 (0x10214090)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10212500)
				virtual void Slot6();
				// vftable slot 7 (0x10214470)
				virtual bool Slot7(int arg, float value);

				core::Link<PrepareTightStrafeRunTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				int unknown2C;  // +0x2C
				math::Vector unknown30;  // +0x30
				math::Vector unknown3C;  // +0x3C
				math::Vector unknown48;  // +0x48
				float unknown54;  // +0x54
				float unknown58;  // +0x58
				int unknown5C;  // +0x5C
				int unknown60;  // +0x60
				bool unknown64;  // +0x64
				unsigned char unknown65[0x3];
				math::Vector unknown68;  // +0x68
				math::Vector unknown74;  // +0x74
				float unknown80;  // +0x80
				unsigned char unknown84[0x4];
			};
			// RTTI: proto::fightitems::ai::TryOpenStrafeRunAction (9 vftable slots, 0x60 bytes)
			class TryOpenStrafeRunAction : public fight::Action
			{
			public:
				// 0x1020E900
				TryOpenStrafeRunAction(TryOpenStrafeRunTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* newEffect, fight::Track* newListener);
				// 0x1020D2E0
				virtual ~TryOpenStrafeRunAction();

				// vftable slot 5 (0x1020E9D0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x1020C020)
				virtual void Slot6();
				// vftable slot 7 (0x10210850)
				virtual bool Slot7(int arg, float value);

				core::IRefCount* effect;  // +0x1C
				engine::TrackWatch listener;  // +0x20
				core::Link<TryOpenStrafeRunTrack> link;  // +0x2C
				engine::GameObjectHandle target;  // +0x38
				unsigned char unknown3C[0x24];
			};
			// ---- actions end
		}
	}
}

#endif
