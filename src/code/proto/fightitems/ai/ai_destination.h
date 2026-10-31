// Fight items of the ai group: InReservedAreaCondition, DestinationDistanceCondition, GroundDistanceCondition, DestinationTargetOrientationCondition, InsideReservedVolumeCondition, InBlastAreaCondition, StuckCondition, HaveDestinationCondition, InHotZoneCondition, DestinationHaveArrivedCondition, SetAvoidanceGapAnywhereTrack, SpeedTrack, DestinationJumpToTrack, DestinationFlyToTrack, SetIntersectionPropertiesTrack, DisableStayOnNavmeshTrack, TargetGoToTrack, ForceMotionTrack, ForceRecalculatePathTrack, ReserveVolumeTrack, DestinationSetDeadBodyTrack, StopTrack, TempSpeedTrack, SetBrakeDistanceTrack, AimTrack, DestinationGoToTrack (unit 0x1023BC30 - 0x102432A0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_DESTINATION_H
#define PROTO_FIGHTITEMS_AI_AI_DESTINATION_H

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
			// RTTI: proto::fightitems::ai::InReservedAreaCondition (10 vftable slots, 0x10 bytes)
			class InReservedAreaCondition : public fight::Condition
			{
			public:
				// 0x1023C5C0
				InReservedAreaCondition();
				virtual ~InReservedAreaCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10200E30, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetUseDestination(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool useDestination;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gInReservedAreaConditionProperties;
			fight::ConditionFactory* CreateInReservedAreaConditionFactory(const char* name);
			void RegisterInReservedAreaConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DestinationDistanceCondition (10 vftable slots, 0x1C bytes)
			class DestinationDistanceCondition : public fight::Condition
			{
			public:
				// 0x1023C620
				DestinationDistanceCondition();
				virtual ~DestinationDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x102004F0, another unit)
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

			extern fight::Property** gDestinationDistanceConditionProperties;
			fight::ConditionFactory* CreateDestinationDistanceConditionFactory(const char* name);
			void RegisterDestinationDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::GroundDistanceCondition (10 vftable slots, 0x1C bytes)
			class GroundDistanceCondition : public fight::Condition
			{
			public:
				// 0x1023C6A0
				GroundDistanceCondition();
				virtual ~GroundDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10204550, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);
				bool SetRadius(float newValue);
				bool SetGroundUnit(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distance;  // +0xC
					float radius;  // +0x10
					int compare;  // +0x14
					bool groundUnit;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gGroundDistanceConditionProperties;
			fight::ConditionFactory* CreateGroundDistanceConditionFactory(const char* name);
			void RegisterGroundDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DestinationTargetOrientationCondition (10 vftable slots, 0x18 bytes)
			class DestinationTargetOrientationCondition : public fight::Condition
			{
			public:
				// 0x1023C720
				DestinationTargetOrientationCondition();
				virtual ~DestinationTargetOrientationCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x102006E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompareTime(int newValue);
				bool SetAngle(float newValue);
				bool SetSigned(bool newValue);
				bool SetUseParams(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float angle;  // +0xC
					int compareTime;  // +0x10
					bool signedValue;  // +0x14
					bool useParams;  // +0x15
					unsigned char unknown16[0x2];
			};

			extern fight::Property** gDestinationTargetOrientationConditionProperties;
			fight::ConditionFactory* CreateDestinationTargetOrientationConditionFactory(const char* name);
			void RegisterDestinationTargetOrientationConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::InsideReservedVolumeCondition (10 vftable slots, 0x14 bytes)
			class InsideReservedVolumeCondition : public fight::Condition
			{
			public:
				// 0x1023C7A0
				InsideReservedVolumeCondition();
				virtual ~InsideReservedVolumeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10200FC0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetInside(bool newValue);
				bool SetRadius(float newValue);
				bool SetDestination(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float radius;  // +0xC
					bool destination;  // +0x10
					bool inside;  // +0x11
					unsigned char unknown12[0x2];
			};

			extern fight::Property** gInsideReservedVolumeConditionProperties;
			fight::ConditionFactory* CreateInsideReservedVolumeConditionFactory(const char* name);
			void RegisterInsideReservedVolumeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::InBlastAreaCondition (10 vftable slots, 0x10 bytes)
			class InBlastAreaCondition : public fight::Condition
			{
			public:
				// 0x1023C820
				InBlastAreaCondition();
				virtual ~InBlastAreaCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10200CA0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetUseDestination(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool useDestination;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gInBlastAreaConditionProperties;
			fight::ConditionFactory* CreateInBlastAreaConditionFactory(const char* name);
			void RegisterInBlastAreaConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::StuckCondition (10 vftable slots, 0x14 bytes)
			class StuckCondition : public fight::Condition
			{
			public:
				// 0x1023C880
				StuckCondition();
				virtual ~StuckCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10200B20, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetStuck(bool newValue);
				bool SetTimeStuck(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeStuck;  // +0xC
					bool stuck;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gStuckConditionProperties;
			fight::ConditionFactory* CreateStuckConditionFactory(const char* name);
			void RegisterStuckConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::HaveDestinationCondition (10 vftable slots, 0xC bytes)
			class HaveDestinationCondition : public fight::Condition
			{
			public:
				// 0x1023C950
				HaveDestinationCondition();
				virtual ~HaveDestinationCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10200A20, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gHaveDestinationConditionProperties;
			fight::ConditionFactory* CreateHaveDestinationConditionFactory(const char* name);
			void RegisterHaveDestinationConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::InHotZoneCondition (10 vftable slots, 0x10 bytes)
			class InHotZoneCondition : public fight::Condition
			{
			public:
				// 0x1023C9B0
				InHotZoneCondition();
				virtual ~InHotZoneCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10200BE0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIn(bool newValue);
				bool SetRequireStayOnGround(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool in;  // +0xC
					bool requireStayOnGround;  // +0xD
					unsigned char unknownE[0x2];
			};

			extern fight::Property** gInHotZoneConditionProperties;
			fight::ConditionFactory* CreateInHotZoneConditionFactory(const char* name);
			void RegisterInHotZoneConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DestinationHaveArrivedCondition (10 vftable slots, 0xC bytes)
			class DestinationHaveArrivedCondition : public fight::Condition
			{
			public:
				// 0x1023CA80
				DestinationHaveArrivedCondition();
				virtual ~DestinationHaveArrivedCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10200480, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gDestinationHaveArrivedConditionProperties;
			fight::ConditionFactory* CreateDestinationHaveArrivedConditionFactory(const char* name);
			void RegisterDestinationHaveArrivedConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::SetAvoidanceGapAnywhereTrack (16 vftable slots, 0x1C bytes)
			class SetAvoidanceGapAnywhereTrack : public fight::Track
			{
			public:
				// 0x1023CAE0
				SetAvoidanceGapAnywhereTrack();
				virtual ~SetAvoidanceGapAnywhereTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x102044B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetEnable(bool newValue);
				bool SetTemporary(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool enable;  // +0x18
					bool temporary;  // +0x19
					unsigned char unknown1A[0x2];
			};

			extern fight::Property** gSetAvoidanceGapAnywhereTrackProperties;
			fight::TrackFactory* CreateSetAvoidanceGapAnywhereTrackFactory(const char* name);
			void RegisterSetAvoidanceGapAnywhereTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::SpeedTrack (16 vftable slots, 0x20 bytes)
			class SpeedTrack : public fight::Track
			{
			public:
				// 0x1023CB90
				SpeedTrack();
				virtual ~SpeedTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10204140, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetSpeed(float newValue);
				bool SetSprint(bool newValue);
				bool SetUseMaxSpeed(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float speed;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
					bool sprint;  // +0x1C
					bool useMaxSpeed;  // +0x1D
					unsigned char unknown1E[0x2];
			};

			extern fight::Property** gSpeedTrackProperties;
			fight::TrackFactory* CreateSpeedTrackFactory(const char* name);
			void RegisterSpeedTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DestinationJumpToTrack (16 vftable slots, 0x1C bytes)
			class DestinationJumpToTrack : public fight::Track
			{
			public:
				// 0x1023CC40
				DestinationJumpToTrack();
				virtual ~DestinationJumpToTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10203CA0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetReverseFacing(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool reverseFacing;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gDestinationJumpToTrackProperties;
			fight::TrackFactory* CreateDestinationJumpToTrackFactory(const char* name);
			void RegisterDestinationJumpToTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DestinationFlyToTrack (16 vftable slots, 0x40 bytes)
			class DestinationFlyToTrack : public fight::Track
			{
			public:
				// 0x1023CCE0
				DestinationFlyToTrack();
				virtual ~DestinationFlyToTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10203C20, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTolerance(float newValue);
				bool SetBrake(bool newValue);
				bool SetIgnoreRestrictions(bool newValue);
				bool SetFreeArea(float newValue);
				bool SetMinHeight(float newValue);
				bool SetMaxSpeed(float newValue);
				bool SetSpeedFactor(const math::Vector& newValue);
				bool SetTurningFactorA(int newValue);
				bool SetTurningFactorB(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector speedFactor;  // +0x10
					float freeArea;  // +0x1C
					float maxSpeed;  // +0x20
					float minHeight;  // +0x24
					float timeBegin;  // +0x28
					float timeEnd;  // +0x2C
					float tolerance;  // +0x30
					int turningFactorA;  // +0x34
					int turningFactorB;  // +0x38
					bool brake;  // +0x3C
					bool ignoreRestrictions;  // +0x3D
					unsigned char unknown3E[0x2];
			};

			extern fight::Property** gDestinationFlyToTrackProperties;
			fight::TrackFactory* CreateDestinationFlyToTrackFactory(const char* name);
			void RegisterDestinationFlyToTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::SetIntersectionPropertiesTrack (16 vftable slots, 0x28 bytes)
			class SetIntersectionPropertiesTrack : public fight::Track
			{
			public:
				// 0x1023D850
				SetIntersectionPropertiesTrack();
				virtual ~SetIntersectionPropertiesTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10204460, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetIntersectionProperties(const fight::Name& newValue);
				bool SetTemporary(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name intersectionProperties;  // +0x10
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
					bool temporary;  // +0x20
					unsigned char unknown21[0x7];
			};

			extern fight::Property** gSetIntersectionPropertiesTrackProperties;
			fight::TrackFactory* CreateSetIntersectionPropertiesTrackFactory(const char* name);
			void RegisterSetIntersectionPropertiesTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DisableStayOnNavmeshTrack (16 vftable slots, 0x18 bytes)
			class DisableStayOnNavmeshTrack : public fight::Track
			{
			public:
				// 0x1023CE10
				DisableStayOnNavmeshTrack();
				virtual ~DisableStayOnNavmeshTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10204500, another unit)
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

			extern fight::Property** gDisableStayOnNavmeshTrackProperties;
			fight::TrackFactory* CreateDisableStayOnNavmeshTrackFactory(const char* name);
			void RegisterDisableStayOnNavmeshTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TargetGoToTrack (16 vftable slots, 0x38 bytes)
			class TargetGoToTrack : public fight::Track
			{
			public:
				// 0x1023CEB0
				TargetGoToTrack();
				virtual ~TargetGoToTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10203D20, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetWhere(int newValue);
				bool SetTolerance(float newValue);
				bool SetToleranceRePathfind(float newValue);
				bool SetMinTimeBetweenPathfind(float newValue);
				bool SetUseRandomOvershoot(bool newValue);
				bool SetRandomOvershootLowerBound(float newValue);
				bool SetRandomOvershootUpperBound(float newValue);
				bool SetBrake(bool newValue);
				bool SetIgnoreRestrictions(bool newValue);
				bool SetStayOnGround(bool newValue);
				bool SetProjectPositionToGround(bool newValue);
				bool SetTargetClimbing(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float minTimeBetweenPathfind;  // +0x10
					float randomOvershootLowerBound;  // +0x14
					float randomOvershootUpperBound;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
					float tolerance;  // +0x24
					float toleranceRePathfind;  // +0x28
					int where;  // +0x2C
					bool brake;  // +0x30
					bool ignoreRestrictions;  // +0x31
					bool projectPositionToGround;  // +0x32
					bool stayOnGround;  // +0x33
					bool targetClimbing;  // +0x34
					bool useRandomOvershoot;  // +0x35
					unsigned char unknown36[0x2];
			};

			extern fight::Property** gTargetGoToTrackProperties;
			fight::TrackFactory* CreateTargetGoToTrackFactory(const char* name);
			void RegisterTargetGoToTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ForceMotionTrack (16 vftable slots, 0x2C bytes)
			class ForceMotionTrack : public fight::Track
			{
			public:
				// 0x1023CFA0
				ForceMotionTrack();
				virtual ~ForceMotionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10204360, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMotion(const math::Vector& newValue);
				bool SetLocal(bool newValue);
				bool SetAccelerationFactor(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector motion;  // +0x10
					float accelerationFactor;  // +0x1C
					float timeBegin;  // +0x20
					float timeEnd;  // +0x24
					bool local;  // +0x28
					unsigned char unknown29[0x3];
			};

			extern fight::Property** gForceMotionTrackProperties;
			fight::TrackFactory* CreateForceMotionTrackFactory(const char* name);
			void RegisterForceMotionTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ForceRecalculatePathTrack (16 vftable slots, 0x14 bytes)
			class ForceRecalculatePathTrack : public fight::Track
			{
			public:
				// 0x1023D070
				ForceRecalculatePathTrack();
				virtual ~ForceRecalculatePathTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10204310, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gForceRecalculatePathTrackProperties;
			fight::TrackFactory* CreateForceRecalculatePathTrackFactory(const char* name);
			void RegisterForceRecalculatePathTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ReserveVolumeTrack (16 vftable slots, 0x20 bytes)
			class ReserveVolumeTrack : public fight::Track
			{
			public:
				// 0x1023D100
				ReserveVolumeTrack();
				virtual ~ReserveVolumeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x102041E0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetRadius(float newValue);
				bool SetStrafeRun(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float radius;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
					bool strafeRun;  // +0x1C
					unsigned char unknown1D[0x3];
			};

			extern fight::Property** gReserveVolumeTrackProperties;
			fight::TrackFactory* CreateReserveVolumeTrackFactory(const char* name);
			void RegisterReserveVolumeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DestinationSetDeadBodyTrack (16 vftable slots, 0x3C bytes)
			class DestinationSetDeadBodyTrack : public fight::Track
			{
			public:
				// 0x1023D1B0
				DestinationSetDeadBodyTrack();
				virtual ~DestinationSetDeadBodyTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10204400, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				fight::BranchHolder* SetBranch();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					fight::ConditionList conditions;  // +0x34
					int priority;  // +0x38
			};

			extern fight::Property** gDestinationSetDeadBodyTrackProperties;
			fight::TrackFactory* CreateDestinationSetDeadBodyTrackFactory(const char* name);
			void RegisterDestinationSetDeadBodyTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::StopTrack (16 vftable slots, 0x18 bytes)
			class StopTrack : public fight::Track
			{
			public:
				// 0x1023D270
				StopTrack();
				virtual ~StopTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x102040F0, another unit)
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

			extern fight::Property** gStopTrackProperties;
			fight::TrackFactory* CreateStopTrackFactory(const char* name);
			void RegisterStopTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::TempSpeedTrack (16 vftable slots, 0x20 bytes)
			class TempSpeedTrack : public fight::Track
			{
			public:
				// 0x1023D300
				TempSpeedTrack();
				virtual ~TempSpeedTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10204190, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetSpeed(float newValue);
				bool SetSprint(bool newValue);
				bool SetUseMaxSpeed(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float speed;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
					bool sprint;  // +0x1C
					bool useMaxSpeed;  // +0x1D
					unsigned char unknown1E[0x2];
			};

			extern fight::Property** gTempSpeedTrackProperties;
			fight::TrackFactory* CreateTempSpeedTrackFactory(const char* name);
			void RegisterTempSpeedTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::SetBrakeDistanceTrack (16 vftable slots, 0x1C bytes)
			class SetBrakeDistanceTrack : public fight::Track
			{
			public:
				// 0x1023D3B0
				SetBrakeDistanceTrack();
				virtual ~SetBrakeDistanceTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x102043B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetBrakeDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float brakeDistance;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
			};

			extern fight::Property** gSetBrakeDistanceTrackProperties;
			fight::TrackFactory* CreateSetBrakeDistanceTrackFactory(const char* name);
			void RegisterSetBrakeDistanceTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::AimTrack (16 vftable slots, 0x2C bytes)
			class AimTrack : public fight::Track
			{
			public:
				// 0x1023D450
				AimTrack();
				virtual ~AimTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x102040A0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetWhere(int newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetForceWorldAngles(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector offset;  // +0x10
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
					int where;  // +0x24
					bool forceWorldAngles;  // +0x28
					unsigned char unknown29[0x3];
			};

			extern fight::Property** gAimTrackProperties;
			fight::TrackFactory* CreateAimTrackFactory(const char* name);
			void RegisterAimTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DestinationGoToTrack (16 vftable slots, 0x20 bytes)
			class DestinationGoToTrack : public fight::Track
			{
			public:
				// 0x1023D510
				DestinationGoToTrack();
				virtual ~DestinationGoToTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10203BA0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTolerance(float newValue);
				bool SetBrake(bool newValue);
				bool SetIgnoreRestrictions(bool newValue);
				bool SetStayOnGround(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					float tolerance;  // +0x18
					bool brake;  // +0x1C
					bool ignoreRestrictions;  // +0x1D
					bool stayOnGround;  // +0x1E
					unsigned char unknown1F[0x1];
			};

			extern fight::Property** gDestinationGoToTrackProperties;
			fight::TrackFactory* CreateDestinationGoToTrackFactory(const char* name);
			void RegisterDestinationGoToTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::SetAvoidanceGapAnywhereAction (9 vftable slots, 0x2C bytes)
			class SetAvoidanceGapAnywhereAction : public fight::Action
			{
			public:
				// 0x102037B0
				SetAvoidanceGapAnywhereAction(SetAvoidanceGapAnywhereTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10200400
				virtual ~SetAvoidanceGapAnywhereAction();

				// vftable slot 5 (0x10203860)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10203950)
				virtual void Slot6();

				core::Link<SetAvoidanceGapAnywhereTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				unsigned char unknown2C[0x4];
			};

			// RTTI: proto::fightitems::ai::SpeedAction (9 vftable slots, 0x2C bytes)
			class SpeedAction : public fight::Action
			{
			public:
				// 0x102025A0
				SpeedAction(SpeedTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101FFED0
				virtual ~SpeedAction();

				// vftable slot 5 (0x101FED50)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101FED60)
				virtual void Slot6();
				// vftable slot 7 (0x10202650)
				virtual bool Slot7(int arg, float value);

				core::Link<SpeedTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::DisableStayOnNavmeshAction (9 vftable slots, 0x2C bytes)
			class DisableStayOnNavmeshAction : public fight::Action
			{
			public:
				// 0x102039E0
				DisableStayOnNavmeshAction(DisableStayOnNavmeshTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10200450
				virtual ~DisableStayOnNavmeshAction();

				// vftable slot 5 (0x10203A90)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10203B20)
				virtual void Slot6();

				core::Link<DisableStayOnNavmeshTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::ForceMotionAction (9 vftable slots, 0x2C bytes)
			class ForceMotionAction : public fight::Action
			{
			public:
				// 0x10202ED0
				ForceMotionAction(ForceMotionTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x102001C0
				virtual ~ForceMotionAction();

				// vftable slot 5 (0x10202F80)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x102001F0)
				virtual void Slot6();
				// vftable slot 7 (0x10203040)
				virtual bool Slot7(int arg, float value);

				core::Link<ForceMotionTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::ForceRecalculatePathAction (9 vftable slots, 0x2C bytes)
			class ForceRecalculatePathAction : public fight::Action
			{
			public:
				// 0x10202E20
				ForceRecalculatePathAction(ForceRecalculatePathTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10200100
				virtual ~ForceRecalculatePathAction();

				// vftable slot 5 (0x10200130)
				virtual bool Slot5(int arg, float value);

				core::Link<ForceRecalculatePathTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::StopAction (9 vftable slots, 0x2C bytes)
			class StopAction : public fight::Action
			{
			public:
				// 0x102024F0
				StopAction(StopTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101FFE30
				virtual ~StopAction();

				// vftable slot 5 (0x101FED30)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101FED40)
				virtual void Slot6();
				// vftable slot 7 (0x101FFE60)
				virtual bool Slot7(int arg, float value);

				core::Link<StopTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::TempSpeedAction (9 vftable slots, 0x2C bytes)
			class TempSpeedAction : public fight::Action
			{
			public:
				// 0x10202730
				TempSpeedAction(TempSpeedTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101FFF20
				virtual ~TempSpeedAction();

				// vftable slot 5 (0x102027E0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10202950)
				virtual void Slot6();
				// vftable slot 7 (0x102028F0)
				virtual bool Slot7(int arg, float value);

				core::Link<TempSpeedTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				unsigned char unknown2C[0x4];
			};

			// RTTI: proto::fightitems::ai::SetBrakeDistanceAction (9 vftable slots, 0x2C bytes)
			class SetBrakeDistanceAction : public fight::Action
			{
			public:
				// 0x10203110
				SetBrakeDistanceAction(SetBrakeDistanceTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10200280
				virtual ~SetBrakeDistanceAction();

				// vftable slot 5 (0x102031C0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x102002B0)
				virtual void Slot6();

				core::Link<SetBrakeDistanceTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				float unknown2C;  // +0x2C
			};

			// RTTI: proto::fightitems::ai::AimAction (9 vftable slots, 0x2C bytes)
			class AimAction : public fight::Action
			{
			public:
				// 0x102022F0
				AimAction(AimTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101FFDE0
				virtual ~AimAction();

				// vftable slot 5 (0x102023A0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101FED20)
				virtual void Slot6();
				// vftable slot 7 (0x102023F0)
				virtual bool Slot7(int arg, float value);

				core::Link<AimTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
