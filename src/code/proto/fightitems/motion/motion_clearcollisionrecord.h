// Fight items of the motion group: ClearCollisionRecordTrack (unit 0x10149A90 - 0x10149DC0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_CLEARCOLLISIONRECORD_H
#define PROTO_FIGHTITEMS_MOTION_CLEARCOLLISIONRECORD_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ClearCollisionRecordTrack (16 vftable slots, 0x14 bytes)
			class ClearCollisionRecordTrack : public fight::Track
			{
			public:
				// 0x10149AE0
				ClearCollisionRecordTrack();
				virtual ~ClearCollisionRecordTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100A2450, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gClearCollisionRecordTrackProperties;
			fight::TrackFactory* CreateClearCollisionRecordTrackFactory(const char* name);
			void RegisterClearCollisionRecordTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
