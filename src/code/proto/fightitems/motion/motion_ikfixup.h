// Fight items of the motion group: IKSurfaceFixupTrack, ShoulderConFixupTrack (unit 0x10180090 - 0x10180910; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_IKFIXUP_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_IKFIXUP_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::IKSurfaceFixupTrack (16 vftable slots, 0x1C bytes)
			class IKSurfaceFixupTrack : public fight::Track
			{
			public:
				// 0x10180160
				IKSurfaceFixupTrack();
				virtual ~IKSurfaceFixupTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100DAEF0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetEnabled(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool enabled;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gIKSurfaceFixupTrackProperties;
			fight::TrackFactory* CreateIKSurfaceFixupTrackFactory(const char* name);
			void RegisterIKSurfaceFixupTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShoulderConFixupTrack (16 vftable slots, 0x1C bytes)
			class ShoulderConFixupTrack : public fight::Track
			{
			public:
				// 0x10180200
				ShoulderConFixupTrack();
				virtual ~ShoulderConFixupTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100DAF40, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetEnabled(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool enabled;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gShoulderConFixupTrackProperties;
			fight::TrackFactory* CreateShoulderConFixupTrackFactory(const char* name);
			void RegisterShoulderConFixupTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::IKSurfaceFixupAction (9 vftable slots, 0x2C bytes)
			class IKSurfaceFixupAction : public fight::Action
			{
			public:
				// 0x100DAB50
				IKSurfaceFixupAction(IKSurfaceFixupTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100DA9F0
				virtual ~IKSurfaceFixupAction();

				// vftable slot 5 (0x100DAC00)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100DAC90)
				virtual void Slot6();

				core::Link<IKSurfaceFixupTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::motion::ShoulderConFixupAction (9 vftable slots, 0x2C bytes)
			class ShoulderConFixupAction : public fight::Action
			{
			public:
				// 0x100DAD20
				ShoulderConFixupAction(ShoulderConFixupTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100DAA40
				virtual ~ShoulderConFixupAction();

				// vftable slot 5 (0x100DADD0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100DAE60)
				virtual void Slot6();

				core::Link<ShoulderConFixupTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
