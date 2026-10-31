// Fight items of the motion group: TargetClassTrack, TargetableTrack, TemporaryTargetableTrack (unit 0x101BD3C0 - 0x101BE030; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_TARGETCLASS_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_TARGETCLASS_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::TargetClassTrack (16 vftable slots, 0x18 bytes)
			class TargetClassTrack : public fight::Track
			{
			public:
				// 0x101BD490
				TargetClassTrack();
				virtual ~TargetClassTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1011F800, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTargetClass(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					int targetClass;  // +0x14
			};

			extern fight::Property** gTargetClassTrackProperties;
			fight::TrackFactory* CreateTargetClassTrackFactory(const char* name);
			void RegisterTargetClassTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TargetableTrack (16 vftable slots, 0x14 bytes)
			class TargetableTrack : public fight::Track
			{
			public:
				// 0x101BD530
				TargetableTrack();
				virtual ~TargetableTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1011F870, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTargetable(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool targetable;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gTargetableTrackProperties;
			fight::TrackFactory* CreateTargetableTrackFactory(const char* name);
			void RegisterTargetableTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TemporaryTargetableTrack (16 vftable slots, 0x20 bytes)
			class TemporaryTargetableTrack : public fight::Track
			{
			public:
				// 0x101BD5C0
				TemporaryTargetableTrack();
				virtual ~TemporaryTargetableTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1011F8D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetOnBegin(int newValue);
				bool SetOnEnd(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int onBegin;  // +0x18
					int onEnd;  // +0x1C
			};

			extern fight::Property** gTemporaryTargetableTrackProperties;
			fight::TrackFactory* CreateTemporaryTargetableTrackFactory(const char* name);
			void RegisterTemporaryTargetableTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
