// Fight items of the motion group: BlockFramerCamTrack (unit 0x1035D8B0 - 0x1035DC50; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_BLOCKFRAMERCAM_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_BLOCKFRAMERCAM_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::BlockFramerCamTrack (16 vftable slots, 0x18 bytes)
			class BlockFramerCamTrack : public fight::Track
			{
			public:
				// 0x1035D920
				BlockFramerCamTrack();
				virtual ~BlockFramerCamTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1035A0B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
			};

			extern fight::Property** gBlockFramerCamTrackProperties;
			fight::TrackFactory* CreateBlockFramerCamTrackFactory(const char* name);
			void RegisterBlockFramerCamTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
