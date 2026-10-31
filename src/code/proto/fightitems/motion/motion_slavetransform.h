// Fight items of the motion group: SlaveTransformTrack (unit 0x101B3470 - 0x101B3980; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_SLAVETRANSFORM_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_SLAVETRANSFORM_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::SlaveTransformTrack (16 vftable slots, 0x30 bytes)
			class SlaveTransformTrack : public fight::Track
			{
			public:
				// 0x101B3520
				SlaveTransformTrack();
				virtual ~SlaveTransformTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10116020, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMasterObject(const fight::Name& newValue);
				bool SetOffset(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name masterObject;  // +0x10
					math::Vector offset;  // +0x18
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
					unsigned char unknown2C[0x4];
			};

			extern fight::Property** gSlaveTransformTrackProperties;
			fight::TrackFactory* CreateSlaveTransformTrackFactory(const char* name);
			void RegisterSlaveTransformTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
