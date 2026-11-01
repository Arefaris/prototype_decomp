// Fight items of the motion group: WallExitTrack (unit 0x101CBD20 - 0x101CC5E0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_WALLEXIT_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_WALLEXIT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::WallExitTrack (16 vftable slots, 0x48 bytes)
			class WallExitTrack : public fight::Track
			{
			public:
				// 0x101CBEE0
				WallExitTrack();
				virtual ~WallExitTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1012CB20, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetSupportingLimb(const fight::Name& newValue);
				bool SetVelocityMin(float newValue);
				bool SetVelocityMax(float newValue);
				bool SetGravity(float newValue);
				bool SetWallAngleUp(float newValue);
				bool SetWallAngleLateral(float newValue);
				bool SetWallAngleDown(float newValue);
				bool SetTurningVelocity(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name supportingLimb;  // +0x10
					float blendInTime;  // +0x18
					float blendOutTime;  // +0x1C
					float gravity;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
					float turningVelocity;  // +0x2C
					float velocityMax;  // +0x30
					float velocityMin;  // +0x34
					float wallAngleDown;  // +0x38
					float wallAngleLateral;  // +0x3C
					float wallAngleUp;  // +0x40
					int priority;  // +0x44
			};

			extern fight::Property** gWallExitTrackProperties;
			fight::TrackFactory* CreateWallExitTrackFactory(const char* name);
			void RegisterWallExitTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::WallExitAction (9 vftable slots, 0x40 bytes)
			class WallExitAction : public fight::Action
			{
			public:
				// 0x1012C180
				WallExitAction(WallExitTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x1012C050
				virtual ~WallExitAction();

				// vftable slot 5 (0x1012C230)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x1012C090)
				virtual void Slot6();
				// vftable slot 7 (0x1012C880)
				virtual bool Slot7(int arg, float value);

				core::Link<WallExitTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				choreo::RootDriver* driver;  // +0x2C
				float unknown30;  // +0x30
				float unknown34;  // +0x34
				float unknown38;  // +0x38
				bool unknown3C;  // +0x3C
				unsigned char unknown3D[0x3];
			};

			// ---- actions end
		}
	}
}

#endif
