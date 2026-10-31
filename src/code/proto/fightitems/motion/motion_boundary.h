// Fight items of the motion group: InsideJumpInBoundaryCondition, DistanceFromWaterSurfaceCondition, HeliBoundaryStatusCondition, FromWaterSetJumpToTrack, IgnoreWaterReactionTrack, JumpFromWaterTrack, OrientTowardsJumpInPositionTrack (unit 0x10144950 - 0x10146A60; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_BOUNDARY_H
#define PROTO_FIGHTITEMS_MOTION_BOUNDARY_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::InsideJumpInBoundaryCondition (10 vftable slots, 0x10 bytes)
			class InsideJumpInBoundaryCondition : public fight::Condition
			{
			public:
				// 0x10144D00
				InsideJumpInBoundaryCondition();
				virtual ~InsideJumpInBoundaryCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1009E560, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetInsideJumpInBoundary(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool insideJumpInBoundary;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gInsideJumpInBoundaryConditionProperties;
			fight::ConditionFactory* CreateInsideJumpInBoundaryConditionFactory(const char* name);
			void RegisterInsideJumpInBoundaryConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DistanceFromWaterSurfaceCondition (10 vftable slots, 0x14 bytes)
			class DistanceFromWaterSurfaceCondition : public fight::Condition
			{
			public:
				// 0x10144D60
				DistanceFromWaterSurfaceCondition();
				virtual ~DistanceFromWaterSurfaceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1009E6D0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetDistanceFromSurface(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distanceFromSurface;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gDistanceFromWaterSurfaceConditionProperties;
			fight::ConditionFactory* CreateDistanceFromWaterSurfaceConditionFactory(const char* name);
			void RegisterDistanceFromWaterSurfaceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::HeliBoundaryStatusCondition (10 vftable slots, 0x10 bytes)
			class HeliBoundaryStatusCondition : public fight::Condition
			{
			public:
				// 0x10144DD0
				HeliBoundaryStatusCondition();
				virtual ~HeliBoundaryStatusCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1009E620, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetHeliBoundaryStatus(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int heliBoundaryStatus;  // +0xC
			};

			extern fight::Property** gHeliBoundaryStatusConditionProperties;
			fight::ConditionFactory* CreateHeliBoundaryStatusConditionFactory(const char* name);
			void RegisterHeliBoundaryStatusConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::FromWaterSetJumpToTrack (16 vftable slots, 0x14 bytes)
			class FromWaterSetJumpToTrack : public fight::Track
			{
			public:
				// 0x10144E40
				FromWaterSetJumpToTrack();
				virtual ~FromWaterSetJumpToTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1009FD70, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gFromWaterSetJumpToTrackProperties;
			fight::TrackFactory* CreateFromWaterSetJumpToTrackFactory(const char* name);
			void RegisterFromWaterSetJumpToTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::IgnoreWaterReactionTrack (16 vftable slots, 0x18 bytes)
			class IgnoreWaterReactionTrack : public fight::Track
			{
			public:
				// 0x10144EC0
				IgnoreWaterReactionTrack();
				virtual ~IgnoreWaterReactionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1009FDF0, another unit)
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

			extern fight::Property** gIgnoreWaterReactionTrackProperties;
			fight::TrackFactory* CreateIgnoreWaterReactionTrackFactory(const char* name);
			void RegisterIgnoreWaterReactionTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::JumpFromWaterTrack (16 vftable slots, 0x50 bytes)
			class JumpFromWaterTrack : public fight::Track
			{
			public:
				// 0x10144F60
				JumpFromWaterTrack();
				virtual ~JumpFromWaterTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1009F5B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetFlightTimeMin(float newValue);
				bool SetFlightTimeMax(float newValue);
				bool SetUpOvershootDistance(float newValue);
				bool SetForwardDistanceMin(float newValue);
				bool SetForwardDistanceMax(float newValue);
				bool SetTurningVelocityMin(float newValue);
				bool SetTurningVelocityMinForwardSpeedCap(float newValue);
				bool SetTurningVelocityMax(float newValue);
				bool SetTurningVelocityMaxForwardSpeedCap(float newValue);
				bool SetMaxFallSpeed(float newValue);
				bool SetForwardVelocityScale(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float flightTimeMax;  // +0x18
					float flightTimeMin;  // +0x1C
					float forwardDistanceMax;  // +0x20
					float forwardDistanceMin;  // +0x24
					float forwardVelocityScale;  // +0x28
					float maxFallSpeed;  // +0x2C
					float timeBegin;  // +0x30
					float timeEnd;  // +0x34
					float turningVelocityMax;  // +0x38
					float turningVelocityMaxForwardSpeedCap;  // +0x3C
					float turningVelocityMin;  // +0x40
					float turningVelocityMinForwardSpeedCap;  // +0x44
					float upOvershootDistance;  // +0x48
					int priority;  // +0x4C
			};

			extern fight::Property** gJumpFromWaterTrackProperties;
			fight::TrackFactory* CreateJumpFromWaterTrackFactory(const char* name);
			void RegisterJumpFromWaterTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::OrientTowardsJumpInPositionTrack (16 vftable slots, 0x30 bytes)
			class OrientTowardsJumpInPositionTrack : public fight::Track
			{
			public:
				// 0x10145060
				OrientTowardsJumpInPositionTrack();
				virtual ~OrientTowardsJumpInPositionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1009F560, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTurningVelocity(float newValue);
				bool SetOrientationCutOffDistance(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);
				bool SetUseJumpDestination(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float orientationCutOffDistance;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
					float turningVelocity;  // +0x24
					int priority;  // +0x28
					bool useJumpDestination;  // +0x2C
					unsigned char unknown2D[0x3];
			};

			extern fight::Property** gOrientTowardsJumpInPositionTrackProperties;
			fight::TrackFactory* CreateOrientTowardsJumpInPositionTrackFactory(const char* name);
			void RegisterOrientTowardsJumpInPositionTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
