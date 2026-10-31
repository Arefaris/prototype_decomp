// Fight items of the motion group: DriftTrack (unit 0x1015A810 - 0x1015AC70; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_DRIFT_H
#define PROTO_FIGHTITEMS_MOTION_DRIFT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::DriftTrack (16 vftable slots, 0x20 bytes)
			class DriftTrack : public fight::Track
			{
			public:
				// 0x1015A8C0
				DriftTrack();
				virtual ~DriftTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100B8D80, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMinVelocity(float newValue);
				bool SetMaxVelocity(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float maxVelocity;  // +0x10
					float minVelocity;  // +0x14
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
			};

			extern fight::Property** gDriftTrackProperties;
			fight::TrackFactory* CreateDriftTrackFactory(const char* name);
			void RegisterDriftTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
