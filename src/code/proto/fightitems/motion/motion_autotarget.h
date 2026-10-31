// Fight items of the motion group: AutoTargetTrack, AutoTargetClearTrack, AutoTargetPositionTrack, FlyingAutoTargetTrack, PedestrianAutoTargetTrack, AutoTargetPlayerTrack (unit 0x10140FC0 - 0x10143E60; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_AUTOTARGET_H
#define PROTO_FIGHTITEMS_MOTION_AUTOTARGET_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::AutoTargetTrack (16 vftable slots, 0x54 bytes)
			class AutoTargetTrack : public fight::Track
			{
			public:
				// 0x10141600
				AutoTargetTrack();
				virtual ~AutoTargetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1009C940, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float value);
				bool SetTimeEnd(float value);
				bool SetTurningVelocity(float value);
				bool SetUseInput(bool value);
				bool SetUseCamera(bool value);
				bool SetDirection(const math::Vector& value);
				bool SetArc(float value);
				bool SetMaxDistance(float value);
				bool SetCheckArc(bool value);
				bool SetCheckDistance(bool value);
				bool SetOrientOffsetFromTarget(float value);
				bool SetTargetFilter(int value);
				bool SetTargetOverrides(int value);
				bool SetMinPriorityTargetClass(int value);
				bool SetMaxPriorityTargetClass(int value);
				bool SetPriority(int value);
				bool SetBlendInTime(float value);
				bool SetBlendOutTime(float value);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector direction;  // +0x10
					float arc;  // +0x1C
					float blendInTime;  // +0x20
					float blendOutTime;  // +0x24
					float maxDistance;  // +0x28
					float orientOffsetFromTarget;  // +0x2C
					float timeBegin;  // +0x30
					float timeEnd;  // +0x34
					float turningVelocity;  // +0x38
					int maxPriorityTargetClass;  // +0x3C
					int minPriorityTargetClass;  // +0x40
					int priority;  // +0x44
					int targetFilter;  // +0x48
					int targetOverrides;  // +0x4C
					bool checkArc;  // +0x50
					bool checkDistance;  // +0x51
					bool useCamera;  // +0x52
					bool useInput;  // +0x53
			};

			extern fight::Property** gAutoTargetTrackProperties;
			fight::TrackFactory* CreateAutoTargetTrackFactory(const char* name);
			void RegisterAutoTargetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::AutoTargetClearTrack (16 vftable slots, 0x14 bytes)
			class AutoTargetClearTrack : public fight::Track
			{
			public:
				// 0x10141720
				AutoTargetClearTrack();
				virtual ~AutoTargetClearTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10099130, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float value);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gAutoTargetClearTrackProperties;
			fight::TrackFactory* CreateAutoTargetClearTrackFactory(const char* name);
			void RegisterAutoTargetClearTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::AutoTargetPositionTrack (16 vftable slots, 0x34 bytes)
			class AutoTargetPositionTrack : public fight::Track
			{
			public:
				// 0x101417B0
				AutoTargetPositionTrack();
				virtual ~AutoTargetPositionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1009C990, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float value);
				bool SetTimeEnd(float value);
				bool SetOffset(const math::Vector& value);
				bool SetVelocity(float value);
				bool SetPriority(int value);
				bool SetBlendInTime(float value);
				bool SetBlendOutTime(float value);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector offset;  // +0x10
					float blendInTime;  // +0x1C
					float blendOutTime;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
					float velocity;  // +0x2C
					int priority;  // +0x30
			};

			extern fight::Property** gAutoTargetPositionTrackProperties;
			fight::TrackFactory* CreateAutoTargetPositionTrackFactory(const char* name);
			void RegisterAutoTargetPositionTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::FlyingAutoTargetTrack (16 vftable slots, 0x5C bytes)
			class FlyingAutoTargetTrack : public fight::Track
			{
			public:
				// 0x10141890
				FlyingAutoTargetTrack();
				virtual ~FlyingAutoTargetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1009CBF0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float value);
				bool SetTimeEnd(float value);
				bool SetVelocity(float value);
				bool SetTurningVelocity(float value);
				bool SetOffset(const math::Vector& value);
				bool SetArc(float value);
				bool SetMaxDistance(float value);
				bool SetCheckArc(bool value);
				bool SetCheckDistance(bool value);
				bool SetTargetFilter(int value);
				bool SetStickToTarget(bool value);
				bool SetUseExistingAutoTarget(bool value);
				bool SetUseReactionHitEvent(bool value);
				bool SetCharacterHeight(float value);
				bool SetCharacterWidth(float value);
				bool SetMinPriorityTargetClass(int value);
				bool SetMaxPriorityTargetClass(int value);
				bool SetPriority(int value);
				bool SetBlendInTime(float value);
				bool SetBlendOutTime(float value);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector offset;  // +0x10
					float arc;  // +0x1C
					float blendInTime;  // +0x20
					float blendOutTime;  // +0x24
					float characterHeight;  // +0x28
					float characterWidth;  // +0x2C
					float maxDistance;  // +0x30
					float timeBegin;  // +0x34
					float timeEnd;  // +0x38
					float turningVelocity;  // +0x3C
					float velocity;  // +0x40
					int maxPriorityTargetClass;  // +0x44
					int minPriorityTargetClass;  // +0x48
					int priority;  // +0x4C
					int targetFilter;  // +0x50
					bool checkArc;  // +0x54
					bool checkDistance;  // +0x55
					bool stickToTarget;  // +0x56
					bool useExistingAutoTarget;  // +0x57
					bool useReactionHitEvent;  // +0x58
					unsigned char unknown59[0x3];
			};

			extern fight::Property** gFlyingAutoTargetTrackProperties;
			fight::TrackFactory* CreateFlyingAutoTargetTrackFactory(const char* name);
			void RegisterFlyingAutoTargetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::PedestrianAutoTargetTrack (16 vftable slots, 0x2C bytes)
			class PedestrianAutoTargetTrack : public fight::Track
			{
			public:
				// 0x101419D0
				PedestrianAutoTargetTrack();
				virtual ~PedestrianAutoTargetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1009CC30, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float value);
				bool SetTimeEnd(float value);
				bool SetTurningVelocity(float value);
				bool SetOrientOffsetFromTarget(float value);
				bool SetPriority(int value);
				bool SetBlendInTime(float value);
				bool SetBlendOutTime(float value);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float orientOffsetFromTarget;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
					float turningVelocity;  // +0x24
					int priority;  // +0x28
			};

			extern fight::Property** gPedestrianAutoTargetTrackProperties;
			fight::TrackFactory* CreatePedestrianAutoTargetTrackFactory(const char* name);
			void RegisterPedestrianAutoTargetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::AutoTargetPlayerTrack (16 vftable slots, 0x24 bytes)
			class AutoTargetPlayerTrack : public fight::Track
			{
			public:
				// 0x10141A90
				AutoTargetPlayerTrack();
				virtual ~AutoTargetPlayerTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1009C9E0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float value);
				bool SetTimeEnd(float value);
				bool SetSetTarget(bool value);
				bool SetArc(float value);
				bool SetMaxDistance(float value);
				bool SetKeepChecking(bool value);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float arc;  // +0x10
					float maxDistance;  // +0x14
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
					bool keepChecking;  // +0x20
					bool setTarget;  // +0x21
					unsigned char unknown22[0x2];
			};

			extern fight::Property** gAutoTargetPlayerTrackProperties;
			fight::TrackFactory* CreateAutoTargetPlayerTrackFactory(const char* name);
			void RegisterAutoTargetPlayerTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
