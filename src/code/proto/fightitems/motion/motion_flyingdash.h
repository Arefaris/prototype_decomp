// Fight items of the motion group: FlyingDashTrack (unit 0x101601F0 - 0x10160940; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_FLYINGDASH_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_FLYINGDASH_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::FlyingDashTrack (16 vftable slots, 0x38 bytes)
			class FlyingDashTrack : public fight::Track
			{
			public:
				// 0x10160320
				FlyingDashTrack();
				virtual ~FlyingDashTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100BF310, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocityAdd(float newValue);
				bool SetVelocityMax(float newValue);
				bool SetPreserveYVelocity(bool newValue);
				bool SetDashToTargetGrabbableClass(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name dashToTargetGrabbableClass;  // +0x10
					float blendInTime;  // +0x18
					float blendOutTime;  // +0x1C
					float timeBegin;  // +0x20
					float timeEnd;  // +0x24
					float velocityAdd;  // +0x28
					float velocityMax;  // +0x2C
					int priority;  // +0x30
					bool preserveYVelocity;  // +0x34
					unsigned char unknown35[0x3];
			};

			extern fight::Property** gFlyingDashTrackProperties;
			fight::TrackFactory* CreateFlyingDashTrackFactory(const char* name);
			void RegisterFlyingDashTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
