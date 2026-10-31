// Fight items of the ai group: TargetHasLoFCondition, HaveTokenCondition, DestinationTargetDistanceCondition, InfectedAlertedCondition, TargetHasLoFDistanceCondition, FloatShotAllowedCondition, InTargetsCameraCondition, ShouldRadioHQCondition, TargetIsHumanCondition, AnyPlayerDistanceCondition, AimingAtCondition, FacingAngleTargetCondition, HaveStrafeRunTokenCondition, AimingAtTargetCondition, TargetBeingHeldCondition, RefreshStrafeRunTokenTrack, ActionTrack, RequestTokenTrack, CombatDestinationFindTrack, CombatDestinationTransmitTrack, DrawDebugTrack, TargetTokenBoostTrack (unit 0x1021E550 - 0x10225F80; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_TOKEN_H
#define PROTO_FIGHTITEMS_AI_AI_TOKEN_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::TargetHasLoFCondition (10 vftable slots, 0x2C bytes)
			class TargetHasLoFCondition : public fight::Condition
			{
			public:
				// 0x1021F090
				TargetHasLoFCondition();
				virtual ~TargetHasLoFCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E5410, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetTimeTolerance(float newValue);
				bool SetDistanceTolerance(float newValue);
				bool SetCollisionFlags(int newValue);
				bool SetCollideWithType(int newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetRadius(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector offset;  // +0xC
					float distanceTolerance;  // +0x18
					float radius;  // +0x1C
					float timeTolerance;  // +0x20
					int collisionFlags;  // +0x24
					int collideWithType;  // +0x28
			};

			extern fight::Property** gTargetHasLoFConditionProperties;
			fight::ConditionFactory* CreateTargetHasLoFConditionFactory(const char* name);
			void RegisterTargetHasLoFConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::HaveTokenCondition (10 vftable slots, 0x14 bytes)
			class HaveTokenCondition : public fight::Condition
			{
			public:
				// 0x1021F150
				HaveTokenCondition();
				virtual ~HaveTokenCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E4E60, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetType(int newValue);
				bool SetOwner(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int owner;  // +0xC
					int type;  // +0x10
			};

			extern fight::Property** gHaveTokenConditionProperties;
			fight::ConditionFactory* CreateHaveTokenConditionFactory(const char* name);
			void RegisterHaveTokenConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DestinationTargetDistanceCondition (10 vftable slots, 0x1C bytes)
			class DestinationTargetDistanceCondition : public fight::Condition
			{
			public:
				// 0x1021F1C0
				DestinationTargetDistanceCondition();
				virtual ~DestinationTargetDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E4FB0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDirection(int newValue);
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);
				bool SetUseParams(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distance;  // +0xC
					int compare;  // +0x10
					int direction;  // +0x14
					bool useParams;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gDestinationTargetDistanceConditionProperties;
			fight::ConditionFactory* CreateDestinationTargetDistanceConditionFactory(const char* name);
			void RegisterDestinationTargetDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::InfectedAlertedCondition (10 vftable slots, 0x1C bytes)
			class InfectedAlertedCondition : public fight::Condition
			{
			public:
				// 0x1021F240
				InfectedAlertedCondition();
				virtual ~InfectedAlertedCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E6430, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDirection(int newValue);
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);
				bool SetTargetingMe(bool newValue);
				bool SetRequireToughGuy(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distance;  // +0xC
					int compare;  // +0x10
					int direction;  // +0x14
					bool requireToughGuy;  // +0x18
					bool targetingMe;  // +0x19
					unsigned char unknown1A[0x2];
			};

			extern fight::Property** gInfectedAlertedConditionProperties;
			fight::ConditionFactory* CreateInfectedAlertedConditionFactory(const char* name);
			void RegisterInfectedAlertedConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetHasLoFDistanceCondition (10 vftable slots, 0x34 bytes)
			class TargetHasLoFDistanceCondition : public fight::Condition
			{
			public:
				// 0x1021F2D0
				TargetHasLoFDistanceCondition();
				virtual ~TargetHasLoFDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E55C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetTimeTolerance(float newValue);
				bool SetDistanceTolerance(float newValue);
				bool SetCollisionFlags(int newValue);
				bool SetCollideWithTypeLessThanDist(int newValue);
				bool SetCollideWithTypeAnyDist(int newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetCompare(int newValue);
				bool SetDistanceFromTargetSqr(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector offset;  // +0xC
					float distanceFromTargetSqr;  // +0x18
					float distanceTolerance;  // +0x1C
					float timeTolerance;  // +0x20
					int collisionFlags;  // +0x24
					int compare;  // +0x28
					int collideWithTypeAnyDist;  // +0x2C
					int collideWithTypeLessThanDist;  // +0x30
			};

			extern fight::Property** gTargetHasLoFDistanceConditionProperties;
			fight::ConditionFactory* CreateTargetHasLoFDistanceConditionFactory(const char* name);
			void RegisterTargetHasLoFDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::FloatShotAllowedCondition (10 vftable slots, 0xC bytes)
			class FloatShotAllowedCondition : public fight::Condition
			{
			public:
				// 0x1021F400
				FloatShotAllowedCondition();
				virtual ~FloatShotAllowedCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E6860, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gFloatShotAllowedConditionProperties;
			fight::ConditionFactory* CreateFloatShotAllowedConditionFactory(const char* name);
			void RegisterFloatShotAllowedConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::InTargetsCameraCondition (10 vftable slots, 0x10 bytes)
			class InTargetsCameraCondition : public fight::Condition
			{
			public:
				// 0x1021F460
				InTargetsCameraCondition();
				virtual ~InTargetsCameraCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E66F0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSize(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float size;  // +0xC
			};

			extern fight::Property** gInTargetsCameraConditionProperties;
			fight::ConditionFactory* CreateInTargetsCameraConditionFactory(const char* name);
			void RegisterInTargetsCameraConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ShouldRadioHQCondition (10 vftable slots, 0x10 bytes)
			class ShouldRadioHQCondition : public fight::Condition
			{
			public:
				// 0x1021F4D0
				ShouldRadioHQCondition();
				virtual ~ShouldRadioHQCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E63B0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetRadio(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool radio;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gShouldRadioHQConditionProperties;
			fight::ConditionFactory* CreateShouldRadioHQConditionFactory(const char* name);
			void RegisterShouldRadioHQConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetIsHumanCondition (10 vftable slots, 0x10 bytes)
			class TargetIsHumanCondition : public fight::Condition
			{
			public:
				// 0x1021F530
				TargetIsHumanCondition();
				virtual ~TargetIsHumanCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E6250, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetHuman(bool newValue);
				bool SetCheckPointPeds(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool checkPointPeds;  // +0xC
					bool human;  // +0xD
					unsigned char unknownE[0x2];
			};

			extern fight::Property** gTargetIsHumanConditionProperties;
			fight::ConditionFactory* CreateTargetIsHumanConditionFactory(const char* name);
			void RegisterTargetIsHumanConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::AnyPlayerDistanceCondition (10 vftable slots, 0x24 bytes)
			class AnyPlayerDistanceCondition : public fight::Condition
			{
			public:
				// 0x1021F5A0
				AnyPlayerDistanceCondition();
				virtual ~AnyPlayerDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E5260, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDirection(int newValue);
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);
				bool SetOffset(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector offset;  // +0xC
					float distance;  // +0x18
					int compare;  // +0x1C
					int direction;  // +0x20
			};

			extern fight::Property** gAnyPlayerDistanceConditionProperties;
			fight::ConditionFactory* CreateAnyPlayerDistanceConditionFactory(const char* name);
			void RegisterAnyPlayerDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::AimingAtCondition (10 vftable slots, 0x40 bytes)
			class AimingAtCondition : public fight::Condition
			{
			public:
				// 0x1021FE70
				AimingAtCondition();
				virtual ~AimingAtCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E5AC0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetJoint(const fight::Name& newValue);
				bool SetTolerance(float newValue);
				bool Set3D(bool newValue);
				bool SetHeading(const math::Vector& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetWhere(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name joint;  // +0x10
					math::Vector heading;  // +0x18
					math::Vector offset;  // +0x24
					float tolerance;  // +0x30
					int where;  // +0x34
					bool flag3D;  // +0x38
					unsigned char unknown39[0x7];
			};

			extern fight::Property** gAimingAtConditionProperties;
			fight::ConditionFactory* CreateAimingAtConditionFactory(const char* name);
			void RegisterAimingAtConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::FacingAngleTargetCondition (10 vftable slots, 0x1C bytes)
			class FacingAngleTargetCondition : public fight::Condition
			{
			public:
				// 0x1021F670
				FacingAngleTargetCondition();
				virtual ~FacingAngleTargetCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E5E70, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetType(int newValue);
				bool SetCompareTime(int newValue);
				bool SetAngle(float newValue);
				bool SetSigned(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float angle;  // +0xC
					int compareTime;  // +0x10
					int type;  // +0x14
					bool signedValue;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gFacingAngleTargetConditionProperties;
			fight::ConditionFactory* CreateFacingAngleTargetConditionFactory(const char* name);
			void RegisterFacingAngleTargetConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::HaveStrafeRunTokenCondition (10 vftable slots, 0x10 bytes)
			class HaveStrafeRunTokenCondition : public fight::Condition
			{
			public:
				// 0x1021F6F0
				HaveStrafeRunTokenCondition();
				virtual ~HaveStrafeRunTokenCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E44E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetRequestIt(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool requestIt;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gHaveStrafeRunTokenConditionProperties;
			fight::ConditionFactory* CreateHaveStrafeRunTokenConditionFactory(const char* name);
			void RegisterHaveStrafeRunTokenConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::AimingAtTargetCondition (10 vftable slots, 0x38 bytes)
			class AimingAtTargetCondition : public fight::Condition
			{
			public:
				// 0x1021FF60
				AimingAtTargetCondition();
				virtual ~AimingAtTargetCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E5810, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetJoint(const fight::Name& newValue);
				bool SetTolerance(float newValue);
				bool Set3D(bool newValue);
				bool SetHeading(const math::Vector& newValue);
				bool SetOffset(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name joint;  // +0x10
					math::Vector heading;  // +0x18
					math::Vector offset;  // +0x24
					float tolerance;  // +0x30
					bool flag3D;  // +0x34
					unsigned char unknown35[0x3];
			};

			extern fight::Property** gAimingAtTargetConditionProperties;
			fight::ConditionFactory* CreateAimingAtTargetConditionFactory(const char* name);
			void RegisterAimingAtTargetConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetBeingHeldCondition (10 vftable slots, 0x10 bytes)
			class TargetBeingHeldCondition : public fight::Condition
			{
			public:
				// 0x1021F780
				TargetBeingHeldCondition();
				virtual ~TargetBeingHeldCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101E6140, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetHeld(bool newValue);
				bool SetDontCountIfHeldByMe(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool dontCountIfHeldByMe;  // +0xC
					bool held;  // +0xD
					unsigned char unknownE[0x2];
			};

			extern fight::Property** gTargetBeingHeldConditionProperties;
			fight::ConditionFactory* CreateTargetBeingHeldConditionFactory(const char* name);
			void RegisterTargetBeingHeldConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::RefreshStrafeRunTokenTrack (16 vftable slots, 0x18 bytes)
			class RefreshStrafeRunTokenTrack : public fight::Track
			{
			public:
				// 0x1021F7F0
				RefreshStrafeRunTokenTrack();
				virtual ~RefreshStrafeRunTokenTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E7FC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
			};

			extern fight::Property** gRefreshStrafeRunTokenTrackProperties;
			fight::TrackFactory* CreateRefreshStrafeRunTokenTrackFactory(const char* name);
			void RegisterRefreshStrafeRunTokenTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ActionTrack (16 vftable slots, 0x1C bytes)
			class ActionTrack : public fight::Track
			{
			public:
				// 0x1021F880
				ActionTrack();
				virtual ~ActionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E7D20, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetButton(int newValue);
				// 0x101E4480 (another unit)
				const fight::EnumEntry* GetButtonEntry(int index);
				// 0x101E44A0 (another unit)
				int GetButtonCount();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int button;  // +0x18
			};

			extern fight::Property** gActionTrackProperties;
			fight::TrackFactory* CreateActionTrackFactory(const char* name);
			void RegisterActionTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::RequestTokenTrack (16 vftable slots, 0x1C bytes)
			class RequestTokenTrack : public fight::Track
			{
			public:
				// 0x1021F920
				RequestTokenTrack();
				virtual ~RequestTokenTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E7DC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int type;  // +0x18
			};

			extern fight::Property** gRequestTokenTrackProperties;
			fight::TrackFactory* CreateRequestTokenTrackFactory(const char* name);
			void RegisterRequestTokenTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::CombatDestinationFindTrack (17 vftable slots, 0xE8 bytes)
			class CombatDestinationFindTrack : public fight::Track
			{
			public:
				// 0x102200A0
				CombatDestinationFindTrack();
				virtual ~CombatDestinationFindTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E7CC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// vftable slot 16: whether the track overrides a property
				virtual bool Slot16(int index);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMinDistance(float newValue);
				bool SetMaxDistance(float newValue);
				bool SetMinAngle(float newValue);
				bool SetMaxAngle(float newValue);
				bool SetNumTries(int newValue);
				bool SetIgnoreRestrictions(bool newValue);
				bool SetCheckNotReserved(bool newValue);
				bool SetCheckCanGo(bool newValue);
				bool SetUseNavMeshHeight(bool newValue);
				bool SetHeightDifferenceCheck(int newValue);
				bool SetMaxHeightDifference(float newValue);
				bool SetMinHeightDifference(float newValue);
				bool SetLookJustCloser(float newValue);
				bool SetMinDistanceFromCurrent(float newValue);
				bool SetFreeRadiusAround(float newValue);
				bool SetAllowedAreas(int newValue);
				bool SetIgnoreAreasWhenAgentOutside(bool newValue);
				bool SetMaxDistanceToGround(float newValue);
				bool SetMaxAbsoluteHeight(float newValue);
				bool SetReferenceOffset(const math::Vector& newValue);
				bool SetAirDestination(bool newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetCameraVisibility(int newValue);
				bool SetCollisionFlagsLOF(int newValue);
				bool SetCollideWithTypeLOF(int newValue);
				bool SetOffsetLOF(const math::Vector& newValue);
				bool SetHeuristic(int newValue);
				bool SetInitialHeuristic(bool newValue);
				// 0x1021F9C0: sets or clears the override bits of a group's members (name guess)
				void ApplyGroup(int group, bool value);
				bool SetInitialHeuristicTimer(const fight::Name& newValue);
				bool SetInitialHeuristicMinTimer(float newValue);
				bool SetInitialHeuristicMinTimerFactor(float newValue);
				bool SetInitialHeuristicMaxTimer(float newValue);
				bool SetInitialHeuristicMaxTimerFactor(float newValue);
				bool SetReferencePosition(int newValue);
				bool SetDeadReckoningTime(float newValue);
				fight::BranchHolder* SetWhenFound();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned __int64 overrideMask;  // +0x10
					fight::BranchHolder whenFound;  // +0x18
					unsigned char unknown3C[0x4];
					fight::Name initialHeuristicTimer;  // +0x40
					math::Vector offset;  // +0x48
					math::Vector offsetLOF;  // +0x54
					math::Vector referenceOffset;  // +0x60
					fight::ConditionList conditions;  // +0x6C
					float deadReckoningTime;  // +0x70
					float freeRadiusAround;  // +0x74
					float initialHeuristicMaxTimer;  // +0x78
					float initialHeuristicMaxTimerFactor;  // +0x7C
					float initialHeuristicMinTimer;  // +0x80
					float initialHeuristicMinTimerFactor;  // +0x84
					float lookJustCloser;  // +0x88
					float maxAbsoluteHeight;  // +0x8C
					float maxAngle;  // +0x90
					float maxDistance;  // +0x94
					float maxDistanceToGround;  // +0x98
					float maxHeightDifference;  // +0x9C
					float minAngle;  // +0xA0
					float minDistance;  // +0xA4
					float minDistanceFromCurrent;  // +0xA8
					float minHeightDifference;  // +0xAC
					float timeBegin;  // +0xB0
					float timeEnd;  // +0xB4
					int cameraVisibility;  // +0xB8
					int collisionFlagsLOF;  // +0xBC
					int heightDifferenceCheck;  // +0xC0
					int heuristic;  // +0xC4
					int numTries;  // +0xC8
					int priority;  // +0xCC
					int referencePosition;  // +0xD0
					int allowedAreas;  // +0xD4
					int collideWithTypeLOF;  // +0xD8
					bool airDestination;  // +0xDC
					bool checkCanGo;  // +0xDD
					bool checkNotReserved;  // +0xDE
					bool ignoreAreasWhenAgentOutside;  // +0xDF
					bool ignoreRestrictions;  // +0xE0
					bool initialHeuristic;  // +0xE1
					bool useNavMeshHeight;  // +0xE2
					unsigned char unknownE3[0x5];
			};

			extern fight::Property** gCombatDestinationFindTrackProperties;
			fight::TrackFactory* CreateCombatDestinationFindTrackFactory(const char* name);
			void RegisterCombatDestinationFindTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::CombatDestinationTransmitTrack (16 vftable slots, 0x20 bytes)
			class CombatDestinationTransmitTrack : public fight::Track
			{
			public:
				// 0x10220350
				CombatDestinationTransmitTrack();
				virtual ~CombatDestinationTransmitTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E7C60, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
			};

			extern fight::Property** gCombatDestinationTransmitTrackProperties;
			fight::TrackFactory* CreateCombatDestinationTransmitTrackFactory(const char* name);
			void RegisterCombatDestinationTransmitTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DrawDebugTrack (16 vftable slots, 0x2C bytes)
			class DrawDebugTrack : public fight::Track
			{
			public:
				// 0x1021FAD0
				DrawDebugTrack();
				virtual ~DrawDebugTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E7D70, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetRadius(float newValue);
				bool SetColour(const math::Colour128& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Colour128 colour;  // +0x10
					float radius;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
			};

			extern fight::Property** gDrawDebugTrackProperties;
			fight::TrackFactory* CreateDrawDebugTrackFactory(const char* name);
			void RegisterDrawDebugTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetTokenBoostTrack (16 vftable slots, 0x1C bytes)
			class TargetTokenBoostTrack : public fight::Track
			{
			public:
				// 0x1021FBA0
				TargetTokenBoostTrack();
				virtual ~TargetTokenBoostTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E8010, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetExtraTokens(int newValue);
				bool SetBoostTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float boostTime;  // +0x10
					float timeBegin;  // +0x14
					int extraTokens;  // +0x18
			};

			extern fight::Property** gTargetTokenBoostTrackProperties;
			fight::TrackFactory* CreateTargetTokenBoostTrackFactory(const char* name);
			void RegisterTargetTokenBoostTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::RefreshStrafeRunTokenAction (9 vftable slots, 0x2C bytes)
			class RefreshStrafeRunTokenAction : public fight::Action
			{
			public:
				// 0x101E7980
				RefreshStrafeRunTokenAction(RefreshStrafeRunTokenTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101E4D20
				virtual ~RefreshStrafeRunTokenAction();

				// vftable slot 5 (0x101E44B0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101E7A70)
				virtual void Slot6();
				// vftable slot 7 (0x101E7A30)
				virtual bool Slot7(int arg, float value);

				core::Link<RefreshStrafeRunTokenTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::ActionAction (9 vftable slots, 0x2C bytes)
			class ActionAction : public fight::Action
			{
			public:
				// 0x101E7530
				ActionAction(ActionTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101E4C20
				virtual ~ActionAction();

				// vftable slot 5 (0x101E4460)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101E4470)
				virtual void Slot6();
				// vftable slot 7 (0x101E75E0)
				virtual bool Slot7(int arg, float value);

				core::Link<ActionTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::DrawDebugAction (9 vftable slots, 0x2C bytes)
			class DrawDebugAction : public fight::Action
			{
			public:
				// 0x101E76A0
				DrawDebugAction(DrawDebugTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101E4C70
				virtual ~DrawDebugAction();

				// vftable slot 5 (0x101E7740)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101E77A0)
				virtual void Slot6();
				// vftable slot 7 (0x101E7790)
				virtual bool Slot7(int arg, float value);

				core::Link<DrawDebugTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				int unknown2C;  // +0x2C
			};

			// RTTI: proto::fightitems::ai::TargetTokenBoostAction (9 vftable slots, 0x2C bytes)
			class TargetTokenBoostAction : public fight::Action
			{
			public:
				// 0x101E7A80
				TargetTokenBoostAction(TargetTokenBoostTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101E4D70
				virtual ~TargetTokenBoostAction();

				// vftable slot 5 (0x101E7B30)
				virtual bool Slot5(int arg, float value);

				core::Link<TargetTokenBoostTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
