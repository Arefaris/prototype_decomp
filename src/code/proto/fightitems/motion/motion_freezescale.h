// Fight items of the motion group: FreezeScaleTrack (unit 0x10161980 - 0x10161F50; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_FREEZESCALE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_FREEZESCALE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::FreezeScaleTrack (16 vftable slots, 0x30 bytes)
			class FreezeScaleTrack : public fight::Track
			{
			public:
				// 0x10161A60
				FreezeScaleTrack();
				virtual ~FreezeScaleTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100C0A20, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name partition;  // +0x10
					float blendInTime;  // +0x18
					float blendOutTime;  // +0x1C
					float timeBegin;  // +0x20
					float timeEnd;  // +0x24
					int priority;  // +0x28
					unsigned char unknown2C[0x4];
			};

			extern fight::Property** gFreezeScaleTrackProperties;
			fight::TrackFactory* CreateFreezeScaleTrackFactory(const char* name);
			void RegisterFreezeScaleTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
