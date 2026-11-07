// Fight items of the motion group: InsideJumpInBoundaryCondition, DistanceFromWaterSurfaceCondition, HeliBoundaryStatusCondition, FromWaterSetJumpToTrack, IgnoreWaterReactionTrack, JumpFromWaterTrack, OrientTowardsJumpInPositionTrack (unit 0x10144950 - 0x10146A60; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_BOUNDARY_H
#define PROTO_FIGHTITEMS_MOTION_BOUNDARY_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/ai/aihelpers.h"
#include "code/math/vector.h"
#include "code/proto/camera/cameramanager.h"

namespace proto
{
	// RTTI: proto::WorldTriggerCollisionCallback (0x3C bytes, the object 0x103B5040 makes): only the flag the water reaction actions set is known
	class WorldTriggerCollisionCallback
	{
	public:
		unsigned char unknown0[0x38];
		bool ignoreWaterReaction;  // +0x38
		unsigned char unknown39[3];
	};

	// 0x11264740
	extern WorldTriggerCollisionCallback* gWorldTriggerCollisionCallback;

	// RTTI: proto::ChargeMessage: the base of the messages to the charge of an object (message type 0x1c)
	class ChargeMessage : public engine::IntrusiveMessage
	{
	public:
		ChargeMessage(short newId, int newValue) : engine::IntrusiveMessage(0x1c, newId), unknownC(0.0f), value(newValue)
		{
		}
		virtual ~ChargeMessage()
		{
		}

		float unknownC;  // +0xC
		int value;  // +0x10
	};

	// RTTI: proto::ChargeEatMessage
	class ChargeEatMessage : public ChargeMessage
	{
	public:
		explicit ChargeEatMessage(int newValue) : ChargeMessage(1, newValue)
		{
		}
		virtual ~ChargeEatMessage()
		{
		}
	};

	// 0x10071800 (another unit): a copy of a transform matrix as the engine makes it, row by row
	struct TransformCopy
	{
		explicit TransformCopy(const math::Matrix& source);

		math::Matrix value;
	};

	// Where a jump ends: an object and the position it was at (guesses)
	struct JumpDestination
	{
		JumpDestination() : target(), position(math::kZeroVector)
		{
		}

		// 0x103C5C60 (another unit): takes the position of the object
		void Update();

		engine::GameObjectHandle target;  // +0
		math::Vector position;  // +4
	};

	// RTTI: proto::GetJumpDestinationMovementMessage: the object answers where it is going to jump
	struct GetJumpDestinationMovementMessage : public MovementMessage
	{
		// 0x1009DFA0
		GetJumpDestinationMovementMessage();
		virtual ~GetJumpDestinationMovementMessage()
		{
		}

		JumpDestination destination;  // +0xC
		bool found;  // +0x1C
	};

	// RTTI: proto::JumpToMovementMessage: the object is to jump to a destination
	struct JumpToMovementMessage : public MovementMessage
	{
		JumpToMovementMessage(const engine::GameObjectHandle& newTarget, const math::Vector& newPosition) : MovementMessage(0x27), target(newTarget), position(newPosition)
		{
		}
		virtual ~JumpToMovementMessage()
		{
		}

		engine::GameObjectHandle target;  // +0xC
		math::Vector position;  // +0x10
	};
}

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

			// The events a jump to a destination is made on (kinds 0x21010 - 0x21013): the destination is at +0x18
			struct JumpDestinationEvent : public TrackOwner
			{
				unsigned char unknown10[8];
				math::Vector position;  // +0x18
			};

			// The owner of a jump to a destination as the actions keep it: null when the owner is none or not one of those events
			inline core::IRefCount* AsJumpDestinationEvent(core::IRefCount* owner)
			{
				if (owner == 0)
				{
					return 0;
				}
				int ownerKind = (int)((TrackOwner*)owner)->kind;
				return (ownerKind >= 0x21010 && ownerKind < 0x21014) ? owner : 0;
			}

			// ---- actions begin
			// RTTI: proto::fightitems::motion::JumpFromWaterAction (9 vftable slots, 0x4C bytes)
			class JumpFromWaterAction : public fight::Action
			{
			public:
				// 0x1009F1B0
				JumpFromWaterAction(JumpFromWaterTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x1009E850
				virtual ~JumpFromWaterAction();

				// vftable slot 5 (0x1009F600)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x1009E890)
				virtual void Slot6();
				// vftable slot 7 (0x1009F8E0)
				virtual bool Slot7(int arg, float value);

				// 0x1009E060: the speed that rises a height in a time (names of the helpers are guesses)
				float GetInitialSpeed(float height, float time);
				// 0x1009E090: the gravity that makes a rise of a height take a time
				float GetGravity(float height, float time);
				// 0x1009F290: the forward speed for a distance in a flight time
				float GetForwardSpeed(float distance, float time);
				// 0x1009F2C0 (left to the engine: it loads the track's four limits before the speed): the turning velocity that goes with a forward speed
				float GetTurningVelocity(float forwardSpeed);
				// 0x1009F310: the distance in the xz plane between two points kept between the track's limits
				float GetForwardDistance(const math::Vector* from, const math::Vector* to);
				// 0x1009F390 (left to the engine: it keeps the track in another register): the flight time that goes with a forward distance
				float GetFlightTime(float distance);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<JumpFromWaterTrack> link;  // +0x20
				bool unknown2C;  // +0x2C
				float unknown30;  // +0x30
				choreo::Driver* driver;  // +0x34
				float unknown38;  // +0x38
				float unknown3C;  // +0x3C
				math::Vector unknown40;  // +0x40
			};

			// RTTI: proto::fightitems::motion::OrientTowardsJumpInPositionAction (9 vftable slots, 0x48 bytes)
			class OrientTowardsJumpInPositionAction : public fight::Action
			{
			public:
				// 0x1009ECB0
				OrientTowardsJumpInPositionAction(OrientTowardsJumpInPositionTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x1009E790
				virtual ~OrientTowardsJumpInPositionAction();

				// vftable slot 5 (0x1009ED60)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x1009E7C0)
				virtual void Slot6();
				// vftable slot 7 (0x1009EF70)
				virtual bool Slot7(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<OrientTowardsJumpInPositionTrack> link;  // +0x20
				choreo::RootDriver* driver;  // +0x2C
				bool unknown30;  // +0x30
				unsigned char unknown31[3];
				math::Vector destination;  // +0x34
				bool found;  // +0x40
				unsigned char unknown41[0x3];
				float unknown44;  // +0x44
			};

			// RTTI: proto::fightitems::motion::FromWaterSetJumpToAction (9 vftable slots, 0x30 bytes)
			class FromWaterSetJumpToAction : public fight::Action
			{
			public:
				// 0x1009F400
				FromWaterSetJumpToAction(FromWaterSetJumpToTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* newEvent);
				// 0x1009E920
				virtual ~FromWaterSetJumpToAction();

				// vftable slot 5 (0x1009E960)
				virtual bool Slot5(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<FromWaterSetJumpToTrack> link;  // +0x20
				core::IRefCount* event;  // +0x2C
			};

			// RTTI: proto::fightitems::motion::IgnoreWaterReactionAction (9 vftable slots, 0x28 bytes)
			class IgnoreWaterReactionAction : public fight::Action
			{
			public:
				// 0x1009F4C0
				explicit IgnoreWaterReactionAction(IgnoreWaterReactionTrack* newTrack);
				// 0x1009EB00
				virtual ~IgnoreWaterReactionAction();

				// vftable slot 5 (0x1009E0C0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x1009E0E0)
				virtual void Slot6();

				core::Link<IgnoreWaterReactionTrack> link;  // +0x1C
			};

			// ---- actions end
		}
	}
}

#endif
