// Fight items of the motion group: NoPushbackTrack (unit 0x101939C0 - 0x10193D60; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_NOPUSHBACK_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_NOPUSHBACK_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::NoPushbackTrack (16 vftable slots, 0x18 bytes)
			class NoPushbackTrack : public fight::Track
			{
			public:
				// 0x10193A30
				NoPushbackTrack();
				virtual ~NoPushbackTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100F6670, another unit)
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

			extern fight::Property** gNoPushbackTrackProperties;
			fight::TrackFactory* CreateNoPushbackTrackFactory(const char* name);
			void RegisterNoPushbackTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
