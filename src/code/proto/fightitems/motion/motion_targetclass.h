// Fight items of the motion group: TargetClassTrack, TargetableTrack, TemporaryTargetableTrack (unit 0x101BD3C0 - 0x101BE030; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_TARGETCLASS_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_TARGETCLASS_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction2.h"
#include "code/engine/fight/effecttrack.h"
#include "code/proto/fightitems/motion/motionmessages2.h"

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

			// ---- actions begin
			// RTTI: proto::fightitems::motion::TargetClassAction (9 vftable slots, 0x3C bytes)
			class TargetClassAction : public fight::Action
			{
			public:
				// 0x1011F2C0
				TargetClassAction(TargetClassTrack* newTrack, engine::GameObjectHandle newTarget, fight::Track* listener, core::IRefCount* newOwner);
				// 0x1011F080
				virtual ~TargetClassAction();

				// vftable slot 5 (0x1011F390)
				virtual bool Slot5(int arg, float value);

				core::Link<TargetClassTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				engine::TrackWatch watch;  // +0x2C
				core::IRefCount* owner;  // +0x38
			};

			// RTTI: proto::fightitems::motion::TemporaryTargetableAction (9 vftable slots, 0x2C bytes)
			class TemporaryTargetableAction : public fight::Action
			{
			public:
				// 0x1011F560
				TemporaryTargetableAction(TemporaryTargetableTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x1011F140
				virtual ~TemporaryTargetableAction();

				// vftable slot 5 (0x1011F610)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x1011F750)
				virtual void Slot6();
				// vftable slot 7 (0x1011F740)
				virtual bool Slot7(int arg, float value);

				core::Link<TemporaryTargetableTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				bool targetable;  // +0x2C
				unsigned char unknown2D[0x3];
			};

			// RTTI: proto::fightitems::motion::TargetableAction (9 vftable slots, 0x2C bytes)
			class TargetableAction : public fight::Action
			{
			public:
				// 0x1011F420
				TargetableAction(TargetableTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x1011F0F0
				virtual ~TargetableAction();

				// vftable slot 5 (0x1011F4D0)
				virtual bool Slot5(int arg, float value);

				core::Link<TargetableTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
