// Fight items of the motion group: OrientationDesiredCondition, OrientTrack, WorldOrientTrack (unit 0x10198800 - 0x101998F0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_ORIENT_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_ORIENT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::OrientationDesiredCondition (10 vftable slots, 0x14 bytes)
			class OrientationDesiredCondition : public fight::Condition
			{
			public:
				// 0x10198A30
				OrientationDesiredCondition();
				virtual ~OrientationDesiredCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100FF2D0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetAngle(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float angle;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gOrientationDesiredConditionProperties;
			fight::ConditionFactory* CreateOrientationDesiredConditionFactory(const char* name);
			void RegisterOrientationDesiredConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::OrientTrack (16 vftable slots, 0x34 bytes)
			class OrientTrack : public fight::Track
			{
			public:
				// 0x10198AA0
				OrientTrack();
				virtual ~OrientTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100FFF70, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTurningVelocity(float newValue);
				bool SetTurningAcceleration(float newValue);
				bool SetOffset(float newValue);
				bool SetFixedInput(bool newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float offset;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
					float turningAcceleration;  // +0x24
					float turningVelocity;  // +0x28
					int priority;  // +0x2C
					bool fixedInput;  // +0x30
					unsigned char unknown31[0x3];
			};

			extern fight::Property** gOrientTrackProperties;
			fight::TrackFactory* CreateOrientTrackFactory(const char* name);
			void RegisterOrientTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::WorldOrientTrack (16 vftable slots, 0x2C bytes)
			class WorldOrientTrack : public fight::Track
			{
			public:
				// 0x10198B70
				WorldOrientTrack();
				virtual ~WorldOrientTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100FFFC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetYaw(float newValue);
				bool SetTurningVelocity(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
					float turningVelocity;  // +0x20
					float yaw;  // +0x24
					int priority;  // +0x28
			};

			extern fight::Property** gWorldOrientTrackProperties;
			fight::TrackFactory* CreateWorldOrientTrackFactory(const char* name);
			void RegisterWorldOrientTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
