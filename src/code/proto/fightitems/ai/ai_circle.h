// Fight items of the ai group: CirclePatrolTrack, IntersectionCirclePatrolTrack, CircleStrafeTrack (unit 0x1021CD90 - 0x1021E550; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_CIRCLE_H
#define PROTO_FIGHTITEMS_AI_AI_CIRCLE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::CirclePatrolTrack (16 vftable slots, 0x44 bytes)
			class CirclePatrolTrack : public fight::Track
			{
			public:
				// 0x1021D220
				CirclePatrolTrack();
				virtual ~CirclePatrolTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E1CA0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetHeightMin(float newValue);
				bool SetHeightMax(float newValue);
				bool SetRadius(float newValue);
				bool SetFreeRadius(float newValue);
				bool SetAvoidRadius(float newValue);
				bool SetAvoidCost(float newValue);
				bool SetTries(int newValue);
				bool SetMaxSpeed(float newValue);
				bool SetMinDistance(float newValue);
				bool SetMinAngle(float newValue);
				bool SetMaxPathHeightDiffCurrent(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float avoidCost;  // +0x10
					float avoidRadius;  // +0x14
					float freeRadius;  // +0x18
					float heightMax;  // +0x1C
					float heightMin;  // +0x20
					float maxPathHeightDiffCurrent;  // +0x24
					float maxSpeed;  // +0x28
					float minAngle;  // +0x2C
					float minDistance;  // +0x30
					float radius;  // +0x34
					float timeBegin;  // +0x38
					float timeEnd;  // +0x3C
					int tries;  // +0x40
			};

			extern fight::Property** gCirclePatrolTrackProperties;
			fight::TrackFactory* CreateCirclePatrolTrackFactory(const char* name);
			void RegisterCirclePatrolTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::IntersectionCirclePatrolTrack (16 vftable slots, 0x30 bytes)
			class IntersectionCirclePatrolTrack : public fight::Track
			{
			public:
				// 0x1021D340
				IntersectionCirclePatrolTrack();
				virtual ~IntersectionCirclePatrolTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E2140, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetHeightMin(float newValue);
				bool SetHeightMinFromTarget(float newValue);
				bool SetMinDistance(float newValue);
				bool SetRadius(float newValue);
				bool SetFreeRadiusPath(float newValue);
				bool SetFreeRadius(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float freeRadius;  // +0x10
					float freeRadiusPath;  // +0x14
					float heightMin;  // +0x18
					float heightMinFromTarget;  // +0x1C
					float minDistance;  // +0x20
					float radius;  // +0x24
					float timeBegin;  // +0x28
					float timeEnd;  // +0x2C
			};

			extern fight::Property** gIntersectionCirclePatrolTrackProperties;
			fight::TrackFactory* CreateIntersectionCirclePatrolTrackFactory(const char* name);
			void RegisterIntersectionCirclePatrolTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::CircleStrafeTrack (16 vftable slots, 0x4C bytes)
			class CircleStrafeTrack : public fight::Track
			{
			public:
				// 0x1021D420
				CircleStrafeTrack();
				virtual ~CircleStrafeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E1760, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetDistanceMin(float newValue);
				bool SetDistanceMax(float newValue);
				bool SetHeightMin(float newValue);
				bool SetHeightMax(float newValue);
				bool SetSafeHeight(float newValue);
				bool SetMinSpeed(float newValue);
				bool SetMaxSpeed(float newValue);
				bool SetShootingDistance(float newValue);
				bool SetUseMissiles(bool newValue);
				bool SetMinFireTime(float newValue);
				bool SetMaxFireTime(float newValue);
				bool SetMinWaitTime(float newValue);
				bool SetMaxWaitTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distanceMax;  // +0x10
					float distanceMin;  // +0x14
					float heightMax;  // +0x18
					float heightMin;  // +0x1C
					float maxFireTime;  // +0x20
					float maxSpeed;  // +0x24
					float maxWaitTime;  // +0x28
					float minFireTime;  // +0x2C
					float minSpeed;  // +0x30
					float minWaitTime;  // +0x34
					float safeHeight;  // +0x38
					float shootingDistance;  // +0x3C
					float timeBegin;  // +0x40
					float timeEnd;  // +0x44
					bool useMissiles;  // +0x48
					unsigned char unknown49[0x3];
			};

			extern fight::Property** gCircleStrafeTrackProperties;
			fight::TrackFactory* CreateCircleStrafeTrackFactory(const char* name);
			void RegisterCircleStrafeTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
